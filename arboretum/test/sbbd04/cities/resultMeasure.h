//---------------------------------------------------------------------------
// resultMeasureH.h - .
//
// Author: Marcos Rodrigues Vieira (mrvieira@icmc.usp.br)
// Copyright (c) 2004 GBDI-ICMC-USP
//---------------------------------------------------------------------------
#ifndef resultMeasureH
#define resultMeasureH

#include <time.h>
#define SIZERINGCALLS 10

//---------------------------------------------------------------------------
// class resultMeasure
//---------------------------------------------------------------------------
class Measure{
   public:

      Measure(int newSize);

      ~Measure(){
         delete[] discAccess;
         delete[] distanceFunction;
         delete[] totalTime;
         delete[] goodKick;
         for (int i=0; i<SIZERINGCALLS; i++){
            delete error[i];
         }//end for
      }//end ~Measure

      int GetSize(){
         return size;
      }//end SetSize

      double GetDiscAccess(int i){
         if (i>=0 && i<size){
            return discAccess[i];
         }else{
            return 0;
         }//end if
      }//end GetDiscAccess

      void SetDiscAccess(int i, double value){
         if (i>=0 && i<size){
            discAccess[i] = value;
         }//end if
      }//end SetDiscAccess

      double GetDistanceFunction(int i){
         if (i>=0 && i<size){
            return distanceFunction[i];
         }else{
            return 0;
         }//end if
      }//end GetDistanceFunction

      void SetDistanceFunction(int i, double value){
         if (i>=0 && i<size){
            distanceFunction[i] = value;
         }//end if
      }//end SetDistanceFunction

      clock_t GetTotalTime(int i){
         if (i>=0 && i<size){
            return totalTime[i];
         }else{
            return 0;
         }//end if
      }//end GetTotalTime

      void SetTotalTime(int i, clock_t value){
         if (i>=0 && i<size){
            totalTime[i] = value;
         }//end if
      }//end SetTotalTime

      int GetError(int i, int number){
         if(i>=0 && i<SIZERINGCALLS && number>=0 && number<size){
            return error[i][number];
         }else{
            return -1;
         }//end if
      }//end GetError

      void SetError(int i, int number, int value){
         if(i>=0 && i<SIZERINGCALLS && number>=0 && number<size){
            error[i][number] = value;
         }//end if
      }//end SetError

      int GetGoodKick(int i){
         if(i>=0 && i<size){
            return goodKick[i];
         }//end if
      }//end GetGoodKick

      void SetGoodKick(int i, int value){
         if(i>=0 && i<size){
            goodKick[i] = value;
         }//end if
      }//end SetGoodKick

      void Reset();

   protected:
      double * discAccess;
      double * distanceFunction;
      clock_t * totalTime;
      int size;
      int * error[SIZERINGCALLS];
      int * goodKick;
      
};//end Measure

//---------------------------------------------------------------------------
// class resultMeasure
//---------------------------------------------------------------------------
class ResultMeasure: public Measure{
   public:

      ResultMeasure(int newSize);

      ~ResultMeasure(){
         delete[] k;
      }//end ~ResultMeasure

      double GetK(int i){
         if (i>=0 && i<size){
            return k[i];
         }else{
            return 0;
         }//end if
      }//end GetK

   private:
      double * k;

};//end ResultMeasure

//---------------------------------------------------------------------------
// class ResultMeasureDiscrete
//---------------------------------------------------------------------------
class ResultMeasureDiscrete: public Measure{
   public:

      ResultMeasureDiscrete(int newSize);

      ~ResultMeasureDiscrete(){
         delete[] k;
      }//end ~ResultMeasureDiscrete

      int GetK(int i){
         if (i>=0 && i<size){
            return k[i];
         }else{
            return 0;
         }//end if
      }//end GetK

   private:
      int * k;

};//end ResultMeasureDiscrete

#endif //end resultMeasureH