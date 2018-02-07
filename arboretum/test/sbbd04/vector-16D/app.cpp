//---------------------------------------------------------------------------
// app.cpp - Implementation of the application.
//
// To change the behavior of this application, comment and uncomment lines at
// TApp::Init() and TApp::Query().
//
// Authors: Marcos Rodrigues Vieira (mrvieira@icmc.usp.br)
//          Adriano Siqueira Arantes (arantes@icmc.usp.br)
// Copyright (c) 2003 GBDI-ICMC-USP
//---------------------------------------------------------------------------
#include <iostream>
#include <stdlib>
#include <math>
#pragma hdrstop
#include "app.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
// Class TApp
//------------------------------------------------------------------------------
void TApp::Init(unsigned int pageSize, unsigned int datasetSize,
                stDistance fractalDimension, char * difRadius,
                stDistance percRadius, unsigned int third, char * prefix){

   this->PageSize = pageSize;
   this->DatasetSize = datasetSize;
   this->FractalDimension = fractalDimension;
   this->Prefix = prefix;

   if (!strcmp(difRadius, "true")){
      this->DifRadius = true;
      this->PercRadius = (percRadius/100);
   }else{
      this->DifRadius = false;
      this->PercRadius = 0; 
   }//end if

   this->Third = third;
   // To create it in disk
   CreateDiskPageManager();
   // Creates the tree
   CreateTree();
}//end TApp::Init

//------------------------------------------------------------------------------
void TApp::Run(char * DataPath, char * DataQueryPath){

   // Lets load the tree with a lot values from the file.
   cout << "Adding objects in the MetricTreeSlim\n";
   LoadTree(DataPath);

   //load the query collection from the file
   cout << "Adding query objects ...\n";
   LoadVectorFromFile(DataQueryPath);

   // Lets do the 500 squeries
   PerformQueries();

   // Hold the screen.
   cout << "\nFinished the whole test!\n";
}//end TApp::Run

//------------------------------------------------------------------------------
void TApp::Done(){

   if (this->MetricTreeSlim != NULL){
      delete this->MetricTreeSlim;
   }//end if
   if (this->PageManagerSlim != NULL){
      delete this->PageManagerSlim;
   }//end if

   // delete the vetor of queries.
   for (int i = 0; i < queryPoints.size(); i++){
      delete (queryPoints.at(i));
   }//end for
}//end TApp::Done

//------------------------------------------------------------------------------
void TApp::CreateDiskPageManager(){
   char fileName[100];
   char pageSizeString[10];
   char tmpStr[11];

   itoa(this->PageSize, pageSizeString, 10);

   //for Slim-Tree MinMax
   strcpy(fileName, this->Prefix.c_str());
   strcat(fileName, "slimTree");
   strcat(fileName, pageSizeString);
   strcat(fileName, ".dat");
   PageManagerSlim = new stPlainDiskPageManager(fileName, this->PageSize);
}//end TApp::CreateDiskPageManager

//------------------------------------------------------------------------------
void TApp::CreateTree(){
   // create for Slim-Tree
   MetricTreeSlim = new mySlimTree(PageManagerSlim);
   MetricTreeSlim->SetSplitMethod(mySlimTree::smSPANNINGTREE);
   MetricTreeSlim->SetChooseMethod(mySlimTree::cmMINOCCUPANCY);
}//end TApp::CreateTree

//------------------------------------------------------------------------------
void TApp::LoadTree(char * fileName){
   ifstream in(fileName);
   double values[MAXSIZE];
   int i;
   int w = 0;

   if (in.is_open()){
      cout << "\nLoading objects ";

      while (in >> values[0]){
         for(i=1; i<MAXSIZE; i++){
            in >> values[i];
         }//end for
         this->AddToTree(values);
         w++;
         if (w % 100 == 0){
            cout << '.';
         }//end if
      }//end while
      cout << " Added " << MetricTreeSlim->GetNumberOfObjects() << " objects ";
      in.close();
   }else{
      cout << "\nProblem to open the file.";
   }//end if
}//end TApp::LoadTree

//------------------------------------------------------------------------------
void TApp::LoadVectorFromFile(char * fileName){
   ifstream in(fileName);
   double values[MAXSIZE];
   int i, contObj;

   if (in.is_open()){
      cout << "\nLoading query objects ";
      contObj = 0;
      while (in >> values[0]){
         for(i=1; i<MAXSIZE; i++){
            in >> values[i];
         }//end for
         queryPoints.insert(queryPoints.end(), new TPoint(values));
         contObj++;
      }//end while
      cout << " Added " << contObj << " query objects \n";
      in.close();
   }else{
      cout << "\nProblem to open the query file.";
      cout << "\n Zero object added!!\n";
   }//end if
}//end TApp::LoadVectorFromFile

