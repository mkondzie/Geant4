#ifndef MyStackingAction_h
#define MyStackingAction_h

#include "G4UserStackingAction.hh"
#include "globals.hh"


/// Stacking action class : manage the newly generated particles
/// One wishes do not track secondary electrons and positrons.
/// Therefore one kills it immediately, before created particles will be put in a stack.

class MyStackingAction : public G4UserStackingAction
{
public:
    MyStackingAction() = default;
    ~MyStackingAction() override = default;

    G4ClassificationOfNewTrack ClassifyNewTrack(const G4Track*) override;
    void NewStage() override;
};

extern const G4double E;

#endif
