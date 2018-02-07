//---------------------------------------------------------------------------
// app.cpp - Implementation of the application.
//
// To change the behavior of this application, comment and uncomment lines at
// TApp::Init() and TApp::Query().
//
// Authors: Marcos Rodrigues Vieira (mrvieira@icmc.usp.br)
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
   for (int i = 0; i < NUMBEROFTREES; i++){
      PageManagerDBM[i] = NULL;
      DBMTree[i] = NULL;
   }//end for
}//end TApp

//------------------------------------------------------------------------------
void TApp::Init(unsigned int pageSize, double maxDistance, double minOccup,
                unsigned int qtdRQ, char * prefix, int split,
                double fractalDimension){
   this->PageSize = pageSize;
   this->MaxDistance = maxDistance;
   this->MinOccup = minOccup;
   this->SizeRQ = qtdRQ;
   this->Prefix = prefix;
   this->Split = split;
   this->FractalDimension = fractalDimension;
   // To create it in disk
   CreateDiskPageManager();
   // Creates the tree
   CreateTree();
}//end TApp::Init

//------------------------------------------------------------------------------
void TApp::CreateTree(){
   // create for DBM-Tree
   for (int i = 0; i < NUMBEROFTREES; i++){
      DBMTree[i] = new myDBMTree(PageManagerDBM[i]);
   }//end for

   DBMTree[0]->SetSplitMethod(myDBMTree::smMIN_MAX);
   DBMTree[0]->SetMinOccupation(this->MinOccup);
   DBMTree[0]->SetChooseMethod(myDBMTree::cmMINDIST);
   DBMTree[0]->SetReInsert(true);

   DBMTree[1]->SetSplitMethod(myDBMTree::smMIN_SUM);
   DBMTree[1]->SetMinOccupation(this->MinOccup);
   DBMTree[1]->SetChooseMethod(myDBMTree::cmMINDIST);
   DBMTree[1]->SetReInsert(true);

   DBMTree[2]->SetSplitMethod(myDBMTree::smMIN_MAX);
   DBMTree[2]->SetChooseMethod(myDBMTree::cmMINDISTWITHCOVER);
   DBMTree[2]->SetMinOccupation(0.5);
   DBMTree[2]->SetReInsert(false);   

   DBMTree[3]->SetSplitMethod(myDBMTree::smMST_SLIM);
   DBMTree[3]->SetChooseMethod(myDBMTree::cmMINDISTWITHCOVER);
   DBMTree[3]->SetReInsert(false);
}//end TApp::CreateTree

//------------------------------------------------------------------------------
void TApp::CreateDiskPageManager(){
   char fileName[100];
   char pageSizeString[10];
   char minOccupString[10];
   char tmpStr[11];
   ifstream in;

   sprintf(pageSizeString, "%d", this->PageSize);
   sprintf(minOccupString, "%4.2f", this->MinOccup);

   //for DBM-Tree 0
   for (int i = 0; i < NUMBEROFTREES; i++){
      strcpy(fileName, this->Prefix.c_str());
      strcat(fileName, "DBMTree");
      sprintf(tmpStr, "%d", i);
      strcat(fileName, tmpStr);
      strcat(fileName, "_");
      strcat(fileName, pageSizeString);
      strcat(fileName, "_");
      strcat(fileName, minOccupString);
      strcat(fileName, ".dat");
      in.open(fileName, ios_base::in);
      // Try to open the file.
      if (in.is_open()){
         // Cannot open. Create it.
         PageManagerDBM[i] = new stPlainDiskPageManager(fileName);
         in.close();
      }else{
         // Opened.
         PageManagerDBM[i] = new stPlainDiskPageManager(fileName, this->PageSize);
      }//end if
   }//end for
}//end TApp::CreateDiskPageManager

