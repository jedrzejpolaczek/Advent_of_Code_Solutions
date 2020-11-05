#include <iostream>		//std::cout
#include <fstream> 		//std::ifstream
#include <sstream>		//std::istringstream
#include <vector>		//std::vector

int main() {
	std::string line;
	std::string word; 
	std::string result;
	std::vector< std::string > vector;
	std::vector< std::vector < std::string > > vector_matrix;
	bool is_unique = true;

	//Loading the file
	std::ifstream puzzle;
	puzzle.open("puzzle_input");

	//Building vector
	while(getline( puzzle, line )){		
		std::stringstream line_stream ( line );
		while( line_stream >> word) 
			vector.push_back( word );
		//We are interested only in "programs" that hold something more than themselves
		if(vector.size() > 2)
			vector_matrix.push_back( vector );
		vector.clear();
	}

	//Searching for word
	for(int i = 0; i < vector_matrix.size(); i++) {		
		for(int j = 0; j < vector_matrix.size(); j++)
			for(int k = 3; k < vector_matrix[j].size(); k++) 
				if(vector_matrix[j][k].find(vector_matrix[i][0]) != std::string::npos)
					is_unique = false;
				
		if(is_unique)
			result = vector_matrix[i][0];
		is_unique = true;
	}

	std::cout<<"\n\n\n\t\t\t"<<result<<"\n\n\n";

	puzzle.close();

	return 0;
}