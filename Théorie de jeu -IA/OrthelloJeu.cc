#include "OrthelloJeu.hh"  
#include <iostream> 
#include <limits> 
#include<chrono> 
#include <numeric>
#include <vector>
using namespace std ; 
std::vector<std::vector<double>> tempsJoueurs(4); 
OrthelloJeu::OrthelloJeu():JoueurCourant('X') {} 
void OrthelloJeu::utilisateur(char joueur){
    int x, y ; 
    int depX[60],depY[60],numMove=0 ; 
    board.MouvementPossible(depX,depY,numMove,joueur) ;  
    //afficher mouvement possible pour utilisateur 
    for(int i=0;i<numMove;++i){
        cout<<"("<<depX[i]<<","<<depY[i]<<")"<<" " ; 
    } 
    cout <<"Entrez votre mouvement (colone ligne) :  "; 
    cin>> x >> y ;  
    cout <<"x= "<<x<< " et y= "<<y<<endl ; 
    
    if(board.MouvementValide(x,y,joueur)){
        board.JouerMouement(x,y,joueur) ; 
    }else {
        cout<<"Mouvement invalide"<<endl ; 
        utilisateur(joueur) ; 
    }
} 
void OrthelloJeu::ordinateur(){
    int depX[60],depY[60],numMove=0 ; 
    board.MouvementPossible(depX,depY,numMove,JoueurCourant) ; 
    if (numMove==0){
        cout<<"L'ordinateur ne peut pas jouer , PASS"<<endl ; 
        return ; 
    } 
    int Mvt= rand()%numMove ; 
    board.JouerMouement(depX[Mvt],depY[Mvt],JoueurCourant) ;   
}
void OrthelloJeu::jouerPartie(){
    int depth =3 ;
    while(!board.PartieFini()){
        board.afficherPlateau() ; 
        if (JoueurCourant=='X'){
             joueurIA2('O') ; 
            JoueurCourant='O' ; 
        }else {
            joueurIA4('X') ;
            JoueurCourant='X' ; 
        }
    } 
    board.afficherPlateau() ; 
    int scoreX=board.score('X') ; 
    int scoreO=board.score('O') ; 
    for (size_t i = 0; i < 4; i++)
    {
        if (tempsJoueurs[i].size() == 0) continue;
        else {
            double sum = std::accumulate(tempsJoueurs[i].begin(), tempsJoueurs[i].end(), 0.0);
            double moyenne = sum / tempsJoueurs[i].size();
            std::cout << "Le temps moyen pris par le joueur " << i + 1 << " pour trouver le bon coup est de " << moyenne << " secondes." << std::endl;
            
    }}       
    std::cout << "Temps des joueurs:" << std::endl; 
        // cette partie est utilisé pour afficher les temps de chaque joueur pour chaque coup
            // for (size_t i = 0; i < tempsJoueurs.size(); i++) {
            //     std::cout << "Joueur " << i + 1 << ": ";
            //     for (size_t j = 0; j < tempsJoueurs[i].size(); j++) {
            //         std::cout << tempsJoueurs[i][j] << " ; ";    
            //     } 
            //     std::cout << std::endl;
            // }
    
        
    
    
    cout<<"Score X : "<<scoreX<<endl ;
    cout<<"Score O : "<<scoreO<<endl ; 
    if (scoreX>scoreO){
        cout<<"X gagne"<<endl ; 
    }else if (scoreX<scoreO){
        cout<<"O gagne"<<endl ; 
    }else {
        cout<<"Egalite"<<endl ; 
    }
}
  