//------------------------------------------------------------------------------
void TApp::Run(char * DataPath, char * DataQueryPath){
   for (int i = 0; i < NUMBEROFTREES; i++){
      if (DBMTree[i]){
         if (DBMTree[i]->GetNumberOfObjects() == 0){
            cout << "\n\nAdding objects in the DBMTree[" << i << "]";
            LoadTree(DataPath, DBMTree[i]);
            cout << "\nExecuting the Slim-Down Algorithm for " << i << ".";
            DBMTree[i]->DeleteUniqueNodes();
            DBMTree[i]->Optimize();
            DBMTree[i]->DeleteUniqueNodes();
            cout << " Done!";
         }//end if
      }//end if
   }//end for

   // Lets do the queries
   cout << "\nAdding query objects ";
   LoadVectorFromFile(DataQueryPath);

   // Lets do the queries
   cout << "\nGenerating the histogram";
   GenerateHistogram(DataPath);

   if (queryObjects.size() > 0){
      // Do 500 queries.
      PerformQueries();
   }//end if
   // Hold the screen.
   cout << "\n\nFinished the whole test!";
}//end TApp::Run

//------------------------------------------------------------------------------
void TApp::Done(){
   for (int i = 0; i < NUMBEROFTREES; i++){
      if (this->DBMTree[i] != NULL){
         delete this->DBMTree[i];
      }//end if
      if (this->PageManagerDBM[i] != NULL){
         delete this->PageManagerDBM[i];
      }//end if
   }//end for
   
   delete Histogram;

   // delete the vetor of queries.
   for (int i = 0; i < queryObjects.size(); i++){
      delete (queryObjects.at(i));
   }//end for
}//end TApp::Done

//------------------------------------------------------------------------------
void TApp::LoadTree(char * fileName, MetricTree * metricTree){
   ifstream in(fileName);
   double ValueX, ValueY;
   BYTE * ptr;
   int size;
   tMetricHistogramBin * bins;
   tMetricHistogram * metricHisto;
   int i;
   int w = 0;

   if (metricTree!=NULL){
      if (metricTree->GetNumberOfObjects() == 0){
         if (in.is_open()){
            cout << "\nLoading objects ";

            while (in >> size){
               bins = new tMetricHistogramBin[size];
               for (int idx = 0; idx < size; idx++){
                  in >> ValueX;
                  in >> ValueY;
                  bins[idx].Set(ValueX, ValueY);
               }//end for
               metricHisto = new tMetricHistogram(size, bins);
               this->AddToTree(metricHisto, metricTree);
               w++;
               if (w % 10 == 0){
                  cout << '.';
               }//end if
               delete metricHisto;
               delete[] bins;
            }//end while
            cout << " Added " << metricTree->GetNumberOfObjects() << " objects ";
            in.close();
         }else{
            cout << "\nProblem to open the file.";
         }//end if
      }//end if
   }else{
      cout << "\n Zero object added!!";
   }//end if
}//end TApp::LoadTree()

//------------------------------------------------------------------------------
void TApp::LoadVectorFromFile(char * fileName){
   ifstream in(fileName);
   int size;
   char tmp[200];
   double ValueX, ValueY;
   BYTE * ptr;
   tMetricHistogramBin * bins;

   // clear before using.
   queryObjects.clear();


   if (!in.is_open()){
      printf("Cannot open input query file!\n\n");
   }else{
      while (in >> size){
         bins = new tMetricHistogramBin[size];
         for (int idx = 0; idx < size; idx++){
            in >> ValueX;
            in >> ValueY;
            bins[idx].Set(ValueX, ValueY);
         }//end for
         queryObjects.insert(queryObjects.end(),
                                     new tMetricHistogram(size, bins));
         delete[] bins;
      }//end do
      cout << "Added " << queryObjects.size() << " objects \n";
      in.close();
   }//end else
}//end TApp::LoadVectorFromFile

