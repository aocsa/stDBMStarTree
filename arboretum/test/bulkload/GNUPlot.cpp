//---------------------------------------------------------------------------
// Author: Marcos Rodrigues Vieira (mrvieira@icmc.usp.br)
// Copyright (c) 2004 GBDI-ICMC-USP
//---------------------------------------------------------------------------
#include "GNUPlot.h"

//---------------------------------------------------------------------------
// class Measure
//---------------------------------------------------------------------------
Measure::Measure(bool stdDev, unsigned int newSize, bool big){
   unsigned int i;
   stdDeviation = stdDev;
   Size = newSize;
   Big = big;
   // Allocate.
   DiskAccess = new double[Size];
   DistanceFunction = new double[Size];
   TotalTime = new double[Size];
   // Allocate for statandard deviation.
   SDDiskAccess = new double[Size];
   SDDistanceFunction = new double[Size];
   SDTotalTime = new double[Size];
   // Set zero to all.
   for (i = 0; i < Size ; i++){
      DiskAccess[i] = 0;
      DistanceFunction[i] = 0;
      TotalTime[i] = 0;
      SDDiskAccess[i] = 0;
      SDDistanceFunction[i] = 0;
      SDTotalTime[i] = 0;
   }//end for
}//end Measure

//---------------------------------------------------------------------------
void Measure::Reset(){
   unsigned int i;
   // Set zero to all.
   for(i = 0; i < Size ; i++){
      DiskAccess[i] = 0;
      DistanceFunction[i] = 0;
      TotalTime[i] = 0;
      SDDiskAccess[i] = 0;
      SDDistanceFunction[i] = 0;
      SDTotalTime[i] = 0;
   }//end for
}//end ReSet

//---------------------------------------------------------------------------
double Measure::GetSDDiskAccess(unsigned int i){
   if (IsStandardDeviaton()){
      if (i < Size){
         return SDDiskAccess[i];
      }//end if
   }//end if
   return 0;
}//end GetSDDiskAccess

//---------------------------------------------------------------------------
double Measure::GetSDDistanceFunction(unsigned int i){
   if (IsStandardDeviaton()){
      if (i < Size){
         return SDDistanceFunction[i];
      }//end if
   }//end if
   return 0;
}//end GetSDDistanceFunction

//---------------------------------------------------------------------------
double Measure::GetSDTotalTime(unsigned int i){
   if (IsStandardDeviaton()){
      if (i < Size){
         return SDTotalTime[i];
      }//end if
   }//end if
   return 0;
}//end GetSDTotalTime


//---------------------------------------------------------------------------
// class ResultMeasure
//---------------------------------------------------------------------------
ResultMeasure::ResultMeasure(bool stdDev, unsigned int newSize, bool big, 
      unsigned int divisions) : Measure(stdDev, newSize, big){
   unsigned int i;
   double last;
   // Set the values.
   Size = newSize;
   Divisions = divisions;
   K = new double[Size];

   // If this is a big evaluation.
   if (Big){
      last = 0.001;
   }else{
      last = 0.01;
   }//end if
   for (i = 0; i < Size; i++){
      K[i] = last;
      last = 2 * last;
   }//end for
}//end ResultMeasure

//---------------------------------------------------------------------------
// class ResultMeasureDiscrete
//---------------------------------------------------------------------------
ResultMeasureDiscrete::ResultMeasureDiscrete(unsigned int initialK,
      bool stdDev, unsigned int newSize) : Measure(stdDev, newSize){
   unsigned int i;

   // Allocate for k.
   K = new unsigned int[Size];
   startValue = initialK;
   // set k.
   for (i = 0; i < Size ; i++){
      K[i] = i * startValue + startValue;
   }//end for
}//end ResultMeasureDiscrete


