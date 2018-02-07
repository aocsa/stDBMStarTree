//---------------------------------------------------------------------------
// app.h - Implementation of the application.
//
// Authors: Marcos Rodrigues Vieira (mrvieira@icmc.sc.usp.br)
//          Adriano Arantes (arantes@icmc.sc.usp.br)
// Copyright (c) 2003 GBDI-ICMC-USP
//---------------------------------------------------------------------------
#ifndef appH
#define appH
#define __stDebugNearest__

// Metric Tree includes
#include <arboretum/stMetricTree.h>
//#include <arboretum/stMemoryPageManager.h>
//#include <arboretum/stDiskPageManager.h>
#include <arboretum/stPlainDiskPageManager.h>
#include <arboretum/stSlimTree.h>

// My object
#include "city.h"

#include <string.h>

//---------------------------------------------------------------------------
// class resultMeasure
//---------------------------------------------------------------------------
class resultMeasure{
   public:

      /**
      * .
      */
      resultMeasure(int newSize){
         size = newSize;
         estimationSel = new double[size];
         realSel = new double [size];
         realSelPlus = new double[size];
         realSelMinus = new double[size];

/*         acerto = new int[size];
         bestAcerto = new int[size];
         bestErro = new int[size];

         for(int i=0; i<3; i++)
            erro[i] = new int[size];
*/
         k = new int[size];
         for(int i=0; i<size; i++){
            k[i] = 56*i + 25;  //5257
//            k[i] = 10*(i+1);  //5257
            estimationSel[i] = 0;
            realSel[i] = 0;
            realSelPlus[i] = 0;
            realSelMinus[i]=0;

/*            acerto[i] = 0;
            bestAcerto[i] = 0;
            bestErro[i] = 0;

            for(int j=0; j<3; j++)
               erro[j][i] = 0; */
         }//end for
      }//end resultMeasure()

      /**
      * .
      */
      ~resultMeasure(){
/*         delete [] discAccess;
         delete [] distanceFunction;
         delete [] totalTime;*/
         delete [] estimationSel;
         delete [] realSel;
         delete [] realSelPlus;
         delete [] realSelMinus;
      }//end ~resultMeasure()

      /**
      * .
      */
      int getSize(){
         return size;
      }//end setSize()

/*      int getErro(int i, int j){
         if(i>=0 && i<3 && j>=0 && j<size)
            return erro[i][j];
         else return -1;
      }//end

      void setErro(int i, int j, int value){
         if(i>=0 && i<3 && j>=0 && j<size)
            erro[i][j] = value;
      }//end

      int getAcerto(int i){
         if(i>=0 && i<size)
            return acerto[i];
         else return -1;
      }//end

      void setAcerto(int i, int value){
         if(i>=0 && i<size)
            acerto[i] = value;
      }//end

       for Best Disjuntive Query
      int getBestErro(int i){
         if(i>=0 && i<size)
            return bestErro[i];
         else return -1;
      }//end

      void setBestErro(int i, int value){
         if(i>=0 && i<size)
            bestErro[i] = value;
      }//end

      int getBestAcerto(int i){
         if(i>=0 && i<size)
            return bestAcerto[i];
         else return -1;
      }//end

      void setBestAcerto(int i, int value){
         if(i>=0 && i<size)
            bestAcerto[i] = value;
      }//end
     /* ************************************* */

      /**
      * .
      */
      double getEstimationSel(int i){
         if(i>=0 && i<size)
            return estimationSel[i];
         else return 0L;
      }//end getDiscAccess

      /**
      * .
      */
      void setEstimationSel(int i, double value){
         if(i>=0 && i<size)
            estimationSel[i] = value;
      }//end setDiscAccess

      /**
      * .
      */
      double getRealSel(int i){
         if(i>=0 && i<size)
            return realSel[i];
         else return 0L;
      }//end getDistanceFunction

      /**
      * .
      */
      void setRealSel(int i, double value){
         if(i>=0 && i<size)
            realSel[i] = value;
      }//end setDistanceFunction

      /**
      * .
      */
      double getRealSelPlus(int i){
         if(i>=0 && i<size)
            return realSelPlus[i];
         else return 0L;
      }//end getTotalTime

      /**
      * .
      */
      void setRealSelPlus(int i, double value){
         if(i>=0 && i<size)
            realSelPlus[i] = value;
      }//end setTotalTime

      /**
      * .
      */
      double getRealSelMinus(int i){
         if(i>=0 && i<size)
            return realSelMinus[i];
         else return 0L;
      }//end getTotalTime

