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
#pragma hdrstop

#include "app.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
// Class TApp
//------------------------------------------------------------------------------
void TApp::Init(unsigned int pageSize, unsigned int querySize,
                stDistance fractalDimension, stDistance maxDistance,
                char * prefix, char * difRadius,
                stDistance percRadius, double third){

   this->PageSize = pageSize;
   this->QuerySize = querySize;
   this->FractalDimension = fractalDimension;
   this->MaxDistance = maxDistance;
   this->Prefix = prefix;

   if (!strcmp(difRadius, "true")){
      this->DifRadius = true;
      this->PercRadius = percRadius;
   }else{
      this->DifRadius = false;
      this->PercRadius = 1; 
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
   if (this->slimTree != NULL){
      delete this->slimTree;
   }//end if
   if (this->pageManagerSlim != NULL){
      delete this->pageManagerSlim;
   }//end if

   for (unsigned int i = 0; i < queryObjects.size(); i++){
      delete (queryObjects.at(i));
   }//end for
}//end TApp::Done

//------------------------------------------------------------------------------
void TApp::CreateDiskPageManager(){
   //for Slim-tree
   char fileName[100];
   FILE * file;

   //for Slim-tree
   strcpy(fileName, this->Prefix.c_str());
   strcat(fileName, "SlimTree");
   strcat(fileName, ".dat");

   // Try to open the file.
   if ((file = fopen(fileName, "r")) == NULL){
      // Opened.
      pageManagerSlim = new stPlainDiskPageManager(fileName, this->PageSize);
   }else{
      // Cannot open. Create it.
      pageManagerSlim = new stPlainDiskPageManager(fileName);
      fclose(file);
   }//end if
}//end TApp::CreateDiskPageManager

//------------------------------------------------------------------------------
void TApp::CreateTree(){
   //create for Slim-tree
   slimTree = new mySlimTree(pageManagerSlim);
   slimTree->SetSplitMethod(mySlimTree::smMINMAX);
   slimTree->SetChooseMethod(mySlimTree::cmMINDIST);
}//end TApp::CreateTree

//------------------------------------------------------------------------------
void TApp::LoadTree(char * fileName){
   FILE * file;
   long w = 0;
   char buffer[200], word[200];
   char * ptr;

   if (slimTree!=NULL){
      // Is there any object?
      if (slimTree->GetNumberOfObjects() == 0){
         if ((file = fopen(fileName, "r")) == NULL){
            cout << "Cannot open input file!\n\n";
         }else{
            fgets(buffer, 200, file);
            do{
               strcpy(word, buffer);
               ptr = strchr(word, '\n');
               *ptr = '\0';
               AddToTree(word);
               fgets(buffer, 200, file);
               w++;
               if (w % 100 == 0){
                  cout << ".";
               }//end if
            }while(!feof(file)); //end do
            cout << "Added " << slimTree->GetNumberOfObjects() << " objects...\n";
            fclose(file);
            cout << "Performing the Slim-Down Algorithm\n";
            slimTree->Optimize();
         }//end else
      }//end else
   }else{
      cout << "Zero object added!!\n";
   }//end else
}//end TApp::LoadTree

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

   char string[] = "\npause -1";
   char percRadius[10], third[10];
   char fileName[50];
   char tmpString[50];
   FILE * fileKAndRange, * fileKOrRange, * fileRingRange;

   //for the result of the tests
   ResultMeasureDiscrete * rMeasureReal = new ResultMeasureDiscrete(this->QuerySize);
   ResultMeasureDiscrete * rMeasureSel = new ResultMeasureDiscrete(this->QuerySize);
   ResultMeasureDiscrete * rMeasureRealSD = new ResultMeasureDiscrete(this->QuerySize);

   //Coping the page size, percent radius and case b) (how is one third of queries?) to a string
   itoa(ceil(this->PercRadius*100), percRadius, 10);
   itoa(this->Third, third, 10);

   //set the name and the header of the file
   strcpy(fileName, this->Prefix.c_str());
   strcat(fileName, "kAndR");
   strcat(fileName, "_R");
   strcat(fileName, percRadius);
   strcat(fileName, "_Q");
   strcat(fileName, third);
   strcat(fileName, ".plt");

   fileKAndRange = fopen(fileName, "w");
   WriteHeader(fileKAndRange, "set ylabel \"Estimativa de Seletividade - Cardinalidade \"\n");

   //set the name and the header of the file
   strcpy(fileName, this->Prefix.c_str());
   strcat(fileName, "kOrR");
   strcat(fileName, "_R");
   strcat(fileName, percRadius);
   strcat(fileName, "_Q");
   strcat(fileName, third);
   strcat(fileName, ".plt");

   fileKOrRange = fopen(fileName, "w");
   WriteHeader(fileKOrRange, "set ylabel \"Estimativa de Seletividade - Cardinalidade \"\n");

   //set the name and the header of the file
   strcpy(fileName, this->Prefix.c_str());
   strcat(fileName, "RingR");
   strcat(fileName, "_R");
   strcat(fileName, percRadius);
   strcat(fileName, "_Q");
   strcat(fileName, third);
   strcat(fileName, ".plt");

   fileRingRange = fopen(fileName, "w");
   WriteHeader(fileRingRange, "set ylabel \"Estimativa de Seletividade - Cardinalidade \"\n");

   cout << "\nStarting Statistics for kAndRange... ";
   PerformKAndRangeQuery(rMeasureReal, rMeasureSel, rMeasureRealSD);
   WriteToFile(fileKAndRange, rMeasureReal, rMeasureSel, rMeasureRealSD);
   fwrite(string, strlen(string), 1, fileKAndRange);
   fclose(fileKAndRange);
   cout << " Ok\n";
   rMeasureReal->Reset();
   rMeasureSel->Reset();

   cout << "\nStarting Statistics for kOrRange... ";
   PerformKOrRangeQuery(rMeasureReal, rMeasureSel, rMeasureRealSD);
   WriteToFile(fileKOrRange, rMeasureReal, rMeasureSel, rMeasureRealSD);
   fwrite(string, strlen(string), 1, fileKOrRange);
   fclose(fileKOrRange);
   cout << " Ok\n";
   rMeasureReal->Reset();
   rMeasureSel->Reset();

   cout << "\nStarting Statistics for RingRangeRange... ";
   PerformRingRangeQuery(rMeasureReal, rMeasureSel, rMeasureRealSD);
   WriteToFile(fileRingRange, rMeasureReal, rMeasureSel, rMeasureRealSD);
   fwrite(string, strlen(string), 1, fileRingRange);
   fclose(fileRingRange);
   cout << " Ok\n";

   //cleaning...
   delete rMeasureReal;
   delete rMeasureRealSD;
   delete rMeasureSel;
}//end TApp::PerformQuery

