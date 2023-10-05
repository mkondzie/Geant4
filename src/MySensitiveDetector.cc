#include "MySensitiveDetector.h"

#include "G4Step.hh"
#include "G4TouchableHistory.hh"
#include "G4AnalysisManager.hh"
#include "G4RunManager.hh"



MySensitiveDetector::MySensitiveDetector(G4String name) : G4VSensitiveDetector(name) 
{ }

MySensitiveDetector::~MySensitiveDetector()
{}


G4bool MySensitiveDetector::ProcessHits(G4Step *aStep, G4TouchableHistory *ROhist){
  G4Track *track = aStep->GetTrack();
  track->SetTrackStatus(fStopAndKill);
  G4StepPoint *preStepPoint = aStep->GetPreStepPoint(); 
  G4StepPoint *postStepPoint = aStep->GetPostStepPoint(); 

  G4ThreeVector position = preStepPoint->GetPosition();

  const G4VTouchable *touchable = aStep->GetPreStepPoint()->GetTouchable();
  G4int copuNo = touchable->GetCopyNumber();
  G4VPhysicalVolume *physVol = touchable->GetVolume();  
  G4ThreeVector posDetector = physVol->GetTranslation();
  G4cout << "Det number :"<<copuNo<<" and position: "<<posDetector << G4endl;

  

  G4AnalysisManager* man = G4AnalysisManager::Instance();
  man->FillNtupleDColumn(0, posDetector[0]);
  man->FillNtupleDColumn(1, posDetector[1]);
  man->FillNtupleDColumn(2, posDetector[2]);
  man->AddNtupleRow(0);

  return true; 
}

