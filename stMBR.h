/* 
 * File:   stMBR.h
 * Author: aocsa
 *
 * Created on January 17, 2007, 6:37 PM
 */

#ifndef _stMBR_H
#define	_stMBR_H

#include <vector>
#include <ostream>

#include <arboretum/stObject.h>
#include <arboretum/stTypes.h>
#include <arboretum/stUtil.h>

#include "point.h"

class stMBR {
protected:
	stMBR() {}
	
public:
	virtual void	    AddInterval(int idx, stDistance origin) = 0;
	virtual void	    AddInterval(int idx, stDistance begin, stDistance end) = 0;
	virtual stSize	    GetDimension() const = 0;
	virtual void	    SetDimension() = 0;
	virtual stDistance& GetBegin(int idx) = 0;
	virtual stDistance& GetEnd(int idx) = 0;
	virtual stDistance GetBegin(int idx) const = 0;
	virtual stDistance GetEnd(int idx) const = 0;
	
	virtual stDistance  GetArea	() = 0;

	virtual stDistance  GetMinDist(const Point &p) = 0;
	virtual stDistance  IntersectionArea(stMBR* mbr) = 0;
	virtual bool	    Intersection(stMBR* mbr) = 0;
	virtual stMBR*		GetUnionMBR(stMBR* mbr) = 0;
};

#endif	/* _stMBR_H */