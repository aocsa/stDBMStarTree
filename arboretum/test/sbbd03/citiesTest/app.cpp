//---------------------------------------------------------------------------
// app.cpp - Implementation of the application.
//
// To change the behavior of this application, comment and uncomment lines at
// TApp::Init() and TApp::Query().
//
// Authors: Marcos Rodrigues Vieira (mrvieira@icmc.sc.usp.br)
//          Adriano Arantes (arantes@icmc.sc.usp.br)
// Copyright (c) 2003 GBDI-ICMC-USP
//---------------------------------------------------------------------------
#include <iostream>
#pragma hdrstop
#include "app.h"

//#define RAIO 1000  //se 1000, vai ateh raio 100% = raio 1 (valor absoluto)
//ateh raio 10% = raio 0.1 (valor absoluto)
#define RAIO 100
// quantidade de amostra
#define QUANTIDADE 10

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

   // Lets load the tree with a lot values from the file.
   LoadTree("cidades.txt");
   //load the query collection from the file
   LoadVectorFromFile("cidades500.txt");
   // Lets do the queries
   PerformQueries();
   // Hold the screen.
   cout << "Finished the whole test!\n";
   cin.get();
}//end TApp::Run

//------------------------------------------------------------------------------
void TApp::Done(){

   if (this->MetricTreeDummy != NULL){
      delete this->MetricTreeDummy;
   }//end if
   if (this->MetricTreeSlim != NULL){
      delete this->MetricTreeSlim;
   }//end if
   if (this->PageManagerSlim != NULL){
      delete this->PageManagerSlim;
   }//end if
   if (this->PageManagerDummy != NULL){
      delete this->PageManagerDummy;
   }//end if
}//end TApp::Done

//------------------------------------------------------------------------------
void TApp::CreateDiskPageManager(){
   //for Slim-tree
   stDiskPageManager * dmanSlim = new stDiskPageManager();
   // Filename is mySlimTree.dat
   dmanSlim->Create("mySlimTree.dat", 1024);
   PageManagerSlim = dmanSlim;
   //for Dummy-tree
   stDiskPageManager * dmanDummy = new stDiskPageManager();
   // Filename is myDummyTree.dat
   dmanDummy->Create("myDummyTree.dat", 1024);
   PageManagerDummy = dmanDummy;
}//end TApp::CreateDiskPageManager

