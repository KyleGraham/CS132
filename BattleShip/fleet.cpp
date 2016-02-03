//----------------------------------------------------------------------------
// File:	fleet.cpp
// 
// Functions: 
//	  setShipInfo()	
//	  allocMem() 
//	  deleteMem()
//	  printShip() 
//	  printGrid() 
//	  initializePlayer() 
//	  setships()	      
//	  saveGrid()
//	  getGrid()
//	  getCoord()
//	  validLocation() 
//	  header() 
//	  endBox() 
//----------------------------------------------------------------------------
#include "fleet.h"
//---------------------------------------------------------------------------------
// YOU ARE RESPONSIBLE FOR CORRECT HEADERS -- one for each function
// include the definitions for each of the non-template functions
//    declared in fleet.h 
//---------------------------------------------------------------------------------

const char* shipNames[SHIP_SIZE_ARRAYSIZE] = 
	{"No Ship", "Mine Sweeper", "Submarine", "Frigate",
		"Battleship", "Aircraft Carrier"};
const int TOTALPIECES = 17; // total pieces in all ships

//---------------------------------------------------------------------------------
// Function:	setShipInfo()
// Title:		Set ShipInfo
// Description:
//		Sets struct ShipInfo fields
// Programmer:
// 
// Date:	12/20/05
//
// Version:	0.1
// 
// Environment: Intel Xeon PC 
//                Software:   MS Windows 7 for execution; 
//                Compiles under Microsoft Visual C++.Net 2012
//
// Calls:
//
// Called By:
//
// Parameters:	shipInfoPtr: ShipInfo *; pointer to the ShipInfo to be set
//				name: Ship;	enumerated name of type of ship; default: NOSHIP
//				orientation: Direction;	enumerated direction; default: HORIZONTAL
//				row: unsigned short; row-coordinate in grid; default: 0
//				col: unsigned short; column-coordinate in grid; default: 0
// 
// Returns:	void
//
// History Log:
//		12/20/05 PB completed v 0.1
//      01/30/15  PB completed v 0.2
//   
//---------------------------------------------------------------------------------
void setShipInfo(ShipInfo * shipInfoPtr, Ship name, Direction orientation,
	unsigned short row, unsigned short col)
{
	Cell location = {row, col};
	shipInfoPtr->m_bowLocation = location; 
	shipInfoPtr->m_name = name;
	shipInfoPtr->m_orientation = orientation;
	shipInfoPtr->m_piecesLeft = shipSize[name];
} 

//---------------------------------------------------------------------------------
// Function:	allocMem()
// Title:		Allocate Memory
// Description:
//		allocates memory for current grids
// Programmer:	Paul Bladek
// modified by:	Paul Bladek
// 
// Date:	9/13/06
//
// Version:	1.01
// 
// Environment: Hardware: i3 
//              Software: OS: Windows 7; 
//              Compiles under Microsoft Visual C++ 2012
//
// Calls:
//
// Called By:	main()
//
// Parameters:	players: Player[]; 	the array of 2 players in the game
//		size: char;	'	S' or 'L' (small or large)
// 
// Returns:	void
//
// History Log:
//		12/20/05 PB completed v 1.0 
//		09/13/06 PB completed v 1.01
//		01/09/15 PB completed v 1.02
//
//---------------------------------------------------------------------------------
void allocMem(Player players[], char size)
{
	char * p = nullptr;
	short numberOfRows = (toupper(size) == 'L') ? LARGEROWS : SMALLROWS;
	short numberOfCols = (toupper(size) == 'L') ? LARGECOLS : SMALLCOLS;

	try
	{
		for(short i = 0; i < NUMPLAYERS; ++i)
		{
			players[i].m_gameGrid[0] = nullptr;
			players[i].m_gameGrid[0] = new Ship*[numberOfRows];
			players[i].m_gameGrid[1] = nullptr;
			players[i].m_gameGrid[1] = new Ship*[numberOfRows];
			for(short j = 0; j < numberOfRows; ++j)
			{
			//-------------------------------------------------
			// set the pointers to NULL, then allocate the
			// memory for each row in each grid
				players[i].m_gameGrid[0][j] = nullptr;
				players[i].m_gameGrid[0][j] = new Ship[numberOfCols];
				players[i].m_gameGrid[1][j] = nullptr;
				players[i].m_gameGrid[1][j] = new Ship[numberOfCols];
				for(short k = 0; k < numberOfCols; ++k)
				{
					players[i].m_gameGrid[0][j][k] = NOSHIP;
					players[i].m_gameGrid[1][j][k] = NOSHIP;
				} // end for k
			} // end for j
		} // end for i
	}
	catch(exception e)
	{
		deleteMem(players, size);
		cerr << "exception: " << e.what() << endl;
		cout << "shutting down" << endl;
		cin.ignore(BUFFER_SIZE, '\n');
		exit(EXIT_FAILURE);
	}
}

