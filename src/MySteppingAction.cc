#include "MySteppingAction.h"
#include "G4RunManager.hh"

#include "G4SystemOfUnits.hh"
#include "CLHEP/Units/PhysicalConstants.h"
#include "G4Gamma.hh"
#include "G4VProcess.hh"
#include "G4AnalysisManager.hh"

MySteppingAction::MySteppingAction(MyEventAction* eventAction) {
    
    fEventAction = eventAction;
}

MySteppingAction::~MySteppingAction() { }

void MySteppingAction::UserSteppingAction(const G4Step* step)
{
   
    G4Track* track = step->GetTrack();
    G4StepPoint* preStepPoint = step->GetPreStepPoint();
    G4StepPoint* postStepPoint = step->GetPostStepPoint();
    const G4VProcess* process = preStepPoint->GetProcessDefinedStep();

    //kill scattered gammas
    
    if (process && process->GetProcessName() == "compt") {

        G4ThreeVector preMomentum = preStepPoint->GetMomentum();
        G4ThreeVector postMomentum = postStepPoint->GetMomentum();
        G4double cosTheta = preMomentum * postMomentum / (preMomentum.mag() * postMomentum.mag());
        G4double scatteringAngle = std::acos(cosTheta);
        G4double maxScatteringAngle = 0.0001 * rad;

        if (scatteringAngle > maxScatteringAngle) {

            track->SetTrackStatus(fKillTrackAndSecondaries);
        }

        else{
        G4AnalysisManager* man = G4AnalysisManager::Instance();
        G4double preEnergy = preStepPoint->GetKineticEnergy();
        G4double postEnergy = postStepPoint->GetKineticEnergy();

        man->FillNtupleDColumn(1, 0, scatteringAngle / rad);
        man->FillNtupleDColumn(1, 1, preEnergy / MeV);
        man->FillNtupleDColumn(1, 2, postEnergy / MeV);
        man->AddNtupleRow(1);
        }

    }

    /*
        if ((track->GetDefinition() == G4Gamma::Gamma()) && (track->GetKineticEnergy() < 9.5 * MeV))
        {
            track->SetTrackStatus(fKillTrackAndSecondaries);
        }
    */

        if (process && ((process->GetProcessName() == "phot") || 
            (process->GetProcessName() == "conv") || 
            (process->GetProcessName() == "annihil") || 
            (process->GetProcessName() == "eIoni") || 
            (process->GetProcessName() == "eBrem") || 
            (process->GetProcessName() == "msc"))) {

            track->SetTrackStatus(fKillTrackAndSecondaries);
            
        }
        
    G4LogicalVolume* volume = preStepPoint->GetTouchableHandle()->GetVolume()->GetLogicalVolume();
    
    const MyDetectorConstruction* detectorConstruction = static_cast<const MyDetectorConstruction*>
        (G4RunManager::GetRunManager()->GetUserDetectorConstruction());
    
}
