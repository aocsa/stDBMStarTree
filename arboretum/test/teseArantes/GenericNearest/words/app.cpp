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
void TApp::Init(unsigned int pageSize,
                unsigned int startK, unsigned int quantidadeK,
                char * tieList, char * prefix){
   this->PageSize = pageSize;
   this->StartK = startK;
   this->QuantidadeK = quantidadeK;

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

   // create for Dummy-tree
   MetricTreeDummy = new myDummyTree(PageManagerDummy);
}//end TApp::CreateTree

//------------------------------------------------------------------------------
void TApp::Run(char * DataPath, char * DataQueryPath){
   // Lets load the tree with a lot values from the file.
   cout << "Adding objects in the MetricTreeSlim\n";
   LoadTree(DataPath, MetricTreeSlim);
   cout << "Adding objects in the MetricTreeDummy\n";
   LoadTree(DataPath, MetricTreeDummy);
   // Write information of trees.
   //WriteStats();
   // Lets do the queries
   cout << "Adding query objects ...\n";
   LoadVectorFromFile(DataQueryPath);
   // Do 500 queries.
   PerformQueries();
   // Hold the screen.
   cout << "Finished the whole test!\n";
}//end TApp::Run

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
void TApp::WriteStats(){
   char pageSizeString[10];
   char fileName[50];
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
      cout << "\nWriting statistics for Slim-tree";
      // Write statistics.
      WriteStat(fileStats);
      cout << "\nDone!";
      // close the file
      fclose(fileStats);
   }//end if

}//end WriteStats

//------------------------------------------------------------------------------
void TApp::WriteStat(FILE * file){
   char strTemp[500];

   if (MetricTreeSlim){
      // Get the information about the tree.
      stTreeInfoResult * infoResult = MetricTreeSlim->GetTreeInfo();
      strcpy(strTemp, "\nHeight: ");
      fwrite(strTemp, strlen(strTemp), 1, file);
      fprintf(file, "%d", infoResult->GetHeight());
      strcpy(strTemp, "\nObjs Count: ");
      fwrite(strTemp, strlen(strTemp), 1, file);
      fprintf(file, "%d", infoResult->GetObjectCount());
      strcpy(strTemp, "\nMaximum Entries per Node: ");
      fwrite(strTemp, strlen(strTemp), 1, file);
      fprintf(file, "%d", MetricTreeSlim->GetMaxOccupation());
      strcpy(strTemp, "\nMinimum Occupation per Node: ");
      fwrite(strTemp, strlen(strTemp), 1, file);
      fprintf(file, "%f", MetricTreeSlim->GetMinOccupation());
      strcpy(strTemp, "\nPage Count: ");
      fwrite(strTemp, strlen(strTemp), 1, file);
      fprintf(file, "%d", MetricTreeSlim->GetNodeCount());
      strcpy(strTemp, "\nPage size: ");
      fwrite(strTemp, strlen(strTemp), 1, file);
      fprintf(file, "%d", MetricTreeSlim->GetPageManager()->GetMinimumPageSize());
      strcpy(strTemp, "\nMean Object Size: ");
      fwrite(strTemp, strlen(strTemp), 1, file);
      fprintf(file, "%f", infoResult->GetMeanObjectSize());

      delete infoResult;
   }//end if
}//end WriteStat

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
            printf("Cannot open input file!\n\n");
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
void TApp::LoadVectorFromFile(char * fileName){
   FILE * file;
   int contObj = 0;
   char buffer[200], word[200];
   char * ptr;

   if ((file = fopen(fileName, "r")) == NULL){
      printf("Cannot open input file!\n\n");
   }else{
      fgets(buffer, 200, file);
      do{
         strcpy(word, buffer);
         ptr = strchr(word, '\n');
         *ptr = '\0';
         queryObjects.insert(queryObjects.end(), new TWord(word));
         fgets(buffer, 200, file);
         contObj++;
      }while(!feof(file));//end while
      cout << "Added " << contObj << " objects...\n";
      fclose(file);
   }//end else
}//end TApp::LoadVectorFromFile