//------------------------------------------------------------------------------
void TApp::GenerateHistogram(char * fileName){
   ifstream in(fileName);
   int size;
   char tmp[200];
   double ValueX, ValueY;
   BYTE * ptr;
   tMetricHistogramBin * bins;
   tMetricHistogram * metricHisto;
   tMetricHistogramEvaluator metricEvaluator;

   if (in.is_open()){
      cout << "\nLoading objects ";
      Histogram = new tHistogram(NUMBEROFBINS);
      while (in >> size){
         bins = new tMetricHistogramBin[size];
         for (int idx = 0; idx < size; idx++){
            in >> ValueX;
            in >> ValueY;
            bins[idx].Set(ValueX, ValueY);
         }//end for
         metricHisto = new tMetricHistogram(size, bins);
         Histogram->Add(metricHisto);
         delete metricHisto;
         delete[] bins;
      }//end while
      cout << " Added " << Histogram->GetNumberOfObjects() << " objects ";
      in.close();
      cout << " Ok.";
      Histogram->Build(&metricEvaluator);
   }else{
      cout << "\nProblem to open the file.";
   }//end if      
}//end TApp::GenerateHistogram

//------------------------------------------------------------------------------
void TApp::PerformQueries(){
   char pageSize[10];
   char numberOfDBMTree[10];
   string treeName;

   sprintf(pageSize, "%d", this->PageSize);
   //for the result of the tests
   ResultMeasure * rMeasureRQ = new ResultMeasure(true, this->SizeRQ, true);
   string fileName = this->Prefix + "RQDisc" + pageSize + ".plt";
   GNUPlot * gnuTest = new GNUPlot(fileName, "", "");

   gnuTest->SetTitle(GNUPlot::DISKACCESS, "metricHisto: Estimation of Disk Access");
   gnuTest->SetXLabel(GNUPlot::DISKACCESS, "% radius");
   gnuTest->SetYLabel(GNUPlot::DISKACCESS, "Avg Number of Disk Access");
   gnuTest->SetYLogScale(GNUPlot::DISKACCESS, false);

   for (int i = 0; i < NUMBEROFTREES; i++){
      if (DBMTree[i]){
         sprintf(numberOfDBMTree, "%d", i);

         cout << "\nStarting Statistics for Range Query with DBMTree-MinMax[" << i << "].... ";
         rMeasureRQ->SetStandardDeviaton(true);
         PerformRangeQuery(rMeasureRQ, DBMTree[i], PageManagerDBM[i]);
         treeName = string("DBMTree: Real") + string(numberOfDBMTree);
         gnuTest->AddMeasure(rMeasureRQ, treeName);
         rMeasureRQ->Reset();
         cout << " Ok\n";

         cout << "\nStarting Statistics for Ciaccia Estimate with DBMTree-MinMax[" << i << "].... ";
         rMeasureRQ->SetStandardDeviaton(false);
         CiacciaEstimateRQ(rMeasureRQ, DBMTree[i]);
         treeName = string("DBMTree: Ciaccia-Node Estimation") + string(numberOfDBMTree);
         gnuTest->AddMeasure(rMeasureRQ, treeName);
         rMeasureRQ->Reset();
         cout << " Ok\n";
      }//end if
   }//end if

   gnuTest->Write(GNUPlot::DISKACCESS);

   //cleaning...
   delete rMeasureRQ;
   delete gnuTest;
}//end TApp::PerformQueries

//------------------------------------------------------------------------------
void TApp::PerformRangeQuery(ResultMeasure * rMeasure, 
                             MetricTree * metricTree, 
                             stPageManager * pageManager){

   myResult * result;
   stDistance range;
   double * measures;
   double sum, mean, last;
   int i, j;
   unsigned int size;

   if (metricTree){
      size = queryObjects.size();
      measures = new double[size];
      //For number of points (range) that I want measure.
      for (i = 0; i < rMeasure->GetSize(); i++){

         range = rMeasure->GetK(i) * this->MaxDistance;

         //reset the statistics
         pageManager->ResetStatistics();
         metricTree->GetMetricEvaluator()->ResetStatistics();
         last = 0;

         for (j = 0; j < size; j++){
            result = metricTree->RangeQuery(queryObjects[j], range);
            measures[j] = (double )pageManager->GetReadCount() - last;
            last = (double )pageManager->GetReadCount();
            delete result;
         }//end for
         // is divided for queryObjects to get the everage
         mean = (double )pageManager->GetReadCount() / (double )size;
         rMeasure->SetDiskAccess(i, mean);

         sum = 0;
         for (j = 0; j < size; j++){
            sum += pow((measures[j] - mean),2); 
         }//end for
         rMeasure->SetSDDiskAccess(i, sqrt(sum / (double )size));

         cout << " " << rMeasure->GetK(i);
      }//end for
      delete[] measures;
   }//end if

}//end TApp::PerformRangeQuery

