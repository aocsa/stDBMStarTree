//---------------------------------------------------------------------------
// app.h - Implementation of the application.
//
// Authors: Marcos Rodrigues Vieira (mrvieira@icmc.usp.br)
// Copyright (c) 2003 GBDI-ICMC-USP
//---------------------------------------------------------------------------
#ifndef appH
#define appH

#define NUMBEROFTREES 4

// Metric Tree includes
#include <arboretum/stMetricTree.h>
#include <arboretum/stMemoryPageManager.h>
#include <arboretum/stSlimTree.h>
#include <arboretum/stMetricTree.h>
#include <arboretum/stMMTree.h>
#include <arboretum/stGHTree.h>
#include <arboretum/stVPTree.h>



// My object
#include "city.h"
#include "resultMeasure.h"

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
      typedef stResult < TCity > myResult;

      typedef stMetricTree < TCity, TCityDistanceEvaluator > MetricTree;

      /**
      * This is the type of the Slim-Tree defined by TCity and
      * TCityDistanceEvaluator.
      */
      typedef stSlimTree < TCity, TCityDistanceEvaluator > mySlimTree;

      typedef stMMTree < TCity, TCityDistanceEvaluator > myMMTree;

      typedef stGHTree < TCity, TCityDistanceEvaluator > myGHTree;

      typedef stVPTree < TCity, TCityDistanceEvaluator > myVPTree;



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
      void Init(unsigned int pageSize, unsigned int quantidade,
                                                  char * prefix, int numcities);

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

/**************************************************************/
      /**
      * The Page Manager for Slim-tree.
      */
      stPageManager * PageManagerSlimMST;

      /**
      * The Slim-Tree.
      */
      mySlimTree * MetricTreeSlimMST;

/**************************************************************/

      /**
      * The Page Manager for MMtrees
      */
      stPageManager * PageManagerMM[NUMBEROFTREES];

      /**
      * The MM-Trees.
      */
      myMMTree * MetricTreeMM[NUMBEROFTREES];

/**************************************************************/
      /**
      * The Page Manager for VPtree
      */
      stPageManager * PageManagerVP;

      /**
      * The VP-Tree.
      */
      myVPTree * MetricTreeVP;

/**************************************************************/
      /**
      * The Page Manager for GHtree
      */
      stPageManager * PageManagerGH;

      /**
      * The GH-Tree.
      */
      myGHTree * MetricTreeGH;

/**************************************************************/

      /**
      * To store the construction total time.
      */
      clock_t MetricTreeSlimMSTTime;
      clock_t MetricTreeMMTime[NUMBEROFTREES];
      clock_t MetricTreeVPTime;
      clock_t MetricTreeGHTime;

      
      /**
      * Vector for holding the query objects.
      */
      vector <TCity *> queryCities;

      /**
      * Vector for holding the radius of the query objects.
      */
      vector <double> radiusQueryCities;

      /**
      * To hold the page size.
      */
      unsigned int PageSize;

      /**
      * To hold the number of the queries.
      */
      unsigned int Quantidade;

      /**
      * To store the prefix of files.
      */
      string Prefix;


      /**
      * To store the number of cities to be added in the trees.
      */
      int NumCities;

      /**
      * Creates a memory page manager. It must be called before CreateTree().
      */
      void CreateMemoryPageManager();

      /**
      * Creates a tree using the current PageManager.
      */
      void CreateTree();


      /**
      * Adds a city to a tree.
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

      void PerformRangeQuery(ResultMeasure * rMeasureSlim, MetricTree * metricTree,
                             stPageManager * pageManager);


      void WriteStats();

      void WriteStat(FILE * file, char * treeName, MetricTree * metricTree, clock_t time);

      void WriteToFile(FILE * file, char * algName, Measure * rMeasure, int type);

      void WriteHeader(FILE * file, char * type, bool range);

};//end TApp

#endif //end appH