//------------------------------------------------------------------------------
void TApp::PerformQueries(){

   char string[] = "\npause -1";
   char pageSizeString[10], percRadius[10], third[10];
   char fileName[50];
   char tmpString[50];
   int idx;

   FILE * fileDistFunc, * fileTime, * fileDiscAccess;

   //for the result of the tests
   ResultMeasure * rMeasureKOrRange = new ResultMeasure(this->DatasetSize);
   ResultMeasure * rMeasureSimpleKOrRange = new ResultMeasure(this->DatasetSize);

   //Coping the page size, percent radius and case b) (how is one third of queries?) to a string
   itoa(this->PageSize, pageSizeString, 10);
   itoa(ceil(this->PercRadius*100), percRadius, 10);
   itoa(this->Third, third, 10);

   //set the name and the header of the distance file
   strcpy(fileName, this->Prefix.c_str());
   strcat(fileName, "Dist");
   strcat(fileName, pageSizeString);
   strcat(fileName, "_R");
   strcat(fileName, percRadius);
   strcat(fileName, "_Q");
   strcat(fileName, third);
   strcat(fileName, ".plt");
   fileDistFunc = fopen(fileName, "w");
   WriteHeader(fileDistFunc, "set ylabel \"AVG of Distance Function\"\n");
   //set the name and the header of the disk file
   strcpy(fileName, this->Prefix.c_str());
   strcat(fileName, "Disk");
   strcat(fileName, pageSizeString);
   strcat(fileName, "_R");
   strcat(fileName, percRadius);
   strcat(fileName, "_Q");
   strcat(fileName, third);
   strcat(fileName, ".plt");
   fileDiscAccess = fopen(fileName, "w");
   WriteHeader(fileDiscAccess, "set ylabel \"AVG of Disk Access\"\n");
   //set the name and the header of the time file
   strcpy(fileName, this->Prefix.c_str());
   strcat(fileName, "Time");
   strcat(fileName, pageSizeString);
   strcat(fileName, "_R");
   strcat(fileName, percRadius);
   strcat(fileName, "_Q");
   strcat(fileName, third);
   strcat(fileName, ".plt");
   fileTime = fopen(fileName, "w");
   WriteHeader(fileTime, "set ylabel \"Total Time\"\n");

   cout << "\n\nStarting Statistics for all kOrRange... ";
   
   for (idx = 0; idx < this->DatasetSize; idx++){
     SetRadiusFromObjects(rMeasureKOrRange, idx);
     PerformSimpleKOrRangeQuery(rMeasureSimpleKOrRange, idx);
     PerformKOrRangeQuery(rMeasureKOrRange, idx);
     cout << " " << idx;
   }//end for
   cout << " Ok\n";

   // write the statistics for kOrRange to files
   WriteToFile(fileDistFunc, rMeasureKOrRange, 1);
   WriteToFile(fileDiscAccess, rMeasureKOrRange, 2);
   WriteToFile(fileTime, rMeasureKOrRange, 3);
   // write the statistics for SimplekOrRange to files
   WriteToFile(fileDistFunc, rMeasureSimpleKOrRange, 1);
   WriteToFile(fileDiscAccess, rMeasureSimpleKOrRange, 2);
   WriteToFile(fileTime, rMeasureSimpleKOrRange, 3);

   // Write the pause -1
   fwrite(string, strlen(string), 1, fileDistFunc);
   fwrite(string, strlen(string), 1, fileDiscAccess);
   fwrite(string, strlen(string), 1, fileTime);

   //close the files
   fclose(fileDistFunc);
   fclose(fileTime);
   fclose(fileDiscAccess);

   //Write log of errors for Simple kOrRange
   strcpy(fileName, "Log");
   strcat(fileName, this->Prefix.c_str());
   strcat(fileName, pageSizeString);
   strcat(fileName, "_R");
   strcat(fileName, percRadius);
   strcat(fileName, "_Q");
   strcat(fileName, third);
   WriteLog(rMeasureSimpleKOrRange, fileName);

   //cleaning...
   delete rMeasureKOrRange;
   delete rMeasureSimpleKOrRange;   
}//end TApp::PerformQuery

