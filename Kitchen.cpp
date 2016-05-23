/*
 * Kitchen.cpp
 *
 *  Created on: May 21, 2016
 *      Author: vinit
 */
#include <iostream>
#include "Kitchen.h"
#include <string>
#include <vector>

using namespace std;

KitchenCfg Kitchen::kitchenCfg;
int Kitchen::number_of_kitchens = 0;
unsigned long int Kitchen::NUM_OF_KITCHENS = 0;

ifstream input_kitchen_config("./config/kitchen.config");
Kitchen::Kitchen() {

	this->kitchen_id = number_of_kitchens++;

	section_1_pointer = 0;
	section_2_pointer = 0;
	section_3_pointer = 0;

	section_1 = Chef::hireChef(RECIPE_1, kitchenCfg[KITCHEN_SECTION_1], this);// Hiring VeggieChef
	section_2 = Chef::hireChef(RECIPE_2, kitchenCfg[KITCHEN_SECTION_2], this);// Hiring ChickenChef
	section_3 = Chef::hireChef(RECIPE_3, kitchenCfg[KITCHEN_SECTION_3], this);// Hiring HamChef

}

void Kitchen::readKitchenConfiguration() {
	string s;
	input_kitchen_config.seekg(0, std::ios::beg);
	while (getline(input_kitchen_config, s)) {
		kitchenCfg[s.substr(0, s.find(':'))] = stoi(s.substr(s.find(':') + 1));	// Reading total number of Kitchen
	}
	Kitchen::NUM_OF_KITCHENS = kitchenCfg[NUMBER_OF_KITCHENS];
}

void Kitchen::showKitchens(vector<Kitchen> kitchens) {
	cout << "\n--------------KICHEN-------\n" << endl;// Printing Kitchen id with number of Chef in each section
	for (int i = 0; i < kitchens.size(); i++) {
		cout << "Kitchen with" << kitchens[i].kitchen_id;
		cout << "\nNumber of chefs in VeggieKitchen = "
				<< kitchens[i].section_1.size();
		cout << "\nNumber of chefs in ChickenKitchen = "
				<< kitchens[i].section_2.size();
		cout << "\nNumber of chefs in HamKitchen = "
				<< kitchens[i].section_3.size() << endl;
	}
}

int Kitchen::getAChef(string speciality) {
	// Retrieving Chef to cook Sandwich if free
	if (!speciality.compare(RECIPE_1)) {
		return (((section_1_pointer++) + 1) % section_1.size());
	} else if (!speciality.compare(RECIPE_2)) {
		return (((section_2_pointer++) + 1) % section_2.size());
	} else if (!speciality.compare(RECIPE_3)) {
		return (((section_3_pointer++) + 1) % section_3.size());
	}
}

vector<Chef*> Kitchen::getASection(string speciality) {

	if (!speciality.compare(RECIPE_1)) {// Retrieving appropriate section to cook the order requested
		return section_1;
	} else if (!speciality.compare(RECIPE_2)) {
		return section_2;
	} else if (!speciality.compare(RECIPE_3)) {
		return section_3;
	}
}

