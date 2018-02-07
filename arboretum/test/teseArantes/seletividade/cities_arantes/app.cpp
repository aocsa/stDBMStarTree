//---------------------------------------------------------------------------
// app.cpp - Implementation of the application.
//
// To change the behavior of this application, comment and uncomment lines at
// TApp::Init() and TApp::Query().
//
// Authors: Marcos Rodrigues Vieira (mrvieira@icmc.usp.br)
//          Adriano Siqueira Arantes (arantes@icmc.usp.br)
// Copyright (c) 2003 GBDI-ICMC-USP
//---------------------------------------------------------------------------
#include <iostream>
#include <stdlib>
#include <math>
#pragma hdrstop
#include "app.h"

//#define __stDebugNearest__
/*#define QUANTIDADE 10
#define FRACTALDIMENSION 1.81
#define RADIUSTREE 4.62
#define NOBJECTS 16.441294

// para variar raio e k juntos
#define RAIO 10
#define MAX_K 10
*/
// Its a percentile = 20 %
#define ERRORFD 0.3
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
// Class TApp
//---------------------------------------------------------------------------

//------------------------------------------------------------------------------
void TApp::Init(unsigned int pageSize, unsigned int datasetSize,
                stDistance fractalDimension, stDistance radiusTree,
                stDistance nObjects, char * prefix, char * range,
                char * difRadius, stDistance percRadius, double third){

   this->PageSize = pageSize;
   this->DatasetSize = datasetSize;
   this->FractalDimension = fractalDimension;
   this->RadiusTree = radiusTree;
   this->NObjects = nObjects;
   this->Prefix = prefix;

   if (!strcmp(range, "true")){
      this->Range = true;
   }else{
      this->Range = false;
   }//end if

   if (!strcmp(difRadius, "true")){
      this->DifRadius = true;
      this->PercRadius = (percRadius/100);
   }else{
      this->DifRadius = false;
      this->PercRadius = 0; 
   }//end if

   this->Third = third;
   // To create it in disk
   CreateDiskPageManager();
   // Creates the tree
   CreateTree();
}//end TApp::Init

//------------------------------------------------------------------------------
void TApp::Run(char * DataPath, char * DataQueryPath){

   // Lets load the tree with a lot values from the file.
   cout << "Adding objects in the MetricTreeSlim\n";
   LoadTree(DataPath);

   //load the query collection from the file
   cout << "Adding query objects ...\n";
   LoadVectorFromFile(DataQueryPath);

   // Lets do the 500 squeries
   PerformQueries();

   // Hold the screen.
   cout << "\nFinished the whole test!\n";
}//end TApp::Run

//------------------------------------------------------------------------------
void TApp::Done(){

   if (this->MetricTreeSlim != NULL){
      delete this->MetricTreeSlim;
   }//end if
   if (this->PageManagerSlim != NULL){
      delete this->PageManagerSlim;
   }//end if
}//end TApp::Done

//------------------------------------------------------------------------------
void TApp::CreateDiskPageManager(){
   //for Slim-tree
   char fileName[100];
   char pageSizeString[10];

   itoa(this->PageSize, pageSizeString, 10);

   //for Slim-tree
   strcpy(fileName, "Slim_P");
   strcat(fileName, pageSizeString);
   strcat(fileName, ".dat");

   PageManagerSlim = new stPlainDiskPageManager(fileName, this->PageSize);

/*   stDiskPageManager * dmanSlim = new stDiskPageManager();
   // Filename is mySlimTree.dat
   dmanSlim->Create("mySlimTree.dat", 1024);
   PageManagerSlim = dmanSlim;
*/
   
}//end TApp::CreateDiskPageManager

//------------------------------------------------------------------------------
void TApp::CreateTree(){
   //create for Slim-tree
   mySlimTree * slimtree = new mySlimTree(PageManagerSlim);
   MetricTreeSlim = slimtree;

/*   MetricTreeSlim->SetSplitMethod(mySlimTree::smSPANNINGTREE);
   MetricTreeSlim->SetChooseMethod(mySlimTree::cmMINDIST);*/
}//end TApp::CreateTree

//------------------------------------------------------------------------------
void TApp::LoadTree(char *fileName){

   FILE *file;
   int n, cont=0, contObj=0;
   char buffer[100], city[100];
   double dlat, dlong;
   char *ptr;

   if ((file = fopen(fileName, "r")) == NULL){
      printf("Cannot open input file.\n");
   }
   else{
   fgets(buffer, 100, file);
   cout << "Adding objects in the tree...\n";
   do{
      switch(cont){
         case 0: strcpy(city, buffer);
                 ptr = strchr(city, '\n');
                 *ptr = '\0';
                 cont++;
                 break;
         case 1: dlat = atof(buffer);
                 cont++;
                 break;
         case 2: dlong = atof(buffer);
                 AddToTree(city, dlat, dlong);
                 contObj++;
                 cont = 0;
      }//end switch
      fgets(buffer, 100, file);
   }while(!feof(file)); //end while
   cout << "Added " << contObj << " objects...\n";
   fclose(file);
  }//end else
}//end TApp::LoadTree()

//------------------------------------------------------------------------------
void TApp::LoadVectorFromFile(char *filename){
   FILE *f;
   int n, cont, contObj;
   char buffer[128], city[128], *ptr;
   double dlat, dlong;

   if ((f = fopen(filename, "r")) == NULL){
      printf("Cannot open input file.\n");
   }
   else{
      contObj = 0;
      cont = 0;

      fgets(buffer, 60, f);
      cout << "Adding the objects for query...\n";
      do{
         switch(cont){
            case 0: strcpy(city, buffer);
                    ptr = strchr(city, '\n');
                    *ptr = '\0';
                    cont++;
                    break;
            case 1: dlat = atof(buffer);
                    cont++;
                    break;
            case 2: dlong = atof(buffer);
                    queryObjects.insert(queryObjects.end(), new TCity(city, dlat, dlong));
                    contObj++;
                    cont = 0;
         }//end switch
        fgets(buffer, 60, f);
      }while(!feof(f));//end while
      cout << "Added " << contObj << " objects...\n";
      fclose(f);
   }//end else
}//end TApp::LoadVectorFromFile

