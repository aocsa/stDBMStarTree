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
//------------------------------------------------------------------------------
void TApp::Init(unsigned int pageSize, unsigned int quantidadeRange,
                unsigned int quantidadeK, char * tieList, char * prefix){
   this->PageSize = pageSize;
   this->QuantidadeRange = quantidadeRange;
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
   char pageSizeString[10];

   itoa(this->PageSize, pageSizeString, 10);

   //for Slim-tree
   strcpy(fileName, this->Prefix.c_str());
   strcat(fileName, "Slim");
   strcat(fileName, pageSizeString);
   strcat(fileName, ".dat");
   PageManagerSlim = new stPlainDiskPageManager(fileName, this->PageSize);

   //for Dummy-tree
   strcpy(fileName, this->Prefix.c_str());
   strcat(fileName, "Dummy");
   strcat(fileName, pageSizeString);
   strcat(fileName, ".dat");
   PageManagerDummy = new stPlainDiskPageManager(fileName, this->PageSize);
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
   for (int i=0; i < queryPoints.size(); i++){
      delete (queryPoints.at(i));
   }//end for
}//end TApp::Done

//------------------------------------------------------------------------------
void TApp::LoadTree(char * fileName, MetricTree * metricTree){
   FILE * file;
   int i;
   char buffer[200], temp[200], * ptr, * ptr2;
   double entries[MAXSIZE];

   if (metricTree!=NULL){
      if ((file = fopen(fileName, "r")) == NULL){
         printf("Cannot open input file!\n\n");
      }else{
         fgets(buffer, 200, file);
         do{
            ptr2 = buffer;
            for(i=0; i<MAXSIZE; i++){
               strcpy(temp, ptr2);
               ptr = strchr(temp, ' ');
               if (ptr==NULL){
                  ptr = strchr(temp, '\n');
                  *ptr = '\0';
               }else{
                  ptr2 = ptr + 1;
                  *ptr = '\0';
               }//end if
               entries[i] = atof(temp);
            }//end for
            AddToTree(entries, metricTree);
            fgets(buffer, 200, file);
         }while(!feof(file));
         cout << "Added " << metricTree->GetNumberOfObjects() << " objects...\n";
         fclose(file);
      }//end if
  }else{
      cout << "Zero object added!!\n";
  }//end else
}//end TApp::LoadTree()

