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
//---------------------------------------------------------------------------
// Class TApp
//------------------------------------------------------------------------------
TApp::TApp(){
   PageManagerSlim = NULL;
   PageManagerDummy = NULL;
   MetricTreeSlim = NULL;
   MetricTreeDummy = NULL;
   MetricTreeSlim = 0;
}//end TApp

//------------------------------------------------------------------------------
void TApp::Init(unsigned int pageSize, char * prefix, unsigned int kValue,
                double rangeValue, int dataNumber){
   this->PageSize = pageSize;
   this->Prefix = prefix;
   this->KValue = kValue;
   this->RangeValue = rangeValue;
   this->DataNumber = dataNumber;
   // To create it in disk
   CreateDiskPageManager();
   // Creates the tree
   CreateTree();
}//end TApp::Init

//------------------------------------------------------------------------------
void TApp::CreateTree(){

   // create for Slim-tree
   MetricTreeSlim = new mySlimTree(PageManagerSlim);
   MetricTreeSlim->SetChooseMethod(mySlimTree::cmMINDIST);
   // create for Dummy-tree
   MetricTreeDummy = new myDummyTree(PageManagerDummy);
}//end TApp::CreateTree

//------------------------------------------------------------------------------
void TApp::CreateDiskPageManager(){
   char fileName[100];
   char pageSizeString[10];

   itoa(this->PageSize, pageSizeString, 10);

   //for Slim-tree
   strcpy(fileName, this->Prefix.c_str());
   strcat(fileName, "SlimTree");
   strcat(fileName, "_");
   strcat(fileName, pageSizeString);
   strcat(fileName, ".dat");
   //PageManagerSlim = new stPlainDiskPageManager(fileName, this->PageSize);
   PageManagerSlim = new stPlainDiskPageManager(fileName);

   //for Dummy-tree
   strcpy(fileName, this->Prefix.c_str());
   strcat(fileName, "Dummy");
   strcat(fileName, pageSizeString);
   strcat(fileName, ".dat");
   //PageManagerDummy = new stPlainDiskPageManager(fileName, this->PageSize);
   PageManagerDummy = new stPlainDiskPageManager(fileName);
}//end TApp::CreateDiskPageManager

//------------------------------------------------------------------------------
void TApp::Run(char * DataQueryPath){
   // Lets do the queries
   cout << "\nAdding query objects ";
   LoadVectorFromFile(DataQueryPath);
   // Do 500 queries.
   PerformQueries();
   // Hold the screen.
   cout << "\n\nFinished the whole test!";
}//end TApp::Run

//------------------------------------------------------------------------------
void TApp::Done(){
   unsigned int i;

   if (this->MetricTreeSlim != NULL){
      delete this->MetricTreeSlim;
   }//end if
   if (this->PageManagerSlim != NULL){
      delete this->PageManagerSlim;
   }//end if
   if (this->MetricTreeDummy != NULL){
      delete this->MetricTreeDummy;
   }//end if
   if (this->PageManagerDummy != NULL){
      delete this->PageManagerDummy;
   }//end if

   // delete the vetor of queries.
   for (i = 0; i < queryObjects.size(); i++){
      delete (queryObjects.at(i));
   }//end for
}//end TApp::Done

//------------------------------------------------------------------------------
void TApp::LoadTree(char * fileName, MetricTree * metricTree){
   ifstream in(fileName);
   int i;
   long w = 0;
   char temp[100];
   double values[MAXSIZE];
   myBasicArrayObject * basicArray;

   if (in.is_open()){
      cout << "\nLoading objects ";

      while (in >> values[0]){
         for (i = 1; i < MAXSIZE; i++){
            in >> values[i];
         }//end for
         basicArray = new myBasicArrayObject(MAXSIZE, values);
         // Add it in Slim-Tree.
         this->AddToTree(basicArray, metricTree);
         w++;
         if (w % 100 == 0){
            cout << '.';
         }//end if
         delete basicArray;
      }//end while
      cout << " Added " << metricTree->GetNumberOfObjects() << " objects ";
      in.close();
   }else{
      cout << "\nProblem to open the file.";
   }//end if
}//end TApp::LoadTree