//---------------------------------------------------------------------------------
// Function:	deleteMem()
// Title:		Delete Memory
// Description:
//		Safely deletes memory for grids
// Programmer:	Paul Bladek
//				Kyle Graham
//				Hang Nguyen
// 
// Date:	12/20/05
//
// Version:	0.1
// 
// Environment: Hardware: i3 
//              Software: OS: Windows 7; 
//              Compiles under Microsoft Visual C++ 2012
//
// Calls:
//
// Called By:	main()
//
// Parameters:	players: Player[]; 	the array of the 2 Players
//		size: char;	'	S' or 'L'
// 
// Returns:	void
//
// History Log:
//		12/20/05 PB completed v 0.1
//		01/09/15 KG & HN completed v 0.2
//		01/10/15 KG & HN completed v 0.3
//   
//---------------------------------------------------------------------------------
void deleteMem(Player players[], char size) 
{
	short numberOfRows = (toupper(size) == 'L') ? LARGEROWS : SMALLROWS;
	// your code goes here ...
	// delete[] in reverse order of allocMem()
	// be sure to check if the memory was allocated (!nullptr) BEFORE deleting
	short numberOfCols = (toupper(size) == 'L') ? LARGECOLS : SMALLCOLS;
	for(short i = 0; i < NUMPLAYERS; ++i)
	{
		for(short j = 0; j < numberOfRows; ++j)
		{
			if (players[i].m_gameGrid[0][j] != nullptr)
				delete[] players[1].m_gameGrid[0][j];
			if (players[i].m_gameGrid[1][j] != nullptr)
				delete[] players[1].m_gameGrid[1][j];
		} // end for i
		if (players[i].m_gameGrid[0] != nullptr)
			delete[] players[i].m_gameGrid[0];
		if (players[i].m_gameGrid[1] != nullptr)
			delete[] players[i].m_gameGrid[1];
	} // end for j
}

//---------------------------------------------------------------------------------
// Function:	printShip()
// Title:	Print Ship 
// Description:
//		Print grid element for the proper ship
// Programmer:	Paul Bladek
// 
// Date:	9/12/06
//
// Version:	1.0
// 
// Environment: Hardware: i3 
//              Software: OS: Windows 7; 
//              Compiles under Microsoft Visual C++ 2012
//
// Output:		three characters representing one ship to sout
//
// Calls:
//
// Called By:	printGrid()
//
// Parameters:	sout: ostream&;	the stream to print to
//				thisShip: Ship;	the Ship to be printed in the grid format
// 
// Returns:	void
//
// History Log: 
//				9/12/06 PB comleted v 1.0
//     
//---------------------------------------------------------------------------------
void printShip(ostream & sout, Ship thisShip)
{	
	sout << ' ' ;
	switch(thisShip)
	{
		case NOSHIP: sout << ' ';
			break;
		case MINESWEEPER: sout << 'M';
			break;
		case SUB: sout << 'S';
			break;
		case FRIGATE: sout << 'F';
			break;
		case BATTLESHIP: sout << 'B';
			break;
		case CARRIER: sout << 'C';
			break;
		case HIT: sout << 'H';
			break;
		case MISSED: sout << MISS;
			break;
		default: sout << 'X';
	}
	sout << VERT ;
}

