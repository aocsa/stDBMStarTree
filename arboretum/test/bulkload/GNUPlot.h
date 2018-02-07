//---------------------------------------------------------------------------
// resultMeasureH - .
// GNUPlot - .
//
// Author: Marcos Rodrigues Vieira (mrvieira@icmc.usp.br)
// Copyright (c) 2004 GBDI-ICMC-USP
//---------------------------------------------------------------------------
#ifndef resultMeasureH
#define resultMeasureH

#include <string>
#include <fstream>
#include <ostream>
#include <time.h>
#include <math.h>
#include <values.h>

using namespace std;
//---------------------------------------------------------------------------
// class resultMeasure
//---------------------------------------------------------------------------
class Measure{
   public:

      /**
      * Default Constructor.
      */
      Measure(bool stdDev = false, unsigned int newSize = 7, bool big = false);

      /**
      * Default Destructor.
      */
      virtual ~Measure(){
         delete[] DiskAccess;
         delete[] SDDiskAccess;
         delete[] DistanceFunction;
         delete[] SDDistanceFunction;
         delete[] TotalTime;
         delete[] SDTotalTime;
      }//end ~Measure

      /**
      * Get the size of this class.
      */
      virtual unsigned int GetSize(){
         return Size;
      }//end SetSize

      /**
      * Get the number of distance function of the index i.
      */
      virtual double GetDiskAccess(unsigned int i){
         if (i < Size){
            return DiskAccess[i];
         }//end if
         return 0;
      }//end GetDiskAccess

      /**
      * Set the number of disc accesses of the index i.
      */
      virtual void SetDiskAccess(unsigned int i, double value){
         if (i < Size){
            DiskAccess[i] = value;
         }//end if
      }//end SetDiskAccess

      /**
      * Get standard deviation for number of distance function of the index i.
      */
      virtual double GetSDDiskAccess(unsigned int i);

      /**
      * Set standard deviation for number of disc accesses of the index i.
      */
      virtual void SetSDDiskAccess(unsigned int i, double value){
         if (IsStandardDeviaton()){
            if (i < Size){
               SDDiskAccess[i] = value;
            }//end if
         }//end if
      }//end SetSDDiskAccess

      /**
      * Get the number of distance function of the index i.
      */
      virtual double GetDistanceFunction(unsigned int i){
         if (i < Size){
            return DistanceFunction[i];
         }//end if
         return 0;
      }//end GetDistanceFunction

      /**
      * Set the number of distance function of the index i.
      */
      virtual void SetDistanceFunction(unsigned int i, double value){
         if (i < Size){
            DistanceFunction[i] = value;
         }//end if
      }//end SetDistanceFunction

      /**
      * Get standard deviation for number of distance function of the index i.
      */
      virtual double GetSDDistanceFunction(unsigned int i);

      /**
      * Set the standard deviation for number of distance function of the index i.
      */
      virtual void SetSDDistanceFunction(unsigned int i, double value){
         if (IsStandardDeviaton()){
            if (i < Size){
               SDDistanceFunction[i] = value;
            }//end if
         }//end if
      }//end SetSDDistanceFunction

      /**
      * Get the total time of the index i.
      */
      virtual double GetTotalTime(unsigned int i){
         if (i < Size){
            return TotalTime[i];
         }//end if
         return 0;
      }//end GetTotalTime

      /**
      * Set the total time of the index i.
      */
      virtual void SetTotalTime(unsigned int i, double value){
         if (i < Size){
            TotalTime[i] = value;
         }//end if
      }//end SetTotalTime

      /**
      * Get the standard deviation for total time of the index i.
      */
      virtual double GetSDTotalTime(unsigned int i);

      /**
      * Set the standard deviation for total time of the index i.
      */
      virtual void SetSDTotalTime(unsigned int i, double value){
         if (IsStandardDeviaton()){
            if (i < Size){
               SDTotalTime[i] = value;
            }//end if
         }//end if
      }//end SetSDTotalTime

      /**
      * Clear all statistics. This method does not delete any allocation.
      */
      virtual void Reset();

      /**
      * Return if this class is big or not (start with 0.0001 or 0.001).
      */
      bool IsBig(){
         return Big;
      }//end IsBig

      /**
      * Set if this class support standard deviation.
      */
      void SetStandardDeviaton(bool stdDev){
         stdDeviation = stdDev;
      }//end SetStandardDeviaton

      /**
      * Return if this class support standard deviation.
      */
      bool IsStandardDeviaton(){
         return stdDeviation;
      }//end IsStandardDeviaton

   protected :

      /**
      * To store the number of disk accesses.
      */
      double * DiskAccess;

      /**
      * To store the standard deviation for disk accesses.
      */
      double * SDDiskAccess;

      /**
      * To store the number of distance funcions.
      */
      double * DistanceFunction;

      /**
      * To store the standard deviation for distance funcions.
      */
      double * SDDistanceFunction;

      /**
      * To store the total time.
      */
      double * TotalTime;

      /**
      * To store the standard deviation for total time.
      */
      double * SDTotalTime;

