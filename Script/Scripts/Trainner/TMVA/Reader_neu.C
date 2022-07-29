#include <cstdlib>
#include <vector>
#include <iostream>
#include <map>
#include <string>
#include "TH2.h"
#include "TRandom.h"
#include "TFile.h"
#include "TTree.h"
#include "TString.h"
#include "TSystem.h"
#include "TROOT.h"
#include "TStopwatch.h"
#include "TChain.h"
#include "TFile.h"
#include "TTree.h"
#include "TString.h"
#include "TObjString.h"
#include "TSystem.h"
#include "TROOT.h"
#include "TMVA/Tools.h"
#include "TMVA/Factory.h"
#include "TFile.h"
#include "TTree.h"
#include "TH2D.h"
#include "TString.h"
#include "TSystem.h"
#include "TROOT.h"
#include "TStopwatch.h"
#include "TMVA/Tools.h"
#include "TMVA/Reader.h"

using namespace TMVA;

void Reader_neu(){
  
  TMVA::Tools::Instance();  
  
  //ofstream myfileM; 
  //myfileM.open("MediumR.txt");
  
    ofstream myfileL; 
    // myfileM.open("Medium_default_flatpt_factory.txt");
    //  myfileL.open("very_Loose_neu_.txt");
    //  myfileL.open("Loose_neu_.txt");
    //    myfileL.open("Medium_neu_.txt");
    myfileL.open("Medium.txt");
  



  //Declaring the reader  
  //  TString methodName = "Cut_Tight_r";
  //TString weightfile = "./weights/TMVAClassification_default_updated_factory__Cut_Tight_r.weights.xml";

      TString methodName = "Cut_Medium_r";
  TString weightfile = "./weights/TMVAClassification_TruePV_Cut_Medium_r.weights.xml";

    //     TString methodName = "Cut_Loose_r";
      //  TString weightfile =  "./weights/TMVAClassification_TruePV_Cut_Loose_r.weights.xml";
  //TString weightfile = "./weights/TMVAClassification_default_factory_Cut_Loose_r.weights.xml";
  // TString weightfile = "./weights/TMVAClassification_flat_default_factory_Cut_Loose_r.weights.xml";
 //TString weightfile = "./weights/TMVAClassification_flat_default__Cut_Medium_r.weights.xml"; 
  //  TString weightfile = "/TMVAClassification_Cut_Loose_r.weights.xml";

  
  //// WARNING !!!!!!!!!!!!!!!!!! THE TIGHT SIGNAL EFF MUST BE CHANGED TO 70 %   

  
  TMVA::Reader *reader = new TMVA::Reader( "!Color" );
   
  float Sieie,ToE,isoC,isoN,isoP,pt;
      reader->AddVariable("Sieie",&Sieie);
      reader->AddVariable("ToE",&ToE);
//  reader->AddVariable( "(isoC-(0.008556*Ppt+0.00001259*Ppt*Ppt) > 0 ) ? isoC-(0.008556*Ppt+0.00001259*Ppt*Ppt) : 0.0 ",&isoC);
      reader->AddVariable( "isoC",&isoC );
  reader->AddVariable( "(isoN-(9.73714e-03*Ppt+ 1.01605e-05 *Ppt*Ppt) > 0 ) ? isoN-(9.73714e-03*Ppt+ 1.01605e-05 *Ppt*Ppt) : 0.0 ",&isoN);

  //    reader->AddVariable( "(isoN-(0.001219*Ppt+0.00000000000001164*Ppt*Ppt) > 0)  ? isoN-(0.001219*Ppt+0.00000000000001164*Ppt*Ppt) : 0.0 ",&isoN ); 
 reader->AddVariable( "(isoP-2.99336e-03*Ppt > 0 ) ? isoP-2.99336e-03*Ppt : 0.0 ",&isoP);
 //  reader->AddVariable("ToE",&ToE); 

  //reader->AddVariable( "(isoN-(0.014*Ppt+0.000019*Ppt*Ppt) > 0 )? isoN-(0.014*Ppt+0.000019*Ppt*Ppt): 0.0 ",&isoN);
  //reader->AddVariable( "(isoP-0.0053*Ppt > 0 ) ? isoP-0.0053*Ppt : 0.0 ",&isoP);

  

  reader->AddSpectator("Ppt",&pt);
  // reader->AddSpectator("ToE",&ToE);
  reader->BookMVA(methodName,weightfile); 


  TMVA::MethodCuts* mcuts = dynamic_cast<TMVA::MethodCuts*>(reader->FindCutsMVA(methodName) );
  std::vector<Double_t> cutsMin;
  std::vector<Double_t> cutsMax;
 
  
          double SEF =  0.80;   
  //          double SEF =  0.91;   
  //    //very loose   
  //    double SEF =  0.89;   //loose   
  //      double SEF =  0.82;   //Medium   
  //    double SEF =  0.73;   //Tight   
  if(mcuts)mcuts->GetCuts(SEF, cutsMin, cutsMax ); 
  myfileL<<" "<<cutsMax[0]<<" "<<cutsMax[1]<<" "<<cutsMax[2]<<" "<<cutsMax[3]<<" "<<cutsMax[4]<<" "<<endl;  
  //myfileL<<" "<<cutsMax[0]<<" "<<cutsMax[1]<<" "<<cutsMax[2]<<" "<<cutsMax[3]<<endl;  
  
 
  
  /*     double SEF =  0.81;   
  if(mcuts)mcuts->GetCuts(SEF, cutsMin, cutsMax ); 
  myfileL<<" "<<cutsMax[0]<<" "<<cutsMax[1]<<" "<<cutsMax[2]<<" "<<cutsMax[3]<<" "<<cutsMax[4]<<endl;  
  */


  
  /*    double SEF =  0.69;   
  if(mcuts)mcuts->GetCuts(SEF, cutsMin, cutsMax ); 
  myfileL<<" "<<cutsMax[0]<<" "<<cutsMax[1]<<" "<<cutsMax[2]<<" "<<cutsMax[3]<<" "<<cutsMax[4]<<" "<<endl;  
  */
  delete reader;



   myfileL.close(); 
  //  myfileM.close(); 
   // myfileT.close(); 
  cout<<"DONE READING CUTS"<<endl;
  
}
