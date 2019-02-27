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

void Analysis(string FName, string Source,string output){

   
  TFile* f_Source = TFile::Open(("../"+FName).c_str());

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
  
    TF1* spectrum = new TF1("SpectrumFit","[0] * exp(-( x-[1] )*( x-[1] )/( 2* [2]* [2])) + [3] / (exp( (x*[4]-(2*[1]*[1]/([1]+2*[1])))) + 1)+ [5] * exp(-( x-[6] )*( x-[6] )/( 2* [7]* [7])) + [8] / (exp( (x*[9]-(2*[6]*[6]/([6]+2*[6])))) + 1)",13,88);

  //gauss1+ gauss2+ fd1+ fd2+ bkg1/2
  
  spectrum->SetParLimits(0,500000,750000);
  spectrum->SetParLimits(1,37,43);
  spectrum->SetParLimits(2,1,5);
  spectrum->SetParLimits(3,200000,750000);
  spectrum->SetParLimits(4,0.6,1.2);
  spectrum->SetParLimits(5,30000,70000);
  spectrum->SetParLimits(6,78,84);
  spectrum->SetParLimits(7,1,5);
  spectrum->SetParLimits(8,37000,60000);
  spectrum->SetParLimits(9,0.6,1.2);
  
 sourceHisto->Fit("SpectrumFit","R");
  

  canvSource->SaveAs(("HistoSource"+Source+output+".png").c_str());
  canvSource->SaveAs(("HistoSource"+Source+output+".pdf").c_str());

  
  
}
