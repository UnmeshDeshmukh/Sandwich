#include <iostream>
#include <string>
#include <unistd.h>
#include "configuration_constants.h"
#include<vector>

using namespace std;

class Chef {
	protected :int chef_id;
	static int number_of_chef;

public:

	Chef() {
		chef_id = number_of_chef++;

		cout << "Chef initialised with id (" << chef_id << ")" << endl;

	}

	static vector<Chef*> hireChef(string speciality, int number_of_position);

	virtual void cook() = 0;

};

int Chef::number_of_chef = 0;
class SandwichChef: public Chef {
public:
	SandwichChef() :
			Chef() {

	}
	void cook() {
		cout << "chef("<<chef_id<<")....Cooking SandWich..." << endl;
		usleep(6500);

	}

};

class WrapChef: public Chef {
public:
	WrapChef() :
			Chef() {

	}
	void cook() {
		cout << "chef("<<chef_id<<")....Cooking Wrap..." << endl;
		usleep(6000);

	}

};

class JuiceChef: public Chef {
public:
	JuiceChef() :
			Chef() {

	}
	void cook() {
		usleep(4000);
		cout << "chef("<<chef_id<<")....Cooking Juice..." << endl;

	}

};

vector<Chef*> Chef::hireChef(string speciality, int number_of_position) {

	vector<Chef*> chef;
	if (!speciality.compare(RECIEPE_1)) {
		//return new vector<SandwichChef>(number_of_position);
		for (int i = 0; i < number_of_position; i++) {

			SandwichChef* sandwichChef = new SandwichChef;
			chef.push_back(sandwichChef);
		}
		return chef;

	} else if (!speciality.compare(RECIEPE_2)) {
		//return new vector<WrapChef>(number_of_position);
		for (int i = 0; i < number_of_position; i++) {

			WrapChef* wrapchef = new WrapChef;
			chef.push_back(wrapchef);
		}
		return chef;
	} else if (!speciality.compare(RECIEPE_3)) {
		//	return new vector<JuiceChef>(number_of_position);
		for (int i = 0; i < number_of_position; i++) {

			JuiceChef* juicechef = new JuiceChef;
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

		section_1 = Chef::hireChef(RECIEPE_1,5);
		section_2 = Chef::hireChef(RECIEPE_2,6);
		section_3 = Chef::hireChef(RECIEPE_3,7);

	}

	static int getAChef(string speciality) {

		if (!speciality.compare(RECIEPE_1)) {
			return (((section_1_pointer++) + 1) % section_1.size());
		} else if (!speciality.compare(RECIEPE_2)) {
			return (((section_2_pointer++) + 1) % section_2.size());
		} else if (!speciality.compare(RECIEPE_3)) {
			return (((section_3_pointer++) + 1) % section_3.size());
		}
	}

	static vector<Chef*> getASection(string speciality) {

		if (!speciality.compare(RECIEPE_1)) {
			return section_1;
		} else if (!speciality.compare(RECIEPE_2)) {
			return section_2;
		} else if (!speciality.compare(RECIEPE_3)) {
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

