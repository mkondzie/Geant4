#include "MySteppingAction.h"
#include "G4RunManager.hh"

#include "G4SystemOfUnits.hh"
#include "CLHEP/Units/PhysicalConstants.h"
#include "G4Gamma.hh"

MySteppingAction::MySteppingAction(MyEventAction* eventAction) {
    fEventAction = eventAction;
}

MySteppingAction::~MySteppingAction() { }

void MySteppingAction::UserSteppingAction(const G4Step* step)
{
    //kill scattered gammas
    G4Track* track = step->GetTrack();
    G4StepPoint* preStepPoint = step->GetPreStepPoint();
    G4StepPoint* postStepPoint = step->GetPostStepPoint();

    G4ThreeVector preMomentum = preStepPoint->GetMomentum();
    G4ThreeVector postMomentum = postStepPoint->GetMomentum();
    G4double cosTheta = preMomentum * postMomentum / (preMomentum.mag() * postMomentum.mag());
    G4double scatteringAngle = std::acos(cosTheta);
    G4double maxScatteringAngle = 0.0001 * rad;
 
    if (scatteringAngle > maxScatteringAngle) {

    track->SetTrackStatus(fKillTrackAndSecondaries);
        
    }


    if ((track->GetDefinition() == G4Gamma::Gamma()) && (track->GetKineticEnergy() < 9.5 * MeV)){
        
    track->SetTrackStatus(fKillTrackAndSecondaries);
        
    }

    
    G4LogicalVolume* volume = step->GetPreStepPoint()->GetTouchableHandle()->GetVolume()->GetLogicalVolume();
        const MyDetectorConstruction* detectorConstruction = static_cast<const MyDetectorConstruction*>
        (G4RunManager::GetRunManager()->GetUserDetectorConstruction());
}
