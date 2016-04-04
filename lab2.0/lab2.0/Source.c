#include<stdio.h>
#include<stdlib.h>
typedef struct Element_
{
	char *nazwisko;
	char *imie;
	int wiek;
	struct Element_ *nast;
} Element;
typedef struct Lista_
{
	struct Element_ *lista;
	int le;
} Lista;
void dodaj_element(Lista *lista, char *nazwa_pliku)
{
	FILE* plik;
	int max_dl = 35; //maksymalna d³ugoœæ imienia/nazwiska (w znakach)
	int i; //licznik pêtli
	int il_osob_w_pliku; //licznik wczytywania
	fopen_s(&plik, nazwa_pliku, "r");
	if (plik == NULL)
	{
		printf("Blad otwarcia pliku\n");
	}
	else
	{
		fscanf_s(plik, "%d", &il_osob_w_pliku);
		lista->le = lista->le + il_osob_w_pliku; //aktualizacja d³ugoœci listy przy wielokrotnym wywo³ywaniu funkcji
		for (i = 0; i < il_osob_w_pliku; i++)
		{
			Element* nowy_element;
			nowy_element = (Element*)malloc(sizeof(Element)); //alokacja pamiêcie dla struktury
			(nowy_element->imie) = malloc(max_dl * sizeof(char)); //alokacja pamiêcie dla ³añcucha znaków(imienia)
			fscanf_s(plik, "%s", nowy_element->imie, max_dl);
			(nowy_element->nazwisko) = malloc(max_dl * sizeof(char)); //alokacja pamiêcie dla ³añcucha znaków(nazwiska)
			fscanf_s(plik, "%s", nowy_element->nazwisko, max_dl);
			fscanf_s(plik, "%d", &nowy_element->wiek);
			nowy_element->nast = lista->lista;
			lista->lista = nowy_element;
		}
		fclose(plik);
	}
}
void wyswietl(Lista *lista)
{
	Lista* wyswietl;
	wyswietl = lista;
	while (wyswietl->lista != NULL)
	{
		printf("%s\n", wyswietl->lista->imie);
		printf("%s\n", wyswietl->lista->nazwisko);
		printf("%d\n", wyswietl->lista->wiek);
		printf("--------------------\n");
		wyswietl->lista = wyswietl->lista->nast;
	}
}
int main(void)
{
	Lista nowa_lista; //inicjacja struktury: Lista
	nowa_lista.lista = NULL; //inicjacja struktury: Lista
	nowa_lista.le = 0; //inicjacja struktury: Lista
	dodaj_element(&nowa_lista, "test.txt");
	wyswietl(&nowa_lista);
	system("Pause");
	return 0;
}