#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "couleursTerminal.h"
#include "fonction.h"

//------------------------------------  Partie 1 ---------------------------------------



int getCase(struct partie *p,int x, int y) //lire la valeur d'une case en X,Y
{
    if (x>=0 && x<NB_CASES_PAR_LIGNE && y>=0 && y<NB_CASES/NB_CASES_PAR_LIGNE)
	{
	    return (p->damier[x+(y*8)]);
	}
    else
    {
        return 0;
    }
}

void setCase(struct partie *p,int x, int y, int val) //modifier la valeur d'une case en X,Y
{
    if (x>=0 && x<NB_CASES_PAR_LIGNE && y>=0 && y<NB_CASES/NB_CASES_PAR_LIGNE)
	{
	    p->damier[x+(y*8)]=val;
	}
    else
    {
        printf("erreur setcase pas dans la map");
    }
}

void change(struct partie *p)
{
	if (p->premierJoueurJoue)
	{
		p->premierJoueurJoue = 0;
	}
	else
	{
		p->premierJoueurJoue = 1;
	}
}

struct partie *creerPartie() //initialiser un partie
{
	struct partie *p = (struct partie *) malloc (sizeof (struct partie) ); //allocation de la memoire et cast
	if (p==NULL)
	{
	    printf("Plus de memoire disponible pour creer partie");
	}
	int i;
	for(i=0; i <NB_CASES; i++) //remplissage du damier
	{
		p->damier [i]=0; //vide
	}
	setCase(p,3, 3,-1); //blanc
	setCase(p,4, 3, 1); // noir
	setCase(p,3, 4, 1);
	setCase(p,4, 4,-1);

    strcpy (p->nomJ1, "Antoine");
    strcpy (p->nomJ2, "Pierre");

    p->premierJoueurJoue = 1;

	return p;
}

void affichage(struct partie *p) //affichage simple
{
	int x, y;
	for (y=0; y <(NB_CASES/NB_CASES_PAR_LIGNE); y++)
	{
		for (x=0; x <NB_CASES_PAR_LIGNE; x++)
		{
		    if (getCase(p,x,y)==0)
		    {
                changerCouleursTerminal(2,2); //vert
		    }
            else if (getCase(p,x,y)==1)
            {
                changerCouleursTerminal(0,0); //noir
            }
            else if (getCase(p,x,y)==-1)
            {
                changerCouleursTerminal(7,7); //blanc
            }
			printf ("  ");
		}
		changerCouleursTerminal(9,9); //par defaut
		printf("\n");
	}
}

void affichage2(struct partie *p) //affiche les coords + les coups jouable + bord
{
	int x, y;
    int j1,j2;
    score(p,&j1,&j2);

    //system("clear");

	changerCouleursTerminal(COLOR_BORD_CAR,COLOR_BORD_BACK); // couleur Top
	printf("  ");
	for (x=0; x <NB_CASES_PAR_LIGNE; x++)
	{
	    printf("%c ",'a'+x); //affichage alphabet
	}
	printf("  ");
	changerCouleursTerminal(9,9);
	printf("\n");


	for (y=0; y <(NB_CASES/NB_CASES_PAR_LIGNE); y++)
	{
	    changerCouleursTerminal(COLOR_BORD_CAR,COLOR_BORD_BACK); //couleur cote gauche
	    printf(" %d",y+1); //affichage numero de ligne

		for (x=0; x <NB_CASES_PAR_LIGNE; x++)
		{
			if (coupValide(p,x,y) && !(getCase(p,x,y)))
			{
			    changerCouleursTerminal(COLOR_AIDE,COLOR_PLATEAU);
				printf ("[]");
			}
			else
			{
				if (getCase(p,x,y)==0)
                {
                    changerCouleursTerminal(COLOR_PLATEAU,COLOR_PLATEAU); //plateau
                }
                else if (getCase(p,x,y)==1)
                {
                    changerCouleursTerminal(COLOR_PION_J1,COLOR_PION_J1); // J1
                }
                else if (getCase(p,x,y)==-1)
                {
                    changerCouleursTerminal(COLOR_PION_J2,COLOR_PION_J2); // J2
                }
                printf ("  ");
			}
		}


		changerCouleursTerminal(COLOR_BORD_CAR,COLOR_BORD_BACK); // couleur cote droit
		printf("  ");
		changerCouleursTerminal(9,9);

		if (y==0)
		{
            if (p->premierJoueurJoue)
            {
                printf("  Tour de %s",p->nomJ1);
            }
            else
            {
                printf("  Tour de %s",p->nomJ2);
            }
        }
        else if (y==1)
		{
            printf("  Score :");
        }
        else if (y==2)
		{
            printf("   %s : %d",p->nomJ1,j1);
        }
        else if (y==3)
		{
            printf("   %s : %d",p->nomJ2,j2);
        }
        printf("\n");
	}
	for (x=0; x <NB_CASES_PAR_LIGNE+2; x++)
    {
        changerCouleursTerminal(COLOR_BORD_CAR,COLOR_BORD_BACK); // couleur footer
		printf("  ");
    }
    changerCouleursTerminal(9,9);
    printf("\n");
}

