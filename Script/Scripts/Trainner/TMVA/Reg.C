#include <cstdlib>
#include <iostream> 
#include <map>
#include <string>
#include <fstream>
#include <sstream>
#include "TChain.h"
#include "TFile.h"
#include "TTree.h"
#include "TString.h"
#include "TObjString.h"
#include "TSystem.h"
#include "TROOT.h"

#include "TMVA/GeneticAlgorithm.h"
#include "TMVA/GeneticFitter.h"
#include "TMVA/IFitterTarget.h"
//#include "TMVA/TMVARegGui.h"
//#include "TMVARegGui.C"
#include "TMVA/Tools.h"
#include "TMVA/Factory.h"
//#include "TMVA/DataLoader.h"
using namespace TMVA;


void Reg(){
  
  TMVA::Tools::Instance();
  std::cout << "==> Start TMVARegression" << std::endl;
    
  //ifstream myfile(); 
  //  ifstream myfile("99per_flat.txt"); 
  //      ifstream myfile("Loose_fixed_sigmaa0.117_50equal.txt"); 
  //    ifstream myfile("99per_updated1.txt"); 
      ifstream myfile("99per_bar.txt");
  //myfile.open("/nfs_scratch/sacharya/monophoton/CMSSW_10_6_20/src/PhotonIDs/merged/ALLPV/Trainner/bar/bar1/99per1.txt");
  //  myfile.open("99per1.txt");



  ostringstream xcS,xcH,xcP,xcC,xcN;  
  // double xcS,xcH,xcP,xcC,xcN;  
  //   ostringstream xcsf,xchf,xccf,xcnf,xcpf;  
  //double xS,xC,xN,xP;
    double xS,xH,xC,xN,xP;
 
  if(myfile.is_open()){
    while(!myfile.eof()){
            myfile>>xS>>xH>>xC>>xN>>xP;
	    //myfile>>xS>>xC>>xN>>xP;
    

      //       cout<<xS<<" "<<xC<<" "<<xN<<" " <<xP<<endl; 
    }
  }

  //  cout<<xcS<<" "<<xcH<<" "<<xcC<<" "<<xcN<<" "<<xcP<<endl;
  

  //xcS<<xS;
  xcS<<xS;
  xcH<<xH;
  xcC<<xC;
  xcN<<xN;
  xcP<<xP;
  
    cout<< xS<< " "<< xH<< " " << xC<< " "<< xN<< " " <<xP<< endl; 
    //cout<< xS<< " " << xC<< " "<< xN<< " " <<xP<< endl; 

  //Output file 
  //     TString outfileName( "Loose_w_BAR_scaled_60_40.root" )
   TString outfileName ("Loose_w_BAR_scaled_TruePV.root");
  //    TString outfileName ("Loose_w_BAR_scaled_fixedsigmaa0.0117_50.root");
// TString outfileName( "Loose_w_BAR_scaled_90_10.root" );
  //    TString outfileName( "Loose_w_BAR_scaled_default_90_10_new_factory.root" );
  //     TString outfileName( "Loose_w_BAR_scaled_default_updated_90_10_new_factory.root" );
  //TString outfileName( "Loose_w_BAR_scaled_default_updated_800_50_factory.root" );
  //TString outfileName( "Loose_w_BAR_scaled_90_10.root" );
  //TString outfileName( "Loose_w_BAR_scaled_90_10.root" );
  //   TString outfileName( "Loose_w_BAR_scaled_dataloader_70.root" );
  TFile* outputFile = TFile::Open( outfileName, "RECREATE" );
  //Declaring the factory
  //     TMVA::Factory *factory = new TMVA::Factory( "TMVAClassification", outputFile,      "!V:!Silent:Color:DrawProgressBar" );
       TMVA::Factory *factory = new TMVA::Factory( "TMVAClassification_TruePV", outputFile,      "!V:!Silent:Color:DrawProgressBar" );
       // TMVA::Factory *factory = new TMVA::Factory( "TMVAClassification_fixedsigmaa0.117_50", outputFile,      "!V:!Silent:Color:DrawProgressBar" );
 

  //  TMVA::Factory *factory = new TMVA::Factory( "TMVAClassification_90_10", outputFile, "!V:!Silent:Color:DrawProgressBar" );
  //TMVA::Factory *factory = new TMVA::Factory( "TMVAClassification_90_10", outputFile, "!V:!Silent:Color:DrawProgressBar" );

    //declaring dataloader new way
     //      TMVA::DataLoader *loader = new TMVA::DataLoader("dataset");
  //declaring dataloader variables
  //Declaring Input Variables                                                    
     /*  loader->AddVariable( "Sieie","Sieie",'F');
  //loader->AddVariable( "Sieie",'F',"Sieie");
  loader->AddVariable( "ToE","ToE",'F' );  
  loader->AddVariable( "(isoC-(0.0121*Ppt+0.00001335*Ppt*Ppt) > 0 ) ? isoC-(0.0121*Ppt+0.00001335*Ppt*Ppt) : 0.0 ","isoC",'F');
  loader->AddVariable( "isoN","isoN",'F' );
  //loader->AddVariable( "(isoP-0.003232*Ppt > 0 ) ? isoP-(0.003232*Ppt) : 0.0 ","isoP",'F');
  loader->AddVariable( "(isoP-0.002948*Ppt > 0 ) ? isoP-(0.002948*Ppt) : 0.0 ","isoP",'F');
     */



   //Declaring Input Variables 
        factory->AddVariable( "Sieie",'F');
	factory->AddVariable( "ToE",'F' );
  //  factory->AddVariable( "(isoC-(0.008556*Ppt+0.00001259*Ppt*Ppt) > 0 ) ? isoC-(0.008556*Ppt+0.00001259*Ppt*Ppt) : 0.0 ",'F' );
       //  factory->AddVariable( "(isoC-(0.0116*Ppt+0.0000136*Ppt*Ppt) > 0 ) ? isoC-(0.0116*Ppt+0.0000136*Ppt*Ppt) : 0.0 ",'F' );
  //  factory->AddVariable( "(isoN-(0.001219*Ppt+0.00000000000001164*Ppt*Ppt) > 0 ) ? isoN-(0.001219*Ppt+0.00000000000001164*Ppt*Ppt) : 0.0 ",'F' );
  //  factory->AddVariable( "(isoN-(0.001219*Ppt+0.00000000000001164*Ppt*Ppt)>0 ) ? isoN-((0.001219*Ppt-0.00000000000001164*Ppt*Ppt) :0.0",'F');
  //  factory->AddVariable( "(isoP-0.00289*Ppt > 0 ) ? isoP-0.00289*Ppt : 0.0 ",'F' );
       // factory->AddVariable( "isoN",'F' );
       //factory->AddVariable( "(isoP-0.003001*Ppt > 0 ) ? isoP-0.003001*Ppt : 0.0 ",'F' );
       factory->AddVariable( "isoC",'F' );
       factory->AddVariable( "(isoN-(9.73714e-03*Ppt+1.01605e-05*Ppt*Ppt) > 0 ) ? isoN-(9.73714e-03*Ppt+1.01605e-05*Ppt*Ppt) : 0.0 ",'F' );
       factory->AddVariable( "(isoP-2.99336e-03*Ppt > 0 ) ? isoP-2.99336e-03*Ppt : 0.0 ",'F' );

   factory->AddSpectator( "Ppt",'F' );
   //   factory->AddSpectator( "ToE",'F');  
  //
  
  // loader->AddSpectator( "Ppt",'F' );
  
  //TString fname = "../../CutTMVABarrel90.root";
  //       TString fname = "/nfs_scratch/sacharya/monophoton/CMSSW_10_6_20/src/PhotonIDs/merged/ALLPV/Trainner/CutTMVABarrel90_test.root";
  TFile *input(0);  


  //       TString fname = "/nfs_scratch/sacharya/monophoton/CMSSW_10_6_20/src/PhotonIDs/merged/ALLPV/Isopt/CutTMVABarrel90update25May_HPT.root";
  //    TString fname = "/nfs_scratch/sacharya/monophoton/CMSSW_10_6_20/src/PhotonIDs/merged/ALLPV/Trainner/CutTMVABarrel90_update_test.root";
  // TString fname = "/nfs_scratch/sacharya/UL_studies/CMSSW_10_6_20/src/Photon_ID_2018/Trainner/CutTMVABarrelTrainnerUL.root";
  TString fname = "../CutTMVABarrelTrainner_TruePV_1_60.root";

     //  	TString fname ="CutTMVABarrel90_test.root";
  //   		TString fname ="CutTMVABarrel90update25May_HPT.root";
//   		TString fname ="CutTMVABarrel90_update_test.root";

  input = TFile::Open( fname );
  
  // --- Register the regression tree
  TTree *signal = (TTree*)input->Get("t_S");
  TTree *background = (TTree*)input->Get("t_B");
  signal->ls();
  //Just Some more settings
  Double_t signalWeight      = 1.0; 
  Double_t backgroundWeight  = 1.0; 


  // You can add an arbitrary number of regression trees
  factory->AddSignalTree( signal, signalWeight );
  //loader->AddSignalTree( signal, signalWeight );
   factory->AddBackgroundTree( background , backgroundWeight );
   //   loader->AddBackgroundTree( background , backgroundWeight );
   //            Double_t Sieie =0.01165; 
  TCut mycuts =" Ppt > 200 ";
  TCut mycutb =" Ppt > 200 ";
  //   TCut mycutb ="Ppt>15   && Ppt < 200 && ToE < 0.05";
  //factory->PrepareTrainingAndTestTree(mycuts,mycutb,""); 
  //  loader->PrepareTrainingAndTestTree(mycuts,mycutb,"nTrain_Signal=31581:nTrain_Background=4598:nTest_Signal=31581:nTest_Background=4597");  //Ul values 
  //loader->PrepareTrainingAndTestTree(mycuts,mycutb,"nTrain_Signal=44213:nTrain_Background=6436:nTest_Signal=18949:nTest_Background=2759");  //Ul values 70-30 
  //  factory->PrepareTrainingAndTestTree(mycuts,mycutb,"nTrain_Signal=31923:nTrain_Background=4875:nTest_Signal=31922:nTest_Background=4875");  //Ul values    //ALL PV
  //    factory->PrepareTrainingAndTestTree(mycuts,mycutb,"nTrain_Signal=31210:nTrain_Background=4666:nTest_Signal=31209:nTest_Background=4666");  //Ul values True PV
  //    factory->PrepareTrainingAndTestTree(mycuts,mycutb,"nTrain_Signal=43694:nTrain_Background=6533:nTest_Signal=18725:nTest_Background=2799");  //Ul 70 % tRUE pv
  factory->SetBackgroundWeightExpression("weighT");
  // loader->SetBackgroundWeightExpression("weighT");
       factory->SetSignalWeightExpression("weighT");
       //loader->SetSignalWeightExpression("weighT");

  TString methodName = "Cut_Loose_r";
    TString methodOptions ="!H:!V:FitMethod=GA:EffMethod=EffSEl:PopSize=600:Steps=50"; 

  //TString methodOptions ="!H:!V:FitMethod=GA:EffMethod=EffSEl"; 


  /* TString methodOptions ="!H:!V:FitMethod=GA:EffMethod=EffSEl:PopSize=400:SC_steps=10:SC_rate=5:SC_factor=0.95:Cycles=4:Steps=50:ConvCrit=0.005:SaveBestCycle=2"; 

  //TString methodOptions ="!H:!V:FitMethod=GA:EffMethod=EffSEl:PopSize=700:SC_steps=20:SC_rate=5:SC_factor=0.95:Cycles=4:Steps=50:ConvCrit=0.050:SaveBestCycle=2"; //better step for 10000
//TString methodOptions ="!H:!V:FitMethod=GA:EffMethod=EffSEl:PopSize=700:SC_steps=20:SC_rate=5:SC_factor=0.95:Cycles=4:Steps=50:ConvCrit=0.0100:SaveBestCycle=2:SaveBestGen=2";  //better step for 15000
//TString methodOptions ="!H:!V:FitMethod=GA:EffMethod=EffSEl:PopSize=500:SC_steps=20:SC_rate=5:SC_factor=0.95:Cycles=4:Steps=50:ConvCrit=0.0060:SaveBestCycle=2:SaveBestGen=2"; //better for 25000
//TString methodOptions ="!H:!V:FitMethod=GA:EffMethod=EffSEl"; 

   methodOptions +=":VarProp[0]=FMin:VarProp[1]=FMin:VarProp[2]=FMin:VarProp[3]=FMin";
  */
  methodOptions +=":VarProp[0]=FMin:VarProp[1]=FMin:VarProp[2]=FMin:VarProp[3]=FMin:VarProp[4]=FMin";
  // methodOptions +=":VarProp[0]=FMin:VarProp[1]=FMin:VarProp[2]=FMin:VarProp[3]=FMin";
  //  methodOptions +=":VarProp[0]=FSmart:VarProp[1]=FSmart:VarProp[2]=FSmart:VarProp[3]=FSmart:VarProp[4]=FSmart";
   

   //commenting this in april  
   methodOptions +=":CutRangeMax[0]="+xcS.str(); 
    methodOptions +=":CutRangeMax[1]="+xcH.str();   
    methodOptions +=":CutRangeMax[2]="+xcC.str();
    methodOptions +=":CutRangeMax[3]="+xcN.str();
    methodOptions +=":CutRangeMax[4]="+xcP.str();
    
//added this line 
// methodOptions +=":CutRangeMax[0]="+xcS.str();                             
    /*methodOptions +=":CutRangeMax[0]="+xcS.str();                               
 methodOptions +=":CutRangeMax[1]="+xcC.str();                               
 methodOptions +=":CutRangeMax[2]="+xcN.str();                               
 methodOptions +=":CutRangeMax[3]="+xcP.str();  
    */
/*
// doing it for BDT
TString methodOptions ="!H:!V:NTrees=400:nEventsMin=400:MaxDepth=3:BoostType=AdaBoost:SeparationType=GiniIndex:nCuts=20:PruneMethod=NoPruning";
*/

   //************
    //    factory->BookMethod(loader,TMVA::Types::kCuts,methodName,methodOptions);
           factory->BookMethod(TMVA::Types::kCuts,methodName,methodOptions);
 //factory->BookMethod(loader,TMVA::Types::kBDT,methodName,methodOptions);   
    factory->TrainAllMethods();
   factory->TestAllMethods();
   factory->EvaluateAllMethods();    
   
   // --------------------------------------------------------------
   // Save the output
   outputFile->Close();



   std::cout << "==> Wrote root file: " << outputFile->GetName() << std::endl;
   std::cout << "==> TMVARegression is done!" << std::endl;      
   delete factory;

}
