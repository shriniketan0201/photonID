#include <stdlib.h>
#include <TSystem.h>
#include <iostream>
#include <fstream>

#include "CutID.C"
//#include "tdrstyle.C"
//#include "Variables.C"
using namespace std;
  void run_ParseEAs(){
  //-----------------Macro Describtion----------------------------------------------------------
  //
  // This macro wraps the whole procedure in a single shell. 
  // Initialy it caluclates the effective areas -macros (AreaCalc.C + Fitter.C) 
  // and then feed them in a Tree Maker, that makes a Tree with the variables of interest 
  // separated to background/signal and weight based on the pt, for possible MVA techinques 
  // and to derive the cuts. 
  // This file to run, needs the full construction of the CUTID class and also the extra macros
  // for each of the specified process. 
  //
  //--------------------------------------------------------------------------------------------
    //             gSystem->CompileMacro("CutID.C");
   //CutID();
    //  TSystem::CompileMacro:int i = gSystem->CompileMacro("CutID.C","k");  
    //    gROOT->processLine("gSystem->CompileMacro(\"CutID.C\",\"k\"); >& build.log");
    //    gROOT->ProcessLine(".L CutID.C");
    //    gSystem->CompileMacro("/afs/hep.wisc.edu/home/sacharya/photonID/GJets/CMSSW_10_2_18/src/gJets/merged/ALLPV/PF/isopt/Isopt/CutID.C");    
    //    if (gSystem->AccessPathName("MC_GJets_HT40-100_350.root"))
    //{   gROOT->ProcessLine(".x CutID.C");
    //} 
    //    gROOT ->ProcessLine(".L CutID.C");
    CutID t; 
    //   cout<<" tree t  :"<<t<<endl;  
  // here you declare the number of eta  bins 
  double Fin[5][3]= {0};


     ifstream myfile; 
     //    myfile.open("../EAS/EA.txt");

     //    myfile.open("../../Eas/EA_1_60_AllPV.txt");
    myfile.open("EA_1_60_TruePV_Fitting_locally.txt");
  // above two lines i have blocke djust to try following code 
   
  //  ifstream myfile("EA.txt");     //open file 

  cout<<"------------------------------------------------------------"<<endl;
  cout<<"                   Reading the EAS "<<endl;
  cout<<"-----------------------------------------------------------"<<endl;

  
  int i = 0; 
  if(myfile.is_open()){   // blocked this line for try
 while(!myfile.eof()) {//blocked this line as well
    
      double iC,iN,iP;      
      myfile>>iC>>iN>>iP;
      //            while(!myfile.eof()){    
      Fin[i][0] = iC; 
      Fin[i][1] = iN; 
      Fin[i][2] = iP; 




      cout<<i<<" "<<iC<<" "<<iN<<" "<<iP<<endl;
            i++;
      if( i > 4) goto conti; 

       }
  }

 conti:
  
  cout<<"----------------------Barrel--------------"<<endl;
  t.CutBasedID(1,Fin);
  cout<<"----------------------End Cap--------------"<<endl;
  t.CutBasedID(2,Fin);
 
  /* cout<<"----------------------Barrel-0<eta<0.5-------------"<<endl;
  t.CutBasedID(1,Fin);
  cout<<"----------------------Barrel---0.5<eta<1.0-----------"<<endl;
  t.CutBasedID(2,Fin);
  cout<<"----------------------Barrel---1.0<eta<1.4442-----------"<<endl;
  t.CutBasedID(3,Fin);
  cout<<"----------------------Endcap 1.566 <eta<2.0--------------"<<endl;
  t.CutBasedID(4,Fin);
  cout<<"----------------------Endcap--2.0<eta<2.5------------"<<endl;
  t.CutBasedID(5,Fin);
  */
  cout<<"..................End of Programme............"<<endl;



  myfile.close();
  return 0;
  

}


