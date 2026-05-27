#include <cstdlib>
#include <iostream>

#include "menuFunctions.hpp"
#include "menuInit.hpp"
#include "menuStructures.hpp"

int main() {
	const tkr::MenuItem* current = &tkr::MAIN;	
	do {
		current = current->func(current);
	} while (true);

	return 0; 
}