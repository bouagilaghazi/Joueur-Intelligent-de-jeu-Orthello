#include "OrthelloPlateau.cc"  
#include <unordered_map>
class OrthelloJeu
{
private:
    OrthelloPlateau board ; 
    char JoueurCourant ; 
    std::unordered_map<std::string, int> memo; 
    
    void utilisateur(char c) ; 
    void ordinateur(); 
    void JoueurMinMax(char joueur) ;  
    void JoueurIA(char joueur) ; 
    void joueurIA1( char joueur);
    void joueurIA2( char joueur);
    void  joueurIA3(char joueur);
    void  joueurIA4( char joueur);
    int MinnMaxx(OrthelloPlateau board, int profondeur, bool maxPlayer, char joueur, int (*evalFunc)(OrthelloPlateau, char));
    static int evaluerBoardMixte(OrthelloPlateau board, char joueur) ;  
    static int evaluerBoardMobilité(OrthelloPlateau board, char joueur) ; 
    static int evaluerBoardAbsolu(OrthelloPlateau board, char joueur) ; 
    static int evaluerBoardPositionnel(OrthelloPlateau board, char joueur) ;
    int MinMaxAlphaBeta(OrthelloPlateau board, int profondeur, bool maxPlayer, char joueur, int alpha, int beta) ;
    void generateRandomMove(OrthelloPlateau copie, char joueur, int& x, int& y) ;
    char simulateGame(OrthelloPlateau copie, char joueur) ;
    void joueurMonteCarlo(char joueur);
public:
    OrthelloJeu(); 
    void jouerPartie() ;
    
};


