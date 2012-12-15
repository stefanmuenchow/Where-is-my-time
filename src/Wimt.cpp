/*
 * Wimt.cpp
 *
 *  Created on: 14.12.2012
 *      Author: stefan
 */

#include <iostream>
#include "../include/Wimt.h"

Wimt::Wimt(DatabaseAccess *dbAccess) {
	Wimt::dbAccess = dbAccess;
}

int Wimt::handleCommand(std::string category, std::string command, std::string args[]) {
	if (category.compare("project") == 0) {
		return handleProjectCommand(command, args);
	} else if (category.compare("entry") == 0) {
		return handleEntryCommand(command, args);
	} else if (category.compare("track") == 0) {
		return handleTrackCommand(command, args);
	} else if (category.compare("stats") == 0) {
		return handleStatsCommand(command, args);
	} else {
		std::cerr << "Unknown category '" << category << "'" << std::endl;
		return 1;
	}
}

int Wimt::handleProjectCommand(std::string command, std::string args[]) {
	if (command.compare("add") == 0) {
		dbAccess->executeUpdate("INSERT INTO projects (name) VALUES '" + args[0] + "'");
	} else if (command.compare("rem") == 0) {
		dbAccess->executeUpdate("DELETE FROM projects WHERE name='" + args[0] + "'");
	} else if (command.compare("list") == 0) {
		std::vector<std::string> projects = dbAccess->queryProjects("SELECT * FROM projects");
		printProjects(projects);
	} else {
		std::cerr << "Unknown command '" << command << "'" << std::endl;
		return 1;
	}

	return 0;
}

int Wimt::handleEntryCommand(std::string command, std::string args[]) {
	return 1;
}

int Wimt::handleTrackCommand(std::string command, std::string args[]) {
	return 1;
}

int Wimt::handleStatsCommand(std::string command, std::string args[]) {
	return 1;
}

void Wimt::printProjects(std::vector<std::string> projects) {

}

void Wimt::printEntries(std::vector<Entry> entries) {

}
