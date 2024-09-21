# Gestion de Réservation de Véhicule

## Description

Ce projet permet de gérer les réservations de véhicules en utilisant Qt pour l'interface utilisateur et MySQL/MariaDB pour la gestion de la base de données. Il offre une solution complète pour créer, modifier, supprimer, lister et rechercher des réservations.

## Fonctionnalités

- **Enregistréer un client :** Ajouter de nouvelles clients dans le système.

## Technologies Utilisées

- **Qt** : Pour le développement de l'interface utilisateur.
- **MySQL/MariaDB** : Pour la gestion de la base de données.
- **Windesign** : Pour la modélisation des données.
- **Inkscape** : Pour la création de maquettes et la conception graphique.

## Prérequis

- **Qt 5.15+** (ou Qt 6.x)
- **C++** (compatible avec la version Qt utilisée)
- **MySQL/MariaDB** (pour la base de données)
- **Git** (pour le contrôle de version)

## Installation

1. **Cloner le dépôt GitHub :**
    ```bash
   git clone https://github.com/DinaTolotra/QReservation.git
   cd QReservation
   ```

2. **Initialiser la base de donnée :**
    ```bash
    mysql -u [nom utilisateur] -p
    ```
    Entrer le mot de passe de l'utilisateur.  
    Ensuite dans **MySQL/MariaDB** :
    ```bash
    > source ./res/script/reservation.SQL;
    ```

## Contribution

### Convention

#### Nommage

- **camelCase** : Variable, fonction
- **PascalCase** : Class, file
- **CONSTAN_CASE** : Constante, enum


#### Norme de code

- **Getter** : getMyGetter
- **Setter** : setMySetter
- **Proprieté** : _myPropriety
