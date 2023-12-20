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
    const G4VProcess* process = postStepPoint->GetProcessDefinedStep();

    if (process && process->GetProcessName() == "compt") {

        G4ThreeVector preMomentum = preStepPoint->GetMomentum();
        G4ThreeVector postMomentum = postStepPoint->GetMomentum();

        if ((preMomentum.mag() * postMomentum.mag()) == 0) {

            track->SetTrackStatus(fKillTrackAndSecondaries);
        }
        
            G4double cosTheta = preMomentum.dot(postMomentum) / (preMomentum.mag() * postMomentum.mag());

            if (cosTheta >= 1 || cosTheta <= -1) {

                track->SetTrackStatus(fKillTrackAndSecondaries);

               }

                G4double scatteringAngle = std::acos(cosTheta);
                G4double maxScatteringAngle = 0.0001 * rad; 

                if (scatteringAngle > maxScatteringAngle) {

                    track->SetTrackStatus(fKillTrackAndSecondaries);

                }

                else {

                    G4AnalysisManager* man = G4AnalysisManager::Instance();
                    G4ThreeVector postPosition = postStepPoint->GetPosition();

                    man->FillNtupleDColumn(1, 0, scatteringAngle / rad);
                    man->FillNtupleDColumn(1, 1, preMomentum.mag());
                    man->FillNtupleDColumn(1, 2, postMomentum.mag());
                    man->FillNtupleDColumn(1, 3, postPosition.x());
                    man->FillNtupleDColumn(1, 4, postPosition.y());
                    man->FillNtupleDColumn(1, 5, postPosition.z());
                    man->AddNtupleRow(1);

                }

    }
   
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
