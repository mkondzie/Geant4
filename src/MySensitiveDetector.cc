#include "MySensitiveDetector.h"
#include "G4Step.hh"
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

  G4ThreeVector prePosition = preStepPoint->GetPosition();
  G4ThreeVector postPosition = postStepPoint->GetPosition();

  G4ThreeVector position = (prePosition + postPosition) / 2;
  G4double energy = track->GetKineticEnergy();
  G4int trackID = track->GetTrackID();
  G4int parentID = track->GetParentID();

  
  G4AnalysisManager* man = G4AnalysisManager::Instance();
 

  man->FillNtupleDColumn(0, position.x());
  man->FillNtupleDColumn(1, position.y());
  man->FillNtupleDColumn(2, position.z());
  man->FillNtupleDColumn(3, energy);
  man->FillNtupleIColumn(4, trackID);
  man->FillNtupleIColumn(5, parentID);

  man->AddNtupleRow(0);
  
 

  return true; 
}

