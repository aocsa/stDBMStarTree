//---------------------------------------------------------------------------
#include <fstream>
using namespace std;

#include "app.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

// Page Size
#define PAGESIZE (1024 * 4) 
#define OBJCOUNT 70000

//---------------------------------------------------------------------------
void tApp::Init(){

   this->PageMan = new stDiskPageManager("tree.dat", PAGESIZE);
   this->MyTree = new myDBMTree(this->PageMan);
   this->MyTree->SetSplitMethod(myDBMTree::smMIN_MAX);
   this->MyTree->SetChooseMethod(myDBMTree::cmMINDIST);
   this->MyTree->SetMinOccupation(0.3);

   LoadTree(); // Make it ready to use.
}//end tApp::Init

//---------------------------------------------------------------------------
void tApp::Run(){
   myObject * word[4];
   myResult * r;
   stTreeInfoResult * treeInfo;

   MyTree->MAMViewInit();

   MyTree->MAMViewSetOutputDir(".");

   word[0] = new myObject("catastrophic");
   word[1] = new myObject("buffalo");
   word[2] = new myObject("officemate");
   word[3] = new myObject("hifalutin");

   r = MyTree->RangeQuery(word[0], 1);
   delete r;
   r = MyTree->RangeQuery(word[1], 3);
   delete r;
   r = MyTree->NearestQuery(word[1], 2);
   delete r;
   r = MyTree->NearestQuery(word[2], 5);
   delete r;
   r = MyTree->NearestQuery(word[3], 10);
   delete r;

   MyTree->MAMViewDumpTree();

   delete[] word;
}//end tApp::Run

//---------------------------------------------------------------------------
void tApp::Done(){

   delete this->MyTree;
   delete this->PageMan;
}//end tApp::Done

//---------------------------------------------------------------------------
bool tApp::LoadTree(){
   ifstream in(DATAPATH);
   myObject obj;
   char buff[128];
   int w;

   // Load dim and size
   if (!in.is_open()){
      throw runtime_error("Unable to open the file");
   }//end if

   // Load words
   w = 0;
   cout << "Loading";
   while (in.getline(buff, 128) && w < OBJCOUNT){
      obj.SetString(buff);
//      this->MyTree->Add(&obj);
      if (w % 20 == 0){
         this->MyTree->Add(&obj);
         cout << '.';
      }//end if
      w++;
   }//end while
   cout << "Done!\n";
   return true;
}//end tApp::LoadTree
