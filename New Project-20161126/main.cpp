#include <iostream>
#include <cmath>
#include <cstdlib>
#include "point.hpp"
#include "distances.hpp"

using namespace std;

#define Point Point<float>

Point* points, *centroids;
unsigned N, D, K;
pair<unsigned, float>* idxs; // Array with cluster indexes to which points belong and their distances

void read() {
	freopen("input.txt", "r", stdin);
	
	scanf("%u %u %u", &N, &D, &K);
	points = new Point[N];
	centroids = new Point[K];
	idxs = new pair<unsigned, float>[N];
	
	for(unsigned i = 0; i < N; i++) {
		points[i] = Point(D);
		for(unsigned j = 0; j < D; j++)
			scanf("%f", &points[i][j]);
	}
	
	fclose(stdin);
}

void write() {
    freopen("output.txt", "w", stdout);
    
    for(unsigned n = 0; n < N; n++) {
        printf("%u\n", idxs[n].first);
    }
    
    fclose(stdout);
}

/*
 * Random integer number from [0; n), n <= RAND_MAX.
*/
unsigned randn(unsigned n) {
	float f = (float)rand() / RAND_MAX * (n-1);
	return (unsigned)f;
}

/*
 * Random number from [0; f]
*/
float randf(float f) {
	return f * rand() / RAND_MAX;
}

pair<unsigned, float> nearest(Point P, unsigned chosen_centroids = K) {
	Point C = centroids[0];
	pair<unsigned, float> min = make_pair(0, dst::euclidean(P, C));
	for(unsigned i = 1; i < chosen_centroids; i++) { // For each centroid
		C = centroids[i]; // Choose one
		pair<unsigned, float> idx = make_pair(i, pow(dst::euclidean(P, C), 2)); // Calculate squared distance from point to it
		if (idx.second < min.second) { // If its distance less than previous minimal
			min = idx; // Make it minimal
		}
	}
	
	return min;
}

void kmeanspp(unsigned K) {
	
	/*
		1. Choose one center uniformly at random from among the data points.
		2. For each data point x, compute D(x), the distance between x and the nearest center that has already been chosen.
		3. Choose one new data point at random as a new center, using a weighted probability distribution where a point x is chosen with probability proportional to D(x)2.
		4. Repeat Steps 2 and 3 until k centers have been chosen.
	*/
	
	/*
		(1)
	*/
	centroids[0] = points[ randn(N) ]; // Choose first centroid random from all of points
	unsigned chosen_centroids = 1; // Number of already assigned centroids
	
	do {
		/*
			(2)
		*/
		float* distances = new float[N]; // Array of distances between points and their centroids
		float S = 0; // Sum of all distances between points and their nearest centroids
		for(unsigned n = 0; n < N; n++) { // For each point
			Point P = points[n];
			pair<unsigned, float> idx = nearest(P, chosen_centroids);
			idxs[n] = idx;
			S += idx.second; // Add it to whole sum of distances
		}
		/*
			(3)
		*/
		float R = randf(S);
		float S2 = 0;
		for(unsigned n = 0; n < N; n++) {
			S2 += idxs[n].second;
			if (S2 >= R) {
				centroids[chosen_centroids] = points[n];
				chosen_centroids++;
				break;
			}
		}
	}
	/*
		(4)
	*/
	while(chosen_centroids != K);
}

void kmeans(unsigned K) {
	kmeanspp(K); // Choose initial points
	
	Point* mass_center = new Point[K];
	unsigned* nink = new unsigned[K];

	unsigned changed;
    do {
		for(unsigned k = 0; k < K; k++) {
		    mass_center[k] = Point(D);
			nink[k] = 0;
		}
		
		for(unsigned n = 0; n < N; n++) { // For each point
			Point P = points[n];
			pair<unsigned, float> idx = nearest(P);
			changed = 0;
			if (idxs[n].first != idx.first) {
				idxs[n] = idx;
				changed++;
				mass_center[idx.first] += P;
				nink[idx.first]++;
			}
		}
		
		for(unsigned k = 0; k < K; k++) {
			mass_center[k] /= nink[k];
		}
	}
	while(changed > 0.999 * N); // End when 99.9% of points are fixed
}

int main()
{

    read();
    kmeans(K);
    write();
    
}
