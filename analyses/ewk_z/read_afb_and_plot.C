void read_afb_and_plot()
{

  //read in file and assign to pointer, which points to an object of class type "TFile"
  TFile* file = new TFile("afb.root");

  //see what ever is in file
  file->ls();
  //assign directories
  TDirectoryFile* wz = (TDirectoryFile*)file->Get("wzp6_ee_mumu_ecm91p2");
  TDirectoryFile* kk = (TDirectoryFile*)file->Get("kkmcee_ee_mumu_ecm91p2");

  //print all hists for information purposes onyly
  wz->ls();
  kk->ls();

  TString histname = "cosThetac"; //put whatever you want to plot here
  TH1D* h1_wz = (TH1D*)wz->Get(histname);
  TH1D* h1_kk = (TH1D*)kk->Get(histname);

  //add histograms together also to get total, although comparision is also interesting
  TH1D* h1 = (TH1D*)h1_wz->Clone();
  h1->Add(h1_kk);


  //this is a root class that automatically takes care of axis limits if you are plotting multiple historgrams
  THStack* ts = new THStack();

  //plot everything
  h1_wz->SetLineColor(kRed);
  h1_kk->SetLineColor(kGreen+2);
  ts->Add(h1_wz);
  ts->Add(h1_kk);
  ts->Add(h1);


  //make a canvas to draw object on
  TCanvas* c1 = new TCanvas();
  ts->Draw("nostack");
  //ts->Draw("norm");
  c1->SaveAs(histname+".pdf");
  
}