//------------------------------------------------------------------------------
void TApp::CreateTree(){
   //create for Slim-tree
   mySlimTree * slimtree = new mySlimTree(PageManagerSlim);
   MetricTreeSlim = slimtree;
   //create for Dummy-tree
   myDummyTree * dummytree = new myDummyTree(PageManagerDummy);
   MetricTreeDummy = dummytree;
   //total number of objects that the tree has
   numberOfObjects = 0L;
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
void TApp::PerformQueries(){

   char string[] = "\npause -1";
   char tmpString[10];
   char fileName[200];
   FILE * fileDistFuncAND, * fileTimeAND, * fileDiscAccessAND;
   FILE * fileDistFuncOR, * fileTimeOR, * fileDiscAccessOR;
   int idx = 0;
   //for the result of the tests
   resultMeasure * rMeasureSlimKAndRange = new resultMeasure(QUANTIDADE);
   resultMeasure * rMeasureDummyKAndRange = new resultMeasure(QUANTIDADE);
   resultMeasure * rMeasureSlimKRange_And = new resultMeasure(QUANTIDADE);
   resultMeasure * rMeasureDummyKRange_And = new resultMeasure(QUANTIDADE);
   resultMeasure * rMeasureSlimKOrRange = new resultMeasure(QUANTIDADE);
   resultMeasure * rMeasureDummyKOrRange = new resultMeasure(QUANTIDADE);
   resultMeasure * rMeasureSlimKRange_Or = new resultMeasure(QUANTIDADE);
   resultMeasure * rMeasureDummyKRange_Or = new resultMeasure(QUANTIDADE);

   for(int radius=10; radius<=RAIO; radius*=10){  // raio comecando de 0.01 = 1% (valor absoluto)
      //set the name and the header of the file
      //for the AND clausure
      strcpy(fileName, "kAndR");
      strcat(fileName, itoa(radius,tmpString,10));
      strcat(fileName, "DistFunc.plt");
      fileDistFuncAND = fopen(fileName, "w");
      WriteHeader(fileDistFuncAND, "set ylabel \"# AVG Distance Function\"\n", true, radius);
      strcpy(fileName, "kAndR");
      strcat(fileName, itoa(radius,tmpString,10));
      strcat(fileName, "DiscAccess.plt");
      fileDiscAccessAND = fopen(fileName, "w");
      WriteHeader(fileDiscAccessAND, "set ylabel \"# AVG Disk Access\"\n", true, radius);
      strcpy(fileName, "kAndR");
      strcat(fileName, itoa(radius,tmpString,10));
      strcat(fileName, "Time.plt");
      fileTimeAND = fopen(fileName, "w");
      WriteHeader(fileTimeAND, "set ylabel \"Total Time\"\n", true, radius);

      //for the OR clausure
      strcpy(fileName, "kOrR");
      strcat(fileName, itoa(radius,tmpString,10));
      strcat(fileName, "DistFunc.plt");
      fileDistFuncOR = fopen(fileName, "w");
      WriteHeader(fileDistFuncOR, "set ylabel \"# AVG Distance Function\"\n", true, radius);
      strcpy(fileName, "kOrR");
      strcat(fileName, itoa(radius,tmpString,10));
      strcat(fileName, "DiscAccess.plt");
      fileDiscAccessOR = fopen(fileName, "w");
      WriteHeader(fileDiscAccessOR, "set ylabel \"# AVG Disk Access\"\n", true, radius);
      strcpy(fileName, "kOrR");
      strcat(fileName, itoa(radius,tmpString,10));
      strcat(fileName, "Time.plt");
      fileTimeOR = fopen(fileName, "w");
      WriteHeader(fileTimeOR, "set ylabel \"# Total Time\"\n", true, radius);

      //perform the new query algorith
      cout << "\nTests with radius: " << radius*0.001 << "\n\n";

      //set the radius of the objects
      cout << "Calculating the absolute radius from the sample query.... ";
      SetRadiusFromObjects(radius*0.001);
      cout << "Ok\n";

      cout << "Starting Statistics for kAndRange .... ";
      PerformQueryKAndRange(rMeasureSlimKAndRange, rMeasureDummyKAndRange);
      cout << "Ok\n";

      //perform the old query algorith
      cout << "Starting Statistics for k-Nearest AND Range Query.... ";
      PerformQueryKRange_And(rMeasureSlimKRange_And, rMeasureDummyKRange_And);
      cout << "Ok\n";

      //perform the new query algorith
      cout << "Starting Statistics for kOrRange.... ";
      PerformQueryKOrRange(rMeasureSlimKOrRange, rMeasureDummyKOrRange);
      cout << "Ok\n";

      //perform the old query algorith
      cout << "Starting Statistics for k-Nearest OR Range Query.... ";
      PerformQueryKRange_Or(rMeasureSlimKRange_Or, rMeasureDummyKRange_Or);
      cout << "Ok\n";

      //Distance Function
      WriteToFile(fileDistFuncAND, rMeasureSlimKAndRange, 1);
      WriteToFile(fileDistFuncAND, rMeasureSlimKRange_And, 1);
      WriteToFile(fileDistFuncAND, rMeasureDummyKAndRange, 1);
      WriteToFile(fileDistFuncAND, rMeasureDummyKRange_And, 1);
      //Disc Access
      WriteToFile(fileDiscAccessAND, rMeasureSlimKAndRange, 2);
      WriteToFile(fileDiscAccessAND, rMeasureSlimKRange_And, 2);
      WriteToFile(fileDiscAccessAND, rMeasureDummyKAndRange, 2);
      WriteToFile(fileDiscAccessAND, rMeasureDummyKRange_And, 2);
      //Total Time
      WriteToFile(fileTimeAND, rMeasureSlimKAndRange, 3);
      WriteToFile(fileTimeAND, rMeasureSlimKRange_And, 3);
      WriteToFile(fileTimeAND, rMeasureDummyKAndRange, 3);
      WriteToFile(fileTimeAND, rMeasureDummyKRange_And, 3);

      //Distance Function
      WriteToFile(fileDistFuncOR, rMeasureSlimKOrRange, 1);
      WriteToFile(fileDistFuncOR, rMeasureSlimKRange_Or, 1);
      WriteToFile(fileDistFuncOR, rMeasureDummyKOrRange, 1);
      WriteToFile(fileDistFuncOR, rMeasureDummyKRange_Or, 1);
      //Disc Access
      WriteToFile(fileDiscAccessOR, rMeasureSlimKOrRange, 2);
      WriteToFile(fileDiscAccessOR, rMeasureSlimKRange_Or, 2);
      WriteToFile(fileDiscAccessOR, rMeasureDummyKOrRange, 2);
      WriteToFile(fileDiscAccessOR, rMeasureDummyKRange_Or, 2);
      //Total Time
      WriteToFile(fileTimeOR, rMeasureSlimKOrRange, 3);
      WriteToFile(fileTimeOR, rMeasureSlimKRange_Or, 3);
      WriteToFile(fileTimeOR, rMeasureDummyKOrRange, 3);
      WriteToFile(fileTimeOR, rMeasureDummyKRange_Or, 3);

      fwrite(string, strlen(string), 1, fileDistFuncAND);
      fwrite(string, strlen(string), 1, fileDiscAccessAND);
      fwrite(string, strlen(string), 1, fileTimeAND);
      fwrite(string, strlen(string), 1, fileDistFuncOR);
      fwrite(string, strlen(string), 1, fileDiscAccessOR);
      fwrite(string, strlen(string), 1, fileTimeOR);
      //close the files
      fclose(fileDistFuncAND);
      fclose(fileTimeAND);
      fclose(fileDiscAccessAND);
      fclose(fileDistFuncOR);
      fclose(fileTimeOR);
      fclose(fileDiscAccessOR);
      //increments the counter
      idx++;
   }//end for

   //cleaning...
   delete rMeasureSlimKAndRange;
   delete rMeasureDummyKAndRange;
   delete rMeasureSlimKRange_And;
   delete rMeasureDummyKRange_And;
   delete rMeasureSlimKOrRange;
   delete rMeasureDummyKOrRange;
   delete rMeasureSlimKRange_Or;
   delete rMeasureDummyKRange_Or;
}//end TApp::PerformQuery()

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
      do{ // Because there is 500 cities
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
                    queryCities.insert(queryCities.end(), new TCity(city, dlat, dlong));
                    contObj++;
                    cont = 0;
         }//end switch
        fgets(buffer, 60, f);
      }while(!feof(f));//end while
      cout << "Added " << contObj << " objects...\n";
      fclose(f);
   }//end else
}//end TApp::LoadVectorFromFile

