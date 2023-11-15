#include <TFile.h>
#include <TTree.h>
#include <TH1F.h>
#include <TH1I.h>
#include <TH2D.h>
#include <TCanvas.h>
#include "TStyle.h"
#include "TLegend.h"

//c://Geant4//geant4-v11.1.2//program_files//share//Geant4//geant4make//step6//build//Release//output.root
void TH1FGeant(){
TFile *rootFile = new TFile("C://Users//CysiaCysia//Downloads//result.root", "READ");
TTree *tree = (TTree *)rootFile->Get("Hits"); 



TH1F *hist = new TH1F("hist_fE", "fE Histogram", 1000, 9.995, 10.0002);

double_t E;
tree->SetBranchAddress("fE", &E);

Long64_t nEntries = tree->GetEntries();
for (Long64_t i = 0; i < nEntries; i++) {
    tree->GetEntry(i);
    hist->Fill(E);
}

TCanvas *canvas = new TCanvas("canvas", "");
	TLegend* leg = new TLegend(0.58, 0.45, 0.88, 0.86, "", "nbNDC"); //0.6, 0.5, 0.75, 0.75
	leg->SetBorderSize(0);


    canvas->SetLogy();
hist->GetXaxis()->SetTitle("E (MeV)");
hist->GetXaxis()->SetNdivisions(409);
hist->GetYaxis()->SetNdivisions(409);
hist->GetXaxis()->CenterTitle(true);
hist->GetYaxis()->CenterTitle(true);


int color = 4;
hist ->SetLineColor(color);
hist ->SetFillColor(color);
hist ->SetFillStyle(3002);


//hist_fX->GetXaxis()->SetRangeUser(549.1, 550.31);
//hist_fX->GetYaxis()->SetRangeUser(0.42, 0.79);
hist->SetTitle(" ");





double mean = hist->GetMean();
double stdDev = hist->GetRMS();
	
leg->AddEntry((TObject*)0, Form("#mu_{E} = %.4f MeV, #sigma_{E} = %.4f MeV", mean, stdDev), "");


gStyle->SetCanvasColor(kWhite);
gStyle->SetLabelOffset(0.05, "XY");
gStyle->SetOptStat(0);
gStyle->SetLegendTextSize(0.057);
gStyle->SetLabelSize(0.07, "XY");

hist->Draw("");
leg->Draw();
canvas->Update();
canvas->Draw();




}