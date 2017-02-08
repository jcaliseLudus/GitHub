// BatailleNavale.cpp : définit le point d'entrée pour l'application console.
//

#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h> 

#define MAXBATEAU 5

typedef struct Cellule {

	int ligne;
	int colonne;

}cell;

typedef struct Bateau {

	cell lico[MAXBATEAU];

}boat;

typedef struct Flotte {

	boat vaisseau[MAXBATEAU];

}fleet;

typedef enum BOOL {
	True, False
}BOOL;

int  Random();
void AfficheBateau(boat navire);
cell CreateCell(int ligne, int colonne);
boat CreateBoat(cell cellule, int i	);
BOOL CompareCell(cell cellule1, cell cellule2);
BOOL VerifBoat(boat navire, cell cellule);
BOOL VerifFleet(fleet armada, boat navire);



int main()
{
	int choix, boucle, ligne, colonne, i;
	double controle1, controle2;
	fleet player1fleet;
	fleet player2fleet;
	boat shipOne;
	boat shipTwo;
	boat shipThree;
	boat shipFour;
	boat shipFive;
	i = 0;
	do
	{
		fflush(stdin);
		system("cls");
		printf("Bienvenue a la Bataille Navale !\n\n\n\n\n");
		printf("Indiquez le nombre de joueur :\n");
		printf("1) Un joueur\n");
		printf("2) Deux joueur\n");
		scanf_s("%d", &choix);

		switch (choix) {

		case 1:
			boucle = 1;
			break;
		case 2:
			boucle = 1;
			break;
		default:
			boucle = 2;
			break;
		}


	} while (boucle == 2);

	if (choix == 1) {

		

		system("cls");
		printf("Création de votre flotte...\n");
		printf("Vous possedez 5 bateau, vous allez les placer les un après les autres.\n");
		

		for (int i = 0; i <= MAXBATEAU; i++) {
			switch (i) {

			case 1:
				
				printf("donner un chiffre pour la ligne, puis la colonne pour votre premier bateau (une case)\n");
				scanf_s("%d", &ligne);
				scanf_s("%d", &colonne);
				shipOne = CreateBoat(CreateCell(ligne, colonne), i-1);
				AfficheBateau(shipOne);
				system("pause");
				break;

			case 2:
				
				system("cls");
				printf("Second bateau (deux cases) (1/2): \n");
				scanf_s("%d", &ligne);
				scanf_s("%d", &colonne);
				controle1 = ligne + colonne;
				shipTwo = CreateBoat(CreateCell(ligne, colonne), i-i);
				do {
					printf("Second bateau (deux cases) (2/2): \n");
					scanf_s("%d", &ligne);
					scanf_s("%d", &colonne);
					controle2 = ligne + colonne;
				} while (controle2 - controle1 != 1 && controle2 - controle1 != -1);
				shipTwo.lico[i-1] = CreateCell(ligne, colonne);
				AfficheBateau(shipTwo);
				system("pause");
				break;

			case 3 : 			

				system("cls");

				printf("Troisieme bateau bateau (3 cases) (1/2): \n");

				scanf_s("%d", &ligne);
				scanf_s("%d", &colonne);

				controle1 = ligne + colonne;

				shipThree = CreateBoat(CreateCell(ligne, colonne), i - i);

				do {
					printf("Troisieme bateau (3 cases) (2/2): \n");
					scanf_s("%d", &ligne);
					scanf_s("%d", &colonne);
					controle2 = ligne + colonne;
				} while (controle2 - controle1 != 1 && controle2 - controle1 != -1);

				shipThree.lico[i - 2] = CreateCell(ligne, colonne);

				if (shipThree.lico[0].ligne == shipThree.lico[1].ligne)
				{
					shipThree.lico[i - 1] = CreateCell(ligne, colonne + 1);
				}
				else
				{
					shipThree.lico[i - 1] = CreateCell(ligne +1, colonne);
				}

				AfficheBateau(shipThree);
				system("pause");
				break;

			case 4:			

				system("cls");

				printf("Quatrieme bateau bateau (4 cases) (1/2): \n");

				scanf_s("%d", &ligne);
				scanf_s("%d", &colonne);

				controle1 = ligne + colonne;

				shipFour = CreateBoat(CreateCell(ligne, colonne), i - i);

				do {
					printf("Quatrieme bateau (4 cases) (2/2): \n");
					scanf_s("%d", &ligne);
					scanf_s("%d", &colonne);
					controle2 = ligne + colonne;
				} while (controle2 - controle1 != 1 && controle2 - controle1 != -1 );

				shipFour.lico[i - 3] = CreateCell(ligne, colonne);

				if (shipFour.lico[0].ligne == shipFour.lico[1].ligne)
				{
					shipFour.lico[i - 2] = CreateCell(ligne, colonne + 1);
					shipFour.lico[i - 1] = CreateCell(ligne, colonne + 2);
				}
				else
				{
					shipFour.lico[i - 2] = CreateCell(ligne + 1, colonne);
					shipFour.lico[i - 1] = CreateCell(ligne + 2, colonne);
				}


				AfficheBateau(shipFour);
				system("pause");
				break;

			case 5:			

				system("cls");

				printf("Quatrieme bateau bateau (4 cases) (1/2): \n");

				scanf_s("%d", &ligne);
				scanf_s("%d", &colonne);

				controle1 = ligne + colonne;

				shipFive = CreateBoat(CreateCell(ligne, colonne), i - i);

				do {
					printf("Quatrieme bateau (4 cases) (2/2): \n");
					scanf_s("%d", &ligne);
					scanf_s("%d", &colonne);
					controle2 = ligne + colonne;
				} while (controle2 - controle1 != 1 && controle2 - controle1 != -1);

				shipFive.lico[i - 3] = CreateCell(ligne, colonne);

				if (shipFive.lico[0].ligne == shipFive.lico[1].ligne)
				{
					shipFive.lico[i - 2] = CreateCell(ligne, colonne + 1);
					shipFive.lico[i - 1] = CreateCell(ligne, colonne + 2);
				}
				else
				{
					shipFive.lico[i - 2] = CreateCell(ligne + 1, colonne);
					shipFive.lico[i - 1] = CreateCell(ligne + 2, colonne);
				}


				AfficheBateau(shipFive);
				system("pause");
				break;
			}
		}

		player1fleet.vaisseau[0] = shipOne;
		player1fleet.vaisseau[1] = shipTwo;
		player1fleet.vaisseau[2] = shipThree;
		player1fleet.vaisseau[3] = shipFour;
		player1fleet.vaisseau[4] = shipFive;

		for (int i = 0; i <= MAXBATEAU; i++) {
			switch (i) {
			case 0:
				shipOne = CreateBoat(CreateCell(Random(), Random()), i);
				controle1 = ligne + colonne;
				break;
			case 1:	 
				shipTwo = CreateBoat(CreateCell(Random(), Random()), i-i);
				controle2 = ligne + colonne;
				do {
					shipTwo.lico[i] = CreateCell(Random(),Random());
				} while (controle2 - controle1 != 1 && controle2 - controle1 != -1);				
				break;
			case 2:
				shipThree = CreateBoat(CreateCell(Random(), Random()), i - 0);
				controle2 = ligne + colonne;
				do {
					shipTwo.lico[i] = CreateCell(Random(), Random());
				} while (controle2 - controle1 != 1 && controle2 - controle1 != -1);
				break;
			case 3:
				break;
			case 4:
				break;
			}
		}

		player2fleet.vaisseau[0] = shipOne;
		player2fleet.vaisseau[1] = shipTwo;
		player2fleet.vaisseau[2] = shipThree;
		player2fleet.vaisseau[3] = shipFour;
		player2fleet.vaisseau[4] = shipFive;
		

		


	}
	else
	{

	}




	return 0;
}


