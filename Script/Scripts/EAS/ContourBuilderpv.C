#include <TMath.h>
#include <cstdlib>
#include <TRandom.h>
#include <TGraph.h>
#include <TMultiGraph.h>
#include <TGraphErrors.h>
#include <TH2.h>
#include <TH1.h>

#include <vector>
#include <new>

#include <string>
#include <fstream>
#include <iostream>

using namespace std;







void ErrCalc(TH1F *HIST,int binxn,double perc,double & X_val, double & errXL,double & errXH){


  cout<<binxn<<endl;
  TH1F *h1 = (TH1F*)HIST->Clone();
  int arsize = h1->GetXaxis()->GetNbins();
  cout<<"arsize"<<arsize<<endl;
  cout<<"h1 is "<<h1->GetEntries()<<endl;
                                                                      
  double *eff;
  double *eff_err;
  double *cutV;
  double *cutV_err;

  eff      = new double[arsize];
  cutV     = new double[arsize];
  eff_err  = new double[arsize];
  cutV_err = new double[arsize];
  h1->Draw();
  int tot = h1->GetEntries();
  cout<<"tot<"<<tot<<endl;
  int integ = 0;
  float tot_nz = tot - h1->GetBinContent(1);
  for(int i  = 1; i < (h1->GetXaxis()->GetNbins() + 1); i++){
    double xCut = h1->GetXaxis()->GetBinLowEdge(i);
    integ += h1->GetBinContent(i);
    if(integ != 0 && tot != 0 ){
      eff[i -1] = (integ*1.0/tot);
      //            eff_err[i -1] = ((integ*1.0/tot)*sqrt(pow(sqrt(tot)/tot,2) + pow(sqrt(integ)/integ,2) ));
      eff_err[i -1] = sqrt ( eff[i-1] * ( 1 - eff[i-1] ) / tot_nz ) ; //test
    }else{
      eff_err[i -1] = 0.0;
      eff[i -1] = 0.0;
    }

    cutV[i -1] = (xCut);
    cutV_err[i - 1] = 0;
  }

  gStyle->SetOptStat(1);

  //Now draw the resulting curve                                                                                                                                                                                                              
  TCanvas *c1 = new TCanvas("c1","The Eff- cut value plot",1200,600);

  c1->Divide(2,1);

  c1->cd(1);
  double x[2] = {h1->GetXaxis()->GetBinCenter(1),h1->GetXaxis()->GetBinCenter(arsize)};
  double y[2] = {perc,perc};

  TGraph *lineP =  new TGraph(2,x,y);
  lineP->SetLineColor(kRed);

  TGraphErrors *efC = new TGraphErrors(arsize ,cutV,eff,cutV_err,eff_err);
  efC->SetMarkerStyle(20);
  efC->SetMarkerSize(0.5);

  //   efC->Draw("AP");                                                                                                                                                                                                                       
  efC->GetXaxis()->SetTitle("Cut Value");
  efC->GetYaxis()->SetTitle("Efficiency");


  TMultiGraph *GRPhs = new TMultiGraph();
  GRPhs->Add(lineP,"l");
  GRPhs->Add(efC,"p");

  GRPhs->Draw("APL");

  c1->cd(2);

  h1->Draw();

  //  c1->SaveAs(graphname);                                                                                                                                                                                                                  

  double * err_up;
  double * err_down;

  err_up = new double [arsize];
  err_down = new double [arsize];

  /*  for(int i = 0;  i < arsize ; i++){

    if( fabs(eff[i]) > 0.00001 && fabs(eff_err[i]) > 0.0001){

      err_up[i] = eff[i] + eff_err[i];
      err_down[i] = eff[i] - eff_err[i];


    }else{


      err_up[i] = 0;
      err_down[i] = 0;


    }
    }*/

  for(int i = 0;  i < arsize ; i++){
    err_up[i] = eff[i] + eff_err[i];
    err_down[i] = eff[i] - eff_err[i];
  }
    
  int xc = 0; 
  for(int i = 0; i < arsize; i++){
    if( eff[i] > perc ){ 
      xc = i; 
      break;
    }
  }


  X_val = cutV[xc];
  //Extrapolation method to find the CutValue errors                                                                                                                                                                                          
  int up = -99;
  int down = -99;
  for( int i  = 0; i < arsize ; i++){
    if( err_up [i] > perc){ up = i;
      //  cout<<"up is"<<up<<endl;                                                                                                                                                                                                        
      break;
    }
  }
  for( int i  = 0; i < arsize ; i++){
    if( err_down [i] > perc){
      down = i;
      break;
    }
  }

  // here it returns the extrapolated result                                                                                                                                                                                                  

  /*  double Usl   = 0;
  double Ustom = 0;
  double err_1 = 0;
  double Dsl   = 0;
  double Dstom = 0;
  double err_2 = 0;
  if(up != -99  ){
    double Usl   = (err_up[up] - err_up[up-1])/(cutV[up] - cutV[up-1]);
    double Ustom = err_up[up] - Usl*cutV[up];
    cout<<"Usl"<<Usl<<endl;
    cout<<"Ustom"<<Ustom<<endl;
    err_1 = (perc - Ustom)/Usl;
  }else{
    err_1 = 0;
    Usl   = 0;
    Ustom = 0;
  }

  if(down != -99){
    double Dsl   = (err_down[down] - err_down[down-1])/(cutV[down] - cutV[down-1]);
    double Dstom = err_down[down] - Dsl*cutV[down];
    err_2 = (perc - Dstom)/Dsl;
  }else{
    err_2 = 0;
    Dsl   = 0;
    Dstom = 0;

  }

  cout<<"down err:"<<err_1<<endl;
  cout<<"UP err:"<<err_2<<endl;
  cout<<"cut value"<<(err_1+err_2)/2.;
  cout<<"sym err:"<< (err_2-err_1)/2.;
  */

  /*  int xc = 0;

  for(int i = 0; i < arsize; i++){
    if( eff[i] > perc ){
      xc = i;
      // cout<<"xc"<<xc<<endl;                                                                                                                                                                                                                
      break;
    }
  }



  if(fabs(eff[xc] - perc) > fabs(eff[xc - 1] - perc) ){
    X_val = cutV[xc -1 ];

  }else{
    X_val = cutV[xc ];

  }
  */

  double Usl   = 0;
  double Ustom = 0;
  double err_1 = 0;
  double Dsl   = 0;
  double Dstom = 0;
  double err_2 = 0;
  if(up != -99  ){
    if(err_up[up] > 0.0 && err_up[up-1] > 0.0 && (cutV[up] - cutV[up-1]) > 0.0){
      double Usl   = (err_up[up] - err_up[up-1])/(cutV[up] - cutV[up-1]);
      if(fabs(Usl) > 0.0){ 
	double Ustom = err_up[up] - Usl*cutV[up];
	err_1 = (perc - Ustom)/Usl;
      }
    }
  }    
    
  if(down != -99){
    if(err_up[down] > 0.0 && err_down[down-1] > 0.0 && (cutV[down] - cutV[down-1]) > 0.0){
      
      double Dsl   = (err_down[down] - err_down[down-1])/(cutV[down] - cutV[down-1]);
      if( Dsl > 0.0){
	double Dstom = err_down[down] - Dsl*cutV[down];
	err_2 = (perc - Dstom)/Dsl;
      }
    }
  }



  //checking case that the lines do not cross !                                                                                                                                                                                               

  if(up == -99){
    errXL = 0 ; //X_val - 0;                                                                                                                                                                                                                  


    //   errXL = X_val - h1->GetXaxis()->GetBinCenter(1);                                                                                                                                                                                     
  }else{
    errXL = X_val - err_1;
  }

  if(down == -99){

    // errXL = ( h1->GetXaxis()->GetBinCenter(arsize) - X_val );                                                                                                                                                                              
    int dif = 0;
    for(int i = 0; i < arsize; i++){
      if(eff[i] >  0.98){
        dif = i;
        break;
      }
    }
                                                                                                                                                                                                             
    errXH = 200 - X_val;
  }else{
    errXH = err_2 - X_val;
  }


  //Deleting all the dynamical arrays                                                                                                                                                                                                         


  delete[] eff;
  delete[] cutV;

  delete[] eff_err;
  delete[] cutV_err;

  delete[] err_up;
  delete[] err_down;

  // endd:                                                                                                                                                                                                                                    
  // if(h1->GetEntries() == 0)  cout<<"Empty histo"<<endl;                                                                                                                                                                                    

}





