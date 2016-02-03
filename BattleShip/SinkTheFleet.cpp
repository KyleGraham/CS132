//----------------------------------------------------------------------------
// File:	SinkTheFleet.cpp
// 
// Function:
//				main()
//----------------------------------------------------------------------------

#include <iostream>
#include <iomanip>
#include "fleet.h"
using namespace std;
extern const char* shipNames[7];
//---------------------------------------------------------------------------------
// Function:	main()
// Title:		Set ShipInfo
// Description:
//				Runs the Sink the Fleet Game
// Programmer:	Paul Bladek
//				Kyle Graham
//				Hang Nguyen
// modified by:
// 
// Date:		12/9/2012
//
// Version:		0.5
// 
// Environment: Hardware: i3 
//              Software: OS: Windows 7; 
//              Compiles under Microsoft Visual C++ 2012
//
// Input:		
//
// Output:		
//
// Calls:		initializePlayer()
//				allocMem()
//				safeChoice()
//				getGrid()
//				printGrid()
//				resetGrid()
//				setships()
//				header()
//				getCoord()
//				deleteMem()
//				endBox()
//
// Called By:	n/a
//
// Parameters:	void
// 
// Returns:		int -- EXIT_SUCCESS upon successful completion
//
// History Log: 
//				12/09/2012 PB completed v 0.5
//				01/26/2015 KG & HN completed v 0.6
//				01/27/2015 KG & HN completed v 0.7
//				01/28/2015 KG & HN completed v 0.8
//				01/29/2015 KG & HN completed v 0.9
//				01/30/2015 KG & HN completed v 1.0
//				01/31/2015 KG & HN completed v 1.1
//				02/01/2015 KG & HN completed v 1.2
//   
//---------------------------------------------------------------------------------
int main(void)
{
	short numRows = SMALLROWS;			// total number of rows in the array
	short numCols = SMALLCOLS;			// total number of columns in the array
	char again = 'N';
	char choice = ' ';
	char gridSize = 'S';
	short whichPlayer = 0;
	bool gameOver = false;
	bool reshot = false;
	Cell coord = {0, 0};
	string message;
	string filename;
	Ship shipHit = NOSHIP;
	Player game[NUMPLAYERS] ;	// the two players in an array

	do
	{
		system("cls");
		cout << endl;
		header(cout);
		gridSize = safeChoice("Which size grid to you want to use", 'S', 'L');

		if( gridSize == 'L')
		{
			numRows = LARGEROWS;
			numCols = LARGECOLS;
		}
		else
		{
			numRows = SMALLROWS;
			numCols = SMALLCOLS;
		}
		initializePlayer(game);		
		initializePlayer(game + 1);
		// dynamically create the rows of the array
		allocMem(game, gridSize);

		// our code
		for(whichPlayer = 0; whichPlayer < NUMPLAYERS; whichPlayer++)
		{

			choice = ' ';
			cout << endl;
			// enter grid files or let users enter ships
			cin.clear();
			fflush(stdin);
			bool goodfile = true;
			do 
			{
				cout << "Player " << whichPlayer + 1;
				choice = safeChoice(", Would you like to read starting "
					"grid from a file?");
				switch(toupper(choice))
				{
					case 'Y': 
						cout << "Enter file name with .shp after the"
							" name" << endl;
						cin >> filename;
						goodfile = getGrid(game, whichPlayer, gridSize, filename);
						cin.clear();
						fflush(stdin);
						break;
					case 'N':
						setships(game, gridSize, whichPlayer);
						break;
				}
			}while (goodfile == false);
		} // end of for loop
		system("cls");
		cin.clear();
		fflush(stdin);
		header(cout);
		cout << "press <enter> to start the battle . . ." << endl;
		cin.get();
		system("cls");
		whichPlayer = 0;
		while(!gameOver)
		{
			printGrid(cout, game[whichPlayer].m_gameGrid[1], gridSize);
			reshot = false;
			cout << "Player " << whichPlayer + 1 << ", Enter " <<
				"Coordinates for Firing: " << endl;
			coord = getCoord(cin, gridSize);
			//check which case that the current player coordinates for firing is in 
			switch(game[!whichPlayer].m_gameGrid[0][coord.m_row][coord.m_col])
			{
			case 0:
				if (game[whichPlayer].m_gameGrid[1][coord.m_row]
				// check whether it is s repeat shot
				[coord.m_col] != NOSHIP)
				{
					cout << "Already shot here!" << endl;
					reshot = true;
					cout << "press <enter> " << endl;
					cin.get();
					system("cls");
				}
				else
				{
					system("cls");
					cout << "Miss!" << endl;
					game[whichPlayer].m_gameGrid[1][coord.m_row]
						[coord.m_col] = MISSED;
					printGrid(cout, game[whichPlayer].m_gameGrid[1], gridSize);
					cout << "press <enter> " << endl;
					cin.get();
					system("cls");
				}
				break;
			case 1:
				// check whether it is s repeat shot
				if (game[whichPlayer].m_gameGrid[1][coord.m_row]
				[coord.m_col] != NOSHIP)
				{
					cout << "Already shot here!" << endl;
					reshot = true;
					cout << "press <enter> " << endl;
					cin.get();
					system("cls");
				}
				else
				{
					system("cls");
					reshot = true;
					game[whichPlayer].m_gameGrid[1][coord.m_row]
						[coord.m_col] = HIT;
					printGrid(cout, game[whichPlayer].m_gameGrid[1], gridSize);
					game[whichPlayer].m_ships[1].m_piecesLeft--;
					game[whichPlayer].m_piecesLeft--;
					if(game[whichPlayer].m_ships[game[!whichPlayer].m_gameGrid[0]
					[coord.m_row][coord.m_col]].m_piecesLeft == 0)
					{
						cout << shipNames[game[!whichPlayer].m_gameGrid[0]
							[coord.m_row][coord.m_col]] << " SUNK!" << endl;
						cout << "press <enter> " << endl;
						cin.get();
						system("cls");
					}
					else 
					{
						cout << " Hit on " << shipNames[1] <<" ! Shoot again.";
						cout << endl;
						cout << "press <enter> " << endl;
						cin.get();
						system("cls");
					}
				}
				break;
			case 2:
				// check whether it is s repeat shot
				if (game[whichPlayer].m_gameGrid[1][coord.m_row]
					[coord.m_col] != NOSHIP)
				{
					cout << "Already shot here!" << endl;
					reshot = true;
					cout << "press <enter> " << endl;
					cin.get();
					system("cls");
				}
				else
				{
					system("cls");
					reshot = true;
					game[whichPlayer].m_gameGrid[1][coord.m_row][coord.m_col] = HIT;
					printGrid(cout, game[whichPlayer].m_gameGrid[1], gridSize);
					game[whichPlayer].m_ships[2].m_piecesLeft--;
					game[whichPlayer].m_piecesLeft--;
					if(game[whichPlayer].m_ships[game[!whichPlayer].m_gameGrid[0]
						[coord.m_row][coord.m_col]].m_piecesLeft == 0)
					{
						cout << shipNames[game[!whichPlayer].m_gameGrid[0]
							[coord.m_row][coord.m_col]] << " SUNK!" << endl;
						cout << "press <enter> " << endl;
						cin.get();
						system("cls");
					}
					else 
					{
						cout << " Hit on " << shipNames[2] <<" ! Shoot again.";
						cout << endl;
						cout << "press <enter> " << endl;
						cin.get();
						system("cls");
					}
				}
				break;
			case 3:
				// check whether it is s repeat shot
				if (game[whichPlayer].m_gameGrid[1][coord.m_row]
					[coord.m_col] != NOSHIP)
				{
					cout << "Already shot here!" << endl;
					reshot = true;
					cout << "press <enter> " << endl;
					cin.get();
					system("cls");
				}
				else
				{
					system("cls");
					reshot = true;
					game[whichPlayer].m_gameGrid[1][coord.m_row]
						[coord.m_col] = HIT;
					printGrid(cout, game[whichPlayer].m_gameGrid[1], gridSize);
					game[whichPlayer].m_ships[3].m_piecesLeft--;
					game[whichPlayer].m_piecesLeft--;
					if(game[whichPlayer].m_ships[game[!whichPlayer].m_gameGrid[0]
						[coord.m_row][coord.m_col]].m_piecesLeft == 0)
					{
						cout << shipNames[game[!whichPlayer].m_gameGrid[0]
							[coord.m_row][coord.m_col]] << " SUNK!" << endl;
						cout << "press <enter> " << endl;
						cin.get();
						system("cls");
					}
					else 
					{
						cout << " Hit on " << shipNames[3] <<" ! Shoot again.";
						cout << endl;
						cout << "press <enter> " << endl;
						cin.get();
						system("cls");
					}
				}
				break;
			case 4:
				// check whether it is s repeat shot
				if (game[whichPlayer].m_gameGrid[1][coord.m_row]
					[coord.m_col] != NOSHIP)
				{
					cout << "Already shot here!" << endl;
					reshot = true;
					cout << "press <enter> " << endl;
					cin.get();
					system("cls");
				}
				else
				{
					system("cls");
					reshot = true;
					game[whichPlayer].m_gameGrid[1][coord.m_row]
						[coord.m_col] = HIT;
					printGrid(cout, game[whichPlayer].m_gameGrid[1], gridSize);
					game[whichPlayer].m_ships[4].m_piecesLeft--;
					game[whichPlayer].m_piecesLeft--;
					if(game[whichPlayer].m_ships[game[!whichPlayer].m_gameGrid[0]
						[coord.m_row][coord.m_col]].m_piecesLeft == 0)
					{
						cout << shipNames[game[!whichPlayer].m_gameGrid[0]
							[coord.m_row][coord.m_col]] << " SUNK!" << endl;
						cout << "press <enter> " << endl;
						cin.get();
						system("cls");
					}
					else 
					{
						cout << " Hit on " << shipNames[4] <<" ! Shoot again.";
						cout << endl;
						cout << "press <enter> " << endl;
						cin.get();
						system("cls");
					}
				}
				break;
			case 5:
				// check whether it is s repeat shot
				if (game[whichPlayer].m_gameGrid[1][coord.m_row]
					[coord.m_col] != NOSHIP)
				{
					cout << "Already shot here!" << endl;
					reshot = true;
					cout << "press <enter> " << endl;
					cin.get();
					system("cls");
				}
				else
				{
					system("cls");
					reshot = true;
					game[whichPlayer].m_gameGrid[1][coord.m_row]
						[coord.m_col] = HIT;
					printGrid(cout, game[whichPlayer].m_gameGrid[1], gridSize);
					game[whichPlayer].m_ships[5].m_piecesLeft--;
					game[whichPlayer].m_piecesLeft--;		
					if(game[whichPlayer].m_ships[game[!whichPlayer].m_gameGrid[0]
						[coord.m_row][coord.m_col]].m_piecesLeft == 0)
					{
						cout << shipNames[game[!whichPlayer].m_gameGrid[0]
							[coord.m_row][coord.m_col]] << " SUNK!" << endl;
						cout << "press <enter> " << endl;
						cin.get();
						system("cls");
					}
					else 
					{
						cout << " Hit on " << shipNames[5] <<" ! Shoot again.";
						cout << endl;
						cout << "press <enter> " << endl;
						cin.get();
						system("cls");
					}
				}
				break;
			}
			if(reshot)
			{
				//system("cls");
				whichPlayer = whichPlayer;
				if(game[whichPlayer].m_piecesLeft == 0)
				{
					gameOver = true;
					endBox(whichPlayer);
				}
			}
			else
			{
				cout << "Player " << ((whichPlayer == 0) ? 2 : 1) << 
					"hit enter" << endl;
				getchar();
				whichPlayer = !whichPlayer;  // switch players
			}
		}
		again = safeChoice("Would you like to play again?", 'Y', 'N');
	}
	while(again == 'Y');

	return EXIT_SUCCESS;
} 