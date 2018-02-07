//---------------------------------------------------------------------------

#ifndef appH
#define appH

#include <arboretum/stMetricTree.h>
#include <arboretum/stDBMTree.h>
#include <arboretum/stMemoryPageManager.h>
#include <arboretum/stMAMView.h>
#include <arboretum/stBasicMetricEvaluators.h>
#include <arboretum/stBasicObjects.h>

//#define __stDEBUG__
#define __stMAMVIEW__

#define MAXSIZE 32

class tApp{
   public:
      typedef stBasicArrayObject <double> myBasicArrayObject;

      typedef stBasicEuclideanMetricEvaluator <myBasicArrayObject> myBasicMetricEvaluator;

      /**
      * This is the type used by the result.
      */
      typedef stResult <myBasicArrayObject> myResult;

      /**
      * This is the type of the DBM-Tree defined by TCity and
      * TCityDistanceEvaluator.
      */
      typedef stDBMTree < myBasicArrayObject, myBasicMetricEvaluator > myDBMTree;

      /**
      * Initializes the application.
      */
      void Init(int pageSize, double minOccup, int cluster, char * dataPath);

      /**
      * Runs the application.
      */
      void Run();

      /**
      * Deinitializes the application.
      */
      void Done();
   private:
      /**
      * Page manager.
      */
      stMemoryPageManager * PageMan;

      /**
      * Metric Tree.
      */
      myDBMTree * MyTree;

      /**
      * Loads the tree with corelHisto.
      */
      bool LoadTree(char * dataPath);
};//end tApp

//---------------------------------------------------------------------------
#endif //end tApp
