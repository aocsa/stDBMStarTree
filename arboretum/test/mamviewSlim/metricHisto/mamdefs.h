
#ifndef __MANDEFS_H
#define __MANDEFS_H

#include "../../../include/arboretum/stMetricTree.h"
#include "../../../include/arboretum/stSlimTree.h"
#include "../../../include/arboretum/stBasicObjects.h"
#include "../../../include/arboretum/stBasicMetricEvaluators.h"
#include "../../../include/arboretum/stMemoryPageManager.h"
#include "../../../include/arboretum/stDiskPageManager.h"
#include "../../../include/arboretum/stMAMView.h"
// My object
#include <gbdi/metrichistogram.h>

using namespace std;
using namespace GBDI;

/**
* The result type.
*/
typedef stResult < tMetricHistogram > myResult;

/**
* The generic metric tree for the pair myObject/myEvaluator.
*/
typedef stMetricTree < tMetricHistogram, tMetricHistogramEvaluator > myMetricTree;

/**
* The Slim-Tree for the pair myObject/myEvaluator.
*/
typedef stSlimTree <tMetricHistogram, tMetricHistogramEvaluator> mySlimTree;

#define PAGESIZE (1024 * 8)

#endif //__MANDEFS_H
 