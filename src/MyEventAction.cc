#include "MyEventAction.h"
#include "MyRunAction.h"


#include "G4AnalysisManager.hh"





MyEventAction::MyEventAction(MyRunAction*)
	{
	fEdep = 0;
		
	}



MyEventAction::~MyEventAction()
{

}


void MyEventAction::BeginOfEventAction(const G4Event*)
{
	fEdep = 0;

}



void MyEventAction::EndOfEventAction(const G4Event*)
{
	G4cout << "Energy deposition:" << fEdep << G4endl;

	G4AnalysisManager* man = G4AnalysisManager::Instance();
	man->FillNtupleDColumn(1, 0, fEdep);

	man->AddNtupleRow(1);


}

