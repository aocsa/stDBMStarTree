
#include "Texture.h"

// TDescriptor Members Implementation
//--------------------------------------------------------------------------
                      
TDescriptors::TDescriptors(){
   int ang, dist,i;

   Serialized = NULL;

   memset(EntropyMatrix,  0, (4*5)    * sizeof(float));
   memset(HomogenMatrix,  0, (4*5)    * sizeof(float));
   memset(UniformMatrix,  0, (4*5)    * sizeof(float));
   memset(Moment3Matrix,  0, (4*5)    * sizeof(float));
   memset(VarianceMatrix, 0, (4*5)    * sizeof(float));
   memset(VarInvMatrix,   0, (4*5)    * sizeof(float));
   memset(RungMatrix,     0, (4*5*16) * sizeof(float));
}//end TDescriptors::TDescriptors()

//--------------------------------------------------------------------------
TDescriptors::TDescriptors(TDescriptors *obj){
   int ang, dist,i;

   Serialized = NULL;

   memcpy(EntropyMatrix,  obj->EntropyMatrix,  (4*5)    * sizeof(float));
   memcpy(HomogenMatrix,  obj->HomogenMatrix,  (4*5)    * sizeof(float));
   memcpy(UniformMatrix,  obj->UniformMatrix,  (4*5)    * sizeof(float));
   memcpy(Moment3Matrix,  obj->Moment3Matrix,  (4*5)    * sizeof(float));
   memcpy(VarianceMatrix, obj->VarianceMatrix, (4*5)    * sizeof(float));
   memcpy(VarInvMatrix,   obj->VarInvMatrix,   (4*5)    * sizeof(float));
   memcpy(RungMatrix,     obj->RungMatrix,     (4*5*16) * sizeof(float));
}

bool TDescriptors::IsEqual(TDescriptors *obj){
   int cmp=0;

   cmp+= memcmp(EntropyMatrix,  obj->EntropyMatrix,  (4*5)    * sizeof(float));
   cmp+= memcmp(HomogenMatrix,  obj->HomogenMatrix,  (4*5)    * sizeof(float));
   cmp+= memcmp(UniformMatrix,  obj->UniformMatrix,  (4*5)    * sizeof(float));
   cmp+= memcmp(Moment3Matrix,  obj->Moment3Matrix,  (4*5)    * sizeof(float));
   cmp+= memcmp(VarianceMatrix, obj->VarianceMatrix, (4*5)    * sizeof(float));
   cmp+= memcmp(VarInvMatrix,   obj->VarInvMatrix,   (4*5)    * sizeof(float));
   cmp+= memcmp(RungMatrix,     obj->RungMatrix,     (4*5*16) * sizeof(float));

   return (cmp==0)?true:false;
}

const unsigned char * TDescriptors::Serialize(){
   unsigned long skip;
   unsigned char *start;

   if(Serialized == NULL)
      Serialized = new char[GetSerializedSize()];

   skip = (4*5) * sizeof(float);
   start = Serialized;

   memcpy(Serialized, EntropyMatrix,  skip);
   memcpy(Serialized += skip, HomogenMatrix,  skip);
   memcpy(Serialized += skip, UniformMatrix,  skip);
   memcpy(Serialized += skip, Moment3Matrix,  skip);
   memcpy(Serialized += skip, VarianceMatrix, skip);
   memcpy(Serialized += skip, VarInvMatrix,   skip);
   memcpy(Serialized += skip, RungMatrix,     skip*16);

   Serialized = start;
   return start;
}

void TDescriptors::Unserialize(const unsigned char *data, unsigned long datasize){
   unsigned long skip;

   skip = (4*5) * sizeof(float);

   memcpy(EntropyMatrix,  data,          skip);
   memcpy(HomogenMatrix,  data += skip,  skip);
   memcpy(UniformMatrix,  data += skip,  skip);
   memcpy(Moment3Matrix,  data += skip,  skip);
   memcpy(VarianceMatrix, data += skip,  skip);
   memcpy(VarInvMatrix,   data += skip,  skip);
   memcpy(RungMatrix,     data += skip,  skip*16);

   if (Serialized != NULL){
      delete [] Serialized;
      Serialized = NULL;
   }//end if
}



