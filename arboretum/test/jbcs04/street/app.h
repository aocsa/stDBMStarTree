//---------------------------------------------------------------------------
// app.h - Implementation of the application.
//
// Authors: Marcos Rodrigues Vieira (mrvieira@icmc.usp.br)
// Copyright (c) 2003 GBDI-ICMC-USP
//---------------------------------------------------------------------------
#ifndef appH
#define appH

#undef __stDEBUG__

// Metric Tree includes
#include <arboretum/stMetricTree.h>
#include <arboretum/stPlainDiskPageManager.h>
#include <arboretum/stSlimTree.h>
#include <arboretum/stDummyTree.h>

// My object
#include "points.h"

#include <string.h>
//---------------------------------------------------------------------------
// class resultMeasure
//---------------------------------------------------------------------------
class resultMeasure{
   public:

      resultMeasure(int newSize){
         double fator[] = {0.0001, 0.0002, 0.0005, 0.001, 0.002, 0.005, 0.01, 0.02, 0.05, 0.1, 0.2, 0.5, 1};
         if (newSize>13){
            newSize = 13;
         }//end if
         size = newSize;
         discAccess = new double[size];
         distanceFunction = new double[size];
         totalTime = new double[size];
         k = new double[size];
         //if is a point query
         for (int i=0; i<size ; i++){
            k[i] = fator[i];
            discAccess[i] = 0;
            distanceFunction[i] = 0;
            totalTime[i] = 0;
         }//end for
      }//end resultMeasure()

      ~resultMeasure(){
         delete [] discAccess;
         delete [] distanceFunction;
         delete [] totalTime;
         delete [] k;
      }//end ~resultMeasure()

      int getSize(){
         return size;
      }//end setSize

      double getDiscAccess(int i){
         if (i>=0 && i<size)
            return discAccess[i];
         else
            return 0;
      }//end getDiscAccess

      void setDiscAccess(int i, double value){
         if (i>=0 && i<size)
            discAccess[i] = value;
      }//end setDiscAccess

      double getDistanceFunction(int i){
         if (i>=0 && i<size)
            return distanceFunction[i];
         else
            return 0;
      }//end getDistanceFunction

      void setDistanceFunction(int i, double value){
         if (i>=0 && i<size)
            distanceFunction[i] = value;
      }//end setDistanceFunction

      double getTotalTime(int i){
         if (i>=0 && i<size)
            return totalTime[i];
         else
            return 0;
      }//end getTotalTime

      void setTotalTime(int i, double value){
         if (i>=0 && i<size)
            totalTime[i] = value;
      }//end setTotalTime

      double getK(int i){
         if (i>=0 && i<size)
            return k[i];
         else
            return 0;
      }//end getK

      void Reset(){
         for(int i=0; i<size ; i++){
            discAccess[i] = 0;
            distanceFunction[i] = 0;
            totalTime[i] = 0;
         }//end for
      }//end Reset

   private:
      double * discAccess;
      double * distanceFunction;
      double * totalTime;
      double * k;
      int size;

};//end resultMeasure

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
      * This is the type of the Dummy Tree defined by TPoint and
      * TPointDistanceEvaluator.
      */
      typedef stDummyTree < TPoint, TPointDistanceEvaluator > myDummyTree;


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
      void Init(unsigned int pageSize, unsigned int quantidadeRange,
                unsigned int quantidadeK, char * tieList, char * prefix);

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
      vector <TPoint *> queryPoints;

      /**
      * Vector for holding the radius of the query objects.
      */
      vector <double> radiusQueryPoints[13];

      /**
      * To hold the page size.
      */
      unsigned int PageSize;

      /**
      * To hold the size of the range queries.
      */
      unsigned int QuantidadeRange;

      /**
      * To hold the size of the nearest queries.
      */
      unsigned int QuantidadeK;

      /**
      * To store the prefix of files.
      */
      string Prefix;

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
      void AddToTree(double Lat, double Lon, MetricTree * metricTree){
         TPoint * point = new TPoint(Lat, Lon);
         metricTree->Add(point);
         delete point;
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
      void SetRadiusFromObjects(resultMeasure * rMeasureSlim);

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
      void NearestAndRange(int idx, resultMeasure * resultSlim, resultMeasure * resultDummy);

      /**
      * Performs a query and outputs its results.
      * K-NEAREST NEIGHBOUR QUERY OR RANGE QUERY WITH NEW ALGORITHM
      *
      * idx the maximum size of the nearest query.
      * resultSlim the place to be save the results of slimTree.
      * resultDummy the place to be save the results of Dummy.
      */
      void NearestOrRange(int idx, resultMeasure * resultSlim, resultMeasure * resultDummy);

      /**
      * Performs a query and outputs its results.
      * K-NEAREST NEIGHBOUR QUERY AND RANGE QUERY WITHOUT NEW ALGORITHM
      *
      * idx the maximum size of the nearest query.
      * resultSlim the place to be save the results of slimTree.
      * resultDummy the place to be save the results of Dummy.
      */
      void NearestIntersectionRange(int idx, resultMeasure * resultSlim, resultMeasure * resultDummy);

      /**
      * Performs a query and outputs its results.
      * K-NEAREST NEIGHBOUR QUERY OR RANGE QUERY WITHOUT NEW ALGORITHM
      *
      * idx the maximum size of the nearest query.
      * resultSlim the place to be save the results of slimTree.
      * resultDummy the place to be save the results of Dummy.
      */
      void NearestUnionRange(int idx, resultMeasure * resultSlim, resultMeasure * resultDummy);

      /**
      * This method saves the results to the file.
      *
      * file the file to be save.
      * algName the string to be save in the file.
      * rMeasure the results to be save.
      * type the type of result (1=distFunc, 2=DiscAccess, 3=Time)
      */
      void WriteToFile(FILE * file, char * algName, resultMeasure * rMeasure, int type);

      /**
      * This method saves the header of the file.
      *
      * file the file to be save.
      * type the type of the query (true=range, false=nerest).
      * and the type of operator (true= And Operator, false= Or Operator). 
      * radius the radius size of the range query.
      */
      void WriteHeader(FILE * file, char * type, bool and, double radius);

};//end TApp

#endif //end appH