void ContourBuilderpv(int bin,double minEta,double maxEta,double & in,double & ein,double & ip,double & eip,double  & ic,double  & eic){

  ostringstream fword; 
  fword << bin;
  string b_name = fword.str();
    string Pngg = "Iso_vsRhoTruePV60_test"+b_name+".png";
   char const *PNGName = Pngg.c_str();
   //   string b_name = fword.str();
   string MacroC = "Iso_vsRhoTruePV60_test"+b_name+".C";
   char const *CMacro = MacroC.c_str();  
   string fou = "Update_ClusterIso_vsRho_test"+b_name+".root";
   char const *outP = fou.c_str();

 //   TTree  *t1;
   //t1->Fill();
  
  //  TFile *f1 = new TFile("../spring16_gjets_25ns.root");");
    TFile *f1 =new TFile ("/nfs_scratch/sacharya/UL_studies/CMSSW_10_6_20/src/PhotonID_2017/Trainner/Trainner_26April/Gjet_merged_pt.root");
    

  //  float rho,phoEta,phoEt,phoPFNeuIso,phoPFChIso,phoPFPhoIso;
    float vtx,vty,vtz,mcvtx,mcvty,mcvtz,rho,ppt,peta,Sie_ie,iso_P,iso_C,iso_N,to_e;
  // int nvtx,phoSeedTime;
     int nvtx,isprmt;
    gStyle->SetOptStat(0);
      TTree *tree = (TTree*)f1->Get("tree");  
      //      TTree *tree = (TTree*)f1->Get("tree")
  //  TTree *tree;
      // TTree  *tree =new TTree("tree","EventTree");
  //list of branches 
  //TBranch *b_ppt;
  //Signal Tree                                                                        
      /*
  tree->SetBranchAddress("PhotonEt",&phoEt);
  tree->SetBranchAddress("PhotonEta",&phoEta);
 tree->SetBranchAddress("NeutronIsolation",&phoPFNeuIso);     
   tree->SetBranchAddress("ChargeIsolation",&phoPFChIso);
  tree->SetBranchAddress("PhotonIsolation",&phoPFPhoIso);
  tree->SetBranchAddress("gedPhisPrompt",&phoSeedTime);

  //  tree->SetBranchAddress("gedPhisPrompt",&isprmt);
  tree->SetBranchAddress("rho",&rho);
      */

      //Signal Tree                                                                        
      tree->SetBranchAddress("gedPhPt",&ppt);
      tree->SetBranchAddress("gedPhEta",&peta);
      tree->SetBranchAddress("gedNeuIso",&iso_N);
      tree->SetBranchAddress("gedChgIso",&iso_C);
      tree->SetBranchAddress("gedPhoIso",&iso_P);
      tree->SetBranchAddress("gedPhisPrompt",&isprmt);
      tree->SetBranchAddress("Rh",&rho);



      TH2F *isoNrho = new TH2F("isoNrho","Iso neutral hadrons vs #rho",60,0,60,2000,0,200);
      TH2F *isoPrho = new TH2F("isoPrho","Iso Photon vs #rho",60,0,60,2000,0,200);
      TH2F *isoCrho = new TH2F("isoCrho","Iso Charge hadrons vs #rho",60,0,60,2000,0,200);
      

      /*      TH2F *isoNrho = new TH2F("isoNrho","Iso neutral hadrons vs #rho",30,0,30,2000,0,200);
      TH2F *isoPrho = new TH2F("isoPrho","Iso Photon vs #rho",30,0,30,2000,0,200);
      TH2F *isoCrho = new TH2F("isoCrho","Iso Charge hadrons vs #rho",30,0,30,2000,0,200);
      */
 //  cout<<"thgis is my name"<<endl;
  int ntot,nPV;
  ntot=nPV=0;
  Float_t nentries = (Float_t)tree->GetEntries(); 
  //   cout<<"tree is "<<tree->GetEntries()<<endl;
  cout<<"tree is " <<nentries <<endl;
  //        for(int i  = 0; i <nentries;i++){
  //    for(int i  = 0; i < 80000000;i++){
  //    for(int i  = 0; i < 80500000;i++){
    for(int i  = 0; i < 82500000;i++){

  //  for(int i  = 0; i < 82571736;i++){
    tree->GetEntry(i);
    if( i % 100000 == 0) cout<<"i"<<100*(1.0*i/(1.0*nentries))<<endl;
    //  cout<<"coming here"<<endl;
  
    /*        if(fabs(phoEta) > maxEta ) continue;
	//cout<<"come again"<<endl;
    if(phoSeedTime == 0 ) continue;

    if(fabs(phoEta) < minEta ) continue;
    if(phoEt < 15 ) continue;
    if(phoEt > 200 ) continue;

    cout<<"Photon Et is "<<phoEt<<endl;  
   
    isoNrho->Fill(rho,phoPFNeuIso);
    isoPrho->Fill(rho,phoPFPhoIso);
    isoCrho->Fill(rho,phoPFChIso);
    */

    if(fabs(peta) > maxEta ) continue;
    if(isprmt == 0 ) continue;
    if(fabs(peta) < minEta ) continue;
    //        if(ppt < 15 ) continue;
    if(ppt < 200 ) continue;
    if (ppt<200){
    //if(ppt > 15 ) continue;
    //    if(ppt < 200 ) continue;
      cout<<"after 200 " <<nentries <<endl;
}
    ntot++;
    if(fabs(mcvtz - vtz) >= 0.1)continue;
    if(fabs( sqrt( pow(mcvtx-vtx,2) +  pow(mcvty-vty,2) ) ) >= 0.2 ) continue;
    nPV++;
   
    isoNrho->Fill(rho,iso_N);
    isoPrho->Fill(rho,iso_P);
    isoCrho->Fill(rho,iso_C);
  }
  //if(fabs(peta) > maxEta ) continue;
   cout<<"Pt Value "<<ppt<<endl;
   cout<<"Neutron Isolation"<<iso_N<<endl;
  
//cout<<"rho is "<<rho<<endl;
  //  cout<<"photon isolation"<phoPFPhoIso<<endl; 
  //cout<<"tree is "<<tree->GetEntry()<<endl;
  // cout<<"Charge Isolation is"<<phoPFChIso<<endl;
  cout<<"Builded the 2d HISTOGRAM"<<endl;
  TH2F *hisN =(TH2F*) isoNrho->Clone();
  TH2F *hisP = (TH2F*)isoPrho->Clone();
  TH2F *hisC = (TH2F*)isoCrho->Clone();
  int dim = hisN->GetXaxis()->GetNbins(); 

  cout<<"ENTRIS PER HISTO GAM TON HISTO TOU"<<endl;
  cout<<hisN->GetEntries()<<endl;
  cout<<hisP->GetEntries()<<endl;
  cout<<hisC->GetEntries()<<endl;
  cout<<"dim"<<dim<<endl;



  double * cutVn; 
  double * errVHn; 
  double * errVLn; 
  double * bincn; 
  double * bincerHn; 
  double * bincerLn; 

  double * cutVp; 
  double * errVHp; 
  double * errVLp; 
  double * bincp; 
  double * bincerHp; 
  double * bincerLp; 

  double * cutVc; 
  double * errVHc; 
  double * errVLc; 
  double * bincc; 
  double * bincerHc; 
  double * bincerLc; 

  cutVp  = new double[dim];
  errVHp  = new double[dim];
  errVLp  = new double[dim];
  bincp  = new double[dim]; 
  bincerHp= new double[dim];
  bincerLp= new double[dim];

  
  cutVc  = new double[dim];
  errVHc  = new double[dim];
  errVLc  = new double[dim];
  bincc  = new double[dim]; 
  bincerHc= new double[dim];
  bincerLc= new double[dim];



  cutVn  = new double[dim];
  errVHn  = new double[dim];
  errVLn  = new double[dim];
  bincn  = new double[dim]; 
  bincerHn= new double[dim];
  bincerLn= new double[dim];


  
  for(int i  = 1; i <= dim ; i++){
    double xval = 0; 
    double errXH = 0; 
    double errXL = 0; 
    
   TH1D *r21 = hisN->ProjectionY(" ",i,i+1," ");
   TH1F *h1 =(TH1F*) r21->Clone();
   cout<<"r21"<<" "<<r21->GetEntries()<<endl;
   cout <<"h1"<<" "<<h1->GetEntries()<<endl;

   //    if(h1->GetEntries() > 10000 ) ErrCalc(h1,i,0.90,xval,errXL,errXH);
    if(h1->GetEntries() > 0 ) ErrCalc(h1,i,0.90,xval,errXL,errXH);
    cout<<"bin :"<<i<<" "<<xval<<"- "<<errXL<<"+ " << errXH<<endl;
    cutVn[i-1]   = xval; 
    errVLn[i-1]   = errXL; 
    errVHn[i-1]   = errXH;
    bincn[i-1] = hisN->GetXaxis()->GetBinCenter(i);
    bincerLn[i-1] = 0.0;
    bincerHn[i-1] = 0.0;
    
    xval = 0; 
    errXH = 0; 
    errXL = 0; 
    cout<<"bincn"<<" "<<bincn<<endl;    

   TH1D *r22 = hisP->ProjectionY(" ",i,i+1," ");
   TH1F *h2 =(TH1F*) r22->Clone();
    if( h2->GetEntries() > 0) ErrCalc(h2,i,0.90,xval,errXL,errXH);
    cout<<"r22 is "<<r22<<endl;
      cout<<"H2 entries"<<h2->GetEntries()<<endl;   
    cout<<"bin :"<<i<<" "<<xval<<"-"<<errXL<<"+ " << errXH<<endl;

    cutVp[i-1]   = xval; 
    errVLp[i-1]   = errXL; 
    errVHp[i-1]   = errXH;
    bincp[i-1] = hisP->GetXaxis()->GetBinCenter(i);
    bincerLp[i-1] = 0.0;
    bincerHp[i-1] = 0.0;

    xval = 0; 
    errXH = 0; 
    errXL = 0; 
    cout<<"bincp"<<" "<<bincp<<endl;

    TH1D *r23 = hisC->ProjectionY(" ",i,i+1," ");
    TH1F *h3 =(TH1F*) r23->Clone();
    //    if(  h3->GetEntries() > 0)ErrCalc(h3,i,0.90,xval,errXL,errXH);
    if(  h3->GetEntries() > 0)ErrCalc(h3,i,0.70,xval,errXL,errXH);   //egamma recommendation
    cout <<"h3"<<" "<<h3->GetEntries()<<endl;

    cout<<"bin :"<<i<<" "<<xval<<"-"<<errXL<<"+ " << errXH<<endl;
    cutVc[i-1]   = xval; 
    errVLc[i-1]   = errXL; 
    errVHc[i-1]   = errXH;
    bincc[i-1] = hisC->GetXaxis()->GetBinCenter(i);
    bincerLc[i-1] = 0.0;
    bincerHc[i-1] = 0.0;
    cout<<"bincc"<<" "<<bincc<<endl;


  }
  


  TGraphAsymmErrors * IsoNvsrho = new TGraphAsymmErrors(dim,bincn,cutVn,bincerLn,bincerHn,errVLn,errVHn);
  TGraphAsymmErrors * IsoPvsrho = new TGraphAsymmErrors(dim,bincp,cutVp,bincerLp,bincerHp,errVLp,errVHp);
  TGraphAsymmErrors * IsoCvsrho = new TGraphAsymmErrors(dim,bincc,cutVc,bincerLc,bincerHc,errVLc,errVHc);
  
  //      TF1 *fnn = new TF1("fnn","[0]*x + [1]",1,60);
    TF1 *fnn = new TF1("fnn","[0]*x + [1]",10,60);
      TF1 *fnp = new TF1("fnp","[0]*x + [1]",10,60);
      //  TF1 *fnp = new TF1("fnp","[0]*x + [1]",1,60);
 
 TF1 *fnc = new TF1("fnc","[0]*x + [1]",10,50);
 
  /* TF1 *fnn = new TF1("fnn","[0]*x + [1]",1,30);
  TF1 *fnp = new TF1("fnp","[0]*x + [1]",1,30);
  TF1 *fnc = new TF1("fnc","[0]*x + [1]",1,30);
  */
  IsoNvsrho->Fit("fnn","R");
  IsoPvsrho->Fit("fnp","R");
  IsoCvsrho->Fit("fnc","R");

  in = fnn->GetParameter(0);
  ip = fnp->GetParameter(0);
  ic = fnc->GetParameter(0);
  cout<<"in"<<in<<endl;  
  ein = fnn->GetParError(0);
  eip = fnp->GetParError(0);
  eic = fnc->GetParError(0);

  gStyle->SetOptFit(1);
  TCanvas *c3 = new TCanvas("c3","Iso vs Pt",1200,400);
  c3->Divide(3,1);
  c3->cd(1);
  IsoNvsrho->SetMarkerStyle(24); 
  IsoNvsrho->SetMarkerSize(0.4);
  IsoNvsrho->Draw("AP");
  IsoNvsrho->GetXaxis()->SetTitle("#rho");
  IsoNvsrho->GetYaxis()->SetTitle("Neutral Isolation 90% Contour ");

  c3->cd(2); 
  IsoPvsrho->SetMarkerStyle(24); 
  IsoPvsrho->SetMarkerSize(0.4);
  IsoPvsrho->Draw("AP");
  IsoPvsrho->GetXaxis()->SetTitle("#rho");
  IsoPvsrho->GetYaxis()->SetTitle("Photon Isolation 90% Contour ");
  
  c3->cd(3); 
  IsoCvsrho->SetMarkerStyle(24); 
  IsoCvsrho->SetMarkerSize(0.4);
  IsoCvsrho->Draw("AP");
  IsoCvsrho->GetXaxis()->SetTitle("#rho");
  IsoCvsrho->GetYaxis()->SetTitle("Worst Charge Isolation 70% Contour ");
  
  c3->SaveAs(PNGName);
  c3->SaveAs(CMacro);
  TFile *fout =new TFile("output_ContourBuilder.root","recreate");
  //  TFile *fout =new TFile("outP");                                                                                                                                    
  fout->cd();
  IsoNvsrho->Write();
  IsoPvsrho->Write();
  IsoCvsrho->Write();
  fout->Close();

}


