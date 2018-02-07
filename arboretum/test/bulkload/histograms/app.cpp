//---------------------------------------------------------------------------
// app.cpp - Implementation of the application.
//
// To change the behavior of this application, comment and uncomment lines at
// TApp::Init() and TApp::Query().
//
// Author: Thiago Galbiatti Vespa (thiago@icmc.sc.usp.br)
//         Marcos Rodrigues Vieira (mrvieira@icmc.usp.br)
//
// Copyright (c) 2006 GBDI-ICMC-USP
//---------------------------------------------------------------------------
#include <iostream>
#pragma hdrstop
#include "app.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
// Class TApp
//------------------------------------------------------------------------------


void TApp::Init(unsigned int pageSize, double maxDistance,
                unsigned int qtdK, unsigned int qtdRQ){
   randomize();
   this->PageSize = pageSize;
   this->MaxDistance = maxDistance;
   this->SizeKNNQ = qtdK;
   this->SizeRQ = qtdRQ;
   // To create it in disk
   CreateDiskPageManager();
   // Creates the tree
   CreateTree();
}//end TApp::Init


//------------------------------------------------------------------------------

void TApp::CreateTree(){
   // create for M-Tree
   MTreeBulk = new myMTree(MTreeBulkPageManager);
   MTreeNormal = new myMTree(MTreeNormalPageManager);

   // create for Slim-Tree
   SlimTreeBulk = new mySlimTree(SlimTreeBulkPageManager);
   SlimTreeNormal = new mySlimTree(SlimTreeNormalPageManager);
}//end TApp::CreateTree

//------------------------------------------------------------------------------
void TApp::CreateDiskPageManager(){
   char fileName[100];
   char pageSizeString[10];
   char tmpStr[11];
   ifstream in;
   sprintf(pageSizeString, "%d", this->PageSize);

   //for MTree
   strcpy(fileName, "MTreeNormal");
   strcat(fileName, pageSizeString);
   strcat(fileName, ".dat");
   in.open(fileName, ios_base::in);
   // Try to open the file.
   if (in.is_open()){
      // Cannot open. Create it.
      MTreeNormalPageManager = new stPlainDiskPageManager(fileName);
      in.close();
   }else{
      // Opened.
      MTreeNormalPageManager = new stPlainDiskPageManager(fileName, this->PageSize);
   }//end if

   //for SlimTree
   strcpy(fileName, "SlimTreeNormal");
   strcat(fileName, pageSizeString);
   strcat(fileName, ".dat");
   in.open(fileName, ios_base::in);
   // Try to open the file.
   if (in.is_open()){
      // Cannot open. Create it.
      SlimTreeNormalPageManager = new stPlainDiskPageManager(fileName);
      in.close();
   }else{
      // Opened.
      SlimTreeNormalPageManager = new stPlainDiskPageManager(fileName, this->PageSize);
   }//end if

   //for MTreeBulk
   strcpy(fileName, "MTreeBulk");
   strcat(fileName, pageSizeString);
   strcat(fileName, ".dat");
   in.open(fileName, ios_base::in);
   // Try to open the file.
   if (in.is_open()){
      // Cannot open. Create it.
      MTreeBulkPageManager = new stPlainDiskPageManager(fileName);
      in.close();
   }else{
      // Opened.
      MTreeBulkPageManager = new stPlainDiskPageManager(fileName, this->PageSize);
   }//end if

   //for SlimTreeBulk
   strcpy(fileName, "SlimTreeBulk");
   strcat(fileName, pageSizeString);
   strcat(fileName, ".dat");
   in.open(fileName, ios_base::in);
   // Try to open the file.
   if (in.is_open()){
      // Cannot open. Create it.
      SlimTreeBulkPageManager = new stPlainDiskPageManager(fileName);
      in.close();
   }else{
      // Opened.
      SlimTreeBulkPageManager = new stPlainDiskPageManager(fileName, this->PageSize);
   }//end if
}//end TApp::CreateDiskPageManager


