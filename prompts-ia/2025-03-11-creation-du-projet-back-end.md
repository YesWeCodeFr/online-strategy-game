[Retour vers le sommaire](sommaire.md)

# Création du projet back-end (11/03/2025)
## Prompt
```
# [DEV] [BACK-END] Création de l'application Back-end

## contexte
- repository multi-projet. 
- pour l'instant seul le projet front-end a été initialisé
- J'aimerai créer le projet correspondant au back-end avec ces contraintes :
  - application implémentée en node js
  - framework de routage : fastify
  - pas de base de données pour l'instant, une implémentation en mémoire est demandée
  -  Une API concerne la création d'un utilisateur dont les informations sont : 
    - id
    - nom
    - mot de passe (qui sera stocké hashé)
  - Un autre API de login qui vérifie que le user existe et que le mot de passe en correcttement renseigné

```

## Réponse

Je vais vous aider à créer l'application back-end avec les spécifications demandées.

Voici la structure de projet proposée :
```
backend/
├── package.json
├── src/
│   ├── server.js
│   ├── routes/
│   │   └── user.routes.js
│   ├── controllers/
│   │   └── user.controller.js
│   ├── services/
│   │   └── user.service.js
│   └── repositories/
│       └── user.repository.js
```

Commençons par initialiser le projet :
```bash
mkdir backend
cd backend
npm init -y
npm install fastify @fastify/cors bcrypt
```
Voici les différents fichiers nécessaires :
1. **package.json :**
```json
{
  "name": "backend",
  "version": "1.0.0",
  "description": "",
  "main": "src/server.js",
  "scripts": {
    "start": "node src/server.js",
    "dev": "nodemon src/server.js"
  },
  "dependencies": {
    "fastify": "^4.x.x",
    "@fastify/cors": "^8.x.x",
    "bcrypt": "^5.x.x"
  },
  "devDependencies": {
    "nodemon": "^2.x.x"
  }
}
```
2. **server.js :**
```javascript
const fastify = require('fastify')({ logger: true })
const cors = require('@fastify/cors')
const userRoutes = require('./routes/user.routes')

// Activation du CORS
fastify.register(cors, {
  origin: true
})

// Enregistrement des routes
fastify.register(userRoutes)

// Démarrage du serveur
const start = async () => {
  try {
    await fastify.listen({ port: 3000 })
  } catch (err) {
    fastify.log.error(err)
    process.exit(1)
  }
}

start()
```
3. **user.routes.js :**
```javascript
const UserController = require('../controllers/user.controller')

async function routes(fastify, options) {
  const userController = new UserController()

  fastify.post('/users', userController.createUser)
  fastify.post('/login', userController.login)
}

module.exports = routes
```
4. **user.controller.js :**
```javascript
const UserService = require('../services/user.service')

class UserController {
  constructor() {
    this.userService = new UserService()
  }

  createUser = async (request, reply) => {
    try {
      const { nom, password } = request.body
      const user = await this.userService.createUser(nom, password)
      reply.code(201).send(user)
    } catch (error) {
      reply.code(400).send({ error: error.message })
    }
  }

  login = async (request, reply) => {
    try {
      const { nom, password } = request.body
      const result = await this.userService.login(nom, password)
      reply.code(200).send(result)
    } catch (error) {
      reply.code(401).send({ error: error.message })
    }
  }
}

module.exports = UserController
```
5. **user.service.js : **
```typescript
const bcrypt = require('bcrypt')
const UserRepository = require('../repositories/user.repository')

class UserService {
  constructor() {
    this.userRepository = new UserRepository()
  }

  async createUser(nom, password) {
    if (!nom || !password) {
      throw new Error('Le nom et le mot de passe sont requis')
    }

    const hashedPassword = await bcrypt.hash(password, 10)
    return this.userRepository.create(nom, hashedPassword)
  }

  async login(nom, password) {
    const user = this.userRepository.findByName(nom)
    if (!user) {
      throw new Error('Utilisateur non trouvé')
    }

    const isValidPassword = await bcrypt.compare(password, user.password)
    if (!isValidPassword) {
      throw new Error('Mot de passe incorrect')
    }

    return { message: 'Connexion réussie', userId: user.id }
  }
}

module.exports = UserService
```
6. **user.repository.js : **
```typescript
class UserRepository {
  constructor() {
    this.users = new Map()
    this.currentId = 1
  }

  create(nom, hashedPassword) {
    const id = this.currentId++
    const user = { id, nom, password: hashedPassword }
    this.users.set(id, user)
    
    // On retourne l'utilisateur sans le mot de passe
    const { password, ...userWithoutPassword } = user
    return userWithoutPassword
  }

  findByName(nom) {
    return Array.from(this.users.values()).find(user => user.nom === nom)
  }
}

module.exports = UserRepository
```
Pour tester l'API, vous pouvez utiliser ces requêtes curl :
```bash
# Création d'un utilisateur
curl -X POST http://localhost:3000/users \
  -H "Content-Type: application/json" \
  -d '{"nom": "test", "password": "password123"}'

# Login
curl -X POST http://localhost:3000/login \
  -H "Content-Type: application/json" \
  -d '{"nom": "test", "password": "password123"}'
```
Cette implémentation offre :
- Une architecture en couches (routes -> controller -> service -> repository)
- Un stockage en mémoire des utilisateurs avec Map
- Le hachage des mots de passe avec bcrypt
- La gestion des erreurs
- Une API RESTful avec Fastify
- Support CORS pour l'interaction avec le frontend
Pour lancer l'application :
```bash
npm install
npm run dev
```
L'API sera disponible sur http://localhost:3000.