// TTextureExtractorMCO Members Implementation
//--------------------------------------------------------------------------
//--------------------------------------------------------------------------

void TTextureExtractorMCO::Reset(){
   memset(CoocurMatrix, 0, 4*5*16*16 * sizeof(float));
}//end TTextureExtractorMCO::Reset()


bool TTextureExtractorMCO::BuildMCO(Graphics::TBitmap *image){
   int **RGBMatrix;
   int nCountX, nCountY, RR, GG, BB, nRGBResult, nResultReduz;
   int ang, dist, degr, i, j, total;
   int ImageHeight, ImageWidth;
   PByteArray p;

   //Checking
   if (image == NULL){
      return false;
   }

   Reset();
   
   //Initializing
   RGBMatrix = new int *[image->Height];
   for (i = 0; i < image->Height; i++)
      RGBMatrix[i] = new int[image->Width];

//   memset(CoocurMatrix,0, (4*5*16*16) * sizeof(float));
   ImageWidth = image->Width;
   ImageHeight = image->Height;

   //Building RGBMatrix
   for (j = 0; j < image->Height; j++){
      p = (unsigned char *)image->ScanLine[j];
      for (i = 0; i < image->Width; i++)
         RGBMatrix[j][i] = p[i] / 16;
   }

   //Co-Ocorrence matrix
   for(nCountY = 0; nCountY < ImageHeight; nCountY ++)
   {   for(nCountX = 0; nCountX < ImageWidth; nCountX ++)
       {
           for (dist = 1; dist <=5; dist++)
           {   // zero grau
               if (nCountX - dist >= 0 && nCountX + dist < ImageWidth)
               // interno às bordas esq e dir
               {   CoocurMatrix[0][dist-1][RGBMatrix[nCountY][nCountX]][RGBMatrix[nCountY][nCountX+dist]] += 1;
                   CoocurMatrix[0][dist-1][RGBMatrix[nCountY][nCountX]][RGBMatrix[nCountY][nCountX-dist]] += 1;
               }
               else
               // bordas
               {   if (nCountX - dist < 0)
                   // borda esquerda
                   {   CoocurMatrix[0][dist-1][RGBMatrix[nCountY][nCountX]][RGBMatrix[nCountY][nCountX+dist]] += 1;
                   }
                   else
                   // borda direita
                   {   CoocurMatrix[0][dist-1][RGBMatrix[nCountY][nCountX]][RGBMatrix[nCountY][nCountX-dist]] += 1;
                   }
               } // zero grau
               // 90 graus
               if (nCountY - dist >= 0 && nCountY + dist < ImageHeight)
               // interno às bordas sup e inf
               {   CoocurMatrix[2][dist-1][RGBMatrix[nCountY][nCountX]][RGBMatrix[nCountY+dist][nCountX]] += 1;
                   CoocurMatrix[2][dist-1][RGBMatrix[nCountY][nCountX]][RGBMatrix[nCountY-dist][nCountX]] += 1;
               }
               else
               // bordas
               {   if (nCountY - dist < 0)
                   // borda superior
                   {   CoocurMatrix[2][dist-1][RGBMatrix[nCountY][nCountX]][RGBMatrix[nCountY+dist][nCountX]] += 1;
                   }
                   else
                   // borda inferior
                   {   CoocurMatrix[2][dist-1][RGBMatrix[nCountY][nCountX]][RGBMatrix[nCountY-dist][nCountX]] += 1;
                   }
               } // 90 graus
               // 45 graus
               if (nCountX - dist >= 0 && nCountX + dist < ImageWidth &&
                   nCountY - dist >= 0 && nCountY + dist < ImageHeight)
               // interno às bordas esq, dir, sup e inf
               {   CoocurMatrix[1][dist-1][RGBMatrix[nCountY][nCountX]][RGBMatrix[nCountY+dist][nCountX+dist]] += 1;
                   CoocurMatrix[1][dist-1][RGBMatrix[nCountY][nCountX]][RGBMatrix[nCountY-dist][nCountX-dist]] += 1;
               }
               else
               // bordas
               {   if ((nCountX - dist < 0 && nCountY + dist < ImageHeight) ||
                       (nCountY - dist < 0 && nCountX + dist < ImageWidth))
                   // bordas esquerda e superior
                   {   CoocurMatrix[1][dist-1][RGBMatrix[nCountY][nCountX]][RGBMatrix[nCountY+dist][nCountX+dist]] += 1;
                   }
                   if ((nCountX + dist >= ImageWidth && nCountY - dist >= 0) ||
                       (nCountY + dist >= ImageHeight && nCountX - dist >= 0))
                   // bordas direita e inferior
                   {   CoocurMatrix[1][dist-1][RGBMatrix[nCountY][nCountX]][RGBMatrix[nCountY-dist][nCountX-dist]] += 1;
                   }
               } // 45 graus
               // 135 graus
               if (nCountX - dist >= 0 && nCountX + dist < ImageWidth &&
                   nCountY - dist >= 0 && nCountY + dist < ImageHeight)
               // interno às bordas esq, dir, sup e inf
               {   CoocurMatrix[3][dist-1][RGBMatrix[nCountY][nCountX]][RGBMatrix[nCountY-dist][nCountX+dist]] += 1;
                   CoocurMatrix[3][dist-1][RGBMatrix[nCountY][nCountX]][RGBMatrix[nCountY+dist][nCountX-dist]] += 1;
               }
               else
               // bordas
               {   if ((nCountX - dist < 0 && nCountY - dist >= 0) ||
                      (nCountY + dist >= ImageHeight && nCountX + dist < ImageWidth))
                   // bordas esquerda e inferior
                   {   CoocurMatrix[3][dist-1][RGBMatrix[nCountY][nCountX]][RGBMatrix[nCountY-dist][nCountX+dist]] += 1;
                   }
                   if ((nCountX + dist >= ImageWidth && nCountY + dist < ImageHeight) ||
                      (nCountY - dist < 0 && nCountX - dist >= 0))
                   // bordas direita e superior
                   {   CoocurMatrix[3][dist-1][RGBMatrix[nCountY][nCountX]][RGBMatrix[nCountY+dist][nCountX-dist]] += 1;
                   }
               } // 135 graus
           } // for dist
       } // for nCountX
   } // for nCountY

   // Normalizing
   for (nCountY = 0; nCountY < 16; nCountY ++)
   {   
       for (nCountX = 0; nCountX < 16; nCountX ++)
       {   for (dist = 1; dist <= 5; dist ++)
           {   // zero grau
               total = 2 * ImageHeight * (ImageWidth - dist);
               CoocurMatrix[0][dist-1][nCountY][nCountX] /= total;
               // 45 graus
               total = 2 * (ImageHeight - dist) * (ImageWidth - dist);
               CoocurMatrix[1][dist-1][nCountY][nCountX] /= total;
               // 90 graus
               total = 2 * (ImageHeight - dist) * ImageWidth;
               CoocurMatrix[2][dist-1][nCountY][nCountX] /= total;
               // 135 graus
               total = 2 * (ImageHeight - dist) * (ImageWidth - dist);
               CoocurMatrix[3][dist-1][nCountY][nCountX] /= total;
           }
       }
   }//end for

  return true;

}//end TTextureExtractorMCO::BuildMCO()


