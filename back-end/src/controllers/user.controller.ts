import { FastifyRequest, FastifyReply } from 'fastify'
import { UserService } from '../services/user.service'

interface CreateUserBody {
  nom: string
  password: string
}

export class UserController {
  private userService: UserService

  constructor() {
    this.userService = new UserService()
  }

  public createUser = async (
    request: FastifyRequest<{ Body: CreateUserBody }>,
    reply: FastifyReply
  ): Promise<void> => {
    try {
      const { nom, password } = request.body
      const user = await this.userService.createUser(nom, password)
      reply.code(201).send(user)
    } catch (error) {
      reply.code(400).send({ error: (error as Error).message })
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
} 