cell CreateCell(int ligne, int colonne)
{
	cell cellule;
	cellule.colonne = colonne;
	cellule.ligne = ligne;
	return cellule;
}

boat CreateBoat(cell cellule, int i)
{
	boat navire;
	navire.lico[i] = cellule;
	return navire;
}

BOOL CompareCell(cell cellule1, cell cellule2)
{
	if (cellule1.colonne == cellule2.colonne && cellule1.ligne == cellule2.ligne)
	{
		return True;
	}
	else
	{
		return False;
	}
}

BOOL VerifBoat(boat navire, cell cellule)
{
	int i;

	for (i = 0; i <= MAXBATEAU; i++)
	{
		CompareCell(navire.lico[i], cellule);
	}

	return False;
}

BOOL VerifFleet(fleet armada, boat navire)
{
	int i;

	for (i = 0; i <= MAXBATEAU; i++)
	{
		VerifBoat(armada.vaisseau[i], navire.lico[i]);
	}

	return False;
}

void AfficheBateau(boat navire) {
	for (int i = 0; i <= MAXBATEAU; i++) {
		if (navire.lico[i].colonne + navire.lico[i].ligne > 0) {
			printf("Coordonee case %d : %d/%d    \n", i+1, navire.lico[i].ligne, navire.lico[i].colonne);
		}
	}
}

int Random(){
	srand(time(NULL));
	int nbgen = rand() % 9 + 1;   
	return nbgen;
}