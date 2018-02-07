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
   PageManagerMTree = NULL;
   PageManagerSlimDown = NULL;
   MTree = NULL;
   SlimDown = NULL;
   MTreeTime = 0;
   SlimDownTime = 0;

   for (int i = 0; i < NUMBEROFTREES; i++){
      PageManagerDBM[i] = NULL;
      DBMTree[i] = NULL;
      DBMTreeTime[i] = 0;
   }//end for
}//end TApp

//------------------------------------------------------------------------------
void TApp::Init(unsigned int pageSize, double maxDistance, double minOccup,
                unsigned int qtdK, unsigned int qtdRQ, char * prefix, int split){
   this->PageSize = pageSize;
   this->MaxDistance = maxDistance;
   this->MinOccup = minOccup;
   this->SizeKNNQ = qtdK;
   this->SizeRQ = qtdRQ;
   this->Prefix = prefix;
   this->Split = split;
   // To create it in disk
   CreateDiskPageManager();
   // Creates the tree
   CreateTree();
}//end TApp::Init

//------------------------------------------------------------------------------
void TApp::CreateTree(){
   SlimDown = new mySlimTree(PageManagerSlimDown);
   SlimDown->SetSplitMethod(mySlimTree::smMINMAX);
   SlimDown->SetChooseMethod(mySlimTree::cmMINDIST);

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

   DBMTree[4]->SetSplitMethod(myDBMTree::smMIN_MAX);
   DBMTree[4]->SetMinOccupation(this->MinOccup);
   DBMTree[4]->SetChooseMethod(myDBMTree::cmMINDIST);
   DBMTree[4]->SetReInsert(true);

   DBMTree[5]->SetSplitMethod(myDBMTree::smMIN_SUM);
   DBMTree[5]->SetMinOccupation(this->MinOccup);
   DBMTree[5]->SetChooseMethod(myDBMTree::cmMINDIST);
   DBMTree[5]->SetReInsert(true);

   DBMTree[6]->SetSplitMethod(myDBMTree::smMIN_MAX);
   DBMTree[6]->SetChooseMethod(myDBMTree::cmMINDISTWITHCOVER);
   DBMTree[6]->SetMinOccupation(0.5);
   DBMTree[6]->SetReInsert(false);

   DBMTree[7]->SetSplitMethod(myDBMTree::smMST_SLIM);
   DBMTree[7]->SetChooseMethod(myDBMTree::cmMINDISTWITHCOVER);
   DBMTree[7]->SetReInsert(false);
}//end TApp::CreateTree

