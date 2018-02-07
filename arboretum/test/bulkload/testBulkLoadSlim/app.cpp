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

   //for mTree
   MTreeBulkPageManager = new stPlainDiskPageManager("MTreeBulk.dat", PAGESIZE);
   MTreeNormalPageManager = new stPlainDiskPageManager("MTreeNormal.dat", PAGESIZE);

   //for SlimTree
   SlimTreeBulkPageManager = new stPlainDiskPageManager("SlimTreeBulk.dat", PAGESIZE);
   SlimTreeNormalPageManager = new stPlainDiskPageManager("SlimTreeNormal.dat", PAGESIZE);

}//end TApp::CreateDiskPageManager

//------------------------------------------------------------------------------
void TApp::Run(){

   // Lets load the tree with a lot values from the file.
   cout << "\n\nAdding objects...";
   LoadTree(CITYFILE);

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
void TApp::LoadTree(char * fileName) {
   cout << "\n\nNormal Insertion...";
   LoadTreeNormal(fileName);

   cout << "\n\nBulk Loading...";
   LoadTreeBulk(fileName);
}
//------------------------------------------------------------------------------

void TApp::LoadTreeBulk(char * fileName){
   char cityName[200];
   double dLat, dLong;
   TCity ** objects = new TCity * [MAXOBJ];

   clock_t start, end;


   cout << "\nBulk loading M-Tree.";

   if (MTreeBulk) {
      ifstream in(fileName);
      long w = 0;
      //reset the statistics
      MTreeBulkPageManager->ResetStatistics();
      MTreeBulk->GetMetricEvaluator()->ResetStatistics();
      start = clock();

      if (in.is_open()){
         cout << "\nLoading objects ";
         while ((in.getline(cityName, 200, '\t')) && (w < MAXOBJ)){
            in >> dLat;
            in >> dLong;
            in.ignore();
            objects[w] = new TCity(cityName, dLat, dLong);
            w++;
            if (w % 10 == 0){
               cout << '.';
            }//end if
         }//end while
         end = clock();
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


   objects = new TCity * [MAXOBJ];

   cout << "\nBulk loading Slim-Tree.";



   if (SlimTreeBulk) {
      ifstream in(fileName);
      long w = 0;

      //reset the statistics
      SlimTreeBulkPageManager->ResetStatistics();
      SlimTreeBulk->GetMetricEvaluator()->ResetStatistics();
      start = clock();

      if (in.is_open()){
         cout << "\nLoading objects ";
         while ((in.getline(cityName, 200, '\t')) && (w < MAXOBJ)){
            in >> dLat;
            in >> dLong;
            in.ignore();
            objects[w] = new TCity(cityName, dLat, dLong);
            w++;
            if (w % 10 == 0){
               cout << '.';
            }//end if
         }//end while
         end = clock();
         in.close();
      }else{
         cout << "\nProblem to open the file.";
      }//end if

      SlimTreeBulk->BulkLoadMemory(objects, MAXOBJ);
      //SlimTree->Optimize();



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

   char cityName[200];
   double dLat, dLong;
   TCity * object;

   clock_t start, end;




   if (MTreeNormal){
      ifstream in(fileName);
      long w = 0;

      //reset the statistics
      MTreeNormalPageManager->ResetStatistics();
      MTreeNormal->GetMetricEvaluator()->ResetStatistics();
      start = clock();

      cout << "\nNormal Insertion M-Tree.";

      if (in.is_open()){
         cout << "\nLoading objects ";
         while ((in.getline(cityName, 200, '\t')) && (w < MAXOBJ)){
            in >> dLat;
            in >> dLong;
            in.ignore();
            object = new TCity(cityName, dLat, dLong);

            //cout << cityName << " " << dLat << " " << dLong << endl;
            MTreeNormal->Add(object);
            w++;
            if (w % 10 == 0){
               cout << '.';
            }//end if
            delete object;
         }//end while
         in.close();
         end = clock();
      }else{
         cout << "\nProblem to open the file.";
      }//end if


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
      long w = 0;

      //reset the statistics
      SlimTreeNormalPageManager->ResetStatistics();
      SlimTreeNormal->GetMetricEvaluator()->ResetStatistics();
      start = clock();

      cout << "\n\nNormal Insertion Slim-Tree.";

      if (in.is_open()){
         cout << "\nLoading objects ";
         while ((in.getline(cityName, 200, '\t')) && (w < MAXOBJ)){
            in >> dLat;
            in >> dLong;
            in.ignore();
            object = new TCity(cityName, dLat, dLong);

            //cout << cityName << " " << dLat << " " << dLong << endl;
            SlimTreeNormal->Add(object);
            w++;
            if (w % 10 == 0){
               cout << '.';
            }//end if
            delete object;
         }//end while
         in.close();
         end = clock();
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
   char cityName[200];
//   int cont;
   double dLat, dLong;

   // clear before using.
   queryObjects.clear();

   if (in.is_open()){
      cout << "\nLoading query objects ";
      while(in.getline(cityName, 200, '\t')){
         in >> dLat;
         in >> dLong;
         in.ignore();
         this->queryObjects.insert(queryObjects.end(), new TCity(cityName, dLat, dLong));
      }//end while
      cout << " Added " << queryObjects.size() << " query objects ";
      in.close();
   }else{
      cout << "\nProblem to open the query file.";
      cout << "\n Zero object added!!\n";
   }//end if
}//end TApp::LoadVectorFromFile

//------------------------------------------------------------------------------
void TApp::PerformQueries(){
   cout << "\nStarting Statistics for Range Query.... ";
   PerformRangeQuery();
   cout << " Ok\n";

   cout << "\nStarting Statistics for Nearest Query.... ";
   PerformNearestQuery();
   cout << " Ok\n";


}//end TApp::PerformQuery

//------------------------------------------------------------------------------

void TApp::PerformRangeQuery(){
   cout << "\n\nRange Query Bulk Loaded.... ";
   PerformRangeQueryBulk();
   cout << "\n\nRange Query Normal.... ";
   PerformRangeQueryNormal();
}

//------------------------------------------------------------------------------
void TApp::PerformRangeQueryBulk(){

   myResult * result;
   stDistance radius;
   clock_t start, end;
   double sum, stdDev;
   unsigned int min, max;
   unsigned int size;
   unsigned int i, j;

   if (MTreeBulk){
      size = queryObjects.size();

      cout << "\nRange Query M-Tree.";

      //reset the statistics
      MTreeBulkPageManager->ResetStatistics();
      MTreeBulk->GetMetricEvaluator()->ResetStatistics();
      sum = 0;
      stdDev = 0;
      min = MAXINT;
      max = 0;
      start = clock();
      for (j=0; j < size; j++){
         result = MTreeBulk->RangeQuery(queryObjects[j], RADIUS);
         sum += result->GetNumOfEntries();

         if (min > result->GetNumOfEntries()){
            min = result->GetNumOfEntries();
         }else if (max < result->GetNumOfEntries()){
            max = result->GetNumOfEntries();
         }//end if
         delete result;
      }//end for
      end = clock();
      stdDev = (double)max - (sum/(double )size);
      if (stdDev < (sum/(double )size) - (double)min){
         stdDev = (sum/(double )size) - (double)min;
      }//end if
      cout << endl << "sum: " << sum/(double )size << " min: " << min << " max: " << max << " std dev: " << stdDev << endl;
      cout << endl << "total time: "
           << ((double )end-(double )start) / CLK_TCK;
      // is divided for queryObjects to get the everage
      cout << endl << "disc accesses: "
           << (double )MTreeBulkPageManager->GetReadCount() / (double )size;
      // is divided for queryObjects to get the everage
      cout << endl << "distance calculations: "
           << (double )MTreeBulk->GetMetricEvaluator()->GetDistanceCount() / (double )size;


   }//end if


   if (SlimTreeBulk){
      size = queryObjects.size();

      cout << "\nRange Query Slim-Tree.";

      //reset the statistics
      SlimTreeBulkPageManager->ResetStatistics();
      SlimTreeBulk->GetMetricEvaluator()->ResetStatistics();
      sum = 0;
      stdDev = 0;
      min = MAXINT;
      max = 0;
      start = clock();
      for (j=0; j < size; j++){
         result = SlimTreeBulk->RangeQuery(queryObjects[j], RADIUS);
         sum += result->GetNumOfEntries();

         if (min > result->GetNumOfEntries()){
            min = result->GetNumOfEntries();
         }else if (max < result->GetNumOfEntries()){
            max = result->GetNumOfEntries();
         }//end if
         delete result;
      }//end for
      end = clock();
      stdDev = (double)max - (sum/(double )size);
      if (stdDev < (sum/(double )size) - (double)min){
         stdDev = (sum/(double )size) - (double)min;
      }//end if
      cout << endl << "sum: " << sum/(double )size << " min: " << min << " max: " << max << " std dev: " << stdDev << endl;
      cout << endl << "total time: "
           << ((double )end-(double )start) / CLK_TCK;
      // is divided for queryObjects to get the everage
      cout << endl << "disc accesses: "
           << (double )SlimTreeBulkPageManager->GetReadCount() / (double )size;
      // is divided for queryObjects to get the everage
      cout << endl << "distance calculations: "
           << (double )SlimTreeBulk->GetMetricEvaluator()->GetDistanceCount() / (double )size;


   }//end if

}//end TApp::PerformRangeQuery

//------------------------------------------------------------------------------

void TApp::PerformRangeQueryNormal(){

   myResult * result;
   stDistance radius;
   clock_t start, end;
   double sum, stdDev;
   unsigned int min, max;
   unsigned int size;
   unsigned int i, j;

   if (MTreeNormal){
      size = queryObjects.size();

      cout << "\nRange Query M-Tree.";

      //reset the statistics
      MTreeNormalPageManager->ResetStatistics();
      MTreeNormal->GetMetricEvaluator()->ResetStatistics();
      sum = 0;
      stdDev = 0;
      min = MAXINT;
      max = 0;
      start = clock();
      for (j=0; j < size; j++){
         result = MTreeNormal->RangeQuery(queryObjects[j], RADIUS);
         sum += result->GetNumOfEntries();

         if (min > result->GetNumOfEntries()){
            min = result->GetNumOfEntries();
         }else if (max < result->GetNumOfEntries()){
            max = result->GetNumOfEntries();
         }//end if
         delete result;
      }//end for
      end = clock();
      stdDev = (double)max - (sum/(double )size);
      if (stdDev < (sum/(double )size) - (double)min){
         stdDev = (sum/(double )size) - (double)min;
      }//end if
      cout << endl << "sum: " << sum/(double )size << " min: " << min << " max: " << max << " std dev: " << stdDev << endl;
      cout << endl << "total time: "
           << ((double )end-(double )start) / CLK_TCK;
      // is divided for queryObjects to get the everage
      cout << endl << "disc accesses: "
           << (double )MTreeNormalPageManager->GetReadCount() / (double )size;
      // is divided for queryObjects to get the everage
      cout << endl << "distance calculations: "
           << (double )MTreeNormal->GetMetricEvaluator()->GetDistanceCount() / (double )size;


   }//end if


   if (SlimTreeNormal){
      size = queryObjects.size();

      cout << "\nRange Query Slim-Tree.";

      //reset the statistics
      SlimTreeNormalPageManager->ResetStatistics();
      SlimTreeNormal->GetMetricEvaluator()->ResetStatistics();
      sum = 0;
      stdDev = 0;
      min = MAXINT;
      max = 0;
      start = clock();
      for (j=0; j < size; j++){
         result = SlimTreeNormal->RangeQuery(queryObjects[j], RADIUS);
         sum += result->GetNumOfEntries();

         if (min > result->GetNumOfEntries()){
            min = result->GetNumOfEntries();
         }else if (max < result->GetNumOfEntries()){
            max = result->GetNumOfEntries();
         }//end if
         delete result;
      }//end for
      end = clock();
      stdDev = (double)max - (sum/(double )size);
      if (stdDev < (sum/(double )size) - (double)min){
         stdDev = (sum/(double )size) - (double)min;
      }//end if
      cout << endl << "sum: " << sum/(double )size << " min: " << min << " max: " << max << " std dev: " << stdDev << endl;
      cout << endl << "total time: "
           << ((double )end-(double )start) / CLK_TCK;
      // is divided for queryObjects to get the everage
      cout << endl << "disc accesses: "
           << (double )SlimTreeNormalPageManager->GetReadCount() / (double )size;
      // is divided for queryObjects to get the everage
      cout << endl << "distance calculations: "
           << (double )SlimTreeNormal->GetMetricEvaluator()->GetDistanceCount() / (double )size;


   }//end if

}//end TApp::PerformRangeQuery




//------------------------------------------------------------------------------
void TApp::PerformNearestQuery(){
   cout << "\n\nNearest Query Bulk Loaded.... ";
   PerformNearestQueryBulk();
   cout << "\n\nNearest Query Normal.... ";
   PerformNearestQueryNormal();
}

//------------------------------------------------------------------------------
void TApp::PerformNearestQueryBulk(){

   myResult * result;

   clock_t start, end;
   unsigned int size;
   unsigned int i, j;


   if (MTreeBulk){
      size = queryObjects.size();

      cout << "\nkNN M-Tree.";

      //reset the statistics for M
      MTreeBulkPageManager->ResetStatistics();
      MTreeBulk->GetMetricEvaluator()->ResetStatistics();
      start = clock();
      for (j=0; j < size; j++){
         result = MTreeBulk->NearestQuery(queryObjects[j], K);
         delete result;
      }//end for
      end = clock();
      cout << endl << "total time: "
           << ((double )end-(double )start) / CLK_TCK;
      // is divided for queryObjects to get the everage
      cout << endl << "disc accesses: "
           << (double )MTreeBulkPageManager->GetReadCount() / (double )size;
      // is divided for queryObjects to get the everage
      cout << endl << "distance calculations: "
           << (double )MTreeBulk->GetMetricEvaluator()->GetDistanceCount() / (double )size;


   }//end if


   if (SlimTreeBulk){
      size = queryObjects.size();

      cout << "\nkNN Slim-Tree.";

      //reset the statistics for Slim
      SlimTreeBulkPageManager->ResetStatistics();
      SlimTreeBulk->GetMetricEvaluator()->ResetStatistics();
      start = clock();
      for (j=0; j < size; j++){
         result = SlimTreeBulk->NearestQuery(queryObjects[j], K);
         delete result;
      }//end for
      end = clock();
      cout << endl << "total time: "
           << ((double )end-(double )start) / CLK_TCK;
      // is divided for queryObjects to get the everage
      cout << endl << "disc accesses: "
           << (double )SlimTreeBulkPageManager->GetReadCount() / (double )size;
      // is divided for queryObjects to get the everage
      cout << endl << "distance calculations: "
           << (double )SlimTreeBulk->GetMetricEvaluator()->GetDistanceCount() / (double )size;

   }//end if
}//end TApp::PerformNearestQuery

//------------------------------------------------------------------------------
void TApp::PerformNearestQueryNormal(){

   myResult * result;
   myResult * result2;
   clock_t start, end;
   unsigned int size;
   unsigned int i, j;

   if (MTreeNormal){
      size = queryObjects.size();

      cout << "\nkNN M-Tree.";

      //reset the statistics for M
      MTreeNormalPageManager->ResetStatistics();
      MTreeNormal->GetMetricEvaluator()->ResetStatistics();
      start = clock();
      for (j=0; j < size; j++){
         result = MTreeNormal->NearestQuery(queryObjects[j], K);
         delete result;
      }//end for
      end = clock();
      cout << endl << "total time: "
           << ((double )end-(double )start) / CLK_TCK;
      // is divided for queryObjects to get the everage
      cout << endl << "disc accesses: "
           << (double )MTreeNormalPageManager->GetReadCount() / (double )size;
      // is divided for queryObjects to get the everage
      cout << endl << "distance calculations: "
           << (double )MTreeNormal->GetMetricEvaluator()->GetDistanceCount() / (double )size;

   }//end if

   if (SlimTreeNormal){
      size = queryObjects.size();

      cout << "\nkNN Slim-Tree.";

      //reset the statistics for Slim
      SlimTreeNormalPageManager->ResetStatistics();
      SlimTreeNormal->GetMetricEvaluator()->ResetStatistics();
      start = clock();
      for (j=0; j < size; j++){
         result = SlimTreeNormal->NearestQuery(queryObjects[j], K);
         delete result;
      }//end for
      end = clock();
      cout << endl << "total time: "
           << ((double )end-(double )start) / CLK_TCK;
      // is divided for queryObjects to get the everage
      cout << endl << "disc accesses: "
           << (double )SlimTreeNormalPageManager->GetReadCount() / (double )size;
      // is divided for queryObjects to get the everage
      cout << endl << "distance calculations: "
           << (double )SlimTreeNormal->GetMetricEvaluator()->GetDistanceCount() / (double )size;


   }//end if
}//end TApp::PerformNearestQuery
