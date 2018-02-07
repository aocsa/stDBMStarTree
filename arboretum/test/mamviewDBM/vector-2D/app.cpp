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
   TPoint * point[4];
   myResult * r;
   stTreeInfoResult * treeInfo;

   MyTree->MAMViewInit();

   MyTree->MAMViewSetOutputDir(".");
/*
   point[0] = new TPoint(-118.053800, 33.983400);
   point[1] = new TPoint(-118.158100, 33.876000);
   point[2] = new TPoint(-117.980900, 33.944600);
   point[3] = new TPoint(-118.041200, 33.876700);

   r = MyTree->RangeQuery(point[0], 0.5);
   delete r;
   r = MyTree->RangeQuery(point[1], 1);
   delete r;
   r = MyTree->NearestQuery(point[1], 5);
   delete r;
   r = MyTree->NearestQuery(point[2], 10);
   delete r;
   r = MyTree->NearestQuery(point[3], 20);
   delete r;
*/
   MyTree->MAMViewDumpTree();

//   delete[] point;
}//end tApp::Run

//---------------------------------------------------------------------------
void tApp::Done(){

   delete this->MyTree;
   delete this->PageMan;
}//end tApp::Done

//---------------------------------------------------------------------------
bool tApp::LoadTree(char * dataPath){
   ifstream in(dataPath);
   double dLat, dLong;
   TPoint * point;

   if (in.is_open()){
      cout << "Loading objects...";
      while(in >> dLat){
         in >> dLong;
         point = new TPoint(dLat, dLong);
         MyTree->Add(point);
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
