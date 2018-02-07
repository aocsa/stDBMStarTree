//---------------------------------------------------------------------------
// citiesMain.cpp - This is a test for DBM-Tree.
//
// Author: Marcos Rodrigues Vieira (mrvieira@icmc.usp.br)
// Copyright (c) 2003 GBDI-ICMC-USP
//---------------------------------------------------------------------------
#pragma hdrstop
#include "app.h"
#include <iostream.h>

#pragma argsused
int main(int argc, char* argv[]){
   TApp app;                                         

   if (argc==7){
      //Initializes
      app.Init(atoi(argv[1]), atoi(argv[2]), argv[3], atoi(argv[4]));
      // Run it.
      app.Run(argv[5], argv[6]);
   }else{
      cout << "The arguments are wrong!";
      cout << "\nUsage: cities PAGESIZE NUMBEROFQUERIES PREFIX NUMCITIES SOURCEDATA SOURCEQUERYDATA";
      cout << "\nPAGESIZE size of the page.";
      cout << "\nNUMBEROFQUERIES number of queries to be perfomed.";
      cout << "\nPREFIX the first letters of the data and result files.";
      cout << "\nCLUSTERS number of clusters.";
      cout << "\nSOURCEDATA file that has the source data to be add in the trees.";
      cout << "\nSOURCEQUERYDATA file that has the query data to be use in the queries.\n\n";
      system("pause");
   }//end if

   // Release resources.
   app.Done();

   return 0;
}//end main
