#include <stdio.h>
#include <stdlib.h>
#include "stdafx.h"
#define TAILLE  4
#define TAILLE2  7

typedef struct position {

	int x;
	int y;

}token;

void forwardE(token *a);
void forwardW(token *a);
void initTab(token a, int tab[][TAILLE]);
void afficherTab(token a, int tab[][TAILLE]);


int main()
{
	int tab[TAILLE][TAILLE];
	int inc = 1;
	token a;

	a.x = 3;
	a.y = 2;

	initTab(a, tab);
	afficherTab(a, tab);

	a.x = 1;
	a.y = 2;


	printf("\n\n");

	for (int i = 0; i < (TAILLE * TAILLE); i++)
	{		
		if (tab[a.x][a.y] == 0){			
			forwardE(&a);
			tab[a.x][a.y] = inc;	
		}
		else {
			forwardW(&a);
			if (tab[a.x][a.y] == 0){
				tab[a.x][a.y] = inc;
				forwardE(&a);
			}
			
		}		
		inc++;
	}

	afficherTab(a, tab);



	getchar();
	return 0;
}



void forwardE(token *a) {

	if (a->x<= 0)
	{
		a->y +=1;
		a->x+= 4;
	}
	else if (a->y >= 4) {
		a->y = 0;
		a->x -= 1;
	}

	else {
		a->y += 1;
		a->x-= 1;
	}

}

void forwardW(token *a) {

	if (a->x <= 0)
	{
		a->y += 1;
		a->x += 4;
	}
	else if(a->y >= 4){
		a->y = 0;
		a->x -= 1;
	}
	else
	{
		a->x -= 1;
		a->y -= 1;
	}
}

void initTab(token a, int tab[][TAILLE]) {

	for (a.x = 0; a.x <= TAILLE; a.x++) {
		for (a.y = 0; a.y <= TAILLE; a.y++) {
			tab[a.x][a.y] = 0;
		}
		tab[a.x][a.y] = 0;
	}
}

void afficherTab(token a, int tab[][TAILLE]) {

	for (a.x = 0; a.x <= TAILLE; a.x++) {
		for (a.y = 0; a.y <= TAILLE; a.y++) {
			printf(" %i ", tab[a.x][a.y]);
		}
		printf("\n");
	}
}

