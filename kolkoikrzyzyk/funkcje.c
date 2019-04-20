#include"funkcje.h"


void wpiszdolisty(lista **current, int pole)
{
	lista *nowy;
	nowy = malloc(sizeof(lista));
	if (*current == NULL) nowy->prev = NULL;
	else nowy->prev = *current;
	nowy->pole = pole;
	*current = nowy;
}

void cofnijruch(int plansza[TAB_SIZE], lista **current)
{
	if (*current != NULL)
	{
		if (plansza != NULL)
			plansza[(*current)->pole] = PUSTE;
		lista *tmp;
		tmp = (*current)->prev;
		free(*current);
		*current = tmp;
	}
}

void usunwszystkieruchy(lista **current)
{
	while (*current != NULL)
		cofnijruch(NULL, current);
}

void rysuj(int plansza[TAB_SIZE], int *gracz, int *komputer)
{
	const int lewy_gorny = 6;
	const int gorny = 7;
	const int prawy_gorny = 8;
	const int lewy = 3;
	const int srodkowy = 4;
	const int prawy = 5;
	const int lewy_dolny = 0;
	const int dolny = 1;
	const int prawy_dolny = 2;

	system("CLS");
	printf("numer pol pokrywaja sie z numlockiem!     zwyciestwa: Gracz - %i Komputer - %i\n", *gracz, *komputer);
	printf(" %c%c%c%c%c%c%c\n", '-', '-', '-', '-', '-', '-', '-');
	printf(" %c%c%c%c%c%c%c\n", '|', plansza[lewy_gorny] == PUSTE ? ' ' : plansza[lewy_gorny] == GRACZ ? 'X' : 'O', '|', plansza[gorny] == PUSTE ? ' ' : plansza[gorny] == GRACZ ? 'X' : 'O', '|', plansza[prawy_gorny] == PUSTE ? ' ' : plansza[prawy_gorny] == GRACZ ? 'X' : 'O', '|');
	printf(" %c%c%c%c%c%c%c\n", '-', '-', '-', '-', '-', '-', '-');
	printf(" %c%c%c%c%c%c%c\n", '|', plansza[lewy] == PUSTE ? ' ' : plansza[lewy] == GRACZ ? 'X' : 'O', '|', plansza[srodkowy] == PUSTE ? ' ' : plansza[srodkowy] == GRACZ ? 'X' : 'O', '|', plansza[prawy] == PUSTE ? ' ' : plansza[prawy] == GRACZ ? 'X' : 'O', '|');
	printf(" %c%c%c%c%c%c%c\n", '-', '-', '-', '-', '-', '-', '-');
	printf(" %c%c%c%c%c%c%c\n", '|', plansza[lewy_dolny] == PUSTE ? ' ' : plansza[lewy_dolny] == GRACZ ? 'X' : 'O', '|', plansza[dolny] == PUSTE ? ' ' : plansza[dolny] == GRACZ ? 'X' : 'O', '|', plansza[prawy_dolny] == PUSTE ? ' ' : plansza[prawy_dolny] == GRACZ ? 'X' : 'O', '|');
	printf(" %c%c%c%c%c%c%c\n", '-', '-', '-', '-', '-', '-', '-');
}

void wyniki(int stan, int *pktgracz, int *pktkomputer)
{
	if (stan == WINGRACZ)
	{
		printf("wygral gracz!\n");
		*pktgracz += 1;
	}
	if (stan == WINKOMPUTER)
	{
		printf("wygral komputer!\n");
		*pktkomputer += 1;
	}
	if (stan == REMIS)
	{
		printf("remis!\n");
		*pktgracz += 1;
		*pktkomputer += 1;
	}
	printf("wpisz '1' aby zagrac, jeszcze raz cokolwiek innego aby wyjsc: ");
}

