/*
 * Wimt.cpp
 *
 *  Created on: 14.12.2012
 *      Author: stefan
 */

#include "../include/Wimt.h"

Wimt::Wimt(DatabaseAccess *dbAccess) {
	Wimt::dbAccess = dbAccess;
}

Wimt::~Wimt() {
}

int Wimt::handleCommand(std::string category, std::string command, std::string args[]) {
	return -1;
}
