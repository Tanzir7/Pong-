#include <iostream>
#include <Windows.h>
#include <WinUser.h>

using namespace std;

char brick = 219;



void gotoxy(int x, int y) //dzieki tej funkcji ustalimy koordynaty dla punktu 
{
	if (x > -1 && y > -1)
	{
		COORD coord;                                                                             //ustawienie kordow
		coord.X = x;
		coord.Y = y;
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);                      //Ustawia pozycje kursora dla okreslonego punktu


	}

}

struct Player
{
	int x, y;
	int height;
	Player()
	{
		x = 1;
		y = 10;
		height = 3;
	}
	void Write()
	{
		for (int i = 0; i < height; i++)
		{
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x04);
			gotoxy(x, y+i );                                             //odwolanie do funkcji gotoxy / dodanie i okresla rozmiar gracza  i < height < 3
			cout << brick;
		}
	}
};

struct Ball
{
	int x, y, velx, vely;                                                                // ve;y velx zmienne kierunkowe dla pilki

	Ball()
	{
		x = 25;
		y = 10;
		velx = 1;
		vely = -1;
	}
	void Write()
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x06);
		gotoxy(x, y);
		cout << "o";
		
	}
	void Wall_col()                                                               //ustalenie granic dla pilki
	{
		//if (x < 1 || x> 50) velx = -velx;        
		if (y < 2 || y> 20) vely = -vely;
	}
	void Update()                                                                 // updatuje pozycje naszej pilki
	{
		x += velx;                                                                // Operator += dodaje wartoœæ po prawej stronie do wartoœci znajduj¹cej siê w danej zmiennej czyli: jest równowa¿ne x = x + y
		y += vely;
	}

	void Player_col(int x, int y, int height)
	{
		if (this->x > x + 1 || this->y > y + height || this->x + 1 < x || this->y + height < y)      // x naszej pilki musi byæ wiekszy niz x gracza + 1 czyli jego szerokosc / szerokosæ naszej pileczki nie moze byc mniejsza od x naszego gracza
		{

		}
		else
		{
			velx = -velx;
			vely = -vely;
		}
	}
};

void sterowanie()
{

	gotoxy(70, 10);
	cout << "GRACZ 1 \n";
	gotoxy(70, 12);
	"GORA - W \n DOL S";
}


void Score_write(int sc1, int sc2)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x04);
	gotoxy(23, 23);
	cout << "wynik " << sc1 << ":" << sc2;
}

void Granice()                // ustalenie ramki gry
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x01);
	for (int i = 0; i < 50 + 2; i++)
	{
		cout << "#";
	}
	for (int i = 0; i < 20 + 2; i++)
	{
		for (int j = 0; j < 52; j++)
		{
			if (j == 0)
				cout << "#";
			else
				cout << " ";
			if (j == 51)
				cout << "#";
		}
		cout << endl;
	}

	for (int i = 0; i < 50 + 3; i++)
	{
		cout << "#";
	}

}


int main()
{
	bool play = true;

	Player* player = new Player();
	Player* player2 = new Player();

	player2->x = 50;

	Ball* ball = new Ball();

	int score_1 = 0;
	int score_2 = 0;

	while (play)
	{
		system("cls");                                                                       //za kazdym razem ekran sie czysci co pozwala nie pokazywac x w tym samym miejscu i go "przesuwac"
		
		Granice();
		

		ball->Wall_col();
		ball->Player_col(player->x, player->y, player->height);
		ball->Player_col(player2->x, player2->y, player2->height);

		if (GetKeyState('W') < 0 && player->y >1)
		{
			player -> y--;
		}
		else if (GetKeyState('S') < 0 && player->y + player->height < 22)        //tu dodajemy wysokosc inaczej gracz bedzie sie zatrzymywac na 20 wierszu ale jego wysokosc bedzie wchodzic pod mape
		{
			player -> y++;
		}
		if (GetKeyState('X') < 0)
		{
			play = false;
		}

		if (GetKeyState('I') < 0 && player2->y > 1)
		{
			player2->y--;
		}
		else if (GetKeyState('K') < 0 && player2->y + player2->height < 22)        //tu dodajemy wysokosc inaczej gracz bedzie sie zatrzymywac na 20 wierszu ale jego wysokosc bedzie wchodzic pod mape
		{
			player2->y++;
		}
		
		if (ball->x < 0)                                                                      // zdobywanie puntków dla gracza 2
		{
			score_2++;
			ball->x =  20;
			ball->y = 10;
			Sleep(1000);
		}
		else if (ball-> x>50)                                                                 // zdobywanie puntków dla gracza 1
		{
			score_1++;
			ball->x = 20;                                                                     // restart pozycji pilki
			ball->y = 10;
			player->x = 1;
			player2->x = 50;
			player->y = 10;
			player2->y = 10;
			Sleep(1000);
		}

		 
		if (score_1 > 5 || score_2 > 5)
		{
			play = false;
		
		}
		

	ball->Update();

		player -> Write();
		player2-> Write();
		ball-> Write();
		Score_write(score_1, score_2);
		//sterowanie();
		Sleep(5);

	
	}

	if (score_1 > 5)
	{
		cout << "  gracz 1 wygrywa!" << endl;
	}
	if (score_2 > 5)
	{
		cout << "  gracz 2 wygrywa!" << endl;
	}
	

	system("pause");
	return 0;
}