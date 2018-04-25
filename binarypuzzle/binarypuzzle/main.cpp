#define _CRT_SECURE_NO_WARNINGS
#define SHIFT 2
#define SHIFTDOWN 2
#define SHIFTLEFT 32
#define TEXT_PLACE 1
#include<stdio.h>
#include"conio2.h"
#include "functions.h"


int main() {
	int zn = 0, x = 5, y = 5, attr = 7, back = 0, zero = 0, testy = 0;
	bool ifSaved = false;
	char txt[32];
	int pola = 0;

	int size = 12;
	gameSpace* plansza = new gameSpace(size);
	loadDefault(*plansza, size);
	settitle("Jakub Wronka 165156");
	do {
		textbackground(BLACK);
		textcolor(7);
		pola = dwuznaczne_pola(*plansza);
		plansza->showTable(SHIFTLEFT, SHIFTDOWN);
		gotoxy(TEXT_PLACE, 1);
		cputs("Puzzle binarne (a,b,c,d,e,f,g,h,i,j,n)");
		gotoxy(TEXT_PLACE, 2);
		cputs("Jakub Wronka, 165156");
		gotoxy(TEXT_PLACE, 3);
		cputs("esc = wyjscie");
		gotoxy(TEXT_PLACE, 4);
		cputs("strzalki = poruszanie");
		gotoxy(TEXT_PLACE, 5);
		cputs("n = nowa gra");
		gotoxy(TEXT_PLACE, 6);
		cputs("01 = wpisanie cyfry");
		gotoxy(TEXT_PLACE, 7);
		cputs("o = losowe wypelnienie");
		// wypisujemy na ekranie kod ostatnio naciœniêtego klawisza
		//if (zero) sprintf(txt, "kod klawisza: 0x00 0x%02x", zn);
		//else sprintf(txt, "kod klawisza: 0x%02x", zn);
		gotoxy(TEXT_PLACE, 8);
		cputs("p = prosta podpowiedz");
		gotoxy(TEXT_PLACE, 9);
		cputs("r = zmiana rozmiaru planszy");
		gotoxy(TEXT_PLACE, 10);
		cputs("k = czy mozna ukonczyc");
		gotoxy(TEXT_PLACE, 11);
		cputs("s = zapis planszy");
		gotoxy(TEXT_PLACE, 12);
		cputs("l = zaladowanie planszy");
		gotoxy(TEXT_PLACE, 13);
		sprintf(txt,"pozycja x: %d", x-1);
		cputs(txt);
		gotoxy(TEXT_PLACE, 14);
		sprintf(txt, "pozycja y: %d", y-1);
		cputs(txt);
		gotoxy(TEXT_PLACE, 15);
		sprintf(txt, "dwuznaczne pola: %d", pola);
		cputs(txt);
		gotoxy(x + SHIFTLEFT, y + SHIFTDOWN);
		textcolor(attr);
		textbackground(back);
		zero = 0;
		zn = getch();
		if (zn == 0x30) //0
		{

			Point* test = new Point(x - SHIFT, y - SHIFT, '0');
			insertInto(*plansza, *test);
			delete test;
		}
		else if (zn == 0x31)//1
		{
			Point* test = new Point(x - SHIFT, y - SHIFT, '1');
			insertInto(*plansza, *test);
			delete test;
		}
		else if ((zn == 0x6f) || (zn == 0x4f))//o lub O
		{
			randomStart(*plansza);
		}
		else if ((zn == 0x70) || (zn == 0x50))//p lub P
		{
			sprintf(txt, "Wcisnij 1 aby");
			gotoxy(TEXT_PLACE, 15);
			cputs(txt);
			sprintf(txt, "zobaczyc czy mozna");
			gotoxy(TEXT_PLACE, 16);
			cputs(txt);
			sprintf(txt, "wpisac 1, albo");
			gotoxy(TEXT_PLACE, 17);
			cputs(txt);
			sprintf(txt, "wcisnij 0 aby");
			gotoxy(TEXT_PLACE, 18);
			cputs(txt);
			sprintf(txt, "sprawdzic mozliwosc");
			gotoxy(TEXT_PLACE, 19);
			cputs(txt);
			sprintf(txt, "wpisania 0.");
			gotoxy(TEXT_PLACE, 20);
			cputs(txt);
			zn = getch();
			if (zn == 0x30)
			{
				Point* test0 = new Point(x - SHIFT, y - SHIFT, '0');
				littleHelp(*plansza, *test0);
				delete test0;
			}
			else if (zn == 0x31)
			{
				Point* test1 = new Point(x - SHIFT, y - SHIFT, '1');
				littleHelp(*plansza, *test1);
				delete test1;
			}
			else;

		}
		else if ((zn == 0x72)||(zn == 0x52)) //r lub R
		{
			clrscr();
			gotoxy(1, 1);
			cputs("Podaj dlugosc boku planszy (musi byc liczba parzysta)\n");
			size = getNumber();
			if (size % 2 == 0)
			{
				plansza->deleteTable(plansza->getTable());
				plansza->setN(size);
				plansza->createTable();
				plansza->fillTable(plansza->getTable());
			}

		}
		else if ((zn == 0x73) || (zn == 0x53)) //s
		{
			saveFile(*plansza);
			ifSaved = true;
		}
		else if ((zn == 0x6c) || (zn == 0x4c))//l
		{
			if (ifSaved)
			{
				loadFile(*plansza, size);
			}
			else
			{
				sprintf(txt, "Nie mozna odczytac");
				gotoxy(TEXT_PLACE, 15);
				cputs(txt);
				sprintf(txt, "Brak zapisanej planszy");
				gotoxy(TEXT_PLACE, 16);
				cputs(txt);
				getch();
			}
		}
		else if ((zn == 0x6e) || (zn == 0x4e))//n lub N
		{
			loadDefault(*plansza, size);
		}
		else if ((zn == 0x6b) || (zn == 0x4b))//k lub K
		{
			checkEnd(*plansza);
		}
		else if ((zn == 0x64) || (zn == 0x44))//d lub D
		{

		}
		else if (zn == 0) {
			zero = 1;		// je¿eli tak, to czytamy
			zn = getch();

			if (zn == 0x48)
			{
				if (y - 1 >= 0 + SHIFT)
				{
					y--;
				}
			}
			else if (zn == 0x50)
			{
				if (y + 1 < size + SHIFT)
				{
					y++;
				}
			}
			else if (zn == 0x4b)
			{
				if (x - 1 >= 0 + SHIFT)
				{
					x--;
				}
			}
			else if (zn == 0x4d)
			{
				if (x + 1 < size + SHIFT)
				{
					x++;
				}
			}
		}
	} while (zn != 0x1b);

	return 0;
}
