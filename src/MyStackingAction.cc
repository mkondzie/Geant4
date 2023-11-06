#include "MyStackingAction.h"
#include "G4Track.hh"

#include "G4Electron.hh"
#include "G4Positron.hh"

#include "G4SystemOfUnits.hh"
#include "CLHEP/Units/PhysicalConstants.h"
#include "G4Gamma.hh"

#include "G4StackManager.hh"

G4ClassificationOfNewTrack
MyStackingAction::ClassifyNewTrack(const G4Track* track)
{
  //keep primary particle
 // if ((track->GetParentID() == 0) || (track->GetDefinition() == G4Gamma::Gamma())) return fUrgent;


  //kill secondary electrons and positrons
  if ((track->GetDefinition() == G4Electron::Electron()) || (track->GetDefinition() == G4Positron::Positron())) return fKill;

  
  G4double particleEnergy = track->GetKineticEnergy();
  G4double theta = 1.e-4;
  G4double E0 = 10 * MeV;
  G4double E = 1 / (((1 - cos(theta)) / CLHEP::electron_mass_c2) + 1 / E0);

  if ((track->GetDefinition() == G4Gamma::Gamma()) && (particleEnergy < E)) return fKill;
																	// 9.5 * MeV
  else return fUrgent;
}


void MyStackingAction::NewStage()
{
	G4StackManager* stackManager = new G4StackManager;
	stackManager->ReClassify();
    stackManager->ClearWaitingStack();
}