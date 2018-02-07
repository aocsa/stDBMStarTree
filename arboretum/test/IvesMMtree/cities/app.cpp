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
   PageManagerSlimMST = NULL;
   PageManagerVP = NULL;
   PageManagerGH = NULL;

   MetricTreeSlimMST = NULL;
   MetricTreeVP = NULL;
   MetricTreeGH = NULL;

   MetricTreeSlimMSTTime = 0;
   MetricTreeVPTime = 0;
   MetricTreeGHTime = 0;

   for (int i = 0; i < NUMBEROFTREES; i++){
      PageManagerMM[i] = NULL;
      MetricTreeMM[i] = NULL;
      MetricTreeMMTime[i] = 0;
   }//end for
}//end TApp

//------------------------------------------------------------------------------
void TApp::Init(unsigned int pageSize, unsigned int quantidade, char * prefix,
                                                                 int numcities){
   this->PageSize = pageSize;
   this->Quantidade = quantidade;
   this->Prefix = prefix;
   this->NumCities = numcities;

   // Create it in memory
   CreateMemoryPageManager();

   // Creates the trees
   CreateTree();
}//end TApp::Init


void TApp::CreateMemoryPageManager(){
   PageManagerSlimMST = new stMemoryPageManager(this->PageSize);
   PageManagerVP = new stMemoryPageManager(this->PageSize);
   PageManagerGH = new stMemoryPageManager(this->PageSize);

   for (int i = 0; i < NUMBEROFTREES; i++){
      PageManagerMM[i] = new stMemoryPageManager(this->PageSize);
   }//end for

}//end TApp::CreateMemoryPageManager()


//------------------------------------------------------------------------------
void TApp::CreateTree(){
   // create for Slim-Tree
   MetricTreeSlimMST = new mySlimTree(PageManagerSlimMST);
   MetricTreeSlimMST->SetSplitMethod(mySlimTree::smSPANNINGTREE);
   MetricTreeSlimMST->SetChooseMethod(mySlimTree::cmMINOCCUPANCY);

   MetricTreeVP = new myVPTree(PageManagerVP);
   MetricTreeGH = new myGHTree(PageManagerGH);

   // create the MM-Trees
   for (int i = 0; i < NUMBEROFTREES; i++){
      MetricTreeMM[i] = new myMMTree(PageManagerMM[i]);
   }//end for

   MetricTreeMM[0]->SetInsertionMethod(myMMTree::imNOBALANCE);
   MetricTreeMM[0]->SetNearestMethod(myMMTree::nmNORMAL);

   MetricTreeMM[1]->SetInsertionMethod(myMMTree::imNOBALANCE);
   MetricTreeMM[1]->SetNearestMethod(myMMTree::nmGUIDED);

   MetricTreeMM[2]->SetInsertionMethod(myMMTree::imTRY2BALANCE);
   MetricTreeMM[2]->SetNearestMethod(myMMTree::nmNORMAL);

   MetricTreeMM[3]->SetInsertionMethod(myMMTree::imTRY2BALANCE);
   MetricTreeMM[3]->SetNearestMethod(myMMTree::nmGUIDED);

}//end TApp::CreateTree              
//------------------------------------------------------------------------------