//------------------------------------  Partie 2 ---------------------------------------


int priseDansDirectionPossible(struct partie *p , int x , int y , int horizontal, int vertical)
{
    if (horizontal==0 && vertical==0) // si direction null
    {
        return 0;
    }

	int scanX = x+horizontal; //deplacement du scanX dans la direction
	int scanY = y+vertical; //deplacement du scanY dans la direction
	int adv;
	int me;

	if (p->premierJoueurJoue) // au tour de joueur 1
	{
		adv=-1; //adversaire == noir
		me=1;  // moi == blanc
	}
	else // au tour de joueur 2
	{
		adv=1;
		me=-1;
	}
	if (scanX>=0 && scanX<NB_CASES_PAR_LIGNE && scanY>=0 && scanY<NB_CASES/NB_CASES_PAR_LIGNE && getCase(p,scanX,scanY)==adv) //Si sur le terrain and adversaire a coter
	{
        scanX += horizontal;
        scanY += vertical;

        while ( scanX>0 && scanX<NB_CASES_PAR_LIGNE && scanY>0 && scanY<NB_CASES/NB_CASES_PAR_LIGNE)
        {
            if (getCase(p,scanX,scanY)==me) // rencontre d'un pion de ma couleur
            {
                return 1;
            }
            else if (getCase(p,scanX,scanY)==0) // rencontre d'une case vide
            {
                return 0;
            }
            scanX += horizontal;
            scanY += vertical;
        }
	}
    return 0;

}

int coupValide(struct partie *p,int x,int y) // == priseDansDirectionPossible() dans une des 8 directions
{
	int dx;
	int dy;
	for(dx=-1;dx<2;dx++)
	{
		for(dy=-1;dy<2;dy++)
			{
				if (priseDansDirectionPossible(p , x , y , dx, dy))
				{
					return 1; //si on peut jouer dans une direction
				}
			}
	}
	return 0; //si aucune solution
}


void mouvementDansDirection(struct partie *p, int x, int y, int horizontal,int vertical )
{
    if (!(horizontal==0 && vertical==0))
    {
		int scanX = x+horizontal;
		int scanY = y+vertical;
		int me;
		int boucle=1;

		if (p->premierJoueurJoue)
		{
			me=1;
		}
		else
		{
			me=-1;
		}
		while ( scanX>0 && scanX<NB_CASES_PAR_LIGNE && scanY>0 && scanY<NB_CASES/NB_CASES_PAR_LIGNE && boucle)
		{
			if (getCase(p,scanX,scanY)==me)
			{
				boucle=0;
			}
			else
			{
				setCase(p,scanX,scanY,me);
			}
			scanX += horizontal;
			scanY += vertical;
		}
    }
}

