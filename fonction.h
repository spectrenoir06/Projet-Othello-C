
#define TAILLE_CH 256
#define NB_CASES 64
#define NB_CASES_PAR_LIGNE 8

#define COLOR_BORD_CAR 0
#define COLOR_BORD_BACK 3
#define COLOR_PION_J1 0
#define COLOR_PION_J2 7
#define COLOR_PLATEAU 2
#define COLOR_AIDE 1

struct partie
{
	int damier[NB_CASES];
	char nomJ1[TAILLE_CH];
	char nomJ2[TAILLE_CH];
	int premierJoueurJoue;
};

int getCase(struct partie *p,int ligne, int colonne); //lire la valeur d'une case en X,Y

void setCase(struct partie *p,int ligne, int colonne, int val); //modifier la valeur d'une case en X,Y

void change(struct partie *p);

struct partie *creerPartie(); //initialiser un partie

void affichage(struct partie *p); //affichage simple

void affichage2(struct partie *p); //affiche les coords + les coups jouable + bord

//------------------------------------  Partie 2 ---------------------------------------


int priseDansDirectionPossible(struct partie *p , int ligne , int colonne , int horizontal, int vertical);

void mouvementDansDirection(struct partie *p, int ligne, int colonne, int horizontal,int vertical );

void mouvement(struct partie *p, int ligne, int colonne);

int joueurPeutJouer(struct partie *p);



//------------------------------------  Partie 3  ---------------------------------------


int saisieJoueur(int *ligne, int *colonne);//int *ligne, int *colonne)

int tourJoueur(struct partie *p);

int gagnant(struct partie *p);

int finPartie(struct partie *p);

int jouerPartie(struct partie *p);

int sauvegardePartie(struct partie *p);

int chargementPartie(struct partie **p);

int menu(struct partie *p);


//--------------------------------en plus----------------------------

void score(struct partie *p,int *j1, int *j2);

