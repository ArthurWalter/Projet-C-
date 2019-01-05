#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define taille 255


struct Coord{//structure contenant les coordonées
   int N;//coordonnées des lignes
   int M;//coordonnées des colonnes
};

struct Case{//structure dédiée aux cases
   struct Coord C;
   int Nim;
};
	


int Lire_Entier(int bi, int bs);
void Lire_Parametres(int *N,int *M, int *R, int *Next,int *Niveau);
int Hasard(int bi, int bs);
void Init_Grille(int N, int M, int R, struct Case liste_pions[taille]);
int Contient_Pion(struct Case liste_pions[taille],int N, int M, int R);
void Affiche_Grille(int N, int M, int R, struct Case liste_pions[taille]);
void Deplacement(int N, int M, struct Case choix[taille],int bouge,int i,int j, int k);
void Tab_voisines(int N , int M, struct Case choix[taille], int i, int j,int *possibilites,int mvt_choisi[taille]);
void Maj_Grille(int i, int j,int N,int M, struct Case liste_pions[taille], int b, int R) ;
int Nimber(int N, int M, int i, int j);
int Nim_Addition(struct Case liste_pions[taille], int R);
void Move_Hasard(struct Case liste_pions[taille],struct Case choix[taille],int R, int N, int M);
void Move_gagnant(struct Case liste_pions[30],struct Case choix[4],int R, int N, int M);
void Move_joueur(struct Case liste_pions[taille],struct Case choix[taille],int R, int N, int M);



int Lire_Entier(int bi, int bs)//Saisie d'un entier compris entre deux bornes
{int x;
   do{
      scanf("%d", &x);
   } while((x < bi) || (x > bs));
   return x;
}

void Lire_Parametres(int *N,int *M, int *R, int *Next,int *Niveau)//Paramètres de jeu
{
   printf("Paramètres du jeu\n---------------\n");
   printf("nombre de lignes (3-30) : "); *N=Lire_Entier(3,30);
   printf("nombre de colonnes (3-30) : ");*M=Lire_Entier(3,30);
   printf("nombre de pions (1-%d) : ",*N);*R=Lire_Entier(1,*N);
   printf("niveau de 1 à 3 : ");*Niveau=Lire_Entier(1,3);
   printf("qui commence ?\nl'ordinateur (1) ou le joueur (2) : ");
   *Next=Lire_Entier(1,2);
}

int Hasard(int bi, int bs)//renvoie un nombre au hasard compris entre deux bornes
{srand((unsigned int)time(NULL));
   return (rand()%(bi+bs));
}



void Init_Grille(int N, int M, int R, struct Case liste_pions[taille]){//définie les coordonnées des pions en début de partie
   int i;
   for (i=1;i<=R;i++)
   {
      liste_pions[i].C.N=i;
      liste_pions[i].C.M=1;
   }
}

int Contient_Pion(struct Case liste_pions[],int N, int M, int R){//définie si une case est occupée par un pion
   int i,rep=0;
   for (i=1;i<=R;i++){
      if(liste_pions[i].C.N==N && liste_pions[i].C.M==M)//vérifie si les coordonnées du pion n°i sont les mêmes que celles de la case
         rep=1;	
   }	
  
   return rep;
   
}


void Affiche_Grille(int N, int M, int R, struct Case liste_pions[taille])//affiche la grille avec des 0 pour les cases occupées et des - pour les cases vides
{	
   int i,j,k;
   printf("\n");
   printf("    |");
   for(k=1;k<=M;k++)
      printf(" %2d |",k);
   printf("\n");
   for(i=1;i<=N;i++)
   {	
      {
         printf(" %2d |",i);
      	
      }
      for(j=1;j<=M;j++)
         if(Contient_Pion(liste_pions,i,j,R))//on vérifie si la case est occupée
            printf(" 0  |");
         else
            printf(" -  |");
      
      printf("\n");
     
   }
}

	
	
	
void Deplacement(int N, int M, struct Case choix[taille],int bouge,int i,int j, int k)//permet le mouvement d'un pion selon la destination saisie par l'utilisateur
{
	
   if (bouge==1)
   {
      choix[k].C.M=j+1; //descend de 1 case
      choix[k].C.N=i;
   }
   if (bouge==2)
   {
      choix[k].C.N=i+1; //avance de 1 case
      choix[k].C.M=j;
   }
   if (bouge==3)
   {
      choix[k].C.M=j+2; //descend de 2 cases
      choix[k].C.N=i;
   }
   if (bouge==4)
   {
      choix[k].C.N=i+2; //avance de 2 cases
      choix[k].C.M=j;
   }
	
}
	
	
void Tab_voisines(int N , int M, struct Case choix[taille], int i, int j,int *possibilites,int mvt_choisi[taille])
{     //définie les possibilités de mouvement par rapport à la position actuelle du pion 
   int k; // itérateur des choix.
   for(k=1;k<=4;k++)
   {
      switch(k) 
      {
         case 1: 
            if(M-(choix[k].C.M)>=1){
               mvt_choisi[*possibilites]=1;
               *possibilites++;}
            break;
      			
         case 2: 
            if(N-(choix[k].C.N)>=1){
               mvt_choisi[*possibilites]=2;
               *possibilites++;}
            break;
      			
         case 3: 
            if(M-(choix[k].C.M)>=2){
               mvt_choisi[*possibilites]=3;
               *possibilites++;}
            break;
      			
         case 4: 
            if(N-(choix[k].C.N)>=2){
               mvt_choisi[*possibilites]=4;
               *possibilites++;}
            break;
      }
   }
}