//------------------------------------------------------------------------------
void TApp::LoadVectorFromFile(char * fileName){
   ifstream in;
   int i, contObj;
   double values[MAXSIZE];
   myBasicArrayObject * basicArray;
   int size;
   BYTE * ptr;

   in.open(fileName);
   if (!in.is_open()){
      printf("Cannot open input query file.\n");
   }else{
      cout << "\nLoading query objects ";
      queryObjects.clear();
      contObj = 0;
      while (in >> values[0]){
         for (i = 1; i < MAXSIZE; i++){
            in >> values[i];
         }//end for
         basicArray = new myBasicArrayObject(MAXSIZE, values);
         // Add it in vector.
         queryObjects.insert(queryObjects.end(), basicArray);
         contObj++;
      }//end while
      cout << " Added " << contObj << " query objects.";
      in.close();
  }//end else
}//end TApp::LoadVectorFromFile

//------------------------------------------------------------------------------
void TApp::PerformQueries(){

   char pause[] = "\npause -1";
   char pageSizeString[50];
   char fileName[50];
   char name[100];
   char strTmp[11];
   int idx;
   FILE * fileDistAND, * fileTimeAND, * fileDiskAND;
   FILE * fileDistOR, * fileTimeOR, * fileDiskOR;
   //for the result of the tests
   ResultMeasureDiscrete * rMeasureKAndRangeSlim = new ResultMeasureDiscrete(DataNumber);
   ResultMeasureDiscrete * rMeasureKInterRangeSlim = new ResultMeasureDiscrete(DataNumber);
   ResultMeasureDiscrete * rMeasureKOrRangeSlim = new ResultMeasureDiscrete(DataNumber);
   ResultMeasureDiscrete * rMeasureKUnionRangeSlim = new ResultMeasureDiscrete(DataNumber);

   ResultMeasureDiscrete * rMeasureKAndRangeSeqScan = new ResultMeasureDiscrete(DataNumber);
   ResultMeasureDiscrete * rMeasureKInterRangeSeqScan = new ResultMeasureDiscrete(DataNumber);
   ResultMeasureDiscrete * rMeasureKOrRangeSeqScan = new ResultMeasureDiscrete(DataNumber);
   ResultMeasureDiscrete * rMeasureKUnionRangeSeqScan = new ResultMeasureDiscrete(DataNumber);

   itoa(this->PageSize, pageSizeString, 10);

   //set the name and the header of the distance function file for RQ
   strcpy(fileName, this->Prefix.c_str());
   strcat(fileName, "DistAND");
   strcat(fileName, pageSizeString);
   strcat(fileName, ".plt");
   fileDistAND = fopen(fileName, "w");
   WriteHeader(fileDistAND, "set ylabel \"Número Médio de Cálculo de Distância\"\n", true);
   //set the name and the header of the distance function file for kNNQ
   strcpy(fileName, this->Prefix.c_str());
   strcat(fileName, "DistOR");
   strcat(fileName, pageSizeString);
   strcat(fileName, ".plt");
   fileDistOR = fopen(fileName, "w");
   WriteHeader(fileDistOR, "set ylabel \"Número Médio de Cálculo de Distância\"\n", false);

   //set the name and the header of the disk access file for RQ
   strcpy(fileName, this->Prefix.c_str());
   strcat(fileName, "DiskAND");
   strcat(fileName, pageSizeString);
   strcat(fileName, ".plt");
   fileDiskAND = fopen(fileName, "w");
   WriteHeader(fileDiskAND, "set ylabel \"Número Médio de Acesso a Disco\"\n", true);
   //set the name and the header of the disk access file for kNNQ
   strcpy(fileName, this->Prefix.c_str());
   strcat(fileName, "DiskOR");
   strcat(fileName, pageSizeString);
   strcat(fileName, ".plt");
   fileDiskOR = fopen(fileName, "w");
   WriteHeader(fileDiskOR, "set ylabel \"Número Médio de Acesso a Disco\"\n", false);

   //set the name and the header of the time file for RQ
   strcpy(fileName, this->Prefix.c_str());
   strcat(fileName,"TimeAND");
   strcat(fileName, pageSizeString);
   strcat(fileName, ".plt");
   fileTimeAND = fopen(fileName, "w");
   WriteHeader(fileTimeAND, "set ylabel \"Tempo Total (ms)\"\n", true);
   //set the name and the header of the time file for kNNQ
   strcpy(fileName, this->Prefix.c_str());
   strcat(fileName, "TimeOR");
   strcat(fileName, pageSizeString);
   strcat(fileName, ".plt");
   fileTimeOR = fopen(fileName, "w");
   WriteHeader(fileTimeOR, "set ylabel \"Tempo Total (ms)\"\n", false);

   for (idx = 0; idx < DataNumber; idx++){
      cout << "\n\nAdding objects in the SlimTree";
      //LoadTree(DataPath[idx], MetricTreeSlim);
      cout << "\n\nAdding objects in the SeqScan";
      //LoadTree(DataPath[idx], MetricTreeDummy);

      if (MetricTreeSlim){
         // queries for Slim-Tree
         cout << "\nStarting Statistics for KAndRange Query ... ";
         //PerformKAndRangeQuery(rMeasureKAndRangeSlim, rMeasureKAndRangeSeqScan, idx);
         cout << " Ok\n";

         cout << "\nStarting Statistics for Nearest AND Range Query ... ";
         //PerformKIntersectionRangeQuery(rMeasureKInterRangeSlim, rMeasureKInterRangeSeqScan, idx);
         cout << " Ok\n";

         cout << "\nStarting Statistics for KORRange Query ... ";
         //PerformKOrRangeQuery(rMeasureKOrRangeSlim, rMeasureKOrRangeSeqScan, idx);
         cout << " Ok\n";

         cout << "\nStarting Statistics for KUnionRange Query ... ";
         //PerformKUnionRangeQuery(rMeasureKUnionRangeSlim, rMeasureKUnionRangeSeqScan, idx);
         cout << " Ok\n";
      }//end if
   }//end for
   
   cout << "\n\nheight" << MetricTreeSlim->GetHeight();
   cout << "\nMaxOccup" << MetricTreeSlim->GetMaxOccupation();
   cout << "\nnodeCount" << MetricTreeSlim->GetNodeCount();
   cout << "\nnroObjs" << MetricTreeSlim->GetNumberOfObjects();

   cout << "\n\nmaxOccup" << MetricTreeDummy->GetMaxOccupation();
   cout << "\nnodeCount" << MetricTreeDummy->GetNodeCount();
   cout << "\nnroObjs" << MetricTreeDummy->GetNumberOfObjects();

   if (MetricTreeSlim){
      //write the statistics to files
      strcpy(name, "# SlimTree\n");
      //Distance Function
      WriteToFile(fileDistAND, name, rMeasureKAndRangeSlim, 1);
      WriteToFile(fileDistAND, name, rMeasureKInterRangeSlim, 1);
      WriteToFile(fileDistOR, name, rMeasureKOrRangeSlim, 1);
      WriteToFile(fileDistOR, name, rMeasureKUnionRangeSlim, 1);
      //Disk Access
      WriteToFile(fileDiskAND, name, rMeasureKAndRangeSlim, 2);
      WriteToFile(fileDiskAND, name, rMeasureKInterRangeSlim, 2);
      WriteToFile(fileDiskOR, name, rMeasureKOrRangeSlim, 2);
      WriteToFile(fileDiskOR, name, rMeasureKUnionRangeSlim, 2);
      //Total Time
      WriteToFile(fileTimeAND, name, rMeasureKAndRangeSlim, 3);
      WriteToFile(fileTimeAND, name, rMeasureKInterRangeSlim, 3);
      WriteToFile(fileTimeOR, name, rMeasureKOrRangeSlim, 3);
      WriteToFile(fileTimeOR, name, rMeasureKUnionRangeSlim, 3);

      strcpy(name, "# DummyTree\n");
      //Distance Function
      WriteToFile(fileDistAND, name, rMeasureKAndRangeSeqScan, 1);
      WriteToFile(fileDistAND, name, rMeasureKInterRangeSeqScan, 1);
      WriteToFile(fileDistOR, name, rMeasureKOrRangeSeqScan, 1);
      WriteToFile(fileDistOR, name, rMeasureKUnionRangeSeqScan, 1);
      //Disk Access
      WriteToFile(fileDiskAND, name, rMeasureKAndRangeSeqScan, 2);
      WriteToFile(fileDiskAND, name, rMeasureKInterRangeSeqScan, 2);
      WriteToFile(fileDiskOR, name, rMeasureKOrRangeSeqScan, 2);
      WriteToFile(fileDiskOR, name, rMeasureKUnionRangeSeqScan, 2);
      //Total Time
      WriteToFile(fileTimeAND, name, rMeasureKAndRangeSeqScan, 3);
      WriteToFile(fileTimeAND, name, rMeasureKInterRangeSeqScan, 3);
      WriteToFile(fileTimeOR, name, rMeasureKOrRangeSeqScan, 3);
      WriteToFile(fileTimeOR, name, rMeasureKUnionRangeSeqScan, 3);
   }//end if

   fwrite(pause, strlen(pause), 1, fileDiskAND);
   fwrite(pause, strlen(pause), 1, fileDistAND);
   fwrite(pause, strlen(pause), 1, fileTimeAND);
   fwrite(pause, strlen(pause), 1, fileDiskOR);
   fwrite(pause, strlen(pause), 1, fileDistOR);
   fwrite(pause, strlen(pause), 1, fileTimeOR);
   // close the files.
   fclose(fileDistAND);
   fclose(fileDistOR);
   fclose(fileDiskAND);
   fclose(fileDiskOR);
   fclose(fileTimeAND);
   fclose(fileTimeOR);
   //cleaning...

   if (MetricTreeSlim){
      delete rMeasureKAndRangeSlim;
      delete rMeasureKInterRangeSlim;
      delete rMeasureKOrRangeSlim;
      delete rMeasureKUnionRangeSlim;
   }//end if
   if (MetricTreeDummy){
      delete rMeasureKAndRangeSeqScan;
      delete rMeasureKInterRangeSeqScan;
      delete rMeasureKOrRangeSeqScan;
      delete rMeasureKUnionRangeSeqScan;
   }//end if
}//end TApp::PerformQuery

