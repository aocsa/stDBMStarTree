
#ifndef __fmutil_H
#define __fmutil_H

#include <ostream>

#include "../../include/slimtree/stBasicObjects.h"
#include "../../include/slimtree/stBasicMetricEvaluators.h"
#include "../../include/slimtree/stFastmapper.h"

typedef stBasicArrayObject <double, int> tMyObject;
typedef stBasicEuclideanMetricEvaluator <tMyObject> tMyEvaluator;
typedef stFastMapper < tMyObject, tMyEvaluator > tMyFastMapper;

ostream & operator << (ostream & out, tMyObject * obj);


#endif //__fmutil_H
 