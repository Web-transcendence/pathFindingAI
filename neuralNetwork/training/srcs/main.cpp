/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thibaud <thibaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 15:36:53 by thibaud           #+#    #+#             */
/*   Updated: 2025/04/16 11:49:40 by thibaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Network.class.hpp"
#include "json.hpp"
#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <exception>

std::array<std::vector<t_tuple*>*, 2>	parse(std::string const & inFile) {
	auto	trainingData = new std::vector<t_tuple*>(50000);
	auto	testingData = new std::vector<t_tuple*>(10000);

	std::ifstream	ifs(inFile.c_str());
	if (!ifs)
		throw std::exception();
	std::string	dataStr;
	std::getline(ifs, dataStr, '\0');	
	ifs.close();
	auto data = nlohmann::json::parse(dataStr);
	int		count = 0;
	for (auto it = trainingData->begin(); it + 1 != trainingData->end(); it++, count++) {
		*it = new t_tuple;
		(*it)->input[0] = data[count]["Xb"];
		(*it)->input[1] = data[count]["Yb"];
		(*it)->input[2] = data[count]["Ob"];
		(*it)->input[3] = data[count]["Ab"];
		(*it)->expectedOutput[0] = data[count + 1]["Xb"];
		(*it)->expectedOutput[1] = data[count + 1]["Yb"];
		(*it)->expectedOutput[2] = data[count + 1]["Ob"];
		(*it)->expectedOutput[3] = data[count + 1]["Ab"];
	}
	for (auto it = testingData->begin(); it + 1 != testingData->end(); it++, count++) {
		*it = new t_tuple;
		(*it)->input[0] = data[count]["Xb"];
		(*it)->input[1] = data[count]["Yb"];
		(*it)->input[2] = data[count]["Ob"];
		(*it)->input[3] = data[count]["Ab"];
		(*it)->expectedOutput[0] = data[count + 1]["Xb"];
		(*it)->expectedOutput[1] = data[count + 1]["Yb"];
		(*it)->expectedOutput[2] = data[count + 1]["Ob"];
		(*it)->expectedOutput[3] = data[count + 1]["Ab"];
	}
	return std::array<std::vector<t_tuple*>*, 2>{trainingData, testingData};
}

int main( void ) {
	std::vector<unsigned int>	net = {16,50,50,4};
	Network						trainingNetwork(net, SIGMOID, SIGMOID);

	auto	dataset = parse("parsing.json");
	std::cout << std::endl << "=== TRAINING NETWORK ===" << std::endl;
	trainingNetwork.SDG(*dataset[0], 10, 10, 3.0, dataset[1]);
	trainingNetwork.printNetworkToJson("weights.json");
	std::cout << std::endl << "=== TESTING ===" << std::endl;
	std::cout << "nothing" << std::endl;
	return 0;
}
