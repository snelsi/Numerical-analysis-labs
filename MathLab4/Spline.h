#include <vector>

// The coefficients of the polynom
struct Coefficients
{
	float a;   // constant
	float b;   // 1st order coefficient
	float c;   // 2nd order coefficient
	float d;   // 3rd order coefficient
	float x;   // starting x value
};


struct Spline
{
	// The fitted points
	std::vector< float > myX;
	std::vector< float > myY;

	// The coefficients of the spline curves between all points
	std::vector< Coefficients > coeff;

	// Constructor
	Spline(std::vector< float > & x, std::vector< float > & y);


	float getY(float x);
};
