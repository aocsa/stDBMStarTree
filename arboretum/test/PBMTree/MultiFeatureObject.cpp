#include "MultiFeatureObject.h"

//------------------------------------------------------------------------------
// TFactory Methods
//------------------------------------------------------------------------------
stArray * TFactory::CreateObject(int i){
   switch (i) {
      case 0 : return new stArray(256);
      case 1 : return new stArray(20);
      case 2 : return new stArray(20);
   }//end switch

   return NULL;
}

//------------------------------------------------------------------------------
// TMultiFeature Methods
//------------------------------------------------------------------------------
TMultiFeature::TMultiFeature(){
   int i;

   for(i=0; i < NF; i++){
      features[i] = NULL;
   }//end for

   metric = LPMetricEvaluator::Linf;
   Serialized = NULL;
}//end TMultiFeature::TMultiFeature()

TMultiFeature::~TMultiFeature(){
   int i;

   for(i=0; i < NF; i++){
      if(features[i] != NULL){
         delete features[i];
      }//end if
   }//end for

   if (Serialized != NULL){
      delete[] Serialized;
      Serialized = NULL;
   }//end if

}//end TMultiFeature::~TMultiFeature()      


void TMultiFeature::SetFeature(int i, stArray *feature){
   if(features[i] != NULL){
    delete features[i];
   }//end if

   features[i] = feature;
}//end TMultiFeature::SetFeature()


stArray * TMultiFeature::GetFeature(int i){
   return features[i];
}//end TMultiFeature::GetFeature()


TMultiFeature * TMultiFeature::Clone(){
   int i;
   TMultiFeature *clone;

   clone = new TMultiFeature();
   
   for(i=0; i < NF; i++){
      if(features[i] != NULL){
         clone->SetFeature(i, features[i]->Clone());   
      }//end if
   }//end for

   clone->SetMetric(this->GetMetric());

   return clone;
}//end TMultiFeature::Clone()


bool TMultiFeature::IsEqual(TMultiFeature* obj){
   int i;

   for(i=0; i < NF; i++){
      if ( ((this->features[i] != NULL) && (obj->GetFeature(i) == NULL)) ||
           ((this->features[i] == NULL) && (obj->GetFeature(i) != NULL))){
         return false;
      }//end if

      if ((this->features[i] != NULL) && (obj->GetFeature(i) != NULL)){
         if (this->features[i]->IsEqual(obj->GetFeature(i)) == false){
            return false;
         }//end if
      }//end if

   }//end for

   return true;
}//end TMultiFeature::IsEqual

stSize TMultiFeature::GetSerializedSize(){
   stSize size;
   int i;

   size=0;

   //The metric associated to the object
   size += sizeof(LPMetricEvaluator::LPMetric);

   //The indication of the size of each feature object
   size += NF * sizeof(stSize);

   //The feature objects size
   for(i=0; i < NF; i++){
      if (this->features[i] != NULL){
         size+= this->features[i]->GetSerializedSize();
      }//end if
   }//end for

   return size;
}//end TMultiFeature::GetSerializedSize()


const stByte * TMultiFeature::Serialize(){
   stByte *tmp;
   int i;

   if (Serialized != NULL){
      delete[] Serialized;
      Serialized = NULL;
   }//end if

   Serialized = new stByte[this->GetSerializedSize()];
   tmp = Serialized;

   //copying associated metric
   *((LPMetricEvaluator::LPMetric *) tmp) = metric;
   ((LPMetricEvaluator::LPMetric *) tmp)++;

   for(i=0; i < NF; i++){
      if(features[i] == NULL){
         *((stSize *) tmp) = 0;
      }
      else{
         *((stSize *) tmp) = features[i]->GetSerializedSize();
         ((stSize *) tmp)++;

         memcpy((void *) tmp, (void *) features[i]->Serialize(), features[i]->GetSerializedSize());

         tmp += features[i]->GetSerializedSize();
      }
   }                                         

   return Serialized;
}//end TMultiFeature::Serialize()


