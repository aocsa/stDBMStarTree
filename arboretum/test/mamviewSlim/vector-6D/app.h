//---------------------------------------------------------------------------

#ifndef appH
#define appH

//#define __stDEBUG__
#define __stMAMVIEW__

#include <arboretum/stMetricTree.h>
#include <arboretum/stSlimTree.h>
#include <arboretum/stMemoryPageManager.h>
#include <arboretum/stMAMView.h>

// My object
#include "points.h"

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
      typedef stSlimTree < TPoint, TPointDistanceEvaluator > mySlimTree;

      /**
      * Initializes the application.
      */
      void Init(int pageSize, char * dataPath);

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
      mySlimTree * MyTree;

      /**
      * Loads the tree with Currency.
      */
      bool LoadTree(char * dataPath);
};//end tApp

//---------------------------------------------------------------------------
#endif //end tApp
