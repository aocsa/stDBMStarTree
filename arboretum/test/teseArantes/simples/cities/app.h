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
#include <arboretum/stSlimTree.h>
#include <arboretum/stDummyTree.h>
#include "../../resultMeasure.h"

// My object
#include "city.h"
#include <fstream.h>
#include <string.h>
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
      typedef stSlimTree < TCity, TCityDistanceEvaluator > mySlimTree;

      /**
      * This is the type of the Dummy Tree defined by TCity and
      * TCityDistanceEvaluator.
      */
      typedef stDummyTree < TCity, TCityDistanceEvaluator > myDummyTree;


      /**
      * Creates a new instance of this class.
      */
      TApp(){
         PageManagerSlim = NULL;
         PageManagerDummy = NULL;
         MetricTreeSlim = NULL;
         MetricTreeDummy = NULL;
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
      void Init(unsigned int pageSize, stDistance maxDistance,
                unsigned int startK, unsigned int quantidadeK,
                unsigned int startRange, unsigned int quantidadeRange,
                char * tieList, char * prefix);

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
      stPageManager * PageManagerSlim;

      /**
      * The Page Manager for Dummy.
      */
      stPageManager * PageManagerDummy;

      /**
      * The Metric Tree for Slim-Tree.
      */
      mySlimTree * MetricTreeSlim;

      /**
      * The Metric Tree for Dummy-Tree.
      */
      myDummyTree * MetricTreeDummy;

      /**
      * Vector for holding the query objects.
      */
      vector <TCity *> queryObjects;

      /**
      * Vector for holding the radius of the query objects.
      */
      vector <double> radiusqueryObjects[13];

      /**
      * To hold the page size.
      */
      unsigned int PageSize;

      /**
      * To hold the size of the nearest queries.
      */
      unsigned int StartK;
      unsigned int QuantidadeK;

      /**
      * To hold the size of the range queries.
      */
      unsigned int StartRange;
      unsigned int QuantidadeRange;

      /**
      * To store the prefix of files.
      */
      string Prefix;
      stDistance MaxDistance;

      /**
      * To store the state of the tie list.
      */
      bool TieList;

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
      void AddToTree(char * Name, double Lat, double Lon, MetricTree * metricTree){
         TCity * city = new TCity(Name, Lat, Lon);
         metricTree->Add(city);
         delete city;
      }//end AddToTree

      /**
      * Loads the tree from file with a set of cities.
      */
      void LoadTree(char * fileName, MetricTree * metricTree);

      /**
      * Loads the vector for queries.
      */
      void LoadVectorFromFile(char * fileName);

      /**
      * Set the radius of each queries.
      */
      void SetRadiusFromObjects(ResultMeasure * rMeasureSlim);

      /**
      * Performs the queries and outputs its results.
      */
      void PerformQueries();

      /**
      * Performs a query and outputs its results.
      * K-NEAREST NEIGHBOUR QUERY AND RANGE QUERY WITH NEW ALGORITHM
      *
      * idx the maximum size of the nearest query.
      * resultSlim the place to be save the results of slimTree.
      * resultDummy the place to be save the results of Dummy.
      */
      void NearestAndRange(unsigned int idx, ResultMeasure * resultSlim, ResultMeasure * resultDummy);

      /**
      * Performs a query and outputs its results.
      * K-NEAREST NEIGHBOUR QUERY OR RANGE QUERY WITH NEW ALGORITHM
      *
      * idx the maximum size of the nearest query.
      * resultSlim the place to be save the results of slimTree.
      * resultDummy the place to be save the results of Dummy.
      */
      void NearestOrRange(unsigned int idx, ResultMeasure * resultSlim, ResultMeasure * resultDummy);

      /**
      * Performs a query and outputs its results.
      * K-NEAREST NEIGHBOUR QUERY AND RANGE QUERY WITHOUT NEW ALGORITHM
      *
      * idx the maximum size of the nearest query.
      * resultSlim the place to be save the results of slimTree.
      * resultDummy the place to be save the results of Dummy.
      */
      void NearestIntersectionRange(unsigned int idx, ResultMeasure * resultSlim, ResultMeasure * resultDummy);

      /**
      * Performs a query and outputs its results.
      * K-NEAREST NEIGHBOUR QUERY OR RANGE QUERY WITHOUT NEW ALGORITHM
      *
      * idx the maximum size of the nearest query.
      * resultSlim the place to be save the results of slimTree.
      * resultDummy the place to be save the results of Dummy.
      */
      void NearestUnionRange(unsigned int idx, ResultMeasure * resultSlim, ResultMeasure * resultDummy);

      /**
      * This method saves the results to the file.
      *
      * file the file to be save.
      * algName the string to be save in the file.
      * rMeasure the results to be save.
      * type the type of result (1=distFunc, 2=DiscAccess, 3=Time)
      */
      void WriteToFile(FILE * file, char * algName, ResultMeasure * rMeasure, int type);

      /**
      * This method saves the header of the file.
      *
      * file the file to be save.
      * type the type of the query (true=range, false=nerest).
      * and the type of operator (true= And Operator, false= Or Operator). 
      * radius the radius size of the range query.
      */
      void WriteHeader(FILE * file, char * type, bool and, double radius);

      void WriteStats();
      
      void WriteStat(FILE * file, char * treeName, MetricTree * metricTree);

};//end TApp

#endif //end appH
