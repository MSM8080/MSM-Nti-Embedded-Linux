#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

void main(int argc, char** argv)
{
    char path[] = "/sys/devices/pci0000:00/0000:00:02.0/drm/card1/card1-eDP-1/intel_backlight/brightness";
    int pctg = 0;
    char* str_brt;

    if(argc < 2)
        printf("!! اكتب النسبة المؤية يامحترم \n");
    else
    {   
        FILE* file = fopen(path,"w+");
        pctg = ((atoi(argv[1]) / 100.0) * 120000);
        printf(";) شطوور \n");
        fprintf(file,"%d",pctg);


    }


    return;
}