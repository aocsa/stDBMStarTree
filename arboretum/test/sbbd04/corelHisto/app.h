//---------------------------------------------------------------------------
// app.h - Implementation of the application.
//
// Authors: Marcos Rodrigues Vieira (mrvieira@icmc.sc.usp.br)
//          Adriano Arantes (arantes@icmc.sc.usp.br)
// Copyright (c) 2003 GBDI-ICMC-USP
//---------------------------------------------------------------------------
#ifndef appH
#define appH
#define __stFRACTALQUERY__
#define MAXSIZE 32

// Metric Tree includes
#include <arboretum/stMetricTree.h>
#include <arboretum/stPlainDiskPageManager.h>
#include <arboretum/stSlimTree.h>
#include <arboretum/stBasicMetricEvaluators.h>
#include <arboretum/stBasicObjects.h>

#include "../Cities/resultMeasure.h"

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

      typedef stBasicEuclideanMetricEvaluator <myBasicArrayObject> myBasicMetricEvaluator;

      typedef stResult <myBasicArrayObject> myResult;

      typedef stMetricTree <myBasicArrayObject, myBasicMetricEvaluator> MetricTree;

      /**
      * This is the type of the Slim-Tree defined by TCity and
      * TCityDistanceEvaluator.
      */
      typedef stSlimTree < myBasicArrayObject, myBasicMetricEvaluator > mySlimTree;


      /**
      * Creates a new instance of this class.
      */
      TApp(){
         PageManagerSlim = NULL;
         MetricTreeSlim = NULL;
      }//end TApp

      /**
      * Initializes the application.
      */
      void TApp::Init(unsigned int pageSize, unsigned int datasetSize,
                stDistance fractalDimension, char * difRadius,
                stDistance percRadius, unsigned int third, char * prefix);

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
      stPageManager * PageManagerSlim;

      /**
      * The Metric Tree for Slim-Tree.
      */
      mySlimTree * MetricTreeSlim;

      /**
      * Vector for holding the query objects.
      */
      vector < myBasicArrayObject * > queryPoints;

      /**
      * Vector for holding the radius of the query objects.
      */
      vector < double > radiusQueryPoints;

      /**
      *  To hold the PageSize
      */
      unsigned int PageSize;

      /**
      * To hold the size of the data set answers.
      */
      unsigned int DatasetSize;

      /**
      * To hold how the queries are divided.
      */
      unsigned int Third;

      /**
      * To hold the fractal dimension.
      */
      stDistance FractalDimension;

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
      */
      void AddToTree(myBasicArrayObject * array){
         MetricTreeSlim->Add(array);
      }//end AddToTree

      /**
      * Loads the tree from file with a set of cities.
      */
      void LoadTree(char * fileName);

      void LoadVectorFromFile(char * fileName);

      /**
      * Performs the queries and outputs its results.
      */
      void PerformQueries();

      void PerformSimpleKOrRangeQuery(ResultMeasure * rMeasure, int i);

      void PerformKOrRangeQuery(ResultMeasure * rMeasure, int i);

      void WriteLog(ResultMeasure * result, char * name);

      void WriteToFile(FILE * file, ResultMeasure * rMeasure, int type);

      void WriteHeader(FILE * file, char * type);

      void PerformQuery();

      void SetRadiusFromObjects(ResultMeasure * rMeasure, int i);

};//end TApp

#endif //end appH