//------------------------------------------------------------------------------
void TApp::OptimalEstimateRQ(ResultMeasure * rMeasure, MetricTree * metricTree){
   stDistance range;
   int i, h;

   if (metricTree){
      //For number of points (range) that I want measure.
      for (i = 0; i < rMeasure->GetSize(); i++){
         // set the radius.
         range = rMeasure->GetK(i) * this->MaxDistance;
         // Call the estimation.
         rMeasure->SetDiskAccess(i,
               metricTree->GetEstimateDiskAccesses(range, FractalDimension, MaxDistance));

         cout << " " << rMeasure->GetK(i);
      }//end for
   }//end if

}//end TApp::OptimalEstimateRQ

//------------------------------------------------------------------------------
void TApp::FastOptimalEstimateRQ(ResultMeasure * rMeasure, MetricTree * metricTree){
   stDistance range;
   int i;

   if (metricTree){
      //For number of points (range) that I want measure.
      for (i = 0; i < rMeasure->GetSize(); i++){
         // set the radius.
         range = rMeasure->GetK(i) * this->MaxDistance;
         // Call the estimation.
         rMeasure->SetDiskAccess(i, metricTree->GetFastEstimateDiskAccesses(range,
                                    FractalDimension, MaxDistance));

         cout << " " << rMeasure->GetK(i);
      }//end for
   }//end if
}//end TApp::FastOptimalEstimateRQ

//------------------------------------------------------------------------------
void TApp::FatFactorEstimateRQ(ResultMeasure * rMeasure, MetricTree * metricTree){
   stTreeInfoResult * infoResult;
   double fatFactor;
   stDistance range;
   int i;

   if (metricTree){
      // Tree info.
      infoResult = metricTree->GetTreeInfo();
      // Get the fat-factor of this tree.
      fatFactor = infoResult->GetGlobalFatFactor();
      //For number of points (range) that I want measure.
      for (i = 0; i < rMeasure->GetSize(); i++){
         // set the radius.
         range = rMeasure->GetK(i) * this->MaxDistance;
         // Call the estimation.
         rMeasure->SetDiskAccess(i, metricTree->GetFatFactorFastEstimateDiskAccesses(
                                 fatFactor, range, FractalDimension, MaxDistance));

         cout << " " << rMeasure->GetK(i);
      }//end for
      // clean.
      delete infoResult;
   }//end if
}//end TApp::FatFactorEstimateRQ

//------------------------------------------------------------------------------
void TApp::CiacciaEstimateRQ(ResultMeasure * rMeasure, MetricTree * metricTree){
   stDistance range;
   int i;

   if (metricTree){
      //For number of points (range) that I want measure.
      for (i = 0; i < rMeasure->GetSize(); i++){
         // set the radius.
         range = rMeasure->GetK(i) * this->MaxDistance;
         // Call the estimation.
         rMeasure->SetDiskAccess(i, metricTree->GetCiacciaEstimateDiskAccesses(range,
                                    Histogram));

         cout << " " << rMeasure->GetK(i);
      }//end for
   }//end if
}//end TApp::CiacciaEstimateRQ

//------------------------------------------------------------------------------
void TApp::CiacciaLevelEstimateRQ(ResultMeasure * rMeasure, MetricTree * metricTree){
   stDistance range;
   stLevelDiskAccess * levelDiskAccess;
   int i;

   if (metricTree){
      // Compute the statistics for all levels.
      levelDiskAccess = new stLevelDiskAccess(metricTree->GetHeight() - 1);
      metricTree->CalculateLevelStatistics(levelDiskAccess);
      //For number of points (range) that I want measure.
      for (i = 0; i < rMeasure->GetSize(); i++){
         // set the radius.
         range = rMeasure->GetK(i) * this->MaxDistance;
         // Call the estimation.
         rMeasure->SetDiskAccess(i,
               metricTree->GetCiacciaLevelEstimateDiskAccesses(levelDiskAccess, range, Histogram));

         cout << " " << rMeasure->GetK(i);
      }//end for

      cout << "\n" << metricTree->GetNodeCount();

      for (i = 0; i < levelDiskAccess->GetHeight(); i++){
         cout << "\n" << i << " " << levelDiskAccess->GetNumberOfNodes(i) << " / " << levelDiskAccess->GetAvgRadius(i);
      }//end for

      delete levelDiskAccess;
   }//end if
}//end TApp::CiacciaLevelEstimateRQ

