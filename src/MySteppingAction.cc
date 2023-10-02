#include "MySteppingAction.h"


MySteppingAction::MySteppingAction(MyEventAction* eventAction) {
    fEventAction = eventAction;
}

MySteppingAction::~MySteppingAction() { }


void MySteppingAction::UserSteppingAction(const G4Step* step)
{
    G4double edep = step->GetTotalEnergyDeposit();
    fEventAction->AddEdep(edep);


    const G4StepPoint* endPoint = step->GetPostStepPoint();
    const G4VProcess* process = endPoint->GetProcessDefinedStep();
    G4cout << process->GetProcessName() << G4endl;

}