#include <iostream>	//std::cout
#include <fstream>	//std::ifstream

int main(int argc, char ** argv) {
	int sum = 0;
	char current, next, first;
	
	//Loading file
	std::ifstream kod("puzzle_input");

	//Remember first digit
	kod>>first;
	current=first;

	//Counting 
	while(kod>>next) {		
		if(current == next) 
			sum += (current - '0');
		current = next;		
	}
	if(first == current)
		sum += (first -'0');

	std::cout<<"\n\t\t\t"<<sum<<"\n";

	puzzle.close();
	
	return 0;
}