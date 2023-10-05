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


		man->CreateNtuple("Position", "Position");
		man->CreateNtupleDColumn("fX"); //XY position
		man->CreateNtupleDColumn("fY"); //Z fixed to 60.*m
		man->CreateNtupleDColumn("fZ");
		man->FinishNtuple(0);


		man->CreateNtuple("Energy", "Energy");
		man->CreateNtupleDColumn("fEdep");
		man->FinishNtuple(1);

}



void MyRunAction::EndOfRunAction(const G4Run*) {

	G4AnalysisManager *man = G4AnalysisManager::Instance();
	man->Write();
	man->CloseFile();

}