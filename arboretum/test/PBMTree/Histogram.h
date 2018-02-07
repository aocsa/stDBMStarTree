#include <graphics.hpp>
#include <arboretum/stBasicObjects.h>

typedef stBasicArrayObject<float> stArray;


//------------------------------------------------------------------------------
class THistogramExtractor{
   public:
      THistogramExtractor(){};
      ~THistogramExtractor(){};

     /**
     *  ExtractHistogram
     *    Calculate the metric histogram, returning them in
     *      an object of type stBasicArrayObject<float>, created in the process.
     *      The retured object does not belong to this class after the call.
     */
     static stArray* ExtractHistogram(Graphics::TBitmap *image);
}; //end class TMetrichistoExtractor
