import { UserRepository } from '../repositories/user.repository'
import { UserWithoutPassword, LoginResponse } from '../types'
import { GameServerService } from './game-server.service'
import { PasswordService } from './password.service'
import { GameServerConnection } from '../game-server-connection'

export class UserService {
  private userRepository: UserRepository
  // private gameServerService: GameServerService
  private passwordService: PasswordService
  private gameServerConnection: GameServerConnection

  constructor() {
    console.log('UserService constructor')
    this.userRepository = new UserRepository()
    // this.gameServerService = new GameServerService()
    this.passwordService = new PasswordService()
    this.gameServerConnection = new GameServerConnection()
    console.log("gameServerConnection", this.gameServerConnection)
    this.gameServerConnection.connect()
  }

  async createUser(nom: string, password: string): Promise<UserWithoutPassword> {
    if (!nom || !password) {
      throw new Error('Le nom et le mot de passe sont requis')
    }

    if (this.userRepository.exists(nom)) {
      throw new Error('Un utilisateur avec ce nom existe déjà')
    }

    const hashedPassword = await this.passwordService.hash(password)
    const newUser = this.userRepository.create(nom, hashedPassword)

    try {
      // await this.gameServerService.notifyNewPlayer(newUser.id)
      await this.gameServerConnection.addPlayer(newUser.id, newUser.nom)
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

    const isValidPassword = await this.passwordService.compare(password, user.password)
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