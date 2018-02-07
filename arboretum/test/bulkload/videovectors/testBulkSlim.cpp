//---------------------------------------------------------------------------

#pragma hdrstop

#include "app.h"
//---------------------------------------------------------------------------

#pragma argsused
int main(int argc, char* argv[])
{
   TApp app;                                         
/*
   // Init application.
   app.Init();
   // Run it.
   app.Run();
   // Release resources.
   app.Done();
*/



//   if (argc == 7){
   if (argc == 5){
      // Init application.
      app.Init(atoi(argv[1]), atof(argv[2]), atoi(argv[3]), atoi(argv[4]));
      // Run it.
      //app.Run(argv[5], argv[6]);
      app.Run();
   }else{
/*      cout << "The arguments are wrong!";
      cout << "\nUsage: Vector PAGESIZE MAXDISTANCE NUMBEROFKNNQ NUMBEROFRQ SOURCEDATA SOURCEQUERYDATA";
      cout << "\nPAGESIZE size of the page.";
      cout << "\nMAXDISTANCE the maximum distance between two objects in the dataset.";
      cout << "\nNUMBEROFkNNQ number of queries to be perfom.";
      cout << "\nNUMBEROFRQ number of queries to be perfom.";
      cout << "\nSOURCEDATA file that has the source data to be add in the trees.";
      cout << "\nSOURCEQUERYDATA file that has the query data to be use in the queries.";
 */  }//end if

   // Release resources.
   app.Done();

   // Pause
   printf("\n\nPress <ENTER> to continue...");
   getchar();

   return 0;
}
//---------------------------------------------------------------------------







 