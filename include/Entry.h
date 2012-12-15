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
	virtual ~Entry();
};

#endif /* ENTRY_H_ */
