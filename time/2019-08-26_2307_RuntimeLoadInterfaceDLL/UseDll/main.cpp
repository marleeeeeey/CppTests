#include <windows.h>
#include <iostream>
#include <functional>
#include "..\Item_ITF\include\item_interface.h"

int main()
{
    HINSTANCE hGetProcIDDLL = LoadLibrary("ImplementationDLL.dll");

    if(!hGetProcIDDLL) {
        std::cout << "could not load the dynamic library" << std::endl;
        return EXIT_FAILURE;
    }
    
    // resolve function address here
    CreateModuleFunPtr createModuleFunction = (CreateModuleFunPtr)GetProcAddress(hGetProcIDDLL, "createModule");
    if(!createModuleFunction) {
        std::cout << "could not locate the function" << std::endl;
        return EXIT_FAILURE;
    }

    ItemInterface* itemPtr = nullptr;
    int result = createModuleFunction(&itemPtr);
    std::cout << "createModuleFunction returned " << result << std::endl;
    std::cout << "I'm " << itemPtr->toString() << std::endl;

    return EXIT_SUCCESS;
}
