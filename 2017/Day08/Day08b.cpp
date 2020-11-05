#include <iostream> //std::cout
#include <fstream>  //std::stringstream
#include <sstream>  //std::ifstream
#include <map>      //std::map
#include <limits>   //std::numeric_limits

int main(int argc, char *argv[]) {
	std::ifstream infile(argv[1]);
  	std::string line;
  	std::map<std::string,int> registers;
  	std::getline(infile,line);
  	int max_value(0);
  
  	while (infile && !line.empty()) {
    	std::stringstream ss (line);
      	std::string reg, op, if_literal, test_register, comp;
      	int diff, number;
      	ss >> reg >> op >> diff >> if_literal >> test_register >> comp >> number;

      	if (op=="dec")
        	diff*=-1;

      	int test_register_value = registers[test_register];
      	if((comp == "==" && test_register_value==number)
         	|| (comp == "!=" && test_register_value!=number)
         	|| (comp == ">=" && test_register_value>=number)
         	|| (comp == "<=" && test_register_value<=number)
         	|| (comp == ">" && test_register_value>number)
         	|| (comp == "<" && test_register_value<number))
        	{
          		registers[reg]+=diff;
          		max_value = std::max(max_value,registers[reg]);
        	}
      	std::getline(infile,line);
    }
  	int max_final_value (std::numeric_limits<int>::min());
  
  	for (auto &r: registers)
    	max_final_value = std::max(max_final_value,r.second);
  
  	std::cout << "Max final value: " << max_final_value << "\n" << "Max intermediate value: " << max_value << "\n";

  	return 0;
}