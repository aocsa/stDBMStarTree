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
TApp::TApp(){
   PageManagerSlimMST = NULL;
   PageManagerVP = NULL;
   PageManagerGH = NULL;

   MetricTreeSlimMST = NULL;
   MetricTreeVP = NULL;
   MetricTreeGH = NULL;

   MetricTreeSlimMSTTime = 0;
   MetricTreeVPTime = 0;
   MetricTreeGHTime = 0;

   for (int i = 0; i < NUMBEROFTREES; i++){
      PageManagerMM[i] = NULL;
      MetricTreeMM[i] = NULL;
      MetricTreeMMTime[i] = 0;
   }//end for
}//end TApp

//------------------------------------------------------------------------------
void TApp::Init(unsigned int pageSize, char * prefix, int numpoints){
   this->PageSize = pageSize;
   this->Prefix = prefix;
   this->NumPoints = numpoints;

   // Create it in memory
   CreateMemoryPageManager();

   // Creates the trees
   CreateTree();
}//end TApp::Init


void TApp::CreateMemoryPageManager(){
   PageManagerSlimMST = new stMemoryPageManager(this->PageSize);
   PageManagerVP = new stMemoryPageManager(this->PageSize);
   PageManagerGH = new stMemoryPageManager(this->PageSize);

   for (int i = 0; i < NUMBEROFTREES; i++){
      PageManagerMM[i] = new stMemoryPageManager(this->PageSize);
   }//end for

}//end TApp::CreateMemoryPageManager()


//------------------------------------------------------------------------------
void TApp::CreateTree(){
   // create for Slim-Tree
   MetricTreeSlimMST = new mySlimTree(PageManagerSlimMST);
   MetricTreeSlimMST->SetSplitMethod(mySlimTree::smSPANNINGTREE);
   MetricTreeSlimMST->SetChooseMethod(mySlimTree::cmMINOCCUPANCY);

   MetricTreeVP = new myVPTree(PageManagerVP);
   MetricTreeGH = new myGHTree(PageManagerGH);

   // create the MM-Trees
   for (int i = 0; i < NUMBEROFTREES; i++){
      MetricTreeMM[i] = new myMMTree(PageManagerMM[i]);
   }//end for

   MetricTreeMM[0]->SetInsertionMethod(myMMTree::imNOBALANCE);

   MetricTreeMM[1]->SetInsertionMethod(myMMTree::imTRY2BALANCE);

}//end TApp::CreateTree
//------------------------------------------------------------------------------


