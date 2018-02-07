//---------------------------------------------------------------------------

#ifndef appH
#define appH
#include "mamdefs.h"
#include "word.h"

/**
* Path to iris objects.
*/
#define DATAPATH "../../../../datasets/English.txt"
//#define DATAPATH "../../../../datasets/LatinWords/decamerone.ks"
//#define DATAPATH "../../../../datasets/LatinWords/divinacommedia.ks"
//#define DATAPATH "../../../../datasets/LatinWords/gerusalemmeliberata.ks"
//#define DATAPATH "../../../../datasets/LatinWords/orlandofurioso.ks"
//#define DATAPATH "../../../../datasets/LatinWords/promessisposi.ks"
//#define DATAPATH "../../../../datasets/LatinWords/SmallLatinWords.ks"

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
      myDBMTree * MyTree;

      /**
      * Loads the tree with IRIS.
      */
      bool LoadTree();
};//end tApp

//---------------------------------------------------------------------------
#endif //end tApp
