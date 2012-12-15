/*
 * Project.h
 *
 *  Created on: 15.12.2012
 *      Author: stefan
 */

#ifndef PROJECT_H_
#define PROJECT_H_

#include <string>

class Project {
private:
	int id;
	std::string name;
	std::string description;

public:
	Project(int id);
	Project(int id, std::string name, std::string description);

	int get_id();
	std::string get_name();
	std::string get_description();
};

#endif /* PROJECT_H_ */
