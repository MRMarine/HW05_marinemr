#include "ListGraph.h"

using namespace std;

ListGraph::ListGraph(int numNodes)	{
	edgeList.resize(numNodes);
	num_edges = 0;
}


ListGraph::~ListGraph(){

}

void ListGraph::addEdge(NodeID u, NodeID v, EdgeWeight weight)	{
	EList::const_iterator it;

	bool found = false;

	for(it = edgeList[u].begin(); it != edgeList[u].end(); it++){
		NWPair pairIT = (*it);

		// update pair
		if(pairIT.first == v){
			pairIT.second = weight;
			return;
		}
	}

	if(found){
		for(it = edgeList[v].begin(); it != edgeList[v].end(); it++){
		NWPair pairIT = (*it);

			// update pair
			if(pairIT.first == u){
				pairIT.second = weight;
				return;
			}
		}
	}

	// create new
	NWPair newPair = make_pair(v, weight);
	edgeList[u].push_back(newPair);

	newPair = make_pair(u, weight);
	edgeList[v].push_back(newPair);

	num_edges++;
}

EdgeWeight ListGraph::weight(NodeID u, NodeID v) const{
	EList::const_iterator it;

	for(it = edgeList[u].begin(); it != edgeList[u].end(); it++){
		NWPair tPair = (*it); // operator overloading.  Not really a pointer.
		
		if(tPair.first == v){
			return tPair.second;
		}
	}
	
	// insert v -> u as well to be semetrical
	
	return -1.0; // no connection.
}

std::list<NWPair> ListGraph::getAdj(NodeID u) const{
	return edgeList[u]; // deep copy
}

unsigned ListGraph::degree(NodeID u) const	{
	return edgeList[u].size();
}

unsigned ListGraph::size() const	{
	return edgeList.size();
}

unsigned ListGraph::numEdges() const	{
	return num_edges;
}