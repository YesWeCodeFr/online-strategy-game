import * as net from 'net';
import dotenv from 'dotenv'
import { encodeMessage, decodeMessage, MessageTypes } from '../protocol/protocol';
import { UserWithoutPassword } from 'user.types';

// Charger les variables d'environnement
dotenv.config()

export default class GameServerService {
  private static readonly GAME_SERVER_PORT = parseInt(process.env.GAME_SERVER_PORT || '8888');
  private static readonly GAME_SERVER_HOST = process.env.GAME_SERVER_HOST || 'localhost';
  
  private socket: net.Socket | null = null;
  private nextRequestId: number = 0;
  private pendingRequests: Map<number, {
    resolve: (value: UserWithoutPassword[]) => void;
    reject: (error: any) => void;
  }>;
  
  constructor() {
    console.log('GameServerService constructor')    
    this.pendingRequests = new Map();
  }
  
  connect(): Promise<void> {
    return new Promise((resolve, reject) => {
      console.log('Tentative de connexion au serveur de jeu...');
      this.socket = net.createConnection(
        GameServerService.GAME_SERVER_PORT, 
        GameServerService.GAME_SERVER_HOST, 
        () => {
          console.log('Socket connecté, envoi du HELLO...');          
          this.sendHello();
          // Attendons la réponse du HELLO avant de résoudre
          setTimeout(() => {
            resolve();
          }, 100); // Petit délai pour s'assurer que le HELLO est traité
        }
      );
      
      this.socket.on('data', (data) => {
        try {
          const message = decodeMessage(data);
          this.handleMessage(message.requestId, message.type, message.payload);
        } catch (error) {
          console.error('Erreur de décodage:', error);
        }
      });
      
      this.socket.on('error', (error) => {
        console.error('Erreur de connexion:', error);
        reject(error);
      });
      
      this.socket.on('close', () => {
        console.log('Connexion fermée');
        this.socket = null;
      });
    });
  }
  
  private sendHello(): void {    
    console.log("Envoi du message HELLO")
    if (!this.socket) {
      console.error("Impossible d'envoyer HELLO: socket null");
      return;
    }
    
    const payload = {
      version: 1
    };
    
    const requestId = this.nextRequestId++;    
    const buffer = encodeMessage(requestId, MessageTypes.MESSAGE_TYPE_HELLO, payload);
    this.socket.write(buffer);
    console.log("Message HELLO envoyé avec requestId:", requestId);
  }
  
  addPlayer(playerId: number, username: string): void {
    if (!this.socket) return;
    
    const payload = {
      playerId,
      username
    };
    
    const buffer = encodeMessage(this.nextRequestId++, MessageTypes.MESSAGE_TYPE_ADD_PLAYER, payload);
    this.socket.write(buffer);
  }

  getPlayerList(): Promise<UserWithoutPassword[]> {
    console.log("getPlayerList() ...")
    const requestId = this.nextRequestId++;
    const promise = new Promise<UserWithoutPassword[]>((resolve, reject) => {
      if (!this.socket) {
        reject(new Error("Rejet : connexion fermée"));
        return;
      }
      this.pendingRequests.set(requestId, { resolve, reject });
      const buffer = encodeMessage(requestId, MessageTypes.MESSAGE_TYPE_GET_PLAYER_LIST, {});
      console.log("Envoi des données ... " + requestId);
      this.socket.write(buffer);
      console.log("Données envoyées ...");
    });

    promise.finally(() => {
      console.log("fin de la promesse ...")
      this.pendingRequests.delete(requestId);
    });

    return promise;
  }
  
  getOldPlayerList(): Promise<UserWithoutPassword[]> {
    console.log("getOldPlayerList() ...")
    return new Promise((resolve, reject) => {
      console.log("résolution de la promesse ...")
      if (!this.socket) {
        this.connect()  // Reconnexion si le socket n'existe pas
          .then(() => this.sendPlayerListRequest(resolve, reject))
          .catch(reject);
      } else {
        this.sendPlayerListRequest(resolve, reject);
      }
      console.log("fin de la promesse")      
    });
  }
  
  private sendPlayerListRequest(resolve: (users: UserWithoutPassword[]) => void, reject: (error: Error) => void): void {
    console.log("sendPlayerListRequest ...")
    const buffer = encodeMessage(this.nextRequestId++, MessageTypes.MESSAGE_TYPE_GET_PLAYER_LIST, {});
    this.socket?.write(buffer);
    console.log("socket écrit ...")
    resolve([])

    /*
    this.socket?.once('data', (data) => {
      console.log("message reçu ...")
      if (!this.socket) {
        console.error('Le socket est déjà fermé, impossible de traiter les données.');
        return;
      }

      try {
        console.log('getPlayerList data : ', data);
        const message = decodeMessage(data);
        if (message.type === MessageTypes.MESSAGE_TYPE_PLAYER_LIST) {
          const usersWithoutPassword: UserWithoutPassword[] = message.payload.players.map((player: any) => ({
            id: player.player_id,
            username: player.username
          }));
          resolve(usersWithoutPassword);
        } else {
          reject(new Error('Type de message inconnu reçu'));
        }
      } catch (error) {
        reject(new Error('Erreur de décodage du message: ' + error));
      }
    });
    */
  }
  
  private handleMessage(requestId: number, type: number, payload: any): void {
    console.log('Message reçu : ' + requestId + ',' + type)
    switch (type) {
      case MessageTypes.MESSAGE_TYPE_HELLO:
        console.log('Message Hello reçu:', payload);
        break;
      case MessageTypes.MESSAGE_TYPE_PLAYER_LIST:
        console.log('Liste des joueurs reçue:', payload.players);
        const pendingRequest = this.pendingRequests.get(requestId);
        if (pendingRequest) {          
          if (payload.players) {
            const usersWithoutPassword: UserWithoutPassword[] = payload.players.map((player: any) => ({
              id: player.playerId,
              username: player.username
            }));
            pendingRequest.resolve(usersWithoutPassword);
          } else  {
            pendingRequest.resolve([]);
          }
        }
        break;
      default:
        console.log('Message inconnu reçu:', type, payload);
    }
  }
  
  disconnect(): void {
    if (this.socket) {
      this.socket.end();
      this.socket = null;
    }
  }
} 