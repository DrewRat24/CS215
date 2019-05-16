//----------------------------------------------------------------------------
//                  CS 215 - Project 2 - MiniMud
//----------------------------------------------------------------------------
// Author:  
// Date:  
// Description:  
// Assistance: I received help from no one.I received help from no one.I received help from no one.I received help from no one.I received help from no one.I received help from no one.I received help from no one.I received help from no one.I received help from no one.I received help from no one.I received help from no one.I received help from no one.I received help from no one.I received help from no one.I received help from no one.I received help from no one.I received help from no one.I received help from no one.I received help from no one.I received help from no one.I received help from no one.I received help from no one.I received help from no one.I received help from no one.I received help from no one.I received help from no one.I received help from no one.I received help from no one.
// OR
// Assistance: I received help from the following:
//-----------------------------------------------------------
#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include "gameutils.h"
using namespace std;

//----------------------------------------------------------------------------
//                          printLogo
//----------------------------------------------------------------------------
void printLogo() {
	cout << "*---------------------------------*" << endl;
	cout << "|            Mini Mud             |" << endl;
	cout << "|          Drew Ratliff           |" << endl;
	cout << "*---------------------------------*" << endl;
} // printLogo()

//----------------------------------------------------------------------------
//                          getInputFileName
//----------------------------------------------------------------------------
string getInputFileName() {
	string gameName;
	cout << "Enter name of game to play: ";
	cin >> gameName;
	gameName = gameName + ".txt";
	return gameName;
} // getInputFileName()

//----------------------------------------------------------------------------
//                          initItems
//----------------------------------------------------------------------------
void initItems(item items[], int & numItems) {
	for (int i = 0; i < MAX_ITEMS; i++) {
		items[i].longDesc = "";
		items[i].shortDesc = "";
	}
	numItems = 0;
} // initItems()

//----------------------------------------------------------------------------
//                          initRooms
//----------------------------------------------------------------------------
void initRooms(room initRoom[MAX_ROOMS]) {
	for (int i = 0; i < MAX_ROOMS; i++) {
		initRoom[i].longDesc = "";
		initRoom[i].shortDesc = "";
		initRoom[i].east = NO_EXIT;
		initRoom[i].west = NO_EXIT;
		initRoom[i].north = NO_EXIT;
		initRoom[i].south = NO_EXIT;
		initItems(initRoom[i].items, initRoom[i].numItems);
	}
} // initRooms()

//----------------------------------------------------------------------------
//                          initWinData
//----------------------------------------------------------------------------
void initWinData(winDataStruct & winData) {
	winData.winMessage = "";
	winData.winRoom = NO_EXIT;
	initItems(winData.winItem, winData.numWinItems);
} // initWinData()

//----------------------------------------------------------------------------
//                          removeItem
//----------------------------------------------------------------------------
item removeItem(int index, int & numItems, item items[]) {
	item item_removed;
	if (index > (numItems - 1)) {
		gameAbort("removeItem: invalid index = " + index);
	}
	else {
		item_removed = items[index];
		items[index].longDesc = "";
		items[index].shortDesc = "";
		for (index; index < (numItems - 1); index++) {
			items[index] = items[index + 1];
			items[index + 1].shortDesc = "";
			items[index + 1].longDesc = "";
		}
		numItems--;
	}
	return item_removed;
} // removeItem()

//----------------------------------------------------------------------------
//                          addItem
//----------------------------------------------------------------------------
void addItem(item items, item item_array[], int & numItems) {
	if (numItems > MAX_ITEMS) {
		gameAbort("addItem: maximum number of items exceeded!");
	}
	else {
		for (int i = 0; i < MAX_ITEMS; i++) {
			if (item_array[i].shortDesc == "") {
				item_array[i].shortDesc = items.shortDesc;
				item_array[i].longDesc = items.longDesc;
				numItems++;
				i = MAX_ITEMS;
			}
		}
	}
} // addItem()

//----------------------------------------------------------------------------
//                          addItem (Overloaded)
//----------------------------------------------------------------------------
void addItem(string & shortDescription, string longDescription, item item_array[], int & numItems) {
	item items;
	items.longDesc = longDescription;
	items.shortDesc = shortDescription;
	addItem(items, item_array, numItems);
} // addItem()

