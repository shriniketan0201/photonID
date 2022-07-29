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
#include "TH1.h"
#include <sstream>
#include <string.h>

void PlotBuilder(){


  //Read the cuts: 


  ifstream tight;
  ifstream medium;
  ifstream loose;

  /*
  //  tight.open("Tight_default_factory_updat_isoN_90_10.txt");
  tight.open("../Tight_neu.txt");
  //medium.open("Medium_default_factory_updat_isoN_90_10.txt");
  medium.open("../Medium_neu.txt");
  //  loose.open("Loose_default_factory_updat_isoN_90_10.txt");
  loose.open("../Loose_neu.txt");

  */
  double isoCL,isoCM,isoCT;
  double isoPL,isoPM,isoPT;
  double isoNL,isoNM,isoNT;
  double sieL,sieM,sieT; 
  double hoeL,hoeM,hoeT;

  /* if(tight.is_open()){
    while(!tight.eof()){
      tight>>sieT>>hoeT>>isoCT>>isoNT>>isoPT;
      break;
    }
  }

  
  if(medium.is_open()){
    while(!medium.eof()){
      medium>>sieM>>hoeM>>isoCM>>isoNM>>isoPM;
      break;
    }
  }


  if(loose.is_open()){
    while(!loose.eof()){
      loose>>sieL>>hoeL>>isoCL>>isoNL>>isoPL;
      break;
    }
  }
  */
  //Read the Cuts. Now test them


  TH1F *EffNVTX0 = new TH1F("EffNVTX0","Signal Eff vs NVTX 0",100,0,100);
  TH1F *EffPT0   = new TH1F("EffPT0","Signal Eff vs PT 0",100,0,1000);
  TH1F *EffETA0  = new TH1F("EffETA0","Signal Eff vs Eta 0",100,-5,5);
  TH1F *EffPHI0  = new TH1F("EffPHI0","Signal Eff vs PHI 0",100,-4,4);

  TH1F *EffNVTXL = new TH1F("EffNVTXL","Signal Eff vs NVTX L",100,0,100);
  TH1F *EffPTL   = new TH1F("EffPTL","Signal Eff vs PT L",100,0,1000);
  TH1F *EffETAL  = new TH1F("EffETAL","Signal Eff vs Eta L",100,-5,5);
  TH1F *EffPHIL  = new TH1F("EffPHIL","Signal Eff vs PHI L",100,-4,4);
  
  TH1F *EffNVTXM = new TH1F("EffNVTXM","Signal Eff vs NVTX M",100,0,100);
  TH1F *EffPTM   = new TH1F("EffPTM","Signal Eff vs PT M",100,0,1000);
  TH1F *EffETAM  = new TH1F("EffETAM","Signal Eff vs Eta M",100,-5,5);
  TH1F *EffPHIM  = new TH1F("EffPHIM","Signal Eff vs PHI M",100,-4,4);

  TH1F *EffNVTXT = new TH1F("EffNVTXT","Signal Eff vs NVTX T",100,0,100);
  TH1F *EffPTT   = new TH1F("EffPTT","Signal Eff vs PT T",100,0,1000);
  TH1F *EffETAT  = new TH1F("EffETAT","Signal Eff vs Eta T",100,-5,5);
  TH1F *EffPHIT  = new TH1F("EffPHIT","Signal Eff vs PHI T",100,-4,4);

  TH1F *EffNVTX0b = new TH1F("EffNVTX0b","Background Eff vs NVTX 0",100,0,100);
  TH1F *EffPT0b   = new TH1F("EffPT0b","Background Eff vs PT 0",100,0,1000);
  TH1F *EffETA0b  = new TH1F("EffETA0b","Background Eff vs Eta 0",100,-5,5);
  TH1F *EffPHI0b  = new TH1F("EffPHI0b","Background Eff vs PHI 0",100,-4,4);

  TH1F *EffNVTXLb = new TH1F("EffNVTXLb","Background Eff vs NVTX L",100,0,100);
  TH1F *EffPTLb   = new TH1F("EffPTLb","Background Eff vs PT L",100,0,1000);
  TH1F *EffETALb  = new TH1F("EffETALb","Background Eff vs Eta L",100,-5,5);
  TH1F *EffPHILb  = new TH1F("EffPHILb","Background Eff vs PHI L",100,-4,4);
  
  TH1F *EffNVTXMb = new TH1F("EffNVTXMb","Background Eff vs NVTX M",100,0,100);
  TH1F *EffPTMb   = new TH1F("EffPTMb","Background Eff vs PT M",100,0,1000);
  TH1F *EffETAMb  = new TH1F("EffETAMb","Background Eff vs Eta M",100,-5,5);
  TH1F *EffPHIMb  = new TH1F("EffPHIMb","Background Eff vs PHI M",100,-4,4);

  TH1F *EffNVTXTb = new TH1F("EffNVTXTb","Background Eff vs NVTX T",100,0,100);
  TH1F *EffPTTb  = new TH1F("EffPTTb","Background Eff vs PT T",100,0,1000);
  TH1F *EffETATb  = new TH1F("EffETATb","Background Eff vs Eta T",100,-5,5);
  TH1F *EffPHITb  = new TH1F("EffPHITb","Background Eff vs PHI T",100,-4,4);

  // Branch out Cuts

   
  TH1F *EffNVTXs = new TH1F("EffNVTXs","Signal Eff vs NVTX T s",100,0,100);
  TH1F *EffPTs  = new TH1F("EffPTs","Signal Eff vs PT T s",100,0,1000);
  TH1F *EffETAs  = new TH1F("EffETAs","Signal Eff vs PT T s",100,-5,5);

  TH1F *EffNVTXt = new TH1F("EffNVTXt","Signal Eff vs NVTX T s",100,0,100);
  TH1F *EffPTt  = new TH1F("EffPTt","Signal Eff vs PT T s",100,0,1000);
  TH1F *EffETAt  = new TH1F("EffETAt","Signal Eff vs PT T s",100,-5,5);

  TH1F *EffNVTXc = new TH1F("EffNVTXc","Signal Eff vs NVTX T s",100,0,100);
  TH1F *EffPTc  = new TH1F("EffPTc","Signal Eff vs PT T s",100,0,1000);
  TH1F *EffETAc  = new TH1F("EffETAc","Signal Eff vs PT T s",100,-5,5);

  TH1F *EffNVTXn = new TH1F("EffNVTXn","Signal Eff vs NVTX T s",100,0,100);
  TH1F *EffPTn  = new TH1F("EffPTn","Signal Eff vs PT T s",100,0,1000);
  TH1F *EffETAn  = new TH1F("EffETAn","Signal Eff vs PT T s",100,-5,5);

  TH1F *EffNVTXp = new TH1F("EffNVTXp","Signal Eff vs NVTX T s",100,0,100);
  TH1F *EffPTp  = new TH1F("EffPTp","Signal Eff vs PT T s",100,0,1000);
  TH1F *EffETAp  = new TH1F("EffETAp","Signal Eff vs PT T s",100,-5,5);


  TH1F *EffNVTXbs = new TH1F("EffNVTXbs","Background Eff vs NVTX T s",100,0,100);
  TH1F *EffPTbs  = new TH1F("EffPTbs","Background Eff vs PT T s",100,0,1000);
  TH1F *EffETAbs  = new TH1F("EffETAbs","Background Eff vs PT T s",100,-5,5);

  TH1F *EffNVTXbt = new TH1F("EffNVTXbt","Background Eff vs NVTX T s",100,0,100);
  TH1F *EffPTbt  = new TH1F("EffPTbt","Background Eff vs PT T s",100,0,1000);
  TH1F *EffETAbt  = new TH1F("EffETAbt","Background Eff vs PT T s",100,-5,5);

  TH1F *EffNVTXbc = new TH1F("EffNVTXbc","Background Eff vs NVTX T s",100,0,100);
  TH1F *EffPTbc  = new TH1F("EffPTbc","Background Eff vs PT T s",100,0,1000);
  TH1F *EffETAbc  = new TH1F("EffETAbc","Background Eff vs PT T s",100,-5,5);

  TH1F *EffNVTXbn = new TH1F("EffNVTXbn","Background Eff vs NVTX T s",100,0,100);
  TH1F *EffPTbn  = new TH1F("EffPTbn","Background Eff vs PT T s",100,0,1000);
  TH1F *EffETAbn  = new TH1F("EffETAbn","Background Eff vs PT T s",100,-5,5);

  TH1F *EffNVTXbp = new TH1F("EffNVTXbp","Background Eff vs NVTX T s",100,0,100);
  TH1F *EffPTbp  = new TH1F("EffPTbp","Background Eff vs PT T s",100,0,1000);
  TH1F *EffETAbp  = new TH1F("EffETAbp","Background Eff vs PT T s",100,-5,5);

  //PT
  TH1F *EffPTMs  = new TH1F("EffPTMs","Signal Eff vs PT T s",100,0,1000);
  TH1F *EffPTMt  = new TH1F("EffPTMt","Signal Eff vs PT T s",100,0,1000);
  TH1F *EffPTMc  = new TH1F("EffPTMc","Signal Eff vs PT T s",100,0,1000);
  TH1F *EffPTMp  = new TH1F("EffPTMp","Signal Eff vs PT T s",100,0,1000);
  TH1F *EffPTMn  = new TH1F("EffPTMn","Signal Eff vs PT T s",100,0,1000);


  TH1F *EffPTTs  = new TH1F("EffPTTs","Signal Eff vs PT T s",100,0,1000);
  TH1F *EffPTTt  = new TH1F("EffPTTt","Signal Eff vs PT T s",100,0,1000);
  TH1F *EffPTTc  = new TH1F("EffPTTc","Signal Eff vs PT T s",100,0,1000);
  TH1F *EffPTTp  = new TH1F("EffPTTp","Signal Eff vs PT T s",100,0,1000);
  TH1F *EffPTTn  = new TH1F("EffPTTn","Signal Eff vs PT T s",100,0,1000);

  //NVTX
  TH1F *EffNVTXMs  = new TH1F("EffNVTXMs","Signal Eff vs NVTX T s",100,0,100);
  TH1F *EffNVTXMt  = new TH1F("EffNVTXMt","Signal Eff vs NVTX T s",100,0,100);
  TH1F *EffNVTXMc  = new TH1F("EffNVTXMc","Signal Eff vs NVTX T s",100,0,100);
  TH1F *EffNVTXMp  = new TH1F("EffNVTXMp","Signal Eff vs NVTX T s",100,0,100);
  TH1F *EffNVTXMn  = new TH1F("EffNVTXMn","Signal Eff vs NVTX T s",100,0,100);


  TH1F *EffNVTXTs  = new TH1F("EffNVTXTs","Signal Eff vs NVTX T s",100,0,100);
  TH1F *EffNVTXTt  = new TH1F("EffNVTXTt","Signal Eff vs NVTX T s",100,0,100);
  TH1F *EffNVTXTc  = new TH1F("EffNVTXTc","Signal Eff vs NVTX T s",100,0,100);
  TH1F *EffNVTXTp  = new TH1F("EffNVTXTp","Signal Eff vs NVTX T s",100,0,100);
  TH1F *EffNVTXTn  = new TH1F("EffNVTXTn","Signal Eff vs NVTX T s",100,0,100);

  //ETA
  TH1F *EffETAMs  = new TH1F("EffETAMs","Signal Eff vs ETA T s",100,-5,5);
  TH1F *EffETAMt  = new TH1F("EffETAMt","Signal Eff vs ETA T s",100,-5,5);
  TH1F *EffETAMc  = new TH1F("EffETAMc","Signal Eff vs ETA T s",100,-5,5);
  TH1F *EffETAMp  = new TH1F("EffETAMp","Signal Eff vs ETA T s",100,-5,5);
  TH1F *EffETAMn  = new TH1F("EffETAMn","Signal Eff vs ETA T s",100,-5,5);


  TH1F *EffETATs  = new TH1F("EffETATs","Signal Eff vs ETA T s",100,-5,5);
  TH1F *EffETATt  = new TH1F("EffETATt","Signal Eff vs ETA T s",100,-5,5);
  TH1F *EffETATc  = new TH1F("EffETATc","Signal Eff vs ETA T s",100,-5,5);
  TH1F *EffETATp  = new TH1F("EffETATp","Signal Eff vs ETA T s",100,-5,5);
  TH1F *EffETATn  = new TH1F("EffETATn","Signal Eff vs ETA T s",100,-5,5);


  //Medium 
  TH1F *EffNVTXMbs = new TH1F("EffNVTXMbs","Background Eff vs NVTX T s",100,0,100);
  TH1F *EffPTMbs  = new TH1F("EffPTMbs","Background Eff vs PT T s",100,0,1000);
  TH1F *EffETAMbs  = new TH1F("EffETAMbs","Background Eff vs PT T s",100,-5,5);

  TH1F *EffNVTXMbt = new TH1F("EffNVTXMbt","Background Eff vs NVTX T s",100,0,100);
  TH1F *EffPTMbt  = new TH1F("EffPTMbt","Background Eff vs PT T s",100,0,1000);
  TH1F *EffETAMbt  = new TH1F("EffETAMbt","Background Eff vs PT T s",100,-5,5);

  TH1F *EffNVTXMbc = new TH1F("EffNVTXMbc","Background Eff vs NVTX T s",100,0,100);
  TH1F *EffPTMbc  = new TH1F("EffPTMbc","Background Eff vs PT T s",100,0,1000);
  TH1F *EffETAMbc  = new TH1F("EffETAMbc","Background Eff vs PT T s",100,-5,5);

  TH1F *EffNVTXMbn = new TH1F("EffNVTXMbn","Background Eff vs NVTX T s",100,0,100);
  TH1F *EffPTMbn  = new TH1F("EffPTMbn","Background Eff vs PT T s",100,0,1000);
  TH1F *EffETAMbn  = new TH1F("EffETAMbn","Background Eff vs PT T s",100,-5,5);

  TH1F *EffNVTXMbp = new TH1F("EffNVTXMbp","Background Eff vs NVTX T s",100,0,100);
  TH1F *EffPTMbp  = new TH1F("EffPTMbp","Background Eff vs PT T s",100,0,1000);
  TH1F *EffETAMbp  = new TH1F("EffETAMbp","Background Eff vs PT T s",100,-5,5);

  //Tight 
  TH1F *EffNVTXTbs = new TH1F("EffNVTXTbs","Background Eff vs NVTX T s",100,0,100);
  TH1F *EffPTTbs  = new TH1F("EffPTTbs","Background Eff vs PT T s",100,0,1000);
  TH1F *EffETATbs  = new TH1F("EffETATbs","Background Eff vs PT T s",100,-5,5);

  TH1F *EffNVTXTbt = new TH1F("EffNVTXTbt","Background Eff vs NVTX T s",100,0,100);
  TH1F *EffPTTbt  = new TH1F("EffPTTbt","Background Eff vs PT T s",100,0,1000);
  TH1F *EffETATbt  = new TH1F("EffETATbt","Background Eff vs PT T s",100,-5,5);

  TH1F *EffNVTXTbc = new TH1F("EffNVTXTbc","Background Eff vs NVTX T s",100,0,100);
  TH1F *EffPTTbc  = new TH1F("EffPTTbc","Background Eff vs PT T s",100,0,1000);
  TH1F *EffETATbc  = new TH1F("EffETATbc","Background Eff vs PT T s",100,-5,5);

  TH1F *EffNVTXTbn = new TH1F("EffNVTXTbn","Background Eff vs NVTX T s",100,0,100);
  TH1F *EffPTTbn  = new TH1F("EffPTTbn","Background Eff vs PT T s",100,0,1000);
  TH1F *EffETATbn  = new TH1F("EffETATbn","Background Eff vs PT T s",100,-5,5);

  TH1F *EffNVTXTbp = new TH1F("EffNVTXTbp","Background Eff vs NVTX T s",100,0,100);
  TH1F *EffPTTbp  = new TH1F("EffPTTbp","Background Eff vs PT T s",100,0,1000);
  TH1F *EffETATbp  = new TH1F("EffETATbp","Background Eff vs PT T s",100,-5,5);





  
  //Setting the Tree Branches

  //   TFile *finput = new TFile( "/nfs_scratch/sacharya/UL_studies/CMSSW_10_6_20/src/Photon_ID/Trainner/CutTMVABarrelTrainnerUL_1_30.root");
   TFile *finput = new TFile( "../../CutTMVABarrelTrainner_TruePV_1_60.root");

  //TFile *finput = new TFile( "/uscms_data/d3/asroy/PhotonIdTuning/CMSSW_7_3_5/src/CutBasedPhoID2016/merged/fabrice_task/PV/PFIso/train/CutTMVABarrel90.root");
  //TFile *finput = new TFile( "/uscms_data/d3/asroy/PhotonIdTuning/CMSSW_7_3_5/src/CutBasedPhoID2016/merged/ChEA_ISOPT/CutTMVABarrel90_HPT.root");
  float Ppt,Peta,Pphi,isoP,isoC,isoN,sieie,toe,weight;
  int   nvtx; 
  
  //  weight = 1.0; 

  finput->cd();
  TTree *t_S = (TTree*)finput->Get("t_S");
 TTree *t_B = (TTree*)finput->Get("t_B");

  //Signal Tree                                                                 
  t_S->SetBranchAddress("Sieie",&sieie);
  t_S->SetBranchAddress("isoP",&isoP);
  t_S->SetBranchAddress("isoC",&isoC);
  t_S->SetBranchAddress("isoN",&isoN);
  t_S->SetBranchAddress("ToE",&toe);
  t_S->SetBranchAddress("weighT",&weight);
  t_S->SetBranchAddress("Nvtx",&nvtx);
  t_S->SetBranchAddress("Peta",&Peta);
  t_S->SetBranchAddress("Ppt",&Ppt);

  //Background Tree                                                                 
  t_B->SetBranchAddress("Sieie",&sieie);
  t_B->SetBranchAddress("isoP",&isoP);
  t_B->SetBranchAddress("isoC",&isoC);
  t_B->SetBranchAddress("isoN",&isoN);
  t_B->SetBranchAddress("ToE",&toe);
  t_B->SetBranchAddress("weighT",&weight);
  t_B->SetBranchAddress("Nvtx",&nvtx);
  t_B->SetBranchAddress("Peta",&Peta);
  t_B->SetBranchAddress("Ppt",&Ppt);


  
  EffNVTX0->Sumw2();
  EffPT0->Sumw2();
  EffETA0->Sumw2();
  EffPHI0->Sumw2();
  
  EffNVTXL->Sumw2();
  EffPTL->Sumw2();
  EffETAL->Sumw2();
  EffPHIL->Sumw2();
  
  EffNVTXM->Sumw2();
  EffPTM->Sumw2();
  EffETAM->Sumw2();
  EffPHIM->Sumw2();
  
  EffNVTXT->Sumw2();
  EffPTT->Sumw2();
  EffETAT->Sumw2();
  EffPHIT->Sumw2();
  
  
  EffNVTX0b->Sumw2();
  EffPT0b->Sumw2();
  EffETA0b->Sumw2();
  EffPHI0b->Sumw2();
  
  EffNVTXLb->Sumw2();
  EffPTLb->Sumw2();
  EffETALb->Sumw2();
  EffPHILb->Sumw2();
  
  EffNVTXMb->Sumw2();
  EffPTMb->Sumw2();
  EffETAMb->Sumw2();
  EffPHIMb->Sumw2();
  
  EffNVTXTb->Sumw2();
  EffPTTb->Sumw2();
  EffETATb->Sumw2();
  EffPHITb->Sumw2(); 

  
  EffNVTXs->Sumw2();
  EffPTs->Sumw2();
  EffETAs->Sumw2();
  
  EffNVTXt->Sumw2();
  EffPTt->Sumw2();
  EffETAt->Sumw2();
  
  EffNVTXc->Sumw2();
  EffPTc->Sumw2();
  EffETAc->Sumw2();
  
  EffNVTXn->Sumw2();
  EffPTn->Sumw2();
  EffETAn->Sumw2();

  EffNVTXp->Sumw2();
  EffPTp->Sumw2();
  EffETAp->Sumw2();

  
  EffNVTXbs->Sumw2();
  EffPTbs->Sumw2();
  EffETAbs->Sumw2();

  EffNVTXbt->Sumw2();
  EffPTbt->Sumw2();
  EffETAbt->Sumw2();

  EffNVTXbc->Sumw2();
  EffPTbc->Sumw2();
  EffETAbc->Sumw2();

  EffNVTXbn->Sumw2();
  EffPTbn->Sumw2();
  EffETAbn->Sumw2();

  EffNVTXbp->Sumw2();
  EffPTbp->Sumw2();
  EffETAbp->Sumw2();

  //PT    
  EffPTMs->Sumw2();
  EffPTMt->Sumw2();
  EffPTMc->Sumw2();
  EffPTMp->Sumw2();
  EffPTMn->Sumw2();
    
  EffPTTs->Sumw2();
  EffPTTt->Sumw2();
  EffPTTc->Sumw2();
  EffPTTp->Sumw2();
  EffPTTn->Sumw2();

  //NVTX
  EffNVTXMs->Sumw2();
  EffNVTXMt->Sumw2();
  EffNVTXMc->Sumw2();
  EffNVTXMp->Sumw2();
  EffNVTXMn->Sumw2();
    
  EffNVTXTs->Sumw2();
  EffNVTXTt->Sumw2();
  EffNVTXTc->Sumw2();
  EffNVTXTp->Sumw2();
  EffNVTXTn->Sumw2();

  //ETA
  EffETAMs->Sumw2();
  EffETAMt->Sumw2();
  EffETAMc->Sumw2();
  EffETAMp->Sumw2();
  EffETAMn->Sumw2();
    
  EffETATs->Sumw2();
  EffETATt->Sumw2();
  EffETATc->Sumw2();
  EffETATp->Sumw2();
  EffETATn->Sumw2();

  //Medium
  EffNVTXMbs->Sumw2();
  EffPTMbs->Sumw2();
  EffETAMbs->Sumw2();

  EffNVTXMbt->Sumw2();
  EffPTMbt->Sumw2();
  EffETAMbt->Sumw2();

  EffNVTXMbc->Sumw2();
  EffPTMbc->Sumw2();
  EffETAMbc->Sumw2();

  EffNVTXMbn->Sumw2();
  EffPTMbn->Sumw2();
  EffETAMbn->Sumw2();

  EffNVTXMbp->Sumw2();
  EffPTMbp->Sumw2();
  EffETAMbp->Sumw2();

  //Tight
  EffNVTXTbs->Sumw2();
  EffPTTbs->Sumw2();
  EffETATbs->Sumw2();

  EffNVTXTbt->Sumw2();
  EffPTTbt->Sumw2();
  EffETATbt->Sumw2();

  EffNVTXTbc->Sumw2();
  EffPTTbc->Sumw2();
  EffETATbc->Sumw2();

  EffNVTXTbn->Sumw2();
  EffPTTbn->Sumw2();
  EffETATbn->Sumw2();

  EffNVTXTbp->Sumw2();
  EffPTTbp->Sumw2();
  EffETATbp->Sumw2();


  for(int i = 0; i < t_S->GetEntries(); i++){
    t_S->GetEntry(i);
    
    EffNVTX0->Fill(nvtx,weight);
    EffPT0->Fill(Ppt,weight);
    EffETA0->Fill(Peta,weight);

  
    //Loose Cut: 
    if((sieie  < 0.0103 )&&
       (toe    < 0.031 )&&
       (isoP < 0.18 + 2.99336e-03*Ppt)&&
       (isoC   <8.61)&&
       //       (isoN-(0.001219*Ppt+0.00000000000001164*Ppt*Ppt) < isoNL)){
       (isoN < 7.26 +9.73714e-03*Ppt+ 1.01605e-05 *Ppt*Ppt)){
      
      EffNVTXL->Fill(nvtx,weight);
      EffPTL->Fill(Ppt,weight);
      EffETAL->Fill(Peta,weight);
    }
    
    //Medium Cut:
    if((sieie  < 0.0103)&&
       (toe    < 0.023)&&
       (isoP < 0.17 + 2.99336e-03*Ppt)&&
       (isoC  < 2.14 )&&
       //       (isoN-(0.001219*Ppt+0.00000000000001164*Ppt*Ppt) < isoNM)){
       (isoN < 7.25 +9.73714e-03*Ppt+ 1.01605e-05 *Ppt*Ppt)){
      EffNVTXM->Fill(nvtx,weight);
      EffPTM->Fill(Ppt,weight);
      EffETAM->Fill(Peta,weight);
    }
    //Tight Cut:
    /*    if((sieie  < 0.0103424 )&&
       (toe    < 0.031 )&&
       (isoP < 20.6312 + 2.99336e-03*Ppt )&&
       (isoC   < 0.313776 )&&
       //      (isoN-(0.001219*Ppt+0.00000000000001164*Ppt*Ppt)  < isoNT)){
       (isoN  < 2.26832 + 0.02312*Ppt + 2.259e-05*Ppt*Ppt )){
      EffNVTXT->Fill(nvtx,weight);
      EffPTT->Fill(Ppt,weight);
      EffETAT->Fill(Peta,weight);
    }
    */
  //Branch out Cuts
    if(sieie  < 0.0103 ){
      EffNVTXs->Fill(nvtx,weight);
      EffPTs->Fill(Ppt,weight);
      EffETAs->Fill(Peta,weight);
       
    }
    if(toe    < 0.031 ){
      EffNVTXt->Fill(nvtx,weight);
      EffPTt->Fill(Ppt,weight);
      EffETAt->Fill(Peta,weight);
     
    }    
    if(isoP < 0.18 + 2.99336e-03*Ppt){    
      EffNVTXp->Fill(nvtx,weight);
      EffPTp->Fill(Ppt,weight);
      EffETAp->Fill(Peta,weight);
     
    }    
    if(isoC   <8.61){
      EffNVTXc->Fill(nvtx,weight);
      EffPTc->Fill(Ppt,weight);
      EffETAc->Fill(Peta,weight);
     
    }
    //    if(isoN-(0.001219*Ppt+0.00000000000001164*Ppt*Ppt) < 7.26 +9.73714e-03*Ppt+ 1.01605e-05 *Ppt*Ppt){
    if(isoN < 7.26 +9.73714e-03*Ppt+ 1.01605e-05 *Ppt*Ppt){
      EffNVTXn->Fill(nvtx,weight);
      EffPTn->Fill(Ppt,weight);
      EffETAn->Fill(Peta,weight);
     
    }

    //Branch out Cuts Medium
    if(sieie  < 0.0103){
      EffPTMs->Fill(Ppt,weight);
      EffNVTXMs->Fill(nvtx,weight);
      EffETAMs->Fill(Peta,weight);
    }
    if(toe    <0.023 ){
      EffPTMt->Fill(Ppt,weight);
      EffNVTXMt->Fill(nvtx,weight);
      EffETAMt->Fill(Peta,weight);
    }    
    if(isoP < 0.17 + 2.99336e-03*Ppt){    
      EffPTMp->Fill(Ppt,weight);
      EffNVTXMp->Fill(nvtx,weight);
      EffETAMp->Fill(Peta,weight);
    }    
    if(isoC   < 2.14 ){
      EffPTMc->Fill(Ppt,weight);
      EffNVTXMc->Fill(nvtx,weight);
      EffETAMc->Fill(Peta,weight);
    }
    //    if(isoN -(0.001219*Ppt+0.00000000000001164*Ppt*Ppt)< isoNM){
    if(isoN <7.25 +9.73714e-03*Ppt+ 1.01605e-05 *Ppt*Ppt){
      EffPTMn->Fill(Ppt,weight);
      EffNVTXMn->Fill(nvtx,weight);
      EffETAMn->Fill(Peta,weight);
    }

    //Branch out Cuts Tight
    /*  if(sieie  < 0.0103424 ){
      EffPTTs->Fill(Ppt,weight);
      EffNVTXTs->Fill(nvtx,weight);
      EffETATs->Fill(Peta,weight);
    }
    if(toe    < 0.031){
      EffPTTt->Fill(Ppt,weight);
      EffNVTXTt->Fill(nvtx,weight);
      EffETATt->Fill(Peta,weight);
    }    
    if(isoP < 20.6312 + 2.99336e-03*Ppt){    
      EffPTTp->Fill(Ppt,weight);
      EffNVTXTp->Fill(nvtx,weight);
      EffETATp->Fill(Peta,weight);
    }    
    if(isoC   < 0.313776 ){
      EffPTTc->Fill(Ppt,weight);
      EffNVTXTc->Fill(nvtx,weight);
      EffETATc->Fill(Peta,weight);
    }
    //    if(isoN-(0.001219*Ppt+0.00000000000001164*Ppt*Ppt) < isoNT){
    if(isoN < 2.26832 + 0.02312*Ppt + 2.259e-05*Ppt*Ppt ){
      EffPTTn->Fill(Ppt,weight);
      EffNVTXTn->Fill(nvtx,weight);
      EffETATn->Fill(Peta,weight);
    }

    */



  }  


  //plots for Background 


  for(int i = 0; i < t_B->GetEntries(); i++){
    t_B->GetEntry(i);
    EffNVTX0b->Fill(nvtx,weight);
    EffPT0b->Fill(Ppt,weight);
    EffETA0b->Fill(Peta,weight);
  
    //Loose Cut: 
    if((sieie  < 0.0103 )&&
       (toe    < 0.031 )&&
       (isoP < 0.18 + 2.99336e-03*Ppt)&&
       (isoC  <8.61)&&
       //(isoN -(0.001219*Ppt+0.00000000000001164*Ppt*Ppt)< 7.26 +9.73714e-03*Ppt+ 1.01605e-05 *Ppt*Ppt))
 (isoN < 7.26 +9.73714e-03*Ppt+ 1.01605e-05 *Ppt*Ppt ))
{
      
	 EffNVTXLb->Fill(nvtx,weight);
	 EffPTLb->Fill(Ppt,weight);
	 EffETALb->Fill(Peta,weight);
       }
    
       //Medium Cut:
       if((sieie  < 0.0103)&&
	  (toe    < 0.023 )&&
	  (isoP < 0.17 + 2.99336e-03*Ppt)&&
	  (isoC  < 2.14 )&&
	  //	  (isoN-(0.001219*Ppt+0.00000000000001164*Ppt*Ppt) < isoNM)){
	  (isoN < 7.25 +9.73714e-03*Ppt+ 1.01605e-05 *Ppt*Ppt)){
	 EffNVTXMb->Fill(nvtx,weight);
	 EffPTMb->Fill(Ppt,weight);
	 EffETAMb->Fill(Peta,weight);
       }
       //Tight Cut:
       /* if((sieie  <  0.0103424)&&
	  (toe    < 0.031 )&&
	  (isoP < 20.6312 + 2.99336e-03*Ppt)&&
	  (isoC   < 0.313776 )&&
	  // (isoN -(0.001219*Ppt+0.00000000000001164*Ppt*Ppt)< isoNT)){
	 (isoN < 2.26832 + 0.02312*Ppt + 2.259e-05*Ppt*Ppt )){
	    EffNVTXTb->Fill(nvtx,weight);
	    EffPTTb->Fill(Ppt,weight);
	    EffETATb->Fill(Peta,weight);
	  }
       */ //Branch out Cuts
	  //Loose
	  if(sieie  < 0.0103 ){
	    EffNVTXbs->Fill(nvtx,weight);
	    EffPTbs->Fill(Ppt,weight);
	    EffETAbs->Fill(Peta,weight);
	  }
	  if(toe    < 0.031 ){
	    EffNVTXbt->Fill(nvtx,weight);
	    EffPTbt->Fill(Ppt,weight);
	    EffETAbt->Fill(Peta,weight);
	  }    
	  if(isoP < 0.18 + 2.99336e-03*Ppt){    
	    EffNVTXbp->Fill(nvtx,weight);
	    EffPTbp->Fill(Ppt,weight);
	    EffETAbp->Fill(Peta,weight);
	  }    
	  if(isoC   <8.61){
	    EffNVTXbc->Fill(nvtx,weight);
	    EffPTbc->Fill(Ppt,weight);
	    EffETAbc->Fill(Peta,weight);
 
	  }
	  //	  if(isoN -(0.001219*Ppt+0.00000000000001164*Ppt*Ppt)< 7.26 +9.73714e-03*Ppt+ 1.01605e-05 *Ppt*Ppt ){
	  if(isoN < 7.26 +9.73714e-03*Ppt+ 1.01605e-05 *Ppt*Ppt ){
	    EffNVTXbn->Fill(nvtx,weight);
	    EffPTbn->Fill(Ppt,weight);
	    EffETAbn->Fill(Peta,weight);
      
	  }

	  //Medium
	  if(sieie  < 0.0103){
	    EffNVTXMbs->Fill(nvtx,weight);
	    EffPTMbs->Fill(Ppt,weight);
	    EffETAMbs->Fill(Peta,weight);
	  }
	  if(toe    < 0.023 ){
	    EffNVTXMbt->Fill(nvtx,weight);
	    EffPTMbt->Fill(Ppt,weight);
	    EffETAMbt->Fill(Peta,weight);
	  }    
	  if(isoP < 0.17 + 2.99336e-03*Ppt){    
	    EffNVTXMbp->Fill(nvtx,weight);
	    EffPTMbp->Fill(Ppt,weight);
	    EffETAMbp->Fill(Peta,weight);
	  }    
	  if(isoC   < 2.14 ){
	    EffNVTXMbc->Fill(nvtx,weight);
	    EffPTMbc->Fill(Ppt,weight);
	    EffETAMbc->Fill(Peta,weight);
 
	  }
	  if(isoN < 7.25 +9.73714e-03*Ppt+ 1.01605e-05 *Ppt*Ppt ){
	    //	  if(isoN-(0.001219*Ppt+0.00000000000001164*Ppt*Ppt) < isoNM){
	    EffNVTXMbn->Fill(nvtx,weight);
	    EffPTMbn->Fill(Ppt,weight);
	    EffETAMbn->Fill(Peta,weight);
      
	  }


	  //Tight
	  /* if(sieie  <  0.0103424 ){
	    EffNVTXTbs->Fill(nvtx,weight);
	    EffPTTbs->Fill(Ppt,weight);
	    EffETATbs->Fill(Peta,weight);
	  }
	  if(toe    < 0.031 ){
	    EffNVTXTbt->Fill(nvtx,weight);
	    EffPTTbt->Fill(Ppt,weight);
	    EffETATbt->Fill(Peta,weight);
	  }    
	  if(isoP  <20.6312 + 2.99336e-03*Ppt ){    
	    EffNVTXTbp->Fill(nvtx,weight);
	    EffPTTbp->Fill(Ppt,weight);
	    EffETATbp->Fill(Peta,weight);
	  }    
	  if(isoC   < 0.313776 ){
	    EffNVTXTbc->Fill(nvtx,weight);
	    EffPTTbc->Fill(Ppt,weight);
	    EffETATbc->Fill(Peta,weight);
 
	  }
	  //	  if(isoN -(0.001219*Ppt+0.00000000000001164*Ppt*Ppt)< isoNT){
	  if(isoN < 2.26832 + 9.73714e-03*Ppt+ 1.01605e-05 *Ppt*Ppt ){
	    EffNVTXTbn->Fill(nvtx,weight);
	    EffPTTbn->Fill(Ppt,weight);
	    EffETATbn->Fill(Peta,weight);
      
	  }
	  */
	  }



       TFile *f1 = new TFile("Eff_updat_SR_TruePVID.root","recreate");
       f1->cd();
       EffNVTX0->Write();
       EffPT0->Write();
       EffETA0->Write();
       EffPHI0->Write();
  
       EffNVTXL->Write();
       EffPTL->Write();
       EffETAL->Write();
       EffPHIL->Write();
  
       EffNVTXM->Write();
       EffPTM->Write();
       EffETAM->Write();
       EffPHIM->Write();
  
       EffNVTXT->Write();
       EffPTT->Write();
       EffETAT->Write();
       EffPHIT->Write();


       EffNVTX0b->Write();
       EffPT0b->Write();
       EffETA0b->Write();
       EffPHI0b->Write();
  
       EffNVTXLb->Write();
       EffPTLb->Write();
       EffETALb->Write();
       EffPHILb->Write();
  
       EffNVTXMb->Write();
       EffPTMb->Write();
       EffETAMb->Write();
       EffPHIMb->Write();
  
       EffNVTXTb->Write();
       EffPTTb->Write();
       EffETATb->Write();
       EffPHITb->Write(); 


       EffNVTXs->Write();
       EffPTs->Write();
       EffETAs->Write();


       EffNVTXt->Write();
       EffPTt->Write();
       EffETAt->Write();
    
       EffNVTXc->Write();
       EffPTc->Write();
       EffETAc->Write();


       EffNVTXn->Write();
       EffPTn->Write();
       EffETAn->Write();
  

       EffNVTXp->Write();
       EffPTp->Write();
       EffETAp->Write();

  
       EffNVTXbs->Write();
       EffPTbs->Write();
       EffETAbs->Write();

  
       EffNVTXbt->Write();
       EffPTbt->Write();
       EffETAbt->Write();
  
       EffNVTXbc->Write();
       EffPTbc->Write();
       EffETAbc->Write();

       EffNVTXbn->Write();
       EffPTbn->Write();
       EffETAbn->Write();

       EffNVTXbp->Write();
       EffPTbp->Write(); 
       EffETAbp->Write();


       //PT
       EffPTMs->Write();
       EffPTMt->Write();
       EffPTMc->Write();
       EffPTMp->Write();
       EffPTMn->Write();
    
       EffPTTs->Write();
       EffPTTt->Write();
       EffPTTc->Write();
       EffPTTp->Write();
       EffPTTn->Write();

       //NVTX
       EffNVTXMs->Write();
       EffNVTXMt->Write();
       EffNVTXMc->Write();
       EffNVTXMp->Write();
       EffNVTXMn->Write();
    
       EffNVTXTs->Write();
       EffNVTXTt->Write();
       EffNVTXTc->Write();
       EffNVTXTp->Write();
       EffNVTXTn->Write();

       //ETA
       EffETAMs->Write();
       EffETAMt->Write();
       EffETAMc->Write();
       EffETAMp->Write();
       EffETAMn->Write();
    
       EffETATs->Write();
       EffETATt->Write();
       EffETATc->Write();
       EffETATp->Write();
       EffETATn->Write();
  
       //Medium
       EffNVTXMbs->Write();
       EffPTMbs->Write();
       EffETAMbs->Write();
  
       EffNVTXMbt->Write();
       EffPTMbt->Write();
       EffETAMbt->Write();
  
       EffNVTXMbc->Write();
       EffPTMbc->Write();
       EffETAMbc->Write();

       EffNVTXMbn->Write();
       EffPTMbn->Write();
       EffETAMbn->Write();

       EffNVTXMbp->Write();
       EffPTMbp->Write(); 
       EffETAMbp->Write();

       //Tight
       EffNVTXTbs->Write();
       EffPTTbs->Write();
       EffETATbs->Write();
  
       EffNVTXTbt->Write();
       EffPTTbt->Write();
       EffETATbt->Write();
  
       EffNVTXTbc->Write();
       EffPTTbc->Write();
       EffETATbc->Write();

       EffNVTXTbn->Write();
       EffPTTbn->Write();
       EffETATbn->Write();

       EffNVTXTbp->Write();
       EffPTTbp->Write(); 
       EffETATbp->Write();




       TFile *feta = new TFile("Eff1etaB_updat_SR_TruePVID.root","recreate");
       feta->cd();


       EffETA0->Write();
       EffETA0b->Write();


       EffETAs->Write();
       EffETAt->Write();
       EffETAc->Write();
       EffETAn->Write();
       EffETAp->Write();


       EffETAbs->Write();
       EffETAbt->Write();
       EffETAbc->Write();
       EffETAbn->Write();
       EffETAbp->Write();

 

       // Plotter.C //
       TH1F *Letas = new TH1F("Letas","Loose Cut TruePV Efficiency Eta",100,-5,5);
       TH1F *Metas = new TH1F("Metas","Medium Cut TruePV Efficiency Eta",100,-5,5);
       TH1F *Tetas = new TH1F("Tetas","Tight Cut TruePV Efficiency Eta",100,-5,5); 

       TH1F *Lpts = new TH1F("Lpts","Loose Cut TruePV Efficiency pt",100,0,1000);
       TH1F *Mpts = new TH1F("Mpts","Medium Cut TruePV Efficiency pt",100,0,1000);
       TH1F *Tpts = new TH1F("Tpts","Tight Cut TruePV Efficiency pt",100,0,1000); 

       TH1F *Lnvtxs = new TH1F("Lnvtxs","Loose Cut TruePV Efficiency vertices",100,0,100);
       TH1F *Mnvtxs = new TH1F("Mnvtxs","Medium Cut TruePV Efficiency vertices",100,0,100);
       TH1F *Tnvtxs = new TH1F("Tnvtxs","Tight Cut TruePV Efficiency vertices",100,0,100); 


       TH1F *Letab = new TH1F("Letab","Loose Cut b TruePV Efficiency Eta",100,-5,5);
       TH1F *Metab = new TH1F("Metab","Medium Cut b TruePV Efficiency Eta",100,-5,5);
       TH1F *Tetab = new TH1F("Tetab","Tight Cut b TruePV Efficiency Eta",100,-5,5); 


       TH1F *Lptb = new TH1F("Lptb","Loose Cut b TruePV Efficiency pt",100,0,1000);
       TH1F *Mptb = new TH1F("Mptb","Medium Cut b TruePV Efficiency pt",100,0,1000);
       TH1F *Tptb = new TH1F("Tptb","Tight Cut b TruePV Efficiency pt",100,0,1000); 


  
       TH1F *Lnvtxb = new TH1F("Lnvtxb","Loose Cut b  TruePV Efficiency vertices",100,0,100);
       TH1F *Mnvtxb = new TH1F("Mnvtxb","Medium Cut b TruePV Efficiency vertices",100,0,100);
       TH1F *Tnvtxb = new TH1F("Tnvtxb","Tight Cut b TruePV Efficiency vertices",100,0,100); 


       /*       TH1F *Sieaft  = new TH1F("Sieaft","Sieie cut only",100,0,1000); 
       TH1F *ToEaft  = new TH1F("ToEaft","HoE cut only",100,0,1000); 
       TH1F *IsoPaft = new TH1F("IsoPaft","IsoP cut only",100,0,1000); 
       TH1F *IsoCaft = new TH1F("IsoCaft","IsoC cut only",100,0,1000); 
       TH1F *IsoNaft = new TH1F("IsoNaft","IsoN cut only",100,0,1000); 
       */

       TH1F *Sieaft  = new TH1F("Sieaft","Sieie cut only",100,0,1000); 
       TH1F *ToEaft  = new TH1F("ToEaft","HoE cut only",100,0,1000); 
       TH1F *IsoPaft = new TH1F("IsoPaft","IsoP cut only",100,0,1000); 
       TH1F *IsoCaft = new TH1F("IsoCaft","IsoC cut only",100,0,1000); 
       TH1F *IsoNaft = new TH1F("IsoNaft","IsoN cut only",100,0,1000); 


       TH1F *SieaftM  = new TH1F("SieaftM","Sieie cut only",100,0,1000); 
       TH1F *ToEaftM  = new TH1F("ToEaftM","HoE cut only",100,0,1000); 
       TH1F *IsoPaftM = new TH1F("IsoPaftM","IsoP cut only",100,0,1000); 
       TH1F *IsoCaftM = new TH1F("IsoCaftM","IsoC cut only",100,0,1000); 
       TH1F *IsoNaftM = new TH1F("IsoNaftM","IsoN cut only",100,0,1000); 


       TH1F *SieaftT  = new TH1F("SieaftT","Sieie cut only",100,0,1000); 
       TH1F *ToEaftT  = new TH1F("ToEaftT","HoE cut only",100,0,1000); 
       TH1F *IsoPaftT = new TH1F("IsoPaftT","IsoP cut only",100,0,1000); 
       TH1F *IsoCaftT = new TH1F("IsoCaftT","IsoC cut only",100,0,1000); 
       TH1F *IsoNaftT = new TH1F("IsoNaftT","IsoN cut only",100,0,1000); 


       TH1F *Sieaftb  = new TH1F("Sieaftb","Sieie cut only",100,0,1000); 
       TH1F *ToEaftb  = new TH1F("ToEaftb","HoE cut only",100,0,1000); 
       TH1F *IsoPaftb = new TH1F("IsoPaftb","IsoP cut only",100,0,1000); 
       TH1F *IsoCaftb = new TH1F("IsoCaftb","IsoC cut only",100,0,1000); 
       TH1F *IsoNaftb = new TH1F("IsoNaftb","IsoN cut only",100,0,1000); 

       TH1F *SieaftN  = new TH1F("SieaftN","Sieie cut only",100,0,100); 
       TH1F *ToEaftN  = new TH1F("ToEaftN","HoE cut only",100,0,100); 
       TH1F *IsoPaftN = new TH1F("IsoPaftN","IsoP cut only",100,0,100); 
       TH1F *IsoCaftN = new TH1F("IsoCaftN","IsoC cut only",100,0,100); 
       TH1F *IsoNaftN = new TH1F("IsoNaftN","IsoN cut only",100,0,100); 

       TH1F *SieaftbN  = new TH1F("SieaftbN","Sieie cut only",100,0,100); 
       TH1F *ToEaftbN  = new TH1F("ToEaftbN","HoE cut only",100,0,100); 
       TH1F *IsoPaftbN = new TH1F("IsoPaftbN","IsoP cut only",100,0,100); 
       TH1F *IsoCaftbN = new TH1F("IsoCaftbN","IsoC cut only",100,0,100); 
       TH1F *IsoNaftbN = new TH1F("IsoNaftbN","IsoN cut only",100,0,100); 

  
       TH1F *SieaftE  = new TH1F("SieaftE","Sieie cut only",100,-5,5); 
       TH1F *ToEaftE  = new TH1F("ToEaftE","HoE cut only",100,-5,5); 
       TH1F *IsoPaftE = new TH1F("IsoPaftE","IsoP cut only",100,-5,5); 
       TH1F *IsoCaftE = new TH1F("IsoCaftE","IsoC cut only",100,-5,5); 
       TH1F *IsoNaftE = new TH1F("IsoNaftE","IsoN cut only",100,-5,5); 

       TH1F *SieaftbE  = new TH1F("SieaftbE","Sieie cut only",100,-5,5); 
       TH1F *ToEaftbE  = new TH1F("ToEaftbE","HoE cut only",100,-5,5); 
       TH1F *IsoPaftbE = new TH1F("IsoPaftbE","IsoP cut only",100,-5,5); 
       TH1F *IsoCaftbE = new TH1F("IsoCaftbE","IsoC cut only",100,-5,5); 
       TH1F *IsoNaftbE = new TH1F("IsoNaftbE","IsoN cut only",100,-5,5); 










       Letas->Divide(EffETAL,EffETA0,1.,1.,"B");
       Metas->Divide(EffETAM,EffETA0,1.,1.,"B");
       Tetas->Divide(EffETAT,EffETA0,1.,1.,"B");
  
       Letab->Divide(EffETALb,EffETA0b,1.,1.,"B");
       Metab->Divide(EffETAMb,EffETA0b,1.,1.,"B");
       Tetab->Divide(EffETATb,EffETA0b,1.,1.,"B");
  

       Lpts->Divide(EffPTL,EffPT0,1.,1.,"B");
       Mpts->Divide(EffPTM,EffPT0,1.,1.,"B");
       Tpts->Divide(EffPTT,EffPT0,1.,1.,"B");

  
       Lptb->Divide(EffPTLb,EffPT0b,1.,1.,"B");
       Mptb->Divide(EffPTMb,EffPT0b,1.,1.,"B");
       Tptb->Divide(EffPTTb,EffPT0b,1.,1.,"B");

       Lnvtxs->Divide(EffNVTXL,EffNVTX0,1.,1.,"B");
       Mnvtxs->Divide(EffNVTXM,EffNVTX0,1.,1.,"B");
       Tnvtxs->Divide(EffNVTXT,EffNVTX0,1.,1.,"B");

  
       Lnvtxb->Divide(EffNVTXLb,EffNVTX0b,1.,1.,"B");
       Mnvtxb->Divide(EffNVTXMb,EffNVTX0b,1.,1.,"B");
       Tnvtxb->Divide(EffNVTXTb,EffNVTX0b,1.,1.,"B");


       // the branch  out cuts 


       Sieaft->Divide(EffPTs,EffPT0,1.,1.,"B"); 
       ToEaft->Divide(EffPTt,EffPT0,1.,1.,"B");
       IsoPaft->Divide(EffPTp,EffPT0,1.,1.,"B");
       IsoCaft->Divide(EffPTc,EffPT0,1.,1.,"B");
       IsoNaft->Divide(EffPTn,EffPT0,1.,1.,"B");

       SieaftM->Divide(EffPTMs,EffPT0,1.,1.,"B"); 
       ToEaftM->Divide(EffPTMt,EffPT0,1.,1.,"B");
       IsoPaftM->Divide(EffPTMp,EffPT0,1.,1.,"B");
       IsoCaftM->Divide(EffPTMc,EffPT0,1.,1.,"B");
       IsoNaftM->Divide(EffPTMn,EffPT0,1.,1.,"B");

       SieaftT->Divide(EffPTTs,EffPT0,1.,1.,"B"); 
       ToEaftT->Divide(EffPTTt,EffPT0,1.,1.,"B");
       IsoPaftT->Divide(EffPTTp,EffPT0,1.,1.,"B");
       IsoCaftT->Divide(EffPTTc,EffPT0,1.,1.,"B");
       IsoNaftT->Divide(EffPTTn,EffPT0,1.,1.,"B");


       Sieaftb->Divide(EffPTbs,EffPT0b,1.,1.,"B"); 
       ToEaftb->Divide(EffPTbt,EffPT0b,1.,1.,"B");
       IsoPaftb->Divide(EffPTbp,EffPT0b,1.,1.,"B");
       IsoCaftb->Divide(EffPTbc,EffPT0b,1.,1.,"B");
       IsoNaftb->Divide(EffPTbn,EffPT0b,1.,1.,"B");


  
       SieaftN->Divide(EffNVTXs,EffNVTX0,1.,1.,"B"); 
       ToEaftN->Divide(EffNVTXt,EffNVTX0,1.,1.,"B");
       IsoPaftN->Divide(EffNVTXp,EffNVTX0,1.,1.,"B");
       IsoCaftN->Divide(EffNVTXc,EffNVTX0,1.,1.,"B");
       IsoNaftN->Divide(EffNVTXn,EffNVTX0,1.,1.,"B");


       SieaftbN->Divide(EffNVTXbs,EffNVTX0b,1.,1.,"B"); 
       ToEaftbN->Divide(EffNVTXbt,EffNVTX0b,1.,1.,"B");
       IsoPaftbN->Divide(EffNVTXbp,EffNVTX0b,1.,1.,"B");
       IsoCaftbN->Divide(EffNVTXbc,EffNVTX0b,1.,1.,"B");
       IsoNaftbN->Divide(EffNVTXbn,EffNVTX0b,1.,1.,"B");


  
       SieaftE->Divide(EffETAs,EffETA0,1.,1.,"B"); 
       ToEaftE->Divide(EffETAt,EffETA0,1.,1.,"B");
       IsoPaftE->Divide(EffETAp,EffETA0,1.,1.,"B");
       IsoCaftE->Divide(EffETAc,EffETA0,1.,1.,"B");
       IsoNaftE->Divide(EffETAn,EffETA0,1.,1.,"B");


       SieaftbE->Divide(EffETAbs,EffETA0b,1.,1.,"B"); 
       ToEaftbE->Divide(EffETAbt,EffETA0b,1.,1.,"B");
       IsoPaftbE->Divide(EffETAbp,EffETA0b,1.,1.,"B");
       IsoCaftbE->Divide(EffETAbc,EffETA0b,1.,1.,"B");
       IsoNaftbE->Divide(EffETAbn,EffETA0b,1.,1.,"B");








  
       TCanvas *c1  = new TCanvas("c1","Medium",600,600);
  c1->Divide(2,2);

  c1->cd(1);
  Mnvtxs->Draw();
  Mnvtxs->GetYaxis()->SetRangeUser(0,1.0);
 
  Mnvtxs->GetXaxis()->SetRangeUser(0,50);
 
  Mnvtxs->GetXaxis()->SetTitle("# Nvtx");
  Mnvtxs->SetLineColor(kRed);
  Mnvtxs->SetMarkerColor(kRed);
  Mnvtxs->SetMarkerSize(0.5);
  Mnvtxb->SetLineColor(kGreen);
  Mnvtxb->SetMarkerColor(kGreen);
  Mnvtxb->SetMarkerSize(0.5);
  Mnvtxb->Draw("same");
  
  c1->cd(2);
  Mpts->Draw();
  Mpts->GetYaxis()->SetRangeUser(0,1.0);
 
  Mpts->GetXaxis()->SetTitle("Pt GeVc^{-1}");
  Mpts->SetLineColor(kRed);
  Mpts->SetMarkerColor(kRed);
  Mpts->SetMarkerSize(0.5);
  Mptb->SetLineColor(kGreen);
  Mptb->SetMarkerColor(kGreen);
  Mptb->SetMarkerSize(0.5);
  Mptb->Draw("same");

  c1->cd(3);
  Metas->Draw();
  Metas->GetYaxis()->SetRangeUser(0,1.0);
  // Metas->GetXaxis()->SetRangeUser(1.5,3.0);
  Metas->GetXaxis()->SetRangeUser(-5.0,5.0);
 
  Metas->GetXaxis()->SetTitle("#eta");
  Metas->SetLineColor(kRed);
  Metas->SetMarkerColor(kRed);
  Metas->SetMarkerSize(0.5);
  Metab->SetLineColor(kGreen);
  Metab->SetMarkerColor(kGreen);
  Metab->SetMarkerSize(0.5);
  Metab->Draw("same");
  c1->SaveAs("MediumEffBck_TruePV.png");

  TCanvas *c2  = new TCanvas("c2","ID TruePV  Efficiency",600,600);
  c2->Divide(2,2);

  c2->cd(1);
  Lnvtxs->Draw();
  Lnvtxs->GetXaxis()->SetTitle("# Nvtx");
  Lnvtxs->GetYaxis()->SetRangeUser(0,1.0);
  Lnvtxs->GetXaxis()->SetRangeUser(0,50);

  Lnvtxs->SetLineColor(kRed);
  Lnvtxs->SetMarkerColor(kRed);
  Lnvtxs->SetMarkerSize(0.5);
  Lnvtxb->SetLineColor(kGreen);
  Lnvtxb->SetMarkerColor(kGreen);
  Lnvtxb->SetMarkerSize(0.5);
  Lnvtxb->Draw("esame");
  
  c2->cd(2);
  Lpts->Draw();
  Lpts->GetXaxis()->SetTitle("Pt GeVc^{-1}");
  Lpts->GetYaxis()->SetRangeUser(0,1.0);
  Lpts->SetLineColor(kRed);
  Lpts->SetMarkerColor(kRed);
  Lpts->SetMarkerSize(0.5);
  Lptb->SetLineColor(kGreen);
  Lptb->SetMarkerColor(kGreen);
  Lptb->SetMarkerSize(0.5);
  Lptb->Draw("esame");



  c2->cd(3);
  Letas->Draw();
  Letas->GetXaxis()->SetTitle("#eta");
  Letas->GetYaxis()->SetRangeUser(0,1.0);
  //Letas->GetXaxis()->SetRangeUser(1.5,3.0);
 Letas->GetXaxis()->SetRangeUser(-5.0,5.0);
  
  Letas->SetLineColor(kRed);

  Letas->SetMarkerColor(kRed);
  Letas->SetMarkerSize(0.5);
  Letab->SetLineColor(kGreen);
  Letab->SetMarkerColor(kGreen);
  Letab->SetMarkerSize(0.5);

  Letab->Draw("esame");
  


  c2->SaveAs("LooseEffBck_TruePV.png");




  TCanvas *c3  = new TCanvas("c3","Tight",600,600);
  c3->Divide(2,2);

  c3->cd(1);
  Tnvtxs->Draw();
  Tnvtxs->GetYaxis()->SetRangeUser(0,1.0);
  Tnvtxs->GetXaxis()->SetRangeUser(0,50);
 
  Tnvtxs->GetXaxis()->SetTitle("# Nvtx");
  Tnvtxs->SetLineColor(kRed);
  Tnvtxs->SetMarkerColor(kRed);
  Tnvtxs->SetMarkerSize(0.5);
  Tnvtxb->SetLineColor(kGreen);
  Tnvtxb->SetMarkerColor(kGreen);
  Tnvtxb->SetMarkerSize(0.5);

  Tnvtxb->Draw("esame");
  
  c3->cd(2);
  Tpts->Draw();
  Tpts->GetYaxis()->SetRangeUser(0,1.0);
  
  Tpts->GetXaxis()->SetTitle("Pt GeVc^{-1}");
  Tpts->SetLineColor(kRed);
  Tpts->SetMarkerColor(kRed);
  Tpts->SetMarkerSize(0.5);
  Tptb->SetLineColor(kGreen);
  Tptb->SetMarkerColor(kGreen);
  Tptb->SetMarkerSize(0.5);
  Tptb->Draw("esame");



  c3->cd(3);
  Tetas->Draw();
  Tetas->GetYaxis()->SetRangeUser(0,1.0);
 
  Tetas->GetXaxis()->SetTitle("#eta");
  //   Tetas->GetXaxis()->SetRangeUser(1.5,3.0);
  Tetas->GetXaxis()->SetRangeUser(-5.0,5.0);
  Tetas->SetLineColor(kRed);
  Tetas->SetMarkerColor(kRed);
  Tetas->SetMarkerSize(0.5);
  Tetab->SetLineColor(kGreen);
  Tetab->SetMarkerColor(kGreen);
  Tetab->SetMarkerSize(0.5);

  Tetab->Draw("same");
  c3->SaveAs("TightEffBck_TruePV.png");

 


  TCanvas *c10 = new TCanvas("c10","Branch Out Cuts",900,600);
  c10->Divide(3,2);
  
  c10->cd(1);  

  Sieaft->Draw();
       Sieaftb->Draw("same");
       Sieaft->SetMarkerSize(0.5);
       Sieaftb->SetMarkerSize(0.5);
       Sieaftb->SetLineColor(kRed);
       Sieaftb->SetMarkerColor(kRed);
       Sieaft->GetYaxis()->SetTitle("Only Sieie Cut TruePV Efficiency");
       Sieaft->GetXaxis()->SetTitle("Pt GeVc^{-1}");
 
       c10->cd(2);
       ToEaft->Draw();
       ToEaftb->Draw("same");
       ToEaft->SetMarkerSize(0.5);
       ToEaftb->SetMarkerSize(0.5);
       ToEaftb->SetLineColor(kRed);
       ToEaftb->SetMarkerColor(kRed);
       ToEaft->GetYaxis()->SetTitle("Only HOE Cut TruePV Efficiency");
       ToEaft->GetXaxis()->SetTitle("Pt GeVc^{-1}");

       c10->cd(3);
       IsoPaft->Draw();
       IsoPaftb->Draw("same");
       IsoPaft->SetMarkerSize(0.5);
       IsoPaftb->SetLineColor(kRed);
       IsoPaftb->SetMarkerColor(kRed);
       IsoPaftb->SetMarkerSize(0.5);
       IsoPaft->GetYaxis()->SetTitle("Only iso p Cut TruePV Efficiency");
       IsoPaft->GetXaxis()->SetTitle("Pt GeVc^{-1}");

       c10->cd(4);
       IsoCaft->Draw();
       IsoCaftb->Draw("same");
       IsoCaft->SetMarkerSize(0.5);
       IsoCaftb->SetLineColor(kRed);
       IsoCaftb->SetMarkerColor(kRed);
       IsoCaftb->SetMarkerSize(0.5);
       IsoCaft->GetYaxis()->SetTitle("Only iso c Cut TruePV Efficiency");
       IsoCaft->GetXaxis()->SetTitle("Pt GeVc^{-1}");
  
       c10->cd(5);
       IsoNaft->Draw();
       IsoNaftb->Draw("same");
       IsoNaft->SetMarkerSize(0.5);
       IsoNaftb->SetMarkerSize(0.5);
       IsoNaftb->SetLineColor(kRed);
       IsoNaftb->SetMarkerColor(kRed);
       IsoNaft->GetYaxis()->SetTitle("Only iso n Cut TruePV Efficiency");
       IsoNaft->GetXaxis()->SetTitle("Pt GeVc^{-1}");
  
       c10->SaveAs("BranchOutCuts_TruePV.png");

 
       TCanvas *c20 = new TCanvas("c20","Branch Out Cuts",900,600);
       c20->Divide(3,2);
  
       c20->cd(1);  

       Sieaft->Draw();
       SieaftM->Draw("same");
       SieaftT->Draw("same");
       Sieaft->SetMarkerSize(0.5);
       SieaftM->SetMarkerSize(0.5);
       SieaftT->SetMarkerSize(0.5);
 
       SieaftM->SetMarkerColor(kOrange -3);
       SieaftT->SetMarkerColor(kYellow);
       Sieaft->GetYaxis()->SetTitle("Only Sieie Cut TruePV Efficiency");
       Sieaft->GetXaxis()->SetTitle("Pt GeVc^{-1}");
 
       c20->cd(2);
  
       ToEaft->Draw();
       ToEaftM->Draw("same");
       ToEaftT->Draw("same");
       ToEaft->SetMarkerSize(0.5);
       ToEaftM->SetMarkerSize(0.5);
       ToEaftT->SetMarkerSize(0.5);
 
       ToEaftM->SetMarkerColor(kOrange -3);
       ToEaftT->SetMarkerColor(kYellow);
       ToEaft->GetYaxis()->SetTitle("Only H over E Cut TruePV Efficiency");
       ToEaft->GetXaxis()->SetTitle("Pt GeVc^{-1}");

       c20->cd(3);

       IsoPaft->Draw();
       IsoPaftM->Draw("same");
       IsoPaftT->Draw("same");
       IsoPaft->SetMarkerSize(0.5);
       IsoPaftM->SetMarkerSize(0.5);
       IsoPaftT->SetMarkerSize(0.5);
 
       IsoPaftM->SetMarkerColor(kOrange -3);
       IsoPaftT->SetMarkerColor(kYellow);
       IsoPaft->GetYaxis()->SetTitle("Only Iso P Cut TruePV Efficiency");
       IsoPaft->GetXaxis()->SetTitle("Pt GeVc^{-1}");

       c20->cd(4);

       IsoCaft->Draw();
       IsoCaftM->Draw("same");
       IsoCaftT->Draw("same");
       IsoCaft->SetMarkerSize(0.5);
       IsoCaftM->SetMarkerSize(0.5);
       IsoCaftT->SetMarkerSize(0.5);
 
       IsoCaftM->SetMarkerColor(kOrange -3);
       IsoCaftT->SetMarkerColor(kYellow);
       IsoCaft->GetYaxis()->SetTitle("Only Iso P Cut TruePV Efficiency");
       IsoCaft->GetXaxis()->SetTitle("Pt GeVc^{-1}");
  
       c20->cd(5);
  
       IsoNaft->Draw();
       IsoNaftM->Draw("same");
       IsoNaftT->Draw("same");
       IsoNaft->SetMarkerSize(0.5);
       IsoNaftM->SetMarkerSize(0.5);
       IsoNaftT->SetMarkerSize(0.5);
 
       IsoNaftM->SetMarkerColor(kOrange -3);
       IsoNaftT->SetMarkerColor(kYellow);
       IsoNaft->GetYaxis()->SetTitle("Only Iso P Cut TruePV Efficiency");
       IsoNaft->GetXaxis()->SetTitle("Pt GeVc^{-1}");

       c20->SaveAs("BranchOutCutsSignalWP_TruePV.png");

 

 









  
       TCanvas *c11 = new TCanvas("c11","Branch Out Cuts",900,600);
       c11->Divide(3,2);
  
       c11->cd(1);  

       SieaftN->Draw();
       SieaftbN->Draw("same");
       SieaftN->SetMarkerSize(0.5);
       SieaftbN->SetMarkerSize(0.5);
       SieaftbN->SetMarkerColor(kRed);
       SieaftN->GetYaxis()->SetTitle("Only Sieie Cut TruePV Efficiency");
       SieaftN->GetXaxis()->SetTitle("# Nvtx");
 
       c11->cd(2);
       ToEaftN->Draw();
       ToEaftbN->Draw("same");
       ToEaftN->SetMarkerSize(0.5);
       ToEaftbN->SetMarkerSize(0.5);
       ToEaftbN->SetMarkerColor(kRed);
       ToEaftN->GetYaxis()->SetTitle("Only HOE Cut TruePV Efficiency");
       ToEaftN->GetXaxis()->SetTitle("# Nvtx");

       c11->cd(3);
       IsoPaftN->Draw();
       IsoPaftbN->Draw("same");
       IsoPaftN->SetMarkerSize(0.5);
       IsoPaftbN->SetMarkerColor(kRed);
       IsoPaftbN->SetMarkerSize(0.5);
       IsoPaftN->GetYaxis()->SetTitle("Only iso p Cut TruePV Efficiency");
       IsoPaftN->GetXaxis()->SetTitle("# Nvtx");

       c11->cd(4);
       IsoCaftN->Draw();
       IsoCaftbN->Draw("same");
       IsoCaftN->SetMarkerSize(0.5);
       IsoCaftbN->SetMarkerColor(kRed);
       IsoCaftbN->SetMarkerSize(0.5);
       IsoCaftN->GetYaxis()->SetTitle("Only iso c Cut TruePV Efficiency");
       IsoCaftN->GetXaxis()->SetTitle("# Nvtx");
  
       c11->cd(5);
       IsoNaftN->Draw();
       IsoNaftbN->Draw("same");
       IsoNaftN->SetMarkerSize(0.5);
       IsoNaftbN->SetMarkerSize(0.5);
       IsoNaftbN->SetMarkerColor(kRed);
       IsoNaftN->GetYaxis()->SetTitle("Only iso n Cut TruePV Efficiency");
       IsoNaftN->GetXaxis()->SetTitle("# Nvtx");
  
       c11->SaveAs("BranchOutCutsNVTX_TruePV.png");




       TCanvas *c12 = new TCanvas("c12","Branch Out Cuts",900,600);
       c12->Divide(3,2);
  
       c12->cd(1);  

       SieaftE->Draw();
       SieaftbE->Draw("same");
       SieaftE->SetMarkerSize(0.5);
       SieaftbE->SetMarkerSize(0.5);
       SieaftbE->SetMarkerColor(kRed);
       SieaftE->GetYaxis()->SetTitle("Only Sieie Cut TruePV Efficiency");
       SieaftE->GetXaxis()->SetTitle("#eta");
 
       c12->cd(2);
       ToEaftE->Draw();
       ToEaftbE->Draw("same");
       ToEaftE->SetMarkerSize(0.5);
       ToEaftbE->SetMarkerSize(0.5);
       ToEaftbE->SetMarkerColor(kRed);
       ToEaftE->GetYaxis()->SetTitle("Only HOE Cut TruePV Efficiency");
       ToEaftE->GetXaxis()->SetTitle("#eta");

       c12->cd(3);
       IsoPaftE->Draw();
       IsoPaftbE->Draw("same");
       IsoPaftE->SetMarkerSize(0.5);
       IsoPaftbE->SetMarkerColor(kRed);
       IsoPaftbE->SetMarkerSize(0.5);
       IsoPaftE->GetYaxis()->SetTitle("Only iso p Cut TruePV Efficiency");
       IsoPaftE->GetXaxis()->SetTitle("#eta");

       c12->cd(4);
       IsoCaftE->Draw();
       IsoCaftbE->Draw("same");
       IsoCaftE->SetMarkerSize(0.5);
       IsoCaftbE->SetMarkerColor(kRed);
       IsoCaftbE->SetMarkerSize(0.5);
       IsoCaftE->GetYaxis()->SetTitle("Only iso c Cut TruePV Efficiency");
       IsoCaftE->GetXaxis()->SetTitle("#eta");
  
       c12->cd(5);
       IsoNaftE->Draw();
       IsoNaftbE->Draw("same");
       IsoNaftE->SetMarkerSize(0.5);
       IsoNaftbE->SetMarkerSize(0.5);
       IsoNaftbE->SetMarkerColor(kRed);
       IsoNaftE->GetYaxis()->SetTitle("Only iso n Cut TruePV Efficiency");
       IsoNaftE->GetXaxis()->SetTitle("#eta");
  
       c12->SaveAs("BranchOutCutsEta_TruePV.png");




       TCanvas *cpt = new TCanvas("cpt","Pt Eff",500,500);
       cpt->cd();
       Lpts->Draw();
       Lpts->GetXaxis()->SetTitle("Pt GeVc^{-1}");
       Lpts->GetYaxis()->SetRangeUser(0,1.0);
       Lpts->SetLineColor(kGray + 3);
       Lpts->SetMarkerColor(kGray +3);
       Lpts->SetMarkerStyle(20);
       Lpts->SetMarkerSize(0.5);

       Mpts->Draw("esame");
       Mpts->SetMarkerColor(kOrange -3);
       Mpts->SetLineColor(kOrange -3);
       Mpts->SetMarkerStyle(20);
       Mpts->SetMarkerSize(0.5);
 
       Tpts->Draw("esame");
       Tpts->SetMarkerColor(kYellow);
       Tpts->SetLineColor(kYellow );
       Tpts->SetMarkerStyle(20);
       Tpts->SetMarkerSize(0.5);
     
       Lptb->SetLineColor(kAzure + 3);
       Lptb->SetMarkerColor(kAzure +3);
       Lptb->SetMarkerStyle(20);
       Lptb->SetMarkerSize(0.5);
       Lptb->Draw("esame");

  
       Mptb->SetLineColor(kAzure + 5);
       Mptb->SetMarkerColor(kAzure +5);
       Mptb->SetMarkerStyle(20);
       Mptb->SetMarkerSize(0.5);
       Mptb->Draw("esame");


  
       Tptb->SetLineColor(kAzure + 10);
       Tptb->SetMarkerColor(kAzure +10);
       Tptb->SetMarkerStyle(20);
       Tptb->SetMarkerSize(0.5);
       Tptb->Draw("esame");





 

       cpt->SaveAs("EfPT_TruePV.png");

       TCanvas *ceta = new TCanvas("ceta","Eta Eff",500,500);
       ceta->cd();
       Letas->GetXaxis()->SetTitle("#eta");
       Letas->GetXaxis()->SetRangeUser(-5,5);
       Letas->GetYaxis()->SetRangeUser(0,1.0);
       Letas->SetLineColor(kGray + 3);
       Letas->SetMarkerColor(kGray +3);
       Letas->SetMarkerStyle(20);
       Letas->SetMarkerSize(0.5);
       Letas->Draw();

       Letab->SetLineColor(kAzure + 3);
       Letab->SetMarkerColor(kAzure +3);
       Letab->SetMarkerStyle(20);
       Letab->SetMarkerSize(0.5);
       Letab->Draw("esame");

  
       Metas->SetMarkerColor(kOrange -3);
       Metas->SetLineColor(kOrange -3);
       Metas->SetMarkerStyle(20);
       Metas->SetMarkerSize(0.5);
       Metas->Draw("esame");




       Metab->SetLineColor(kAzure + 5);
       Metab->SetMarkerColor(kAzure +5);
       Metab->SetMarkerStyle(20);
       Metab->SetMarkerSize(0.5);
       Metab->Draw("esame");


       Tetas->SetMarkerColor(kYellow );
       Tetas->SetLineColor(kYellow );
       Tetas->SetMarkerStyle(20);
       Tetas->SetMarkerSize(0.5);
       Tetas->Draw("esame");

  
       Tetab->SetLineColor(kAzure + 10);
       Tetab->SetMarkerColor(kAzure +10);
       Tetab->SetMarkerStyle(20);
       Tetab->SetMarkerSize(0.5);
       Tetab->Draw("esame");





      
       ceta->SaveAs("EfETA_TruePV.png");


  
       TCanvas *cnvtx = new TCanvas("cnvtx","NVtx Eff",500,500);
       cnvtx->cd();
       Lnvtxs->GetXaxis()->SetTitle("Nvtx");
       Lnvtxs->GetYaxis()->SetRangeUser(0,1.0);
       Lnvtxs->GetXaxis()->SetRangeUser(0,50);
       Lnvtxs->SetLineColor(kGray +3 );
       Lnvtxs->SetMarkerColor(kGray +3 );
       Lnvtxs->SetMarkerStyle(20);
       Lnvtxs->SetMarkerSize(0.5);
       Lnvtxs->Draw();

       Mnvtxs->Draw("esame");
       Mnvtxs->SetMarkerColor(kOrange -3);
       Mnvtxs->SetLineColor(kOrange -3);
       Mnvtxs->SetMarkerStyle(20);
       Mnvtxs->SetMarkerSize(0.5);
       Tnvtxs->Draw("esame");
       Tnvtxs->SetMarkerColor(kYellow);
       Tnvtxs->SetMarkerSize(0.5);
       Tnvtxs->SetLineColor(kYellow);
       Tnvtxs->SetMarkerStyle(20);


  
       Lnvtxb->SetLineColor(kAzure + 3);
       Lnvtxb->SetMarkerColor(kAzure +3);
       Lnvtxb->SetMarkerStyle(20);
       Lnvtxb->SetMarkerSize(0.5);
       Lnvtxb->Draw("esame");

  
       Mnvtxb->SetLineColor(kAzure + 5);
       Mnvtxb->SetMarkerColor(kAzure +5);
       Mnvtxb->SetMarkerStyle(20);
       Mnvtxb->SetMarkerSize(0.5);
       Mnvtxb->Draw("esame");


  
       Tnvtxb->SetLineColor(kAzure + 10);
       Tnvtxb->SetMarkerColor(kAzure +10);
       Tnvtxb->SetMarkerStyle(20);
       Tnvtxb->SetMarkerSize(0.5);
       Tnvtxb->Draw("esame");


       cnvtx->Update();
       cnvtx->SaveAs("EfNVTX_TruePV.png");


       // sig-eff/bkg-eff plots
       TCanvas *crpt = new TCanvas("crpt","Pt SBR Eff",500,500);
       crpt->cd();
       TH1F *Lptr = (TH1F*)Lpts->Clone();
       Lptr->Divide(Lptb);
       Lptr->Draw();
       Lptr->GetXaxis()->SetTitle("Pt GeVc^{-1}");
       Lptr->GetYaxis()->SetTitle("Sig Eff/Bkg Eff");
       Lptr->GetYaxis()->SetRangeUser(0,10.0);
       Lptr->SetLineColor(kGray + 3);
       Lptr->SetMarkerColor(kGray +3);
       Lptr->SetMarkerStyle(20);
       Lptr->SetMarkerSize(0.5);

       TH1F *Mptr = (TH1F*)Mpts->Clone();
       Mptr->Divide(Mptb);
       Mptr->Draw("esame");
       Mptr->SetMarkerColor(kOrange -3);
       Mptr->SetLineColor(kOrange -3);
       Mptr->SetMarkerStyle(20);
       Mptr->SetMarkerSize(0.5);


       TH1F *Tptr = (TH1F*)Tpts->Clone();
       Tptr->Divide(Tptb);
       Tptr->Draw("esame");
       Tptr->SetMarkerColor(kYellow);
       Tptr->SetLineColor(kYellow );
       Tptr->SetMarkerStyle(20);
       Tptr->SetMarkerSize(0.5);

  
       auto lptr = new TLegend(0.55,0.15,0.9,0.3);
       lptr->SetBorderSize(0);
       lptr->SetFillColor(0);
       lptr->AddEntry(Lptr,"Loose","lp");
       lptr->AddEntry(Mptr,"Medium","lp");
       lptr->AddEntry(Tptr,"Tight","lp");
       lptr->Draw("same");     


       crpt->SaveAs("EfSBR_PT_TruePV.png");




       TCanvas *creta = new TCanvas("creta","Eta SBR Eff",500,500);
       creta->cd();
       TH1F *Letar = (TH1F*)Letas->Clone();
       Letar->Divide(Letab);
       Letar->Draw();
       Letar->GetXaxis()->SetTitle("#eta");
       Letar->GetYaxis()->SetTitle("Sig Eff/Bkg Eff");
       Letar->GetYaxis()->SetRangeUser(0,10.0);
       Letar->SetLineColor(kGray + 3);
       Letar->SetMarkerColor(kGray +3);
       Letar->SetMarkerStyle(20);
       Letar->SetMarkerSize(0.5);

       TH1F *Metar = (TH1F*)Metas->Clone();
       Metar->Divide(Metab);
       Metar->Draw("esame");
       Metar->SetMarkerColor(kOrange -3);
       Metar->SetLineColor(kOrange -3);
       Metar->SetMarkerStyle(20);
       Metar->SetMarkerSize(0.5);
 
       TH1F *Tetar = (TH1F*)Tetas->Clone();
       Tetar->Divide(Tetab);
       Tetar->Draw("esame");
       Tetar->SetMarkerColor(kYellow);
       Tetar->SetLineColor(kYellow );
       Tetar->SetMarkerStyle(20);
       Tetar->SetMarkerSize(0.5);

  
       auto letar = new TLegend(0.55,0.15,0.9,0.3);
       letar->SetBorderSize(0);
       letar->SetFillColor(0);
       letar->AddEntry(Letar,"Loose","lp");
       letar->AddEntry(Metar,"Medium","lp");
       letar->AddEntry(Tetar,"Tight","lp");
       letar->Draw("same");     


       creta->SaveAs("EfSBR_ETA_TruePV.png");




       TCanvas *crnvtx = new TCanvas("crnvtx","Nvtx SBR Eff",500,500);
       crnvtx->cd();
       TH1F *Lnvtxr = (TH1F*)Lnvtxs->Clone();
       Lnvtxr->Divide(Lnvtxb);
       Lnvtxr->Draw();
       Lnvtxr->GetXaxis()->SetTitle("Nvtx");
       Lnvtxr->GetYaxis()->SetTitle("Sig Eff/Bkg Eff");
       Lnvtxr->GetYaxis()->SetRangeUser(0,10.0);
       Lnvtxr->SetLineColor(kGray + 3);
       Lnvtxr->SetMarkerColor(kGray +3);
       Lnvtxr->SetMarkerStyle(20);
       Lnvtxr->SetMarkerSize(0.5);

       TH1F *Mnvtxr = (TH1F*)Mnvtxs->Clone();
       Mnvtxr->Divide(Mnvtxb);
       Mnvtxr->Draw("esame");
       Mnvtxr->SetMarkerColor(kOrange -3);
       Mnvtxr->SetLineColor(kOrange -3);
       Mnvtxr->SetMarkerStyle(20);
       Mnvtxr->SetMarkerSize(0.5);
 
       TH1F *Tnvtxr = (TH1F*)Tnvtxs->Clone();
       Tnvtxr->Divide(Tnvtxb);
       Tnvtxr->Draw("esame");
       Tnvtxr->SetMarkerColor(kYellow);
       Tnvtxr->SetLineColor(kYellow );
       Tnvtxr->SetMarkerStyle(20);
       Tnvtxr->SetMarkerSize(0.5);

  
       auto lnvtxr = new TLegend(0.55,0.15,0.9,0.3);
       lnvtxr->SetBorderSize(0);
       lnvtxr->SetFillColor(0);
       lnvtxr->AddEntry(Lnvtxr,"Loose","lp");
       lnvtxr->AddEntry(Mnvtxr,"Medium","lp");
       lnvtxr->AddEntry(Tnvtxr,"Tight","lp");
       lnvtxr->Draw("same");     


       crnvtx->SaveAs("EfSBR_NVTX_TruePV.png");


       /*
  TCanvas *c1  = new TCanvas("c1","Medium",600,600);
  c1->Divide(2,2);

  c1->cd(1);
  Mnvtxs->Draw();
  Mnvtxs->GetYaxis()->SetRangeUser(0,1.0);
 
  Mnvtxs->GetXaxis()->SetRangeUser(0,50);
 
  Mnvtxs->GetXaxis()->SetTitle("# Nvtx");
  Mnvtxs->SetLineColor(kRed);
  Mnvtxs->SetMarkerColor(kRed);
  Mnvtxs->SetMarkerSize(0.5);
  Mnvtxb->SetMarkerSize(0.5);
  Mnvtxb->Draw("same");
  
  c1->cd(2);
  Mpts->Draw();
  Mpts->GetYaxis()->SetRangeUser(0,1.0);
 
  Mpts->GetXaxis()->SetTitle("Pt GeVc^{-1}");
  Mpts->SetLineColor(kRed);
  Mpts->SetMarkerColor(kRed);
  Mpts->SetMarkerSize(0.5);
  Mptb->SetMarkerSize(0.5);
  Mptb->Draw("same");

  c1->cd(3);
  Metas->Draw();
  Metas->GetYaxis()->SetRangeUser(0,1.0);

 
  Metas->GetXaxis()->SetTitle("#eta");
  Metas->SetLineColor(kRed);
  Metas->SetMarkerColor(kRed);
  Metas->SetMarkerSize(0.5);
  Metab->SetMarkerSize(0.5);
  Metab->Draw("same");
  c1->SaveAs("MediumEffBck.png");

  TCanvas *c2  = new TCanvas("c2","Loose",600,600);
  c2->Divide(2,2);

  c2->cd(1);
  Lnvtxs->Draw();
  Lnvtxs->GetXaxis()->SetTitle("# Nvtx");
  Lnvtxs->GetYaxis()->SetRangeUser(0,1.0);
  Lnvtxs->GetXaxis()->SetRangeUser(0,50);

  Lnvtxs->SetLineColor(kRed);
  Lnvtxs->SetMarkerColor(kRed);
  Lnvtxs->SetMarkerSize(0.5);
  Lnvtxb->SetMarkerSize(0.5);
  Lnvtxb->Draw("esame");
  
  c2->cd(2);
  Lpts->Draw();
  Lpts->GetXaxis()->SetTitle("Pt GeVc^{-1}");
  Lpts->GetYaxis()->SetRangeUser(0,1.0);
  Lpts->SetLineColor(kRed);
  Lpts->SetMarkerColor(kRed);
  Lpts->SetMarkerSize(0.5);
  Lptb->SetMarkerSize(0.5);
  Lptb->Draw("esame");



  c2->cd(3);
  Letas->Draw();
  Letas->GetXaxis()->SetTitle("#eta");
  Letas->GetYaxis()->SetRangeUser(0,1.0);
 
  
  Letas->SetLineColor(kRed);
  Letas->SetMarkerColor(kRed);
  Letas->SetMarkerSize(0.5);
  Letab->SetMarkerSize(0.5);

  Letab->Draw("esame");
  


  c2->SaveAs("LooseEffBck.png");




  TCanvas *c3  = new TCanvas("c3","Tight",600,600);
  c3->Divide(2,2);

  c3->cd(1);
  Tnvtxs->Draw();
  Tnvtxs->GetYaxis()->SetRangeUser(0,1.0);
  Tnvtxs->GetXaxis()->SetRangeUser(0,50);
 
  Tnvtxs->GetXaxis()->SetTitle("# Nvtx");
  Tnvtxs->SetLineColor(kRed);
  Tnvtxs->SetMarkerColor(kRed);
  Tnvtxs->SetMarkerSize(0.5);
  Tnvtxb->SetMarkerSize(0.5);

  Tnvtxb->Draw("esame");
  
  c3->cd(2);
  Tpts->Draw();
  Tpts->GetYaxis()->SetRangeUser(0,1.0);
  
  Tpts->GetXaxis()->SetTitle("Pt GeVc^{-1}");
  Tpts->SetLineColor(kRed);
  Tpts->SetMarkerColor(kRed);
  Tpts->SetMarkerSize(0.5);
  Tptb->SetMarkerSize(0.5);
  Tptb->Draw("esame");



  c3->cd(3);
  Tetas->Draw();
  Tetas->GetYaxis()->SetRangeUser(0,1.0);
 
  Tetas->GetXaxis()->SetTitle("#eta");

  Tetas->SetLineColor(kRed);
  Tetas->SetMarkerColor(kRed);
  Tetas->SetMarkerSize(0.5);
  Tetab->SetMarkerSize(0.5);

  Tetab->Draw("same");
  c3->SaveAs("TightEffBck.png");

       */



       TFile *f3 = new TFile("EtasB_updat_SR_TruePVID.root","recreate");
       f3->cd();
       Letas->Write();
       Metas->Write();
       Tetas->Write();

       Letab->Write();
       Metab->Write();
       Tetab->Write();


       TFile *fb = new TFile("Barrel_Plots_updat_SR_TruePVID.root","recreate");
       fb->cd();

       Lpts->Write();
       Mpts->Write();
       Tpts->Write();

       Lptb->Write();
       Mptb->Write();
       Tptb->Write();

       Lnvtxs->Write();
       Mnvtxs->Write();
       Tnvtxs->Write();

       Lnvtxb->Write();
       Mnvtxb->Write();
       Tnvtxb->Write();



       }
