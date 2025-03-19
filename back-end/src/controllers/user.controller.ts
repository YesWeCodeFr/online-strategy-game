import { FastifyRequest, FastifyReply } from 'fastify'
import { UserService } from '../services/user.service'
import { UserWithoutPassword } from 'user.types'

interface CreateUserBody {
  nom: string
  password: string
}

export class UserController {
  private userService: UserService

  constructor() {
    console.log('UserController constructor')
    this.userService = new UserService()
  }

  public createUser = async (
    request: FastifyRequest<{ Body: CreateUserBody }>,
    reply: FastifyReply
  ): Promise<void> => {
    try {
      const { nom, password } = request.body
      const user = await this.userService.createUser(nom, password)
      return reply.code(201).send(user)
    } catch (error) {
      console.error('Error creating user:', error)
      return reply.code(400).send({ error: (error as Error).message })
    }
  }

  public login = async (
    request: FastifyRequest<{ Body: CreateUserBody }>,
    reply: FastifyReply
  ): Promise<void> => {
    try {
      const { nom, password } = request.body
      const result = await this.userService.login(nom, password)
      reply.code(200).send(result)
    } catch (error) {
      reply.code(401).send({ error: (error as Error).message })
    }
  }

  public getUsers = async (
    request: FastifyRequest,
    reply: FastifyReply
  ): Promise<UserWithoutPassword[]> => {
    try {
      console.log('getUsers (dans user.controller) ...') 
      const users = await this.userService.getUsers()
      console.log('getUsers : ', users)
      return reply.code(200).send(users)
    } catch (error) {
      console.error('Error fetching users:', error)
      return reply.code(500).send({ error: (error as Error).message })
    }
  }
} 