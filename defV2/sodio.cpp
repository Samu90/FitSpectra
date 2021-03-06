#include "iostream"
#include "string"
#include "TH1.h"
#include "TString.h"
#include "TFile.h"
#include "TTree.h"
#include "string"
#include "TF1.h"
#include "TCanvas.h"


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
  
    TF1* spectrum = new TF1("SpectrumFit","[0] * exp(-( x-[1] )*( x-[1] )/( 2* [2]* [2]))  +  [3] * exp(-( x-[4] )*( x-[4] )/( 2* [5]* [5]))  +  [6] / (exp((x - [7]) * [8]) + 1)  +  [9] / (exp((x - [10]) * [11]) + 1)  +                    [12] * exp(-(x*[13]-[14]))",20,88);

  //gauss1+ gauss2+ fd1+ fd2+ bkg1/2
  
  spectrum->SetParLimits(0,600000,750000);
  spectrum->SetParLimits(1,36,44);
  spectrum->SetParLimits(2,0,6);
  
  spectrum->SetParLimits(3,20000,60000);
  spectrum->SetParLimits(4,80,84);
  spectrum->SetParLimits(5,2,10);

  spectrum->SetParLimits(6,40000,80000); //altezza FermiDirac
  spectrum->SetParLimits(7,65,75); //punto inversione
  
  spectrum->SetParLimits(12,10000,1000000);
  spectrum->SetParLimits(13,1,5);
  

  
  sourceHisto->Fit("SpectrumFit","R");
  




  //canvSource->SaveAs(("HistoSource"+Source+".png").c_str());
  //canvSource->SaveAs(("HistoSource"+Source+".pdf").c_str());

  
  
}
