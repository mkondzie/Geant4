#include <iostream>
#include "G4RunManager.hh"
#include "G4MTRunManager.hh"
#include "G4UImanager.hh"
#include "G4VisManager.hh"
#include "G4VisExecutive.hh"
#include "G4UIExecutive.hh"

#include "MyDetectorConstruction.h"
#include "MyPhysicsList.h"
#include "MyActionInitialization.h"

#include "G4PhysListFactory.hh"
#include "Randomize.hh"

int main(int argc, char **argv)
{
  G4UIExecutive* ui = nullptr;
  if (argc == 1) { ui = new G4UIExecutive(argc, argv); }


  G4Random::setTheEngine(new CLHEP::RanecuEngine);
  CLHEP::HepRandom::setTheSeed((unsigned)clock());


#ifdef G4MULTITHREADED
  G4MTRunManager* runManager = new G4MTRunManager;
  runManager->SetNumberOfThreads(2 * (G4Threading::G4GetNumberOfCores()));
  G4cout << "Multithreaded" << G4endl;
#else
  G4RunManager* runManager = new G4RunManager;
  G4cout << "Single threaded" << G4endl;
#endif


  runManager->SetUserInitialization(new MyDetectorConstruction());


  


 




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
 



  delete runManager;
  delete visManager;
  //delete ui;


  return 0;
}