void mouvement(struct partie *p, int x, int y)
{
	int dx;
	int dy;

    if (p->premierJoueurJoue)
    {
        setCase(p,x,y,1);  // on pose un pion
    }
    else
    {
        setCase(p,x,y,-1);
    }

	for(dx=-1;dx<2;dx++)
	{
		for(dy=-1;dy<2;dy++)
        {
            if (priseDansDirectionPossible(p,x,y,dx,dy))
            {
                mouvementDansDirection(p,x,y,dx,dy);
            }
        }
	}
}

int joueurPeutJouer(struct partie *p)
{
    int x,y;
    for (y=0; y <(NB_CASES/NB_CASES_PAR_LIGNE); y++)
	{
		for (x=0; x <NB_CASES_PAR_LIGNE; x++)
		{
			if (!(getCase(p,x,y)) && coupValide(p,x,y))
			{
			    return 1;
			}
		}
    }
    return 0;
}





//------------------------------------  Partie 3  ---------------------------------------


int saisieJoueur(int *x, int *y)//int *x, int *y)
{
    char input[10];
    while (1)
    {
        scanf("%s",input);
        if (input[0]=='A')
        {
            return -2;
        }
        else if (input[0]=='M')
        {
            return -1;
        }
        else if ( (input[0]>= 'a' && input[0] <= 'h' ) && (input[1] > '0' && input[1] < '9') )
        {
            *x = (input[0]-'a');
            *y = (input[1]-'1');
            return 1;
        }
        printf("pas compris : %s\n",input);
        //return 0;
    }
}

int tourJoueur(struct partie *p)
{
    affichage2(p);
    if (joueurPeutJouer(p))
    {
        int x,y;
        int r;
        while (1)
        {
            r = saisieJoueur(&x,&y);
            if (r == 1)
            {
                if (coupValide(p,x,y) && !(getCase(p,x,y)))
                {
                    mouvement(p, x, y);
                    change(p);
                    return r;
                }
                printf("Coup impossible.\n");
            }
            else
            {
                return r;
            }
        }
    }
    else
    {
        change(p);
        return 0;
    }
}

int gagnant(struct partie *p)
{
    int i;
    int j1;
    int j2;
    for (i=0;i<NB_CASES;i++)
    {
        if (p->damier[i]==1)
        {
           j1++;
        }
        else if (p->damier[i]==-1)
        {
            j2++;
        }
    }
    if (j2==j1)
    {
        return 0;
    }
    else if (j1>j2)
    {
        return 1;
    }
    else
    {
        return -1;
    }
}

int finPartie(struct partie *p)
{
    if (!joueurPeutJouer(p))
    {
        change(p);
        if (!joueurPeutJouer(p))
        {
            return 1;
        }
    }
    return 0;
}

int jouerPartie(struct partie *p)
{
    int mode;
    while (1)
    {
        mode = tourJoueur(p);
        if (finPartie(p)) // si partie fini
        {
            printf("fin partie\n");
            if (gagnant(p)==1)
            {
                printf("%s a gagné\n",p->nomJ1);
            }
            else if (gagnant(p)==-1)
            {
                printf("%s a gagné\n",p->nomJ2);
            }
            else
            {
                printf("egalité");
            }
            return 1;
        }
        else if (mode == -2) // si "A"
        {
            if (p->premierJoueurJoue)
            {
                printf("%s a gagné\n",p->nomJ2);
            }
            else
            {
                printf("%s a gagné\n",p->nomJ1);
            }
            return 1;
        }
        else if (mode==-1) // si "M"
        {
            return 0;
        }
    }
}





//------------------------------------  Partie 4  ---------------------------------------




int sauvegardePartie(struct partie *p)
{
    FILE* fichier = NULL; // struct FILE* fichier

    fichier = fopen("sauvegarde.txt", "w");

    if (fichier != NULL)
    {
        int i;
        for (i=0;i<NB_CASES;i++)
        {
            if (p->damier[i] == 0)
            {
                fputc('0', fichier);
            }
            else if (p->damier[i] == 1)
            {
                fputc('1', fichier);
            }
            else if (p->damier[i] == -1)
            {
                fputc('2', fichier);
            }

        }
        fprintf(fichier, " %s %s %d",p->nomJ1,p->nomJ2,p->premierJoueurJoue);

        fclose(fichier);
        return 1;
    }
    else
    {
        printf("erreur de sauvegarde");
        return 0;
    }
}

