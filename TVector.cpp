
#include "TVector.h"

//---------------------------------------------------------------------------
// Class TVector
//---------------------------------------------------------------------------
/**
* Returns the serialized version of this object.
* This method is required  by  stObject interface.
* @warning If you don't know how to serialize an object, this methos may
* be a good example.
*/
const stByte * TVector::Serialize(){
   stDistance * d;

   // Is there a seralized version ?
   if (Serialized == NULL){
      // No! Lets build the serialized version.

      // The first thing we need to do is to allocate resources...
      Serialized = new stByte[GetSerializedSize()];
      stPageID* id = (stPageID *) (Serialized);
      id[0] = this->ObjectID;
      
      d = (stDistance *) (Serialized + sizeof(stPageID)); // If you ar not familiar with pointers, this
                                 // action may be tricky! Be careful!
      for(int i=0; i < GetDimension(); i++)
        d[i] = Values[i];

   }//end if

   return Serialized;
}//end TVector::Serialize


void TVector::Unserialize(const stByte *data, stSize datasize){

   // Now we know the size, lets get it from the serialized version.
   stPageID *id = (stPageID *)data;
   this->ObjectID = id[0];
   
   stDistance *d;
   d = (stDistance *) (data + sizeof(stPageID));  // If you ar not familiar with pointers, this
                         // action may be tricky! Be careful!
   for(int i = 0; i < GetDimension(); i++)
        Values[i] = d[i];

   if (Serialized != NULL){
      delete [] Serialized;
      Serialized = NULL;
   }//end if
}//end TVector::Unserialize

//---------------------------------------------------------------------------
// Output operator
//---------------------------------------------------------------------------
/**
* This operator will write a string representation of a city to an outputstream.
*/
std::ostream & operator << (std::ostream & out, const TVector & city){
   std::cout << "idObj: " << city.GetOID() ;
   //for( int k = 0 ; k < city.GetDimention(); k++)
     //   out << city[k] << ", ";
   return out;
}//end operator <<

 