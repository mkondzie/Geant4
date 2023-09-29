#include "physics.hh"

#include "G4EmStandardPhysics.hh"


MyPhysicsList::MyPhysicsList() {

    RegisterPhysics(new G4EmStandardPhysics());


}



MyPhysicsList::~MyPhysicsList() { 

  


}