//------------------------------------------------------------------------------
void TApp::PerformKAndRangeQuery(ResultMeasureDiscrete * rMeasureReal,
      ResultMeasureDiscrete * rMeasureSel, ResultMeasureDiscrete * rMeasureRealSD){

   myResult * result;
   double * measures;
   double sum, last;
   unsigned int size;
   unsigned int i, j;
   double root, radius, logRadius, totalObjects, logMaxDistance;
   stCount numK, k;
   double avgEstimationK, avgRealK;
   long numberOfObjects = slimTree->GetNumberOfObjects();

   size = queryObjects.size();
   measures = new double[size];
   totalObjects = log((numberOfObjects * numberOfObjects) - numberOfObjects);
   logMaxDistance = log(this->MaxDistance);

   //For number of points (radius) that I want to measure.
   for (i = 0; i < rMeasureReal->getSize(); i++){
      avgEstimationK = 0;
      avgRealK = 0;
      // set the k
      k = rMeasureReal->getK(i);
      // Set the radius.
      SetRadiusFromObjects(rMeasureReal, i);

      last = 0;
      // for each city.
      for (j = 0; j < size; j++){
         //Estimate k
         logRadius = log(radiusqueryObjects[j]);
         root = exp(totalObjects + (this->FractalDimension * logRadius) - (this->FractalDimension * logMaxDistance));
         numK = (1 + sqrt(1 + 4 * root))/2.0;
         // Get the greatest value between numK and k (because the kOrRange is not restrictive!).
         if (numK < k){
            avgEstimationK += numK;
         }else{
            avgEstimationK += k;
         }//end if
         // Perform the query.
         result = slimTree->KAndRangeQuery(queryObjects[j], radiusqueryObjects[j], k);
         avgRealK += result->GetNumOfEntries();

         // For standand deviation.
         measures[j] = (double) result->GetNumOfEntries() - last;
         last = (double )result->GetNumOfEntries();
         delete result;
      }//end for
      // is divided for queryObjects to get the everage
      avgRealK = avgRealK / (double )size;

      sum = 0;
      for (j = 0; j < size; j++){
         sum += pow((measures[j] - avgRealK), 2);
      }//end for
      rMeasureRealSD->setDiskAccess(i, sqrt(sum / (double )size));

      //Set the Selectivity
      rMeasureReal->setDiskAccess(i, avgRealK);
      rMeasureSel->setDiskAccess(i, avgEstimationK / (double) size);
      cout << " est=" << rMeasureReal->getDiskAccess(i) << "/" << rMeasureSel->getDiskAccess(i) << " ";

      cout << " " << i;
   }//end for
   //delete
   delete[] measures;
}//end TApp::PerformKAndRange

