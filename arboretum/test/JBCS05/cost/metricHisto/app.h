//---------------------------------------------------------------------------
// app.h - Implementation of the application.
//
// Authors: Marcos Rodrigues Vieira (mrvieira@icmc.sc.usp.br)
// Copyright (c) 2003 GBDI-ICMC-USP
//---------------------------------------------------------------------------
#ifndef appH
#define appH

#define NUMBEROFTREES 4
#define NUMBEROFBINS 100
#define __stDEBUG__
#define __stDISKACCESSSTATS__

// Metric Tree includes
#include <arboretum/stPlainDiskPageManager.h>
#include <arboretum/stDiskPageManager.h>
#include <arboretum/stMetricTree.h>
#include <arboretum/stSlimTree.h>
#include <arboretum/stDBMTree.h>
// My object
#include <gbdi/metrichistogram.h>

using namespace std;
using namespace GBDI;

#include "../../../GNUPlot.h"
#include <arboretum/stHistogram.h>
#include <arboretum/stLeveldiskAccess.h>

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
      typedef stResult < tMetricHistogram > myResult;

      /**
      * This is the type of the Slim-Tree defined by tMetricHistogram and
      * tMetricHistogramEvaluator.
      */
      typedef stMetricTree < tMetricHistogram, tMetricHistogramEvaluator > MetricTree;

      typedef stSlimTree < tMetricHistogram, tMetricHistogramEvaluator > mySlimTree;

      typedef stDBMTree < tMetricHistogram, tMetricHistogramEvaluator > myDBMTree;

      typedef stHistogram < tMetricHistogram, tMetricHistogramEvaluator > tHistogram;

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
      stPlainDiskPageManager * PageManagerDBM[NUMBEROFTREES];

      /**
      * The Slim-Tree.
      */
      myDBMTree * DBMTree[NUMBEROFTREES];

      /**
      * Vector for holding the query objects.
      */
      vector <tMetricHistogram *> queryObjects;

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
      double MinOccup;
      double MaxDistance;
      double FractalDimension;

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
      bool AddToTree(tMetricHistogram * array, MetricTree * metricTree){
         return metricTree->Add(array);
      }//end AddToTree

      /**
      * Loads the tree from file with a set of points.
      */
      void LoadTree(char * fileName, MetricTree * metricTree);

      void LoadVectorFromFile(char * fileName);

      void GenerateHistogram(char * fileName);

      /**
      * Performs the queries and outputs its results.
      */
      void PerformQueries();

      void PerformRangeQuery(ResultMeasure * rMeasure, 
                             MetricTree * metricTree, stPageManager * pageManager);
                             
      void OptimalEstimateRQ(ResultMeasure * rMeasure, MetricTree * metricTree);

      void FastOptimalEstimateRQ(ResultMeasure * rMeasure, MetricTree * metricTree);

      void FatFactorEstimateRQ(ResultMeasure * rMeasure, MetricTree * metricTree);

      void CiacciaEstimateRQ(ResultMeasure * rMeasure, MetricTree * metricTree);

      void CiacciaLevelEstimateRQ(ResultMeasure * rMeasure, MetricTree * metricTree);

      void TestEstimateRQ(ResultMeasure * rMeasure, MetricTree * metricTree);

      void SampledLevelEstimateRQ(ResultMeasure * rMeasure, MetricTree * metricTree);

};//end TApp

#endif //end appH
