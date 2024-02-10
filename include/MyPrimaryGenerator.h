#include "G4Types.hh" 
#ifndef MyPrimaryGenerator_H
#define MyPrimaryGenerator_H

#include "G4VUserPrimaryGeneratorAction.hh"

class G4Event;
class  G4ParticleGun;

class MyPrimaryGenerator : public G4VUserPrimaryGeneratorAction 
{
public:
  MyPrimaryGenerator();
  ~MyPrimaryGenerator();
  virtual void GeneratePrimaries( G4Event *ev) ;
  G4double GetPrimaryEnergy() const { return fPrimaryEnergy; }
private:
  G4ParticleGun *fParticleGun;
  G4double fPrimaryEnergy;
};

#endif 
