import * as net from 'net';
import { encodeMessage, decodeMessage, MessageTypes } from './protocol/protocol';

export class GameServerConnection {
  private socket: net.Socket | null = null;
  
  constructor(private host: string, private port: number) {}
  
  connect(): Promise<void> {
    return new Promise((resolve, reject) => {
      this.socket = net.createConnection(this.port, this.host, () => {
        console.log('Connecté au serveur de jeu');
        
        // Envoyer un message HELLO
        this.sendHello();
        
        resolve();
      });
      
      this.socket.on('data', (data) => {
        try {
          const message = decodeMessage(data);
          this.handleMessage(message.type, message.payload);
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
    if (!this.socket) return;
    
    const payload = {
      version: 1
    };
    
    const buffer = encodeMessage(MessageTypes.HELLO, payload);
    this.socket.write(buffer);
  }
  
  addPlayer(playerId: number, username: string): void {
    if (!this.socket) return;
    
    const payload = {
      playerId,
      username
    };
    
    const buffer = encodeMessage(MessageTypes.ADD_PLAYER, payload);
    this.socket.write(buffer);
  }
  
  getPlayerList(): void {
    if (!this.socket) return;
    
    const buffer = encodeMessage(MessageTypes.GET_PLAYER_LIST, {});
    this.socket.write(buffer);
  }
  
  private handleMessage(type: number, payload: any): void {
    switch (type) {
      case MessageTypes.HELLO:
        console.log('Message HELLO reçu:', payload);
        break;
      case MessageTypes.PLAYER_LIST:
        console.log('Liste des joueurs reçue:', payload.players);
        // Traiter la liste des joueurs
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