//------------------------------------------------------------------------------
void TApp::PerformQueryKAndRange(resultMeasure * rMeasureSlim,
                                 resultMeasure * rMeasureDummy){

   myResult * resultSlim, * resultDummy;
   TCity * sample;
   clock_t start, end;

   cout << "\n PerformQuery KAndRange: ";
   //For number of points (radius) that I want measure.
   for(int i=0; i < rMeasureSlim->getSize(); i++){
      PageManagerSlim->ResetStatistics();
      PageManagerDummy->ResetStatistics();
      MetricTreeSlim->GetMetricEvaluator()->ResetStatistics();
      MetricTreeDummy->GetMetricEvaluator()->ResetStatistics();

      start = clock();
      for (int j=0; j < queryCities.size(); j++){
         sample = new TCity(queryCities[j]->GetName().c_str(),
                            queryCities[j]->GetLatitude(),
                            queryCities[j]->GetLongitude());
         resultSlim = MetricTreeSlim->KAndRangeQuery(sample, radiusQueryCities[j],
                                                     rMeasureSlim->getK(i));
         delete resultSlim;
         delete sample;
      }//end for
      end = clock();
      //to return the average in ms
      rMeasureSlim->setTotalTime(i, (1000*(end-start))/CLK_TCK);
      rMeasureSlim->setDiscAccess(i, PageManagerSlim->GetReadCount() / queryCities.size());
      rMeasureSlim->setDistanceFunction(i, MetricTreeSlim->GetMetricEvaluator()->GetDistanceCount() /
      												 queryCities.size());

      start = clock();
      for (int j=0; j < queryCities.size(); j++){
         sample = new TCity(queryCities[j]->GetName().c_str(),
                            queryCities[j]->GetLatitude(),
                            queryCities[j]->GetLongitude());
         resultDummy = MetricTreeDummy->KAndRangeQuery(sample, radiusQueryCities[j],
                                                 rMeasureDummy->getK(i));
         delete resultDummy;
         delete sample;
      }//end for
      end = clock();
      //to return the average in ms
      rMeasureDummy->setTotalTime(i, (1000*(end-start))/CLK_TCK);
      rMeasureDummy->setDiscAccess(i, PageManagerDummy->GetReadCount() / queryCities.size());
      rMeasureDummy->setDistanceFunction(i, MetricTreeDummy->GetMetricEvaluator()->GetDistanceCount() /
      													 queryCities.size());

      cout << i << " ";
   }//end for

}//end TApp::PerformQueryKAndRange

