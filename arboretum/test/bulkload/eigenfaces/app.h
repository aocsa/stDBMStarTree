#define __BULKLOAD__
//#define __stPRINTMSG__
//#define __stDEBUG__
//#define __stMAMVIEW__
#define __QUERYSLIM__
#define __MTREECMP__

//---------------------------------------------------------------------------
// app.h - Implementation of the application.
//
// Author: Thiago Galbiatti Vespa (thiago@icmc.sc.usp.br)
//         Marcos Rodrigues Vieira (mrvieira@icmc.usp.br)
// Copyright (c) 2006 GBDI-ICMC-USP
//---------------------------------------------------------------------------
#ifndef appH
#define appH

// Metric Tree includes
#include <arboretum/stMetricTree.h>
#include <arboretum/stPlainDiskPageManager.h>
#include <arboretum/stDiskPageManager.h>
#include <arboretum/stMemoryPageManager.h>
#include <arboretum/stSlimTree.h>
#include <arboretum/stMTree.h>
#include <arboretum/stMetricTree.h>
#include <arboretum/stBasicMetricEvaluators.h>
#include <arboretum/stBasicObjects.h>

#include "../GNUPlot.h"

#include <string.h>
#include <fstream>

#define INSFILE "Lyfn.txt"
#define QUERYCITYFILE "LyfnRq.txt"


#define MAXSIZE 16

#define MAXOBJ 11900

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
      * This is the type of the Slim-Tree defined by TCity and
      * TCityDistanceEvaluator.
      */
      typedef stSlimTree < myBasicArrayObject, myBasicMetricEvaluator > mySlimTree;

      /**
      * This is the type of the M-Tree defined by TCity and
      * TCityDistanceEvaluator.
      */
      typedef mySlimTree myMTree;

      /**
      * Creates a new instance of this class.
      */
      TApp(){
         MTreeBulkPageManager = NULL;
         MTreeNormalPageManager = NULL;
         SlimTreeBulkPageManager = NULL;
         SlimTreeNormalPageManager = NULL;
         MTreeBulk = NULL;
         MTreeNormal = NULL;
         SlimTreeBulk = NULL;
         SlimTreeNormal = NULL;
      }//end TApp


      /**
      * Initializes the application.
      *
      * @param pageSize
      * @param minOccup
      * @param quantidade
      * @param prefix
      */
      void Init(unsigned int pageSize, double maxDistance,
                unsigned int qtdK, unsigned int qtdRQ);
      /**
      * Runs the application.
      *
      * @param DataPath
      * @param DataQueryPath
      */
      void Run();

      /**
      * Deinitialize the application.
      */
      void Done();

   private:

      /**
      * The Page Manager for MTree.
      */
      stPlainDiskPageManager * MTreeBulkPageManager;
      stPlainDiskPageManager * MTreeNormalPageManager;

      /**
      * The Page Manager for SlimTree.
      */
      stPlainDiskPageManager * SlimTreeBulkPageManager;
      stPlainDiskPageManager * SlimTreeNormalPageManager;

      /**
      * The MTree.
      */
      myMTree * MTreeBulk;
      myMTree * MTreeNormal;


      /**
      * The SlimTree.
      */
      mySlimTree * SlimTreeBulk;
      mySlimTree * SlimTreeNormal;

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
      double MaxDistance;

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
      * Loads the tree from file with a set of cities.
      */
      void LoadTree(char * fileName);
      void LoadTreeBulk(char * fileName);
      void LoadTreeNormal(char * fileName);

      /**
      * Loads the vector for queries.
      */
      void LoadVectorFromFile(char * fileName);

      /**
      * Performs the queries and outputs its results.
      */
      void PerformQueries();

      void PerformNearestQuery(ResultMeasureDiscrete * rMeasure, MetricTree * metricTree,
                               stPageManager * pageManager);

      void PerformRangeQuery(ResultMeasure * rMeasure, MetricTree * metricTree,
                             stPageManager * pageManager);




};//end TApp

#endif //end appH