//------------------------------------------------------------------------------
void TApp::Run(char * DataPath, char * DataQueryPath){
   FILE *times = fopen("tempo.txt","w");
   FILE *dist_file = fopen("Distancias_calculadas_building.txt","w");

   // Lets load the tree with a lot values from the file.


   cout << "\n\nAdding objects in the MetricTreeSlimMST";
   MetricTreeSlimMST->GetMetricEvaluator()->ResetStatistics();
   LoadTree(DataPath, MetricTreeSlimMST, &MetricTreeSlimMSTTime);
   if (MetricTreeSlimMST){
      cout << "\nExecuting the Slim-Down Algorithm.";
      MetricTreeSlimMST->Optimize();
   }//end if
   fprintf(dist_file,"Slim-MST: %u\n", MetricTreeSlimMST->GetMetricEvaluator()->GetDistanceCount());
   cout << " Done!";


   cout << "\n\nAdding objects in the MetricTreeGH";
   MetricTreeGH->GetMetricEvaluator()->ResetStatistics();
   LoadTree(DataPath, MetricTreeGH, &MetricTreeGHTime);
   fprintf(dist_file,"GH-tree: %u\n", MetricTreeGH->GetMetricEvaluator()->GetDistanceCount());
   cout << " Done!";


   cout << "\n\nAdding objects in the MetricTreeVP";
   MetricTreeVP->GetMetricEvaluator()->ResetStatistics();
   LoadTree(DataPath, MetricTreeVP, &MetricTreeVPTime);
   fprintf(dist_file,"VP-tree: %u\n", MetricTreeVP->GetMetricEvaluator()->GetDistanceCount());
   cout << " Done!";


   for (int i = 0; i < NUMBEROFTREES; i++){
      cout << "\n\nAdding objects in the MetricTreeMM[" << i << "]";
      MetricTreeMM[i]->GetMetricEvaluator()->ResetStatistics();
      LoadTree(DataPath, MetricTreeMM[i], &MetricTreeMMTime[i]);
      fprintf(dist_file,"MM-tree %i: %u\n", i, MetricTreeMM[i]->GetMetricEvaluator()->GetDistanceCount());
      cout << " Done!";
   }//end for

   //Writing times to building the trees
   fprintf(times, "Slim-tree:  %li \n", MetricTreeSlimMSTTime);
   fprintf(times, "GH-tree:  %li \n", MetricTreeGHTime);
   fprintf(times, "VP-tree:  %li \n", MetricTreeVPTime);
   for (int i = 0; i < NUMBEROFTREES; i++){
      fprintf(times, "MM-tree %i:  %li \n", i, MetricTreeMMTime[i]);
   }//end for                                  

   
   fclose(times);
   fclose(dist_file);

   
   // Lets do the queries
   cout << "\nAdding query objects ";
   LoadVectorFromFile(DataQueryPath);

   // Do queries.
   PerformQueries();

   // Hold the screen.
   cout << "\n\nFinished the whole test!";
}//end TApp::Run


//------------------------------------------------------------------------------
void TApp::WriteStats(){
   char pageSizeString[10];
   char fileName[50];
   char strTemp[500];
   char tmpStr[11];
   FILE * fileStats;

   itoa(this->PageSize, pageSizeString, 10);

   // set the name of this file
   strcpy(fileName, this->Prefix.c_str());
   strcat(fileName, "Stats");
   strcat(fileName, pageSizeString);
   strcat(fileName, ".txt");

   if ((fileStats = fopen(fileName, "w")) == NULL){
      printf("\nCannot open statistics file.");
   }else{
      cout << "\nWriting statistics for trees";
      // Write statistics.
      WriteStat(fileStats, "MetricTreeSlimMST", MetricTreeSlimMST, this->MetricTreeSlimMSTTime);
      cout << "\nDone for MetricTreeSlimMST.";

      WriteStat(fileStats, "MetricTreeGH", MetricTreeGH, this->MetricTreeGHTime);
      cout << "\nDone for MetricTreeGH.";

      WriteStat(fileStats, "MetricTreeVP", MetricTreeVP, this->MetricTreeVPTime);
      cout << "\nDone for MetricTreeVP.";

      for (int i = 0; i < NUMBEROFTREES; i++){
         strcpy(strTemp, "MetricTreeMM[");
         strcat(strTemp, itoa(i, tmpStr, 10));
         strcat(strTemp, "]");
         WriteStat(fileStats, strTemp, MetricTreeMM[i], this->MetricTreeMMTime[i]);
         cout << "\nDone for MetricTreeMM[" << i << "].";
      }//end for                      
      
      // close the file
      fclose(fileStats);
   }//end if

}//end WriteStats

