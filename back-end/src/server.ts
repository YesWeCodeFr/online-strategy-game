import fastify, { FastifyInstance } from 'fastify'
import cors from '@fastify/cors'
import userRoutes from './routes/user.routes'

const server: FastifyInstance = fastify({ logger: true })

// Activation du CORS
server.register(cors, {
  origin: true
})

// Enregistrement des routes avec préfixe /api
server.register(userRoutes, { prefix: '/api' })

// Démarrage du serveur
const start = async (): Promise<void> => {
  try {
    await server.listen({ port: 3000 })
  } catch (err) {
    server.log.error(err)
    process.exit(1)
  }
}

start() 