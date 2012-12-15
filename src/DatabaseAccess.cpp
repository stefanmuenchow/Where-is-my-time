/*
 * DatabaseAccess.cpp
 *
 *  Created on: 14.12.2012
 *      Author: stefan
 */

#include "../include/DatabaseAccess.h"
#include <iostream>
#include <stdlib.h>


static int projectsCallback(void *resultVector, int numResults, char **values, char **colNames) {
	std::vector<Project> *projectResults =  (std::vector<Project>*) resultVector;
	int projId = atoi(values[0]);
	Project project = Project(projId, values[1], values[2]);
	projectResults->push_back(project);

	return 0;
}

static int entriesCallback(void *resultVector, int numResults, char **values, char **colNames) {
	std::vector<Entry> *entryResults =  (std::vector<Entry>*) resultVector;
	int entryId = atoi(values[0]);
	time_t startTime = atol(values[1]);
	time_t endTime = atol(values[2]);
	int projId = atoi(values[3]);
	Entry entry = Entry(entryId, startTime, endTime, projId, values[4]);
	entryResults->push_back(entry);

	return 0;
}


DatabaseAccess::DatabaseAccess(std::string dbName) {
	// Establish database connection
	int rc;
	rc = sqlite3_open(dbName.c_str(), &dataBase);

	if (rc) {
		std::cerr << "Can't open database: " << sqlite3_errmsg(dataBase) << std::endl;
		sqlite3_close(dataBase);
	}

	// Initialize vectors
	projects = std::vector<Project>();
	executeQuery("SELECT * FROM projects", projectsCallback, &projects);
	entries = std::vector<Entry>();
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

std::vector<Project>* DatabaseAccess::getProjects() {
	return &projects;
}

std::vector<Entry> DatabaseAccess::queryEntries(std::string stmt) {
	executeQuery(stmt, entriesCallback, &entries);
	return entries;
}

void DatabaseAccess::executeUpdate(std::string stmt) {
	executeQuery(stmt, NULL, NULL);
}