//------------------------------------------------------------------------------
void TApp::PerformQueryKOrRange(resultMeasure * rMeasureSlim,
                                resultMeasure * rMeasureDummy){

   myResult * resultSlim, * resultDummy;
   TCity * sample;
   clock_t start, end;

   cout << "\n PerformQuery KOrRange: ";
   //For number of points (radius) that I want measure.
   for(int i=0; i < rMeasureSlim->getSize(); i++){
      PageManagerSlim->ResetStatistics();
      PageManagerDummy->ResetStatistics();
      MetricTreeSlim->GetMetricEvaluator()->ResetStatistics();
      MetricTreeDummy->GetMetricEvaluator()->ResetStatistics();

      start = clock();
      for (int j=0; j<queryCities.size(); j++){
         sample = new TCity(queryCities[j]->GetName().c_str(),
                            queryCities[j]->GetLatitude(),
                            queryCities[j]->GetLongitude());
         resultSlim = MetricTreeSlim->KOrRangeQuery(sample, radiusQueryCities[j],
                                                    rMeasureSlim->getK(i));
         delete resultSlim;
         delete sample;
      }//end for
      end = clock();
		//to return the average in ms
      rMeasureSlim->setTotalTime(i, (1000*(end-start))/CLK_TCK);
      rMeasureSlim->setDiscAccess(i, PageManagerSlim->GetReadCount() / queryCities.size());
      rMeasureSlim->setDistanceFunction(i, MetricTreeSlim->GetMetricEvaluator()->GetDistanceCount() /
      												 queryCities.size());

      start = clock();
      for (int j=0; j<queryCities.size(); j++){
         sample = new TCity(queryCities[j]->GetName().c_str(),
                            queryCities[j]->GetLatitude(),
                            queryCities[j]->GetLongitude());
         resultDummy = MetricTreeDummy->KOrRangeQuery(sample, radiusQueryCities[j],
                                                      rMeasureDummy->getK(i));
         delete resultDummy;
         delete sample;
      }//end for
      end = clock();
		//to return the average in ms
      rMeasureDummy->setTotalTime(i, (1000*(end-start))/CLK_TCK);
      rMeasureDummy->setDiscAccess(i, PageManagerDummy->GetReadCount() / queryCities.size());
      rMeasureDummy->setDistanceFunction(i, MetricTreeDummy->GetMetricEvaluator()->GetDistanceCount() /
      													queryCities.size());

      cout << i << " ";
   }//end for

}//end TApp::PerformQueryKOrRange