//----------------------------------------------------------------------------
//							loadData
//----------------------------------------------------------------------------
void loadData(room rooms[], int & numRooms, winDataStruct & winData) {
	// variable declarations
	ifstream f;				// input file handle
	string tag;				// first word extracted from each line
	string filename;		// name of input file
	string data;			// data read from file using cleanGetline()
	int roomNdx = -1;		// index of the "current room" being read/populated
							// this should always be rumRooms-1 

	// initialize the rooms and winData
	initRooms(rooms);

	initWinData(winData);
	
	// get input file name and open the input file; abort on failure
	filename = getInputFileName();
	f.open(filename);
	if (f.fail()) gameAbort("Unable to open " + filename);

	// read line-by-line and store data in the game data structures
	f >> tag;
	while (tag != "END:") {
		if (tag == "ROOM:") {
			numRooms++;		// starting a new room
			roomNdx++;		// increment every time numRooms is incremented
			cleanGetline(f, rooms[roomNdx].shortDesc); // short desc on remainder of ROOM: line
			cleanGetline(f, rooms[roomNdx].longDesc);  // long desc on next line by itself (no tag)
		}
		else if (tag == "ITEM:") {
			string shortDesc, longDesc;
			cleanGetline(f, shortDesc);
			cleanGetline(f, longDesc);
			addItem(shortDesc, longDesc, rooms[roomNdx].items, rooms[roomNdx].numItems);
		}
		else if (tag == "WIN_ITEM:") {
			cleanGetline(f, data);
			addItem(data, "", winData.winItem, winData.numWinItems);
		}
		else if (tag == "NORTH:")
			f >> rooms[roomNdx].north;
		else if (tag == "SOUTH:")
			f >> rooms[roomNdx].south;
		else if (tag == "EAST:")
			f >> rooms[roomNdx].east;
		else if (tag == "WEST:")
			f >> rooms[roomNdx].west;
		else if (tag == "WIN_ROOM:")
			f >> winData.winRoom;
		else if (tag == "REMARK:")
			cleanGetline(f, data);		// data is junk, throw it away
		else if (tag == "WIN_TEXT:")
			cleanGetline(f, winData.winMessage);
		else if (tag == "END:");

		else
			gameAbort("Unknown tag in " + filename + ": " + tag);

		// check for read failure and read the next tag
		if (f.fail())
			gameAbort("Failure while reading input file " + filename);
		f >> tag;
	}
} // loadData()

//----------------------------------------------------------------------------
//                          getCmd
//----------------------------------------------------------------------------
string getCmd(string & remainder) {
	string input;
	cout << "===> ";
	if (cin.peek() == '\n') cin.ignore();
	getline(cin, input);
	input = split(input, remainder);
	return input;
} // getCmd()

//----------------------------------------------------------------------------
//							makeExitList
//----------------------------------------------------------------------------
string makeExitList(room thisRoom) {
	string exitList = "You can go:";
	if (thisRoom.north != NO_EXIT) exitList += " north,";
	if (thisRoom.south != NO_EXIT) exitList += " south,";
	if (thisRoom.east != NO_EXIT) exitList += " east,";
	if (thisRoom.west != NO_EXIT) exitList += " west.";
	exitList[exitList.length() - 1] = '.'; // change last comma to a period
	return exitList;
} // makeExitList()

//----------------------------------------------------------------------------
//                          doLook
//----------------------------------------------------------------------------
void doLook(room rooms, bool description) {
	if (description == true) cout << rooms.shortDesc << endl;
	else  cout << rooms.longDesc << endl;
	if (rooms.numItems > 0) {
		cout << "You notice the following: ";
		for (int i = 0; i < (rooms.numItems - 1); i++)		// for all but last item
			cout << rooms.items[i].shortDesc << ", ";			// print short desc with comma
		cout << rooms.items[rooms.numItems - 1].shortDesc << ".\n";  // for last item, use period and newline
	}
	cout << makeExitList(rooms) << endl;
} // doLook()

//----------------------------------------------------------------------------
//                          doLook (Overloaded)
//----------------------------------------------------------------------------
void doLook(room rooms) {
	doLook(rooms, false);
} // doLook()

//----------------------------------------------------------------------------
//                          startUp
//----------------------------------------------------------------------------
void startUp(item inventory[], room rooms[], winDataStruct winData) {
	printLogo();
	loadData(rooms, rooms->numItems, winData);
	initItems(rooms->items, rooms->numItems);
	cout << "You fall asleep and dream of a place far away..." << endl;
	doLook(rooms[START_ROOM], true);
} // startUp()

