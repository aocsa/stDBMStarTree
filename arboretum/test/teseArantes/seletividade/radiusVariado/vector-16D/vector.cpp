
//---------------------------------------------------------------------------
// dummysample.cpp - This is a small example of use of the GBDI SlimTree
// Library.
//
// It contains the implementation of an application and the complete
// implementaion of an User Layer.
//
// Author: Marcos Rodrigues Vieira (mrvieira@icmc.usp.br)
// Copyright (c) 2002 GBDI-ICMC-USP
//---------------------------------------------------------------------------
#pragma hdrstop
#include <iostream.h>
#include "app.h"

#pragma argsused
int main(int argc, char* argv[]){
   TApp app;

   if (argc==11){
      // Init the tests.
     app.Init(atoi(argv[1]), atoi(argv[2]), atof(argv[3]), atof(argv[4]), argv[5], argv[6], atof(argv[7]), atof(argv[8]));
     // Run the tests.
     app.Run(argv[9], argv[10]);
   }else{
      cout << "The arguments are wrong!";
      cout << "\nUsage: Cities PAGESIZE DATASETSIZE DIMFRACTAL RADIUSTREE NOBJECTS PREFIX SOURCEDATA SOURCEQUERYDATA RANGE DIFRADIUS PERCRADIUS THIRD";
      cout << "\n1)PAGESIZE size of the page.";
      cout << "\n2)DATASETSIZE size of the dataset to be returned (1 to 10)";
      cout << "\n3)DIMFRACTAL the fractal dimension od the data set.";
      cout << "\n4)RADIUSTREE the maximum radius of index structure to this data set.";
      cout << "\n5)PREFIX the first letters of the data and result files.";
      cout << "\n6)DIFRADIUS Is nearest radius different from range radius? (true or false).";
      cout << "\n7)PERCRADIUS How different is this value? (1 a 99).";
      cout << "\n8)THIRD How I want to divided. (3)";
      cout << "\n9)SOURCEDATA file that has the source data to be add in the trees.";
      cout << "\n10)SOURCEQUERYDATA file that has the query data to be use in the queries.";
   }//end if
   // Release resources.
   app.Done();
   return 0;
}//end main
