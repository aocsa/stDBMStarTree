//---------------------------------------------------------------------------

#ifndef appH
#define appH

#include <arboretum/stMetricTree.h>
#include <arboretum/stDBMTree.h>
#include <arboretum/stMemoryPageManager.h>
#include <arboretum/stMAMView.h>
// My object
#include "points.h"

#define __stMAMVIEW__

class tApp{
   public:
      /**
      * This is the type used by the result.
      */
      typedef stResult < TPoint > myResult;

      /**
      * This is the type of the DBM-Tree defined by TCity and
      * TCityDistanceEvaluator.
      */
      typedef stDBMTree < TPoint, TPointDistanceEvaluator > myDBMTree;

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
      * Loads the tree with Points.
      */
      bool LoadTree(char * dataPath);
};//end tApp

//---------------------------------------------------------------------------
#endif //end tApp
