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

  gStyle->SetOptFit(1111);
  gStyle->SetStatW(0.2);
  gStyle->SetStatH(0.1);
  
  TCanvas* canvSource = new TCanvas(("SourceCanvas"+Source).c_str(),("SourceCanvas"+Source).c_str(),1200,800);

  sourceHisto->GetXaxis()->SetRangeUser(0,100);
  canvSource->cd();
  sourceHisto->Draw();
    
    TF1* spectrum = new TF1("SpectrumFit","[0] * exp(-( x-[1] )*( x-[1] )/( 2* [2]* [2]))  +  [3] * exp(-( x-[4] )*( x-[4] )/( 2* [5]* [5]))  +  [6] / (exp((x - [7]) * [8]) + 1)  +  [9] / (exp((x - [10]) * [11]) + 1)  +                    [12] * exp(-(x*[13]-[14]))",21,88);

  //gauss1+ gauss2+ fd1+ fd2+ bkg1/2
  
  spectrum->SetParLimits(0,500000,650000);
  spectrum->SetParLimits(1,36,45);
  spectrum->SetParLimits(2,2.7,3);
  
  spectrum->SetParLimits(3,41500,6150);
  spectrum->SetParLimits(4,79.5,81.5);
  spectrum->SetParLimits(5,3.22,3.42);

  spectrum->SetParLimits(6,40600,65000); //altezza FermiDirac
  spectrum->SetParLimits(7,72.7,74.7); //punto inversione
  spectrum->SetParLimits(8,0.8,1.1); //flesso fermi dirac

  
  
  spectrum->SetParLimits(12,5e-05,0.01);
  spectrum->SetParLimits(13,1e-05,0.27); 
  spectrum->SetParLimits(14,19,22); //24


  spectrum->SetParameter(0,597350);
  spectrum->SetParameter(1,41.072);
  spectrum->SetParameter(2,2.7498);

  spectrum->SetParameter(3,51572);
  spectrum->SetParameter(4,80.54);
  spectrum->SetParameter(5,3.32);

  spectrum->SetParameter(6,60608);
  spectrum->SetParameter(7,72.96);
  spectrum->SetParameter(8,0.981);

  
  spectrum->SetParameter(12,0.01);
  spectrum->SetParameter(13,0.15139);
  spectrum->SetParameter(14,21.46);
  

  
  sourceHisto->Fit("SpectrumFit","R");

  Double_t xmin,xmax;

  spectrum->GetRange(&xmin,&xmax);
  
  TF1* gauss1 = new TF1("gauss1","gaus",xmin,xmax);
  TF1* gauss2 = new TF1("gauss2","gaus",xmin,xmax);
  TF1* fd1 = new TF1("fd1","[0] / (exp((x - [1]) * [2]) + 1)",xmin,xmax);
  TF1* fd2 = new TF1("fd2","[0] / (exp((x - [1]) * [2]) + 1)",xmin,xmax);
  TF1* decExp = new TF1("decExp","[0] * exp(-(x*[1]-[2]))",xmin,xmax);
  
  gauss1->FixParameter(0,spectrum->GetParameter(0));
  gauss1->FixParameter(1,spectrum->GetParameter(1));
  gauss1->FixParameter(2,spectrum->GetParameter(2));

  gauss2->FixParameter(0,spectrum->GetParameter(3));
  gauss2->FixParameter(1,spectrum->GetParameter(4));
  gauss2->FixParameter(2,spectrum->GetParameter(5));

  fd1->FixParameter(0,spectrum->GetParameter(6));
  fd1->FixParameter(1,spectrum->GetParameter(7));
  fd1->FixParameter(2,spectrum->GetParameter(8));

  fd2->FixParameter(0,spectrum->GetParameter(9));
  fd2->FixParameter(1,spectrum->GetParameter(10));
  fd2->FixParameter(2,spectrum->GetParameter(11));

  decExp->FixParameter(0,spectrum->GetParameter(12));
  decExp->FixParameter(1,spectrum->GetParameter(13));
  decExp->FixParameter(2,spectrum->GetParameter(14));

  gauss1->SetLineStyle(10);
  gauss1->SetLineColor(kRed);
  gauss2->SetLineStyle(10);
  gauss2->SetLineColor(kBlue);
  fd1->SetLineStyle(10);
  fd1->SetLineColor(kBlack);
  fd2->SetLineStyle(10);
  fd2->SetLineColor(kGreen);
  decExp->SetLineStyle(10);

  gauss1->Draw("SAME");
  gauss2->Draw("SAME");
  fd1->Draw("SAME");
  fd2->Draw("SAME");
  decExp->Draw("SAME");
  
  
  canvSource->SaveAs(("HistoSourceFit"+Source+".png").c_str());
  canvSource->SaveAs(("HistoSourceFit"+Source+".pdf").c_str());

  
  
}
