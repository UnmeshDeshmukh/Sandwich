#include <iostream>
#include <string>

using namespace std;

class Chef
{
	string chef_id;



public:

	Chef(string id){
		chef_id = id;
		cout<<"Chef initialised with id ("<<chef_id<<")";
		
	}

	void cook(string recipe){
		cout<<"Chef with id ("<<chef_id<<")is cooking "<<recipe<<endl;

	}


};