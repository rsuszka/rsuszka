#include<stdio.h>
#include<stdbool.h>
#include<math.h>
unsigned int zmiana_bitu(unsigned int liczba, int mod_bitu, int bit)
{
	unsigned int zmiana, zmiana2, nowa_liczba;
	if ((bit >= 1) && (bit <= 8 * (sizeof(unsigned int)))) //sprawdzenie zakresu
	{
		if (mod_bitu == 0)
		{
			zmiana = pow(2, (bit - 1));
			zmiana2 = ~zmiana;
			nowa_liczba = liczba & zmiana2; //"ustawienie" n-tego bitu na wartoœæ 0
		}
		if (mod_bitu == 1)
		{
			zmiana = pow(2, (bit - 1));
			nowa_liczba = liczba | zmiana; //"ustawienie" n-tego bitu na wartoœæ 1
		}
		return nowa_liczba;
	}
	else
	{
		printf("Podany bit nie jest z zakresu!\n");
		return 0;
	}
}
bool sprawdzenie(unsigned int liczba, int bit)
{
	unsigned int wynik, sprawdzanie, liczba_sprawdzaj¹ca;
	if ((bit >= 0) && (bit <= 8 * (sizeof(unsigned int)))) //sprawdzenie zakresu
	{
		liczba_sprawdzaj¹ca = pow(2, (bit - 1));
		sprawdzanie = liczba | liczba_sprawdzaj¹ca; //zmiana n-tego bitu na 1
		if (liczba == sprawdzanie)
		{
			wynik = 1; //je¿eli by³a "1"
		}
		else
		{
			wynik = 0; //je¿eli by³o "0"
		}
		printf("bit wynosi: %d\n", wynik); //wyœwitlenie wartoœci n-tego bitu
		return true;
	}
	else
	{
		printf("Podany bit nie jest z zakresu!\n");
		return false; //zwrócenie false gdy n nie nale¿y do zakresu
	}
}
int main(void)
{
	unsigned int liczba, n_liczba;
	int mod_bitu, bit;
	bool spr;
	printf("Podaj liczbe\n");
	scanf_s("%u", &liczba);
	printf("Podaj modyfikacje bitu (0 lub 1)\n");
	scanf_s("%d", &mod_bitu);
	printf("Podaj numer bitu\n");
	scanf_s("%d", &bit);
	n_liczba = zmiana_bitu(liczba, mod_bitu, bit);
	if (n_liczba != 0)
	{
		printf("Liczba po modyfikacji wynosi: %u\n", n_liczba);
	}
	spr = sprawdzenie(liczba, bit);
	system("Pause");
	return 0;
}