//---------------------------------------------------------------------------
// app.cpp - Implementation of the application.
//
// To change the behavior of this application, comment and uncomment lines at
// TApp::Init() and TApp::Query().
//
// Authors: Marcos Rodrigues Vieira (mrvieira@icmc.sc.usp.br)
// Copyright (c) 2003 GBDI-ICMC-USP
//---------------------------------------------------------------------------
#include <iostream>
#pragma hdrstop
#include "app.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)

//------------------------------------------------------------------------------
void TApp::Init(unsigned int pageSize, unsigned int k, 
                unsigned int quantidadeRange, char * prefix){
   this->PageSize = pageSize;
   this->QuantidadeRange = quantidadeRange;
   this->K = k;
   this->Prefix = prefix;
   // To create it in disk
   CreateDiskPageManager();
   // Creates the tree
   CreateTree();
}//end TApp::Init

//------------------------------------------------------------------------------
void TApp::CreateDiskPageManager(){
   char fileName[100];
   char pageSizeString[100];
   FILE * file;

   itoa(this->PageSize, pageSizeString, 10);

   //for Slim-tree
   strcpy(fileName, this->Prefix.c_str());
   strcat(fileName, "Slim");
   strcat(fileName, pageSizeString);
   strcat(fileName, ".dat");
   // Try to open the file.
   if ((file = fopen(fileName, "r")) == NULL){
      // Opened.
      PageManagerSlim = new stPlainDiskPageManager(fileName, this->PageSize);
   }else{
      // Cannot open. Create it.
      PageManagerSlim = new stPlainDiskPageManager(fileName);
      fclose(file);
   }//end if

   //for Dummy-tree
   strcpy(fileName, this->Prefix.c_str());
   strcat(fileName, "Dummy");
   strcat(fileName, pageSizeString);
   strcat(fileName, ".dat");
   // Try to open the file.
   if ((file = fopen(fileName, "r")) == NULL){
      // Opened.
      PageManagerDummy = new stPlainDiskPageManager(fileName, this->PageSize);
   }else{
      // Cannot open. Create it.
      PageManagerDummy = new stPlainDiskPageManager(fileName);
      fclose(file);
   }//end if
}//end TApp::CreateDiskPageManager

//------------------------------------------------------------------------------
void TApp::CreateTree(){
   // create for Slim-tree
   SlimTree = new mySlimTree(PageManagerSlim);
   SlimTree->SetSplitMethod(mySlimTree::smSPANNINGTREE);
   SlimTree->SetChooseMethod(mySlimTree::cmMINDIST);

   // create for Dummy-tree
   DummyTree = new myDummyTree(PageManagerDummy);
}//end TApp::CreateTree

//------------------------------------------------------------------------------
void TApp::Run(char * DataPath, char * DataQueryPath1,
               char * DataQueryPath2, char * DataQueryPath3){
   // Lets load the tree with a lot values from the file.
   cout << "Adding objects in the MetricTreeSlim\n";
   LoadTree(DataPath, SlimTree);
   cout << "Adding objects in the MetricTreeDummy\n";
   LoadTree(DataPath, DummyTree);
   // Lets do the queries
   cout << "Adding query objects ...\n";
   LoadVectorFromFile(DataQueryPath1, DataQueryPath2, DataQueryPath3);
   // Do 500 queries.
   PerformQueries();
   // Hold the screen.
   cout << "Finished the whole test!\n";
}//end TApp::Run

//------------------------------------------------------------------------------
void TApp::Done(){

   if (this->SlimTree != NULL){
      delete this->SlimTree;
   }//end if
   if (this->DummyTree != NULL){
      delete this->DummyTree;
   }//end if

   if (this->PageManagerSlim != NULL){
      delete this->PageManagerSlim;
   }//end if
   if (this->PageManagerDummy != NULL){
      delete this->PageManagerDummy;
   }//end if

   // delete the vetor of queries.
   for (int idx = 0; idx < NUMBEROFCENTERS; idx++){
      for (unsigned int i = 0; i < queryObjects[idx].size(); i++){
         delete (queryObjects[idx].at(i));
      }//end for
   }//end for
}//end TApp::Done

