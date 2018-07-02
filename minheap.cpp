#include "minheap.h"

#include <limits>
#include <iostream>
namespace sapph_dijkstra
{


	void Node::set_distance(double dist)
	{
		m_distance = dist;
	}
	std::ostream& operator<<(std::ostream& stream, const MinHeap& heap)
	{
		const int num_slots = heap.heap_size/2;
		stream << "Size: "<< heap.heap_size << std::endl;
		for(int i = 1, count = 1;i<=heap.heap_size; i*=2, count++)
		{
			int maxj = 2*i;
			for(int j = i; j<maxj && j<=heap.heap_size; j++)
			{
				node_index_t node_idx = heap.heap[j-1];
				Node node = heap.nodes[node_idx];
				stream << node_idx << "(" << node.distance() << ")" << ' ';
			}
			stream << std::endl;
		}
		return stream;
	}
	template <class T>
	Array<T>::Array(size_t size): m_data(size)
	{}

	double Node::distance() const
	{
		return m_distance;
	}
	template <class T>
	Array<T>::Array(const std::vector<T> &vec): m_data(vec)
	{}

	template <class T>
	T& Array<T>::operator[](size_t idx)
	{
		return m_data[idx];
	}
	
	template <class T>
	const T& Array<T>::operator[](size_t idx) const
	{
		return m_data[idx];
	}


	//normal constructor
	Node::Node(const std::vector<node_index_t> &that_neighbours, node_index_t node_idx, double dist):
		neighbours(that_neighbours), m_distance(dist), node_index(node_idx)
	{
		
	}

	MinHeap::MinHeap(const std::vector<Node> &nodes): 
		num_nodes(nodes.size()),
		heap_size(nodes.size()),
		internal_indices(nodes.size()), 
		nodes(nodes),
		heap(nodes.size())
	{
		for(size_t i = 0; i<num_nodes; i++)
		{
			internal_indices[i] = i;
			heap[i] = i;
		}
		for(int64_t i = (heap_size-1)/2; i>=0; i--)
		{
			min_heapify(i);
		}
	}

	bool MinHeap::decrease_key(node_index_t node_idx, double new_distance)
	{
		Node* n = &nodes[0]+node_idx;
		if(node_idx >= num_nodes)
		{
			return false;
		}
		else if(n->distance() < new_distance)
		{
			return false;
		}
		else
		{
			n->set_distance(new_distance);
			heap_index_t i = internal_indices[node_idx];
			heap_index_t par = parent(i);
			while(i>0 && (get_node(i)->distance() < get_node(par)->distance()) ) 
			{
				swap_heap_elems(i, par);
				i=par;
				par = parent(i);
			}
			return true;
		}
	}
	void MinHeap::min_heapify(size_t root)
	{
		Node* root_node = get_node(root);
		if(root_node != nullptr)
		{
			const size_t left_idx = left(root);
			const size_t right_idx = right(root);
			const Node* const left_node = get_node(left_idx);
			const Node* const right_node = get_node(right_idx);
			//if the root has both children...
			if(left_node != nullptr && right_node != nullptr)
			{
				//if the root node isn't the smallest element, then do a swap with the smallest element
				if(root_node->m_distance > left_node->m_distance || root_node->m_distance > right_node->m_distance)
				{
					//if the left node is the smallest node 
					if(left_node->m_distance < right_node->m_distance)
					{
						swap_heap_elems(root, left_idx);
						min_heapify(left_idx);
					}
					else
					{
						swap_heap_elems(root, right_idx);
						min_heapify(right_idx);
					}
				}
				//otherwise we don't do anything (min heap property is satisfied)
			}
			//if the only child is has is the left one
			else if(left_node != nullptr)
			{
				//then to satisfy the min heap property we just need to have root le left
				if(left_node->m_distance < root_node->m_distance)
				{
					swap_heap_elems(root, left_idx);
				}
			}
			else if(right_node != nullptr)
			{
				if(right_node->m_distance < root_node->m_distance)
				{
					swap_heap_elems(root, right_idx);
				}
			}
		}
	}

	Node* MinHeap::extract_min()
	{
		Node* result = get_node(0);
		swap_heap_elems(0, heap_size-1);
		heap_size--;
		min_heapify(0);
	}
}
