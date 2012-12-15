/*
 * Wimt.cpp
 *
 *  Created on: 14.12.2012
 *      Author: stefan
 */

#include <iostream>
#include <sstream>
#include <stdio.h>
#include <time.h>
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
	if (command.compare("add") == 0) {
			if (args.size() == 4) {
				time_t startTime = parseTime(args[0]);
				std::cout << "Start: " << args[0] << " in secs " << startTime << std::endl;
				time_t endTime = parseTime(args[1]);
				std::cout << "End: " << args[1] << " in secs " << endTime << std::endl;
				std::ostringstream stringStream;
				stringStream << "INSERT INTO entries VALUES (NULL, "
							 << startTime << ", " << endTime << ", "
							 <<	"\"" << args[2] << "\", \"" << args[3] << "\")";
				dbAccess->executeUpdate(stringStream.str());
			} else {
				std::cerr << "Not enough parameters." << std::endl;
				return 1;
			}
		} else if (command.compare("rm") == 0) {
			if (args.size() == 1) {
				dbAccess->executeUpdate("DELETE FROM entries WHERE id='" + args[0] + "'");
			} else {
				std::cerr << "Not enough parameters." << std::endl;
				return 1;
			}
		} else if (command.compare("list") == 0) {
			std::vector<Entry> entries = dbAccess->queryEntries("SELECT * FROM entries");
			printEntries(entries, dbAccess->getProjects());
		} else {
			std::cerr << "Unknown command '" << command << "'" << std::endl;
			return 1;
		}

		return 0;
}

int Wimt::handleTrackCommand(std::string command, std::vector<std::string> args) {
	return 1;
}

int Wimt::handleStatsCommand(std::string command, std::vector<std::string> args) {
	return 1;
}

time_t Wimt::parseTime(std::string timeStr) {
	struct tm time;
	sscanf(timeStr.c_str(), "%4d-%02d-%02d_%02d:%02d", &time.tm_year, &time.tm_mon,
			&time.tm_mday, &time.tm_hour, &time.tm_min);

	time.tm_year = time.tm_year - 1900;
	time.tm_mon = time.tm_mon - 1;
	time.tm_sec = 0;
	time.tm_isdst = 0;

	std::cout << "Parsed: Y=" << time.tm_year << ", M=" << time.tm_mon << ", D="
			<< time.tm_mday << ", H=" << time.tm_hour << ", m=" << time.tm_min
			<< std::endl;

	return mktime(&time);
}

std::string Wimt::formatTime(time_t time) {
	struct tm *ts;
	char buffer[256];
	ts = localtime(&time);
	sprintf(buffer, "%4d-%02d-%02d %02d:%02d", ts->tm_year + 1900, ts->tm_mon + 1,
			ts->tm_mday, ts->tm_hour, ts->tm_min);

	return std::string(buffer);
}

std::string Wimt::formatDuration(time_t duration) {
	char buffer[256];
	sprintf(buffer, "%02ld:%02ld", duration / 3600, (duration % 3600) / 60);

	return std::string(buffer);
}

void Wimt::printProjects(std::vector<Project>* projects) {
	char output[1024];
	sprintf(output, "%-3s   %-16s   %s", "Id", "Name", "Description");
	std::cout << output << std::endl;

	for(std::vector<Project>::iterator it = projects->begin(); it != projects->end(); ++it) {
		sprintf(output, "%-3d   %-16s   %s", it->get_id(), it->get_name().c_str(), it->get_description().c_str());
	    std::cout << output << std::endl;
	}
}

void Wimt::printEntries(std::vector<Entry>& entries, std::vector<Project>* projects) {
	char output[1024];
	sprintf(output, "%-3s   %-16s   %-16s   %-16s   %-16s   %s", "Id", "StartTime", "EndTime", "Duration", "Project", "Description");
	std::cout << output << std::endl;

	for(std::vector<Entry>::iterator it = entries.begin(); it != entries.end(); ++it) {
		std::string projName;
		for (std::vector<Project>::iterator it2 = projects->begin(); it2 != projects->end(); ++it2) {
			if (it->get_project_id() == it2->get_id()) {
				projName = it2->get_name();
			}
		}

		sprintf(output, "%-3d   %-16s   %-16s   %-16s   %-16s   %s",
				it->get_id(), formatTime(it->get_start_time()).c_str(),
				formatTime(it->get_end_time()).c_str(),
				formatDuration(it->get_duration()).c_str(), projName.c_str(),
				it->get_description().c_str());
	    std::cout << output << std::endl;
	}
}
