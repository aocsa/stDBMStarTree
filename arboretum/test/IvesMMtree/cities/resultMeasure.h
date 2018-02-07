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

      Measure(int newSize);

      ~Measure(){
         delete[] discAccess;
         delete[] distanceFunction;
         delete[] totalTime;
      }//end ~Measure

      int getSize(){
         return size;
      }//end setSize

      virtual double GetK(int i){};

      double getDiscAccess(int i){
         if (i>=0 && i<size)
            return discAccess[i];
         else
            return 0;
      }//end getDiscAccess

      void setDiscAccess(int i, double value){
         if (i>=0 && i<size)
            discAccess[i] = value;
      }//end setDiscAccess

      double getDistanceFunction(int i){
         if (i>=0 && i<size)
            return distanceFunction[i];
         else
            return 0;
      }//end getDistanceFunction

      void setDistanceFunction(int i, double value){
         if (i>=0 && i<size)
            distanceFunction[i] = value;
      }//end setDistanceFunction

      clock_t getTotalTime(int i){
         if (i>=0 && i<size)
            return totalTime[i];
         else
            return 0;
      }//end getTotalTime

      void setTotalTime(int i, clock_t value){
         if (i>=0 && i<size)
            totalTime[i] = value;
      }//end setTotalTime

      void Reset();

   protected:
      double * discAccess;
      double * distanceFunction;
      clock_t * totalTime;
      int size;
      double *k;

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
         if (i>=0 && i<size)
            return k[i];
         else
            return 0;
      }//end getK

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

      double GetK(int i){
         if (i>=0 && i<size)
            return (double) k[i];
         else
            return 0;
      }//end getK

};//end ResultMeasureDiscrete

#endif //end resultMeasureH