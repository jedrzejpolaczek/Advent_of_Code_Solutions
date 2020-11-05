// #include <iostream>      //std::cout
// #include <fstream>	    //std::ifstream
// #include <sstream>	    //std::istringstream

// int main(int argc, char **argv) {

//     std::ifstream infile(argv[1]);
//     std::string line;
//     std::getline(infile,line);    
//     char instruction;        
//     std::stringstream commands (line);

//     while (commands >> instruction) {

//      }


// 	return 0;
// }

#include <fstream>  //std::ifstream
#include <vector>   //std::vector
#include <iostream> //std::cout
#include <map>      //std::map

int main(int, char **argv)
{
  	std::vector< std::string > input_map;

  	std::ifstream infile(argv[1]);
  	std::string line;
  	std::getline(infile, line);

	//creating map
  	while(infile) {
    	input_map.push_back( line );
      	std::getline(infile, line );
	}

	//printing map
  	for(auto &m: input_map) { 
	  	std::cout << m << "\n"; 
	}

	//
  	const int map_size =  10001;
  	std::vector< std::vector< char > > map( map_size );
	  
	for(auto &m: map)
    	m.resize(map_size, '.');

	//Initial position
	int dx(map_size / 2 - input_map.size() / 2);
	int dy(map_size / 2 - input_map.size() / 2);

  	for(int y=0; y < input_map.size(); ++y)
    	for(int x=0; x < input_map[y].size(); ++x)
       		map[y + dy][x + dx] = input_map[ y ][ x ]; 

	int x = map_size / 2;
	int y = map_size / 2; 
	int dir = 0;

  	int infections = 0;
  	for(size_t step = 0; step < 10000; ++step) { //10000000 for part two
      	switch(map[ y ][ x ]) {
        	case '.':
          		dir = (dir + 3) % 4;
          		map[ y ][ x ] = 'W';
          		break;
			//comment this case out for part 1
			case 'W':
          		map[ y ][ x ] = '#';
          		++infections;
          		break;
        	case '#':
          		dir = (dir + 1) % 4;
          		map[ y ][ x ] = 'F';
				break;
			//comment this case out for part 1
        	case 'F':
          		dir = (dir + 2) % 4;
          		map[ y ][ x ] = '.';
          		break;
        }
      	switch( dir ) {
        	case 0:
          		--y;
          		break;
        	case 1:
          		++x;
          		break;
        	case 2:
          		++y;
          		break;
        	case 3:
          		--x;
          		break;
        }
	}
	
  	std::cout << "infections: " << infections << "\n";
}