stArray * TTextureExtractorMCO::GetEntropy(int angles, int distances){
   float *temp,*projected;
   int ang, dist,i, j;
   stArray * result;

   temp = new float[20];
   projected = new float[angles*distances];

   memset(temp, 0, 20 * sizeof(float));
   memset(projected, 0, (angles*distances) * sizeof(float));
   
   //Calculatin the Entropy
   for (ang = 0; ang < 4; ang ++)
   {
      for (dist = 0; dist < 5; dist ++)
      {   // somatória sem diag princ
         for (i = 0; i < 15; i ++)
         {
            for (j = i+1; j < 16; j ++)
            {  if ( CoocurMatrix[ang][dist][i][j] != 0 )
               {
                   temp[5*ang+dist] -=
                    2*(CoocurMatrix[ang][dist][i][j]*log10(CoocurMatrix[ang][dist][i][j]));
               }
            }
         }
         // somatória diag princ
         for (i = 0; i < 16; i ++)
         {
            if ( CoocurMatrix[ang][dist][i][i] != 0 )
            {
               temp[5*ang+dist] -=
                 CoocurMatrix[ang][dist][i][i]*log10(CoocurMatrix[ang][dist][i][i]);
            }
         }
      }//end for
   }//end for

   //projecting angles and distances
     for(int a=0; a < angles; a++){
        for(int d=0; d < distances; d++){
           projected[distances*a+d]=temp[5*a+d];
        }//end for
     }//end for


   //Building stArray
   result = new stArray(angles*distances, projected);
   result->SetTag(angles*10+distances);

   delete [] temp;
   delete [] projected;

   return result;
}