//------------------------------------------------------------------------------
void TApp::CreateDiskPageManager(){
   char fileName[100];
   char pageSizeString[10];
   char minOccupString[10];
   char tmpStr[11];

   sprintf(pageSizeString, "%d", this->PageSize);
   sprintf(minOccupString, "%4.2f", this->MinOccup);

   //for Slim-Tree MinMax
   strcpy(fileName, this->Prefix.c_str());
   strcat(fileName, "slimTreeMinMax");
   strcat(fileName, pageSizeString);
   strcat(fileName, "_");
   strcat(fileName, minOccupString);
   strcat(fileName, ".dat");
   PageManagerMTree = new stPlainDiskPageManager(fileName, this->PageSize);
   //for Slim-Tree SlimDown
   strcpy(fileName, this->Prefix.c_str());
   strcat(fileName, "slimTreeSlimDown");
   strcat(fileName, pageSizeString);
   strcat(fileName, "_");
   strcat(fileName, minOccupString);
   strcat(fileName, ".dat");
   PageManagerSlimDown = new stPlainDiskPageManager(fileName, this->PageSize);

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
void TApp::Run(char * DataPath, char * DataQueryPath){
   // Lets load the tree with a lot values from the file.
   if (MTree){
      cout << "\n\nAdding objects in the MTree";
      LoadTree(DataPath, MTree, &MTreeTime);
      cout << " Done!";
   }//end if

   if (SlimDown){
      cout << "\n\nAdding objects in the SlimDown";
      LoadTree(DataPath, SlimDown, &SlimDownTime);
      cout << "\nExecuting the Slim-Down Algorithm.";
      SlimDown->Optimize();
      cout << " Done!";
   }//end if

   for (int i = 0; i < NUMBEROFTREES; i++){
      cout << "\n\nAdding objects in the DBMTree[" << i << "]";
      LoadTree(DataPath, DBMTree[i], &DBMTreeTime[i]);
   }//end for

   for (int i = 4; i < NUMBEROFTREES; i++){
      if (DBMTree[i]){
         cout << "\nExecuting the Slim-Down Algorithm for " << i << ".";
         DBMTree[i]->DeleteUniqueNodes();
         cout << " Done1!";
         DBMTree[i]->Optimize();
         cout << " Done2!";
         DBMTree[i]->DeleteUniqueNodes(); /**/
         cout << " Done3!";
         //cout << "\nConsistency: " << DBMTree[i]->Consistency();
      }//end if
   }//end for
   // Write information of trees.
   //WriteStats();

   // Lets do the queries
   cout << "\nAdding query objects ";
   LoadVectorFromFile(DataQueryPath);

   if (this->MaxDistance <= 0){
      cout << "\nCalculating the maximum distance ...\n";
      if (SlimDown){
         this->MaxDistance = SlimDown->GetGreaterDistance();
      }//end if
      cout << MaxDistance;
      cout << " Ok\n";
   }//end if
   if (queryObjects.size() > 0){
      // Do 500 queries.
      PerformQueries();
   }//end if
   // Hold the screen.
   cout << "\n\nFinished the whole test!";
}//end TApp::Run

//------------------------------------------------------------------------------
void TApp::WriteStats(){
   char pageSizeString[10];
   char minOccupString[10];
   char fileName[50];
   char strTemp[500];
   char tmpStr[11];
   FILE * fileStats;

   sprintf(pageSizeString, "%d", this->PageSize);
   sprintf(minOccupString, "%4.2f", this->MinOccup);

   // set the name of this file
   strcpy(fileName, this->Prefix.c_str());
   strcat(fileName, "Stats");
   strcat(fileName, pageSizeString);
   strcat(fileName, "_");
   strcat(fileName, minOccupString);
   strcat(fileName, ".txt");

   if ((fileStats = fopen(fileName, "w")) == NULL){
      printf("\nCannot open statistics file.");
   }else{
      cout << "\nWriting statistics for trees";
      // Write statistics.
      WriteStat(fileStats, "MTree", MTree, this->MTreeTime);
      cout << "\nDone for MTree.";
      WriteStat(fileStats, "SlimDown", SlimDown, this->SlimDownTime);
      cout << "\nDone for SlimDown.";
      for (int i = 0; i < NUMBEROFTREES; i++){
         strcpy(strTemp, "DBMTree[");
         sprintf(tmpStr, "%d", i);
         strcat(fileName, tmpStr);
         strcat(strTemp, "]");
         WriteStat(fileStats, strTemp, DBMTree[i], this->DBMTreeTime[i]);
         cout << "\nDone for DBMTree[" << i << "].";
      }//end for
      // close the file
      fclose(fileStats);
   }//end if

}//end WriteStats

//------------------------------------------------------------------------------
void TApp::WriteStat(FILE * file, char * treeName, MetricTree * metricTree, clock_t time){
   char strTemp[500];
   myDBMTree * metricTreeDB;

   if (metricTree){
      // Get the information about the tree.
      stTreeInfoResult * infoResult = metricTree->GetTreeInfo();
      strcpy(strTemp, "\n\n");
      strcat(strTemp, treeName);
      fwrite(strTemp, strlen(strTemp), 1, file);
      strcpy(strTemp, "\n\tHeight: ");
      fwrite(strTemp, strlen(strTemp), 1, file);
      fprintf(file, "%d", infoResult->GetHeight());
      strcpy(strTemp, "\n\tObjs Count: ");
      fwrite(strTemp, strlen(strTemp), 1, file);
      fprintf(file, "%d", infoResult->GetObjectCount());
      strcpy(strTemp, "\n\tRadius Tree: ");
      fwrite(strTemp, strlen(strTemp), 1, file);
      if (metricTreeDB = dynamic_cast <myDBMTree *> (metricTree)){
         metricTreeDB = (myDBMTree *)metricTree;
         fprintf(file, "%f", metricTreeDB->GetTreeRadius());
         strcpy(strTemp, "\n\tMaximum Entries per Node: ");
         fwrite(strTemp, strlen(strTemp), 1, file);
         fprintf(file, "%d", metricTreeDB->GetMaxOccupation());
         strcpy(strTemp, "\n\tMinimum Occupation per Node: ");
         fwrite(strTemp, strlen(strTemp), 1, file);
         fprintf(file, "%f", metricTree->GetMinOccupation());
      }else{
         fprintf(file, "-1");
         strcpy(strTemp, "\n\tMaximum Entries per Node: ");
         fwrite(strTemp, strlen(strTemp), 1, file);
         fprintf(file, "-1");
         strcpy(strTemp, "\n\tMinimum Occupation per Node: ");
         fwrite(strTemp, strlen(strTemp), 1, file);
         fprintf(file, "%f", metricTree->GetMinOccupation());
      }//end if
      strcpy(strTemp, "\n\tPage Count: ");
      fwrite(strTemp, strlen(strTemp), 1, file);
      fprintf(file, "%d", metricTree->GetNodeCount());
      strcpy(strTemp, "\n\tPage size: ");
      fwrite(strTemp, strlen(strTemp), 1, file);
      fprintf(file, "%d", metricTree->GetPageManager()->GetMinimumPageSize());
      strcpy(strTemp, "\n\tMean Object Size: ");
      fwrite(strTemp, strlen(strTemp), 1, file);
      fprintf(file, "%f", infoResult->GetMeanObjectSize());

      strcpy(strTemp, "\n\tTotal Time Construction: ");
      fwrite(strTemp, strlen(strTemp), 1, file);
      fprintf(file, "%ld", time);

      delete infoResult;
   }//end if
}//end WriteStat

//------------------------------------------------------------------------------
void TApp::Done(){

   if (this->MTree != NULL){
      delete this->MTree;
   }//end if
   if (this->SlimDown != NULL){
      delete this->SlimDown;
   }//end if

   if (this->PageManagerMTree != NULL){
      delete this->PageManagerMTree;
   }//end if
   if (this->PageManagerSlimDown != NULL){
      delete this->PageManagerSlimDown;
   }//end if

   for (int i = 0; i < NUMBEROFTREES; i++){
      if (this->DBMTree[i] != NULL){
         delete this->DBMTree[i];
      }//end if
      if (this->PageManagerDBM[i] != NULL){
         delete this->PageManagerDBM[i];
      }//end if
   }//end for                         

   // delete the vetor of queries.
   for (unsigned int i = 0; i < queryObjects.size(); i++){
      delete (queryObjects.at(i));
   }//end for
}//end TApp::Done

//------------------------------------------------------------------------------
void TApp::LoadTree(char * fileName, MetricTree * metricTree, clock_t * totalTime){
   ifstream in(fileName);
   double values[MAXSIZE];
   myBasicArrayObject * basicArray;
   clock_t totalTimeTemp = 0;
   clock_t start, end;
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
            start = clock();
            this->AddToTree(basicArray, metricTree);
            end = clock();
            w++;
            if (w % 100 == 0){
               cout << '.';
            }//end if
            totalTimeTemp += end-start;
            delete basicArray;
         }//end while
         cout << " Added " << metricTree->GetNumberOfObjects() << " objects ";
         *totalTime = totalTimeTemp;
         in.close();
      }else{
         cout << "\nProblem to open the file.";
      }//end if
   }else{
      cout << "\n Zero object added!!";
   }//end if
}//end TApp::LoadTree()

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
         basicArray = new myBasicArrayObject(MAXSIZE, values);
         // Add it in vector.
         queryObjects.insert(queryObjects.end(), basicArray);
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
   char minOccupString[10];
   string fileNameDA, fileNameDF, fileNameTT;
   char name[100], line[100];
   char strTmp[11];

   //for the result of the tests
   ResultMeasureDiscrete * rMeasurekNNQ = new ResultMeasureDiscrete(2, false, this->SizeKNNQ);
   ResultMeasure * rMeasureRQ = new ResultMeasure(false, this->SizeRQ, true, 3);

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

   gnuTestRQ->SetTitle(GNUPlot::DISTFUNCTION, "RQ: Synt16D");
   gnuTestRQ->SetTitle(GNUPlot::DISKACCESS, "RQ: Synt16D");
   gnuTestRQ->SetTitle(GNUPlot::TOTALTIME, "RQ: Synt16D");
   gnuTestRQ->SetXLabel(GNUPlot::DISTFUNCTION, "% radius");
   gnuTestRQ->SetXLabel(GNUPlot::DISKACCESS, "% radius");
   gnuTestRQ->SetXLabel(GNUPlot::TOTALTIME, "% radius");
   gnuTestRQ->SetYLogScale(GNUPlot::DISTFUNCTION, false);
   gnuTestRQ->SetYLogScale(GNUPlot::DISKACCESS, false);
   gnuTestRQ->SetYLogScale(GNUPlot::TOTALTIME, false);
   gnuTestRQ->SetYLabel(GNUPlot::DISTFUNCTION, "Avg Number of Distance Calculation");
   gnuTestRQ->SetYLabel(GNUPlot::DISKACCESS, "Avg Number of Disk Access");
   gnuTestRQ->SetYLabel(GNUPlot::TOTALTIME, "Total Time (s)");

   gnuTestkNNQ->SetTitle(GNUPlot::DISTFUNCTION, "kNNQ: Synt16D");
   gnuTestkNNQ->SetTitle(GNUPlot::DISKACCESS, "kNNQ: Synt16D");
   gnuTestkNNQ->SetTitle(GNUPlot::TOTALTIME, "kNNQ: Synt16D");
   gnuTestkNNQ->SetXLabel(GNUPlot::DISTFUNCTION, "k");
   gnuTestkNNQ->SetXLabel(GNUPlot::DISKACCESS, "k");
   gnuTestkNNQ->SetXLabel(GNUPlot::TOTALTIME, "k");
   gnuTestkNNQ->SetLogScale(GNUPlot::DISTFUNCTION, false);
   gnuTestkNNQ->SetLogScale(GNUPlot::DISKACCESS, false);
   gnuTestkNNQ->SetLogScale(GNUPlot::TOTALTIME, false);
   gnuTestkNNQ->SetYLabel(GNUPlot::DISTFUNCTION, "Avg Number of Distance Calculation");
   gnuTestkNNQ->SetYLabel(GNUPlot::DISKACCESS, "Avg Number of Disk Access");
   gnuTestkNNQ->SetYLabel(GNUPlot::TOTALTIME, "Total Time (s)");

   if (MTree){
      cout << "\nStarting Statistics for Range Query with MTree-MinMax.... ";
      PerformRangeQuery(rMeasureRQ, MTree, PageManagerMTree);
      cout << " Ok\n";

      cout << "\nStarting Statistics for Nearest Query with MTree-MinMax.... ";
      PerformNearestQuery(rMeasurekNNQ, MTree, PageManagerMTree);
      cout << " Ok\n";

      // Add the result
      gnuTestRQ->AddMeasure(rMeasureRQ, "MTree-Minmax", "linespoints lt 6 lw 2 pt 5");
      gnuTestkNNQ->AddMeasure(rMeasurekNNQ, "MTree-Minmax", "linespoints lt 6 lw 2 pt 5");
      // Reset the statistics.
      rMeasureRQ->Reset();
      rMeasurekNNQ->Reset();
   }//end if

   if (SlimDown){

      cout << "\nStarting Statistics for Range Query with SlimTree-SlimDown.... ";
      PerformRangeQuery(rMeasureRQ, SlimDown, PageManagerSlimDown);
      cout << " Ok\n";

      cout << "\nStarting Statistics for Nearest Query with SlimTree-SlimDown.... ";
      PerformNearestQuery(rMeasurekNNQ, SlimDown, PageManagerSlimDown);
      cout << " Ok\n";

      // Add the result
      gnuTestRQ->AddMeasure(rMeasureRQ, "SlimTree-MinMax-SlimDown", "linespoints lt 8 lw 2 pt 11");
      gnuTestkNNQ->AddMeasure(rMeasurekNNQ, "SlimTree-MinMax-SlimDown", "linespoints lt 8 lw 2 pt 11");
      // Reset the statistics.
      rMeasureRQ->Reset();
      rMeasurekNNQ->Reset();
   }//end if

   for (int i = 0; i < NUMBEROFTREES; i++){
      if (DBMTree[i]){
         // queries for DBM-Tree
         cout << "\nStarting Statistics for Range Query with DBMTree-" << i << ".... ";
         PerformRangeQuery(rMeasureRQ, DBMTree[i], PageManagerDBM[i]);
         cout << " Ok\n";

         cout << "\nStarting Statistics for Nearest Query with DBMTree-" << i << ".... ";
         PerformNearestQuery(rMeasurekNNQ, DBMTree[i], PageManagerDBM[i]);
         cout << " Ok\n";

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
         gnuTestRQ->AddMeasure(rMeasureRQ, name, line);
         gnuTestkNNQ->AddMeasure(rMeasurekNNQ, name, line);
         // Reset the statistics.
         rMeasureRQ->Reset();
         rMeasurekNNQ->Reset();
      }//end if
   }//end for

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

   myResult * result;
   stDistance radius;
   stDistance diameter;
   clock_t start, end;
   unsigned int i, j;
   unsigned int size;
   long sum;

   if (metricTree){
      size = queryObjects.size();
      //For number of points (radius) that I want measure.
      for (i=0; i < rMeasure->GetSize(); i++){

         radius = rMeasure->GetK(i) * this->MaxDistance;
         //reset the statistics
         pageManager->ResetStatistics();
         metricTree->GetMetricEvaluator()->ResetStatistics();
         start = clock();
         for (j=0; j < size; j++){
            result = metricTree->RangeQuery(queryObjects[j], radius);
            sum += result->GetNumOfEntries();
            delete result;
         }//end for
         end = clock();
         cout << " sum: " << sum;
         rMeasure->SetTotalTime(i, ((double )end-(double )start) / CLK_TCK);
         // is divided for queryObjects to get the everage
         rMeasure->SetDiskAccess(i, (double )pageManager->GetReadCount() / (double )size);
         // is divided for queryObjects to get the everage
         rMeasure->SetDistanceFunction(i,
            (double )metricTree->GetMetricEvaluator()->GetDistanceCount() / (double )size);

         cout << rMeasure->GetK(i) << " ";
      }//end for
   }//end if
}//end TApp::PerformRangeQuery

