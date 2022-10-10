#include "Node.hpp"

bool operator<(const Node &_node1, const Node &_node2)
{
	// reverse!!!
	return _node1.w > _node2.w;
}
