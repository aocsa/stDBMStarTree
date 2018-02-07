#define __stMAMVIEW__

#include <arboretum/stMetricTree.h>
#include <arboretum/stSlimTree.h>
#include <arboretum/stMemoryPageManager.h>
#include <arboretum/stDiskPageManager.h>
#include <arboretum/stMAMView.h>
// My object
#include "city.h"

#ifndef appH
#define appH

//---------------------------------------------------------------------------

class tApp{
   public:
      /**
      * This is the type used by the result.
      */
      typedef stResult < TCity > myResult;

      /**
      * This is the type of the DBM-Tree defined by TCity and
      * TCityDistanceEvaluator.
      */
      typedef stSlimTree < TCity, TCityDistanceEvaluator > mySlimTree;

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
      stDiskPageManager * PageMan;

      /**
      * Metric Tree.
      */
      mySlimTree * MyTree;

      /**
      * Loads the tree with Cities.
      */
      bool LoadTree(char * dataPath);
};//end tApp

//---------------------------------------------------------------------------
#endif //end tApp
