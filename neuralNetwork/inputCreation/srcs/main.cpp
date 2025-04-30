/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmouche <tmouche@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 17:25:52 by thibaud           #+#    #+#             */
/*   Updated: 2025/04/30 21:21:49 by tmouche          ###   ########.fr       */
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

#define W 30
#define H 20
#define R 40

void printVector(std::vector<double>& vec) {
	std::cout << "\033[H"; // remet le curseur en haut à gauche
    for (size_t i = 0; i < vec.size(); ++i) {
        if (i % W == 0 && i != 0)
            std::cout << '\n';
        std::cout << std::setw(3) << std::fixed << std::setprecision(1) << 0.0;
    }
    std::cout << "\033[H"; // remet le curseur en haut à gauche
	for (auto it = vec.begin(); it != vec.end();) {
		for (int count = 0; count < W; count++, it++) {
			if (*it != 0.)
            	std::cout << "\033[31m"; // rouge
        	else
            	std::cout << "\033[0m";  // reset couleur
        	std::cout << std::setw(3) << std::fixed << std::setprecision(1) << *it;
		}
		std::cout << '\n';
	}
    std::cout << "\033[0m" << std::flush; // reset couleur à la fin
}

void	drawBall(std::vector<double> & s, int x, int y, double num) {
	int i = y * W + x;
	
	if (i < 600 && i >= 0)
		s.at(i) = num;
	return ;
}

void	drawPaddle(std::vector<double> & s, int x, int y, int sizePaddle, double num) {
	int	size = sizePaddle / R;
	int start = (y - (size / 2)) * W;
	
	
	while (size && start < 600 && start >= 0) {
		s.at(start + x) = num;
		start += W;
		--size;
	}
	return ;
}

std::vector<std::vector<double>*>*	parse(std::string const & inFile) {
	auto	simul = new std::vector<std::vector<double>*>(500);

	std::ifstream	ifs(inFile.c_str());
	if (!ifs)
		throw std::exception();
	std::string	dataStr;
	std::getline(ifs, dataStr, '\0');	
	ifs.close();
	auto data = nlohmann::json::parse(dataStr);
	int		count = 0;
	for (auto it = simul->begin(); it != simul->end(); it++) {
		*it = new	std::vector<double>(H * W);
		for (double num = 0.16, lap = 0; lap < 6 ;lap++, count++, num += 0.16) {
			drawBall(**it, std::floor(static_cast<double>(data[count]["bx"])/R), std::floor(static_cast<double>(data[count]["by"])/R), num);
			drawPaddle(**it, std::floor(static_cast<double>(data[count]["rPx"])/R), std::floor(static_cast<double>(data[count]["rPy"])/R), 200, num);
			drawPaddle(**it, std::floor(static_cast<double>(data[count]["lPx"])/R), std::floor(static_cast<double>(data[count]["lPy"])/R), 200, num);
		}
	}
	return simul;
}

int	main( void ) { 
	auto test = parse("gameState.json");
	for (auto it = test->begin(); it != test->end(); it++) {
		printVector(**it);
		std::this_thread::sleep_for(std::chrono::milliseconds(50)); // ~30 fps
		delete *it;
	}
	delete test;
	return 0;
}