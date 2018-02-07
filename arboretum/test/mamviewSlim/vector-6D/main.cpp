//---------------------------------------------------------------------------
#include <iostream>
#pragma hdrstop
#include "app.h"
//---------------------------------------------------------------------------

#pragma argsused
int main(int argc, char* argv[]){
   tApp app;

   if (argc==3){
      app.Init(atoi(argv[1]), argv[2]);
      app.Run();
      app.Done();
   }else{
      cout << "The number of arguments is wrong!";
      cout << "\nUsage: Vector PAGESIZE SOURCEDATA";
      cout << "\nPAGESIZE size of the page.";
      cout << "\nSOURCEDATA file that has the source data to be add in the trees.";
   }//end if

   //cin.get(); // Hold the screen
   return 0;
}
//--------------------------------------------------------------------------- 
