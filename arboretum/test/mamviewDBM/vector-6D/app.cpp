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
void tApp::Run(char * dataPath){
   TPoint * point;
   myResult * r;
   stTreeInfoResult * treeInfo;

   MyTree->MAMViewInit();

   MyTree->MAMViewSetOutputDir(".");

   if (!strcmp(dataPath, "../../data/LBeachResto.txt")){
      point = new TPoint(-117.992400, 33.925000);
   }else if (!strcmp(dataPath, "../../data/MGCountyResto.txt")){
      point = new TPoint(-76980400, 39143600);
   }else{ //../../data/Gen14_2D.txt
      point = new TPoint(0.565900, 0.124496);
   }//end if

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
   double dLat, dLong;
   TPoint * point;
   int w = 0;

   if (in.is_open()){
      cout << "Loading objects...";
      while(in >> dLat){
         in >> dLong;
         point = new TPoint(dLat, dLong);
         MyTree->Add(point);
         w++;
         if (w % 100 == 0){
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
