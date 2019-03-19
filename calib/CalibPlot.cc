#include "iostream"
#include "TH1.h"
#include "TString.h"
#include "TFile.h"
#include "TTree.h"
#include "string"
#include "TF1.h"
#include "TCanvas.h"
#include "TGraphErrors.h"
#include "TGraphPainter.h"
#include "TStyle.h"

void CalibPlot(TString dataset){

    gStyle->SetOptFit(1111);
  // gStyle->SetOptStat(0000);

  TGraphErrors *graph = new TGraphErrors(dataset,"%lg %lg");
  TCanvas* CalibPlot= new TCanvas("CalibPlot","CalibPlot",1200,1200);

  graph->SetMarkerStyle(20);
    
  graph->Draw("AP");

  TF1* fit = new TF1("fitCalib"," [0] * (1-exp(-[1]*x) )",0,1300);

  fit->SetParameter(0,144);
  fit->SetParameter(1,4e-4);
  
  
  //fit->SetParLimits(0,100,120);
  // fit->SetParLimits(1,0,1);
  
  graph->Fit("fitCalib","R");

  graph->GetXaxis()->SetRangeUser(0.0,1300.0);
  graph->GetYaxis()->SetRangeUser(0.0,80.0);

  graph->GetXaxis()->SetTitle("E[KeV]");
  graph->GetYaxis()->SetTitle("E[D.U.]");
  
  graph->Draw("AP");  

  //fit->DrawF1(0,1300,"SAME");


  Double_t SigmaYPost=0;
  Int_t N=graph->GetN();
  Double_t *Y,*X;
  
  Y=graph->GetY();
  X=graph->GetX();
  
  for(int i=0;i<N;i++){
    
    SigmaYPost+= (Y[i]-fit->Eval(X[i])) * (Y[i]-fit->Eval(X[i]));
    
  }

  SigmaYPost /= (N-2);

  std::cout << SigmaYPost << std::endl;

  for(int i=0;i<N;i++){
    graph->SetPointError(i,0,SigmaYPost);
  }
  graph->SetTitle(fit->GetExpFormula());
  graph->Draw("AP");
  graph->SetMarkerSize(.4);
  graph->Fit("fitCalib");
  //fit->Draw("SAME");
  
}

