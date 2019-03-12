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

void mainfun(){
  
  Source* Na = new Source("Na22",2);
  TCanvas* canvas = new TCanvas(("HistoSource"+Na->GetSourceName()).c_str(),("HistoSource"+Na->GetSourceName()).c_str(),1200,800);

  Na->GetPlot()->Draw();

  TF1* spectrum = new TF1("SpectrumFit","[0] * exp(-( x-[1] )*( x-[1] )/( 2* [2]* [2])) + [3] / (exp( (x*[4]-(2*[1]*[1]/([1]+2*[1])))) + 1)+ [5] * exp(-( x-[6] )*( x-[6] )/( 2* [7]* [7])) + [8] / (exp( (x*[9]-(2*[6]*[6]/([6]+2*[6])))) + 1) + [10]*exp(-x*[11]-[12])",27,88);

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
      
}
