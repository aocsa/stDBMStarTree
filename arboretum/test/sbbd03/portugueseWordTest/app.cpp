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

//for the absolute radius of the queries
// with value 4 is between 0.0001 though 0.0004 of the query
#define QUANTIDADE 10
#define RAIO 4

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
//   LoadTree("port.txt");
   //load the query collection from the file
   LoadVectorFromFile("port500.txt");
   // Lets do the queries
   PerformQueries();
   // Hold the screen.
   cout << "Finished the whole test!\n";
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
   dmanSlim->Open("mySlimTree.dat");
//   dmanSlim->Create("mySlimTree.dat", 1024);
   PageManagerSlim = dmanSlim;
   //for Dummy-tree
   stDiskPageManager * dmanDummy = new stDiskPageManager();
   // Filename is myDummyTree.dat
   dmanDummy->Open("myDummyTree.dat");
//   dmanDummy->Create("myDummyTree.dat", 1024);
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
   int contObj=0;
   char buffer[100], word[100];
   char *ptr;

   if ((file = fopen(fileName, "r")) == NULL){
      printf("Cannot open input file.\n");
   }
   else{
   fgets(buffer, 100, file);
   cout << "Adding objects in the tree...\n";
   do{
      strcpy(word, buffer);
      ptr = strchr(word, '\n');
      *ptr = '\0';
      AddToTree(word);
      fgets(buffer, 100, file);
      contObj++;
   }while(!feof(file)); //end while
   cout << "Added " << contObj << " objects...\n";
   fclose(file);
  }//end else
}//end TApp::LoadTree()

