// Simulation d'une base de données utilisateurs
const users = new Map<string, { username: string; password: string }>();

interface AuthResponse {
  userId: string;
}

export const authService = {
  login: async (username: string, password: string): Promise<AuthResponse> => {
    // Simulation d'un délai réseau
    await new Promise(resolve => setTimeout(resolve, 500));

    const user = Array.from(users.entries()).find(
      ([_, userData]) => userData.username === username && userData.password === password
    );

    if (user) {
      return { userId: user[0] };
    }

    throw new Error('Identifiants invalides');
  },

  register: async (username: string, password: string): Promise<AuthResponse> => {
    // Simulation d'un délai réseau
    await new Promise(resolve => setTimeout(resolve, 500));

    // Vérifie si l'utilisateur existe déjà
    const userExists = Array.from(users.values()).some(
      userData => userData.username === username
    );

    if (userExists) {
      throw new Error('Cet utilisateur existe déjà');
    }

    // Crée un nouvel utilisateur avec un ID unique
    const userId = `user_${Date.now()}`;
    users.set(userId, { username, password });

    return { userId };
  }
}; 