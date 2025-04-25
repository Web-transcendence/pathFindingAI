/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thibaud <thibaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 17:25:52 by thibaud           #+#    #+#             */
/*   Updated: 2025/04/24 23:20:23 by thibaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vector>
#include <fstream>
#include <iostream>
#include "json.hpp"
#include <chrono>
#include <thread>
#include <cmath>

#define W 60
#define H 40

void printVector(const std::vector<double>& vec) {
    const int WIDTH = 60;

	std::cout << "\033[H"; // remet le curseur en haut à gauche
    for (size_t i = 0; i < vec.size(); ++i) {
        if (i % WIDTH == 0 && i != 0)
            std::cout << '\n';
        std::cout << std::setw(2) << std::fixed << std::setprecision(0) << 0.0;
    }
    std::cout << "\033[H"; // remet le curseur en haut à gauche
    for (size_t i = 0; i < vec.size(); ++i) {
        if (i % WIDTH == 0 && i != 0)
            std::cout << '\n';

        if (vec[i] == 1.0)
            std::cout << "\033[31m"; // rouge
        else
            std::cout << "\033[0m";  // reset couleur

        std::cout << std::setw(2) << std::fixed << std::setprecision(0) << vec[i];
    }
    std::cout << "\033[0m" << std::flush; // reset couleur à la fin
}

void	lineTraine(std::vector<double> & simulation, int act, int old) {
	simulation.at(act) = 1.0;
	simulation.at(old) = 1.0;
	unsigned int diffLine = std::abs(act / W - old / W);
	if (!diffLine) {
		if (act < old) {
			while (act < old) {
				simulation.at(act) = 1.0;
				++act;
			} 
		}
		else {
			while (act > old) {
				simulation.at(act) = 1.0;
				--act;
			}
		}
	}
	// else {
	// 	unsigned int diffCol = std::abs(act % W - old % W);
	// 	unsigned int littlePart = diffCol / diffLine;
	// 	if (act < old) {
	// 		while (act < old) {
	// 			simulation.at(act) = 1.0;
	// 			++act;
	// 		} 
	// 	}
	// 	else {
	// 		while (act > old) {
	// 			simulation.at(act) = 1.0;
	// 			--act;
	// 		}
	// 	}
	// }
}

std::vector<std::vector<double>*>*	parse(std::string const & inFile) {
	auto	simul = new std::vector<std::vector<double>*>(1000);

	std::ifstream	ifs(inFile.c_str());
	if (!ifs)
		throw std::exception();
	std::string	dataStr;
	std::getline(ifs, dataStr, '\0');	
	ifs.close();
	auto data = nlohmann::json::parse(dataStr);
	int		count = 0;
	unsigned int	last_idx = W*H/2;
	for (auto it = simul->begin(); it != simul->end(); it++, count++) {
		*it = new std::vector<double>(W*(H+1));
		double x = data[count]["bx"];
		double y = data[count]["by"];
		unsigned int idx = static_cast<unsigned int>((y/20)*60 + (x/20));
		lineTraine(**it, idx, last_idx);
		last_idx = idx;
	} 
	return simul;
}

int	main( void ) {
	auto test = parse("gameState.json");
	for (auto it = test->begin(); it != test->end(); it++) {
		printVector(**it);
		std::this_thread::sleep_for(std::chrono::milliseconds(100)); // ~30 fps
		delete *it;
	}
	delete test;
	return 0;
}