//------------------------------------------------------------------------------
void TApp::PerformQueryKRange_And(resultMeasure * rMeasureSlim,
                                  resultMeasure * rMeasureDummy){

   myResult * resultSlim1, * resultSlim2, * resultDummy1, * resultDummy2;
   myResult * resultSlim, * resultDummy;
   TCity * sample;
   vector <TCity *> cities;
   double dlat, dlong, dist;
   clock_t start, end;
   int k, w;
   TCity * tmp1, * tmp2;
   const char *p1, *p2;

   cout << "\n PerformQuery Nearest AND Range: ";
   for(int i=0; i < rMeasureSlim->getSize(); i++){ // For number of points (radius) that i want measure.
      PageManagerSlim->ResetStatistics();
      PageManagerDummy->ResetStatistics();
      MetricTreeSlim->GetMetricEvaluator()->ResetStatistics();
      MetricTreeDummy->GetMetricEvaluator()->ResetStatistics();

      start = clock();
      for (int j=0; j < queryCities.size(); j++){
         sample = new TCity(queryCities[j]->GetName().c_str(),
                            queryCities[j]->GetLatitude(),
                            queryCities[j]->GetLongitude());
         resultSlim1 = MetricTreeSlim->RangeQuery(sample, radiusQueryCities[j]);
         resultSlim2 = MetricTreeSlim->NearestQuery(sample, rMeasureSlim->getK(i));
         resultSlim = new myResult();
         //resultSlim1 intersection resultSlim2
         resultSlim->Intersection(resultSlim1, resultSlim2);

         delete resultSlim;
         delete resultSlim1;
         delete resultSlim2;
         delete sample;
      }//end for
      end = clock();
		//to return the average in ms
      rMeasureSlim->setTotalTime(i, (1000*(end-start))/CLK_TCK);
      rMeasureSlim->setDiscAccess(i, PageManagerSlim->GetReadCount() / queryCities.size());
      rMeasureSlim->setDistanceFunction(i, MetricTreeSlim->GetMetricEvaluator()->GetDistanceCount() /
      													queryCities.size());

      start = clock();
      for (int j=0; j < queryCities.size(); j++){
         sample = new TCity(queryCities[j]->GetName().c_str(),
                            queryCities[j]->GetLatitude(),
                            queryCities[j]->GetLongitude());
         resultDummy1 = MetricTreeDummy->RangeQuery(sample, radiusQueryCities[j]);
         resultDummy2 = MetricTreeDummy->NearestQuery(sample, rMeasureDummy->getK(i));
         //resultDummy1 intersection resultDummy2
         resultDummy = new myResult();
         resultDummy->Intersection(resultDummy1, resultDummy2);

         delete resultDummy;
         delete resultDummy1;
         delete resultDummy2;
         delete sample;
      }//end for
      end = clock();
		//to return the average in ms
      rMeasureDummy->setTotalTime(i, (1000*(end-start))/CLK_TCK);
      rMeasureDummy->setDiscAccess(i, PageManagerDummy->GetReadCount() / queryCities.size());
      rMeasureDummy->setDistanceFunction(i, MetricTreeDummy->GetMetricEvaluator()->GetDistanceCount() /
      													queryCities.size());

      cout << i << " ";
   }//end for

}//end TApp::PerformQueryKRange_And

//------------------------------------------------------------------------------
void TApp::PerformQueryKRange_Or(resultMeasure * rMeasureSlim,
                                 resultMeasure * rMeasureDummy){

   myResult * resultSlim1, * resultSlim2, * resultDummy1, * resultDummy2;
   myResult * resultSlim, * resultDummy;
   TCity * sample;
   vector <TCity *> cities;
   double dlat, dlong, dist;
   clock_t start, end;
   int w;
   TCity * tmp;

   cout << "\n PerformQuery Nearest OR Range: ";
   for(int i=0; i< rMeasureSlim->getSize(); i++){ // For number of points (radius) that i want measure.
      PageManagerSlim->ResetStatistics();
      PageManagerDummy->ResetStatistics();
      MetricTreeSlim->GetMetricEvaluator()->ResetStatistics();
      MetricTreeDummy->GetMetricEvaluator()->ResetStatistics();

      start = clock();
      for (int j=0; j < queryCities.size(); j++){
         sample = new TCity(queryCities[j]->GetName().c_str(),
                            queryCities[j]->GetLatitude(),
                            queryCities[j]->GetLongitude());
         resultSlim1 = MetricTreeSlim->RangeQuery(sample, radiusQueryCities[j]);
         resultSlim2 = MetricTreeSlim->NearestQuery(sample, rMeasureSlim->getK(i));
         //resultSlim1 union resultSlim2
         resultSlim = new myResult();
         resultSlim->Union(resultSlim1, resultSlim2);

         delete resultSlim;
         delete resultSlim1;
         delete resultSlim2;
         delete sample;
      }// end for
      end = clock();
		//to return the average in ms
      rMeasureSlim->setTotalTime(i, (1000*(end-start))/CLK_TCK);
      rMeasureSlim->setDiscAccess(i, PageManagerSlim->GetReadCount() / queryCities.size());
      rMeasureSlim->setDistanceFunction(i, MetricTreeSlim->GetMetricEvaluator()->GetDistanceCount() /
      													queryCities.size());

      start = clock();
      for (int j=0; j < queryCities.size(); j++){
         sample = new TCity(queryCities[j]->GetName().c_str(),
                            queryCities[j]->GetLatitude(),
                            queryCities[j]->GetLongitude());
         resultDummy1 = MetricTreeDummy->RangeQuery(sample, radiusQueryCities[j]);
         resultDummy2 = MetricTreeDummy->NearestQuery(sample, rMeasureDummy->getK(i));
         // resultDummy1 union resultDummy2
         resultDummy = new myResult();
         resultDummy->Union(resultDummy1, resultDummy2);

         delete resultDummy;
         delete resultDummy1;
         delete resultDummy2;
         delete sample;
      }// end for
      end = clock();
		//to return the average in ms
      rMeasureDummy->setTotalTime(i, (1000*(end-start))/CLK_TCK);
      rMeasureDummy->setDiscAccess(i, PageManagerDummy->GetReadCount() / queryCities.size());
      rMeasureDummy->setDistanceFunction(i, MetricTreeDummy->GetMetricEvaluator()->GetDistanceCount() /
      													queryCities.size());

      cout << i << " ";
   }//end for

}//end TApp::PerformQueryKRange_Or

