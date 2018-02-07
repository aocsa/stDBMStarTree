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
void TApp::Init(unsigned int pageSize, stDistance maxDistance,
                unsigned int startK, unsigned int quantidadeK,
                unsigned int startRange, unsigned int quantidadeRange,
                char * tieList, char * prefix){
   this->PageSize = pageSize;
   if (startK > 1){
      this->StartK = startK;
   }else{
      this->StartK = 1;
   }//end if
   this->QuantidadeK = quantidadeK;
   this->StartRange = startRange;
   this->QuantidadeRange = quantidadeRange;
   this->MaxDistance = maxDistance;

   if (!strcmp(tieList, "true")){
      this->TieList = true;
   }else{
      this->TieList = false;
   }//end if
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
   MetricTreeSlim = new mySlimTree(PageManagerSlim);
   MetricTreeSlim->SetSplitMethod(mySlimTree::smSPANNINGTREE);
   MetricTreeSlim->SetChooseMethod(mySlimTree::cmMINDIST);

   // create for DB-tree
   MetricTreeDummy = new myDummyTree(PageManagerDummy);
}//end TApp::CreateTree

//------------------------------------------------------------------------------
void TApp::Run(char * DataPath, char * DataQueryPath){
   // Lets load the tree with a lot values from the file.
   cout << "Adding objects in the MetricTreeSlim\n";
   LoadTree(DataPath, MetricTreeSlim);
   cout << "Adding objects in the MetricTreeDummy\n";
   LoadTree(DataPath, MetricTreeDummy);
   // Lets do the queries
   cout << "Adding query objects ...\n";
   LoadVectorFromFile(DataQueryPath);
   // Writing the statistics of all trees.
   //WriteStats();
   // Do 500 queries.
   PerformQueries();
   // Hold the screen.
   cout << "Finished the whole test!\n";
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
      WriteStat(fileStats, "MetricTreeDummy", MetricTreeDummy);
      cout << "\nDone for MetricTreeDummy.";
      WriteStat(fileStats, "MetricTreeSlim", MetricTreeSlim);
      cout << "\nDone for MetricTreeSlim.";
      // close the file
      fclose(fileStats);
   }//end if

}//end WriteStats

//------------------------------------------------------------------------------
void TApp::WriteStat(FILE * file, char * treeName, MetricTree * metricTree){
   char strTemp[500];

   if (metricTree){
      // Get the information about the tree.
      stTreeInfoResult * infoResult = metricTree->GetTreeInfo();
      strcpy(strTemp, "\n\n");
      strcat(strTemp, treeName);
      fwrite(strTemp, strlen(strTemp), 1, file);
      strcpy(strTemp, "\n\tHeight: ");
      fwrite(strTemp, strlen(strTemp), 1, file);
      if (infoResult){
         fprintf(file, "%d", infoResult->GetHeight());
      }else{
         strcpy(strTemp, "0");
         fwrite(strTemp, strlen(strTemp), 1, file);
      }//end if
      strcpy(strTemp, "\n\tObjs Count: ");
      fwrite(strTemp, strlen(strTemp), 1, file);
      if (infoResult){
         fprintf(file, "%d", infoResult->GetObjectCount());
      }else{
         fprintf(file, "%d", metricTree->GetNumberOfObjects());
      }//end if
      strcpy(strTemp, "\n\tMaximum Entries per Node: ");
      fwrite(strTemp, strlen(strTemp), 1, file);
      fprintf(file, "%d", metricTree->GetMaxOccupation());
      strcpy(strTemp, "\n\tMinimum Occupation per Node: ");
      fwrite(strTemp, strlen(strTemp), 1, file);
      fprintf(file, "%f", metricTree->GetMinOccupation());
      strcpy(strTemp, "\n\tPage Count: ");
      fwrite(strTemp, strlen(strTemp), 1, file);
      fprintf(file, "%d", metricTree->GetNodeCount());
      strcpy(strTemp, "\n\tPage size: ");
      fwrite(strTemp, strlen(strTemp), 1, file);
      fprintf(file, "%d", metricTree->GetPageManager()->GetMinimumPageSize());
      if (infoResult){
         strcpy(strTemp, "\n\tMean Object Size: ");
         fwrite(strTemp, strlen(strTemp), 1, file);
         fprintf(file, "%f", infoResult->GetMeanObjectSize());

         delete infoResult;
      }//end if
   }//end if
}//end WriteStat

