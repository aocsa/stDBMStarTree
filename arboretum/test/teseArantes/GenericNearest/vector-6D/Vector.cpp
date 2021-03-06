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

   if (argc >= 8){
      // Init application.
      app.Init(atoi(argv[1]), atoi(argv[2]), atoi(argv[3]), argv[4], argv[5]);
      // Run it.
      app.Run(argv[6], argv[7]);
   }else{
      cout << "The arguments are wrong!";
      cout << "\nUsage: Cities PAGESIZE STARTK INCREMENTOFK NUMBEROFK TIELIST PREFIX SOURCEDATA SOURCEQUERYDATA";
      cout << "\nPAGESIZE size of the page.";
      cout << "\nSTARTK first number of nearest queries to be perfom.";
      cout << "\nNUMBEROFK number of nearest queries to be perfom.";
      cout << "\nTIELIST true if the tie list is to be returned.";
      cout << "\nPREFIX the first letters of the data and result files.";
      cout << "\nSOURCEDATA file that has the source data to be add in the trees.";
      cout << "\nSOURCEQUERYDATA file that has the query data to be use in the queries.";
      cout << "\n\nExample: Cities 1024 5 6 false EG ../../../../../datasets/EnglishResto.txt ../../../../datasets/English500.txt";
   }//end if

   // Release resources.
   app.Done();

   return 0;
}//end main