//------------------------------------------------------------------------------
void TApp::SetRadiusFromObjects(double radius){

   myResult * result;
   TCity * sample;
   //clear before insert new radium values
   radiusQueryCities.clear();
   cout << "\n SetRadiusFromObjects: ";
   for (int i=0; i < queryCities.size(); i++){
      sample = new TCity(queryCities[i]->GetName().c_str(),
                         queryCities[i]->GetLatitude(),
                         queryCities[i]->GetLongitude());
      result = MetricTreeSlim->NearestQuery(sample, radius*numberOfObjects);
      radiusQueryCities.insert(radiusQueryCities.end(), result->GetMaximumDistance());
      delete result;
      delete sample;
      cout << i << " ";
   }//end for
}//end TApp::SetRadiusFromObjects

//----------------------------------------------------------------------------
void TApp::WriteToFile(FILE * file, resultMeasure * rMeasure, int type){
   char * strTemp = new char[500];
   char * string = new char[50];

   //write the statistics to files
   for(int i=0; i < rMeasure->getSize(); i++){
      strcpy(strTemp, itoa(rMeasure->getK(i),string,10));
      strcat(strTemp, "\t");
      fwrite(strTemp, strlen(strTemp), 1, file);
      if(type==1)
         fprintf(file, "%d", rMeasure->getDistanceFunction(i));
      else if(type==2)
         fprintf(file, "%d", rMeasure->getDiscAccess(i));
      else
         fprintf(file, "%f", rMeasure->getTotalTime(i));
      strcpy(strTemp, "\n");
      fwrite(strTemp, strlen(strTemp), 1, file);
   }//end for
   strcpy(strTemp, "end\n");
   fwrite(strTemp, strlen(strTemp), 1, file);

   delete strTemp;
   delete string;
}//end TApp::WriteToFile()

//----------------------------------------------------------------------------
void TApp::WriteHeader(FILE * file, char * type, bool and, double radius){
   char * strTemp = new char[500];

   if(and){
      strcpy(strTemp,"set title \"Cities: kAndRange Queries");
   }else{
      strcpy(strTemp,"set title \"Cities: kOrRange Queries");
   }//end if
   fwrite(strTemp, strlen(strTemp), 1, file);
   fprintf(file, "%f", radius*0.001);
   strcpy(strTemp,"\"\nset xlabel \"k\"\n");
   fwrite(strTemp, strlen(strTemp), 1, file);
   strcpy(strTemp, type);
   fwrite(strTemp, strlen(strTemp), 1, file);
   if(and){
      strcpy(strTemp,"plot '-' title 'Slim-tree kAndRange' with linespoints 3, ");
   }else{
      strcpy(strTemp,"plot '-' title 'Slim-tree kOrRange' with linespoints 3, ");
   }//end if
   strcat(strTemp,"'-' title 'Slim-tree basic operations' with linespoints 4, ");
   if(and){
      strcat(strTemp,"'-' title 'SeqScan kAndRange' with linespoints 5, ");
   }else{
      strcat(strTemp,"'-' title 'SeqScan kOrRange' with linespoints 5, ");
   }//end if
   strcat(strTemp,"'-' title 'SeqScan basic operations' with linespoints 8 \n\n");
   fwrite(strTemp, strlen(strTemp), 1, file);

   delete strTemp;
}//end TApp::WriteHeader()
