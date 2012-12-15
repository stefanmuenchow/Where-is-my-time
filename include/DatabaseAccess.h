/*
 * DatabaseAccess.h
 *
 *  Created on: 14.12.2012
 *      Author: stefan
 */

#ifndef DATABASEACCESS_H_
#define DATABASEACCESS_H_

#include <string>
#include <vector>
#include "sqlite3.h"
#include "Entry.h"

class DatabaseAccess {
private:
	sqlite3 *dataBase;
	std::vector<Project> projects;
	std::vector<Entry> entries;
	void executeQuery(std::string stmt, sqlite3_callback callback, void *resultVector);

public:
	DatabaseAccess(std::string dbName);
	virtual ~DatabaseAccess();
	std::vector<Project>* getProjects();
	std::vector<Entry> queryEntries(std::string stmt);
	void executeUpdate(std::string stmt);
};

#endif /* DATABASEACCESS_H_ */