//------------------------------------------------------------------------------
void TApp::Run(char * DataPath){
   char filename[50];
   FILE *times, *distances, *heights;

   sprintf(filename,"%stimes.txt",this->Prefix);
   times = fopen(filename,"w");

   sprintf(filename,"%sdistances.txt",this->Prefix);
   distances = fopen(filename,"w");

   sprintf(filename,"%sheights.txt",this->Prefix);
   heights = fopen(filename,"w");

   int ND_Slim, ND_GH, ND_VP, ND_MM[2], HG_min[2], HG_max[2], HG_avg[2];

   // Lets load the tree with a lot values from the file.

   cout << "\n\nAdding objects in the MetricTreeSlimMST";
   MetricTreeSlimMST->GetMetricEvaluator()->ResetStatistics();
   LoadTree(DataPath, MetricTreeSlimMST, &MetricTreeSlimMSTTime);
   if (MetricTreeSlimMST){
      cout << "\nExecuting the Slim-Down Algorithm.";
      MetricTreeSlimMST->Optimize();
   }//end if
   ND_Slim = MetricTreeSlimMST->GetMetricEvaluator()->GetDistanceCount();
   cout << " Done!";

   cout << "\n\nAdding objects in the MetricTreeGH";
   MetricTreeGH->GetMetricEvaluator()->ResetStatistics();
   LoadTree(DataPath, MetricTreeGH, &MetricTreeGHTime);
   ND_GH = MetricTreeGH->GetMetricEvaluator()->GetDistanceCount();
   cout << " Done!";

   MetricTreeVP->GetMetricEvaluator()->ResetStatistics();
   cout << "\n\nAdding objects in the MetricTreeVP";
   LoadTree(DataPath, MetricTreeVP, &MetricTreeVPTime);
   ND_VP = MetricTreeVP->GetMetricEvaluator()->GetDistanceCount();
   cout << " Done!";

   for (int i = 0; i < NUMBEROFTREES; i++){
      cout << "\n\nAdding objects in the MetricTreeMM[" << i << "]";
      MetricTreeMM[i]->GetMetricEvaluator()->ResetStatistics();
      LoadTree(DataPath, MetricTreeMM[i], &MetricTreeMMTime[i]);
      MetricTreeMM[i]->GetHeights(HG_min[i],HG_max[i],HG_avg[i]);
      ND_MM[i] = MetricTreeMM[i]->GetMetricEvaluator()->GetDistanceCount();
      cout << " Done!";
   }//end for

   //Write information of trees building.

   //Writing times
   //In file
   fprintf(times, "SlimTree:  %li\n",MetricTreeSlimMSTTime);
   fprintf(times, "GH-tree:   %li\n",MetricTreeGHTime);
   fprintf(times, "VP-tree:   %li\n",MetricTreeVPTime);
   fprintf(times, "MM-tree0:  %li\n",MetricTreeMMTime[0]);
   fprintf(times, "MM-tree1:  %li\n",MetricTreeMMTime[1]);
   //In screen
   printf("\nTimes:\nSlimTree:  %li\n",MetricTreeSlimMSTTime);
   printf("GH-tree:   %li\n",MetricTreeGHTime);
   printf("VP-tree:   %li\n",MetricTreeVPTime);
   printf("MM-tree0:  %li\n",MetricTreeMMTime[0]);
   printf("MM-tree1:  %li\n",MetricTreeMMTime[1]);

   //Writing distances
   fprintf(distances, "SlimTree:  %i\n",ND_Slim);
   fprintf(distances, "GH-tree:   %i\n",ND_GH);
   fprintf(distances, "VP-tree:   %i\n",ND_VP);
   fprintf(distances, "MM-tree0:  %i\n",ND_MM[0]);
   fprintf(distances, "MM-tree1:  %i\n",ND_MM[1]);

   printf("\nDistances:\nSlimTree:  %i\n",ND_Slim);
   printf("GH-tree:   %i\n",ND_GH);
   printf("VP-tree:   %i\n",ND_VP);
   printf("MM-tree0:  %i\n",ND_MM[0]);
   printf("MM-tree1:  %i\n",ND_MM[1]);

   //Writing heights
   fprintf(heights, "MM-tree0:  Min=%i  Max=%i  Avg=%i\n",HG_min[0],HG_max[0],HG_avg[0]);
   fprintf(heights, "MM-tree1:  Min=%i  Max=%i  Avg=%i\n",HG_min[1],HG_max[1],HG_avg[1]);

   printf("\nHeights of MM-trees:\nMM-tree0:  Min=%i  Max=%i  Avg=%i\n",HG_min[0],HG_max[0],HG_avg[0]);
   printf("MM-tree1:  Min=%i  Max=%i  Avg=%i\n",HG_min[1],HG_max[1],HG_avg[1]);


   fclose(times);
   fclose(distances);
   fclose(heights);

   // Hold the screen.
   cout << "\n\nFinished the whole test!";
   system("pause");
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
      WriteStat(fileStats, "MetricTreeSlimMST", MetricTreeSlimMST, this->MetricTreeSlimMSTTime);
      cout << "\nDone for MetricTreeSlimMST.";

      WriteStat(fileStats, "MetricTreeGH", MetricTreeGH, this->MetricTreeGHTime);
      cout << "\nDone for MetricTreeGH.";

      WriteStat(fileStats, "MetricTreeVP", MetricTreeVP, this->MetricTreeVPTime);
      cout << "\nDone for MetricTreeVP.";

      for (int i = 0; i < NUMBEROFTREES; i++){
         strcpy(strTemp, "MetricTreeMM[");
         strcat(strTemp, itoa(i, tmpStr, 10));
         strcat(strTemp, "]");
         WriteStat(fileStats, strTemp, MetricTreeMM[i], this->MetricTreeMMTime[i]);
         cout << "\nDone for MetricTreeMM[" << i << "].";
      }//end for                      

      // close the file
      fclose(fileStats);
   }//end if

}//end WriteStats