//------------------------------------------------------------------------------
void TApp::Run(){

   // Lets load the tree with a lot values from the file.
   cout << "\n\nAdding objects...";
   LoadTree(INSFILE);

   #ifdef __stMAMVIEW__
      SlimTreeBulk->MAMViewInit();
      SlimTreeBulk->MAMViewSetOutputDir(".");
      SlimTreeBulk->MAMViewDumpTree();
   #endif //__stMAMVIEW__

   #ifdef __QUERYSLIM__

      cout << "\n\nLoading the query file";
      LoadVectorFromFile(QUERYCITYFILE);

      if (queryObjects.size() > 0){
         // Do 500 queries.
         PerformQueries();
      }//end if

   #endif

   cout << "\n\nFinished the whole test!";
}//end TApp::Run

//------------------------------------------------------------------------------
void TApp::Done(){

   if (this->MTreeBulk != NULL){
      delete this->MTreeBulk;
   }//end if
   if (this->MTreeNormal != NULL){
      delete this->MTreeNormal;
   }//end if

   if (this->SlimTreeBulk != NULL){
      delete this->SlimTreeBulk;
   }//end if
   if (this->SlimTreeNormal != NULL){
      delete this->SlimTreeNormal;
   }//end if


   if (this->MTreeBulkPageManager != NULL){
      delete this->MTreeBulkPageManager;
   }//end if
   if (this->MTreeNormalPageManager != NULL){
      delete this->MTreeNormalPageManager;
   }//end if

   if (this->SlimTreeBulkPageManager != NULL){
      delete this->SlimTreeBulkPageManager;
   }//end if
   if (this->SlimTreeNormalPageManager != NULL){
      delete this->SlimTreeNormalPageManager;
   }//end if

   // delete the vetor of queries.
   for (unsigned int i = 0; i < queryObjects.size(); i++){
      delete (queryObjects.at(i));
   }//end for
}//end TApp::Done


//------------------------------------------------------------------------------



