#include "MyActionInitialization.h"
#include "MyPrimaryGenerator.h"
#include "MyRunAction.h"

MyActionInitialization::MyActionInitialization() { }

void MyActionInitialization::Build() const
{
  MyPrimaryGenerator *generator = new MyPrimaryGenerator();
  SetUserAction(generator);

  MyRunAction* runAction = new
	  MyRunAction();
  SetUserAction(runAction);


}
