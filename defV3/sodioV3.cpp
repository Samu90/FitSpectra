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

  gStyle->SetOptFit(1111);
  gStyle->SetStatW(0.2);
  gStyle->SetStatH(0.1);
  
  TCanvas* canvSource = new TCanvas(("SourceCanvas"+Source).c_str(),("SourceCanvas"+Source).c_str(),1200,800);
  
  sourceHisto->GetXaxis()->SetRangeUser(0,100);
  canvSource->cd();
  sourceHisto->Draw();
  
    
    TF1* spectrum = new TF1("SpectrumFit","[0] * exp(-( x-[1] )*( x-[1] )/( 2* [2]* [2])) + [3] / (exp( (x*[4]-(2*[1]*[1]/([1]+2*[1])))) + 1)+ [5] * exp(-( x-[6] )*( x-[6] )/( 2* [7]* [7])) + [8] / (exp( (x*[9]-(2*[6]*[6]/([6]+2*[6])))) + 1) + [10]*exp(-x*[11]-[12])",27,88);

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
  spectrum->SetParLimits(10,10e-6,10e-4); 
  spectrum->SetParLimits(11,10e-3,10e-1);
  spectrum->SetParLimits(12,-30,-15); 
  
  
  
  sourceHisto->Fit("SpectrumFit","R");
  
  Double_t xmin,xmax;
  
  spectrum->GetRange(&xmin,&xmax);
  
  TF1* gauss1 = new TF1("gauss1","gaus",xmin,xmax);
  TF1* gauss2 = new TF1("gauss2","gaus",xmin,xmax);
  TF1* fd1 = new TF1("fd1","[0] / (exp( (x*[1]-(2*[2]*[2]/([2]+2*[2])))) + 1)",xmin,xmax);
  TF1* fd2 = new TF1("fd2","[0] / (exp( (x*[1]-(2*[2]*[2]/([2]+2*[2])))) + 1)",xmin,xmax);
  TF1* decExp = new TF1("decExp","[0] * exp(-(x*[1]-[2]))",xmin,xmax);
  
  gauss1->FixParameter(0,spectrum->GetParameter(0));
  gauss1->FixParameter(1,spectrum->GetParameter(1));
  gauss1->FixParameter(2,spectrum->GetParameter(2));

  gauss2->FixParameter(0,spectrum->GetParameter(5));
  gauss2->FixParameter(1,spectrum->GetParameter(6));
  gauss2->FixParameter(2,spectrum->GetParameter(7));

  fd1->FixParameter(0,spectrum->GetParameter(3));
  fd1->FixParameter(1,spectrum->GetParameter(4));
  fd1->FixParameter(2,spectrum->GetParameter(1));

  fd2->FixParameter(0,spectrum->GetParameter(8));
  fd2->FixParameter(1,spectrum->GetParameter(9));
  fd2->FixParameter(2,spectrum->GetParameter(6));

  decExp->FixParameter(0,spectrum->GetParameter(10));
  decExp->FixParameter(1,spectrum->GetParameter(11));
  decExp->FixParameter(2,spectrum->GetParameter(12));

  gauss1->SetLineStyle(10);
  gauss1->SetLineColor(kRed);
  gauss2->SetLineStyle(10);
  gauss2->SetLineColor(kBlue);
  fd1->SetLineStyle(10);
  fd1->SetLineColor(kBlack);
  fd2->SetLineStyle(10);
  fd2->SetLineColor(kGreen);
  decExp->SetLineStyle(10);
  decExp->SetLineColor(kPink);

  gauss1->Draw("SAME");
  gauss2->Draw("SAME");
  fd1->Draw("SAME");
  fd2->Draw("SAME");
  decExp->Draw("SAME");


  
  canvSource->SaveAs(("HistoSource"+Source+output+".png").c_str());
  canvSource->SaveAs(("HistoSource"+Source+output+".pdf").c_str());

  
  
}
