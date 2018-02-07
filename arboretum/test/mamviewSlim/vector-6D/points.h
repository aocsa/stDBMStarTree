//---------------------------------------------------------------------------
// point.h - Implementation of the User Layer
//
// This file implements the 2 classes required by the SlimTree Library User
// Layer.
//
// TPoint is the object which will be indexed by a metric tree. It abstracts a
// point. Each point has a latitude and a longitude. TPoint defines an
// interface to manipulate its information and also implements the stObject
// interface.
//
// TPointDistanceEvaluator implements the stMetricEvaluator interface. It will
// mesure the distance between MAXSIZE TPoint instances.
//
// With these classes, it is possible to define and instantiate any metric tree
// defined by the SlimTree Library.
//
// Authors: Marcos Rodrigues Vieira (mrvieira@icmc.usp.br)
// Copyright (c) 2002 GBDI-ICMC-USP
//---------------------------------------------------------------------------
#ifndef pointH
#define pointH

#include <math.h>
#include <string>
#include <ostream>
using namespace std;

// define the maxsize of vector
#define MAXSIZE 6

// Metric Tree includes
#include <arboretum/stUserLayerUtil.h>
#include <arboretum/stTypes.h>
#include <arboretum/stUtil.h>

//---------------------------------------------------------------------------
// Class TPoint
//---------------------------------------------------------------------------
/**
* This class abstracts a point in a map. Each point has a pair
* latitude/longitude.
*
* <P>In addition to data manipulation methods (such as GetLatitude()
* and others), this class implements the stObject interface. This interface
* qualifies this object to be indexed by a metric tree implemented by GBDI
* SlimTree Library.
*
* <P>This interface requires no inheritance (because of the use of class
* templates in the Structure Layer) but requires the following methods:
*     - TPoint() - A default constructor.
*     - Clone() - Creates a clone of this object.
*     - IsEqual() - Checks if this instance is equal to another.
*     - GetSerializedSize() - Gets the size of the serialized version of this object.
*     - Serialize() - Gets the serialzied version of this object.
*     - Unserialize() - Restores a serialzied object.
*
* <P>Since the array which contains the serialized version of the object must be
* created and destroyed by each object instance, this class will hold this array
* as a buffer of the serialized version of this instance. This buffer will be
* created only if required and will be invalidated every time the object changes
* its values.
*
* <P>The serialized version of the object will be created as follows:<BR>
* <CODE>
* +--------+--------+--------------+<BR>
* | Value1 | ...    | ValueMAXSIZE |
* +--------+--------+--------------+<BR>
* </CODE>
*
* <P>Values are stored as doubles (2 64-bit IEEE floating point value).
*
* @version 1.0
* @author Marcos Rodrigues Vieira
*/
class TPoint{
   public:
      /**
      * Default constructor. It creates a point with no name and longitude and
      * latitude set to 0. This constructor is required by stObject interface.
      */
      TPoint(){
         for (int i=0; i<MAXSIZE; i++){
            Values[i] = 0;
         }//end for

         // Invalidate Serialized buffer.
         Serialized = NULL;
      }//end TPoint

      /**
      * Creates a new point.
      *
      * @param values[].
      */
      TPoint(double values[]){
         for (int i=0; i<MAXSIZE; i++){
            Values[i] = values[i];
         }//end for

         // Invalidate Serialized buffer.
         Serialized = NULL;
      }//end TPoint

      /**
      * Destroys this instance and releases all associated resources.
      */
      ~TPoint(){

         // Does Serialized exist ?
         if (Serialized != NULL){
            // Yes! Dispose it!
            delete [] Serialized;
         }//end if
      }//end TPoint

      /**
      * Gets the value of the point.
      */
      double GetValue(int i){
         return Values[i];
      }//end GetValue

      /**
      * Gets the values of the EigenFaces.
      *
      */
      double * GetValues(){
         double * d = new double[MAXSIZE];
         int i;

         for(i=0; i<MAXSIZE; i++)
            d[i] = Values[i];

            return d;
      }//end GetLatitude

