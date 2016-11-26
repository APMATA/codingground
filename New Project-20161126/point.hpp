#ifndef point_class

#include <initializer_list>
#include <stdexcept>

template <typename t> class Point {
private:	
	t* vector;
	unsigned n;
	
public:
	Point() {
	}
	
	Point(unsigned dimension) {
		n = dimension;
		vector = new t[n];
	}
	
	Point(std::initializer_list <t> list) {
	    n = list.size();
	    vector = new t[n];

    	unsigned i = 0;
    	auto it = list.begin(), end = list.end();
    	for (; it != end; it++, i++)
    	    vector[i] = *it;
	}
	
	unsigned dimension() {
	    return n;
	}
	
	t& operator[](unsigned i) {
	    return vector[i];
	}
	
	Point operator*(t s) {
	    Point<t> Pn(n);
	    for (unsigned i = 0; i < n; i++)
	        Pn[i] = vector[i] * s;
	        
	    return Pn;
	}
	
	Point operator*=(t s) {
	    *this = *this * s;
	    return *this;
	}
	
	Point operator/(t s) {
		Point<t> Pn(n);
	    for (unsigned i = 0; i < n; i++)
	        Pn[i] = vector[i] / s;
	        
	    return Pn;
	}

	Point operator/=(t s) {
	    *this = *this / s;
	    return *this;
	}
	
	Point operator+(Point P2) throw(std::length_error) {
	    if (P2.dimension() != n)
	        throw std::length_error("Dimensions are not same");
	    
	    Point<t> Pn(n);
	    for(unsigned i = 0; i < n; i++)
	        Pn[i] = vector[i] + P2[i];
	    return Pn;
	}
	
	Point operator+=(Point<t> P2) {
	    *this = *this + P2;
	    return *this;
	}
	
	Point operator-(Point P2) throw(std::length_error) {
	    if (P2.dimension() != n)
	        throw std::length_error("Dimensions are not same");
	    
	    Point<t> Pn(n);
	    for(unsigned i = 0; i < n; i++)
	        Pn[i] = vector[i] - P2[i];
	    return Pn;
	}
	
	Point operator-=(Point<t> P2) {
	    *this = *this - P2;
	    return *this;
	}
	
	
};

#define point_class
#endif