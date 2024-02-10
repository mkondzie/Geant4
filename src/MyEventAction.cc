#include "MyEventAction.h"
#include "MyRunAction.h"
#include "G4SystemOfUnits.hh"
#include "G4AnalysisManager.hh"

MyEventAction::MyEventAction(MyRunAction *) {}

MyEventAction::~MyEventAction() {}

void MyEventAction::BeginOfEventAction(const G4Event *) {}

void MyEventAction::EndOfEventAction(const G4Event *event)
{

    G4AnalysisManager *man = G4AnalysisManager::Instance();
    man->FillH1(0, 0.5, event->GetPrimaryVertex()->GetNumberOfParticle());
}

