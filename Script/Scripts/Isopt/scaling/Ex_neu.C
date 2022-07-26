#include <TMath.h>
#include <cstdlib>
#include <TRandom.h>
#include <TGraph.h>
#include "vector"
#include <new>
#include "sstream"
#include <string>
#include <fstream>
#include <iostream>
//#include <ErrCalc.C>
//#include <limits>
void ErrCalc(TH1F *HIST,int binxn,double perc,double & X_val, double & errXL,double & errXH){
  
  // Naming the output 
  /*  ostringstream gn; 
   gn << binxn; 
  string gnm = "Efficiency_CutVal"+gn.str()+".png"; 
  const char *graphname = gnm.c_str();
  //
  */
  //  cout<<binxn<<endl;

  TH1F *h1 = (TH1F*)HIST->Clone();
  int arsize = h1->GetXaxis()->GetNbins(); 
  // cout<<"arsize="<<arsize<<endl;  
  //  if(h1->GetEntries() == 0 ) goto endd; 

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
  float tot_nz = tot - h1->GetBinContent(1); // copied from the barrel one not the original  
  // cout<<"total="<<tot<<endl;
  
  //cout<<"totalnZ="<<tot_nz<<endl;
 int integ = 0; 
  for(int i  = 1; i < (h1->GetXaxis()->GetNbins() + 1); i++){ 
    double xCut = h1->GetXaxis()->GetBinLowEdge(i); 
    integ += h1->GetBinContent(i); 
    //cout<<"Integer="<<integ<<endl;
    //cout<<"xCut="<<xCut<<endl;


    if(integ != 0 && tot != 0 ){ 
      eff[i -1] = (integ*1.0/tot);
            eff_err[i -1] = ((integ*1.0/tot)*sqrt(pow(sqrt(tot)/tot,2) + pow(sqrt(integ)/integ,2) )); 
	    //cout<<"efficiency="<<(integ*1.0/tot)<<endl;
      //      eff_err[i -1] = sqrt ( eff[i-1] * ( 1 - eff[i-1] ) / tot_nz ) ;  
 }
else{
      eff_err[i -1] = 0.0; 
      eff[i -1] = 0.0;
    }
      
    cutV[i -1] = (xCut);
    cutV_err[i - 1] = 0;
    // cout<<"xCut_New="<<xCut<<endl;
    //  cout<<"bin :"<<i<<"  % :"<<integ*1.0/tot<<" cut val :"<<xCut <<endl;
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

  //  c1->SaveAs(graphname);   //it is block but here in barrel file we are opening it

  double * err_up; 
  double * err_down; 

  err_up = new double [arsize];
  err_down = new double [arsize];
        
  for(int i = 0;  i < arsize ; i++){
    
    if( fabs(eff[i]) > 0.00001 && fabs(eff_err[i]) > 0.0001){ // this loop is blocked also in ghe barrel one

      err_up[i] = eff[i] + eff_err[i];
      err_down[i] = eff[i] - eff_err[i];
      

    }
    else{        // this one is also block in barral one 

      
      err_up[i] = 0; 
      err_down[i] = 0; 


    }
    // cout<< "i: "<<i <<" "<<eff[i] <<" "<<err_up[i]<<"  "<<err_down[i]<<endl;
  }
  


  //Extrapolation method to find the CutValue errors
  int up = -99; 
  int down = -99;  
  for( int i  = 0; i < arsize ; i++){
    if( err_up [i] > perc){ up = i; 
      break;
    }
  }
  for( int i  = 0; i < arsize ; i++){
    if( err_down [i] > perc){
      down = i; 
      break;
    }
  }
  //  cout<<"up="<<up <<"down="<<down<<endl;   
  // here it returns the extrapolated result
    
  double Usl   = 0; 
  double Ustom = 0; 
  double err_1 = 0; 
  double Dsl   = 0; 
  double Dstom = 0; 
  double err_2 = 0; 

  if(up != -99  ){
    double Usl   = (err_up[up] - err_up[up-1])/(cutV[up] - cutV[up-1]); 
    double Ustom = err_up[up] - Usl*cutV[up]; 
   
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

  //cout<<"down err:"<<err_1<<endl;
  //cout<<"UP err:"<<err_2<<endl;
  // cout<<"cut value"<<(err_1+err_2)/2.; 
  //cout<<"sym err:"<< (err_2-err_1)/2.;

  int xc = 0; 
   
  for(int i = 0; i < arsize; i++){
    if( eff[i] > perc ){ 
      xc = i; 
      break;
    }
  }
    
   

  if(fabs(eff[xc] - perc) > fabs(eff[xc - 1] - perc) ){
    X_val = cutV[xc -1 ]; 
   
  }else{
    X_val = cutV[xc ];
   
      }
  // cout<<"X_val is"<<X_val<<endl;    
  // X_val = (err_1+err_2)/2.; 

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
    // errXH = (cutV[dif] - X_val );
    errXH = 200 - X_val;


  }else{
    errXH = err_2 - X_val;
  }
  //  cout<<"errXH is"<<errXH<<endl;
  // cout<<"errXL is"<<errXL<<endl;
    


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






void Ex_neu(){

  
  //    TFile  *f1 =  new TFile ("/nfs_scratch/sacharya/monophoton/CMSSW_10_6_20/src/PhotonIDs/merged/ALLPV/Isopt/CutTMVABarrel90update25May_HPT.root");
  //  TFile  *f1 =  new TFile ("/nfs_scratch/sacharya/UL_studies/CMSSW_10_6_20/src/Photon_ID_2018/Isopt/CutTMVABarrelUL.root");
  //  TFile  *f1 =  new TFile ("/nfs_scratch/sacharya/UL_studies/CMSSW_10_6_20/src/Photon_ID_2018/Isopt/CutTMVABarrelUL3.root");
  //  TFile  *f1 =  new TFile ("/nfs_scratch/sacharya/UL_studies/CMSSW_10_6_20/src/Photon_ID_");
  //  TFile  *f1 =  new TFile ("/nfs_scratch/sacharya/UL_studies/CMSSW_10_6_20/src/Photon_ID/egamma_id/Isopt/CutTMVAEndCapUL.root");
  //  TFile  *f1 =  new TFile ("/nfs_scratch/sacharya/UL_studies/CMSSW_10_6_20/src/PhotonID_2017/Iso/CutTMVAEndCapUL.root");
  // TFile  *f1 =  new TFile ("CutTMVABarrelUL1_60.root");
  TFile  *f1 =  new TFile ("CutTMVAEndCapUL1_60_Truepv.root");
  float genPt,ppt,peta,Sie_ie,iso_P,iso_C,iso_N,to_e,weighT;
  int nvtx;
  gStyle->SetOptStat(0);
    TTree *t_S = (TTree*)f1->Get("t_S");
    TTree *t_B = (TTree*)f1->Get("t_B");

  //Signal Tree                                                                         
  //     TTree *t_S = new TTree("t_S","CUT NEEDS THIS  ");
  // TTree *t_B = new TTree("t_B","CUT NEEDS THIS ");
     
     // set Branch Address 


  t_S->SetBranchAddress("Sieie",&Sie_ie);
  t_S->SetBranchAddress("isoP",&iso_P);
  t_S->SetBranchAddress("isoC",&iso_C);
  t_S->SetBranchAddress("isoN",&iso_N);
  t_S->SetBranchAddress("ToE",&to_e);
  t_S->SetBranchAddress("weighT",&weighT);

  t_S->SetBranchAddress("Nvtx",&nvtx);
  t_S->SetBranchAddress("Peta",&peta);
  t_S->SetBranchAddress("Ppt",&ppt);
  t_S->SetBranchAddress("genPt",&genPt);

  //Background Tree                  
  //  TFile *f = new TFile("../../CutTMVABarrel90_HPT.root");
 
  /*  TTree *t_B = (TTree*)f1->Get("t_B");                                     */            
  t_B->SetBranchAddress("Sieie",&Sie_ie);
  t_B->SetBranchAddress("isoP",&iso_P);
  t_B->SetBranchAddress("isoC",&iso_C);
  t_B->SetBranchAddress("isoN",&iso_N);
  t_B->SetBranchAddress("ToE",&to_e);
  t_B->SetBranchAddress("weighT",&weighT);

  t_B->SetBranchAddress("Nvtx",&nvtx);
  t_B->SetBranchAddress("Peta",&peta);
  t_B->SetBranchAddress("Ppt",&ppt);
  
 TH2F *isoPptS = new TH2F("isoPptS","Neutral Isolation vs Pt",250,0,1000,1000,0,100);


  for(int i  = 0; i < t_S->GetEntries();i++){
    t_S->GetEntry(i);

    //    if(ppt < 15 || ppt > 1000) continue;
    if(ppt < 200) continue;
    if(iso_P == 0) continue;

    isoPptS->Fill(ppt,iso_N);

  }

  cout<<"Builded the 2d HISTOGRAM"<<endl;



  TH2F *his2 =(TH2F*) isoPptS->Clone();



  int dim = his2->GetXaxis()->GetNbins(); 
  cout<<"dim"<<dim<<endl;  
  double * cutV; 
  double * errVH; 
  double * errVL; 
  double * binc; 
  double * bincerH; 
  double * bincerL; 
  cutV   = new double[dim];
  errVH   = new double[dim];
  errVL   = new double[dim];
  binc   = new double[dim]; 
  bincerH = new double[dim];
  bincerL = new double[dim];
  
  for(int i  = 1; i < dim ; i++){
    double xval = 0; 
    double errXH = 0; 
    double errXL = 0; 
TH1D * r22 = his2->ProjectionY(" ",i,i+1," ");
    
   TH1F *h1 = (TH1F*)r22->Clone();
     
   cout<<"h1 get entries"<<h1->GetEntries()<<endl; 
    ErrCalc(h1,i,0.900,xval,errXL,errXH);
    // cout<<"h1"<<h1<<endl;    
    cout<<"bin :"<<i<<" "<<xval<<"-"<<errXL<<"+ " << errXH<<endl;
    
    cutV[i-1]   = xval; 
    
    errVL[i-1]   = errXL; 
    errVH[i-1]   = errXH;
    
    binc[i-1]   = his2->GetXaxis()->GetBinCenter(i);
    bincerL[i-1] = 0;
    bincerH[i-1] = 0;
  }
  TGraphAsymmErrors * IsoptScaling = new TGraphAsymmErrors(dim,binc,cutV,bincerL,bincerH,errVL,errVH);
  TGraphAsymmErrors * IsoptScaling2 = new TGraphAsymmErrors(dim,binc,cutV,bincerL,bincerH,errVL,errVH);
  TGraphAsymmErrors * IsoptScalingLin = new TGraphAsymmErrors(dim,binc,cutV,bincerL,bincerH,errVL,errVH);

  // double DownL = his2->GetXaxis()->GetBinCenter(1);
  //double UpperL = his2->GetXaxis()->GetBinCenter(dim);

  //    float a = std::numeric_limits<float>::infinity();  
  // TF1 *fn1 = new TF1("fn1","exp([0]*x + [1])",20,700);
  /*  TF1 *fn1 = new TF1("fn1","exp([0]*x + [1])",200,1000);
  //TF1 *fn2 = new TF1("fn2","[1]*x + [2]*x*x + [0]",20,700);
        TF1 *fn2 = new TF1("fn2","[1]*x + [2]*x*x + [0]",200,1000);
  //      TF1 *fn2 = new TF1("fn2","[1]*x + [2]*x*x + [0]",200,700);
  //  TF1 *fnlin = new TF1("fnlin","[1]*x + [0]",20,700);
  TF1 *fnlin = new TF1("fnlin","[1]*x + [0]",200,1000);

  //  fn2->SetParameters(2,25163e-06);

  //  fn2->SetParameters(2.09584e+00,7.49996e-03,1.64912e-19);
  //  fn2->SetParLimits(0,0.0,3.25915e+00);
  // fn2->SetParLimits(1,0.0,2.71288e-03);
  //           fn2->SetParLimits(2,0.0,2.25163e-06);
  //           fn2->SetParLimits(2,0.0,1.47185e-12);


  IsoptScaling->Fit("fn1","R");
  IsoptScaling2->Fit("fn2","R");
  IsoptScalingLin->Fit("fnlin","R");
  */

  gStyle->SetOptFit(1);
  
  TCanvas *c3 = new TCanvas("c3","Iso Pt",1200,600);
  c3->Divide(2,1);
  
  c3->cd(1);
  IsoptScaling->SetMarkerStyle(24); 
  IsoptScaling->SetMarkerSize(0.4);
  IsoptScaling->Draw("AP");
  IsoptScaling->GetXaxis()->SetTitle("Photon Pt GeVc^{-1}");
  IsoptScaling->GetYaxis()->SetTitle("Neutral Isolation");
  //  IsoptScaling->GetYaxis()->SetRangeUser(0,35.0);
  IsoptScaling->GetXaxis()->SetRangeUser(0,1000);
  c3->cd(2); 
  his2->Draw("colz");
  his2->GetXaxis()->SetTitle("Photon Pt GeVc^{-1}");
  his2->GetYaxis()->SetTitle("Neutral Isolation");
  his2->GetYaxis()->SetRangeUser(0,100);
  c3->SaveAs("exponentialneu60.png");
    c3->SaveAs("exponentialneu60.C");
              //lets fit this graph
  
  TCanvas *c4 = new TCanvas("c4","Iso Pt",1200,600);
  c4->Divide(2,1);
  
  c4->cd(1);
  IsoptScaling2->SetMarkerStyle(24); 
  IsoptScaling2->SetMarkerSize(0.4);
  //  IsoptScaling2->Draw("AP");
  IsoptScaling2->Draw("");
  IsoptScaling2->GetXaxis()->SetTitle("Photon Pt GeVc^{-1}");
  IsoptScaling2->GetYaxis()->SetTitle("Neutral Isolation");
  IsoptScaling2->GetYaxis()->SetRangeUser(0,35.0);
  IsoptScaling2->GetYaxis()->SetRangeUser(0,100);
  c4->cd(2);
  /*  IsoptScalingLin->SetMarkerStyle(24); 
  IsoptScalingLin->SetMarkerSize(0.4);
  IsoptScalingLin->Draw("AP");
  IsoptScalingLin->GetXaxis()->SetTitle("Photon Pt GeVc^{-1}");
  IsoptScalingLin->GetYaxis()->SetTitle("Isolation Contour PF::h0 rho corr.");
  */
  his2->Draw("colz");
  his2->GetXaxis()->SetTitle("Photon Pt GeVc^{-1}");
  his2->GetYaxis()->SetTitle("Neutral Isolation");
  his2->GetYaxis()->SetRangeUser(0,50);
  c4->SaveAs("Quadratic1to60_neu.png");
  c4->SaveAs("Quadratic1to60_neu.C");


  //c4->SaveAs("POl.png");

  TCanvas *c6 = new TCanvas("c6","Iso Pt",1200,600);
  c6->Divide(2,1);  
  c6->cd(1);
  IsoptScalingLin->SetMarkerStyle(24); 
  IsoptScalingLin->SetMarkerSize(0.4);
  IsoptScalingLin->Draw("AP");
  IsoptScalingLin->GetXaxis()->SetTitle("Photon Pt GeVc^{-1}");
  IsoptScalingLin->GetYaxis()->SetTitle("Charge Isolation ");
  //  IsoptScalingLin->GetYaxis()->SetRangeUser(0,35.0);

  c6->cd(2);
  his2->Draw("colz");
  his2->GetXaxis()->SetTitle("Photon Pt GeVc^{-1}");
  his2->GetYaxis()->SetTitle("Charge Isolation");
  //  his2->GetYaxis()->SetRangeUser(0,100);
  c6->SaveAs("Straightline1to60.png");
  c6->SaveAs("Straightline1to60.C");

  TCanvas *c7 = new TCanvas("c7","Iso Pt",1200,600);

  isoPptS->Draw("colz");
  c7->SaveAs("isoPptS_neu.png");

}


