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

  TGraphErrors *graph = new TGraphErrors(dataset,"%lg %lg %lg");
  TCanvas* CalibPlot= new TCanvas("CalibPlot","CalibPlot",1200,1200);
  graph->SetMarkerStyle(8);
  graph->GetXaxis()->SetRange(0,1300);

  graph->Draw("AP");

  TF1* fit = new TF1("fitCalib"," [0] * (1-exp(-[1]*x) )",300,1300);

  gStyle->SetOptFit(1101);
  
  graph->Fit("fitCalib");

  std::cout << graph->GetN() << std::endl;
  
  Double_t *X,*Y,*EY;

  int N=graph->GetN();
  
  X=graph->GetX();
  Y=graph->GetY();
  EY=graph->GetEY();

  for(int i=0;i<N;i++){
    std::cout << X[i]<<"  " << Y[i] <<"  "<< EY[i] << std::endl;
  }

  std::cout << fit->GetChisquare()<< std::endl;

  Double_t sigmaY,temp;
  temp=0;
  
  for(int i=0;i<N;i++){
    temp+=(Y[i]-fit->Eval(X[i]))*(Y[i]-fit->Eval(X[i]));
    
  }

  sigmaY=sqrt(1/(N-2)*temp);

  
}
