#include <iostream>		//std::cout
#include <fstream>		//getline
#include <vector>		//std::vector
#include <sstream>		//std::stringstream
#include <algorithm>    // std::sort

int main(int argc, char ** argv) {
	std::ifstream puzzle;
	puzzle.open("puzzle_input");

	std::string row;
	int number, sum_total = 0;
	int dividend, divider = 1;

	while(getline( puzzle, row )){		
		std::stringstream row_stream ( row );
		std::vector<int> v;
		while( row_stream >> number) 
			v.push_back(number);
		std::sort(v.begin(), v.end());

		for(int i = 0; i < v.size(); i++) {
			for(int j = i+1; j <v.size(); j++)
				if((v[j] % v[i]) == 0) {
					divider = v[i];
					dividend = v[j];
					break;
				}
		}
		sum_total += dividend / divider;
	}
	
	std::cout<<"\n\n\n\t\t\t"<<sum_total<<"\n\n\n";

	puzzle.close();

	return 0;
}