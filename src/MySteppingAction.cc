#include "MySteppingAction.h"
#include "G4RunManager.hh"

#include "G4SystemOfUnits.hh"
#include "CLHEP/Units/PhysicalConstants.h"
#include "G4Gamma.hh"

//#include "MyStackingAction.h"
//G4double previousEnergy = 10 * MeV;

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

    G4double particleEnergy = postStepPoint->GetKineticEnergy();//track->GetKineticEnergy();
    G4double previousEnergy = preStepPoint->GetKineticEnergy();

    G4double theta = 0.0001 * rad; // 1.e-4
    G4double E = 1 / (((1 - cos(theta)) / CLHEP::electron_mass_c2) + 1 / previousEnergy);
 
   
  
    if ((track->GetDefinition() == G4Gamma::Gamma()) && (particleEnergy < E))
    {
        track->SetTrackStatus(fKillTrackAndSecondaries);
    }
    
    //G4double previousEnergy = track->GetKineticEnergy();




    G4LogicalVolume* volume = step->GetPreStepPoint()->GetTouchableHandle()->GetVolume()->GetLogicalVolume();
        const MyDetectorConstruction* detectorConstruction = static_cast<const MyDetectorConstruction*>
        (G4RunManager::GetRunManager()->GetUserDetectorConstruction());


    /* //string comparison - slow
    G4String processName = step->GetTrack()->GetCreatorProcess()->GetProcessName();

    G4String particleName = track->GetDefinition()->GetParticleName();

    G4int parentId = track->GetParentID();

    const G4ParticleDefinition* particleDef = track->GetParticleDefinition();

    if ((processName == "phot") || (processName == "conv")) {

        track->SetTrackStatus(fKillTrackAndSecondaries);
    }

    if ((processName == "compt") && (particleName == "gamma") && (particleEnergy < E)) {

        track->SetTrackStatus(fKillTrackAndSecondaries);
    }

    if ((processName == "compt") && ((particleName == "e-") || (particleName == "e+")) && (parentId > 0)) {

        track->SetTrackStatus(fKillTrackAndSecondaries);
    }

    */

   // if (particleDef->GetPDGCharge() == 0.0)
   // {
       // if ((processName == "phot") || (processName == "conv")) {
        //    track->SetTrackStatus(fKillTrackAndSecondaries);
       // }



    
      


    

}