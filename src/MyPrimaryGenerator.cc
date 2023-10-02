#include "MyPrimaryGenerator.h"

#include "G4Event.hh"
#include "G4ParticleGun.hh"
#include "G4SystemOfUnits.hh"
#include "G4ParticleTable.hh"
#include "G4ThreeVector.hh"
#include "G4ParticleDefinition.hh"
#include "CLHEP/Units/PhysicalConstants.h"
#include "Randomize.hh"

MyPrimaryGenerator::MyPrimaryGenerator() { 
  G4int n_particle = 1;
  fParticleGun = new G4ParticleGun(1);




}

MyPrimaryGenerator::~MyPrimaryGenerator() {
  delete fParticleGun;
}

void MyPrimaryGenerator::GeneratePrimaries(G4Event *ev) {
  G4ParticleTable * particleTable = G4ParticleTable::GetParticleTable();
  G4String beamPart="gamma";
  G4ParticleDefinition *particle=particleTable->FindParticle(beamPart);


  // To generate a beam with a 1 mm diameter, initial
    // particle positions are randomized within a circle
  G4double radius = 0.5 * mm;
  G4double phi = 2.0 * CLHEP::pi * G4UniformRand();
  G4double r = radius * G4UniformRand();
  G4double x0 = r * cos(phi);
  G4double y0 = r * sin(phi);
  G4double z0 = 0.;


  G4ThreeVector pos(0., 0., 0.);
  G4ThreeVector mom(0.,0.,1.);

  fParticleGun->SetParticlePosition(pos);
  fParticleGun->SetParticleMomentumDirection(mom);
  fParticleGun->SetParticleEnergy(10.*MeV);
  fParticleGun->SetParticleDefinition(particle);




  fParticleGun->GeneratePrimaryVertex(ev);
}
