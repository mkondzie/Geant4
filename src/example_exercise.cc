#include <iostream>
#include "G4RunManager.hh"
#include "G4UImanager.hh"
#include "G4VisManager.hh"
#include "G4VisExecutive.hh"
#include "G4UIExecutive.hh"

#include "MyDetectorConstruction.h"
#include "MyPhysicsList.h"
#include "MyActionInitialization.h"
#include "MySteppingAction.h"

#include "G4PhysListFactory.hh"
#include "G4VModularPhysicsList.hh"
#include "Randomize.hh"

int main(int argc, char **argv)
{
  G4UIExecutive* ui = nullptr;
  if (argc == 1) { ui = new G4UIExecutive(argc, argv); }

  G4RunManager *runManager = new G4RunManager();
  runManager->SetUserInitialization(new MyDetectorConstruction());


  G4Random::setTheEngine(new CLHEP::RanecuEngine);

  //G4PhysListFactory physListFactory;
  //G4String plName = "FTFP_BERT";
  //G4VModularPhysicsList *pList = physListFactory.GetReferencePhysList(plName);
  //runManager->SetUserInitialization(pList);
  //pList->SetVerboseLevel(1);
  runManager->SetUserInitialization(new MyPhysicsList());

  runManager->SetUserInitialization(new MyActionInitialization());
  runManager->Initialize();


  G4VisManager *visManager = new G4VisExecutive();
  visManager->Initialize();
  G4UImanager *UImanager = G4UImanager::GetUIpointer();
  

if (!ui) {
      // batch mode
      G4String command = "/control/execute ";
      G4String fileName = argv[1];
      UImanager->ApplyCommand(command + fileName);
  }
  else {
      // interactive mode
    

    
    UImanager->ApplyCommand("/vis/open OGL");
    UImanager->ApplyCommand("/vis/viewer/set/viewpointVector 1 1 1");
    UImanager->ApplyCommand("/vis/drawVolume");
    UImanager->ApplyCommand("/vis/viewea/set/autoRefresh true");
    UImanager->ApplyCommand("/vis/scene/add/trajectories smooth");

    ui->SessionStart();
      
      delete ui;

  }
 

//  runManager->BeamOn(1);

  delete runManager;
  delete visManager;
  //delete ui;


  return 0;
}
