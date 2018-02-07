//---------------------------------------------------------------------------

#ifndef appH
#define appH
#include "mamdefs.h"

/**
* Path to iris objects.
*/
#define IRISPATH "../../data/IRIS.txt"

class tApp{
   public:
      /**
      * Initializes the application.
      */
      void Init();

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
      stPageManager * PageMan;

      /**
      * Metric Tree.
      */
      mySlimTree * MyTree;

      /**
      * Loads the tree with IRIS.
      */
      bool LoadTree();
};//end tApp

//---------------------------------------------------------------------------
#endif //end tApp