int chargementPartie(struct partie **p)
{
    *p = creerPartie(); // nouvelle partie
    FILE* fichier = NULL; // struct FILE* fichier

    fichier = fopen("sauvegarde.txt", "r");

    if (fichier != NULL)
    {
        char tab[NB_CASES];
        char j1[TAILLE_CH];
        char j2[TAILLE_CH];
        int play;
        fscanf(fichier,"%s",tab);
        fscanf(fichier,"%s",j1);
        fscanf(fichier,"%s",j2);
        fscanf(fichier,"%d",&play);
        int i;

        for (i=0;i<NB_CASES;i++)
        {
            if (tab[i] == '0')
            {
                (*p)->damier[i]=0;
            }
            else if (tab[i] == '1')
            {
                (*p)->damier[i]=1;
            }
            else if (tab[i] == '2')
            {
                (*p)->damier[i]= -1 ;
            }
        }

        strcpy ((*p)->nomJ1, j1);
        strcpy ((*p)->nomJ2, j2);
        (*p)->premierJoueurJoue=play;

        fclose(fichier);
        printf("Sauvegarde dispo\n");
        return 1;
    }
    else
    {
        printf("Pas de sauvegarde dispo\n");
        return 0;
    }
}

int menu(struct partie *p)
{
    //system("clear");
    printf("1 - Nouvelle partie\n");
    printf("2 - Charger partie sauvegarde\n");
    printf("3 - Quitter\n");
    if (p!=NULL)
    {
        printf("4 - Sauvegarder partie courante\n");
        printf("5 - Reprendre partie courante\n");
    }

    int inp;

    while(1)
    {
        printf("\nSelectionne une option : ");
        //fflush(stdin);

        scanf("%d",&inp);
        return inp;
    }
}

//-----------------------------------------------------------

void score(struct partie *p,int *j1, int *j2)
{
    int i;
    *j1=0;
    *j2=0;

    for (i=0;i<NB_CASES;i++)
    {
        if (p->damier[i]==1)
        {
           (*j1)++;
        }
        else if (p->damier[i]==-1)
        {
            (*j2)++;
        }
    }
}

//------------------------------------  couleur ---------------------------------------

void changerCouleursTerminal(int couleurE, int couleurF)
{
		printf("\E[%dm", couleurE+30);
		printf("\E[%dm", couleurF+40);
}

void changerCouleurFondTerminal(int couleurF)
{
	printf("\E[%dm", couleurF+40);
}

void changerCouleurEcritureTerminal(int couleurE)
{
	printf("\E[%dm", couleurE+30);
}


//-------------------------------------------Main----------------------------------------------

int main ()
{
    int test, mode;
	struct partie *jeu = NULL ;
	while (1)
	{
        mode = menu(jeu);
        if (mode==1) // nouvelle partie
        {
            jeu = creerPartie();
            printf("Nom du joueur 1 : ");
            scanf("%s",jeu->nomJ1);
            printf("Nom du joueur 2 : ");
            scanf("%s",jeu->nomJ2);

            if (jouerPartie(jeu))
            {
                free(jeu);
                jeu = NULL;
            }
        }
        else if (mode==2) // chargement partie
        {
            if (chargementPartie(&jeu))
            {
                if (jouerPartie(jeu))
                {
                    free(jeu);
                    jeu = NULL;
                }
            }
        }
        else if (mode==3)
        {
            printf("Fermeture du jeu\n"); // fermeture du prog
            return 0;
        }
        else if (mode == 4 && jeu!=NULL) // sauvegarde de la partie
        {
            sauvegardePartie(jeu);
            printf("Sauvegarde termine\n");
        }
        else if (mode == 5 && jeu!=NULL) // reprise d'une partie
        {
            printf("Reprise\n");
            if (jouerPartie(jeu))
            {
                free(jeu);
                jeu = NULL;
            }
        }
        else
        {
            printf("Cmd inconnue\n");
        }

	}
	return 0;
}
