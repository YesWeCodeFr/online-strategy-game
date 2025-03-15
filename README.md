# online-strategy-game
Tests de développement d'un jeu de stratégie en ligne de style Travian.<br/>
Le code est en grande partie généré par l'IA Claude 3.5 Sonnet.<br/>
L'un des objectifs de ce projet est de montrer comment travailler avec l'IA pour générer du code et l'intégrer dans un projet.<br>
J'ai choisi d'utiliser Cursor pour générer le code, mais il est possible d'utiliser d'autres outils comme GitHub Copilot ou Tabnine.


## Prompts IA générative
Les réponses au prompts ont été générées avec l'IA Claude 3.5 Sonnet.

[Cliquer sur ce lien pour voir les prompts](prompts-ia/sommaire.md)

Note : générer les fichiers protobuf avec la commande suivante :
```
protoc --proto_path=protocol --c_out=game-server/src/protocol/generated protocol/*.proto
```