//---------------------------------------------------------------------------
// class GNUPlot
//---------------------------------------------------------------------------
GNUPlot::GNUPlot(unsigned int size){
   Size = size;
   NroResults = 0;
   // Set the default values for the 3 files.
   FileName[0] = "DiskAccess.plt";
   FileName[1] = "DistFunction.plt";
   FileName[2] = "TotalTime.plt";
   // Set the rest of attributes.
   for (int i = 0; i < NUMBEROFFILES; i++){
      XLogScale[i] = true;
      YLogScale[i] = true;
      XLabel[i] = "";
      YLabel[i] = "";
   }//end for
   // Allocate resource.
   Legend = new string[Size];
   Line = new string[Size];
   Results = new Measure * [Size];
}//end GNUPlot

//---------------------------------------------------------------------------
GNUPlot::GNUPlot(string fileName1, string fileName2, string fileName3,
                 unsigned int size){
   Size = size;
   NroResults = 0;
   // Set the name of the tree files.
   FileName[0] = fileName1;
   FileName[1] = fileName2;
   FileName[2] = fileName3;
   // Set the rest of attributes.
   for (int i = 0; i < NUMBEROFFILES; i++){
      XLogScale[i] = true;
      YLogScale[i] = true;
      XLabel[i] = "";
      YLabel[i] = "";
   }//end for
   // Allocate resource.
   Legend = new string[Size];
   Line = new string[Size];
   Results = new Measure * [Size];
}//end GNUPlot

//---------------------------------------------------------------------------
GNUPlot::~GNUPlot(){
   // Clean the results.
   for (unsigned int i = 0; i < NroResults; i++){
      delete Results[i];
   }//end for
   Size = 0;
   NroResults = 0;
   // Clean the rest.
   delete[] Legend;
   delete[] Line;
   delete[] Results;
}//end ~GNUPlot

//---------------------------------------------------------------------------
bool GNUPlot::GetLogScale(unsigned int i){
   if (i < NUMBEROFFILES){
      if (XLogScale[i] && YLogScale[i]){
         return true;
      }//end if
   }//end if
   return false;
}//end GetLogScale

//---------------------------------------------------------------------------
void GNUPlot::SetXLabel(unsigned int i, string label){
   if (i < NUMBEROFFILES){
      XLabel[i] = label;
   }//end if
}//end SetXLabel

//---------------------------------------------------------------------------
void GNUPlot::SetYLabel(unsigned int i, string label){
   if (i < NUMBEROFFILES){
      YLabel[i] = label;
   }//end if
}//end SetYLabel

//---------------------------------------------------------------------------
void GNUPlot::SetLegend(unsigned int i, string legend){
   if (i < NroResults){
      Legend[i] = legend;
   }//end if
}//end SetLegend

//---------------------------------------------------------------------------
void GNUPlot::SetLine(unsigned int i, string line){
   if (i < NroResults){
      Line[i] = line;
   }//end if
}//end SetLine

//---------------------------------------------------------------------------
void GNUPlot::SetFileName(unsigned int i, string fileName){
   if (i < NUMBEROFFILES){
      FileName[i] = fileName;
   }//end if
}//end SetFileName

//---------------------------------------------------------------------------
int GNUPlot::AddMeasure(Measure * result){
   // Resize if it is necessary.
   if (NroResults == Size){
      Resize();
   }//end if
   // Allocate the resource.
   ResultMeasureDiscrete * rMeasureDiscrete;
   ResultMeasure * rMeasure;

   if (rMeasureDiscrete = dynamic_cast <ResultMeasureDiscrete *> (result)){
      Results[NroResults] = new ResultMeasureDiscrete(rMeasureDiscrete->StartValue(),
                                rMeasureDiscrete->IsStandardDeviaton(), rMeasureDiscrete->GetSize());
   }else{
      rMeasure = dynamic_cast <ResultMeasure *> (result);
      Results[NroResults] = new ResultMeasure(result->IsStandardDeviaton(),
                                result->GetSize(), result->IsBig(), rMeasure->GetDivisions());
   }//end if

   // Copy the values
   for (unsigned int i = 0; i < result->GetSize(); i++){
      Results[NroResults]->SetDiskAccess(i, result->GetDiskAccess(i));
      Results[NroResults]->SetDistanceFunction(i,
                           result->GetDistanceFunction(i));
      Results[NroResults]->SetTotalTime(i, result->GetTotalTime(i));
      // If there is standard deviation.
      if (result->IsStandardDeviaton()){
         Results[NroResults]->SetSDDiskAccess(i, result->GetSDDiskAccess(i));
         Results[NroResults]->SetSDDistanceFunction(i,
                              result->GetSDDistanceFunction(i));
         Results[NroResults]->SetSDTotalTime(i, result->GetSDTotalTime(i));
      }//end if
   }//end for
   // Set the new legend.
   SetLegend(NroResults, "");
   // Set the new line.
   SetLine(NroResults, "");
   // Update the number of results in this class.
   NroResults++;
   // return the index that the result was added.
   return NroResults - 1;
}//end AddMeasure

