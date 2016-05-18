#include <unistd.h>
#include <iostream>
#include <map>
#include <string>
#include <vector>

#include "configuration_constants.h"
#include "inventory.h"

using namespace std;

class Chef {
	int chef_id;
	static int number_of_chef;
protected:
	map<string, int> reciepe;

public:

	Chef() {
		chef_id = number_of_chef++;

		cout << "Chef initialised with id (" << chef_id << ")" << endl;

	}

	static vector<Chef*> hireChef(string speciality, int number_of_position);

	virtual bool cook() = 0;

};

int Chef::number_of_chef = 0;
class VeggieChef: public Chef {
public:
	VeggieChef() :
			Chef() {
		reciepe[LETTUCE] = 3;
		reciepe[OLIVES] = 4;
		reciepe[ONIONS] = 2;
		reciepe[SOURDOUGH] = 1;

	}
	bool cook() {

		//Atomic
		if (Inventory::isItemAvailable(reciepe)) {
			Inventory::getItems(reciepe);
			cout << "....Cooking Veggie..." << endl;
			//Atomic end
			usleep(6500);
			return true;
		} else {
			return false;

		}

	}

};

class ChickenChef: public Chef {
public:
	ChickenChef() :
			Chef() {
		reciepe[OLIVES] = 8;
		reciepe[ONIONS] = 5;
		reciepe[TOMATOES] = 4;
		reciepe[CHICKEN] = 4;
		reciepe[MULTI_GRAIN] = 1;
	}
	bool cook() {

		//Atomic
		if (Inventory::isItemAvailable(reciepe)) {
			Inventory::getItems(reciepe);
			cout << "....Cooking Chicken..." << endl;
			usleep(6000);
			return true;
		} else
			return false;
	}

};

class HamChef: public Chef {
public:
	HamChef() :
			Chef() {
		reciepe[HAM] = 2;
		reciepe[TURKEY] = 2;
		reciepe[LETTUCE] = 5;
		reciepe[TOMATOES] = 3;
		reciepe[ITALIAN_BREAD] = 1;
	}
	bool cook() {
		if (Inventory::isItemAvailable(reciepe)) {
			Inventory::getItems(reciepe);
			cout << "....Cooking Ham..." << endl;
			usleep(6000);
			return true;
		} else
			return false;
	}

};

vector<Chef*> Chef::hireChef(string speciality, int number_of_position) {

	vector<Chef*> chef;
	if (!speciality.compare(RECIPE_1)) {
		//return new vector<SandwichChef>(number_of_position);
		for (int i = 0; i < number_of_position; i++) {

			VeggieChef* sandwichChef = new VeggieChef;
			chef.push_back(sandwichChef);
		}
		return chef;

	} else if (!speciality.compare(RECIPE_2)) {
		//return new vector<WrapChef>(number_of_position);
		for (int i = 0; i < number_of_position; i++) {

			ChickenChef* wrapchef = new ChickenChef;
			chef.push_back(wrapchef);
		}
		return chef;
	} else if (!speciality.compare(RECIPE_3)) {
		//	return new vector<JuiceChef>(number_of_position);
		for (int i = 0; i < number_of_position; i++) {

			HamChef* juicechef = new HamChef;
			chef.push_back(juicechef);
		}
		return chef;
	}

}

class Kitchen {

public:

	static vector<Chef*> section_1;
	static vector<Chef*> section_2;

	static vector<Chef*> section_3;

	static int section_1_pointer;
	static int section_2_pointer;
	static int section_3_pointer;

	Kitchen() {

		section_1 = Chef::hireChef(RECIPE_1, 2);
		section_2 = Chef::hireChef(RECIPE_2, 1);
		section_3 = Chef::hireChef(RECIPE_3, 2);

	}

	static int getAChef(string speciality) {

		if (!speciality.compare(RECIPE_1)) {
			return (((section_1_pointer++) + 1) % section_1.size());
		} else if (!speciality.compare(RECIPE_2)) {
			return (((section_2_pointer++) + 1) % section_2.size());
		} else if (!speciality.compare(RECIPE_3)) {
			return (((section_3_pointer++) + 1) % section_3.size());
		}
	}

	static vector<Chef*> getASection(string speciality) {

		if (!speciality.compare(RECIPE_1)) {
			return section_1;
		} else if (!speciality.compare(RECIPE_2)) {
			return section_2;
		} else if (!speciality.compare(RECIPE_3)) {
			return section_3;
		}
	}

};

vector<Chef*> Kitchen::section_1;
vector<Chef*> Kitchen::section_2;
vector<Chef*> Kitchen::section_3;
int Kitchen::section_1_pointer = 0;
int Kitchen::section_2_pointer = 0;
int Kitchen::section_3_pointer = 0;
