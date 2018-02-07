//---------------------------------------------------------------------------
// Author: Marcos Rodrigues Vieira (mrvieira@icmc.usp.br)
// Copyright (c) 2004 GBDI-ICMC-USP
//---------------------------------------------------------------------------
#include "resultMeasure.h"

//---------------------------------------------------------------------------
// class Measure
//---------------------------------------------------------------------------
Measure::Measure(int newSize){
   int i, j;
   size = newSize;
   discAccess = new double[size];
   distanceFunction = new double[size];
   totalTime = new clock_t[size];
   goodKick = new int[size];
   for (i = 0; i < SIZERINGCALLS; i++){
      error[i] = new int[size];
   }//end for

   for (i = 0; i < size; i++){
      discAccess[i] = 0;
      distanceFunction[i] = 0;
      totalTime[i] = 0;
      goodKick[i] = 0;
   }//end for

   for (i = 0; i < SIZERINGCALLS; i++){
      for (j = 0; j < size; j++){
         error[i][j] = 0;
      }//end for
   }//end for
}//end Measure

//---------------------------------------------------------------------------
void Measure::Reset(){
   int i;
   for(i = 0; i < size ; i++){
      discAccess[i] = 0;
      distanceFunction[i] = 0;
      totalTime[i] = 0;
   }//end for
}//end Reset

//---------------------------------------------------------------------------
// class ResultMeasure
//---------------------------------------------------------------------------
ResultMeasure::ResultMeasure(int newSize) : Measure(newSize){
   int i;
   double fator[] = {0.001, 0.002, 0.005, 0.01, 0.02, 0.05, 0.1, 0.2, 0.5, 1};
   if (newSize>10){
      size = 10;
   }//end if
   k = new double[size];
   //if is a point query
   for (i = 0; i < size ; i++){
      k[i] = fator[i];
   }//end for
}//end ResultMeasure

//---------------------------------------------------------------------------
// class ResultMeasureDiscrete
//---------------------------------------------------------------------------
ResultMeasureDiscrete::ResultMeasureDiscrete(int newSize) : Measure(newSize){
   int i;
   k = new int[size];
   //if is a point query
   for (i = 0; i < size ; i++){
      k[i] = i+1;
   }//end for
}//end ResultMeasureDiscrete
