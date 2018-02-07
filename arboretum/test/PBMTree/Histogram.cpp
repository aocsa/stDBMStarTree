#include "Histogram.h"

//------------------------------------------------------------------------------
stArray * THistogramExtractor::ExtractHistogram(Graphics::TBitmap *image){
   PByteArray p;
   float *histogram;
   stArray *Histo;

   histogram = new float[256];
   memset(histogram, 0, sizeof(float) * 256);

   //building histogram
   for (int j = 0; j < image->Height; j++){
      p = (unsigned char *)image->ScanLine[j];
      for (int i = 0; i < image->Width; i++)
         histogram[p[i]]++;
   }

   for (int j = 0; j < 256; j++)
      histogram[j] /= (image->Width * image->Height);

   Histo = new stArray(256, histogram);
   Histo->SetTag(1);

   delete [] histogram;
   
   return Histo;
}


/*
float * THistogramExtractor::ExtractFeatures(Graphics::TBitmap *image){
   PByteArray p;
   float *histogram;

   histogram = new float[256];
   memset(histogram, 0, sizeof(float) * 256);

   //building histogram
   for (int j = 0; j < image->Height; j++){
      p = (unsigned char *)image->ScanLine[j];
      for (int i = 0; i < image->Width; i++)
         histogram[p[i]]++;
   }

   for (int j = 0; j < 256; j++)
      histogram[j] /= (image->Width * image->Height);

   return histogram;
}
*/
