#include <iostream>		//std::cout
#include <fstream> 		//std::ifstream
#include <sstream>		//std::istringstream
#include <vector>		//std::vector

int main() {
	std::string line;
	int number = 0; 
	int cycles = 0;
	std::vector< int > vector;
	std::vector< std::vector< int >> vector_matrix;
	int tie_winer = 0;
	int tie_winer_index = 0;
	int blocks_to_relocate = 0;
	int current_vector_index = 0;
	bool continue_loop = true;

	//Loading the file
	std::ifstream puzzle;
	puzzle.open("puzzle_input");

	//Building vector
	while(getline( puzzle, line )){		
		std::stringstream line_stream ( line );
		while( line_stream >> number)
			vector.push_back( number );
	}
	vector_matrix.push_back( vector );

	//Relocation routine
	do {
		cycles++;
		tie_winer = 0;

		//Finding bank with the most blocks
		for(int i = 0; i < vector.size(); i++) {
			if( tie_winer < vector[i]) {
				tie_winer = vector[i];
				tie_winer_index = i;
			}
		}
		blocks_to_relocate = vector[tie_winer_index];
		vector[tie_winer_index] = 0;
		current_vector_index = tie_winer_index + 1;

		//Relocation
		while(blocks_to_relocate) {
			if( current_vector_index >= vector.size() )
				current_vector_index = 0;
			vector[current_vector_index]++;
			current_vector_index++;
			blocks_to_relocate--;
		}

		std::cout<<"\nStep "<<cycles<<": ";
		for(int i = 0; i < vector.size(); i++)
			std::cout<<vector[i]<<" ";

		//Checking for prevoius solution		
		for(int i = 0; i < vector_matrix.size(); i++)
			if(vector_matrix[i] == vector)
				continue_loop = false;
		vector_matrix.push_back( vector );

	} while(continue_loop);
	
	std::cout<<"\n\n\n\t\t\t"<<cycles<<"\n\n\n";

	puzzle.close();

	return 0;
}