#include <iostream>
#include <string>
#include "chef.h"
#include "order.h"
#include "configuration_constants.h"
#include <omp.h>
#include <fstream>
#include <vector>
#include "Task.h"

//

using namespace std;

vector<Order> orders;
vector<Task> tasks;

int main() {

	orders = Order::read_Orders();
	Order::print_Orders(orders);

	tasks = Task::getTasks(orders);
	Task::printTasks(tasks);

	Kitchen* kitchen = new Kitchen;



	for(int i=0;i<tasks.size();i++){

		vector<Chef*> section = Kitchen::getASection(tasks[i].getTaskType());
		section[Kitchen::getAChef(tasks[i].getTaskType())]->cook();

	}

	//Chefs::chefr1[1]->cook();

	cout << "End";

	return 0;
}
