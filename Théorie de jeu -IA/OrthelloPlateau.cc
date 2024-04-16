#include"OrthelloPlateau.hh" 
using namespace std;  
//création du plateau de jeu
OrthelloPlateau::OrthelloPlateau(){
    for (int i =0 ;i<8;i++){
        for (int j =0 ;j<8;j++){ 
            if ((i==3 && j==3) || (i==4 && j==4)) plateau[i][j]='O'; 
            else if ((i==3 && j==4) || (i==4 && j==3)) plateau[i][j]='X'; 
            else plateau[i][j]='.';
            
        }
    }
}   
string OrthelloPlateau::to_string(){
     string s = "" ; 
    for (int i=0;i<8;++i){
        for (int j=0;j<8;++j){
            s+=plateau[i][j] ;
        }
    }
    return s ; 
}
//affichage du plateau de jeu
void OrthelloPlateau::afficherPlateau(){
    for (int y = 7; y >= 0; y--)
	{
		cout << y << " ";
		for (int x = 0; x < 8; x++)
			cout << " " << plateau[x][y];
		cout << endl;
	}
    cout<<"   0 1 2 3 4 5 6 7"<<endl;
}   
//calcul du score
int OrthelloPlateau::score(char piece){
    int score=0;
    for (int i =0 ;i<8;i++){ 
        for (int j =0 ;j<8;j++){ 
            if (plateau[i][j]==piece) score++;
        }
    }
    return score;
}  
//vérification si la partie est finie
bool OrthelloPlateau::PartieFini(){
    for (int i =0 ;i<8;i++){ 
        for (int j =0 ;j<8;j++){ 
            if (plateau[i][j]=='.') return false;
        }
    }return true ; 
}  
//Retourner les pions de l'adversaire 
void OrthelloPlateau::RetournePion(int a ,int b, int x , int y , char pion , char adversaire){
    while (plateau[a][b]==adversaire){
        plateau[a][b]=pion ; 
        a+=x ; 
        b+=y ; 
    }
} 
bool OrthelloPlateau::verifierRetournement (int a,int b,int x,int y, char pion, char adversaire){
    if(plateau[a][b] != adversaire) return false ; 
    int newA=a+x ; 
    int newB=b+y ;
    while (newA>=0 && newA<8 && newB>=0 && newB<8){
        if (plateau[newA][newB]== '.') break ; 
        if (plateau[newA][newB]== pion) return true ; 
        newA += x ;
        newB += y ;
    }
    return false ; 
} 

void OrthelloPlateau::JouerMouement(int x,int y , char pion){
    if (x < 0 || x >= 8 || y < 0 || y >= 8 || plateau[x][y] != '.') {
        std::cout << "Mouvement invalide. Veuillez réessayer." << std::endl;
        return;
    } 
    plateau[x][y]=pion ; 
    
    char adversaire =(pion =='O') ? 'X' : 'O';
    int direction [8][2] = {
        {-1,0}, {1,0}, {0,-1}, {0,1}, 
        {-1,-1}, {1,-1} , {-1,1},{1,1}
    } ; 
    for (int i=0;i<8;++i){
        int NewX=direction[i][0]; 
        int NewY=direction[i][1] ; 
        if(verifierRetournement(x+NewX,y+NewY,NewX,NewY,pion,adversaire)){
            RetournePion(x+NewX,y+NewY,NewX,NewY,pion,adversaire);
        }
    }
}

bool OrthelloPlateau::MouvementValide(int x,int y,char pion){
  if (plateau[x][y] !='.') return false ; 
  char adversaire =(pion =='O') ? 'X' : 'O'; 
  int direction [8][2] = {
    {-1,0}, {1,0}, {0,-1}, {0,1}, 
    {-1,-1}, {1,-1} , {-1,1},{1,1}
 } ;  
    for (int i=0;i<8;++i){
        int NewX=direction[i][0]; 
        int NewY=direction[i][1] ; 
        if(verifierRetournement(x+NewX,y+NewY,NewX,NewY,pion,adversaire)){
            return true ; 
        }
    } 
    return false ;
} 
char OrthelloPlateau::gagnant() {
    int countX = 0;
    int countO = 0;
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (plateau[i][j] == 'X') {
                countX++;
            } else if (plateau[i][j] == 'O') {
                countO++;
            }
        }
    }
    if (countX > countO) {
        return 'X';
    } else if (countO > countX) {
        return 'O';
    } else {
        return '.'; // Le jeu est un match nul
    }
}
void OrthelloPlateau::MouvementPossible(int depX[],int depY[],int &numMove,char pion){
    numMove=0 ; 
    for (int i =0 ;i<8;i++){ 
        for (int j =0 ;j<8;j++){ 
            if (MouvementValide(i,j,pion)){
                depX[numMove]=i ; 
                depY[numMove]=j ; 
                numMove++ ; 
            }
        }
    }
} 
char OrthelloPlateau::getCase(int x,int y){
    return plateau[x][y] ; 
} 
int OrthelloPlateau::getTotalPions(){
    int total=0 ; 
    for (int i =0 ;i<8;i++){ 
        for (int j =0 ;j<8;j++){ 
            if (plateau[i][j]!='.') total++ ; 
        }
    }
    return total ; 
}


