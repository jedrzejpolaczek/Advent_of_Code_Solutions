#include <iostream>     //std::cout
#include <fstream>	    //std::ifstream
#include <sstream>	    //std::istringstream
#include <algorithm>    //std::rotate, std::swap
#include <map>          //std::map
#include <bits/stdc++.h>

int main(int argc, char **argv) {
    std::string programs = "abcdefghijklmnop";
    //std::string programs = "abcde";
    std::ifstream infile(argv[1]);
    std::string line;
    std::getline(infile,line);    
    char instruction;        
    std::map<std::string, int> prev;

    //Repeat all commands 1 000 000 000 times
    for(int i = 1; i <= 1000000000; i++) {
        std::stringstream commands (line);
        //Set programs in order according to instructions
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

        //Catch repetition and print answer
        if(prev.count(programs)) {
            if((1000000000 - i) % (i - prev[programs]) == 0) {
                break;
            }
        }
        prev[programs] = i;
    }
    std::cout << programs;
	return 0;
}