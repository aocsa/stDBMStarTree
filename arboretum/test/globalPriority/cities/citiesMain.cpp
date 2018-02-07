//---------------------------------------------------------------------------
// dummysample.cpp - This is a small example of use of the GBDI SlimTree
// Library.
//
// It contains the implementation of an application and the complete
// implementaion of an User Layer.
//
// Author: Marcos Rodrigues Vieira (mrvieira@icmc.usp.br)
//
// Copyright (c) 2002 GBDI-ICMC-USP
//---------------------------------------------------------------------------
#pragma hdrstop
#include <iostream.h>
#include "app.h"

#pragma argsused
int main(int argc, char* argv[]){
   TApp app;

   // Init application.
   app.Init();

   try{
      // Run it.
      app.Run();
   }catch(exception e){
      cout << e.what();
   }//end try

   // Release resources.
   app.Done();

   return 0;
}//end main


