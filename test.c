#include "minheap.h"
#include <iostream>


int main()
{
	using namespace sapph_dijkstra;
	double distances[] = {-1, 0.0,5,8,3,9,0.1,4,5,2};
	size_t size = sizeof(distances)/sizeof(*distances);
	std::vector<Node> nodes(size);
	for(int i = 0; i<size; i++)
	{
		nodes[i] = Node(std::vector<node_index_t>(0), i, distances[i]);
	}

	MinHeap h(nodes);
	for(int i =0; i<size; i++)
	{
		std::cout << std::endl;
		std::cout << h << std::endl;
		h.extract_min();
	}

	MinHeap h2(nodes);
	std::cout << h2 << std::endl;;
	h2.decrease_key(5, 1.5);
	std::cout << h2 << std::endl;;
	
	return 0;
}
