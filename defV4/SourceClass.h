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



class Source{

 public:

  Source();
  Source(string SourceID, Int_t N);
  ~Source();
  
  void  SetPeak1(Double_t a){ Peak1=a; }
  void  SetPeak2(Double_t a){ Peak2=a; }
  void  SetDevPeak1(Double_t a){ DevPeak1=a; }
  void  SetDevPeak2(Double_t a){ DevPeak2=a; }

  Double_t GetPeak1(){return Peak1;}
  Double_t GetPeak2(){return Peak2;}
  Double_t GetDPeak1(){return DevPeak1;}
  Double_t GetDPeak2(){return DevPeak2;}
  
  TH1D* GetPlot(){return Spectrum;}

  string GetSourceName(){return SourceName;}

  void SetPedestal();

  void MakePlot();
  
  Double_t GetPedesta(){return Pedestal;}
  
 private:
  
  TFile* FileData;
  TFile* DataPedestal;

  TTree* DataTree;
  TTree* PedestalTree;
  
  string SourceName;

  TH1D* Spectrum;

  Int_t NPeaks = 0;

  Double_t Peak1;
  Double_t Peak2;
  
  Double_t DevPeak1;
  Double_t DevPeak2;
  
  Double_t Pedestal;

  string path="/afs/cern.ch/work/s/storelli/private/TOFPET/Sources/def/";

};


Source::Source(string SourceID , Int_t N){

  FileData=TFile::Open((path+"Source"+SourceID+"_qdc_def_singles.root").c_str());
  DataPedestal=TFile::Open((path+"../Pedestal_Source"+SourceID+"_qdc_1_singles.root").c_str());

  DataTree = (TTree*)FileData->Get("data");
  PedestalTree = (TTree*)DataPedestal->Get("data");

  if(FileData){ std::cout << "file open " << std::endl;}
  if(DataPedestal){ std::cout << "file open " << std::endl;}
  
  NPeaks = N;

  SourceName = SourceID;

  SetPedestal();
  MakePlot();
};

void Source::SetPedestal(){
  Float_t Energy;
  UShort_t ChID;
  int count;
  
  PedestalTree->SetBranchAddress("energy",&Energy);
  PedestalTree->SetBranchAddress("channelID",&ChID);
  
  Pedestal=0;
  count=0;

  for(int i=0;i<PedestalTree->GetEntries();i++){
     PedestalTree->GetEntry(i);
    if(ChID==315){
      Pedestal+=Energy;
      count+=1;
      // std::cout<<"Hiiii"<<std::endl;
    }//chiudo if
  }//chiudo for
  
  Pedestal/=count;

  std::cout << count << "   Pedestal=" << Pedestal<< std::endl;
}


void Source::MakePlot(){

  Float_t Energy;
  UShort_t ChID;
    
  DataTree->SetBranchAddress("energy",&Energy);
  DataTree->SetBranchAddress("channelID",&ChID);

  Spectrum = new TH1D(("HistoSource"+SourceName).c_str(),("HistoSource"+SourceName).c_str(),600,0,600);
  
  for(int i=0;i<DataTree->GetEntries();i++){
    DataTree->GetEntry(i);
    if(ChID==315) Spectrum->Fill(Energy-Pedestal);
    if(i%10000==0)std::cout << i << "/" << DataTree->GetEntries() << std::endl;
  }

  Spectrum->GetXaxis()->SetRangeUser(0,100);
  Spectrum->GetXaxis()->SetTitle("E[D.U.]");
  Spectrum->GetYaxis()->SetTitle("Counts");
  
}