/**
* Performs a query and outputs its results.

void TApp::PerformQuery(){
   myResult * resultKOrRange, * resultFastKOrRange, * resultRange;
   TCity * sample;
   clock_t start, end;

   double radius = 0.3;
   int k = 5;

   // Choose a sample by uncomenting one of then
   //sample = new TCity("Motuca", -48.15, -21.5);
   //sample = new TCity("Araraquara", -48.17, -21.79);
   //sample = new TCity("São Paulo-SP", -23.3251, 46.3810);
   sample = new TCity("São Carlos", -22.0103, 47.5327);
   //sample = new TCity("Unknown City", -43, - 22);

   // Perform a query...
  // result = MetricTree->RangeQuery(sample, 0.2);
   //result = MetricTree->RangeQuery(sample, 0.5, 5);
//   result = MetricTree->NearestQuery(sample, 5, true);
//   result = MetricTree->KandRangeQuery(sample, 0.3, 5, true);
//   result = MetricTree->KorRangeQuery(sample, 0.5, 60);

   //reset the statistics
   PageManagerSlim->ResetStatistics();
   MetricTreeSlim->GetMetricEvaluator()->ResetStatistics();

   start = clock();

   resultKOrRange = MetricTreeSlim->KOrRangeQuery (sample, radius,
                           k, true);
   end = clock();

   cout << "Results for kOrRange query ...";
   PrintResults(resultKOrRange);
   cout << "\nDisk Accesses: " << PageManagerSlim->GetReadCount();
   cout << "\nDistance Calculations: " << MetricTreeSlim->GetMetricEvaluator()->GetDistanceCount();
   cout << "\nTotal Time in ms: "  << (double) end - (double) start;

   //reset the statistics
   PageManagerSlim->ResetStatistics();
   MetricTreeSlim->GetMetricEvaluator()->ResetStatistics();

   start = clock();
   resultFastKOrRange = MetricTreeSlim->SimpleKOrRangeQuery (sample,
                           FRACTALDIMENSION, NOBJECTS, radius,
                          k, true);

   end = clock();
   cout << "\n\nResults for Simple kOrRange query ...";
   PrintResults(resultFastKOrRange);
   cout << "\nDisk Accesses: " << PageManagerSlim->GetReadCount();
   cout << "\nDistance Calculations: " << MetricTreeSlim->GetMetricEvaluator()->GetDistanceCount();
   cout << "\nTotal Time in ms: "  << (double) end - (double) start;

   //reset the statistics
   PageManagerSlim->ResetStatistics();
   MetricTreeSlim->GetMetricEvaluator()->ResetStatistics();

   start = clock();
   resultRange = MetricTreeSlim->RangeQuery (sample, radius);

   end = clock();

   cout << "\n\nResults for Range query ...";
   PrintResults(resultRange);
   cout << "\nDisk Accesses: " << PageManagerSlim->GetReadCount();
   cout << "\nDistance Calculations: " << MetricTreeSlim->GetMetricEvaluator()->GetDistanceCount();
   cout << "\nTotal Time in ms: "  << (double) end - (double) start;



   // Clean home
   delete resultKOrRange;
   delete resultFastKOrRange;
   delete resultRange;
   delete sample;

}//end TApp::PerformQuery
*/
//------------------------------------------------------------------------------
void TApp::PerformQueries(){

   char string[] = "\npause -1";
   char pageSizeString[10], percRadius[10], third[10];
   char fileName[50];
   char tmpString[50];

//   FILE * fileDistFunc, * fileTime, * fileDiscAccess,
   FILE * fileSelKAnd, * fileSelKOr, * fileSelRing;

   //for the result of the tests
/*   resultMeasure * rMeasureKOrRange = new resultMeasure(this->DatasetSize);
   resultMeasure * rMeasureSimpleKOrRange = new resultMeasure(this->DatasetSize);
   resultMeasure * rMeasureBestKOrRange = new resultMeasure(this->DatasetSize);
   resultMeasure * rMeasureRange = new resultMeasure(this->DatasetSize);
*/
   resultMeasure * rMeasureKAndRange = new resultMeasure(this->DatasetSize);
   resultMeasure * rMeasureKOrRange = new resultMeasure(this->DatasetSize);
   resultMeasure * rMeasureRingRange = new resultMeasure(this->DatasetSize);

   //Coping the page size, percent radius and case b) (how is one third of queries?) to a string
   itoa(this->PageSize, pageSizeString, 10);
   itoa(ceil(this->PercRadius*100), percRadius, 10);
   itoa(this->Third, third, 10);

   //set the name and the header of the file
   strcpy(fileName, this->Prefix.c_str());
   strcat(fileName, "SelkAndRange");
   strcat(fileName, "_P");
   strcat(fileName, pageSizeString);
   strcat(fileName, "_R");
   strcat(fileName, percRadius);
   strcat(fileName, "_Q");
   strcat(fileName, third);

   strcat(fileName, ".plt");

   fileSelKAnd = fopen(fileName, "w");
   WriteHeader(fileSelKAnd, "set ylabel \"Estimativa de Seletividade - Cardinalidade \"\n");

   //set the name and the header of the file
   strcpy(fileName, this->Prefix.c_str());
   strcat(fileName, "SelkOrRange");
   strcat(fileName, "_P");
   strcat(fileName, pageSizeString);
   strcat(fileName, "_R");
   strcat(fileName, percRadius);
   strcat(fileName, "_Q");
   strcat(fileName, third);

   strcat(fileName, ".plt");

   fileSelKOr = fopen(fileName, "w");
   WriteHeader(fileSelKOr, "set ylabel \"Estimativa de Seletividade - Cardinalidade \"\n");

   //set the name and the header of the file
   strcpy(fileName, this->Prefix.c_str());
   strcat(fileName, "SelRingRange");
   strcat(fileName, "_P");
   strcat(fileName, pageSizeString);
   strcat(fileName, "_R");
   strcat(fileName, percRadius);
   strcat(fileName, "_Q");
   strcat(fileName, third);

   strcat(fileName, ".plt");

   fileSelRing = fopen(fileName, "w");
   WriteHeader(fileSelRing, "set ylabel \"Estimativa de Seletividade - Cardinalidade \"\n");


   for(int cont = 0; cont < this->DatasetSize; cont++){  // raio comecando de 0.003 = 0.3% (valor absoluto)

     cout << "\n\nSetting radius to objects ... " << cont;
     SetRadiusFromObjects(rMeasureKAndRange, cont);

     cout << "\nStarting Statistics for kAndRange... ";
     PerformKAndRangeQuery(rMeasureKAndRange, cont);
     cout << "Ok\n";

     cout << "\n\nSetting radius to objects ... " << cont;
     SetRadiusFromObjects(rMeasureKOrRange, cont);

     cout << "\nStarting Statistics for kOrRange... ";
     PerformKOrRangeQuery(rMeasureKOrRange, cont);
     cout << "Ok\n";

/*     cout << "\n\nSetting radius to Ring objects ... " << cont;
     SetRadiusToRingObjects(rMeasureRingRange, cont);

     cout << "\nStarting Statistics for RingRange... ";
     PerformRingRangeQuery(rMeasureRingRange, cont);
     cout << "Ok\n";

/*
     if (this->Range){
       cout << "\nStarting Statistics for Range... ";
       PerformRangeQuery(rMeasureRange, cont);
       cout << "Ok\n";
     }

     cout << "\nStarting Statistics for kOrRange... ";
     PerformKOrRangeQuery(rMeasureKOrRange, cont);
     cout << "Ok\n";
*/
   };

   //write the statistics to files
   //* kAndRange

   //Cardinality Estimation
   // Estimation
   WriteToFile(fileSelKAnd, rMeasureKAndRange, 1);
   // Real
   WriteToFile(fileSelKAnd, rMeasureKAndRange, 2);
   // Plus Error
   WriteToFile(fileSelKAnd, rMeasureKAndRange, 3);
   // Minus Error
   WriteToFile(fileSelKAnd, rMeasureKAndRange, 4);

   //* kOrRange

   //Cardinality Estimation
   // Estimation
   WriteToFile(fileSelKOr, rMeasureKOrRange, 1);
   // Real
   WriteToFile(fileSelKOr, rMeasureKOrRange, 2);
   // Plus Error
   WriteToFile(fileSelKOr, rMeasureKOrRange, 3);
   // Minus Error
   WriteToFile(fileSelKOr, rMeasureKOrRange, 4);

   //* RingRange

   //Cardinality Estimation
   // Estimation
   WriteToFile(fileSelRing, rMeasureRingRange, 1);
   // Real
   WriteToFile(fileSelRing, rMeasureRingRange, 2);
   // Plus Error
   WriteToFile(fileSelRing, rMeasureRingRange, 3);
   // Minus Error
   WriteToFile(fileSelRing, rMeasureRingRange, 4);


   // Write the pause -1
   fwrite(string, strlen(string), 1, fileSelKAnd);
   fwrite(string, strlen(string), 1, fileSelKOr);
   fwrite(string, strlen(string), 1, fileSelRing);

   //close the files
   fclose(fileSelKAnd);
   fclose(fileSelKOr);
   fclose(fileSelRing);

   //Write log of errors for Simple kOrRange
//   strcpy(fileName, this->Prefix.c_str());
/*   strcpy(fileName, "Log");
   strcat(fileName, "_P");
   strcat(fileName, pageSizeString);
   strcat(fileName, "_R");
   strcat(fileName, percRadius);
   strcat(fileName, "_Q");
   strcat(fileName, third);

   WriteLog(rMeasureSimpleKOrRange, fileName);
   //Write log of errors for Best kOrRange
//   strcpy(fileName, this->Prefix.c_str());
   strcpy(fileName, "LogBest");
   strcat(fileName, "_P");
   strcat(fileName, pageSizeString);
   strcat(fileName, "_R");
   strcat(fileName, percRadius);
   strcat(fileName, "_Q");
   strcat(fileName, third);

   WriteLog(rMeasureBestKOrRange, fileName);

   //Write log of errors for Best kOrRange
//   strcpy(fileName, this->Prefix.c_str());
   strcpy(fileName, "LogBestApp");
   strcat(fileName, "_P");
   strcat(fileName, pageSizeString);
   strcat(fileName, "_R");
   strcat(fileName, percRadius);
   strcat(fileName, "_Q");
   strcat(fileName, third);

   WriteBestLog(rMeasureBestKOrRange, fileName);
*/
   //cleaning...
   delete rMeasureKAndRange;
   delete rMeasureKOrRange;
   delete rMeasureRingRange;

}//end TApp::PerformQuery()