//---------------------------------------------------------------------------------
// Function:	printGrid()
// Title:	Print Ship 
// Description:
//		Print grid element for the proper ship
// Programmer:	Paul Bladek
//				Kyle Graham
//				Hang Nguyen
// 
// Date:	12/20/05
//
// Version:	0.1
// 
// Environment: Hardware: i3 
//              Software: OS: Windows 7; 
//              Compiles under Microsoft Visual C++ 2012
//
// Output:	a single grid to sout
//
// Calls:	printShip()
//
// Called By:	main()
//		setships()
//		saveGrid()
//
// Parameters:	sout: ostream&;	the stream to print to
//		grid: Ship**;	the 2-D array of Ships 
//		size: char;	'S' or 'L'
// 
// Returns:	void
//
// History Log:
//				12/20/05 PB completed v 0.1
//				01/16/15 KG & HN completed v 0.2
//     
//---------------------------------------------------------------------------------
void printGrid(ostream& sout, Ship** grid, char size)
{
	short numberOfRows = (toupper(size) == 'L') ? LARGEROWS : SMALLROWS;
	short numberOfCols = (toupper(size) == 'L') ? LARGECOLS : SMALLCOLS;

	for(short j = 1; j <= numberOfCols; ++j)
	{
		sout << setw(3) << j;	
	}
	sout << endl;
	// our code 
	// use printShip for each element in the grid 
	for(short i = 1; i <= numberOfRows; ++i)
	{
		sout  << static_cast<char>(64 + i);
		for(short j = 1; j <= numberOfCols; ++j)
		{
			printShip(sout, grid[i - 1][j - 1]);
		} 
		sout  << endl;
		sout  << " ";
		for(short j = 1; j <= numberOfCols; ++j)
		{
			sout << HORIZ << HORIZ << CL;
		}
		sout  << endl;
	}
} 

//---------------------------------------------------------------------------------
// Function:	initializePlayer()
// Title:	Initialize Player 
// Description:
//		sets initial values for m_ships and m_piecesLeft
// Programmer:	Paul Bladek
// 
// Date:	9/12/06
//
// Version:	1.0
// 
// Environment: Hardware: i3 
//              Software: OS: Windows 7; 
//              Compiles under Microsoft Visual C++ 2012
//
// Calls:
//
// Called By:	main()
//
// Parameters:	playerPtr: Player*;	a pointer to the current Player
// 
// Returns:	void
//
// History Log: 
//				09/12/06 PB comleted v 1.0
//     
//---------------------------------------------------------------------------------
void initializePlayer(Player* playerPtr)
{
	for(short i = 0; i < SHIP_SIZE_ARRAYSIZE; i++)
		setShipInfo(playerPtr->m_ships + i, static_cast<Ship>(i));
	playerPtr->m_piecesLeft = TOTALPIECES; 
}

