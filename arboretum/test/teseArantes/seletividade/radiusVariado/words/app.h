//---------------------------------------------------------------------------
// app.h - Implementation of the application.
//
// Authors: Marcos Rodrigues Vieira (mrvieira@icmc.usp.br)
//          Adriano Arantes (arantes@icmc.usp.br)
// Copyright (c) 2003 GBDI-ICMC-USP
//---------------------------------------------------------------------------
#ifndef appH
#define appH

#define ERRORFD 0.3
#define RINGFACTOR 0.7

// Metric Tree includes
#include <arboretum/stMetricTree.h>
#include <arboretum/stPlainDiskPageManager.h>
#include <arboretum/stSlimTree.h>
#include <arboretum/stBasicMetricEvaluators.h>
#include <arboretum/stBasicObjects.h>

// My object
#include "../../../resultMeasure.h"

#include <iostream>
#include <stdlib>
#include <math>
#include <string.h>
#include <fstream.h>
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

      /**
      * This is the type of the Slim-Tree defined by TWord and
      * TPointDistanceEvaluator.
      */
      typedef stSlimTree < TWord, TWordDistanceEvaluator > mySlimTree;

      /**
      * Creates a new instance of this class.
      */
      TApp(){
         pageManagerSlim = NULL;
         slimTree = NULL;
      }//end TApp

      /**
      * Initializes the application.
      */
      void TApp::Init(unsigned int pageSize, unsigned int querySize,
                stDistance fractalDimension, stDistance maxDistance,
                char * prefix, char * difRadius,
                stDistance percRadius, double third);

      /**
      * Runs the application.
      */
      void TApp::Run(char * DataPath, char * DataQueryPath);

      /**
      * Deinitialize the application.
      */
      void Done();
   private:

      /**
      * The Page Manager for Slim.
      */
      stPageManager * pageManagerSlim;

      /**
      * The Metric Tree for Slim-Tree.
      */
      mySlimTree * slimTree;

      /**
      * Vector for holding the query objects.
      */
      vector <TWord *> queryObjects;

      /**
      * Vector for holding the radius of the query objects.
      */
      vector < stCount > radiusqueryObjects;

      /**
      *  To hold the PageSize
      */
      unsigned int PageSize;

      /**
      * To hold the size of the data set answers.
      */
      unsigned int QuerySize;

      /**
      * To hold how the queries are divided.
      */
      unsigned int Third;

      /**
      * To hold the fractal dimension.
      */
      stDistance FractalDimension;

      /**
      * To hold the maximum distance between 2 object in the tree.
      */
      stDistance MaxDistance;

      /**
      * To hold if a different radius is required.
      */
      bool DifRadius;

      /**
      * To hold the size of the range queries.
      */
      stDistance PercRadius;

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
      * @param name City's name.
      * @param lat City's latitude.
      * @param lon City's longitude.
      */
      void AddToTree(char * name){
         TWord * word = new TWord(name);
         slimTree->Add(word);
         delete word;
      }//end AddToTree

      /**
      * Loads the tree from file with a set of cities.
      */
      void LoadTree(char * fileName);

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
      * K-NEAREST NEIGHBOR QUERY AND RANGE QUERY WITH ESTIMATE RADIUS
      */
      void PerformKAndRangeQuery(ResultMeasureDiscrete * rMeasureReal,
      ResultMeasureDiscrete * rMeasureSel, ResultMeasureDiscrete * rMeasureRealSD);

      void PerformKOrRangeQuery(ResultMeasureDiscrete * rMeasureReal,
      ResultMeasureDiscrete * rMeasureSel, ResultMeasureDiscrete * rMeasureRealSD);

      void PerformRingRangeQuery(ResultMeasureDiscrete * rMeasureReal,
      ResultMeasureDiscrete * rMeasureSel, ResultMeasureDiscrete * rMeasureRealSD);

      void WriteLog(ResultMeasureDiscrete * resultSlim, char * name);

      void WriteToFile(FILE * file, ResultMeasureDiscrete * rMeasureReal,
                       ResultMeasureDiscrete * rMeasureSel, ResultMeasureDiscrete * rMeasureRealSD);

      void WriteHeader(FILE * file, char * type);

      void PerformQuery();

      void SetRadiusFromObjects(ResultMeasureDiscrete * rMeasureSlim, int i);

};//end TApp

#endif //end appH
