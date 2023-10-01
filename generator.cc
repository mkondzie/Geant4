#include "generator.hh"
#include "CLHEP/Units/PhysicalConstants.h"




MyPrimaryGenerator::MyPrimaryGenerator() {

   
    G4int n_particle = 1;
    fParticleGun = new G4ParticleGun(n_particle);

    G4ParticleTable *particleTable = G4ParticleTable::GetParticleTable();
    G4String particleName;
    G4ParticleDefinition* particle
        = particleTable->FindParticle(particleName = "gamma");

    fParticleGun->SetParticleDefinition(particle);
    fParticleGun->SetParticleMomentumDirection(G4ThreeVector(0., 0., 1.));
    fParticleGun->SetParticleEnergy(10.*MeV);

}



MyPrimaryGenerator::~MyPrimaryGenerator() {

    delete fParticleGun;


}



void MyPrimaryGenerator::GeneratePrimaries(G4Event* anEvent) {




  

 

    // To generate a beam with a 1 mm diameter, initial
    // particle positions are randomized within a circle
    G4double radius = 0.5 * mm;
    G4double phi = 2.0 * CLHEP::pi * G4UniformRand();
    G4double r = radius * sqrt(G4UniformRand());  
    G4double x0 = r * cos(phi);
    G4double y0 = r * sin(phi);
    G4double z0 = 0.;


    fParticleGun->SetParticlePosition(G4ThreeVector(x0, y0, z0));








  
    fParticleGun->GeneratePrimaryVertex(anEvent);

}
