/**
* @file
*
* This file defines a string object.
*
* @version 1.0
* @author Marcos Rodrigues Vieira (mrvieira@icmc.usp.br)
*/
// Copyright (c) 2002-2003 GBDI-ICMC-USP

#include "stString.h"

//==============================================================================
//  class stString
//------------------------------------------------------------------------------
bool stString::IsEqual(stString * obj){
   bool equal;
   bool stop;
   int i;

   if (GetSize() != obj->GetSize()){
      return false;
   }//end if

   // Scanning...
   equal = true;
   i = 0;
   stop = (i >= GetSize());
   while (!stop){
      if (Data[i] != obj->Data[i]){
         stop = true;
         equal = false;
      }else{
         i++;
         stop = (i >= GetSize());
      }//end if
   }//end while

   return equal;
}//end IsEqual

//------------------------------------------------------------------------------
int stString::StrLength(const char * str){
   int len = 0;

   while (str[len] != 0){
      len++;
   }//end while

   return len;
}//end StrLength

//------------------------------------------------------------------------------
ostream & operator << (ostream & out, stString & word){
   out << "[Word=" << word.GetString() << "]";
   return out;
}//end operator <<