      /**
      * The size of the measures.
      */
      unsigned int Size;

      /**
      * For standard deviation.
      */
      bool stdDeviation;

      /**
      * For the start value (0.0001 or 0.001).
      */
      bool Big;

};//end Measure

//---------------------------------------------------------------------------
// class resultMeasure
//---------------------------------------------------------------------------
class ResultMeasure: public Measure{
   public:

      /**
      * Default Constructor.
      */
      ResultMeasure(bool stdDev = false, unsigned int newSize = 7, 
                    bool big = false, unsigned int divisions = 3);

      /**
      * Default Destructor.
      */
      ~ResultMeasure(){
         delete[] K;
      }//end ~ResultMeasure

      /**
      * Get the value of k in the index i. This method will return a double
      * value to indicate how percentage of the dataset the query must return.
      */
      double GetK(unsigned int i){
         if (i < Size){
            return K[i];
         }//end if
         return 0;
      }//end GetK

      /**
      * Return the number of division points in X scale.
      */
      unsigned int GetDivisions(){
         return Divisions;
      }//end GetDivisions

   private:

      /**
      * Store the values of the percentage of radius in a RQ.
      */
      double * K;

      /**
      * Store the number of point between one block of log values.
      */
      unsigned int Divisions;

};//end ResultMeasure

//---------------------------------------------------------------------------
// class ResultMeasureDiscrete
//---------------------------------------------------------------------------
class ResultMeasureDiscrete: public Measure{
   public:

      /**
      * Default Constructor.
      */
      ResultMeasureDiscrete(unsigned int initialK = 2, bool stdDev = false, 
                            unsigned int newSize = 7);

      /**
      * Default Destructor.
      */
      ~ResultMeasureDiscrete(){
         delete[] K;
      }//end ~ResultMeasureDiscrete

      /**
      * Get the value of k in the index i. This value represents the k in a
      * kNNQ.
      */
      unsigned int GetK(unsigned int i){
         if (i < Size){
            return K[i];
         }//end if
         return 0;
      }//end GetK

      unsigned int StartValue(){
         return startValue;
      }//end StartValue
      
   private:

      /**
      * Store the values of k in a kNNQ.
      */
      unsigned int * K;

      /**
      * Store the initial value of K.
      */
      unsigned int startValue;

};//end ResultMeasureDiscrete

#endif //end resultMeasureH


#ifndef gnuPlotH
#define gnuPlotH

#define NUMBEROFFILES 3

//---------------------------------------------------------------------------
// class GNUPlot
//---------------------------------------------------------------------------
class GNUPlot{

   public:

      /**
      * The kind of measure.
      */
      enum tFileType{
         /**
         * For disk access.
         */
         DISKACCESS,

         /**
         * For distance function.
         */
         DISTFUNCTION,

         /**
         * For total time.
         */
         TOTALTIME
      };//end tFileType

      /**
      * Constructor.
      *
      * @param size Is the initial value to store Result classes. This value
      * can grow with the Resize() method.
      * @see Resize()
      */
      GNUPlot(unsigned int size = 10);

      /**
      * Constructor.
      *
      * @param fileNameDA The name of the file to write the statistics of
      * disc access.
      * @param fileNameDF The name of the file to write the statistics of
      * distance function.
      * @param fileNameTT The name of the file to write the statistics of
      * total time.
      */
      GNUPlot(string fileNameDA, string fileNameDF, string fileNameTT,
              unsigned int size = 10);

      /**
      * Destructor.
      */
      ~GNUPlot();
      
      /**
      * Set the name of the file in the index i.
      */
      void SetFileName(unsigned int i, string fileName);

      /**
      * Get the name of the file in the index i.
      */
      string GetFileName(unsigned int i){
         if (i < NUMBEROFFILES){
            return FileName[i];
         }//end if
         return "";
      }//end GetFileName

      /**
      * Get the result in the index i.
      */
      const Measure * GetMeasure(unsigned int i){
         if (i < NroResults){
            return Results[i];
         }//end if
         return NULL;
      }//end GetResultMeasure

      /**
      * Add a new result in this class.
      *
      * @param result The result class to be added.
      * @return the index that the result was added.
      */
      int AddMeasure(Measure * result);

      /**
      * Add a new result in this class.
      *
      * @param result The result class to be added.
      * @param legend The legend of this result.
      * @return the index that the result was added.
      */
      int AddMeasure(Measure * result, string legend);

      /**
      * Add a new result in this class.
      *
      * @param result The result class to be added.
      * @param legend The legend of this result.
      * @param line  The line of this result.
      * @return the index that the result was added.
      */
      int AddMeasure(Measure * result, string legend, string line);

      /**
      * Write the file of filetype in the disk.
      *
      * @param filetype The file to be write.
      */
      void Write(enum tFileType filetype);

      /**
      * Print in the standard output the results of the index i.
      *
      * @param i Index of the result.
      */
      void Print(unsigned int i);

      /**
      * Print in the standard output all the results and the header.
      */
      void Print();

