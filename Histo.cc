#include "iostream"
#include "TH1.h"
#include "TString.h"
#include "TFile.h"
#include "TTree.h"
#include "string"
#include "TF1.h"
#include "TCanvas.h"

void Analysis(TString Source, TFile* saveFile) {

  TFile* f_Source = TFile::Open("def/Source"+Source+"_qdc_def_singles.root");
  TFile* f_Ped = TFile::Open("Pedestal_Source"+Source+"_qdc_1_singles.root");

  //Pedestal_SourceNa22_qdc_1_singles.root
  
  TTree* dataSource = (TTree*)f_Source->Get("data");
  TTree* dataPed = (TTree*)f_Ped->Get("data");
  
  Float_t eSource, ePed;
  UShort_t SourceChId, PedChId;

  dataSource->SetBranchAddress("energy",&eSource);
  dataSource->SetBranchAddress("channelID",&SourceChId);
  dataPed->SetBranchAddress("energy",&ePed);
  dataPed->SetBranchAddress("channelID",&PedChId);

  //PEDESTAL ANALYSIS
  
  TH1F* pedHisto = new TH1F("HistoPedestal"+Source,"HistoPedestal"+Source,600,150,250);

  for(int i=0;i<dataSource->GetEntries();i++){
    dataPed->GetEntry(i);
    if(PedChId==315) pedHisto->Fill(ePed);
    //pedHisto->Fill(ePed);
  }
  
  TCanvas* canvPed = new TCanvas("PedCanvas","PedCanvas",1200,1200);
  TF1* fitPed = new TF1("PedFit","gaus",pedHisto->GetMean()-7*pedHisto->GetRMS(),pedHisto->GetMean()+7*pedHisto->GetRMS());
  pedHisto->GetXaxis()->SetRangeUser(pedHisto->GetMean()-7*pedHisto->GetRMS(),pedHisto->GetMean()+7*pedHisto->GetRMS());
  pedHisto->Draw("");
  pedHisto->Fit("PedFit");
  fitPed->Draw("same");
  
  Float_t meanPed = pedHisto->GetMean();

  //SOURCE DATA ANALYSIS

  
  TH1F* sourceHisto = new TH1F("HistoSource"+Source,"HistoSource"+Source,600,0,600);

  for(int i=0;i<dataSource->GetEntries();i++){
    dataSource->GetEntry(i);
    if(SourceChId==315) sourceHisto->Fill(eSource-meanPed);
    //pedHisto->Fill(ePed);
  }
  
  TCanvas* canvSource = new TCanvas("SourceCanvas","SourceCanvas",1200,1200);
  //TF1* fitSource = new TF1("SourceFit","gaus",sourceHisto->GetMean()-7*sourceHisto->GetRMS(),sourceHisto->GetMean()+7*sourceHisto->GetRMS());
  sourceHisto->GetXaxis()->SetRangeUser(sourceHisto->GetMean()-7*sourceHisto->GetRMS(),sourceHisto->GetMean()+7*sourceHisto->GetRMS());
  sourceHisto->Draw("");
  //sourceHisto->Fit("SourceFit");
  //fitSource->Draw("same");

  saveFile->cd();
  
  pedHisto->Write();
  sourceHisto->Write();
  
}

void Main(){

  TFile* histoFile = TFile::Open("def/histoFile.root", "RECREATE");

  Analysis("Na22",histoFile);
  Analysis("Ba135",histoFile);
  Analysis("Cs137",histoFile);
  Analysis("Co60",histoFile);
  
}
