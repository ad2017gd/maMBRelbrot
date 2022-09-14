
asm(".code16gcc\n");
/* ------------------------------------ */

#define noret  __attribute__((noreturn))
#define v320x200V 0x13
#define v40x25T 0x01
#define MAX_ITER 70

float zoom = 1;

/* ------------------------------------ */


void noret __attribute__((section("__start"))) main(){


    unsigned char* s = "ad2017.dev/m";
    while (*s != '\0') {
    asm volatile (
			"mov	ah,0x0E\n"
			"mov	al,%b0\n"
			"int	0x10"
			: 
			: "al"(*(s++)):"ah","bx");
}


    asm  (
        "MOV     CX, 0x004c\n"
"MOV     DX, 0x4b40\n"
"MOV     AH, 0x86\n"
"INT     0x15\n" :::"cx","dx","ah"
    );




    asm volatile (
			"mov	%%ax, 0x13\n"
			"int	0x10" : : : "ax"
        ); // CHANGE TO 320x200x256 VIDEO MODE


    double zx = 0, zy = 0, cX = 0, cY = 0, tmp = 0;
    char a = 0;
    while(1) {
while(zoom<50000047) {

    for (unsigned char y = 0; y < 100; y+=2) {
            for (unsigned char x = 0; x < 200; x++) {

                unsigned char* location = (unsigned char*)0xA0000 + (320) * (y+50) + (60+x);
if(x%2==0){
                zx = zy = 0;
                cX = (x - 100 + 20) / zoom + (-0.562712585);
                cY = (y - 50 - 20) / zoom + (-0.658482912);
                int i = 0;
  double zx2 = 0.0, zy2 = 0.0;
  while (i < MAX_ITER && zx2 + zy2 < 4.0) {
    double temp = zx2 - zy2 + cX;
    zy = 2.0 * zx * zy + cY;
    zx = temp;
    zx2 = zx * zx;
    zy2 = zy * zy;
    ++i;
  }
                a= (MAX_ITER-i) != 0 ? ((unsigned char)0x20+i%24) : 0;  
}
                *location = a;

                
            }
        }

zoom*=1.012017;   
}
zoom = 1;
    }
    
}

