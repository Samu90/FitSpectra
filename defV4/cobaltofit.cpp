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
#include "SourceClass.h"

#define CHID 315
#define Me 36.01
#define MeErr 0.11

void mainfun(string outputname){

  gStyle->SetOptFit(1111);
  gStyle->SetOptStat(0000);

  
  
  Source* Sour = new Source("Co60",2);
  TCanvas* canvas = new TCanvas(("HistoSource"+Sour->GetSourceName()).c_str(),("HistoSource"+Sour->GetSourceName()).c_str(),1200,800);

  /*Sour->GetPlot()->Rebin(2);
  Sour->GetPlot()->Scale(0.5);
  Sour->GetPlot()->GetXaxis()->SetRangeUser(0,100);
  */
  
  Sour->GetPlot()->Draw();

  /*  TF1* spectrum = new TF1("SpectrumFit","[0] * exp(-( x-[1] )*( x-[1] )/( 2* [2]* [2])) + [3] / (exp( (x*[4]-(2*[1]*[1]/([8]+2*[1])))) + 1)+ [5]/ (exp( (x*[6]-(2*[7]*[7]/([8]+2*[7])))) + 1)",13,88);

  //gaussiana più 2 fermi-dirac
  
  spectrum->SetParLimits(0,700,800);
  spectrum->SetParLimits(1,40,50);
  spectrum->SetParLimits(2,2,4);
  spectrum->SetParLimits(3,400,600);
  spectrum->SetParLimits(4,0.6,1.2);
  spectrum->SetParLimits(5,150,230);
  spectrum->SetParLimits(6,1,1.4);
  spectrum->SetParLimits(7,30,45);
  spectrum->FixParameter(8,Me);
  spectrum->SetParError(8,MeErr);

  
  Sour->GetPlot()->Fit("SpectrumFit","R");

  
  Double_t xmin,xmax;
  
  spectrum->GetRange(&xmin,&xmax);
  
  TF1* gauss1 = new TF1("gauss1","gaus",xmin,xmax);
  TF1* fd1 = new TF1("fd1","[0] / (exp( (x*[1]-(2*[2]*[2]/([3]+2*[2])))) + 1)",xmin,xmax);
  TF1* fd2 = new TF1("fd2","[0] / (exp( (x*[1]-(2*[2]*[2]/([3]+2*[2])))) + 1)",xmin,xmax);
  
  
  gauss1->FixParameter(0,spectrum->GetParameter(0));
  gauss1->FixParameter(1,spectrum->GetParameter(1));
  gauss1->FixParameter(2,spectrum->GetParameter(2));
  
  fd1->FixParameter(0,spectrum->GetParameter(3));
  fd1->FixParameter(1,spectrum->GetParameter(4));
  fd1->FixParameter(2,spectrum->GetParameter(1));
  fd1->FixParameter(3,spectrum->GetParameter(8));

  fd2->FixParameter(0,spectrum->GetParameter(5));
  fd2->FixParameter(1,spectrum->GetParameter(6));
  fd2->FixParameter(2,spectrum->GetParameter(7));
  fd2->FixParameter(3,spectrum->GetParameter(8));
    
  gauss1->SetLineStyle(10);
  gauss1->SetLineColor(kRed);
  fd1->SetLineStyle(10);
  fd1->SetLineColor(kBlack);
  fd2->SetLineStyle(10);
  fd2->SetLineColor(kGreen);
  
  gauss1->Draw("SAME");
  fd1->Draw("SAME");
  fd2->Draw("SAME");
  
  */
  canvas->SaveAs(("HistoSource"+Sour->GetSourceName()+outputname+".png").c_str());
  canvas->SaveAs(("HistoSource"+Sour->GetSourceName()+outputname+".pdf").c_str());
  
}
