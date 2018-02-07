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
   PageManagerSlimMST = NULL;
   PageManagerSlimDown = NULL;
   MetricTreeMTree = NULL;
   MetricTreeSlimMST = NULL;
   MetricTreeSlimDown = NULL;
   MetricTreeMTreeTime = 0;
   MetricTreeSlimMSTTime = 0;
   MetricTreeSlimDownTime = 0;

   for (int i = 0; i < NUMBEROFTREES; i++){
      PageManagerDBM[i] = NULL;
      MetricTreeDBM[i] = NULL;
      MetricTreeDBMTime[i] = 0;
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
   // create for Slim-Tree
   MetricTreeMTree = new mySlimTree(PageManagerMTree);
   MetricTreeMTree->SetSplitMethod(mySlimTree::smMINMAX);
   MetricTreeMTree->SetChooseMethod(mySlimTree::cmMINDIST);
/*
   MetricTreeSlimMST = new mySlimTree(PageManagerSlimMST);
   MetricTreeSlimMST->SetSplitMethod(mySlimTree::smSPANNINGTREE);
   MetricTreeSlimMST->SetChooseMethod(mySlimTree::cmMINDIST); /**/

   MetricTreeSlimDown = new mySlimTree(PageManagerSlimDown);
   MetricTreeSlimDown->SetSplitMethod(mySlimTree::smMINMAX);
   MetricTreeSlimDown->SetChooseMethod(mySlimTree::cmMINDIST);

   // create for DBM-Tree
   for (int i = 0; i < NUMBEROFTREES; i++){
      MetricTreeDBM[i] = new myDBMTree(PageManagerDBM[i]);
   }//end for

   MetricTreeDBM[0]->SetSplitMethod(myDBMTree::smMIN_MAX);
   MetricTreeDBM[0]->SetMinOccupation(this->MinOccup);
   MetricTreeDBM[0]->SetChooseMethod(myDBMTree::cmMINDIST);
   MetricTreeDBM[0]->SetReInsert(true);

   MetricTreeDBM[1]->SetSplitMethod(myDBMTree::smMIN_SUM);
   MetricTreeDBM[1]->SetMinOccupation(this->MinOccup);
   MetricTreeDBM[1]->SetChooseMethod(myDBMTree::cmMINDIST);
   MetricTreeDBM[1]->SetReInsert(true);

   MetricTreeDBM[2]->SetSplitMethod(myDBMTree::smMIN_MAX);
   MetricTreeDBM[2]->SetChooseMethod(myDBMTree::cmMINDISTWITHCOVER);
   MetricTreeDBM[2]->SetMinOccupation(0.5);
   MetricTreeDBM[2]->SetReInsert(false);

   MetricTreeDBM[3]->SetSplitMethod(myDBMTree::smMST_SLIM);
   MetricTreeDBM[3]->SetChooseMethod(myDBMTree::cmMINDISTWITHCOVER);
   MetricTreeDBM[3]->SetMinOccupation(0.5);
   MetricTreeDBM[3]->SetReInsert(false);
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
   strcat(fileName, "MTreeMinMax");
   strcat(fileName, pageSizeString);
   strcat(fileName, "_");
   strcat(fileName, minOccupString);
   strcat(fileName, ".dat");
   PageManagerMTree = new stPlainDiskPageManager(fileName, this->PageSize);
   //for Slim-Tree MST
   strcpy(fileName, this->Prefix.c_str());
   strcat(fileName, "SlimTreeMST");
   strcat(fileName, pageSizeString);
   strcat(fileName, "_");
   strcat(fileName, minOccupString);
   strcat(fileName, ".dat");
   PageManagerSlimMST = new stPlainDiskPageManager(fileName, this->PageSize);
   //for Slim-Tree SlimDown
   strcpy(fileName, this->Prefix.c_str());
   strcat(fileName, "SlimTreeSlimDown");
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
   cout << "\n\nAdding objects in the MetricTreeMTree";
   LoadTree(DataPath, MetricTreeMTree, &MetricTreeMTreeTime);

   if (MetricTreeSlimMST){
      cout << "\n\nAdding objects in the MetricTreeSlimMST";
      LoadTree(DataPath, MetricTreeSlimMST, &MetricTreeSlimMSTTime);
      cout << "\nExecuting the Slim-Down Algorithm.";
      MetricTreeSlimMST->Optimize();
   }//end if
   cout << " Done!";

   if (MetricTreeSlimDown){
      cout << "\n\nAdding objects in the MetricTreeSlimDown";
      LoadTree(DataPath, MetricTreeSlimDown, &MetricTreeSlimDownTime);
      cout << "\nExecuting the Slim-Down Algorithm.";
      MetricTreeSlimDown->Optimize();
   }//end if
   cout << " Done!";

   for (int i = 0; i < NUMBEROFTREES; i++){
      if (MetricTreeDBM[i]){
         cout << "\n\nAdding objects in the MetricTreeDBM[" << i << "]";
         LoadTree(DataPath, MetricTreeDBM[i], &MetricTreeDBMTime[i]);
         cout << "\nExecuting the Slim-Down Algorithm for " << i << ".";
         MetricTreeDBM[i]->DeleteUniqueNodes();
         MetricTreeDBM[i]->Optimize();
         MetricTreeDBM[i]->DeleteUniqueNodes();
         cout << " Done!";
         //cout << "\nConsistency: " << MetricTreeDBM[i]->Consistency();
      }//end if
   }//end for
   // Write information of trees.
   //WriteStats();

   // Lets do the queries
   cout << "\nAdding query objects ";
   LoadVectorFromFile(DataQueryPath);

   if (this->MaxDistance <= 0){
      cout << "\nCalculating the maximum distance ...\n";
      if (MetricTreeSlimDown){
         this->MaxDistance = MetricTreeSlimDown->GetGreaterDistance();
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
      WriteStat(fileStats, "MetricTreeMTree", MetricTreeMTree, this->MetricTreeMTreeTime);
      cout << "\nDone for MetricTreeMTree.";
      WriteStat(fileStats, "MetricTreeSlimMST", MetricTreeSlimMST, this->MetricTreeSlimMSTTime);
      cout << "\nDone for MetricTreeSlimMST.";
      WriteStat(fileStats, "MetricTreeSlimDown", MetricTreeSlimDown, this->MetricTreeSlimDownTime);
      cout << "\nDone for MetricTreeSlimDown.";
      for (int i = 0; i < NUMBEROFTREES; i++){
         strcpy(strTemp, "MetricTreeDBM[");
         sprintf(tmpStr, "%d", i);
         strcat(strTemp, tmpStr);
         strcat(strTemp, "]");
         WriteStat(fileStats, strTemp, MetricTreeDBM[i], this->MetricTreeDBMTime[i]);
         cout << "\nDone for MetricTreeDBM[" << i << "].";
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

   if (this->MetricTreeMTree != NULL){
      delete this->MetricTreeMTree;
   }//end if
   if (this->MetricTreeSlimMST != NULL){
      delete this->MetricTreeSlimMST;
   }//end if
   if (this->MetricTreeSlimDown != NULL){
      delete this->MetricTreeSlimDown;
   }//end if

   if (this->PageManagerMTree != NULL){
      delete this->PageManagerMTree;
   }//end if
   if (this->PageManagerSlimMST != NULL){
      delete this->PageManagerSlimMST;
   }//end if
   if (this->PageManagerSlimDown != NULL){
      delete this->PageManagerSlimDown;
   }//end if

   for (int i = 0; i < NUMBEROFTREES; i++){
      if (this->MetricTreeDBM[i] != NULL){
         delete this->MetricTreeDBM[i];
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
   char cityName[200];
   double dLat, dLong;
   int w = 0;
   clock_t totalTimeTemp = 0;
   clock_t start, end;

   if (metricTree!=NULL){
      if (in.is_open()){
         cout << "\nLoading objects ";
         while(in.getline(cityName, 200, '\t')){
            in >> dLat;
            in >> dLong;
            in.ignore();
            start = clock();
            this->AddToTree(cityName, dLat, dLong, metricTree);
            end = clock();
            totalTimeTemp += end-start;
            w++;
            if (w % 10 == 0){
               cout << '.';
            }//end if
         }//end while
         cout << " Added " << metricTree->GetNumberOfObjects() << " objects ";
         in.close();
         *totalTime = totalTimeTemp;
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
   char cityName[200];
   int cont;
   double dLat, dLong;

   // clear before using.
   queryObjects.clear();

   if (in.is_open()){
      cout << "\nLoading query objects ";
      cont = 0;
      while(in.getline(cityName, 200, '\t')){
         in >> dLat;
         in >> dLong;
         in.ignore();
         this->queryObjects.insert(queryObjects.end(), new TCity(cityName, dLat, dLong));
         cont++;
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

   gnuTestRQ->SetTitle(GNUPlot::DISTFUNCTION, "RQ: Cities");
   gnuTestRQ->SetTitle(GNUPlot::DISKACCESS, "RQ: Cities");
   gnuTestRQ->SetTitle(GNUPlot::TOTALTIME, "RQ: Cities");
   gnuTestRQ->SetXLabel(GNUPlot::DISTFUNCTION, "% radius");
   gnuTestRQ->SetXLabel(GNUPlot::DISKACCESS, "% radius");
   gnuTestRQ->SetXLabel(GNUPlot::TOTALTIME, "% radius");
   gnuTestRQ->SetYLogScale(GNUPlot::DISTFUNCTION, false);
   gnuTestRQ->SetYLogScale(GNUPlot::DISKACCESS, false);
   gnuTestRQ->SetYLogScale(GNUPlot::TOTALTIME, false);
   gnuTestRQ->SetYLabel(GNUPlot::DISTFUNCTION, "Avg Number of Distance Calculation");
   gnuTestRQ->SetYLabel(GNUPlot::DISKACCESS, "Avg Number of Disk Access");
   gnuTestRQ->SetYLabel(GNUPlot::TOTALTIME, "Total Time (s)");

   gnuTestkNNQ->SetTitle(GNUPlot::DISTFUNCTION, "kNNQ: Cities");
   gnuTestkNNQ->SetTitle(GNUPlot::DISKACCESS, "kNNQ: Cities");
   gnuTestkNNQ->SetTitle(GNUPlot::TOTALTIME, "kNNQ: Cities");
   gnuTestkNNQ->SetXLabel(GNUPlot::DISTFUNCTION, "k");
   gnuTestkNNQ->SetXLabel(GNUPlot::DISKACCESS, "k");
   gnuTestkNNQ->SetXLabel(GNUPlot::TOTALTIME, "k");
   gnuTestkNNQ->SetLogScale(GNUPlot::DISTFUNCTION, false);
   gnuTestkNNQ->SetLogScale(GNUPlot::DISKACCESS, false);
   gnuTestkNNQ->SetLogScale(GNUPlot::TOTALTIME, false);
   gnuTestkNNQ->SetYLabel(GNUPlot::DISTFUNCTION, "Avg Number of Distance Calculation");
   gnuTestkNNQ->SetYLabel(GNUPlot::DISKACCESS, "Avg Number of Disk Access");
   gnuTestkNNQ->SetYLabel(GNUPlot::TOTALTIME, "Total Time (s)");

   if (MetricTreeMTree){
      cout << "\nStarting Statistics for Range Query with MTree-MinMax.... ";
      PerformRangeQuery(rMeasureRQ, MetricTreeMTree, PageManagerMTree);
      cout << " Ok\n";

      cout << "\nStarting Statistics for Nearest Query with MTree-MinMax.... ";
      PerformNearestQuery(rMeasurekNNQ, MetricTreeMTree, PageManagerMTree);
      cout << " Ok\n";

      // Add the result
      gnuTestRQ->AddMeasure(rMeasureRQ, "MTree-Minmax", "linespoints lt 6 lw 2 pt 5");
      gnuTestkNNQ->AddMeasure(rMeasurekNNQ, "MTree-Minmax", "linespoints lt 6 lw 2 pt 5");
      // Reset the statistics.
      rMeasureRQ->Reset();
      rMeasurekNNQ->Reset();
   }//end if

   if (MetricTreeSlimMST){
      cout << "\nStarting Statistics for Range Query with SlimTree-MST.... ";
      PerformRangeQuery(rMeasureRQ, MetricTreeSlimMST, PageManagerSlimMST);
      cout << " Ok\n";

      cout << "\nStarting Statistics for Nearest Query with SlimTree-MST.... ";
      PerformNearestQuery(rMeasurekNNQ, MetricTreeSlimMST, PageManagerSlimMST);
      cout << " Ok\n";

      // Add the result
      gnuTestRQ->AddMeasure(rMeasureRQ, "SlimTree-MST", "linespoints lt 7 lw 2 pt 7");
      gnuTestkNNQ->AddMeasure(rMeasurekNNQ, "SlimTree-MST", "linespoints lt 7 lw 2 pt 7");
      // Reset the statistics.
      rMeasureRQ->Reset();
      rMeasurekNNQ->Reset();
   }//end if

   if (MetricTreeSlimDown){

      cout << "\nStarting Statistics for Range Query with SlimTree-SlimDown.... ";
      PerformRangeQuery(rMeasureRQ, MetricTreeSlimDown, PageManagerSlimDown);
      cout << " Ok\n";

      cout << "\nStarting Statistics for Nearest Query with SlimTree-SlimDown.... ";
      PerformNearestQuery(rMeasurekNNQ, MetricTreeSlimDown, PageManagerSlimDown);
      cout << " Ok\n";

      // Add the result
      gnuTestRQ->AddMeasure(rMeasureRQ, "SlimTree-MinMax-SlimDown", "linespoints lt 8 lw 2 pt 11");
      gnuTestkNNQ->AddMeasure(rMeasurekNNQ, "SlimTree-MinMax-SlimDown", "linespoints lt 8 lw 2 pt 11");
      // Reset the statistics.
      rMeasureRQ->Reset();
      rMeasurekNNQ->Reset();
   }//end if

   for (int i = 0; i < NUMBEROFTREES; i++){
      if (MetricTreeDBM[i]){
         // queries for DBM-Tree
         cout << "\nStarting Statistics for Range Query with DBMTree-" << i << ".... ";
         PerformRangeQuery(rMeasureRQ, MetricTreeDBM[i], PageManagerDBM[i]);
         cout << " Ok\n";

         cout << "\nStarting Statistics for Nearest Query with DBMTree-" << i << ".... ";
         PerformNearestQuery(rMeasurekNNQ, MetricTreeDBM[i], PageManagerDBM[i]);
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
   myResult * result2;
   stDistance radius;
   clock_t start, end;
   unsigned int size;
   unsigned int i, j;
   long sum;

   if (metricTree){
      size = queryObjects.size();
      //For number of points (radius) that I want measure.
      for (i=0; i < rMeasure->GetSize(); i++){
         radius = rMeasure->GetK(i) * this->MaxDistance;
         //reset the statistics
         pageManager->ResetStatistics();
         metricTree->GetMetricEvaluator()->ResetStatistics();
         sum = 0;
         start = clock();
         for (j=0; j < size; j++){
            result = metricTree->RangeQuery(queryObjects[j], radius);
            sum += result->GetNumOfEntries();
            #ifdef __CMPANSWER__
            result2 = MetricTreeSlimDown->RangeQuery(queryObjects[j], radius);
            if (!result2->IsEqual(result)){
               cout << "\n\n Pau\n";
               int w;
               TCity * tmp;

               cout << "Range query with radius " << result->GetRadius() << ".\n";
               cout << "The sample object was " << *(result->GetSample()) << ".\n";

               if (result->GetNumOfEntries() == 0){
                  cout << "No results!\n";
               }else{
                  cout << "  " << result->GetNumOfEntries() << " results:\n";
                  for (w = 0; w < result->GetNumOfEntries(); w++){
                     tmp = (TCity *)(*result)[w].GetObject();
                     cout << "  Distance = " << (*result)[w].GetDistance() <<
                           " - Object = ";
                     cout << *tmp << "\n";
                  }//end for
               }//end if
               if (result2->GetNumOfEntries() == 0){
                  cout << "No results in MetricTreeSlimDown!\n";
               }else{
                  cout << "  " << result2->GetNumOfEntries() << " results in MetricTreeSlimDown:\n";
                  for (w = 0; w < result2->GetNumOfEntries(); w++){
                     tmp = (TCity *)(*result2)[w].GetObject();
                     cout << "  Distance = " << (*result2)[w].GetDistance() <<
                           " - Object = ";
                     cout << *tmp << "\n";
                  }//end for
               }//end if
            }//end if
            delete result2;
            #endif //__CMPANSWER__
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
   myResult * result2;
   clock_t start, end;
   unsigned int size;
   unsigned int i, j;

   if (metricTree){
      size = queryObjects.size();
      //For number of objects that I want measure.
      for (i=0; i < rMeasure->GetSize(); i++){
         //reset the statistics for Slim
         pageManager->ResetStatistics();
         metricTree->GetMetricEvaluator()->ResetStatistics();
         start = clock();
         for (j=0; j < size; j++){
            result = metricTree->NearestQuery(queryObjects[j], rMeasure->GetK(i));
            #ifdef __CMPANSWER__
            result2 = MetricTreeSlimDown->NearestQuery(queryObjects[j], rMeasure->GetK(i));
            if (!result2->IsEqual(result)){
               cout << "\n\n Pau\n";
               int w;
               TCity * tmp;

               cout << "Range query with radius " << result->GetRadius() << ".\n";
               cout << "The sample object was " << *(result->GetSample()) << ".\n";

               if (result->GetNumOfEntries() == 0){
                  cout << "No results!\n";
               }else{
                  cout << "  " << result->GetNumOfEntries() << " results:\n";
                  for (w = 0; w < result->GetNumOfEntries(); w++){
                     tmp = (TCity *)(*result)[w].GetObject();
                     cout << "  Distance = " << (*result)[w].GetDistance() <<
                           " - Object = ";
                     cout << *tmp << "\n";
                  }//end for
               }//end if
               if (result2->GetNumOfEntries() == 0){
                  cout << "No results in MetricTreeSlimDown!\n";
               }else{
                  cout << "  " << result2->GetNumOfEntries() << " results in MetricTreeSlimDown:\n";
                  for (w = 0; w < result2->GetNumOfEntries(); w++){
                     tmp = (TCity *)(*result2)[w].GetObject();
                     cout << "  Distance = " << (*result2)[w].GetDistance() <<
                           " - Object = ";
                     cout << *tmp << "\n";
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
            (double )metricTree->GetMetricEvaluator()->GetDistanceCount() / (double )size);

         cout << rMeasure->GetK(i) << " ";
      }//end for
   }//end if
}//end TApp::PerformNearestQuery
