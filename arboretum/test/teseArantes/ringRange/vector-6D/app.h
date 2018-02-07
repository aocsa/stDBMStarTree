//---------------------------------------------------------------------------
// app.h - Implementation of the application.
//
// Authors: Marcos Rodrigues Vieira (mrvieira@icmc.usp.br)
// Copyright (c) 2003 GBDI-ICMC-USP
//---------------------------------------------------------------------------
#ifndef appH
#define appH

#define MAXSIZE 6

// Metric Tree includes
#include <arboretum/stMetricTree.h>
#include <arboretum/stPlainDiskPageManager.h>
#include <arboretum/stSlimTree.h>
#include <arboretum/stDummyTree.h>

#include <fstream>

// My object
#include <arboretum/stBasicObjects.h>
// My metric
#include <arboretum/stBasicMetricEvaluators.h>

#include "../../resultMeasure.h"
#include <string.h>
//---------------------------------------------------------------------------
// class TApp
//---------------------------------------------------------------------------
class TApp{
   public:
      /**
      * This is the type used by the result.
      */
      typedef stBasicArrayObject <double> myBasicArrayObject;

      typedef stBasicEuclideanMetricEvaluator <myBasicArrayObject> myBasicMetricEvaluator;

      typedef stResult < myBasicArrayObject > myResult;

      typedef stMetricTree <myBasicArrayObject, myBasicMetricEvaluator> MetricTree;  

      /**
      * This is the type of the Slim-Tree defined by TPoint and
      * TPointDistanceEvaluator.
      */
      typedef stSlimTree < myBasicArrayObject, myBasicMetricEvaluator > mySlimTree;

      /**
      * This is the type of the Dummy Tree defined by TPoint and
      * TPointDistanceEvaluator.
      */
      typedef stDummyTree < myBasicArrayObject, myBasicMetricEvaluator > myDummyTree;


      /**
      * Creates a new instance of this class.
      */
      TApp(){
         PageManagerSlim = NULL;
         PageManagerDummy = NULL;
         MetricTreeSlim = NULL;
         MetricTreeDummy = NULL;
      }//end TApp

      /**
      * Initializes the application.
      *
      * @param pageSize the size of the page.
      * @param quantidadeRange the maximum number of range queries.
      * @param quantidadeK the maximum number of nearest queries.
      * @param tieList the status of the tie list.
      * @param prefix the prefix name to be used to save the tree.
      */
      void Init(unsigned int pageSize, stDistance maxDistance,
                unsigned int startRange, unsigned int quantidadeRange,
                double percentage, char * prefix);

      /**
      * Runs the application.
      *
      * @param DataPath
      * @param DataQueryPath
      */
      void Run(char * DataPath, char * DataQueryPath);

      /**
      * Deinitialize the application.
      */
      void Done();

   private:

      /**
      * The Page Manager for Slim.
      */
      stPageManager * PageManagerSlim;

      /**
      * The Page Manager for Dummy.
      */
      stPageManager * PageManagerDummy;

      /**
      * The Metric Tree for Slim-Tree.
      */
      mySlimTree * MetricTreeSlim;

      /**
      * The Metric Tree for Dummy-Tree.
      */
      myDummyTree * MetricTreeDummy;

      /**
      * Vector for holding the query objects.
      */
      vector <myBasicArrayObject *> queryObjects;

      /**
      * Vector for holding the radius of the query objects.
      */
      vector <double> radiusqueryObjects[13];

      /**
      * To hold the page size.
      */
      unsigned int PageSize;

      /**
      * To hold the size of the nearest queries.
      */
      double Percentage;
      double MaxDistance;

      /**
      * To hold the size of the range queries.
      */
      unsigned int StartRange;
      unsigned int QuantidadeRange;

      /**
      * To store the prefix of files.
      */
      string Prefix;

      /**
      * Creates a disk page manager. It must be called before CreateTree().
      */
      void CreateDiskPageManager();

      /**
      * Creates a tree using the current PageManager.
      */
      void CreateTree();

      /**
      * Adds a city to tree.
      *
      * @param lat City's latitude.
      * @param lon City's longitude.
      */
      void AddToTree(myBasicArrayObject * array, MetricTree * metricTree){
         metricTree->Add(array);
      }//end AddToTree

      /**
      * Loads the tree from file with a set of cities.
      */
      void LoadTree(char * fileName, MetricTree * metricTree);

      /**
      * Loads the vector for queries.
      */
      void LoadVectorFromFile(char * fileName);

      /**
      * Performs the queries and outputs its results.
      */
      void PerformQueries();

      /**
      * Performs a query and outputs its results.
      * K-NEAREST NEIGHBOUR QUERY AND RANGE QUERY WITH NEW ALGORITHM
      *
      * idx the maximum size of the nearest query.
      * resultSlim the place to be save the results of slimTree.
      * resultDummy the place to be save the results of Dummy.
      */
      void RingRange(ResultMeasure * resultSlim, ResultMeasure * resultDummy);
      void Range(ResultMeasure * resultSlim, ResultMeasure * resultDummy);

      /**
      * Performs a query and outputs its results.
      * K-NEAREST NEIGHBOUR QUERY OR RANGE QUERY WITH NEW ALGORITHM
      *
      * idx the maximum size of the nearest query.
      * resultSlim the place to be save the results of slimTree.
      * resultDummy the place to be save the results of Dummy.
      */
      void RingRangeIntersection(ResultMeasure * resultSlim, ResultMeasure * resultDummy);

      /**
      * This method saves the results to the file.
      *
      * file the file to be save.
      * algName the string to be save in the file.
      * rMeasure the results to be save.
      * type the type of result (1=distFunc, 2=DiscAccess, 3=Time)
      */
      void WriteToFile(FILE * file, char * algName, ResultMeasure * rMeasure, int type);

      /**
      * This method saves the header of the file.
      *
      * file the file to be save.
      * type the type of the query (true=range, false=nerest).
      * and the type of operator (true= And Operator, false= Or Operator). 
      * radius the radius size of the range query.
      */
      void WriteHeader(FILE * file, char * type, bool and, double radius);

};//end TApp

#endif //end appH