int OrthelloJeu::evaluerBoardMobilité(OrthelloPlateau board, char joueur){
    int score = 0; 
    int depX[60], depY[60], numMove = 0;
    board.MouvementPossible(depX, depY, numMove, joueur);
    score += numMove * 10;

    board.MouvementPossible(depX, depY, numMove, joueur == 'X' ? 'O' : 'X');
    score -= numMove * 10; 
    return score ;  

} 
int OrthelloJeu::evaluerBoardAbsolu(OrthelloPlateau board, char joueur){
    int score = 0; 
    score += board.score(joueur) - board.score(joueur == 'X' ? 'O' : 'X');
    return score ; 
} 
int OrthelloJeu::evaluerBoardPositionnel(OrthelloPlateau board, char joueur){
    int valeur [8][8]={
      {500, -150, 30, 10, 10, 30, -150, 500},
        {-150, -250, 0, 0, 0, 0, -250, -150},
        {30, 0, 1, 2, 2, 1, 0, 30},
        {10, 0, 2, 16, 16, 2, 0, 10},
        {10, 0, 2, 16, 16, 2, 0, 10},
        {30, 0, 1, 2, 2, 1, 0, 30},
        {-150, -250, 0, 0, 0, 0, -250, -150},
        {500, -150, 30, 10, 10, 30, -150, 500}  
    };  
    //  score en fonction de la valeur de chaque case
    int score=0 ;
    for(int i=0;i<8;++i){
        for(int j=0;j<8;++j){
            if(board.getCase(i,j)==joueur){
                score+=valeur[i][j] ; 
            } else if (board.getCase(i, j) == (joueur == 'X' ? 'O' : 'X')) {
                score -= valeur[i][j];
            }
        }
    } 
    return score ;
}
int OrthelloJeu::evaluerBoardMixte(OrthelloPlateau board, char joueur){
    int totalPions=board.getTotalPions() ; 
    if (totalPions<25){
        return evaluerBoardPositionnel(board,joueur) ;
    } 
    else if (totalPions<44){
        return evaluerBoardMobilité(board,joueur) ; 
    }else {
        return evaluerBoardAbsolu(board,joueur) ; 
    }
    
} 
int OrthelloJeu::MinMaxAlphaBeta(OrthelloPlateau board, int profondeur, bool maxPlayer, char joueur, int alpha, int beta){
    if (profondeur==0 || board.PartieFini()){
        return evaluerBoardMixte(board,joueur) ; 
    } 
    int depX[60], depY[60], numMove = 0;
    board.MouvementPossible(depX, depY, numMove, joueur);
    if (maxPlayer){
        int maxEval = -1000000;
        for (int i = 0; i < numMove; ++i) {
            OrthelloPlateau newBoard = board;
            newBoard.JouerMouement(depX[i], depY[i], joueur);
            int eval = MinMaxAlphaBeta(newBoard, profondeur - 1, false, joueur, alpha, beta);
            maxEval = max(maxEval, eval);
            alpha = max(alpha, eval);
            if (beta <= alpha) break;
        }
        return maxEval;
    }else {
        int minEval = 1000000;
        for (int i = 0; i < numMove; ++i) {
            OrthelloPlateau newBoard = board;
            newBoard.JouerMouement(depX[i], depY[i], joueur);
            int eval = MinMaxAlphaBeta(newBoard, profondeur - 1, true, joueur, alpha, beta);
            minEval = min(minEval, eval);
            beta = min(beta, eval);
            if (beta <= alpha) break;
        }
        return minEval;
    } 

}
void OrthelloJeu::joueurIA1( char joueur) {
    int meilleurScore = -std::numeric_limits<int>::max();
    int posX, posY;
    int profondeur = 5;
    int depX[60], depY[60], numMove = 0;
    board.MouvementPossible(depX, depY, numMove, joueur);

    for (int i = 0; i < numMove; ++i) {
        OrthelloPlateau newBoard = board;
        newBoard.JouerMouement(depX[i], depY[i], joueur); 
        auto start = std::chrono::high_resolution_clock::now();
        int score = MinnMaxx(newBoard, profondeur - 1, false, joueur, &OrthelloJeu::evaluerBoardPositionnel);
        auto finish = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> elapsed = finish - start;
        tempsJoueurs[0].push_back(elapsed.count());
        if (score > meilleurScore) {
            meilleurScore = score;
            posX = depX[i];
            posY = depY[i];
        }
    }

    if (board.MouvementValide(posX, posY, joueur)) {
        board.JouerMouement(posX, posY, joueur);
    } else {
        cout << "L'ordinateur ne peut pas jouer, PASS" << endl;
    }  
}