//------------------------------------------------------------------------------
void TApp::PerformKAndRangeQuery(ResultMeasureDiscrete * rMeasureSlim,
                                 ResultMeasureDiscrete * rMeasureSeqScan,
                                 int idx){

   myResult * result;
   stDistance radius;
   clock_t start, end;
   unsigned int i, j;
   int size = queryObjects.size();

   if (MetricTreeSlim){
      //reset the statistics
      PageManagerSlim->ResetStatistics();
      MetricTreeSlim->GetMetricEvaluator()->ResetStatistics();
      start = clock();
      for (j = 0; j < size; j++){
         result = MetricTreeSlim->KAndRangeQuery(queryObjects[j], this->RangeValue, this->KValue);
         delete result;
      }//end for
      end = clock();
      rMeasureSlim->setTotalTime(idx, ((double )end-(double )start) / CLK_TCK);
      // is divided for queryObjects to get the everage
      rMeasureSlim->setDiskAccess(idx, (double )PageManagerSlim->GetReadCount() / (double )size);
      // is divided for queryObjects to get the everage
      rMeasureSlim->setDistanceFunction(idx,
         (double )MetricTreeSlim->GetMetricEvaluator()->GetDistanceCount() / (double )size);

      cout << " st: " << idx;
   }//end if

   if (MetricTreeDummy){
      //reset the statistics
      PageManagerDummy->ResetStatistics();
      MetricTreeDummy->GetMetricEvaluator()->ResetStatistics();
      start = clock();
      for (j = 0; j < size; j++){
         result = MetricTreeDummy->KAndRangeQuery(queryObjects[j], this->RangeValue, this->KValue);
         delete result;
      }//end for
      end = clock();
      rMeasureSeqScan->setTotalTime(idx, ((double )end-(double )start) / CLK_TCK);
      // is divided for queryObjects to get the everage
      rMeasureSeqScan->setDiskAccess(idx, (double )PageManagerDummy->GetReadCount() / (double )size);
      // is divided for queryObjects to get the everage
      rMeasureSeqScan->setDistanceFunction(idx,
         (double )MetricTreeDummy->GetMetricEvaluator()->GetDistanceCount() / (double )size);

      cout << " sq: " << idx;
   }//end if

}//end TApp::PerformKAndRangeQuery

