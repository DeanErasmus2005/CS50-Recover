#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

int main(int argc, char *argv[])
{
    if (argc >= 2)
    {
        printf("Usage: ./recover IMAGE\n");
        return 1;
    }
    //kon ek hierso nie card.raw in tik nie? soos inplaas van argv1 want dit kan mos geen ander file wees nie.
    FILE *raw_file = fopen(argv1, "r");
    //hkm moet ek uint8_t hier gebruik as ek in elk geval integers sal assign daaraan
    uint8_t buffer[512];
    bool found_jpeg = false;
    int counter = 0;
    char filename[8];
    FILE *img = NULL;
    while (fread(buffer, 1, 512, raw_file))
    {
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            found_jpeg = true;
        }
        if (found_jpeg == true)
        {
            if (counter != 0)
            {
                fclose(img);
            }


            sprintf(filename, "%03i.jpeg", counter);
            img = fopen(filename, "w");
            fwrite(buffer, 1, 512, img);
            found_jpeg = false;
            counter++;
        }
        else if(counter != 0)
        {
            fwrite(buffer, 1, 512, img);
        }

    }
    fclose(img);
    fclose(raw_file);
}

