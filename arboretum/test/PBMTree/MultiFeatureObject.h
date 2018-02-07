
//Includes
#include <arboretum/stBasicObjects.h>
#include <stdlib.h>
#include <mem.h>
#include <math.h>

//Includes for the factory
#include "Histogram.h"
#include "Texture.h" 

//---------------------------------------------------------------
//MODIFY HERE THE FEATURES SUPPORTED
//---------------------------------------------------------------

//Modify the type of the array feature
typedef stBasicArrayObject<float> stArray;

//Includes for the features supported (stArray polymorphism plz)


//------------------------------------------------------------------------------
// TFactory - for the feature objects
//------------------------------------------------------------------------------
class TFactory {
   public:
      static const int NF=3;
      static stArray * CreateObject(int i);
};


class TMultiFeature;

//------------------------------------------------------------------------------
// LPMetricEvaluator
//------------------------------------------------------------------------------
class LPMetricEvaluator{
   private:

   public:
      LPMetricEvaluator(){};
      ~LPMetricEvaluator(){};
      
      //Note the order of the functions. One metric must enclose
      //  all others on its left side.
      typedef enum LP {L1, L2, Linf} LPMetric;

      stDistance GetDistance(TMultiFeature *obj1,
                             TMultiFeature *obj2);
};

class TMultiFeature {
   private:
      //Getting the number of features
      static const int NF = TFactory::NF;

      /*
      * This holds the features that the object has, any index, except the first
      * one, can be null.
      */
      stArray *features[NF];

      /*
      * this member represents the metric associated with this object.
      */
      LPMetricEvaluator::LPMetric metric;

      stByte *Serialized;

   public:
      TMultiFeature();
      ~TMultiFeature();

      /*
      * This method sets the specified feature of the object.
      * Warning: The method gets the control of the object pointed by feature.
      */
      void SetFeature(int i, stArray *feature);

       /*
      * This method returns the address of the specified object feature.
      */
      stArray *GetFeature(int i);

      int GetNF(){
         return NF;
      }

      /*
      * This method sets the metric associated with this object.
      */
      void SetMetric(LPMetricEvaluator::LPMetric newmetric){
         metric = newmetric;
      }

       /*
      * This method returns the metric associated with this object.
      */                                     
      LPMetricEvaluator::LPMetric GetMetric(){
         return metric;
      }

    
      //The following methods are required by the stObject polimorphism
      
      TMultiFeature * Clone();

      bool IsEqual(TMultiFeature* obj);

      stSize GetSerializedSize();

      const stByte * Serialize();

      void Unserialize(const stByte * data, stSize datasize);    
};


