/*
 * Wimt.cpp
 *
 *  Created on: 14.12.2012
 *      Author: stefan
 */

#include <iostream>
#include <sstream>
#include <stdio.h>
#include "../include/Wimt.h"

Wimt::Wimt(DatabaseAccess *dbAccess) {
	Wimt::dbAccess = dbAccess;
}

int Wimt::handleCommand(std::string category, std::string command, std::vector<std::string> args) {
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

int Wimt::handleProjectCommand(std::string command, std::vector<std::string> args) {
	if (command.compare("add") == 0) {
		if (args.size() == 2) {
			std::ostringstream stringStream;
			stringStream << "INSERT INTO projects VALUES (NULL, \""
						 << args[0] << "\", \"" << args[1] << "\")";
			dbAccess->executeUpdate(stringStream.str());
		} else {
			std::cerr << "Not enough parameters." << std::endl;
			return 1;
		}
	} else if (command.compare("rm") == 0) {
		if (args.size() == 1) {
			dbAccess->executeUpdate("DELETE FROM projects WHERE id='" + args[0] + "'");
		} else {
			std::cerr << "Not enough parameters." << std::endl;
			return 1;
		}
	} else if (command.compare("list") == 0) {
		std::vector<Project> *projects = dbAccess->getProjects();
		printProjects(projects);
	} else {
		std::cerr << "Unknown command '" << command << "'" << std::endl;
		return 1;
	}

	return 0;
}

int Wimt::handleEntryCommand(std::string command, std::vector<std::string> args) {
	return 1;
}

int Wimt::handleTrackCommand(std::string command, std::vector<std::string> args) {
	return 1;
}

int Wimt::handleStatsCommand(std::string command, std::vector<std::string> args) {
	return 1;
}

void Wimt::printProjects(std::vector<Project>* projects) {
	char output[1024];
	sprintf(output, "%-3s       %-32s       %-32s", "ID", "NAME", "DESCRIPTION");
	std::cout << std::endl << output << std::endl;
	sprintf(output, "%-3s       %-32s       %-32s", "--", "----", "-----------");
	std::cout << output << std::endl;

	for(std::vector<Project>::iterator it = projects->begin(); it != projects->end(); ++it) {
		sprintf(output, "%03d   |   %-32s   |   %-32s", it->get_id(), it->get_name().c_str(), it->get_description().c_str());
	    std::cout << output << std::endl;
	}

	std::cout << std::endl;
}

void Wimt::printEntries(std::vector<Entry> entries, std::vector<Project>* projects) {

}
