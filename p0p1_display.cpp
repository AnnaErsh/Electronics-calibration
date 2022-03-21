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

using namespace std;

void Style()
{
  gStyle->SetOptStat(0);
  gStyle->SetTextFont(40);
  //gROOT->SetBatch(kTRUE);

  // use plain black on white colors
  gStyle->SetFrameBorderMode(0);
  gStyle->SetCanvasBorderMode(0);
  gStyle->SetPadBorderMode(0);
  gStyle->SetPadColor(0);
  gStyle->SetCanvasColor(0);
  gStyle->SetStatColor(0);
  gStyle->SetLegendBorderSize(1);

  // set the paper & margin sizes
  gStyle->SetPaperSize(20,26);
  gStyle->SetPadTopMargin(0.10);
  gStyle->SetPadRightMargin(0.16);
  gStyle->SetPadBottomMargin(0.16);
  gStyle->SetPadLeftMargin(0.13);

  // use large Times-Roman fonts
  gStyle->SetTextFont(132);
  gStyle->SetTextSize(0.06);
  gStyle->SetLabelFont(132,"x");
  gStyle->SetLabelFont(132,"y");
  gStyle->SetLabelFont(132,"z");
  gStyle->SetLabelSize(0.05,"x");
  gStyle->SetTitleSize(0.06,"x");
  gStyle->SetLabelSize(0.05,"y");
  gStyle->SetTitleSize(0.06,"y");
  gStyle->SetTitleOffset(0.9,"y");
  gStyle->SetTitleOffset(0.9,"x");
  gStyle->SetTitleOffset(0.75,"z");
  gStyle->SetLabelSize(0.05,"z");
  gStyle->SetTitleSize(0.06,"z");
  gStyle->SetLabelFont(132,"t");
  gStyle->SetTitleFont(132,"x");
  gStyle->SetTitleFont(132,"y");
  gStyle->SetTitleFont(132,"z");
  gStyle->SetTitleFont(132,"t");
  gStyle->SetTitleFillColor(0);
  //gStyle->SetTitleX(0.25);
  gStyle->SetTitleFontSize(0.06);
  gStyle->SetTitleFont(132,"pad");

  gStyle->SetTitleBorderSize(1);
  gStyle->SetPadBorderSize(1);
  //gStyle->SetPadRightMargin(1.3);
  gStyle->SetCanvasBorderSize(1);

  // use bold lines and markers
  gStyle->SetMarkerStyle(20);
  gStyle->SetHistLineWidth(3);
  gStyle->SetLineStyleString(2,"[12 12]"); // postscript dashes

  // get rid of X error bars and y error bar caps
  gStyle->SetErrorX(0.001);

  // do not display any of the standard histogram decorations
  // gStyle->SetOptTitle(0);
  gStyle->SetOptStat(0);
  gStyle->SetOptFit(0);

  // put tick marks on top and RHS of plots
  gStyle->SetPadTickX(1);
  gStyle->SetPadTickY(1); 
}

