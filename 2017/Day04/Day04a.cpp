#include <iostream>		//std::cout
#include <set>			//std::set
#include <fstream> 		//std::ifstream
#include <sstream>		//std::istringstream
#include <string>		//std::string

int main() {
  int sum{0};

	std::ifstream puzzle;
	puzzle.open("puzzle_input");

  for (std::string line; std::getline(puzzle, line);) {
    sum += [&] {
      std::istringstream iss{line};
      std::set<std::string> words;
      for (std::string word; iss >> word;) {
        if (!words.insert(word).second) {
          return 0;
        }
      }
      return 1;
    }();
  }
  std::cout << sum << '\n';

  puzzle.close();
  
  return 0;
}