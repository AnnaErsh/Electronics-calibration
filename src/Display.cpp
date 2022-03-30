#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

#include "TF1.h"
#include "TH1D.h"
#include "TH2D.h"
#include "TLegend.h"
#include "TCanvas.h"
#include "TStyle.h"

#include "Style.h"
#include "Params.h"

using namespace std;

double PlotAllLines()
{
  Style();
  ifstream file_names("results/txt/file_names.txt");
  string name;

  vector<double> v_p0;
  vector<double> v_p1;

  while (getline(file_names, name))
  {
    ifstream cur_file(("results/txt/" + name + ".txt").c_str());

    string str;
    string n;
    double p0 = 0, p1 = 0, x=0, y=0;
    while (bool(getline(cur_file, str)))
    {
      istringstream ss(str);
      ss>>n>>p0>>p1>>x>>y;
      v_p0.push_back(p0);
      v_p1.push_back(p1);
    }
  }

  double min_val = *min_element(v_p1.begin(), v_p1.end());
  double max_val = *max_element(v_p1.begin(), v_p1.end());

  TH1D* h_p1 = new TH1D("p1", "; p_{1}; Number of Events", 50, 0.99 * min_val, 1.01 * max_val);
  TF1* lines[v_p0.size()];

  TCanvas* c1 = new TCanvas();
  for (uint i = 0; i < v_p0.size(); ++i)
  {
    lines[i] = new TF1(("line" + to_string(i)).c_str(), "pol1", 0, 24);
    lines[i]->SetParameter(0, v_p0[i]);
    lines[i]->SetParameter(1, v_p1[i]);
    h_p1->Fill(v_p1[i]);

    if(i == 0) lines[i]->Draw();
    else lines[i]->Draw("SAME");
  }

  c1->Print(("results/histograms/all_lines." + params::ext).c_str());

  gStyle->SetOptStat(1);
  gStyle->SetOptFit(1);
  h_p1->Fit("gaus");
  TF1 *fit = new TF1("fit", "gaus", min_val, max_val);
  h_p1->Fit("fit", "s", "", min_val, max_val);    
  double mean = fit->GetParameter(1);

  h_p1->Draw();
  fit->Draw("SAME");
  c1->Print(("results/histograms/p1_superimposed." + params::ext).c_str());

  for (uint i = 0; i < v_p0.size(); ++i) delete lines[i];
  delete fit;
  delete h_p1;
  delete c1;

  return mean;
}

int main(int argc, char const *argv[])
{
	Style();

  TH2D* h0 = new TH2D("p0_display", "p_{0} (intercept); ;", 36, 0, 36, 32, 0, 32);
  TH2D* h1 = new TH2D("p1_display", "p_{1} (slope); ;", 36, 0, 36, 32, 0, 32);
  TH2D* h1_rel = new TH2D("p1_display_relative", "p_{1} (slope); ;", 36, 0, 36, 32, 0, 32);

  double p0_max = 0, p0_min = 1000, p1_max = 0, p1_min = 1000;
  double p1_max_rel = 0, p1_min_rel = 1000;

  double MEAN = PlotAllLines();
  cout<<"MEAN = "<<MEAN<<endl;

  ifstream file_names("results/txt/file_names.txt");
  string name;
  while (getline(file_names, name))
  {
    ifstream cur_file(("results/txt/" + name + ".txt").c_str());

    string str;
    string n;
    double p0 = 0, p1 = 0, x=0, y=0;

    while (bool(getline(cur_file, str)))
    {
      istringstream ss(str);
      ss>>n>>p0>>p1>>x>>y;

      // if(p0 == 0 && p1 == 0) continue;
      if(p0<p0_min) p0_min = p0;
      if(p1<p1_min) p1_min = p1;
      if(p0>p0_max) p0_max = p0;
      if(p1>p1_max) p1_max = p1;

      if((p1 - MEAN) / MEAN * 100<p1_min_rel) p1_min_rel = (p1 - MEAN) / MEAN * 100;
      if((p1 - MEAN) / MEAN * 100>p1_max_rel) p1_max_rel = (p1 - MEAN) / MEAN * 100;

      h0->SetBinContent(x+1, y+1, p0);
      h1->SetBinContent(x+1, y+1, p1);
      h1_rel->SetBinContent(x, y, double(p1 - MEAN) / MEAN * 100);
    }
    cur_file.close();
  }

  gStyle->SetOptStat(0);
  h0->SetBit(TH1::kNoStats);
  h0->SetMaximum(p0_max);
  h0->SetMinimum(p0_min);
  
  HistPrint(h0, "", "COLZ0", "", false);

  h1->SetBit(TH1::kNoStats);
  h1->SetMaximum(p1_max);
  h1->SetMinimum(p1_min);
  h1->GetZaxis()->SetTitleOffset(0.4);
  HistPrint(h1, "", "COLZ0", "", false);

  h1->SetBit(TH1::kNoStats);
  h1->SetMaximum(p1_max_rel);
  h1->SetMinimum(p1_min_rel);
  h1_rel->GetZaxis()->SetTitle("%");
  HistPrint(h1_rel, "", "COLZ0", "", false);

  delete h0;
  delete h1;
  delete h1_rel;
  return 0;
}