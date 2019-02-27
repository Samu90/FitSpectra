#include "iostream"
#include "string"
#include "TH1.h"
#include "TString.h"
#include "TFile.h"
#include "TTree.h"
#include "string"
#include "TF1.h"
#include "TCanvas.h"
#include "TStyle.h"

void Analysis(string FName, string Source){

   
  TFile* f_Source = TFile::Open(("../"+FName).c_str());
  TFile* output = TFile::Open("HistoRes","RECREATE");

  TTree* dataSource = (TTree*)f_Source->Get("data");
  
  Float_t eSource;
  UShort_t SourceChId;
  
  dataSource->SetBranchAddress("energy",&eSource);
  dataSource->SetBranchAddress("channelID",&SourceChId);
  
  TH1D* sourceHisto = new TH1D(("HistoSource"+Source).c_str(),("HistoSource"+Source).c_str(),600,0,600);
  
  for(int i=0;i<dataSource->GetEntries();i++){
    dataSource->GetEntry(i);
    if(SourceChId==315)sourceHisto->Fill(eSource-180);
  }
  
  TCanvas* canvSource = new TCanvas(("SourceCanvas"+Source).c_str(),("SourceCanvas"+Source).c_str(),1200,800);
  
  sourceHisto->GetXaxis()->SetRangeUser(0,100);
  canvSource->cd();
  sourceHisto->Draw();
  
  gStyle->SetOptFit(1000);
  
    TF1* spectrum = new TF1("SpectrumFit","[0] * exp(-( x-[1] )*( x-[1] )/( 2* [2]* [2]))  +  [3] * exp(-( x-[4] )*( x-[4] )/( 2* [5]* [5]))  +  [6] / (exp((x - [7]) * [8]) + 1)  +  [9] / (exp((x - [10]) * [11]) + 1)  +                    [12] * exp(-(x*[13]-[14]))",21,88);

  //gauss1+ gauss2+ fd1+ fd2+ bkg1/2
  
  spectrum->SetParLimits(0,500000,750000);
  spectrum->SetParLimits(1,36,44);
  spectrum->SetParLimits(2,2,6);
  
  spectrum->SetParLimits(3,40000,60000);
  spectrum->SetParLimits(4,78,83);
  spectrum->SetParLimits(5,2,5);

  spectrum->SetParLimits(6,40000,80000); //altezza FermiDirac
  spectrum->SetParLimits(7,70,75); //punto inversione
  spectrum->SetParLimits(8,0.55,1.1); //flesso fermi dirac

  
  
  spectrum->SetParLimits(12,5e-05,0.00051);
  spectrum->SetParLimits(13,0.0001,0.27); 
  spectrum->SetParLimits(14,0.1,40); //24


  spectrum->SetParameter(2,2.78);
 
  spectrum->SetParameter(12,0.00025);
  spectrum->SetParameter(13,0.12374);
  spectrum->SetParameter(14,24.25);
  

  
  sourceHisto->Fit("SpectrumFit","R");
  




  //canvSource->SaveAs(("HistoSource"+Source+".png").c_str());
  //canvSource->SaveAs(("HistoSource"+Source+".pdf").c_str());

  
  
}