void TMultiFeature::Unserialize(const stByte * data, stSize datasize){
   const stByte *tmp;
   stSize size;
   int i;

   if (Serialized != NULL){
      delete[] Serialized;
      Serialized = NULL;
   }//end if

   tmp = data;

   metric = *((LPMetricEvaluator::LPMetric *) tmp);
   ((LPMetricEvaluator::LPMetric *) tmp)++;

   for(i=0; i < NF; i++){
      size = *((stSize *) tmp);
      ((stSize *) tmp)++;

      if(size == 0){
         if(features[i] != NULL){
            delete features[i];
            features[i] = NULL;
         }//end if       
      }
      else{
         if(features[i] == NULL){
            //Create object
            features[i] = TFactory::CreateObject(i);
         }//end if

         features[i]->Unserialize(tmp, size);
         tmp += size;
       }//end if
   }//end for

}//end TMultiFeature::Unserialize()


//------------------------------------------------------------------------------
// LPMetricEvaluator Methods
//------------------------------------------------------------------------------

stDistance LPMetricEvaluator::
GetDistance(TMultiFeature *obj1, TMultiFeature *obj2){
   LPMetricEvaluator::LPMetric ChosenMetric;
   stDistance distance, temp;
   int i,j;

   //Verifying if both can be projected on the same space
   if( (obj1->GetFeature(0) == NULL) || (obj2->GetFeature(0) == NULL) ){
      //cout << "Error, one object doesnt have the projection attribute\n"
      throw "no_project_attribute_exception";
//      return -1;
   }//end if

   //First choose the metric
   //Tip: The one that contain the other

   ChosenMetric = (obj1->GetMetric() >= obj2->GetMetric()) ? obj1->GetMetric()
                                                           : obj2->GetMetric();
   distance = 0;
   switch (ChosenMetric) {
      case L1:{
         //Compare using L1 only the features objects that both have
         // L1 =  SUM { ((Ai - Bi)) }

         //for every feature object
         for(i=0; i < obj1->GetNF(); i++){
            if( (obj1->GetFeature(i) != NULL) && (obj2->GetFeature(i) != NULL)){
               if( obj1->GetFeature(i)->GetTag() == obj2->GetFeature(i)->GetTag()){
                  for(j=0; j < (int)obj1->GetFeature(i)->GetSize(); j++){
                     temp = fabs(obj1->GetFeature(i)->Get(j) - obj2->GetFeature(i)->Get(j));
                     distance += temp;
                  }//end for
               }// end if tag == tag
            }//end if both are not null
         }//end for

      }
      case L2:{
         //Compare using L2 only the features objects that both have
         // L2 =  sqrt{ SUM { ((Ai - Bi)^2) } }

         //for every feature object
         for(i=0; i < obj1->GetNF(); i++){
            if( (obj1->GetFeature(i) != NULL) && (obj2->GetFeature(i) != NULL)){
               if( obj1->GetFeature(i)->GetTag() == obj2->GetFeature(i)->GetTag()){
                  for(j=0; j < (int)obj1->GetFeature(i)->GetSize(); j++){
                     temp = fabs(obj1->GetFeature(i)->Get(j) - obj2->GetFeature(i)->Get(j));
                     distance += temp * temp;
                  }//end for
               }// end if tag == tag
            }//end if both are not null
         }//end for

         distance = sqrt(distance);
      }
      case Linf:{
         //Compare using Linf only the features objects that both have
         // Linf = max |Ai - Bi|

         //for every feature object
         for(i=0; i < obj1->GetNF(); i++){
            if( (obj1->GetFeature(i) != NULL) && (obj2->GetFeature(i) != NULL)){
               if( obj1->GetFeature(i)->GetTag() == obj2->GetFeature(i)->GetTag()){
                  for(j=0; j < (int)obj1->GetFeature(i)->GetSize(); j++){
                     temp = fabs(obj1->GetFeature(i)->Get(j) - obj2->GetFeature(i)->Get(j));
                     distance = (temp > distance) ? temp : distance;
                  }//end for
               }// end if tag == tag
            }//end if both are not null
         }//end for
      }
   };

   return distance;
}


