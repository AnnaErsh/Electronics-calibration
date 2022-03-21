#include <string>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <tuple>
#include <map>

#include "TFile.h"
#include "TTree.h"
#include "TLeaf.h"
#include "TH2D.h"
#include "TH2I.h"
#include "TF1.h"
#include "TLeafD.h"
#include "TCanvas.h"
#include "TStyle.h"
#include "TGraph.h"
#include "TGraphErrors.h"
#include "TMath.h"
#include "TLegend.h"

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

void HistPrint(TH1I* h, string file_name)
{
	TCanvas* c1 = new TCanvas();
	h->Draw("HIST");
	string histname = h->GetName();
	c1->Print(("hists/" + histname + "_" + file_name + ".pdf").c_str());
	c1->Print(("hists/macros/" + histname + "_" + file_name + ".C").c_str());
	delete c1;
}

tuple<double, double> histsPlot(TH1I* hist, string file_name)
{
	Style();
	string h_name = hist->GetName();
	ofstream debug("debug.txt", std::ios::app);
	const int N_PEAKS = 25;
	Double_t x[N_PEAKS], y[N_PEAKS];
	int n_hists = 0, n_empty_bins = 0;
	int bin_left = 0, bin_right = 0;
	map<int, double> m_res;

	vector<int> values;

	bool isStarted = false;

	TH1D* h_peak[N_PEAKS];

	// fill X axis
	for (int i = 0; i < N_PEAKS; ++i) x[i] = i + 1;

	for (int i = 0; i < 4096; ++i)
	{
		int cur_bin = hist->FindBin(i);
		double value = hist->GetBinContent(cur_bin);

		// value != 1 removes random noise in the beginning
		if(value != 0 && !isStarted && value != 1)    // start histogram
		{
			// out<<"value != 0 && !isStarted "<<i<<endl;
			isStarted = true;
			bin_left = cur_bin - 5;
		}
		if(isStarted)
		{
			values.push_back(value);                    // fill histogram
			// out<<"value = "<<value<<endl;
		}
		if(value == 0 && isStarted)                   // catch right side of the histogram
			n_empty_bins++;
		else if(value != 0 && isStarted) n_empty_bins = 0;
		if(n_empty_bins >= 20 && isStarted) // histogram has finished
		{
			bin_right = cur_bin - 10;                   // we won't write all empty bins
			int n_bins = bin_right - bin_left;
			h_peak[n_hists] = new TH1D((h_name + to_string(n_hists)).c_str(), ("h_peak_" + to_string(n_hists) + "; ADC; counts").c_str(), n_bins, bin_left, bin_right);

			// fill histogram
			for (uint bin = 0; bin < values.size(); ++bin)
			{
				h_peak[n_hists]->SetBinContent(bin, values[bin]);
			}

			TF1 *fit = new TF1("fit", "gaus", bin_left, bin_right);
			h_peak[n_hists]->Fit("fit", "s", "", bin_left, bin_right);
			m_res[n_hists] = fit->GetParameter(1);

			// for Gaussian distribution:
			// 0 - constant
			// 1 - mean
			// 2 - sigma

			// TCanvas* c1 = new TCanvas();
			// h_peak[n_hists]->Draw("HIST");
			// fit->Draw("same");
			// string histname = h_peak[n_hists]->GetName();
			// c1->Print(("hists/separation/" + histname + ".pdf").c_str());
			// c1->Print(("hists/separation/macros/" + histname + ".C").c_str());

			n_hists++;

			// clean data
			bin_left = 0, bin_right = 0;
			n_empty_bins = 0;
			isStarted = false;
			values.clear();
		}
	} // 4096 loop

	int n_peak = 0;
	for(const auto & peak : m_res)
	{
		if(peak.second != 0)
		{
			x[n_peak] = n_peak;
			y[n_peak] = peak.second;
			debug<<h_name<<" "<<x[n_peak]<<" "<<y[n_peak]<<endl;
			n_peak++;
		}
	}

	TCanvas* c2 = new TCanvas();
	TGraph* gr = new TGraphErrors(n_peak, x, y);
	TF1* fit_gr = new TF1("fit_gr", "pol1", 0., 24.);
	gr->SetTitle((h_name + "; peak number; ADS mean").c_str());
	gr->Fit("fit_gr");
	gr->Draw();
	fit_gr->Draw("same");

	auto legend = new TLegend(0.5,0.2,0.8,0.4);
			 legend->AddEntry("fit_gr","p_0 + p_1 * x","l");
			 legend->AddEntry((TObject*)0, ("p_0 = " + to_string(fit_gr->GetParameter(0))).c_str(), "");
			 legend->AddEntry((TObject*)0, ("p_1 = " + to_string(fit_gr->GetParameter(1))).c_str(), "");
	legend->Draw();
	c2->Print(("hists/plot_" + h_name + "_" + file_name + ".pdf").c_str());
	return std::make_tuple(fit_gr->GetParameter(0), fit_gr->GetParameter(1));
}