//------------------------------------------------------------------------------
void TApp::LoadVectorFromFile(char *filename){
   FILE *f;
   int contObj=0;
   char buffer[128], word[128], *ptr;

   if ((f = fopen(filename, "r")) == NULL){
      printf("Cannot open input file.\n");
   }
   else{
      fgets(buffer, 60, f);
      cout << "Adding the objects for query...\n";
      do{ // Because there is 500 words
         strcpy(word, buffer);
         ptr = strchr(word, '\n');
         *ptr = '\0';
         queryWords.insert(queryWords.end(), new TWord(word));
         fgets(buffer, 60, f);
         contObj++;
      }while(!feof(f));//end while
      cout << "Added " << contObj << " objects...\n";
      fclose(f);
   }//end else
}//end TApp::LoadVectorFromFile

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

   for(int radius=3; radius<=RAIO; radius++){  // raio comecando de 0.003 = 0.3% (valor absoluto)
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
      cout << "\nTests with radius: " << radius << "\n\n";

      //set the radius of the objects
      cout << "Calculating the absolute radius from the sample query.... ";
      SetRadiusFromObjects(radius);
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
void TApp::PerformQueryKAndRange(resultMeasure * rMeasureSlim,
                                 resultMeasure * rMeasureDummy){

   myResult * resultSlim, * resultDummy;
   TWord * sample;
   clock_t start, end;

   PageManagerSlim->ResetStatistics();
   PageManagerDummy->ResetStatistics();
   MetricTreeSlim->GetMetricEvaluator()->ResetStatistics();
   MetricTreeDummy->GetMetricEvaluator()->ResetStatistics();

   cout << "\n PerformQueryKAndRange: ";
   //For number of points (radius) that I want measure.
   for(int i=0; i < rMeasureSlim->getSize(); i++){
      start = clock();
      for (int j=0; j < queryWords.size(); j++){
         sample = new TWord(queryWords[j]->GetName().c_str());
         resultSlim = MetricTreeSlim->KAndRangeQuery(sample, radiusQueryWords[j],
                                                 rMeasureSlim->getK(i));
         delete resultSlim;
         delete sample;
      }//end for
      end = clock();
      rMeasureSlim->setTotalTime(i, ((end-start)/CLK_TCK)/0.5);
      // is divided for queryWords to get the everage
      rMeasureSlim->setDiscAccess(i, PageManagerSlim->GetReadCount() / queryWords.size());
      // is divided for queryWords to get the everage
      rMeasureSlim->setDistanceFunction(i,
         MetricTreeSlim->GetMetricEvaluator()->GetDistanceCount() / queryWords.size());

      start = clock();
      for (int j=0; j < queryWords.size(); j++){
         sample = new TWord(queryWords[j]->GetName().c_str());
         resultDummy = MetricTreeDummy->KAndRangeQuery(sample, radiusQueryWords[j],
                                                 rMeasureDummy->getK(i));
         delete resultDummy;
         delete sample;
      }//end for
      end = clock();
      rMeasureDummy->setTotalTime(i, ((end-start)/CLK_TCK)/0.5);
      // is divided for queryWords to get the everage
      rMeasureDummy->setDiscAccess(i, PageManagerDummy->GetReadCount() / queryWords.size());
      // is divided for queryWords to get the everage
      rMeasureDummy->setDistanceFunction(i,
         MetricTreeDummy->GetMetricEvaluator()->GetDistanceCount() / queryWords.size());

      PageManagerSlim->ResetStatistics();
      PageManagerDummy->ResetStatistics();
      MetricTreeSlim->GetMetricEvaluator()->ResetStatistics();
      MetricTreeDummy->GetMetricEvaluator()->ResetStatistics();
      cout << i << " ";
   }//end for

}//end TApp::PerformQueryKAndRange

//------------------------------------------------------------------------------
void TApp::PerformQueryKOrRange(resultMeasure * rMeasureSlim,
                                resultMeasure * rMeasureDummy){

   myResult * resultSlim, * resultDummy;
   TWord * sample;
   clock_t start, end;

   PageManagerSlim->ResetStatistics();
   PageManagerDummy->ResetStatistics();
   MetricTreeSlim->GetMetricEvaluator()->ResetStatistics();
   MetricTreeDummy->GetMetricEvaluator()->ResetStatistics();

   cout << "\n PerformQueryKOrRange: ";
   //For number of points (radius) that I want measure.
   for(int i=0; i < rMeasureSlim->getSize(); i++){
      start = clock();
      for (int j=0; j<queryWords.size(); j++){
         sample = new TWord(queryWords[j]->GetName().c_str());
         resultSlim = MetricTreeSlim->KOrRangeQuery(sample, radiusQueryWords[j],
                                                    rMeasureSlim->getK(i));
         delete resultSlim;
         delete sample;
      }//end for
      end = clock();

      rMeasureSlim->setTotalTime(i, ((end-start)/CLK_TCK)/0.5);
      // is divided for queryWords to get the everage
      rMeasureSlim->setDiscAccess(i, PageManagerSlim->GetReadCount() / queryWords.size());
      // is divided for queryWords to get the everage
      rMeasureSlim->setDistanceFunction(i,
         MetricTreeSlim->GetMetricEvaluator()->GetDistanceCount() / queryWords.size());

      start = clock();
      for (int j=0; j<queryWords.size(); j++){
         sample = new TWord(queryWords[j]->GetName().c_str());
         resultDummy = MetricTreeDummy->KOrRangeQuery(sample, radiusQueryWords[j],
                                                      rMeasureDummy->getK(i));
         delete resultDummy;
         delete sample;
      }//end for
      end = clock();

      rMeasureDummy->setTotalTime(i, ((end-start)/CLK_TCK)/0.5);
      // is divided for queryWords to get the everage
      rMeasureDummy->setDiscAccess(i, PageManagerDummy->GetReadCount() / queryWords.size());
      // is divided for queryWords to get the everage
      rMeasureDummy->setDistanceFunction(i,
         MetricTreeDummy->GetMetricEvaluator()->GetDistanceCount() / queryWords.size());

      PageManagerSlim->ResetStatistics();
      PageManagerDummy->ResetStatistics();
      MetricTreeSlim->GetMetricEvaluator()->ResetStatistics();
      MetricTreeDummy->GetMetricEvaluator()->ResetStatistics();
      cout << i << " ";
   }//end for

}//end TApp::PerformQueryKOrRange

//------------------------------------------------------------------------------
void TApp::PerformQueryKRange_And(resultMeasure * rMeasureSlim,
                                  resultMeasure * rMeasureDummy){

   myResult * resultSlim1, * resultSlim2, * resultDummy1, * resultDummy2;
   TWord * sample;
   double dist;
   clock_t start, end;
   int k, w;
   TWord * tmp1, * tmp2;
   const char *p1, *p2;

   PageManagerSlim->ResetStatistics();
   PageManagerDummy->ResetStatistics();
   MetricTreeSlim->GetMetricEvaluator()->ResetStatistics();
   MetricTreeDummy->GetMetricEvaluator()->ResetStatistics();

   cout << "\n PerformQueryKRange_And: ";
   for(int i=0; i < rMeasureSlim->getSize(); i++){ // For number of points (radius) that i want measure.
      start = clock();
      for (int j=0; j < queryWords.size(); j++){
         sample = new TWord(queryWords[j]->GetName().c_str());
         resultSlim1 = MetricTreeSlim->RangeQuery(sample, radiusQueryWords[j]);
         resultSlim2 = MetricTreeSlim->NearestQuery(sample, rMeasureSlim->getK(i));
         //resultSlim1 intersection resultSlim2
         // if one word is equal to another- add to result
         // Here, its not important the result but the time
         // so i just add to calculate the time
         if ((resultSlim2->GetNumOfEntries()!=0) && (resultSlim1->GetNumOfEntries()!=0)){
            int numObj = resultSlim1->GetNumOfEntries();
            k = 0;
            while (k < numObj){
               tmp1 = (TWord *)(* resultSlim1)[k].GetObject();
               dist = (* resultSlim1)[k].GetDistance();
               p1 = tmp1->GetName().c_str();
               for (w = 0; w < resultSlim2->GetNumOfEntries(); w++){
                  tmp2 = (TWord *)(* resultSlim2)[w].GetObject();
                  p2 = tmp2->GetName().c_str();
                  if (tmp1->GetName() == tmp2->GetName()){ // if
                     resultSlim1->AddPair(tmp1->Clone(), dist);
                     break;
                  }//end if
               }//end for
               k++;
            }//end while
         }//end if
         delete resultSlim1;
         delete resultSlim2;
         delete sample;
      }//end for
      end = clock();

      rMeasureSlim->setTotalTime(i, ((end-start)/CLK_TCK)/0.5);
      // is divided for queryWords to get the everage
      rMeasureSlim->setDiscAccess(i, PageManagerSlim->GetReadCount() / queryWords.size());
      // is divided for queryWords to get the everage
      rMeasureSlim->setDistanceFunction(i,
         MetricTreeSlim->GetMetricEvaluator()->GetDistanceCount() / queryWords.size());

      start = clock();
      for (int j=0; j < queryWords.size(); j++){
         sample = new TWord(queryWords[j]->GetName().c_str());
         resultDummy1 = MetricTreeDummy->RangeQuery(sample, radiusQueryWords[j]);
         resultDummy2 = MetricTreeDummy->NearestQuery(sample, rMeasureDummy->getK(i));
         //resultSlim1 intersection resultSlim2
         // if one word is equal to another- add to result
         // Here, its not important the result but the time
         // so i just add to calculate the time
         if (resultDummy2->GetNumOfEntries()!=0 && resultDummy1->GetNumOfEntries()!=0){
            int numObj = resultDummy1->GetNumOfEntries();
            k = 0;
            while (k < numObj){
               tmp1 = (TWord *)(* resultDummy1)[k].GetObject();
               dist = (* resultDummy1)[k].GetDistance();
               p1 = tmp1->GetName().c_str();
               for (w = 0; w < resultDummy2->GetNumOfEntries(); w++){
                  tmp2 = (TWord *)(* resultDummy2)[w].GetObject();
                  p2 = tmp2->GetName().c_str();
                  if (tmp1->GetName() == tmp2->GetName()){ // if
                     resultDummy1->AddPair(tmp1->Clone(), dist);
                     break;
                  }//end if
               }//end for
               k++;
            }//end while
         }//end if
         delete resultDummy1;
         delete resultDummy2;
         delete sample;
      }//end for
      end = clock();

      rMeasureDummy->setTotalTime(i, ((end-start)/CLK_TCK)/0.5);
      // is divided for queryWords to get the everage
      rMeasureDummy->setDiscAccess(i, PageManagerDummy->GetReadCount() / queryWords.size());
      // is divided for queryWords to get the everage
      rMeasureDummy->setDistanceFunction(i,
         MetricTreeDummy->GetMetricEvaluator()->GetDistanceCount() / queryWords.size());

      PageManagerSlim->ResetStatistics();
      PageManagerDummy->ResetStatistics();
      MetricTreeSlim->GetMetricEvaluator()->ResetStatistics();
      MetricTreeDummy->GetMetricEvaluator()->ResetStatistics();
      cout << i << " ";
   }//end for

}//end TApp::PerformQueryKRange_And

//------------------------------------------------------------------------------
void TApp::PerformQueryKRange_Or(resultMeasure * rMeasureSlim,
                                 resultMeasure * rMeasureDummy){

   myResult * resultSlim1, * resultSlim2, * resultDummy1, * resultDummy2;
   TWord * sample;
   double dist;
   clock_t start, end;
   int w;
   TWord * tmp;
   PageManagerSlim->ResetStatistics();
   PageManagerDummy->ResetStatistics();
   MetricTreeSlim->GetMetricEvaluator()->ResetStatistics();
   MetricTreeDummy->GetMetricEvaluator()->ResetStatistics();

   cout << "\n PerformQueryKRange_Or: ";
   for(int i=0; i< rMeasureSlim->getSize(); i++){ // For number of points (radius) that i want measure.
      start = clock();
      for (int j=0; j < queryWords.size(); j++){
         sample = new TWord(queryWords[j]->GetName().c_str());
         resultSlim1 = MetricTreeSlim->RangeQuery(sample, radiusQueryWords[j]);
         resultSlim2 = MetricTreeSlim->NearestQuery(sample, rMeasureSlim->getK(i));
         //resultSlim1 union resultSlim2 with possible objects duplicate
         if (resultSlim2->GetNumOfEntries() != 0){
            for (w = 0; w < resultSlim2->GetNumOfEntries(); w++){
               tmp = (TWord *)(* resultSlim2)[w].GetObject();
               dist = (* resultSlim2)[w].GetDistance();
               resultSlim1->AddPair(tmp->Clone(), dist);
            }//end for
         }//end if
         delete resultSlim1;
         delete resultSlim2;
         delete sample;
      }// end for
      end = clock();

      rMeasureSlim->setTotalTime(i, ((end-start)/CLK_TCK)/0.5);
      // is divided for queryWords to get the everage
      rMeasureSlim->setDiscAccess(i, PageManagerSlim->GetReadCount() / queryWords.size());
      // is divided for queryWords to get the everage
      rMeasureSlim->setDistanceFunction(i,
         MetricTreeSlim->GetMetricEvaluator()->GetDistanceCount() / queryWords.size());

      start = clock();
      for (int j=0; j < queryWords.size(); j++){
         sample = new TWord(queryWords[j]->GetName().c_str());
         resultDummy1 = MetricTreeDummy->RangeQuery(sample, radiusQueryWords[j]);
         resultDummy2 = MetricTreeDummy->NearestQuery(sample, rMeasureDummy->getK(i));
         // resultDummy1 union resultDummy2 with possible objects duplicate
         if (resultDummy2->GetNumOfEntries() != 0){
            for (w = 0; w < resultDummy2->GetNumOfEntries(); w++){
               tmp = (TWord *)(*resultDummy2)[w].GetObject();
               dist = (*resultDummy2)[w].GetDistance();
               resultDummy1->AddPair(tmp->Clone(), dist);
            }//end for
         }//end if
         delete resultDummy1;
         delete resultDummy2;
         delete sample;
      }// end for
      end = clock();

      rMeasureDummy->setTotalTime(i, ((end-start)/CLK_TCK)/0.5);
      // is divided for queryWords to get the everage
      rMeasureDummy->setDiscAccess(i, PageManagerDummy->GetReadCount() / queryWords.size());
      // is divided for queryWords to get the everage
      rMeasureDummy->setDistanceFunction(i,
         MetricTreeDummy->GetMetricEvaluator()->GetDistanceCount() / queryWords.size());

      PageManagerSlim->ResetStatistics();
      PageManagerDummy->ResetStatistics();
      MetricTreeSlim->GetMetricEvaluator()->ResetStatistics();
      MetricTreeDummy->GetMetricEvaluator()->ResetStatistics();
      cout << i << " ";
   }//end for

}//end TApp::PerformQueryKRange_Or

//------------------------------------------------------------------------------
void TApp::SetRadiusFromObjects(double radius){

   myResult * result;
   TWord * sample;
   //clear before insert new radium values
   radiusQueryWords.clear();
   cout << "\n SetRadiusFromObjects: ";
   for (int i=0; i < queryWords.size(); i++){
      sample = new TWord(queryWords[i]->GetName().c_str());
      result = MetricTreeSlim->NearestQuery(sample, radius*numberOfObjects);
      radiusQueryWords.insert(radiusQueryWords.end(), result->GetMaximumDistance());
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
void TApp::WriteHeader(FILE * file, char * type, bool and, int radius){
   char * strTemp = new char[500];

   if(and){
      strcpy(strTemp,"set title \"Portuguese Words: kAndRange Queries");
   }else{
      strcpy(strTemp,"set title \"Portuguese Words: kOrRange Queries");
   }//end if
   fwrite(strTemp, strlen(strTemp), 1, file);
   fprintf(file, "%f", radius);
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