//------------------------------------------------------------------------------
void TApp::PerformKAndRangeQuery(resultMeasure * rMeasure, int i){

   myResult * resultSlim;
   TCity * sample;
   int k, j;
   stDistance kRadius, radiusQuery;
   double  numObj=0, numK=0, logr=0, VObjects=0;

   // The average cardinality
   double avgEstimationK=0, avgRealK=0,  avgRealKplus=0, avgRealKminus=0;


   cout << "\n Perform kAndRange: " << i;
/*   #ifdef __stDebugNearest__
   MetricTreeSlim->numberOfGoodKicks = 0;
   for(int w=0; w<3; w++)
      MetricTreeSlim->numberOfRingCalls[w] = 0;
   #endif //__stDebugNearest__
*/
   //reset the statistics
   PageManagerSlim->ResetStatistics();
   MetricTreeSlim->GetMetricEvaluator()->ResetStatistics();


   k = rMeasure->getK(i);

   for (j=0; j < queryObjects.size(); j++){
      // Create object
      sample = new TCity(queryObjects[j]->GetName().c_str(),
                         queryObjects[j]->GetLatitude(),
                         queryObjects[j]->GetLongitude());

      // Set the Radius Query
      radiusQuery = radiusqueryObjects[j];

      // Estimate first radius
      // check if it is possible to calculate the log funcion
      //Estimate k
      logr = log(radiusQuery);

      VObjects = (5257*5257) - 5257;
      VObjects = log(VObjects);

//      numK = exp(this->NObjects + this->FractalDimension*logr - this->FractalDimension*this->RadiusTree);
      numK = exp(VObjects + this->FractalDimension*logr - this->FractalDimension*this->RadiusTree);

      numK = (1 + sqrt(1 + 4*numK))/2;

      if (numK < k){
        avgEstimationK += numK;
      }
      else{
        avgEstimationK += k;
      } //end if (numK < k)


      resultSlim = MetricTreeSlim->KAndRangeQuery (sample, radiusQuery, k);

      numObj = resultSlim->GetNumOfEntries();

      avgRealK += numObj;

      delete resultSlim;
      delete sample;
   }//end for

   // Setting the errors
//   perc =  0.2;
   avgRealKplus = avgEstimationK + (avgEstimationK * ERRORFD );

   avgRealKminus = avgEstimationK - (avgEstimationK * ERRORFD );


   //Set the Estimation Selectivity - Cardinality
   rMeasure->setEstimationSel(i, avgEstimationK / queryObjects.size());

   //Set the Real Selectivity - Cardinality
   rMeasure->setRealSel(i, avgRealK / queryObjects.size());

   //Set the Real Selectivity - Cardinality
   rMeasure->setRealSelPlus(i, avgRealKplus / queryObjects.size());

   //Set the Real Selectivity - Cardinality
   rMeasure->setRealSelMinus(i, avgRealKminus / queryObjects.size());


//   rMeasure->setDistanceFunction(i,
//      MetricTreeSlim->GetMetricEvaluator()->GetDistanceCount() / queryObjects.size());

/*   #ifdef __stDebugNearest__
   for(int w=0; w<3; w++)
      rMeasure->setErro(w, i, MetricTreeSlim->numberOfRingCalls[w]);

   rMeasure->setAcerto(i, MetricTreeSlim->numberOfGoodKicks);
   #endif //__stDebugNearest__
*/
/*   rMeasure->setBestAcerto(i, radiusKick);
   rMeasure->setBestErro(i, estimateKick);
*/
}//end TApp::PerformKAndRange

