#include <iostream>
#include <map>
#include <string>
#include <fstream>
#include <stdlib.h>

using namespace std;

std::ifstream input_kitchen( "kitchen_stock.config" );
typedef map<const string,string> CfgMap;



class Ingredients{
	//	static ifstream input_kitchen("kitchen_stock.config");
		static CfgMap config;
		//static int counter;

	public:
		
		Ingredients(){
			//config = new CfgMap;
			//counter = 0;
		}
		static void showInventory(){
			for( map<const string,string>:: const_iterator it = config.begin(); it != config.end(); ++it)
			{
				int converted = atoi(it->second.c_str());
	   			std::cout <<"INGREDIENT NAME ="<< it->first << " INGREDIENT STOCK =" << it->second << " " << "\n";
				std::cout <<"CONVERTED INTEGER ="<<converted<<endl;
			//	cout<<"Counter is "<<counter;

			}
		}

		static void scanInventory(){
			string s;
			while(getline(input_kitchen,s)) 
			{
				config[s.substr(0,s.find('='))]=s.substr(s.find('=')+1);
			//	counter++;
				
			}
		}

};


CfgMap Ingredients::config;

int main()
{
	
	Ingredients* ingredients = new Ingredients;
	ingredients->scanInventory();
	ingredients->showInventory();

	return 1;

}

