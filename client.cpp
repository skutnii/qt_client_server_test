/*
 * client.cpp
 *
 *  Created on: May 4, 2026
 *      Author: Sergii Kutnii
 */

#include <QApplication>
#include "client_view_model.h"
#include "client_window.h"

int main(int argc, char **argv) {
	QApplication app{argc, argv};
	client_window main_window{client_view_model_ptr::create()};
	main_window.show();
	app.exec();
	return 0;
}