//---------------------------------------------------------------------------------
// Function:	setships()
// Title:	Set Ships 
// Description:
//		Allows user to put ships in grid
// Programmer:	Paul Bladek
// modified by:	Kyle Graham
//				Hang Nguyen
// 
// Date:	9/12/06
//
// Version:	0.5
// 
// Environment: Hardware: i3 
//              Software: OS: Windows 7; 
//              Compiles under Microsoft Visual C++ 2012
//
// Input:	location and orientation using getCoord from cin
//
// Output:	prompts to cout
//
// Calls:	printGrid()
//		safeChoice()
//		getCoord()
//		saveGrid()
//
// Called By:	main()
//
// Parameters:	players: Player[];	the array of 2 players 
//		size: char;		'S' or 'L'
//		whichPlayer: short;	the player number (0 or 1)
// 
// Returns:	void
//
// History Log: 
//				9/12/06 PB comleted v 0.5
//				1/16/15 KG & HN completed v 0.6
//				1/23/15 KG & HN completed v 0.7
//				1/29/15 KG & HN completed v 0.8
//     
//---------------------------------------------------------------------------------
void setships(Player players[], char size, short whichPlayer)
{
	char input = 'V';
	char ok = 'Y';
	char save = 'N';
	ostringstream outSStream;
	Cell location = {0, 0};

	for(short j = 1; j < SHIP_SIZE_ARRAYSIZE; j++)
	{
		system("cls");
		printGrid(cout, players[whichPlayer].m_gameGrid[0], size);
		outSStream.str("");
		outSStream << "Player " << whichPlayer + 1 << " Enter " 
			<< shipNames[j] << " orientation";
		input = safeChoice(outSStream.str(), 'V', 'H');
		players[whichPlayer].m_ships[j].m_orientation = (input == 'V') 
			? VERTICAL : HORIZONTAL;
		cout << "Player " << whichPlayer + 1 << " Enter " << shipNames[j] 
			<< " bow coordinates <row letter><col #>: ";
		players[whichPlayer].m_ships[j].m_bowLocation = getCoord(cin, size);
		location = players[whichPlayer].m_ships[j].m_bowLocation;
		// if ok
		if(!validLocation(players[whichPlayer], j, size))
		{
			cout << "invalid location. Press <enter>" ;
			cin.get();
			j--; // redo
			continue;
		}
		// our code
		for(int i = 0; i < shipSize[j]; i ++)
		{
			if (input == 'V')
			{
				players[whichPlayer].m_gameGrid[0][location.m_row + i]
					[location.m_col] = static_cast<Ship>(j);
			}
			else
			{
				players[whichPlayer].m_gameGrid[0][location.m_row]
					[location.m_col + i] = static_cast<Ship>(j);
			}
		}
		system("CLS");
		printGrid(cout, players[whichPlayer].m_gameGrid[0], size);
		ok = safeChoice("Position okay? ", 'Y', 'N');
		// choice not ok
		if (ok == 'N')
		{
			for(int i = 0; i < shipSize[j]; i ++)
			{
				if (input == 'V')
				{
					players[whichPlayer].m_gameGrid[0][location.m_row + i]
						[location.m_col] = NOSHIP;
				}
				else
				{
					players[whichPlayer].m_gameGrid[0][location.m_row]
						[location.m_col + i] = NOSHIP;
				}
			}
			system("CLS");
			printGrid(cout, players[whichPlayer].m_gameGrid[0], size);
			j--;
		}
	} // end for j
	save = safeChoice("\nSave starting grid?", 'Y', 'N');
	if(save == 'Y')
	saveGrid(players, whichPlayer, size);
}

