#include "Systems/Window.h"

int main()
{
    std::unique_ptr<Window> mainWindow = std::make_unique<Window>("Engine", 1920, 1800);
   	return 0;  
}