//------------------------------------------------------------------------------
void TApp::LoadTree(char * fileName, MetricTree * metricTree){

   FILE * file;
   long w = 0;
   char buffer[200], word[200];
   char * ptr;

   if (metricTree!=NULL){
      // Is there any object?
      if (metricTree->GetNumberOfObjects() == 0){
         if ((file = fopen(fileName, "r")) == NULL){
            cout << "Cannot open input file!\n\n";
         }else{
            fgets(buffer, 200, file);
            do{
               strcpy(word, buffer);
               ptr = strchr(word, '\n');
               *ptr = '\0';
               AddToTree(word, metricTree);
               fgets(buffer, 200, file);
               w++;
               if (w % 100 == 0){
                  cout << ".";
               }//end if
            }while(!feof(file)); //end do
            cout << "Added " << metricTree->GetNumberOfObjects() << " objects...\n";
            fclose(file);
            cout << "Performing the Slim-Down Algorithm\n";
            metricTree->Optimize();
         }//end else
      }//end else
   }else{
      cout << "Zero object added!!\n";
   }//end else
}//end TApp::LoadTree()

//------------------------------------------------------------------------------
void TApp::LoadVectorFromFile(char * fileName1, char * fileName2, char * fileName3){
   ifstream in;
   int id, i, contObj;
   int idx;
   char buffer[200], word[200];
   char * ptr;
   int size;
   char * fileName;

   for (idx = 0; idx < 3; idx++){
      if (idx==0){
         fileName = fileName1;
      }else if (idx==1){
         fileName = fileName2;
      }else{
         fileName = fileName3;
      }//end if
      contObj = 0;
      in.open(fileName);
      if (!in.is_open()){
         cout << "Cannot open input query file.\n";
      }else{
         cout << "\nLoading query objects ";
         queryObjects[idx].clear();
         contObj = 0;
         while(in.getline(word, 200, '\n')){
            // Add it in vector.
            queryObjects[idx].insert(queryObjects[idx].end(), new TWord(word));
            contObj++;
         }//end while
         cout << " Added " << contObj << " query objects in " << idx << "\n";
         in.close();
     }//end else
  }//end for
}//end TApp::LoadVectorFromFile

