#define _CRT_SECURE_NO_WARNINGS
#include "functions.h"
#define SHIFT 2
#define SHIFTDOWN 2
#define SHIFTLEFT 32
#define TEXT_PLACE 1
#define ENTER 0x0d
//metody do planszy
char messages[80];

gameSpace::gameSpace()
{

}
gameSpace::gameSpace(int n)
{
	N = n;
	if ((N != 0) && (N % 2 == 0))
	{
		createTable();
		fillTable(table);
	}

}
void gameSpace::createTable()
{
	table = (char**)malloc(N * sizeof(char*));
	for (int i = 0; i < N; i++)
	{
		table[i] = (char*)malloc(N * sizeof(char));
	}
}

void gameSpace::fillTable(char** table)
{
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			table[j][i] = '.';
		}
	}
}

void gameSpace::setN(int n)
{
	N = n;	
}

int gameSpace::getN()
{
	return N;
}

char** gameSpace::getTable()
{
	return table;
}

void gameSpace::showTable(int dx, int dy)
{
	clrscr();
	for (int i = 0; i < N; i++)
	{
		gotoxy(2+dx-1, 2 + i+dy-1);
		putch('|');
		gotoxy(2 + dx, 2 + i + dy);
		for (int j = 0; j < N; j++)
		{
			putch(table[j][i]);
		}
		putch('|');
	}
	gotoxy(2 + dx -1, 2 + dy + N-1);
	putch('|');
	gotoxy(2 + dx - 1, 2 + dy - 1);
	for (int i = 0; i < N+2; i++)
	{
		putch('-');
	}
	gotoxy(2 + dx -1, 2 + dy + N);
	for (int i = 0; i < N+2; i++)
	{
		putch('-');
	}

}

void gameSpace::deleteTable(char** table)
{
	for (int i = 0; i < N; i++)
	{
		free(table[i]);
	}
	free(table);
}

gameSpace::~gameSpace()
{

}

//metody do wpisywanej liczby

Point::Point()
{
	x = 0;
	y = 0;
	number = '.';
}

Point::Point(int x1, int y1, char symbol)
{
	x = x1;
	y = y1;
	number = symbol;
}

int Point::getRow()
{
	return x;
}
int Point::getCol()
{
	return y;
}
void Point::setRow(int row)
{
	x = row;
}
void Point::setCol(int col)
{
	y = col;
}

char Point::getSymbol()
{
	return number;
}

void Point::setSymbol(char symbol)
{
	number = symbol;
}

Point::~Point()
{

}

//wype³nianie

bool ifEmpty(gameSpace &g, Point& p)
{
	if ((g.getTable()[p.getRow()][p.getCol()] == '.'))
		return true;
	else return false;
}

bool canItBePutIn(gameSpace &g, Point &p)
{
	if ((firstRule(g, p)) && (secondRule(g, p)) && (thirdRule(g, p)))
	{
		return true;
	}
	else return false;

}


int whichRule(gameSpace &g, Point &p)
{
	if (!firstRule(g, p))
	{
		return 1;
	}
	else if (!secondRule(g, p))
	{
		return 2;
	}
	else if (!thirdRule(g, p))
	{
		return 3;
	}
}


void insertInto(gameSpace &g, Point& p)
{
	int rule_num = 0;
	bool empty = true;
	bool put = true;
	empty = ifEmpty(g, p);
	put = canItBePutIn(g, p);
	if (empty && put)
	{
		g.getTable()[p.getRow()][p.getCol()] = p.getSymbol();
	}
	else if (!put)
	{
		rule_num = whichRule(g, p);
		gotoxy(TEXT_PLACE, 15);
		sprintf(messages, "Nie mozna wpisac.");
		cputs(messages);
		gotoxy(TEXT_PLACE, 16);
		sprintf(messages, "Niezgodnosc z zasada nr %d.", rule_num);
		cputs(messages);
		gotoxy(TEXT_PLACE, 17);
		sprintf(messages, "Wcisnij enter");
		cputs(messages);
		gotoxy(TEXT_PLACE, 18);
		sprintf(messages, "aby kontynuowac");
		cputs(messages);
		getch();
	}
	else if (!empty)
	{
		gotoxy(TEXT_PLACE, 15);
		sprintf(messages, "Nie mozna wpisac.");
		cputs(messages);
		gotoxy(TEXT_PLACE, 16);
		sprintf(messages, "Pole niemodyfikowalne");
		cputs(messages);
		gotoxy(TEXT_PLACE, 17);
		sprintf(messages, "Wcisnij enter");
		cputs(messages);
		gotoxy(TEXT_PLACE, 18);
		sprintf(messages, "aby kontynuowac");
		cputs(messages);
		getch();
	}
	
	
}

