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

   if (argc >= 9){
      // Init application.
      // pageSize, quantidadeRadius, quantidadeK, prefix
      app.Init(atoi(argv[1]), atof(argv[2]), atoi(argv[3]), atoi(argv[4]), argv[5]);
      // Run it.
      // prefix, DataPath, DataQueryPath1, DataQueryPath2, DataQueryPath3
      app.Run(argv[6], argv[7], argv[8], argv[9]);
   }else{
      cout << "The arguments are wrong!";
      cout << "Usage: Histo PAGESIZE NUMBEROFRANGEQUERIES NUMBEROFKQUERIES PREFIX SOURCEDATA \
               SOURCEQUERYDATA1 SOURCEQUERYDATA2 SOURCEQUERYDATA3";
      cout << "PAGESIZE size of the page.";
      cout << "NUMBEROFRANGEQUERIES number of queries to be perfom.";
      cout << "NUMBEROFKQUERIES number of queries to be perfom.";
      cout << "PREFIX the first letters of the data and result files.";
      cout << "SOURCEDATA file that has the source data to be add in the trees.";
      cout << "SOURCEQUERYDATA1 first file that has the query data to be use in the queries.";
      cout << "SOURCEQUERYDATA2 second file that has the query data to be use in the queries.";
      cout << "SOURCEQUERYDATA3 third file that has the query data to be use in the queries.";
   }//end if

   // Release resources.
   app.Done();

   return 0;
}//end main