//------------------------------------------------------------------------------
void TApp::PerformKIntersectionRangeQuery(ResultMeasureDiscrete * rMeasureSlim,
                                          ResultMeasureDiscrete * rMeasureSeqScan,
                                          int idx){

   myResult * result1, * result2, * result;
   stDistance radius;
   clock_t start, end;
   unsigned int i, j;
   int size = queryObjects.size();

   if (MetricTreeSlim){
      //reset the statistics
      PageManagerSlim->ResetStatistics();
      MetricTreeSlim->GetMetricEvaluator()->ResetStatistics();
      start = clock();
      for (j = 0; j < size; j++){
         result1 = MetricTreeSlim->RangeQuery(queryObjects[j], this->RangeValue);
         result2 = MetricTreeSlim->NearestQuery(queryObjects[j], this->KValue);
         result = new myResult();
         result->Intersection(result1, result2);
         delete result1;
         delete result2;
         delete result;
      }//end for
      end = clock();
      rMeasureSlim->setTotalTime(idx, ((double )end-(double )start) / CLK_TCK);
      // is divided for queryObjects to get the everage
      rMeasureSlim->setDiskAccess(idx, (double )PageManagerSlim->GetReadCount() / (double )size);
      // is divided for queryObjects to get the everage
      rMeasureSlim->setDistanceFunction(idx,
         (double )MetricTreeSlim->GetMetricEvaluator()->GetDistanceCount() / (double )size);

      cout << " st: " << idx;
   }//end if

   if (MetricTreeDummy){
      //reset the statistics
      PageManagerDummy->ResetStatistics();
      MetricTreeDummy->GetMetricEvaluator()->ResetStatistics();
      start = clock();
      for (j = 0; j < size; j++){
         result1 = MetricTreeDummy->RangeQuery(queryObjects[j], this->RangeValue);
         result2 = MetricTreeDummy->NearestQuery(queryObjects[j], this->KValue);
         result = new myResult();
         result->Intersection(result1, result2);
         delete result1;
         delete result2;
         delete result;
      }//end for
      end = clock();
      rMeasureSeqScan->setTotalTime(idx, ((double )end-(double )start) / CLK_TCK);
      // is divided for queryObjects to get the everage
      rMeasureSeqScan->setDiskAccess(idx, (double )PageManagerDummy->GetReadCount() / (double )size);
      // is divided for queryObjects to get the everage
      rMeasureSeqScan->setDistanceFunction(idx,
         (double )MetricTreeDummy->GetMetricEvaluator()->GetDistanceCount() / (double )size);

      cout << " sq: " << idx;
   }//end if
}//end TApp::PerformKIntersectionRangeQuery

