#include <stdio.h>      // rpintf, scanf
#include <stdint.h>     // int32_t
#include <stdlib.h>     // rand()
#include <time.h>       // initialisierung des Zufallsgenerators
#include <stdbool.h>	// boolean
#include <math.h>

#define MinRowCount 2
#define MaxRowCount 6
#define MinElements 1
#define MaxElements 6

int32_t ReadNumberInRange(int32_t minRange, int32_t maxRange);
bool ReadYesOrNoInput(char* askText);
void GeneratePlayground(int32_t* playground);
void ManuallyCreatePlayground(int32_t* playground);
void ShowPlayground(int32_t* playground);
void UsersTurn(int32_t* playground);
void RandomComputerTurn(int32_t* playground);
bool IsWinner(int32_t* playground);
void ShowWinner(bool playersTurn);
void SmartComputerTurn(int32_t* playgorund);
void PlayGame();


int main() {
	srand(time(0));
	printf("Willkommen zum NIM-Spiel.\n\n");
	while (ReadYesOrNoInput("M\x94\chten sie eine Runde NIM spielen? y/n\n"))
	{
		PlayGame();
	}
	printf("\nBis zum n\x84\chsten Mal!");
}

int32_t ReadNumberInRange(int32_t minRange, int32_t maxRange) {
	int32_t number = 0;
	while (true)
	{
		scanf_s("%i", &number);
		while (getchar() != '\n'); // this is needed to clear the buffer!
		if (number >= minRange && number <= maxRange)
			return number;
		else
			printf("Zahl zu gross oder zu klein. Bitte erneut versuchen (Min: %i, Max: %i).\n", minRange, maxRange);
	} 
}

/// <summary>
/// Shows a message to ask and reads input. 
/// </summary>
/// <param name="askText">Text to show to the user (usually a question)</param>
/// <returns>true if input is 'y' and false if input is 'n'</returns>
bool ReadYesOrNoInput(char* askText)
{
	char input = '\0';
	printf(askText);
	while (input != 'y' && input != 'n')
	{
		scanf_s("%c", &input, 1);
		while (getchar() != '\n');
		if (input == 'y')
			return true;
		else if (input == 'n')
			return false;
		else
			printf("Ung\x81\ltige Eingabe. Bitte erneut versuchen.\n");
	}
}

/// <summary>
/// The Function which runs the game
/// </summary>
void PlayGame()
{
	bool playersTurn = false;
	int32_t playground[MaxRowCount];
	for (int i = 0; i < MaxRowCount; i++)
		playground[i] = -1;

	if (ReadYesOrNoInput("\nSoll das Spiel automatisch generiert werden? y/n\n"))
		GeneratePlayground(playground);
	else
		ManuallyCreatePlayground(playground);
	do
	{
		playersTurn = !playersTurn;
		if (playersTurn == 1)
		{
			ShowPlayground(playground);
			UsersTurn(playground);
		}
		else
			SmartComputerTurn(playground);
	} while (!IsWinner(playground));
	ShowWinner(playersTurn);
}

/// <summary>
/// Creates a random playground
/// </summary>
/// <param name="playground">Pointer to the playground array</param>
void GeneratePlayground(int32_t* playground)
{
	int rowCount = rand() % MaxRowCount + MinRowCount;
	for (uint32_t i = 0; i < rowCount; i++)
		playground[i] = rand() % MaxElements + 1;
}

/// <summary>
/// Creates playground from users Input
/// </summary>
/// <param name="playground">Pointer to the playground array</param>
void ManuallyCreatePlayground(int32_t* playground)
{
	printf("\nWie viele Reihen soll das Spiel haben?\n");
	int rowCount = ReadNumberInRange(MinRowCount, MaxRowCount);
	for (uint32_t i = 0; i < rowCount; i++)
	{
		printf("Wie viele Elemente soll die Reihe %i haben?\n", i + 1);
		playground[i] = ReadNumberInRange(MinElements, MaxElements);
	}
}

/// <summary>
/// Shows the playground
/// </summary>
/// <param name="playground">Pointer to the playground array</param>
void ShowPlayground(int32_t* playground)
{
	for (size_t i = 0; i < MaxRowCount; i++)
	{
		if (playground[i] == -1)
			return;
		printf("\nElemente in Reihe %i:", i + 1);
		for (size_t j = 0; j < playground[i]; j++)
			printf(" | ");
	}
}

