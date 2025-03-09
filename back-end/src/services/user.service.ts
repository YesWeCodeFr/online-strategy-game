import bcrypt from 'bcrypt'
import net from 'net'
import { UserRepository } from '../repositories/user.repository'
import { UserWithoutPassword, LoginResponse } from '../types'

export class UserService {
  private userRepository: UserRepository
  private readonly GAME_SERVER_PORT = 8888
  private readonly GAME_SERVER_HOST = 'localhost'

  constructor() {
    this.userRepository = new UserRepository()
  }

  private async notifyGameServer(userId: number): Promise<void> {
    return new Promise((resolve, reject) => {
      const client = new net.Socket()

      client.connect(this.GAME_SERVER_PORT, this.GAME_SERVER_HOST, () => {
        console.log(`Connexion établie avec le serveur de jeu pour l'utilisateur ${userId}`)
        client.write(userId.toString(), () => {
          // Fermer la connexion après l'envoi des données
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

  async createUser(nom: string, password: string): Promise<UserWithoutPassword> {
    if (!nom || !password) {
      throw new Error('Le nom et le mot de passe sont requis')
    }

    if (this.userRepository.exists(nom)) {
      throw new Error('Un utilisateur avec ce nom existe déjà')
    }

    const hashedPassword = await bcrypt.hash(password, 10)
    const newUser = this.userRepository.create(nom, hashedPassword)

    try {
      // Notification au serveur de jeu
      await this.notifyGameServer(newUser.id)
    } catch (error) {
      console.error('Impossible de notifier le serveur de jeu:', error)
      // On ne bloque pas la création de l'utilisateur si la notification échoue
    }

    return newUser
  }

  async login(nom: string, password: string): Promise<LoginResponse> {
    const user = this.userRepository.findByName(nom)
    if (!user) {
      throw new Error('Utilisateur non trouvé')
    }

    const isValidPassword = await bcrypt.compare(password, user.password)
    if (!isValidPassword) {
      throw new Error('Mot de passe incorrect')
    }

    const { password: _, ...userWithoutPassword } = user
    return { 
      message: 'Connexion réussie', 
      user: userWithoutPassword 
    }
  }
} 