//---------------------------------------------------------------------------------
// Function:	saveGrid()
// Title:	Save Grid 
// Description:
//		Saves the ship grid to a file
// Programmer:	Paul Bladek
//				Kyle Graham
//				Hang Nguyen
// 
// Date:	12/20/05
//
// Version:	0.1
// 
// Environment: Hardware: i3 
//              Software: OS: Windows 7; 
//              Compiles under Microsoft Visual C++ 2012
//
// Output:	grid to specified file
//
// Calls:	printGrid()
//
// Called By:	setships()
//
// Parameters:	player: sPlayer[];	the array of 2 players
//		whichPlayer: short; the player number (0 or 1) 
//		size: char;	'S' or 'L'
// 
// Returns:	void
//
// History Log:
//				12/20/05 PB completed v 0.1
//				01/23/15 KG & HN completed v 0.2
//				01/27/15 KG & HN completed v 0.3
//				02/01/15 KG & HN completed v 0.4
//     
//---------------------------------------------------------------------------------
void saveGrid(Player players[], short whichPlayer, char size)
{
	short numberOfRows = (toupper(size) == 'L') ? LARGEROWS : SMALLROWS;
	short numberOfCols = (toupper(size) == 'L') ? LARGECOLS : SMALLCOLS;	
	// your code goes here ...
	std::ofstream;
	string name_output_file;
	string name_output_file_final;
	char size_of_grid;
	cout <<"Enter the name of an output file: ";
	cin >> name_output_file;
	name_output_file_final = name_output_file + ".shp"; 
	ofstream ofs;
	ofs.open(name_output_file_final);
	if(!ofs)
		{
			cout << "could not open file " << name_output_file << endl;
		}
	// print out the grid size for the 1st line of the output file
	if  (size == 'L')
	{
		size_of_grid = 'L';
		ofs.put(size_of_grid);
		ofs << endl;
	}
	else if (size == 'S')
	{
		size_of_grid = 'S';
		ofs.put(size_of_grid);
		ofs << endl;
	}
	// print out the location of the ship
	// 1st number is the orientation
	// 2nd number is the row
	// 3nd number is the column
	// one ship per line
	for (int i = 1; i < SHIP_SIZE_ARRAYSIZE; i++)
	{
		ofs << static_cast<int> (players[whichPlayer].m_ships[i].m_orientation);
		ofs << " ";
		ofs << (players[whichPlayer].m_ships[i].m_bowLocation.m_row);
		ofs << " ";
		ofs << (players[whichPlayer].m_ships[i].m_bowLocation.m_col);
		ofs << endl;
	}
	cout << name_output_file_final << " is saved." << endl;
	ofs.close();
}

//---------------------------------------------------------------------------------
// Function:	getGrid()
// Title:	GetGrid 
// Description:
//		Reads grid from a file and properly sets the ships
// Programmer:	Paul Bladek
//				Kyle Graham
//				Hang Nguyen
// modified by:	
// 
// Date:	9/12/06
//
// Version:	0.5
// 
// Environment: Hardware: i3 
//              Software: OS: Windows 7; 
//              Compiles under Microsoft Visual C++ 2012
//
// Input:	grid from specified file
//
// Output:	prompts to cout
//
// Calls:
//
// Called By:	main()
//
// Parameters:	players: Player[];	the array of 2 players
//		whichPlayer: short;	the player number  (0 or 1) 
//		size: char;		'S' or 'L'
//		string fileName:	the name of the file to be opened for reading
// 
// Returns: bool -- 	true if the file is opened and read;
//			false otherwise
//
// History Log: 
//				9/12/06 PB comleted v 0.5
//				1/26/2015 KG & HN completed v 0.6
//				1/27/2015 KG & HN completed v 0.7
//				1/28/2015 KG & HN completed v 0.8
//				1/29/2015 KG & HN completed v 0.9
//     
//---------------------------------------------------------------------------------
bool getGrid(Player players[], short whichPlayer, char size, string fileName)
{
	string line;
	ifstream ifs;
	Ship ship = NOSHIP;
	short shipCount[SHIP_SIZE_ARRAYSIZE] = {0};
	char cell = ' ';
	//char fsize = 'S';
	char size_of_grid;
	short numberOfRows = (toupper(size) == 'L') ? LARGEROWS : SMALLROWS;
	short numberOfCols = (toupper(size) == 'L') ? LARGECOLS : SMALLCOLS;

	try
	{
		ifs.open(fileName.c_str());
		if(!ifs)
		{
			cout << "could not open file " << fileName << endl
				<< " press <enter> to continue" << endl;
			cin.ignore(BUFFER_SIZE, '\n');
			return false;
		}
	}
	catch(exception e)
	{
		cout << "could not open file " << fileName << endl
			<< " press <enter> to continue" << endl;
		cin.ignore(BUFFER_SIZE, '\n');
		return false;
	}	
	// the 2 following lines are yours, so we didn't delete that.
	// while(ifs.get(cell))
	//	cout << cell;
	
	// our code
	size_of_grid = ifs.get();
	if ((size == 'L') && (size_of_grid != 'L'))
	{ 
		cout << "The input file size is not compatible with the " <<
			"grid size that you chose from the beginning.";
		cout << endl;
		return false;
	}
	else if ((size == 'S') && (size_of_grid != 'S'))
	{ 
		cout << "The input file size is not compatible with the " <<
			"grid size that you chose from the beginning.";
		cout << endl;
		return false;
	}

	for (int i = 1; i < SHIP_SIZE_ARRAYSIZE; i++)
	{
		int input_orentation;
		int input_row;
		int input_col;
		ifs >> input_orentation ;
		ifs >> input_row;
		ifs >> input_col;

		Cell location = {0, 0};
		location.m_row = input_row;
		location.m_col = input_col;
		players[whichPlayer].m_ships[i].m_bowLocation = location;

		if (input_orentation == 0)
			players[whichPlayer].m_ships[i].m_orientation = HORIZONTAL;
		else if (input_orentation == 1)
			players[whichPlayer].m_ships[i].m_orientation = VERTICAL;
		
		for(int j = 0; j < shipSize[i]; j++)
		{
			if (players[whichPlayer].m_ships[i].m_orientation == VERTICAL)
			{
				players[whichPlayer].m_gameGrid[0][location.m_row + j]
					[location.m_col] = static_cast<Ship>(i);
			}
			else if (players[whichPlayer].m_ships[i].m_orientation == HORIZONTAL)
			{
				players[whichPlayer].m_gameGrid[0][location.m_row]
					[location.m_col + j] = static_cast<Ship>(i);
			} // end of if statement
		} // end of j
		system("CLS");
		printGrid(cout, players[whichPlayer].m_gameGrid[0], size);
	}
	system("CLS");
	ifs.close();	
	return true;
}

