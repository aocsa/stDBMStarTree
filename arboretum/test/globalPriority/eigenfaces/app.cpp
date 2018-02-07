//---------------------------------------------------------------------------
// app.cpp - Implementation of the application.
//
// To change the behavior of this application, comment and uncomment lines at
// TApp::Init() and TApp::Query().
//
// Author: Marcos Rodrigues Vieira (mrvieira@icmc.usp.br)
//
// Copyright (c) 2003 GBDI-ICMC-USP
//---------------------------------------------------------------------------
#include <iostream>
#include <stdlib>
#include <math>
#pragma hdrstop

#include "app.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
// Class TApp
//---------------------------------------------------------------------------

void TApp::Init(){
   // To create it in disk
   CreateDiskPageManager();
   // Creates the tree
   CreateTree();
}//end TApp::Init

//------------------------------------------------------------------------------
void TApp::Run(){
   //load the query collection from the file
   LoadVectorFromFile("Lyfnmp500.txt");
   // Lets do the queries
   PerformQueries();
   // Hold the screen.
   cout << "Finished the whole test!\n";
}//end TApp::Run

//------------------------------------------------------------------------------
void TApp::Done(){

   if (this->MetricTreeSlim != NULL){
      delete this->MetricTreeSlim;
   }//end if
   if (this->PageManagerSlim != NULL){
      delete this->PageManagerSlim;
   }//end if                vector
   for (int i=0; i<queryPoints.size(); i++){
      delete (queryPoints.at(i));
   }//end for
}//end TApp::Done

//------------------------------------------------------------------------------
void TApp::CreateDiskPageManager(){
   //for Slim-tree
   stDiskPageManager * dmanSlim = new stDiskPageManager();
   // Filename is mySlimTree.dat
   dmanSlim->Open("Lyfnmp512.dat");
//   dmanSlim->Open("lyfnmp4k.dat");
   PageManagerSlim = dmanSlim;
}//end TApp::CreateDiskPageManager

//------------------------------------------------------------------------------
void TApp::CreateTree(){
   //create for Slim-tree
   mySlimTree * slimtree = new mySlimTree(PageManagerSlim);
   MetricTreeSlim = slimtree;
}//end TApp::CreateTree

//------------------------------------------------------------------------------
void TApp::LoadVectorFromFile(char *filename){
   FILE * file;
   int idx, contObj, i;
   char buffer[600], point[600], *ptr;
   double values[16];

   if ((file = fopen(filename, "r")) == NULL){
      printf("Cannot open input file.\n");
   }
   else{
      contObj = 0;
      fgets(buffer, 600, file);
      cout << "Adding the objects for query...\n";
      do{
         values[0] = atof(buffer);
         for(i=1; i<16; i++){
            strcpy(point, buffer + 10*i);
            ptr = strchr(point, '  ');
            *ptr = '\0';
            values[i] = atof(point);
         }//end for
         queryPoints.insert(queryPoints.end(), new TPoint(values));
         contObj++;
         fgets(buffer, 600, file);
      }while(!feof(file));//end while
      cout << "Added " << contObj << " objects...\n";
      fclose(file);
   }//end else
}//end TApp::LoadVectorFromFile