//------------------------------------------------------------------------------
void TApp::PerformQueries(){

   char pause[] = "\npause -1";
   char pageSizeString[10];
   char fileName[50];

   FILE * fileDist, * fileTime, * fileDisc;

   //for the result of the tests
   ResultMeasureDiscrete * rMeasureMultipleSlim = new ResultMeasureDiscrete(this->QuantidadeRange);
   ResultMeasureDiscrete * rMeasureMultipleDummy = new ResultMeasureDiscrete(this->QuantidadeRange);
   ResultMeasureDiscrete * rMeasureBasicSlim = new ResultMeasureDiscrete(this->QuantidadeRange);
   ResultMeasureDiscrete * rMeasureBasicDummy = new ResultMeasureDiscrete(this->QuantidadeRange);
   ResultMeasureDiscrete * rMeasureRangeSlim = new ResultMeasureDiscrete(this->QuantidadeRange);
   ResultMeasureDiscrete * rMeasureRangeDummy = new ResultMeasureDiscrete(this->QuantidadeRange);
   ResultMeasureDiscrete * rMeasureNearestSlim = new ResultMeasureDiscrete(this->QuantidadeRange);
   ResultMeasureDiscrete * rMeasureNearestDummy = new ResultMeasureDiscrete(this->QuantidadeRange);
   ResultMeasureDiscrete * rMeasureKAndNearestSlim = new ResultMeasureDiscrete(this->QuantidadeRange);
   ResultMeasureDiscrete * rMeasureKAndNearestDummy = new ResultMeasureDiscrete(this->QuantidadeRange);
   ResultMeasureDiscrete * rMeasureNearest_Inter_RangeSlim = new ResultMeasureDiscrete(this->QuantidadeRange);
   ResultMeasureDiscrete * rMeasureNearest_Inter_RangeDummy = new ResultMeasureDiscrete(this->QuantidadeRange);

   itoa(this->PageSize, pageSizeString, 10);

   //set the name and the header of the distance function file for RQ
   strcpy(fileName, this->Prefix.c_str());
   strcat(fileName, "Dist");
   strcat(fileName, pageSizeString);
   strcat(fileName, ".plt");
   fileDist = fopen(fileName, "w");
   WriteHeader(fileDist, "set ylabel \"# AVG Distance Function\"\n");
   //set the name and the header of the disc access file for RQ
   strcpy(fileName, this->Prefix.c_str());
   strcat(fileName, "Disc");
   strcat(fileName, pageSizeString);
   strcat(fileName, ".plt");
   fileDisc = fopen(fileName, "w");
   WriteHeader(fileDisc, "set ylabel \"# AVG Disc Access\"\n");
   //set the name and the header of the time file for RQ
   strcpy(fileName, this->Prefix.c_str());
   strcat(fileName,"Time");
   strcat(fileName, pageSizeString);
   strcat(fileName, ".plt");
   fileTime = fopen(fileName, "w");
   WriteHeader(fileTime, "set ylabel \"Total Time\"\n");

   cout << "\nStarting Statistics for multiple centers.... ";
   PerformMultipleNearestAndRange(rMeasureMultipleSlim, rMeasureMultipleDummy,
                                  rMeasureBasicSlim, rMeasureBasicDummy);
   cout << " Ok\n";

   cout << "\nStarting Statistics for simple queries.... ";
   PerformSingleNearestAndRange(rMeasureRangeSlim, rMeasureRangeDummy,
         rMeasureNearestSlim, rMeasureNearestDummy,
         rMeasureKAndNearestSlim, rMeasureKAndNearestDummy,
         rMeasureNearest_Inter_RangeSlim, rMeasureNearest_Inter_RangeDummy);
   cout << " Ok\n";

   //write the statistics to files
   //Distance Function
   WriteToFile(fileDist, rMeasureMultipleSlim, 1);
   WriteToFile(fileDist, rMeasureMultipleDummy, 1);
   WriteToFile(fileDist, rMeasureBasicSlim, 1);
   WriteToFile(fileDist, rMeasureBasicDummy, 1);
   WriteToFile(fileDist, rMeasureRangeSlim, 1);
   WriteToFile(fileDist, rMeasureRangeDummy, 1);
   WriteToFile(fileDist, rMeasureNearestSlim, 1);
   WriteToFile(fileDist, rMeasureNearestDummy, 1);
   WriteToFile(fileDist, rMeasureKAndNearestSlim, 1);
   WriteToFile(fileDist, rMeasureKAndNearestDummy, 1);
   WriteToFile(fileDist, rMeasureNearest_Inter_RangeSlim, 1);
   WriteToFile(fileDist, rMeasureNearest_Inter_RangeDummy, 1);
   //Disc Access
   WriteToFile(fileDisc, rMeasureMultipleSlim, 2);
   WriteToFile(fileDisc, rMeasureMultipleDummy, 2);
   WriteToFile(fileDisc, rMeasureBasicSlim, 2);
   WriteToFile(fileDisc, rMeasureBasicDummy, 2);
   WriteToFile(fileDisc, rMeasureRangeSlim, 2);
   WriteToFile(fileDisc, rMeasureRangeDummy, 2);
   WriteToFile(fileDisc, rMeasureNearestSlim, 2);
   WriteToFile(fileDisc, rMeasureNearestDummy, 2);
   WriteToFile(fileDisc, rMeasureKAndNearestSlim, 2);
   WriteToFile(fileDisc, rMeasureKAndNearestDummy, 2);
   WriteToFile(fileDisc, rMeasureNearest_Inter_RangeSlim, 2);
   WriteToFile(fileDisc, rMeasureNearest_Inter_RangeDummy, 2);
   //Total Time
   WriteToFile(fileTime, rMeasureMultipleSlim, 3);
   WriteToFile(fileTime, rMeasureMultipleDummy, 3);
   WriteToFile(fileTime, rMeasureBasicSlim, 3);
   WriteToFile(fileTime, rMeasureBasicDummy, 3);
   WriteToFile(fileTime, rMeasureRangeSlim, 3);
   WriteToFile(fileTime, rMeasureRangeDummy, 3);
   WriteToFile(fileTime, rMeasureNearestSlim, 3);
   WriteToFile(fileTime, rMeasureNearestDummy, 3);
   WriteToFile(fileTime, rMeasureKAndNearestSlim, 3);
   WriteToFile(fileTime, rMeasureKAndNearestDummy, 3);
   WriteToFile(fileTime, rMeasureNearest_Inter_RangeSlim, 3);
   WriteToFile(fileTime, rMeasureNearest_Inter_RangeDummy, 3);
   // Reset the statistics.
   rMeasureMultipleSlim->Reset();
   rMeasureMultipleDummy->Reset();
   rMeasureBasicSlim->Reset();
   rMeasureBasicDummy->Reset();
   rMeasureRangeSlim->Reset();
   rMeasureRangeDummy->Reset();
   rMeasureNearestSlim->Reset();
   rMeasureNearestDummy->Reset();
   rMeasureKAndNearestSlim->Reset();
   rMeasureKAndNearestDummy->Reset();
   rMeasureNearest_Inter_RangeSlim->Reset();
   rMeasureNearest_Inter_RangeDummy->Reset();

   // write pause into the files.
   fwrite(pause, strlen(pause), 1, fileDisc);
   fwrite(pause, strlen(pause), 1, fileDist);
   fwrite(pause, strlen(pause), 1, fileTime);
   // close the files.
   fclose(fileDist);
   fclose(fileDisc);
   fclose(fileTime);
   //cleaning...
   delete rMeasureMultipleSlim;
   delete rMeasureBasicSlim;
   delete rMeasureMultipleDummy;
   delete rMeasureBasicDummy;
   delete rMeasureRangeSlim;
   delete rMeasureRangeDummy;
   delete rMeasureNearestSlim;
   delete rMeasureNearestDummy;
   delete rMeasureKAndNearestSlim;
   delete rMeasureKAndNearestDummy;
   delete rMeasureNearest_Inter_RangeSlim;
   delete rMeasureNearest_Inter_RangeDummy;
}//end TApp::PerformQuery

