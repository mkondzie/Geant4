#include "MySensitiveDetector.h"
#include "G4Step.hh"
#include "G4AnalysisManager.hh"
#include "MyPrimaryGenerator.h"
#include "G4RunManager.hh"
#include "G4SystemOfUnits.hh"

MySensitiveDetector::MySensitiveDetector(G4String name) : G4VSensitiveDetector(name) { }

MySensitiveDetector::~MySensitiveDetector() { }

G4bool MySensitiveDetector::ProcessHits(G4Step *aStep, G4TouchableHistory *ROhist)
{
  const MyPrimaryGenerator *primaryGenerator = static_cast<const MyPrimaryGenerator *>(G4RunManager::GetRunManager()->GetUserPrimaryGeneratorAction());

  G4Track *track = aStep->GetTrack();
  track->SetTrackStatus(fStopAndKill);

  G4StepPoint *preStepPoint = aStep->GetPreStepPoint();
  G4StepPoint *postStepPoint = aStep->GetPostStepPoint();

  G4ThreeVector prePosition = preStepPoint->GetPosition();
  G4ThreeVector postPosition = postStepPoint->GetPosition();

  G4ThreeVector position = (prePosition + postPosition) / 2;
  G4double energy = track->GetKineticEnergy();

  G4AnalysisManager *man = G4AnalysisManager::Instance();

  if (track->GetParentID() == 0)
  {
    man->FillH1(1, 0.5);
  }

  if (energy < primaryGenerator->GetPrimaryEnergy())
  {
    man->FillH1(2, 0.5);
    man->FillNtupleDColumn(0, position.x());
    man->FillNtupleDColumn(1, position.y());
    man->FillNtupleDColumn(2, energy);
    man->AddNtupleRow(0);
  }

  if (man->GetH1(3)->entries() == 0)
  {
    man->FillH1(3, 0.5, primaryGenerator->GetPrimaryEnergy());
  }

  return true;
}
