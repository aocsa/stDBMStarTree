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
   PageManagerSlimTree = NULL;	
   SlimTree = NULL;	
   for (int i = 0; i < NUMBEROFTREES; i++){
      PageManagerDBM[i] = NULL;
      DBMTree[i] = NULL;
   }//end for
}//end TApp

//------------------------------------------------------------------------------
void TApp::Init(unsigned int pageSize, double minOccup,
                unsigned int k, double radius, char * prefix,
                int split, int dataNumber){
   this->PageSize = pageSize;
   this->MinOccup = minOccup;
   this->Radius = radius;
   this->K = k;
   this->Prefix = prefix;
   this->Split = split;
   this->DataNumber = dataNumber;
   DataPath = new char * [this->DataNumber];
   // To create it in disk
   CreateDiskPageManager();
   // Creates the tree
   CreateTree();
}//end TApp::Init

//------------------------------------------------------------------------------
void TApp::CreateTree(){
   // create for Slim-Tree
   SlimTree = new mySlimTree(PageManagerSlimTree);
   SlimTree->SetSplitMethod(mySlimTree::smMINMAX);
   SlimTree->SetChooseMethod(mySlimTree::cmMINDIST);

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
   DBMTree[3]->SetReInsert(false); /**/
}//end TApp::CreateTree

//------------------------------------------------------------------------------
void TApp::CreateDiskPageManager(){
   char fileName[100];
   char pageSizeString[10];
   char minOccupString[10];
   char tmpStr[11];

   sprintf(pageSizeString, "%d", this->PageSize);
   sprintf(minOccupString, "%4.2f", this->MinOccup);

   strcpy(fileName, this->Prefix.c_str());
   strcat(fileName, "SlimTree");
   strcat(fileName, "_");
   strcat(fileName, pageSizeString);
   strcat(fileName, ".dat");
   PageManagerSlimTree = new stPlainDiskPageManager(fileName, this->PageSize);

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
      PageManagerDBM[i] = new stPlainDiskPageManager(fileName, this->PageSize);
   }//end for
}//end TApp::CreateDiskPageManager

//------------------------------------------------------------------------------
void TApp::Run(char * DataQueryPath){
   // Lets do the queries
   cout << "\nAdding query objects ";
   LoadVectorFromFile(DataQueryPath);
   if (queryObjects.size() > 0){
      // Do 500 queries.
      PerformQueries();
   }//end if
   // Hold the screen.
   cout << "\n\nFinished the whole test!";
}//end TApp::Run

//------------------------------------------------------------------------------
void TApp::Done(){

   if (this->SlimTree != NULL){
      delete this->SlimTree;
   }//end if
   if (this->PageManagerSlimTree != NULL){
      delete this->PageManagerSlimTree;
   }//end if
   
   for (int i = 0; i < NUMBEROFTREES; i++){
      if (this->DBMTree[i] != NULL){
         delete this->DBMTree[i];
      }//end if
      if (this->PageManagerDBM[i] != NULL){
         delete this->PageManagerDBM[i];
      }//end if
   }//end for                         
   for (int i = 0; i < this->DataNumber; i++){
      delete DataPath[i];
   }//end for
   delete[] DataPath;

   // delete the vetor of queries.
   for (unsigned int i = 0; i < queryObjects.size(); i++){
      delete (queryObjects.at(i));
   }//end for
}//end TApp::Done

//------------------------------------------------------------------------------
void TApp::LoadTree(char * fileName, metricTree * metricTree){
   ifstream in(fileName);
   double values[MAXSIZE];
   myBasicArrayObject * basicArray;
   int i;
   int w = 0;

   if (metricTree!=NULL){
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
         cout << "Done!";
         in.close();
      }else{
         cout << "\nProblem to open the file.";
      }//end if
   }else{
      cout << "\n Zero object added!!";
   }//end if
}//end TApp::LoadTree