//------------------------------------------------------------------------------
void TApp::WriteStat(FILE * file, char * treeName, MetricTree * metricTree, clock_t time){
   char strTemp[500];
   int minh, maxh;

   if (metricTree){
      // Get the information about the tree.
      strcpy(strTemp, "\n\n");
      strcat(strTemp, treeName);
      fwrite(strTemp, strlen(strTemp), 1, file);
      strcpy(strTemp, "\n\tHeight: ");
      fwrite(strTemp, strlen(strTemp), 1, file);
//      fprintf(file, "%d", infoResult->GetHeight());
      strcpy(strTemp, "\n\tObjs Count: ");
      fwrite(strTemp, strlen(strTemp), 1, file);
//      fprintf(file, "%d", infoResult->GetObjectCount());
      strcpy(strTemp, "\n\tRadius Tree: ");
      fwrite(strTemp, strlen(strTemp), 1, file);
      strcpy(strTemp, "\n\tPage Count: ");
      fwrite(strTemp, strlen(strTemp), 1, file);
      fprintf(file, "%d", metricTree->GetNodeCount());
      strcpy(strTemp, "\n\tPage size: ");
      fwrite(strTemp, strlen(strTemp), 1, file);
      fprintf(file, "%d", metricTree->GetPageManager()->GetMinimumPageSize());

      strcpy(strTemp, "\n\tTotal Time Construction: ");
      fwrite(strTemp, strlen(strTemp), 1, file);
      fprintf(file, "%ld", time);

//      delete infoResult;
   }//end if
}//end WriteStat

//------------------------------------------------------------------------------
void TApp::Done(){

   if (this->MetricTreeSlimMST != NULL){
      delete this->MetricTreeSlimMST;
   }//end if
   if (this->PageManagerSlimMST != NULL){
      delete this->PageManagerSlimMST;
   }//end if


   if (this->MetricTreeGH != NULL){
      delete this->MetricTreeGH;
   }//end if
   if (this->PageManagerGH != NULL){
      delete this->PageManagerGH;
   }//end if


   if (this->MetricTreeVP= NULL){
      delete this->MetricTreeVP;
   }//end if
   if (this->PageManagerVP != NULL){
      delete this->PageManagerVP;
   }//end if

   
   for (int i = 0; i < NUMBEROFTREES; i++){
      if (this->MetricTreeMM[i] != NULL){
         delete this->MetricTreeMM[i];
      }//end if
      if (this->PageManagerMM[i] != NULL){
         delete this->PageManagerMM[i];
      }//end if
   }//end for

}//end TApp::Done

//------------------------------------------------------------------------------
void TApp::LoadTree(char * fileName, MetricTree * metricTree, clock_t * totalTime){
  //printf("filename=%s\n",fileName); getchar();

   ifstream in(fileName);
   double values[MAXSIZE];
   int w = 0, i = 0;
   clock_t totalTimeTemp = 0;
   clock_t start, end;

   //for VP-tree
   myVPTree * metricTreeVP=NULL;
   TPoint *points=NULL;                             

   if (metricTree!=NULL){
      if (in.is_open()){
         cout << "\nLoading objects ";

         if (metricTreeVP = dynamic_cast<myVPTree *> (metricTree)){
            //It is the vp-tree
            points = new TPoint[this->NumPoints];
         }

         while(in >> values[0]){
            for(i=1; i<MAXSIZE; i++){
               in >> values[i];
            }//end for

            if (metricTreeVP){
               points[i++] = TPoint(values);
            }
            else{
               start = clock();
               this->AddToTree(values, metricTree);
               end = clock();
               totalTimeTemp += end-start;
            }

            w++;
            if (w % 10 == 0){
               cout << '.';
            }//end if

         }//end while

         if (metricTreeVP){
            //Adds in the VP-tree
            start = clock();
            MetricTreeVP->Add(points, this->NumPoints);
            end = clock();
            totalTimeTemp += end-start;
            if (points) delete[] points;
         }

         cout << " Objects successfully added";
         in.close();
         *totalTime = totalTimeTemp;
      }else{
         cout << "\nProblem to open the file.";
      }//end if
   }else{
      cout << "\n Zero object added!!";
   }//end if
}//end TApp::LoadTree



