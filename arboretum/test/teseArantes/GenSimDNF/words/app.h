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
#include <arboretum/stBasicMetricEvaluators.h>
#include <arboretum/stBasicObjects.h>
#include <arboretum/stSlimTree.h>
#include <arboretum/stDummyTree.h>

#include "../../resultMeasure.h"
#define NUMBEROFCENTERS 3

#include <string.h>
#include <iostream.h>
#include <fstream>
//---------------------------------------------------------------------------
// class TApp
//---------------------------------------------------------------------------
class TApp{
   public:
      typedef stBasicStringObject < char > TWord;

      typedef stBasicLEditMetricEvaluator < TWord , char > TWordDistanceEvaluator;

      /**
      * This is the type used by the result.
      */
      typedef stResult < TWord > myResult;


      typedef stMetricTree < TWord, TWordDistanceEvaluator > MetricTree;

      /**
      * This is the type of the Slim-Tree defined by TWord and
      * TPointDistanceEvaluator.
      */
      typedef stSlimTree < TWord, TWordDistanceEvaluator > mySlimTree;

      /**
      * This is the type of the Dummy Tree defined by TWord and
      * TPointDistanceEvaluator.
      */
      typedef stDummyTree < TWord, TWordDistanceEvaluator > myDummyTree;


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
      * @param pageSize the size of the page.
      * @param quantidadeRange the maximum number of range queries.
      * @param quantidadeK the maximum number of nearest queries.
      * @param tieList the status of the tie list.
      * @param prefix the prefix name to be used to save the tree.
      */
      void Init(unsigned int pageSize, unsigned int k, 
                unsigned int quantidadeRange, char * prefix);

      /**
      * Runs the application.
      *
      * @param DataPath
      * @param DataQueryPath
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
      stPageManager * PageManagerSlim;

      /**
      * The Page Manager for Dummy.
      */
      stPageManager * PageManagerDummy;

      /**
      * The Metric Tree for Slim-Tree.
      */
      mySlimTree * SlimTree;
      myDummyTree * DummyTree;

      /**
      * Vector for holding the query objects.
      */
      vector <TWord *> queryObjects[NUMBEROFCENTERS];

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
      void AddToTree(char * name, MetricTree * metricTree){
         TWord * word = new TWord(name);
         metricTree->Add(word);
         delete word;
      }//end AddToTree

      /**
      * Loads the tree from file with a set of cities.
      */
      void LoadTree(char * fileName, MetricTree * metricTree);

      /**
      * Loads the vector for queries.
      */
      void LoadVectorFromFile(char * fileName1, char * fileName2, char * fileName3);

      /**
      * Performs the queries and outputs its results.
      */
      void PerformQueries();

      void PerformMultipleNearestAndRange(ResultMeasureDiscrete * rMeasureMultiSlim, ResultMeasureDiscrete * rMeasureMultiDummy,
                                  ResultMeasureDiscrete * rMeasureBasicSlim, ResultMeasureDiscrete * rMeasureBasicDummy);


      void PerformSingleNearestAndRange(ResultMeasureDiscrete * rMeasureRangeSlim, ResultMeasureDiscrete * rMeasureRangeDummy,
            ResultMeasureDiscrete * rMeasureNearestSlim, ResultMeasureDiscrete * rMeasureNearestDummy,
            ResultMeasureDiscrete * rMeasureKAndNearestSlim, ResultMeasureDiscrete * rMeasureKAndNearestDummy,
            ResultMeasureDiscrete * rMeasureNearest_Inter_RangeSlim, ResultMeasureDiscrete * rMeasureNearest_Inter_RangeDummy);

      void WriteToFile(FILE * file, ResultMeasureDiscrete * rMeasure, int type);

      void WriteHeader(FILE * file, char * type);

};//end TApp

#endif //end appH