//------------------------------------------------------------------------------
void TApp::PerformQueries(){
   char pause[] = "\npause -1";
   char pageSizeString[10];
   char fileName[50];
   char tmpString[50];
   FILE * fileDistFunc, * fileTime, * fileDiscAccess;

   //for the result of the tests
   ResultMeasureDiscrete * rMeasureSlim  = new ResultMeasureDiscrete(this->QuantidadeK);
   ResultMeasureDiscrete * rMeasureSlimInter  = new ResultMeasureDiscrete(this->QuantidadeK);
   ResultMeasureDiscrete * rMeasureDummy  = new ResultMeasureDiscrete(this->QuantidadeK);
   ResultMeasureDiscrete * rMeasureDummyInter = new ResultMeasureDiscrete(this->QuantidadeK);

   itoa(this->PageSize, pageSizeString, 10);

   // distance function
   strcpy(fileName, this->Prefix.c_str());
   strcat(fileName, "Dist_");
   strcat(fileName, pageSizeString);
   strcat(fileName, ".plt");
   fileDistFunc = fopen(fileName, "w");
   WriteHeader(fileDistFunc, "set ylabel \"Nro. Médio de Cálculo de Distância\"\n");
   // disc access
   strcpy(fileName, this->Prefix.c_str());
   strcat(fileName, "Disc_");
   strcat(fileName, pageSizeString);
   strcat(fileName, ".plt");
   fileDiscAccess = fopen(fileName, "w");
   WriteHeader(fileDiscAccess, "set ylabel \"Nro. Médio de Acesso a Disco\"\n");
   // time
   strcpy(fileName, this->Prefix.c_str());
   strcat(fileName, "Time_");
   strcat(fileName, pageSizeString);
   strcat(fileName, ".plt");
   fileTime = fopen(fileName, "w");
   WriteHeader(fileTime, "set ylabel \"Tempo Total (s)\"\n");

   cout << "\nStarting Statistics for Nearest Query.... ";
   NearestQuery(rMeasureSlim, rMeasureDummy);
   cout << " Ok\n";

   cout << "\nStarting Statistics for NearestIntersectionRange Query.... ";
   NearestIntersectionQuery(rMeasureSlimInter, rMeasureDummyInter);
   cout << " Ok\n";

   // Slim:Nearest
   WriteToFile(fileDistFunc, "# SlimTree-Nearest\n", rMeasureSlim, 1);
   WriteToFile(fileDiscAccess, "# SlimTree-Nearest\n", rMeasureSlim, 2);
   WriteToFile(fileTime, "# SlimTree-Nearest\n", rMeasureSlim, 3);
   // Slim:NearestIntersection
   WriteToFile(fileDistFunc, "# SlimTree-NearestIntersection\n", rMeasureSlimInter, 1);
   WriteToFile(fileDiscAccess, "# SlimTree-RangeIntersection\n", rMeasureSlimInter, 2);
   WriteToFile(fileTime, "# SlimTree-RangeIntersection\n", rMeasureSlimInter, 3);

   // Dummy:Nearest
   WriteToFile(fileDistFunc, "# SeqScan-Nearest\n", rMeasureDummy, 1);
   WriteToFile(fileDiscAccess, "# SeqScan-Nearest\n", rMeasureDummy, 2);
   WriteToFile(fileTime, "# SeqScan-Nearest\n", rMeasureDummy, 3);
   // Dummy:NearestIntersection
   WriteToFile(fileTime, "# SeqScan-NearestIntersection\n", rMeasureDummyInter, 3);
   WriteToFile(fileDistFunc, "# SeqScan-NearestIntersection\n", rMeasureDummyInter, 1);
   WriteToFile(fileDiscAccess, "# SeqScan-IntersectionNearest\n", rMeasureDummyInter, 2);

   // write the pause string.
   fwrite(pause, strlen(pause), 1, fileDistFunc);
   fwrite(pause, strlen(pause), 1, fileDiscAccess);
   fwrite(pause, strlen(pause), 1, fileTime);
   //close the files
   fclose(fileDistFunc);
   fclose(fileTime);
   fclose(fileDiscAccess);

   //cleaning...
   delete rMeasureSlim;
   delete rMeasureSlimInter;
   delete rMeasureDummy;
   delete rMeasureDummyInter;
}//end TApp::PerformQuery

