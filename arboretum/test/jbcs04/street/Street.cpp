//---------------------------------------------------------------------------
// citiesMain.cpp - This is a test for DB-Tree.
//
// Author: Marcos Rodrigues Vieira (mrvieira@icmc.usp.br)
// Copyright (c) 2003 GBDI-ICMC-USP
//---------------------------------------------------------------------------
#pragma hdrstop
#include "app.h"

#pragma argsused
int main(int argc, char* argv[]){
   TApp app;                                         

   if (argc>=6){
      if (atoi(argv[3])<14){
         // Init application.
         app.Init(atoi(argv[1]), atoi(argv[2]), atoi(argv[3]), argv[4], argv[5]);
      }else{
         // Init application.
         app.Init(atoi(argv[1]), atoi(argv[2]), 13, argv[4], argv[5]);
      }//end if
   }else{
      // Init application.
      app.Init(1024, 4, 13, "true", "St");
   }//end if

   if (argc==8){
      // Run it.
      app.Run(argv[6], argv[7]);
   }else{
      cout << "The arguments are wrong!";
      cout << "\nUsage: Street PAGESIZE NUMBEROFRANGE NUMBEROFK TIELIST PREFIX SOURCEDATA SOURCEQUERYDATA";
      cout << "\nPAGESIZE size of the page.";
      cout << "\nNUMBEROFRANGE number of range queries to be perfom.";
      cout << "\nNUMBEROFK number of nearest queries to be perfom.";
      cout << "\nTIELIST true if the tie list is to be returned.";
      cout << "\nPREFIX the first letters of the data and result files.";
      cout << "\nSOURCEDATA file that has the source data to be add in the trees.";
      cout << "\nSOURCEQUERYDATA file that has the query data to be use in the queries.";
   }//end if

   // Release resources.
   app.Done();

   return 0;
}//end main
