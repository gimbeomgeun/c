#include <stdio.h>
#include <conio.h>
#include <time.h>
#include <windows.h>
#include <stdlib.h>

#define UP 72
#define DOWN 80
#define LEFT 75
#define RIGHT 77
#define LEN_PAN 3
#define AREA_ROW 6
#define AREA_COL 10

int area[AREA_ROW][AREA_COL+2];
int pan[LEN_PAN] = { 2,2,2 };

int set_area();
void print_area();
void init(int px);
int input(int px);
int game(int bx, int by, int px, int bsx, int bsy);
int is_gameover();


int set_area()
{
	for (int i = 0; i < AREA_ROW; i++)
	{
		for (int j = 1; j < AREA_COL+1; j++)
		{
			if (i < 2)
				area[i][j] = 1;
			else
				area[i][j] = 0;
		}
	}
	return game(5, 3,1, -1, -1);
}

void print_area()
{
	system("cls");
	for (int i = 0; i < AREA_ROW; i++)
	{
		for (int j = 1; j < AREA_COL+1; j++)
		{
			if (area[i][j] == 1)
				printf("¡á");
			else if (area[i][j] == 0)
				printf("¡à");
			else if (area[i][j] == 2)
				printf("¡ª");
			else if (area[i][j] == 3)
				printf("¡Ü");
		}
		printf("\n");
	}
}

void init(int px)
{
	for (int i = 0; i < LEN_PAN; i++)
	{
		area[5][px + i] = 0;
	}
}

void put_pan(int px)
{
	for (int i = 0; i < LEN_PAN; i++)
	{
		area[5][px + i] = 2;
	}
}

int input(int px)
{
	char c;

	clock_t s_time, e_time;
	s_time = clock();
	e_time = clock();
	while (e_time - s_time < 200)
	{
		e_time = clock();
		if (_kbhit()) {
			c = _getch();
			if (c == -32) {
				c = _getch();
				switch (c) {
				case LEFT:
					if (px > 1)
					{
						init(px);
						px -= 1;
						put_pan(px);
						print_area();
					}
					break;
				case RIGHT:
					if (px < 8)
					{
						init(px);
						px += 1;
						put_pan(px);
						print_area();
					}
					break;
				}
			}
		}
	}
	return px;
}

int game(int bx, int by, int px, int bsx, int bsy)
{
	srand(time(NULL));
	area[by][bx] = 3;
	put_pan(px);
	print_area();
	px = input(px);
	area[by][bx] = 0;

	if (area[by + 1][bx] == 2)
	{
		bsy = -bsy;
		if (rand() % 2)
		{
			bsx = rand() % 2;
		}
		else
		{
			bsx = -(rand() % 2);
		}
	}

	if (bx+bsx<1||bx + bsx >= 10 || by + bsy < 0)
	{
		if (bx + bsx >= 10)
		{
			bx = 10;
			bsx = -bsx;
		}
		else if(bx+bsx<1)
		{
			bx = 1;
			bsx = -bsx;
		}
		else
		{
			by = 0;
			bsy = -bsy;
		}
	}

	if(!area[by+bsy][bx+bsx])
		bx += bsx, by += bsy;
	else if(area[by-1][bx]==1)
	{
		area[by -1][bx] = 0;
		bsy = -bsy;
	}
	else if (area[by -1][bx + bsx] == 1)
	{
		if (bsx > 0)
			area[by - 1][bx + 1] = 0;
		else
			area[by - 1][bx - 1] = 0;
	}
	else if (area[by + bsy][bx + bsx] == 1)
	{
		area[by + bsy][bx + bsx] = 0;
	}
	if (is_gameover())
		return set_area();
	if (by == 6)
	{
		return 0;
	}
	return game(bx, by, px,bsx,bsy);
}

int is_gameover()
{
	for (int i = 0; i < 2; i++)
	{
		for (int j = 1; j < AREA_COL+1; j++)
		{
			if (area[i][j] == 1)
			{
				return 0;
			}
		}
	}
	return 1;
}


int main()
{
	set_area();
}