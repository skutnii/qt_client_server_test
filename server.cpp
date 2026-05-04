/*
 * server.cpp
 *
 *  Created on: May 4, 2026
 *      Author: Sergii Kutnii
 */

#include "server_app.h"
#include <iostream>
#include <qt5/QtCore/qchar.h>

//==============================================================================

static void print_usage() {
	std::cout << "Usage: test_app <port>" << std::endl;
}

//==============================================================================

int main(int argc, char **argv) {
	if (argc < 2) {
		print_usage();
		return 1;
	}

	bool port_ok;
	quint16 port = QString{argv[1]}.toUShort(&port_ok);
	if (!port_ok) {
		print_usage();
		return 1;
	}

	server_app app{port};
	app.run();
	return 0;
}


