#ifndef GENERATOR_HH
#define GENERATOR_HH

#include "G4Event.hh"
#include "G4VUserPrimaryGeneratorAction.hh"
#include "G4ParticleGun.hh"
#include "G4SystemOfUnits.hh"
#include "G4ParticleTable.hh"
#include "G4ThreeVector.hh"
#include "G4ParticleDefinition.hh"


class G4Event;
class G4ParticleGun;

class MyPrimaryGenerator : public G4VUserPrimaryGeneratorAction
{

public:
    MyPrimaryGenerator();
    ~MyPrimaryGenerator();


    virtual void GeneratePrimaries(G4Event *anEvent);

private:
    G4ParticleGun *fParticleGun;

};
#endif




