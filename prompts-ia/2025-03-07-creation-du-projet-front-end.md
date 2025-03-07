[Retour vers le sommaire](sommaire.md)

# Présentation du contexte du projet (05/03/2025)
## Prompt
```
J'aimerai créer le sous-projet de l'application front. 
Elle est implémentée avec react js, en typescript. 
Elle utilise la librairie tailwind pour le css.
Elle est créée avec vite js, j'aimerai disposer des scripts de build, de tests, d'exécution sur un serveur local.
```

## Réponse

Je vais vous guider pour créer votre application front-end avec les technologies mentionnées.

1. **Création du projet avec Vite :**
```bash
npm create vite@latest front-app -- --template react-ts
cd front-app
```
2. **Installation des dépendances principales :**
```bash
# Dépendances de base
npm install

# Tailwind CSS et ses dépendances
npm install -D tailwindcss postcss autoprefixer

# Tests
npm install -D vitest @testing-library/react @testing-library/jest-dom jsdom

# ESLint et Prettier
npm install -D eslint prettier eslint-config-prettier eslint-plugin-react @typescript-eslint/eslint-plugin @typescript-eslint/parser
```
3. **Configuration de Tailwind CSS** (`tailwind.config.js`) :
```javascript
/** @type {import('tailwindcss').Config} */
export default {
  content: [
    "./index.html",
    "./src/**/*.{js,ts,jsx,tsx}",
  ],
  theme: {
    extend: {
      colors: {
        // Vos couleurs personnalisées
        'game-primary': '#1a2b3c',
        'game-secondary': '#2c3e50',
      },
    },
  },
  plugins: [],
}
```
4. **Configuration PostCSS** (`postcss.config.js`) :
```javascript
export default {
  plugins: {
    tailwindcss: {},
    autoprefixer: {},
  },
}
```
5. **Configuration des tests** (`vitest.config.ts`) :
```typescript:prompts-ia/2025-03-07-creation-du-projet-frontend.md
/// <reference types="vitest" />
import { defineConfig } from 'vite';

export default defineConfig({
  test: {
    globals: true,
    environment: 'jsdom',
    setupFiles: './src/test/setup.ts',
    coverage: {
      reporter: ['text', 'json', 'html'],
    },
  },
});
```
6. **Configuration du fichier de setup des tests** (`src/test/setup.ts`) :
```typescript
import '@testing-library/jest-dom';
```
7. **Configuration ESLint** (`.eslintrc.json`) :
```json
{
  "env": {
    "browser": true,
    "es2021": true
  },
  "extends": [
    "eslint:recommended",
    "plugin:react/recommended",
    "plugin:@typescript-eslint/recommended",
    "prettier"
  ],
  "parser": "@typescript-eslint/parser",
  "parserOptions": {
    "ecmaFeatures": {
      "jsx": true
    },
    "ecmaVersion": "latest",
    "sourceType": "module"
  },
  "plugins": ["react", "@typescript-eslint"],
  "rules": {
    "react/react-in-jsx-scope": "off"
  },
  "settings": {
    "react": {
      "version": "detect"
    }
  }
}
```
8. **Scripts dans `package.json` :**
```json
{
  "scripts": {
    "dev": "vite",
    "build": "tsc && vite build",
    "lint": "eslint src --ext ts,tsx --report-unused-disable-directives --max-warnings 0",
    "preview": "vite preview",
    "test": "vitest",
    "test:coverage": "vitest run --coverage",
    "format": "prettier --write 'src/**/*.{js,jsx,ts,tsx,css,md,json}'"
  }
}
```
9. **Structure de base des dossiers :**
```
front-app/
├── src/
│   ├── assets/
│   ├── components/
│   │   └── common/
│   ├── hooks/
│   ├── pages/
│   ├── services/
│   ├── types/
│   ├── utils/
│   ├── App.tsx
│   └── main.tsx
├── public/
├── index.html
├── package.json
├── tsconfig.json
├── vite.config.ts
├── tailwind.config.js
└── postcss.config.js
```

10. **Exemple de composant avec test** :

src/components/common/Button.tsx
```typescript
interface ButtonProps {
  label: string;
  onClick?: () => void;
  variant?: 'primary' | 'secondary';
}

export const Button = ({ label, onClick, variant = 'primary' }: ButtonProps) => {
  const baseClasses = "px-4 py-2 rounded-lg font-medium";
  const variantClasses = {
    primary: "bg-game-primary text-white hover:bg-opacity-90",
    secondary: "bg-game-secondary text-white hover:bg-opacity-90"
  };

  return (
    <button
      onClick={onClick}
      className={`${baseClasses} ${variantClasses[variant]}`}
    >
      {label}
    </button>
  );
};
```
src/components/common/\_\_tests\_\_/Button.test.tsx
```typescript
import { render, screen, fireEvent } from '@testing-library/react';
import { Button } from '../Button';

describe('Button', () => {
  it('renders with label', () => {
    render(<Button label="Test Button" />);
    expect(screen.getByText('Test Button')).toBeInTheDocument();
  });

  it('calls onClick when clicked', () => {
    const handleClick = vi.fn();
    render(<Button label="Click me" onClick={handleClick} />);
    fireEvent.click(screen.getByText('Click me'));
    expect(handleClick).toHaveBeenCalled();
  });
});
```
**Utilisation :**
```bash
# Développement local
npm run dev

# Tests
npm run test

# Build production
npm run build

# Prévisualisation du build
npm run preview

# Linting
npm run lint

# Formatage du code
npm run format
```

Voulez-vous que je développe un aspect particulier ou que je vous montre d'autres exemples ?

## Prompt
```
[vite] Internal server error: [postcss] It looks like you're trying to use `tailwindcss` directly as a PostCSS plugin. The PostCSS plugin has moved to a separate package, so to continue using Tailwind CSS with PostCSS you'll need to install `@tailwindcss/postcss` and update your PostCSS configuration.
```

## Réponse

Ah, je vois l'erreur. Il y a eu une confusion dans la configuration de PostCSS. Voici la correction :

1. **Modification du fichier `postcss.config.js` :**
```javascript
export default {
  plugins: {
    '@tailwindcss/postcss7-compat': {},
    autoprefixer: {},
  },
}
```
2. **Ajout de la dépendance manquante :**
```bash
npm install -D @tailwindcss/postcss7-compat
```

3. **Assurez-vous d'avoir le fichier `src/index.css` avec les directives Tailwind :**
src/index.css
```css
@tailwind base;
@tailwind components;
@tailwind utilities;
```

4. **Importez le CSS dans votre `src/main.tsx` :**
src/main.tsx
```typescript
import './index.css'
// ... reste du code
```

Essayez de relancer le serveur après ces modifications. Si vous rencontrez encore des problèmes, faites-le moi savoir !