//----------------------------------------------------------------------------
//                          findItem
//----------------------------------------------------------------------------
int findItem(string search, item items[]) {
	for (int i = 0; i < MAX_ITEMS; i++) {
		if (search == items[i].shortDesc)
			return i;
	}
	return NOT_FOUND;
} // findItem()

//----------------------------------------------------------------------------
//                          doExamine
//----------------------------------------------------------------------------
void doExamine(string shortDescription, item room[], item inventory[]) {
	if (findItem(shortDescription, room) != NOT_FOUND) {
		cout << room->longDesc << endl;
	}
	else if (findItem(shortDescription, inventory) != NOT_FOUND)
		cout << inventory->longDesc << endl;
	else
		cout << "You see no " + shortDescription << endl;
} // doExamine()

//----------------------------------------------------------------------------
//                          doTake
//----------------------------------------------------------------------------
void doTake(string shortDescription, item room_item[], item inventory[], int & roomItems, int & invItems) {
	item items_catch;
	int itemStatus;
	itemStatus = findItem(shortDescription, room_item);

	if ((itemStatus != NOT_FOUND) && (invItems < MAX_ITEMS)) {
		items_catch = removeItem(itemStatus, roomItems, room_item);
		addItem(items_catch, inventory, invItems);
		cout << "You take the " << shortDescription << "." << endl;
	}
	else if ((itemStatus != NOT_FOUND) && (invItems >= MAX_ITEMS)) {
		cout << "Your hands are full, you can't take that." << endl;
	}
	else {
		if ((itemStatus) != NOT_FOUND) cout << "You already have the " + shortDescription << endl;
		else cout << "You see no " + shortDescription << endl;
	}
} // doTake()

//----------------------------------------------------------------------------
//                          doDrop
//----------------------------------------------------------------------------
void doDrop(string shortDescription, item room_item[], item inventory[], int & roomItems, int & invItems) {
	item items_catch;
	int itemStatus;
	itemStatus = findItem(shortDescription, inventory);

	if ((itemStatus != NOT_FOUND) && (roomItems < MAX_ITEMS)) {
		items_catch = removeItem(itemStatus, invItems, inventory);
		addItem(items_catch, room_item, roomItems);
		cout << "You drop the " << shortDescription << "." << endl;
	}
	else if ((itemStatus != NOT_FOUND) && (roomItems >= MAX_ITEMS)) {
		cout << "The room is full of junk; you can't drop that." << endl;
	}
	else {
		if ((itemStatus) != NOT_FOUND) cout << "You don't have the " + shortDescription << endl;
		else cout << "You have no " + shortDescription << endl;
	}
} // doDrop()

//----------------------------------------------------------------------------
//                          gameWon
//----------------------------------------------------------------------------
bool gameWon(winDataStruct winData, room rooms[]) {
	int found = 0;
	for (int i = 0; i < winData.numWinItems; i++) {
		if (findItem(winData.winItem[i].shortDesc, rooms[winData.winRoom].items) != NOT_FOUND) {
			found++;
		}
	}
	if (found == winData.numWinItems) 
		return true;
	else 
		return false;
	//Unfinished
} // gameWon()

//----------------------------------------------------------------------------
//							doInventory
//----------------------------------------------------------------------------
// Given: the player's inventory (partial array of items)
// This is the game's response to the "inv"/"i" (inventory) command.
// Prints a message telling the player what he/she is holding.
//----------------------------------------------------------------------------
void doInventory(item item[], int numItems) {
	if (numItems == 0)
		cout << "You don't have anything.\n";
	else {
		cout << "You are holding: ";
		for (int i = 0; i < (numItems - 1); i++)		// for all but last item
			cout << item[i].shortDesc << ", ";			// print short desc with comma
		cout << item[numItems - 1].shortDesc << ".\n";  // for last item, use period and newline
	}
} // doInventory()

//----------------------------------------------------------------------------
//							goNorth
//----------------------------------------------------------------------------
// Given:    partial array of rooms
// Modifies: index of current room
// This is the game's response to the player entering the "north"/"n" command.
// When the north exit exists, changes the current room index and performs
// a "look" command with a short room description
void goNorth(int & currentRoom, room rooms[]) {
	if (rooms[currentRoom].north == NO_EXIT)
		cout << "You can't go north.\n";
	else {
		currentRoom = rooms[currentRoom].north;
		doLook(rooms[currentRoom], true); // true = show short room desc.
	}
} // goNorth()