void TApp::LoadTree(char * fileName){

   LoadTreeBulk(fileName);

   LoadTreeNormal(fileName);


}
//------------------------------------------------------------------------------
void TApp::LoadTreeBulk(char * fileName){

   myBasicArrayObject ** objects = new myBasicArrayObject * [MAXOBJ];

   clock_t start, end;


   cout << "\nBulk loading M-Tree.";

   if (MTreeBulk) {
      ifstream in(fileName);
      double values[MAXSIZE];
      myBasicArrayObject * basicArray;
      int i;
      int w = 0;

      //reset the statistics
      MTreeBulkPageManager->ResetStatistics();
      MTreeBulk->GetMetricEvaluator()->ResetStatistics();
      start = clock();

      if (in.is_open()){
         cout << "\nLoading objects ";


         while (in >> values[0]){
            for (i = 1; i < MAXSIZE; i++){
               in >> values[i];
            }//end for
            basicArray = new myBasicArrayObject(MAXSIZE, values);
            // Add it
            objects[w] = basicArray;
            w++;
            if (w % 100 == 0){
               cout << '.';
            }//end if
            //delete basicArray;
         }//end while
         in.close();

      }else{
         cout << "\nProblem to open the file.";
      }//end if


      MTreeBulk->BulkLoadMemory(objects, MAXOBJ);

      end = clock();

      cout << endl << "total time: "
           << ((double )end-(double )start) / CLK_TCK;

      cout << endl << " read disc accesses: "
           << (double )MTreeBulkPageManager->GetReadCount();

      cout << endl << " write disc accesses: "
           << (double )MTreeBulkPageManager->GetWriteCount();

      cout << endl << " access count disc accesses: "
           << (double )MTreeBulkPageManager->GetAccessCount();

      cout << endl << "distance calculations: "
           << (double )MTreeBulk->GetMetricEvaluator()->GetDistanceCount();

      cout << endl << " Added using BulkLoad: " << MTreeBulk->GetNumberOfObjects() << " objects ";
      cout << endl << " Consistency for BulkLoad: " << MTreeBulk->Consistency();



      for (int i = 0; i < MAXOBJ; i++) {
         delete objects[i];
      }//end for
      delete[] objects;
   }//end if


   objects = new myBasicArrayObject * [MAXOBJ];

   cout << "\nBulk loading Slim-Tree.";



   if (SlimTreeBulk) {
      ifstream in(fileName);
      double values[MAXSIZE];
      myBasicArrayObject * basicArray;
      int i;
      int w = 0;

      //reset the statistics
      SlimTreeBulkPageManager->ResetStatistics();
      SlimTreeBulk->GetMetricEvaluator()->ResetStatistics();
      start = clock();

      if (in.is_open()){
         cout << "\nLoading objects ";



         while (in >> values[0]){
            for (i = 1; i < MAXSIZE; i++){
               in >> values[i];
            }//end for
            basicArray = new myBasicArrayObject(MAXSIZE, values);
            // Add it
            objects[w] = basicArray;
            w++;
            if (w % 100 == 0){
               cout << '.';
            }//end if
            //delete basicArray;
         }//end while
         in.close();

      }else{
         cout << "\nProblem to open the file.";
      }//end if

      SlimTreeBulk->BulkLoadMemory(objects, MAXOBJ);
      
      end = clock();

      cout << endl << "total time: "
           << ((double )end-(double )start) / CLK_TCK;

      cout << endl << " read disc accesses: "
           << (double )SlimTreeBulkPageManager->GetReadCount();

      cout << endl << " write disc accesses: "
           << (double )SlimTreeBulkPageManager->GetWriteCount();

      cout << endl << " access count disc accesses: "
           << (double )SlimTreeBulkPageManager->GetAccessCount();

      cout << endl << "distance calculations: "
           << (double )SlimTreeBulk->GetMetricEvaluator()->GetDistanceCount();


      cout << endl << " Added using BulkLoad: " << SlimTreeBulk->GetNumberOfObjects() << " objects ";
      cout << endl << " Consistency for BulkLoad: " << SlimTreeBulk->Consistency();

      for (int i = 0; i < MAXOBJ; i++) {
         delete objects[i];
      }//end for
      delete[] objects;
   }//end if
}//end TApp::LoadTree

