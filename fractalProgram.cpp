#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <ctime>

using namespace std;

#define LINES 250
#define COLUMNS 250

int result[400][500], p[5], xAxis, yAxis;

//verifica se existe pelo menos um ponto já preenchido ao redor do novo ponto criado
int checkPoint(int xAxis, int yAxis)
{
	int value = 0;

	if(result[xAxis+1][yAxis] == 1 || result[xAxis-1][yAxis] == 1 || result[xAxis][yAxis+1] == 1 || result[xAxis][yAxis-1] == 1)
		value = 1;

	return value;
}

//cria um novo ponto random se orientando com os pontos já criados
void nova()
{
	int c1 = 0, pos;
	do
	{
		pos = rand() % 4;

		switch(pos)
		{
			case 0:
				if(p[2] == 1)
					continue;
				xAxis = 1;
				yAxis = (rand() % COLUMNS) + 1;
				break;
			case 1:
				if(p[4] == 1)
					continue;
				yAxis = 1;
				xAxis = (rand() % LINES) + 1;
				break;
			case 2:
				if(p[1] == 1)
					continue;
				xAxis = LINES;
				yAxis = (rand() % COLUMNS) + 1;
				break;
			case 3:
				if(p[3] == 1)
					continue;
				yAxis = COLUMNS;
				xAxis = (rand() % LINES) + 1;
				break;

		}

		if(result[xAxis][yAxis] == 0)
		{
			result[xAxis][yAxis] = 1;
			c1 = 1;
		}
	} while(c1 != 1);
}

//Se movimento no "mapa" para adicionar um novo ponto em um lugar que não exista
void movimenta()
{
	int pp, ii, jj;

	result[xAxis][yAxis] = 0;

	pp = (rand() % 4) + 1;

	switch(pp)
	{
		case 1:
			yAxis = yAxis+1;
			break;
		case 2:
			yAxis = yAxis-1;
			break;
		case 3:
			xAxis = xAxis + 1;
			break;
		case 4:
			xAxis = xAxis - 1;
			break;
	}

	if(xAxis > LINES || xAxis < 1 || yAxis > COLUMNS || yAxis < 1)//Se chegou em um ponto fora do mapa cria uma nova partícula
		nova();
	else
	{
		result[xAxis][yAxis] = 1;
		if(checkPoint(xAxis,yAxis) == 1)
		{
			if(xAxis == LINES || xAxis == 1 || yAxis == COLUMNS || yAxis == 1)
			{
				if(xAxis == LINES)
					p[1] = 1;
				if(xAxis == 1)
					p[2] = 1;
				if(yAxis == COLUMNS)
					p[3] = 1;
				if(yAxis == 1)
					p[4] = 1;

				xAxis = 0;
				yAxis = 0;
			}
			else
				nova();
		}
	}
}

//salva os pontos PREENCHIDOS no "fractal_fisica.txt"
void salva()
{

	FILE *arq;

	arq = fopen("fractal_fisica.txt", "w+");
	for (int xAxis = 0; xAxis < LINES; ++xAxis)
	{
		for (int yAxis = 0; yAxis < COLUMNS; ++yAxis)
		{
			if(result[xAxis][yAxis] != 0)
				fprintf(arq, "%d %d %d\n", xAxis,yAxis,result[xAxis][yAxis]);
		}
	}
	fclose(arq);
}

int main()
{
	int control;

	srand(time(NULL));//seed do random

	control = 0;

	for (int xAxis = 1; xAxis <= 4; ++xAxis)
		p[xAxis] = 0;

	for (int xAxis = 1; xAxis < LINES; ++xAxis)
	{
		for (int yAxis = 1; yAxis < COLUMNS; ++yAxis)
			result[xAxis][yAxis] = 0;
	}

	result[LINES/2+1][COLUMNS/2+1] = 1; //particula do centro
	nova();

	while(control != 1)
	{
		if(p[1] == 1 && p[2] == 1 && p[3] == 1 && p[4] == 1)//Se chegar no ponto em que p[] está todo 1 os pontos possíveis foram preechidos
		{
			control = 1;
			salva();
		}
		else
			movimenta();
	}
	return 0;
}
