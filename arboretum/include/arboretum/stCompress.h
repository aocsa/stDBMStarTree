/**********************************************************************
* GBDI Arboretum - Copyright (c) 2002-2004 GBDI-ICMC-USP
*
*                           Homepage: http://gbdi.icmc.usp.br/arboretum
**********************************************************************/
/* ====================================================================
 * The GBDI-ICMC-USP Software License Version 1.0
 *
 * Copyright (c) 2004 Grupo de Bases de Dados e Imagens, Instituto de
 * Ci�ncias Matem�ticas e de Computa��o, University of S�o Paulo -
 * Brazil (the Databases and Image Group - Intitute of Matematical and 
 * Computer Sciences).  All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the documentation and/or other materials provided with the
 *    distribution.
 *
 * 3. The end-user documentation included with the redistribution,
 *    if any, must include the following acknowledgment:
 *       "This product includes software developed by Grupo de Bases
 *        de Dados e Imagens, Instituto de Ci�ncias Matem�ticas e de
 *        Computa��o, University of S�o Paulo - Brazil (the Databases 
 *        and Image Group - Intitute of Matematical and Computer 
 *        Sciences)"
 *
 *    Alternately, this acknowledgment may appear in the software itself,
 *    if and wherever such third-party acknowledgments normally appear.
 *
 * 4. The names of the research group, institute, university, authors
 *    and collaborators must not be used to endorse or promote products
 *    derived from this software without prior written permission.
 *
 * 5. The names of products derived from this software may not contain
 *    the name of research group, institute or university, without prior
 *    written permission of the authors of this software.
 *
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND ANY EXPRESSED OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED.  IN NO EVENT SHALL THE AUTHORS OF THIS SOFTWARE OR
 * ITS CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF
 * USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT
 * OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 * ====================================================================
 *                                            http://gbdi.icmc.usp.br/
 */
/**
* @file
*
* This file defines the class...
*
* @version 1.0
* $Revision: 1.3 $
* $Date: 2004/03/06 18:48:37 $
* $Author: fabio $
* @author Fabio Jun Takada Chino (chino@icmc.sc.usp.br)
* @author Enzo Seraphim (seraphim@icmc.sc.usp.br)
* @todo Documentation!!!
*/
// Copyright (c) 2002-2003 GBDI-ICMC-USP
#ifndef __STCOMPRESS_H
#define __STCOMPRESS_H

#include <arboretum/stCommon.h>
#include <arboretum/stTypes.h>

/**
*
* @ingroup userlayerutil
*/
class stCompressor{
   public:
      /**
      * Returns a pointer to the data array.
      */
      const stByte * GetData() const{
         return buff;
      }//end GetData
      
      /**
      * Returns the number of bytes of the data array.
      */
      const stSize GetDataSize() const{
         // return ceil(bitOffset / 8)
         return (bitOffset >> 3) + ((bitOffset & 0x7) ? 1 : 0);
      }//end GetDataSize
      
      /**
      * Writes the contents of buff to this compressor.
      *
      * @param buff The buffer.
      * @param size Size of the buffer in bytes.
      */
      virtual void Write(stByte * buff, stSize size) = 0;      
      
      /**
      * Resets this compressor. All compressed data will be lost.
      */
      void Reset(){
         bitOffset = 0;
      }//end Reset
      
      /**
      * Reserves a given number of bytes in the internal buffer.
      *
      * @param size The number of byte to be reserved.
      */
      void Reserve(stSize size){
         Resize(size * 8);
      }//end Reserve
   protected:
      /**
      * Bit buffer.
      */
      stByte * buff;
      
      /**
      * Size of bit buffer in bytes.
      */
      stSize buffSize;
      
      /**
      * Current bit offset.
      */
      stSize bitOffset;
      
      /**
      * Increment of the internal buffer in bytes.
      */
      stSize increment;
      
      /**
      * Returns true if the given number of bits will fit in the internal buffer.
      *
      * @param size Number of bits.
      */
      bool WillFit(stSize size);
      
      /**
      * Writes the contents of buff to this compressor.
      *
      * @param buff The buffer.
      * @param size Number of bits to write.
      */
      void WriteBits(stByte * buff, stSize size);
      
      /**
      * Resizes the internal buffer.
      *
      * @param newSize New number of bits.
      */
      void Resize(stSize newSize);
};//end stCompressor

/**
*
* @ingroup userlayerutil
*/
class stDecompressor{
   public:
      /**
      * Sets the compressed data. This method copies the contents of
      * buff to an internal buffer.
      *
      * @param buff Compressed data.
      * @param size Size of the compressed data in bytes.
      */
      void SetData(const stByte * buff, stSize size);
      
      /**
      * Reads some bytes to a buffer.
      *
      * @param buff The buffer.
      * @param size Size of the buffer in bytes.
      */
      virtual void Read(stByte * buff, stSize size) = 0;    
      
      /**
      * Resets the data offset.
      */
      void Reset(){
         bitOffset = 0;
      }//end Reset
   protected:
      /**
      * Bit buffer.
      */
      stByte * buff;
      
      /**
      * Size of bit buffer in bytes.
      */
      stSize buffSize;
      
      /**
      * Current bit offset.
      */
      stSize bitOffset;
      
      /**
      * Reads some bits from data.
      *
      * @param buff The buffer.
      * @param size Number of bits.
      */
      void ReadBits(stByte * buff, stSize size);
};//end stDecompressor


#endif //__STCOMPRESS_H
