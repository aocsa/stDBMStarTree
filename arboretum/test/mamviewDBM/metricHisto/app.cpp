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
   int size;
   double ValueX, ValueY;
   BYTE * ptr;
   tMetricHistogramBin * bins;
   tMetricHistogram * metricHisto;
   int i;

   if (in.is_open()){
      cout << "Loading objects...";
      while (in >> size){
         bins = new tMetricHistogramBin[size];
         for (int idx = 0; idx < size; idx++){
            in >> ValueX;
            in >> ValueY;
            bins[idx].Set(ValueX, ValueY);
         }//end for
         metricHisto = new tMetricHistogram(size, bins);
         MyTree->Add(metricHisto);
         delete metricHisto;
         delete[] bins;
      }//end while
      cout << "\nAdded " << MyTree->GetNumberOfObjects() << " objects...\n";
      in.close();
      return true;
   }else{
      cout << "Problem to open the file.";
      return false;
   }//end if
}//end tApp::LoadTree
