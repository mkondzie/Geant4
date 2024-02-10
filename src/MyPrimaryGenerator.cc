#include "MyPrimaryGenerator.h"

#include "G4Event.hh"
#include "G4ParticleGun.hh"
#include "G4SystemOfUnits.hh"
#include "G4ParticleTable.hh"
#include "G4ThreeVector.hh"
#include "G4ParticleDefinition.hh"
#include "CLHEP/Units/PhysicalConstants.h"
#include "Randomize.hh"
#include "G4Types.hh"

MyPrimaryGenerator::MyPrimaryGenerator()
{

  G4int nParticles = 5000000; // 1000000
  fParticleGun = new G4ParticleGun(nParticles);
}

MyPrimaryGenerator::~MyPrimaryGenerator()
{

  delete fParticleGun;
}

void MyPrimaryGenerator::GeneratePrimaries(G4Event *ev)
{

  G4ParticleTable *particleTable = G4ParticleTable::GetParticleTable();
  G4String beamPart = "gamma";
  G4ParticleDefinition *particle = particleTable->FindParticle(beamPart);

  G4double radius = 0.5 * mm;
  G4double phi = 2.0 * CLHEP::pi * G4UniformRand();
  G4double r = radius * std::sqrt(G4UniformRand());
  G4double x0 = r * cos(phi);
  G4double y0 = r * sin(phi);
  G4double z0 = 0.;
  fPrimaryEnergy = 10. * MeV;

  G4ThreeVector pos(x0, y0, z0);
  G4ThreeVector mom(0., 0., 1.);

  fParticleGun->SetParticlePosition(pos);
  fParticleGun->SetParticleMomentumDirection(mom);
  fParticleGun->SetParticleEnergy(fPrimaryEnergy);
  fParticleGun->SetParticleDefinition(particle);

  fParticleGun->GeneratePrimaryVertex(ev);
}