//------------------------------------------------------------------------------
void TApp::PerformKOrRangeQuery(ResultMeasureDiscrete * rMeasureReal,
      ResultMeasureDiscrete * rMeasureSel, ResultMeasureDiscrete * rMeasureRealSD){

   myResult * result;
   double * measures;
   double sum, last;
   unsigned int size;
   unsigned int i, j;
   double root, radius, logRadius, totalObjects, logMaxDistance;
   stCount numK, k;
   double avgEstimationK, avgRealK;
   long numberOfObjects = slimTree->GetNumberOfObjects();

   size = queryObjects.size();
   measures = new double[size];
   totalObjects = log((numberOfObjects * numberOfObjects) - numberOfObjects);
   logMaxDistance = log(this->MaxDistance);

   //For number of points (radius) that I want to measure.
   for (i = 0; i < rMeasureReal->getSize(); i++){
      avgEstimationK = 0;
      avgRealK = 0;
      // set the k
      k = rMeasureReal->getK(i);
      // Set the radius.
      SetRadiusFromObjects(rMeasureReal, i);

      last = 0;
      // for each city.
      for (j = 0; j < size; j++){
         //Estimate k
         logRadius = log(radiusqueryObjects[j]);
         root = exp(totalObjects + (this->FractalDimension * logRadius) - (this->FractalDimension * logMaxDistance));
         numK = (1 + sqrt(1 + 4 * root))/2.0;
         // Get the greatest value between numK and k (because the kOrRange is not restrictive!).
         if (numK > k){
            avgEstimationK += numK;
         }else{
            avgEstimationK += k;
         }//end if
         // Perform the query.
         result = slimTree->KOrRangeQuery(queryObjects[j], radiusqueryObjects[j], k);
         avgRealK += result->GetNumOfEntries();

         // For standand deviation.
         measures[j] = (double) result->GetNumOfEntries() - last;
         last = (double )result->GetNumOfEntries();
         delete result;
      }//end for
      // is divided for queryObjects to get the everage
      avgRealK = avgRealK / (double )size;

      sum = 0;
      for (j = 0; j < size; j++){
         sum += pow((measures[j] - avgRealK), 2);
      }//end for
      rMeasureRealSD->setDiskAccess(i, sqrt(sum / (double )size));

      // Set the Selectivity
      rMeasureReal->setDiskAccess(i, avgRealK);
      rMeasureSel->setDiskAccess(i, avgEstimationK / (double) size);
      cout << " est=" << rMeasureReal->getDiskAccess(i) << "/" << rMeasureSel->getDiskAccess(i) << " ";

      cout << " " << i;
   }//end for
   //delete
   delete[] measures;
}//end TApp::PerformKOrRange