      // The following methods are required by the stObject interface.
      /**
      * Creates a perfect clone of this object. This method is required by
      * stObject interface.
      *
      * @return A new instance of TPoint wich is a perfect clone of the original
      * instance.
      */
      TPoint * Clone(){
         return new TPoint(Values);
      }//end Clone

      /**
      * Checks to see if this object is equal to other. This method is required
      * by  stObject interface.
      *
      * @param obj Another instance of TPoint.
      * @return True if they are equal or false otherwise.
      */
      bool IsEqual(TPoint * obj){

         for (int i=0; i<MAXSIZE; i++){
            if (this->Values[i] != obj->GetValue(i))
               return false;
         }//end for

         return true;
      }//end IsEqual

      /**
      * Returns the size of the serialized version of this object in bytes.
      * This method is required  by  stObject interface.
      */
      stSize GetSerializedSize(){

         return (sizeof(double) * MAXSIZE);
      }//end GetSerializedSize

      /**
      * Returns the serialized version of this object.
      * This method is required  by  stObject interface.
      *
      * @warning If you don't know how to serialize an object, this methos may
      * be a good example.
      */
      const stByte * Serialize();

      /**
      * Rebuilds a serialized object.
      * This method is required  by  stObject interface.
      *
      * @param data The serialized object.
      * @param datasize The size of the serialized object in bytes.
      * @warning If you don't know how to serialize an object, this methos may
      * be a good example.
      */
      void Unserialize (const stByte * data, stSize datasize);

   private:

      /**
      * Values.
      */
      double Values[MAXSIZE];

      /**
      * Serialized version. If NULL, the serialized version is not created.
      */
      stByte * Serialized;
};//end TMapPoint

//---------------------------------------------------------------------------
// Class TPointDistanceEvaluator
//---------------------------------------------------------------------------
/**
* This class implements a metric evaluator for TPoint instances. It calculates
* the distance between cities by performing a euclidean distance between point
* coordinates (I know it is not accurate but is is only a sample!!!).
*
* <P>It implements the stMetricEvaluator interface. As stObject interface, the
* stMetricEvaluator interface requires no inheritance and defines 2 methods:
*     - GetDistance() - Calculates the distance between 2 objects.
*     - GetDistance2()  - Calculates the distance between 2 objects raised by 2.
*
* <P>Both methods are defined due to optmization reasons. Since euclidean
* distance raised by 2 is easier to calculate, It will implement GetDistance2()
* and use it to calculate GetDistance() result.
*
* @version 1.0
* @author Marcos Rodrigues Vieira
*/
class TPointDistanceEvaluator : public stMetricEvaluatorStatistics{
   public:

      /**
      * Returns the distance between 2 cities. This method is required by
      * stMetricEvaluator interface.
      *
      * @param obj1 Object 1.
      * @param obj2 Object 2.
      */
      stDistance GetDistance(TPoint * obj1, TPoint * obj2){
         return sqrt(GetDistance2(obj1, obj2));
      }//end GetDistance

      /**
      * Returns the distance between 2 cities raised by the power of 2.
      * This method is required by stMetricEvaluator interface.
      *
      * @param obj1 Object 1.
      * @param obj2 Object 2.
      */
      stDistance GetDistance2(TPoint * obj1, TPoint * obj2){
         double delta;
         double sum = 0;

         UpdateDistanceCount(); // Update Statistics

         for (int i=0; i<MAXSIZE; i++){
            delta = obj1->GetValue(i) - obj2->GetValue(i);
            sum += delta * delta;
         }//end for

         return sum;
      }//end GetDistance2

};//end TPointDistanceEvaluator

//---------------------------------------------------------------------------
// Output operator
//---------------------------------------------------------------------------
/**
* This operator will write a string representation of a point to an outputstream.
*/
ostream & operator << (ostream & out, TPoint & point);

#endif //end myobjectH
