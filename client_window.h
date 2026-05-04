/*
 * client_window.h
 *
 *  Created on: May 4, 2026
 *      Author: diamat
 */

#ifndef CLIENT_WINDOW_H_
#define CLIENT_WINDOW_H_

#include <QWidget>
#include <QBoxLayout>
#include <QLineEdit>
#include <QPushButton>
#include "client_view_model.h"

/**
 * Client UI.
 */
class client_window : public QWidget {
	Q_OBJECT
public:
	/**
	 * Initialize with a view model
	 */
	client_window(const client_view_model_ptr &view_model);
	virtual ~client_window() = default;
private:
	client_view_model_ptr m_view_model;

	QVBoxLayout *m_main_layout;
	
	QHBoxLayout *m_server_params_row;
	QLineEdit *m_address_input;
	QLineEdit *m_port_input;

	QLineEdit *m_user_id_input;
	QLineEdit *m_user_name_input;
	QLineEdit *m_user_email_input;
	QPushButton * m_send;
};

#endif /* CLIENT_WINDOW_H_ */
