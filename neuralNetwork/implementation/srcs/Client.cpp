/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thibaud <thibaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 14:55:53 by thibaud           #+#    #+#             */
/*   Updated: 2025/04/16 12:29:51 by thibaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Client.class.hpp"

#include "TypeDefinition.hpp"
#include "Network.class.hpp"

#include <chrono>
#include <sstream>
#include <exception>

char	_1[sizeof(double)*N_NEURON_INPUT]; //place holder input
double	_2[sizeof(double)*N_NEURON_OUTPUT]; //place holder output

Client::Client(std::string const & urlGame, std::string const & weightFile) {
	
	this->myNet = new Network(weightFile);
	this->c.init_asio();
	this->c.set_message_handler([this](websocketpp::connection_hdl hdl, client::message_ptr msg){this->on_message(hdl, msg);});
	websocketpp::lib::error_code	ec;
	this->gameServer = c.get_connection(urlGame, ec);
	if (ec) {
		std::cout << "Error: " << ec.message() << std::endl;
		throw std::exception();
	}
	c.connect(this->gameServer);
	return ;
}

Client::~Client( void ) {
	if (this->myNet)
		delete this->myNet;
	return ;
}

void	Client::on_message(websocketpp::connection_hdl hdl, client::message_ptr msg) {
	auto	data = nlohmann::json::parse(msg->get_payload());
	std::vector<double> input(N_NEURON_INPUT);
	
	input.at(0) = data[0]["Xb"];
	input.at(1) = data[0]["Yb"];
	input.at(2) = data[0]["Ob"];
	input.at(3) = data[0]["Ab"];
	auto	output = this->myNet->feedForward(input);
	memcpy(_1, output.data(), sizeof(double)*N_NEURON_INPUT);
	this->gameServer->send(_1, sizeof(double)*N_NEURON_INPUT);	
	(void)hdl;
	return ;
}

void	Client::run( void ) {this->c.run();}
void	Client::stop( void ) {this->c.stop();}