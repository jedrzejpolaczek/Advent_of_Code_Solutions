#include <fstream>	//std::ifstream
#include <iostream>	//std::cout
#include <string>	//.size()

enum State {
    NONE, GARBAGE, IGNORE,
};

int main(int argc, char ** argv) {
    std::ifstream infile("puzzle_input");
  	std::string feed;

    size_t len = 0;
	std::getline(infile,feed);
    len = feed.size();

    State state = NONE;
    int sum = 0;
    int level = 0;
    int chars = 0;
    for (int i = 0; i < len; ++i) {
        char ch = feed[i];
        if (state == NONE) {
            if (ch == '<') {
                state = GARBAGE;
            } else if (ch == '{') {
                level += 1;
            } else if (ch == '}') {
                sum += level;
                level -= 1;
            }
        } else if (state == GARBAGE) {
            if (ch == '!') {
                state = IGNORE;
            } else if (ch == '>') {
                state = NONE;
            } else {
                chars += 1;
            }
        } else if (state == IGNORE) {
            state = GARBAGE;
        }
    }

    printf("%d\n", sum);
    printf("%d\n", chars);

    return 0;
}