//------------------------------------------------------------------------------
void TApp::PerformKOrRangeQuery(resultMeasure * rMeasure, int i){

   myResult * resultSlim;
   TCity * sample;
   int k, j;
   stDistance kRadius, radiusQuery;
   double  numObj=0, numK=0, logr=0, VObjects=0;

   // The average cardinality
   double avgEstimationK=0, avgRealK=0,  avgRealKplus=0, avgRealKminus=0;


   cout << "\n Perform kOrRange: " << i;
/*   #ifdef __stDebugNearest__
   MetricTreeSlim->numberOfGoodKicks = 0;
   for(int w=0; w<3; w++)
      MetricTreeSlim->numberOfRingCalls[w] = 0;
   #endif //__stDebugNearest__
*/
   //reset the statistics
   PageManagerSlim->ResetStatistics();
   MetricTreeSlim->GetMetricEvaluator()->ResetStatistics();


   k = rMeasure->getK(i);

   for (j=0; j < queryObjects.size(); j++){
      // Create object
      sample = new TCity(queryObjects[j]->GetName().c_str(),
                         queryObjects[j]->GetLatitude(),
                         queryObjects[j]->GetLongitude());

      // Set the Radius Query
      radiusQuery = radiusqueryObjects[j];

      // Estimate first radius
      // check if it is possible to calculate the log funcion
      //Estimate k
      logr = log(radiusQuery);

      VObjects = (5257*5257) - 5257;
      VObjects = log(VObjects);

//      numK = exp(this->NObjects + this->FractalDimension*logr - this->FractalDimension*this->RadiusTree);
      numK = exp(VObjects + this->FractalDimension*logr - this->FractalDimension*this->RadiusTree);

      numK = (1 + sqrt(1 + 4*numK))/2;

      if (numK > k){
        avgEstimationK += numK;
      }
      else{
        avgEstimationK += k;
      } //end if (numK < k)


      resultSlim = MetricTreeSlim->KOrRangeQuery (sample, radiusQuery, k);

      numObj = resultSlim->GetNumOfEntries();

      avgRealK += numObj;

      delete resultSlim;
      delete sample;
   }//end for

   // Setting the errors
   avgRealKplus = avgEstimationK + (avgEstimationK * ERRORFD );

   avgRealKminus = avgEstimationK - (avgEstimationK * ERRORFD );


   //Set the Estimation Selectivity - Cardinality
   rMeasure->setEstimationSel(i, avgEstimationK / queryObjects.size());

   //Set the Real Selectivity - Cardinality
   rMeasure->setRealSel(i, avgRealK / queryObjects.size());

   //Set the Real Selectivity - Cardinality
   rMeasure->setRealSelPlus(i, avgRealKplus / queryObjects.size());

   //Set the Real Selectivity - Cardinality
   rMeasure->setRealSelMinus(i, avgRealKminus / queryObjects.size());


//   rMeasure->setDistanceFunction(i,
//      MetricTreeSlim->GetMetricEvaluator()->GetDistanceCount() / queryObjects.size());

/*   #ifdef __stDebugNearest__
   for(int w=0; w<3; w++)
      rMeasure->setErro(w, i, MetricTreeSlim->numberOfRingCalls[w]);

   rMeasure->setAcerto(i, MetricTreeSlim->numberOfGoodKicks);
   #endif //__stDebugNearest__
*/
/*   rMeasure->setBestAcerto(i, radiusKick);
   rMeasure->setBestErro(i, estimateKick);
*/
}//end TApp::PerformKOrRange


