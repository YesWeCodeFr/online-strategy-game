import { useSelector, useDispatch } from 'react-redux';
import { useNavigate } from 'react-router-dom';
import { RootState } from '../store';
import { logout } from '../store/authSlice';
import { Button } from '../components/common/Button';

export const HomePage = () => {
  const dispatch = useDispatch();
  const navigate = useNavigate();
  const userId = useSelector((state: RootState) => state.auth.userId);

  const handleLogout = () => {
    dispatch(logout());
    navigate('/auth');
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
      </div>
    </div>
  );
}; 