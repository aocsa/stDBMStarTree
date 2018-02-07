//---------------------------------------------------------------------------
// point.cpp - Implementation of the User Layer
//
// In this file we have the implementation of TPoint::Serialize(),
// TPoint::Unserialize() and an output operator for TPoint (which is not required
// by user layer).
//
// Authors: Marcos Rodrigues Vieira (mrvieira@icmc.sc.usp.br)
// Copyright (c) 2003 GBDI-ICMC-USP
//---------------------------------------------------------------------------
#include <mem.h>
#pragma hdrstop
#include "points.h"
#pragma package(smart_init)

//---------------------------------------------------------------------------
// Class TPoint
//---------------------------------------------------------------------------

const stByte * TPoint::Serialize(){
   double * d;

   // Is there a seralized version ?
   if (Serialized == NULL){
      // No! Lets build the serialized version.

      // The first thing we need to do is to allocate resources...
      Serialized = new stByte[GetSerializedSize()];

      d = (double *) Serialized; // If you ar not familiar with pointers, this
                                 // action may be tricky! Be careful!
      for (int i=0; i<MAXSIZE; i++){
         d[i] = Values[i];
      }//end for

   }//end if

   return Serialized;
}//end TPoint::Serialize

//---------------------------------------------------------------------------
void TPoint::Unserialize(const stByte *data, stSize datasize){
   double * d;

   // Read Longitude and Latitude
   d = (double *) data;  // If you ar not familiar with pointers, this
                         // action may be tricky! Be careful!
   for (int i=0; i<MAXSIZE; i++){
      Values[i] = d[i];
   }//end for

   // Since we have changed the object contents, we must invalidate the old
   // serialized version if it exists. In fact we, may copy the given serialized
   // version of tbe new object to the buffer but we don't want to spend memory.
   if (Serialized != NULL){
      delete [] Serialized;
      Serialized = NULL;
   }//end if
}//end TPoint::Unserialize

//---------------------------------------------------------------------------
// Output operator
//---------------------------------------------------------------------------
ostream & operator << (ostream & out, TPoint & point){

   out << "[Point=";
   for (int i=0; i<MAXSIZE; i++){
      out << point.GetValue(i) << ",";
   }//end for
   out << "]";
   return out;
}//end operator <<