void randomStart(gameSpace &g)
{
	srand(time(NULL));
	int x, y;
	int binary_number;
	for (int i = 0; i < g.getN(); i++)
	{
		x = rand() % g.getN();
		y = rand() % g.getN();
		binary_number = rand() % 2;
		if (binary_number == 0)
		{
			Point* newPoint = new Point(x, y, '0');
			insertInto(g, *newPoint);
			delete newPoint;
		}
		if (binary_number == 1)
		{
			Point *newPoint = new Point(x, y, '1');
			insertInto(g, *newPoint);
			delete newPoint;
		}

	}
}

void testInsert(gameSpace &g, Point &p)
{
	g.getTable()[p.getRow()][p.getCol()] = p.getSymbol();
}

void littleHelp(gameSpace &g, Point &p)
{
	if (!ifEmpty(g, p))
	{
		gotoxy(TEXT_PLACE, 15);
		sprintf(messages, "Nie mozna wpisac.");
		cputs(messages);
		gotoxy(TEXT_PLACE, 16);
		sprintf(messages, "Pole niemodyfikowalne");
		cputs(messages);
		gotoxy(TEXT_PLACE, 17);
		sprintf(messages, "Wcisnij enter");
		cputs(messages);
		gotoxy(TEXT_PLACE, 18);
		sprintf(messages, "aby kontynuowac");
		cputs(messages);
		getch();
	}
	else
	{
		testInsert(g, p);
		if (!canItBePutIn(g, p))
		{
			int rule_nr = whichRule(g, p);
			gotoxy(TEXT_PLACE, 15);
			sprintf(messages, "Nie mozna wpisac %c.", p.getSymbol());
			cputs(messages);
			gotoxy(TEXT_PLACE, 16);
			sprintf(messages, "Niezgodnosc z zasada nr %d.", rule_nr);
			cputs(messages);
			gotoxy(TEXT_PLACE, 17);
			sprintf(messages, "Wcisnij enter");
			cputs(messages);
			gotoxy(TEXT_PLACE, 18);
			sprintf(messages, "aby kontynuowac");
			cputs(messages);
			getch();
		}
		else
		{
			gotoxy(TEXT_PLACE, 15);
			sprintf(messages, "Mozna wpisac %c.", p.getSymbol());
			cputs(messages);
			getch();
		}
		deleteFrom(g, p);
	}
}



int getNumber()
{
	char liczba[3];
	int i = 0, rozmiar = 0;
	char cyfra = getch();
	while (cyfra != ENTER)
	{
		putch(cyfra);
		liczba[i] = cyfra;
		i++;
		cyfra = getch();
	}
	rozmiar = atoi(liczba);
	return rozmiar;
}

//pierwsza zasada

bool checkUp(gameSpace &g, Point &p)
{
	if (p.getRow() - 2 >= 0)
	{
		if (g.getTable()[p.getRow() - 1][p.getCol()] == p.getSymbol())
		{
			if (g.getTable()[p.getRow() - 2][p.getCol()] == p.getSymbol())
			{
				return false;
			}
			else if (p.getRow() + 1 < g.getN())
			{
				if (g.getTable()[p.getRow() + 1][p.getCol()] == p.getSymbol())
				{
					return false;
				}
				else return true;

			}
		}
		else return true;
	}
	else return true;
}

