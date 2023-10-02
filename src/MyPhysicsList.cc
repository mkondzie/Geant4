#include "MyPhysicsList.h"
#include "G4EmStandardPhysics.hh"
#include "CLHEP/Units/PhysicalConstants.h"

MyPhysicsList::MyPhysicsList()
{
  RegisterPhysics(new G4EmStandardPhysics());
  
}


MyPhysicsList::~MyPhysicsList() {




}



// G4Double theta = 1.e-4
// G4Double E0 = 10 * MeV
// E = 1 / (((1 - cos(theta)) / CLHEP::electron_mass_c2) + 1 / E0);