//------------------------------------------------------------------------------
void TApp::WriteStat(FILE * file, char * treeName, MetricTree * metricTree, clock_t time){
   char strTemp[500];
   int minh, maxh;

   if (metricTree){
      // Get the information about the tree.
      strcpy(strTemp, "\n\n");
      strcat(strTemp, treeName);
      fwrite(strTemp, strlen(strTemp), 1, file);
      strcpy(strTemp, "\n\tHeight: ");
      fwrite(strTemp, strlen(strTemp), 1, file);
//      fprintf(file, "%d", infoResult->GetHeight());
      strcpy(strTemp, "\n\tObjs Count: ");
      fwrite(strTemp, strlen(strTemp), 1, file);
//      fprintf(file, "%d", infoResult->GetObjectCount());
      strcpy(strTemp, "\n\tRadius Tree: ");
      fwrite(strTemp, strlen(strTemp), 1, file);
      strcpy(strTemp, "\n\tPage Count: ");
      fwrite(strTemp, strlen(strTemp), 1, file);
      fprintf(file, "%d", metricTree->GetNodeCount());
      strcpy(strTemp, "\n\tPage size: ");
      fwrite(strTemp, strlen(strTemp), 1, file);
      fprintf(file, "%d", metricTree->GetPageManager()->GetMinimumPageSize());

      strcpy(strTemp, "\n\tTotal Time Construction: ");
      fwrite(strTemp, strlen(strTemp), 1, file);
      fprintf(file, "%ld", time);

//      delete infoResult;
   }//end if
}//end WriteStat

//------------------------------------------------------------------------------
void TApp::Done(){

   if (this->MetricTreeSlimMST != NULL){
      delete this->MetricTreeSlimMST;
   }//end if
   if (this->PageManagerSlimMST != NULL){
      delete this->PageManagerSlimMST;
   }//end if


   if (this->MetricTreeGH != NULL){
      delete this->MetricTreeGH;
   }//end if
   if (this->PageManagerGH != NULL){
      delete this->PageManagerGH;
   }//end if


   if (this->MetricTreeVP= NULL){
      delete this->MetricTreeVP;
   }//end if
   if (this->PageManagerVP != NULL){
      delete this->PageManagerVP;
   }//end if

   
   for (int i = 0; i < NUMBEROFTREES; i++){
      if (this->MetricTreeMM[i] != NULL){
         delete this->MetricTreeMM[i];
      }//end if
      if (this->PageManagerMM[i] != NULL){
         delete this->PageManagerMM[i];
      }//end if
   }//end for                         

   // delete the vetor of queries.
   for (int i = 0; i < queryCities.size(); i++){
      delete (queryCities.at(i));
   }//end for
}//end TApp::Done

