#pragma once
#include "teamList.h"
#include <iomanip>

class game {
public:
	friend class gameList;
	game();
	void setMembers(string d, int sc1, int sc2, team * p1, team * p2);
	string getDate();
	int getScore1();
	int getScore2();
	team * getPointer1();
	team * getPointer2();

private:
	string date;
	int score1, score2;
	team * teamPointer1;
	team * teamPointer2;
	game * next;
};

//-------------------------------------------------------------------------
//						   	game (Constructor)
//-------------------------------------------------------------------------
game::game() {
	date = ""; score1 = 0; score2 = 0; teamPointer1 = NULL; 
	teamPointer2 = NULL; next = NULL;
}// game() Constructor

//-------------------------------------------------------------------------
//								setMembers
//-------------------------------------------------------------------------
void game::setMembers(string d, int sc1, int sc2, team * p1, team * p2) {
	date = d; score1 = sc1; score2 = sc2; teamPointer1 = p1; teamPointer2 = p2;
}// setMembers()

//-------------------------------------------------------------------------
//								getDate
//-------------------------------------------------------------------------
string game::getDate() {
	return date;
}// getDate()

//-------------------------------------------------------------------------
//								getScore1
//-------------------------------------------------------------------------
int game::getScore1() {
	return score1;
}// getScore1()

//-------------------------------------------------------------------------
//								getScore2
//-------------------------------------------------------------------------
int game::getScore2() {
	return score2;
}// getScore2()

//-------------------------------------------------------------------------
//								getPointer1
//-------------------------------------------------------------------------
team * game::getPointer1() {
	return teamPointer1;
}// getPointer1()

//-------------------------------------------------------------------------
//								getPointer2
//-------------------------------------------------------------------------
team * game::getPointer2() {
	return teamPointer2;
}// getPointer2()

class gameList {
public:
	gameList();
	void addGame(game g);
	void readGames(teamList t);
	int getNumGames();
	int getNumWins(team * t);
	int getNumLoses(team * t);
	void printGames(team * t);
	void writeGames();
private:
	game * head;
	game * tail;
};

//-------------------------------------------------------------------------
//                          gameList (Contructor)
//-------------------------------------------------------------------------
gameList::gameList() {
	head = NULL; tail = NULL;
}// gameList() Contructor

//-------------------------------------------------------------------------
//                               addGame
//-------------------------------------------------------------------------
void gameList::addGame(game g) {
	game * n = new game;
	n->date = g.date;
	n->score1 = g.score1;
	n->score2 = g.score2;
	n->teamPointer1 = g.teamPointer1;
	n->teamPointer2 = g.teamPointer2;
	n->next = tail;
	tail = n;
}// addGame()

//-------------------------------------------------------------------------
//                               readGames
//-------------------------------------------------------------------------
void gameList::readGames(teamList t) {
	ifstream fin;
	game g;
	fin.open("games.txt");
	if (fin.fail()) {
		cout << "gameList::readGames: unable to open games.txt" << endl;
		abort();
	}
	while (!fin.eof()) {
		string ID1, ID2;
		fin >> g.date;
		fin >> ID1;
		g.teamPointer1 = t.getTeamRef(ID1);
		fin >> g.score1;
		fin >> ID2;
		g.teamPointer2 = t.getTeamRef(ID2);
		fin >> g.score2;

		if (t.getTeamRef(ID1) == NULL) {
			cout << "gameList::read: invalid team id 1/2 = " + ID1; 
			abort();
		}
		else if (t.getTeamRef(ID2) == NULL) {
			cout << "gameList::read: invalid team id 1/2 = " + ID2;
			abort();
		}
		addGame(g);
	}
	fin.close();
}// readGames()

//-------------------------------------------------------------------------
//                               getNumGames
//-------------------------------------------------------------------------
int gameList::getNumGames() {
	game * g = tail;
	int total = 0;
	while (g != NULL) {
		total++;
		if (g->next == NULL)
			head = tail;
		g = g->next;
	}
	if (total > 0)
		return total;
	else
		return 0;
}// getNumGames()

//-------------------------------------------------------------------------
//                               getNumWins
//-------------------------------------------------------------------------
int gameList::getNumWins(team * t) {
	game * g = tail;
	int wins=0;
	while (g != NULL) {
		if (t == g->teamPointer1) {
			if (g->score1 > g->score2) {
				wins++;
			}
		}
		else if (t == g->teamPointer2) {
			if (g->score2 > g->score1) {
				wins++;
			}
		}
		g = g->next;
	}
	return wins;
}// getNumWins()

//-------------------------------------------------------------------------
//                               getNumLoses
//-------------------------------------------------------------------------
int gameList::getNumLoses(team * t) {
	game * g = tail;
	int losses=0;
	while (g != NULL) {
		if (t == g->teamPointer1) {
			if (g->score1 < g->score2) {
				losses++;
			}
		}
		else if (t == g->teamPointer2) {
			if (g->score2 < g->score1) {
				losses++;
			}
		}
		g = g->next;
	}
	return losses;
}// getNumLoses()

//-------------------------------------------------------------------------
//                               printGames
//-------------------------------------------------------------------------
void gameList::printGames(team * t) {
	game * g = tail;
	cout << endl;
	if (t == NULL) {
		cout << "---------- GAMES <" << getNumGames() << "> ----------" << endl;
		cout << "DATE        TEAM  SC   TEAM  SC " << endl;
		cout << "----------  ----  ---  ----  ---" << endl;
		while (g != NULL) {
			cout << 
				setw(10) << left << g->getDate() << "  " << 
				setw(4) << left << g->teamPointer1->getID() << "  " << 
				setw(3) << right << g->getScore1() << "  " <<
				setw(4) << left << g->teamPointer2->getID() << "  " <<
				setw(3) << right << g->getScore2() << endl;
			g = g->next;
		}
	}
	else if (t != NULL) {
		cout << "---------- GAMES <" << (getNumLoses(t) + getNumWins(t)) << "> ----------" << endl;
		cout << "DATE        TEAM  SC   TEAM  SC " << endl;
		cout << "----------  ----  ---  ----  ---" << endl;
		while (g != NULL) {
			if (g->teamPointer1 == t || g->teamPointer2 == t) {
				cout <<
					setw(10) << left << g->getDate() << "  " <<
					setw(4) << left << g->teamPointer1->getID() << "  " <<
					setw(3) << right << g->getScore1() << "  " <<
					setw(4) << left << g->teamPointer2->getID() << "  " <<
					setw(3) << right << g->getScore2() << endl;
			}
			g = g->next;
		}
	}
}// printGames()

//-------------------------------------------------------------------------
//                               writeGames
//-------------------------------------------------------------------------
void gameList::writeGames() {
	ofstream fout;
	game * g = head;
	fout.open("games2.txt");
	while (g != NULL) {
		fout <<
			setw(10) << left << g->date << " " <<
			setw(4) << left << g->teamPointer1->getID() << " " <<
			setw(3) << right << g->score1 << " " <<
			setw(4) << left << g->teamPointer2->getID() << " " <<
			setw(3) << right << g->score2 << endl;
		g = g->next;
	}
	fout.close();
}// writeGames()