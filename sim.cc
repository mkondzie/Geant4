#include <iostream>

#include "G4RunManager.hh"
#include "G4UImanager.hh"
#include "G4VisManager.hh"
#include "G4VisExecutive.hh"
#include "G4UIExecutive.hh"

#include "construction.hh"
#include "physics.hh"
#include "action.hh"
#include "generator.hh"

#include "G4PhysListFactory.hh"
#include "G4VModularPhysicsList.hh"
#include "Randomize.hh"


int main(int argc, char** argv) {

    G4RunManager *runManager = new G4RunManager();
    runManager->SetUserInitialization(new MyDetectorConstruction());
    

    G4Random::setTheEngine(new CLHEP::RanecuEngine);
 

    G4PhysListFactory physListFactory;
    G4String plName = "FTFP_BERT";
    G4VModularPhysicsList* pList = physListFactory.GetReferencePhysList(plName);
    runManager->SetUserInitialization(pList);
    //runManager->SetUserInitialization(new MyPhysicsList());

    runManager->SetUserInitialization(new MyActionInitialization());
    runManager->Initialize();

    G4UIExecutive *ui = new G4UIExecutive(argc, argv);

    G4VisManager *visManager = new G4VisExecutive;
    visManager->Initialize();


   

    //G4int numberOfEvents = 3;  
    //runManager->BeamOn(numberOfEvents);


    G4UImanager *UImanager = G4UImanager::GetUIpointer();

    UImanager->ApplyCommand("/vis/open OGL");
    UImanager->ApplyCommand("/vis/viewer/set/viewpointVector 1 1 1");
    UImanager->ApplyCommand("/vis/drawVolume");
    UImanager->ApplyCommand("/vis/viewer/set/autoRefresh true");
    UImanager->ApplyCommand("/vis/scene/add/trajectories smooth");

    ui->SessionStart();

    delete runManager;
    delete visManager;
    delete ui;
    return 0;
}



