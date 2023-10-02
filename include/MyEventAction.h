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
		
		
	virtual void BeginOfEventAction(const G4Event*);
	virtual void EndOfEventAction(const G4Event*);

	void AddEdep(G4double edep) {
		fEdep += edep;
	}
private:
	G4double fEdep;

};

#endif

