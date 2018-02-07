//---------------------------------------------------------------------------
// app.h - Implementation of the application.
//
// Authors: Marcos Rodrigues Vieira (mrvieira@icmc.usp.br)
// Copyright (c) 2003 GBDI-ICMC-USP
//---------------------------------------------------------------------------
#ifndef appH
#define appH

#define NUMBEROFTREES 2

// Metric Tree includes
#include <arboretum/stMetricTree.h>
#include <arboretum/stMemoryPageManager.h>
#include <arboretum/stSlimTree.h>
#include <arboretum/stMetricTree.h>
#include <arboretum/stMMTree.h>
#include <arboretum/stGHTree.h>
#include <arboretum/stVPTree.h>

// My object
#include "points.h"
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
      typedef stResult < TPoint > myResult;

      typedef stMetricTree < TPoint, TPointDistanceEvaluator > MetricTree;

      /**
      * This is the type of the Slim-Tree defined by TPoint and
      * TPointDistanceEvaluator.
      */
      typedef stSlimTree < TPoint, TPointDistanceEvaluator > mySlimTree;

      typedef stMMTree < TPoint, TPointDistanceEvaluator > myMMTree;

      typedef stGHTree < TPoint, TPointDistanceEvaluator > myGHTree;

      typedef stVPTree < TPoint, TPointDistanceEvaluator > myVPTree;


      /**
      * Creates a new instance of this class.
      */
      TApp();

      /**
      * Initializes the application.
      *
      * @param pageSize
      * @param minOccup
      * @param prefix
      */
      void Init(unsigned int pageSize, char * prefix, int numpoints);

      /**
      * Runs the application.
      *
      * @param DataPath
      */
      void Run(char * DataPath);

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
      * To hold the page size.
      */
      unsigned int PageSize;

      /**
      * To store the prefix of files.
      */
      string Prefix;

      /**
      * To store the number of points to be added in the trees.
      */
      int NumPoints;

      /**
      * Creates a memory page manager. It must be called before CreateTree().
      */
      void CreateMemoryPageManager();

      /**
      * Creates a tree using the current PageManager.
      */
      void CreateTree();


      /**
      * Adds a point to the tree.
      */
      bool AddToTree(double values[], MetricTree * metricTree){
         TPoint * point = new TPoint(values);
         bool ret = metricTree->Add(point);
         delete point;
         return ret;
      }//end AddToTree

      /**
      * Loads the tree from file with a set of cities.
      */
      void LoadTree(char * fileName, MetricTree * metricTree, clock_t * totalTime);

      void WriteStats();

      void WriteStat(FILE * file, char * treeName, MetricTree * metricTree, clock_t time);

      void WriteToFile(FILE * file, char * algName, Measure * rMeasure, int type);

      void WriteHeader(FILE * file, char * type, bool range);

};//end TApp

#endif //end appH
