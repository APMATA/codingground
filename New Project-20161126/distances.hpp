#ifndef distances_class

#include <cmath>
#include "point.hpp"

namespace dst {
	
	template<typename t, typename t2, typename t3> t powered(Point<t> p1, Point<t> p2,
	t2 p, t3 r) {
		
		t acc = 0;
        for(unsigned i = 0; i < p1.dimension(); i++)
            acc += pow(abs(p1[i] - p2[i]), p);
        acc = pow(acc, (t)1/r);
		
		return acc;
	}
	
	template<typename t> t euclidean(Point<t> p1, Point<t> p2) {
	    return powered(p1, p2, 2, 2);
	}
	
	template<typename t> t sqEuclidean(Point<t> p1, Point<t> p2) {
	    return powered(p1, p2, 2, 1);
	}
	
	template<typename t> t manhattan(Point<t> p1, Point<t> p2) {
	    return powered(p1, p2, 1, 1);
	}
	
};

#define distances_class
#endif