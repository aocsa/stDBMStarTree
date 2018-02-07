//---------------------------------------------------------------------------
// app.h - Implementation of the application.
//
// Authors: Marcos Rodrigues Vieira (mrvieira@icmc.sc.usp.br)
// Copyright (c) 2003 GBDI-ICMC-USP
//---------------------------------------------------------------------------
#ifndef appH
#define appH

#define NUMBEROFTREES 4
#define MAXSIZE 16
#define __stDEBUG__

#ifndef CLK_TCK
   #define CLK_TCK 1000.0
#endif //CLK_TCK

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

      typedef stMetricTree < myBasicArrayObject, myBasicMetricEvaluator > metricTree;

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
      void Init(unsigned int pageSize, double minOccup,
                unsigned int k, double radius, char * prefix,
                int split, int dataNumber);

      /**
      * Runs the application.
      *
      * @param prefix
      * @param DataPath
      * @param DataQueryPath
      */
      void Run(char * DataQueryPath);

      void SetFile(int i, char * dataPath){
         DataPath[i] = new char[strlen(dataPath) + 1];
         strcpy(DataPath[i],dataPath);
      }//end SetFile

      /**
      * Deinitialize the application.
      */
      void Done();
      
   private:

      /**
      * The Page Manager for DBMTree.
      */
      stPlainDiskPageManager * PageManagerSlimTree;
      stPlainDiskPageManager * PageManagerDBM[NUMBEROFTREES];

      /**
      * The DBM-Tree.
      */
      mySlimTree * SlimTree;
      myDBMTree * DBMTree[NUMBEROFTREES];

      /**
      * Vector for holding the query objects.
      */
      vector <myBasicArrayObject *> queryObjects;

      char ** DataPath;

      int DataNumber;

      /**
      * To hold the page size.
      */
      unsigned int PageSize;

      /**
      * To hold the size of the queries.
      */
      unsigned int K;

      /**
      * To hold the minimum occupation of the pages.
      */
      double MinOccup;
      double Radius;

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
      bool AddToTree(myBasicArrayObject * array, metricTree * metricTree){
         return metricTree->Add(array);
      }//end AddToTree

      /**
      * Loads the tree from file with a set of points.
      */
      void LoadTree(char * fileName, metricTree * metricTree);

      void LoadVectorFromFile(char * fileName);

      /**
      * Performs the queries and outputs its results.
      */
      void PerformQueries();

      void PerformNearestQuery(ResultMeasureDiscrete * rMeasure, metricTree * metricTree,
                               stPageManager * pageManager, int idx);

      void PerformRangeQuery(ResultMeasureDiscrete * rMeasure, metricTree * metricTree,
                             stPageManager * pageManager, int idx);

      void WriteStats();

      void WriteStat(FILE * file, char * treeName, metricTree * metricTree, clock_t time);

};//end TApp

#endif //end appH