//------------------------------------------------------------------------------
void TApp::PerformQueries(){

   char string[] = "\npause -1";
   FILE * fileDistFunc, * fileTime, * fileDiscAccess;

   //for the result of the tests
   resultMeasure * rMeasureIncrementalNearest = new resultMeasure(QUANTIDADE);
   resultMeasure * rMeasureLocalNearest = new resultMeasure(QUANTIDADE);
   resultMeasure * rMeasureGlobalNearest = new resultMeasure(QUANTIDADE);
   resultMeasure * rMeasureFractalNearest1 = new resultMeasure(QUANTIDADE);
   resultMeasure * rMeasureRange = new resultMeasure(QUANTIDADE);

   //set the name and the header of the file
   fileDistFunc = fopen("DistFuncEF512L.plt", "w");
//   fileDistFunc = fopen("DistFuncEF4kL.plt", "w");
   WriteHeader(fileDistFunc, "set ylabel \"# AVG Distance Function\"\n");

   fileDiscAccess = fopen("DiscAccessEF512L.plt", "w");
//   fileDiscAccess = fopen("DiscAccessEF4kL.plt", "w");
   WriteHeader(fileDiscAccess, "set ylabel \"# AVG Disc Access\"\n");

   fileTime = fopen("TimeEF512L.plt", "w");
//   fileTime = fopen("TimeEF4kL.plt", "w");
   WriteHeader(fileTime, "set ylabel \"Total Time\"\n");

   cout << "\nStarting Incremental Nearest";
   PerformIncrementalNearest(rMeasureIncrementalNearest);
   cout << " Ok\n";

   cout << "\nStarting Local Nearest";
   PerformLocalNearest(rMeasureLocalNearest);
   cout << " Ok\n";

   cout << "\nStarting Global Nearest";
   PerformGlobalNearest(rMeasureGlobalNearest);
   cout << " Ok\n";

   cout << "\nStarting Range";
   PerformRange(rMeasureRange);
   cout << " Ok\n";

   cout << "\nStarting Fractal Nearest1";
   PerformFractalNearest(rMeasureFractalNearest1, DIMENSAOFRACTAL1);
   cout << " Ok\n";

   //write the statistics to files
   //Distance Function
   WriteToFile(fileDistFunc, rMeasureIncrementalNearest, 1);
   WriteToFile(fileDistFunc, rMeasureLocalNearest, 1);
   WriteToFile(fileDistFunc, rMeasureGlobalNearest, 1);
   WriteToFile(fileDistFunc, rMeasureFractalNearest1, 1);
   WriteToFile(fileDistFunc, rMeasureRange, 1);
   fwrite(string, strlen(string), 1, fileDistFunc);

   //Disc Access
   WriteToFile(fileDiscAccess, rMeasureIncrementalNearest, 2);
   WriteToFile(fileDiscAccess, rMeasureLocalNearest, 2);
   WriteToFile(fileDiscAccess, rMeasureGlobalNearest, 2);
   WriteToFile(fileDiscAccess, rMeasureFractalNearest1, 2);
   WriteToFile(fileDiscAccess, rMeasureRange, 2);
   fwrite(string, strlen(string), 1, fileDiscAccess);

   //Total Time
   WriteToFile(fileTime, rMeasureIncrementalNearest, 3);
   WriteToFile(fileTime, rMeasureLocalNearest, 3);
   WriteToFile(fileTime, rMeasureGlobalNearest, 3);
   WriteToFile(fileTime, rMeasureFractalNearest1, 3);
   WriteToFile(fileTime, rMeasureRange, 3);
   fwrite(string, strlen(string), 1, fileTime);

   //close the files
   fclose(fileDistFunc);
   fclose(fileTime);
   fclose(fileDiscAccess);

   //cleaning...
   delete rMeasureIncrementalNearest;
   delete rMeasureLocalNearest;
   delete rMeasureGlobalNearest;
   delete rMeasureFractalNearest1;
   delete rMeasureRange;

}//end TApp::PerformQueries()

//------------------------------------------------------------------------------
void TApp::PerformIncrementalNearest(resultMeasure * rMeasure){

   myResult * resultSlim = NULL;
   TPoint * sample;
   tPGenericHeap * genericHeap = NULL;
//   tPGenericList * genericList = NULL;
   clock_t start, end;
   int i, j;

   for (i=0; i < rMeasure->getSize(); i++){
      //reset the statistics
      PageManagerSlim->ResetStatistics();
      MetricTreeSlim->GetMetricEvaluator()->ResetStatistics();
      start = clock();
      for (j=0; j < queryPoints.size(); j++){
         sample = new TPoint(queryPoints[j]->GetValues());
         resultSlim = new myResult();
//         genericHeap = new tPGenericHeap(2*ceil(NROOBJECTS*rMeasure->getK(i)) + 10);
         genericHeap = new tPGenericHeap(12000, 1000);
//         genericList = new tPGenericList();
         // call the initialize to the incremental nearest.
         MetricTreeSlim->InitializeIncrementalNearestQueryHeap(sample,
                                 ceil(NROOBJECTS*rMeasure->getK(i)), resultSlim, genericHeap);
//         MetricTreeSlim->InitializeIncrementalNearestQueryList(sample,
//                                 ceil(NROOBJECTS*rMeasure->getK(i)), resultSlim, genericList);
         // call the query itself.
         MetricTreeSlim->IncrementalNearestQueryHeap(sample, ceil(NROOBJECTS*rMeasure->getK(i)),
                                                     resultSlim, genericHeap);
//         MetricTreeSlim->IncrementalNearestQueryList(sample, ceil(NROOBJECTS*rMeasure->getK(i)),
//                                                     resultSlim, genericList);
         delete resultSlim;
         delete genericHeap;
//         delete genericList;
         delete sample;
      }//end for
      end = clock();
      rMeasure->setTotalTime(i, (1000*((double )end-(double )start))/CLK_TCK);
      // is divided for queryPoints to get the everage
      rMeasure->setDiscAccess(i, PageManagerSlim->GetReadCount() / queryPoints.size());
      // is divided for queryPoints to get the everage
      rMeasure->setDistanceFunction(i,
         MetricTreeSlim->GetMetricEvaluator()->GetDistanceCount() / queryPoints.size());

      cout << " " << i;
   }//end for

}//end TApp::PerformIncrementalNearest

