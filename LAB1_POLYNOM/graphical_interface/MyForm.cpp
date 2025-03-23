#include "MyForm.h"
#include "../polynom/test_for_form.h"
using namespace System;
using namespace System::Windows::Forms;

[STAThread]
void main(array<String^>^ arg) {
    Application::EnableVisualStyles();
    Application::SetCompatibleTextRenderingDefault(false);

    graphicalinterface::MyForm form; 
    Application::Run(% form);
}

