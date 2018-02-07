#define __stMAMVIEW__

#include <arboretum/stDBMTree.h>
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
      typedef stDBMTree < TCity, TCityDistanceEvaluator > myDBMTree;

      /**
      * Initializes the application.
      */
      void Init(int pageSize, char * abreviation,
                int factor, char * dataPath);

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
      myDBMTree * MyTree;

      /**
      * Loads the tree with Cities.
      */
      bool LoadTree(char * abreviation, int factor, char * dataPath);
      bool LoadTree2(char * dataPath);

};//end tApp

//---------------------------------------------------------------------------
#endif //end tApp
