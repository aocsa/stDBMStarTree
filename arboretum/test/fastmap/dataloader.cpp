//---------------------------------------------------------------------------

#include <fstream>
#pragma hdrstop

#include "dataloader.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)


//---------------------------------------------------------------------------
//class tData
//---------------------------------------------------------------------------
tData::tData(const char * filename){
   ifstream in(filename);
   int dim;
   int w1;
   int w2;
   double d;
   int tag;

   // Load size and dimension
   in >> dim >> size;

   // Alloc resources
   objects = new tMyObject *[size];

   // Load data
   for (w1 = 0; w1 < size; w1++){
      objects[w1] = new tMyObject(dim);
      for (w2 = 0; w2 < dim; w2++){
         in >> d;
         (*(objects[w1]))[w2] = d;
      }//end for
      in >> tag;
      objects[w1]->SetTag(tag);
   }//end for
   in.close();
}//end tData::tData 

tData::~tData(){
   int w;

   for (w =0; w < size; w++){
      delete objects[w];
   }//end for

   delete [] objects;
}//end tData::~tData

void tData::Print(ostream & out){
   int w;

   for (w =0; w < size; w++){
      out << w << " - " << objects[w] << '\n';
   }//end for
}//end tData::Print


