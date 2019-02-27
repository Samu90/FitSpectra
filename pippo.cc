
  //TFile *_file0 = TFile::Open("output/Pedestal/PedestalTest13_2ch_100000delay_qdc_1_singles.root");
  //TFile *_file1 = TFile::Open("output/Sources/SourceCs137_qdc_180_singles.root");
  TFile *_file1 = TFile::Open("output/Sources/");

  //TH1F *histoPedCh0 = new TH1F("histoPedCh0","histoPedCh0",200,150,350);    
  //TH1F *histoSigPlusPedCh0 = new TH1F("histoSigPlusPedCh0","histoSigPlusPedCh0",600,0,600);
  TH1F *histoSigPlusPedCh1 = new TH1F("histoSigPlusPedCh1","histoSigPlusPedCh1",600,0,600);
  //TH1F *histoPedCh1 = new TH1F("histoPedCh1","histoPedCh1",200,150,350);

  //_file0->cd();
  //data->Project("histoPedCh0","energy","channelID==59");
  //data->Project("histoPedCh1","energy","channelID==315");
  _file1->cd();
  //data->Project("histoSigPlusPedCh0","energy-247.3","channelID==59");
  data->Project("histoSigPlusPedCh1","energy","channelID==315");

  //histoPedCh0->Draw();
  //histoSigPlusPedCh0->Draw();
  //histoPedCh1->Draw();
  histoSigPlusPedCh1->Draw();

}
