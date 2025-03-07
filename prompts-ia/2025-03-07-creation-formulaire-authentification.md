[Retour vers le sommaire](sommaire.md)

# Création du formulaire d'authentification (07/03/2025)
## Prompt
```
J'aimerai que l'application gère un utilisateur connecté.
Lorsque l'utilisateur est connecté, l'application connait son identifiant
Lorsque l'utilisateur n'est pas connecté, j'aimerai être redirigé vers un formulaire d'authentification qui contient 2 champs :
- un nom d'utilisateur
- un mot de passe
Le formulaire doit proposer également un formulaire de création de l'utilisateur si celui-ci se connecte pour la première fois.
Lorsque l'utilisateur soumet le formulaire, un appel d'api est réalisé. selon la réponse http le user est authentifié et redirigé vers la page d'accueil, sinon un message d'erreur est affiché et l'utilisateur est invité à s'authentifier de nouveau
```

## Réponse

Je vais vous proposer une implémentation avec React Router pour la gestion des routes et Redux pour la gestion de l'état de l'authentification.


1. **Installation des dépendances nécessaires :**
```bash
npm install @reduxjs/toolkit react-redux react-router-dom axios
```
2. **Création du store Redux pour l'authentification :**
src/store/authSlice.ts
```typescript
import { createSlice, PayloadAction } from '@reduxjs/toolkit';

interface AuthState {
  userId: string | null;
  isAuthenticated: boolean;
  error: string | null;
  loading: boolean;
}

const initialState: AuthState = {
  userId: null,
  isAuthenticated: false,
  error: null,
  loading: false,
};

const authSlice = createSlice({
  name: 'auth',
  initialState,
  reducers: {
    loginStart: (state) => {
      state.loading = true;
      state.error = null;
    },
    loginSuccess: (state, action: PayloadAction<string>) => {
      state.isAuthenticated = true;
      state.userId = action.payload;
      state.loading = false;
      state.error = null;
    },
    loginFailure: (state, action: PayloadAction<string>) => {
      state.loading = false;
      state.error = action.payload;
    },
    logout: (state) => {
      state.isAuthenticated = false;
      state.userId = null;
      state.error = null;
    },
  },
});

export const { loginStart, loginSuccess, loginFailure, logout } = authSlice.actions;
export default authSlice.reducer;
```
3. **Création du composant de formulaire d'authentification :**
src/components/LoginForm.tsx
```typescript
import { useState } from 'react';
import { useDispatch, useSelector } from 'react-redux';
import { useNavigate } from 'react-router-dom';
import { loginStart, loginSuccess, loginFailure } from '../../store/authSlice';
import { Button } from '../common/Button';
import axios from 'axios';

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
      const response = await axios.post('/api/auth/login', {
        username,
        password,
      });

      dispatch(loginSuccess(response.data.userId));
      navigate('/');
    } catch (error) {
      dispatch(loginFailure('Identifiants invalides'));
    }
  };

  return (
    <div className="max-w-md mx-auto mt-8 p-6 bg-white rounded-lg shadow-lg">
      <h2 className="text-2xl font-bold mb-6">Connexion</h2>
      <form onSubmit={handleSubmit}>
        <div className="mb-4">
          <label className="block text-gray-700 mb-2" htmlFor="username">
            Nom d'utilisateur
          </label>
          <input
            id="username"
            type="text"
            value={username}
            onChange={(e) => setUsername(e.target.value)}
            className="w-full px-3 py-2 border rounded-lg focus:outline-none focus:ring-2 focus:ring-blue-500"
            required
          />
        </div>
        <div className="mb-6">
          <label className="block text-gray-700 mb-2" htmlFor="password">
            Mot de passe
          </label>
          <input
            id="password"
            type="password"
            value={password}
            onChange={(e) => setPassword(e.target.value)}
            className="w-full px-3 py-2 border rounded-lg focus:outline-none focus:ring-2 focus:ring-blue-500"
            required
          />
        </div>
        {error && (
          <div className="mb-4 text-red-500 text-sm">{error}</div>
        )}
        <Button label="Se connecter" type="submit" variant="primary" />
        <p className="mt-4 text-center">
          Pas encore de compte ?{' '}
          <button
            type="button"
            onClick={onToggleMode}
            className="text-blue-500 hover:underline"
          >
            Créer un compte
          </button>
        </p>
      </form>
    </div>
  );
};
```
4. **Création du composant d'inscription :**
src/components/auth/RegisterForm.tsx
```typescript
import { useState } from 'react';
import { useDispatch, useSelector } from 'react-redux';
import { useNavigate } from 'react-router-dom';
import { loginStart, loginSuccess, loginFailure } from '../../store/authSlice';
import { Button } from '../common/Button';
import axios from 'axios';

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
      const response = await axios.post('/api/auth/register', {
        username,
        password,
      });

      dispatch(loginSuccess(response.data.userId));
      navigate('/');
    } catch (error) {
      dispatch(loginFailure("Erreur lors de l'inscription"));
    }
  };

  return (
    <div className="max-w-md mx-auto mt-8 p-6 bg-white rounded-lg shadow-lg">
      <h2 className="text-2xl font-bold mb-6">Créer un compte</h2>
      <form onSubmit={handleSubmit}>
        <div className="mb-4">
          <label className="block text-gray-700 mb-2" htmlFor="username">
            Nom d'utilisateur
          </label>
          <input
            id="username"
            type="text"
            value={username}
            onChange={(e) => setUsername(e.target.value)}
            className="w-full px-3 py-2 border rounded-lg focus:outline-none focus:ring-2 focus:ring-blue-500"
            required
          />
        </div>
        <div className="mb-4">
          <label className="block text-gray-700 mb-2" htmlFor="password">
            Mot de passe
          </label>
          <input
            id="password"
            type="password"
            value={password}
            onChange={(e) => setPassword(e.target.value)}
            className="w-full px-3 py-2 border rounded-lg focus:outline-none focus:ring-2 focus:ring-blue-500"
            required
          />
        </div>
        <div className="mb-6">
          <label className="block text-gray-700 mb-2" htmlFor="confirmPassword">
            Confirmer le mot de passe
          </label>
          <input
            id="confirmPassword"
            type="password"
            value={confirmPassword}
            onChange={(e) => setConfirmPassword(e.target.value)}
            className="w-full px-3 py-2 border rounded-lg focus:outline-none focus:ring-2 focus:ring-blue-500"
            required
          />
        </div>
        {error && (
          <div className="mb-4 text-red-500 text-sm">{error}</div>
        )}
        <Button label="S'inscrire" type="submit" variant="primary" />
        <p className="mt-4 text-center">
          Déjà un compte ?{' '}
          <button
            type="button"
            onClick={onToggleMode}
            className="text-blue-500 hover:underline"
          >
            Se connecter
          </button>
        </p>
      </form>
    </div>
  );
};
```
5. **Page d'authentification qui gère les deux formulaires :**
src/pages/AuthPage.tsx
```typescript
import { useState } from 'react';
import { LoginForm } from '../components/auth/LoginForm';
import { RegisterForm } from '../components/auth/RegisterForm';

export const AuthPage = () => {
  const [isLogin, setIsLogin] = useState(true);

  return (
    <div className="min-h-screen bg-gray-100 py-12">
      {isLogin ? (
        <LoginForm onToggleMode={() => setIsLogin(false)} />
      ) : (
        <RegisterForm onToggleMode={() => setIsLogin(true)} />
      )}
    </div>
  );
};
```