//------------------------------------------------------------------------------
void TApp::NearestQuery(ResultMeasureDiscrete * rMeasureSlim, ResultMeasureDiscrete * rMeasureDummy){

   myResult * result, * finalResult;
   clock_t start, end;
   unsigned int i, j;
   long outerK, innerK;
   int size = queryObjects.size();

   //For number of points (radius) that I want to measure.
   for (i = 0; i < rMeasureSlim->getSize(); i++){
      outerK = i + 1;
      innerK = ceil(0.7 * outerK);

      PageManagerSlim->ResetStatistics();
      PageManagerDummy->ResetStatistics();
      MetricTreeSlim->GetMetricEvaluator()->ResetStatistics();
      MetricTreeDummy->GetMetricEvaluator()->ResetStatistics();

      start = clock();
      for (j = 0; j < size; j++){
         result = MetricTreeSlim->NearestQuery(queryObjects[j], outerK, this->TieList);
         finalResult = new myResult();
         // select the final result.
         for (int w = innerK; w < outerK; w++){
            finalResult->AddPair((TWord *)(*result)[w].GetObject()->Clone(), (*result)[w].GetDistance());
         }//end if
         delete finalResult;
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
         result = MetricTreeDummy->NearestQuery(queryObjects[j], outerK, this->TieList);
         finalResult = new myResult();
         // select the final result.
         for (int w = outerK - innerK; w < outerK; w++){
            finalResult->AddPair((TWord *)(*result)[w].GetObject()->Clone(), (*result)[w].GetDistance());
         }//end if
         delete finalResult;
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

}//end TApp::NearestQuery

//------------------------------------------------------------------------------
void TApp::NearestIntersectionQuery(ResultMeasureDiscrete * rMeasureSlim, ResultMeasureDiscrete * rMeasureDummy){

   myResult * result1, * result2, * finalResult;
   clock_t start, end;
   unsigned int i, j;
   long outerK, innerK;
   long numberOfObjects = MetricTreeSlim->GetNumberOfObjects();
   int size = queryObjects.size();

   //For number of points (radius) that I want to measure.
   for (i = 0; i < rMeasureSlim->getSize(); i++){
      outerK = i + 1;
      innerK = ceil(0.7 * outerK);

      PageManagerSlim->ResetStatistics();
      PageManagerDummy->ResetStatistics();
      MetricTreeSlim->GetMetricEvaluator()->ResetStatistics();
      MetricTreeDummy->GetMetricEvaluator()->ResetStatistics();

      start = clock();
      for (j = 0; j < size; j++){
         result1 = MetricTreeSlim->NearestQuery(queryObjects[j], outerK, this->TieList);
         result2 = MetricTreeSlim->FarthestQuery(queryObjects[j], (numberOfObjects - innerK), this->TieList);
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
         result1 = MetricTreeDummy->NearestQuery(queryObjects[j], outerK, this->TieList);
         result2 = MetricTreeDummy->FarthestQuery(queryObjects[j], (numberOfObjects - innerK), this->TieList);
         finalResult = new myResult();
         //result1 intersection result2
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

}//end TApp::NearestIntersectionQuery

//------------------------------------------------------------------------------
void TApp::WriteToFile(FILE * file, char * algName, ResultMeasureDiscrete * rMeasure, int type){
   char * strTemp = new char[500];
   char * string = new char[50];
   unsigned int i;

   fprintf(file, "%s", algName);
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
}//end TApp::WriteToFile

//----------------------------------------------------------------------------
void TApp::WriteHeader(FILE * file, char * type){
   char strTemp[500];
   char pageSize[10];
   char tmpString[10];

   itoa(this->PageSize, pageSize, 10);

   strcpy(strTemp,"set title \"Conjunto de Dados: Words");
   fwrite(strTemp, strlen(strTemp), 1, file);
   strcpy(strTemp,"  page=");
   fwrite(strTemp, strlen(strTemp), 1, file);
   fwrite(pageSize, strlen(pageSize), 1, file);
   strcpy(strTemp,"\"\nset logscale y");
   strcat(strTemp,"\nset xlabel \"k\"\n");
   fwrite(strTemp, strlen(strTemp), 1, file);
   strcpy(strTemp, type);
   fwrite(strTemp, strlen(strTemp), 1, file);

   strcpy(strTemp, "plot '-' title '(A) Slim-Tree: GenericNearest' with linespoints lt 1 lw 2 pt 1, ");
   strcat(strTemp, "'-' title '(B) Slim-Tree: Basic Nearest' with linespoints lt 8 lw 2 pt 3, ");
   fwrite(strTemp, strlen(strTemp), 1, file);
   strcpy(strTemp, "'-' title '(C) SeqScan: GenericNearest' with linespoints lt 3 lw 2 pt 2, ");
   strcat(strTemp, "'-' title '(D) SeqScan: Basic Nearest' with linespoints lt 6 lw 2 pt 6\n\n");
   fwrite(strTemp, strlen(strTemp), 1, file);

   strcpy(strTemp,"####################\n");
   fwrite(strTemp, strlen(strTemp), 1, file);

}//end TApp::WriteHeader
