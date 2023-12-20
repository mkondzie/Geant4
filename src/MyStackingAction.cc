#include "MyStackingAction.h"
#include "G4Track.hh"

#include "G4Electron.hh"
#include "G4Positron.hh"

G4ClassificationOfNewTrack
MyStackingAction::ClassifyNewTrack(const G4Track* track) {

  if ((track->GetDefinition() == G4Electron::Electron()) || (track->GetDefinition() == G4Positron::Positron())) return fKill;

  else return fUrgent;

}