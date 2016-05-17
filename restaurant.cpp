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



int main(){


	orders=Order::read_Orders();
	Order::print_Orders(orders);

	tasks=Task::getTasks(orders);
	Task::printTasks(tasks);

	Chef chef("1");

	cout<<"End";
	

	return 0;
}
