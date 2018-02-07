//---------------------------------------------------------------------------
// app.h - Implementation of the application.
//
// Authors: Marcos Rodrigues Vieira (mrvieira@icmc.usp.br)
// Copyright (c) 2003 GBDI-ICMC-USP
//---------------------------------------------------------------------------
#ifndef appH
#define appH

#define NUMBEROFTREES 4

#undef __stDBNENTRIES__
#undef __stDBHEIGHT__
//#define __CMPANSWER__

// Metric Tree includes
#include <arboretum/stMetricTree.h>
#include <arboretum/stPlainDiskPageManager.h>
#include <arboretum/stDiskPageManager.h>
#include <arboretum/stMemoryPageManager.h>
#include <arboretum/stSlimTree.h>
#include <arboretum/stMetricTree.h>
#include <arboretum/stDBMTree.h>
#include <arboretum/stMTree.h>

// My object
#include "city.h"
#include "../../../GNUPlot.h"

#include <iostream.h>
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
      /**
      * This is the type used by the result.
      */
      typedef stResult < TCity > myResult;

      typedef stMetricTree < TCity, TCityDistanceEvaluator > MetricTree;

      /**
      * This is the type of the Slim-Tree defined by TCity and
      * TCityDistanceEvaluator.
      */
      typedef stMTree < TCity, TCityDistanceEvaluator > myMTree;

      /**
      * This is the type of the Slim-Tree defined by TCity and
      * TCityDistanceEvaluator.
      */
      typedef stSlimTree < TCity, TCityDistanceEvaluator > mySlimTree;

      /**
      * This is the type of the Slim-Tree defined by TCity and
      * TCityDistanceEvaluator.
      */
      typedef stDBMTree < TCity, TCityDistanceEvaluator > myDBMTree;

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
      vector <TCity *> queryObjects;

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

      int Split;

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
      bool AddToTree(char * name, double lat, double lon, MetricTree * metricTree){
         TCity * city = new TCity(name, lat, lon);
         bool ret = metricTree->Add(city);
         delete city;
         return ret;
      }//end AddToTree

      /**
      * Loads the tree from file with a set of cities.
      */
      void LoadTree(char * fileName, MetricTree * metricTree, clock_t * totalTime);

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

      void WriteStats();

      void WriteStat(FILE * file, char * treeName, MetricTree * metricTree, clock_t time);

};//end TApp

#endif //end appH