//------------------------------------------------------------------------------
void TApp::LoadVectorFromFile(char * fileName){
   FILE * file;
   int i, contObj=0;
   char buffer[200], temp[200], * ptr, * ptr2;
   double entries[MAXSIZE];

   if ((file = fopen(fileName, "r")) == NULL){
      printf("Cannot open input file!\n\n");
   }else{
      fgets(buffer, 200, file);
      do{
         ptr2 = buffer;
         for(i=0; i<MAXSIZE; i++){
            strcpy(temp, ptr2);
            ptr = strchr(temp, ' ');
            if (ptr==NULL){
               ptr = strchr(temp, '\n');
               *ptr = '\0';
            }else{
               ptr2 = ptr + 1;
               *ptr = '\0';
            }//end if
            entries[i] = atof(temp);
         }//end for
         queryPoints.insert(queryPoints.end(), new TPoint(entries));
         contObj++;
         fgets(buffer, 200, file);
      }while(!feof(file));
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

   //for the result of the tests
   resultMeasure * rMeasureSlimKAndR  = new resultMeasure(this->QuantidadeRange);
   resultMeasure * rMeasureSlimKOrR   = new resultMeasure(this->QuantidadeRange);
   resultMeasure * rMeasureSlimInter  = new resultMeasure(this->QuantidadeRange);
   resultMeasure * rMeasureSlimUnion  = new resultMeasure(this->QuantidadeRange);
   resultMeasure * rMeasureDummyKAndR = new resultMeasure(this->QuantidadeRange);
   resultMeasure * rMeasureDummyKOrR  = new resultMeasure(this->QuantidadeRange);
   resultMeasure * rMeasureDummyInter = new resultMeasure(this->QuantidadeRange);
   resultMeasure * rMeasureDummyUnion = new resultMeasure(this->QuantidadeRange);

   FILE * fileDistFunc, * fileTime, * fileDiscAccess;
   int idx;

   itoa(this->PageSize, pageSizeString, 10);

   //set the radius of the objects
   cout << "Calculating the radius from the sample queries.... ";
   SetRadiusFromObjects(rMeasureSlimKAndR);
   cout << " Ok\n";

   for (idx=0; idx<this->QuantidadeK; idx++){  // raio comecando de 0.01 = 1% (valor absoluto)
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
      WriteHeader(fileDistFunc, "set ylabel \"# AVG Distance Function\"\n", true, rMeasureSlimKAndR->getK(idx));
      // disc access
      strcpy(fileName, this->Prefix.c_str());
      strcat(fileName, "Disc");
      sprintf(fileName+strlen(fileName), "%.4f", rMeasureSlimKAndR->getK(idx));
      strcat(fileName, "_");
      strcat(fileName, pageSizeString);
      strcat(fileName, ".plt");
      fileDiscAccess = fopen(fileName, "w");
      WriteHeader(fileDiscAccess, "set ylabel \"# AVG Disc Access\"\n", true, rMeasureSlimKAndR->getK(idx));
      // time
      strcpy(fileName, this->Prefix.c_str());
      strcat(fileName, "Time");
      sprintf(fileName+strlen(fileName), "%.4f", rMeasureSlimKAndR->getK(idx));
      strcat(fileName, "_");
      strcat(fileName, pageSizeString);
      strcat(fileName, ".plt");
      fileTime = fopen(fileName, "w");
      WriteHeader(fileTime, "set ylabel \"Total Time (s)\"\n", true, rMeasureSlimKAndR->getK(idx));

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
void TApp::NearestAndRange(int idx, resultMeasure * rMeasureSlim, resultMeasure * rMeasureDummy){

   double * d;
   myResult * result;
   TPoint * sample;
   clock_t start, end;
   int i, j;
   long numberOfObjects;

   //For number of points (radius) that I want measure.
   for (i=0; i < rMeasureSlim->getSize(); i++){
      if (i > idx){
         numberOfObjects = ceil(rMeasureSlim->getK(idx) * MetricTreeSlim->GetNumberOfObjects());
      }else{
         numberOfObjects = ceil(rMeasureSlim->getK(i) * MetricTreeSlim->GetNumberOfObjects());
      }//end if
      if (numberOfObjects > MetricTreeSlim->GetNumberOfObjects()){
         numberOfObjects = MetricTreeSlim->GetNumberOfObjects();
      }//end if

      PageManagerSlim->ResetStatistics();
      PageManagerDummy->ResetStatistics();
      MetricTreeSlim->GetMetricEvaluator()->ResetStatistics();
      MetricTreeDummy->GetMetricEvaluator()->ResetStatistics();

      start = clock();
      for (j=0; j < queryPoints.size(); j++){
         d = queryPoints[j]->GetValues();
         sample = new TPoint(d);
         result = MetricTreeSlim->KAndRangeQuery(sample, radiusQueryPoints[i][j], numberOfObjects, this->TieList);
         delete [] d;
         delete result;
         delete sample;
      }//end for
      end = clock();
      //to return the average in ms
      rMeasureSlim->setTotalTime(i, (double )end-(double )start);
      rMeasureSlim->setDiscAccess(i, (double )PageManagerSlim->GetReadCount() / (double )queryPoints.size());
      rMeasureSlim->setDistanceFunction(i, (double )MetricTreeSlim->GetMetricEvaluator()->GetDistanceCount() /
      												 (double )queryPoints.size());

      start = clock();
      for (j=0; j < queryPoints.size(); j++){
         d = queryPoints[j]->GetValues();
         sample = new TPoint(d);
         result = MetricTreeDummy->KAndRangeQuery(sample, radiusQueryPoints[i][j], numberOfObjects, this->TieList);
         delete [] d;
         delete result;
         delete sample;
      }//end for
      end = clock();
      //to return the average in ms
      rMeasureDummy->setTotalTime(i, (double )end-(double )start);
      rMeasureDummy->setDiscAccess(i, (double )PageManagerDummy->GetReadCount() / (double )queryPoints.size());
      rMeasureDummy->setDistanceFunction(i, (double )MetricTreeDummy->GetMetricEvaluator()->GetDistanceCount() /
      													 (double )queryPoints.size());

      cout << i << " ";
   }//end for

}//end TApp::NearestAndRange

//------------------------------------------------------------------------------
void TApp::NearestOrRange(int idx, resultMeasure * rMeasureSlim, resultMeasure * rMeasureDummy){

   double * d;
   myResult * result;
   TPoint * sample;
   clock_t start, end;
   int i, j;
   long numberOfObjects;

   //For number of points (radius) that I want measure.
   for (i=0; i < rMeasureSlim->getSize(); i++){
      if (i > idx){
         numberOfObjects = ceil(rMeasureSlim->getK(idx) * MetricTreeSlim->GetNumberOfObjects());
      }else{
         numberOfObjects = ceil(rMeasureSlim->getK(i) * MetricTreeSlim->GetNumberOfObjects());
      }//end if
      if (numberOfObjects > MetricTreeSlim->GetNumberOfObjects()){
         numberOfObjects = MetricTreeSlim->GetNumberOfObjects();
      }//end if

      PageManagerSlim->ResetStatistics();
      PageManagerDummy->ResetStatistics();
      MetricTreeSlim->GetMetricEvaluator()->ResetStatistics();
      MetricTreeDummy->GetMetricEvaluator()->ResetStatistics();

      start = clock();
      for (j=0; j<queryPoints.size(); j++){
         d = queryPoints[j]->GetValues();
         sample = new TPoint(d);
         result = MetricTreeSlim->KOrRangeQuery(sample, radiusQueryPoints[i][j], numberOfObjects, this->TieList);
         delete [] d;
         delete result;
         delete sample;
      }//end for
      end = clock();
		//to return the average in ms
      rMeasureSlim->setTotalTime(i, (double )end-(double )start);
      rMeasureSlim->setDiscAccess(i, (double )PageManagerSlim->GetReadCount() / (double )queryPoints.size());
      rMeasureSlim->setDistanceFunction(i, (double )MetricTreeSlim->GetMetricEvaluator()->GetDistanceCount() /
      												 (double )queryPoints.size());

      start = clock();
      for (j=0; j<queryPoints.size(); j++){
         d = queryPoints[j]->GetValues();
         sample = new TPoint(d);
         result = MetricTreeDummy->KOrRangeQuery(sample, radiusQueryPoints[i][j], numberOfObjects, this->TieList);
         delete [] d;
         delete result;
         delete sample;
      }//end for
      end = clock();
		//to return the average in ms
      rMeasureDummy->setTotalTime(i, (double )end-(double )start);
      rMeasureDummy->setDiscAccess(i, (double )PageManagerDummy->GetReadCount() / (double )queryPoints.size());
      rMeasureDummy->setDistanceFunction(i, (double )MetricTreeDummy->GetMetricEvaluator()->GetDistanceCount() /
      													(double )queryPoints.size());

      cout << i << " ";
   }//end for

}//end TApp::NearestOrRange

//------------------------------------------------------------------------------
void TApp::NearestIntersectionRange(int idx, resultMeasure * rMeasureSlim, resultMeasure * rMeasureDummy){

   double * d;
   myResult * result1, * result2, * finalResult;
   TPoint * sample;
   clock_t start, end;
   int i, j;
   long numberOfObjects;

   for (i=0; i < rMeasureSlim->getSize(); i++){
      if (i > idx){
         numberOfObjects = ceil(rMeasureSlim->getK(idx) * MetricTreeSlim->GetNumberOfObjects());
      }else{
         numberOfObjects = ceil(rMeasureSlim->getK(i) * MetricTreeSlim->GetNumberOfObjects());
      }//end if
      if (numberOfObjects > MetricTreeSlim->GetNumberOfObjects()){
         numberOfObjects = MetricTreeSlim->GetNumberOfObjects();
      }//end if

      PageManagerSlim->ResetStatistics();
      PageManagerDummy->ResetStatistics();
      MetricTreeSlim->GetMetricEvaluator()->ResetStatistics();
      MetricTreeDummy->GetMetricEvaluator()->ResetStatistics();

      start = clock();
      for (j=0; j < queryPoints.size(); j++){
         d = queryPoints[j]->GetValues();
         sample = new TPoint(d);
         result1 = MetricTreeSlim->RangeQuery(sample, radiusQueryPoints[i][j]);
         result2 = MetricTreeSlim->NearestQuery(sample, numberOfObjects, this->TieList);
         finalResult = new myResult();
         //result1 intersection result2
         finalResult->Intersection(result1, result2);

         delete [] d;
         delete finalResult;
         delete result1;
         delete result2;
         delete sample;
      }//end for
      end = clock();
		//to return the average in ms
      rMeasureSlim->setTotalTime(i, (double )end-(double )start);
      rMeasureSlim->setDiscAccess(i, (double )PageManagerSlim->GetReadCount() / (double )queryPoints.size());
      rMeasureSlim->setDistanceFunction(i, (double )MetricTreeSlim->GetMetricEvaluator()->GetDistanceCount() /
      													(double )queryPoints.size());

      start = clock();
      for (j=0; j < queryPoints.size(); j++){
         d = queryPoints[j]->GetValues();
         sample = new TPoint(d);
         result1 = MetricTreeDummy->RangeQuery(sample, radiusQueryPoints[i][j]);
         result2 = MetricTreeDummy->NearestQuery(sample, numberOfObjects, this->TieList);
         //result1 intersection result2
         finalResult = new myResult();
         finalResult->Intersection(result1, result2);

         delete [] d;
         delete finalResult;
         delete result1;
         delete result2;
         delete sample;
      }//end for
      end = clock();
		//to return the average in ms
      rMeasureDummy->setTotalTime(i, (double )end-(double )start);
      rMeasureDummy->setDiscAccess(i, (double )PageManagerDummy->GetReadCount() / (double )queryPoints.size());
      rMeasureDummy->setDistanceFunction(i, (double )MetricTreeDummy->GetMetricEvaluator()->GetDistanceCount() /
      													(double )queryPoints.size());

      cout << i << " ";
   }//end for

}//end TApp::NearestIntersectionRange

//------------------------------------------------------------------------------
void TApp::NearestUnionRange(int idx, resultMeasure * rMeasureSlim, resultMeasure * rMeasureDummy){

   double * d;
   myResult * result1, * result2, * finalResult;
   TPoint * sample;
   clock_t start, end;
   int i, j;
   long numberOfObjects;

   for (i=0; i< rMeasureSlim->getSize(); i++){
      if (i > idx){
         numberOfObjects = ceil(rMeasureSlim->getK(idx) * MetricTreeSlim->GetNumberOfObjects());
      }else{
         numberOfObjects = ceil(rMeasureSlim->getK(i) * MetricTreeSlim->GetNumberOfObjects());
      }//end if
      if (numberOfObjects > MetricTreeSlim->GetNumberOfObjects()){
         numberOfObjects = MetricTreeSlim->GetNumberOfObjects();
      }//end if

      PageManagerSlim->ResetStatistics();
      PageManagerDummy->ResetStatistics();
      MetricTreeSlim->GetMetricEvaluator()->ResetStatistics();
      MetricTreeDummy->GetMetricEvaluator()->ResetStatistics();

      start = clock();
      for (j=0; j < queryPoints.size(); j++){
         d = queryPoints[j]->GetValues();
         sample = new TPoint(d);
         result1 = MetricTreeSlim->RangeQuery(sample, radiusQueryPoints[i][j]);
         result2 = MetricTreeSlim->NearestQuery(sample, numberOfObjects, this->TieList);
         //result1 union result2
         finalResult = new myResult();
         finalResult->Union(result1, result2);

         delete [] d;
         delete finalResult;
         delete result1;
         delete result2;
         delete sample;
      }// end for
      end = clock();
		//to return the average in ms
      rMeasureSlim->setTotalTime(i, (double )end-(double )start);
      rMeasureSlim->setDiscAccess(i, (double )PageManagerSlim->GetReadCount() / (double )queryPoints.size());
      rMeasureSlim->setDistanceFunction(i, (double )MetricTreeSlim->GetMetricEvaluator()->GetDistanceCount() /
      													(double )queryPoints.size());

      start = clock();
      for (j=0; j < queryPoints.size(); j++){
         d = queryPoints[j]->GetValues();
         sample = new TPoint(d);
         result1 = MetricTreeDummy->RangeQuery(sample, radiusQueryPoints[i][j]);
         result2 = MetricTreeDummy->NearestQuery(sample, numberOfObjects, this->TieList);
         // result1 union result2
         finalResult = new myResult();
         finalResult->Union(result1, result2);

         delete [] d;
         delete finalResult;
         delete result1;
         delete result2;
         delete sample;
      }// end for
      end = clock();
		//to return the average in ms
      rMeasureDummy->setTotalTime(i, (double )end-(double )start);
      rMeasureDummy->setDiscAccess(i, (double )PageManagerDummy->GetReadCount() / (double )queryPoints.size());
      rMeasureDummy->setDistanceFunction(i, (double )MetricTreeDummy->GetMetricEvaluator()->GetDistanceCount() /
      													(double )queryPoints.size());

      cout << i << " ";
   }//end for

}//end TApp::NearestUnionRange

//------------------------------------------------------------------------------
void TApp::SetRadiusFromObjects(resultMeasure * rMeasureSlim){

   double * d;
   myResult * result;
   TPoint * sample;
   long numberOfObjects;
   int i, j;

   //clear before insert new radium values
   for (i=0; i < this->QuantidadeRange; i++){
      radiusQueryPoints[i].clear();
      // set the number of objects.
      numberOfObjects = ceil(rMeasureSlim->getK(i) * MetricTreeSlim->GetNumberOfObjects());
      if (numberOfObjects > MetricTreeSlim->GetNumberOfObjects()){
         numberOfObjects = MetricTreeSlim->GetNumberOfObjects();
      }//end if
      // perform the query.
      for (j=0; j < queryPoints.size(); j++){
         d = queryPoints[j]->GetValues();
         sample = new TPoint(d);
         result = MetricTreeSlim->NearestQuery(sample, numberOfObjects);
         // set the radius.
         radiusQueryPoints[i].insert(radiusQueryPoints[i].end(), result->GetMaximumDistance());
         delete [] d;
         delete result;
         delete sample;
      }//end for
      cout << " " << i;
   }//end for
}//end TApp::SetRadiusFromObjects

//------------------------------------------------------------------------------
void TApp::WriteToFile(FILE * file, char * algName, resultMeasure * rMeasure, int type){
   char * strTemp = new char[500];
   char * string = new char[50];

   fprintf(file, "%s", algName);
   //write the statistics to files
   for(int i=0; i < rMeasure->getSize(); i++){
      fprintf(file, "%f", rMeasure->getK(i));
      strcpy(strTemp, "\t");
      fwrite(strTemp, strlen(strTemp), 1, file);
      if (type==1)
         fprintf(file, "%f", rMeasure->getDistanceFunction(i));
      else if (type==2)
         fprintf(file, "%f", rMeasure->getDiscAccess(i));
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

   strcpy(strTemp,"set title \"Currency dataset:");
   fwrite(strTemp, strlen(strTemp), 1, file);
   strcpy(strTemp,"  page=");
   fwrite(strTemp, strlen(strTemp), 1, file);
   fwrite(pageSize, strlen(pageSize), 1, file);
   strcpy(strTemp,",  k=");
   fwrite(strTemp, strlen(strTemp), 1, file);
   fprintf(file, "%.4f", radius);
   strcpy(strTemp,"\"\nset logscale xy");
   strcat(strTemp,"\nset xlabel \"% Radius\"\n");
   fwrite(strTemp, strlen(strTemp), 1, file);
   strcpy(strTemp, type);
   fwrite(strTemp, strlen(strTemp), 1, file);

   strcpy(strTemp,"plot '-' title '(A) Slim-Tree: kAndRange' with linespoints 1, ");
   strcat(strTemp,"'-' title '(B) Slim-Tree: Inters. basic alg.' with linespoints 2, ");
   strcat(strTemp,"'-' title '(C) Slim-Tree: kOrRange' with linespoints 3, ");
   strcat(strTemp,"'-' title '(D) Slim-Tree: Union basic alg.' with linespoints 4, ");
   strcat(strTemp,"'-' title '(E) SeqScan: kAndRange' with linespoints 5, ");
   strcat(strTemp,"'-' title '(F) SeqScan: Inters. basic alg.' with linespoints 6, ");
   strcat(strTemp,"'-' title '(G) SeqScan: kOrRange' with linespoints 7, ");
   strcat(strTemp,"'-' title '(H) SeqScan: Union basic alg.' with linespoints 8\n\n");
   fwrite(strTemp, strlen(strTemp), 1, file);

   strcpy(strTemp,"####################\n");
   fwrite(strTemp, strlen(strTemp), 1, file);

}//end TApp::WriteHeader