//------------------------------------------------------------------------------
void TApp::LoadTreeNormal(char * fileName){


   clock_t start, end;


   if (MTreeNormal){

      ifstream in(fileName);
      double values[MAXSIZE];
      myBasicArrayObject * basicArray;
      int i;
      int w = 0;

      //reset the statistics
      MTreeNormalPageManager->ResetStatistics();
      MTreeNormal->GetMetricEvaluator()->ResetStatistics();
      start = clock();

      cout << "\n\nNormal Insertion M-Tree.";

      if (in.is_open()){
         cout << "\nLoading objects ";
         while (in >> values[0]){
            for (i = 1; i < MAXSIZE; i++){
               in >> values[i];
            }//end for
            basicArray = new myBasicArrayObject(MAXSIZE, values);
            // Add it in Slim-Tree.
            this->AddToTree(basicArray, MTreeNormal);
            w++;
            if (w % 100 == 0){
               cout << '.';
            }//end if
            delete basicArray;
         }//end while
         cout << " Added " << MTreeNormal->GetNumberOfObjects() << " objects ";
         end = clock();
         in.close();

      }else{
         cout << "\nProblem to open the file.";
      }//end if



      in.close();

      cout << endl << "total time: "
           << ((double )end-(double )start) / CLK_TCK;

      cout << endl << " read disc accesses: "
           << (double )MTreeNormalPageManager->GetReadCount();

      cout << endl << " write disc accesses: "
           << (double )MTreeNormalPageManager->GetWriteCount();

      cout << endl << " access count disc accesses: "
           << (double )MTreeNormalPageManager->GetAccessCount();

      cout << endl << "distance calculations: "
           << (double )MTreeNormal->GetMetricEvaluator()->GetDistanceCount();


      cout << endl << " Added using Normal method: " << MTreeNormal->GetNumberOfObjects() << " objects ";
      cout << endl << " Consistency for the traditional MTree: " << MTreeNormal->Consistency();

   }//end if


   if (SlimTreeNormal){

      ifstream in(fileName);
      double values[MAXSIZE];
      myBasicArrayObject * basicArray;
      int i;
      int w = 0;

      //reset the statistics
      SlimTreeNormalPageManager->ResetStatistics();
      SlimTreeNormal->GetMetricEvaluator()->ResetStatistics();
      start = clock();

      cout << "\n\nNormal Insertion Slim-Tree.";

      if (in.is_open()){
         cout << "\nLoading objects ";
         while (in >> values[0]){
            for (i = 1; i < MAXSIZE; i++){
               in >> values[i];
            }//end for
            basicArray = new myBasicArrayObject(MAXSIZE, values);
            // Add it in Slim-Tree.
            this->AddToTree(basicArray, SlimTreeNormal);
            w++;
            if (w % 100 == 0){
               cout << '.';
            }//end if
            delete basicArray;
         }//end while
         cout << " Added " << SlimTreeNormal->GetNumberOfObjects() << " objects ";
         SlimTreeNormal->Optimize(); //Slim-Down
         end = clock();
         in.close();
      }else{
         cout << "\nProblem to open the file.";
      }//end if



      in.close();

      cout << endl << "total time: "
           << ((double )end-(double )start) / CLK_TCK;

      cout << endl << " read disc accesses: "
           << (double )SlimTreeNormalPageManager->GetReadCount();

      cout << endl << " write disc accesses: "
           << (double )SlimTreeNormalPageManager->GetWriteCount();

      cout << endl << " access count disc accesses: "
           << (double )SlimTreeNormalPageManager->GetAccessCount();

      cout << endl << "distance calculations: "
           << (double )SlimTreeNormal->GetMetricEvaluator()->GetDistanceCount();


      cout << endl << " Added using Normal method: " << SlimTreeNormal->GetNumberOfObjects() << " objects ";
      cout << endl << " Consistency for the traditional SlimTree: " << SlimTreeNormal->Consistency();



   }//end if

}//end TApp::LoadTreeSlim


//------------------------------------------------------------------------------
void TApp::LoadVectorFromFile(char * fileName){
   ifstream in(fileName);
   double values[MAXSIZE];
   myBasicArrayObject * basicArray;
   int i;

   // clear before using.
   queryObjects.clear();

   if (in.is_open()){
      cout << "\nLoading query objects ";
      while (in >> values[0]){
         for (i = 1; i < MAXSIZE; i++){
            in >> values[i];
         }//end for
         // Add it in vector.
         queryObjects.insert(queryObjects.end(), new myBasicArrayObject(MAXSIZE, values));
      }//end while
      cout << " Added " << queryObjects.size() << " query objects \n";
      in.close();
   }else{
      cout << "\nProblem to open the query file.";
      cout << "\n Zero object added!!\n";
   }//end if
}//end TApp::LoadVectorFromFile

