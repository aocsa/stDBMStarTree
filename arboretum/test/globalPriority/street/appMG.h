//---------------------------------------------------------------------------
// app.h - Implementation of the application.
//
// Author: Marcos Rodrigues Vieira (mrvieira@icmc.sc.usp.br)
//
// Copyright (c) 2003 GBDI-ICMC-USP
//---------------------------------------------------------------------------
#ifndef appH
#define appH
// quantidade de amostra
#define QUANTIDADE 12
#define NROOBJECTS 27282
#define DIMENSAOFRACTAL1 1.82
#define DIMENSAOFRACTAL2 3.53

// Metric Tree includes
#include <slimtree/stMetricTree.h>
#include <slimtree/stMemoryPageManager.h>
#include <slimtree/stDiskPageManager.h>
#include <slimtree/stSlimTree.h>
#include <slimtree/stGenericPriorityQueue.h>

// My object
#include "points.h"
#include <time>

//---------------------------------------------------------------------------
// class resultMeasure
//---------------------------------------------------------------------------
class resultMeasure{
   public:

      resultMeasure(int newSize){
         size = newSize;
         discAccess = new double[size];
         distanceFunction = new double[size];
         totalTime = new double[size];
         k = new double[size];
         double fator = 0.0001;
         // numero de objetos 5507
         // 0.0001, 0.0002, 0.0005, 0.001, 0.002, 0.005, 0.01, 0.02, 0.05, 0.1, 0.2, 0.5
         for (int i=0; i<size; i=i+3){
            k[i] = fator;
            k[i+1] = 2*fator;
            k[i+2] = 5*fator;
            fator = fator*10;
         }//end for
         for (int i=0; i<size; i++){
            totalTime[i] = 0;
            discAccess[i] = 0;
            distanceFunction[i] = 0;
         }//end for
      }//end resultMeasure()

      ~resultMeasure(){
         delete[] k;
         delete[] discAccess;
         delete[] distanceFunction;
         delete[] totalTime;
      }//end ~resultMeasure()

      int getSize(){
         return size;
      }//end setSize()

      double getDiscAccess(int i){
         if(i>=0 && i<size)
            return discAccess[i];
         else return 0L;
      }//end getDiscAccess

      void setDiscAccess(int i, double value){
         if(i>=0 && i<size)
            discAccess[i] = value;
      }//end setDiscAccess

      double getDistanceFunction(int i){
         if(i>=0 && i<size)
            return distanceFunction[i];
         else return 0L;
      }//end getDistanceFunction

      void setDistanceFunction(int i, double value){
         if(i>=0 && i<size)
            distanceFunction[i] = value;
      }//end setDistanceFunction

      double getTotalTime(int i){
         if(i>=0 && i<size)
            return totalTime[i];
         else return 0L;
      }//end getTotalTime

      void setTotalTime(int i, double value){
         if(i>=0 && i<size)
            totalTime[i] = value;
      }//end setTotalTime

      double getK(int i){
         if(i>=0 && i<size)
            return k[i];
         else return 0;
      }//end getK

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

      /**
      * This type is used by the priority key.
      */
      typedef stGenericPriorityQueue < TPoint > tGenericPriorityQueue;

      /**
      * This type is used by the priority key.
      */
      typedef stGenericPriorityHeap < TPoint > tPGenericHeap;

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
      */
      void Init();

      /**
      * Runs the application.
      */
      void Run();

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
      * Vector for holding the final radius of the queries for the range queries.
      */
      vector <double> radiusPoints;

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
      * @param lat Point's latitude.
      * @param lon Point's longitude.
      */
      void AddToTree(double lat, double lon){
         TPoint * point = new TPoint(lat, lon);
         MetricTreeSlim->Add(point);
         delete point;
      }//end AddToTree

      /**
      * Load the queries from the file.
      */
      void LoadVectorFromFile(char * filename);

      /**
      * Performs the queries and outputs its results.
      */
      void PerformQueries();

      /**
      * Performs a Fractal Nearest Query.
      */
      void PerformFractalNearest(resultMeasure * resultSlim, double dimensaoFractal);

      /**
      * Performs a Incremental Nearest Query.
      */
      void PerformIncrementalNearest(resultMeasure * resultSlim);

      /**
      * Performs a Local Nearest Query.
      */
      void PerformLocalNearest(resultMeasure * resultSlim);

      /**
      * Performs a Global Nearest Query.
      */
      void PerformGlobalNearest(resultMeasure * resultSlim);

      /**
      * Performs a Range Query.
      */
      void PerformRange(resultMeasure * resultSlim);

      /**
      * Write the results into the files.
      */
      void WriteToFile(FILE * file, resultMeasure * rMeasure, int type);

      /**
      * Write the header into the files.
      */
      void WriteHeader(FILE * file, char * type);

};//end TApp

#endif //end appH
