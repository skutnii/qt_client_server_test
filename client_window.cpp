/*
 * client_window.cpp
 *
 *  Created on: May 4, 2026
 *      Author: diamat
 */

#include "client_window.h"
#include "client_view_model.h"
#include <qboxlayout.h>
#include <qpushbutton.h>
#include <qt5/QtWidgets/qlineedit.h>

//==============================================================================

client_window::client_window(const client_view_model_ptr &view_model) :
		QWidget{}, m_view_model{view_model} {
	m_main_layout = new QVBoxLayout{};

	m_server_params_row = new QHBoxLayout{};
	m_main_layout->addLayout(m_server_params_row);

	m_address_input = new QLineEdit{this};
	m_address_input->setPlaceholderText("Server address...");
	m_server_params_row->addWidget(m_address_input);
	connect(m_address_input, &QLineEdit::textChanged, this,
					[this](const QString &text) { m_view_model->set_host(text); });

	m_port_input = new QLineEdit{this};
	m_port_input->setPlaceholderText("Server port (1234)");
	m_server_params_row->addWidget(m_port_input);
	connect(m_port_input, &QLineEdit::textChanged, this,
					[this](const QString &text) { m_view_model->set_port(text); });

	m_user_id_input = new QLineEdit{this};
	m_user_id_input->setPlaceholderText("User ID");
	m_main_layout->addWidget(m_user_id_input);
	connect(m_user_id_input, &QLineEdit::textChanged, this,
					[this](const QString &text) { m_view_model->set_id(text); });

	m_user_name_input = new QLineEdit{this};
	m_user_name_input->setPlaceholderText("User name");
	m_main_layout->addWidget(m_user_name_input);
	connect(m_user_name_input, &QLineEdit::textChanged, this,
					[this](const QString &text) { m_view_model->set_name(text); });

	m_user_email_input = new QLineEdit{this};
	m_user_email_input->setPlaceholderText("User email");
	m_main_layout->addWidget(m_user_email_input);
	connect(m_user_email_input, &QLineEdit::textChanged, this,
					[this](const QString &text) { m_view_model->set_email(text); });

	m_send = new QPushButton{"Send", this};
	m_main_layout->addWidget(m_send);
	connect(m_send, &QPushButton::clicked, this,
					[this]() { m_view_model->send(); });

	setLayout(m_main_layout);

	connect(view_model.get(), &client_view_model::enable_send_button, this,
					[this](bool enabled) { m_send->setEnabled(enabled); });

	view_model->update_ui();
}
