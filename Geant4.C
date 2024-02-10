#include <TFile.h>
#include <TTree.h>
#include <TH1F.h>
#include <TH1I.h>
#include <TH2D.h>
#include <TCanvas.h>
#include "TStyle.h"
#include "TLegend.h"
#include "TLatex.h"
#include "TProfile2D.h"
#include "TProfile.h"
#include "TColor.h"
#include <iomanip> 

std::string formatInExponentialNotation(double value) {
	double mantissa;
	int exponent = std::log10(std::abs(value));
	mantissa = value / std::pow(10, exponent);

	std::ostringstream stream;
	if (std::abs(exponent) < 2){
		stream << value;
	}
	else {
		stream << mantissa << " #upoint 10^{" << exponent << "}";
	}
	return stream.str();
}

void Geant4() {
	TFile* rootFile = new TFile("output_0.root", "READ");

	TH1D* primaries; 
	TH1D* primaryHits; 
	TH1D* scatteredHits;
	TH1D* cylinderHalfLengthHist;
	rootFile->GetObject("Primaries", primaries);
	rootFile->GetObject("PrimaryHits", primaryHits);
	rootFile->GetObject("ScatteredHits", scatteredHits);
	rootFile->GetObject("CylinderHalfLength", cylinderHalfLengthHist);
	double cylinderLength = 2 * (cylinderHalfLengthHist->GetSumOfWeights()) / (10 * cylinderHalfLengthHist->GetEntries());
	//2 is for converting half to full length, dividing by 10 to convert mm to cm, dividing by number of entries (threads)

	std::string sumOfWeightsString = formatInExponentialNotation(primaries->GetSumOfWeights());
	std::string primaryHitsString = formatInExponentialNotation(primaryHits->GetEntries());
	std::string scatteredHitsString = formatInExponentialNotation(scatteredHits->GetEntries());
	std::string cylinderLengthString = formatInExponentialNotation(cylinderLength);
	//////////////////////////////
	TCanvas* canvas = new TCanvas("canvas", "", 670, 600);
	canvas->Print("Geant.pdf[");
	TPaveText* t = new TPaveText(.05, .1, .95, .8);
	t->AddText("");
	t->AddText((cylinderLengthString + " cm cylinder").c_str()); 
	t->AddLine(0, 0.5, 1, 0.5);
	t->AddText(""); 

	t->SetTextAlign(12);
	t->AddText(("Primary photons: " + sumOfWeightsString).c_str());
	t->AddText(("Primary hits: " + primaryHitsString).c_str());
	t->AddText(("Scattered hits: " + scatteredHitsString).c_str());
	t->Draw();

	canvas->Print("Geant.pdf");
	//////////////////////////
	TTree* scattering;
	rootFile->GetObject("Scattering", scattering);
	TH2D* histScatteringXY = new TH2D("", "", 34, -0.55, 0.55, 34, -0.55, 0.55);
	TH1F* histScatteringZ = new TH1F("", "", 100, 10000 - cylinderLength * 5.1, 10000 + 5.1 * cylinderLength);

	double_t x, y, z, E;
	scattering->SetBranchAddress("fX", &x);
	scattering->SetBranchAddress("fY", &y);
	scattering->SetBranchAddress("fZ", &z);

	/////////
	for (Long64_t i = 0; i < scattering->GetEntries(); i++) {
		scattering->GetEntry(i);
		histScatteringXY->Fill(x, y);
		histScatteringZ->Fill(z);
	}

	gStyle->SetPalette(kCandy);
	TColor::InvertPalette();
	gStyle->SetCanvasColor(kWhite);
	gStyle->SetOptStat(0);
	histScatteringXY->GetXaxis()->SetNdivisions(409);
	histScatteringXY->GetYaxis()->SetNdivisions(409);
	histScatteringXY->GetXaxis()->SetTitle("x (mm)");
	histScatteringXY->GetXaxis()->SetLabelSize(0.04);
	histScatteringXY->GetYaxis()->SetLabelSize(0.04);
	histScatteringXY->GetZaxis()->SetLabelSize(0.04);
	histScatteringXY->GetYaxis()->SetLabelOffset(0.005);
	histScatteringXY->GetXaxis()->SetLabelOffset(0.005);
	histScatteringXY->GetXaxis()->SetTitleOffset(1.2);
	histScatteringXY->GetYaxis()->SetTitleOffset(1);
	histScatteringXY->GetYaxis()->SetTitle("y (mm)");
	histScatteringXY->SetTitle("Compton scattering positions");
	histScatteringXY->GetZaxis()->SetRangeUser(0, 8);
	histScatteringXY->GetXaxis()->CenterTitle(true);
	histScatteringXY->GetYaxis()->CenterTitle(true);
	histScatteringXY->Draw("COLZ");

	canvas->Print("Geant.pdf");
	//////////////////////////

	//n of major divisions to 5 and n of minor divisions to 4
	histScatteringZ->GetXaxis()->SetNdivisions(505, 4);
	histScatteringZ->GetXaxis()->SetTitle("z (mm)");
	histScatteringZ->GetYaxis()->SetTitle("counts");
	histScatteringZ->SetTitle("Compton scattering positions");
	histScatteringZ->GetYaxis()->SetNdivisions(409);
	histScatteringZ->GetXaxis()->SetLabelSize(0.04);
	histScatteringZ->GetYaxis()->SetLabelSize(0.04);
	histScatteringZ->GetYaxis()->SetLabelOffset(0.005);
	histScatteringZ->GetXaxis()->SetLabelOffset(0.005);
	histScatteringZ->GetXaxis()->CenterTitle(true);
	histScatteringZ->GetYaxis()->CenterTitle(true);
	histScatteringZ->GetXaxis()->SetTitleOffset(1.2);

	histScatteringZ->SetLineColor(kAzure + 2);
	histScatteringZ->SetFillColor(kAzure + 2);
	histScatteringZ->SetFillStyle(3002);

	gStyle->SetCanvasColor(kWhite);
	gStyle->SetOptStat(0);
	histScatteringZ->Draw("");
	canvas->Print("Geant.pdf");
	///////////////////////////////////////////
	TTree* hits;
	TH1D* primaryEnergyHist;
	rootFile->GetObject("Hits", hits);
	rootFile->GetObject("PrimaryEnergy", primaryEnergyHist);
	double primaryEnergy = primaryEnergyHist->GetSumOfWeights() / primaryEnergyHist->GetEntries();

	auto profHitsXY = new TProfile2D("", "", 25, -5.99, 5.9, 25, -5.99, 5.9, -1, 0);
	auto profHitsEr = new TProfile("", "", 28, 0.01, 6, -1, 0);
	TH1D* histHitsr = new TH1D("", "", 35, 0.01, 6);

	hits->SetBranchAddress("fX", &x);
	hits->SetBranchAddress("fY", &y);
	hits->SetBranchAddress("fE", &E);

	Long64_t nEntries = hits->GetEntries();
	for (Long64_t i = 0; i < nEntries; i++) {
		hits->GetEntry(i);
		//profHitsXY->Fill(x, y, (E - 10) * 1e6);
		profHitsXY->Fill(x, y, (E - primaryEnergy) * 1e6);
		//profHitsEr->Fill(std::sqrt(x * x + y * y), (E - 10) * 1e6);
		profHitsEr->Fill(std::sqrt(x * x + y * y), (E - primaryEnergy) * 1e6);
		histHitsr->Fill(std::sqrt(x * x + y * y));
	}

	gStyle->SetPalette(kViridis);
	profHitsXY->GetZaxis()->SetRangeUser(-1, 0);
	profHitsXY->GetXaxis()->SetNdivisions(409);
	profHitsXY->GetYaxis()->SetNdivisions(409);
	profHitsXY->GetXaxis()->SetLabelSize(0.04);
	profHitsXY->GetZaxis()->SetLabelSize(0.04);
	profHitsXY->GetYaxis()->SetLabelSize(0.04);
	profHitsXY->GetYaxis()->SetLabelOffset(0.005);
	profHitsXY->GetXaxis()->SetLabelOffset(0.005);
	profHitsXY->GetXaxis()->SetTitle("x (mm)");
	profHitsXY->GetYaxis()->SetTitle("y (mm)");
	profHitsXY->SetTitle("Scattered photons #DeltaE (eV)");

	profHitsXY->GetXaxis()->SetTitleOffset(1.2);
	profHitsXY->GetXaxis()->CenterTitle(true);
	profHitsXY->GetYaxis()->CenterTitle(true);
	profHitsXY->Draw("COLZ");
	canvas->SetRightMargin(0.12);
	canvas->Print("Geant.pdf");

	//////////////////////////
	canvas->SetRightMargin(0.05);
	profHitsEr->GetXaxis()->SetNdivisions(505, 4);
	profHitsEr->GetYaxis()->SetNdivisions(505, 4);
	profHitsEr->GetXaxis()->SetLabelSize(0.034);
	profHitsEr->GetYaxis()->SetLabelSize(0.033);
	profHitsEr->GetZaxis()->SetLabelSize(0.038);
	profHitsEr->GetYaxis()->SetLabelOffset(0.005);
	profHitsEr->GetXaxis()->SetLabelOffset(0.005);
	profHitsEr->GetXaxis()->SetTitle("r (mm)");
	profHitsEr->GetYaxis()->SetTitle("#DeltaE (eV)");
	profHitsEr->GetXaxis()->SetTitleOffset(1.2);
	profHitsEr->GetYaxis()->SetTitleOffset(1.4);
	profHitsEr->GetXaxis()->CenterTitle(true);
	profHitsEr->GetYaxis()->CenterTitle(true);
	profHitsEr->SetLineColor(kSpring - 7);
	profHitsEr->SetTitle("Scattered photons");
	gStyle->SetEndErrorSize(3);
	gStyle->SetErrorX(1.);
	profHitsEr->SetMarkerStyle(21);
	profHitsEr->SetMarkerSize(0.7);
	profHitsEr->Draw("E1"); 

	canvas->Print("Geant.pdf");

	///////////////////////////

	histHitsr->GetXaxis()->SetNdivisions(505, 5);
	histHitsr->GetYaxis()->SetNdivisions(505, 4);
	histHitsr->GetXaxis()->SetLabelSize(0.04);
	histHitsr->GetYaxis()->SetLabelSize(0.04);
	histHitsr->GetYaxis()->SetLabelOffset(0.005);
	histHitsr->GetXaxis()->SetLabelOffset(0.005);
	histHitsr->GetXaxis()->SetTitle("r (mm)");
	histHitsr->GetYaxis()->SetTitle("counts");
	histHitsr->GetXaxis()->SetTitleOffset(1.2);
	histHitsr->GetXaxis()->CenterTitle(true);
	histHitsr->GetYaxis()->CenterTitle(true);
	histHitsr->SetLineColor(kAzure - 9);
	histHitsr->SetFillColor(kAzure - 9);
	histHitsr->SetFillStyle(3002);
	histHitsr->SetTitle("Scattered photons");
	histHitsr->Draw();

	canvas->Print("Geant.pdf");
	canvas->Print("Geant.pdf]");
}
