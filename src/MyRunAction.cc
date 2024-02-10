#include "MyRunAction.h"
#include "MyActionInitialization.h"
#include "G4AnalysisManager.hh"
#include "MyPrimaryGenerator.h"
#include "MyDetectorConstruction.h"
#include "G4RunManager.hh"
#include "Randomize.hh"

MyRunAction::MyRunAction()
{
	G4AnalysisManager *man = G4AnalysisManager::Instance();
	man->SetNtupleMerging(true);
	man->Reset();
	man->CreateH1("Primaries", "", 1, 0, 1);
	man->CreateH1("PrimaryHits", "", 1, 0, 1);
	man->CreateH1("ScatteredHits", "", 1, 0, 1);

	man->CreateH1("PrimaryEnergy", "", 1, 0, 1);
	man->CreateH1("CylinderHalfLength", "", 1, 0, 1);

	man->CreateNtuple("Hits", "Hits");
	man->CreateNtupleDColumn("fX");
	man->CreateNtupleDColumn("fY");
	man->CreateNtupleDColumn("fE");
	man->FinishNtuple(0);

	man->CreateNtuple("Scattering", "Scattering");
	man->CreateNtupleDColumn("fTheta");
	man->CreateNtupleDColumn("fEi");
	man->CreateNtupleDColumn("fEf");
	man->CreateNtupleDColumn("fX");
	man->CreateNtupleDColumn("fY");
	man->CreateNtupleDColumn("fZ");
	man->FinishNtuple(1);
}

MyRunAction::~MyRunAction() { }

void MyRunAction::BeginOfRunAction(const G4Run *)
{
	G4AnalysisManager *man = G4AnalysisManager::Instance();
	man->OpenFile("output.root");
}

void MyRunAction::EndOfRunAction(const G4Run *)
{
	G4AnalysisManager *man = G4AnalysisManager::Instance();
	man->Write();
	man->CloseFile(false);
}
