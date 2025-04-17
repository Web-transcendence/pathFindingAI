/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thibaud <thibaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 15:36:53 by thibaud           #+#    #+#             */
/*   Updated: 2025/04/17 16:38:02 by thibaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Network.class.hpp"
#include "json.hpp"
#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <exception>

double	remap(double x) {
	return ((x+1.)/2.);
}

std::array<std::vector<t_tuple*>*, 2>	parse(std::string const & inFile) {
	auto	trainingData = new std::vector<t_tuple*>(40000);
	auto	testingData = new std::vector<t_tuple*>(10000);

	std::ifstream	ifs(inFile.c_str());
	if (!ifs)
		throw std::exception();
	std::string	dataStr;
	std::getline(ifs, dataStr, '\0');	
	ifs.close();
	auto data = nlohmann::json::parse(dataStr);
	int		count = 0;
	for (auto it = trainingData->begin(); it != trainingData->end(); it++, count++) {
		*it = new t_tuple;
		(*it)->input[0] = remap(data[count]["x"]);
		(*it)->input[1] = remap(data[count]["y"]);
		(*it)->input[2] = remap(data[count]["angle"]);
		(*it)->expectedOutput[0] = remap(data[count + 1]["x"]);
		(*it)->expectedOutput[1] = remap(data[count + 1]["y"]);
		(*it)->expectedOutput[2] = remap(data[count + 1]["angle"]);
	}
	for (auto it = testingData->begin(); it != testingData->end(); it++, count++) {
		*it = new t_tuple;
		(*it)->input[0] = remap(data[count]["x"]);
		(*it)->input[1] = remap(data[count]["y"]);
		(*it)->input[2] = remap(data[count]["angle"]);
		(*it)->expectedOutput[0] = remap(data[count + 1]["x"]);
		(*it)->expectedOutput[1] = remap(data[count + 1]["y"]);
		(*it)->expectedOutput[2] = remap(data[count + 1]["angle"]);
	}
	return std::array<std::vector<t_tuple*>*, 2>{trainingData, testingData};
}

int main( void ) {
	std::vector<unsigned int>	net = {4,32,32,4};
	Network						trainingNetwork(net, SIGMOID, SIGMOID);

	auto	dataset = parse("parsing.json");
	std::cout << std::endl << "=== TRAINING NETWORK ===" << std::endl;
	trainingNetwork.SDG(*dataset[0], 10, 50, 5., dataset[1]);
	trainingNetwork.printNetworkToJson("weights.json");
	std::cout << std::endl << "=== TESTING ===" << std::endl;
	std::cout << "nothing" << std::endl;
	return 0;
}