## Prompt

j'aimerai que le repertoire du projet back-end s'appelle \"back-end\" et que l'application back-end se nomme \"back-end\"

## Réponse

Je vais ajuster les noms selon votre demande.

Voici la nouvelle structure :

```
back-end/
├── package.json
├── src/
│   ├── server.js
│   ├── routes/
│   │   └── user.routes.js
│   ├── controllers/
│   │   └── user.controller.js
│   ├── services/
│   │   └── user.service.js
│   └── repositories/
│       └── user.repository.js
```

Pour initialiser le projet avec le nouveau nom :

```bash
mkdir back-end
cd back-end
npm init -y
npm install fastify @fastify/cors bcrypt
```

Le seul fichier qui nécessite une modification est le package.json :

```json:back-end/package.json
{
  "name": "back-end",
  "version": "1.0.0",
  "description": "",
  "main": "src/server.js",
  "scripts": {
    "start": "node src/server.js",
    "dev": "nodemon src/server.js"
  },
  "dependencies": {
    "fastify": "^4.x.x",
    "@fastify/cors": "^8.x.x",
    "bcrypt": "^5.x.x"
  },
  "devDependencies": {
    "nodemon": "^2.x.x"
  }
}
```

Tous les autres fichiers restent identiques, seul leur emplacement change (ils seront maintenant dans le dossier `back-end` au lieu de `backend`).

Pour lancer l'application :
```bash
cd back-end
npm install
npm run dev
```

L'API sera toujours disponible sur `http://localhost:3000`.


## Prompt

pouvez-vous ajouter le fichier .gitignore dans le dossier back-end ?

## Réponse

Voici le contenu recommandé pour le fichier .gitignore du projet back-end :

```text:back-end/.gitignore
# Dependencies
node_modules/
npm-debug.log
yarn-debug.log
yarn-error.log

# Environment variables
.env
.env.local
.env.*.local

# IDE
.idea/
.vscode/
*.swp
*.swo

# OS
.DS_Store
Thumbs.db

# Logs
logs/
*.log

# Build
dist/
build/
```

Ce fichier .gitignore couvre :
- Les dépendances Node.js
- Les fichiers de configuration d'environnement
- Les fichiers spécifiques aux IDEs
- Les fichiers système
- Les logs
- Les dossiers de build potentiels

## Prompt

J'aimerai que le projet soit entioèrement écrit en typescript, et disposer d'un serveur qui a la capacité de hot-reloading en compilant le code typescript à la volée

## Réponse

Je vais modifier le projet pour utiliser TypeScript avec hot-reloading. Nous allons utiliser `ts-node-dev` pour le développement.

D'abord, mettons à jour le package.json avec les dépendances TypeScript nécessaires :

```json:back-end/package.json
{
  "name": "back-end",
  "version": "1.0.0",
  "description": "",
  "main": "dist/server.js",
  "scripts": {
    "start": "node dist/server.js",
    "dev": "ts-node-dev --respawn --transpile-only src/server.ts",
    "build": "tsc",
    "lint": "eslint . --ext .ts",
    "type-check": "tsc --noEmit"
  },
  "dependencies": {
    "fastify": "^4.x.x",
    "@fastify/cors": "^8.x.x",
    "bcrypt": "^5.x.x"
  },
  "devDependencies": {
    "@types/node": "^20.x.x",
    "@types/bcrypt": "^5.x.x",
    "@typescript-eslint/eslint-plugin": "^6.x.x",
    "@typescript-eslint/parser": "^6.x.x",
    "eslint": "^8.x.x",
    "ts-node-dev": "^2.x.x",
    "typescript": "^5.x.x"
  }
}
```