//------------------------------------------------------------------------------
void TApp::Done(){

   if (this->MetricTreeSlim != NULL){
      delete this->MetricTreeSlim;
   }//end if
   if (this->MetricTreeDummy != NULL){
      delete this->MetricTreeDummy;
   }//end if

   if (this->PageManagerSlim != NULL){
      delete this->PageManagerSlim;
   }//end if
   if (this->PageManagerDummy != NULL){
      delete this->PageManagerDummy;
   }//end if

   // delete the vetor of queries.
   for (unsigned int i = 0; i < queryObjects.size(); i++){
      delete (queryObjects.at(i));
   }//end for
}//end TApp::Done

//------------------------------------------------------------------------------
void TApp::LoadTree(char * fileName, MetricTree * metricTree){
   ifstream in(fileName);
   char cityName[200];
   double dLat, dLong;

   if (metricTree != NULL){
      // Is there any object?
      if (metricTree->GetNumberOfObjects() == 0){
         if (in.is_open()){
            cout << "\nLoading objects...";
            while ((in.getline(cityName, 200, '\t'))){
               in >> dLat;
               in >> dLong;
               in.ignore();
               this->AddToTree(cityName, dLat, dLong, metricTree);
            }//end while
            cout << " Added " << metricTree->GetNumberOfObjects() << " objects...";
            in.close();
            cout << "Performing the Slim-Down Algorithm\n";
            metricTree->Optimize();
         }else{
            cout << "\nProblem to open the file.";
         }//end if
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
      cout << "\nLoading query objects...";
      cont = 0;
      while(in.getline(cityName, 200, '\t')){
         in >> dLat;
         in >> dLong;
         in.ignore();
         this->queryObjects.insert(queryObjects.end(), new TCity(cityName, dLat, dLong));
         cont++;
      }//end while
      cout << " Added " << cont << " query objects...";
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
   char tmpString[50];
   FILE * fileDistFunc, * fileTime, * fileDiscAccess;
   unsigned int idx;

   //for the result of the tests
   ResultMeasure * rMeasureSlimKAndR  = new ResultMeasure(this->QuantidadeRange);
   ResultMeasure * rMeasureSlimKOrR   = new ResultMeasure(this->QuantidadeRange);
   ResultMeasure * rMeasureSlimInter  = new ResultMeasure(this->QuantidadeRange);
   ResultMeasure * rMeasureSlimUnion  = new ResultMeasure(this->QuantidadeRange);
   ResultMeasure * rMeasureDummyKAndR = new ResultMeasure(this->QuantidadeRange);
   ResultMeasure * rMeasureDummyKOrR  = new ResultMeasure(this->QuantidadeRange);
   ResultMeasure * rMeasureDummyInter = new ResultMeasure(this->QuantidadeRange);
   ResultMeasure * rMeasureDummyUnion = new ResultMeasure(this->QuantidadeRange);

   itoa(this->PageSize, pageSizeString, 10);

   //set the radius of the objects
   //SetRadiusFromObjects(rMeasureSlimKAndR);
   if (this->MaxDistance <= 0){
      cout << "Calculating the radius from the sample queries.... ";
      this->MaxDistance = MetricTreeSlim->GetGreaterDistance();
      cout << MaxDistance;
      cout << " Ok\n";
   }//end if

   for (idx = this->StartK-1; idx < this->QuantidadeK; idx++){
      //set the name and the header of the file
      //for the AND clausure
      // distance function
      strcpy(fileName, this->Prefix.c_str());
      strcat(fileName, "Dist");
      sprintf(fileName+strlen(fileName), "%.4f", rMeasureSlimKAndR->getK(idx));
      strcat(fileName, "_");
      strcat(fileName, pageSizeString);
      strcat(fileName, ".plt");
      fileDistFunc = fopen(fileName, "w");
      WriteHeader(fileDistFunc, "set ylabel \"Nro. Médio de Cálculo de Distância\"\n", true, rMeasureSlimKAndR->getK(idx));
      // disc access
      strcpy(fileName, this->Prefix.c_str());
      strcat(fileName, "Disc");
      sprintf(fileName+strlen(fileName), "%.4f", rMeasureSlimKAndR->getK(idx));
      strcat(fileName, "_");
      strcat(fileName, pageSizeString);
      strcat(fileName, ".plt");
      fileDiscAccess = fopen(fileName, "w");
      WriteHeader(fileDiscAccess, "set ylabel \"Nro. Médio de Acesso a Disco\"\n", true, rMeasureSlimKAndR->getK(idx));
      // time
      strcpy(fileName, this->Prefix.c_str());
      strcat(fileName, "Time");
      sprintf(fileName+strlen(fileName), "%.4f", rMeasureSlimKAndR->getK(idx));
      strcat(fileName, "_");
      strcat(fileName, pageSizeString);
      strcat(fileName, ".plt");
      fileTime = fopen(fileName, "w");
      WriteHeader(fileTime, "set ylabel \"Tempo Total (s)\"\n", true, rMeasureSlimKAndR->getK(idx));

      cout << "\nTests with radius: " << rMeasureSlimKAndR->getK(idx) << "\n\n";

      cout << "\nStarting Statistics for kAndRange Query.... ";
      NearestAndRange(idx, rMeasureSlimKAndR, rMeasureDummyKAndR);
      cout << " Ok\n";

      cout << "\nStarting Statistics for NearestIntersectionRange Query.... ";
      NearestIntersectionRange(idx, rMeasureSlimInter, rMeasureDummyInter);
      cout << " Ok\n";

      cout << "\nStarting Statistics for kOrRange Query.... ";
      NearestOrRange(idx, rMeasureSlimKOrR, rMeasureDummyKOrR);
      cout << " Ok\n";

      cout << "\nStarting Statistics for NearestUnionRange Query.... ";
      NearestUnionRange(idx, rMeasureSlimUnion, rMeasureDummyUnion);
      cout << " Ok\n";

      // Slim:KAndRange
      WriteToFile(fileDistFunc, "# SlimTree-KAndRange\n", rMeasureSlimKAndR, 1);
      WriteToFile(fileDiscAccess, "# SlimTree-KAndRange\n", rMeasureSlimKAndR, 2);
      WriteToFile(fileTime, "# SlimTree-KAndRange\n", rMeasureSlimKAndR, 3);
      // Slim:Intersection
      WriteToFile(fileDistFunc, "# SlimTree-KIntersectionRange\n", rMeasureSlimInter, 1);
      WriteToFile(fileDiscAccess, "# SlimTree-KIntersectionRange\n", rMeasureSlimInter, 2);
      WriteToFile(fileTime, "# SlimTree-KIntersectionRange\n", rMeasureSlimInter, 3);
      // Slim:KOrRange
      WriteToFile(fileDistFunc, "# SlimTree-KORRange\n", rMeasureSlimKOrR, 1);
      WriteToFile(fileDiscAccess, "# SlimTree-KORRange\n", rMeasureSlimKOrR, 2);
      WriteToFile(fileTime, "# SlimTree-KORRange\n", rMeasureSlimKOrR, 3);
      // Slim:Union
      WriteToFile(fileDistFunc, "# SlimTree-KUnionRange\n", rMeasureSlimUnion, 1);
      WriteToFile(fileDiscAccess, "# SlimTree-KUnionRange\n", rMeasureSlimUnion, 2);
      WriteToFile(fileTime, "# SlimTree-KUnionRange\n", rMeasureSlimUnion, 3);

      // Dummy:KAndRange
      WriteToFile(fileDistFunc, "# SeqScan-KAndRange\n", rMeasureDummyKAndR, 1);
      WriteToFile(fileDiscAccess, "# SeqScan-KAndRange\n", rMeasureDummyKAndR, 2);
      WriteToFile(fileTime, "# SeqScan-KAndRange\n", rMeasureDummyKAndR, 3);
      // Dummy:Intersection
      WriteToFile(fileTime, "# SeqScan-KIntersectionRange\n", rMeasureDummyInter, 3);
      WriteToFile(fileDistFunc, "# SeqScan-KIntersectionRange\n", rMeasureDummyInter, 1);
      WriteToFile(fileDiscAccess, "# SeqScan-KIntersectionRange\n", rMeasureDummyInter, 2);
      // Dummy:KOrRange
      WriteToFile(fileDistFunc, "# SeqScan-KORRange\n", rMeasureDummyKOrR, 1);
      WriteToFile(fileDiscAccess, "# SeqScan-KORRange\n", rMeasureDummyKOrR, 2);
      WriteToFile(fileTime, "# SeqScan-KORRange\n", rMeasureDummyKOrR, 3);
      // Dummy:Union
      WriteToFile(fileDistFunc, "# SeqScan-KUnionRange\n", rMeasureDummyUnion, 1);
      WriteToFile(fileDiscAccess, "# SeqScan-KUnionRange\n", rMeasureDummyUnion, 2);
      WriteToFile(fileTime, "# SeqScan-KUnionRange\n", rMeasureDummyUnion, 3);

      // write the pause string.
      fwrite(pause, strlen(pause), 1, fileDistFunc);
      fwrite(pause, strlen(pause), 1, fileDiscAccess);
      fwrite(pause, strlen(pause), 1, fileTime);
      //close the files
      fclose(fileDistFunc);
      fclose(fileTime);
      fclose(fileDiscAccess);
      //increments the counter
   }//end for

   //cleaning...
   delete rMeasureSlimKAndR;
   delete rMeasureSlimInter;
   delete rMeasureSlimKOrR;
   delete rMeasureSlimUnion;
   delete rMeasureDummyKAndR;
   delete rMeasureDummyInter;
   delete rMeasureDummyKOrR;
   delete rMeasureDummyUnion;

}//end TApp::PerformQuery

//------------------------------------------------------------------------------
void TApp::NearestAndRange(unsigned int idx, ResultMeasure * rMeasureSlim, ResultMeasure * rMeasureDummy){

   myResult * result;
   clock_t start, end;
   unsigned int i, j;
   long numberOfObjects, k;
   stDistance radius;
   numberOfObjects = MetricTreeSlim->GetNumberOfObjects();
   int size = queryObjects.size();

   //For number of points (radius) that I want to measure.
   for (i = 0; i < rMeasureSlim->getSize(); i++){
      k = ceil(rMeasureSlim->getK(idx) * numberOfObjects);
      if (k > numberOfObjects){
         k = numberOfObjects;
      }//end if

      PageManagerSlim->ResetStatistics();
      PageManagerDummy->ResetStatistics();
      MetricTreeSlim->GetMetricEvaluator()->ResetStatistics();
      MetricTreeDummy->GetMetricEvaluator()->ResetStatistics();

      radius = this->MaxDistance * rMeasureSlim->getK(i);

      start = clock();
      for (j = 0; j < size; j++){
         result = MetricTreeSlim->KAndRangeQuery(queryObjects[j], radius, k, this->TieList);
         delete result;
      }//end for
      end = clock();
      //to return the average in ms
      rMeasureSlim->setTotalTime(i, ((double )end-(double )start) / CLK_TCK);
      rMeasureSlim->setDiskAccess(i, (double )PageManagerSlim->GetReadCount() / (double )size);
      rMeasureSlim->setDistanceFunction(i, (double )MetricTreeSlim->GetMetricEvaluator()->GetDistanceCount() /
                                           (double )size);

      start = clock();
      for (j = 0; j < size; j++){
         result = MetricTreeDummy->KAndRangeQuery(queryObjects[j], radius, k, this->TieList);
         delete result;
      }//end for
      end = clock();
      //to return the average in ms
      rMeasureDummy->setTotalTime(i, ((double )end-(double )start) / CLK_TCK);
      rMeasureDummy->setDiskAccess(i, (double )PageManagerDummy->GetReadCount() / (double )size);
      rMeasureDummy->setDistanceFunction(i, (double )MetricTreeDummy->GetMetricEvaluator()->GetDistanceCount() /
                                              (double )size);

      cout << i << " ";
   }//end for

}//end TApp::NearestAndRange

//------------------------------------------------------------------------------
void TApp::NearestOrRange(unsigned int idx, ResultMeasure * rMeasureSlim, ResultMeasure * rMeasureDummy){

   myResult * result;
   clock_t start, end;
   unsigned int i, j;
   long numberOfObjects, k;
   stDistance radius;
   numberOfObjects = MetricTreeSlim->GetNumberOfObjects();
   int size = queryObjects.size();

   //For number of points (radius) that I want measure.
   for (i = 0; i < rMeasureSlim->getSize(); i++){
      k = ceil(rMeasureSlim->getK(idx) * numberOfObjects);
      if (k > numberOfObjects){
         k = numberOfObjects;
      }//end if

      PageManagerSlim->ResetStatistics();
      PageManagerDummy->ResetStatistics();
      MetricTreeSlim->GetMetricEvaluator()->ResetStatistics();
      MetricTreeDummy->GetMetricEvaluator()->ResetStatistics();

      radius = this->MaxDistance * rMeasureSlim->getK(i);

      start = clock();
      for (j = 0; j < size; j++){
         result = MetricTreeSlim->KOrRangeQuery(queryObjects[j], radius, k, this->TieList);
         delete result;
      }//end for
      end = clock();
      //to return the average in ms
      rMeasureSlim->setTotalTime(i, ((double )end-(double )start) / CLK_TCK);
      rMeasureSlim->setDiskAccess(i, (double )PageManagerSlim->GetReadCount() / (double )size);
      rMeasureSlim->setDistanceFunction(i, (double )MetricTreeSlim->GetMetricEvaluator()->GetDistanceCount() /
                                           (double )size);

      start = clock();
      for (j = 0; j < size; j++){
         result = MetricTreeDummy->KOrRangeQuery(queryObjects[j], radius, k, this->TieList);
         delete result;
      }//end for
      end = clock();
      //to return the average in ms
      rMeasureDummy->setTotalTime(i, ((double )end-(double )start) / CLK_TCK);
      rMeasureDummy->setDiskAccess(i, (double )PageManagerDummy->GetReadCount() / (double )size);
      rMeasureDummy->setDistanceFunction(i, (double )MetricTreeDummy->GetMetricEvaluator()->GetDistanceCount() /
                                             (double )size);

      cout << i << " ";
   }//end for

}//end TApp::NearestOrRange

//------------------------------------------------------------------------------
void TApp::NearestIntersectionRange(unsigned int idx, ResultMeasure * rMeasureSlim, ResultMeasure * rMeasureDummy){

   myResult * result1, * result2, * finalResult;
   clock_t start, end;
   unsigned int i, j;
   long numberOfObjects, k;
   stDistance radius;
   numberOfObjects = MetricTreeSlim->GetNumberOfObjects();
   int size = queryObjects.size();

   for (i = 0; i < rMeasureSlim->getSize(); i++){
      k = ceil(rMeasureSlim->getK(idx) * numberOfObjects);
      if (k > numberOfObjects){
         k = numberOfObjects;
      }//end if

      PageManagerSlim->ResetStatistics();
      PageManagerDummy->ResetStatistics();
      MetricTreeSlim->GetMetricEvaluator()->ResetStatistics();
      MetricTreeDummy->GetMetricEvaluator()->ResetStatistics();

      radius = this->MaxDistance * rMeasureSlim->getK(i);
      start = clock();
      for (j = 0; j < size; j++){
         result1 = MetricTreeSlim->RangeQuery(queryObjects[j], radius);
         result2 = MetricTreeSlim->NearestQuery(queryObjects[j], k, this->TieList);
         finalResult = new myResult();
         //result1 intersection result2
         finalResult->Intersection(result1, result2);

         delete finalResult;
         delete result1;
         delete result2;
      }//end for
      end = clock();
      //to return the average in ms
      rMeasureSlim->setTotalTime(i, ((double )end-(double )start) / CLK_TCK);
      rMeasureSlim->setDiskAccess(i, (double )PageManagerSlim->GetReadCount() / (double )size);
      rMeasureSlim->setDistanceFunction(i, (double )MetricTreeSlim->GetMetricEvaluator()->GetDistanceCount() /
                                             (double )size);

      start = clock();
      for (j = 0; j < size; j++){
         result1 = MetricTreeDummy->RangeQuery(queryObjects[j], radius);
         result2 = MetricTreeDummy->NearestQuery(queryObjects[j], k, this->TieList);
         //result1 intersection result2
         finalResult = new myResult();
         finalResult->Intersection(result1, result2);

         delete finalResult;
         delete result1;
         delete result2;
      }//end for
      end = clock();
      //to return the average in ms
      rMeasureDummy->setTotalTime(i, ((double )end-(double )start) / CLK_TCK);
      rMeasureDummy->setDiskAccess(i, (double )PageManagerDummy->GetReadCount() / (double )size);
      rMeasureDummy->setDistanceFunction(i, (double )MetricTreeDummy->GetMetricEvaluator()->GetDistanceCount() /
                                             (double )size);

      cout << i << " ";
   }//end for

}//end TApp::NearestIntersectionRange

//------------------------------------------------------------------------------
void TApp::NearestUnionRange(unsigned int idx, ResultMeasure * rMeasureSlim, ResultMeasure * rMeasureDummy){

   myResult * result1, * result2, * finalResult;
   clock_t start, end;
   unsigned int i, j;
   long numberOfObjects, k;
   stDistance radius;
   numberOfObjects = MetricTreeSlim->GetNumberOfObjects();
   int size = queryObjects.size();

   for (i = 0; i < rMeasureSlim->getSize(); i++){
      k = ceil(rMeasureSlim->getK(idx) * numberOfObjects);
      if (k > numberOfObjects){
         k = numberOfObjects;
      }//end if

      PageManagerSlim->ResetStatistics();
      PageManagerDummy->ResetStatistics();
      MetricTreeSlim->GetMetricEvaluator()->ResetStatistics();
      MetricTreeDummy->GetMetricEvaluator()->ResetStatistics();

      radius = this->MaxDistance * rMeasureSlim->getK(i);
      start = clock();
      for (j = 0; j < size; j++){
         result1 = MetricTreeSlim->RangeQuery(queryObjects[j], radius);
         result2 = MetricTreeSlim->NearestQuery(queryObjects[j], k, this->TieList);
         //result1 union result2
         finalResult = new myResult();
         finalResult->Union(result1, result2);

         delete finalResult;
         delete result1;
         delete result2;
      }// end for
      end = clock();
      //to return the average in ms
      rMeasureSlim->setTotalTime(i, ((double )end-(double )start) / CLK_TCK);
      rMeasureSlim->setDiskAccess(i, (double )PageManagerSlim->GetReadCount() / (double )size);
      rMeasureSlim->setDistanceFunction(i, (double )MetricTreeSlim->GetMetricEvaluator()->GetDistanceCount() /
                                             (double )size);

      start = clock();
      for (j = 0; j < size; j++){
         result1 = MetricTreeDummy->RangeQuery(queryObjects[j], radius);
         result2 = MetricTreeDummy->NearestQuery(queryObjects[j], k, this->TieList);
         // result1 union result2
         finalResult = new myResult();
         finalResult->Union(result1, result2);

         delete finalResult;
         delete result1;
         delete result2;
      }// end for
      end = clock();
      //to return the average in ms
      rMeasureDummy->setTotalTime(i, ((double )end-(double )start) / CLK_TCK);
      rMeasureDummy->setDiskAccess(i, (double )PageManagerDummy->GetReadCount() / (double )size);
      rMeasureDummy->setDistanceFunction(i, (double )MetricTreeDummy->GetMetricEvaluator()->GetDistanceCount() /
                                             (double )size);

      cout << i << " ";
   }//end for

}//end TApp::NearestUnionRange

//------------------------------------------------------------------------------
void TApp::SetRadiusFromObjects(ResultMeasure * rMeasureSlim){

   myResult * result;
   long numberOfObjects;
   unsigned int i, j;

   //clear before insert new radium values
   for (i = 0; i < this->QuantidadeRange; i++){
      radiusqueryObjects[i].clear();
      // set the number of objects.
      numberOfObjects = ceil(rMeasureSlim->getK(i) * MetricTreeSlim->GetNumberOfObjects());
      if (numberOfObjects > MetricTreeSlim->GetNumberOfObjects()){
         numberOfObjects = MetricTreeSlim->GetNumberOfObjects();
      }//end if
      // perform the query.
      for (j = 0; j < queryObjects.size(); j++){
         result = MetricTreeSlim->NearestQuery(queryObjects[j], numberOfObjects);
         // set the radius.
         radiusqueryObjects[i].insert(radiusqueryObjects[i].end(), result->GetMaximumDistance());
         delete result;
      }//end for
      cout << " " << i;
   }//end for
}//end TApp::SetRadiusFromObjects

//------------------------------------------------------------------------------
void TApp::WriteToFile(FILE * file, char * algName, ResultMeasure * rMeasure, int type){
   char * strTemp = new char[500];
   char * string = new char[50];
   unsigned int i;

   fprintf(file, "%s", algName);
   //write the statistics to files
   for(i = 0; i < rMeasure->getSize(); i++){
      fprintf(file, "%f", rMeasure->getK(i));
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
}//end TApp::WriteToFile

//----------------------------------------------------------------------------
void TApp::WriteHeader(FILE * file, char * type, bool and, double radius){
   char strTemp[500];
   char pageSize[10];
   char tmpString[10];

   itoa(this->PageSize, pageSize, 10);

   strcpy(strTemp,"set title \"Conjunto de Dados: Cidades");
   fwrite(strTemp, strlen(strTemp), 1, file);
   strcpy(strTemp,"  page=");
   fwrite(strTemp, strlen(strTemp), 1, file);
   fwrite(pageSize, strlen(pageSize), 1, file);
   strcpy(strTemp,",  k=");
   fwrite(strTemp, strlen(strTemp), 1, file);
   fprintf(file, "%.4f", radius);
   strcpy(strTemp,"\"\nset logscale xy");
   strcat(strTemp,"\nset xlabel \"% raio\"\n");
   fwrite(strTemp, strlen(strTemp), 1, file);
   strcpy(strTemp, type);
   fwrite(strTemp, strlen(strTemp), 1, file);
   strcpy(strTemp, "set xrange [0.001:0.1]\n");
   fwrite(strTemp, strlen(strTemp), 1, file);

   strcpy(strTemp, "plot '-' title '(A) Slim-Tree: kAndRange' with linespoints lt 1 lw 2 pt 1, ");
   strcat(strTemp, "'-' title '(B) Slim-Tree: Nearest AND Range' with linespoints lt 6 lw 2 pt 3, ");
   strcat(strTemp, "'-' title '(C) Slim-Tree: kOrRange' with linespoints lt 3 lw 2 pt 2, ");
   strcat(strTemp, "'-' title '(D) Slim-Tree: Nearest OR Range' with linespoints lt 8 lw 2 pt 4, ");
   fwrite(strTemp, strlen(strTemp), 1, file);
   strcpy(strTemp, "'-' title '(E) SeqScan: kAndRange' with linespoints lt 2 lw 2 pt 5, ");
   strcat(strTemp, "'-' title '(F) SeqScan: Nearest AND Range' with linespoints lt 4 lw 2 pt 6, ");
   strcat(strTemp, "'-' title '(G) SeqScan: kOrRange' with linespoints lt 5 lw 2 pt 11, ");
   strcat(strTemp, "'-' title '(H) SeqScan: Nearest OR Range' with linespoints lt 6 lw 2 pt 8\n\n");
   fwrite(strTemp, strlen(strTemp), 1, file);

   strcpy(strTemp,"####################\n");
   fwrite(strTemp, strlen(strTemp), 1, file);

}//end TApp::WriteHeader
