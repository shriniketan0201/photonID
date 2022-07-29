#include <cstdlib>
#include <iostream> 
#include <map>
#include <string>
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
#include "TMVA/Tools.h"
#include "TMVA/Factory.h"
#include <sstream>
#include <string.h>

void Calculator_ef(){

    ifstream tight; 
  ifstream medium; 
  ifstream loose; 
  ofstream outp; 

  //   tight.open("Tight_default_factory_updat_80.txt");
  //   tight.open("../../end/Loose_T_neu_.txt");
  medium.open("../Medium.txt");
   //  medium.open("Medium_default_factory_updat_80.txt");
  //loose.open("LooseR_default_flatpt_factory.txt");
  loose.open("../Loose.txt");
  outp.open("efBk.txt");
  //outp.open("efBk_default_flatpt_factory.txt");

  double efL,efM,efT,bkL,bkM,bkT; 
  double IsoPcutL,IsoPcutM,IsoPcutT,IsoCcutL,IsoCcutM,IsoCcutT,IsoNcutL,IsoNcutM,IsoNcutT,SieiecutL,SieiecutM,SieiecutT,HoEcutL,HoEcutM,HoEcutT;
  
  /*  if(tight.is_open()){
    while(!tight.eof()){
      
      tight>>SieiecutT>>IsoCcutT>>IsoNcutT>>IsoPcutT;
      break;
    }
  }
  */
  if(medium.is_open()){
    while(!medium.eof()){
      
      medium>>SieiecutM>>HoEcutM>>IsoCcutM>>IsoNcutM>>IsoPcutM;
      break;

    }
  }


    
  if(loose.is_open()){
    while(!loose.eof()){
      
      loose>>SieiecutL>>HoEcutL>>IsoCcutL>>IsoNcutL>>IsoPcutL;
      break;

    }
  }
  
  /*  HoEcutL = 0.05; 
  HoEcutM = 0.05; 
  HoEcutT = 0.05; 
  */
  //Input file:
  TFile *input(0);
  //  TString fname = "../../../../fabrice_task/PV/PFIso/train/CutTMVABarrel90.root";
  //  TString fname = "/nfs_scratch/sacharya/UL_studies/CMSSW_10_6_20/src/Photon_ID_2018/Trainner/CutTMVABarrelTrainnerUL1to30.root";
    TString fname = "../../CutTMVABarrelTrainner_TruePV_1_60.root";
  input = TFile::Open( fname );
  


  TTree *t_S = (TTree*)input->Get("t_S");
  TTree *t_B = (TTree*)input->Get("t_B");
  // --- Register the regression tree
  float Sie_ie,iso_P,iso_C,iso_N,to_e,weightXS,weighT;
  float Ppt; 
  int Pix;

  //Signal Tree
  t_S->SetBranchAddress("Sieie",&Sie_ie);
  t_S->SetBranchAddress("isoP",&iso_P);
  t_S->SetBranchAddress("isoC",&iso_C);
  t_S->SetBranchAddress("isoN",&iso_N);
  t_S->SetBranchAddress("ToE",&to_e);
  t_S->SetBranchAddress("weighT",&weighT);
  t_S->SetBranchAddress("Pix",&Pix);
  t_S->SetBranchAddress("Ppt",&Ppt);

  //Background Tree
  t_B->SetBranchAddress("Sieie",&Sie_ie);
  t_B->SetBranchAddress("isoP",&iso_P);
  t_B->SetBranchAddress("isoC",&iso_C);
  t_B->SetBranchAddress("isoN",&iso_N);
  t_B->SetBranchAddress("ToE",&to_e);  
 
  t_B->SetBranchAddress("weighT",&weighT);
  t_B->SetBranchAddress("Pix",&Pix);
  t_B->SetBranchAddress("Ppt",&Ppt);




  double LoosSEf = 0; 
  double TightSEf = 0; 
  double MediumSEf = 0; 

  
  double LoosBckR = 0; 
  double TightBckR = 0; 
  double MediumBckR = 0; 

  
  double totS = 0; 
 
  for(int i  = 0 ; i < t_S->GetEntries(); i++){
 
   t_S->GetEntry(i);
    //    if(Pix == 1)continue;
    if(Ppt < 200 ) continue;
    //    if(to_e >  0.05) continue;
    totS = totS+ weighT; 

    //    double slopeP = 0.003347; 
        double slopeP =2.99336e-03;   //barrel 
    //    double slopeP =1.95851e-03;   //Endcap

      double slopeN=(9.73714e-03*Ppt+ 1.01605e-05 *Ppt*Ppt); //Barrel
	//    double slopeN=(7.54298e-03*Ppt+1.61508e-05*Ppt*Ppt); //Endcap

    //cout<<"iso_N "<<iso_N<<endl;
    //    cout<<"to_e "<<to_e<<endl;
    //    cout<<"Sie_ie "<<Sie_ie<<endl;
    //Calculating the Efficiencies for the Loose Set of Cuts 
	//    if((iso_P < (IsoPcutL + slopeP*Ppt))&&(iso_N < IsoNcutL +slopeN)&&(iso_C < (IsoCcutL + slopeC))&&(to_e<HoEcutL)&&(Sie_ie < SieiecutL )) {	
	// if((iso_P < (IsoPcutL + slopeP*Ppt))&&(iso_N < IsoNcutL )&&(iso_C < (IsoCcutL + slopeC))&&(to_e<HoEcutL)&&(Sie_ie < SieiecutL )) {	
    //    if((iso_P < (IsoPcutL + slopeP*Ppt))&&(iso_C < (IsoCcutL + slopeC))) {	
   if((iso_P < IsoPcutL + slopeP*Ppt)&&(iso_N < IsoNcutL  + slopeN)&&(iso_C < IsoCcutL)&&(to_e<HoEcutL)&&(Sie_ie < SieiecutL )){
      LoosSEf = LoosSEf + weighT;
      //	     cout<<"LoosSEf "<<LoosSEf<<endl;
      }
        

    
    
 //    if((iso_P < (IsoPcutM + slopeP*Ppt))&&(iso_N < IsoNcutM  +slopeN )&&(iso_C < (IsoCcutM + slopeC))&&(to_e<HoEcutM)&&(Sie_ie < SieiecutM )){
   //    if((iso_P < (IsoPcutM + slopeP*Ppt))&&(iso_N < IsoNcutM  )&&(iso_C < (IsoCcutM + slopeC))&&(to_e<HoEcutM)&&(Sie_ie < SieiecutM )){
    //    if((iso_P < (IsoPcutM + slopeP*Ppt))&&(iso_C < (IsoCcutM + slopeC))){
   if((iso_P < IsoPcutM +slopeP*Ppt)&&(iso_N < IsoNcutM +slopeN)&&(iso_C < IsoCcutM)&&(to_e<HoEcutM)&&(Sie_ie < SieiecutM )){
    MediumSEf = MediumSEf + weighT;
  }
    
    //    if((iso_P < IsoPcutT + slopeP*Ppt)&&(iso_N < IsoNcutT +slopeN)&&(iso_C < IsoCcutT + slopeC)&&(to_e<HoEcutT)&&(Sie_ie < SieiecutT ) ){
    //if((iso_P < IsoPcutT + slopeP*Ppt)&&(iso_N < IsoNcutT )&&(iso_C < IsoCcutT + slopeC)&&(to_e<HoEcutT)&&(Sie_ie < SieiecutT ) ){
   /* if((iso_P < IsoPcutT +slopeP*Ppt)&&(iso_N < IsoNcutT + slopeN)&&(iso_C < IsoCcutT)&&(to_e<HoEcutT)&&(Sie_ie < SieiecutT ) ){
    TightSEf = TightSEf + weighT;
  }
   */
    //cout<<"slopeSP"<<slopeP<<"slopeSC"<<slopeC<<endl;
}

double totB = 0; 
for(int i  = 0 ; i < t_B->GetEntries(); i++){
  t_B->GetEntry(i);

  if(Ppt < 200 ) continue;
  //    if(to_e > 0.05) continue;

  totB = totB+ weighT; 
   
  //  double slopeP = 0.0046; 
  //double slopeN = ((0.0143*Ppt+0.000017*Ppt*Ppt));///Ppt; 
  //double slopeP = 0.0053; 
  //double slopeN = ((0.014*Ppt+0.000019*Ppt*Ppt));///Ppt; 

  /*  double slopeP = 0.003001;
  double slopeC = ((0.0116*Ppt+0.0000136*Ppt*Ppt));
  */
  //  double slopeP = 0.002995;
  //  //    double slopeC = ((0.01253*Ppt+0.00001237*Ppt*Ppt));///Ppt;                                                                                                     
  //  double slopeC = ((0.01171*Ppt+0.00001396*Ppt*Ppt));///Ppt;

  //  double slopeN=(0.001219*Ppt+0.00000000000001164*Ppt*Ppt);

    double slopeP =2.99336e-03;
  double slopeN=(9.73714e-03*Ppt+ 1.01605e-05 *Ppt*Ppt);
  
  //      double slopeP =1.95851e-03;   //Endcap
  //  double slopeN=(7.54298e-03*Ppt+1.61508e-05*Ppt*Ppt); //Endcap

    if((iso_P < (IsoPcutL +Ppt*slopeP) )&&(iso_N < IsoNcutL +slopeN)&&(iso_C < (IsoCcutL))&&(to_e<HoEcutL)&&(Sie_ie < SieiecutL )){
  //if((iso_P < (IsoPcutL +Ppt*slopeP) )&&(iso_N < IsoNcutL )&&(iso_C < (IsoCcutL +slopeC))&&(to_e<HoEcutL)&&(Sie_ie < SieiecutL )){
  //  if((iso_P <( IsoPcutL + slopeP*Ppt))&&(iso_C < (IsoCcutL + slopeC))) {	  
  LoosBckR = LoosBckR + weighT;
  }
    
    if((iso_P < (IsoPcutM +slopeP*Ppt))&&(iso_N < IsoNcutM+slopeN)&&(iso_C < (IsoCcutM ))&&(to_e<HoEcutM)&&(Sie_ie < SieiecutM )){
    //  if((iso_P < (IsoPcutM +slopeP*Ppt))&&(iso_N < IsoNcutM)&&(iso_C < (IsoCcutM +slopeC))&&(to_e<HoEcutM)&&(Sie_ie < SieiecutM )){
  // if((iso_P < (IsoPcutM + slopeP*Ppt))&&(iso_C < (IsoCcutM + slopeC))){
      MediumBckR = MediumBckR + weighT;
  }
    
  //    if((iso_P < IsoPcutT +  Ppt*slopeP)&&(iso_N < IsoNcutT+slopeN)&&(iso_C < IsoCcutT +slopeC)&&(to_e<HoEcutT)&&(Sie_ie < SieiecutT )){
    /*  if((iso_P < IsoPcutT +  Ppt*slopeP)&&(iso_N < IsoNcutT)&&(iso_C < IsoCcutT )&&(to_e<HoEcutT)&&(Sie_ie < SieiecutT )){
    TightBckR = TightBckR + weighT;
    }*/
  
  //   cout<<"slopeBP"<<slopeP<<"slopeBC"<<slopeC<<endl;
  // cout<<"slopeBP "<<slopeP<<"slopeBN"<<slopeN<<endl;
 }// Eoff Back ground tree for Sig Back 





//outp<<LoosSEf/totS<<" "<<1 - LoosBckR/totB<<" "<<MediumSEf/totS<<" "<<1 - MediumBckR/totB<<" "<<TightSEf/totS<<" "<<1 - TightBckR/totB;
 outp<<LoosSEf/totS<<" "<<1 - (LoosBckR/totB)<<" "<<MediumSEf/totS<<" "<<1 - (MediumBckR/totB);




}
