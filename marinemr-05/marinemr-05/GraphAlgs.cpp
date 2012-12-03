#include "GraphAlgs.h"
#include "Graph.h"
#include <iostream>

using namespace std;

NodeID* best;
double bestSum = 0;
Graph* graph;
int arr_len;


void checkTour(double sum, int j, NodeID* arr){
	//double sum = 0;
	//double sum = sum1;

	int i = j-3; // this value took quite a while to find.
	if(i < 0){
		sum = 0;
		i = 0;
	}

	//i = 0;

	for(; i < arr_len - 1; i++){
		sum += graph->weight(arr[i], arr[i+1]);
	}
	sum += graph->weight(arr[arr_len-1], arr[0]);

	if(sum < bestSum){
		for(int i = 0; i < arr_len; i++){
			best[i] = arr[i];
		}
		
		bestSum = sum;
	}
}

void swap(NodeID* arr, int first, int second){
	NodeID temp = arr[first];

	arr[first] = arr[second];
	arr[second] = temp;
}

/*
void findBestTour(int cur, NodeID* arr){
	double sum = 0;
	for(int i = 0; i < cur - 1; i++){
		sum += graph->weight(arr[i], arr[i+1]);
	}
	if(sum < bestSum){

		for(int i = cur + 1; i < arr_len; i++){
			swap(arr, i, cur);
			checkTour(sum, cur, arr);
			findBestTour(i, arr);
			swap(arr, i, cur);
		}
	}
}*/

void findBestTour(double sum, int cur, NodeID* arr){

	if(sum < bestSum){

		for(int i = cur + 1; i < arr_len; i++){
			swap(arr, i, cur);

			double d = graph->weight(arr[cur-1], arr[cur]);
			sum += d;
			checkTour(sum, cur, arr);
			findBestTour(sum, i, arr);

			swap(arr, i, cur);
		}
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

	NodeID* arr = setup(G);

	findBestTour(0.0,1, arr);

	vector<NodeID> vect;

	for(int i = 0; i < arr_len; i++){
		vect.push_back(best[i]);
	}

	return make_pair(vect, bestSum);
}
