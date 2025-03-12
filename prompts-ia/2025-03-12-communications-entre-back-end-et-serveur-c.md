[Retour vers le sommaire](sommaire.md)

# Création du projet serveur de jeu en C (12/03/2025)
## Prompt
```
Dans l'application back-end, le service user.service.ts possède une fonction afin de créer un user.
- Dès lors qu'un user est créé avec succès, j'aimerai qu'un appel vers le serveur de jeu se fasse au travers d'une socket afin de communiquer l'id du joueur créé au serveur de jeu
```

## Réponse



Je vais modifier le service `user.service.ts` pour ajouter la communication avec le serveur de jeu. Voici les modifications nécessaires :

back-end/src/services/user.service.ts
```typescript
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
        client.write(userId.toString())
      })

      client.on('error', (error) => {
        console.error('Erreur de connexion au serveur de jeu:', error)
        reject(error)
      })

      client.on('close', () => {
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

  // ... existing code ...
}
```

Les modifications apportées sont :
1. Import du module `net` pour la gestion des sockets
2. Ajout des constantes pour la configuration du serveur de jeu
3. Création d'une méthode privée `notifyGameServer` qui gère la communication socket
4. Modification de la méthode `createUser` pour notifier le serveur de jeu après la création réussie d'un utilisateur

La notification au serveur de jeu est gérée de manière asynchrone et ne bloque pas la création de l'utilisateur en cas d'échec. Si le serveur de jeu n'est pas disponible, un message d'erreur sera affiché dans la console, mais l'utilisateur sera quand même créé dans la base de données.

## Prompt
```
j'aimerai disposer d'une log dans la console javascript si la fonction notifyGameServer a bien appelé le serveur de jeu
```

## Réponse

Je vais modifier la méthode `notifyGameServer` pour ajouter des logs de succès :

back-end/src/services/user.service.ts
```typescript
private async notifyGameServer(userId: number): Promise<void> {
  return new Promise((resolve, reject) => {
    const client = new net.Socket()

    client.connect(this.GAME_SERVER_PORT, this.GAME_SERVER_HOST, () => {
      console.log(`Connexion établie avec le serveur de jeu pour l'utilisateur ${userId}`)
      client.write(userId.toString())
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
```

Les modifications ajoutent :
1. Un log lors de la connexion réussie au serveur
2. Un log lors de la fermeture de la connexion, confirmant que la notification a été envoyée

Ces logs vous permettront de suivre le processus de notification dans la console du back-end.

## Prompt
```
A priori je ne vois aucune log dans la console, ni la log de connexion établie ni la log de notification réussie
```

## Réponse

Le problème vient probablement du fait que nous ne fermons pas explicitement la connexion socket côté client après l'envoi des données. Voici la correction :

back-end/src/services/user.service.ts
```typescript
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
```

Les modifications principales sont :
1. Ajout de `client.end()` après l'envoi des données
2. Utilisation du callback de `write()` pour s'assurer que les données sont envoyées avant de fermer la connexion

Maintenant, vous devriez voir les logs apparaître dans la console car :
- La connexion est établie
- Les données sont envoyées
- La connexion est fermée proprement, déclenchant l'événement 'close'

## Prompt
```
dans l'applmication back-end, le service user.service.ts encapsule les appels vers le serveur de jeu game-server.
J'aimerai créer un service qui s'occupe de communiquer avec le serveur de jeu
```

## Réponse



Je vais créer un nouveau service dédié à la communication avec le serveur de jeu. Voici la structure proposée :

back-end/src/services/game-server.service.ts
```typescript
import net from 'net'

export class GameServerService {
  private readonly GAME_SERVER_PORT = 8888
  private readonly GAME_SERVER_HOST = 'localhost'

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
```

Et voici la modification nécessaire dans le service utilisateur :

back-end/src/services/user.service.ts
```typescript
import bcrypt from 'bcrypt'
import { UserRepository } from '../repositories/user.repository'
import { UserWithoutPassword, LoginResponse } from '../types'
import { GameServerService } from './game-server.service'

export class UserService {
  private userRepository: UserRepository
  private gameServerService: GameServerService

  constructor() {
    this.userRepository = new UserRepository()
    this.gameServerService = new GameServerService()
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
      await this.gameServerService.notifyNewPlayer(newUser.id)
    } catch (error) {
      console.error('Impossible de notifier le serveur de jeu:', error)
      // On ne bloque pas la création de l'utilisateur si la notification échoue
    }

    return newUser
  }

  // ... existing code ...
}
```

Les avantages de cette nouvelle structure sont :
1. Séparation claire des responsabilités
2. Le `GameServerService` peut être réutilisé par d'autres services si nécessaire
3. Toute la logique de communication avec le serveur de jeu est centralisée
4. Plus facile à maintenir et à étendre avec de nouvelles fonctionnalités

À l'avenir, vous pourrez facilement ajouter d'autres méthodes dans le `GameServerService` pour d'autres types de communications avec le serveur de jeu.

## Prompt
```
J'aimerai également externaliser dans un service la gestion des hash de password
```

## Réponse


Je vais créer un nouveau service pour gérer le hachage des mots de passe. Voici la structure proposée :

back-end/src/services/password.service.ts
```typescript
import bcrypt from 'bcrypt'

export class PasswordService {
  private readonly SALT_ROUNDS = 10

  async hash(password: string): Promise<string> {
    return bcrypt.hash(password, this.SALT_ROUNDS)
  }

  async compare(password: string, hashedPassword: string): Promise<boolean> {
    return bcrypt.compare(password, hashedPassword)
  }
}
```

Et voici la modification du service utilisateur pour utiliser ce nouveau service :

back-end/src/services/user.service.ts
```typescript
import { UserRepository } from '../repositories/user.repository'
import { UserWithoutPassword, LoginResponse } from '../types'
import { GameServerService } from './game-server.service'
import { PasswordService } from './password.service'

export class UserService {
  private userRepository: UserRepository
  private gameServerService: GameServerService
  private passwordService: PasswordService

  constructor() {
    this.userRepository = new UserRepository()
    this.gameServerService = new GameServerService()
    this.passwordService = new PasswordService()
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
      await this.gameServerService.notifyNewPlayer(newUser.id)
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
```

Les avantages de cette nouvelle structure sont :
1. Séparation de la logique de hachage des mots de passe
2. Centralisation des paramètres de hachage (comme le nombre de tours de sel)
3. Réutilisabilité du service pour d'autres besoins de hachage
4. Plus facile à maintenir et à tester
5. Plus facile à modifier si on veut changer l'algorithme de hachage dans le futur