//------------------------------------------------------------------------------
void TApp::PerformRingRangeQuery(resultMeasure * rMeasure, int i){

   myResult * resultSlim;
   TCity * sample;
   int k, j;
   stDistance kRadius, radiusQuery, innerRadiusQuery;
   double  numObj=0, numK=0, numK_e=0, numK_i=0, logr=0, VObjects=0;

   // The average cardinality
   double avgEstimationK=0, avgRealK=0,  avgRealKplus=0, avgRealKminus=0;


   cout << "\n Perform RingRange: " << i;
/*   #ifdef __stDebugNearest__
   MetricTreeSlim->numberOfGoodKicks = 0;
   for(int w=0; w<3; w++)
      MetricTreeSlim->numberOfRingCalls[w] = 0;
   #endif //__stDebugNearest__
*/
   //reset the statistics
   PageManagerSlim->ResetStatistics();
   MetricTreeSlim->GetMetricEvaluator()->ResetStatistics();


   k = rMeasure->getK(i);

   for (j=0; j < queryObjects.size(); j++){
      // Create object
      sample = new TCity(queryObjects[j]->GetName().c_str(),
                         queryObjects[j]->GetLatitude(),
                         queryObjects[j]->GetLongitude());

      // Set the Radius Query
      radiusQuery = radiusqueryObjects[j];
      innerRadiusQuery = innerRadiusqueryObjects[j];


      // This gives an better estimation than NObjects
      VObjects = (5257*5257) - 5257;
      VObjects = log(VObjects);

//      numK = exp(this->NObjects + this->FractalDimension*logr - this->FractalDimension*this->RadiusTree);

      //Estimate outer k
      logr = log(radiusQuery);

      // Estimating the outer number of objects
      numK_e = exp(VObjects + this->FractalDimension*logr - this->FractalDimension*this->RadiusTree);
      numK_e = (1 + sqrt(1 + 4*numK_e))/2;

      //Estimate inner k
      logr = log(innerRadiusQuery);

      // Estimating the inner number of objects
      numK_i = exp(VObjects + this->FractalDimension*logr - this->FractalDimension*this->RadiusTree);
      numK_i = (1 + sqrt(1 + 4*numK_i))/2;

      // Estimating the Cardinality
      numK = numK_e - numK_i;
      avgEstimationK += numK;

      // Perform the Ring Query
      resultSlim = MetricTreeSlim->RingQuery (sample, innerRadiusQuery, radiusQuery);

      // Getting the real query cardinality  
      numObj = resultSlim->GetNumOfEntries();
      avgRealK += numObj;

      delete resultSlim;
      delete sample;
   }//end for

   // Setting the errors
//   perc =  0.2;
   avgRealKplus = avgEstimationK + (avgEstimationK * ERRORFD );

   avgRealKminus = avgEstimationK - (avgEstimationK * ERRORFD );


   //Set the Estimation Selectivity - Cardinality
   rMeasure->setEstimationSel(i, avgEstimationK / queryObjects.size());

   //Set the Real Selectivity - Cardinality
   rMeasure->setRealSel(i, avgRealK / queryObjects.size());

   //Set the Real Selectivity - Cardinality
   rMeasure->setRealSelPlus(i, avgRealKplus / queryObjects.size());

   //Set the Real Selectivity - Cardinality
   rMeasure->setRealSelMinus(i, avgRealKminus / queryObjects.size());


//   rMeasure->setDistanceFunction(i,
//      MetricTreeSlim->GetMetricEvaluator()->GetDistanceCount() / queryObjects.size());

/*   #ifdef __stDebugNearest__
   for(int w=0; w<3; w++)
      rMeasure->setErro(w, i, MetricTreeSlim->numberOfRingCalls[w]);

   rMeasure->setAcerto(i, MetricTreeSlim->numberOfGoodKicks);
   #endif //__stDebugNearest__
*/
/*   rMeasure->setBestAcerto(i, radiusKick);
   rMeasure->setBestErro(i, estimateKick);
*/
}//end TApp::PerformRingRange