stArray * TTextureExtractorMCO::GetHomogen(int angles, int distances){
   int ang, dist,i, j;
   float *temp,*projected;
   stArray * result;

   temp = new float[20];
   projected = new float[angles*distances];

   memset(temp, 0, 20 * sizeof(float));
   memset(projected, 0, (angles*distances) * sizeof(float));

   for (ang = 0; ang < 4; ang ++)
   {
      for (dist = 0; dist < 5; dist ++)
      {   // somatória sem diag princ
         for (i = 0; i < 15; i ++)
         {
            for (j = i+1; j < 16; j ++)
            {
               temp[5*ang+dist] +=
                 2*(CoocurMatrix[ang][dist][i][j]/(1+abs(i-j)));
            }
         }
         // somatória diag princ
         for (i = 0; i < 16; i ++)
         {
            temp[5*ang+dist] += CoocurMatrix[ang][dist][i][i];
         }
      }
   }//end for

   //projecting angles and distances
     for(int a=0; a < angles; a++){
        for(int d=0; d < distances; d++){
           projected[distances*a+d]=temp[5*a+d];
        }//end for
     }//end for


   //Building stArray
   result = new stArray(angles*distances, projected);
   result->SetTag(angles*10+distances);

   delete [] temp;
   delete [] projected;

   return result;
}




