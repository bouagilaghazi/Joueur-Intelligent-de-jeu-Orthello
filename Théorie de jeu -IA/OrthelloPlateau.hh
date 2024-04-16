#include <iostream> 
#include <cstdlib> 
#include <string> 
using namespace std;
class OrthelloPlateau
{
private:
    char plateau [8][8] ; 
    void RetournePion(int a ,int b, int x , int y , char pion , char adversaire) ; 
    bool verifierRetournement (int a,int b,int x,int y, char pion, char adversaire) ;

public:
    string to_string() ; 
    OrthelloPlateau(); 
    void afficherPlateau() ; 
    int score(char piece) ;  
    char getCase(int x,int y) ; 
    bool PartieFini() ; 
    void JouerMouement(int x,int y , char pion) ; 
    bool MouvementValide(int x,int y,char pion) ; 
    void MouvementPossible(int depX[],int depY[],int &numMove,char pion); 
    int getTotalPions() ;
    char gagnant() ;
   
};