//------------------------------------------------------------------------------
void TApp::PerformMultipleNearestAndRange(
      ResultMeasureDiscrete * rMeasureMultiSlim, ResultMeasureDiscrete * rMeasureMultiDummy,
      ResultMeasureDiscrete * rMeasureBasicSlim, ResultMeasureDiscrete * rMeasureBasicDummy){

   myResult * result[NUMBEROFCENTERS],
            * resultRange[NUMBEROFCENTERS], * resultNearest[NUMBEROFCENTERS],
            * resultTemp, * finalResult;
   long numberOfObject = SlimTree->GetNumberOfObjects();
   clock_t start, end;
   unsigned int i, j, idx;
   stCount radius;
   stCount size = queryObjects[0].size();
   
   //For number of points (radius) that I want measure.
   for (i = 0; i < rMeasureMultiSlim->getSize(); i++){
      // Set the radius.
      radius = rMeasureMultiSlim->getK(i);
      // Statistics for Multiple Slim-Tree
      // Reset the statistics
      PageManagerSlim->ResetStatistics();
      SlimTree->GetMetricEvaluator()->ResetStatistics();
      start = clock();
      for (j = 0; j < size; j++){
         // Set the queries variables and do the queries
         for (idx = 0; idx < NUMBEROFCENTERS; idx++){
            result[idx] = SlimTree->KAndRangeQuery(queryObjects[idx][j], radius, this->K);
         }//end for
         // Do the Union of results
         resultTemp = new myResult();
         finalResult = new myResult();
         resultTemp->Union(result[0], result[1]);
         finalResult->Union(resultTemp, result[2]);
         // clean
         for(idx = 0; idx < NUMBEROFCENTERS; idx++){
            delete result[idx];
         }//end for
         delete resultTemp;
         delete finalResult;
      }//end for
      end = clock();
      // Get the tests results. 
      rMeasureMultiSlim->setTotalTime(i, ((double )end-(double )start) / CLK_TCK);
      // is divided for queryObjects1 to get the everage
      rMeasureMultiSlim->setDiskAccess(i, (double )PageManagerSlim->GetReadCount() / (double )size);
      // is divided for queryObjects to get the everage
      rMeasureMultiSlim->setDistanceFunction(i,
         (double )SlimTree->GetMetricEvaluator()->GetDistanceCount() / (double )size);

      // Statisctics for Multiple Dummy
      // Reset the statistics
      PageManagerDummy->ResetStatistics();
      DummyTree->GetMetricEvaluator()->ResetStatistics();
      start = clock();
      for (j = 0; j < size; j++){
         // Set the queries variables and do the queries
         for (idx = 0; idx < NUMBEROFCENTERS; idx++){
            result[idx] = DummyTree->KAndRangeQuery(queryObjects[idx][j], radius, this->K);
         }//end for
         // Do the Union of results
         resultTemp = new myResult();
         finalResult = new myResult();
         resultTemp->Union(result[0], result[1]);
         finalResult->Union(resultTemp, result[2]);
         // clean
         for(idx = 0; idx < NUMBEROFCENTERS; idx++){
            delete result[idx];
         }//end for
         delete resultTemp;
         delete finalResult;
      }//end for
      end = clock();
      // Get the tests results. 
      rMeasureMultiDummy->setTotalTime(i, ((double )end-(double )start) / CLK_TCK);
      // is divided for queryObjects1 to get the everage
      rMeasureMultiDummy->setDiskAccess(i, (double )PageManagerDummy->GetReadCount() / (double )size);
      // is divided for queryObjects to get the everage
      rMeasureMultiDummy->setDistanceFunction(i,
         (double )DummyTree->GetMetricEvaluator()->GetDistanceCount() / (double )size);


      // Statisctics for Basic Slim-Tree
      // Reset the statistics for Slim
      PageManagerSlim->ResetStatistics();
      SlimTree->GetMetricEvaluator()->ResetStatistics();
      start = clock();
      for (j = 0; j < size; j++){
         // Set the queries variables and do the queries
         for (idx = 0; idx < NUMBEROFCENTERS; idx++){
            resultRange[idx] = SlimTree->RangeQuery(queryObjects[idx][j], radius);
            resultNearest[idx] = SlimTree->ListNearestQuery(queryObjects[idx][j], this->K);
            result[idx] = new myResult();
            result[idx]->Intersection(resultRange[idx], resultNearest[idx]);
         }//end for
         // Do the Union of results
         resultTemp = new myResult();
         finalResult = new myResult();
         resultTemp->Union(result[0], result[1]);
         finalResult->Union(resultTemp, result[2]);
         // clean
         for(idx = 0; idx < NUMBEROFCENTERS; idx++){
            delete result[idx];
            delete resultRange[idx];
            delete resultNearest[idx];
         }//end for
         delete resultTemp;
         delete finalResult;
      }//end for
      end = clock();
      // Get the tests results. 
      rMeasureBasicSlim->setTotalTime(i, ((double )end-(double )start) / CLK_TCK);
      // is divided for queryObjects1 to get the everage
      rMeasureBasicSlim->setDiskAccess(i, (double )PageManagerSlim->GetReadCount() / (double )size);
      // is divided for queryObjects to get the everage
      rMeasureBasicSlim->setDistanceFunction(i,
         (double )SlimTree->GetMetricEvaluator()->GetDistanceCount() / (double )size);

      // Statisctics for Basic Dummy
      // Reset the statistics for Slim
      PageManagerDummy->ResetStatistics();
      DummyTree->GetMetricEvaluator()->ResetStatistics();
      start = clock();
      for (j = 0; j < size; j++){
         // Set the queries variables and do the queries
         for (idx = 0; idx < NUMBEROFCENTERS; idx++){
            resultRange[idx] = DummyTree->RangeQuery(queryObjects[idx][j], radius);
            resultNearest[idx] = DummyTree->NearestQuery(queryObjects[idx][j], this->K);
            result[idx] = new myResult();
            result[idx]->Intersection(resultRange[idx], resultNearest[idx]);
         }//end for
         // Do the Union of results
         resultTemp = new myResult();
         finalResult = new myResult();
         resultTemp->Union(result[0], result[1]);
         finalResult->Union(resultTemp, result[2]);
         // clean
         for(idx = 0; idx < NUMBEROFCENTERS; idx++){
            delete result[idx];
            delete resultRange[idx];
            delete resultNearest[idx];
         }//end for
         delete resultTemp;
         delete finalResult;
      }//end for
      end = clock();
      // Get the tests results. 
      rMeasureBasicDummy->setTotalTime(i, ((double )end-(double )start) / CLK_TCK);
      // is divided for queryObjects to get the everage
      rMeasureBasicDummy->setDiskAccess(i, (double )PageManagerDummy->GetReadCount() / (double )size);
      // is divided for queryObjects to get the everage
      rMeasureBasicDummy->setDistanceFunction(i,
         (double )DummyTree->GetMetricEvaluator()->GetDistanceCount() / (double )size);

      cout << i << " ";
   }//end for

}//end TApp::PerformMultipleNearestAndRange

