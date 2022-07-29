#include <TFile.h>
#include <cstdlib>
#include <TH1F.h>

void Plots()
{
  TFile *f1 = new TFile("Gjet_merged_pt.root");
  TCanvas *c1 = new TCanvas("c1","NVtx",800,840);
  c1->SetBorderSize(2);
  c1->SetLeftMargin(0.15);
  auto legend = new TLegend(0.5, 0.6, .7, .9);
  gStyle->SetOptStat(kTRUE);
  TTree *t1= (TTree*)f1->Get("tree");
  // TH1F *h1 = new TH1F("NVtx","Nvtx",20,0,200);  
  //  h1->Fill("NVtx","Rh");
  // h1->Draw();

  //  t1->GetXaxis()->SetUserRange(0,50);
    t1->Draw("NVtx");
    //  t1->Draw("Rh");
    // c1->SaveAs("Rh.png");
    c1->SaveAs("NVtx.png");
}
