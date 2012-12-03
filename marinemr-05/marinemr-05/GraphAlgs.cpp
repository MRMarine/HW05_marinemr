#include "GraphAlgs.h"
#include "Graph.h"
#include <iostream>

using namespace std;

NodeID* best;
double bestSum = 0;
Graph* graph;
int arr_len;

//bool check;

void checkTour(NodeID* arr){
	double sum = 0;

	for(int i = 0; i < arr_len - 1; i++){
		sum += graph->weight(arr[i], arr[i+1]);
	}
	sum += graph->weight(arr[arr_len-1], arr[0]);

	if(sum < bestSum){
		for(int i = 0; i < arr_len; i++){
			best[i] = arr[i];
		}
		
		bestSum = sum;
		//check = false;
	}
}

void swap(NodeID* arr, int first, int second){
	NodeID temp = arr[first];

	arr[first] = arr[second];
	arr[second] = temp;
}

void findBestTour(int cur, NodeID* arr){
	for(int i = cur + 1; i < arr_len; i++){
		swap(arr, i, cur);
		checkTour(arr);
		findBestTour(i, arr);
		swap(arr, i, cur);
	}
}

NodeID* setup(Graph* G){
	list<NWPair> pairs = G->getAdj(0);

	arr_len = G->size();
	graph = G;

	NodeID* arr = new NodeID[arr_len];
	best = new NodeID[arr_len];

	list<NWPair>::const_iterator it;

	for(int i = 0; i < arr_len; i++){
		arr[i] = i;
		best[i] = i;
	}

	for(int i = 0; i < arr_len - 1; i++){
		bestSum += graph->weight(arr[i], arr[i+1]);
	}
	bestSum += graph->weight(arr[arr_len-1], arr[0]);

	return arr;
}

std::pair<std::vector<NodeID>, EdgeWeight> TSP(Graph* G){
	//check = true;

	NodeID* arr = setup(G);

	findBestTour(0, arr);

	vector<NodeID> vect;

	for(int i = 0; i < arr_len; i++){
		vect.push_back(best[i]);
	}

	return make_pair(vect, bestSum);
}