//------------------------------------------------------------------------------
void TApp::PerformSingleNearestAndRange(
      ResultMeasureDiscrete * rMeasureRangeSlim, ResultMeasureDiscrete * rMeasureRangeDummy,
      ResultMeasureDiscrete * rMeasureNearestSlim, ResultMeasureDiscrete * rMeasureNearestDummy,
      ResultMeasureDiscrete * rMeasureKAndNearestSlim, ResultMeasureDiscrete * rMeasureKAndNearestDummy,
      ResultMeasureDiscrete * rMeasureNearest_Inter_RangeSlim, ResultMeasureDiscrete * rMeasureNearest_Inter_RangeDummy){

   myResult * result,
            * resultRange, * resultNearest,
            * resultTemp, * finalResult;
   long numberOfObject = SlimTree->GetNumberOfObjects();
   clock_t start, end;
   unsigned int i, j, idx;
   stCount radius;
   stCount size = queryObjects[0].size();

   //For number of points (radius) that I want measure.
   for (i = 0; i < rMeasureRangeSlim->getSize(); i++){
      // Set the radius.
      radius = rMeasureRangeSlim->getK(i);

      // Statistics for Multiple Slim-Tree
      // Reset the statistics
      PageManagerSlim->ResetStatistics();
      SlimTree->GetMetricEvaluator()->ResetStatistics();
      start = clock();
      for (j = 0; j < size; j++){
         // Set the queries variables and do the queries
         result = SlimTree->RangeQuery(queryObjects[0][j], radius);
         delete result;
      }//end for
      end = clock();
      // Get the tests results.
      rMeasureRangeSlim->setTotalTime(i, ((double )end-(double )start) / CLK_TCK);
      // is divided for queryObjects1 to get the everage
      rMeasureRangeSlim->setDiskAccess(i, (double )PageManagerSlim->GetReadCount() / (double )size);
      // is divided for queryObjects to get the everage
      rMeasureRangeSlim->setDistanceFunction(i,
         (double )SlimTree->GetMetricEvaluator()->GetDistanceCount() / (double )size);

      // Statisctics for Multiple Dummy
      // Reset the statistics
      PageManagerDummy->ResetStatistics();
      DummyTree->GetMetricEvaluator()->ResetStatistics();
      start = clock();
      for (j = 0; j < size; j++){
         // Set the queries variables and do the queries
         result = DummyTree->RangeQuery(queryObjects[0][j], radius);
         delete result;
      }//end for
      end = clock();
      // Get the tests results.
      rMeasureRangeDummy->setTotalTime(i, ((double )end-(double )start) / CLK_TCK);
      // is divided for queryObjects1 to get the everage
      rMeasureRangeDummy->setDiskAccess(i, (double )PageManagerDummy->GetReadCount() / (double )size);
      // is divided for queryObjects to get the everage
      rMeasureRangeDummy->setDistanceFunction(i,
         (double )DummyTree->GetMetricEvaluator()->GetDistanceCount() / (double )size);

      // Statisctics for Basic Slim-Tree
      // Reset the statistics for Slim
      PageManagerSlim->ResetStatistics();
      SlimTree->GetMetricEvaluator()->ResetStatistics();
      start = clock();
      for (j = 0; j < size; j++){
         // Set the queries variables and do the queries
         result = SlimTree->ListNearestQuery(queryObjects[0][j], this->K);
         // Do the Union of results
         delete result;
      }//end for
      end = clock();
      // Get the tests results.
      rMeasureNearestSlim->setTotalTime(i, ((double )end-(double )start) / CLK_TCK);
      // is divided for queryObjects1 to get the everage
      rMeasureNearestSlim->setDiskAccess(i, (double )PageManagerSlim->GetReadCount() / (double )size);
      // is divided for queryObjects to get the everage
      rMeasureNearestSlim->setDistanceFunction(i,
         (double )SlimTree->GetMetricEvaluator()->GetDistanceCount() / (double )size);

      // Statisctics for Basic Dummy
      // Reset the statistics for Slim
      PageManagerDummy->ResetStatistics();
      DummyTree->GetMetricEvaluator()->ResetStatistics();
      start = clock();
      for (j = 0; j < size; j++){
         // Set the queries variables and do the queries
         result = DummyTree->NearestQuery(queryObjects[0][j], this->K);
         // clean
         delete result;
      }//end for
      end = clock();
      // Get the tests results.
      rMeasureNearestDummy->setTotalTime(i, ((double )end-(double )start) / CLK_TCK);
      // is divided for queryObjects to get the everage
      rMeasureNearestDummy->setDiskAccess(i, (double )PageManagerDummy->GetReadCount() / (double )size);
      // is divided for queryObjects to get the everage
      rMeasureNearestDummy->setDistanceFunction(i,
         (double )DummyTree->GetMetricEvaluator()->GetDistanceCount() / (double )size);

      // Statistics for Multiple Slim-Tree
      // Reset the statistics
      PageManagerSlim->ResetStatistics();
      SlimTree->GetMetricEvaluator()->ResetStatistics();
      start = clock();
      for (j = 0; j < size; j++){
         // Set the queries variables and do the queries
         result = SlimTree->KAndRangeQuery(queryObjects[0][j], radius, this->K);
         delete result;
      }//end for
      end = clock();
      // Get the tests results.
      rMeasureKAndNearestSlim->setTotalTime(i, ((double )end-(double )start) / CLK_TCK);
      // is divided for queryObjects1 to get the everage
      rMeasureKAndNearestSlim->setDiskAccess(i, (double )PageManagerSlim->GetReadCount() / (double )size);
      // is divided for queryObjects to get the everage
      rMeasureKAndNearestSlim->setDistanceFunction(i,
         (double )SlimTree->GetMetricEvaluator()->GetDistanceCount() / (double )size);

      // Statisctics for Multiple Dummy
      // Reset the statistics
      PageManagerDummy->ResetStatistics();
      DummyTree->GetMetricEvaluator()->ResetStatistics();
      start = clock();
      for (j = 0; j < size; j++){
         // Set the queries variables and do the queries
         result = DummyTree->KAndRangeQuery(queryObjects[0][j], radius, this->K);
         delete result;
      }//end for
      end = clock();
      // Get the tests results. 
      rMeasureKAndNearestDummy->setTotalTime(i, ((double )end-(double )start) / CLK_TCK);
      // is divided for queryObjects1 to get the everage
      rMeasureKAndNearestDummy->setDiskAccess(i, (double )PageManagerDummy->GetReadCount() / (double )size);
      // is divided for queryObjects to get the everage
      rMeasureKAndNearestDummy->setDistanceFunction(i,
         (double )DummyTree->GetMetricEvaluator()->GetDistanceCount() / (double )size);

      // Statisctics for Basic Slim-Tree
      // Reset the statistics for Slim
      PageManagerSlim->ResetStatistics();
      SlimTree->GetMetricEvaluator()->ResetStatistics();
      start = clock();
      for (j = 0; j < size; j++){
         // Set the queries variables and do the queries
         resultRange = SlimTree->RangeQuery(queryObjects[0][j], radius);
         resultNearest = SlimTree->ListNearestQuery(queryObjects[0][j], this->K);
         result = new myResult();
         result->Intersection(resultRange, resultNearest);
         delete result;
         delete resultRange;
         delete resultNearest;
      }//end for
      end = clock();
      // Get the tests results.
      rMeasureNearest_Inter_RangeSlim->setTotalTime(i, ((double )end-(double )start) / CLK_TCK);
      // is divided for queryObjects1 to get the everage
      rMeasureNearest_Inter_RangeSlim->setDiskAccess(i, (double )PageManagerSlim->GetReadCount() / (double )size);
      // is divided for queryObjects to get the everage
      rMeasureNearest_Inter_RangeSlim->setDistanceFunction(i,
         (double )SlimTree->GetMetricEvaluator()->GetDistanceCount() / (double )size);

      // Statisctics for Basic Dummy
      // Reset the statistics for Slim
      PageManagerDummy->ResetStatistics();
      DummyTree->GetMetricEvaluator()->ResetStatistics();
      start = clock();
      for (j = 0; j < size; j++){
         // Set the queries variables and do the queries
         resultRange = DummyTree->RangeQuery(queryObjects[0][j], radius);
         resultNearest = DummyTree->NearestQuery(queryObjects[0][j], this->K);
         result = new myResult();
         result->Intersection(resultRange, resultNearest);
         // clean
         delete result;
         delete resultRange;
         delete resultNearest;
      }//end for
      end = clock();
      // Get the tests results. 
      rMeasureNearest_Inter_RangeDummy->setTotalTime(i, ((double )end-(double )start) / CLK_TCK);
      // is divided for queryObjects to get the everage
      rMeasureNearest_Inter_RangeDummy->setDiskAccess(i, (double )PageManagerDummy->GetReadCount() / (double )size);
      // is divided for queryObjects to get the everage
      rMeasureNearest_Inter_RangeDummy->setDistanceFunction(i,
         (double )DummyTree->GetMetricEvaluator()->GetDistanceCount() / (double )size);

      cout << i << " ";
   }//end for

}//end TApp::PerformSingleNearestAndRange