//---------------------------------------------------------------------------------
// Function:	getCoord()
// Title:	Get Coordinates 
// Description:
//		Returns a cell with coordinates set by user
// Programmer:	Paul Bladek
// 
// Date:	9/12/06
//
// Version:	1.0
// 
// Environment: Hardware: i3 
//              Software: OS: Windows 7; 
//              Compiles under Microsoft Visual C++ 2012
//
// Input:	cell coordinates (in the form "A13" from sin
//
// Output:	prompts to cout
//
// Calls:	none
//
// Called By:	main()
//		setships()
//
// Parameters:	sin: istream&;	the stream to read from
//		size: char;	'S' or 'L'
// 
// Returns:	Cell location -- a cell containing the input coordinates
//
// History Log: 
//				9/12/06 PB comleted v 1.0
//				1/20/15 KG % HN completed v 1.1
//     
//---------------------------------------------------------------------------------
Cell getCoord(istream& sin, char size)
{
	cin.clear();
	fflush(stdin);
	short numberOfRows = (toupper(size)=='L') ? LARGEROWS : SMALLROWS;
	short numberOfCols = (toupper(size)=='L') ? LARGECOLS : SMALLCOLS;
	char highChar = static_cast<char>(numberOfRows - 1) + 'A';
	char row  = 'A';
	short col = 0;
	Cell location = {0, 0};
	do
	{
		col = 0;
		cout << "Row must be a letter from A to " << highChar 
			<< " and column must be  from 1 to "  << numberOfCols << ": ";
		while((row = toupper(sin.get())) < 'A' || row  > highChar)
		{
			sin.ignore(BUFFER_SIZE, '\n');
			cout << "Row must be a letter from A to " << highChar 
				<< " and column must be  from 1 to "  << numberOfCols << ": ";
		}
		sin >> col;
		if(!sin)
			sin.clear();
		sin.ignore(BUFFER_SIZE, '\n');
	}
	while(col < 1 || col > numberOfCols);
	location.m_col = col - 1;
	location.m_row = static_cast<short>(row - 'A');
	return location;
}

