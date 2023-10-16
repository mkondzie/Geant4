#include "MyActionInitialization.h"
#include "MyPrimaryGenerator.h"
#include "MyRunAction.h"
#include "MyEventAction.h"
#include "MySteppingAction.h"
#include "MyStackingAction.h"
#include "MyStackingAction.h"

MyActionInitialization::MyActionInitialization() { }

void MyActionInitialization::Build() const
{
  MyPrimaryGenerator *generator = new MyPrimaryGenerator();
  SetUserAction(generator);

  MyRunAction* runAction = new MyRunAction();
  SetUserAction(runAction);

  MyEventAction* eventAction = new MyEventAction(runAction);
  SetUserAction(eventAction);

  MySteppingAction* steppingAction = new MySteppingAction(eventAction);
  SetUserAction(steppingAction);

  MyStackingAction* stackingAction = new MyStackingAction();
  SetUserAction(stackingAction);

}
