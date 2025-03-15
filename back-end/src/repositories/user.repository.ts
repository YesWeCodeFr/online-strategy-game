import { User, UserWithoutPassword } from '../types'

export class UserRepository {
  private users: Map<number, User>
  private currentId: number

  constructor() {
    console.log('UserRepository constructor')
    this.users = new Map()
    this.currentId = 1
  }

  create(nom: string, hashedPassword: string): UserWithoutPassword {
    const id = this.currentId++
    const user: User = { id, nom, password: hashedPassword }
    this.users.set(id, user)
    
    const { password, ...userWithoutPassword } = user
    return userWithoutPassword
  }

  findByName(nom: string): User | undefined {
    return Array.from(this.users.values()).find(user => user.nom === nom)
  }

  exists(nom: string): boolean {
    return this.findByName(nom) !== undefined
  }
} 