#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_RESET   "\x1b[0m"

typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    // checks if there is only one command line argument
    if (argc != 2)
    {
        printf("Usage: ./recover image\n");
        return 1;
    }
    else
    {
        // open file to be recovered (param 1 in command line)
        FILE *file = fopen(argv[1], "r");
        if (!file)
        {
            // file not found
            printf("File " ANSI_COLOR_YELLOW "%s" ANSI_COLOR_RESET " not found.\n", argv[1]);
            return 1;
        }
        else
        {
            int fcount = 0; // number of JPG found
            char *fname = malloc(8); // outfile filename
            BYTE buffer[512];
            FILE *img;;;
            while (fread(buffer, sizeof(BYTE) * 512, 1, file) == 1)
            {
                if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
                {
                    // JPEG signature found
                    if (fcount == 0)
                    {
                        // first JPEG found
                        sprintf(fname, "%03i.jpg", fcount);
                        img = fopen(fname, "w");
                        fwrite(buffer, sizeof(BYTE) * 512, 1, img);
                        fcount++;
                    }
                    else
                    {
                        fclose(img);
                        sprintf(fname, "%03i.jpg", fcount);
                        img = fopen(fname, "w");
                        fwrite(buffer, sizeof(BYTE) * 512, 1, img);
                        fcount++;
                    }
                }
                else
                {
                    if (fcount > 0)
                    {
                        // keep wrinting found image
                        fwrite(buffer, sizeof(BYTE) * 512, 1, img);
                    }
                }
            }
            fclose(img);
            fclose(file);
        }
    }
}
