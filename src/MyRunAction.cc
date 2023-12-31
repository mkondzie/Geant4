#include "MyRunAction.h"
#include "MyActionInitialization.h"
#include "G4AnalysisManager.hh"
#include "MyPrimaryGenerator.h"
#include "G4RunManager.hh"
#include "Randomize.hh"

MyRunAction::MyRunAction() 
{ }

MyRunAction::~MyRunAction() 
{ }

void MyRunAction::BeginOfRunAction(const G4Run*) {

		G4AnalysisManager* man = G4AnalysisManager::Instance();

		man->OpenFile("output.root");

		man->CreateNtuple("Hits", "Hits");
		man->CreateNtupleDColumn("fX"); 
		man->CreateNtupleDColumn("fY"); 
		man->CreateNtupleDColumn("fE");
		man->FinishNtuple(0);
		
		man->CreateNtuple("Scattering", "Scattering");
		man->CreateNtupleDColumn("fTheta"); 
		man->CreateNtupleDColumn("fpreMomentum");
		man->CreateNtupleDColumn("fpostMomentum");
		man->CreateNtupleDColumn("fX");
		man->CreateNtupleDColumn("fY");
		man->CreateNtupleDColumn("fZ");
		man->FinishNtuple(1);
		
}

void MyRunAction::EndOfRunAction(const G4Run*) {

	G4AnalysisManager *man = G4AnalysisManager::Instance();
	man->Write();
	man->CloseFile();

}