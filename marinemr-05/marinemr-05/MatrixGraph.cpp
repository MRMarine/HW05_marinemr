#include "MatrixGraph.h"

using namespace std;

MatrixGraph::MatrixGraph(unsigned num_nodes){
	M.resize(num_nodes);
	num_edges = 0;

	for(int i = 0; i < (int)num_nodes; i++){
		M[i].resize(num_nodes);

		for(int j = 0; j < (int)num_nodes; j++){
			M[i][j] = 0; // is this needed?
		}
	}
}

MatrixGraph::~MatrixGraph(){

}

void MatrixGraph::addEdge(NodeID u, NodeID v, EdgeWeight weight){
	M[u][v] = weight;
	M[v][u] = weight;
	num_edges++;
}

EdgeWeight MatrixGraph::weight(NodeID u, NodeID v) const{
	return M[u][v];
}

unsigned MatrixGraph::degree(NodeID u) const{
	return getAdj(u).size();
}

unsigned MatrixGraph::size() const{
	return M.size();
}

unsigned MatrixGraph::numEdges() const{
	return num_edges;
}

std::list<NWPair> MatrixGraph::getAdj(NodeID u) const	{
	EList list;
	
	for(int i = 0; i < (int)(M[u].size()); i++){
		if(M[u][i] != 0){
			list.push_back(make_pair(i, M[u][i]));
		}
	}

	return list;
}