//------------------------------------------------------------------------------
void TApp::PerformKOrRangeQuery(ResultMeasureDiscrete * rMeasureSlim,
                                ResultMeasureDiscrete * rMeasureSeqScan,
                                int idx){

   myResult * result;
   clock_t start, end;
   unsigned int i, j;
   int size = queryObjects.size();

   if (MetricTreeSlim){
      //For number of points (radius) that I want measure.
      //reset the statistics for Slim
      PageManagerSlim->ResetStatistics();
      MetricTreeSlim->GetMetricEvaluator()->ResetStatistics();
      start = clock();
      for (j = 0; j < size; j++){
         result = MetricTreeSlim->KOrRangeQuery(queryObjects[j], this->RangeValue, this->KValue);
         delete result;
      }//end for
      end = clock();
      rMeasureSlim->setTotalTime(idx, ((double )end-(double )start) / CLK_TCK);
      // is divided for queryObjects to get the everage
      rMeasureSlim->setDiskAccess(idx, (double )PageManagerSlim->GetReadCount() / (double )size);
      // is divided for queryObjects to get the everage
      rMeasureSlim->setDistanceFunction(idx,
         (double )MetricTreeSlim->GetMetricEvaluator()->GetDistanceCount() / (double )size);

      cout << " st: " << idx;
   }//end if

   if (MetricTreeDummy){
      //For number of points (radius) that I want measure.
      //reset the statistics for Dummy
      PageManagerDummy->ResetStatistics();
      MetricTreeDummy->GetMetricEvaluator()->ResetStatistics();
      start = clock();
      for (j = 0; j < size; j++){
         result = MetricTreeDummy->KOrRangeQuery(queryObjects[j], this->RangeValue, this->KValue);
         delete result;
      }//end for
      end = clock();
      rMeasureSeqScan->setTotalTime(idx, ((double )end-(double )start) / CLK_TCK);
      // is divided for queryObjects to get the everage
      rMeasureSeqScan->setDiskAccess(idx, (double )PageManagerDummy->GetReadCount() / (double )size);
      // is divided for queryObjects to get the everage
      rMeasureSeqScan->setDistanceFunction(idx,
         (double )MetricTreeDummy->GetMetricEvaluator()->GetDistanceCount() / (double )size);

      cout << " sq: " << idx;
   }//end if
}//end TApp::PerformKOrRangeQuery