//------------------------------------------------------------------------------
void TApp::WriteToFile(FILE * file, char * algName, Measure * rMeasure, int type){
   char * strTemp = new char[500];
   char * string = new char[50];

   fprintf(file, "%s", algName);
   //write the statistics to files
   for(int i=0; i < rMeasure->getSize(); i++){
      fprintf(file, "%f", rMeasure->GetK(i));
      strcpy(strTemp, "\t");
      fwrite(strTemp, strlen(strTemp), 1, file);
      if (type==1)
         fprintf(file, "%f", rMeasure->getDistanceFunction(i));
      else if (type==2)
         fprintf(file, "%f", rMeasure->getDiscAccess(i));
      else
         fprintf(file, "%ld", rMeasure->getTotalTime(i));
      strcpy(strTemp, "\n");
      fwrite(strTemp, strlen(strTemp), 1, file);
   }//end for
   strcpy(strTemp, "end\n");
   fwrite(strTemp, strlen(strTemp), 1, file);

   delete strTemp;
   delete string;
}//end TApp::WriteToFile()

//------------------------------------------------------------------------------
void TApp::WriteHeader(FILE * file, char * type, bool range){
   char * strTemp = new char[500];
   char pageSize[10];
   char tmpString[10];
   char number[11];

   itoa(this->PageSize, pageSize, 10);

   if (range){
      strcpy(strTemp,"set title \"RQ: Cidades\"");
   }else{
      strcpy(strTemp,"set title \"kNNQ: Cidades\"");
   }//end if

   fwrite(strTemp, strlen(strTemp), 1, file);
   strcpy(strTemp,"\nset xlabel \"k\"\n");
   fwrite(strTemp, strlen(strTemp), 1, file);
   strcpy(strTemp, type);
   fwrite(strTemp, strlen(strTemp), 1, file);

   //Plotting
   strcpy(strTemp, "plot ");
   fwrite(strTemp, strlen(strTemp), 1, file);

   //for SlimTree
   if (MetricTreeSlimMST){
      strcpy(strTemp, "'-' title 'Slim-Tree MST' with linespoints 1, ");
      fwrite(strTemp, strlen(strTemp), 1, file);
   }//end if

   if (MetricTreeGH){
      strcpy(strTemp, "'-' title 'GH-Tree' with linespoints 2, ");
      fwrite(strTemp, strlen(strTemp), 1, file);
   }//end if

   if (MetricTreeVP){
      strcpy(strTemp, "'-' title 'VP-Tree' with linespoints 3 ");
      fwrite(strTemp, strlen(strTemp), 1, file);
   }//end if


   //for MMTree
   for (int i = 0; i < NUMBEROFTREES; i++){
      if (MetricTreeMM[i]){
         strcpy(strTemp, ", '-' title 'MM-Tree ");
         strcat(strTemp, itoa(i, number, 10));
         strcat(strTemp, "' with linespoints ");
         strcat(strTemp, itoa(i+4, number, 10));
         fwrite(strTemp, strlen(strTemp), 1, file);
      }//end if
   }//end for
   
   strcpy(strTemp, "\n\n");
   fwrite(strTemp, strlen(strTemp), 1, file);
   strcpy(strTemp,"####################\n");
   fwrite(strTemp, strlen(strTemp), 1, file);
   
   delete strTemp;
}//end TApp::WriteHeader()