TDescriptors* TTextureExtractorMCO::ExtractFeatures(Graphics::TBitmap *image){

   //Variables
   float CoocurMatrix[4][5][16][16]; // [ang][dist][i][j]
   int **RGBMatrix;
   int nCountX, nCountY, RR, GG, BB, nRGBResult, nResultReduz;
   int ang, dist, degr, i, j, total;
   int ImageHeight, ImageWidth;
   PByteArray p;
   TDescriptors * result;

   //Initializing
   RGBMatrix = new int *[image->Height];
   for (i = 0; i < image->Height; i++)
      RGBMatrix[i] = new int[image->Width];

   memset(CoocurMatrix,0, (4*5*16*16) * sizeof(float));
   ImageWidth = image->Width;
   ImageHeight = image->Height;
   result = new TDescriptors();

   //Building RGBMatrix
   for (j = 0; j < image->Height; j++){
      p = (unsigned char *)image->ScanLine[j];
      for (i = 0; i < image->Width; i++)
         RGBMatrix[j][i] = p[i] / 16;
   }

   //Co-Ocorrence matrix
   for(nCountY = 0; nCountY < ImageHeight; nCountY ++)
   {   for(nCountX = 0; nCountX < ImageWidth; nCountX ++)
       {
           for (dist = 1; dist <=5; dist++)
           {   // zero grau
               if (nCountX - dist >= 0 && nCountX + dist < ImageWidth)
               // interno às bordas esq e dir
               {   CoocurMatrix[0][dist-1][RGBMatrix[nCountY][nCountX]][RGBMatrix[nCountY][nCountX+dist]] += 1;
                   CoocurMatrix[0][dist-1][RGBMatrix[nCountY][nCountX]][RGBMatrix[nCountY][nCountX-dist]] += 1;
               }
               else
               // bordas
               {   if (nCountX - dist < 0)
                   // borda esquerda
                   {   CoocurMatrix[0][dist-1][RGBMatrix[nCountY][nCountX]][RGBMatrix[nCountY][nCountX+dist]] += 1;
                   }
                   else
                   // borda direita
                   {   CoocurMatrix[0][dist-1][RGBMatrix[nCountY][nCountX]][RGBMatrix[nCountY][nCountX-dist]] += 1;
                   }
               } // zero grau
               // 90 graus
               if (nCountY - dist >= 0 && nCountY + dist < ImageHeight)
               // interno às bordas sup e inf
               {   CoocurMatrix[2][dist-1][RGBMatrix[nCountY][nCountX]][RGBMatrix[nCountY+dist][nCountX]] += 1;
                   CoocurMatrix[2][dist-1][RGBMatrix[nCountY][nCountX]][RGBMatrix[nCountY-dist][nCountX]] += 1;
               }
               else
               // bordas
               {   if (nCountY - dist < 0)
                   // borda superior
                   {   CoocurMatrix[2][dist-1][RGBMatrix[nCountY][nCountX]][RGBMatrix[nCountY+dist][nCountX]] += 1;
                   }
                   else
                   // borda inferior
                   {   CoocurMatrix[2][dist-1][RGBMatrix[nCountY][nCountX]][RGBMatrix[nCountY-dist][nCountX]] += 1;
                   }
               } // 90 graus
               // 45 graus
               if (nCountX - dist >= 0 && nCountX + dist < ImageWidth &&
                   nCountY - dist >= 0 && nCountY + dist < ImageHeight)
               // interno às bordas esq, dir, sup e inf
               {   CoocurMatrix[1][dist-1][RGBMatrix[nCountY][nCountX]][RGBMatrix[nCountY+dist][nCountX+dist]] += 1;
                   CoocurMatrix[1][dist-1][RGBMatrix[nCountY][nCountX]][RGBMatrix[nCountY-dist][nCountX-dist]] += 1;
               }
               else
               // bordas
               {   if ((nCountX - dist < 0 && nCountY + dist < ImageHeight) ||
                       (nCountY - dist < 0 && nCountX + dist < ImageWidth))
                   // bordas esquerda e superior
                   {   CoocurMatrix[1][dist-1][RGBMatrix[nCountY][nCountX]][RGBMatrix[nCountY+dist][nCountX+dist]] += 1;
                   }
                   if ((nCountX + dist >= ImageWidth && nCountY - dist >= 0) ||
                       (nCountY + dist >= ImageHeight && nCountX - dist >= 0))
                   // bordas direita e inferior
                   {   CoocurMatrix[1][dist-1][RGBMatrix[nCountY][nCountX]][RGBMatrix[nCountY-dist][nCountX-dist]] += 1;
                   }
               } // 45 graus
               // 135 graus
               if (nCountX - dist >= 0 && nCountX + dist < ImageWidth &&
                   nCountY - dist >= 0 && nCountY + dist < ImageHeight)
               // interno às bordas esq, dir, sup e inf
               {   CoocurMatrix[3][dist-1][RGBMatrix[nCountY][nCountX]][RGBMatrix[nCountY-dist][nCountX+dist]] += 1;
                   CoocurMatrix[3][dist-1][RGBMatrix[nCountY][nCountX]][RGBMatrix[nCountY+dist][nCountX-dist]] += 1;
               }
               else
               // bordas
               {   if ((nCountX - dist < 0 && nCountY - dist >= 0) ||
                      (nCountY + dist >= ImageHeight && nCountX + dist < ImageWidth))
                   // bordas esquerda e inferior
                   {   CoocurMatrix[3][dist-1][RGBMatrix[nCountY][nCountX]][RGBMatrix[nCountY-dist][nCountX+dist]] += 1;
                   }
                   if ((nCountX + dist >= ImageWidth && nCountY + dist < ImageHeight) ||
                      (nCountY - dist < 0 && nCountX - dist >= 0))
                   // bordas direita e superior
                   {   CoocurMatrix[3][dist-1][RGBMatrix[nCountY][nCountX]][RGBMatrix[nCountY+dist][nCountX-dist]] += 1;
                   }
               } // 135 graus
           } // for dist
       } // for nCountX
   } // for nCountY

   // Normalizing
   for (nCountY = 0; nCountY < 16; nCountY ++)
   {   
       for (nCountX = 0; nCountX < 16; nCountX ++)
       {   for (dist = 1; dist <= 5; dist ++)
           {   // zero grau
               total = 2 * ImageHeight * (ImageWidth - dist);
               CoocurMatrix[0][dist-1][nCountY][nCountX] /= total;
               // 45 graus
               total = 2 * (ImageHeight - dist) * (ImageWidth - dist);
               CoocurMatrix[1][dist-1][nCountY][nCountX] /= total;
               // 90 graus
               total = 2 * (ImageHeight - dist) * ImageWidth;
               CoocurMatrix[2][dist-1][nCountY][nCountX] /= total;
               // 135 graus
               total = 2 * (ImageHeight - dist) * (ImageWidth - dist);
               CoocurMatrix[3][dist-1][nCountY][nCountX] /= total;
           }
       }
   }//end for

   //Calculating descriptors

   //Entropy
   for (ang = 0; ang < 4; ang ++)
   {
      for (dist = 0; dist < 5; dist ++)
      {   // somatória sem diag princ
         for (i = 0; i < 15; i ++)
         {
            for (j = i+1; j < 16; j ++)
            {  if ( CoocurMatrix[ang][dist][i][j] != 0 )
               {
                  result->EntropyMatrix[ang][dist] -=
                    2*(CoocurMatrix[ang][dist][i][j]*log10(CoocurMatrix[ang][dist][i][j]));
               }
            }
         }
         // somatória diag princ
         for (i = 0; i < 16; i ++)
         {
            if ( CoocurMatrix[ang][dist][i][i] != 0 )
            {
               result->EntropyMatrix[ang][dist] -=
                 CoocurMatrix[ang][dist][i][i]*log10(CoocurMatrix[ang][dist][i][i]);
            }
         }
      }//end for
   }//end for

   // Homogeneity
   for (ang = 0; ang < 4; ang ++)
   {
      for (dist = 0; dist < 5; dist ++)
      {   // somatória sem diag princ
         for (i = 0; i < 15; i ++)
         {
            for (j = i+1; j < 16; j ++)
            {
               result->HomogenMatrix[ang][dist] +=
                 2*(CoocurMatrix[ang][dist][i][j]/(1+abs(i-j)));
            }
         }
         // somatória diag princ
         for (i = 0; i < 16; i ++)
         {
            result->HomogenMatrix[ang][dist] += CoocurMatrix[ang][dist][i][i];
         }
      }
   }//end for

   // Uniformity
   for (ang = 0; ang < 4; ang ++)
   {
      for (dist = 0; dist < 5; dist ++)
      {   // somatória sem diag princ
         for (i = 0; i < 15; i ++)
         {
            for (j = i+1; j < 16; j ++)
            {
               result->UniformMatrix[ang][dist] +=
                2*(CoocurMatrix[ang][dist][i][j]*CoocurMatrix[ang][dist][i][j]);
            }
         }
         // somatória diag princ
         for (i = 0; i < 16; i ++)
         {
            result->UniformMatrix[ang][dist] +=
                    CoocurMatrix[ang][dist][i][i]*CoocurMatrix[ang][dist][i][i];
         }
      }
   }//end for

   //Third Order Moment
   for (ang = 0; ang < 4; ang ++)
   {
      for (dist = 0; dist < 5; dist ++)
      {   // somatória sem diag princ
         for (i = 0; i < 15; i ++)
         {
            for (j = i+1; j < 16; j ++)
            {
               result->Moment3Matrix[ang][dist] +=
                         2*(CoocurMatrix[ang][dist][i][j]*(i-j)*(i-j)*abs(i-j));
            }//end for
         }//end for
       }//end for
   }//end for

   //Variance
   for (ang = 0; ang < 4; ang ++)
   {
      for (dist = 0; dist < 5; dist ++)
      {   // somatória sem diag princ
         for (i = 0; i < 15; i ++)
         {
            for (j = i+1; j < 16; j ++)
            {
                  result->VarianceMatrix[ang][dist] +=
                                  2*(CoocurMatrix[ang][dist][i][j]*(i-j)*(i-j));
            }//end for
         }//end for
       }//end for
   }//end for

   //Inverse Variance
   for (ang = 0; ang < 4; ang ++)
   {
      for (dist = 0; dist < 5; dist ++)
      {   // somatória sem diag princ
         for (i = 0; i < 15; i ++)
         {
            for (j = i+1; j < 16; j ++)
            {
               result->VarInvMatrix[ang][dist] +=
                                2*(CoocurMatrix[ang][dist][i][j]/((i-j)*(i-j)));
            }//end for
         }//end for
       }//end for
   }//end for

   // degree  (gradient)
   for (ang = 0; ang < 4; ang ++)
   {
       for (dist = 0; dist < 5; dist ++)
       {   // somatória sem diag princ
           for (i = 0; i < 15; i ++)
           {   for (j = i+1; j < 16; j ++)
               {   result->RungMatrix[ang][dist][j-i] += 2 * CoocurMatrix[ang][dist][i][j];
               }
           }
           // somatória diag princ
           for (i = 0; i < 16; i ++)
           {   result->RungMatrix[ang][dist][0] += CoocurMatrix[ang][dist][i][i];
           }

       }
   }//end for



   for (i = 0; i < image->Height; i++)
      delete [] RGBMatrix[i];

   delete[] RGBMatrix;

   return result;
}


