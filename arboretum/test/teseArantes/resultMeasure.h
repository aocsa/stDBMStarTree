//---------------------------------------------------------------------------
// resultMeasureH.h - .
//
// Author: Marcos Rodrigues Vieira (mrvieira@icmc.usp.br)
// Copyright (c) 2004 GBDI-ICMC-USP
//---------------------------------------------------------------------------
#ifndef resultMeasureH
#define resultMeasureH

#include <time.h>

//---------------------------------------------------------------------------
// class resultMeasure
//---------------------------------------------------------------------------
class Measure{
   public:

      Measure(unsigned int newSize);

      ~Measure(){
         delete[] diskAccess;
         delete[] distanceFunction;
         delete[] totalTime;
      }//end ~Measure

      unsigned int getSize(){
         return size;
      }//end setSize

      double getDiskAccess(unsigned int i){
         if (i < size){
            return diskAccess[i];
         }else{
            return 0;
         }//end if
      }//end getDiskAccess

      void setDiskAccess(unsigned int i, double value){
         if (i < size){
            diskAccess[i] = value;
         }//end if
      }//end setDiskAccess

      double getDistanceFunction(unsigned int i){
         if (i < size){
            return distanceFunction[i];
         }else{
            return 0;
         }//end if
      }//end getDistanceFunction

      void setDistanceFunction(unsigned int i, double value){
         if (i < size){
            distanceFunction[i] = value;
         }//end if
      }//end setDistanceFunction

      double getTotalTime(unsigned int i){
         if (i < size){
            return totalTime[i];
         }else{
            return 0;
         }//end if
      }//end getTotalTime

      void setTotalTime(unsigned int i, double value){
         if (i < size){
            totalTime[i] = value;
         }//end if
      }//end setTotalTime

      void Reset();

   protected:
      double * diskAccess;
      double * distanceFunction;
      double * totalTime;
      unsigned int size;

};//end Measure

//---------------------------------------------------------------------------
// class resultMeasure
//---------------------------------------------------------------------------
class ResultMeasure: public Measure{
   public:

      ResultMeasure(unsigned int newSize);

      ~ResultMeasure(){
         delete[] k;
      }//end ~ResultMeasure

      double getK(unsigned int i){
         if (i < size){
            return k[i];
         }else{
            return 0;
         }//end if
      }//end getK

   private:
      double * k;

};//end ResultMeasure

//---------------------------------------------------------------------------
// class ResultMeasureDiscrete
//---------------------------------------------------------------------------
class ResultMeasureDiscrete: public Measure{
   public:

      ResultMeasureDiscrete(unsigned int newSize);

      ~ResultMeasureDiscrete(){
         delete[] k;
      }//end ~ResultMeasureDiscrete

      unsigned int getK(unsigned int i){
         if (i < size){
            return k[i];
         }else{
            return 0;
         }//end if
      }//end getK

   private:
      unsigned int * k;

};//end ResultMeasureDiscrete

#endif //end resultMeasureH