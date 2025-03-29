#!/bin/bash

# URL de l'API
API_URL="http://localhost:3000/api/users"  # Remplacez par l'URL de votre serveur

# Vérifiez la valeur de API_URL
echo "URL de l'API : $API_URL"

# Nombre total de requêtes
TOTAL_REQUESTS=1000

# Nombre de threads
THREADS=4

# Exporter la variable API_URL pour qu'elle soit accessible dans les sous-processus
export API_URL

# Fonction pour générer un nom aléatoire
generate_random_name() {
    local random_number=$(od -An -N2 -i /dev/urandom | awk '{print $1 % 100000}')
    echo "user_$random_number"
}

# Fonction pour envoyer une requête POST
send_request() {
    local name=$(generate_random_name)
    local password="password123"

    # Afficher le nom généré pour le débogage
    echo "Envoi de la requête avec nom: $name"

    # Préparer les données JSON
    json_data=$(printf '{\\\"nom\\\":\\\"%s\\\", \\\"password\\\":\\\"%s\\\"}' "$name" "$password")

    # Encapsuler la commande curl dans une variable
    local curl_command="curl -s -o /dev/null -w \"%{http_code}\" -X POST \"$API_URL\" -H \"Content-Type: application/json\" -d \"$json_data\""

    # Afficher la commande curl pour le débogage
    echo "Commande curl : $curl_command"

    # Exécuter la commande curl
    response=$(eval $curl_command)

    # Afficher le code de réponse pour le débogage
    echo "Réponse HTTP: $response"
}

# Fonction pour une requête GET
get_request() {
    # Afficher l'URL pour le débogage
    echo "Envoi d'une requête GET à : $API_URL"

    # Encapsuler la commande curl dans une variable 
    local curl_command="curl -s -o /dev/null -w \"%{http_code}\" -X GET \"$API_URL\" -H \"Content-Type: application/json\""

    # Afficher la commande curl pour le débogage
    echo "Commande curl : $curl_command"

    # Exécuter la commande curl
    response=$(eval $curl_command)

    # Afficher le code de réponse pour le débogage
    echo "Réponse HTTP: $response"
}


# Exporter les fonctions
export -f send_request
export -f get_request
export -f generate_random_name

# Mesurer le temps d'exécution
start_time=$(date +%s)

# Exécuter les requêtes en parallèle
seq 1 $TOTAL_REQUESTS | parallel -j $THREADS send_request

end_time=$(date +%s)
execution_time=$((end_time - start_time))

# Afficher le temps d'exécution
echo "Temps d'exécution : $execution_time secondes"
echo "Vélocité : $((TOTAL_REQUESTS / execution_time)) requêtes par seconde"

# Mesurer le temps d'exécution
start_time=$(date +%s)

# Exécuter les requêtes en parallèle
seq 1 $((TOTAL_REQUESTS / 10)) | parallel -j $THREADS get_request

echo "terminé"

end_time=$(date +%s)
execution_time=$((end_time - start_time))

# Afficher le temps d'exécution
echo "Temps d'exécution : $execution_time secondes"
echo "Vélocité : $((TOTAL_REQUESTS / execution_time)) requêtes par seconde"