#ifndef MySteppingAction_H
#define MySteppingAction_H

#include "G4UserSteppingAction.hh"
#include "G4Step.hh"
#include "MyDetectorConstruction.h"
#include "MyEventAction.h"


class MySteppingAction : public G4UserSteppingAction
{
public:
	MySteppingAction(MyEventAction* eventAction);
    ~MySteppingAction();

	virtual void UserSteppingAction(const G4Step*);
private:
	MyEventAction* fEventAction;
};
#endif