//---------------------------------------------------------------------------------
// Function:	validLocation()
// Title:	Valid Location 
// Description:
//		Can the ship legitimately go there?
// Programmer:	Paul Bladek
//				Kyle Graham
//				Hang Nguyen
// 
// Date:	12/20/05
//
// Version:	0.1
// 
// Environment: Hardware: i3 
//              Software: OS: Windows 7; 
//              Compiles under Microsoft Visual C++ 2012
//
// Calls:
//
// Called By:
//
// Parameters:	player: const Player&;	a reference to the specific Player
//		shipNumber: short;	the number of the ship (1 - 5)
//					in the array player.m_ships[]
//		size: char;		'S' or 'L'
// 
// Returns: bool -- 	true if the ship would not go off the edge
//				or cross another ship;
//			false otherwise
//
// History Log:
//				12/20/05 PB completed v 0.1
//				01/23/15 KG & HN completed v 0.2
//     
//---------------------------------------------------------------------------------
bool validLocation(const Player& player, short shipNumber, char size)
{
	short numberOfRows = (toupper(size)=='L') ? LARGEROWS : SMALLROWS;
	short numberOfCols = (toupper(size)=='L') ? LARGECOLS : SMALLCOLS;

	// our code
	if (player.m_ships[shipNumber].m_orientation == VERTICAL)
	{
		if(shipSize[shipNumber] == 2)
		{
			if(player.m_ships[shipNumber].m_bowLocation.m_row == 
				(numberOfRows - 1))
				return false;
		}
		if (shipSize[shipNumber] == 3)
		{
			if (player.m_ships[shipNumber].m_bowLocation.m_row == 
				((numberOfRows - 1)))
				return false;
			if(player.m_ships[shipNumber].m_bowLocation.m_row == 
				(numberOfRows - 2))
				return false;
		}
		if (shipSize[shipNumber] == 4)
		{
			if (player.m_ships[shipNumber].m_bowLocation.m_row == 
				((numberOfRows - 1)))
				return false;
			if (player.m_ships[shipNumber].m_bowLocation.m_row == 
				((numberOfRows - 2)))
				return false;
			if (player.m_ships[shipNumber].m_bowLocation.m_row == 
				((numberOfRows - 3)))
				return false;
		}
		if (shipSize[shipNumber] == 5)
		{
			if (player.m_ships[shipNumber].m_bowLocation.m_row == 
				((numberOfRows - 1)))
				return false;
			if (player.m_ships[shipNumber].m_bowLocation.m_row == 
				((numberOfRows - 2)))
				return false;
			if (player.m_ships[shipNumber].m_bowLocation.m_row == 
				((numberOfRows - 3)))
				return false;
			if (player.m_ships[shipNumber].m_bowLocation.m_row == 
				((numberOfRows - 4)))
				return false;
		}
	} // end for 'V'
	if (player.m_ships[shipNumber].m_orientation == HORIZONTAL)
	{
		if (shipSize[shipNumber] == 2)
		{
			if (player.m_ships[shipNumber].m_bowLocation.m_col == 
				(numberOfCols - 1))
				return false;
		}
		if (shipSize[shipNumber] == 3)
		{
			if (player.m_ships[shipNumber].m_bowLocation.m_col == 
				(numberOfCols - 1))
				return false;
			if (player.m_ships[shipNumber].m_bowLocation.m_col == 
				(numberOfCols - 2))
				return false;
		}
		if (shipSize[shipNumber] == 4)
		{
			if (player.m_ships[shipNumber].m_bowLocation.m_col == 
				(numberOfCols - 1))
				return false;
			if (player.m_ships[shipNumber].m_bowLocation.m_col == 
				(numberOfCols - 2))
				return false;
			if (player.m_ships[shipNumber].m_bowLocation.m_col == 
				(numberOfCols - 3))
				return false;
		}
		if (shipSize[shipNumber] == 5)
		{
			if (player.m_ships[shipNumber].m_bowLocation.m_col == 
				(numberOfCols - 1))
				return false;
			if (player.m_ships[shipNumber].m_bowLocation.m_col == 
				(numberOfCols - 2))
				return false;
			if (player.m_ships[shipNumber].m_bowLocation.m_col == 
				(numberOfCols - 3))
				return false;
			if (player.m_ships[shipNumber].m_bowLocation.m_col == 
				(numberOfCols - 4))
				return false;
			}
	} // end for 'H'
	if (player.m_ships[shipNumber].m_orientation == HORIZONTAL)
	{
		int i = static_cast<int>(shipSize[shipNumber]);
		for (int x = 0; x < (i-1); x++)
		{
			if (player.m_gameGrid[0][player.m_ships[shipNumber].m_bowLocation.m_row]
			[player.m_ships[shipNumber].m_bowLocation.m_col + x] != NOSHIP)
				return false;
		}	
	}
	if (player.m_ships[shipNumber].m_orientation == VERTICAL)
	{
		int i = static_cast<int>(shipSize[shipNumber]);
		for (int x = 0; x < i; x++)
		{
			if (player.m_gameGrid[0][player.m_ships[shipNumber]
			.m_bowLocation.m_row + x][player.m_ships[shipNumber]
			.m_bowLocation.m_col] != NOSHIP)
				return false;
		}	
	}
	return true;
}

