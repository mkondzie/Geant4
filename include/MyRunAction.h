#ifndef MyRunAction_H
#define MyRunAction_H

#include "G4UserRunAction.hh"

class MyRunAction : public G4UserRunAction
{
public:
	MyRunAction();
	~MyRunAction();
  virtual void BeginOfRunAction(const G4Run*);
  virtual void EndOfRunAction(const G4Run*);
};

#endif

