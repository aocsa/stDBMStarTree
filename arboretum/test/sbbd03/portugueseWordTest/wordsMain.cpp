//---------------------------------------------------------------------------
// dummysample.cpp - This is a small example of use of the GBDI SlimTree
// Library.
//
// It contains the implementation of an application and the complete
// implementaion of an User Layer.
//
// Authors: Marcos Rodrigues Vieira (mrvieira@icmc.sc.usp.br)
//          Adriano Arantes (arantes@icmc.sc.usp.br)
// Copyright (c) 2003 GBDI-ICMC-USP
//---------------------------------------------------------------------------
#pragma hdrstop
#include "app.h"

#pragma argsused
int main(int argc, char* argv[]){
   TApp app;

   // Init application.
   app.Init();

   // Run it.
   app.Run();

   // Release resources.
   app.Done();

   return 0;
}//end main