bool checkDown(gameSpace& g, Point& p)
{
	if (p.getRow() + 2 < g.getN())
	{
		if (g.getTable()[p.getRow() + 1][p.getCol()] == p.getSymbol())
		{
			if (g.getTable()[p.getRow() + 2][p.getCol()] == p.getSymbol())
			{
				return false;
			}
			else if (p.getRow() - 1 >= 0)
			{
				if (g.getTable()[p.getRow() - 1][p.getCol()] == p.getSymbol())
				{
					return false;
				}
				else return true;
				
			}
		}
		else return true;
	}
	else return true;
}

bool checkLeft(gameSpace &g, Point &p)
{
	if (p.getCol() - 2 >= 0)
	{
		if (g.getTable()[p.getRow()][p.getCol()-1] == p.getSymbol())
		{
			if (g.getTable()[p.getRow()][p.getCol()-2] == p.getSymbol())
			{
				return false;
			}
			else if (p.getCol() + 1 < g.getN())
			{
				if (g.getTable()[p.getRow()][p.getCol()+1] == p.getSymbol())
				{
					return false;
				}
				else return true;

			}
		}
		else return true;
	}
	else return true;
}

bool checkRight(gameSpace &g, Point &p)
{
	if (p.getCol() + 2 < g.getN())
	{
		if (g.getTable()[p.getRow()][p.getCol()+1] == p.getSymbol())
		{
			if (g.getTable()[p.getRow()][p.getCol()+2] == p.getSymbol())
			{
				return false;
			}
			else if (p.getCol() - 1 >= 0)
			{
				if (g.getTable()[p.getRow()][p.getCol()-1] == p.getSymbol())
				{
					return false;
				}
				else return true;

			}
		}
		else return true;
	}
	else return true;
}

bool firstRule(gameSpace &g, Point &p)
{
	if ((!checkUp(g, p)) || (!checkDown(g, p)) || (!checkLeft(g, p)) || (!checkRight(g, p)))
	{
		return false;
	}
	else return true;
}

//druga zasada


bool secondRuleCols(gameSpace &g, Point &p)
{
	int zera = 0, jedynki = 0;
	for (int i = 0; i < g.getN(); i++)
	{
		if (g.getTable()[i][p.getCol()] == '0')
			zera++;
		if (g.getTable()[i][p.getCol()] == '1')
			jedynki++;
	}
	if (p.getSymbol() == '0')
	{
		if (zera < g.getN() / 2)
			return true;
		else return false;
	}
	if (p.getSymbol() == '1')
	{
		if (jedynki < g.getN() / 2)
			return true;
		else return false;
	}
}

bool secondRuleRows(gameSpace &g, Point &p)
{
	int zera = 0, jedynki = 0;
	for (int i = 0; i < g.getN(); i++)
	{
		if (g.getTable()[p.getRow()][i] == '0')
			zera++;
		if (g.getTable()[p.getRow()][i] == '1')
			jedynki++;
	}
	if (p.getSymbol() == '0')
	{
		if (zera < g.getN() / 2)
			return true;
		else return false;
	}
	if (p.getSymbol() == '1')
	{
		if (jedynki < g.getN() / 2)
			return true;
		else return false;
	}
}

bool secondRule(gameSpace& g, Point& p)
{
	if ((!secondRuleCols(g,p) || (!secondRuleRows(g, p))))
		return false;
	else return true;
}

//trzecia zasada

bool thirdCheckDown(gameSpace &g, Point &p)
{
	testInsert(g, p);
	int test = 0, test2 = 0;
	for (int i = 0; i < g.getN(); i++)
	{
		if (g.getTable()[i][p.getCol()] == '.')
			test++;
	}
	if (test == 0)
	{
		for (int i = 0; i < g.getN(); i++)
		{
			test2 = 0;
			for (int j = 0; j < g.getN(); j++)
			{
				if (p.getCol() != i)
				{
					if (g.getTable()[j][i] == g.getTable()[j][p.getCol()])
						test2++;
				}
			}
			if (test2 == g.getN())
			{
				deleteFrom(g, p);
				return false;
			}
		}
		
	}
	deleteFrom(g, p);
	return true;
}

