#include <string.h>
#include <stdio.h>
#include <array>
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

    printf("\x1b[1;1HPress PLUS to exit.");

    for(auto& controller : controllers) {
        if (controller->color.singleSet)
            printf("\x1b[%i;1HController #%i: singleColorBody = 0x%08x, singleColorButtons = 0x%08x", 3 + (controller->id * 2), controller->id, controller->color.singleColorBody, controller->color.singleColorButtons);
        if (controller->color.splitSet)
            printf("\x1b[%i;1HController #%i: leftColorBody  = 0x%08x, leftColorButtons  = 0x%08x\nController #%i: rightColorBody = 0x%08x, rightColorButtons = 0x%08x", 4 + (controller->id * 2), controller->id, controller->color.leftColorBody, controller->color.leftColorButtons, controller->id, controller->color.rightColorBody, controller->color.rightColorButtons);
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

            printf("\x1b[%i;1H\x1b[2KController #%i: %04d %04d %04d %04d", 23 + controller->id, controller->id, controller->stick.left.dx,  controller->stick.left.dy, controller->stick.right.dx, controller->stick.right.dy);

            if(controller->keys.value)
                printf("\x1b[%i;1H\x1b[2KController #%i: %s", 33 + controller->id, controller->id, controller->GetKeyStr().c_str());
            else
                printf("\x1b[%i;1H\x1b[2KController #%i: Nothing pressed", 33 + controller->id, controller->id);
        }
    }
}
