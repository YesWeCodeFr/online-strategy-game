[Retour vers le sommaire](sommaire.md)

# Création du service d'authentification simulée (07/03/2025)
## Prompt
```
Dans ce composant (LoginForm.tsx), une api est appelée lors de la soumission du formulaire.
J'aimerai dans un premier temps que cela n'appelle pas une vraie api, mais une fonction asynchrone que je changerais plus tard en appel d'api
```

## Réponse

Je vais créer un service d'authentification simulé qui pourra être facilement remplacé par de vrais appels API plus tard.

authService.ts
```typescript
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
```
Maintenant, modifions le `LoginForm` pour utiliser ce service : LoginForm.tsx
```typescript
import { useState } from 'react';
import { useDispatch, useSelector } from 'react-redux';
import { useNavigate } from 'react-router-dom';
import { loginStart, loginSuccess, loginFailure } from '../../store/authSlice';
import { Button } from '../common/Button';
import { authService } from '../../services/authService';
import { RootState } from '../../store';

interface LoginFormProps {
  onToggleMode: () => void;
}

export const LoginForm = ({ onToggleMode }: LoginFormProps) => {
  const [username, setUsername] = useState('');
  const [password, setPassword] = useState('');
  const dispatch = useDispatch();
  const navigate = useNavigate();
  const error = useSelector((state: RootState) => state.auth.error);

  const handleSubmit = async (e: React.FormEvent) => {
    e.preventDefault();
    dispatch(loginStart());

    try {
      const response = await authService.login(username, password);
      dispatch(loginSuccess(response.userId));
      navigate('/');
    } catch (error) {
      dispatch(loginFailure('Identifiants invalides'));
    }
  };

  // ... reste du code inchangé ...
};
```

Et le `RegisterForm` également : RegisterForm.tsx
```typescript
import { useState } from 'react';
import { useDispatch, useSelector } from 'react-redux';
import { useNavigate } from 'react-router-dom';
import { loginStart, loginSuccess, loginFailure } from '../../store/authSlice';
import { Button } from '../common/Button';
import { authService } from '../../services/authService';
import { RootState } from '../../store';

interface RegisterFormProps {
  onToggleMode: () => void;
}

export const RegisterForm = ({ onToggleMode }: RegisterFormProps) => {
  const [username, setUsername] = useState('');
  const [password, setPassword] = useState('');
  const [confirmPassword, setConfirmPassword] = useState('');
  const dispatch = useDispatch();
  const navigate = useNavigate();
  const error = useSelector((state: RootState) => state.auth.error);

  const handleSubmit = async (e: React.FormEvent) => {
    e.preventDefault();
    
    if (password !== confirmPassword) {
      dispatch(loginFailure('Les mots de passe ne correspondent pas'));
      return;
    }

    dispatch(loginStart());

    try {
      const response = await authService.register(username, password);
      dispatch(loginSuccess(response.userId));
      navigate('/');
    } catch (error) {
      dispatch(loginFailure(error instanceof Error ? error.message : "Erreur lors de l'inscription"));
    }
  };

  // ... reste du code inchangé ...
};
```

