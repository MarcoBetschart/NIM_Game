#include <stdio.h>      // rpintf, scanf
#include <stdint.h>     // int32_t
#include <stdlib.h>     // rand()
#include <time.h>       // initialisierung des Zufallsgenerators
#include <stdbool.h>	// boolean
#include <string.h>		// memcpy

struct Playground {
	int16_t playGroundArray[6];
	int16_t rowCount;
};

int16_t ReadNumberInRange(int16_t minRange, int16_t maxRange);
bool ReadYesOrNoInput(char* askText);
void GeneratePlayground(struct Playground* playground);
void ManuallyCreatePlayground(struct Playground* playground);
void ShowPlayground(struct Playground playground);
void UsersTurn(struct Playground* playground);
void RandomComputerTurn(struct Playground* playground);
bool IsWinner(struct Playground playground);
void ShowWinner(bool playersTurn);
void SmartComputerTurn(struct Playground* playgorund);
void PlayGame();

int main() {
	srand(time(NULL));
	printf("Willkommen zum NIM-Spiel.\n\n");
	while (ReadYesOrNoInput("M\x94\chten sie eine Runde NIM spielen? y/n\n"))
	{
		PlayGame();
	}
	printf("\nBis zum n\x84\chsten Mal!");
}

int16_t ReadNumberInRange(int16_t minRange, int16_t maxRange) {
	int16_t number = 0;
	while (true)
	{
		scanf_s("%hu", &number);
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
	return false;
}

/// <summary>
/// The Function which runs the game
/// </summary>
void PlayGame()
{
	bool playersTurn = false;
	struct Playground playground;

	if (ReadYesOrNoInput("\nSoll das Spiel automatisch generiert werden? y/n\n"))
		GeneratePlayground(&playground);
	else
		ManuallyCreatePlayground(&playground);
	do
	{
		playersTurn = !playersTurn;
		if (playersTurn == 1)
		{
			ShowPlayground(playground);
			UsersTurn(&playground);
		}
		else
			SmartComputerTurn(&playground);
	} while (!IsWinner(playground));
	ShowWinner(playersTurn);
}

/// <summary>
/// Creates a random playground
/// </summary>
/// <param name="playground">Pointer to the playground struct</param>
void GeneratePlayground(struct Playground* playground)
{
	playground->rowCount = rand() % 6 + 2;
	for (uint16_t i = 0; i < playground->rowCount; i++)
		playground->playGroundArray[i] = rand() % 6 + 1;
}

/// <summary>
/// Creates playground from users Input
/// </summary>
/// <param name="playground">Pointer to the playground struct</param>
void ManuallyCreatePlayground(struct Playground* playground)
{
	printf("\nWie viele Reihen soll das Spiel haben?\n");
	playground->rowCount = ReadNumberInRange(2, 6);
	for (uint16_t i = 0; i < playground->rowCount; i++)
	{
		printf("Wie viele Elemente soll die Reihe %i haben?\n", i + 1);
		playground->playGroundArray[i] = ReadNumberInRange(1, 6);
	}
}

/// <summary>
/// Shows the playground
/// </summary>
/// <param name="playground">The playground array</param>
void ShowPlayground(struct Playground playground)
{
	for (int16_t i = 0; i < playground.rowCount; i++)
	{
		printf("\nElemente in Reihe %i:", i + 1);
		for (int16_t j = 0; j < playground.playGroundArray[i]; j++)
			printf(" | ");
	}
}

/// <summary>
/// Updates the playground with the users inputs
/// </summary>
/// <param name="playground">Pointer to the playground struct</param>
void UsersTurn(struct Playground* playground)
{
	int8_t i = 0;
	int16_t row = -1;
	printf("\n\nAus welcher Reihe sollen Elemente entfernt werden?\n");
	do
	{
		if (row > playground->rowCount || playground->playGroundArray[row] == 0)
			printf("\nDiese Reihe hat keine Elemente. Bitte erneut versuchen.\n");
		row = ReadNumberInRange(1, playground->rowCount) - 1;
	} while (playground->playGroundArray[row] == 0);
	printf("\nWie viele Elemente sollen entfernt werden?\n");
	int16_t elements = ReadNumberInRange(1, playground->playGroundArray[row]);
	playground->playGroundArray[row] -= elements;
}

/// <summary>
/// Makes a random turn and subtracts it from playground
/// </summary>
/// <param name="playground">Pointer to the playground struct</param>
void RandomComputerTurn(struct Playground* playground)
{
	int16_t row;
	int16_t elements;
	do
	{
		row = rand() % playground->rowCount;
	} while (playground->playGroundArray[row] <= 0 || row > 6);
	do
	{
		elements = rand() % playground->playGroundArray[row] + 1;
	} while (elements <= 0 || playground->playGroundArray[row] < elements);
	playground->playGroundArray[row] -= elements;
	printf("\nDer Computer entfernt %i Elemente aus Reihe %i\n", elements, row + 1);
}

/// <summary>
/// Finds out if no elements are in rows
/// </summary>
/// <param name="playground">Pointer to the playground struct</param>
/// <returns>If no elements: true, if any elements: false</returns>
bool IsWinner(struct Playground playground)
{
	for (int16_t i = 0; i < playground.rowCount; i++)
		if (playground.playGroundArray[i] > 0)
			return false;
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
/// Function to make smart moves. 
/// Removes as many items from highest, that all bits are even
/// If highest has wrong bits, it uses second highest and so on.
/// See scheme on https://www.hep-verlag.ch/pub/media/import/public/6486/mathematikaufgaben.pdf
/// </summary>
/// <param name="playgorund">Pointer to the playground struct</param>
void SmartComputerTurn(struct Playground* playground) {
	int16_t xorSum = 0;
	for (int16_t i = 0; i < playground->rowCount; i++)
	{
		xorSum ^= playground->playGroundArray[i];
	}
	if (xorSum != 0)
	{
		int16_t elementesToRemove = 0;
		for (int16_t i = 0; i < playground->rowCount; i++)
		{
			elementesToRemove = playground->playGroundArray[i] ^ xorSum;
			if (elementesToRemove < playground->playGroundArray[i])
			{
				printf("\nDer Computer entfernt %i Elemente aus Reihe %i\n", playground->playGroundArray[i] - elementesToRemove, i + 1);
				playground->playGroundArray[i] = elementesToRemove;
				return;
			}
		}
	}
	else
	{
		RandomComputerTurn(playground);
	}


	//int16_t playgroundBinaries[6][3];
	//for (int16_t i = 0; i < playground->rowCount; i++)
	//	for (int16_t j = 0; j < 3; j++)
	//		playgroundBinaries[i][j] = 0;

	//for (int16_t i = 0; i < playground->rowCount; i++)
	//{
	//	uint16_t x = playground->playGroundArray[i];
	//	for (uint16_t j = 0; x > 0; j++)
	//	{
	//		playgroundBinaries[i][j] += x % 2;
	//		x /= 2;
	//	}
	//}

	//uint16_t isEven[3] = { 1, 1, 1 };
	//for (uint16_t i = 0; i < 3; i++)
	//{
	//	for (uint16_t j = 0; j < playground->rowCount; j++)
	//		isEven[i] = isEven[i] ^ playgroundBinaries[j][i];
	//}

	//if (isEven[0] == 1 && isEven[1] == 1 && isEven[2] == 1)
	//{
	//	RandomComputerTurn(playground);
	//	return;
	//}

	//int16_t sortedPlayground[6] = { 0 };
	//memcpy(sortedPlayground, playground->playGroundArray, sizeof(playground->playGroundArray));
	//for (int i = 0; i < playground->rowCount; i++)
	//{
	//	for (int j = 0; j < playground->rowCount; j++)
	//	{
	//		if (sortedPlayground[j] < sortedPlayground[i])
	//		{
	//			int tmp = sortedPlayground[i];
	//			sortedPlayground[i] = sortedPlayground[j];
	//			sortedPlayground[j] = tmp;
	//		}
	//	}
	//}

	//int16_t rowToRemove = -1;
	//int16_t sortedIndex = 0;
	//for (int16_t i = 0; i < playground->rowCount; i++)
	//{
	//	if (playground->playGroundArray[i] == sortedPlayground[sortedIndex])
	//	{
	//		for (size_t j = 0; j < 3; j++)
	//		{
	//			if (isEven[j] == 1)
	//			{
	//				continue;
	//			}
	//			if (playgroundBinaries[i][j] == 1)
	//			{
	//				rowToRemove = i;
	//			}
	//			else
	//				rowToRemove = -1;
	//		}
	//		if (rowToRemove != -1)
	//			break;
	//		else
	//			sortedIndex++;
	//	}
	//}

	//uint16_t binaryNumber = 1;
	//uint16_t elementsToRemove = 0;
	//for (uint16_t i = 0; i < 3; i++)
	//{
	//	if (isEven[i] == 0)
	//		elementsToRemove += binaryNumber;
	//	binaryNumber *= 2;
	//}
	//if (rowToRemove != -1 && elementsToRemove > 0 && elementsToRemove <= playground->playGroundArray[rowToRemove])
	//{
	//	printf("\nDer Computer entfernt %i Elemente aus Reihe %i\n", elementsToRemove, rowToRemove + 1);
	//	playground->playGroundArray[rowToRemove] -= elementsToRemove;
	//}
	//else
	//	RandomComputerTurn(playground);
}