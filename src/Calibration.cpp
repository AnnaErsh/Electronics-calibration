#include <string>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <algorithm>
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

#include "Style.h"
#include "Params.h"

using namespace std;

void ReadConfig()
{
  std::ifstream cFile("Configure.conf");
  if (cFile.is_open())
  {
    std::string line;
    while (getline(cFile, line)) 
    {
      line.erase(std::remove_if(line.begin(), line.end(), ::isspace),line.end());
      if (line[0] == '#' || line.empty()) continue;

      auto delimiterPos = line.find("=");
      auto name = line.substr(0, delimiterPos);
      auto value = line.substr(delimiterPos + 1);

      if (name == "NPeaks")          params::NPeaks     = std::stoi(value);
      else if (name == "MinNEvents") params::MinNEvents = std::stoi(value);
      else if (name == "MinNBins")   params::MinNBins   = std::stoi(value);
      else if (name == "NEvents")    params::NEvents    = std::stoi(value);
      else if (name == "Cut")        params::Cut        = std::stoi(value);
      else if (name == "ifPlotPeaks")params::ifPlotPeaks= std::stoi(value);
      else if (name == "ext")        params::ext        = value;
    }
  }
  else 
  {
    std::cerr << "Couldn't open config file for reading.\n";
  }
  cout << "***** PARAMETERS *****";
  cout << "\nNPeaks = " << params::NPeaks;
  cout << "\nMinNEvents = " << params::MinNEvents;
  cout << "\nMinNBins = " << params::MinNBins;
  cout << "\nNEvents = " << params::NEvents;
  cout << "\nCut = " << params::Cut;
  cout << "\nifPlotPeaks = " << params::ifPlotPeaks;
  cout << "\next = " << params::ext<<"\n";
  cout << "**********************" << "\n";

}

tuple<double, double> histsPlot(TH1I* hist, string file_name, bool ifPlotPeaks = false)
{
	Style();
	string h_name = hist->GetName();
	const int N_PEAKS = params::NPeaks;
	const int TOP_ADC = params::Cut; 				             // we do not go higher to remove saturation peak
	Double_t x[N_PEAKS], y[N_PEAKS];
	int n_hists = 0, n_empty_bins = 0;
	int bin_left = 0, bin_right = 0;
	map<int, double> m_res;
	vector<int> values;
	bool isStarted = false;
	TH1D* h_peak[N_PEAKS];

	// fill X axis
	for (int i = 0; i < N_PEAKS; ++i) x[i] = i + 1;

	for (int i = 0; i < TOP_ADC; ++i)
	{
		int cur_bin  = hist->FindBin(i);
		double value = hist->GetBinContent(cur_bin);

		// value != 1 removes random noise in the beginning
		if(value != 0 && !isStarted && value != 1)         // start histogram
		{
			isStarted = true;
			bin_left = cur_bin - params::MinNBins/2;
		}
		if(isStarted)
		{
			values.push_back(value);                         // fill histogram
		}
		if(value == 0 && isStarted)                        // catch right side of the histogram
			n_empty_bins++;
		else if(value != 0 && isStarted) n_empty_bins = 0;
		if(n_empty_bins >= params::MinNBins && isStarted
			&& values.size() > params::MinNEvents)           // histogram has finished
		{
			bin_right = cur_bin - params::MinNBins/2;        // we won't write all empty bins
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
			if(params::ifPlotPeaks)
			{
				TCanvas* c1 = new TCanvas();
				h_peak[n_hists]->Draw("HIST");
				fit->Draw("same");
				string histname = h_peak[n_hists]->GetName();
				c1->Print(("results/histograms/separation/" + histname + "." + params::ext).c_str());
				c1->Print(("results/histograms/separation/macros/" + histname + ".C").c_str());	
				delete c1;
			}
			delete fit;

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
			x[n_peak] = n_peak + 1;
			y[n_peak] = peak.second;
			n_peak++;
		}
	}

	TCanvas* c2 = new TCanvas();
	TGraph* gr = new TGraphErrors(n_peak, x, y);
	TF1* fit_gr = new TF1("fit_gr", "pol1", 0., 24.);
	gr->SetTitle((h_name + "; peak number; ADC mean").c_str());
	gr->Fit("fit_gr");
	gr->Draw();
	fit_gr->Draw("same");

	auto legend = new TLegend(0.5,0.2,0.8,0.4);
			 legend->AddEntry("fit_gr","p_0 + p_1 * x","l");
			 legend->AddEntry((TObject*)0, ("p_0 = " + to_string(fit_gr->GetParameter(0))).c_str(), "");
			 legend->AddEntry((TObject*)0, ("p_1 = " + to_string(fit_gr->GetParameter(1))).c_str(), "");
	legend->Draw();
	c2->Print(("results/histograms/lines/line_" + h_name + "_" + file_name + "." + params::ext).c_str());
	c2->Print(("results/histograms/lines/macros/line_" + h_name + "_" + file_name + ".C").c_str());

	delete c2;
	delete gr;
	double p0 = fit_gr->GetParameter(0);
	double p1 = fit_gr->GetParameter(1);
	delete fit_gr;
	return std::make_tuple(p0, p1);
}

int main(int argc, char** argv)
{
	Style();
	ReadConfig();

	const int WIDTH  = 36;
	const int HEIGHT = 32;
	const int DEPTH  = 510;

	string name = argv[1];
	ofstream out_files("results/txt/file_names.txt", ios_base::app);

	TFile* file = new TFile((name).c_str());

	size_t found = name.find_last_of("/\\");
	string file_name = name.substr(found + 1);
	file_name.resize(file_name.size() - 5);

	cout<<"file_name: "<<file_name<<endl;
	out_files<<file_name<<endl;
	ofstream out(("results/txt/" + file_name + ".txt").c_str());
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
   	histo[x][y] = new TH1I(("h_" + to_string(x) + "_" + to_string(y)).c_str(), ("Pad" + to_string(x) + "_" + to_string(y) + "; ADC; counts").c_str(), 4096, 1, 4096);
  }

	//*******************
	//    main action
	//*******************

	double nentries = tree->GetEntries();
	cout << "entries: " << nentries << endl;

	for (int event = 0; event < nentries; ++event)
	{
		tree->GetEntry(event);
		if(event%100 == 0) cout << "progress:" << setw(4) << setprecision(2) << double(event)/nentries * 100. << "%" << '\r' << flush;
		for (int x = 0; x < WIDTH; ++x) for (int y = 0; y < HEIGHT; ++y)
		{
			for (int t = 0; t < DEPTH; ++t)
			{
				PadAmpl[x][y][t]-= 250;                        // remove pedestal
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
		if(histo[x][y]->GetEntries() > params::NEvents && histo[x][y]->GetMean() > 900)
		{
			double p0 = 0, p1 = 0;
			HistPrint(histo[x][y], file_name, "HIST", "peaks");
			tie(p0, p1) = histsPlot(histo[x][y], file_name, false);
			out<<histo[x][y]->GetName()<<" "<<p0<<" "<<p1<<" "<<x<<" "<<y<<endl;
		}
	}
	HistPrint(h_ampl, file_name, "COLZ", "ampl");

	delete h_ampl;
	for (int x = 0; x < WIDTH; ++x) for (int y = 0; y < HEIGHT; ++y) delete histo[x][y];
	delete file;
	return 0;
}
