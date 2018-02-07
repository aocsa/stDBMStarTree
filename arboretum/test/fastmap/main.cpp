//---------------------------------------------------------------------------

#pragma hdrstop
#include "fmutil.h"
#include "dataloader.h"
#include <fstream>


//---------------------------------------------------------------------------
#pragma argsused


int main(int argc, char* argv[]){
   int w;
   tData data("../data/IRIS.objects");  // Load data.
   tMyEvaluator eval;
   tMyFastMapper fm(&eval, 3);

   double map[3];
   ofstream out("iris.plt");

   //data.Print(cout);
   fm.ChoosePivots(data.GetObjects(), data.GetSize());


   out << "splot '-' title '1', '-' title '2', '-' title '3'\n\n";
   for (w = 0; w < data.GetSize(); w++){
      fm.Map((data.GetObjects())[w], map);
      out << map[0] << ' ' << map[1] << ' ' << map[2] << '\n';
      if (w % 50 == 49){
         out << "end\n";
      }//end if
   }//end for

   cin.get(); // Hold the screen
   out.close();
   return 0;
}
//---------------------------------------------------------------------------
 