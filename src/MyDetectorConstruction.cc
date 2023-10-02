#include "MyDetectorConstruction.h"

#include "G4SystemOfUnits.hh"
#include "G4PhysicalConstants.hh"
#include "G4VPhysicalVolume.hh"
#include "G4NistManager.hh"
#include "G4Material.hh"
#include "globals.hh"
#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4ThreeVector.hh"
#include "G4MaterialPropertiesTable.hh"
#include "MySensitiveDetector.h"

MyDetectorConstruction::MyDetectorConstruction() { }

MyDetectorConstruction::~MyDetectorConstruction() { }

G4VPhysicalVolume *MyDetectorConstruction::Construct() {

  G4NistManager *nist = G4NistManager::Instance();
  G4Material* copperMat = nist->FindOrBuildMaterial("G4_Cu");


  G4double A, Z;
  G4Element* elN = new G4Element("Nitrogen", "N", Z = 7., A = 14.00674 * g / mole);
  G4Element* elO = new G4Element("Oxygen", "O", Z = 8., A = 15.9994 * g / mole);
  G4double density;
  G4int nel;
  // vacuum
  density = universe_mean_density;
  G4Material* worldMat = new G4Material("Vacuum", density, nel = 2);
  worldMat->AddElement(elN, .7);
  worldMat->AddElement(elO, .3);
  
  

  G4Box* solidWorld = new G4Box("solidWorld", 0.5 * m, 0.5 * m, 0.8 * m);
  G4LogicalVolume *logicWorld = new G4LogicalVolume(solidWorld, copperMat,"logicWorld");
  G4VPhysicalVolume *physWorld = new G4PVPlacement(0, G4ThreeVector(0.,0.,0.), logicWorld, "physWorld", 0, false, 0, true);


  G4Tubs* solidCylinder = new G4Tubs("cylinder", 0, 5 * cm, 19.5 * cm, 0, 360 * deg);
  G4LogicalVolume* logicCylinder = new G4LogicalVolume(solidCylinder, worldMat, "solidCylinder");
  G4VPhysicalVolume* physCylinder = new G4PVPlacement(0, G4ThreeVector(0., 0., 10. * cm), logicCylinder, "physCylinder", logicWorld, false, 0, true);


  
  int ndiv=10;
  G4Box* solidDet = new G4Box("solidDet", 0.5 / ndiv * m, 0.5 / ndiv * m, 0.01 * m);
  logicDet = new G4LogicalVolume(solidDet, worldMat, "logicDetector");
  
  for (G4int i=0; i<ndiv; i++) {
    for (G4int j=0; j<ndiv; j++) {
      G4VPhysicalVolume *physDet = new G4PVPlacement(0,G4ThreeVector(-0.5*m+(i+0.5)*m/ndiv, -0.5*m+(j+0.5)*m/ndiv, 60*cm),logicDet, "physDet",logicWorld, false, j+i*ndiv, true); 
    }
  }   
   
  return physWorld;
}

void MyDetectorConstruction::ConstructSDandField() {
  MySensitiveDetector *sensDet = new MySensitiveDetector("SensitiveDetector");
  logicDet->SetSensitiveDetector(sensDet);
}
