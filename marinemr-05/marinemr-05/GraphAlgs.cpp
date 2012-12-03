#include "GraphAlgs.h"
#include "Graph.h"

using namespace std;

int* best;
double bestSum = 0;
Graph* graph;
int arr_len;

bool check;

void checkTour(int* arr){
	double sum = 0;
	arr_len = 0;

	for(int i = 0; i < (int)(graph->size()); i++){
		sum += graph->weight(i, i+1);
		arr_len++;
	}

	if(sum < bestSum || check){
		bestSum = sum;
		best = arr;

		check = false;
	}
}

void swap(int* arr, int first, int second){
	int temp = arr[first];

	arr[first] = arr[second];
	arr[second] = temp;
}

void findBestTour(int cur, int len, int* arr){
	for(int i = cur + 1; i < len; i++){
		swap(arr, i, cur);
		findBestTour(i, len, arr);
		swap(arr, i, cur);
	}
}

std::pair<std::vector<NodeID>, EdgeWeight> TSP(Graph* G){
	check = true;
	list<NWPair> pairs = G->getAdj(0);
	
	int j = 0;
	int* arr = new int[pairs.size()];

	list<NWPair>::const_iterator it;

	int k = 0;
	for(it = pairs.begin(); it != pairs.end(); it++){
		NWPair pairIT = (*it);

		arr[k++] = pairIT.first;
	}

	findBestTour(1, G->size(), arr);

	vector<NodeID> vect;

	for(int i = 0; i < arr_len; i++){
		vect.push_back(best[i]);
	}

	return make_pair(vect, bestSum);
}