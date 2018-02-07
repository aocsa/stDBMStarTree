//---------------------------------------------------------------------------
// citiesMain.cpp - This is a test for Arantes' thesis.
//
// Author: Marcos Rodrigues Vieira (mrvieira@icmc.usp.br)
// Copyright (c) 2004 GBDI-ICMC-USP
//---------------------------------------------------------------------------
#pragma hdrstop
#include "app.h"

#pragma argsused
int main(int argc, char* argv[]){
   TApp app;                                         

   if (argc >= 9){
      // Init application.
      app.Init(atoi(argv[1]), atof(argv[2]), atoi(argv[3]), atoi(argv[4]), atof(argv[5]), argv[6]);
      // Run it.
      app.Run(argv[7], argv[8]);
   }else{
      cout << "The arguments are wrong!";
      cout << "\nUsage: Cities PAGESIZE STARTK NUMBEROFK STARTRANGE NUMBEROFRANGE TIELIST PREFIX SOURCEDATA SOURCEQUERYDATA";
      cout << "\nPAGESIZE size of the page.";
      cout << "\nSTARTRANGE first number of range queries to be perfom.";
      cout << "\nNUMBEROFRANGE number of range queries to be perfom.";
      cout << "\n...";
      cout << "\nPREFIX the first letters of the data and result files.";
      cout << "\nSOURCEDATA file that has the source data to be add in the trees.";
      cout << "\nSOURCEQUERYDATA file that has the query data to be use in the queries.";
      cout << "\n\nExample: Cities 1024 1 10 0.2 EG ../../../../../datasets/EnglishResto.txt ../../../../datasets/English500.txt";
   }//end if

   // Release resources.
   app.Done();

   return 0;
}//end main
