//---------------------------------------------------------------------------
#include <fstream>
using namespace std;

#include "app.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

//---------------------------------------------------------------------------
void tApp::Init(){

   this->PageMan = new stDiskPageManager("tree.dat", PAGESIZE);
   this->MyTree = new mySlimTree(this->PageMan);

   LoadTree(); // Make it ready to use.
   
   this->MyTree->Optimize();
}//end tApp::Init

//---------------------------------------------------------------------------
void tApp::Run(){
   stTreeInfoResult * treeInfo;

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
bool tApp::LoadTree(){
   ifstream in(FILEPATH);
   int size;
   int w = 0;
   char tmp[200];
   double ValueX, ValueY;
   BYTE * ptr;
   tMetricHistogramBin * bins;
   tMetricHistogram * metricHisto;

   if (!in.is_open()){
      printf("\nCannot open input file!");
   }else{
      while (in >> size){
         bins = new tMetricHistogramBin[size];
         for (int idx=0; idx<size; idx++){
            in >> ValueX;
            in >> ValueY;
            bins[idx].Set(ValueX, ValueY);
         }//end for
         metricHisto = new tMetricHistogram(size, bins);
         this->MyTree->Add(metricHisto);
         w++;
         if (w % 10 == 0){
            cout << '.';
         }//end if
         delete metricHisto;
         delete [] bins;
      }
      cout << " Added " << this->MyTree->GetNumberOfObjects() << " objects...";
      in.close();
   }//end else

   return true;
}//end tApp::LoadTree
