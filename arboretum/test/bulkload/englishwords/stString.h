/**
* @file
*
* This file defines a string object.
*
* @version 1.0
* @author Marcos Rodrigues Vieira (mrvieira@icmc.usp.br)
*/
// Copyright (c) 2002-2003 GBDI-ICMC-USP
#ifndef __STSTRING_H
#define __STSTRING_H

#include <arboretum/stTypes.h>
#include <arboretum/stException.h>

#include <ostream> 

#define DIMENSION 30 

//==============================================================================
//  class stString
//------------------------------------------------------------------------------
class stString{

   public:

      /**
      * Default constructor. It creates an array with 0 elements. Use SetSize()
      * to change the number of entries before use this instance.
      *
      * <P>This constructor is required by the stObject interface.
      */
      stString(){
         Data = NULL;
         Length = 0;
         SetSize();
      }//end stString

      /**
      * Creates a new instance of this class and initializes it with a given
      * null terminated string.
      *
      * @param str A null terminated string.
      */
      stString(const char * str){
         Data = NULL;
         Length = StrLength(str);
         SetSize();
         // Initializing...
         SetString(str);
      }//end stString

      /**
      * Creates a new instance of this class and initializes it with a given
      * null terminated string.
      *
      * @param str A null terminated string.
      */
      stString(stString * str){
         Data = NULL;
         Length = str->GetSize();
         SetSize();
         // Initializing...
         memcpy(Data, str->Data, sizeof(char) * DIMENSION + 1);
      }//end stString

      /**
      * Disposes this instance and releases all associated resources.
      */
      ~stString(){
         if (Data != NULL){
            delete[] Data;
         }//end if
      }//end ~stString

      /**
      * Returns the length of this string. It is a synonym to GetLength().
      * This name is used by the basic metric evaluators templates.
      */
      stSize GetSize(){
         return Length;
      }//end GetSize

      /**
      * Returns the length of this string. It is a synonym to GetSize().
      */
      stSize GetLength(){
         return Length;
      }//end GetLength

      /**
      * This operator can be used to access all positions of the array for
      * reading or writing.
      *
      * @param idx The index of the element.
      * @warning This operator does not check the range of idx.
      */
      unsigned char & operator [] (int idx){
         return Data[idx];
      }//end operator []

      /**
      * Gets the value of the element at a given position.
      *
      * @param idx The index of the desired entry.
      * @exception out_of_range If the index is out of range.
      */
      unsigned char Get(unsigned int idx){
         if (idx >= Length){
            throw out_of_range("Index out of range.");
         }else{
            return Data[idx];
         }//end if
      }//end Get

      /**
      * Copies a null terminated string to this instance.
      *
      * @param str A null terminates string.
      * @see GetString()
      */
      void SetString(const char * str){
         memcpy(Data, str, sizeof(char) * DIMENSION);
         Length = StrLength(str);
         Data[DIMENSION] = '\0'; // Null!!!
      }//end SetString

      /**
      * Returns the contents of this object as a null terminated string.
      *
      * @warning This method is meaningless if the contents of this instance is
      * not a null terminated string.
      * @see SetString()
      */
      const char * GetString(){
         return Data;
      }//end GetString

      // stObject interface
      /**
      * @copydoc stObject::Clone()
      */
      stString * Clone(){
         return new stString(this);
      }//end Clone

      /**
      * @copydoc stObject::GetSerializedSize()
      */
      stSize GetSerializedSize(){
         return (sizeof(char) * DIMENSION);
      }//end GetSerializedSize

      /**
      * @copydoc stObject::Serialize()
      */
      const stByte * Serialize(){
         return Data;
      }//end Serialize

      /**
      * @copydoc stObject::Unserialize()
      */
      void Unserialize(const stByte * data, stSize dataSize){
         // How many entries
         Length = StrLength(data);
         // Copy the data.
         memset(Data, 0, sizeof(char) * DIMENSION);
         memcpy(Data, data, DIMENSION);
         Data[DIMENSION] = '\0'; // Null!!!
      }//end Unserialize

      /**
      * @copydoc stObject::IsEqual()
      */
      bool IsEqual(stString * obj);

   private:

      /**
      * Data array. It points to a position in the Data array.
      */
      stByte * Data;

      /**
      * String length of the Data used.
      */
      stSize Length;

      /**
      * Calculates the size of a NULL terminates string.
      *
      * @param str The string.
      */
      int StrLength(const char * str);

      /**
      * Resizes the string if required. Only the OID value will be preserved.
      *
      * @param length The new length.
      */
      void SetSize(){
         // I must resize it.
         if (Data == NULL){
            // Allocate
            Data = new stByte[(sizeof(char) * (DIMENSION + 1))];
            memset(Data, 0, DIMENSION);
         }//end if
      }//end SetSize
      
};//end stString

ostream & operator << (ostream & out, stString & obj);

#endif //__STSTRING_H
