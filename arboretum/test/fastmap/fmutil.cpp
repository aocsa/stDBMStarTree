
#include "fmutil.h"

ostream & operator << (ostream & out, tMyObject * obj){
   int w;

   out << '[' << obj->GetTag() << " | ";
   for (w = 0; w < obj->GetSize() - 1; w++){
      out << (*obj)[w] << ' ';
   }//end for
   out << (*obj)[w] << ']';

   return out;
}//end operator <<
