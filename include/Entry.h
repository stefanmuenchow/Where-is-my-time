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

class Entry {
private:
	time_t startTime;
	time_t endTime;
	std::string projectName;
	std::string description;

public:
	Entry(time_t startTime, time_t endTime, std::string projectName, std::string description);

	time_t get_start_time();
	time_t get_end_time();
	double get_duration();
	std::string get_project_name();
	std::string get_description();
};

#endif /* ENTRY_H_ */