/*
//------------------------------------------------------------------------------
void TApp::PerformSimpleKOrRangeQuery(resultMeasure * rMeasure, int i){

   myResult * resultSlim;
   TCity * sample;
   clock_t start, end;
   long nroObjectsTree;
   int k, j;


   cout << "\n Perform Simple kOrRange: " << i;
      #ifdef __stDebugNearest__
      MetricTreeSlim->numberOfGoodKicks = 0;
      for(int w=0; w<3; w++)
         MetricTreeSlim->numberOfRingCalls[w] = 0;
      #endif //__stDebugNearest__

      //reset the statistics
      PageManagerSlim->ResetStatistics();
      MetricTreeSlim->GetMetricEvaluator()->ResetStatistics();

      k = rMeasure->getK(i);

      start = clock();
      for (j=0; j < queryObjects.size(); j++){
         sample = new TCity(queryObjects[j]->GetName().c_str(),
                            queryObjects[j]->GetLatitude(),
                            queryObjects[j]->GetLongitude());
         resultSlim = MetricTreeSlim->SimpleKOrRangeQuery (sample, this->FractalDimension,
                                      this->NObjects, radiusqueryObjects[j], k);
         delete resultSlim;
         delete sample;
      }//end for
      end = clock();


      //time in ms
      rMeasure->setTotalTime(i, (double) end - (double) start);
      // is divided for queryObjects to get the everage
      rMeasure->setDiscAccess(i, PageManagerSlim->GetReadCount() / queryObjects.size());
      // is divided for queryObjects to get the everage
      rMeasure->setDistanceFunction(i,
         MetricTreeSlim->GetMetricEvaluator()->GetDistanceCount() / queryObjects.size());

      #ifdef __stDebugNearest__
      for(int w=0; w<3; w++)
         rMeasure->setErro(w, i, MetricTreeSlim->numberOfRingCalls[w]);
      rMeasure->setAcerto(i, MetricTreeSlim->numberOfGoodKicks);
      #endif //__stDebugNearest__

}//end TApp::PerformSimpleKOrRange



//------------------------------------------------------------------------------
void TApp::PerformKOrRangeQuery(resultMeasure * rMeasure, int i){

   myResult * resultSlim;
   TCity * sample;
   clock_t start, end;
   int k, j;

   cout << "\n Perform Default kOrRange: " << i;
   PageManagerSlim->ResetStatistics();
   MetricTreeSlim->GetMetricEvaluator()->ResetStatistics();

   k = rMeasure->getK(i);

   start = clock();
   for (j=0; j < queryObjects.size(); j++){
      sample = new TCity(queryObjects[j]->GetName().c_str(),
                         queryObjects[j]->GetLatitude(),
                         queryObjects[j]->GetLongitude());
      resultSlim = MetricTreeSlim->KOrRangeQuery(sample, radiusqueryObjects[j],
                                                 k);
      delete resultSlim;
      delete sample;
   }//end for
   end = clock();

   // time in ms
   rMeasure->setTotalTime(i, (double) end - (double) start);
   // is divided for queryObjects to get the everage
   rMeasure->setDiscAccess(i, PageManagerSlim->GetReadCount() / queryObjects.size());
   // is divided for queryObjects to get the everage
   rMeasure->setDistanceFunction(i,
      MetricTreeSlim->GetMetricEvaluator()->GetDistanceCount() / queryObjects.size());

}//end TApp::PerformQueryNearest

//------------------------------------------------------------------------------
void TApp::PerformRangeQuery(resultMeasure * rMeasure, int i){

   myResult * resultSlim;
   TCity * sample;
   clock_t start, end;
   int k, j;

   cout << "\n Perform Range Query: " << i;
   //reset the statistics
   PageManagerSlim->ResetStatistics();
   MetricTreeSlim->GetMetricEvaluator()->ResetStatistics();

   k = rMeasure->getK(i);

   start = clock();
   for (j=0; j < queryObjects.size(); j++){
     sample = new TCity(queryObjects[j]->GetName().c_str(),
                        queryObjects[j]->GetLatitude(),
                        queryObjects[j]->GetLongitude());
     resultSlim = MetricTreeSlim->RangeQuery(sample, radiusqueryObjects[j]);
     delete resultSlim;
     delete sample;
   }//end for
   end = clock();

   // time in ms
   rMeasure->setTotalTime(i, (double) end - (double) start);
   // is divided for queryObjects to get the everage
   rMeasure->setDiscAccess(i, PageManagerSlim->GetReadCount() / queryObjects.size());
   // is divided for queryObjects to get the everage
   rMeasure->setDistanceFunction(i,
      MetricTreeSlim->GetMetricEvaluator()->GetDistanceCount() / queryObjects.size());

}//end TApp::PerformrRangeQuery
//------------------------------------------------------------------------------
void TApp::WriteLog(resultMeasure * resultSlim, char * name){

   char strTemp[500], string[10];
   FILE * fileStats;

   strcpy(strTemp, name);
   strcat(strTemp, ".plt");
   fileStats = fopen(strTemp, "w");
   //write the statistics to files
   //set the name and the header of the file for statistics
   strcpy(strTemp,"set title \"Statistics for Queries ");
   strcat(strTemp, name);
   fwrite(strTemp, strlen(strTemp), 1, fileStats);
   strcpy(strTemp,"\"\nset xlabel \"k\"\n");
   fwrite(strTemp, strlen(strTemp), 1, fileStats);
   strcpy(strTemp,"set ylabel \"# of Queries\"\n");
   fwrite(strTemp, strlen(strTemp), 1, fileStats);
   strcpy(strTemp,"plot '-' title '(A) Zero Ring Call' with linespoints 1,");
   strcat(strTemp," '-' title '(B) One Ring Call' with linespoints 2,");
   strcat(strTemp," '-' title '(C) Two Ring Call' with linespoints 3,");
   strcat(strTemp," '-' title '(D) Three Ring Call' with linespoints 4\n\n");
   fwrite(strTemp, strlen(strTemp), 1, fileStats);

   #ifdef __stDebugNearest__
   for(int i=0; i < this->DatasetSize; i++){
      fprintf(fileStats, "%d\t%d\n", resultSlim->getK(i), resultSlim->getAcerto(i));
   }//end for
   strcpy(strTemp, "end\n");
   fwrite(strTemp, strlen(strTemp), 1, fileStats);
   for(int j=0; j<3; j++){
      for(int i=0; i < this->DatasetSize; i++){
         fprintf(fileStats, "%d\t%d\n", resultSlim->getK(i), resultSlim->getErro(j,i));
      }//end for
      strcpy(strTemp, "end\n");
      fwrite(strTemp, strlen(strTemp), 1, fileStats);
   }//end for
   #endif //__stDebugNearest__

   strcpy(strTemp, "\n\npause -1");
   fwrite(strTemp, strlen(strTemp), 1, fileStats);
   fclose(fileStats);

}//end TApp::WriteLog()
*/

//------------------------------------------------------------------------------
void TApp::WriteHeader(FILE * file, char * type){
   char * strTemp = new char[500];
   char pageSize[10];
   char tmpString[10];

   itoa(this->PageSize, pageSize, 10);

   // Title
   strcpy(strTemp,"set title \"Cidades Brasileiras - Estimativa de Seletividade");
   fwrite(strTemp, strlen(strTemp), 1, file);

   strcpy(strTemp,"  page=");
   fwrite(strTemp, strlen(strTemp), 1, file);
   fwrite(pageSize, strlen(pageSize), 1, file);
   // End Title
   // x and y label
   strcpy(strTemp,"\"\nset xlabel \"k\"\n");
   fwrite(strTemp, strlen(strTemp), 1, file);
   strcpy(strTemp, type);
   fwrite(strTemp, strlen(strTemp), 1, file);
   strcpy(strTemp, "set xrange [0.001:0.1]\n");
   fwrite(strTemp, strlen(strTemp), 1, file);

   strcpy(strTemp,"set logscale y \n");
   fwrite(strTemp, strlen(strTemp), 1, file);


   // Plots
   strcpy(strTemp,"plot '-' title '(A) Cardinalidade usando Seletividade XX' with linespoints 1, ");
   strcat(strTemp,"'-' title '(B) Cardinalidade Real' with linespoints 2, ");
   strcat(strTemp,"'-' title '(C) Erro Acima' with linespoints 3, ");
   strcat(strTemp,"'-' title '(D) Erro Abaixo' with linespoints 4\n\n");

   fwrite(strTemp, strlen(strTemp), 1, file);

   strcpy(strTemp,"####################\n");
   fwrite(strTemp, strlen(strTemp), 1, file);

   delete strTemp;
}//end TApp::WriteHeader()


