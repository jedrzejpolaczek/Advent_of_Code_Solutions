#include <iostream>		//std::cout
#include <fstream> 		//std::ifstream
#include <sstream>		//std::istringstream
#include <vector>		//std::vector

int main() {
	std::string line;
	int number = 0; 
	int offset = 0; 
	int steps = 0;
	std::vector<int> jumps_vector;

	//Loading the file
	std::ifstream puzzle;
	puzzle.open("puzzle_input");

	//Building vector
	while(getline( puzzle, line )){		
		std::stringstream line_stream ( line );
		while( line_stream >> number)
			jumps_vector.push_back( number );
	}
	
	//Counting steps
	for(int i = 0; i < jumps_vector.size(); i+=offset, steps++) {
			offset = jumps_vector[i];
			if(jumps_vector[i] < 3)
				jumps_vector[i]++;
			else	
				jumps_vector[i]--;
	}
	
	std::cout<<"\n\n\n\t\t\t"<<steps<<"\n\n\n";

	puzzle.close();

	return 0;
}