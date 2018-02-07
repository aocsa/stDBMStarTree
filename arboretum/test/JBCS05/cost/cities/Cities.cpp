//---------------------------------------------------------------------------
// citiesMain.cpp - This is a test for DBM-Tree.
//
// Author: Marcos Rodrigues Vieira (mrvieira@icmc.usp.br)
// Copyright (c) 2003 GBDI-ICMC-USP
//---------------------------------------------------------------------------
#pragma hdrstop
#include "app.h"

#pragma argsused
int main(int argc, char* argv[]){
   TApp app;                                         

   if (argc==10){
      // Init application.
      app.Init(atoi(argv[1]), atof(argv[2]), atof(argv[3]), atoi(argv[4]), argv[5], atoi(argv[6]), atof(argv[7]));
      // Run it.
      app.Run(argv[8], argv[9]);
   }else{
      cout << "The arguments are wrong!";
      cout << "\nUsage: Cities PAGESIZE MAXDISTANCE MINOCCUPATION NUMBEROFKNNQ NUMBEROFRQ PREFIX SOURCEDATA SOURCEQUERYDATA";
      cout << "\nPAGESIZE size of the page.";
      cout << "\nMAXDISTANCE the maximum distance between two objects in the dataset.";
      cout << "\nMINOCCUPATION minimum occupation in percentage of nodes.";
      cout << "\nNUMBEROFkNNQ number of queries to be perfom.";
      cout << "\nNUMBEROFRQ number of queries to be perfom.";
      cout << "\nPREFIX the first letters of the data and result files.";
      cout << "\nCLUSTERS number of clusters.";
      cout << "\nSOURCEDATA file that has the source data to be add in the trees.";
      cout << "\nSOURCEQUERYDATA file that has the query data to be use in the queries.";
   }//end if

   // Release resources.
   app.Done();

   return 0;
}//end main
