#include "GraphAlgs.h"

int* best;
int bestSum = 0;
Graph* graph;

void checkTour(int* arr){
	int sum;
	for(int i = 0; i < graph->size(); i++){
		sum += graph->weight(i, i+1);
	}

	if(sum < bestSum){
		bestSum = sum;
		best = arr;
	}
}

void findBestTour(int cur, int len, int* arr){
	for(int i = cur + 1; i < len; i++){
		swap(arr[i], arr[cur]);
		findBestTour(i, len, arr);
		swap(arr[i], arr[cur]);
	}
}

std::pair<std::vector<NodeID>, EdgeWeight> TSP(Graph* G){

}