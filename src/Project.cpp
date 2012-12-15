/*
 * Project.cpp
 *
 *  Created on: 15.12.2012
 *      Author: stefan
 */

#include "../include/Project.h"

Project::Project(int id, std::string name, std::string description) {
	Project::id = id;
	Project::name = name;
	Project::description = description;
}

Project::Project(int id) {
	Project(id, NULL, NULL);
}

int Project::get_id() {
	return id;
}

std::string Project::get_name() {
	return name;
}

std::string Project::get_description() {
	return description;
}

