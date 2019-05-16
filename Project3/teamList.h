#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

class team {
public:
	friend class teamList;
	team();
	void setID(string i);
	void setName(string n);
	void setCoach(string c);
	string getID();
	string getName();
	string getCoach();

private:
	string name, coach, teamID;
	team * next;
};

team::team() {
	teamID = ""; name = ""; coach = ""; next = NULL;
}// team(); Constructor

void team::setID(string i) {
	teamID = i;
}// setID();

void team::setName(string n) {
	name = n;
}// setName();

void team::setCoach(string c) {
	coach = c;
}// setCoach();

string team::getID() {
	return teamID;
}// getID();

string team::getName() {
	return name;
}// getName();

string team::getCoach() {
	return coach;
}// getCoach();

class teamList {
public:
	teamList();
	void addTeam(team o);
	void readData();
	void printTeams();
	team * getTeamRef(string x);
	int getNumTeams();
private:
	team * head;
};

teamList::teamList() {
	head = NULL;
}// teamList(); Constructor

void teamList::addTeam(team o) {
	team * t = new team;
	t->coach = o.coach;
	t->name = o.name;
	t->teamID = o.teamID;
	t->next = head;
	head = t;
}// addTeam();

void teamList::readData() {
	ifstream fin;
	team t;
	fin.open("teams.txt");
	while (!fin.eof()) {
		getline(fin, t.teamID);
		getline(fin, t.name);
		getline(fin, t.coach);
		addTeam(t);
	}
	fin.close();
}// readData();

void teamList::printTeams() {
	team * t = head;
	cout << endl;
	cout << "--------------------- TEAMS <" << getNumTeams() << "> -------------" << endl;
	cout << "TID   Team                       COACH" << endl;
	cout << "----  -------------------------  ------------" << endl;
	while (t != NULL) {
		cout << 
			setw(4) << left << t->teamID << "  " <<
			setw(25) << left << t->name << "  " <<
			setw(20) << left << t->coach << endl;
		t = t->next;
	}
}// printTeams();

team * teamList::getTeamRef(string x) {
	team * t = head;
	while (t != NULL) {
		if (t->teamID == x)
			return t;
		else
			t = t->next;
	}
	return NULL;
}// getTeamRef();

int teamList::getNumTeams() {
	team * t = head;
	int total=0;
	while (t != NULL) {
		total++;
		t = t->next;
	}
	if (total > 0)
		return total;
	else
		return 0;
}// getNumTeams();