//------------------------------------------------------------------------------
void TApp::PerformLocalNearest(resultMeasure * rMeasure){

   myResult * resultSlim;
   TPoint * sample;
   clock_t start, end;
   int i, j;

   for (i=0; i < rMeasure->getSize(); i++){
      //reset the statistics
      PageManagerSlim->ResetStatistics();
      MetricTreeSlim->GetMetricEvaluator()->ResetStatistics();
      start = clock();
      for (j=0; j < queryPoints.size(); j++){
         sample = new TPoint(queryPoints[j]->GetValues());
         resultSlim = MetricTreeSlim->LocalNearestQuery(sample, ceil(NROOBJECTS*rMeasure->getK(i)), false);
         delete resultSlim;
         delete sample;
      }//end for
      end = clock();
      rMeasure->setTotalTime(i, (1000*((double )end-(double )start))/CLK_TCK);
      // is divided for queryPoints to get the everage
      rMeasure->setDiscAccess(i, PageManagerSlim->GetReadCount() / queryPoints.size());
      // is divided for queryPoints to get the everage
      rMeasure->setDistanceFunction(i,
         MetricTreeSlim->GetMetricEvaluator()->GetDistanceCount() / queryPoints.size());

      cout << " " << i;
   }//end for

}//end TApp::PerformLocalNearest

//------------------------------------------------------------------------------
void TApp::PerformGlobalNearest(resultMeasure * rMeasure){

   myResult * resultSlim;
   TPoint * sample;
   clock_t start, end;
   int i, j;

   for (i=0; i < rMeasure->getSize(); i++){
      //reset the statistics
      PageManagerSlim->ResetStatistics();
      MetricTreeSlim->GetMetricEvaluator()->ResetStatistics();
      start = clock();
      for (j=0; j < queryPoints.size(); j++){
         sample = new TPoint(queryPoints[j]->GetValues());
         resultSlim = MetricTreeSlim->NearestQuery(sample, ceil(NROOBJECTS*rMeasure->getK(i)), false);
         // set the radius for the range query.
         delete resultSlim;
         delete sample;
      }//end for
      end = clock();
      rMeasure->setTotalTime(i, (1000*((double )end-(double )start))/CLK_TCK);
      // is divided for queryPoints to get the everage
      rMeasure->setDiscAccess(i, PageManagerSlim->GetReadCount() / queryPoints.size());
      // is divided for queryPoints to get the everage
      rMeasure->setDistanceFunction(i,
         MetricTreeSlim->GetMetricEvaluator()->GetDistanceCount() / queryPoints.size());

      cout << " " << i;
   }//end for

}//end TApp::PerformGlobalNearest

//------------------------------------------------------------------------------
void TApp::PerformRange(resultMeasure * rMeasure){

   myResult * resultSlim;
   TPoint * sample;
   clock_t start, end;
   int i, j;

   for (i=0; i < rMeasure->getSize(); i++){
      //clear before use.
      radiusPoints.clear();
      // set the radius of the queries
      for (j=0; j < queryPoints.size(); j++){
         sample = new TPoint(queryPoints[j]->GetValues());
         resultSlim = MetricTreeSlim->NearestQuery(sample, ceil(NROOBJECTS*rMeasure->getK(i)));
         // set the radius for the range query.
         radiusPoints.insert(radiusPoints.end(), resultSlim->GetMaximumDistance());
         delete resultSlim;
         delete sample;
      }//end for

      //reset the statistics
      PageManagerSlim->ResetStatistics();
      MetricTreeSlim->GetMetricEvaluator()->ResetStatistics();
      start = clock();
      for (j=0; j < queryPoints.size(); j++){
         sample = new TPoint(queryPoints[j]->GetValues());
         // performs the range query.
         resultSlim = MetricTreeSlim->RangeQuery(sample, radiusPoints[j]);
         delete resultSlim;
         delete sample;
      }//end for
      end = clock();
      rMeasure->setTotalTime(i, (1000*((double )end-(double )start))/CLK_TCK);
      // is divided for queryPoints to get the everage
      rMeasure->setDiscAccess(i, PageManagerSlim->GetReadCount() / queryPoints.size());
      // is divided for queryPoints to get the everage
      rMeasure->setDistanceFunction(i,
         MetricTreeSlim->GetMetricEvaluator()->GetDistanceCount() / queryPoints.size());

      cout << " " << i;
   }//end for

}//end TApp::PerformRange

