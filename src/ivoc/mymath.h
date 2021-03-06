#ifndef mymath_h
#define mymath_h

#include <OS/math.h>
#include <InterViews/geometry.h>

extern "C" {
extern int nrn_isdouble(double*, double, double);
}

class Extension;

class MyMath {
public:
	// increase all around in screen coords
	static void extend(Extension&, Coord);
	static void extend(Extension&, const Extension&);
	
	static void minmax(Coord& min, Coord& max);
	static boolean inside(Coord x, Coord min, Coord max);

	static float min(int count, const float*);
	static float max(int count, const float*);
	
	static boolean inside(
		Coord x, Coord y,
		Coord left, Coord bottom, Coord right, Coord top
	);

	// within epsilon distance from the infinite line
	static boolean near_line(
		Coord x, Coord y,
		Coord x1, Coord y1, Coord x2, Coord y2,
		float epsilon
	);

	// within epsilon distance from the line segment
	static boolean near_line_segment(
		Coord x, Coord y,
		Coord x1, Coord y1, Coord x2, Coord y2,
		float epsilon
	);

	// returns distance between point and line segment
	static float distance_to_line_segment(
		Coord x, Coord y,
		Coord x1, Coord y1, Coord x2, Coord y2
	);

	// returns distance between point and line
	static float distance_to_line(
		Coord x, Coord y,
		Coord x1, Coord y1, Coord x2, Coord y2
	);

	
	// returns square norm
	static float norm2(Coord x, Coord y) {
		return x*x + y*y;
	}

	// unit length vector perpindicular to vector (x, y)
	static boolean unit_normal(Coord x, Coord y, Coord* perp);
	
	// returns range extended to nearest 1.5 digit accuracy.
	// ie. digit is 1, 2, or 5
	static void round_range(Coord x1, Coord x2, double& y1, double& y2,
		int& ntic);
	static void round_range_down(Coord x1, Coord x2, double& y1, double& y2,
		int& ntic);

	enum {Expand, Contract, Higher, Lower};
	static double round(float& x1, float& x2, int direction, int digits);
	 
	static void box(Requisition&, Coord& x1, Coord& y1, Coord& x2, Coord& y2);

	static double anint(double); /* round toward nearest integer */
	static double resolution(double); // 100, 10, .1,... least significant digit

	static boolean lt(double x, double y, double e) { return x < (y-e); }
	static boolean le(double x, double y, double e) { return x <= (y+e); }
	static boolean eq(double x, double y, double e) { return Math::equal(x,y,e);}
};

inline void MyMath::extend(Extension& e, const Extension& x) {
	e.set_xy(nil, e.left() + x.left(), e.bottom() + x.bottom(),
		e.right() + x.right(), e.top() + x.top());
}

inline void MyMath::extend(Extension& e, Coord x) {
	e.set_xy(nil, e.left() - x, e.bottom() - x, e.right() + x, e.top() + x);
}

inline void MyMath::minmax(Coord& x, Coord& y) {
	if (y < x) {Coord z = x; x = y; y = z;}
}

inline boolean MyMath::inside(Coord x, Coord x1, Coord x2) {
	return (x >= x1 && x <= x2);
}

inline boolean MyMath::inside(Coord x, Coord y, Coord x1, Coord y1, Coord x2, Coord y2) {
	return inside(x, x1, x2) && inside(y, y1, y2);
}

#endif
