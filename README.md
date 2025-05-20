# Simulation Interactive en C++

Ce projet est une application interactive développée en C++, structurée autour d’un moteur de simulation simple et extensible. Il repose sur une architecture orientée objet et propose une modélisation d’un monde virtuel interactif composé de pièces et d’objets.

## 🎮 Concept du Jeu

Le programme simule un univers dans lequel un joueur évolue à travers différentes pièces, interagit avec des objets dynamiques, et déclenche des comportements spécifiques. Il ne s’agit pas d’un jeu graphique, mais d’une simulation textuelle ou logique, qui met en valeur la structure logicielle et les interactions entre entités.

## 💡 Concepts de Programmation Utilisés
### 🧠 Programmation Orientée Objet (POO)

- Encapsulation : Chaque composant (Jeu, Monde, Piece, ObjetInteractif) possède ses propres attributs et méthodes.
- Héritage : Les objets interactifs héritent d’une classe de base ObjetInteractif pour unifier les comportements.
- Polymorphisme : Les objets sont manipulés via des pointeurs ou références à leur classe mère, permettant des comportements dynamiques.
- Abstraction : L'utilisateur interagit avec un système cohérent sans voir la complexité interne.

### 🧩 Modularité

- Séparation claire entre les entités : le monde, les pièces, les objets et la logique de jeu.
- Utilisation d’en-têtes (.hpp) pour déclarer les interfaces, et de fichiers .cpp pour l’implémentation.

## 📫 Contact

Pour toute suggestion ou question, ouvrez une issue sur le dépôt GitHub.
