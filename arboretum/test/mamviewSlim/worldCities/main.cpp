//---------------------------------------------------------------------------
#include <iostream>
#pragma hdrstop
#include "app.h"
//---------------------------------------------------------------------------

#pragma argsused
int main(int argc, char* argv[]){
   tApp app;

   if (argc==5){
      app.Init(atoi(argv[1]), argv[2], atoi(argv[3]), argv[4]);
      app.Run();
      app.Done();
   }else{
      cout << "The number of arguments is wrong!";
      cout << "\nUsage: Cities PAGESIZE COUNTRY PERCENT SOURCEDATA";
      cout << "\nPAGESIZE size of the page.";
      cout << "\nCOUNTRY the country abreviation (BR, US, ALL, ...).";
      cout << "\nPERCENT percent of the dataset (0.01 though 1%).";
      cout << "\nSOURCEDATA file that has the source data to be add in the trees.";
   }//end if

   //cin.get(); // Hold the screen
   return 0;
}
//--------------------------------------------------------------------------- 
