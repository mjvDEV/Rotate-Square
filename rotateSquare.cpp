////////////////////////////////////////////////////////////////////
// Application: rotateSquare
//		Provides sample code for dynamic 2D array squares:
//			- Allocate memory
//			- Deallocate memory
//			- Print to console
//			- Initialize with random values
//			- Rotate
// *NOTE: outside of MVS, remove line: #include "stdafx.h"
////////////////////////////////////////////////////////////////////

#include <iostream>
#include <cstdlib>
#include <time.h>

using namespace std;

////////////////////////////////////////////////////////////////////
// Algorithm printGrid(g, n)
//		Prints a dyanamic grid to the console.
//
// Pre: g :: refToRefToChar, contains valid references in x and y directions.
//		n :: integer, the dimensions of the desired square array.
// Post: prints g to the console
// Return: nothing
////////////////////////////////////////////////////////////////////

void printGrid(int** g, int n)
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			cout << g[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;
}

////////////////////////////////////////////////////////////////////
// Algorithm initGrid(g, n)
//		Initializes a dynamic character grid to '*'
//
// Pre: g :: refToRefToChar, contains valid references in x and y directions.
//		n :: integer, the dimensions of the desired square array.
// Post: sets all values in g to '*'
// Return: nothing
////////////////////////////////////////////////////////////////////

void initGrid(int** g, int n)
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			g[i][j] = rand() % 9 + 1;
		}
	}
}

////////////////////////////////////////////////////////////////////
// Algorithm makeGrid(n)
//		Allocates a 2D character array on the heap.
//
// Pre: n :: integer, the dimensions of the desired square array.
// Post: Allocates memory for the 2D array.
// Return: a refToRefToChar, which points to the array.
////////////////////////////////////////////////////////////////////

int** makeGrid(int n)
{
	int** g = new int*[n];
	for (int i = 0; i < n; i++)
	{
		g[i] = new int[n];
	}
	return g;
}

////////////////////////////////////////////////////////////////////
// Algorithm destroyGrid(g, n)
//		Deallocates a dynamic 2D array from the heap.
//
// Pre: g :: refToRefToChar, contains valid references in x and y directions.
//		n :: integer, the dimensions of the desired square array.
// Post: Deallocates g
// Return: nothing
////////////////////////////////////////////////////////////////////

void destroyGrid(int** g, int n)
{
	for (int i = 0; i < n; i++)
	{
		delete[] g[i];
	}
	delete[] g;
}

////////////////////////////////////////////////////////////////////
// Algorithm rotateSquare(large, N, dir)
//		rotates any N size dynamic square large in direction dir once.
//
// Pre: large :: refToRefTo int, contains valid references.
//		N :: integer, the dimensions of square formed by large.
//		dir :: bool, true for clockwise, false for counterclockwise.
// Post: Rotates large in desired direction.
// Return: nothing
////////////////////////////////////////////////////////////////////

void rotateSquare(int** large, int N, bool dir)
{
	int temp;

	if (dir)
	{
		for (int b = 0; b < N / 2; b++)
		{
			for (int a = 1; a < (N - (b * 2)); a++)
			{
				temp = large[N - a - b][b];
				large[N - a - b][b] = large[N - 1 - b][N - a - b];
				large[N - 1 - b][N - a - b] = large[b + a - 1][N - 1 - b];
				large[b + a - 1][N - 1 - b] = large[b][b + a - 1];
				large[b][b + a - 1] = temp;
			}
		}
	}
	else
	{
		for (int b = 0; b < N / 2; b++)
		{
			for (int a = 1; a < (N - (b * 2)); a++)
			{
				temp = large[b][b + a - 1];
				large[b][b + a - 1] = large[b + a - 1][N - 1 - b];
				large[b + a - 1][N - 1 - b] = large[N - 1 - b][N - a - b];
				large[N - 1 - b][N - a - b] = large[N - a - b][b];
				large[N - a - b][b] = temp;
			}
		}
	}
}

////////////////////////////////////////////////////////////////////
// Algorithm main()
//		Provides test code for variableGrid operations
//
// Pre: nothing
// Post: nothing
// Return: 0 
////////////////////////////////////////////////////////////////////

int main(void)
{
	srand(time(NULL));
	int N;
	int** square;
	char test = 'y', dir;
	do
	{
		cout << "What size square would you like? ";
		cin >> N;
		cout << " w :: rotate clocksise" << endl
			<< " c :: rotate counterclockwise" << endl
			<< "Which direction would you like to rotate? ";
		cin >> dir;

		square = makeGrid(N);
		initGrid(square, N);
		cout << "Here is your square:" << endl << endl;
		printGrid(square, N);

		switch (dir)
		{
		case 'w':
			rotateSquare(square, N, true);
			cout << "Here is your square, rotated: " << endl << endl;
			printGrid(square, N);
			break;
		case 'c':
			rotateSquare(square, N, false);
			cout << "Here is your square, rotated: " << endl << endl;
			printGrid(square, N);
			break;
		default:
			cout << "Invalid selection" << endl << endl;
		}

		destroyGrid(square, N);
		cout << "continue testing? (y/n): ";
		cin >> test;
	} while (test == 'y');
	return 0;
}