6. **Protection des routes avec un composant PrivateRoute :**
src/components/auth/PrivateRoute.tsx
```typescript
import { Navigate } from 'react-router-dom';
import { useSelector } from 'react-redux';
import { RootState } from '../../store';

interface PrivateRouteProps {
  children: React.ReactNode;
}

export const PrivateRoute = ({ children }: PrivateRouteProps) => {
  const isAuthenticated = useSelector((state: RootState) => state.auth.isAuthenticated);

  if (!isAuthenticated) {
    return <Navigate to="/auth" replace />;
  }

  return <>{children}</>;
};
```

7. **Configuration des routes dans App.tsx :**
src/App.tsx
```typescript
import { BrowserRouter as Router, Routes, Route } from 'react-router-dom';
import { Provider } from 'react-redux';
import { store } from './store';
import { AuthPage } from './pages/AuthPage';
import { HomePage } from './pages/HomePage';
import { PrivateRoute } from './components/auth/PrivateRoute';

function App() {
  return (
    <Provider store={store}>
      <Router>
        <Routes>
          <Route path="/auth" element={<AuthPage />} />
          <Route
            path="/"
            element={
              <PrivateRoute>
                <HomePage />
              </PrivateRoute>
            }
          />
        </Routes>
      </Router>
    </Provider>
  );
}

export default App;
```
Cette implémentation :
- Utilise Redux pour gérer l'état d'authentification
- Protège les routes qui nécessitent une authentification
- Gère les formulaires de connexion et d'inscription
- Utilise Axios pour les appels API
- Intègre Tailwind CSS pour le style
- Gère les erreurs et les états de chargement

Voulez-vous que je développe un aspect particulier ou que je vous montre d'autres exemples ?