// Please enjoy this NABU joystick testing program (njoytest.c)
//
// Let me know if there are any issues.
//
// https://github.com/jefferystone/nabu_stuff.git
//
// I used snake.c (by David Latham aka productiondave) as a starting point:
// https://github.com/linuxplayground/nabu-games
//
// Thank you David
//
#define DISABLE_HCCA_RX_INT
#define DISABLE_CURSOR

#include "NABU-LIB.h"
#include "NabuTracker.h"
#include "patterns.h"

//#include "stdio.h"
#include "strings.h"

// Globals
uint8_t ticks;
uint8_t game_speed;
int8_t col;

//Music score
uint16_t music[] = {
    0, NT_NOTE_ON, 0, 20, 10,
    1, NT_NOTE_OFF, 0,
    2, NT_NOTE_ON, 0, 10, 10,
    3, NT_NOTE_OFF, 0,
    4, NT_NOTE_ON, 0, 20, 10,
    5, NT_NOTE_OFF, 0,
    6, NT_NOTE_ON, 0, 10, 10,
    7, NT_NOTE_OFF, 0,
    8, NT_NOTE_ON, 0, 15, 10,
    9, NT_NOTE_OFF, 0,
    10, NT_NOTE_ON, 0, 20, 10,
    11, NT_NOTE_OFF, 0,
    12, NT_NOTE_ON, 0, 10, 10,
    13, NT_NOTE_OFF, 0,
    14, NT_NOTE_ON, 0, 30, 10,
    15, NT_NOTE_OFF, 0,
    16, NT_LOOP
};

void init() {
    initNABULib();
    initNABULIBAudio();
    nt_init(music);
    vdp_clearVRAM();
    vdp_initG2Mode(1, false, false, false, false);
    vdp_loadPatternTable(FAT,0x330);
    uint16_t _vdpColorTableAddr = 0x2000;
    uint16_t _vdpColorTableSize = 0x1800;
    vdp_setWriteAddress(_vdpColorTableAddr);
    for (uint16_t i = 0; i<_vdpColorTableSize; i++) {
        IO_VDPDATA = 0x41;                                  // Dark blue on black
    }

    vdp_setBackDropColor(VDP_DARK_BLUE);                  //Set border color
}

int center(char * msg) {
	return (14-(strlen(msg)/2));
}

void vdp_show(int col,int row,char * msg) {
	// if col = -1, then we center
	if(col == -1) {
		col = center(msg);
	}
	vdp_setCursor2(col,row);
	vdp_print(msg);
}

void joy_test() {
    vdp_fillScreen(0x00);
    initNABULIBAudio(); // reset to regular music mode
    ticks = 0;
    game_speed = 10;

    vdp_enableVDPReadyInt();
    vdp_show(-1,14,"NABU JOYSTICK TEST V1.02");
    vdp_show(-1,16,"ESC TO QUIT");
    vdp_show(6,1,"JOY 1");
    vdp_show(18,1,"JOY 2");
    
    while(true) {
		// joystick 1
        if(getJoyStatus(0) & Joy_Left) {
            if(getJoyStatus(0) & Joy_Up) {
              vdp_show(5,3,"LU");
            } else if(getJoyStatus(0) & Joy_Down) {
              vdp_show(5,7,"LD");
            } else {
              vdp_show(5,5,"L");
        	}
        }

        if(getJoyStatus(0) & Joy_Right) {
            if(getJoyStatus(0) & Joy_Up) {
              vdp_show(10,3,"UR");
            } else if(getJoyStatus(0) & Joy_Down) {
              vdp_show(10,7,"DR");
            } else {
              vdp_show(10,5," R");
        	}
        }

        if(getJoyStatus(0) & Joy_Up) {
        	if(getJoyStatus(0) & Joy_Left) {
	          vdp_show(8,3," ");
			} else if(getJoyStatus(0) & Joy_Right) {
	          vdp_show(8,3," ");
	        } else {
              vdp_show(8,3,"U");
            }
        }
        
        if(getJoyStatus(0) & Joy_Down) {
        	if(getJoyStatus(0) & Joy_Left) {
	            vdp_show(8,7," ");
			} else if(getJoyStatus(0) & Joy_Right) {
	            vdp_show(8,7," ");
	        } else {
	            vdp_show(8,7,"D");
	        }
        }

		if (getJoyStatus(0) & Joy_Button) {
			vdp_show(8,5,"F");
		} else {
			vdp_show(8,5," ");
		  }

		// joystick 2
        if(getJoyStatus(1) & Joy_Left) {
            if(getJoyStatus(1) & Joy_Up) {
              vdp_show(17,3,"LU");
            } else if(getJoyStatus(1) & Joy_Down) {
              vdp_show(17,7,"LD");
            } else {
              vdp_show(17,5,"L");
        	}
        }

        if(getJoyStatus(1) & Joy_Right) {
            if(getJoyStatus(1) & Joy_Up) {
              vdp_show(22,3,"UR");
            } else if(getJoyStatus(1) & Joy_Down) {
              vdp_show(22,7,"DR");
            } else {
              vdp_show(22,5," R");
        	}
        }

        if(getJoyStatus(1) & Joy_Up) {
        	if(getJoyStatus(1) & Joy_Left) {
	          vdp_show(20,3," ");
			} else if(getJoyStatus(1) & Joy_Right) {
	          vdp_show(20,3," ");
	        } else {
              vdp_show(20,3,"U");
            }
        }
        
        if(getJoyStatus(1) & Joy_Down) {
        	if(getJoyStatus(1) & Joy_Left) {
	            vdp_show(20,7," ");
			} else if(getJoyStatus(1) & Joy_Right) {
	            vdp_show(20,7," ");
	        } else {
	            vdp_show(20,7,"D");
	        }
        }

		if (getJoyStatus(1) & Joy_Button) {
			vdp_show(20,5,"F");
		} else {
			vdp_show(20,5," ");
		  }

        if (ticks % game_speed == 0) {
			// clear the joystick statuses
			vdp_clearRows(2,8);                          
        }
        
        if (isKeyPressed()) {
            uint8_t _key = getChar();
            if(_key == 0x1b)
                //return false;
                break;
		}
        
        vdp_waitVDPReadyInt();
        vdp_refreshViewPort();
        ticks ++;
    }
    /*
    // play crash sound
    ayWrite(6,  0x0f);
    ayWrite(7,  0b11000111);
    ayWrite(8,  0x1f);
    ayWrite(9,  0x1f);
    ayWrite(10, 0x1f);
    ayWrite(11, 0xa0);
    ayWrite(12, 0x40);
    ayWrite(13, 0x00);
    // we have crashed - lets pause for a bit
    uint16_t timer = 0;
    while (timer < 180) { //3 seconds
        vdp_waitVDPReadyInt();
        timer ++;
    }
    */
    vdp_disableVDPReadyInt();  //only use vdp interrupts during game play.
}

void main() {
    //vdp_setCharAtLocationBuf(apple.x, apple.y, applechar);
    init();
    vdp_clearScreen();
    joy_test();
    vdp_disableVDPReadyInt();
    #if BIN_TYPE == BIN_HOMEBREW
    __asm
        di
        rst 0x00
    __endasm;
    #endif
}
