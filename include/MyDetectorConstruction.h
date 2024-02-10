#ifndef MYDETECTORCONSTRUCTION_H
#define MYDETECTORCONSTRUCTION_H

#include "G4VUserDetectorConstruction.hh"
#include "G4LogicalVolume.hh"

class G4VPhysicalVolume;
class G4LogicalVolume;

class MyDetectorConstruction : public G4VUserDetectorConstruction 
{
public: 
  MyDetectorConstruction();

  ~MyDetectorConstruction();

  G4LogicalVolume* GetScoringVolume() const { return fScoringVolume; }
  G4double GetCylinderHalfLength() const { return fCylinderHalfLength; }
  virtual G4VPhysicalVolume *Construct();

private:
  G4LogicalVolume * logicDet;
  virtual void ConstructSDandField();

  G4LogicalVolume *fScoringVolume;
  G4double fCylinderHalfLength; 
};
#endif
