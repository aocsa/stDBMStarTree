//---------------------------------------------------------------------------
// word.h - Implementation of the User Layer
//
// This file implements the 2 classes required by the SlimTree Library User
// Layer.
//
// TWord is the object which will be indexed by a metric tree. It abstracts a
// word. Each word has some letters. TWord defines an interface to manipulate
// its information and also implements the stObject interface.
//
// TWordDistanceEvaluator implements the stMetricEvaluator interface. It will
// mesure the distance between 2 TWord instances.
//
// With these classes, it is possible to define and instantiate any metric tree
// defined by the SlimTree Library.
//
// Authors: Marcos Rodrigues Vieira (mrvieira@icmc.sc.usp.br)
//          Adriano Arantes (arantes@icmc.sc.usp.br)
// Copyright (c) 2003 GBDI-ICMC-USP
//---------------------------------------------------------------------------
#ifndef wordH
#define wordH

#include <math.h>
#include <string>
#include <ostream>
using namespace std;

// Metric Tree includes
#include <slimtree/stUserLayerUtil.h>
#include <slimtree/stTypes.h>
#include <slimtree/stUtil.h>

//---------------------------------------------------------------------------
// Class TWord
//---------------------------------------------------------------------------
/**
* This class abstracts a word in a dicitionary. Each word has a collection of
* letters.
*
* <P>In addition to data manipulation methods (such as GetName()
* and others), this class implements the stObject interface. This interface
* qualifies this object to be indexed by a metric tree implemented by GBDI
* SlimTree Library.
*
* <P>This interface requires no inheritance (because of the use of class
* templates in the Structure Layer) but requires the following methods:
*     - TWord() - A default constructor.
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
* +---------+<BR>
* | Name[] |<BR>
* +---------+<BR>
* </CODE>
*
* @version 1.0
* @author Marcos Rodrigues Vieira
*/
class TWord{
   public:
      /**
      * Default constructor. It creates a word with no name.
      * This constructor is required by stObject interface.
      */
      TWord(){
         Name = "";

         // Invalidate Serialized buffer.
         Serialized = NULL;
      }//end TWord

      /**
      * Creates a new word.
      *
      * @param name The name of the word.
      */
      TWord(const string name){
         Name = name;

         // Invalidate Serialized buffer.
         Serialized = NULL;
      }//end TWord

      /**
      * Destroys this instance and releases all associated resources.
      */
      ~TWord(){

         // Does Serialized exist ?
         if (Serialized != NULL){
            // Yes! Dispose it!
            delete [] Serialized;
         }//end if
      }//end TWord

      /**
      * Gets the name of the word.
      */
      const string & GetName(){
         return Name;
      }//end GetName

      // The following methods are required by the stObject interface.
      /**
      * Creates a perfect clone of this object. This method is required by
      * stObject interface.
      *
      * @return A new instance of TWord wich is a perfect clone of the original
      * instance.
      */
      TWord * Clone(){
         return new TWord(Name);
      }//end Clone

      /**
      * Checks to see if this object is equal to other. This method is required
      * by  stObject interface.
      *
      * @param obj Another instance of TWord.
      * @return True if they are equal or false otherwise.
      */
      bool IsEqual(TWord *obj){

         return (Name == obj->GetName());
      }//end IsEqual

      /**
      * Returns the size of the serialized version of this object in bytes.
      * This method is required  by  stObject interface.
      */
      stSize GetSerializedSize(){

         return Name.length();
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
      void Unserialize (const stByte *data, stSize datasize);

   private:

      /**
      * The name of the word.
      */
      string Name;

      /**
      * Serialized version. If NULL, the serialized version is not created.
      */
      stByte * Serialized;
};//end TMapPoint

//---------------------------------------------------------------------------
// Class TWordDistanceEvaluator
//---------------------------------------------------------------------------
/**
* This class implements a metric evaluator for TWord instances. It calculates
* the distance between cities by performing a euclidean distance between word
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
* @author Fabio Jun Takada Chino
*/
class TWordDistanceEvaluator : public stMetricEvaluatorStatistics{

  public:

      /**
      * This method implements the getDistance() defined in stMetricEvaluator interface.
      * LInfinity distance function is used to perform distance evaluation.
      *
      * @param o1 Object 1.
      * @param o2 Object 2.
      * @return The distance.
      */
      stDistance GetDistance(TWord * o1, TWord * o2);

      /**
      * This method calculates the metric distance between 2 objects raised
      * by the power of 2.
      *
      * @param obj1 Object 1.
      * @param obj2 Object 2.
      * @return The distance between to objects raised by the power of 2.
      */
      stDistance GetDistance2(TWord * obj1, TWord * obj2);

  protected:

        /**
        * This method returns the smallest number between three integers.
        *
        * @param a integer 1.
        * @param b integer 2.
        * @param c integer 3.
        * @return the smallest parameter.
        */
        int Min3(int a, int b, int c);
};//end TWordDistanceEvaluator

//---------------------------------------------------------------------------
// Output operator
//---------------------------------------------------------------------------
/**
* This operator will write a string representation of a word to an outputstream.
*/
ostream & operator << (ostream & out, TWord & word);

#endif //end myobjectH
