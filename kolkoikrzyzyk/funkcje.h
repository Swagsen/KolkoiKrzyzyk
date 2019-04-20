#include<stdlib.h>
#include<stdio.h>
#include"pliki.h"
#include"stdbool.h"
#define TAB_SIZE 9
#define TAB_FIRST_ELEM 0
#define duzo 9
#define malo -9

typedef struct kolejka
{
	int pole;
	struct kolejka *prev;
}lista;

enum ktogra { GRACZ = 1, KOMPUTER = -1, PUSTE = 0 };
enum stan { WTRAKCIE = 0, WINGRACZ = 1, WINKOMPUTER = -1, REMIS = 2 };


void wpiszdolisty(lista **current, int pole);


void cofnijruch(int plansza[TAB_SIZE], lista **current);


void usunwszystkieruchy(lista **current);


void rysuj(int plansza[TAB_SIZE], int *gracz, int *komputer);


void wyniki(int stan, int *pktgracz, int *pktkomputer);


int gracz(int plansza[TAB_SIZE], lista **current);


int minimax(int plansza[TAB_SIZE], int zawodnik);


void komputer(int plansza[TAB_SIZE], lista **current);


int sprawdz(int plansza[TAB_SIZE]);


void czysc(int plansza[TAB_SIZE]);
