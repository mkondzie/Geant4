#ifndef MyStackingAction_h
#define MyStackingAction_h

#include "G4UserStackingAction.hh"
#include "globals.hh"

class MyStackingAction : public G4UserStackingAction
{
public:
    MyStackingAction() = default;
    ~MyStackingAction() override = default;

    G4ClassificationOfNewTrack ClassifyNewTrack(const G4Track*) override;
};

#endif
