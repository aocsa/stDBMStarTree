//---------------------------------------------------------------------------
#include <iostream>
#pragma hdrstop
#include "app.h"
//---------------------------------------------------------------------------

#pragma argsused
int main(int argc, char* argv[]){
   tApp app;

   if (argc==5){
      app.Init(atoi(argv[1]), atof(argv[2]), atoi(argv[3]), argv[4]);
      app.Run();
      app.Done();
   }else{
      cout << "The number of arguments is wrong!";
      cout << "\nUsage: Words PAGESIZE MINOCCUPATION NUMBEROFCLUSTERS SOURCEDATA";
      cout << "\nPAGESIZE size of the page.";
      cout << "\nMINOCCUPATION minimum occupation in percentage of nodes.";
      cout << "\nNUMBEROFCLUSTERS number of clusters to be done.";
      cout << "\nSOURCEDATA file that has the source data to be add in the trees.";
   }//end if

   //cin.get(); // Hold the screen
   return 0;
}
//---------------------------------------------------------------------------
 