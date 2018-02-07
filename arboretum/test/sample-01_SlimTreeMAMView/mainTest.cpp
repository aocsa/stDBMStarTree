//---------------------------------------------------------------------------
#pragma hdrstop
//---------------------------------------------------------------------------
#include "app.h"

#include <stdio.h>
#include <iostream>
#include <string.h>
//---------------------------------------------------------------------------
#pragma argsused

#define __ubDEBUG__
#define __stDEBUG__

int main(int argc, char* argv[]){

   TApp app(atoi(argv[1]));
   // Init application.
   app.Init();
   // Run it.
   app.Run();
   // Release resources.
   app.Done();
   return 0;
}
//---------------------------------------------------------------------------