//------------------------------------------------------------------------------
void TApp::PerformKUnionRangeQuery(ResultMeasureDiscrete * rMeasureSlim,
                                   ResultMeasureDiscrete * rMeasureSeqScan,
                                   int idx){

   myResult * result1, * result2, * result;
   clock_t start, end;
   unsigned int i, j;
   int size = queryObjects.size();

   if (MetricTreeSlim){
      //For number of points (radius) that I want measure.
      //reset the statistics for Slim
      PageManagerSlim->ResetStatistics();
      MetricTreeSlim->GetMetricEvaluator()->ResetStatistics();
      start = clock();
      for (j = 0; j < size; j++){
         result1 = MetricTreeSlim->RangeQuery(queryObjects[j], this->RangeValue);
         result2 = MetricTreeSlim->NearestQuery(queryObjects[j], this->KValue);
         result = new myResult();
         result->Union(result1, result2);
         delete result1;
         delete result2;
         delete result;
      }//end for
      end = clock();
      rMeasureSlim->setTotalTime(idx, ((double )end-(double )start) / CLK_TCK);
      // is divided for queryObjects to get the everage
      rMeasureSlim->setDiskAccess(idx, (double )PageManagerSlim->GetReadCount() / (double )size);
      // is divided for queryObjects to get the everage
      rMeasureSlim->setDistanceFunction(idx,
         (double )MetricTreeSlim->GetMetricEvaluator()->GetDistanceCount() / (double )size);

      cout << " st: " << idx;
   }//end if

   if (MetricTreeDummy){
      //For number of points (radius) that I want measure.
      //reset the statistics for Dummy
      PageManagerDummy->ResetStatistics();
      MetricTreeDummy->GetMetricEvaluator()->ResetStatistics();
      start = clock();
      for (j = 0; j < size; j++){
         result1 = MetricTreeDummy->RangeQuery(queryObjects[j], this->RangeValue);
         result2 = MetricTreeDummy->NearestQuery(queryObjects[j], this->KValue);
         result = new myResult();
         result->Union(result1, result2);
         delete result1;
         delete result2;
         delete result;
      }//end for
      end = clock();
      rMeasureSeqScan->setTotalTime(idx, ((double )end-(double )start) / CLK_TCK);
      // is divided for queryObjects to get the everage
      rMeasureSeqScan->setDiskAccess(idx, (double )PageManagerDummy->GetReadCount() / (double )size);
      // is divided for queryObjects to get the everage
      rMeasureSeqScan->setDistanceFunction(idx,
         (double )MetricTreeDummy->GetMetricEvaluator()->GetDistanceCount() / (double )size);

      cout << " sq: " << idx;
   }//end if
}//end TApp::PerformKUnionRangeQuery

