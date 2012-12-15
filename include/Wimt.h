/*
 * Wimt.h
 *
 *  Created on: 14.12.2012
 *      Author: stefan
 */

#ifndef WIMT_H_
#define WIMT_H_

#include <string>
#include "DatabaseAccess.h"

class Wimt {
private:
	DatabaseAccess *dbAccess;
	int handleProjectCommand(std::string command, std::vector<std::string> args);
	int handleEntryCommand(std::string command, std::vector<std::string> args);
	int handleTrackCommand(std::string command, std::vector<std::string> args);
	int handleStatsCommand(std::string command, std::vector<std::string> args);
	void printProjects(std::vector<Project>* projects);
	void printEntries(std::vector<Entry> entries, std::vector<Project>* projects);

public:
	Wimt(DatabaseAccess *dbAccess);
	int handleCommand(std::string category, std::string command, std::vector<std::string> args);
};

#endif /* WIMT_H_ */
