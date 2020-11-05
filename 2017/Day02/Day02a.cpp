#include <iostream>		//std::cout
#include <fstream>		//getline
#include <vector>		//std::vector
#include <sstream>		//std::stringstream

int main(int argc, char ** argv) {
	std::ifstream puzzle;
	puzzle.open("puzzle_input");

	std::string row;
	int number = 0;
	int max_in_row = 0;
	int min_in_row = 2147483647;
	int sum_total = 0;

	while(getline( puzzle, row )){		
		std::stringstream row_stream ( row );
		while( row_stream >> number) {			
			std::cout<<number<<" ";
			if(max_in_row < number)
				max_in_row = number;
			if(min_in_row > number)
				min_in_row = number;
		}		
		sum_total += max_in_row - min_in_row;
		//std::cout<<"\nMax: "<<max_in_row<<" | Min: "<<min_in_row<<" | Sum: "<<sum_total<<std::endl;
		max_in_row = 0;
		min_in_row = 2147483647;
	}
	std::cout<<"\n\n\n\t\t\t"<<sum_total<<"\n\n\n";

	puzzle.close();

	return 0;
}