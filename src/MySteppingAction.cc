#include "MySteppingAction.h"
#include "G4RunManager.hh"
#include "G4SystemOfUnits.hh"
#include "CLHEP/Units/PhysicalConstants.h"


MySteppingAction::MySteppingAction(MyEventAction* eventAction) {
    fEventAction = eventAction;
}

MySteppingAction::~MySteppingAction() { }


void MySteppingAction::UserSteppingAction(const G4Step* step)
{

    /*G4Track* track = step->GetTrack();
    
    G4String processName = step->GetTrack()->GetCreatorProcess()->GetProcessName();
    G4cout << "Process Name :" << processName << G4endl;

    G4String particleName = track->GetDefinition()->GetParticleName();
    G4cout << "particle Name:" << particleName << G4endl;

    G4double particleEnergy = track->GetKineticEnergy();
    G4cout << "particle Energy:" << particleEnergy << G4endl;

    G4double theta = 1.e-4;
    G4double E0 = 10 * MeV;
    G4double E = 1 / (((1 - cos(theta)) / CLHEP::electron_mass_c2) + 1 / E0);

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


   // G4Track* track = step->GetTrack();

    //G4String processName = step->GetTrack()->GetCreatorProcess()->GetProcessName();
   // const G4ParticleDefinition* particleDef = track->GetParticleDefinition();



    
   // if (particleDef->GetPDGCharge() == 0.0)
   // {
        

       // if ((processName == "phot") || (processName == "conv")) {

        //    track->SetTrackStatus(fKillTrackAndSecondaries);
       // }


        G4LogicalVolume* volume = step->GetPreStepPoint()->GetTouchableHandle()->GetVolume()->GetLogicalVolume();
        const MyDetectorConstruction* detectorConstruction = static_cast<const MyDetectorConstruction*>
            (G4RunManager::GetRunManager()->GetUserDetectorConstruction());

        G4LogicalVolume* fScoringVolume = detectorConstruction->GetScoringVolume();
        if (volume != fScoringVolume)
            return;

        G4double edep = step->GetTotalEnergyDeposit();
        fEventAction->AddEdep(edep);
  //  }



    

}