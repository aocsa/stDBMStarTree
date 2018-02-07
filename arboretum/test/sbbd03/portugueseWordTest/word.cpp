//---------------------------------------------------------------------------
// word.cpp - Implementation of the User Layer
//
// In this file we have the implementation of TWord::Serialize(),
// TWord::Unserialize() and an output operator for TWord (which is not required
// by user layer).
//
// Authors: Marcos Rodrigues Vieira (mrvieira@icmc.sc.usp.br)
//          Adriano Arantes (arantes@icmc.sc.usp.br)
// Copyright (c) 2003 GBDI-ICMC-USP
//---------------------------------------------------------------------------
#include <mem.h>
#pragma hdrstop
#include "word.h"
#pragma package(smart_init)

//---------------------------------------------------------------------------
// Class TWord
//---------------------------------------------------------------------------
/**
* Returns the serialized version of this object.
* This method is required  by  stObject interface.
* @warning If you don't know how to serialize an object, this methos may
* be a good example.
*/
const stByte * TWord::Serialize(){
   double * d;

   // Is there a seralized version ?
   if (Serialized == NULL){
      // No! Lets build the serialized version.

      // The first thing we need to do is to allocate resources...
      Serialized = new stByte[GetSerializedSize()+1];
      Serialized[GetSerializedSize()] = '\0';

      // Now, write the name...
      memcpy(Serialized, Name.c_str(), Name.length());
   }//end if

   return Serialized;
}//end TWord::Serialize

/**
* Rebuilds a serialized object.
* This method is required  by  stObject interface.
*
* @param data The serialized object.
* @param datasize The size of the serialized object in bytes.
* @warning If you don't know how to serialize an object, this methos may
* be a good example.
*/
void TWord::Unserialize(const stByte *data, stSize datasize){
   double * d;
   stSize strl;

   // This is the reverse of Serialize(). So the steps are similar.
   // Remember, the format of the serizalized object is
   // +--------+
   // | Name[] |
   // +--------+

   // To read the name, we must discover its size first. Since it is the only
   // variable length field, we can get it back by subtract the fixed size
   // from the serialized size.
   strl = datasize;

   // Now we know the size, lets get it from the serialized version.
   Name.assign((char *)(data), strl);

   // Since we have changed the object contents, we must invalidate the old
   // serialized version if it exists. In fact we, may copy the given serialized
   // version of tbe new object to the buffer but we don't want to spend memory.
   if (Serialized != NULL){
      delete [] Serialized;
      Serialized = NULL;
   }//end if
}//end TWord::Unserialize

//---------------------------------------------------------------------------
// Output operator
//---------------------------------------------------------------------------
/**
* This operator will write a string representation of a word to an outputstream.
*/
ostream & operator << (ostream & out, TWord & word){

   out << "[Word=" << word.GetName() << "]";
   return out;
}//end operator <<



//--------------------------------------------------------------------------
//  class stLEdit
//--------------------------------------------------------------------------
stDistance TWordDistanceEvaluator::GetDistance(TWord * o1, TWord * o2){// Original LEdit

   UpdateDistanceCount(); // Update Statistics

   char *s1;
   char *s2;
   int lens, lenl;
   int i, j, temp;
   int diff1[200][200];
   char *w1, *w2;

   s1 = (char *) o1->Serialize();
   s2 = (char *) o2->Serialize();

   /* worddiffcalcount++; */
   lens = strlen(s1);
   lenl = strlen(s2);
   w1 = s1;
   w2 = s2;
   if(lens > lenl){
      temp = lens;
      lens = lenl;
      lenl = temp;
      w1 = s2;
      w2 = s1;
   }//end if
   if ((lens >= 199) || (lenl >= 199)) {
      printf("Word too long\n");
      return(-1);
   }
   for (i=0; i <= lens;  i++)
      diff1[i][0] = i;
   for (i=1; i <= lenl;  i++)
      diff1[0][i] = i;
      
   for (i = 1; i <= lens; i++) {
      for (j = 1; j <= i; j++)
         diff1[i-j+1][ j]  = Min3(diff1[i-j][ j-1] + (w1[i-j] != w2[j-1]),
            diff1[i-j][ j] + 1,
            diff1[i-j+1][ j-1] + 1);
   }//end for
   for (i = 1; i <= lenl - lens - 1; i++) {
      for (j = 1; j <= lens; j++)
         diff1[lens-j+1][ i + j]  =
            Min3(diff1[lens-j][ i+j-1] + (w1[lens-j] != w2[i + j-1]),
               diff1[lens-j][ i+j] + 1,
               diff1[lens-j+1][ i+j-1] + 1);
   }//end for
   for (i = 1; i <= lens; i++) {
      for (j = 0; j <= lens - i; j++)
         diff1[lens-j][ lenl- lens + j + i]  =
            Min3(diff1[lens-j - 1][ lenl - lens + i+j-1] +
            (w1[lens-j - 1] != w2[lenl - lens + i + j-1]),
               diff1[lens-j - 1][ lenl - lens + i+j] + 1,
               diff1[lens-j][ lenl - lens + i+j-1] + 1);
   }//end for

   return(diff1[lens][lenl]);
}//getDistance()

//------------------------------------------------------------------------------
stDistance TWordDistanceEvaluator::GetDistance2(TWord * obj1, TWord * obj2){

   return pow(this->GetDistance(obj1, obj2),2);
}//GetDistance2()

//------------------------------------------------------------------------------
int TWordDistanceEvaluator::Min3(int a, int b, int c) {
   if ((a <= b) && (a <= c)) return(a);
   else if (b <= c)
      return(b);
   else return(c);
}
