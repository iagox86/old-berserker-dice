#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <time.h>


#define DICE 6
//#define DEBUG

int GetDiceTotal(int NumberOfDice, int Berserk/*, int depth*/)
{
	// The dice are going to be a bytemap, for the purpose of 
	// making berserker rules easier to deal with
	int depth = 0;
	int DiceRolls[DICE]; // The bytemap
	int Total;
	int i; // Loop counter
	int Die; // Current die

	// Initialize the bytemap to 0
	memset(DiceRolls, 0, sizeof(int) * DICE);
	// Initialize Total to 0
	Total = 0;

#ifdef DEBUG
	for(int j = 0; j < depth; j++)
		putchar(' ');
#endif

	for(i = 0; i < NumberOfDice; i++)
	{
		// Get the number
		Die = (rand() % DICE);
		// Increment the bytemap
		DiceRolls[Die]++;
		// Add this die to the total
		Total += (Die + 1);
#ifdef DEBUG
	printf("%d ", Die + 1);
#endif
	}

	// If it's a berserk roll, call recursively for each of the sets of dice
	// that's greater than one
	if(Berserk)
	{
		for(i = 0; i < DICE; i++)
		{
			if(DiceRolls[i] > 1)
			{
#ifdef DEBUG
				putchar('\n');
				// Put in spaces for depth, make it look nicer :)
				for(int j = 0; j < depth; j++)
					putchar(' ');

				printf("Rolling %d's: ", i + 1);
#endif
				Total = Total + GetDiceTotal(DiceRolls[i], 1/*, depth + 1*/);
			}
		}
	}

	return Total;
}

int main(int argc, char *argv[])
{
	int NumberOfDice;
	int i;

	// Seed the random number generator
	srand( time( NULL ));
	
	printf("How many dice? ");
	scanf("%d", &NumberOfDice);

//	for(i = 0; i < 10; i++)
//	{
		int StartTime = time( NULL );

		printf("\nTotal: %u\n\n", GetDiceTotal(NumberOfDice, 0));

		printf("\nTotal with berserk: %u\n\n", GetDiceTotal(NumberOfDice, 1));

		printf("\nTime: %d seconds\n\n\n", time( NULL ) - StartTime);
//	}

#ifdef WIN32
	system("pause");
#endif

	return 0;
}

