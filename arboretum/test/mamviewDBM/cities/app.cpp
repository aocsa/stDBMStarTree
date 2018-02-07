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
   cout << "\n" << this->MyTree->Consistency(); /**/
}//end tApp::Init

//---------------------------------------------------------------------------
void tApp::Run(){
   TCity * city;
   myResult * r;
   stTreeInfoResult * treeInfo;

   MyTree->MAMViewInit();

   MyTree->MAMViewSetOutputDir(".");

   city = new TCity("Santa Fe city-NM", 35.6672, -105.965);
   r = MyTree->RangeQuery(city, 0.3);
   delete r;
   r = MyTree->RangeQuery(city, 0.5);
   delete r;
   r = MyTree->NearestQuery(city, 5);
   delete r;
   r = MyTree->NearestQuery(city, 15);
   delete r;
   r = MyTree->NearestQuery(city, 20);
   delete r;

   MyTree->MAMViewDumpTree();

   delete city;
}//end tApp::Run

//---------------------------------------------------------------------------
void tApp::Done(){

   delete this->MyTree;
   delete this->PageMan;
}//end tApp::Done

//---------------------------------------------------------------------------
bool tApp::LoadTree(char * dataPath){
   ifstream in(dataPath);
   char cityName[200];
   int w;
   double dLat, dLong;
   TCity * city;

   w = 0;
   if (in.is_open()){
      cout << "Loading objects...";
      while(in.getline(cityName, 200, '\t')){
         in >> dLat;
         in >> dLong;
         in.ignore();
         city = new TCity(cityName, dLat, dLong);
         MyTree->Add(city);
         delete city;
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
