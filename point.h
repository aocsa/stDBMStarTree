
#ifndef _POINT_H_
#define _POINT_H_

#include <cassert>
#include <vector>
#include <ostream>

#define DIMENSION 3

#define PointToXYZ(p) p[0], p[1], p[2]
// Error codes
enum Error {
	Enot,	// no error
	Edim,	// error: dim of point invalid for operation
	Esum	// error: sum not affine (cooefs add to 1)
};
enum booleano {FALSE_B=0, TRUE_B=1, ERROR_B= -1 };


class Point{
protected:
	Error err;           // error indicator

public:
	std::vector<double> myPoint;

	//----------------------------------------------------------
	// Lots of Constructors (add more as needed)
	Point(int dim = DIMENSION) : myPoint(dim) {
		for (int i=0; i < this->dim(); i++){
			myPoint[i] = 0;
		}
	} 
	Point(const Point& p) : myPoint(p.dim()){
		for (int i=0; i < dim(); i++){
			myPoint[i] = p.myPoint[i];
		}
		err=Enot;
	}
	// Destructor
	~Point() {};

	void insertArray(double v[], int dim) {
		this->myPoint.clear();
		for (int i = 0; i < dim ; i++)
		{
			myPoint.push_back(v[i]);
		}
	}
	void insertArray(float v[], int dim) {
		this->myPoint.clear();
		for (int i = 0; i < dim ; i++)
		{
			myPoint.push_back(v[i]);
		}
	}
	//----------------------------------------------------------
	friend std::ostream& operator<<( std::ostream&, const Point&);

	// Assignment "=": use the default to copy all members
	int dim() const{ return this->myPoint.size(); }      // get dimension
	
	//----------------------------------------------------------
	// Comparison (dimension must match, or not)
	bool operator == ( const Point&);
	bool operator != ( const Point&);
	void operator = ( const Point&);	
	//----------------------------------------------------------
	// Point and Vector Operations (always valid) 
	Point  operator-( const Point&);       // Vector difference
	Point  operator+( const Point&);      // +translate
	
	Point  operator*( const Point&);       // Vector difference
	Point  operator/( const Point&);      // +translate
	
	Point& operator+=( const Point&);     // inc translate
	Point& operator-=( const Point&);     // dec translate
	
	double& operator [] (int idx)  {
		assert(idx < dim()); 
		return this->myPoint[idx];
	}
	double operator [] (int idx)  const{
		return this->myPoint[idx];
	}

	// Scalar Multiplication
	friend Point operator*( int, const Point&);
	friend Point operator*( double, const Point&);
	friend Point operator*( const Point&, double);
	// Scalar Division
	friend Point operator/( const Point&, double);

	friend Point operator+( const Point&, double);
	friend Point operator-( const Point&, double);

	//----------------------------------------------------------
	// Point Relations
	static double distance( const Point&, const Point&);         // Distance
	//----------------------------------------------------------
	// Error Handling
	void  clerr() { err = Enot;}            // clear error
	int   geterr() { return err;}           // get error
	char* errstr();                         // return error string

};
//-------------------------------------------------------------


#endif //POINT_H_
