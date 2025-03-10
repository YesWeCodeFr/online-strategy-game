import net from 'net'
import dotenv from 'dotenv'

// Charger les variables d'environnement
dotenv.config()

export class GameServerService {
  private readonly GAME_SERVER_PORT = parseInt(process.env.GAME_SERVER_PORT || '8888')
  private readonly GAME_SERVER_HOST = process.env.GAME_SERVER_HOST || 'localhost'

  async notifyNewPlayer(userId: number): Promise<void> {
    return new Promise((resolve, reject) => {
      const client = new net.Socket()

      client.connect(this.GAME_SERVER_PORT, this.GAME_SERVER_HOST, () => {
        console.log(`Connexion établie avec le serveur de jeu pour l'utilisateur ${userId}`)
        
        client.write(userId.toString(), () => {
          client.end()
        })
      })

      client.on('error', (error) => {
        console.error('Erreur de connexion au serveur de jeu:', error)
        reject(error)
      })

      client.on('close', () => {
        console.log(`Notification réussie au serveur de jeu pour l'utilisateur ${userId}`)
        resolve()
      })
    })
  }
} 