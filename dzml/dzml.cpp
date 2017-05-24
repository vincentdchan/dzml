// dzml.cpp : Defines the exported functions for the static library.
//

#include "dzml.h"

// This is an example of an exported variable
int ndzml=0;

// This is an example of an exported function.
int fndzml(void)
{
    return 42;
}

// This is the constructor of a class that has been exported.
// see dzml.h for the class definition
Cdzml::Cdzml()
{
    return;
}