void OrthelloJeu::joueurIA2(char joueur) {
     int meilleurScore = -std::numeric_limits<int>::max();
    int posX, posY;
    int profondeur = 5;
    int depX[60], depY[60], numMove = 0;
    board.MouvementPossible(depX, depY, numMove, joueur);

    for (int i = 0; i < numMove; ++i) {
        OrthelloPlateau newBoard = board;
        newBoard.JouerMouement(depX[i], depY[i], joueur);
        auto start = std::chrono::high_resolution_clock::now();
        int score = MinnMaxx(newBoard, profondeur - 1, false, joueur, &OrthelloJeu::evaluerBoardMobilité);
        auto finish = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> elapsed = finish - start;
        tempsJoueurs[1].push_back(elapsed.count());
        if (score > meilleurScore) {
            meilleurScore = score;
            posX = depX[i];
            posY = depY[i];
        }
    }

    if (board.MouvementValide(posX, posY, joueur)) {
        board.JouerMouement(posX, posY, joueur);
    } else {
        cout << "L'ordinateur ne peut pas jouer, PASS" << endl;
    }  
}

void OrthelloJeu::joueurIA3(char joueur) {
     int meilleurScore = -std::numeric_limits<int>::max();
    int posX, posY;
    int profondeur = 5;
    int depX[60], depY[60], numMove = 0;
    board.MouvementPossible(depX, depY, numMove, joueur);

    for (int i = 0; i < numMove; ++i) {
        OrthelloPlateau newBoard = board;
        newBoard.JouerMouement(depX[i], depY[i], joueur); 
        auto start = std::chrono::high_resolution_clock::now();
        int score = MinnMaxx(newBoard, profondeur - 1, false, joueur, &OrthelloJeu::evaluerBoardAbsolu);
        auto finish = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> elapsed = finish - start;
        tempsJoueurs[2].push_back(elapsed.count());
        if (score > meilleurScore) {
            meilleurScore = score;
            posX = depX[i];
            posY = depY[i];
        }
    }

    if (board.MouvementValide(posX, posY, joueur)) {
        board.JouerMouement(posX, posY, joueur);
    } else {
        cout << "L'ordinateur ne peut pas jouer, PASS" << endl;
    }  
}