//---------------------------------------------------------------------------
int GNUPlot::AddMeasure(Measure * result, string legend){
   int idx = AddMeasure(result);
   // Set the legend.
   SetLegend(idx, legend);
   // Set the line.
   SetLine(idx, "");
   return idx;
}//end AddMeasure

//---------------------------------------------------------------------------
int GNUPlot::AddMeasure(Measure * result, string legend, string line){
   int idx = AddMeasure(result);
   // Set the legend.
   SetLegend(idx, legend);
   // Set the line.
   SetLine(idx, line);
   return idx;
}//end AddMeasure

//---------------------------------------------------------------------------
void GNUPlot::SetTitle(unsigned int i, string title){
   if (i < NUMBEROFFILES){
      Title[i] = title;
   }//end if
}//end SetTitle

//---------------------------------------------------------------------------
void GNUPlot::Write(enum tFileType filetype){
   unsigned int i, j;
   // output file. It depends on the file. One file per time.
   ofstream out(FileName[filetype].c_str());
   ResultMeasureDiscrete * rMeasureDiscrete;
   ResultMeasure * resultMeasure;
   double minX, maxX;

   // Try to open the file.
   if (out.is_open()){
	   // to delimiter the x axis.
	   minX = MAXDOUBLE;
	   maxX = MINDOUBLE;
      for (i = 0; i < NroResults; i++){
         if (rMeasureDiscrete = dynamic_cast <ResultMeasureDiscrete *> (Results[i])){
            rMeasureDiscrete = (ResultMeasureDiscrete *)Results[i];
            // For each result.
            for (j = 0; j < rMeasureDiscrete->GetSize(); j++){
               // for each X in the result.
               if (minX > rMeasureDiscrete->GetK(j)){
                  minX = rMeasureDiscrete->GetK(j);
               }//end if
               if (maxX < rMeasureDiscrete->GetK(j)){
                  maxX = rMeasureDiscrete->GetK(j);
               }//end if
            }//end for
         }else{
            resultMeasure = (ResultMeasure *)Results[i];
            // For each result.
            for (j = 0; j < resultMeasure->GetSize(); j++){
               // for each X in the result.
               if (minX > resultMeasure->GetK(j)){
                  minX = resultMeasure->GetK(j);
               }//end if
               if (maxX < resultMeasure->GetK(j)){
                  maxX = resultMeasure->GetK(j);
               }//end if
            }//end for
         }//end if
      }//end for

      // First write the header.
      out << "set title \"" << GetTitle(filetype) << "\"" << endl;
      out << "set xlabel \"" << GetXLabel(filetype) << "\"" << endl;
      out << "set ylabel \"" << GetYLabel(filetype) << "\"" << endl;
      // Write the XRange
//      out << "set xrange [" << minX << ":" << maxX << "]" << endl;
      // Write the logscale.
      if (GetLogScale(filetype)){
         out << "set logscale xy" << endl;
      }else if (GetXLogScale(filetype)){
         out << "set logscale x" << endl;
      }else if (GetYLogScale(filetype)){
         out << "set logscale y" << endl;
      }//end if
      // Write the legends of the lines.
      out << "plot ";
      for (i = 0; i < NroResults; i++){
         out << "'-' title '" << GetLegend(i) << "' with ";
         if (GetLine(i) == ""){
            if (Results[i]->IsStandardDeviaton()){
               out << "error ";
            }else{
               out << "linespoints ";
            }//end if
            out << "lt " << i + 1 << " lw 2 pt " << i + 1 << " ";
         }else{
            out << GetLine(i);
         }//end if
         // Write the comma if there is another line.
         if (i < NroResults - 1){
            out << ", ";
         }//end if
      }//end for
      out << endl << endl;
      
      // Write the data of the results.
      out << "####################" << endl;
      for (i = 0; i < NroResults; i++){
         // Write the title of this result.
         out << "# " << Legend[i] << endl;
         // Write the data itself.
         for (j = 0; j < Results[i]->GetSize(); j++){
            // Write the x data.
            // What kind of result this is?
            if (rMeasureDiscrete = dynamic_cast <ResultMeasureDiscrete *> (Results[i])){
               rMeasureDiscrete = (ResultMeasureDiscrete *)Results[i];
               out << rMeasureDiscrete->GetK(j);
            }else{
               resultMeasure = (ResultMeasure *)Results[i];
               out << resultMeasure->GetK(j);
            }//end if
            // Write the y data.
            out << "\t";
            switch (filetype){
               case DISKACCESS :
                  out << Results[i]->GetDiskAccess(j);
                  // If there is standard deviation.
                  if (Results[i]->IsStandardDeviaton()){
                     out << "\t" << Results[i]->GetDiskAccess(j) -
                                    Results[i]->GetSDDiskAccess(j)
                         << "\t" << Results[i]->GetDiskAccess(j) +
                                    Results[i]->GetSDDiskAccess(j);
                  }//end if
                  break;
               case DISTFUNCTION :
                  out << Results[i]->GetDistanceFunction(j);
                  // If there is standard deviation.
                  if (Results[i]->IsStandardDeviaton()){
                     out << "\t" << Results[i]->GetDistanceFunction(j) -
                                    Results[i]->GetSDDistanceFunction(j)
                         << "\t" << Results[i]->GetDistanceFunction(j) +
                                    Results[i]->GetSDDistanceFunction(j);
                  }//end if
                  break;
               case TOTALTIME :
                  out << Results[i]->GetTotalTime(j);
                  // If there is standard deviation.
                  if (Results[i]->IsStandardDeviaton()){
                     out << "\t" << Results[i]->GetTotalTime(j) -
                                    Results[i]->GetSDTotalTime(j)
                         << "\t" << Results[i]->GetTotalTime(j) +
                                    Results[i]->GetSDTotalTime(j);
                  }//end if
                  break;
            }//end switch
            out << endl;
         }//end for
         // End of data for this result.
         out << "end" << endl;
      }//end for

      // End of file.
      out << endl << endl << "pause -1";
      
      // Close the file.
      out.close();
   }//end if
}//end Write

//---------------------------------------------------------------------------
void GNUPlot::Resize(unsigned int newInc){
   Measure ** newResults;
   string * newLegend;
   string * newLine;
   unsigned int i;

   // New result vector
   newResults = new Measure * [Size + newInc];
   memcpy(newResults, Results, sizeof(Results) * Size);
   // New legend vector
   newLegend = new string[Size + newInc];
   for (i = 0; i < Size; i++){
      newLegend[i] = Legend[i];
   }//end for
   // New line vector
   newLine = new string[Size + newInc];
   for (i = 0; i < Size; i++){
      newLine[i] = Line[i];
   }//end for

   // Delete old vector
   delete[] Results;
   delete[] Legend;
   delete[] Line;
   Results = newResults;
   Legend = newLegend;
   Line = newLine;
   this->Size += newInc;
}//end Resize

//---------------------------------------------------------------------------
void GNUPlot::Clear(){
   for (unsigned int i = 0; i < Size; i++){
      delete Results;
      Legend[i] = "";
   }//end for
   NroResults = 0;
   for (unsigned int i = 0; i < NUMBEROFFILES; i++){
      XLabel[i] = "";
   }//end for
}//end Clear
