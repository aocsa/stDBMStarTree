//---------------------------------------------------------------------------
// app.h - Implementation of the application.
//
// Authors: Marcos Rodrigues Vieira (mrvieira@icmc.sc.usp.br)
// Copyright (c) 2003 GBDI-ICMC-USP
//---------------------------------------------------------------------------
#ifndef appH
#define appH

#define MAXSIZE 30

// Metric Tree includes
#include <arboretum/stMetricTree.h>
#include <arboretum/stPlainDiskPageManager.h>
#include <arboretum/stDiskPageManager.h>
#include <arboretum/stSlimTree.h>
#include <arboretum/stMetricTree.h>
#include <arboretum/stSlimTree.h>
#include <arboretum/stDummyTree.h>

#include "../resultMeasure.h"
// My object
#include <arboretum/stBasicObjects.h>
// My metric
#include <arboretum/stBasicMetricEvaluators.h>

#include <string.h>
#include <fstream>

//---------------------------------------------------------------------------
// class TApp
//---------------------------------------------------------------------------
class TApp{
   public:
      /**
      * This is the type used by the result.
      */
      typedef stBasicArrayObject <double> myBasicArrayObject;

      typedef stBasicManhatanMetricEvaluator <myBasicArrayObject> myBasicMetricEvaluator;

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
      TApp();

      /**
      * Initializes the application.
      *
      * @param pageSize
      * @param quantidade
      * @param prefix
      */
      void Init(unsigned int pageSize, char * prefix, unsigned int kValue, double rangeValue, int dataNumber);

      /**
      * Runs the application.
      *
      * @param prefix
      * @param DataPath
      * @param DataQueryPath
      */
      void Run(char * DataQueryPath);

      void SetFile(int i, char * dataPath){
         DataPath[i] = dataPath;
      }//end SetFile

      /**
      * Deinitialize the application.
      */
      void Done();
      
   private:

      /**
      * The Page Manager for Slim.
      */
      stPlainDiskPageManager * PageManagerSlim;
      stPlainDiskPageManager * PageManagerDummy;

      /**
      * The Slim-Tree.
      */
      mySlimTree * MetricTreeSlim;
      myDummyTree * MetricTreeDummy;

      /**
      * Vector for holding the query objects.
      */
      vector <myBasicArrayObject *> queryObjects;

      char * DataPath[100];

      int DataNumber;

      /**
      * To hold the page size.
      */
      unsigned int PageSize;

      /**
      * To hold the size of the queries.
      */
      unsigned int KValue;
      double RangeValue;

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
      * Adds a point to tree.
      *
      * @param lat Point's latitude.
      * @param lon Point's longitude.
      */
      void AddToTree(myBasicArrayObject * array, MetricTree * metricTree){
         bool ret = metricTree->Add(array);
      }//end AddToTree

      /**
      * Loads the tree from file with a set of points.
      */
      void LoadTree(char * fileName, MetricTree * metricTree);

      void LoadVectorFromFile(char * fileName);

      /**
      * Performs the queries and outputs its results.
      */
      void PerformQueries();

      void PerformKAndRangeQuery(ResultMeasureDiscrete * rMeasureSlim, ResultMeasureDiscrete * rMeasureSeqScan,
                                 int idx);

      void PerformKIntersectionRangeQuery(ResultMeasureDiscrete * rMeasureSlim, ResultMeasureDiscrete * rMeasureSeqScan,
                                          int idx);

      void PerformKOrRangeQuery(ResultMeasureDiscrete * rMeasureSlim, ResultMeasureDiscrete * rMeasureSeqScan,
                                int idx);

      void PerformKUnionRangeQuery(ResultMeasureDiscrete * rMeasureSlim, ResultMeasureDiscrete * rMeasureSeqScan,
                                   int idx);                                        

      void WriteStats();

      void WriteStat(FILE * file, char * treeName, MetricTree * metricTree, clock_t time);

      void WriteToFile(FILE * file, char * algName, Measure * rMeasure, int type);

      void WriteHeader(FILE * file, char * type, bool and);
      
};//end TApp

#endif //end appH
