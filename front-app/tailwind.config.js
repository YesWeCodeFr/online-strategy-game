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