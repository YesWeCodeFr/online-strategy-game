import { API_URL } from '../config/config';

// Définition de l'interface User
export interface User {
  id: number; // Identifiant unique de l'utilisateur
  nom: string; // Nom de l'utilisateur
}

// Définition de UserListResponse comme un tableau de User
export type UserListResponse = User[];

// Nouvelle fonction pour obtenir la liste des utilisateurs
export const getUsers = async (): Promise<UserListResponse> => {
  const response = await fetch(`${API_URL}/users`) // Appel à l'API pour obtenir la liste des utilisateurs
  if (!response.ok) {
    throw new Error('Erreur lors de la récupération des utilisateurs')
  }
  return response.json()
} 