//---------------------------------------------------------------------------
// app.h - Implementation of the application.
//
// Authors: Marcos Rodrigues Vieira (mrvieira@icmc.usp.br)
// Copyright (c) 2003 GBDI-ICMC-USP
//---------------------------------------------------------------------------
#ifndef appH
#define appH

// Metric Tree includes
#include <arboretum/stMetricTree.h>
#include <arboretum/stPlainDiskPageManager.h>
#include <arboretum/stDiskPageManager.h>
#include <arboretum/stSlimTree.h>
#include <arboretum/stMetricTree.h>
#include <arboretum/stDummyTree.h>
// My object
#include <gbdi/metrichistogram.h>

using namespace std;
using namespace GBDI;
#include "../../resultMeasure.h"

#define NUMBEROFCENTERS 3

#include <string.h>
#include <stdlib.h>
#include <iostream.h>
#include <fstream>
#include <mem.h>

//---------------------------------------------------------------------------
// class TApp
//---------------------------------------------------------------------------
class TApp{
   public:

      typedef stResult <tMetricHistogram> myResult;

      typedef stMetricTree <tMetricHistogram, tMetricHistogramEvaluator> MetricTree;  

      /**
      * This is the type of the Slim-Tree defined by TCity and
      * TCityDistanceEvaluator.
      */
      typedef stSlimTree < tMetricHistogram, tMetricHistogramEvaluator > mySlimTree;
      typedef stDummyTree < tMetricHistogram, tMetricHistogramEvaluator > myDummyTree;

      /**
      * Creates a new instance of this class.
      */
      TApp(){
         PageManagerSlim = NULL;
         PageManagerDummy = NULL;
         SlimTree = NULL;
         DummyTree = NULL;
      }//end TApp

      /**
      * Initializes the application.
      *
      * @param pageSize
      * @param quantidade
      * @param prefix
      */
      void Init(unsigned int pageSize, double maxDistance, unsigned int k, 
                unsigned int quantidadeRange, char * prefix);

      /**
      * Runs the application.
      *
      * @param prefix
      * @param DataPath
      * @param DataQueryPath1
      * @param DataQueryPath2
      * @param DataQueryPath3
      */
      void Run(char * DataPath, char * DataQueryPath1,
               char * DataQueryPath2, char * DataQueryPath3);

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
      mySlimTree * SlimTree;
      myDummyTree * DummyTree;

      /**
      * Vector for holding the query objects.
      */
      vector <tMetricHistogram *> queryObjects[NUMBEROFCENTERS];

      /**
      * To hold the page size.
      */
      unsigned int PageSize;

      /**
      * To hold the size of radius in the queries.
      */
      unsigned int QuantidadeRange;

      /**
      * To hold the size of K.
      */
      unsigned int K;
      string Prefix;
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
      * Adds a metric histogram into the tree.
      *
      */
      void AddToTree(tMetricHistogram * array, MetricTree * metricTree){
         metricTree->Add(array);
      }//end AddToTree

      /**
      * Loads the tree from file with a set of cities.
      */
      void LoadTree(char * fileName, MetricTree * metricTree);

      void LoadVectorFromFile(char * fileName1, char * fileName2, char * fileName3);

      void PerformQueries();

      void PerformMultipleNearestAndRange(ResultMeasure * rMeasureMultiSlim, ResultMeasure * rMeasureMultiDummy,
                                  ResultMeasure * rMeasureBasicSlim, ResultMeasure * rMeasureBasicDummy);


      void PerformSingleNearestAndRange(ResultMeasure * rMeasureRangeSlim, ResultMeasure * rMeasureRangeDummy,
            ResultMeasure * rMeasureNearestSlim, ResultMeasure * rMeasureNearestDummy,
            ResultMeasure * rMeasureKAndNearestSlim, ResultMeasure * rMeasureKAndNearestDummy,
            ResultMeasure * rMeasureNearest_Inter_RangeSlim, ResultMeasure * rMeasureNearest_Inter_RangeDummy);

      void WriteToFile(FILE * file, ResultMeasure * rMeasure, int type);

      void WriteHeader(FILE * file, char * type);

};//end TApp

#endif //end appH
