
//Includes
#include <graphics.hpp>
#include <math.h>
#include <arboretum/stBasicObjects.h>

//Typedefs
typedef stBasicArrayObject<float> stArray;

typedef float TipoDescrMatrix[4][5];    // [ang][dist]
typedef float TipoRungMatrix[4][5][16]; // [ang][dist][degrau]

//Definitions
 class TTextureExtractorMCO;
 class TDescriptors;
 class TDescriptorsDistanceEvaluator;



//--------------------------------------------------------------------------------
/*
TTextureExtractorMCO
   This class extracts the features of a given bitmap image.
*/
class TTextureExtractorMCO{
   private:
      void Reset();
      float CoocurMatrix[4][5][16][16]; // [ang][dist][i][j]

   public:
      TTextureExtractorMCO(){};
      ~TTextureExtractorMCO(){};

     /**
     *  ExtractFeatures
     *    Calculate the image texture descriptors, returning them in
     *      an object of type TDescriptors, created in the process.
     *      The retured object not belongs to this class after calling the
     *      function.
     */
     TDescriptors* ExtractFeatures(Graphics::TBitmap *image);

     bool BuildMCO(Graphics::TBitmap *image);
     stArray * GetEntropy(int angles=4, int distances=5);
     stArray * GetHomogen(int angles=4, int distances=5);



}; //end class TTextureExtractorMCO

//--------------------------------------------------------------------------------
/*
TDescriptors
   This class stores the image feature as texture descriptors
*/
class TDescriptors{
   private:
      unsigned char *Serialized;

   public:

      //Entropy
      TipoDescrMatrix EntropyMatrix;
      //homogeneity
      TipoDescrMatrix HomogenMatrix;
      //Uniformity or energy
      TipoDescrMatrix UniformMatrix;
      //Third order moment or distortion
      TipoDescrMatrix Moment3Matrix;
      //Variance or contrast
      TipoDescrMatrix VarianceMatrix;
      //Inverse variance or inverse contrast
      TipoDescrMatrix VarInvMatrix;
      //degree (gradient)
      TipoRungMatrix RungMatrix;

      TDescriptors();

      /**
      *  This constructor copies the values of the object pointed by obj
      */
      TDescriptors(TDescriptors *obj);

      ~TDescriptors(){
         if (Serialized != NULL){
            delete [] Serialized;
         }//end if
      };                                

      float GetEntropy(int ang, int dist){
         return EntropyMatrix[ang][dist];
      }
      float GetHomogen(int ang, int dist){
         return HomogenMatrix[ang][dist];
      }
      float GetUniform(int ang, int dist){
         return UniformMatrix[ang][dist];
      }
      float GetMoment3(int ang, int dist){
         return Moment3Matrix[ang][dist];
      }
      float GetVariance(int ang, int dist){
         return VarianceMatrix[ang][dist];
      }
      float GetVarInv(int ang, int dist){
         return VarInvMatrix[ang][dist];
      }
      float GetRung(int ang, int dist, int degree){
         return RungMatrix[ang][dist][degree];
      }

      // The following methods are required by the stObject interface.
      /**
      * Creates a perfect clone of this object. This method is required by
      * stObject interface.
      *
      * @return A new instance of TCity wich is a perfect clone of the original
      * instance.
      */
      TDescriptors * Clone(){
         return new TDescriptors(this);
      }//end Clone

      /**
      * Checks to see if this object is equal to other. This method is required
      * by  stObject interface.
      *
      * @param obj Another instance of TCity.
      * @return True if they are equal or false otherwise.
      */
      bool IsEqual(TDescriptors *obj);

      /**
      * Returns the size of the serialized version of this object in bytes.
      * This method is required  by  stObject interface.
      */
      unsigned long GetSerializedSize(void){
         return (sizeof(float) * ( (6*(4*5)) + (4*5*16) ) );
      }//end GetSerializedSize

      /**
      * Returns the serialized version of this object.
      * This method is required  by  stObject interface.
      *
      */
      const unsigned char * Serialize();

      /**
      * Rebuilds a serialized object.
      * This method is required  by  stObject interface.
      *
      * @param data The serialized object.
      * @param datasize The size of the serialized object in bytes.
      * @warning If you don't know how to serialize an object, this methos may
      * be a good example.
      */
      void Unserialize (const unsigned char *data, unsigned long datasize);   
};


//--------------------------------------------------------------------------------
/*
TDescriptorsDistanceEvaluator
   This class calculates the distance between two TDescriptors objects
*/
class TDescriptorsDistanceEvaluator {   
   private:

     float distance(TipoDescrMatrix feature1, TipoDescrMatrix feature2);
     float distance(TipoRungMatrix feature1, TipoRungMatrix feature2);

   public:

      TDescriptorsDistanceEvaluator(){};
      ~TDescriptorsDistanceEvaluator(){};

      double GetDistance(TDescriptors *obj1, TDescriptors *obj2);

};//end class TDescriptorsDistanceEvaluator


