//---------------------------------------------------------------------------
// app.h - Implementation of the application.
//
// Authors: Marcos Rodrigues Vieira (mrvieira@icmc.sc.usp.br)
// Copyright (c) 2003 GBDI-ICMC-USP
//---------------------------------------------------------------------------
#ifndef appH
#define appH

#define __stFRACTALQUERY__
// Metric Tree includes
#include <arboretum/stMetricTree.h>
#include <arboretum/stPlainDiskPageManager.h>
#include <arboretum/stDiskPageManager.h>
#include <arboretum/stSlimTree.h>

// My object
#include "points.h"
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
      typedef stResult < TPoint > myResult;

      typedef stMetricTree < TPoint, TPointDistanceEvaluator > MetricTree;

      /**
      * This is the type of the Slim-Tree defined by TPoint and
      * TPointDistanceEvaluator.
      */
      typedef stSlimTree < TPoint, TPointDistanceEvaluator > mySlimTree;

      /**
      * Creates a new instance of this class.
      */
      TApp(){
         PageManagerSlim = NULL;
         MetricTreeSlim = NULL;
      }//end TApp

      /**
      * Initializes the application.
      *
      * @param pageSize
      * @param minOccup
      * @param quantidade
      * @param prefix
      */
      void TApp::Init(unsigned int pageSize, unsigned int datasetSize,
                stDistance fractalDimension, char * difRadius,
                stDistance percRadius, unsigned int third, char * prefix);

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
      stPageManager * PageManagerSlim;

      /**
      * The Metric Tree for Slim-Tree.
      */
      mySlimTree * MetricTreeSlim;

      /**
      * Vector for holding the query objects.
      */
      vector <TPoint *> queryPoints;

      /**
      * Vector for holding the radius of the query objects.
      */
      vector <double> radiusQueryPoints;

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
      * To hold the radius of the tree.
      */
      stDistance RadiusTree;

      /**
      * To hold if the range is required.
      */
      bool Range;

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
      void AddToTree(double values[]){
         TPoint * point = new TPoint(values);
         MetricTreeSlim->Add(point);
         delete point;
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
