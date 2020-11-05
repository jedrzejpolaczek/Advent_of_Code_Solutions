#include <iostream>	//std::cout
#include <fstream>	//std::ifstream
#include <vector>	//std::vector


int main(int argc, char ** argv)
{
    std::ifstream input(argv[1]);
    std::vector<int> firewalls(99);

    if (input) {
        std::string colon;
        for (int idx, layers; input >> idx >> colon >> layers;)
            firewalls[idx] = layers;
    }

    input.close();

    int severity = 0;
    int delay = 0;

    for (bool found = true; found; delay++) {
        found = false;

        for (int i = 0; i < firewalls.size() && (!found || delay == 0); i++) {
            if (firewalls[i] > 0 && (delay + i) % (2 * firewalls[i] - 2) == 0) {
				if (delay == 0) 
					severity += i * firewalls[i];
                found = true;
            }
        }
    }

    std::cout << "Severity: " << severity << std::endl;
    std::cout << "Delay: " << delay - 1 << std::endl;

    return 0;
}