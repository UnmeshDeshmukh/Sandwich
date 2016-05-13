#include <iostream>
#include <string>
#include "chef.h"
#include "order.h"
#include "configuration_constants.h"
#include <omp.h>
#include <fstream>


std::ifstream csv_Orders("order.csv");

using namespace std;

Order orders[ORDER_SIZE];

Order::read_Orders();


int main(){

read_Orders();
	Chef chef("1");
	

	return 0;
}