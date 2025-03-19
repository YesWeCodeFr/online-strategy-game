import { useSelector, useDispatch } from 'react-redux';
import { useNavigate } from 'react-router-dom';
import { RootState } from '../store';
import { logout } from '../store/authSlice';
import { Button } from '../components/common/Button';
import { getUsers } from '../services/userService';

export const HomePage = () => {
  const dispatch = useDispatch();
  const navigate = useNavigate();
  const userId = useSelector((state: RootState) => state.auth.userId);

  const handleLogout = () => {
    dispatch(logout());
    navigate('/auth');
  };

  const handleShowUsers = async () => {
    try {
      const users = await getUsers();
      console.log(users);
    } catch (error) {
      console.error('Erreur lors de la récupération des utilisateurs:', error);
    }
  };

  return (
    <div className="min-h-screen bg-gray-100 p-8">
      <div className="max-w-2xl mx-auto bg-white rounded-lg shadow-lg p-6">
        <h1 className="text-2xl font-bold mb-4">Page d'accueil</h1>
        <p className="mb-4">
          Bienvenue ! Votre identifiant utilisateur est : {' '}
          <span className="font-semibold">{userId}</span>
        </p>
        <Button 
          label="Se déconnecter" 
          onClick={handleLogout} 
          variant="secondary"
        />
        <Button 
          label="Afficher les utilisateurs" 
          onClick={handleShowUsers} 
          variant="primary"
        />
      </div>
    </div>
  );
}; 