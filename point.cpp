

#include <cmath>

#include "point.h"
#ifndef max
#define max(a,b)    (((a) > (b)) ? (a) : (b))
#endif


//==================================================================
//------------------------------------------------------------------
// Assign (set) dimension
//------------------------------------------------------------------



bool Point::operator==( const Point& Q)
{
	if (dim() != Q.dim()) return FALSE_B;
	for (int i = 0; i < dim() ; i++)
	{
		if ( this->myPoint[i] != Q.myPoint[i] ) {
			return false;
		}
	}
		
	return true;
}


bool Point::operator!=( const Point& Q)
{
	return !(operator == (Q));
}


void Point::operator=(const Point& p)
{
	err = p.err;           // error indicator
	
	for (int i = 0; i < dim() ; i++)
	{
		this->myPoint[i] = p.myPoint[i];
	}
}
//------------------------------------------------------------------
// Point Vector Operations
//------------------------------------------------------------------


Point Point::operator+( const Point& v)        // +ve translation
{
	Point P(v.dim());
	assert(this->dim() == v.dim());
	for (int i = 0; i < dim() ; i++)
	{
		P[i] = this->myPoint[i] + v.myPoint[i];
	}
	return P;
}


Point Point::operator-( const Point& v)        // -ve translation
{
	Point P(v.dim());
	assert(this->dim() == v.dim());

	for (int i = 0; i < dim() ; i++) {
		P[i] = this->myPoint[i] - v.myPoint[i];
	}
	return P;
}


Point Point::operator*( const Point& v)        // +ve translation
{
	Point P(v.dim());
	assert(this->dim() == v.dim());
	
	for (int i = 0; i < dim() ; i++)
	{
		P[i] = this->myPoint[i] * v.myPoint[i];
	}

	return P;
}


Point Point::operator/( const Point& v)        // -ve translation
{
	Point P(v.dim());
	assert(this->dim() == v.dim());
	for (int i = 0; i < dim() ; i++)
	{
		assert(v.myPoint[i] != 0);
		P[i] = this->myPoint[i] / v.myPoint[i];
	}

	return P;
}


Point& Point::operator+=( const Point& v)        // +ve translation
{
	assert(this->dim() == v.dim());
	for (int i = 0; i < dim() ; i++) {
		this->myPoint[i] += v.myPoint[i];
	}
	return *this;
}


Point& Point::operator-=( const Point& v)        // -ve translation
{
	assert(this->dim() == v.dim());
	for (int i = 0; i < dim() ; i++)
	{
		this->myPoint[i] -= v.myPoint[i];
	}
	return *this;
}

//------------------------------------------------------------------
// Point Scalar Operations (convenient but often illegal)
//        are not valid for points in general,
//        unless they are 'affine' as coeffs of 
//        a sum in which all the coeffs add to 1,
//        such as: the sum (a*P + b*Q) with (a+b == 1).
//        The programmer must enforce this (if they want to).
//------------------------------------------------------------------

std::ostream& operator<<( std::ostream& out,const Point& p) {
	for (int i = 0; i < p.dim(); i++) {
		out << p[i] << ", ";
	}
	return out;
}

Point operator*( int c, const Point& Q) {
	Point P(Q.dim());
	
	for (int i = 0; i < Q.dim() ; i++)
	{
		P[i] = c * Q[i];
	}
	return P;
}

Point operator*( double c, const Point& Q) {
	Point P(Q.dim());
	for (int i = 0; i < Q.dim() ; i++)
	{
		P[i] = c * Q[i];
	}
	return P;
}

Point operator*( const Point& Q, double c) {
	Point P(Q.dim());
	for (int i = 0; i < Q.dim() ; i++)
	{
		P[i] = c * Q[i];
	}
	return P;
}

Point operator/( const Point& Q, double c) {
	Point P(Q.dim());
	assert(c != 0);
	for (int i = 0; i < Q.dim() ; i++)
	{
		P[i] = Q[i]/c;
	}
	return P;
}

//------------------------------------------------------------------
// Point Addition (also convenient but often illegal)
//    is not valid unless part of an affine sum.
//    The programmer must enforce this (if they want to).
//------------------------------------------------------------------

Point operator+( const Point& Q, double c) {
	Point P(Q.dim());
	for (int i = 0; i < Q.dim() ; i++)
	{
		P[i] = Q[i] + c;
	}
	return P;
}

Point operator-( const Point& Q, double c) {
	Point P(Q.dim());
	for (int i = 0; i < Q.dim() ; i++)
	{
		P[i] = Q[i] - c;
	}
	return P;
}


//------------------------------------------------------------------
// Sidedness of a Point wrt a directed line P1->P2
//        - makes sense in 2D only
//------------------------------------------------------------------

//------------------------------------------------------------------
// Error Routines
//------------------------------------------------------------------

char* Point::errstr() {            // return error string
	switch (err) {
	case Enot:
		return "no error";
	case Edim:
		return "error: invalid dimension for operation";
	case Esum:
		return "error: Point sum is not affine";
	default:
		return "error: unknown err value";
	}
}

double Point::distance( const Point&p0, const Point&p1)         // Distance
{
	double sum = 0.0f;
	//sum += (p0.x - p1.x)*(p0.x - p1.x);
	//sum += (p0.y - p1.y)*(p0.y - p1.y);
	//sum += (p0.z - p1.z)*(p0.z - p1.z);
	assert(p0.dim() == p1.dim());
	for (int i = 0; i < p0.dim(); i++) {
		sum += (p0[i] - p1[i])*(p0[i] - p1[i]);
	}
	return sqrt(sum);
}

