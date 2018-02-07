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
void TApp::Init(unsigned int pageSize, stDistance maxDistance,
                unsigned int startRange, unsigned int quantidadeRange,
                double percentage, char * prefix){
   this->PageSize = pageSize;
   this->StartRange = startRange;
   this->Percentage = percentage;
   this->QuantidadeRange = quantidadeRange;
   this->MaxDistance = maxDistance;
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
   cout << "Performing the Slim-Down Algorithm\n";
   MetricTreeSlim->Optimize();
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
void TApp::LoadTree(char * fileName, MetricTree * metricTree){
   ifstream in(fileName);
   int i;
   long w = 0;
   char temp[100];
   double values[MAXSIZE];
   myBasicArrayObject * basicArray;

   // Is there any object?
   if (metricTree->GetNumberOfObjects() == 0){
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

   contObj = 0;

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
      cout << " Added " << contObj << " query objects\n";
      in.close();
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
   ResultMeasure * rMeasureSlimRingRange  = new ResultMeasure(this->QuantidadeRange);
   ResultMeasure * rMeasureSlimRingRangeInter  = new ResultMeasure(this->QuantidadeRange);
   ResultMeasure * rMeasureSlimRange  = new ResultMeasure(this->QuantidadeRange);
   ResultMeasure * rMeasureDummyRingRange = new ResultMeasure(this->QuantidadeRange);
   ResultMeasure * rMeasureDummyRingRangeInter = new ResultMeasure(this->QuantidadeRange);
   ResultMeasure * rMeasureDummyRange = new ResultMeasure(this->QuantidadeRange);

   itoa(this->PageSize, pageSizeString, 10);

   //set the radius of the objects
   if (this->MaxDistance <= 0){
      cout << "Calculating the radius from the sample queries.... ";
      this->MaxDistance = MetricTreeSlim->GetGreaterDistance();
      cout << MaxDistance;
      cout << " Ok\n";
   }//end if

   //set the name and the header of the file
   //for the AND clausure
   // distance function
   strcpy(fileName, this->Prefix.c_str());
   strcat(fileName, "Dist");
   sprintf(fileName+strlen(fileName), "%.2f", this->Percentage);
   strcat(fileName, "_");
   strcat(fileName, pageSizeString);
   strcat(fileName, ".plt");
   fileDistFunc = fopen(fileName, "w");
   WriteHeader(fileDistFunc, "set ylabel \"Nro. Médio de Cálculo de Distância\"\n", true, this->Percentage);
   // disc access
   strcpy(fileName, this->Prefix.c_str());
   strcat(fileName, "Disc");
   sprintf(fileName+strlen(fileName), "%.2f", this->Percentage);
   strcat(fileName, "_");
   strcat(fileName, pageSizeString);
   strcat(fileName, ".plt");
   fileDiscAccess = fopen(fileName, "w");
   WriteHeader(fileDiscAccess, "set ylabel \"Nro. Médio de Acesso a Disco\"\n", true, this->Percentage);
   // time
   strcpy(fileName, this->Prefix.c_str());
   strcat(fileName, "Time");
   sprintf(fileName+strlen(fileName), "%.2f", this->Percentage);
   strcat(fileName, "_");
   strcat(fileName, pageSizeString);
   strcat(fileName, ".plt");
   fileTime = fopen(fileName, "w");
   WriteHeader(fileTime, "set ylabel \"Tempo Total (s)\"\n", true, this->Percentage);

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
void TApp::RingRange(ResultMeasure * rMeasureSlim, ResultMeasure * rMeasureDummy){

   myResult * result;
   clock_t start, end;
   unsigned int i, j;
   double outerDistance;
   double innerDistance;
   int size = queryObjects.size();

   //For number of points (radius) that I want to measure.
   for (i = 0; i < rMeasureSlim->getSize(); i++){
      // Set the radius.
      outerDistance = this->MaxDistance * rMeasureSlim->getK(i);
      innerDistance = this->Percentage * outerDistance;

      PageManagerSlim->ResetStatistics();
      PageManagerDummy->ResetStatistics();
      MetricTreeSlim->GetMetricEvaluator()->ResetStatistics();
      MetricTreeDummy->GetMetricEvaluator()->ResetStatistics();

      start = clock();
      for (j = 0; j < size; j++){
         result = MetricTreeSlim->RingQuery(queryObjects[j], innerDistance, outerDistance);
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
         result = MetricTreeDummy->RingQuery(queryObjects[j], innerDistance, outerDistance);
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
}//end TApp::RingRange

//------------------------------------------------------------------------------
void TApp::RingRangeIntersection(ResultMeasure * rMeasureSlim, ResultMeasure * rMeasureDummy){

   myResult * result1, * result2, * finalResult;
   clock_t start, end;
   unsigned int i, j;
   double outerDistance;
   double innerDistance;
   int size = queryObjects.size();

   //For number of points (radius) that I want to measure.
   for (i = 0; i < rMeasureSlim->getSize(); i++){
      // Set the radius.
      outerDistance = this->MaxDistance * rMeasureSlim->getK(i);
      innerDistance = this->Percentage * outerDistance;

      PageManagerSlim->ResetStatistics();
      PageManagerDummy->ResetStatistics();
      MetricTreeSlim->GetMetricEvaluator()->ResetStatistics();
      MetricTreeDummy->GetMetricEvaluator()->ResetStatistics();

      start = clock();
      for (j = 0; j < size; j++){
         result1 = MetricTreeSlim->RangeQuery(queryObjects[j], innerDistance);
         result2 = MetricTreeSlim->RangeQuery(queryObjects[j], outerDistance);
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
         result1 = MetricTreeDummy->RangeQuery(queryObjects[j], innerDistance);
         result2 = MetricTreeDummy->RangeQuery(queryObjects[j], outerDistance);
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

}//end TApp::RingRangeIntersection

//------------------------------------------------------------------------------
void TApp::Range(ResultMeasure * rMeasureSlim, ResultMeasure * rMeasureDummy){

   myResult * result;
   clock_t start, end;
   unsigned int i, j;
   double outerDistance;
   int size = queryObjects.size();

   //For number of points (radius) that I want to measure.
   for (i = 0; i < rMeasureSlim->getSize(); i++){
      // Set the radius.
      outerDistance = this->MaxDistance * rMeasureSlim->getK(i);

      PageManagerSlim->ResetStatistics();
      PageManagerDummy->ResetStatistics();
      MetricTreeSlim->GetMetricEvaluator()->ResetStatistics();
      MetricTreeDummy->GetMetricEvaluator()->ResetStatistics();

      start = clock();
      for (j = 0; j < size; j++){
         result = MetricTreeSlim->RangeQuery(queryObjects[j], outerDistance);
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
         result = MetricTreeDummy->RangeQuery(queryObjects[j], outerDistance);
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
}//end TApp::Range

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
   strcpy(strTemp,", ratio (outer/inner) =");
   fwrite(strTemp, strlen(strTemp), 1, file);
   fprintf(file, "%.2f", radius);
   strcpy(strTemp,"\"\nset logscale xy");
   strcat(strTemp,"\nset xlabel \"% raio\"\n");
   fwrite(strTemp, strlen(strTemp), 1, file);
   strcpy(strTemp, type);
   fwrite(strTemp, strlen(strTemp), 1, file);
   strcpy(strTemp, "set xrange [0.001:0.1]\n");
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
