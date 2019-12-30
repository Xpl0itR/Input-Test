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

    printf(CONSOLE_CYAN CONSOLE_ESC(1;1H)" ______                           __           ______                __");
    printf(CONSOLE_CYAN CONSOLE_ESC(2;1H)"/\\__  _\\                         /\\ \\__       /\\__  _\\              /\\ \\__");
    printf(CONSOLE_CYAN CONSOLE_ESC(3;1H)"\\/_/\\ \\/     ___   _____   __  __\\ \\ ,_\\      \\/_/\\ \\/    __    ____\\ \\ ,_\\");
    printf(CONSOLE_CYAN CONSOLE_ESC(4;1H)"   \\ \\ \\   /' _ `\\/\\ '__`\\/\\ \\/\\ \\\\ \\ \\/  _______\\ \\ \\  /'__`\\ /',__\\\\ \\ \\/");
    printf(CONSOLE_CYAN CONSOLE_ESC(5;1H)"    \\_\\ \\__/\\ \\/\\ \\ \\ \\L\\ \\ \\ \\_\\ \\\\ \\ \\_/\\______\\\\ \\ \\/\\  __//\\__, `\\\\ \\ \\_");
    printf(CONSOLE_CYAN CONSOLE_ESC(6;1H)"    /\\_____\\ \\_\\ \\_\\ \\ ,__/\\ \\____/ \\ \\__\\/______/ \\ \\_\\ \\____\\/\\____/ \\ \\__\\");
    printf(CONSOLE_CYAN CONSOLE_ESC(7;1H)"    \\/_____/\\/_/\\/_/\\ \\ \\/  \\/___/   \\/__/          \\/_/\\/____/\\/___/   \\/__/");
    printf(CONSOLE_CYAN CONSOLE_ESC(8;1H)"                     \\ \\_\\");
    printf(CONSOLE_CYAN CONSOLE_ESC(9;1H)"                      \\/_/");
	printf(CONSOLE_BLUE CONSOLE_ESC(10;1H)"v%d.%d.%d - by Xpl0itR", 1, 2, 0);
                                                                         
	
    printf(CONSOLE_WHITE CONSOLE_ESC(7m) CONSOLE_ESC(12;1H)"Controller Status");

    for(auto& controller : controllers) {
        std::string controller_id = "#" + std::to_string(controller->id + 1);
        if      (controller_id == "#9")  controller_id = "Handheld";
        else if (controller_id == "#10") controller_id = "Unknown";
    	
        if (controller->isConnected) {
            printf(CONSOLE_RESET CONSOLE_GREEN CONSOLE_ESC(%i;1H)"Controller %s: Connected", 13 + controller->id, controller_id.c_str());
        }
        else if (!controller->isConnected) {
            printf(CONSOLE_RESET CONSOLE_RED CONSOLE_ESC(%i;1H)"Controller %s: Disconnected", 13 + controller->id, controller_id.c_str());
        }
    }

    while(appletMainLoop()) {
        consoleUpdate(NULL);
        hidScanInput();
         
        for(auto& controller : controllers) {
            controller->Update();
			
            if (controller->keys.plus) {
                consoleExit(NULL);
                return 0;
            }

            std::string controller_id = "#" + std::to_string(controller->id + 1);
            if      (controller_id == "#9")  controller_id = "Handheld";
            else if (controller_id == "#10") controller_id = "Unknown";

            printf(CONSOLE_WHITE CONSOLE_ESC(7m) CONSOLE_ESC(24;1H)"Stick Status");
            printf(CONSOLE_RESET CONSOLE_WHITE CONSOLE_ESC(%i;1H) CONSOLE_ESC(2K)"Controller %s: %04d %04d %04d %04d", 25 + controller->id, controller_id.c_str(), controller->stick.left.dx,  controller->stick.left.dy, controller->stick.right.dx, controller->stick.right.dy);

            printf(CONSOLE_WHITE CONSOLE_ESC(7m) CONSOLE_ESC(36;1H)"Button Status");
            if(controller->keys.value)
                printf(CONSOLE_RESET CONSOLE_WHITE CONSOLE_ESC(%i;1H) CONSOLE_ESC(2K)"Controller %s: %s", 37 + controller->id, controller_id.c_str(), controller->GetKeyStr().c_str());
            else
                printf(CONSOLE_RESET CONSOLE_WHITE CONSOLE_ESC(%i;1H) CONSOLE_ESC(2K)"Controller %s:", 37 + controller->id, controller_id.c_str());
        }
    }
}
