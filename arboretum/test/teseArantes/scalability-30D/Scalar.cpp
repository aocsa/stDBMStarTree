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
#include "app.h"

#pragma argsused
int main(int argc, char* argv[]){
   TApp app;
   int i;                                         

   if (argc >= 5){
      // Init application.
      app.Init(atoi(argv[1]), argv[2], atoi(argv[3]), atof(argv[4]), atoi(argv[6]));
   }//end if

   for (i = 0; i < atoi(argv[6]); i++){
      app.SetFile(i, argv[i + 7]);
   }//end if
   // Run it.
   app.Run(argv[5]);

   // Release resources.
   app.Done();

   return 0;
}//end main
