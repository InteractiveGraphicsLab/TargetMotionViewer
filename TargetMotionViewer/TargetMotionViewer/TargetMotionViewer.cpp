#include "FormMain.h"

using namespace System;
using namespace TargetMotionViewer;

[STAThreadAttribute]
int main()
{
  FormMain::getInst()->ShowDialog();
  return 0;
}
