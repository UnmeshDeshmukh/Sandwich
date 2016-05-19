#g++ inventory.h inventory.cpp order.h Task.h restaurant.cpp configuration_constants.h chef.h -o 275-project-2.out -Wall -std=c++11
#chmod +x 275-project-2.out

g++ -c inventory.cpp -std=c++11
g++ -c restaurant.cpp -std=c++11
g++ -o main inventory.o restaurant.o -std=c++11