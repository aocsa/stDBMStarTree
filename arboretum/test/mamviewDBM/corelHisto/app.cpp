//---------------------------------------------------------------------------
#include <fstream>
using namespace std;

#include "app.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

//---------------------------------------------------------------------------
void tApp::Init(int pageSize, double minOccup, int cluster, char * dataPath){

   this->PageMan = new stMemoryPageManager(pageSize);
   this->MyTree = new myDBMTree(this->PageMan);

   this->MyTree->SetSplitMethod(myDBMTree::smMIN_MAX);
   this->MyTree->SetChooseMethod(myDBMTree::cmMINDIST);
   this->MyTree->SetMinOccupation(minOccup);
   this->MyTree->SetReInsert(true);
   this->MyTree->SetNumberOfClusters(cluster);
   this->MyTree->SetRemoveFarthest(false); /**/

   LoadTree(dataPath); // Make it ready to use.

   this->MyTree->DeleteUniqueNodes();
   this->MyTree->Optimize();
   this->MyTree->DeleteUniqueNodes();
}//end tApp::Init

//---------------------------------------------------------------------------
void tApp::Run(){
   double values[] = {0.363708, 0.134181, 0.027397, 0.043128, 0.025532, 0.009272, 0.000833, 0.006459, 0.000000, 0.000000, 0.000000, 0.019896, 0.000000, 0.001667, 0.002708, 0.087604, 0.010835, 0.000625, 0.001667, 0.003750, 0.051355, 0.008750, 0.011876, 0.028231, 0.029792, 0.001146, 0.001563, 0.001042, 0.117293, 0.005937, 0.001563, 0.002292};
   myBasicArrayObject * basicArray;
   myResult * r;

   basicArray = new myBasicArrayObject(MAXSIZE, values);
   basicArray->SetOID(34457);

   MyTree->MAMViewInit();

   MyTree->MAMViewSetOutputDir(".");

   r = MyTree->RangeQuery(basicArray, 0.001 * MyTree->GetGreaterEstimatedDistance());
   delete r;
   r = MyTree->RangeQuery(basicArray, 0.01 * MyTree->GetGreaterEstimatedDistance());
   delete r;
   r = MyTree->NearestQuery(basicArray, 5);
   delete r;
   r = MyTree->NearestQuery(basicArray, 10);
   delete r;
   r = MyTree->NearestQuery(basicArray, 20);
   delete r;

   MyTree->MAMViewDumpTree();

   delete basicArray;
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
         for (i = 0; i<MAXSIZE; i++){
            in >> values[i];
         }//end for
         basicArray = new myBasicArrayObject(MAXSIZE, values);
         basicArray->SetOID(id);
         MyTree->Add(basicArray);
         delete basicArray;
         w++;
         if (w % 100 == 0){
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
