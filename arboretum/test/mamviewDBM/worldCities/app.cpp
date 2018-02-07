//---------------------------------------------------------------------------
#include <fstream>
using namespace std;                                                          

#include "app.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

//---------------------------------------------------------------------------
void tApp::Init(int pageSize, char * abreviation,
                int factor, char * dataPath){

   this->PageMan = new stDiskPageManager("cities.dat", pageSize);
   this->MyTree = new myDBMTree(this->PageMan);

   this->MyTree->SetSplitMethod(myDBMTree::smMIN_MAX);
   this->MyTree->SetChooseMethod(myDBMTree::cmMINDIST);
   this->MyTree->SetMinOccupation(0.25);
   this->MyTree->SetReInsert(true);
   this->MyTree->SetRemoveFarthest(false); /**/

   LoadTree(abreviation, factor, dataPath); // Make it ready to use.
   //LoadTree2(dataPath); // Make it ready to use.

   cout << "\n" << this->MyTree->Consistency();
   this->MyTree->DeleteUniqueNodes();
   cout << "\n" << this->MyTree->Consistency();
   this->MyTree->Optimize();
   cout << "\n" << this->MyTree->Consistency();
   this->MyTree->DeleteUniqueNodes();
   cout << "\n" << this->MyTree->Consistency(); /**/
}//end tApp::Init

//---------------------------------------------------------------------------
void tApp::Run(){
   TCity * city[6];
   myResult * r;
   stTreeInfoResult * treeInfo;

   MyTree->MAMViewInit();

   MyTree->MAMViewSetOutputDir(".");

   city[0] = new TCity("Pittsburgh city-PA", 40.4414, -79.9773);
   city[1] = new TCity("Washington city-DC", 38.9136,	-77.0132);
   city[2] = new TCity("Palm City CDP-FL", 27.1711, -80.2787);
   city[3] = new TCity("Seattle city-WA", 47.6264, -122.333);
   city[4] = new TCity("Sacramento city-CA", 38.5556, -121.469);
   city[5] = new TCity("Honolulu CDP-HI", 21.3089, -157.826);

   r = MyTree->RangeQuery(city[0], 0.6);
   delete r;
   r = MyTree->RangeQuery(city[1], 1.0);
   delete r;
   r = MyTree->RangeQuery(city[2], 0.4);
   delete r;
   r = MyTree->RangeQuery(city[3], 0.5);
   delete r;
   r = MyTree->RangeQuery(city[4], 1.2);
   delete r;
   r = MyTree->RangeQuery(city[5], 0.8);
   delete r;

   r = MyTree->NearestQuery(city[0], 10);
   delete r;
   r = MyTree->NearestQuery(city[1], 15);
   delete r;
   r = MyTree->NearestQuery(city[2], 20);
   delete r;
   r = MyTree->NearestQuery(city[3], 7);
   delete r;
   r = MyTree->NearestQuery(city[4], 8);
   delete r;
   r = MyTree->NearestQuery(city[5], 9);
   delete r;
/**/
   MyTree->MAMViewDumpTree();

   delete[] city; /**/
}//end tApp::Run

//---------------------------------------------------------------------------
void tApp::Done(){

   delete this->MyTree;
   delete this->PageMan;
}//end tApp::Done

//---------------------------------------------------------------------------
bool tApp::LoadTree(char * abreviation, int factor, char * dataPath){
   ifstream in(dataPath);
   char cityNameAccent[200], cityName[200], lixo[200], country[50];
   char cityNameOLD[200];
   long sizeAll, w;
   bool all;
   double dLat, dLong, dLatOld, dLongOld;
   TCity * city;

   // format of the file
   // Country - City - Accent City - Region - Latitude - Longitude
   w = 0;
   all = !strcmp(abreviation, "ALL");
   cityNameOLD[0] = '\0';
   dLatOld = 0;
   dLongOld = 0;
   if (in.is_open()){
      cout << "Loading objects...";
      // forget the first line
      in.getline(lixo, 200, '\n');
      // try to get the others.
      while(in.getline(country, 200, '\t')){
         in.getline(cityName, 200, '\t');
         in.getline(cityNameAccent, 200, '\t');
         in.getline(lixo, 200, '\t');
         in >> dLat;
         in >> dLong;
         in.ignore();
         strcat(cityNameAccent, "-\0");
         strcat(cityNameAccent, country);
         if ((!strcmp(country, abreviation)) || (all)){
            if ((strcmp(cityName, cityNameOLD)) && (dLat!=dLatOld) && (dLong!=dLongOld)){
               if (!(w % factor)){
                  city = new TCity(cityNameAccent, dLat, dLong);
                  MyTree->Add(city);
                  delete city;
                  //cout << "\n[" << cityNameAccent << "," << dLat << "," << dLong << "]";
               }//end if
               strcpy(cityNameOLD, cityName);
               dLatOld = dLat;
               dLongOld = dLong;
            }//end if
            w++;
         }//end if
      }//end while
      cout << "\nAdded " << MyTree->GetNumberOfObjects() << " objects...\n";
      in.close();
      return true;
   }else{
      cout << "Problem to open the file.";
      return false;
   }//end if
}//end tApp::LoadTree

//---------------------------------------------------------------------------
bool tApp::LoadTree2(char * dataPath){
   ifstream in(dataPath);
   char cityName[200];
   long w;
   double dLat, dLong;
   TCity * city;

   w = 0;
   if (in.is_open()){
      cout << "Loading objects...";
      // try to get the others.
      while(in.get(cityName, 200, '\t')){
         in >> dLat;
         in >> dLong;
         in.ignore();
         city = new TCity(cityName, dLat, dLong);
         MyTree->Add(city);
         delete city;
         //cout << "\n[" << cityName << dLat << "," << dLong << "]";
         w++;
      }//end while
      cout << "\nAdded " << MyTree->GetNumberOfObjects() << " objects...\n";
      in.close();
      return true;
   }else{
      cout << "Problem to open the file.";
      return false;
   }//end if
}//end tApp::LoadTree2
