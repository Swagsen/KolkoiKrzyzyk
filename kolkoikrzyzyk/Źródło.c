#include"funkcje.h"
#include"pliki.h"

int main()
{
	lista **adrcurrent;
	int zawodnik = GRACZ;
	int gameover = WTRAKCIE;
	bool otwarty = true;
	bool cofanie = false;
	int *pktGracz = malloc(sizeof(int));
	int *pktKomputer = malloc(sizeof(int));
	int plansza[TAB_SIZE];

	wczytaj(pktGracz, pktKomputer);

	while (otwarty == true)
	{
		adrcurrent = malloc(sizeof(lista));
		*adrcurrent = NULL;
		czysc(plansza);
		gameover = WTRAKCIE;

		while (gameover == WTRAKCIE)
		{
			rysuj(plansza, pktGracz, pktKomputer);
			if (cofanie == true) zawodnik = GRACZ;
			if (zawodnik == GRACZ) cofanie = gracz(plansza, adrcurrent);
			if (zawodnik == KOMPUTER) komputer(plansza, adrcurrent);
			gameover = sprawdz(plansza);
			if (zawodnik == GRACZ) zawodnik = KOMPUTER;
			else zawodnik = GRACZ;
		}
		rysuj(plansza, pktGracz, pktKomputer);
		wyniki(gameover, pktGracz, pktKomputer);
		scanf(" %i", &otwarty);
		usunwszystkieruchy(adrcurrent);
		free(adrcurrent);
	}
	zapisz(pktGracz, pktKomputer);

	return 0;
}