      /**
      * .
      */
      void setRealSelMinus(int i, double value){
         if(i>=0 && i<size)
            realSelMinus[i] = value;
      }//end setTotalTime


      /**
      * .
      */
      int getK(int i){
         if(i>=0 && i<size)
            return k[i];
         else return 0;
      }//end getK

   private:

      double * estimationSel;
      double * realSel;
      double * realSelPlus;
      double * realSelMinus;

      int * k;

/*      int * erro[3];
      int * acerto;
      int * bestAcerto;
      int * bestErro;*/
      int size;

};//end resultMeasure

//---------------------------------------------------------------------------
// class TApp
//---------------------------------------------------------------------------
class TApp{
   public:
      /**
      * This is the type used by the result.
      */
      typedef stResult < TCity > myResult;

      /**
      * This is the type of the Slim-Tree defined by TCity and
      * TCityDistanceEvaluator.
      */
      typedef stSlimTree < TCity, TCityDistanceEvaluator > mySlimTree;

      /**
      * Creates a new instance of this class.
      */
      TApp(){
         PageManagerSlim = NULL;
         MetricTreeSlim = NULL;
      }//end TApp

      /**
      * Initializes the application.
      */
      void TApp::Init(unsigned int pageSize, unsigned int datasetSize,
                stDistance fractalDimension, stDistance radiusTree,
                stDistance nObjects, char * prefix, char * range,
                char * difRadius, stDistance percRadius, double third);

      /**
      * Runs the application.
      */
      void TApp::Run(char * DataPath, char * DataQueryPath);

      /**
      * Deinitialize the application.
      */
      void Done();
   private:

      /**
      * The Page Manager for Slim.
      */
      stPageManager * PageManagerSlim;

      /**
      * The Metric Tree for Slim-Tree.
      */
      mySlimTree * MetricTreeSlim;

      /**
      * Vector for holding the query objects.
      */
      vector <TCity *> queryObjects;

      /**
      * Vector for holding the radius of the query objects.
      */
      vector <double> radiusqueryObjects;

      /**
      * Vector for holding the inner radius for the Ring Query objects.
      */
      vector <double> innerRadiusqueryObjects;

      /**
      *  To hold the PageSize
      */
      unsigned int PageSize;

      /**
      * To hold the size of the data set answers.
      */
      unsigned int DatasetSize;

      /**
      * To hold how the queries are divided.
      */
      unsigned int Third;

      /**
      * To hold the fractal dimension.
      */
      stDistance FractalDimension;

      /**
      * To hold the radius of the tree.
      */
      stDistance RadiusTree;

      /**
      * To hold the number of objects in tree.
      */
      stDistance NObjects;

      /**
      * To hold if the range is required.
      */
      bool Range;

      /**
      * To hold if a different radius is required.
      */
      bool DifRadius;

      /**
      * To hold the size of the range queries.
      */
      stDistance PercRadius;

      /**
      * To store the prefix of files.
      */
      string Prefix;

      /**
      * Creates a disk page manager. It must be called before CreateTree().
      */
      void CreateDiskPageManager();

      /**
      * Creates a tree using the current PageManager.
      */
      void CreateTree();

      /**
      * Adds a city to tree.
      *
      * @param name City's name.
      * @param lat City's latitude.
      * @param lon City's longitude.
      */
      void AddToTree(char * name, double lat, double lon){
         TCity * city = new TCity(name, lat, lon);
         MetricTreeSlim->Add(city);
         delete city;
      }//end AddToTree

      /**
      * Loads the tree from file with a set of cities.
      */
      void LoadTree(char * fileName);

      /**
      * .
      */
      void LoadVectorFromFile(char * filename);

      /**
      * Performs the queries and outputs its results.
      */
      void PerformQueries();

      /**
      * Performs a query and outputs its results.
      * K-NEAREST NEIGHBOR QUERY AND RANGE QUERY WITH ESTIMATE RADIUS
      */

      void PerformKAndRangeQuery(resultMeasure * rMeasure, int i);

      void PerformKOrRangeQuery(resultMeasure * resultSlim, int i);

      void PerformRingRangeQuery(resultMeasure * rMeasure, int i);

      void WriteLog(resultMeasure * resultSlim, char * name);

      void WriteBestLog(resultMeasure * resultSlim, char * name);

      void WriteToFile(FILE * file, resultMeasure * rMeasure, int type);

      void WriteHeader(FILE * file, char * type);

      void PrintResults(myResult * result);

      void PerformQuery();

      void SetRadiusFromObjects(resultMeasure * rMeasureSlim, int i);

      void SetRadiusToRingObjects(resultMeasure * rMeasureSlim, int i);


};//end TApp

#endif //end appH