// TDescriptorsDistanceEvaluator Members Implementation
//--------------------------------------------------------------------------
double TDescriptorsDistanceEvaluator::GetDistance(TDescriptors *obj1, TDescriptors *obj2){
   float dist1,dist2,dist3;

   dist1 = distance(obj1->EntropyMatrix,obj2->EntropyMatrix);
   dist2 = distance(obj1->HomogenMatrix,obj2->HomogenMatrix);
   dist3 = distance(obj1->RungMatrix,obj2->RungMatrix);

   return (double)((dist1+dist2+dist3)/3);
}

//--------------------------------------------------------------------------
float TDescriptorsDistanceEvaluator::distance(TipoDescrMatrix feature1, TipoDescrMatrix feature2){

   float avgfeature1[4];  //mediaquery
   float avgfeature2[4];  //mediaimage
   float sumquadr, lesser;
   int i,j;

   //initializing
   memset(avgfeature1,0,4*sizeof(float));
   memset(avgfeature2,0,4*sizeof(float));

   //Getting average of descriptor
   for(i=0; i<4; i++)
   {
      for(j=0; j<5; j++)
      {
         avgfeature1[i] += feature1[i][j]/5.0;
         avgfeature2[i] += feature2[i][j]/5.0;
      }
   }

   /*
   for (int ang=0; ang<4; ang++)
      for (int dist=0; dist<5; dist++)
        if(feature1[ang][dist] != feature2[ang][dist]){
           ang=ang;
        }
   */

   //volta zero
   sumquadr = 0;
   for(i=0; i<4; i++)
   {
      sumquadr += (avgfeature1[i]-avgfeature2[i])*(avgfeature1[i]-avgfeature2[i]);
   }
   lesser = sumquadr;
   
   //volta um
   sumquadr = 0;
   for(i=1; i<4; i++)
   {
      sumquadr += (avgfeature1[i]-avgfeature2[i-1])*(avgfeature1[i]-avgfeature2[i-1]);
   }
   sumquadr += (avgfeature1[0]-avgfeature2[3])*(avgfeature1[0]-avgfeature2[3]);
   lesser =  sumquadr < lesser ? sumquadr : lesser;

   //volta dois
   sumquadr = 0;
   for(i=2; i<4; i++)
   {   sumquadr += (avgfeature1[i]-avgfeature2[i-2])*(avgfeature1[i]-avgfeature2[i-2]);
   }
   sumquadr += (avgfeature1[0]-avgfeature2[2])*(avgfeature1[0]-avgfeature2[2]);
   sumquadr += (avgfeature1[1]-avgfeature2[3])*(avgfeature1[1]-avgfeature2[3]);
   lesser =  sumquadr < lesser ? sumquadr : lesser;

   //volta três
   sumquadr = 0;
   for(i=0; i<3; i++)
   {   sumquadr += (avgfeature1[i]-avgfeature2[i+1])*(avgfeature1[i]-avgfeature2[i+1]);
   }
   sumquadr += (avgfeature1[3]-avgfeature2[0])*(avgfeature1[3]-avgfeature2[0]);
   lesser =  sumquadr < lesser ? sumquadr : lesser;
   
   // distância final
   return sqrt(lesser);
}

