//---------------------------------------------------------------------------
#ifndef TVector_h
#define TVector_h

#include <string>
#include <iostream>
#include <cstdlib>
#include <cmath>

// Metric Tree includes
#include "arboretum/stUserLayerUtil.h"
#include "arboretum/stTypes.h"
#include "arboretum/stUtil.h"


#include "point.h"


//---------------------------------------------------------------------------
// Class TVector
//---------------------------------------------------------------------------
class TVector{
   public:
    TVector() {
        // Invalidate Serialized buffer.
         
		//Initialize with zeros  
		for(int i = 0; i < GetDimension(); i++)
				 Values[i] = 0.0f;
			Serialized = NULL;
		this->ObjectID = 0;
    }//end TVector
    
    TVector(const Point & p, stPageID oiD = 0) {
        assert( p.dim() == GetDimension() );
        for(int i = 0; i < GetDimension(); i++) {
            this->Values[i] = p[i];
        }
        Serialized = NULL;
        this->ObjectID = oiD;
    }
      TVector(stDistance values[], int dim, stPageID id_){
         for(int i = 0; i < GetDimension(); i++)
             Values[i] = values[i];
         // Invalidate Serialized buffer.
         Serialized = NULL;
         this->ObjectID = id_;         
      }//end TVector

      ~TVector(){
         // Does Serialized exist ?
         if (Serialized != NULL){
            // Yes! Dispose it!
            delete [] Serialized;
         }//end if
      }//end TVector

   	  stDistance& operator [] (int i){
		 return Values[i];
	  }
      const stDistance operator [] (int i) const{
		 return Values[i];
	  }
      int GetDimension() const{
            return DIMENSION;
      }
      // The following methods are required by the stObject interface.
      /**
      * Creates a perfect clone of this object. This method is required by
      * stObject interface.
      *
      * @return A new instance of TVector wich is a perfect clone of the original
      * instance.
      */
      TVector * Clone(){
         return new TVector(Values, GetDimension(), ObjectID);
      }//end Clone

      /**
      * Checks to see if this object is equal to other. This method is required
      * by  stObject interface.
      *
      * @param obj Another instance of TVector.
      * @return True if they are equal or false otherwise.
      */
      bool IsEqual(TVector *obj){
         for(int i = 0; i < obj->GetDimension(); i++) {
            if( Values[i] != obj->Values[i])
                return false;
         }
         return true;
      }//end IsEqual

      /**
      * Returns the size of the serialized version of this object in bytes.
      * This method is required  by  stObject interface.
      */
      stSize GetSerializedSize(){
         return GetDimension() * sizeof(stDistance) + sizeof(stPageID);
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
      void SetOID(stPageID id){ 
            ObjectID = id;
      }
      stPageID GetOID() const {
            return ObjectID;
      }
      const stDistance*	GetWeight() const{
            return Values;	
     }
   private:
      stDistance  Values[DIMENSION];
      stPageID      ObjectID;
      stByte *      Serialized;
};//end TMapPoint

class TVectorDistanceEvaluator : public stMetricEvaluatorStatistics{
public:
	/**
	* Returns the distance between 2 cities. This method is required by
	* stMetricEvaluator interface.
	*
	* @param obj1 Object 1.
	* @param obj2 Object 2.
	*/
	stDistance GetDistance(TVector *obj1, TVector *obj2){
	 return GetDistance2(obj1, obj2);
	}//end GetDistance

	/**
	* Returns the distance between 2 strings raised by the power of 2.
	* This method is required by stMetricEvaluator interface.
	*
	* @param obj1 Object 1.
	* @param obj2 Object 2.
	*/
	stDistance GetDistance2(TVector *obj1, TVector *obj2){
        stDistance distance = 0.0f;
        for(int i = 0; i < obj1->GetDimension(); i++ ) {
            distance += pow((*obj2)[i] - (*obj1)[i], 2);
        }
		this->UpdateDistanceCount();
		return distance;
	}//end GetDistance2


};//end TVectorDistanceEvaluator

//---------------------------------------------------------------------------
// Output operator
//---------------------------------------------------------------------------
/**
* This operator will write a string representation of a city to an outputstream.
*/
std::ostream & operator << (std::ostream & out, const TVector & city);

#endif //end 
 