
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
 
  TTree* dataSource = (TTree*)f_Source->Get("data");
  
  Double_t eSource[2];
    
  dataSource->SetBranchAddress("energy",eSource);
  
  
  TH1D* sourceHisto1 = new TH1D(("HistoSourceCoinc1"+Source).c_str(),("HistoSourceCoinc1"+Source).c_str(),600,0,600);
  TH1D* sourceHisto2 = new TH1D(("HistoSourceCoinc2"+Source).c_str(),("HistoSourceCoinc2"+Source).c_str(),600,0,600);
  TH1D* sourceHistoSum = new TH1D(("HistoSourceCoincSum"+Source).c_str(),("HistoSourceCoincSum"+Source).c_str(),600,0,600);
  
  for(int i=0;i<dataSource->GetEntries();i++){
    dataSource->GetEntry(i);
    sourceHisto1->Fill(eSource[0]-235-12);
    sourceHisto2->Fill(eSource[1]-180);
  }

  gStyle->SetOptFit(1111);
  gStyle->SetStatW(0.2);
  gStyle->SetStatH(0.1);
  
  TCanvas* canvSourceCoinc = new TCanvas(("SourceCoincCanvas"+Source).c_str(),("SourceCoincCanvas"+Source).c_str(),1200,800);
  canvSourceCoinc->Divide(2,1);

  sourceHisto1->GetXaxis()->SetRangeUser(0,100);
  sourceHisto2->GetXaxis()->SetRangeUser(0,100);
  canvSourceCoinc->cd(1);
  sourceHisto1->Draw();
  canvSourceCoinc->cd(2);
  sourceHisto2->Draw();
    
  /*   TF1* spectrum = new TF1("SpectrumFit","[0] * exp(-( x-[1] )*( x-[1] )/( 2* [2]* [2]))  +  [3] * exp(-( x-[4] )*( x-[4] )/( 2* [5]* [5]))  +  [6] / (exp((x - [7]) * [8]) + 1)  +  [9] / (exp((x - [10]) * [11]) + 1)  +                    [12] * exp(-(x*[13]-[14]))",21,88);
    */

  TF1* spectrum1 = new TF1("SpectrumFit1","[0] * exp(-( x-[1] )*( x-[1] )/( 2* [2]* [2])) + [3] / (exp( (x-(2*[1]*[1]/(511+2*[1]))) * [4]) + 1)",12,60);

  spectrum1->SetParLimits(0,9000,11000);
  spectrum1->SetParLimits(1,36,44);
  spectrum1->SetParLimits(2,0,10);

  spectrum1->SetParLimits(3,3000,4000);
  spectrum1->SetParLimits(4,0.9,1.2);

  
  TF1* spectrum2 = new TF1("SpectrumFit2","[0] * exp(-( x-[1] )*( x-[1] )/( 2* [2]* [2])) + [3] / (exp((x - (2*[1]*[1]/(511+2*[1]))) * [4]) + 1)",12,60);

  spectrum2->SetParLimits(0,9000,11000);
  spectrum2->SetParLimits(1,36,44);
  spectrum2->SetParLimits(2,0,10);

  spectrum2->SetParLimits(3,3000,4000);
  spectrum2->SetParLimits(4,0.7,1.2);

  
  canvSourceCoinc->cd(1);
  sourceHisto1->Fit("SpectrumFit1","R");

  canvSourceCoinc->cd(2);
  sourceHisto2->Fit("SpectrumFit2","R");
  
  canvSourceCoinc->SaveAs(("HistoSourceCoincFit"+Source+"ComEdgRel.png").c_str());
  canvSourceCoinc->SaveAs(("HistoSourceCoincFit"+Source+"ComEdgRel.pdf").c_str());

  
  
  
}