/// <summary>
/// Updates the playground with the users inputs
/// </summary>
/// <param name="playground">Pointer to the playground array</param>
void UsersTurn(int32_t* playground)
{
	int16_t i = 0;
	int32_t row = -1;
	while (playground[i] != -1)
		i++;
	printf("\n\nAus welcher Reihe sollen Elemente entfernt werden?\n");
	do
	{
		if (row != -1)
			printf("\nDiese Reihe hat keine Elemente. Bitte erneut versuchen.\n");
		row = ReadNumberInRange(1, i) - 1;
	} while (playground[row] == 0);
	printf("\nWie viele Elemente sollen entfernt werden?\n");
	int32_t elements = ReadNumberInRange(MinElements, playground[row]);
	playground[row] -= elements;
}

/// <summary>
/// Makes a random turn and subtracts it from playground
/// </summary>
/// <param name="playground">Pointer to the playground array</param>
void RandomComputerTurn(int32_t* playground)
{
	int32_t row;
	int32_t elements;
	do
	{
		row = rand() % MaxRowCount;
	} while (playground[row] <= 0 || row > MaxRowCount);
	do
	{
		elements = rand() % playground[row] + 1;
	} while (elements <= 0 || playground[row] < elements);
	playground[row] -= elements;
	printf("\nDer Computer entfernt %i Elemente aus Reihe %i\n", elements, row + 1);
}

/// <summary>
/// Finds out if no elements are in rows
/// </summary>
/// <param name="playground">Pointer to the playground array</param>
/// <returns>If no elements: true, if any elements: false</returns>
bool IsWinner(int32_t* playground)
{
	for (size_t i = 0; i < MaxRowCount; i++)
	{
		if (playground[i] == -1)
			return true;
		if (playground[i] > 0)
			return false;
	}
	return true;
}

/// <summary>
/// Shows the winner
/// </summary>
/// <param name="playersTurn">true if player moved</param>
void ShowWinner(bool playersTurn) 
{
	printf("***");
	if (playersTurn)
		printf("\nSie haben Gewonnen! Herzlichen Gl\x81\ckwunsch.\n\n");
	else
		printf("\nDer Computer ist der Sieger.\n");
	printf("***\n\n");
}

/// <summary>
/// Function to make some smart moves. If no smart move found, make random move
/// </summary>
/// <param name="playgorund"></param>
void SmartComputerTurn(int32_t* playgorund) {
	int32_t rowsWithElements = 0;
	int32_t i = 0;
	while (rowsWithElements <= 2 && playgorund[i] >= 0)
	{
		if (playgorund[i] > 0)
			rowsWithElements++;
		i++;
	}
	i = 0;
	// if only one row with elements, remove all
	if (rowsWithElements == 1)
	{
		while (playgorund[i] >= 0)
		{
			if (playgorund[i] > 0)
			{
				printf("\nDer Computer entfernt %i Elemente aus Reihe %i\n", playgorund[i], i + 1);
				playgorund[i] = 0;
				return;
			}
			i++;
		}
	}
	// if two rows, create two rows with same count of elements
	if (rowsWithElements == 2)
	{
		int32_t firstRowWithElements = -1;
		int32_t secondRowWithElements = -1;
		while (playgorund[i] >= 0)
		{
			if (playgorund[i] >= 0)
			{
				if (firstRowWithElements >= 0)
					secondRowWithElements = i;
				else
					firstRowWithElements = i;
			}
			i++;
		}
		if (playgorund[firstRowWithElements] > playgorund[secondRowWithElements])
		{
			printf("\nDer Computer entfernt %i Elemente aus Reihe %i\n", playgorund[firstRowWithElements] - playgorund[secondRowWithElements], firstRowWithElements + 1);
			playgorund[firstRowWithElements] -= playgorund[firstRowWithElements] - playgorund[secondRowWithElements];
			return;
		}
		else if (playgorund[firstRowWithElements] < playgorund[secondRowWithElements])
		{
			printf("\nDer Computer entfernt %i Elemente aus Reihe %i\n", playgorund[secondRowWithElements] - playgorund[firstRowWithElements], secondRowWithElements + 1);
			playgorund[secondRowWithElements] -= playgorund[secondRowWithElements] - playgorund[firstRowWithElements];
			return;
		}
	}
	RandomComputerTurn(playgorund);


	/*uint32_t playgorundBinaries[MaxRowCount][3];
	for (int i = 0; i < MaxRowCount; i++)
		for (int j = 0; j <= 3; j++)
		{
			playgorundBinaries[i][j] = 0;
		}
		
	uint32_t k = 0;
	uint32_t l = 0;

	while (playgorund[k] >= 0)
	{
		int x = playgorund[k];
		for (l = 0; x > 0; l++)
		{
			playgorundBinaries[k][l] += x % 2;
			x = x / 2;
		}
		k++;
	}*/
}