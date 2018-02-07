//---------------------------------------------------------------------------
// app.h - Implementation of the application.
//
// Authors: Marcos Rodrigues Vieira (mrvieira@icmc.sc.usp.br)
//          Adriano Arantes (arantes@icmc.sc.usp.br)
// Copyright (c) 2003 GBDI-ICMC-USP
//---------------------------------------------------------------------------
#ifndef appH
#define appH

// Metric Tree includes
#include <slimtree/stMetricTree.h>
#include <slimtree/stDummyTree.h>
#include <slimtree/stMemoryPageManager.h>
#include <slimtree/stDiskPageManager.h>
#include <slimtree/stSlimTree.h>

// My object
#include "word.h"

#include <string.h>

//---------------------------------------------------------------------------
// class resultMeasure
//---------------------------------------------------------------------------
class resultMeasure{
   public:

      resultMeasure(int newSize){
         size = newSize;
         discAccess = new long[size];
         distanceFunction = new long[size];
         totalTime = new double[size];
         k = new int[size];
         for(int i=0; i<size ; i++){
            k[i] = i+1;
         }//end for
      }//end resultMeasure()

      ~resultMeasure(){
         delete [] discAccess;
         delete [] distanceFunction;
         delete [] totalTime;
      }//end ~resultMeasure()

      int getSize(){
         return size;
      }//end setSize()

      long getDiscAccess(int i){
         if(i>=0 && i<size)
            return discAccess[i];
         else return 0L;
      }//end getDiscAccess

      void setDiscAccess(int i, long value){
         if(i>=0 && i<size)
            discAccess[i] = value;
      }//end setDiscAccess

      long getDistanceFunction(int i){
         if(i>=0 && i<size)
            return distanceFunction[i];
         else return 0L;
      }//end getDistanceFunction

      void setDistanceFunction(int i, long value){
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

      int getK(int i){
         if(i>=0 && i<size)
            return k[i];
         else return 0;
      }//end getK

   private:

      long * discAccess;
      long * distanceFunction;
      double * totalTime;
      int * k;
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
      typedef stResult < TWord > myResult;

      /**
      * This is the type of the Metric Tree defined by TWord and
      * TWordDistanceEvaluator.
      */
      typedef stMetricTree < TWord, TWordDistanceEvaluator > myMetricTree;

      /**
      * This is the type of the Dummy Tree defined by TWord and
      * TWordDistanceEvaluator.
      */
      typedef stDummyTree < TWord, TWordDistanceEvaluator > myDummyTree;

      /**
      * This is the type of the Dummy Tree defined by TWord and
      * TWordDistanceEvaluator.
      */
      typedef stSlimTree < TWord, TWordDistanceEvaluator > mySlimTree;

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
      * The Page Manager for Dummy.
      */
      stPageManager * PageManagerDummy;

      /**
      * The Metric Tree for Slim-Tree.
      */
      myMetricTree * MetricTreeSlim;

      /**
      * The Metric Tree for Dummy-Tree.
      */
      myMetricTree * MetricTreeDummy;

      /**
      * Vector for holding the query objects.
      */
      vector <TWord *> queryWords;

      /**
      * Vector for holding the radius of the query objects.
      */
      vector <double> radiusQueryWords;

      /**
      * For hold the number of objects inserted into the tree.
      */
      long numberOfObjects;

      /**
      * Creates a disk page manager. It must be called before CreateTree().
      */
      void CreateDiskPageManager();

      /**
      * Creates a tree using the current PageManager.
      */
      void CreateTree();

      /**
      * Adds a word to tree.
      *
      * @param name of the word.
      */
      void AddToTree(char * name){
         TWord * word = new TWord(name);
         
         MetricTreeSlim->Add(word);
         MetricTreeDummy->Add(word);
         numberOfObjects++;
         delete word;
      }//end AddToTree

      /**
      * Loads the tree from file with a set of words.
      */
      void LoadTree(char *fileName);

      /**
      * .
      */
      void LoadVectorFromFile(char *filename);

      /**
      * .
      */
      void SetRadiusFromObjects(double radius);

      /**
      * Performs the queries and outputs its results.
      */
      void PerformQueries();

      /**
      * Performs a query and outputs its results.
      * K-NEAREST NEIGHBOUR QUERY AND RANGE QUERY WITH NEW ALGORITHM
      */
      void PerformQueryKAndRange(resultMeasure * resultSlim,
                                 resultMeasure * resultDummy);

      /**
      * Performs a query and outputs its results.
      * K-NEAREST NEIGHBOUR QUERY OR RANGE QUERY WITH NEW ALGORITHM
      */
      void PerformQueryKRange_And(resultMeasure * resultSlim,
                                  resultMeasure * resultDummy);

      /**
      * Performs a query and outputs its results.
      * K-NEAREST NEIGHBOUR QUERY AND RANGE QUERY WITHOUT NEW ALGORITHM
      */
      void PerformQueryKOrRange(resultMeasure * resultSlim,
                                resultMeasure * resultDummy);

      /**
      * Performs a query and outputs its results.
      * K-NEAREST NEIGHBOUR QUERY OR RANGE QUERY WITHOUT NEW ALGORITHM
      */
      void PerformQueryKRange_Or(resultMeasure * resultSlim,
                                 resultMeasure * resultDummy);

      void WriteToFile(FILE * file, resultMeasure * rMeasure, int type);

      void WriteHeader(FILE * file, char * type, bool and, int radius);

};//end TApp

#endif //end appH
