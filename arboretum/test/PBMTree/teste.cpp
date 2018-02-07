//---------------------------------------------------------------------------
#pragma hdrstop

#include <iostream.h>

//My Multi Feature object
#include "MultiFeatureObject.h"


//---------------------------------------------------------------------------

#pragma argsused
int main(int argc, char* argv[])
{


/*
//Teste Histograma
   Graphics::TBitmap *image;
   stArray *feature;

   image = new Graphics::TBitmap;
   image->LoadFromFile("img\\1145.bmp");

   feature = THistogramExtractor::ExtractHistogram(image);

   for(int i=0; i < feature->GetSize(); i++)
      cout << FloatToStrF(feature->Get(i),ffFixed, 9,6) << " \n";

   cout << " \n";
   system("pause");

   delete image;
   delete feature;

   return 0;
/**/

/*
//Teste Textura - Entropia
   Graphics::TBitmap *image;
   stArray *feature;
   TTextureExtractorMCO * extractor;

   image = new Graphics::TBitmap;
   image->LoadFromFile("img\\1145.bmp");

   extractor = new TTextureExtractorMCO;
   extractor->BuildMCO(image);
   feature = extractor->GetEntropy();

   for(int i=0; i < feature->GetSize(); i++)
      cout << FloatToStrF(feature->Get(i),ffFixed, 9,6) << " \n";

   delete extractor;
   delete image;
   delete feature;
   system("pause");
   return 0;
/**/

/*
//Teste Textura - Homogen
   Graphics::TBitmap *image;
   stArray *feature;
   TTextureExtractorMCO * extractor;

   image = new Graphics::TBitmap;
   image->LoadFromFile("img\\1145.bmp");

   extractor = new TTextureExtractorMCO;
   extractor->BuildMCO(image);
   feature = extractor->GetHomogen();

   for(int i=0; i < feature->GetSize(); i++)
      cout << FloatToStrF(feature->Get(i),ffFixed, 9,6) << " \n";

   delete extractor;
   delete image;
   delete feature;
   system("pause");
   return 0;
/**/

/*
//Teste Multifeature
   Graphics::TBitmap *image, *image2;
   stArray *feature;
   TMultiFeature *multifeature, *multifeature2, *multifeature3, *multifeature4;
   TTextureExtractorMCO * extractorT;
   LPMetricEvaluator *evaluator;

   image = new Graphics::TBitmap;
   image->LoadFromFile("img\\1145.bmp");

   image2 = new Graphics::TBitmap;
   image2->LoadFromFile("img\\1149.bmp");

   multifeature = new TMultiFeature;
   multifeature2 = new TMultiFeature;
   multifeature3 = new TMultiFeature;
   multifeature4 = new TMultiFeature;

   //Associating metrics
   multifeature->SetMetric(LPMetricEvaluator::Linf);
   multifeature2->SetMetric(LPMetricEvaluator::L2);



   extractorT = new TTextureExtractorMCO;

   extractorT->BuildMCO(image);
   multifeature->SetFeature(0,THistogramExtractor::ExtractHistogram(image));
   multifeature->SetFeature(1,extractorT->GetEntropy());
//   multifeature->SetFeature(2,extractorT->GetHomogen());

   extractorT->BuildMCO(image2);
   multifeature2->SetFeature(0,THistogramExtractor::ExtractHistogram(image2));
//   multifeature2->SetFeature(1,extractorT->GetEntropy());
//   multifeature2->SetFeature(2,extractorT->GetHomogen());

   evaluator = new LPMetricEvaluator;

   cout << evaluator->GetDistance(multifeature, multifeature2) << "\n";

   multifeature3->Unserialize(multifeature->Serialize(), multifeature->GetSerializedSize());

   multifeature4 = multifeature3->Clone();

   cout << "is Equal?? = " << multifeature3->IsEqual(multifeature2) << "\n\n";

   for(int i=0; i < (int)multifeature4->GetFeature(1)->GetSize(); i++)
      cout << FloatToStrF(multifeature4->GetFeature(1)->Get(i),ffFixed, 9,6) << "\n ";// <<
//         FloatToStrF(multifeature2->GetFeature(0)->Get(i),ffFixed, 9,6) << " \n";


   delete multifeature;
   delete multifeature2;
   delete multifeature3;
   delete multifeature4;

   delete extractorT;
   delete evaluator;
   delete image;
   delete image2;
   system("pause");
   return 0;
/**/


//Teste Textura - Entropia Parametrizada
   Graphics::TBitmap *image;
   stArray *feature,*feature2;
   TTextureExtractorMCO * extractor;

   image = new Graphics::TBitmap;
   image->LoadFromFile("img\\1145.bmp");

   extractor = new TTextureExtractorMCO;
   extractor->BuildMCO(image);
   feature  = extractor->GetEntropy();
   feature2 = extractor->GetEntropy(3,3);

   for(int i=0; i < feature->GetSize(); i++)
      cout << FloatToStrF(feature->Get(i),ffFixed, 9,6) << " ";

   cout << " \n";

   for(int i=0; i < feature2->GetSize(); i++)
      cout << FloatToStrF(feature2->Get(i),ffFixed, 9,6) << " ";

   cout << " \n";

   delete extractor;
   delete image;
   delete feature;
   delete feature2;
   system("pause");
   return 0;
/**/


}
//---------------------------------------------------------------------------
