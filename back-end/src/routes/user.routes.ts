import { FastifyInstance, FastifyRequest, FastifyReply } from 'fastify'
import { UserController } from '../controllers/user.controller'
import { FastifyPluginAsync } from 'fastify'

interface CreateUserBody {
  nom: string
  password: string
}

const userRoutes: FastifyPluginAsync = async (fastify: FastifyInstance): Promise<void> => {
  const userController = new UserController()

  fastify.post<{ Body: CreateUserBody }>(
    '/users',
    async (request: FastifyRequest<{ Body: CreateUserBody }>, reply: FastifyReply) => {
      return userController.createUser(request, reply)
      //reply.code(201).send(user)
    }
  )

  fastify.post<{ Body: CreateUserBody }>(
    '/login',
    async (request: FastifyRequest<{ Body: CreateUserBody }>, reply: FastifyReply) => {
      return userController.login(request, reply)
    }
  )
}

export default userRoutes 