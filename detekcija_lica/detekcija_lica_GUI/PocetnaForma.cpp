#include "PocetnaForma.h"
#include <windows.h>
#include <stdlib.h>
#include <string.h>
#include <tchar.h>

using namespace System;
using namespace System::Windows::Forms;
using namespace detekcija_lica_GUI;


[STAThread]
void Main(array<System::String^>^ args)
{
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
	PocetnaForma forma;
	Application::Run(%forma);
}