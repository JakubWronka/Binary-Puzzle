#include<stdio.h>
#include<malloc.h>
#include<string.h>
#include <stdlib.h>
#include <time.h>
#include "conio2.h"

class gameSpace //plansza do gry
{
private:
	int N; //rozmiar plansza
	char** table; //plansza

public:
	gameSpace(); //konstruktor bez parametrow
	gameSpace(int n); //kostruktor z rozmiarem
	void createTable(); //tworzenie pustej tabeli
	void fillTable(char**table);//wypelnienie tabeli kropkami
	char** getTable(); //zwracanie tabeli
	void showTable(int dx, int dy); //wyswietlanie tabeli z odpowiednim przesunieciem
	void setN(int n); //ustawianie rozmiaru
	int getN(); //zwracanie rozmiaru
	void deleteTable(char**table); //usuniecie tabeli(planszy)
	~gameSpace(); //destruktor
};

class Point //liczba który bêdzie mia³a byæ wpisana na nasz¹ planszê
{
private:
	int x, y; //wspolrzedne punktu
	char number; //znak (0 lub 1)
public:
	Point();//konstruktor bez parametrow
	Point(int x, int y, char symbol); //konstruktor z wspolrzednymi i symbolem
	void setRow(int row); //ustawianie rzêdu
	void setCol(int col); //ustawianie kolumny
	void setSymbol(char symbol); //ustawianie symbolu
	char getSymbol(); //zwarcanie symbolu
	int getRow(); //analogicznie
	int getCol();
	~Point(); // destruktor
};


bool firstRule(gameSpace &g, Point &p); //pierwsza zasada - wiêcej ni¿ 2 te same cyfry obok siebie
bool checkUp(gameSpace &g, Point &p); //sprawdzanie pierwszej zasady w górê
bool checkDown(gameSpace& g, Point &p); //analogicznie
bool checkLeft(gameSpace &g, Point &p);
bool checkRight(gameSpace &g, Point &p);


bool secondRule(gameSpace &g, Point &p); //druga zasada - taka sama liczba zer i jedynek
bool secondRuleRows(gameSpace &g, Point &p);
bool secondRuleCols(gameSpace &g, Point &p);

bool thirdRule(gameSpace &g, Point &p); // trzecia zasada - ró¿ne rzêdy i kolumny
bool thirdCheckDown(gameSpace& g, Point &p);
bool thirdCheckAcross(gameSpace& g, Point& p);

void insertInto(gameSpace &g, Point &p); //wpisywanie na planszê
void testInsert(gameSpace &g, Point &p); //wpisywanie testowe, potrzebne do 3 zasady
void deleteFrom(gameSpace &g, Point &p); // usuwanie po testowym wpisaniu
void randomStart(gameSpace &g); //losowe wypelnianie
bool ifEmpty(gameSpace &g, Point &p); //sprawdzanie czy pole jest puste
bool canItBePutIn(gameSpace &g, Point &p); //sprawdzanie czy cyfra moze byc umieszczona w polu
int whichRule(gameSpace &g, Point &p);// zwracanie nr zasady której nie spe³nia punkt który chcemy wpisaæ
void littleHelp(gameSpace &g, Point &p); //prosta podpowiedŸ
int getNumber(); //pobieranie liczby do stworzenia nowej planszy
void saveFile(gameSpace& g); //zapis
void loadFile(gameSpace& g, int& size); //odczyt
void loadDefault(gameSpace& g, int& size); //nowa gra, domyslna
void checkEnd(gameSpace& g); //sprawdzenie konca
int dwuznaczne_pola(gameSpace& g);