//------------------------------------------------------------------------------
void TApp::LoadTree(char * fileName, MetricTree * metricTree, clock_t * totalTime){
   ifstream in(fileName);
   char cityName[200];
   double dLat, dLong;
   int w = 0, i = 0;
   clock_t totalTimeTemp = 0;
   clock_t start, end;

   myVPTree * metricTreeVP=NULL;
   TCity *cities=NULL, *tmp;

   if (metricTree!=NULL){
      if (in.is_open()){
         cout << "\nLoading objects ";

         if (metricTreeVP = dynamic_cast<myVPTree *> (metricTree)){
            //It is the vp-tree
            cities = new TCity[this->NumCities];
         }

         while(in.getline(cityName, 200, '\t')){
            in >> dLat;
            in >> dLong;
            in.ignore();

            if (metricTreeVP){
//               cities[i++] = TCity(cityName, dLat, dLong);
               tmp = new TCity(cityName, dLat, dLong);
               cities[i++].Unserialize(tmp->Serialize(), tmp->GetSerializedSize());
               delete tmp;
            }
            else{
               start = clock();
               this->AddToTree(cityName, dLat, dLong, metricTree);
               end = clock();
               totalTimeTemp += end-start;
            }

            w++;
            if (w % 10 == 0){
               cout << '.';
            }//end if

         }//end while

         if (metricTreeVP){
            //Adds in the VP-tree
            start = clock();
            MetricTreeVP->Add(cities, this->NumCities);
            end = clock();
            totalTimeTemp += end-start;
            if (cities) delete[] cities;
         }

         cout << " Objects successfully added";
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

   if (in.is_open()){
      cout << "\nLoading query objects ";
      cont = 0;
      while(in.getline(cityName, 200, '\t')){
         in >> dLat;
         in >> dLong;
         in.ignore();
         this->queryCities.insert(queryCities.end(), new TCity(cityName, dLat, dLong));
         cont++;
      }//end while
      cout << " Added " << cont << " query objects ";
      in.close();
   }else{
      cout << "\nProblem to open the query file.";
      cout << "\n Zero object added!!\n";
   }//end if
}//end TApp::LoadVectorFromFile

//------------------------------------------------------------------------------
void TApp::PerformQueries(){

   char pause[] = "\npause -1";
   char pageSizeString[10];
   char fileName[50];
   char name[100];
   char strTmp[11];

   //for the result of the tests
   ResultMeasureDiscrete * rMeasurekNNQ = new ResultMeasureDiscrete(this->Quantidade);
   ResultMeasure * rMeasureRQ = new ResultMeasure(this->Quantidade);

   FILE * fileDistRQ, * fileTimeRQ, * fileDiscRQ;
   FILE * fileDistkNNQ, * fileTimekNNQ, * fileDisckNNQ;

   itoa(this->PageSize, pageSizeString, 10);

   //set the name and the header of the distance function file for RQ
   strcpy(fileName, this->Prefix.c_str());
   strcat(fileName, "RQDist");
   strcat(fileName, pageSizeString);
   strcat(fileName, ".plt");
   fileDistRQ = fopen(fileName, "w");
   WriteHeader(fileDistRQ, "set ylabel \"# Médio de Cálculos de Distância\"\n", true);

   //set the name and the header of the distance function file for kNNQ
   strcpy(fileName, this->Prefix.c_str());
   strcat(fileName, "kNNDist");
   strcat(fileName, pageSizeString);
   strcat(fileName, ".plt");
   fileDistkNNQ = fopen(fileName, "w");
   WriteHeader(fileDistkNNQ, "set ylabel \"# Médio de Cálculos de Distância\"\n", false);

   //set the name and the header of the disc access file for RQ
   strcpy(fileName, this->Prefix.c_str());
   strcat(fileName, "RQDisc");
   strcat(fileName, pageSizeString);
   strcat(fileName, ".plt");
   fileDiscRQ = fopen(fileName, "w");
   WriteHeader(fileDiscRQ, "set ylabel \"# Médio de Acessos a Disco\"\n", true);

   //set the name and the header of the disc access file for kNNQ
   strcpy(fileName, this->Prefix.c_str());
   strcat(fileName, "kNNQDisc");
   strcat(fileName, pageSizeString);
   strcat(fileName, ".plt");
   fileDisckNNQ = fopen(fileName, "w");
   WriteHeader(fileDisckNNQ, "set ylabel \"# Médio de Acessos a Disco\"\n", false);

   //set the name and the header of the time file for RQ
   strcpy(fileName, this->Prefix.c_str());
   strcat(fileName,"RQTime");
   strcat(fileName, pageSizeString);
   strcat(fileName, ".plt");
   fileTimeRQ = fopen(fileName, "w");
   WriteHeader(fileTimeRQ, "set ylabel \"Tempo Total (ms)\"\n", true);

   //set the name and the header of the time file for kNNQ
   strcpy(fileName, this->Prefix.c_str());
   strcat(fileName, "kNNTime");
   strcat(fileName, pageSizeString);
   strcat(fileName, ".plt");
   fileTimekNNQ = fopen(fileName, "w");
   WriteHeader(fileTimekNNQ, "set ylabel \"Tempo Total (ms)\"\n", false);

   if (MetricTreeSlimMST){
      cout << "\nStarting Statistics for Range Query with SlimTree-MST.... ";
      cout < "HHHHHH";
      PerformRangeQuery(rMeasureRQ, MetricTreeSlimMST, PageManagerSlimMST);
      cout << " Ok\n";

      cout << "\nStarting Statistics for Nearest Query with SlimTree-MST.... ";
      PerformNearestQuery(rMeasurekNNQ, MetricTreeSlimMST, PageManagerSlimMST);
      cout << " Ok\n";

      //write the statistics to files
      //Distance Function
      WriteToFile(fileDistRQ, "# SlimTree-MST\n", rMeasureRQ, 1);
      WriteToFile(fileDistkNNQ, "# SlimTree-MST\n", rMeasurekNNQ, 1);
      //Disc Access
      WriteToFile(fileDiscRQ, "# SlimTree-MST\n", rMeasureRQ, 2);
      WriteToFile(fileDisckNNQ, "# SlimTree-MST\n", rMeasurekNNQ, 2);
      //Total Time
      WriteToFile(fileTimeRQ, "# SlimTree-MST\n", rMeasureRQ, 3);
      WriteToFile(fileTimekNNQ, "# SlimTree-MST\n", rMeasurekNNQ, 3);
      // Reset the statistics.
      rMeasureRQ->Reset();
      rMeasurekNNQ->Reset();
   }//end if

   if (MetricTreeGH){
      cout << "\nStarting Statistics for Range Query with GH-tree.... ";
      PerformRangeQuery(rMeasureRQ, MetricTreeGH, PageManagerGH);
      cout << " Ok\n";

      cout << "\nStarting Statistics for Nearest Query with GH-tree.... ";
      PerformNearestQuery(rMeasurekNNQ, MetricTreeGH, PageManagerGH);
      cout << " Ok\n";

      //write the statistics to files
      //Distance Function
      WriteToFile(fileDistRQ, "# GH-tree\n", rMeasureRQ, 1);
      WriteToFile(fileDistkNNQ, "# GH-tree\n", rMeasurekNNQ, 1);
      //Disc Access
      WriteToFile(fileDiscRQ, "# GH-tree\n", rMeasureRQ, 2);
      WriteToFile(fileDisckNNQ, "# GH-tree\n", rMeasurekNNQ, 2);
      //Total Time
      WriteToFile(fileTimeRQ, "# GH-tree\n", rMeasureRQ, 3);
      WriteToFile(fileTimekNNQ, "# GH-tree\n", rMeasurekNNQ, 3);
      // Reset the statistics.
      rMeasureRQ->Reset();
      rMeasurekNNQ->Reset();
   }//end if

   if (MetricTreeVP){
      cout << "\nStarting Statistics for Range Query with VP-tree.... ";
      PerformRangeQuery(rMeasureRQ, MetricTreeVP, PageManagerVP);
      cout << " Ok\n";

      cout << "\nStarting Statistics for Nearest Query with VP-tree.... ";
      PerformNearestQuery(rMeasurekNNQ, MetricTreeVP, PageManagerVP);
      cout << " Ok\n";

      //write the statistics to files
      //Distance Function
      WriteToFile(fileDistRQ, "# VP-tree\n", rMeasureRQ, 1);
      WriteToFile(fileDistkNNQ, "# VP-tree\n", rMeasurekNNQ, 1);
      //Disc Access
      WriteToFile(fileDiscRQ, "# VP-tree\n", rMeasureRQ, 2);
      WriteToFile(fileDisckNNQ, "# VP-tree\n", rMeasurekNNQ, 2);
      //Total Time
      WriteToFile(fileTimeRQ, "# VP-tree\n", rMeasureRQ, 3);
      WriteToFile(fileTimekNNQ, "# VP-tree\n", rMeasurekNNQ, 3);
      // Reset the statistics.
      rMeasureRQ->Reset();
      rMeasurekNNQ->Reset();
   }//end if


   for (int i = 0; i < NUMBEROFTREES; i++){
      if (MetricTreeMM[i]){
         // queries for MM-Tree
         cout << "\nStarting Statistics for Range Query with MMTree-" << i << ".... ";
         PerformRangeQuery(rMeasureRQ, MetricTreeMM[i], PageManagerMM[i]);
         cout << " Ok\n";

         cout << "\nStarting Statistics for Nearest Query with MMTree-" << i << ".... ";
         PerformNearestQuery(rMeasurekNNQ, MetricTreeMM[i], PageManagerMM[i]);
         cout << " Ok\n";

         //write the statistics to files
         strcpy(name, "# MMTree-");
         strcat(name, itoa(i, strTmp, 10));
         strcat(name, "\n");

         //Distance Function
         WriteToFile(fileDistRQ, name, rMeasureRQ, 1);
         WriteToFile(fileDistkNNQ, name, rMeasurekNNQ, 1);
         //Disc Access
         WriteToFile(fileDiscRQ, name, rMeasureRQ, 2);
         WriteToFile(fileDisckNNQ, name, rMeasurekNNQ, 2);
         //Total Time
         WriteToFile(fileTimeRQ, name, rMeasureRQ, 3);
         WriteToFile(fileTimekNNQ, name, rMeasurekNNQ, 3);

         //Reset the statistics.
         rMeasureRQ->Reset();
         rMeasurekNNQ->Reset();
       }//end if
   }//end for

   fwrite(pause, strlen(pause), 1, fileDiscRQ);
   fwrite(pause, strlen(pause), 1, fileDistRQ);
   fwrite(pause, strlen(pause), 1, fileTimeRQ);
   fwrite(pause, strlen(pause), 1, fileDisckNNQ);
   fwrite(pause, strlen(pause), 1, fileDistkNNQ);
   fwrite(pause, strlen(pause), 1, fileTimekNNQ);

   // close files.
   fclose(fileDistRQ);
   fclose(fileDiscRQ);
   fclose(fileTimeRQ);
   fclose(fileDistkNNQ);
   fclose(fileDisckNNQ);
   fclose(fileTimekNNQ);

   //cleaning...
   delete rMeasurekNNQ;
   delete rMeasureRQ;
   
}//end TApp::PerformQuery

//------------------------------------------------------------------------------
void TApp::PerformRangeQuery(ResultMeasure * rMeasure, MetricTree * metricTree,
                             stPageManager * pageManager){

   myResult * result;
   TCity * sample;
   clock_t start, end;
   int i, j;
   
   if (metricTree){
      //For number of points (radius) that we want to measure.
      for (i=0; i < rMeasure->getSize(); i++){

         //reset the statistics
         pageManager->ResetStatistics();
         metricTree->GetMetricEvaluator()->ResetStatistics();

         start = clock();
         for (j=0; j < queryCities.size(); j++){
            sample = new TCity(queryCities[j]->GetName().c_str(),
                               queryCities[j]->GetLatitude(),
                               queryCities[j]->GetLongitude());
            result = metricTree->RangeQuery(sample, rMeasure->GetK(i)*42);
            delete result;
            delete sample;
         }//end for
         end = clock();

         rMeasure->setTotalTime(i, end-start);

         // is divided for queryCities to get the everage
         rMeasure->setDiscAccess(i, (double )pageManager->GetReadCount() / (double )queryCities.size());

         // is divided for queryCities to get the everage
         rMeasure->setDistanceFunction(i,
            (double )metricTree->GetMetricEvaluator()->GetDistanceCount() / (double )queryCities.size());

         cout << " " << i;
      }//end for
   }//end if

}//end TApp::PerformRangeQuery


//------------------------------------------------------------------------------
void TApp::PerformNearestQuery(ResultMeasureDiscrete * rMeasure, MetricTree * metricTree,
                               stPageManager * pageManager){

   myResult * result;
   myResult * result2;
   TCity * sample;
   clock_t start, end;
   int i, j;

   if (metricTree){
      //For number of points (radius) that I want measure.
      for (i=0; i < rMeasure->getSize(); i++){

         //reset the statistics for Slim
         pageManager->ResetStatistics();
         metricTree->GetMetricEvaluator()->ResetStatistics();
         start = clock();
         for (j=0; j < queryCities.size(); j++){
            sample = new TCity(queryCities[j]->GetName().c_str(),
                               queryCities[j]->GetLatitude(),
                               queryCities[j]->GetLongitude());
            result = metricTree->NearestQuery(sample, (int) rMeasure->GetK(i));
            delete result;
            delete sample;
         }//end for
         end = clock();
         rMeasure->setTotalTime(i, end-start);
         // is divided for queryCities to get the everage
         rMeasure->setDiscAccess(i, (double )pageManager->GetReadCount() / (double )queryCities.size());
         // is divided for queryCities to get the everage
         rMeasure->setDistanceFunction(i,
            (double )metricTree->GetMetricEvaluator()->GetDistanceCount() / (double )queryCities.size());

         cout << i << " ";
      }//end for
   }//end if

}//end TApp::PerformNearestQuery

//------------------------------------------------------------------------------
void TApp::WriteToFile(FILE * file, char * algName, Measure * rMeasure, int type){
   char * strTemp = new char[500];
   char * string = new char[50];

   fprintf(file, "%s", algName);
   //write the statistics to files
   for(int i=0; i < rMeasure->getSize(); i++){
      fprintf(file, "%f", rMeasure->GetK(i));
      strcpy(strTemp, "\t");
      fwrite(strTemp, strlen(strTemp), 1, file);
      if (type==1)
         fprintf(file, "%f", rMeasure->getDistanceFunction(i));
      else if (type==2)
         fprintf(file, "%f", rMeasure->getDiscAccess(i));
      else
         fprintf(file, "%ld", rMeasure->getTotalTime(i));
      strcpy(strTemp, "\n");
      fwrite(strTemp, strlen(strTemp), 1, file);
   }//end for
   strcpy(strTemp, "end\n");
   fwrite(strTemp, strlen(strTemp), 1, file);

   delete strTemp;
   delete string;
}//end TApp::WriteToFile()

//------------------------------------------------------------------------------
void TApp::WriteHeader(FILE * file, char * type, bool range){
   char * strTemp = new char[500];
   char pageSize[10];
   char tmpString[10];
   char number[11];

   itoa(this->PageSize, pageSize, 10);

   if (range){
      strcpy(strTemp,"set title \"RQ: Cidades\"");
   }else{
      strcpy(strTemp,"set title \"kNNQ: Cidades\"");
   }//end if

   fwrite(strTemp, strlen(strTemp), 1, file);
   strcpy(strTemp,"\nset xlabel \"k\"\n");
   fwrite(strTemp, strlen(strTemp), 1, file);
   strcpy(strTemp, type);
   fwrite(strTemp, strlen(strTemp), 1, file);

   //Plotting
   strcpy(strTemp, "plot ");
   fwrite(strTemp, strlen(strTemp), 1, file);

   //for SlimTree
   if (MetricTreeSlimMST){
      strcpy(strTemp, "'-' title 'Slim-Tree MST' with linespoints 1, ");
      fwrite(strTemp, strlen(strTemp), 1, file);
   }//end if

   if (MetricTreeGH){
      strcpy(strTemp, "'-' title 'GH-Tree' with linespoints 2, ");
      fwrite(strTemp, strlen(strTemp), 1, file);
   }//end if

   if (MetricTreeVP){
      strcpy(strTemp, "'-' title 'VP-Tree' with linespoints 3 ");
      fwrite(strTemp, strlen(strTemp), 1, file);
   }//end if


   //for MMTree
   for (int i = 0; i < NUMBEROFTREES; i++){
      if (MetricTreeMM[i]){
         strcpy(strTemp, ", '-' title 'MM-Tree ");
         strcat(strTemp, itoa(i, number, 10));
         strcat(strTemp, "' with linespoints ");
         strcat(strTemp, itoa(i+4, number, 10));
         fwrite(strTemp, strlen(strTemp), 1, file);
      }//end if
   }//end for
   
   strcpy(strTemp, "\n\n");
   fwrite(strTemp, strlen(strTemp), 1, file);
   strcpy(strTemp,"####################\n");
   fwrite(strTemp, strlen(strTemp), 1, file);
   
   delete strTemp;
}//end TApp::WriteHeader()
