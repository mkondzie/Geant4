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

    G4double particleEnergy = postStepPoint->GetKineticEnergy();
    G4double previousEnergy = preStepPoint->GetKineticEnergy();

    G4double theta = 0.0001 * rad; 
    G4double E = 1 / (((1 - cos(theta)) / CLHEP::electron_mass_c2) + 1 / previousEnergy);
 
    if ((track->GetDefinition() == G4Gamma::Gamma()) && (particleEnergy < E))
    {
        track->SetTrackStatus(fKillTrackAndSecondaries);
    }
    
    G4LogicalVolume* volume = step->GetPreStepPoint()->GetTouchableHandle()->GetVolume()->GetLogicalVolume();
        const MyDetectorConstruction* detectorConstruction = static_cast<const MyDetectorConstruction*>
        (G4RunManager::GetRunManager()->GetUserDetectorConstruction());
}
