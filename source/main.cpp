#include <array>
#include <stdio.h>
#include <string>
#include <memory>
#include "controller.h"

int main(int argc, char **argv)
{
    std::array<std::shared_ptr<Controller>, 10> controllers {
        std::make_shared<Controller>(CONTROLLER_PLAYER_1),
        std::make_shared<Controller>(CONTROLLER_PLAYER_2),
        std::make_shared<Controller>(CONTROLLER_PLAYER_3),
        std::make_shared<Controller>(CONTROLLER_PLAYER_4),
        std::make_shared<Controller>(CONTROLLER_PLAYER_5),
        std::make_shared<Controller>(CONTROLLER_PLAYER_6),
        std::make_shared<Controller>(CONTROLLER_PLAYER_7),
        std::make_shared<Controller>(CONTROLLER_PLAYER_8),
        std::make_shared<Controller>(CONTROLLER_HANDHELD),
        std::make_shared<Controller>(CONTROLLER_UNKNOWN)
    };

    consoleInit(NULL);

    printf(CONSOLE_RESET CONSOLE_CYAN CONSOLE_ESC(1;1H)"  ___                   _      _____         _       ");
    printf(CONSOLE_RESET CONSOLE_CYAN CONSOLE_ESC(2;1H)" |_ _|_ __  _ __  _   _| |_   |_   _|__  ___| |_     ");
    printf(CONSOLE_RESET CONSOLE_CYAN CONSOLE_ESC(3;1H)"  | || '_ \\| '_ \\| | | | __|____| |/ _ \\/ __| __| ");
    printf(CONSOLE_RESET CONSOLE_CYAN CONSOLE_ESC(4;1H)"  | || | | | |_) | |_| | ||_____| |  __/\\__ \\ |_   ");
    printf(CONSOLE_RESET CONSOLE_CYAN CONSOLE_ESC(5;1H)" |___|_| |_| .__/ \\__,_|\\__|    |_|\\___||___/\\__|");
    printf(CONSOLE_RESET CONSOLE_CYAN CONSOLE_ESC(6;1H)"           |_|                                       ");
    printf(CONSOLE_RESET CONSOLE_CYAN CONSOLE_ESC(8;1H)"v%s - by Xpl0itR (Mark helped a bit too I guess)", VERSION);

    printf(CONSOLE_RESET CONSOLE_WHITE CONSOLE_ESC(7m) CONSOLE_ESC(10;1H)"Controller Status");

    for(auto& controller : controllers) {
        std::string controller_id;
        if (controller->id < 8) controller_id = "#" + std::to_string(controller->id + 1);
        else if (controller->id == 8) controller_id = "Handheld";
        else if (controller->id == 9) controller_id = "Unknown";
    	
        if (controller->isConnected) {
            printf(CONSOLE_RESET CONSOLE_GREEN CONSOLE_ESC(%i;1H)"Controller %s: Connected, singleSet = %d, splitSet = %d", 11 + controller->id, controller_id.c_str(), controller->colors.singleSet, controller->colors.splitSet);
        }
        else if (!controller->isConnected) {
            printf(CONSOLE_RESET CONSOLE_RED CONSOLE_ESC(%i;1H)"Controller %s: Disconnected, singleSet = %d, splitSet = %d", 11 + controller->id, controller_id.c_str(), controller->colors.singleSet, controller->colors.splitSet);
        }
    }

    while(appletMainLoop()) {
        consoleUpdate(NULL);
        hidScanInput();
         
        for(auto& controller : controllers) {
            controller->Update();
			
            if (controller->keys.plus && controller->keys.minus) {
                consoleExit(NULL);
                return 0;
            }

            std::string controller_id;
            if (controller->id < 8) controller_id = "#" + std::to_string(controller->id + 1);
            else if (controller->id == 8) controller_id = "Handheld";
            else if (controller->id == 9) controller_id = "Unknown";

            printf(CONSOLE_WHITE CONSOLE_ESC(7m) CONSOLE_ESC(22;1H)"Stick Status");
            printf(CONSOLE_RESET CONSOLE_WHITE CONSOLE_ESC(%i;1H) CONSOLE_ESC(2K)"Controller %s: %04d %04d %04d %04d", 23 + controller->id, controller_id.c_str(), controller->stick.left.dx,  controller->stick.left.dy, controller->stick.right.dx, controller->stick.right.dy);

            printf(CONSOLE_WHITE CONSOLE_ESC(7m) CONSOLE_ESC(34;1H)"Button Status");
            if(controller->keys.value)
                printf(CONSOLE_RESET CONSOLE_WHITE CONSOLE_ESC(%i;1H) CONSOLE_ESC(2K)"Controller %s: %s", 35 + controller->id, controller_id.c_str(), controller->GetKeyStr().c_str());
            else
                printf(CONSOLE_RESET CONSOLE_WHITE CONSOLE_ESC(%i;1H) CONSOLE_ESC(2K)"Controller %s:", 35 + controller->id, controller_id.c_str());
        }
    }
}
