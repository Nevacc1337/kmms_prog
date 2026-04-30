#include <cstdlib>
#include <iostream>

#include "menuFunctions.hpp"
#include "menuStructures.hpp"

const tkr::MenuItem* tkr::showMenu(const tkr::MenuItem* current) {
	std::cout << "Добро пожаловать в тестовую программу!" << std::endl;
	for (int i = 1; i < current->childrenSize; i++) {
			std::cout << current->children[i]->text << std::endl;
	}

	std::cout << current->children[0]->text << std::endl;
	std::cout << "Меню > ";

	int userInput;
	std::cin >> userInput;
	std::cout << std::endl;
	
	return current->children[userInput]; 
}

const tkr::MenuItem* tkr::exit(const MenuItem* current) {
	std::exit(0);
}

const tkr::MenuItem* tkr::goBack(const MenuItem* current) {
	std::cout << current-> text << std::endl << std::endl;
	return current->parent->parent;

}

// ALGEBRA
const tkr::MenuItem* tkr::algebraSum(const MenuItem* current) {
	std::cout << current-> text << std::endl << std::endl;
	return current->parent;
}

const tkr::MenuItem* tkr::algebraSubt(const MenuItem* current) {
	std::cout << current-> text << std::endl << std::endl;
	return current->parent;
}

const tkr::MenuItem* tkr::algebraMult(const MenuItem* current) {
	std::cout << current-> text << std::endl << std::endl;
	return current->parent;
}

const tkr::MenuItem* tkr::algebraDiv(const MenuItem* current) {
	std::cout << current-> text << std::endl << std::endl;
	return current->parent;
}

// MATHANALYSIS
const tkr::MenuItem* tkr::mathanDiff(const MenuItem* current) {
	std::cout << current-> text << std::endl << std::endl;
	return current->parent;
}

const tkr::MenuItem* tkr::mathanInter(const MenuItem* current) {
	std::cout << current-> text << std::endl << std::endl;
	return current->parent;
}