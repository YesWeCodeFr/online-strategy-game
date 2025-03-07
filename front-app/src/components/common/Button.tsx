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