//------------------------------------------------------------------------------
void TApp::WriteToFile(FILE * file, resultMeasure * rMeasure, int type){
   char * strTemp = new char[500];
   char * string = new char[50];

   //write the statistics to files
   for(int i=0; i < rMeasure->getSize(); i++){
      strcpy(strTemp, itoa(rMeasure->getK(i),string,10));
      strcat(strTemp, "\t");
      fwrite(strTemp, strlen(strTemp), 1, file);
      // Write the cardinalities
      switch(type){

        case 1:  fprintf(file, "%f", rMeasure->getEstimationSel(i));
                 break;

        case 2:  fprintf(file, "%f", rMeasure->getRealSel(i));
                 break;

        case 3:  fprintf(file, "%f", rMeasure->getRealSelPlus(i));
                 break;

        case 4:  fprintf(file, "%f", rMeasure->getRealSelMinus(i));
                 break;

      } //end   switch(type){

      strcpy(strTemp, "\n");
      fwrite(strTemp, strlen(strTemp), 1, file);
   }//end for
   strcpy(strTemp, "end\n");
   strcat(strTemp, "####################\n");
   fwrite(strTemp, strlen(strTemp), 1, file);

   delete strTemp;
   delete string;
}//end TApp::WriteToFile()

/*
//------------------------------------------------------------------------------
void TApp::WriteBestLog(resultMeasure * resultSlim, char * name){

   char strTemp[500], string[10];
   FILE * fileStats;

   strcpy(strTemp, name);
   strcat(strTemp, ".plt");
   fileStats = fopen(strTemp, "w");
   //write the statistics to files
   //set the name and the header of the file for statistics
   strcpy(strTemp,"set title \"Statistics for Best Approach ");
   strcat(strTemp, name);
   fwrite(strTemp, strlen(strTemp), 1, fileStats);
   strcpy(strTemp,"\"\nset xlabel \"k\"\n");
   fwrite(strTemp, strlen(strTemp), 1, fileStats);
   strcpy(strTemp,"set ylabel \"# of Queries\"\n");
   fwrite(strTemp, strlen(strTemp), 1, fileStats);
   strcpy(strTemp,"plot '-' title '(A) # of Good Kicks' with linespoints 1,");
   strcat(strTemp," '-' title '(B) # of Wrong Kicks' with linespoints 2\n\n");
   fwrite(strTemp, strlen(strTemp), 1, fileStats);

   for(int i=0; i < this->DatasetSize; i++){
      fprintf(fileStats, "%d\t%d\n", resultSlim->getK(i), resultSlim->getBestAcerto(i));
   }//end for
   strcpy(strTemp, "end\n");
   fwrite(strTemp, strlen(strTemp), 1, fileStats);

   for(int i=0; i< this->DatasetSize; i++){
     fprintf(fileStats, "%d\t%d\n", resultSlim->getK(i), resultSlim->getBestErro(i));
   }//end for
   strcpy(strTemp, "end\n");
   fwrite(strTemp, strlen(strTemp), 1, fileStats);


   strcpy(strTemp, "\n\npause -1");
   fwrite(strTemp, strlen(strTemp), 1, fileStats);
   fclose(fileStats);

}//end TApp::WriteLog()

//------------------------------------------------------------------------------
/**
* Prints the result set to the standard output.
*
* @param result The result to be printed.
*/
void TApp::PrintResults(myResult * result){
   int w;
   TCity * tmp;

   if (result->GetNumOfEntries() == 0){
      cout << "No results!\n";
   }else{
      cout << "   " << result->GetNumOfEntries() << " results:\n";
      for (w = 0; w < result->GetNumOfEntries(); w++){
         tmp = (TCity *)(*result)[w].GetObject();
         cout << "      Distance = " << (*result)[w].GetDistance() <<
               " - Object = ";
         cout << *tmp << "\n";
      }//end for
   }//end if
}//end TApp::PrintResults

//------------------------------------------------------------------------------
void TApp::SetRadiusFromObjects(resultMeasure * rMeasureSlim, int i){

   myResult * result;
   TCity * sample;
   long numberOfObjects;
   int j;
   double radius;

   unsigned int oneThird;

   // How many is One Third of queries?
   oneThird = (unsigned int) floor(queryObjects.size() / this->Third);

   //clear before insert new radium values
   radiusqueryObjects.clear();
   // set the number of objects.
   numberOfObjects = rMeasureSlim->getK(i);

   // perform the query.
   for (j=0; j < queryObjects.size(); j++){

     sample = new TCity(queryObjects[j]->GetName().c_str(),
                        queryObjects[j]->GetLatitude(),
                        queryObjects[j]->GetLongitude());

     result = MetricTreeSlim->NearestQuery(sample, numberOfObjects);


     // set the radius.
     radius = result->GetMaximumDistance();

     if (this->DifRadius){
       if (j < oneThird){
         radius = radius + (radius * this->PercRadius);
       }
       else{
         if (j >= oneThird && (j < (2*oneThird)) ){
           radius = radius - (radius * this->PercRadius);
         } //end if
       }//end if*/
     }//end if (this->DifRadius)

     if (radius < 0)
       radius = 0.00;

     /////////////////////////////
     radiusqueryObjects.insert(radiusqueryObjects.end(), radius);
     delete result;
     delete sample;
  }//end for

}//end TApp::SetRadiusFromObjects


//------------------------------------------------------------------------------
void TApp::SetRadiusToRingObjects(resultMeasure * rMeasureSlim, int i){

   myResult * result;
   TCity * sample;
   long numberOfObjects;
   int j;
   double radius=0, innerRadius=0;

   unsigned int oneThird;

   // How many is One Third of queries?
   oneThird = (unsigned int) floor(queryObjects.size() / this->Third);

   //clear before insert new radium values
   radiusqueryObjects.clear();
   // set the number of objects.
   numberOfObjects = rMeasureSlim->getK(i);

   // perform the query.
   for (j=0; j < queryObjects.size(); j++){

     sample = new TCity(queryObjects[j]->GetName().c_str(),
                        queryObjects[j]->GetLatitude(),
                        queryObjects[j]->GetLongitude());

     result = MetricTreeSlim->NearestQuery(sample, numberOfObjects);


     // set the radius.
     radius = result->GetMaximumDistance();
     innerRadius = radius - (radius * 0.20);

     if (innerRadius < 0)
       radius = 0.00;

     /////////////////////////////
     radiusqueryObjects.insert(radiusqueryObjects.end(), radius);
     innerRadiusqueryObjects.insert(innerRadiusqueryObjects.end(), innerRadius);

     delete result;
     delete sample;
  }//end for

}//end TApp::SetRadiusToRingObjects



