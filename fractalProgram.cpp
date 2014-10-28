#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <ctime>

using namespace std;

#define LINES 400
#define COLUMNS 400

int matrixWithThePointToPlot[500][500], neiborhoodPoints[5], xAxis, yAxis;

//verifica se existe pelo menos um ponto já preenchido ao redor do novo ponto criado
int checkExistingPoint(int xAxis, int yAxis)
{
	int value = 0;

	if(matrixWithThePointToPlot[xAxis+1][yAxis] == 1 || matrixWithThePointToPlot[xAxis-1][yAxis] == 1 || matrixWithThePointToPlot[xAxis][yAxis+1] == 1 || matrixWithThePointToPlot[xAxis][yAxis-1] == 1)
		value = 1;

	return value;
}

//cria um novo ponto random se orientando com os pontos já criados
void createANewRandowPoint()
{
	int auxiliaryVarible = 0, randomPointPosition;

	do
	{
		randomPointPosition = rand() % 4;

		switch(randomPointPosition)
		{
			case 0:
				if(neiborhoodPoints[2] == 1)
					continue;
				xAxis = 1;
				yAxis = (rand() % COLUMNS) + 1;
				break;
			case 1:
				if(neiborhoodPoints[4] == 1)
					continue;
				yAxis = 1;
				xAxis = (rand() % LINES) + 1;
				break;
			case 2:
				if(neiborhoodPoints[1] == 1)
					continue;
				xAxis = LINES;
				yAxis = (rand() % COLUMNS) + 1;
				break;
			case 3:
				if(neiborhoodPoints[3] == 1)
					continue;
				yAxis = COLUMNS;
				xAxis = (rand() % LINES) + 1;
				break;
		}

		if(matrixWithThePointToPlot[xAxis][yAxis] == 0)
		{
			matrixWithThePointToPlot[xAxis][yAxis] = 1;
			auxiliaryVarible = 1;
		}
	} while(auxiliaryVarible != 1);
}

//Se movimento no "mapa" para adicionar um novo ponto em um lugar que não exista
void moveToAddANewPoint()
{
	int randomPointPosition;

	matrixWithThePointToPlot[xAxis][yAxis] = 0;

	randomPointPosition = (rand() % 4) + 1;

	switch(randomPointPosition)
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

	if(xAxis > LINES || xAxis < 1 || yAxis > COLUMNS || yAxis < 1)//Se chegou em um ponto fora do mapa cria uma createANewRandowPoint partícula
		createANewRandowPoint();
	else
	{
		matrixWithThePointToPlot[xAxis][yAxis] = 1;

		if(checkExistingPoint(xAxis,yAxis) == 1)
		{
			if(xAxis == LINES || xAxis == 1 || yAxis == COLUMNS || yAxis == 1)
			{
				if(xAxis == LINES)
					neiborhoodPoints[1] = 1;
				if(xAxis == 1)
					neiborhoodPoints[2] = 1;
				if(yAxis == COLUMNS)
					neiborhoodPoints[3] = 1;
				if(yAxis == 1)
					neiborhoodPoints[4] = 1;

				xAxis = 0;
				yAxis = 0;
			}
			else
				createANewRandowPoint();
		}
	}
}

//salva os pontos (x,y) preechidos no "fractalPoints.txt" para plotar
void savePointsToPlot()
{

	FILE *outFile;

	outFile = fopen("fractalPoints.txt", "w+");

	for (int xAxis = 0; xAxis < LINES; ++xAxis)
	{
		for (int yAxis = 0; yAxis < COLUMNS; ++yAxis)
		{
			if(matrixWithThePointToPlot[xAxis][yAxis] != 0)
				fprintf(outFile, "%d %d \n", xAxis,yAxis);
		}
	}
	fclose(outFile);
}

int main()
{
	int auxiliaryVarible=0;

	srand(time(NULL));

	for (int xAxis = 1; xAxis <= 4; xAxis++)
		neiborhoodPoints[xAxis] = 0;

	for (int xAxis = 1; xAxis < LINES; xAxis++)
	{
		for (int yAxis = 1; yAxis < COLUMNS; yAxis++)
			matrixWithThePointToPlot[xAxis][yAxis] = 0;
	}

	matrixWithThePointToPlot[LINES/2+1][COLUMNS/2+1] = 1; //particula do centro

	createANewRandowPoint();

	while(auxiliaryVarible != 1)
	{
		//Se chegar no ponto em que todos os seus vizinhos estam todo preechidos
		if(neiborhoodPoints[1] == 1 && neiborhoodPoints[2] == 1 && neiborhoodPoints[3] == 1 && neiborhoodPoints[4] == 1)
		{
			auxiliaryVarible = 1;
			savePointsToPlot();
		}
		else
			moveToAddANewPoint();
	}

	return 0;
}
