#include <iostream>		//std::cout
#include <fstream>		//getline
#include <vector>		//std::vector
#include <sstream>		//std::stringstream
#include <string>   	// std::string

int main(int argc, char *argv[])
{
	int sum (0);
	
	//Loading file
	std::ifstream puzzle;
	puzzle.open("puzzle_input");
	std::string line;
	getline( puzzle, line );
		
	//Counting
	for(int i = 0; i < line.size(); i++) 
		if (line[i] == line[ (i + (line.size()/2) ) % line.size() ])
			sum += line[i]-'0';
	
	std::cout<<"\n\t\t\t"<<sum<<"\n";

	puzzle.close();

	return 0;
}