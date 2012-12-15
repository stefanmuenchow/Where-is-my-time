/*
 * Wimt.h
 *
 *  Created on: 14.12.2012
 *      Author: stefan
 */

#ifndef WIMT_H_
#define WIMT_H_

#include <string>
#include "DatabaseAccess.h"

class Wimt {
private:
	DatabaseAccess *dbAccess;
public:
	Wimt(DatabaseAccess *dbAccess);
	virtual ~Wimt();

	int handleCommand(std::string category, std::string command, std::string args[]);
};

#endif /* WIMT_H_ */
