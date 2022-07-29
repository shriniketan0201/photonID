#define ID_cxx
#include "ID.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TChain.h>
#include <TFile.h>
#include <iomanip>
#include <cstdlib>
#include <iostream>
#include <TMath.h>
#include <vector>
#include <TVector3.h>
#include <TProfile.h>
#include "TStopwatch.h"
#include <algorithm>
#include "TROOT.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>

using namespace std;


int main(int argc, const char *argv[]){
  gROOT->ProcessLine("#include <vector>");

  string outfile = argv[2];
  long int nTotEvt = atof(argv[3]);
  //std::cout<<"r a valid value for maxEvents (parameter 3)."<<std          ::endl;                                                                                                                                                          
  long int nPrintEvt = atof(argv[4]);
  double evtWt = atof(argv[5]);
  ID m(argv[1],argv[2]);
  m.Loop(outfile,nTotEvt,nPrintEvt,evtWt);
  //return 0;                                                                                                                                                                                                                                

}

  void ID::Loop(string outputfile, int ntotEvent, int nPrintEvent, double evtWeight)
  {
    TStopwatch sw;
    sw.Start();

    cout<<"Output file : " << outputfile << endl;
    char *outfilename = const_cast<char*>(outputfile.c_str());
    fileName = new TFile(outfilename,"RECREATE");
    tree = new TTree("tree","EventsTree");
    TH1D *MatchPhos = new TH1D("MatchPhos","# of matched photons in event",5,0,5);

    
    float  Vtx,Vty,Vtz,MCVtx,MCVty,MCVtz,gedPhR9,gedPhEta,gedPhSCEta,gedPhPt,gedPhPhi,gedPhoIso,gedChgIso,gedNeuIso,gedPhTower,gedPhSieie,Rh,gedGenPt,gedPhweightXS,PhCITKChIso,PhCITKNeuIso,PhCITKPhoIso,PhPUPPIChIso,PhPUPPINeuIso,PhPUPPIPhoIso,gedPhIDMVA;
  int gedPhPixSeed,NVtx,gedPhisPrompt,hascorrectPrimV,gedPhEleVeto;

    fileName->cd();

    //Float Branches                                                                                                                                                    

    tree->Branch("Vtx",&Vtx,"Vtx/F");
 tree->Branch("Vty",&Vty,"Vty/F");
 tree->Branch("Vtz",&Vtz,"Vtz/F");
 tree->Branch("MCVtx",&MCVtx,"MCVtx/F");
 tree->Branch("MCVty",&MCVty,"MCVty/F");
 tree->Branch("MCVtz",&MCVtz,"MCVtz/F");
 tree->Branch("gedPhR9",&gedPhR9,"gedPhR9/F");
 tree->Branch("Rh",&Rh,"Rh/F");
 tree->Branch("gedPhEta",&gedPhEta,"gedPhEta/F");
 tree->Branch("gedPhPhi",&gedPhPhi,"gedPhPhi/F");
 tree->Branch("gedPhPt",&gedPhPt,"gedPhPt/F");
 tree->Branch("gedPhSieie",&gedPhSieie,"gedPhSieie/F");
 tree->Branch("gedPhTower",&gedPhTower,"gedPhTower/F");
 tree->Branch("gedPhoIso",&gedPhoIso,"gedPhoIso/F");
 tree->Branch("gedChgIso",&gedChgIso,"gedChgIso/F");
 tree->Branch("gedNeuIso",&gedNeuIso,"gedNeuIso/F");
 tree->Branch("gedPhSCEta",&gedPhSCEta,"gedPhSCEta/F");
 tree->Branch("gedGenPt",&gedGenPt,"gedGenPt/F");
 tree->Branch("gedPhweightXS",&gedPhweightXS,"gedPhweightXS/F");
 tree->Branch("PhCITKChIso",&PhCITKChIso,"PhCITKChIso/F");
 tree->Branch("PhCITKNeuIso",&PhCITKNeuIso,"PhCITKNeuIso/F");
 tree->Branch("PhCITKPhoIso",&PhCITKPhoIso,"PhCITKPhoIso/F");
 tree->Branch("PhPUPPIChIso",&PhPUPPIChIso,"PhPUPPIChIso/F");
 tree->Branch("PhPUPPINeuIso",&PhPUPPINeuIso,"PhPUPPINeuIso/F");
 tree->Branch("PhPUPPIPhoIso",&PhPUPPIPhoIso,"PhPUPPIPhoIso/F");
 tree->Branch("gedPhIDMVA",&gedPhIDMVA,"gedPhIDMVA/F");
 
 tree->Branch("NVtx",&NVtx,"NVtx/I");
 tree->Branch("gedPhPixSeed",&gedPhPixSeed,"gedPhPixSeed/I");
 tree->Branch("gedPhisPrompt",&gedPhisPrompt,"gedPhisPrompt/I");
 tree->Branch("hascorrectPrimV",&hascorrectPrimV,"hascorrectPrimV/I");
 tree->Branch("gedPhEleVeto",&gedPhEleVeto,"gedPhEleVeto/I");
 if (fChain == 0) return;
 Long64_t nentries = fChain->GetEntries();

 Long64_t nbytes = 0, nb = 0;
 double weightt1 = evtWeight;
 cout<<"weight of  this sample "<<weightt1<<endl;
 cout<<"total entries:"<<nentries<<endl;

 cout<<"nPrintevents"<<nPrintEvent<<" "<<ntotEvent<<endl;
 Long64_t nentriesToCheck = nentries;
 //   if (ntotEvent >= 0) nentries = ntotEvent;                                                                                                                                                                                             
 if (ntotEvent != -1LL && nentries > ntotEvent)nentriesToCheck = ntotEvent;

 for (Long64_t jentry=0; jentry<nentriesToCheck;jentry++) {
   Long64_t ientry = LoadTree(jentry);
   if (ientry < 0) break;
   nb = fChain->GetEntry(jentry);   nbytes += nb;
   // if (Cut(ientry) < 0) continue;                                                                                                                                                                                                         

   //      for (Long64_t jentry=0; jentry<nentries;jentry++) {                                                                                                                                                                               
   //        Long64_t ientry = LoadTree(jentry);                                                                                                                                                                                             
   //if (ientry < 0) break;                                                                                                                                                                                                                  
   //nb = fChain->GetEntry(jentry);   nbytes += nb;                                                                                                                                                                                          

   if (jentry % nPrintEvent == 0) std::cout << "  " << jentry  << "  Events Processed... " << std::endl;
   int mPHOS = 0;
   int mto1st = 0;

   Vtx= vtxX;
   Vty=vtxY;
   Vtz=vtxZ;

   MCVtx=(*mcVtx)[0];
   MCVty=(*mcVty)[0];
   MCVtz=(*mcVtz)[0];
   //      cout<<"(*phoEt).size()"<<(*phoEt).size()<<endl;                                                                                                                                                                                   
   //      if ((*phoEt).size()==0)cout<<"(*phoEt).size()"<<(*phoEt).size()<<" jentry "<<jentry<<endl;                                                                                                                                        
   if ((*phoEt).size()<0) continue;

   for(int ipho = 0; ipho < (*phoEt).size(); ipho++){
     double pEta = (*phoEta)[ipho];
     double pPhi = (*phoPhi)[ipho];
     Rh = rho;

     NVtx = nVtx;
     gedPhEleVeto = (*phoEleVeto)[ipho];
     //    gedPhR9 = (*phoR9)[ipho];                                                                                                                                                                                                         
     gedPhR9 =(*phoR9Full5x5)[ipho];
     gedPhPt = (*phoEt)[ipho];
     gedPhEta = pEta;
     gedPhSCEta = (*phoSCEta)[ipho];                                                                                                                                         gedPhPhi = pPhi;
     //gedPhPhi = phoPhi;                                                                                                                                                
     gedPhSieie = (*phoSigmaIEtaIEtaFull5x5)[ipho];
     gedPhTower = (*phoHoverE)[ipho];
     gedPhoIso = (*phoPFPhoIso)[ipho];
     gedChgIso = (*phoPFChWorstIso)[ipho];
     gedNeuIso = (*phoPFNeuIso)[ipho];
     gedPhPixSeed  = (*phohasPixelSeed)[ipho];
     gedPhweightXS = weightt1;
     gedPhIDMVA = (*phoIDMVA)[ipho];

     int pass = 0;
     int HLTPhoIsPrescaled = 0;                                                                                                                                                                                                         \

     //int phoispr=0;                                                                                                                                                                                                                        
     double genPt = -1;
     //      std::cout << " gEdph  " << gedPhIDMVA << " ... " << std::endl;                                                                                                                                                                  
     for(int imc = 0; imc < (*mcPID).size(); imc++){
              if((*mcPt)[imc] < 15 ) continue;
       
       if((*mcStatus)[imc] != 1)continue;
       if((*mcPID)[imc] != 22)continue;
       //if(TMath::Abs((*mcMomPID)[imc]) >  21 )continue;                                                                                                                                                                                    
       pass++;
       double meta = (*mcEta)[imc];
       double mphi = (*mcPhi)[imc];
       TVector3 mcphoton;
       TVector3 recoPHOTOn;
       mcphoton.SetPtEtaPhi(1.0,meta,mphi);
       recoPHOTOn.SetPtEtaPhi(1.0,pEta,pPhi);
       double DR = mcphoton.DrEtaPhi(recoPHOTOn);
       double dp = fabs((*mcPt)[imc] - (*phoEt)[ipho] )/(*mcPt)[imc];
       if(DR < 0.2 && dp < 0.2  ){
	 mPHOS++;
	 if(pass == 1 ){
	   genPt = (*mcPt)[imc];
	   HLTPhoIsPrescaled= 1;
	 }
       }
     }//EOF MC Particles loop                                                                                                                                           

     gedPhisPrompt = HLTPhoIsPrescaled;
     gedGenPt = genPt;
     tree->Fill();
   }//EOF Photon Loop                                                                                                                                                   

   MatchPhos->Fill(mPHOS);

 }//EOF EVENT LOOP                                                                                                                                                      

 MatchPhos->Write();
 //t1->Write();                                                                                                                                                         

                                                                     
 //      fileName->Close();                                                                                                                                           
                                                                       

 cout<<outputfile<< " created ...."<<endl;

 sw.Stop();
 std::cout << "RealTime : " << sw.RealTime() / 60.0 << " minutes" << std::endl;
 std::cout << "CPUTime  : " << sw.CpuTime()  / 60.0 << " minutes" << std::endl;

  }
  void ID::histograms(const char* file2)
  {
    fileName = new TFile(file2, "RECREATE");
    fileName->cd();
  }



