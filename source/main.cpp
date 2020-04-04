#include <array>
#include <iomanip>
#include <stdio.h>
#include <string>
#include <sstream>
#include <memory>
#include "controller.h"

const char* to_hex_string(const int i) {
    std::stringstream stream;
    stream << "0x" << std::setfill('0') << std::setw(6) << std::hex << i;
    return stream.str().c_str();
}

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

    printf(CONSOLE_RESET CONSOLE_WHITE CONSOLE_ESC(2;60H)"Hold - and Press");
    printf(CONSOLE_RESET CONSOLE_WHITE CONSOLE_ESC(3;60H)"A for Input");
    printf(CONSOLE_RESET CONSOLE_WHITE CONSOLE_ESC(4;60H)"B for Color");

    printf(CONSOLE_RESET CONSOLE_WHITE CONSOLE_ESC(7m) CONSOLE_ESC(10;1H)"Controller Status");

    for (std::shared_ptr<Controller>& controller : controllers) {
        std::string controller_id;
        if (controller->id < 8) controller_id = "#" + std::to_string(controller->id + 1);
        else if (controller->id == 8) controller_id = "Handheld";
        else if (controller->id == 9) controller_id = "Unknown";
        
        if (controller->isConnected) {
            printf(CONSOLE_RESET CONSOLE_GREEN CONSOLE_ESC(%i;1H)"Controller %s: Connected", 11 + controller->id, controller_id.c_str());
        }
        else if (!controller->isConnected) {
            printf(CONSOLE_RESET CONSOLE_RED CONSOLE_ESC(%i;1H)"Controller %s: Disconnected", 11 + controller->id, controller_id.c_str());
        }
    }

    std::string status   = "input";
    int controller_index = 0;

    while(appletMainLoop()) {
        consoleUpdate(NULL);
         
        for (std::shared_ptr<Controller>& controller : controllers) {
            controller->Update();
            
            if (controller->keys.minus && controller->keys.plus) {
                consoleExit(NULL);
                return 0;
            }

            if (controller->keys.minus && controller->keys.a)
                status = "input";
            else if (controller->keys.minus && controller->keys.b)
                status = "color";
            else if (controller->keys.minus && controller->keys.dpadLeft)
                controller_index -= 1;
            else if (controller->keys.minus && controller->keys.dpadRight)
                controller_index += 1;

            if (controller_index < 0)
                controller_index = 0;
            if (controller_index > 9)
                controller_index = 9;

            std::string controller_id;
            if (controller->id < 8) controller_id = "#" + std::to_string(controller->id + 1);
            else if (controller->id == 8) controller_id = "Handheld";
            else if (controller->id == 9) controller_id = "Unknown";

            if (status == "input") {
                printf(CONSOLE_RESET CONSOLE_ESC(6;51H) CONSOLE_ESC(2K));
                printf(CONSOLE_RESET CONSOLE_ESC(7;51H) CONSOLE_ESC(2K));
                printf(CONSOLE_WHITE CONSOLE_ESC(22;1H) CONSOLE_ESC(2K) CONSOLE_ESC(7m)"Stick Status");
                printf(CONSOLE_RESET CONSOLE_WHITE CONSOLE_ESC(%i;1H) CONSOLE_ESC(2K)"Controller %s: %04d %04d %04d %04d", 23 + controller->id, controller_id.c_str(), controller->stick.left.dx, controller->stick.left.dy, controller->stick.right.dx, controller->stick.right.dy);

                printf(CONSOLE_WHITE CONSOLE_ESC(34;1H) CONSOLE_ESC(2K) CONSOLE_ESC(7m)"Button Status");
                if (controller->keys.value)
                    printf(CONSOLE_RESET CONSOLE_WHITE CONSOLE_ESC(%i;1H) CONSOLE_ESC(2K)"Controller %s: %s", 35 + controller->id, controller_id.c_str(), controller->GetKeyStr().c_str());
                else
                    printf(CONSOLE_RESET CONSOLE_WHITE CONSOLE_ESC(%i;1H) CONSOLE_ESC(2K)"Controller %s:", 35 + controller->id, controller_id.c_str());
            }
            else if (status == "color") {
                printf(CONSOLE_RESET CONSOLE_WHITE CONSOLE_ESC(6;51H)"DLeft for Previous Controller");
                printf(CONSOLE_RESET CONSOLE_WHITE CONSOLE_ESC(7;51H)"DRight for Next Controller");
                printf(CONSOLE_WHITE CONSOLE_ESC(22;1H) CONSOLE_ESC(2K) CONSOLE_ESC(7m)"Set Status");
                printf(CONSOLE_RESET CONSOLE_WHITE CONSOLE_ESC(%i;1H) CONSOLE_ESC(2K)"Controller %s: singleSet = %d, splitSet = %d ", 23 + controller->id, controller_id.c_str(), controller->colors.singleSet, controller->colors.splitSet);

                if (controller->id == controller_index)
                {
                    printf(CONSOLE_WHITE CONSOLE_ESC(34;1H) CONSOLE_ESC(2K) CONSOLE_ESC(7m)"Controller %s: Color Status", controller_id.c_str());

                    printf(CONSOLE_RESET CONSOLE_WHITE CONSOLE_ESC(35;1H) CONSOLE_ESC(2K)"Single Color Body:    %s", to_hex_string(controller->colors.singleColorBody));
                    printf(CONSOLE_RESET CONSOLE_WHITE CONSOLE_ESC(36;1H) CONSOLE_ESC(2K)"Single Color Buttons: %s", to_hex_string(controller->colors.singleColorButtons));
                    printf(CONSOLE_RESET CONSOLE_WHITE CONSOLE_ESC(37;1H) CONSOLE_ESC(2K)"Left   Color Body:    %s", to_hex_string(controller->colors.leftColorBody));
                    printf(CONSOLE_RESET CONSOLE_WHITE CONSOLE_ESC(38;1H) CONSOLE_ESC(2K)"Left   Color Buttons: %s", to_hex_string(controller->colors.leftColorButtons));
                    printf(CONSOLE_RESET CONSOLE_WHITE CONSOLE_ESC(39;1H) CONSOLE_ESC(2K)"Right  Color Body:    %s", to_hex_string(controller->colors.rightColorBody));
                    printf(CONSOLE_RESET CONSOLE_WHITE CONSOLE_ESC(40;1H) CONSOLE_ESC(2K)"Right  Color Buttons: %s", to_hex_string(controller->colors.rightColorButtons));
                }

                printf(CONSOLE_RESET CONSOLE_ESC(41;1H) CONSOLE_ESC(2K));
                printf(CONSOLE_RESET CONSOLE_ESC(42;1H) CONSOLE_ESC(2K));
                printf(CONSOLE_RESET CONSOLE_ESC(43;1H) CONSOLE_ESC(2K));
                printf(CONSOLE_RESET CONSOLE_ESC(44;1H) CONSOLE_ESC(2K));
            }
        }
    }
}