//------------------------------------------------------------------------------
void TApp::WriteToFile(FILE * file, ResultMeasureDiscrete * rMeasure, int type){
   char * strTemp = new char[500];
   char * string = new char[50];
   unsigned int i;

   //write the statistics to files
   for(i = 0; i < rMeasure->getSize(); i++){
      fprintf(file, "%d", rMeasure->getK(i));
      strcpy(strTemp, "\t");
      fwrite(strTemp, strlen(strTemp), 1, file);
      if (type==1)
         fprintf(file, "%f", rMeasure->getDistanceFunction(i));
      else if (type==2)
         fprintf(file, "%f", rMeasure->getDiskAccess(i));
      else
         fprintf(file, "%f", rMeasure->getTotalTime(i));
      strcpy(strTemp, "\n");
      fwrite(strTemp, strlen(strTemp), 1, file);
   }//end for
   strcpy(strTemp, "end\n");
   fwrite(strTemp, strlen(strTemp), 1, file);

   delete strTemp;
   delete string;
}//end TApp::WriteToFile()

//------------------------------------------------------------------------------
void TApp::WriteHeader(FILE * file, char * type){
   char * strTemp = new char[500];
   char pageSize[10];

   itoa(this->PageSize, pageSize, 10);

   strcpy(strTemp,"set title \"Words Queries-");
   fwrite(strTemp, strlen(strTemp), 1, file);
   strcpy(strTemp,"page:");
   fwrite(strTemp, strlen(strTemp), 1, file);
   fwrite(pageSize, strlen(pageSize), 1, file);
   strcpy(strTemp,"\"\nset logscale y");
   strcat(strTemp,"\nset xlabel \"% dataset\"\n");
   fwrite(strTemp, strlen(strTemp), 1, file);
   strcpy(strTemp, type);
   fwrite(strTemp, strlen(strTemp), 1, file);

   strcpy(strTemp,"plot '-' title 'Generic Algorithms - Slim-Tree' with linespoints lt 1 lw 2 pt 1,");
   fwrite(strTemp, strlen(strTemp), 1, file);
   strcpy(strTemp," '-' title 'Generic Algorithm - Seq-Scan' with linespoints lt 2 lw 2 pt 2,");
   fwrite(strTemp, strlen(strTemp), 1, file);
   strcpy(strTemp," '-' title 'Basic Algorithms - Slim-Tree' with linespoints lt 3 lw 2 pt 3,");
   fwrite(strTemp, strlen(strTemp), 1, file);
   strcpy(strTemp," '-' title 'Basic Algorithms - Seq-Scan' with linespoints lt 4 lw 2 pt 4,");
   fwrite(strTemp, strlen(strTemp), 1, file);

   strcpy(strTemp," '-' title 'Range - Slim' with linespoints lt 5 lw 2 pt 5,");
   fwrite(strTemp, strlen(strTemp), 1, file);
   strcpy(strTemp," '-' title 'Range - Seq-Scan' with linespoints lt 6 lw 2 pt 6,");
   fwrite(strTemp, strlen(strTemp), 1, file);
   strcpy(strTemp," '-' title 'Nearest - Slim' with linespoints lt 7 lw 2 pt 7,");
   fwrite(strTemp, strlen(strTemp), 1, file);
   strcpy(strTemp," '-' title 'Nearest - Seq-Scan' with linespoints lt 8 lw 2 pt 8,");
   fwrite(strTemp, strlen(strTemp), 1, file);
   strcpy(strTemp," '-' title 'Single KAndRange - Slim' with linespoints lt 9 lw 2 pt 9,");
   fwrite(strTemp, strlen(strTemp), 1, file);
   strcpy(strTemp," '-' title 'Single KAndRange - Seq-Scan' with linespoints lt 10 lw 2 pt 10,");
   fwrite(strTemp, strlen(strTemp), 1, file);
   strcpy(strTemp," '-' title 'Single Nearest Intersection Range - Slim' with linespoints lt 11 lw 2 pt 11,");
   fwrite(strTemp, strlen(strTemp), 1, file);
   strcpy(strTemp," '-' title 'Single Nearest Intersection Range - Seq-Scan' with linespoints lt 12 lw 2 pt 12\n\n");
   fwrite(strTemp, strlen(strTemp), 1, file);
   delete strTemp;
}//end TApp::WriteHeader()
