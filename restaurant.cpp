#include <iostream>
#include <string>
#include "order.h"
#include "configuration_constants.h"
#include <omp.h>
#include "configuration_constants.h"
#include <fstream>
#include <vector>
#include "Task.h"
#include "inventory.h"
#include <boost/chrono.hpp>
#include "Kitchen.h"
#include "Chef.h"
#include <boost/array.hpp>

using namespace std;
using namespace boost::chrono;

int orders_delivered = 0;
int total_processed_orders = 0;
double initial_time, end_time;
double revenue;
int main(int argc, char* argv[]) {

	Kitchen::readKitchenConfiguration();		// Reading kitchen configuration
	vector<Kitchen> kitchens(Kitchen::NUM_OF_KITCHENS);	// Vector to store all kitchen informations
	vector<double> v(10);													//
	vector<Order> orders;				// Vector to store all order information
	vector<Task> tasks;						// Vector to store task information
	map<Order, vector<Task>> reducer;// Reducer map to track if complete order is complete
	std::string filename=argv[1];

	char ans;
	int num_of_task_distribution_threads;
	int num_of_reducer_threads;
	orders = Order::read_Orders(filename.c_str());							// Reading orders
	Order::print_Orders(orders);							// Printing orders

	tasks = Task::getTasks(&orders);// Determining individual tasks to be completed

	cout << "\nNUMBER OF PROCESSORS AVAILABLE FOR PARALLELISATION "
			<< omp_get_num_procs();
	omp_set_num_threads(Kitchen::NUM_OF_KITCHENS);// Assigning threads= Number of kitchens configured

	int dummy;

	while (true) {

		Inventory::scanInventory();	// Scanning inventory from the configured inventory file
		Inventory::showInventory();						// Printing inventory
		Kitchen::showKitchens(kitchens);		// Printing available kitchens
		auto dt_s = high_resolution_clock::now();// Clock to track exection time

		initial_time = omp_get_wtime();

#pragma omp parallel
		{
#pragma omp  for nowait
			for (int i = 0; i < tasks.size(); i++) {

				if (i == 0) {
					num_of_task_distribution_threads = omp_get_num_threads();

				}

				if (!tasks[i].getStatus().compare(INCOMPLETE)) {// If task incomplete
					vector<Chef*> section =
							kitchens[omp_get_thread_num()].getASection(
									tasks[i].getTaskType());// Retrieving available section

					if (section.size() != 0
							&& section[kitchens[omp_get_thread_num()].getAChef(
									tasks[i].getTaskType())]->cook())// Cooking the requested item
						tasks[i].changeStatus(COMPLETE);
					else
						tasks[i].changeStatus(INCOMPLETE);// If section not available task incomplete
				}

			}

#pragma omp  for reduction(+:revenue)											// Calculating revenue
			for (int i = 0; i < tasks.size(); i++) {

				if (i == 0) {
					num_of_reducer_threads = omp_get_num_threads();

				}

				if (tasks[i].getStatus().compare(DELIVERED)
						&& !tasks[i].getStatus().compare(COMPLETE)) {// Checking if the tasks from an order are incomplete

#pragma omp critical
					{

						reducer[orders[tasks[i].getOrderId()]].push_back(
								tasks[i]);		// Pushing orders to the reducer
						tasks[i].changeStatus(DELIVERED);// Task status changed to delivered
					}

					if (orders[tasks[i].getOrderId()].getStatus().compare(
					COMPLETE)
							&& (reducer[orders[tasks[i].getOrderId()]].size()
									== orders[tasks[i].getOrderId()].getTaskCount())) {	// Checking if all the orders is complete

						orders_delivered++;	// Incrementing count for delivered orders
						orders[tasks[i].getOrderId()].changeStatus(COMPLETE);// Changing Status of orders
						revenue += Task::getTaskCost(tasks[i]);	// Calculating the revenue
					}

				}

			}
		}
		auto dt = duration_cast<milliseconds>(
				high_resolution_clock::now() - dt_s);
		Inventory::showInventory();
		//	Task::printTasks(tasks);

		end_time = omp_get_wtime();
		// or miliseconds

		Order::print_Orders(orders);
		cout << "OVERALL STATUS : " << orders_delivered << "/" << orders.size()
				<< " orders delivered" << endl;
		cout << "\nNUMBER OF THREADS SET IN THIS TASK DISTRIBUTION TEAM ="
				<< num_of_task_distribution_threads << endl;

		cout << "\nNUMBER OF THREADS SET IN THIS TASK REDUCER TEAM ="
				<< num_of_reducer_threads << endl;

		cout << "\nREVENUE =" << revenue;
		cout << "\nTask assignment and execution time =" << dt.count() << endl;

		cout << "Do you want to replenish?" << endl;
		cin >> ans;
		initial_time = omp_get_wtime();
		if (ans != 'Y')
			break;

		cout << "End";

	}
	return 0;
}
