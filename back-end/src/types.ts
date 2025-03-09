export interface User {
  id: number
  nom: string
  password: string
}

export type UserWithoutPassword = Omit<User, 'password'>

export interface LoginResponse {
  message: string
  user: UserWithoutPassword
} 