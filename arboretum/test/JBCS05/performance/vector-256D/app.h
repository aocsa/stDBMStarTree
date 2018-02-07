//---------------------------------------------------------------------------
// app.h - Implementation of the application.
//
// Authors: Marcos Rodrigues Vieira (mrvieira@icmc.sc.usp.br)
// Copyright (c) 2003 GBDI-ICMC-USP
//---------------------------------------------------------------------------
#ifndef appH
#define appH

#define NUMBEROFTREES 4
#define MAXSIZE 256
//#define __stDEBUG__

// Metric Tree includes
#include <arboretum/stMetricTree.h>
#include <arboretum/stPlainDiskPageManager.h>
#include <arboretum/stDiskPageManager.h>
#include <arboretum/stSlimTree.h>
#include <arboretum/stDBMTree.h>
#include <arboretum/stBasicMetricEvaluators.h>
#include <arboretum/stBasicObjects.h>

#include "../../../GNUPlot.h"

#include <string.h>
#include <fstream>

#ifndef CLK_TCK
   #define CLK_TCK 1000.0
#endif //CLK_TCK



//---------------------------------------------------------------------------
// class TApp
//---------------------------------------------------------------------------
class TApp{
   public:

      typedef stBasicArrayObject <double> myBasicArrayObject;
      typedef stBasicEuclideanMetricEvaluator <myBasicArrayObject> myBasicMetricEvaluator;

      /**
      * This is the type used by the result.
      */
      typedef stResult < myBasicArrayObject > myResult;

      typedef stMetricTree < myBasicArrayObject, myBasicMetricEvaluator > MetricTree;

      /**
      * This is the type of the Slim-Tree defined by myBasicArrayObject and
      * myBasicMetricEvaluator.
      */
      typedef stSlimTree < myBasicArrayObject, myBasicMetricEvaluator > mySlimTree;

      /**
      * This is the type of the Slim-Tree defined by myBasicArrayObject and
      * myBasicMetricEvaluator.
      */
      typedef stDBMTree < myBasicArrayObject, myBasicMetricEvaluator > myDBMTree;

      /**
      * Creates a new instance of this class.
      */
      TApp();

      /**
      * Initializes the application.
      *
      * @param pageSize
      * @param minOccup
      * @param quantidade
      * @param prefix
      */
      void Init(unsigned int pageSize, double maxDistance, double minOccup,
                unsigned int qtdK, unsigned int qtdRQ, char * prefix, int split);

      /**
      * Runs the application.
      *
      * @param prefix
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
      stPlainDiskPageManager * PageManagerMTree;
      stPlainDiskPageManager * PageManagerSlimMST;
      stPlainDiskPageManager * PageManagerSlimDown;

      /**
      * The Page Manager for Slim.
      */
      stPlainDiskPageManager * PageManagerDBM[NUMBEROFTREES];

      /**
      * The Slim-Tree.
      */
      mySlimTree * MetricTreeMTree;
      mySlimTree * MetricTreeSlimMST;
      mySlimTree * MetricTreeSlimDown;
      /**
      * The DBM-Tree.
      */
      myDBMTree * MetricTreeDBM[NUMBEROFTREES];

      /**
      * To store the construction total time.
      */
      clock_t MetricTreeMTreeTime;
      clock_t MetricTreeSlimMSTTime;
      clock_t MetricTreeSlimDownTime;
      clock_t MetricTreeDBMTime[NUMBEROFTREES];

      /**
      * Vector for holding the query objects.
      */
      vector <myBasicArrayObject *> queryObjects;

      /**
      * To hold the page size.
      */
      unsigned int PageSize;

      /**
      * To hold the size of the queries.
      */
      unsigned int SizeKNNQ;
      unsigned int SizeRQ;

      /**
      * To hold the minimum occupation of the pages.
      */
      double MinOccup;
      double MaxDistance;

      /**
      * To store the prefix of files.
      */
      string Prefix;

      int Split;

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
      bool AddToTree(myBasicArrayObject * array, MetricTree * metricTree){
         return metricTree->Add(array);
      }//end AddToTree

      /**
      * Loads the tree from file with a set of points.
      */
      void LoadTree(char * fileName, MetricTree * metricTree, clock_t * totalTime);

      void LoadVectorFromFile(char * fileName);

      /**
      * Performs the queries and outputs its results.
      */
      void PerformQueries();

      void PerformNearestQuery(ResultMeasureDiscrete * rMeasure, MetricTree * metricTree,
                               stPageManager * pageManager);

      void PerformRangeQuery(ResultMeasure * rMeasure, MetricTree * metricTree,
                             stPageManager * pageManager);

      void WriteStats();

      void WriteStat(FILE * file, char * treeName, MetricTree * metricTree, clock_t time);

};//end TApp

#endif //end appH