//------------------------------------------------------------------------------
void TApp::PerformSimpleKOrRangeQuery(ResultMeasure * rMeasure, int i){
   myResult * result;
   TPoint * sample;
   double * d;
   clock_t start, end;
   int k, j;

   //reset the statistics
   PageManagerSlim->ResetStatistics();
   MetricTreeSlim->GetMetricEvaluator()->ResetStatistics();
   MetricTreeSlim->ResetFractalStatistics();

   k = MetricTreeSlim->GetNumberOfObjects() * rMeasure->GetK(i);
   if (k == 0){
      k = 1;
   }//end if

   start = clock();
   for (j=0; j < queryPoints.size(); j++){
      d = queryPoints[j]->GetValues();
      sample = new TPoint(d);
      result = MetricTreeSlim->SimpleKOrRangeQuery(sample,
                                   this->FractalDimension, 
                                   radiusQueryPoints[j], k);
      delete[] d;
      delete result;
      delete sample;
   }//end for
   end = clock();

   //time in ms
   rMeasure->SetTotalTime(i, (double) end - (double) start);
   // is divided for queryPoints to get the everage
   rMeasure->SetDiscAccess(i, (double) PageManagerSlim->GetReadCount() / (double) queryPoints.size());
   // is divided for queryPoints to get the everage
   rMeasure->SetDistanceFunction(i,
      (double) MetricTreeSlim->GetMetricEvaluator()->GetDistanceCount() / (double) queryPoints.size());

   for(j=0; j<SIZERINGCALLS; j++){
      rMeasure->SetError(j, i, MetricTreeSlim->GetNumberOfRingCalls(j));
   }//end for
   rMeasure->SetGoodKick(i, MetricTreeSlim->GetNumberOfGoodKicks());

}//end TApp::PerformSimpleKOrRange

//------------------------------------------------------------------------------
void TApp::PerformKOrRangeQuery(ResultMeasure * rMeasure, int i){
   myResult * result;
   TPoint * sample;
   double * d;
   clock_t start, end;
   int k, j;

   PageManagerSlim->ResetStatistics();
   MetricTreeSlim->GetMetricEvaluator()->ResetStatistics();

   k = MetricTreeSlim->GetNumberOfObjects() * rMeasure->GetK(i);
   if (k == 0){
      k = 1;
   }//end if

   start = clock();
   for (j=0; j < queryPoints.size(); j++){
      d = queryPoints[j]->GetValues();
      sample = new TPoint(d);
      result = MetricTreeSlim->KOrRangeQuery(sample, radiusQueryPoints[j], k);
      delete[] d;
      delete result;
      delete sample;
   }//end for
   end = clock();

   // time in ms
   rMeasure->SetTotalTime(i, (double) end - (double) start);
   // is divided for queryPoints to get the everage
   rMeasure->SetDiscAccess(i, (double) PageManagerSlim->GetReadCount() / (double) queryPoints.size());
   // is divided for queryPoints to get the everage
   rMeasure->SetDistanceFunction(i,
      (double) MetricTreeSlim->GetMetricEvaluator()->GetDistanceCount() / (double) queryPoints.size());
      
}//end TApp::PerformKOrRangeQuery

//------------------------------------------------------------------------------
void TApp::WriteLog(ResultMeasure * result, char * name){

   char strTemp[500], string[10];
   FILE * fileStats;

   strcpy(strTemp, name);
   strcat(strTemp, ".plt");
   fileStats = fopen(strTemp, "w");
   //write the statistics to files
   //set the name and the header of the file for statistics
   strcpy(strTemp,"set title \"Statistics for Queries ");
   strcat(strTemp, name);
   fwrite(strTemp, strlen(strTemp), 1, fileStats);
   strcpy(strTemp,"\"\nset xlabel \"k\"\n");
   fwrite(strTemp, strlen(strTemp), 1, fileStats);
   strcpy(strTemp,"set logscale x\n");
   fwrite(strTemp, strlen(strTemp), 1, fileStats);
   strcpy(strTemp,"set ylabel \"# of Queries\"\n");
   fwrite(strTemp, strlen(strTemp), 1, fileStats);
   strcpy(strTemp,"plot '-' title '(A) Zero Ring Call' with linespoints 1,");
   strcat(strTemp," '-' title '(B) One Ring Call' with linespoints 2,");
   strcat(strTemp," '-' title '(C) Two Ring Call' with linespoints 3,");
   strcat(strTemp," '-' title '(D) Three Ring Call' with linespoints 4\n\n");
   fwrite(strTemp, strlen(strTemp), 1, fileStats);

   #ifdef __stFRACTALQUERY__
   for(int i=0; i < this->DatasetSize; i++){
      fprintf(fileStats, "%f\t%d\n", result->GetK(i), result->GetGoodKick(i));
   }//end for
   strcpy(strTemp, "end\n");
   fwrite(strTemp, strlen(strTemp), 1, fileStats);
   for(int j=0; j<3; j++){
      for(int i=0; i < this->DatasetSize; i++){
         fprintf(fileStats, "%f\t%d\n", result->GetK(i), result->GetError(j,i));
      }//end for
      strcpy(strTemp, "end\n");
      fwrite(strTemp, strlen(strTemp), 1, fileStats);
   }//end for
   #endif //__stFRACTALQUERY__

   strcpy(strTemp, "\n\npause -1");
   fwrite(strTemp, strlen(strTemp), 1, fileStats);
   fclose(fileStats);

}//end TApp::WriteLog