void  OrthelloJeu::joueurIA4( char joueur) {
    int meilleurScore = -std::numeric_limits<int>::max();
    int posX, posY;
    int profondeur = 5;
    int depX[60], depY[60], numMove = 0;
    board.MouvementPossible(depX, depY, numMove, joueur);

    for (int i = 0; i < numMove; ++i) {
        OrthelloPlateau newBoard = board;
        newBoard.JouerMouement(depX[i], depY[i], joueur);
        auto start = std::chrono::high_resolution_clock::now();
        int score = MinnMaxx(newBoard, profondeur - 1, false, joueur, &OrthelloJeu::evaluerBoardMixte);
        auto finish = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> elapsed = finish - start;
        tempsJoueurs[3].push_back(elapsed.count());
        if (score > meilleurScore) {
            meilleurScore = score;
            posX = depX[i];
            posY = depY[i];
        }
    }

    if (board.MouvementValide(posX, posY, joueur)) {
        board.JouerMouement(posX, posY, joueur);
    } else {
        cout << "L'ordinateur ne peut pas jouer, PASS" << endl;
    }  
}  
int OrthelloJeu::MinnMaxx(OrthelloPlateau board, int profondeur, bool maxPlayer, char joueur, int (*evalFunc)(OrthelloPlateau, char)) {
    string key = board.to_string() ; 
    if (memo.find(key) != memo.end()) {
        return memo[key];
    }
    if (profondeur==0 || board.PartieFini()){
        return evalFunc(board,joueur); 
    } 
    int depX[60], depY[60], numMove = 0;
    board.MouvementPossible(depX, depY, numMove, joueur);
    if (maxPlayer){
        int maxEval = -1000000;
        for (int i = 0; i < numMove; ++i) {
            OrthelloPlateau newBoard = board;
            newBoard.JouerMouement(depX[i], depY[i], joueur);
            int eval = MinnMaxx(newBoard, profondeur - 1, false, joueur, evalFunc);
            maxEval = max(maxEval, eval);
        } 
        memo[key] = maxEval;
        return maxEval;
    }else {
        int minEval = 1000000;
        for (int i = 0; i < numMove; ++i) {
            OrthelloPlateau newBoard = board;
            newBoard.JouerMouement(depX[i], depY[i], joueur);
            int eval = MinnMaxx(newBoard, profondeur - 1, true, joueur, evalFunc);
            minEval = min(minEval, eval);
        }
        memo[key] = minEval;
        return minEval;
    }
}
void OrthelloJeu::JoueurIA(char joueur ) {
    int meilleurScore = -std::numeric_limits<int>::max();
    int posX, posY;
    int alpha = -std::numeric_limits<int>::max();
    int beta = std::numeric_limits<int>::max();
    int profondeur = 5;
    int depX[60], depY[60], numMove = 0;
    board.MouvementPossible(depX, depY, numMove, joueur);  
    for (int i = 0; i < numMove; ++i) {
        OrthelloPlateau newBoard = board;
        newBoard.JouerMouement(depX[i], depY[i], joueur);
        int score = MinMaxAlphaBeta(newBoard, profondeur - 1, true, joueur, alpha, beta);
        if (score > meilleurScore) {
            meilleurScore = score;
            posX = depX[i];
            posY = depY[i];
        }
    }

    if (board.MouvementValide(posX, posY, joueur)) {
        board.JouerMouement(posX, posY, joueur);
    } else {
        cout << "L'ordinateur ne peut pas jouer, PASS" << endl;
    }  
}
char OrthelloJeu::simulateGame(OrthelloPlateau copie, char joueur) {
    char adversaire = (joueur == 'O') ? 'X' : 'O';
    while (!copie.PartieFini()) {
        int x, y;
        generateRandomMove(copie, adversaire, x, y);
        if (copie.MouvementValide(x, y, adversaire)) {
            copie.JouerMouement(x, y, adversaire);
        }
        swap(joueur, adversaire);
    }
    return copie.gagnant();
}
void OrthelloJeu::joueurMonteCarlo(char joueur) {
        int meilleurX, meilleurY;
        int meilleurScore = -1;
        for (int x = 0; x < 8; x++) {
            for (int y = 0; y < 8; y++) {
                if (board.MouvementValide(x, y, joueur)) {
                    int score = 0;
                    for (int i = 0; i < 3; i++) { // N est le nombre de simulations pour chaque mouvement
                        OrthelloPlateau copie = board; // copie l'état actuel du jeu
                        copie.JouerMouement(x, y, joueur);
                        if (simulateGame(copie, joueur) == joueur) {
                            score++;
                        }
                    }
                    if (score > meilleurScore) {
                        meilleurScore = score;
                        meilleurX = x;
                        meilleurY = y;
                    }
                }
            }
        }
        board.JouerMouement(meilleurX, meilleurY, joueur);
    }
void OrthelloJeu::generateRandomMove(OrthelloPlateau copie, char joueur, int& x, int& y) {
    vector<pair<int, int>> validMoves;
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (copie.MouvementValide(i, j, joueur)) {
                validMoves.push_back({i, j});
            }
        }
    }
    if (!validMoves.empty()) {
        int randomIndex = rand() % validMoves.size();
        x = validMoves[randomIndex].first;
        y = validMoves[randomIndex].second;
    }
}


  
int main(){
    OrthelloJeu o ; 
    o.jouerPartie() ; 
}