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
	
  //kill secondary electrons and positrons
  if ((track->GetDefinition() == G4Electron::Electron()) || (track->GetDefinition() == G4Positron::Positron())) return fKill;

  G4double particleEnergy = track->GetKineticEnergy();
  if ((track->GetDefinition() == G4Gamma::Gamma()) && (particleEnergy < 9.5 * MeV)) return fKill;
  	
  //keep primary particles  
  else return fUrgent;
}
