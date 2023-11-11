#include "MyStackingAction.h"
#include "G4Track.hh"

#include "G4Electron.hh"
#include "G4Positron.hh"

#include "G4SystemOfUnits.hh"
#include "CLHEP/Units/PhysicalConstants.h"
#include "G4Gamma.hh"

#include "G4StackManager.hh"


/*
const G4double theta = 1.e-4;
const G4double E0 = 10 * MeV;
const G4double E = 1 / (((1 - cos(theta)) / CLHEP::electron_mass_c2) + 1 / E0);
*/

G4ClassificationOfNewTrack
MyStackingAction::ClassifyNewTrack(const G4Track* track)
{
  //keep primary particle
 // if ((track->GetParentID() == 0) || (track->GetDefinition() == G4Gamma::Gamma())) return fUrgent;


  //kill secondary electrons and positrons
  if ((track->GetDefinition() == G4Electron::Electron()) || (track->GetDefinition() == G4Positron::Positron())) return fKill;

  
  G4double particleEnergy = track->GetKineticEnergy();
  if ((track->GetDefinition() == G4Gamma::Gamma()) && (particleEnergy < 9.5 * MeV)) return fKill;
  																			// E
  
  else return fUrgent;
}


void MyStackingAction::NewStage()
{/*
	G4StackManager* stackManager = new G4StackManager;
	stackManager->ReClassify();
    stackManager->ClearWaitingStack();
	*/
}