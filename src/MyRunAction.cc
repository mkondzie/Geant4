#include "MyRunAction.h"
#include "MyActionInitialization.h"
#include "G4AnalysisManager.hh"
#include "MyPrimaryGenerator.h"




MyRunAction::MyRunAction() {

	
	
}



MyRunAction::~MyRunAction() {

}



void MyRunAction::BeginOfRunAction(const G4Run*) {


		G4AnalysisManager* man = G4AnalysisManager::Instance();
		man->OpenFile("output.root");


		man->CreateNtuple("Hits", "Hits");
		man->CreateNtupleDColumn("fX"); //XY position
		man->CreateNtupleDColumn("fY"); //Z fixed to 60.*m
		man->CreateNtupleDColumn("fZ");
		man->CreateNtupleDColumn("fE");
		man->FinishNtuple(0);


		

}



void MyRunAction::EndOfRunAction(const G4Run*) {

	G4AnalysisManager *man = G4AnalysisManager::Instance();
	man->Write();
	man->CloseFile();

}