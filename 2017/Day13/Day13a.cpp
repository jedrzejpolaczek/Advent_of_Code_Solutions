#include <fstream>	//std::ifstream
#include <iostream>	//std::cout
#include <sstream>	//std::istringstream
#include <map>		//std::map

int main(int argc, char **argv) {
  	std::ifstream infile(argv[1]);
	std::string line;
	int severity = 0;  
  	int picosecond;
  	int depth;
	char garbage;
	std::map <int, int> scanner_map;
  
	//Creating map
	while (std::getline(infile,line)) {
    	std::istringstream iss (line);
		iss >> picosecond >> garbage >> depth;
		scanner_map[picosecond] = depth;
	}

	//Finding severity
	for(auto x:scanner_map) {
		if( x.first % (2 * x.second - 2) == 0 )	
			severity += x.first * x.second;
	}

	std::cout<<"\n\t\t"<<severity;
  return 0;
}