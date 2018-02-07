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

   cout << "\n" << this->MyTree->Consistency();
   this->MyTree->DeleteUniqueNodes();
   cout << "\n" << this->MyTree->Consistency();
   this->MyTree->Optimize();
   cout << "\n" << this->MyTree->Consistency();
   this->MyTree->DeleteUniqueNodes();
   cout << "\n" << this->MyTree->Consistency();
}//end tApp::Init

//---------------------------------------------------------------------------
void tApp::Run(){
   TPoint * point;
   myResult * r;
   ifstream in("../../Gen256_500.txt");
   double values[MAXSIZE];
   int i;

   if (in.is_open()){
      cout << "Loading query object...";

      for (i = 0; i < MAXSIZE; i++){
         in >> values[i];
      }//end for
      point = new TPoint(values);
      in.close();
   }//end if

   MyTree->MAMViewInit();

   MyTree->MAMViewSetOutputDir(".");

   r = MyTree->RangeQuery(point, 0.001 * MyTree->GetGreaterEstimatedDistance());
   delete r;
   r = MyTree->RangeQuery(point, 0.01 * MyTree->GetGreaterEstimatedDistance());
   delete r;
   r = MyTree->NearestQuery(point, 5);
   delete r;
   r = MyTree->NearestQuery(point, 10);
   delete r;
   r = MyTree->NearestQuery(point, 20);
   delete r;

   MyTree->MAMViewDumpTree();

   delete point;

}//end tApp::Run

//---------------------------------------------------------------------------
void tApp::Done(){
   delete this->MyTree;
   delete this->PageMan;
}//end tApp::Done

//---------------------------------------------------------------------------
bool tApp::LoadTree(char * dataPath){
   ifstream in(dataPath);
   double values[MAXSIZE];
   TPoint * point;
   int w = 0;
   int i;

   if (in.is_open()){
      cout << "Loading objects...";

      while (in >> values[0]){
         for (i = 1; i < MAXSIZE; i++){
            in >> values[i];
         }//end for
         point = new TPoint(values);
         MyTree->Add(point);
         w++;
         if (w % 1000 == 0){
            cout << '.';
         }//end if
         delete point;
      }//end while
      cout << "\nAdded " << MyTree->GetNumberOfObjects() << " objects...\n";
      in.close();
      return true;
   }else{
      cout << "Problem to open the file.";
      return false;
   }//end if
}//end tApp::LoadTree