void Maj_Grille(int i, int j,int N,int M, struct Case liste_pions[taille], int b, int R) 
{
   liste_pions[b].C.N=i;
   liste_pions[b].C.M=j;
   if(liste_pions[b].C.N==N && liste_pions[b].C.M==M )
   {
      liste_pions[i].Nim=0;
      liste_pions[i].C.N=0;
      liste_pions[i].C.M=0;
      R--;
   }
   Nim_Addition(liste_pions,R);
   Affiche_Grille(N,M,R,liste_pions);

}	

int Nimber(int N, int M, int i, int j)
{
   return ((N-i)%3)^((M-j)%3);  //calcul du nimber d'une case à l'aide du ou exclusif
}

int Nim_Addition(struct Case liste_pions[taille], int R)
{
   int total=liste_pions[1].Nim, i;   
   for(i=2;i<=R;i++)
      total=total^liste_pions[i].Nim;  //Permet de recalculer le nimber en tenant compte des cases occupées par les pions grâce à l'opérateur ^
   return total;
}

void Move_Hasard(struct Case liste_pions[taille],struct Case choix[taille],int R, int N, int M)
{	
   int i,j,pion_choisi,mvt_choisi[taille],possibilites,bouge;
   pion_choisi=Hasard(1,R);
   i=liste_pions[pion_choisi].C.N; 
   j=liste_pions[pion_choisi].C.M;
   Tab_voisines(N,M,choix,i,j,&possibilites,mvt_choisi);
   bouge=Hasard(1,possibilites);   //Permet à l'ordi de choisir une des possibilités de déplacement au hasard
   bouge=mvt_choisi[bouge];        //Bouge: Variable recyclée pour optimisation
   Deplacement(N,M,choix,bouge,i,j,pion_choisi);
   Maj_Grille(i,j,N,M,liste_pions,pion_choisi,R); //Met à jour la grille de jeu une fois le déplacement effectué
}
void Move_gagnant(struct Case liste_pions[taille],struct Case choix[taille],int R, int N, int M)
{
   int possibilites,k,mvtchoisi[taille],bouge; 
   for(k=1;k<=R;k++)
   {
      if(Nimber(N,M,liste_pions[k].C.N,liste_pions[k].C.M)!=0)
      {
         Tab_voisines(N,M,choix,choix[k].C.N,choix[k].C.M,&possibilites,mvtchoisi);
      	
         if(Nimber(N,M,choix[k].C.N,choix[k].C.M)==0)
         {bouge=mvtchoisi[0];
            Deplacement(N,M,choix,bouge,choix[k].C.N,choix[k].C.M,k);}
         else
            Move_Hasard(liste_pions,choix,R,N, M);   //Mouvement gagnant et s'il n'y en a pas, on fait MoveHasard
      }
   }
}

void Move_joueur(struct Case liste_pions[taille],struct Case choix[taille],int R, int N, int M)
{
   int i,choix_pion,mvt_choisi[taille],nb_cases,possibilites,choix_dest;
   printf("Choisir un pion : \n");
   for (i=1;i<=R;i++)
      printf("%d : (%d,%d)\n",i,liste_pions[i].C.N,liste_pions[i].C.M);  //Mouvements du joueur
   printf("\n ---> ");
   choix_pion=Lire_Entier(1,R);
   printf("\nChoisir la destination : \n");
   Tab_voisines(N,M,choix,liste_pions[i].C.N,liste_pions[i].C.M,&possibilites,mvt_choisi);
   for (i=1;i<=possibilites;i++)
      printf("%d : (%d,%d)\n ",i,liste_pions[i].C.N,liste_pions[i].C.M);
   printf("\n ---> ");
   choix_dest=Lire_Entier(1,possibilites);
   Deplacement(N,M,choix,choix_dest,liste_pions[i].C.N,liste_pions[i].C.M,i);
   Maj_Grille(liste_pions[i].C.N,liste_pions[i].C.M,N, M,liste_pions,i,R);
	
}


main()
{
   int N,M,R,Next,Niveau;
   struct Case liste_pions[taille];
   struct Case choix[taille];
   Lire_Parametres(&N,&M,&R,&Next,&Niveau);
   Init_Grille(N,M,R,liste_pions);
   Affiche_Grille(N,M,R,liste_pions);
   while(1)
   {
      if(Next==2)
      {
         printf("\nÀ toi de jouer ! ");
         Move_joueur(liste_pions,choix, R, N, M);
      }
      else
      {printf("\nL'ordinateur joue ---> \n");
         switch(Niveau)
         {
            case 1:
               if(Hasard(1,10)==1)
                  Move_gagnant(liste_pions,choix,R, N, M);
               else Move_Hasard(liste_pions,choix,R,  N,  M); 
               break ;
            case 2 :
               if(Hasard(1,2)==1)
                  Move_gagnant(liste_pions,choix,R, N, M);
               else Move_Hasard(liste_pions,choix,R,  N,  M); 
               break ;
            case 3 :
               if(Hasard(1,10)>1)
                  Move_gagnant(liste_pions,choix,R, N, M);
               else Move_Hasard(liste_pions,choix,R,  N,  M); 
               break ;
         }
      
      
      }
   if (Next==2) //changement de tour
      Next=1;
   else
      Next=2;
   
   }




}
