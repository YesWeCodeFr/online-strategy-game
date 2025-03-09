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
        <div className="w-full min-h-screen">
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
        </div>
      </Router>
    </Provider>
  );
}

export default App; 