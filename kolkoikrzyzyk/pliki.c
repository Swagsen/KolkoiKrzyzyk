#include"pliki.h"

void wczytaj(int *pktgracz, int *pktkomputer)
{
	const int liczbapktpoczatkowych = 0;

	FILE* file = fopen("save.txt", "r");
	if (file != NULL)
	{
		fscanf(file, "%i\n%i", pktgracz, pktkomputer);
		fclose(file);
	}
	else
	{
		*pktgracz = liczbapktpoczatkowych;
		*pktkomputer = liczbapktpoczatkowych;
	}

}

void zapisz(int *pktgracz, int *pktkomputer)
{
	FILE* file = fopen("save.txt", "w");
	fprintf(file, "%i\n%i", *pktgracz, *pktkomputer);
	fclose(file);
}