/*
 * DatabaseAccess.cpp
 *
 *  Created on: 14.12.2012
 *      Author: stefan
 */

#include "../include/DatabaseAccess.h"
#include <iostream>
#include <stdlib.h>

DatabaseAccess::DatabaseAccess(std::string dbName) {
	// Establish database connection
	int rc;
	rc = sqlite3_open(dbName.c_str(), &dataBase);

	if (rc) {
		std::cerr << "Can't open database: " << sqlite3_errmsg(dataBase) << std::endl;
		sqlite3_close(dataBase);
	}

	// Initialize vectors
	projectResults = std::vector<std::string>();
	entryResults = std::vector<Entry>();
}

DatabaseAccess::~DatabaseAccess() {
	sqlite3_close(dataBase);
}

void DatabaseAccess::executeQuery(std::string stmt, sqlite3_callback callback, void *resultVector) {
	int rc;
	char *errMsg = '\0';
	rc = sqlite3_exec(dataBase, stmt.c_str(), callback, resultVector, &errMsg);

	if (rc != SQLITE_OK) {
		std::cerr << "SQL error: " << errMsg << std::endl;
		sqlite3_free(errMsg);
	}
}

static int projectsCallback(void *resultVector, int numResults, char **values, char **colNames) {
	std::vector<std::string> *projectResults =  (std::vector<std::string>*) resultVector;
	projectResults->clear();
	projectResults->push_back(values[1]);

	return 0;
}

static int entriesCallback(void *resultVector, int numResults, char **values, char **colNames) {
	std::vector<Entry> *entryResults =  (std::vector<Entry>*) resultVector;
	entryResults->clear();
	time_t startTime = atoi(values[1]);
	time_t endTime = atoi(values[2]);

	Entry entry = Entry(startTime, endTime, values[3], values[4]);
	entryResults->push_back(entry);

	return 0;
}

std::vector<std::string> DatabaseAccess::queryProjects(std::string stmt) {
	executeQuery(stmt, projectsCallback, &projectResults);
	return std::vector<std::string>(projectResults);
}

std::vector<Entry> DatabaseAccess::queryEntries(std::string stmt) {
	executeQuery(stmt, entriesCallback, &entryResults);
	return std::vector<Entry>(entryResults);
}

void DatabaseAccess::executeUpdate(std::string stmt) {
	executeQuery(stmt, NULL, NULL);
}