//---------------------------------------------------------------------------------
// Function:	header()
// Title:	header 
// Description:
//		Prints opening graphic
// Programmer:	Paul Bladek
//				Kyle Graham
//				Hang Nguyen
// 
// Date:	9/12/06
//
// Version:	1.0
// 
// Environment: Hardware: i3 
//              Software: OS: Windows 7; 
//              Compiles under Microsoft Visual C++ 2012
//
// Output:	
//
// Calls:	boxTop()
//		boxLine()
//		boxBottom()
//
// Called By:	main()
//
// Parameters:	sout: ostream&;	the stream to print to
// 
// Returns:	void
//
// History Log: 
//		9/12/06 PB comleted v 1.0
//		1/16/15 KG & HN completed v 0.2	
//     
//---------------------------------------------------------------------------------
void header(ostream& sout)
{
	const string empty;
	const string sink("SINK THE FLEET!");
	const string name("Kyle Graham & Hang Nguyen");	//our code
	const string by("Edmonds Community College CS 132");
	boxTop(sout, BOXWIDTH);
	boxLine(sout, empty, BOXWIDTH);
	boxLine(sout, sink , BOXWIDTH, 'C');
	boxLine(sout, empty, BOXWIDTH);
	boxLine(sout, name, BOXWIDTH, 'C'); // our code
	boxLine(sout, empty, BOXWIDTH);
	boxLine(sout, by, BOXWIDTH, 'C');
	boxLine(sout, empty, BOXWIDTH);
	boxBottom(sout, BOXWIDTH);
}

//---------------------------------------------------------------------------------
// Function:	endBox()
// Title:	End Box 
// Description:
//		prints closinging graphic
// Programmer:	Paul Bladek
// 
// Date:	9/12/06
//
// Version:	1.0
// 
// Environment: Hardware: i3 
//              Software: OS: Windows 7; 
//              Compiles under Microsoft Visual C++ 2012
//
// Output:	
//
// Calls:	boxTop()
//		boxLine()
//		boxBottom()
//
// Called By:	main()
//
// Parameters:	player: short; the number of the winner (0 or 1)
// 
// Returns:	void
//
// History Log: 
//		9/12/06 PB comleted v 1.0
//     
//---------------------------------------------------------------------------------
void endBox(short player)
{
	const string empty;
	ostringstream msg;
	msg << "Congratulations player " << player + 1 << "!";
	boxTop(cout, BOXWIDTH);
	boxLine(cout, empty, BOXWIDTH);
	boxLine(cout, msg.str() , BOXWIDTH, 'C');
	boxLine(cout, empty, BOXWIDTH);
	boxBottom(cout, BOXWIDTH);
}

