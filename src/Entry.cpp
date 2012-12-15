/*
 * Entry.cpp
 *
 *  Created on: 14.12.2012
 *      Author: stefan
 */

#include "../include/Entry.h"

Entry::Entry(time_t startTime, time_t endTime, std::string projectName, std::string description) {
	Entry::startTime = startTime;
	Entry::endTime = endTime;
	Entry::projectName = projectName;
	Entry::description = description;
}

time_t Entry::get_start_time() {
	return startTime;
}

time_t Entry::get_end_time() {
	return endTime;
}

double Entry::get_duration() {
	return difftime(endTime, startTime);
}

std::string Entry::get_project_name() {
	return projectName;
}

std::string Entry::get_description() {
	return description;
}
