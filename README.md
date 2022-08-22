# photonID
it consist of script for developing the PhotonID
First make the root files from Your sample area
do makeclass on it to produce the .C and .h file 

After editing the  .C and .h file 
e.g ID.C and ID.h file here 
we compile the code using ./rootcom 
e.g 
./rootcom ID all
after that we submitted for all sample in the submit.sh 
./all sample_location outputrootfile -1 10000 evenweight 




one such sample is below 
./all /hdfs/store/user/sdogra/Summer20ULMiniAOD_Dec2021/2017_v2/Summer20UL2017_MiniAODv2/GJet_Pt-20to40_DoubleEMEnriched_MGG-80toInf_TuneCP5_13TeV_Pythia8/crab_job_GJet_Pt_40toInf_DoubleEMEnriched_MGG_80toInf/220129_023313/0000/ Gj20to40.root -1 10000 0.278082004

after submitting the sample we get the two pt sample root files with 40toInf.root and 20Toinf.root and one flat_pt root file with flat_PT_15_6000 sample 

the pt bin samples are merged into one using hadd command 
e.g 
hadd merged_pt.root 40toInf.root 20Toinf.root
1st step completed 
............................................................
2nd step  
after obtaining these root files 
we took merged pt sample and evaluate the EA 
We used merged pt root file as an input to contourbuilderpv.C 
fitted the isolation vs rho curve with staright line to obatin the Effective area 
EA is obtain to maintain the flat pileup dependency
for compiling we have to use root -l -b runCont.C 

after ensuring all input files and fitted range are correct
("I fitted them by downloading the .C files produced and thus obtaining the EA ") 
........................................................................
3rd Step 
 copy the flat_pt root file and do makeclass on it to produce Cut_ID.C and Cut_ID.h 
include the EA.txt in runparse.C
do root -l -b runparse.C to obtain root files for barrel and endcap 
In the scaling directory There are two script Ex_neu.C and Ex_pho.C 
The above obatined root files are used as an input to Ex_neu.C and Ex_pho.C to obatian the pt scaling values respectively for barrel and endcap input files 
("we could also obtain the .C files after running root -l -b Ex-neu.C an Ex_pho.C and fitted it locally with diffrenet range to obatian scaling values")
...........................................................................

4th step 

Repeat the 3rd step but this time with mergedpt sample to obtain the two root files one for Barrel and endcap (dont go to scaling directory)

make a directory for barrel and endcap  both have same script only input file is changed 

inside the TMVA directory 
compute root -l -b Scr99.C to obtain 99per.txt file for the given input file(Barrel and endcap root file produced above)
make sure to put the pt scaling value obtained in the 3rd step for both neutral isolation and photon isolation 

after that use this file as an input to Reg.C file along with the input root file  and isoltion scaling value 
root -l -b Reg.C
This will generate xml file in the weight directory and a root file 
with the xml file in the input in the Reader_neu.C we can obtain the 90% txt file by computing root -l -b Reader_neu.C 
the corresponding 80% and 70% efficiency could be chosen from the xml file obtained above 

for endcap similar process is repeated 

5th step  
Inside TMVA their is a plot folder 
using the text file for loose medium and tight and the input  root file w ecan obtain the efficiency plots 
root -l -b PlotBuilder.C 

and efficiency will computed using the 
root -l -b Calculator.C with these txt files
