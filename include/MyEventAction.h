#ifndef MyEventAction_H
#define MyEventAction_H

#include "G4UserEventAction.hh"
#include "G4Event.hh"
#include "G4AnalysisManager.hh"
#include "MyRunAction.h"

class MyEventAction : public G4UserEventAction
{
public:
	MyEventAction(MyRunAction*);
	~MyEventAction();

	void BeginOfEventAction(const G4Event*) override;
	void EndOfEventAction(const G4Event*) override;

};

#endif