bool thirdCheckAcross(gameSpace &g, Point& p)
{

	testInsert(g, p);
	int test = 0, test2 = 0;
	for (int i = 0; i < g.getN(); i++)
	{
		if (g.getTable()[p.getRow()][i] == '.')
			test++;
	}
	if (test == 0)
	{
		for (int i = 0; i < g.getN(); i++)
		{
			for (int j = 0; j < g.getN(); j++)
			{
				if (p.getRow() != i)
				{
					if (g.getTable()[i][j] == g.getTable()[p.getCol()][j])
						test2++;
				}
			}
			if (test2 == g.getN())
			{
				deleteFrom(g, p);
				return false;
			}
		}
		
	}
	deleteFrom(g, p);
	return true;
}

bool thirdRule(gameSpace& g, Point& p)
{
	if (ifEmpty(g, p))
	{
		if ((!thirdCheckAcross(g, p)) || (!thirdCheckDown(g, p)))
			return false;
		else return true;
	}
	else return true;
}

void deleteFrom(gameSpace& g, Point &p)
{
	g.getTable()[p.getRow()][p.getCol()] = '.';
}

void saveFile(gameSpace &g)
{
	char output_size[3];
	int size = g.getN();
	_itoa(size, output_size, 10);

	FILE* f = fopen("plansza.txt", "w+" );
	for (int i = 0; i < 3; i++)
	{
		fputc(output_size[i], f);
	}
	fputc('\n', f);

	for (int i = 0; i < g.getN(); i++)
	{
		for (int j = 0; j < g.getN(); j++)
		{
			fputc(g.getTable()[j][i], f);
		}
	}

	fclose(f);
	gotoxy(TEXT_PLACE, 15);
	sprintf(messages, "Zapis udany");
	cputs(messages);
	gotoxy(TEXT_PLACE, 16);
	sprintf(messages, "Wcisnij dowolny klawisz");
	cputs(messages);
	gotoxy(TEXT_PLACE, 17);
	sprintf(messages, "aby kontynuowac");
	cputs(messages);
	getch();
}

void loadFile(gameSpace& g, int& size)
{
	char input_size[4];
	FILE* f = fopen("plansza.txt", "r");
	fgets(input_size, 4, f);
	size = atoi(input_size);
	g.deleteTable(g.getTable());
	g.setN(size);
	g.createTable();
	fgetc(f);
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			g.getTable()[j][i] = fgetc(f);
		}
	}
	fclose(f);
}

void loadDefault(gameSpace& g, int& size)
{
	char input_size[4];
	FILE* f = fopen("planszaDefault.txt", "r");
	fgets(input_size, 4, f);
	size = atoi(input_size);
	g.deleteTable(g.getTable());
	g.setN(size);
	g.createTable();
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			g.getTable()[j][i] = fgetc(f);
		}
	}
	fclose(f);
}

void checkEnd(gameSpace& g)
{
	for (int i = 0; i < g.getN(); i++)
	{
		for (int j = 0; j < g.getN(); j++)
		{
			Point* p0 = new Point(j, i, '0');
			Point* p1 = new Point(j, i, '1');
			if (ifEmpty(g, *p0) && ifEmpty(g, *p1) && !canItBePutIn(g, *p0) && !canItBePutIn(g, *p1))
			{
				g.getTable()[j][i] = 'x';
			}
			else;
			
		}
	}
	g.showTable(SHIFTLEFT, SHIFTDOWN);
	getch();
	for (int i = 0; i < g.getN(); i++)
	{
		for (int j = 0; j < g.getN(); j++)
		{
			if (g.getTable()[j][i] == 'x')
			{
				g.getTable()[j][i] = '.';
			}
		}
	}

}

int dwuznaczne_pola(gameSpace& g)
{
	int pola = 0;
	for (int i = 0; i < g.getN(); i++)
	{
		for (int j = 0; j < g.getN(); j++)
		{
			Point* p0 = new Point(j, i, '0');
			Point* p1 = new Point(j, i, '1');
			if ((canItBePutIn(g, *p0) && (canItBePutIn(g, *p1))))
			{
				pola++;
			}
			delete p0;
			delete p1;
		}
	}
	return pola;
}