//------------------------------------------------------------------------------
void TApp::TestEstimateRQ(ResultMeasure * rMeasure, MetricTree * metricTree){
   stDistance range;
   tMetricHistogramEvaluator metricEvaluator;
   tHistogram ** histogram;
   unsigned int height;
   int i;

   if (metricTree){
      // Get the tree height.
      height = metricTree->GetHeight();
      histogram = new tHistogram * [height];
      // For each level...
      for (i = 0; i < height; i++) {
         histogram[i] = new tHistogram(NUMBEROFBINS);
      }//end for

      // Generate the histogram.
      metricTree->GenerateTestHistograms(histogram);

      // Build the distance matrix.
      cout << "\nBuild the distance matrix...";
      for (i = 0; i < height; i++) {
         histogram[i]->Build(&metricEvaluator);
         cout << " " << i;
      }//end for
      cout << " Done.\n";

      //For number of points (range) that I want measure.
      for (i = 0; i < rMeasure->GetSize(); i++){
         // set the radius.
         range = rMeasure->GetK(i) * this->MaxDistance;
         // Call the estimation.
         rMeasure->SetDiskAccess(i,
               metricTree->GetTestEstimateDiskAccesses(histogram, range));

         cout << " " << rMeasure->GetK(i);
      }//end for

      // Clean.
      for (i = 0; i < height; i++) {
         delete histogram[i];
      }//end for
      delete[] histogram;
   }//end if
}//end TApp::TestEstimateRQ

//------------------------------------------------------------------------------
void TApp::SampledLevelEstimateRQ(ResultMeasure * rMeasure, MetricTree * metricTree){
   stDistance range;
   stLevelDiskAccess * levelDiskAccess;
   tMetricHistogramEvaluator metricEvaluator;
   tHistogram ** histogram;
   unsigned int height;
   int i;

   if (metricTree){
      height = metricTree->GetHeight() - 1;
      // Compute the statistics for all levels.
      levelDiskAccess = new stLevelDiskAccess(height);
      metricTree->CalculateLevelStatistics(levelDiskAccess);

      histogram = new tHistogram * [height];
      // For each level...
      for (i = 0; i < height; i++) {
         histogram[i] = new tHistogram(NUMBEROFBINS);
      }//end for

      // Generate the histogram.
      metricTree->GenerateSampledLevelHistograms(histogram);

      // Build the distance matrix.
      cout << "Build the distance matrix...";
      for (i = 0; i < height; i++) {
         histogram[i]->Build(&metricEvaluator);
         cout << " " << i;
      }//end for

      //For number of points (range) that I want measure.
      for (i = 0; i < rMeasure->GetSize(); i++){
         // set the radius.
         range = rMeasure->GetK(i) * this->MaxDistance;
         // Call the estimation.
         rMeasure->SetDiskAccess(i,
               metricTree->GetSampledLevelEstimateDiskAccesses(levelDiskAccess, histogram, range));

         cout << " " << rMeasure->GetK(i);
      }//end for
      cout << "\n" << metricTree->GetNodeCount();

      for (i = 0; i < height; i++){
         cout << "\n" << i << " " << levelDiskAccess->GetNumberOfNodes(i) << " / " << levelDiskAccess->GetAvgRadius(i);
      }//end for

      // Clean.
      for (i = 0; i < height; i++) {
         delete histogram[i];
      }//end for
      delete[] histogram;
      delete levelDiskAccess;
   }//end if
}//end TApp::SampledLevelEstimateRQ