//----------------------------------------------------------------------------
//							goSouth
//----------------------------------------------------------------------------
// Given:    partial array of rooms
// Modifies: index of current room
// This is the game's response to the player entering the "south"/"n" command.
// When the north exit exists, changes the current room index and performs
// a "look" command with a short room description
void goSouth(int & currentRoom, room rooms[]) {
	if (rooms[currentRoom].south == NO_EXIT)
		cout << "You can't go south.\n";
	else {
		currentRoom = rooms[currentRoom].south;
		doLook(rooms[currentRoom], true); // true = show short room desc.
	}
} // goSouth()

//----------------------------------------------------------------------------
//							goWest
//----------------------------------------------------------------------------
// Given:    partial array of rooms
// Modifies: index of current room
// This is the game's response to the player entering the "west"/"n" command.
// When the north exit exists, changes the current room index and performs
// a "look" command with a short room description
void goWest(int & currentRoom, room rooms[]) {
	if (rooms[currentRoom].west == NO_EXIT)
		cout << "You can't go west.\n";
	else {
		currentRoom = rooms[currentRoom].west;
		doLook(rooms[currentRoom], true); // true = show short room desc.
	}
} // gowest()

//----------------------------------------------------------------------------
//							goEast
//----------------------------------------------------------------------------
// Given:    partial array of rooms
// Modifies: index of current room
// This is the game's response to the player entering the "east"/"n" command.
// When the north exit exists, changes the current room index and performs
// a "look" command with a short room description
void goEast(int & currentRoom, room rooms[]) {
	if (rooms[currentRoom].east == NO_EXIT)
		cout << "You can't go east.\n";
	else {
		currentRoom = rooms[currentRoom].east;
		doLook(rooms[currentRoom], true); // true = show short room desc.
	}
} // goEast()

//----------------------------------------------------------------------------
//							main
//----------------------------------------------------------------------------
int main() {
	// declare data structures
	item inventory[MAX_ITEMS];
	winDataStruct winData;
	room rooms[MAX_ROOMS];

	// declare other variables
	string cmd;					// command entered by user (first word of input)
	string remainder;			// remainder of command entered by user
	bool gameWasWon = false;	// check with gameWon() as needed
	int numRooms = 0, invItems=0; // number of rooms and inventory items
	int currentRoom = 0;		// current room

	// print the logo of the game
	printLogo();

	// start up: load game data from file and initialize player inventory
	loadData(rooms, numRooms, winData);
	initItems(inventory, invItems);

	// get first command input
	cmd = getCmd(remainder);

	// repeat until "exit" entered or the game is won
	while (cmd != "exit" && !gameWasWon) {
		if (cmd == "help")
			printHelp();

		else if (cmd == "look" || cmd == "l")
			doLook(rooms[currentRoom]);
		else if (cmd == "inv" || cmd == "i")
			doInventory(inventory, invItems);
		else if (cmd == "exa" || cmd == "x")
			doExamine(remainder, rooms[currentRoom].items, inventory);
		else if (cmd == "take" || cmd == "t")
			doTake(remainder, rooms[currentRoom].items, inventory, rooms[currentRoom].numItems, invItems);
		else if (cmd == "drop" || cmd == "d")
			doDrop(remainder, rooms[currentRoom].items, inventory, rooms[currentRoom].numItems, invItems);
		else if (cmd == "north" || cmd == "n") {
			goNorth(currentRoom, rooms);
		}
		else if (cmd == "south" || cmd == "s") {
			goSouth(currentRoom, rooms);
		}
		else if (cmd == "east" || cmd == "e") {
			goEast(currentRoom, rooms);
		}
		else if (cmd == "west" || cmd == "w") {
			goWest(currentRoom, rooms);
		}
		else if (cmd == "exit") {
			system("pause");
			return 0;
		}

		else // the user entered an unrecognized command
			cout << "What??\n";

		gameWasWon = gameWon(winData, rooms);

		// check if game was won and print win message or get next user input
		if (gameWasWon)
			cout << winData.winMessage << endl;
		else
			cmd = getCmd(remainder);
	}

	system("pause");
	return 0;
}
