# Jeu Othello

Ce projet est une implémentation du jeu de société classique Othello (également connu sous le nom de Reversi) en C++. Il comprend une interface utilisateur simple en texte et des joueurs IA avec différentes stratégies.

## Caractéristiques

- Interface utilisateur en texte
- Joueurs IA avec différentes stratégies
- Simulation de Monte Carlo pour la sélection des mouvements

## Pour commencer

### Prérequis

- Un compilateur C++ (par exemple, g++)

### Compilation

Pour compiler le projet, naviguez jusqu'au répertoire du projet et exécutez la commande suivante :

```bash
g++ -o orthelloJeu orthelloJeu.cc 
#### execution 
./orthelloJeu 


##### pour changer les joueur : 
il faut modifier cette partie de code dans le fichier orthellojeu.cc 
 while(!board.PartieFini()){
        board.afficherPlateau() ; 
        if (JoueurCourant=='X'){
             joueurIA2('O') ; // cette ligne 
            JoueurCourant='O' ; 
        }else {
            joueurIA4('X') ; // et cette ligne 
            JoueurCourant='X' ; 
        }
    } 
    