//------------------------------------------------------------------------------
void TApp::WriteToFile(FILE * file, char * algName, Measure * rMeasure, int type){
   char * strTemp = new char[500];
   char * string = new char[50];
   int i;

   fprintf(file, "%s", algName);
   //write the statistics to files
   for (i = 0; i < rMeasure->getSize(); i++){
      fprintf(file, "%d\t", i * 50 + 50);
      if (type==1){
         fprintf(file, "%f", rMeasure->getDistanceFunction(i));
      }else if (type==2){
         fprintf(file, "%f", rMeasure->getDiskAccess(i));
      }else{
         fprintf(file, "%ld", rMeasure->getTotalTime(i));
      }//end if
      strcpy(strTemp, "\n");
      fwrite(strTemp, strlen(strTemp), 1, file);
   }//end for
   strcpy(strTemp, "end\n");
   fwrite(strTemp, strlen(strTemp), 1, file);

   delete strTemp;
   delete string;
}//end TApp::WriteToFile

//------------------------------------------------------------------------------
void TApp::WriteHeader(FILE * file, char * type, bool and){
   char * strTemp = new char[500];
   char KNumber[20];
   char RangeNumber[20];

   itoa(this->KValue, KNumber, 10);
   itoa(this->RangeValue, RangeNumber, 10);

   strcpy(strTemp,"set title \"Escalabilidade de Synt30D: k=");
   fwrite(strTemp, strlen(strTemp), 1, file);
   fprintf(file, "%d", this->KValue);
   strcpy(strTemp," rq=");
   fwrite(strTemp, strlen(strTemp), 1, file);
   fprintf(file, "%f", this->RangeValue);

   strcpy(strTemp,"\"\nset xlabel \"Número de objetos indexados (x1000)\"\n");
   fwrite(strTemp, strlen(strTemp), 1, file);
   strcpy(strTemp, type);
   fwrite(strTemp, strlen(strTemp), 1, file);

   strcpy(strTemp, "plot ");
   fwrite(strTemp, strlen(strTemp), 1, file);
   if (and){
      strcpy(strTemp, "'-' title '(A) Slim-Tree: KAndRange' with linespoints lt 1 lw 2 pt 1,");
      fwrite(strTemp, strlen(strTemp), 1, file);
      strcpy(strTemp, "'-' title '(B) Slim-Tree: Nearest AND Range' with linespoints lt 6 lw 2 pt 3,");
      fwrite(strTemp, strlen(strTemp), 1, file);
      strcpy(strTemp, "'-' title '(C) Seq-Scan: KAndRange' with linespoints lt 3 lw 2 pt 2,");
      fwrite(strTemp, strlen(strTemp), 1, file);
      strcpy(strTemp, "'-' title '(D) Seq-Scan: Nearest AND Range' with linespoints lt 8 lw 2 pt 4");
      fwrite(strTemp, strlen(strTemp), 1, file);
   }else{
      strcpy(strTemp, "'-' title '(A) Slim-Tree: KOrRange' with linespoints lt 1 lw 2 pt 1,");
      fwrite(strTemp, strlen(strTemp), 1, file);
      strcpy(strTemp, "'-' title '(B) Slim-Tree: Nearest OR Range' with linespoints lt 6 lw 2 pt 3,");
      fwrite(strTemp, strlen(strTemp), 1, file);
      strcpy(strTemp, "'-' title '(C) Seq-Scan: KOrRange' with linespoints lt 3 lw 2 pt 2,");
      fwrite(strTemp, strlen(strTemp), 1, file);
      strcpy(strTemp, "'-' title '(D) Seq-Scan: Nearest OR Range' with linespoints lt 8 lw 2 pt 4");
      fwrite(strTemp, strlen(strTemp), 1, file);
   }//end if

   strcpy(strTemp, "\n\n");
   fwrite(strTemp, strlen(strTemp), 1, file);
   strcpy(strTemp,"####################\n");

   fwrite(strTemp, strlen(strTemp), 1, file);
   delete strTemp;
}//end TApp::WriteHeader