//------------------------------------------------------------------------------
void TApp::PerformRingRangeQuery(ResultMeasureDiscrete * rMeasureReal,
      ResultMeasureDiscrete * rMeasureSel, ResultMeasureDiscrete * rMeasureRealSD){

   myResult * result;
   double * measures;
   double sum, last;
   unsigned int size;
   unsigned int i, j;
   double root, logRadius, logMaxDistance, totalObjects;
   stCount numK_e, numK_i;
   double avgEstimationK, avgRealK;
   long numberOfObjects = slimTree->GetNumberOfObjects();

   size = queryObjects.size();
   measures = new double[size];
   totalObjects = log((numberOfObjects * numberOfObjects) - numberOfObjects);
   logMaxDistance = log(this->MaxDistance);

   //For number of points (radius) that I want to measure.
   for (i = 0; i < rMeasureReal->getSize(); i++){
      avgEstimationK = 0;
      avgRealK = 0;
      // Set the radius.
      SetRadiusFromObjects(rMeasureReal, i);

      last = 0;
      // for each city.
      for (j = 0; j < size; j++){
         // Estimate outer radius
         logRadius = log(radiusqueryObjects[j]);
         // Estimating the outer number of objects
         root = exp(totalObjects + (this->FractalDimension * logRadius) - (this->FractalDimension * logMaxDistance));
         numK_e = (1 + sqrt(1 + 4 * root))/2.0;

         //Estimate inner radius 
         logRadius = log(RINGFACTOR * radiusqueryObjects[j]);
         // Estimating the inner number of objects
         root = exp(totalObjects + (this->FractalDimension * logRadius) - (this->FractalDimension * logMaxDistance));
         numK_i = (1 + sqrt(1 + 4 * root))/2.0; /**/

         // Estimating the Cardinality
         avgEstimationK += (numK_e - numK_i);
         // Perform the Ring Query
         result = slimTree->RingQuery(queryObjects[j], RINGFACTOR * radiusqueryObjects[j], radiusqueryObjects[j]);
         // Getting the real query cardinality
         avgRealK += result->GetNumOfEntries();

         // For standand deviation.
         measures[j] = (double) result->GetNumOfEntries() - last;
         last = (double )result->GetNumOfEntries();
         delete result;
      }//end for
      // is divided for queryObjects to get the everage
      avgRealK = avgRealK / (double )size;

      sum = 0;
      for (j = 0; j < size; j++){
         sum += pow((measures[j] - avgRealK), 2);
      }//end for
      rMeasureRealSD->setDiskAccess(i, sqrt(sum / (double )size));

      //Set the Estimation Selectivity - Cardinality
      rMeasureReal->setDiskAccess(i, avgRealK);
      rMeasureSel->setDiskAccess(i, avgEstimationK / size);
      cout << " est=" << rMeasureReal->getDiskAccess(i) << "/" << rMeasureSel->getDiskAccess(i) << " ";

      cout << " " << i;
   }//end for
   //delete
   delete[] measures;
}//end TApp::PerformRingRange

