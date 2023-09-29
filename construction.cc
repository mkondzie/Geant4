#include "construction.hh"

#include "G4SystemOfUnits.hh"
#include "G4NistManager.hh"
#include "G4Material.hh"
#include "G4Tubs.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4ThreeVector.hh"
#include "G4Box.hh"

MyDetectorConstruction::MyDetectorConstruction() {

}




MyDetectorConstruction::~MyDetectorConstruction() {

}

G4VPhysicalVolume * MyDetectorConstruction::Construct() {

    G4NistManager* nist = G4NistManager::Instance();
    
    G4double density = 1.0e-25 * g / cm3;
    G4Material *worldMat = new G4Material("void", density, 0, kStateGas);


  


   //G4Tubs* solidCylinder = new G4Tubs("cylinder", 0, 5 * cm, 19.5 * cm, 0, 360 * deg);
   //G4LogicalVolume *logicWorld = new G4LogicalVolume(solidCylinder, worldMat, "logicWorld");


    G4Box* solidWorld = new G4Box("solidWorld", 5 * cm, 5 * cm, 60 * m);
    G4LogicalVolume* logicWorld = new G4LogicalVolume(solidWorld, worldMat, "logicWorld");
   
   G4VPhysicalVolume *physWorld = new G4PVPlacement(0, G4ThreeVector(0., 0., 0.), logicWorld, "physWorld", 0, false, 0, true);

    return physWorld;


}


