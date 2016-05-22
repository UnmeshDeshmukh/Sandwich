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
/*
 vector<Chef*> Kitchen::section_1;
 vector<Chef*> Kitchen::section_2;
 vector<Chef*> Kitchen::section_3;
 int Kitchen::section_1_pointer = 0;
 int Kitchen::section_2_pointer = 0;
 int Kitchen::section_3_pointer = 0;*/
KitchenCfg Kitchen::kitchenCfg;
int Kitchen::number_of_kitchens = 0;
unsigned long int Kitchen::NUM_OF_KITCHENS = 0;
//Kitchen* Kitchen::kitchen_instance;
ifstream input_kitchen_config("./config/kitchen.config");
Kitchen::Kitchen() {

	this->kitchen_id = number_of_kitchens++;

	section_1_pointer = 0;
	section_2_pointer = 0;
	section_3_pointer = 0;
	//input_kitchen_config.clear();

	section_1 = Chef::hireChef(RECIPE_1, kitchenCfg[KITCHEN_SECTION_1], this);
	section_2 = Chef::hireChef(RECIPE_2, kitchenCfg[KITCHEN_SECTION_2], this);
	section_3 = Chef::hireChef(RECIPE_3, kitchenCfg[KITCHEN_SECTION_3], this);

}

void Kitchen::readKitchenConfiguration() {
	string s;
	input_kitchen_config.seekg(0, std::ios::beg);
	while (getline(input_kitchen_config, s)) {
		kitchenCfg[s.substr(0, s.find(':'))] = stoi(s.substr(s.find(':') + 1));
		//	counter++;

	}
	Kitchen::NUM_OF_KITCHENS = kitchenCfg[NUMBER_OF_KITCHENS];
}
/*
 Kitchen* Kitchen::getKitchen() {
 if (kitchen_instance != NULL) {
 return kitchen_instance;
 } else {
 kitchen_instance = new Kitchen;
 return kitchen_instance;
 }
 }*/
void Kitchen::showKitchens(vector<Kitchen> kitchens) {
	cout << "\n--------------KICHEN-------\n" << endl;
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

	if (!speciality.compare(RECIPE_1)) {
		return (((section_1_pointer++) + 1) % section_1.size());
	} else if (!speciality.compare(RECIPE_2)) {
		return (((section_2_pointer++) + 1) % section_2.size());
	} else if (!speciality.compare(RECIPE_3)) {
		return (((section_3_pointer++) + 1) % section_3.size());
	}
}

vector<Chef*> Kitchen::getASection(string speciality) {

	if (!speciality.compare(RECIPE_1)) {
		return section_1;
	} else if (!speciality.compare(RECIPE_2)) {
		return section_2;
	} else if (!speciality.compare(RECIPE_3)) {
		return section_3;
	}
}

