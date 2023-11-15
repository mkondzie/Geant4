#include <TFile.h>
#include <TTree.h>
#include <TH1F.h>
#include <TH1I.h>
#include <TH2D.h>
#include <TCanvas.h>
#include "TStyle.h"
#include "TLegend.h"

//c://Geant4//geant4-v11.1.2//program_files//share//Geant4//geant4make//step6//build//Release//output.root
void TH2DGeantEnergy(){
TFile *rootFile = new TFile("C://Users//CysiaCysia//Downloads//result.root", "READ");
TTree *tree = (TTree *)rootFile->Get("Hits"); 


TH2D* hist = new TH2D("histYvsE", "", 50, -500, 500, 50, 9.99, 10.0006);


double_t x, y, E;

tree->SetBranchAddress("fX", &x);
tree->SetBranchAddress("fY", &y);
tree->SetBranchAddress("fE", &E);


Long64_t nEntries = tree->GetEntries();
for (Long64_t i = 0; i < nEntries; i++) {
    tree->GetEntry(i);
    hist->Fill(y, E);
   
}

TCanvas *canvas = new TCanvas("canvas", "");
	TLegend* leg = new TLegend(0.58, 0.45, 0.88, 0.86, "", "nbNDC"); //0.6, 0.5, 0.75, 0.75
	leg->SetBorderSize(0);


    canvas->SetLogz();
hist->GetXaxis()->SetTitle("y (mm)");
hist->GetYaxis()->SetTitle("E (MeV)");
hist->GetXaxis()->SetNdivisions(409);
hist->GetYaxis()->SetNdivisions(409);
hist->GetXaxis()->CenterTitle(true);
hist->GetYaxis()->CenterTitle(true);



	
double meanX = hist->GetMean(1);
double meanY = hist->GetMean(2);
double stdDevX = hist->GetStdDev(1);
double stdDevY = hist->GetStdDev(2);

leg->AddEntry((TObject*)0, Form("#mu_{y} = %.0f mm, #sigma_{y} = %.0f mm", meanX, stdDevX), "");
leg->AddEntry((TObject*)0, Form("#mu_{E} = %.4f MeV, #sigma_{E} = %.4f MeV", meanY, stdDevY), "");
leg->AddEntry((TObject*)0, "#theta > 0.0001 rad", "");

gStyle->SetPalette(kAvocado);//Viridis 
gStyle->SetCanvasColor(kWhite);
gStyle->SetLabelOffset(0.05, "XY");
gStyle->SetOptStat(0);
gStyle->SetLegendTextSize(0.057);
gStyle->SetLabelSize(0.07, "XY");

hist->Draw("COLZ");
leg->Draw();
canvas->Update();
canvas->Draw();




}