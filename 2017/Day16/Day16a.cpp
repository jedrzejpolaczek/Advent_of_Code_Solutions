#include <iostream>     //std::cout
#include <fstream>	    //std::ifstream
#include <sstream>	    //std::istringstream
#include <algorithm>    //std::rotate, std::swap

int main(int argc, char **argv) {
    std::string programs = "abcdefghijklmnop";
    //std::string programs = "abcde";
    std::ifstream infile(argv[1]);
    std::string line;
    std::getline(infile,line);
    std::stringstream commands (line);
    char instruction;        

    while (commands >> instruction) {
        if(instruction == 's') {
            int s = 0;
            commands >> s; 
            std::rotate(programs.begin(), programs.begin() + (programs.size() - s), programs.end());
        }
        else if(instruction == 'x') {
            int a = 0;
            int b = 0;
            commands >> a >> instruction >> b;
            std::swap(programs[a], programs[b]);
        }
        else if(instruction == 'p') {
            char a;
            char b;
            commands >> a >> instruction >> b;

            int ai = 0;
            int bi = 0;
            for(int i = 0; i < programs.size(); i++) {
                if(programs[i] == a)
                    ai = i;
                if(programs[i] == b)
                    bi = i;
            }
            std::swap(programs[ai], programs[bi]);
        }
        commands >> instruction;
    }
    
    std::cout<<programs;
	return 0;
}