int main(int argc, char const *argv[])
{
	Style();
  string option = argv[1];
  string name1, name2;
  vector<string> names;
  if(option == 3)
  {
    name1 = "TXT/txt3/R2021_07_30-";
    name2 = "-000.txt";
    names.insert(names.end(), {"13_32_52", "13_42_51", "13_52_28", "14_02_19", "14_12_18", "14_22_16", "14_31_43", 
                               "14_41_24", "14_51_11", "15_00_58", "15_10_44", "15_20_44", "15_41_48", 
                               "15_51_15", "16_00_46", "16_10_30", "16_20_14", "16_29_58", "16_39_42", "16_50_14", 
                               "17_01_00", "17_11_40", "17_22_25", "17_33_07", "17_53_16", "18_03_04", 
                               "18_12_50", "18_22_37", "18_32_24", "18_42_25", "18_53_09", "19_03_59", "19_14_53", "19_25_47"});    
  }
  else if (option == "new")
  {
    name1 = "TXT/txt_new/R2021_10_13-";
    name2 = "-000.txt";
    names.insert(names.end(), {"15_01_25", "15_10_37", "15_19_41", "15_28_55", "15_38_14", "15_47_33", "15_56_52", "16_06_11", "16_15_30", "16_24_49", "16_33_59", 
                               "16_43_04", "16_52_14", "17_01_32", "17_10_37", "17_19_42", "17_28_57", "17_38_16", "17_47_35", "17_56_54", "18_06_13", "18_15_32", 
                               "18_24_51", "18_34_10", "18_43_30", "18_52_49", "19_02_08", "19_11_27", "19_20_46", "19_30_05", "19_39_24", "19_48_43", "19_58_03", 
                               "20_07_22", "20_16_42", "20_26_01" }); 
  }
  else if (option == "211126_3")
  {
    name1 = "TXT/txt_211126_3/R2021_11_26-";
    name2 = "-000.txt";
    names.insert(names.end(), {"15_33_31","15_39_46","15_46_01","15_52_16","15_58_32","16_04_48","16_11_04","16_17_20","16_23_35","16_29_51","16_36_07",
                               "16_42_23","16_48_37","16_54_53","17_01_10","17_07_25","17_13_42","17_19_58","17_26_14","17_32_30","17_38_46","17_45_03",
                               "17_51_19","17_57_35","18_03_51","18_10_07","18_16_23","18_22_40","18_28_56","18_35_13","18_41_29","18_47_46","18_54_03",
                               "19_00_20","19_06_37","19_12_53","19_19_10","19_25_26"}); 
  }
  else if (option == "211126_4")
  {
    name1 = "TXT/txt_211126_4/R2021_11_28-";
    name2 = "-000.txt";
    names.insert(names.end(), {"15_04_07", "15_10_25", "15_16_42", "15_23_00", "15_29_18", "15_35_35", "15_41_53", "15_48_11", "15_54_29", "16_00_47", "16_07_04", 
                               "16_13_22", "16_19_40", "16_25_59", "16_32_17", "16_38_35", "16_44_52", "16_51_10", "16_57_28", "17_03_46", "17_10_04", "17_16_22", 
                               "17_22_40", "17_28_58", "17_35_16", "17_41_34", "17_47_51", "17_54_09", "18_00_27", "18_06_44", "18_13_02", "18_19_20", "18_25_38", 
                               "18_31_56", "18_38_14", "18_44_32", "18_50_50", "18_57_07"}); 
  }
  else if (option == "220131_3")
  {
    name1 = "TXT/txt_220131_3/R2022_01_31-";
    name2 = "-000.txt";
    names.insert(names.end(), {"17_35_08", "18_10_50", "18_47_14", "19_23_56", "17_38_45", "18_14_28", "18_50_54", "19_27_32", "17_42_19", "18_18_07", "18_54_33", 
                               "19_31_05", "17_45_54", "18_21_45", "18_58_15", "19_34_36", "17_49_26", "18_25_24", "19_01_54", "19_38_09", "17_52_57", "18_29_04", 
                               "19_05_33", "19_41_39", "17_56_28", "18_32_43", "19_09_09", "19_45_08", "18_00_00", "18_36_20", "19_12_46", "19_48_38", "18_03_34", 
                               "18_39_58", "19_16_30", "18_07_12", "18_43_35", "19_20_14" }); 
  }
  else if (option == "220131_4")
  {
    name1 = "TXT/txt_220131_4/R2022_01_31-";
    name2 = "-000.txt";
    names.insert(names.end(), {"21_09_55", "21_13_32", "21_17_07", "21_20_41", "21_24_14", "21_27_47", "21_31_20", "21_34_54", "21_38_29", "21_42_04", "21_45_40", 
                               "21_49_15", "21_52_48", "21_56_21", "21_59_55", "22_03_30", "22_07_05", "22_10_40", "22_14_16", "22_17_51", "22_21_25", "22_25_00", 
                               "22_28_34", "22_32_07", "22_35_41", "22_39_16", "22_42_48", "22_46_23", "22_49_58", "22_53_33", "22_57_07", "23_00_42", "23_04_16", 
                               "23_07_50", "23_11_25", "23_15_09", "23_18_54", "23_22_38" }); 
  }
  TH2D* h0 = new TH2D("h0", "p_{0} (intercept); ;", 36, 0, 36, 32, 0, 32);
  TH2D* h1 = new TH2D("h1", "p_{1} (slope); ;", 36, 0, 36, 32, 0, 32);
  double p0_max = 0, p0_min = 1000, p1_max = 0, p1_min = 1000;

  const double MEAN = 162.8;

  for(const auto& name : names)
  {
    cout<<name<<" "<<name1 + name + name2<<endl;
    ifstream out((name1 + name + name2).c_str());

    string str;
    string n;
    double p0 = 0, p1 = 0, x=0, y=0;

    while (bool(getline(out, str)))
    {
      istringstream ss(str);
      ss>>n>>p0>>p1>>x>>y;

      cout<<x<<" "<<y<<endl;
      if(p0 == 0 && p1 == 0) continue;
      // p0-=250;
      if(p0<p0_min) p0_min = p0;
      if(p1<p1_min) p1_min = p1;
      //if((p1 - MEAN) / MEAN * 100<p1_min) p1_min = (p1 - MEAN) / MEAN * 100;
      if(p0>p0_max) p0_max = p0;
      if(p1>p1_max) p1_max = p1;
      //if((p1 - MEAN) / MEAN * 100>p1_max) p1_max = (p1 - MEAN) / MEAN * 100;
      h0->SetBinContent(x+1, y+1, p0);
      // h1->SetBinContent(x, y, double(p1 - MEAN) / MEAN * 100);
      h1->SetBinContent(x+1, y+1, p1);
      // cout<<double(p1 - MEAN) / MEAN * 100<<endl;
    }
    out.close();
  }
  TCanvas* c1 = new TCanvas();
  h0->SetBit(TH1::kNoStats);
  h0->SetMaximum(p0_max);
  h0->SetMinimum(p0_min);
  h0->Draw("COLZ0");
  c1->Print("p0_display.pdf");

  h1->SetBit(TH1::kNoStats);
  h1->SetMaximum(p1_max);
  h1->SetMinimum(p1_min);
  // cout<<"!!! "<<p1_max - p1_min<<endl;
  h1->GetZaxis()->SetTitleOffset(0.4);
  // h1->GetZaxis()->SetTitle("%");
  h1->Draw("COLZ0");
  c1->Print("p1_display.pdf");
  delete c1;
  delete h0;
  delete h1;
  return 0;
}