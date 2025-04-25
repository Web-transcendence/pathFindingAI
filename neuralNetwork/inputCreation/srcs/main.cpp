/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmouche <tmouche@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 17:25:52 by thibaud           #+#    #+#             */
/*   Updated: 2025/04/25 18:36:45 by tmouche          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vector>
#include <fstream>
#include <iostream>
#include "json.hpp"
#include <chrono>
#include <thread>
#include <cmath>
#include <array>

#define W 60
#define H 40
#define R 20

void printVector(const std::vector<std::vector<double>>& vec) {
    const int WIDTH = 60;

	std::cout << "\033[H"; // remet le curseur en haut à gauche
    for (size_t i = 0; i < vec.size(); ++i) {
        if (i % WIDTH == 0 && i != 0)
            std::cout << '\n';
        std::cout << std::setw(3) << std::fixed << std::setprecision(1) << 0.0;
    }
    std::cout << "\033[H"; // remet le curseur en haut à gauche
	for (auto it = vec.begin(); it != vec.end(); it++) {
		for (auto it_in = (*it).begin(); it_in != (*it).end(); it_in++) {
			if (*it_in != 0.)
            	std::cout << "\033[31m"; // rouge
        	else
            	std::cout << "\033[0m";  // reset couleur
        	std::cout << std::setw(3) << std::fixed << std::setprecision(1) << *it_in;
		}
		std::cout << '\n';
	}
    std::cout << "\033[0m" << std::flush; // reset couleur à la fin
}

void	paddle(std::vector<std::vector<double>> & simulation, std::array<int, 2> pxy) {
	int	size = 6;
	
	pxy[1] -= 3;
	while (size) {
		simulation.at(pxy[1]).at(pxy[0]) = 0.5;
		++pxy[1];
		--size;
	}
	return ;
}

void	lineDrag(std::vector<std::vector<double>> & simulation, std::array<int, 2> actxy, std::array<int, 2> oldxy) {
	int				diffX = std::abs(actxy[0] - oldxy[0]);
	int const		diffY = std::abs(actxy[1] - oldxy[1]);
	int const		direcX = actxy[0] < oldxy[0] ? 1 : -1;
	int const		direcY = actxy[1] < oldxy[1] ? 1 : -1;
	int	const		valuePerRow = diffY == 0 ? diffX : diffX / diffY;
	double const	offset = 1. / diffX;
	int				countValue = 0;
	double			value = 1.;
	// std::cout << "diff X" << diffX << std::endl;
	while (diffX > 0) {
		simulation.at(actxy[1]).at(actxy[0]) = value;
		if (countValue < valuePerRow) {
			actxy[0] += direcX;
			++countValue;
		} else {
			actxy[1] += direcY;
			countValue = 0;
		}
		value -= offset;
		--diffX;
	}
	return ;
}

std::vector<std::vector<std::vector<double>>*>*	parse(std::string const & inFile) {
	auto	simul = new std::vector<std::vector<std::vector<double>>*>(1000);

	std::ifstream	ifs(inFile.c_str());
	if (!ifs)
		throw std::exception();
	std::string	dataStr;
	std::getline(ifs, dataStr, '\0');	
	ifs.close();
	auto data = nlohmann::json::parse(dataStr);
	int		count = 0;
	std::array<int, 2>	lastIdx = {W/2, H/2};
	for (auto it = simul->begin(); it != simul->end(); it++, count += 3) {
		*it = new std::vector<std::vector<double> >(H, std::vector<double>(W));
		double x = data[count]["bx"];
		double y = data[count]["by"];
		std::array<int, 2>	idx = {static_cast<int>(x/R), static_cast<int>(y/R)};
		lineDrag(**it, idx, lastIdx);
		std::array<double, 4>	pCoord = {data[count]["rPx"], data[count]["rPy"], data[count]["lPx"], data[count]["lPy"]}; 
		paddle(**it, std::array<int, 2>{static_cast<int>(pCoord[0]/R), static_cast<int>(pCoord[1]/R)});
		paddle(**it, std::array<int, 2>{static_cast<int>(pCoord[2]/R), static_cast<int>(pCoord[3]/R)});
		lastIdx = {idx[0],idx[1]};
	} 
	return simul;
}

int	main( void ) {
	auto test = parse("gameState.json");
	int	count = 0;
	for (auto it = test->begin(); it != test->end(); it++, count++) {
		printVector(**it);
		std::this_thread::sleep_for(std::chrono::milliseconds(30)); // ~30 fps
		delete *it;
	}
	delete test;
	return 0;
}