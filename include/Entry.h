/*
 * Entry.h
 *
 *  Created on: 14.12.2012
 *      Author: stefan
 */

#ifndef ENTRY_H_
#define ENTRY_H_

#include <string>
#include <time.h>
#include "../include/Project.h"

class Entry {
private:
	int id;
	time_t startTime;
	time_t endTime;
	int projectId;
	std::string description;

public:
	Entry(int id, time_t startTime, time_t endTime, int projectId, std::string description);

	int get_id();
	time_t get_start_time();
	time_t get_end_time();
	time_t get_duration();
	int get_project_id();
	std::string get_description();
};

#endif /* ENTRY_H_ */