//------------------------------------------------------------------------------
void TApp::PerformFractalNearest(resultMeasure * rMeasure, double dimensaoFractal){

   myResult * resultSlim;
   TPoint * sample;
   clock_t start, end;
   int i, j;

   //For number of points (radius) that I want measure.
   for (i=0; i < rMeasure->getSize(); i++){
      //reset the statistics
      PageManagerSlim->ResetStatistics();
      MetricTreeSlim->GetMetricEvaluator()->ResetStatistics();
      start = clock();
      for (j=0; j < queryPoints.size(); j++){
         sample = new TPoint(queryPoints[j]->GetValues());
         resultSlim = MetricTreeSlim->EstimateNearestQuery(sample,
                           dimensaoFractal, 16.632793, -0.831462,
                           ceil(NROOBJECTS*rMeasure->getK(i)), false);
         delete resultSlim;
         delete sample;
      }//end for
      end = clock();
      rMeasure->setTotalTime(i, (1000*((double )end-(double )start))/CLK_TCK);
      // is divided for queryPoints to get the everage
      rMeasure->setDiscAccess(i, PageManagerSlim->GetReadCount() / queryPoints.size());
      // is divided for queryPoints to get the everage
      rMeasure->setDistanceFunction(i,
         MetricTreeSlim->GetMetricEvaluator()->GetDistanceCount() / queryPoints.size());

      cout << " " << i;
   }//end for

}//end TApp::PerformFractalNearest

//------------------------------------------------------------------------------
void TApp::WriteToFile(FILE * file, resultMeasure * rMeasure, int type){
   char * strTemp = new char[500];
   char * string = new char[50];

   //write the statistics to files
   for (int i=0; i < rMeasure->getSize(); i++){
      fprintf(file, "%f", rMeasure->getK(i));
      strcpy(strTemp, "\t");
      fwrite(strTemp, strlen(strTemp), 1, file);
      if(type==1)
         fprintf(file, "%f", rMeasure->getDistanceFunction(i));
      else if(type==2)
         fprintf(file, "%f", rMeasure->getDiscAccess(i));
      else
         fprintf(file, "%f", rMeasure->getTotalTime(i));
      strcpy(strTemp, "\n");
      fwrite(strTemp, strlen(strTemp), 1, file);
   }//end for
   strcpy(strTemp, "end\n\n");
   fwrite(strTemp, strlen(strTemp), 1, file);

   delete strTemp;
   delete string;
}//end TApp::WriteToFile()

//------------------------------------------------------------------------------
void TApp::WriteHeader(FILE * file, char * type){
   char * strTemp = new char[500];

   strcpy(strTemp,"set title \"EigenFaces: Nearest Queries");
   fwrite(strTemp, strlen(strTemp), 1, file);
   strcpy(strTemp,"\"\nset logscale xy\n");
   strcat(strTemp,"set xlabel \"k\"\n");
   fwrite(strTemp, strlen(strTemp), 1, file);
   strcpy(strTemp, type);
   fwrite(strTemp, strlen(strTemp), 1, file);
   strcpy(strTemp,"plot '-' title 'Incremental Nearest - Hjaltson' with linespoints 1, ");
   fwrite(strTemp, strlen(strTemp), 1, file);
   strcpy(strTemp,"'-' title 'Local Nearest - Roussopoulos' with linespoints 2, ");
   fwrite(strTemp, strlen(strTemp), 1, file);
   strcpy(strTemp,"'-' title 'Global Nearest - Slim-tree' with linespoints 3, ");
   fwrite(strTemp, strlen(strTemp), 1, file);
   strcpy(strTemp,"'-' title 'Fractal Nearest - Traina' with linespoints 4,");
   fwrite(strTemp, strlen(strTemp), 1, file);
   strcpy(strTemp,"'-' title 'Range' with linespoints 5\n\n");
   fwrite(strTemp, strlen(strTemp), 1, file);

   delete strTemp;
}//end TApp::WriteHeader()