//--------------------------------------------------------------------------
float TDescriptorsDistanceEvaluator::distance(TipoRungMatrix feature1, TipoRungMatrix feature2){

   float avgdistfeature1[4][16];
   float avgdistfeature2[4][16];
   int i,j,k;
   float sumquadr;
   float lesser;
   float distpond;


   //initializing
   memset(avgdistfeature1,0,4*16*sizeof(float));
   memset(avgdistfeature2,0,4*16*sizeof(float));

   //vetores para sumarizar gradiente antes de calcular a dist
   for(i=0; i<4; i++)
   {   for(k=0; k<16; k++)
       {
           for(j=0; j<5; j++)
           {
              avgdistfeature1[i][k] += feature1[i][j][k]/5.0;
              avgdistfeature2[i][k] += feature2[i][j][k]/5.0;
           }
       }
   }

   //volta zero
   distpond = 0;
   for(i=0; i<4; i++)
   {
      sumquadr = 0;
      for(k=0; k<16; k++)
      {
         sumquadr += (k+1)*(k+1)*(avgdistfeature1[i][k]-avgdistfeature2[i][k])*(avgdistfeature1[i][k]-avgdistfeature2[i][k]);
      }
      distpond += sqrt(sumquadr);
   }//end for
   lesser = distpond;

   //volta um
   distpond = 0;
   for(i=1; i<4; i++)
   {
      sumquadr = 0;
      for(k=0; k<16; k++)
      {
         sumquadr += (k+1)*(k+1)*(avgdistfeature1[i][k]-avgdistfeature2[i-1][k])*(avgdistfeature1[i][k]-avgdistfeature2[i-1][k]);
      }
      distpond += sqrt(sumquadr);
   }
   sumquadr = 0;
   for (k=0; k<16; k++)
   {   sumquadr += (k+1)*(k+1)*(avgdistfeature1[0][k]-avgdistfeature2[3][k])*(avgdistfeature1[0][k]-avgdistfeature2[3][k]);
   }
   distpond += sqrt(sumquadr);
   lesser =  distpond < lesser ? distpond : lesser;

   //volta 2
   distpond = 0;
   for(i=2; i<4; i++)
   {
      sumquadr = 0;
      for(k=0; k<16; k++)
      {
         sumquadr += (k+1)*(k+1)*(avgdistfeature1[i][k]-avgdistfeature2[i-2][k])*(avgdistfeature1[i][k]-avgdistfeature2[i-2][k]);
      }
      distpond += sqrt(sumquadr);
   }
   sumquadr = 0;
   for (k=0; k<16; k++)
   {
      sumquadr += (k+1)*(k+1)*(avgdistfeature1[0][k]-avgdistfeature2[2][k])*(avgdistfeature1[0][k]-avgdistfeature2[2][k]);
   }
   distpond += sqrt(sumquadr);
   sumquadr = 0;
   for (k=0; k<16; k++)
   {
      sumquadr += (k+1)*(k+1)*(avgdistfeature1[1][k]-avgdistfeature2[3][k])*(avgdistfeature1[1][k]-avgdistfeature2[3][k]);
   }
   distpond += sqrt(sumquadr);   
   lesser =  distpond < lesser ? distpond : lesser;

   //volta 3
   distpond = 0;
   for(i=1; i<4; i++)
   {
      sumquadr = 0;
      for(k=0; k<16; k++)
      {
         sumquadr += (k+1)*(k+1)*(avgdistfeature1[i][k]-avgdistfeature2[i+1][k])*(avgdistfeature1[i][k]-avgdistfeature2[i+1][k]);
      }
      distpond += sqrt(sumquadr);
   }
   sumquadr = 0;
   for (k=0; k<16; k++)
   {   sumquadr += (k+1)*(k+1)*(avgdistfeature1[3][k]-avgdistfeature2[0][k])*(avgdistfeature1[3][k]-avgdistfeature2[0][k]);
   }
   distpond += sqrt(sumquadr);
   lesser =  distpond < lesser ? distpond : lesser;
   
   return  lesser;
}