Ajoutons un fichier de configuration TypeScript :

```json:back-end/tsconfig.json
{
  "compilerOptions": {
    "target": "ES2020",
    "module": "commonjs",
    "lib": ["ES2020"],
    "outDir": "./dist",
    "rootDir": "./src",
    "strict": true,
    "esModuleInterop": true,
    "skipLibCheck": true,
    "forceConsistentCasingInFileNames": true,
    "moduleResolution": "node",
    "resolveJsonModule": true,
    "baseUrl": ".",
    "paths": {
      "*": ["node_modules/*"]
    }
  },
  "include": ["src/**/*"],
  "exclude": ["node_modules", "dist"]
}
```

Maintenant, convertissons tous les fichiers en TypeScript :

1. **server.ts** :
```typescript:back-end/src/server.ts
import fastify, { FastifyInstance } from 'fastify'
import cors from '@fastify/cors'
import { userRoutes } from './routes/user.routes'

const server: FastifyInstance = fastify({ logger: true })

// Activation du CORS
server.register(cors, {
  origin: true
})

// Enregistrement des routes
server.register(userRoutes)

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
```

2. **types.ts** (nouveau fichier pour les interfaces) :
```typescript:back-end/src/types.ts
export interface User {
  id: number
  nom: string
  password: string
}

export type UserWithoutPassword = Omit<User, 'password'>

export interface LoginResponse {
  message: string
  userId: number
}
```

3. **user.routes.ts** :
```typescript:back-end/src/routes/user.routes.ts
import { FastifyInstance, FastifyRequest, FastifyReply } from 'fastify'
import { UserController } from '../controllers/user.controller'

interface CreateUserBody {
  nom: string
  password: string
}

export async function userRoutes(fastify: FastifyInstance): Promise<void> {
  const userController = new UserController()

  fastify.post<{ Body: CreateUserBody }>(
    '/users',
    async (request: FastifyRequest<{ Body: CreateUserBody }>, reply: FastifyReply) => {
      return userController.createUser(request, reply)
    }
  )

  fastify.post<{ Body: CreateUserBody }>(
    '/login',
    async (request: FastifyRequest<{ Body: CreateUserBody }>, reply: FastifyReply) => {
      return userController.login(request, reply)
    }
  )
}
```

4. **user.controller.ts** :
```typescript:back-end/src/controllers/user.controller.ts
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
```

5. **user.service.ts** :
```typescript:back-end/src/services/user.service.ts
import bcrypt from 'bcrypt'
import { UserRepository } from '../repositories/user.repository'
import { UserWithoutPassword, LoginResponse } from '../types'

export class UserService {
  private userRepository: UserRepository

  constructor() {
    this.userRepository = new UserRepository()
  }

  async createUser(nom: string, password: string): Promise<UserWithoutPassword> {
    if (!nom || !password) {
      throw new Error('Le nom et le mot de passe sont requis')
    }

    const hashedPassword = await bcrypt.hash(password, 10)
    return this.userRepository.create(nom, hashedPassword)
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

    return { message: 'Connexion réussie', userId: user.id }
  }
}
```

6. **user.repository.ts** :
```typescript:back-end/src/repositories/user.repository.ts
import { User, UserWithoutPassword } from '../types'

export class UserRepository {
  private users: Map<number, User>
  private currentId: number

  constructor() {
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
}
```

Pour installer et démarrer le projet :

```bash
cd back-end
npm install
npm run dev
```

Le serveur démarrera avec hot-reloading activé, ce qui signifie que :
- Les modifications de code seront automatiquement détectées
- Le code TypeScript sera recompilé à la volée
- Le serveur redémarrera automatiquement
- Les erreurs de type seront signalées immédiatement

Les avantages de cette configuration :
- Type safety avec TypeScript
- Hot-reloading pour un développement plus rapide
- Meilleure maintenabilité grâce aux interfaces et types
- Support complet d'IDE avec autocomplétion
- Détection d'erreurs plus tôt dans le cycle de développement