      /**
      * Get the title of the file in the index i.
      */
      string GetTitle(unsigned int i){
         if (i < NUMBEROFFILES){
            return Title[i];
         }//end if
         return "";
      }//end GetTitle

      /**
      * Set the title of the file in the index i.
      *
      * @param i the index.
      * @param title the new title.
      */
      void SetTitle(unsigned int i, string title);

      /**
      * Set the logscale (axis x and y) of the file in the index i.
      *
      * @param i the index.
      * @param log true if both axis are in log scale.
      */
      void SetLogScale(unsigned int i, bool log){
         if (i < NUMBEROFFILES){
            XLogScale[i] = log;
            YLogScale[i] = log;
         }//end if
      }//end SetLogScale

      /**
      * Get if both axis (x and y) are in logscale.
      *
      * @param i the index.
      */
      bool GetLogScale(unsigned int i);

      /**
      * Set the axis x of logscale.
      *
      * @param i the index.
      * @param newValue true or false.
      */
      void SetXLogScale(unsigned int i, bool newValue){
         if (i < NUMBEROFFILES){
            XLogScale[i] = newValue;
         }//end if
      }//end SetXLogScale

      /**
      * Get if axis x is in logscale.
      *
      * @param i the index.
      */
      bool GetXLogScale(unsigned int i){
         if (i < NUMBEROFFILES){
            return XLogScale[i];
         }//end if
         return false;
      }//end GetXLogScale

      /**
      * Set the axis y of logscale.
      *
      * @param i the index.
      * @param newValue true or false.
      */
      void SetYLogScale(unsigned int i, bool newValue){
         if (i < NUMBEROFFILES){
            YLogScale[i] = newValue;
         }//end if
      }//end SetYLogScale

      /**
      * Get if axis y is in logscale.
      *
      * @param i the index.
      */
      bool GetYLogScale(unsigned int i){
         if (i < NUMBEROFFILES){
            return YLogScale[i];
         }//end if
         return false;
      }//end GetYLogScale

      /**
      * Set the label of axis x.
      *
      * @param i the index.
      * @param label the new value.
      */
      void SetXLabel(unsigned int i, string label);

      /**
      * Get the label of axis x.
      *
      * @param i the index.
      */
      string GetXLabel(unsigned int i){
         if (i < NUMBEROFFILES){
            return XLabel[i];
         }//end if
         return "";
      }//end GetXLabel

      /**
      * Set the label of axis y.
      *
      * @param i the index.
      * @param label the new value.
      */
      void SetYLabel(unsigned int i, string label);

      /**
      * Get the label of axis y.
      *
      * @param i the index.
      */
      string GetYLabel(unsigned int i){
         if (i < NUMBEROFFILES){
            return YLabel[i];
         }//end if
         return "";
      }//end GetYLabel

      /**
      * Set the legend of the index i.
      *
      * @param i the index.
      * @param legend the new legend.
      */
      void SetLegend(unsigned int i, string legend);

      /**
      * Get the legend of the index i.
      *
      * @param i the index.
      */
      string GetLegend(unsigned int i){
         if (i < NroResults){
            return Legend[i];
         }//end if
         return "";
      }//end GetLegend

      /**
      * Set the line of the index i.
      *
      * @param i the index.
      * @param legend the new legend.
      */
      void SetLine(unsigned int i, string line);

      /**
      * Get the line of the index i.
      *
      * @param i the index.
      */
      string GetLine(unsigned int i){
         if (i < NroResults){
            return Line[i];
         }//end if
         return "";
      }//end GetLine

      /**
      * Clear all the results, legends, lines and axis.
      */
      void Clear();

      /**
      * Resize the number of results that can be added in this class.
      */
      void Resize(unsigned int newInc = 10);

      /**
      * Return if this class support standard deviation.
      */
      bool IsStandardDeviaton(){
         return stdDeviation;
      }//end IsStandardDeviaton

   private :

      /**
      * The type of the file: disk access, distance function and total time.
      */
      enum tFileType FileType;

      /**
      * The names for the three files: disk access, distance function
      * and total time. 
      */
      string FileName[NUMBEROFFILES];

      /**
      * The Xlog for the three files.
      */
      bool XLogScale[NUMBEROFFILES];

      /**
      * The Ylog for the three files.
      */
      bool YLogScale[NUMBEROFFILES];

      /**
      * The Xlabel for the three files.
      */
      string XLabel[NUMBEROFFILES];

      /**
      * The Ylabel for the three files.
      */
      string YLabel[NUMBEROFFILES];

      /**
      * The title of the three files.
      */
      string Title[NUMBEROFFILES];

      /**
      * The legend of the three files.
      */
      string * Legend;

      /**
      * The line of the three files.
      */
      string * Line;

      /**
      * The results for the three files.
      */
      Measure ** Results;

      /**
      * The number of Results used in the files.
      */
      unsigned int NroResults;

      /**
      * The maximum number of Results to be used in the files.
      */
      unsigned int Size;

      /**
      * For standard deviation.
      */
      bool stdDeviation;

};//end GNUPlot

#endif //end gnuPlotH