//------------------------------------------------------------------------------
void TApp::PerformQueries(){

   char pageSizeString[10];
   string fileNameDA, fileNameDF, fileNameTT;
   char name[100], line[100];
   char strTmp[11];

   //for the result of the tests
   ResultMeasureDiscrete * rMeasurekNNQ = new ResultMeasureDiscrete(5, false, this->SizeKNNQ);
   ResultMeasure * rMeasureRQ = new ResultMeasure(false, this->SizeRQ, false, 3);

   sprintf(pageSizeString, "%d", this->PageSize);

   fileNameDF = string("HiRQDist") + pageSizeString + ".plt";
   fileNameDA = string("HiRQDisc") + pageSizeString + ".plt";
   fileNameTT = string("HiRQTime") + pageSizeString + ".plt";
   GNUPlot * gnuTestRQ = new GNUPlot(fileNameDA, fileNameDF, fileNameTT);

   fileNameDF = string("HikNNQDist") + pageSizeString + ".plt";
   fileNameDA = string("HikNNQDisc") + pageSizeString + ".plt";
   fileNameTT = string("HikNNQTime") + pageSizeString + ".plt";
   GNUPlot * gnuTestkNNQ = new GNUPlot(fileNameDA, fileNameDF, fileNameTT);

   gnuTestRQ->SetTitle(GNUPlot::DISTFUNCTION, "RQ: Histograms");
   gnuTestRQ->SetTitle(GNUPlot::DISKACCESS, "RQ: Histograms");
   gnuTestRQ->SetTitle(GNUPlot::TOTALTIME, "RQ: Histograms");
   gnuTestRQ->SetXLabel(GNUPlot::DISTFUNCTION, "% radius");
   gnuTestRQ->SetXLabel(GNUPlot::DISKACCESS, "% radius");
   gnuTestRQ->SetXLabel(GNUPlot::TOTALTIME, "% radius");
   gnuTestRQ->SetYLabel(GNUPlot::DISTFUNCTION, "Avg Number of Distance Calculation (x1000 - log)");
   gnuTestRQ->SetYLabel(GNUPlot::DISKACCESS, "Avg Number of Disk Access (x1000 - log)");
   gnuTestRQ->SetYLabel(GNUPlot::TOTALTIME, "Total Time (s - log)");

   gnuTestkNNQ->SetTitle(GNUPlot::DISTFUNCTION, "kNNQ: Histograms");
   gnuTestkNNQ->SetTitle(GNUPlot::DISKACCESS, "kNNQ: Histograms");
   gnuTestkNNQ->SetTitle(GNUPlot::TOTALTIME, "kNNQ: Histograms");
   gnuTestkNNQ->SetXLabel(GNUPlot::DISTFUNCTION, "k");
   gnuTestkNNQ->SetXLabel(GNUPlot::DISKACCESS, "k");
   gnuTestkNNQ->SetXLabel(GNUPlot::TOTALTIME, "k");
   gnuTestkNNQ->SetLogScale(GNUPlot::DISTFUNCTION, false);
   gnuTestkNNQ->SetLogScale(GNUPlot::DISKACCESS, false);
   gnuTestkNNQ->SetLogScale(GNUPlot::TOTALTIME, false);
   gnuTestkNNQ->SetYLabel(GNUPlot::DISTFUNCTION, "Avg Number of Distance Calculation (x1000)");
   gnuTestkNNQ->SetYLabel(GNUPlot::DISKACCESS, "Avg Number of Disk Access");
   gnuTestkNNQ->SetYLabel(GNUPlot::TOTALTIME, "Total Time (s)");



   if (MTreeNormal){
      cout << "\nStarting Statistics for Range Query with MTree.... ";
      PerformRangeQuery(rMeasureRQ, MTreeNormal, MTreeNormalPageManager);
      cout << " Ok\n";

      cout << "\nStarting Statistics for Nearest Query with MTree.... ";
      PerformNearestQuery(rMeasurekNNQ, MTreeNormal, MTreeNormalPageManager);
      cout << " Ok\n";

      // Add the result
      gnuTestRQ->AddMeasure(rMeasureRQ, "MTree");
      gnuTestkNNQ->AddMeasure(rMeasurekNNQ, "MTree");
      // Reset the statistics.
      rMeasureRQ->Reset();
      rMeasurekNNQ->Reset();
   }//end if

   if (SlimTreeNormal){
      cout << "\nStarting Statistics for Range Query with SlimTree.... ";
      PerformRangeQuery(rMeasureRQ, SlimTreeNormal, SlimTreeNormalPageManager);
      cout << " Ok\n";

      cout << "\nStarting Statistics for Nearest Query with SlimTree.... ";
      PerformNearestQuery(rMeasurekNNQ, SlimTreeNormal, SlimTreeNormalPageManager);
      cout << " Ok\n";

      // Add the result
      gnuTestRQ->AddMeasure(rMeasureRQ, "SlimTree");
      gnuTestkNNQ->AddMeasure(rMeasurekNNQ, "SlimTree");
      // Reset the statistics.
      rMeasureRQ->Reset();
      rMeasurekNNQ->Reset();
   }//end if

   if (MTreeBulk){
      cout << "\nStarting Statistics for Range Query with MTree-BulkLoad.... ";
      PerformRangeQuery(rMeasureRQ, MTreeBulk, MTreeBulkPageManager);
      cout << " Ok\n";

      cout << "\nStarting Statistics for Nearest Query with MTree-BulkLoad.... ";
      PerformNearestQuery(rMeasurekNNQ, MTreeBulk, MTreeBulkPageManager);
      cout << " Ok\n";

      // Add the result
      gnuTestRQ->AddMeasure(rMeasureRQ, "MTree-BulkLoad");
      gnuTestkNNQ->AddMeasure(rMeasurekNNQ, "MTree-BulkLoad");
      // Reset the statistics.
      rMeasureRQ->Reset();
      rMeasurekNNQ->Reset();
   }//end if

   if (SlimTreeBulk){
      cout << "\nStarting Statistics for Range Query with SlimTree-BulkLoad.... ";
      PerformRangeQuery(rMeasureRQ, SlimTreeBulk, SlimTreeBulkPageManager);
      cout << " Ok\n";

      cout << "\nStarting Statistics for Nearest Query with SlimTree-BulkLoad.... ";
      PerformNearestQuery(rMeasurekNNQ, SlimTreeBulk, SlimTreeBulkPageManager);
      cout << " Ok\n";

      // Add the result
      gnuTestRQ->AddMeasure(rMeasureRQ, "SlimTree-BulkLoad");
      gnuTestkNNQ->AddMeasure(rMeasurekNNQ, "SlimTree-BulkLoad");
      // Reset the statistics.
      rMeasureRQ->Reset();
      rMeasurekNNQ->Reset();
   }//end if

   // Write the files.
   gnuTestRQ->Write(GNUPlot::DISTFUNCTION);
   gnuTestRQ->Write(GNUPlot::DISKACCESS);
   gnuTestRQ->Write(GNUPlot::TOTALTIME);
   gnuTestkNNQ->Write(GNUPlot::DISTFUNCTION);
   gnuTestkNNQ->Write(GNUPlot::DISKACCESS);
   gnuTestkNNQ->Write(GNUPlot::TOTALTIME);

   //cleaning...
   delete gnuTestRQ;
   delete gnuTestkNNQ;
   delete rMeasurekNNQ;
   delete rMeasureRQ;




}//end TApp::PerformQuery