//------------------------------------------------------------------------------
void TApp::WriteHeader(FILE * file, char * type){
   char * strTemp = new char[500];
   char tmpString[10];

   // Title
   strcpy(strTemp,"set title \"corelHisto - Seletividade");
   fwrite(strTemp, strlen(strTemp), 1, file);
   // End Title
   // x and y label
   strcpy(strTemp,"\"\nset xlabel \"k\"\n");
   fwrite(strTemp, strlen(strTemp), 1, file);
   strcpy(strTemp, type);
   fwrite(strTemp, strlen(strTemp), 1, file);

   strcpy(strTemp,"set logscale y \n");
   fwrite(strTemp, strlen(strTemp), 1, file);

   // Plots
   strcpy(strTemp,"plot '-' title '(A) Seletividade Real' with error lt 5 lw 2 pt 2, ");
   strcat(strTemp,"'-' title '(B) Seletividade Estimada' with errorlines lt 1 lw 2 pt 8\n\n");
   fwrite(strTemp, strlen(strTemp), 1, file);                           
   strcpy(strTemp,"####################\n");
   fwrite(strTemp, strlen(strTemp), 1, file);

   delete strTemp;
}//end TApp::WriteHeader()

//------------------------------------------------------------------------------
void TApp::WriteToFile(FILE * file, ResultMeasureDiscrete * rMeasureReal,
                       ResultMeasureDiscrete * rMeasureSel, ResultMeasureDiscrete * rMeasureRealSD){
   char * strTemp = new char[500];
   char * string = new char[50];
   int i;

   //write the statistics to files
   for (i = 0; i < rMeasureSel->getSize(); i++){
      fprintf(file, "%d\t", rMeasureReal->getK(i));
      // Write the cardinalities
      fprintf(file, "%f", rMeasureReal->getDiskAccess(i));
      if (rMeasureReal->getDiskAccess(i) - rMeasureRealSD->getDiskAccess(i) < 0){
         fprintf(file, "\t%f", 0.0);
      }else{
         fprintf(file, "\t%f", rMeasureReal->getDiskAccess(i) - rMeasureRealSD->getDiskAccess(i));
      }//end if
      fprintf(file, "\t%f\n", rMeasureReal->getDiskAccess(i) + rMeasureRealSD->getDiskAccess(i));
   }//end for
   strcpy(strTemp, "end\n####################\n");
   fwrite(strTemp, strlen(strTemp), 1, file);

   for (i = 0; i < rMeasureSel->getSize(); i++){
      fprintf(file, "%d\t", rMeasureSel->getK(i));
      // Write the cardinalities
      fprintf(file, "%f", rMeasureSel->getDiskAccess(i));
      fprintf(file, "\t%f", rMeasureSel->getDiskAccess(i) - (ERRORFD * rMeasureSel->getDiskAccess(i)));
      fprintf(file, "\t%f", rMeasureSel->getDiskAccess(i) + (ERRORFD * rMeasureSel->getDiskAccess(i)));
      strcpy(strTemp, "\n");
      fwrite(strTemp, strlen(strTemp), 1, file);
   }//end for
   strcpy(strTemp, "end\n####################\n");
   fwrite(strTemp, strlen(strTemp), 1, file);

   delete strTemp;
   delete string;
}//end TApp::WriteToFile

//------------------------------------------------------------------------------
void TApp::SetRadiusFromObjects(ResultMeasureDiscrete * rMeasureSlim, int i){
   myResult * result;
   int j;
   stCount k;
   stDistance radius;
   unsigned int oneThird;
   long numberOfObjects = slimTree->GetNumberOfObjects();
   // How many is One Third of queries?
   oneThird = (unsigned int) floor(queryObjects.size() / this->Third);

   //clear before insert new radium values
   radiusqueryObjects.clear();

   // set the number of objects.
   k = rMeasureSlim->getK(i);
   // perform the query.
   for (j = 0; j < queryObjects.size(); j++){
      result = slimTree->NearestQuery(queryObjects[j], k);
      // set the radius.
      radius = result->GetMaximumDistance();
      delete result;
      if (this->DifRadius){
         if (j < oneThird){
            radius = (1.0 + this->PercRadius) * radius;
         }else{
            if (j < (2 * oneThird)) {
               radius = (1.0 - this->PercRadius) * radius;
            }//end if
         }//end if
      }//end if
      radiusqueryObjects.insert(radiusqueryObjects.end(), radius);
   }//end for
}//end TApp::SetRadiusFromObjects
