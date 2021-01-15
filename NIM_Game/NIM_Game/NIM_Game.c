#include <stdio.h>      // rpintf, scanf
#include <stdint.h>     // int32_t
#include <stdlib.h>     // rand()
#include <time.h>       // initialisierung des Zufallsgenerators
#include <stdbool.h>	// boolean

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
void ComputersTurn(int32_t* playground);
bool IsWinner(int32_t* playground);
void ShowWinner(bool playersTurn);
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
			ComputersTurn(playground);
	} while (IsWinner(playground));
	ShowWinner(playersTurn);
}

void GeneratePlayground(int32_t* playground)
{
	int rowCount = rand() % MaxRowCount + MinRowCount;
	for (uint32_t i = 0; i < rowCount; i++)
		playground[i] = rand() % MaxElements + 1;
}

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
		row = ReadNumberInRange(0, i) - 1;
	} while (playground[row] == 0);
	printf("\nWie viele Elemente sollen entfernt werden?\n");
	int32_t elements = ReadNumberInRange(MinElements, playground[row]);
	playground[row] -= elements;
}

void ComputersTurn(int32_t* playground)
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

bool IsWinner(int32_t* playground)
{
	for (size_t i = 0; i < MaxRowCount; i++)
	{
		if (playground[i] == -1)
			return false;
		if (playground[i] > 0)
			return true;
	}
	return true;
}

void ShowWinner(bool playersTurn) 
{
	printf("***");
	if (playersTurn)
		printf("\nSie haben Gewonnen! Herzlichen Gl\x81\ckwunsch.\n\n");
	else
		printf("\nDer Computer ist der Sieger.\n");
	printf("***\n\n");
}