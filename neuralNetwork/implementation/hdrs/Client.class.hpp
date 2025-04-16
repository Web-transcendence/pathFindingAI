/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.class.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thibaud <thibaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 09:46:47 by thibaud           #+#    #+#             */
/*   Updated: 2025/04/16 12:28:53 by thibaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_CLASS_HPP
# define CLIENT_CLASS_HPP

#include <websocketpp/config/asio_no_tls_client.hpp>
#include <websocketpp/client.hpp>

#include "../../third-party/json.hpp"

#include <vector>

typedef websocketpp::client<websocketpp::config::asio_client>	client;
typedef std::shared_ptr<websocketpp::connection<websocketpp::config::asio_client>>	server_ptr;

class Network;

class Client {
public:
	Client(std::string const & urlGame, std::string const & weightFile);
	~Client( void );
	
	void	run( void );

private:
	Client( void );
	
	void	on_message(websocketpp::connection_hdl hdl, client::message_ptr msg);

	void	stop( void );
	
	Network*	myNet;

	client	c;

	server_ptr	gameServer;

};


#endif
