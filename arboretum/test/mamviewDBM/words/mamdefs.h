
#ifndef __MANDEFS_H
#define __MANDEFS_H

#include "../../../include/arboretum/stMetricTree.h"
#include "../../../include/arboretum/stDBMTree.h"
#include "../../../include/arboretum/stBasicObjects.h"
#include "../../../include/arboretum/stBasicMetricEvaluators.h"
#include "../../../include/arboretum/stMemoryPageManager.h"
#include "../../../include/arboretum/stDiskPageManager.h"
#include "../../../include/arboretum/stMAMView.h"

/**
* Basic object type. It is a double array.
*/
typedef stBasicStringObject <char> myObject;

/**
* The euclidean metric evaluator for myObject.
*/
typedef stBasicLEditMetricEvaluator < myObject > myEvaluator;

/**
* The result type.
*/
typedef stResult < myObject > myResult;

/**
* The generic metric tree for the pair myObject/myEvaluator.
*/
typedef stMetricTree <myObject, myEvaluator> myMetricTree;

/**
* The DBM-Tree for the pair myObject/myEvaluator.
*/
typedef stDBMTree <myObject, myEvaluator> myDBMTree;



#endif //__MANDEFS_H
 