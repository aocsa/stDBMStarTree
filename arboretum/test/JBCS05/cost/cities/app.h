//---------------------------------------------------------------------------
// app.h - Implementation of the application.
//
// Authors: Marcos Rodrigues Vieira (mrvieira@icmc.usp.br)
// Copyright (c) 2003 GBDI-ICMC-USP
//---------------------------------------------------------------------------
#ifndef appH
#define appH

#define NUMBEROFTREES 4
#define NUMBEROFBINS 100
#define __stDEBUG__
#define __stDISKACCESSSTATS__

// Metric Tree includes
#include <arboretum/stTreeInformation.h>
#include <arboretum/stPlainDiskPageManager.h>
#include <arboretum/stDiskPageManager.h>
#include <arboretum/stMemoryPageManager.h>
#include <arboretum/stMetricTree.h>
#include <arboretum/stSlimTree.h>
#include <arboretum/stDBMTree.h>

// My object
#include "city.h"
#include "../../../GNUPlot.h"
#include <arboretum/stHistogram.h>
#include <arboretum/stLevelDiskAccess.h>

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

      /**
      * This is the type of the Slim-Tree defined by TCity and
      * TCityDistanceEvaluator.
      */
      typedef stMetricTree < TCity, TCityDistanceEvaluator > MetricTree;

      typedef stSlimTree < TCity, TCityDistanceEvaluator > mySlimTree;

      typedef stDBMTree < TCity, TCityDistanceEvaluator > myDBMTree;

      typedef stHistogram < TCity, TCityDistanceEvaluator > tHistogram;

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
                unsigned int qtdRQ, char * prefix, int split,
                double fractalDimension);

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
      stPlainDiskPageManager * PageManagerDBM[NUMBEROFTREES];

      /**
      * The Slim-Tree.
      */
      myDBMTree * DBMTree[NUMBEROFTREES];

      /**
      * Vector for holding the query objects.
      */
      vector <TCity *> queryObjects;

      tHistogram * Histogram;

      /**
      * To hold the page size.
      */
      unsigned int PageSize;

      /**
      * To hold the size of the queries.
      */
      unsigned int SizeRQ;

      /**
      * To hold the minimum occupation of the pages.
      */
      double MaxDistance;
      double FractalDimension;
      double MinOccup;

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
      void LoadTree(char * fileName, MetricTree * metricTree);

      /**
      * Loads the vector for queries.
      */
      void LoadVectorFromFile(char * fileName);

      void GenerateHistogram(char * fileName);

      /**
      * Performs the queries and outputs its results.
      */
      void PerformQueries();

      void PerformRangeQuery(ResultMeasure * rMeasure, 
                             MetricTree * metricTree, stPageManager * pageManager);
                             
      void TestEstimateRQ(ResultMeasure * rMeasure, MetricTree * metricTree);

      void CiacciaEstimateRQ(ResultMeasure * rMeasure, MetricTree * metricTree);

};//end TApp

#endif //end appH
