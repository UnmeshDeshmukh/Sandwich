/*
 * Inventory.cpp
 *
 *  Created on: May 17, 2016
 *      Author: vinit
 */

#include "inventory.h"
#include <omp.h>
#include "omp_sync.h"

std::ifstream input_kitchen_inventory("./config/kitchen_inventory.config");
InventoryCfg Inventory::config;

Inventory::Inventory() {
	// TODO Auto-generated constructor stub

}

Inventory::~Inventory() {
	// TODO Auto-generated destructor stub
}

void Inventory::showInventory() {

	for (map<string, int>::const_iterator it = config.begin();
			it != config.end(); ++it) {
		//int converted = atoi(it->second.c_str());
		std::cout << "INGREDIENT NAME =" << it->first << " INGREDIENT STOCK ="
				<< it->second << " " << "\n";

	}

}

void Inventory::scanInventory() {

	string s;
	input_kitchen_inventory.clear();                 // clear fail and eof bits
	input_kitchen_inventory.seekg(0, std::ios::beg);
	while (getline(input_kitchen_inventory, s)) {
		config[s.substr(0, s.find(':'))] = stoi(s.substr(s.find(':') + 1));
		//	counter++;

	}

}

bool Inventory::isItemAvailable(map<string, int> recipe) {

	Mutex::getMutex()->lock();

	for (map<string, int>::const_iterator it = recipe.begin();
			it != recipe.end(); ++it) {
		//int converted = atoi(it->second.c_str());
		//	std::cout << "INGREDIENT NAME =" << it->first << " INGREDIENT STOCK ="
		//		<< it->second << " " << "\n";

		if ((it->second) <= config[it->first]) {
			continue;
		} else {
			Mutex::getMutex()->unlock();

			return false;
		}

	}
	Mutex::getMutex()->unlock();

	return true;

}
void Inventory::getItems(map<string, int> recipe) {

	Mutex::getMutex()->lock();

	for (map<string, int>::const_iterator it = recipe.begin();
			it != recipe.end(); ++it) {
		//int converted = atoi(it->second.c_str());
		//std::cout << "INGREDIENT NAME =" << it->first << " INGREDIENT STOCK ="
//				<< it->second << " " << "\n";

		config[it->first] = config[it->first] - it->second;

	}
	Mutex::getMutex()->unlock();

}

