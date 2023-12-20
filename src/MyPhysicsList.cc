#include "MyPhysicsList.h"

#include "G4Gamma.hh"
#include "G4Electron.hh"
#include "G4Positron.hh"

#include "G4VUserPhysicsList.hh"
#include "G4ParticleDefinition.hh"

#include "G4ProcessManager.hh"
#include "G4ParticleTypes.hh"
#include "G4ParticleTable.hh"

#include "G4SystemOfUnits.hh"
#include "CLHEP/Units/PhysicalConstants.h"

#include "G4PhotoElectricEffect.hh"
#include "G4ComptonScattering.hh"
#include "G4GammaConversion.hh"


#include "G4eMultipleScattering.hh"
#include "G4eIonisation.hh"
#include "G4eBremsstrahlung.hh"
#include "G4eplusAnnihilation.hh"

#include "G4VModularPhysicsList.hh"
#include "G4StepLimiterPhysics.hh"

MyPhysicsList::MyPhysicsList() : G4VUserPhysicsList()
{
	fCutForGamma = 0.7 * mm;
	fCutForElectron = 1000 * km;
	fCutForPositron = 1000 * km;
	
	SetVerboseLevel(1);
	/*
	G4StepLimiterPhysics* stepLimitPhys = new G4StepLimiterPhysics();
	stepLimitPhys->SetApplyToAll(true); 
	RegisterPhysics(stepLimitPhys);*/
}

MyPhysicsList::~MyPhysicsList() 
{

}

void MyPhysicsList::ConstructParticle()
{
	ConstructBosons();
	ConstructLeptons();
}

void MyPhysicsList::ConstructBosons()
{
	G4Gamma::GammaDefinition();
}

void MyPhysicsList::ConstructLeptons()
{
	G4Electron::ElectronDefinition();
	G4Positron::PositronDefinition();
}

void MyPhysicsList::ConstructProcess()
{
	AddTransportation();
	ConstructEM();
}

void MyPhysicsList::ConstructEM()
{
	
	G4PhysicsListHelper* ph = G4PhysicsListHelper::GetPhysicsListHelper();
	auto particleIterator = GetParticleIterator();
	particleIterator->reset();

	while ((*particleIterator)()) {

		G4ParticleDefinition* particle = particleIterator->value();

		G4String particleName = particle->GetParticleName();

		if (particleName == "gamma") {

			ph->RegisterProcess(new G4PhotoElectricEffect(), particle);
			ph->RegisterProcess(new G4ComptonScattering(), particle);
			ph->RegisterProcess(new G4GammaConversion(), particle);

		}
		
		else if (particleName == "e-") {

			ph->RegisterProcess(new G4eMultipleScattering(), particle);
			ph->RegisterProcess(new G4eIonisation(), particle);
			ph->RegisterProcess(new G4eBremsstrahlung(), particle);

		}
		else if (particleName == "e+") {

			ph->RegisterProcess(new G4eMultipleScattering(), particle);
			ph->RegisterProcess(new G4eIonisation(), particle);
			ph->RegisterProcess(new G4eBremsstrahlung(), particle);
			ph->RegisterProcess(new G4eplusAnnihilation(), particle);

		}
		
	}

}

void MyPhysicsList::SetCuts()
{
		SetCutValue(fCutForGamma, "gamma");
		SetCutValue(fCutForElectron, "e-");
		SetCutValue(fCutForPositron, "e+");

		if (verboseLevel > 0) DumpCutValuesTable();
}

void MyPhysicsList::SetGammaCut(G4double val)
{
	fCutForGamma = val;
}

void MyPhysicsList::SetElectronCut(G4double val)
{
	fCutForElectron = val;
}

void MyPhysicsList::SetPositronCut(G4double val)
{
	fCutForPositron = val;
}