//------------------------------------------------------------------------------
void TApp::PerformRangeQuery(ResultMeasure * rMeasure, MetricTree * metricTree,
                             stPageManager * pageManager){

   myResult * result, * result2;
   stDistance radius;
   stDistance diameter;
   clock_t start, end;
   unsigned int i, j;
   unsigned int size;

   if (metricTree){
      size = queryObjects.size();
      //For number of points (radius) that I want measure.
      for (i = 0; i < rMeasure->GetSize(); i++){

         radius = rMeasure->GetK(i) * this->MaxDistance;
         //reset the statistics
         pageManager->ResetStatistics();
         metricTree->GetMetricEvaluator()->ResetStatistics();
         start = clock();
         for (j = 0; j < size; j++){
            result = metricTree->RangeQuery(queryObjects[j], radius);
            #ifdef __CMPANSWER__
               result2 = SlimMST->RangeQuery(queryObjects[j], radius);
               if (!result->IsEqual(result2)){
                  cout << "\n\n Pau\n";
                  int w;
                  myBasicArrayObject * tmp;

                  cout << "Range query with radius " << result->GetRadius() << ".\n";
                  //cout << "The sample object was " << *(result->GetSample()) << ".\n";

                  if (result->GetNumOfEntries() == 0){
                     cout << "No results in VPTree!\n";
                  }else{
                     cout << "\n  " << result->GetNumOfEntries() << " results in VPTree:\n";
                     for (w = 0; w < result->GetNumOfEntries(); w++){
                        tmp = (myBasicArrayObject *)(*result)[w].GetObject();
                        cout << "  Distance = " << (*result)[w].GetDistance();
                     }//end for
                  }//end if
                  if (result2->GetNumOfEntries() == 0){
                     cout << "No results in SlimTree!\n";
                  }else{
                     cout << "\n  " << result2->GetNumOfEntries() << " results in SlimTree:\n";
                     for (w = 0; w < result2->GetNumOfEntries(); w++){
                        tmp = (myBasicArrayObject *)(*result2)[w].GetObject();
                        cout << "  Distance = " << (*result2)[w].GetDistance();
                     }//end for
                  }//end if
               }//end if
               delete result2;
            #endif //__CMPANSWER__
            delete result;
         }//end for
         end = clock();
         rMeasure->SetTotalTime(i, ((double )end-(double )start) / CLK_TCK);
         // is divided for queryObjects to get the everage
         rMeasure->SetDiskAccess(i, (double )pageManager->GetReadCount() / (double )size);
         // is divided for queryObjects to get the everage
         rMeasure->SetDistanceFunction(i,
            (double )metricTree->GetMetricEvaluator()->GetDistanceCount() / ((double )size*1000.0));

         cout << rMeasure->GetK(i) << " ";
      }//end for
   }//end if
}//end TApp::PerformRangeQuery

