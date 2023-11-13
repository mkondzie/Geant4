#include "MySteppingAction.h"
#include "G4RunManager.hh"

#include "G4SystemOfUnits.hh"
#include "CLHEP/Units/PhysicalConstants.h"
#include "G4Gamma.hh"
#include "G4VProcess.hh"
#include "G4AnalysisManager.hh"

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
    const G4VProcess* process = preStepPoint->GetProcessDefinedStep();

   // G4double particleEnergy = postStepPoint->GetKineticEnergy();//track->GetKineticEnergy();
   // G4double previousEnergy = preStepPoint->GetKineticEnergy();

  

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
        

    /*
    G4double E = previousEnergy / (1 + (previousEnergy / (CLHEP::electron_mass_c2)) * (1 - cos(theta)));

    if ((track->GetDefinition() == G4Gamma::Gamma()) && (particleEnergy < E))
    {
        track->SetTrackStatus(fKillTrackAndSecondaries);
    }
    */


    //G4double previousEnergy = track->GetKineticEnergy();


    G4LogicalVolume* volume = preStepPoint->GetTouchableHandle()->GetVolume()->GetLogicalVolume();
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