//------------------------------------------------------------------------------
void TApp::WriteToFile(FILE * file, ResultMeasure * rMeasure, int type){
   char strTemp[500];
   char string[50];

   //write the statistics to files
   for(int i=0; i < rMeasure->GetSize(); i++){
      fprintf(file, "%f", rMeasure->GetK(i));
      strcpy(strTemp, "\t");
      fwrite(strTemp, strlen(strTemp), 1, file);
      if(type==1)
         fprintf(file, "%f", rMeasure->GetDistanceFunction(i));
      else if(type==2)
         fprintf(file, "%f", rMeasure->GetDiscAccess(i));
      else
         fprintf(file, "%ld", rMeasure->GetTotalTime(i));
      strcpy(strTemp, "\n");
      fwrite(strTemp, strlen(strTemp), 1, file);
   }//end for
   strcpy(strTemp, "end\n");
   strcat(strTemp, "####################\n");
   fwrite(strTemp, strlen(strTemp), 1, file);
}//end TApp::WriteToFile

//------------------------------------------------------------------------------
void TApp::WriteHeader(FILE * file, char * type){
   char strTemp[500];
   char pageSize[10];
   char tmpString[10];

   itoa(this->PageSize, pageSize, 10);

   // Title
   strcpy(strTemp,"set title \"Vector2D - Disjuntive Complex Queries ");
   strcat(strTemp,"D= ");
   fwrite(strTemp, strlen(strTemp), 1, file);
   fprintf(file, "%f", this->FractalDimension);
   strcpy(strTemp,"  page=");
   fwrite(strTemp, strlen(strTemp), 1, file);
   fwrite(pageSize, strlen(pageSize), 1, file);
   // x and y label
   strcpy(strTemp,"\"\nset xlabel \"k\"\n");
   fwrite(strTemp, strlen(strTemp), 1, file);
   strcpy(strTemp, type);
   fwrite(strTemp, strlen(strTemp), 1, file);
   // Type
   strcpy(strTemp,"set logscale x\n");
   fwrite(strTemp, strlen(strTemp), 1, file);
   // Plots
   strcpy(strTemp,"plot '-' title '(A) kOrRange()' with linespoints 1, ");
   strcat(strTemp,"'-' title '(B) Simple kOrRange()' with linespoints 2\n\n");
   fwrite(strTemp, strlen(strTemp), 1, file);
   strcpy(strTemp,"####################\n");
   fwrite(strTemp, strlen(strTemp), 1, file);
}//end TApp::WriteHeader()

//------------------------------------------------------------------------------
void TApp::SetRadiusFromObjects(ResultMeasure * rMeasure, int i){
   myResult * result;
   TPoint * sample;
   double * d;
   long numberOfObjects;
   int j;
   double radius;
   unsigned int oneThird;

   // How many is One Third of queries?
   oneThird = (unsigned int) floor(queryPoints.size() / this->Third);
   //clear before insert new radium values
   radiusQueryPoints.clear();
   // set the number of objects.
   numberOfObjects = MetricTreeSlim->GetNumberOfObjects() * rMeasure->GetK(i);
   if (numberOfObjects < 2){
      numberOfObjects = 2;
   }//end if

   // perform the query.
   for (j=0; j < queryPoints.size(); j++){
      d = queryPoints[j]->GetValues();
      sample = new TPoint(d);
      result = MetricTreeSlim->NearestQuery(sample, numberOfObjects);
      // set the radius.
      radius = result->GetMaximumDistance();
      if (this->DifRadius){
         if (j < oneThird){
            radius = radius + (radius * this->PercRadius);
         }else{
            if (j >= oneThird && (j < (2*oneThird)) ){
               radius = radius - (radius * this->PercRadius);
            }//end if
         }//end if
      }//end if

      if (radius < 0){
         radius = 0;
      }//end if
      radiusQueryPoints.insert(radiusQueryPoints.end(), radius);
      delete[] d;
      delete result;
      delete sample;
   }//end for
}//end TApp::SetRadiusFromObjects
