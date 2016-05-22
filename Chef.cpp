/*
 * Chef.cpp
 *
 *  Created on: May 22, 2016
 *      Author: vinit
 */

#include "Chef.h"
#include "Kitchen.h"

using namespace std;
int Chef::number_of_chef = 0;

Chef::Chef(Kitchen* kitchen) {
	// TODO Auto-generated constructor stub
	this->kitchen = kitchen;

}

VeggieChef::VeggieChef(Kitchen* kitchen) :
		Chef(kitchen) {
	reciepe[LETTUCE] = 3;
	reciepe[OLIVES] = 4;
	reciepe[ONIONS] = 2;
	reciepe[SOURDOUGH] = 1;

}

bool VeggieChef::cook() {

	//Atomic
	bool isCookingDone = false;

	if (Inventory::isItemAvailable(reciepe)) {
		Inventory::getItems(reciepe);
		cout << "....Cooking Veggie..." << endl;
		//Atomic end
		if (kitchen->section_1.size() != 0) {
			usleep(10500 / kitchen->section_1.size());
			isCookingDone = true;
		} else {
			isCookingDone = false;
		}

	}

	return isCookingDone;
}
vector<Chef*> Chef::hireChef(string speciality, int number_of_position,
		Kitchen* kitchen) {

	vector<Chef*> chef;
	if (!speciality.compare(RECIPE_1)) {
		//return new vector<SandwichChef>(number_of_position);
		for (int i = 1; i <= number_of_position; i++) {

			VeggieChef* sandwichChef = new VeggieChef(kitchen);
			chef.push_back(sandwichChef);
		}
		return chef;

	} else if (!speciality.compare(RECIPE_2)) {
		//return new vector<WrapChef>(number_of_position);
		for (int i = 1; i <= number_of_position; i++) {

			ChickenChef* wrapchef = new ChickenChef(kitchen);
			chef.push_back(wrapchef);
		}
		return chef;
	} else if (!speciality.compare(RECIPE_3)) {
		//	return new vector<JuiceChef>(number_of_position);
		for (int i = 1; i <= number_of_position; i++) {

			HamChef* juicechef = new HamChef(kitchen);
			chef.push_back(juicechef);
		}
		return chef;
	}

}

ChickenChef::ChickenChef(Kitchen* kitchen) :
		Chef(kitchen) {
	reciepe[OLIVES] = 8;
	reciepe[ONIONS] = 5;
	reciepe[TOMATOES] = 4;
	reciepe[CHICKEN] = 4;
	reciepe[MULTI_GRAIN] = 1;
}

bool ChickenChef::cook() {
//Atomic
	bool isCookingDone = false;

	if (Inventory::isItemAvailable(reciepe)) {
		Inventory::getItems(reciepe);
		cout << "....Cooking Chicken..." << endl;
		usleep(11000 / kitchen->section_2.size());
		isCookingDone = true;
	} else {
		isCookingDone = false;
	}
	return isCookingDone;
}

HamChef::HamChef(Kitchen* kitchen) :
		Chef(kitchen) {
	reciepe[HAM] = 2;
	reciepe[TURKEY] = 2;
	reciepe[LETTUCE] = 5;
	reciepe[TOMATOES] = 3;
	reciepe[ITALIAN_BREAD] = 1;
}

bool HamChef::cook() {
	bool isCookingDone = false;
	if (Inventory::isItemAvailable(reciepe)) {
		Inventory::getItems(reciepe);
		cout << "....Cooking Ham..." << endl;
		if (kitchen->section_3.size() != 0) {
			usleep(8000 / kitchen->section_3.size());
			isCookingDone = true;
		}
	} else {
		isCookingDone = false;
	}

	return isCookingDone;

}
