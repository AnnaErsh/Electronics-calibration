#pragma once

#include<string>

#include"TCanvas.h"

#include"Params.h"

template<typename H>
void HistPrint(H h, std::string file_name, std::string draw_option, std::string folder, bool ifMacros = true)
{
  TCanvas* c1 = new TCanvas();
  h->Draw(draw_option.c_str());
  std::string histname = h->GetName();
  c1->Print(("results/histograms/" + folder + "/"        + histname + "_" + file_name + "." + params::ext).c_str());
  if(ifMacros) c1->Print(("results/histograms/" + folder + "/macros/" + histname + "_" + file_name + ".C").c_str());
  delete c1;
}

void Style()
{
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
  // gStyle->SetOptStat(0);
  // gStyle->SetOptFit(0);

  // put tick marks on top and RHS of plots
  gStyle->SetPadTickX(1);
  gStyle->SetPadTickY(1);
}