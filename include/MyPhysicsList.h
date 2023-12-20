#ifndef MyPhysicsList_h
#define MyPhysicsList_h

#include "G4VUserPhysicsList.hh"
#include "G4PhysicsListHelper.hh"
#include "G4ParticleTypes.hh"
/*
class MyPhysicsList : public G4VUserPhysicsList
{
public:
  MyPhysicsList();
  ~MyPhysicsList();

protected:
	void ConstructParticle();
	void ConstructProcess();
	void SetCuts();

public:
	void SetGammaCut(G4double);
	void SetElectronCut(G4double);
	void SetPositronCut(G4double);

private:
	G4double fCutForGamma;
	G4double fCutForElectron;
	G4double fCutForPositron;

protected:
	void ConstructBosons();
	void ConstructLeptons();

protected:
	void ConstructEM();


};
*/ 

#include "G4VModularPhysicsList.hh"
class MyPhysicsList : public G4VModularPhysicsList
{
public:
	MyPhysicsList();
	~MyPhysicsList();

protected:
	void ConstructParticle();
	void ConstructProcess();
	void SetCuts();

public:
	void SetGammaCut(G4double);
	void SetElectronCut(G4double);
	void SetPositronCut(G4double);

private:
	G4double fCutForGamma;
	G4double fCutForElectron;
	G4double fCutForPositron;

protected:
	void ConstructBosons();
	void ConstructLeptons();

protected:
	void ConstructEM();


};
#endif
