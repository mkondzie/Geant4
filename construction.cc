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
    G4Material *worldMat = new G4Material("voidMaterial", density, 0, kStateGas);

    G4Material *copperMat = nist->FindOrBuildMaterial("G4_Cu");
 
    G4Box* solidWorld = new G4Box("solidWorld", 5 * cm, 5 * cm, 60 * cm); //60 * m
    G4LogicalVolume* logicWorld = new G4LogicalVolume(solidWorld, worldMat, "logicWorld");

   G4Tubs* solidCylinder = new G4Tubs("cylinder", 0, 5 * cm, 19.5 * cm, 0, 360 * deg);
   G4LogicalVolume *copperCylinder = new G4LogicalVolume(solidCylinder, copperMat, "solidCylinder");


    


    G4int ndiv = 10;
    //G4Box* solidDet = new G4Box("solidDet", 5/ndiv * cm, 5 / ndiv * cm, 1.e-10 * cm); //60 * m
    //G4LogicalVolume* logicDet = new G4LogicalVolume(solidDet, worldMat, "logicDet");
   
    G4VPhysicalVolume *physWorld = new G4PVPlacement(0, G4ThreeVector(0., 0., 0.), logicWorld, "physWorld", 0, false, 0, true);
    G4VPhysicalVolume* physCylinder = new G4PVPlacement(0, G4ThreeVector(0., 0., 10.*cm), copperCylinder, "physCylinder", logicWorld, false, 0, true);
    //for (G4int i = 0; i < ndiv; i++) {
    //    for (G4int j = 0; j < ndiv; j++) {
            //G4VPhysicalVolume* physDet = new G4PVPlacement(0, G4ThreeVector(-5 * cm + (i+5) * cm/ndiv, -5 * cm + (j + 5) * cm / ndiv, (60 - 1.e-10) * cm), logicDet, "physDet", logicWorld, false, i + j * ndiv, true); // copy number i + j*ndiv
     //   }
    //}

    return physWorld;
  
}


