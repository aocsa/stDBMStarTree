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

   if (argc==5){
      //Initializes
      app.Init(atoi(argv[1]), argv[2], atoi(argv[3]));
      // Run it.
      app.Run(argv[4]);
   }else{
      cout << "The arguments are wrong!";
      cout << "\nUsage: cities PAGESIZE PREFIX NUMPOINTS SOURCEDATA";
      cout << "\nPAGESIZE size of the page.";
      cout << "\nPREFIX the first letters of the data and result files.";
      cout << "\nNUMPOINTS number of points to add.";
      cout << "\nSOURCEDATA file that has the source data to be add in the trees.";
      system("pause");
   }//end if

   // Release resources.
   app.Done();

   return 0;
}//end main
