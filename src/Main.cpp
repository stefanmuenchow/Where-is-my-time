//============================================================================
// Name        : Main.cpp
// Author      : Stefan Münchow
// Version     :
// Copyright   : (C)2012 Stefan Münchow
//============================================================================

#include <iostream>
#include <stdio.h>
#include "../include/sqlite3.h"

#include "../include/DatabaseAccess.h"
#include "../include/Wimt.h"

using namespace std;

static string USAGE = string(
		"USAGE:\n"
		"  project add <projectName>\n"
		"  project rem <projectName>\n"
		"  project list\n\n"
		"  entry add <startTime> <endTime> <projectName> <description>\n"
		"  entry rem <startTime> <endTime> <projectName>\n"
		"  entry list [<startTime> <endTime>]\n"
		"  entry list <projectName> [<startTime> <endTime>]\n\n"
		"  track start <projectName>\n"
		"  track stop <projectName> <description>\n\n"
		"  stats [show | export] [<startTime> <endTime>]\n"
		"  stats [show | export] <projectName> [<startTime> <endTime>]\n\n"
		"  help\n");

static string DB_NAME = "wimt.db";

int main(int argc, char** argv) {
	// Parse command line args and store in variables
	if (argc == 1) {
		cout << USAGE << endl;
		return 0;
	}

	string paramCategory = string(argv[1]);
	string paramCommand;
	string paramArgs[4]= { "\0", "\0", "\0", "\0" };

	if (argc >= 3) {
		paramCommand = string(argv[2]);
	}

	int i;
	for (i = 0; (i + 3) < argc; i++) {
		paramArgs[i] = string(argv[i + 3]);
	}

	cout << paramCategory << endl;
	cout << paramCommand << endl;
	for (i = 0; i < 4; i++) {
		cout << paramArgs[i] << endl;
	}

	// Start main class with given params
	DatabaseAccess dbAccess = DatabaseAccess(DB_NAME);
	Wimt wimt = Wimt(&dbAccess);
	return wimt.handleCommand(paramCategory, paramCommand, paramArgs);
}