//------------------------------------------------------------------------------
void TApp::PerformNearestQuery(ResultMeasureDiscrete * rMeasure, MetricTree * metricTree,
                               stPageManager * pageManager){

   myResult * result;
   clock_t start, end;
   unsigned int i, j;
   unsigned int size;

   if (metricTree){
      size = queryObjects.size();
      //For number of points (radius) that I want measure.
      for (i=0; i < rMeasure->GetSize(); i++){

         //reset the statistics for Slim
         pageManager->ResetStatistics();
         metricTree->GetMetricEvaluator()->ResetStatistics();
         start = clock();
         for (j=0; j < size; j++){
            result = metricTree->NearestQuery(queryObjects[j], rMeasure->GetK(i));
            delete result;
         }//end for
         end = clock();
         rMeasure->SetTotalTime(i, ((double )end-(double )start) / CLK_TCK);
         // is divided for queryObjects to get the everage
         rMeasure->SetDiskAccess(i, (double )pageManager->GetReadCount() / (double )size);
         // is divided for queryObjects to get the everage
         rMeasure->SetDistanceFunction(i,
            (double )metricTree->GetMetricEvaluator()->GetDistanceCount() / (double )size);

         cout << rMeasure->GetK(i) << " ";
      }//end for
   }//end if

}//end TApp::PerformNearestQuery

