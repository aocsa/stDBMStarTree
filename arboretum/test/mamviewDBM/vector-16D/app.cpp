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
   double values0[] = {0.540033, 0.440387, 0.441820, 0.429985, 0.434104, 0.442185, 0.444674, 0.436901, 0.440147, 0.443123, 0.437200, 0.442684, 0.441088, 0.439991, 0.438262, 0.440930};
   double values1[] = {0.534563, 0.444249, 0.754017, 0.021705, 0.121695, 0.488539, 0.525755, 0.807681, 0.965271, 0.947438, 0.586423, 0.949353, 0.796199, 0.220760, 0.097806, 0.906685};
   myResult * r;

   if (!strcmp(dataPath, "../../data/LyfnmpResto.txt")){
      point = new TPoint(values0);
   }else{ //../../data/gen5_16DSResto.txt
      point = new TPoint(values1);
   }//end if

   MyTree->MAMViewInit();

   MyTree->MAMViewSetOutputDir(".");

   r = MyTree->RangeQuery(point, 0.01 * MyTree->GetGreaterEstimatedDistance());
   delete r;
   r = MyTree->RangeQuery(point, 0.03 * MyTree->GetGreaterEstimatedDistance());
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
         for (i = 1; i<MAXSIZE; i++){
            in >> values[i];
         }//end for
         point = new TPoint(values);
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
