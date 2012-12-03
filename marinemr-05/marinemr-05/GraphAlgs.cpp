#include "GraphAlgs.h"
#include "Graph.h"
#include <iostream>
#include <deque>

using namespace std;

//NodeID* best;
double bestSum = 0;
Graph* graph;
int arr_len;
vector<NodeID> best;


void checkTour(double sum1, int j, vector<NodeID> arr){
	double sum = 0;

	for(int i = 0; i < arr_len - 1; i++){
		sum += graph->weight(arr[i], arr[i+1]);
	}
	sum += graph->weight(arr[arr_len-1], 0);

	if(sum < bestSum){
		/*for(int i = 0; i < arr_len; i++){
			best[i] = arr[i];
		}*/
		
		best = arr;
		bestSum = sum;
	}
}

void swap(vector<NodeID> arr, int first, int second){
	NodeID temp = arr[first];

	arr[first] = arr[second];
	arr[second] = temp;
}

//void half_tours(){
//	vector<NodeID> vec;
//	vector<double> sums;
//
//	for(int j = 0; j < h_size; j++){
//		vec = arrs_h[j];
//		double sum = 0;
//		for(int i = 0; i < arr_len / 2 + 1; i++){
//			sum += graph->weight(vec[i], vec[i+1]);
//		}
//		//sum += graph->weight(arrs_h[arr_len-1], arr[0]);
//		sums.push_back(sum);
//	}
//	
//	sort(sums.begin(),sums.end());
//}

// Cary Willard suggested that I pass sum in somehow, although he mentioned a global variable instead
void findBestTour(int sum, int cur, vector<NodeID> arr){
	// don't redo the sum each time

	sum += graph->weight(arr[cur-1], arr[cur]);

	if(sum < bestSum){
		for(int i = cur + 1; i < arr_len -1; i++){
			swap(arr, i, cur);

			//sum += graph->weight(arr[cur-1], arr[cur]);

			checkTour(sum, cur, arr);
			findBestTour(sum, i, arr);
			swap(arr, i, cur);
		}
	}

	//half_tours();
}

vector<NodeID> setup(Graph* G){
	list<NWPair> pairs = G->getAdj(0);

	arr_len = G->size();
	graph = G;

	vector<NodeID> arr;

	list<NWPair>::const_iterator it;

	for(int i = 0; i < arr_len; i++){
		arr.push_back(i);
		//best.push_back(i);
	}

	best = arr;

	for(int i = 0; i < arr_len - 1; i++){
		bestSum += graph->weight(arr[i], arr[i+1]);
	}
	bestSum += graph->weight(arr[arr_len-1], arr[0]);

	return arr;
}

std::pair<std::vector<NodeID>, EdgeWeight> TSP(Graph* G){

	vector<NodeID> arr = setup(G);

	// if you don't swap the first element, you don't check anything you've already checked but are shifted over.
	// if you don't swap the first element, you only have 1 reverse
	// if you don't check things, you don't spend time
	// correct + fast solution = good grade
	findBestTour(0.0, 1, arr);

	return make_pair(best, bestSum);
}