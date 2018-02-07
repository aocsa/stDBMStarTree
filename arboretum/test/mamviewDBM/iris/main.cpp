//---------------------------------------------------------------------------
#include <iostream>
#pragma hdrstop
#include "mamdefs.h"
#include "app.h"
//---------------------------------------------------------------------------

#pragma argsused
int main(int argc, char* argv[]){
   tApp app;

   app.Init();
   app.Run();
   app.Done();      

   //cin.get(); // Hold the screen
   return 0;
}
//---------------------------------------------------------------------------
 