int gracz(int plansza[TAB_SIZE], lista **current)
{
	const int poprawka = 1; //poprawka wpisywanej cyfry a pole tablicy
	char pole = 0;
	bool zle = true;
	while (zle == true)
	{
		printf("podaj pole <1-9> lub '<' aby cofnac ruch : ");
		scanf(" %c", &pole);

		if (pole == '<')
		{
			cofnijruch(plansza, current); //cofa dwa razy aby cofnac tez ruch komputera
			cofnijruch(plansza, current);
			return true;
		}
		else if (pole - '0' > 0 && pole - '0' <= TAB_SIZE && plansza[pole - '0' - poprawka] == PUSTE)
		{
			zle = false;
		}
		else
		{
			printf("zle podane pole sproboj jeszcze raz\n");
		}
	}
	plansza[pole - '0' - poprawka] = GRACZ;
	wpiszdolisty(current, pole - '0' - poprawka);
	return false;
}

int minimax(int plansza[TAB_SIZE], int zawodnik)
{
	int m, max;
	if (sprawdz(plansza) == zawodnik) return (zawodnik == KOMPUTER) ? WINGRACZ : WINKOMPUTER;
	if (sprawdz(plansza) == REMIS) return PUSTE;
	zawodnik = (zawodnik == KOMPUTER) ? GRACZ : KOMPUTER;
	max = (zawodnik == GRACZ) ? duzo : malo;

	for (int i = TAB_FIRST_ELEM; i < TAB_SIZE; i++)
	{
		if (plansza[i] == PUSTE)
		{
			plansza[i] = zawodnik;
			m = minimax(plansza, zawodnik);
			plansza[i] = PUSTE;
			if (((zawodnik == GRACZ) && (m < max)) || ((zawodnik == KOMPUTER) && (m > max))) max = m;

		}
	}
	return max;
}

void komputer(int plansza[TAB_SIZE], lista **current)
{
	int pole, i, m, max;
	max = malo;
	for (i = TAB_FIRST_ELEM; i < TAB_SIZE; i++)
	{
		if (plansza[i] == PUSTE)
		{
			plansza[i] = KOMPUTER;
			m = minimax(plansza, KOMPUTER);
			plansza[i] = PUSTE;
			if (m > max)
			{
				max = m;
				pole = i;
			}
		}
	}
	plansza[pole] = KOMPUTER;
	wpiszdolisty(current, pole);
}

int sprawdz(int plansza[TAB_SIZE])
{
	const int ilelini = 3;
	const int wiersz1 = 0;
	const int wiersz2 = 3;
	const int wiersz3 = 6;
	const int kolumna1 = 0;
	const int kolumna2 = 1;
	const int kolumna3 = 2;

	const int lewy_gorny = 6;
	const int prawy_gorny = 8;
	const int srodkowy = 4;
	const int lewy_dolny = 0;
	const int prawy_dolny = 2;

	for (int zawodnik = KOMPUTER; zawodnik <= GRACZ; zawodnik += 2)
	{
		for (int i = TAB_FIRST_ELEM; i < ilelini; i++)
		{
			if ((plansza[kolumna1 + ilelini * i] == zawodnik) && (plansza[kolumna2 + ilelini * i] == zawodnik) && (plansza[kolumna3 + ilelini * i] == zawodnik)) return zawodnik;
			if ((plansza[wiersz1 + i] == zawodnik) && (plansza[wiersz2 + i] == zawodnik) && (plansza[wiersz3 + i] == zawodnik)) return zawodnik;

		}
		if ((plansza[lewy_dolny] == zawodnik) && (plansza[srodkowy] == zawodnik) && (plansza[prawy_gorny] == zawodnik)) return zawodnik;
		if ((plansza[prawy_dolny] == zawodnik) && (plansza[srodkowy] == zawodnik) && (plansza[lewy_dolny] == zawodnik)) return zawodnik;
	}

	int tmp = 0;
	for (int i = TAB_FIRST_ELEM; i < TAB_SIZE; i++)
		if (plansza[i] != PUSTE) tmp++;

	if (tmp == TAB_SIZE) return REMIS;
	return WTRAKCIE;
}

void czysc(int plansza[TAB_SIZE])
{
	for (int i = TAB_FIRST_ELEM; i < TAB_SIZE; i++)
		plansza[i] = 0;
}