/****************************************************************************
*****************************************************************************

//------------------------------------------------------------------------------
void TApp::PerformBestKOrRangeQuery(resultMeasure * rMeasure, int i){

   myResult * resultSlim;
   TCity * sample;
   clock_t start, end;
//   long nroObjectsTree;
   int k, j, rightKick, wrongKick;
   stDistance kRadius;

   double logK=0, numK=0, logr=0;


   cout << "\n Perform Best kOrRange: " << i;
   #ifdef __stDebugNearest__
   MetricTreeSlim->numberOfGoodKicks = 0;
   for(int w=0; w<3; w++)
      MetricTreeSlim->numberOfRingCalls[w] = 0;
   #endif //__stDebugNearest__

   //reset the statistics
   PageManagerSlim->ResetStatistics();
   MetricTreeSlim->GetMetricEvaluator()->ResetStatistics();


   k = rMeasure->getK(i);

   rightKick = 0;
   wrongKick = 0;

      start = clock();
      for (j=0; j < queryObjects.size(); j++){
         // Create object
         sample = new TCity(queryObjects[j]->GetName().c_str(),
                            queryObjects[j]->GetLatitude(),
                            queryObjects[j]->GetLongitude());

         // Estimate first radius
         // check if it is possible to calculate the log funcion
         //Estimate k

         logr = log(radiusqueryObjects[j]);

         numK = exp(NOBJECTS + FRACTALDIMENSION*logr - FRACTALDIMENSION*RADIUSTREE);

         numK = (1 + sqrt(1 + 4*numK))/2;

         if (numK >= k){
           resultSlim = MetricTreeSlim->SimpleKOrRangeQuery (sample, FRACTALDIMENSION,
                                             NOBJECTS, radiusqueryObjects[j], k);

           if (j >= 150 && j < 300)
             resultSlim = MetricTreeSlim->KOrRangeQuery(sample, radiusqueryObjects[j],
                                                      k, true);
           else
             resultSlim = MetricTreeSlim->SimpleKOrRangeQuery (sample, FRACTALDIMENSION,
                                             NOBJECTS, radiusqueryObjects[j], k);

         }else{
           resultSlim = MetricTreeSlim->KOrRangeQueryOld(sample, radiusqueryObjects[j],
                                                      k, true);

           if (j >= 240 && j < 300)
             rightKick++;
           else
             wrongKick++;
         }// end if (firstRange <= radiusqueryObjects[j])


         // Estimate Radius
         if (k > 2)
           logK = log(k*(k-1)/2);



         kRadius = exp( (logK - NOBJECTS)/FRACTALDIMENSION + RADIUSTREE);

         if (kRadius <= radiusqueryObjects[j]){
           resultSlim = MetricTreeSlim->SimpleKOrRangeQuery (sample, FRACTALDIMENSION,
                                             NOBJECTS, radiusqueryObjects[j], k);

           if (j >= 360)
             wrongKick++;
           else
             rightKick++;

         }else{
           resultSlim = MetricTreeSlim->KOrRangeQuery(sample, radiusqueryObjects[j],
                                                      k);
           if (j >= 360)
             rightKick++;
           else
             wrongKick++;
         }// end if (firstRange <= radiusqueryObjects[j])

         #ifdef __stDebugNearest__
         average += resultSlim->GetMaximumDistance();
         if(minDistance > resultSlim->GetMaximumDistance())
            minDistance = resultSlim->GetMaximumDistance();
         if(maxDistance < resultSlim->GetMaximumDistance())
            maxDistance = resultSlim->GetMaximumDistance();
         #endif //__stDebugNearest__
         delete resultSlim;
         delete sample;
      }//end for
      end = clock();
      //time in ms
      rMeasure->setTotalTime(i, (double) end - (double) start);
      // is divided for queryObjects to get the everage
      rMeasure->setDiscAccess(i, PageManagerSlim->GetReadCount() / queryObjects.size());
      // is divided for queryObjects to get the everage
      rMeasure->setDistanceFunction(i,
         MetricTreeSlim->GetMetricEvaluator()->GetDistanceCount() / queryObjects.size());

      #ifdef __stDebugNearest__
      for(int w=0; w<3; w++)
         rMeasure->setErro(w, i, MetricTreeSlim->numberOfRingCalls[w]);

      rMeasure->setAcerto(i, MetricTreeSlim->numberOfGoodKicks);
      cout << "\n distancia estimada: " << exp( (log(rMeasure->getK(i)*(rMeasure->getK(i)-1)/2) - 16.441294)/fractalDimension + 4.62 + 0.1*4.62);
      cout << "\n minDistance: " << minDistance << " maxDistance: " << maxDistance << " media: " << average/queryObjects.size();
      cout << "\n  passo:" << i << " acertos:" << rMeasure->getAcerto(i) << " - ring1:" << rMeasure->getErro(0,i) << " - ring2:" << rMeasure->getErro(1,i) << " - ring3:" << rMeasure->getErro(2,i);
      cout << "\n" <<  ((log(rMeasure->getK(i)*(rMeasure->getK(i)-1)/2) - 16.441294)/fractalDimension +4.62) + 0.1*4.62 << "\t" << log((56*i + 25)*(56*i + 25 -1)/2);

      #endif //__stDebugNearest__

      rMeasure->setBestAcerto(i, rightKick);
      rMeasure->setBestErro(i, wrongKick);
      cout << "Chutes certos: " << rightKick << "\n";
      cout << "Chutes errados: " << wrongKick << "\n";
  // }//end for

}//end TApp::PerformBestKOrRange
*/
