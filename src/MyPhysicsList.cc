#include "MyPhysicsList.h"
#include "G4EmStandardPhysics.hh"
#include "CLHEP/Units/PhysicalConstants.h"
#include "G4Gamma.hh"
#include "G4PhotoElectricEffect.hh"
#include "G4ComptonScattering.hh"
#include "G4GammaConversion.hh"

MyPhysicsList::MyPhysicsList()
{
  RegisterPhysics(new G4EmStandardPhysics());
  
}


MyPhysicsList::~MyPhysicsList() {




}


void MyPhysicsList::ConstructProcess()
{

	AddTransportation();

	ConstructEM();
}

void MyPhysicsList::ConstructEM()
{

	G4PhysicsListHelper* ph = G4PhysicsListHelper::GetPhysicsListHelper();

	G4ParticleDefinition* particle = G4Gamma::GammaDefinition();


	ph->RegisterProcess(new G4PhotoElectricEffect(), particle);
	ph->RegisterProcess(new G4ComptonScattering(), particle);
	ph->RegisterProcess(new G4GammaConversion(), particle);
}



// G4Double theta = 1.e-4
// G4Double E0 = 10 * MeV
// E = 1 / (((1 - cos(theta)) / CLHEP::electron_mass_c2) + 1 / E0);