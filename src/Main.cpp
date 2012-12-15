//============================================================================
// Name        : Main.cpp
// Author      : Stefan Münchow
// Version     :
// Copyright   : (C)2012 Stefan Münchow
//============================================================================

#include <iostream>
#include <stdio.h>
#include <string.h>
#include "../include/sqlite3.h"

#include "../include/DatabaseAccess.h"
#include "../include/Wimt.h"

using namespace std;

static string USAGE = string(
		"USAGE:\n"
		"  project add <projectName> <description>\n"
		"  project rm  <projectId>\n"
		"  project list\n\n"
		"  entry add <startTime> <endTime> <projectName> <description>\n"
		"  entry rm  <startTime> <endTime> <projectName>\n"
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
	if (argc >= 3) {
		paramCommand = string(argv[2]);
	}

	vector<string> paramArgs = vector<string>();
	int i;
	for (i = 0; (i + 3) < argc; i++) {
		if (strlen(argv[i + 3]) != 0) {
			paramArgs.push_back(argv[i + 3]);
		}
	}

	// Start main class with given params
	DatabaseAccess dbAccess = DatabaseAccess(DB_NAME);
	Wimt wimt = Wimt(&dbAccess);
	return wimt.handleCommand(paramCategory, paramCommand, paramArgs);
}
