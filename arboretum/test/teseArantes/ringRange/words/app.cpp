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
                unsigned int startRange, unsigned int quantidadeRange,
                stCount difference, char * prefix){
   this->PageSize = pageSize;
   this->StartRange = startRange;
   this->Difference = difference;
   this->QuantidadeRange = quantidadeRange;
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
   for (unsigned int i = 0; i < queryWords.size(); i++){
      delete (queryWords.at(i));
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
         queryWords.insert(queryWords.end(), new TWord(word));
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
   ResultMeasureDiscrete * rMeasureSlimRingRange  = new ResultMeasureDiscrete(this->QuantidadeRange);
   ResultMeasureDiscrete * rMeasureSlimRingRangeInter  = new ResultMeasureDiscrete(this->QuantidadeRange);
   ResultMeasureDiscrete * rMeasureSlimRange  = new ResultMeasureDiscrete(this->QuantidadeRange);
   ResultMeasureDiscrete * rMeasureDummyRingRange = new ResultMeasureDiscrete(this->QuantidadeRange);
   ResultMeasureDiscrete * rMeasureDummyRingRangeInter = new ResultMeasureDiscrete(this->QuantidadeRange);
   ResultMeasureDiscrete * rMeasureDummyRange = new ResultMeasureDiscrete(this->QuantidadeRange);

   itoa(this->PageSize, pageSizeString, 10);

   //set the name and the header of the file
   //for the AND clausure
   // distance function
   strcpy(fileName, this->Prefix.c_str());
   strcat(fileName, "Dist");
   sprintf(fileName + strlen(fileName), "%d", this->Difference);
   strcat(fileName, "_");
   strcat(fileName, pageSizeString);
   strcat(fileName, ".plt");
   fileDistFunc = fopen(fileName, "w");
   WriteHeader(fileDistFunc, "set ylabel \"Nro. Médio de Cálculo de Distância\"\n", true, this->Difference);
   // disc access
   strcpy(fileName, this->Prefix.c_str());
   strcat(fileName, "Disc");
   sprintf(fileName + strlen(fileName), "%d", this->Difference);
   strcat(fileName, "_");
   strcat(fileName, pageSizeString);
   strcat(fileName, ".plt");
   fileDiscAccess = fopen(fileName, "w");
   WriteHeader(fileDiscAccess, "set ylabel \"Nro. Médio de Acesso a Disco\"\n", true, this->Difference);
   // time
   strcpy(fileName, this->Prefix.c_str());
   strcat(fileName, "Time");
   sprintf(fileName + strlen(fileName), "%d", this->Difference);
   strcat(fileName, "_");
   strcat(fileName, pageSizeString);
   strcat(fileName, ".plt");
   fileTime = fopen(fileName, "w");
   WriteHeader(fileTime, "set ylabel \"Tempo Total (s)\"\n", true, this->Difference);

   cout << "\nStarting Statistics for RingRange Query.... ";
   RingRange(rMeasureSlimRingRange, rMeasureDummyRingRange);
   cout << " Ok\n";

   cout << "\nStarting Statistics for RingRange Intersection Query.... ";
   RingRangeIntersection(rMeasureSlimRingRangeInter, rMeasureDummyRingRangeInter);
   cout << " Ok\n";

   cout << "\nStarting Statistics for Range Query.... ";
   Range(rMeasureSlimRange, rMeasureDummyRange);
   cout << " Ok\n";

   // Slim:RingRange
   WriteToFile(fileDistFunc, "# SlimTree-RingRange\n", rMeasureSlimRingRange, 1);
   WriteToFile(fileDiscAccess, "# SlimTree-RingRange\n", rMeasureSlimRingRange, 2);
   WriteToFile(fileTime, "# SlimTree-RingRange\n", rMeasureSlimRingRange, 3);
   // Slim:RingRange Intersection
   WriteToFile(fileDistFunc, "# SlimTree-RingRange Intersection\n", rMeasureSlimRingRangeInter, 1);
   WriteToFile(fileDiscAccess, "# SlimTree-RingRange Intersection\n", rMeasureSlimRingRangeInter, 2);
   WriteToFile(fileTime, "# SlimTree-RingRange Intersection\n", rMeasureSlimRingRangeInter, 3);
   // Slim:Range
   WriteToFile(fileDistFunc, "# SlimTree-Range\n", rMeasureSlimRange, 1);
   WriteToFile(fileDiscAccess, "# SlimTree-Range\n", rMeasureSlimRange, 2);
   WriteToFile(fileTime, "# SlimTree-Range\n", rMeasureSlimRange, 3);

   // Dummy:RingRange
   WriteToFile(fileDistFunc, "# SeqScan-RingRange\n", rMeasureDummyRingRange, 1);
   WriteToFile(fileDiscAccess, "# SeqScan-RingRange\n", rMeasureDummyRingRange, 2);
   WriteToFile(fileTime, "# SeqScan-RingRange\n", rMeasureDummyRingRange, 3);
   // Dummy:RingRange Intersection
   WriteToFile(fileDistFunc, "# SeqScan-RingRange Intersection\n", rMeasureDummyRingRangeInter, 1);
   WriteToFile(fileDiscAccess, "# SeqScan-RingRange Intersection\n", rMeasureDummyRingRangeInter, 2);
   WriteToFile(fileTime, "# SeqScan-RingRange Intersection\n", rMeasureDummyRingRangeInter, 3);
   // Dummy:Range
   WriteToFile(fileDistFunc, "# SeqScan-Range\n", rMeasureDummyRange, 1);
   WriteToFile(fileDiscAccess, "# SeqScan-Range\n", rMeasureDummyRange, 2);
   WriteToFile(fileTime, "# SeqScan-Range\n", rMeasureDummyRange, 3);

   // write the pause string.
   fwrite(pause, strlen(pause), 1, fileDistFunc);
   fwrite(pause, strlen(pause), 1, fileDiscAccess);
   fwrite(pause, strlen(pause), 1, fileTime);
   //close the files
   fclose(fileDistFunc);
   fclose(fileTime);
   fclose(fileDiscAccess);

   //cleaning...
   delete rMeasureSlimRingRange;
   delete rMeasureSlimRingRangeInter;
   delete rMeasureSlimRange;
   delete rMeasureDummyRingRange;
   delete rMeasureDummyRingRangeInter;
   delete rMeasureDummyRange;

}//end TApp::PerformQuery

//------------------------------------------------------------------------------
void TApp::RingRange(ResultMeasureDiscrete * rMeasureSlim, ResultMeasureDiscrete * rMeasureDummy){

   myResult * result;
   clock_t start, end;
   unsigned int i, j;
   stCount outerDistance;
   stCount innerDistance;

   //For number of points (radius) that I want to measure.
   for (i = 0; i < rMeasureSlim->getSize(); i++){
      // Set the radius.
      innerDistance = rMeasureSlim->getK(i);
      outerDistance = innerDistance + this->Difference;

      PageManagerSlim->ResetStatistics();
      PageManagerDummy->ResetStatistics();
      MetricTreeSlim->GetMetricEvaluator()->ResetStatistics();
      MetricTreeDummy->GetMetricEvaluator()->ResetStatistics();

      start = clock();
      for (j = 0; j < queryWords.size(); j++){
         result = MetricTreeSlim->RingQuery(queryWords[j], innerDistance, outerDistance);
         delete result;
      }//end for
      end = clock();
      //to return the average in ms
      rMeasureSlim->setTotalTime(i, ((double )end-(double )start) / CLK_TCK);
      rMeasureSlim->setDiskAccess(i, (double )PageManagerSlim->GetReadCount() / (double )queryWords.size());
      rMeasureSlim->setDistanceFunction(i, (double )MetricTreeSlim->GetMetricEvaluator()->GetDistanceCount() /
                                           (double )queryWords.size());

      start = clock();
      for (j = 0; j < queryWords.size(); j++){
         result = MetricTreeDummy->RingQuery(queryWords[j], innerDistance, outerDistance);
         delete result;
      }//end for
      end = clock();
      //to return the average in ms
      rMeasureDummy->setTotalTime(i, ((double )end-(double )start) / CLK_TCK);
      rMeasureDummy->setDiskAccess(i, (double )PageManagerDummy->GetReadCount() / (double )queryWords.size());
      rMeasureDummy->setDistanceFunction(i, (double )MetricTreeDummy->GetMetricEvaluator()->GetDistanceCount() /
                                              (double )queryWords.size());

      cout << i << " ";
   }//end for
}//end TApp::RingRange

//------------------------------------------------------------------------------
void TApp::RingRangeIntersection(ResultMeasureDiscrete * rMeasureSlim, ResultMeasureDiscrete * rMeasureDummy){

   myResult * result1, * result2, * finalResult;
   clock_t start, end;
   unsigned int i, j;
   stCount outerDistance;
   stCount innerDistance;

   //For number of points (radius) that I want to measure.
   for (i = 0; i < rMeasureSlim->getSize(); i++){
      // Set the radius.
      innerDistance = rMeasureSlim->getK(i);
      outerDistance = innerDistance + this->Difference;

      PageManagerSlim->ResetStatistics();
      PageManagerDummy->ResetStatistics();
      MetricTreeSlim->GetMetricEvaluator()->ResetStatistics();
      MetricTreeDummy->GetMetricEvaluator()->ResetStatistics();

      start = clock();
      for (j = 0; j < queryWords.size(); j++){
         result1 = MetricTreeSlim->RangeQuery(queryWords[j], innerDistance);
         result2 = MetricTreeSlim->RangeQuery(queryWords[j], outerDistance);
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
      rMeasureSlim->setDiskAccess(i, (double )PageManagerSlim->GetReadCount() / (double )queryWords.size());
      rMeasureSlim->setDistanceFunction(i, (double )MetricTreeSlim->GetMetricEvaluator()->GetDistanceCount() /
                                             (double )queryWords.size());

      start = clock();
      for (j = 0; j < queryWords.size(); j++){
         result1 = MetricTreeDummy->RangeQuery(queryWords[j], innerDistance);
         result2 = MetricTreeDummy->RangeQuery(queryWords[j], outerDistance);
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
      rMeasureDummy->setDiskAccess(i, (double )PageManagerDummy->GetReadCount() / (double )queryWords.size());
      rMeasureDummy->setDistanceFunction(i, (double )MetricTreeDummy->GetMetricEvaluator()->GetDistanceCount() /
                                             (double )queryWords.size());

      cout << i << " ";
   }//end for
}//end TApp::RingRangeIntersection

//------------------------------------------------------------------------------
void TApp::Range(ResultMeasureDiscrete * rMeasureSlim, ResultMeasureDiscrete * rMeasureDummy){

   myResult * result;
   clock_t start, end;
   unsigned int i, j;
   stCount outerDistance;

   //For number of points (radius) that I want to measure.
   for (i = 0; i < rMeasureSlim->getSize(); i++){
      // Set the radius.
      outerDistance = rMeasureSlim->getK(i) + this->Difference;

      PageManagerSlim->ResetStatistics();
      PageManagerDummy->ResetStatistics();
      MetricTreeSlim->GetMetricEvaluator()->ResetStatistics();
      MetricTreeDummy->GetMetricEvaluator()->ResetStatistics();

      start = clock();
      for (j = 0; j < queryWords.size(); j++){
         result = MetricTreeSlim->RangeQuery(queryWords[j], outerDistance);
         delete result;
      }//end for
      end = clock();
      //to return the average in ms
      rMeasureSlim->setTotalTime(i, ((double )end-(double )start) / CLK_TCK);
      rMeasureSlim->setDiskAccess(i, (double )PageManagerSlim->GetReadCount() / (double )queryWords.size());
      rMeasureSlim->setDistanceFunction(i, (double )MetricTreeSlim->GetMetricEvaluator()->GetDistanceCount() /
                                           (double )queryWords.size());

      start = clock();
      for (j = 0; j < queryWords.size(); j++){
         result = MetricTreeDummy->RangeQuery(queryWords[j], outerDistance);
         delete result;
      }//end for
      end = clock();
      //to return the average in ms
      rMeasureDummy->setTotalTime(i, ((double )end-(double )start) / CLK_TCK);
      rMeasureDummy->setDiskAccess(i, (double )PageManagerDummy->GetReadCount() / (double )queryWords.size());
      rMeasureDummy->setDistanceFunction(i, (double )MetricTreeDummy->GetMetricEvaluator()->GetDistanceCount() /
                                              (double )queryWords.size());

      cout << i << " ";
   }//end for
}//end TApp::Range

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
      if (type==1){
         fprintf(file, "%f", rMeasure->getDistanceFunction(i));
      }else if (type==2){
         fprintf(file, "%f", rMeasure->getDiskAccess(i));
      }else{
         fprintf(file, "%f", rMeasure->getTotalTime(i));
      }//end if
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

   strcpy(strTemp,"set title \"Conjunto de Dados: Words");
   fwrite(strTemp, strlen(strTemp), 1, file);
   strcpy(strTemp,"  page=");
   fwrite(strTemp, strlen(strTemp), 1, file);
   fwrite(pageSize, strlen(pageSize), 1, file);
   strcpy(strTemp,", ratio (outer/inner) =");
   fwrite(strTemp, strlen(strTemp), 1, file);
   fprintf(file, "%.2f", radius);
   strcpy(strTemp,"\"\nset logscale y");
   strcat(strTemp,"\nset xlabel \"% raio\"\n");
   fwrite(strTemp, strlen(strTemp), 1, file);
   strcpy(strTemp, type);
   fwrite(strTemp, strlen(strTemp), 1, file);

   strcpy(strTemp, "plot '-' title '(A) Slim-Tree: RingRange' with linespoints lt 1 lw 2 pt 1, ");
   strcat(strTemp, "'-' title '(B) Slim-Tree: Basic Ranges' with linespoints lt 6 lw 2 pt 3, ");
   strcat(strTemp, "'-' title '(C) Slim-Tree: Single Range' with linespoints lt 3 lw 2 pt 4, ");
   fwrite(strTemp, strlen(strTemp), 1, file);
   strcpy(strTemp, "'-' title '(D) SeqScan: RingRange' with linespoints lt 2 lw 2 pt 5, ");
   strcat(strTemp, "'-' title '(E) SeqScan: Basic Ranges' with linespoints lt 4 lw 2 pt 6, ");
   strcat(strTemp, "'-' title '(F) SeqScan: Single Range' with linespoints lt 5 lw 2 pt 2");
   fwrite(strTemp, strlen(strTemp), 1, file);

   strcpy(strTemp,"####################\n");
   fwrite(strTemp, strlen(strTemp), 1, file);
}//end TApp::WriteHeader
