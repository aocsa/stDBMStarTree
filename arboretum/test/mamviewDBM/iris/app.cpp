//---------------------------------------------------------------------------
#include <fstream>
using namespace std;

#include "app.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

//---------------------------------------------------------------------------
void tApp::Init(){

   this->PageMan = new stDiskPageManager("iris.dat", PAGESIZE);
   this->MyTree = new myDBMTree(this->PageMan);

   this->MyTree->SetSplitMethod(myDBMTree::smMIN_MAX);
   this->MyTree->SetChooseMethod(myDBMTree::cmMINDIST);
   this->MyTree->SetMinOccupation(0.3);

   LoadTree(); // Make it ready to use.
}//end tApp::Init

//---------------------------------------------------------------------------
void tApp::Run(){
   myObject obj(4);
   myResult * r;
   stTreeInfoResult * treeInfo;

   MyTree->MAMViewInit();
   
   MyTree->MAMViewSetOutputDir(".");

   obj[0] = 6.3;
   obj[1] = 3.3;
   obj[2] = 6.0;
   obj[3] = 2.5;

   r = MyTree->RangeQuery(&obj, 0.5);
   delete r;
   r = MyTree->RangeQuery(&obj, 1);
   delete r;
   r = MyTree->NearestQuery(&obj, 5);
   delete r;
   r = MyTree->NearestQuery(&obj, 10);
   delete r;
   r = MyTree->NearestQuery(&obj, 20);
   delete r;

   MyTree->MAMViewDumpTree();

   // treeInfo = MyTree->GetTreeInfo();

   // cout << "FatFactor:" << treeInfo->GetGlobalFatFactor() << "\n";
   // delete treeInfo;
}//end tApp::Run

//---------------------------------------------------------------------------
void tApp::Done(){

   delete this->MyTree;
   delete this->PageMan;
}//end tApp::Done

//---------------------------------------------------------------------------
bool tApp::LoadTree(){
   ifstream in(IRISPATH);
   myObject * obj;
   int w1;
   int w2;
   int count;
   int dim;
   double trash;

   // Load dim and size
   if (!in.is_open()){
      throw runtime_error("Unable to open the file");
   }//end if

   dim = 4;
   count = 150;
   cout << "Loading " << count << " objects...";

   // Create temp object
   obj = new myObject(dim);
   for (w1 = 0; w1 < count; w1++){
      for (w2 = 0; w2 < dim; w2++){
         in >> trash;
         (*obj)[w2] = trash;
      }//end for
      in >> trash;
      cout << " " << w1;      
      MyTree->Add(obj);
   }//end for
   cout << "done\n";

   delete obj;

   return true;
}//end tApp::LoadTree