//------------------------------------------------------------------------------
void TApp::LoadVectorFromFile(char * fileName){
   ifstream in(fileName);
   double values[MAXSIZE];
   myBasicArrayObject * basicArray;
   int i, contObj;

   // clear before using.
   queryObjects.clear();

   if (in.is_open()){
      cout << "\nLoading query objects ";
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
      cout << " Added " << contObj << " query objects \n";
      in.close();
   }else{
      cout << "\nProblem to open the query file.";
      cout << "\n Zero object added!!\n";
   }//end if
}//end TApp::LoadVectorFromFile

//------------------------------------------------------------------------------
void TApp::PerformQueries(){
   char pageSizeString[10];
   char minOccupString[10];
   string fileNameDA, fileNameDF, fileNameTT;
   char name[100], line[100];
   char strTmp[11];

   //for the result of the tests
   ResultMeasureDiscrete * rMeasurekNNQDBM[NUMBEROFTREES];
   ResultMeasureDiscrete * rMeasureRQDBM[NUMBEROFTREES];
   ResultMeasureDiscrete * rMeasurekNNQSlimTree;
   ResultMeasureDiscrete * rMeasureRQSlimTree;

   for (int i = 0; i < NUMBEROFTREES; i++){
      rMeasurekNNQDBM[i] = new ResultMeasureDiscrete(1, false, this->DataNumber);
      rMeasureRQDBM[i] = new ResultMeasureDiscrete(1, false, this->DataNumber);
   }//end for   
   rMeasurekNNQSlimTree = new ResultMeasureDiscrete(1, false, this->DataNumber);
   rMeasureRQSlimTree = new ResultMeasureDiscrete(1, false, this->DataNumber);

   sprintf(pageSizeString, "%d", this->PageSize);
   sprintf(minOccupString, "%4.2f", this->MinOccup);

   fileNameDF = this->Prefix + "RQDist" + pageSizeString + "_" + minOccupString + ".plt";
   fileNameDA = this->Prefix + "RQDisc" + pageSizeString + "_" + minOccupString + ".plt";
   fileNameTT = this->Prefix + "RQTime" + pageSizeString + "_" + minOccupString + ".plt";
   GNUPlot * gnuTestRQ = new GNUPlot(fileNameDA, fileNameDF, fileNameTT);

   fileNameDF = this->Prefix + "kNNQDist" + pageSizeString + "_" + minOccupString + ".plt";
   fileNameDA = this->Prefix + "kNNQDisc" + pageSizeString + "_" + minOccupString + ".plt";
   fileNameTT = this->Prefix + "kNNQTime" + pageSizeString + "_" + minOccupString + ".plt";
   GNUPlot * gnuTestkNNQ = new GNUPlot(fileNameDA, fileNameDF, fileNameTT);

   gnuTestRQ->SetTitle(GNUPlot::DISTFUNCTION, "RQ: Vector-16D");
   gnuTestRQ->SetTitle(GNUPlot::DISKACCESS, "RQ: Vector-16D");
   gnuTestRQ->SetTitle(GNUPlot::TOTALTIME, "RQ: Vector-16D");
   gnuTestRQ->SetXLabel(GNUPlot::DISTFUNCTION, "dataset size");
   gnuTestRQ->SetXLabel(GNUPlot::DISKACCESS, "dataset size");
   gnuTestRQ->SetXLabel(GNUPlot::TOTALTIME, "dataset size");
   gnuTestRQ->SetLogScale(GNUPlot::DISTFUNCTION, false);
   gnuTestRQ->SetLogScale(GNUPlot::DISKACCESS, false);
   gnuTestRQ->SetLogScale(GNUPlot::TOTALTIME, false);
   gnuTestRQ->SetYLabel(GNUPlot::DISTFUNCTION, "Avg Number of Distance Calculation");
   gnuTestRQ->SetYLabel(GNUPlot::DISKACCESS, "Avg Number of Disk Access");
   gnuTestRQ->SetYLabel(GNUPlot::TOTALTIME, "Total Time (s)");

   gnuTestkNNQ->SetTitle(GNUPlot::DISTFUNCTION, "kNNQ: Cities");
   gnuTestkNNQ->SetTitle(GNUPlot::DISKACCESS, "kNNQ: Cities");
   gnuTestkNNQ->SetTitle(GNUPlot::TOTALTIME, "kNNQ: Cities");
   gnuTestkNNQ->SetXLabel(GNUPlot::DISTFUNCTION, "dataset size");
   gnuTestkNNQ->SetXLabel(GNUPlot::DISKACCESS, "dataset size");
   gnuTestkNNQ->SetXLabel(GNUPlot::TOTALTIME, "dataset size");
   gnuTestkNNQ->SetLogScale(GNUPlot::DISTFUNCTION, false);
   gnuTestkNNQ->SetLogScale(GNUPlot::DISKACCESS, false);
   gnuTestkNNQ->SetLogScale(GNUPlot::TOTALTIME, false);
   gnuTestkNNQ->SetYLabel(GNUPlot::DISTFUNCTION, "Avg Number of Distance Calculation");
   gnuTestkNNQ->SetYLabel(GNUPlot::DISKACCESS, "Avg Number of Disk Access");
   gnuTestkNNQ->SetYLabel(GNUPlot::TOTALTIME, "Total Time (s)");

   for (int idx = 0; idx < this->DataNumber; idx++){
      for (int i = 0; i < NUMBEROFTREES; i++){
         cout << "\n\nAdding objects in the DBMTree[" << i << "]";
         LoadTree(DataPath[idx], DBMTree[i]);
         cout << "\nDeleting Unique Nodes... ";
         DBMTree[i]->DeleteUniqueNodes();
         cout << "Done!";
         cout << "\nOptimizing... ";
         DBMTree[i]->Optimize();
         cout << "Done!";
         cout << "\nDeleting Unique Nodes... ";
         DBMTree[i]->DeleteUniqueNodes();
         cout << "Done!";
      }//end for
      cout << "\n\nAdding objects in the SlimTree";
      LoadTree(DataPath[idx], SlimTree);
      cout << "\nOptimizing... ";
      SlimTree->Optimize();
      cout << "Done!";

      for (int i = 0; i < NUMBEROFTREES; i++){
         if (DBMTree[i]){
            // queries for DBM-Tree
            cout << "\nStarting Statistics for Range Query with DBMTree-" << i << ".... ";
            PerformRangeQuery(rMeasureRQDBM[i], DBMTree[i], PageManagerDBM[i], idx);
            cout << " Ok\n";

            cout << "\nStarting Statistics for Nearest Query with DBMTree-" << i << ".... ";
            PerformNearestQuery(rMeasurekNNQDBM[i], DBMTree[i], PageManagerDBM[i], idx);
            cout << " Ok\n";
         }//end if
      }//end for
      
      if (SlimTree){
         // queries for DBM-Tree
         cout << "\nStarting Statistics for Range Query with SlimTree...";
         PerformRangeQuery(rMeasureRQSlimTree, SlimTree, PageManagerSlimTree, idx);
         cout << " Ok\n";

         cout << "\nStarting Statistics for Nearest Query with SlimTree.... ";
         PerformNearestQuery(rMeasurekNNQSlimTree, SlimTree, PageManagerSlimTree, idx);
         cout << " Ok\n";
      }//end if
   }//end for

   for (int i = 0; i < NUMBEROFTREES; i++){
      if (DBMTree[i]){
         //write the statistics to files
         //Distance Function
         strcpy(name, "DBMTree-");
         sprintf(strTmp, "%d", i);
         strcat(name, strTmp);
         strcpy(line, "linespoints lt ");
         sprintf(strTmp, "%d", i+1);
         strcat(line, strTmp);
         strcat(line, " lw 2 pt ");
         strcat(line, strTmp);
         // Add the result
         gnuTestRQ->AddMeasure(rMeasureRQDBM[i], name, line);
         gnuTestkNNQ->AddMeasure(rMeasurekNNQDBM[i], name, line);
         // Reset the statistics.
         rMeasureRQDBM[i]->Reset();
         rMeasurekNNQDBM[i]->Reset();
      }//end if
   }//end for
   if (SlimTree){
      //write the statistics to files
      //Distance Function
      strcpy(name, "SlimTree");
      strcpy(line, "linespoints lt 8 lw 2 pt 8");
      // Add the result
      gnuTestRQ->AddMeasure(rMeasureRQSlimTree, name, line);
      gnuTestkNNQ->AddMeasure(rMeasurekNNQSlimTree, name, line);
      // Reset the statistics.
      rMeasureRQSlimTree->Reset();
      rMeasurekNNQSlimTree->Reset();
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

   //cleaning...
   for (int i = 0; i < NUMBEROFTREES; i++){
      if (DBMTree[i]){
         delete rMeasurekNNQDBM[i];
         delete rMeasureRQDBM[i];
      }//end if
   }//end for
   delete rMeasurekNNQSlimTree;
   delete rMeasureRQSlimTree;
}//end TApp::PerformQuery

//------------------------------------------------------------------------------
void TApp::PerformRangeQuery(ResultMeasureDiscrete * rMeasure, metricTree * metricTree,
                             stPageManager * pageManager, int idx){

   myResult * result;
   stDistance radius;
   clock_t start, end;
   unsigned int i, j;
   unsigned int size;
   long sum;

   if (metricTree){
      size = queryObjects.size();
      //reset the statistics
      pageManager->ResetStatistics();
      metricTree->GetMetricEvaluator()->ResetStatistics();
      sum = 0;      
      start = clock();
      for (j=0; j < size; j++){
         result = metricTree->RangeQuery(queryObjects[j], this->Radius);
         sum += result->GetNumOfEntries();
         delete result;
      }//end for
      end = clock();
      cout << " sum: " << sum;
      rMeasure->SetTotalTime(idx, ((double )end-(double )start) / CLK_TCK);
      // is divided for queryObjects to get the everage
      rMeasure->SetDiskAccess(idx, (double )pageManager->GetReadCount() / (double )size);
      // is divided for queryObjects to get the everage
      rMeasure->SetDistanceFunction(idx,
         (double )metricTree->GetMetricEvaluator()->GetDistanceCount() / (double )size);

      cout << " " << idx;
   }//end if

}//end TApp::PerformRangeQuery

//------------------------------------------------------------------------------
void TApp::PerformNearestQuery(ResultMeasureDiscrete * rMeasure, metricTree * metricTree,
                               stPageManager * pageManager, int idx){

   myResult * result;
   clock_t start, end;
   unsigned int i, j;
   unsigned int size;

   if (metricTree){
      size = queryObjects.size();
      //For number of points (radius) that I want measure.
      //reset the statistics for Slim
      pageManager->ResetStatistics();
      metricTree->GetMetricEvaluator()->ResetStatistics();
      start = clock();
      for (j = 0; j < size; j++){
         result = metricTree->NearestQuery(queryObjects[j], this->K);
         delete result;
      }//end for
      end = clock();
      rMeasure->SetTotalTime(idx, ((double )end-(double )start) / CLK_TCK);
      // is divided for queryObjects to get the everage
      rMeasure->SetDiskAccess(idx, (double )pageManager->GetReadCount() / (double )size);
      // is divided for queryObjects to get the everage
      rMeasure->SetDistanceFunction(idx,
         (double )metricTree->GetMetricEvaluator()->GetDistanceCount() / (double )size);

      cout << " " << idx;
   }//end if

}//end TApp::PerformNearestQuery
