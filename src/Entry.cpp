/*
 * Entry.cpp
 *
 *  Created on: 14.12.2012
 *      Author: stefan
 */

#include "../include/Entry.h"

Entry::Entry(int id, time_t startTime, time_t endTime, int projectId, std::string description) {
	Entry::id = id;
	Entry::startTime = startTime;
	Entry::endTime = endTime;
	Entry::projectId = projectId;
	Entry::description = description;
}

int Entry::get_id() {
	return id;
}

time_t Entry::get_start_time() {
	return startTime;
}

time_t Entry::get_end_time() {
	return endTime;
}

time_t Entry::get_duration() {
	return endTime - startTime;
}

int Entry::get_project_id() {
	return projectId;
}

std::string Entry::get_description() {
	return description;
}