//------------------------------------------------------------------------------
void TApp::PerformNearestQuery(ResultMeasureDiscrete * rMeasure, MetricTree * metricTree,
                               stPageManager * pageManager){

   myResult * result, * result2;
   clock_t start, end;
   unsigned int i, j;
   unsigned int size;

   if (metricTree){
      size = queryObjects.size();
      //For number of points (radius) that I want measure.
      for (i = 0; i < rMeasure->GetSize(); i++){

         //reset the statistics for Slim
         pageManager->ResetStatistics();
         metricTree->GetMetricEvaluator()->ResetStatistics();
         start = clock();
         for (j = 0; j < size; j++){
            result = metricTree->NearestQuery(queryObjects[j], rMeasure->GetK(i));
            #ifdef __CMPANSWER__
               result2 = SlimMST->NearestQuery(queryObjects[j], rMeasure->GetK(i));
               if (!result->IsEqual(result2)){
                  cout << "\n\n Pau\n";
                  int w;
                  myBasicArrayObject * tmp;

                  cout << "Nearest query with k " << result->GetK() << ".\n";
                  //cout << "The sample object was " << *(result->GetSample()) << ".\n";

                  if (result->GetNumOfEntries() == 0){
                     cout << "No results in VPTree!\n";
                  }else{
                     cout << "\n  " << result->GetNumOfEntries() << " results in VPTree:\n";
                     for (w = 0; w < result->GetNumOfEntries(); w++){
                        tmp = (myBasicArrayObject *)(*result)[w].GetObject();
                        cout << "  Distance = " << (*result)[w].GetDistance();
                     }//end for
                  }//end if
                  if (result2->GetNumOfEntries() == 0){
                     cout << "No results in SlimTree!\n";
                  }else{
                     cout << "\n  " << result2->GetNumOfEntries() << " results in SlimTree:\n";
                     for (w = 0; w < result2->GetNumOfEntries(); w++){
                        tmp = (myBasicArrayObject *)(*result2)[w].GetObject();
                        cout << "  Distance = " << (*result2)[w].GetDistance();
                     }//end for
                  }//end if
               }//end if
               delete result2;
            #endif //__CMPANSWER__
            delete result;
         }//end for
         end = clock();
         rMeasure->SetTotalTime(i, ((double )end-(double )start) / CLK_TCK);
         // is divided for queryObjects to get the everage
         rMeasure->SetDiskAccess(i, (double )pageManager->GetReadCount() / (double )size);
         // is divided for queryObjects to get the everage
         rMeasure->SetDistanceFunction(i,
            (double )metricTree->GetMetricEvaluator()->GetDistanceCount() / ((double )size*1000.0));

         cout << rMeasure->GetK(i) << " ";
      }//end for
   }//end if

}//end TApp::PerformNearestQuery
