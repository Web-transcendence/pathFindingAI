/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thibaud <thibaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 15:41:00 by tmouche           #+#    #+#             */
/*   Updated: 2025/04/16 12:28:33 by thibaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Math.namespace.hpp"
#include "Client.class.hpp"

#include <iostream>
#include <string>
#include <chrono>



int	main( void ) {
	try {
		Client	c("test","weight.json");
		c.run();
	} catch (websocketpp::exception const & e) {
		std::cout << e.what() << std::endl;
	} catch ( ... ) {
		std::cout << "An unexpected exception" << std::endl;
	}
	return 0;
}
