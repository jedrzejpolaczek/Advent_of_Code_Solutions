#include <iostream>			//std::cout
#include <fstream>			//std::ifstream
#include <unordered_map>	//std::unordered_map

using namespace std;

void reduceDirections(const string &direction, unordered_map<string, int> &path_directions);

int main(int argc, char const* argv[])
{
    ifstream input("puzzle_input");
    unordered_map<string, int> path_directions({{"n", 0}, {"s", 0}, {"ne", 0}, {"se", 0}, {"nw", 0}, {"sw", 0}});
    int max_steps = 0;
    int steps = 0;

    if (input) {
        string direction;
        while (getline(input, direction, ',')) {

            int sum = 0;

            reduceDirections(direction, path_directions);

            for (auto &it : path_directions)
                sum += it.second;

            max_steps = max(sum, max_steps);
        }
    }

    input.close();

    for (auto &it : path_directions)
        steps += it.second;

    cout << "Steps: " << steps << endl;
    cout << "Max steps: " << max_steps << endl;

    return 0;
}

void reduceDirections(const string &direction, unordered_map<string, int> &path_directions) {

    string opposite = direction;
    opposite[0] = (opposite[0] == 'n') ? 's' : 'n';

    if (opposite.length() > 1)
        opposite[1] = (opposite[1] == 'e') ? 'w' : 'e';

    if (path_directions[opposite] != 0) {
        path_directions[opposite]--;
        return;
    }

    if (direction == "n" || direction == "s") {
        if (path_directions[opposite + "e"] != 0) {
            path_directions[opposite + "e"]--;
            path_directions[direction + "e"]++;
        } else if (path_directions[opposite + "w"] != 0) {
            path_directions[opposite + "w"]--;
            path_directions[direction + "w"]++;
        } else {
            path_directions[direction]++;
        }
    } else {
        if (path_directions[opposite.substr(0, 1)] != 0) {
            path_directions[opposite.substr(0, 1)]--;
            path_directions[opposite.substr(0, 1) + direction.substr(1, 1)]++;
        } else if (path_directions[direction.substr(0, 1) + opposite.substr(1, 1)] != 0) {
            path_directions[direction.substr(0, 1) + opposite.substr(1, 1)]--;
            path_directions[direction.substr(0, 1)]++;
        } else {
            path_directions[direction]++;
        }
    }

    return;
}