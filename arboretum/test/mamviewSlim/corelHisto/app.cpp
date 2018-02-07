//---------------------------------------------------------------------------
#include <fstream>
using namespace std;

#include "app.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

//---------------------------------------------------------------------------
void tApp::Init(int pageSize, char * dataPath){

   this->PageMan = new stMemoryPageManager(pageSize);
   this->MyTree = new mySlimTree(this->PageMan);

   this->MyTree->SetSplitMethod(mySlimTree::smMINMAX);
   this->MyTree->SetChooseMethod(mySlimTree::cmMINDIST);

   LoadTree(dataPath); // Make it ready to use.

   this->MyTree->Optimize();   
}//end tApp::Init

//---------------------------------------------------------------------------
void tApp::Run(){
   MyTree->MAMViewInit();

   MyTree->MAMViewSetOutputDir(".");

   MyTree->MAMViewDumpTree();
}//end tApp::Run

//---------------------------------------------------------------------------
void tApp::Done(){
   delete this->MyTree;
   delete this->PageMan;
}//end tApp::Done

//---------------------------------------------------------------------------
bool tApp::LoadTree(char * dataPath){
   ifstream in(dataPath);
   int id, i;
   int w = 0;
   double values[MAXSIZE];
   myBasicArrayObject * basicArray;

   if (in.is_open()){
      cout << "Loading objects...";

      while (in >> id){
         for(i=0; i<MAXSIZE; i++){
            in >> values[i];
         }//end for
         basicArray = new myBasicArrayObject(MAXSIZE, values);
         basicArray->SetOID(id);
         MyTree->Add(basicArray);
         delete basicArray;
         w++;
         if (w % 10 == 0){
            cout << '.';
         }//end if
      }//end while
      cout << "\nAdded " << MyTree->GetNumberOfObjects() << " objects...\n";
      in.close();
      return true;
   }else{
      cout << "Problem to open the file.";
      return false;
   }//end if
}//end tApp::LoadTree
