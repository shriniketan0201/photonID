#include <cstdlib>
#include <TMath.h>
#include <stdio.h>
#include <iostream>
using namespace std;
void Scr99(){

TFile *f1 = new TFile("../CutTMVABarrelTrainner_TruePV_1_60.root");
  Float_t ToE,Sie,IsoP,IsoC,IsoN,Ppt; 
  Double_t weighT;
  ofstream myfile; 
  myfile.open("99per_bar.txt");   
  TTree *t_S = (TTree*)f1->Get("t_S");
  t_S->SetBranchAddress("Ppt",&Ppt);
  t_S->SetBranchAddress("ToE",&ToE);
  t_S->SetBranchAddress("Sieie",&Sie);
  t_S->SetBranchAddress("isoP",&IsoP);
  t_S->SetBranchAddress("isoC",&IsoC);
  t_S->SetBranchAddress("isoN",&IsoN);
  //t_S->SetBranchAddress("weighT",&weighT);

  weighT = 1;
  TH1F *HPt = new TH1F("HPt","HPt ",10000,0,1000);
  TH1F *HS = new TH1F("HS","sieie ",10000,0,0.5);
  TH1F *HH = new TH1F("HH","h over e ",10000,0,0.5);
  TH1F *HP = new TH1F("HP","photon  iso ",10000,0,1200);
  TH1F *HC = new TH1F("HC","worst charge  iso ",10000,0,1000);
    TH1F *HN = new TH1F("HN","neutral iso ",50000,0,1000);
    //   TH1F *HN = new TH1F("HN","neutral iso ",500000,0,10000);
  TH1F *W = new TH1F("W","weights  ",3,0,3);

  cout<<" Total entries in the tree  " <<t_S->GetEntries()<<endl;

  double max_s,max_p,max_n,max_c,max_t; 
  max_s = 0; 
  max_p = 0; 
  max_c = 0; 
  max_n = 0; 
  max_t = 0; 
  double totS = 1;
  for(int i = 0; i < t_S->GetEntries(); i++){
    t_S->GetEntry(i);
    //    if(Ppt < 20 ) continue;
    if(Ppt < 200 ) continue;
    HPt->Fill(Ppt);
    if(Sie > max_s)max_s = Sie; 
    if(ToE > max_t)max_t = ToE; 
    totS += weighT;
    W->Fill(1.0,weighT);
    HH->Fill(ToE,weighT);
    HS->Fill(Sie,weighT);
    //  double isoph = TMath::Max(IsoP - 0.003232*Ppt,0.0);
    //    double isoph = TMath::Max(IsoP - 0.00289*Ppt,0.0);
    //    double isoph = TMath::Max(IsoP - 0.003347*Ppt,0.0);
    double isoph = TMath::Max(IsoP - 2.99336e-03*Ppt,0.0);
    //    double isoch = TMath::Max(IsoC - (0.008556*Ppt+0.00001259*Ppt*Ppt),0.0);
    double ison = TMath::Max(IsoN - (9.73714e-03*Ppt+1.01605e-05*Ppt*Ppt),0.0);
    if(isoph> max_p)max_p = isoph; 
    if(IsoC> max_c)max_c =IsoC; 
    if(ison > max_n)max_n =ison; 
    HP->Fill(isoph,weighT);
    HC->Fill(IsoC,weighT);
    HN->Fill(ison,weighT);
  }

  cout<<  t_S->GetEntries() <<  " " << totS<< endl;
  
  double xcsf=0; 
  double xchf=0; 
  double xcpf=0; 
  double xccf=0; 
  double xcnf=0; 
  
  int p1 = 0;
  int p2 = 0;
  int p3 = 0;
  int p4 = 0;
  int p5 = 0;

  double sie_b = 0; 
  double neu_b = 0; 
  double pho_b = 0; 
  double chg_b = 0; 
  double toe_b = 0; 


  cout<<std::fixed<<(HS->Integral())<<" "<<(HS->Integral(0,10001))<<" "<<(HS->GetEntries())<<endl;
  cout<<std::fixed<<(HH->Integral())<<" "<<(HH->Integral(0,10001))<<" "<<(HH->GetEntries())<<endl;
  cout<<std::fixed<<(HP->Integral())<<" "<<(HP->Integral(0,10001))<<" "<<(HP->GetEntries())<<endl;
  cout<<std::fixed<<(HC->Integral())<<" "<<(HC->Integral(0,10001))<<" "<<(HC->GetEntries())<<endl;  
  cout<<std::fixed<<(HN->Integral())<<" "<<(HN->Integral(0,10001))<<" "<<(HN->GetEntries())<<endl;

  double HSIntegral  = HS->Integral(0,10001);
  double HHIntegral  = HH->Integral(0,10001);
  double HPIntegral  = HP->Integral(0,10001);
  double HCIntegral  = HC->Integral(0,10001);
  //   double HNIntegral  = HN->Integral(0,500001);
  double HNIntegral  = HN->Integral(0,50001);
  
  for(int i = 1 ; i <= 10000; i++){
    double xcs = (i*0.5)/10000; 
    double xch = (i*0.5)/10000; 
    double xcp = (i*1200.0)/10000; 
    double xcc = (i*1000.0)/10000; 
    double xcn = (i*1000.0)/50000; 
    if(1.0*HS->Integral(1,i)/(double)HSIntegral > 0.9999 && p1 == 0){
      p1 = 1;
      xcsf = xcs; 
    }
    if(1.0*HH->Integral(1,i)/(double)HHIntegral > 0.9999 && p2 == 0){
      xchf = xch; 
      p2 =1;
    }
    if(1.0*HP->Integral(1,i)/(double)HPIntegral > 0.9999 && p3 == 0){
      xcpf = xcp; 
      p3 = 1; 
    }
    if(1.0*HC->Integral(1,i)/(double)HCIntegral > 0.9999 && p4 == 0){
      xccf = xcc; 
      p4 = 1; 
    }
    if(1.0*HN->Integral(1,i)/(double)HNIntegral > 0.9999 && p5 == 0){
      p5 = 1;
      xcnf = xcn;
    }  
  
  }  
  /*   for(int j = 1 ; j <= 500000; j++){
  // for(int j = 1 ; j <= 50000; j++){
      double xcn = (j*10000.0)/500000; 
    if(1.0*HN->Integral(1,j)/(double)HNIntegral > 0.9999 && p5 == 0){
      p5 = 1;
      xcnf = xcn; 
    }
       if(j%1==0)cout<<std::setprecision(2)<<std::fixed<< HN->Integral(1,j)<< " " << HNIntegral<<  " " << j<< " " << xcnf<< " " << totS<<endl;
    if(xcnf>0)break;
  }
  */
  myfile<<" "<<xcsf<<"  "<<xchf<<" "<<xccf<<" "<<xcnf<<" "<<xcpf<<endl;
  //  myfile<<"H/E       "<<xchf<<endl;
  //myfile<<"HCAL      "<<xccf<<endl;
  // myfile<<"Tracker   "<<xcnf<<endl;
  // myfile<<"ECAL      "<<xcpf<<endl;


  myfile.close();
  /*
    cout<<sie_b/totS<<endl;
    cout<<toe_b/totS<<endl;
    cout<<pho_b/totS<<endl;
    cout<<chg_b/totS<<endl;
    cout<<neu_b/totS<<endl;
    cout<<"Sie  :"<<xcsf<<endl;
    cout<<"HoE  :"<<xchf<<endl;
    cout<<"IsoP :"<<xcpf<<endl;
    cout<<"IsoC :"<<xccf<<endl;
    cout<<"IsoN :"<<xcnf<<endl;
  */
  TFile *f = new TFile("Vars_bar.root","recreate");
  HS->Write();
  HH->Write();
  HP->Write();
  HC->Write();
  HN->Write();
  W->Write();
  HPt->Write();
  f->Close();

}