int main(int argc, char** argv)
{
	const int WIDTH  = 36;
	const int HEIGHT = 32;
	const int DEPTH  = 510;

	string name = argv[1];
	cout<<name<<endl;

	TFile* file = new TFile((name).c_str());
	string file_name = name.erase(0, 11);
	file_name.resize(file_name.size() - 5);
	cout<<file_name<<endl;
	ofstream out(("txt/" + file_name + ".txt").c_str());
	TTree* tree = (TTree*) file->Get("tree");
	Int_t PadAmpl[WIDTH][HEIGHT][DEPTH];
	tree->SetBranchAddress("PadAmpl",	&PadAmpl);

	double arr_ampl[WIDTH][HEIGHT] = {0};

	TH2D* h_ampl = new TH2D("h_ampl", "map of maximal amplitude", WIDTH, 0, WIDTH, HEIGHT, 0, HEIGHT);

	cout<<tree->GetEntries()<<endl;

	TH1I *histo[WIDTH][HEIGHT];
	double max[WIDTH][HEIGHT] = {0};
  for (int x = 0; x < WIDTH; ++x) for (int y = 0; y < HEIGHT; ++y)
	{
   	histo[x][y] = new TH1I(("h_" + to_string(x) + "_" + to_string(y)).c_str(), ("Pad" + to_string(x) + "_" + to_string(y) + "; ADS; counts").c_str(), 4096, 1, 4096);
  }

	//*******************
	//    main action
	//*******************

	double nentries = tree->GetEntries();

	for (int event = 0; event < nentries; ++event)
	{
		tree->GetEntry(event);
		if(event%100 == 0) cout<<setw(7)<<double(event)/nentries * 100.<<"%"<<'\r'<<flush;
		for (int x = 0; x < WIDTH; ++x) for (int y = 0; y < HEIGHT; ++y)
		{
			for (int t = 0; t < DEPTH; ++t)
			{
				if (PadAmpl[x][y][t]>max[x][y]) max[x][y]=PadAmpl[x][y][t];
			}
		}

		for (int x = 0; x < WIDTH; ++x) for (int y = 0; y < HEIGHT; ++y)
		{
			if(max[x][y] != 0)
			{
				histo[x][y]->Fill(max[x][y]);
				h_ampl->Fill(x, y, max[x][y]);
				arr_ampl[x][y]+=max[x][y];
			}
			max[x][y]=0;
		}
	}

	//*******************
	//   print results
	//*******************

	for (int x = 0; x < WIDTH; ++x) for (int y = 0; y < HEIGHT; ++y)
	{
		if(histo[x][y]->GetEntries() > 23990 && histo[x][y]->GetMean() > 900)
		{
			double p0 = 0, p1 = 0;
			HistPrint(histo[x][y], file_name);
			tie(p0, p1) = histsPlot(histo[x][y], file_name);
			out<<histo[x][y]->GetName()<<" "<<p0<<" "<<p1<<endl;
		}
	}
	TCanvas* c1 = new TCanvas();
	h_ampl->Draw("COLZ");
	c1->Print(("hists/amplCOLZ_" + file_name + ".pdf").c_str());
	c1->Print(("hists/amplCOLZ_" + file_name + ".C").c_str());

	delete file;
	return 0;
}
