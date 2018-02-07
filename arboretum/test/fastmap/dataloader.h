//---------------------------------------------------------------------------

#ifndef dataloaderH
#define dataloaderH
//---------------------------------------------------------------------------
#include "fmutil.h"
#include <ostream>

/**
* Data loader.
*/
class tData{
   public:
      tData(const char * filename);

      ~tData();

      tMyObject ** GetObjects(){
         return objects;
      }//end GetObjects

      int GetSize(){
         return size;
      }//end GetSize

      void Print(ostream & out);
   private:
      tMyObject ** objects;

      int size;
};//end tData



#endif //end dataloaderH
