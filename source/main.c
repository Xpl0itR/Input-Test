#include <string.h>
#include <stdio.h>

#include <switch.h>

int main(int argc, char **argv)
{
    char keysNames[32][32] = {
        "KEY_A", "KEY_B", "KEY_X", "KEY_Y",
        "KEY_LSTICK", "KEY_RSTICK", "KEY_L", "KEY_R",
        "KEY_ZL", "KEY_ZR", "KEY_PLUS", "KEY_MINUS",
        "KEY_DLEFT", "KEY_DUP", "KEY_DRIGHT", "KEY_DDOWN",
        "KEY_LSTICK_LEFT", "KEY_LSTICK_UP", "KEY_LSTICK_RIGHT", "KEY_LSTICK_DOWN",
        "KEY_RSTICK_LEFT", "KEY_RSTICK_UP", "KEY_RSTICK_RIGHT", "KEY_RSTICK_DOWN",
        "KEY_SL_LEFT", "KEY_SR_LEFT", "KEY_SL_RIGHT", "KEY_SR_RIGHT",
        "KEY_TOUCH", "", "", ""
    };

    consoleInit(NULL);

	u32 p1kDownOld = 0, p1kHeldOld = 0, p1kUpOld = 0, p2kDownOld = 0, p2kHeldOld = 0, p2kUpOld = 0, p3kDownOld = 0, p3kHeldOld = 0, p3kUpOld = 0, p4kDownOld = 0, p4kHeldOld = 0, p4kUpOld = 0,
		p5kDownOld = 0, p5kHeldOld = 0, p5kUpOld = 0, p6kDownOld = 0, p6kHeldOld = 0, p6kUpOld = 0, p7kDownOld = 0, p7kHeldOld = 0, p7kUpOld = 0, p8kDownOld = 0, p8kHeldOld = 0, p8kUpOld = 0,
		phkDownOld = 0, phkHeldOld = 0, phkUpOld = 0;

	printf("\x1b[1;1HPress PLUS to exit.");

	while(appletMainLoop())
    {
         hidScanInput();

		 u64 p1kDown = hidKeysDown(CONTROLLER_PLAYER_1);
		 u64 p1kHeld = hidKeysHeld(CONTROLLER_PLAYER_1);
		 u64 p1kUp   = hidKeysUp(CONTROLLER_PLAYER_1);

		 u64 p2kDown = hidKeysDown(CONTROLLER_PLAYER_2);
		 u64 p2kHeld = hidKeysHeld(CONTROLLER_PLAYER_2);
		 u64 p2kUp   = hidKeysUp(CONTROLLER_PLAYER_2);

		 u64 p3kDown = hidKeysDown(CONTROLLER_PLAYER_3);
		 u64 p3kHeld = hidKeysHeld(CONTROLLER_PLAYER_3);
		 u64 p3kUp   = hidKeysUp(CONTROLLER_PLAYER_3);

		 u64 p4kDown = hidKeysDown(CONTROLLER_PLAYER_4);
		 u64 p4kHeld = hidKeysHeld(CONTROLLER_PLAYER_4);
		 u64 p4kUp   = hidKeysUp(CONTROLLER_PLAYER_4);

		 u64 p5kDown = hidKeysDown(CONTROLLER_PLAYER_5);
		 u64 p5kHeld = hidKeysHeld(CONTROLLER_PLAYER_5);
		 u64 p5kUp   = hidKeysUp(CONTROLLER_PLAYER_5);

		 u64 p6kDown = hidKeysDown(CONTROLLER_PLAYER_6);
		 u64 p6kHeld = hidKeysHeld(CONTROLLER_PLAYER_6);
		 u64 p6kUp   = hidKeysUp(CONTROLLER_PLAYER_6);

		 u64 p7kDown = hidKeysDown(CONTROLLER_PLAYER_7);
		 u64 p7kHeld = hidKeysHeld(CONTROLLER_PLAYER_7);
		 u64 p7kUp   = hidKeysUp(CONTROLLER_PLAYER_7);

		 u64 p8kDown = hidKeysDown(CONTROLLER_PLAYER_8);
		 u64 p8kHeld = hidKeysHeld(CONTROLLER_PLAYER_8);
		 u64 p8kUp   = hidKeysUp(CONTROLLER_PLAYER_8);

		 u64 phkDown = hidKeysDown(CONTROLLER_HANDHELD);
		 u64 phkHeld = hidKeysHeld(CONTROLLER_HANDHELD);
		 u64 phkUp   = hidKeysUp(CONTROLLER_HANDHELD);

        if ((p1kDown & KEY_PLUS) || (p2kDown & KEY_PLUS) || (p3kDown & KEY_PLUS) || (p4kDown & KEY_PLUS) || (p5kDown & KEY_PLUS) || (p6kDown & KEY_PLUS) || (p7kDown & KEY_PLUS) || (p8kDown & KEY_PLUS) || (phkDown & KEY_PLUS)) break;

        if (p1kDown != p1kDownOld || p1kHeld != p1kHeldOld || p1kUp != p1kUpOld || p2kDown != p2kDownOld || p2kHeld != p2kHeldOld || p2kUp != p2kUpOld || p3kDown != p3kDownOld || p3kHeld != p3kHeldOld || p3kUp != p3kUpOld ||
			p4kDown != p4kDownOld || p4kHeld != p4kHeldOld || p4kUp != p4kUpOld || p5kDown != p5kDownOld || p5kHeld != p5kHeldOld || p5kUp != p5kUpOld || p6kDown != p6kDownOld || p6kHeld != p6kHeldOld || p6kUp != p6kUpOld ||
			p7kDown != p7kDownOld || p7kHeld != p7kHeldOld || p7kUp != p7kUpOld || p8kDown != p8kDownOld || p8kHeld != p8kHeldOld || p8kUp != p8kUpOld || phkDown != phkDownOld || phkHeld != phkHeldOld || phkUp != phkUpOld)
        {
            consoleClear();

			printf("\x1b[1;1HPress PLUS to exit.");

			printf("\x1b[32;1H");

			for (int i = 0; i < 32; i++)
            {
                if (p1kDown & BIT(i)) printf("Controller 1: %s down\n", keysNames[i]);
                if (p1kHeld & BIT(i)) printf("Controller 1: %s held\n", keysNames[i]);
                if (p1kUp   & BIT(i)) printf("Controller 1: %s up\n",   keysNames[i]);

				if (p2kDown & BIT(i)) printf("Controller 2: %s down\n", keysNames[i]);
                if (p2kHeld & BIT(i)) printf("Controller 2: %s held\n", keysNames[i]);
                if (p2kUp   & BIT(i)) printf("Controller 2: %s up\n",   keysNames[i]);

				if (p3kDown & BIT(i)) printf("Controller 3: %s down\n", keysNames[i]);
                if (p3kHeld & BIT(i)) printf("Controller 3: %s held\n", keysNames[i]);
                if (p3kUp   & BIT(i)) printf("Controller 3: %s up\n",   keysNames[i]);

				if (p4kDown & BIT(i)) printf("Controller 4: %s down\n", keysNames[i]);
                if (p4kHeld & BIT(i)) printf("Controller 4: %s held\n", keysNames[i]);
                if (p4kUp   & BIT(i)) printf("Controller 4: %s up\n",   keysNames[i]);

				if (p5kDown & BIT(i)) printf("Controller 5: %s down\n", keysNames[i]);
                if (p5kHeld & BIT(i)) printf("Controller 5: %s held\n", keysNames[i]);
                if (p5kUp   & BIT(i)) printf("Controller 5: %s up\n",   keysNames[i]);

				if (p6kDown & BIT(i)) printf("Controller 6: %s down\n", keysNames[i]);
                if (p6kHeld & BIT(i)) printf("Controller 6: %s held\n", keysNames[i]);
                if (p6kUp   & BIT(i)) printf("Controller 6: %s up\n",   keysNames[i]);

				if (p7kDown & BIT(i)) printf("Controller 7: %s down\n", keysNames[i]);
                if (p7kHeld & BIT(i)) printf("Controller 7: %s held\n", keysNames[i]);
                if (p7kUp   & BIT(i)) printf("Controller 7: %s up\n",   keysNames[i]);

				if (p8kDown & BIT(i)) printf("Controller 8: %s down\n", keysNames[i]);
                if (p8kHeld & BIT(i)) printf("Controller 8: %s held\n", keysNames[i]);
                if (p8kUp   & BIT(i)) printf("Controller 8: %s up\n",   keysNames[i]);

            	if (phkDown & BIT(i)) printf("Controller H: %s down\n", keysNames[i]);
                if (phkHeld & BIT(i)) printf("Controller H: %s held\n", keysNames[i]);
                if (phkUp   & BIT(i)) printf("Controller H: %s up\n",   keysNames[i]);
            }
        }

        p1kDownOld = p1kDown;
        p1kHeldOld = p1kHeld;
        p1kUpOld   = p1kUp;

		p2kDownOld = p2kDown;
		p2kHeldOld = p2kHeld;
		p2kUpOld   = p2kUp;

		p3kDownOld = p3kDown;
		p3kHeldOld = p3kHeld;
		p3kUpOld   = p3kUp;

		p4kDownOld = p4kDown;
		p4kHeldOld = p4kHeld;
		p4kUpOld   = p4kUp;

		p5kDownOld = p5kDown;
        p5kHeldOld = p5kHeld;
        p5kUpOld   = p5kUp;

		p6kDownOld = p6kDown;
		p6kHeldOld = p6kHeld;
		p6kUpOld   = p6kUp;

		p7kDownOld = p7kDown;
		p7kHeldOld = p7kHeld;
		p7kUpOld   = p7kUp;

		p8kDownOld = p8kDown;
		p8kHeldOld = p8kHeld;
		p8kUpOld   = p8kUp;

    	phkDownOld = phkDown;
		phkHeldOld = phkHeld;
		phkUpOld   = phkUp;

		HidControllerColors p1color, p2color, p3color, p4color, p5color, p6color, p7color, p8color, phcolor;

		hidGetControllerColors(CONTROLLER_PLAYER_1, &p1color);
		hidGetControllerColors(CONTROLLER_PLAYER_2, &p2color);
		hidGetControllerColors(CONTROLLER_PLAYER_3, &p3color);
		hidGetControllerColors(CONTROLLER_PLAYER_4, &p4color);
		hidGetControllerColors(CONTROLLER_PLAYER_5, &p5color);
		hidGetControllerColors(CONTROLLER_PLAYER_6, &p6color);
		hidGetControllerColors(CONTROLLER_PLAYER_7, &p7color);
		hidGetControllerColors(CONTROLLER_PLAYER_8, &p8color);
		hidGetControllerColors(CONTROLLER_HANDHELD, &phcolor);

		if (p1color.singleSet) printf("\x1b[3;1HController 1: singleColorBody = 0x%08x, singleColorButtons = 0x%08x", p1color.singleColorBody, p1color.singleColorButtons);
		if (p1color.splitSet)  printf("\x1b[3;1HController 1: leftColorBody  = 0x%08x, leftColorButtons  = 0x%08x\nController 1: rightColorBody = 0x%08x, rightColorButtons = 0x%08x", p1color.leftColorBody, p1color.leftColorButtons, p1color.rightColorBody, p1color.rightColorButtons);
		
		if (p2color.singleSet) printf("\x1b[5;1HController 2: singleColorBody = 0x%08x, singleColorButtons = 0x%08x", p2color.singleColorBody, p2color.singleColorButtons);
		if (p2color.splitSet)  printf("\x1b[5;1HController 2: leftColorBody  = 0x%08x, leftColorButtons  = 0x%08x\nController 2: rightColorBody = 0x%08x, rightColorButtons = 0x%08x", p2color.leftColorBody, p2color.leftColorButtons, p2color.rightColorBody, p2color.rightColorButtons);
		
		if (p3color.singleSet) printf("\x1b[7;1HController 3: singleColorBody = 0x%08x, singleColorButtons = 0x%08x", p3color.singleColorBody, p3color.singleColorButtons);
		if (p3color.splitSet)  printf("\x1b[7;1HController 3: leftColorBody  = 0x%08x, leftColorButtons  = 0x%08x\nController 3: rightColorBody = 0x%08x, rightColorButtons = 0x%08x", p3color.leftColorBody, p3color.leftColorButtons, p3color.rightColorBody, p3color.rightColorButtons);
		
		if (p4color.singleSet) printf("\x1b[9;1HController 4: singleColorBody = 0x%08x, singleColorButtons = 0x%08x", p4color.singleColorBody, p4color.singleColorButtons);
		if (p4color.splitSet)  printf("\x1b[9;1HController 4: leftColorBody  = 0x%08x, leftColorButtons  = 0x%08x\nController 4: rightColorBody = 0x%08x, rightColorButtons = 0x%08x", p4color.leftColorBody, p4color.leftColorButtons, p4color.rightColorBody, p4color.rightColorButtons);
		
		if (p5color.singleSet) printf("\x1b[11;1HController 5: singleColorBody = 0x%08x, singleColorButtons = 0x%08x", p5color.singleColorBody, p5color.singleColorButtons);
		if (p5color.splitSet)  printf("\x1b[11;1HController 5: leftColorBody  = 0x%08x, leftColorButtons  = 0x%08x\nController 5: rightColorBody = 0x%08x, rightColorButtons = 0x%08x", p5color.leftColorBody, p5color.leftColorButtons, p5color.rightColorBody, p5color.rightColorButtons);
		
		if (p6color.singleSet) printf("\x1b[13;1HController 6: singleColorBody = 0x%08x, singleColorButtons = 0x%08x", p6color.singleColorBody, p6color.singleColorButtons);
		if (p6color.splitSet)  printf("\x1b[13;1HController 6: leftColorBody  = 0x%08x, leftColorButtons  = 0x%08x\nController 6: rightColorBody = 0x%08x, rightColorButtons = 0x%08x", p6color.leftColorBody, p6color.leftColorButtons, p6color.rightColorBody, p6color.rightColorButtons);
		
		if (p7color.singleSet) printf("\x1b[15;1HController 7: singleColorBody = 0x%08x, singleColorButtons = 0x%08x", p7color.singleColorBody, p7color.singleColorButtons);
		if (p7color.splitSet)  printf("\x1b[15;1HController 7: leftColorBody  = 0x%08x, leftColorButtons  = 0x%08x\nController 7: rightColorBody = 0x%08x, rightColorButtons = 0x%08x", p7color.leftColorBody, p7color.leftColorButtons, p7color.rightColorBody, p7color.rightColorButtons);
		
		if (p8color.singleSet) printf("\x1b[17;1HController 8: singleColorBody = 0x%08x, singleColorButtons = 0x%08x", p8color.singleColorBody, p8color.singleColorButtons);
		if (p8color.splitSet)  printf("\x1b[17;1HController 8: leftColorBody  = 0x%08x, leftColorButtons  = 0x%08x\nController 8: rightColorBody = 0x%08x, rightColorButtons = 0x%08x", p8color.leftColorBody, p8color.leftColorButtons, p8color.rightColorBody, p8color.rightColorButtons);
		
		if (phcolor.singleSet) printf("\x1b[19;1HController H: singleColorBody = 0x%08x, singleColorButtons = 0x%08x", phcolor.singleColorBody, phcolor.singleColorButtons);
		if (phcolor.splitSet)  printf("\x1b[19;1HController H: leftColorBody  = 0x%08x, leftColorButtons  = 0x%08x\nController H: rightColorBody = 0x%08x, rightColorButtons = 0x%08x", phcolor.leftColorBody, phcolor.leftColorButtons, phcolor.rightColorBody, phcolor.rightColorButtons);

		JoystickPosition p1posLeft, p1posRight, p2posLeft, p2posRight, p3posLeft, p3posRight, p4posLeft, p4posRight, p5posLeft, p5posRight, p6posLeft, p6posRight, p7posLeft, p7posRight, p8posLeft, p8posRight, phposLeft, phposRight;

		hidJoystickRead(&p1posLeft,  CONTROLLER_PLAYER_1, JOYSTICK_LEFT);
		hidJoystickRead(&p1posRight, CONTROLLER_PLAYER_1, JOYSTICK_RIGHT);
		
		hidJoystickRead(&p2posLeft,  CONTROLLER_PLAYER_2, JOYSTICK_LEFT);
		hidJoystickRead(&p2posRight, CONTROLLER_PLAYER_2, JOYSTICK_RIGHT);
		
		hidJoystickRead(&p3posLeft,  CONTROLLER_PLAYER_3, JOYSTICK_LEFT);
		hidJoystickRead(&p3posRight, CONTROLLER_PLAYER_3, JOYSTICK_RIGHT);
		
		hidJoystickRead(&p4posLeft,  CONTROLLER_PLAYER_4, JOYSTICK_LEFT);
		hidJoystickRead(&p4posRight, CONTROLLER_PLAYER_4, JOYSTICK_RIGHT);
		
		hidJoystickRead(&p5posLeft,  CONTROLLER_PLAYER_5, JOYSTICK_LEFT);
		hidJoystickRead(&p5posRight, CONTROLLER_PLAYER_5, JOYSTICK_RIGHT);
		
		hidJoystickRead(&p6posLeft,  CONTROLLER_PLAYER_6, JOYSTICK_LEFT);
		hidJoystickRead(&p6posRight, CONTROLLER_PLAYER_6, JOYSTICK_RIGHT);
		
		hidJoystickRead(&p7posLeft,  CONTROLLER_PLAYER_7, JOYSTICK_LEFT);
		hidJoystickRead(&p7posRight, CONTROLLER_PLAYER_7, JOYSTICK_RIGHT);
		
		hidJoystickRead(&p8posLeft,  CONTROLLER_PLAYER_8, JOYSTICK_LEFT);
		hidJoystickRead(&p8posRight, CONTROLLER_PLAYER_8, JOYSTICK_RIGHT);
		
		hidJoystickRead(&phposLeft,  CONTROLLER_HANDHELD, JOYSTICK_LEFT);
		hidJoystickRead(&phposRight, CONTROLLER_HANDHELD, JOYSTICK_RIGHT);

		printf("\x1b[22;1HController 1: %04d %04d %04d %04d", p1posLeft.dx,  p1posLeft.dy, p1posRight.dx, p1posRight.dy);
		printf("\x1b[23;1HController 2: %04d %04d %04d %04d", p2posLeft.dx,  p2posLeft.dy, p2posRight.dx, p2posRight.dy);
		printf("\x1b[24;1HController 3: %04d %04d %04d %04d", p3posLeft.dx,  p3posLeft.dy, p3posRight.dx, p3posRight.dy);
		printf("\x1b[25;1HController 4: %04d %04d %04d %04d", p4posLeft.dx,  p4posLeft.dy, p4posRight.dx, p4posRight.dy);
		printf("\x1b[26;1HController 5: %04d %04d %04d %04d", p5posLeft.dx,  p5posLeft.dy, p5posRight.dx, p5posRight.dy);
		printf("\x1b[27;1HController 6: %04d %04d %04d %04d", p6posLeft.dx,  p6posLeft.dy, p6posRight.dx, p6posRight.dy);
		printf("\x1b[28;1HController 7: %04d %04d %04d %04d", p7posLeft.dx,  p7posLeft.dy, p7posRight.dx, p7posRight.dy);
		printf("\x1b[29;1HController 8: %04d %04d %04d %04d", p8posLeft.dx,  p8posLeft.dy, p8posRight.dx, p8posRight.dy);
		printf("\x1b[30;1HController H: %04d %04d %04d %04d", phposLeft.dx,  phposLeft.dy, phposRight.dx, phposRight.dy);

        consoleUpdate(NULL);
    }

    consoleExit(NULL);
    return 0;
}
