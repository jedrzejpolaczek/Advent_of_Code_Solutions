#include <fstream>		//std::ifstream
#include <iostream>		//std::cout
#include <set>			//std::set
#include <algorithm>	//std::count
#include <vector>		//std::vector
#include <deque>		//std::deque
#include <sstream>		//std::istringstream

int main(int argc, char ** argv) { 
	std::ifstream in (argv[1]);

	std::vector<std::vector<int>> edges;
	std::vector<int>              group;

	for (std::string line; std::getline(in, line); )
	{
		int vertex_a, vertex_b;
		std::string _;
		std::istringstream line_stream (line);
		line_stream >> vertex_a >> _;
		for (edges.push_back({}); line_stream >> vertex_b; line_stream >> _)
			edges[vertex_a].push_back(vertex_b);
	}
	group.resize(edges.size(), -1);

	auto vertex = group.begin();
	for (int group_num = 0; vertex != group.end();
			++group_num, vertex = std::find_if(group.begin(), group.end(), [](int g){ return g < 0; }))
	{
		std::deque<int> search_queue;
		search_queue.push_back(vertex - group.begin());
		while (not search_queue.empty())
		{
			int visiting = search_queue.front();
			search_queue.pop_front();
			group[visiting] = group_num;
			std::copy_if(edges[visiting].begin(), edges[visiting].end(), std::back_inserter(search_queue),
						[&](int v){ return group[v] < 0; });
		}
	}

	std::cout << std::count(group.begin(), group.end(), 0) << std::endl;
	std::cout << std::set<int>(group.begin(), group.end()).size() << std::endl;
}