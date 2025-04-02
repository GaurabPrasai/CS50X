#include <stdio.h>
#include <stdlib.h>

// command line arguments
int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        printf("Usage: ./recover IMAGE\n");
        return 1;
    }

    // Open the memory card
    FILE *file = fopen(argv[1], "r");
    if (file == NULL)
    {
        printf("Could not open %s\n", argv[1]);
        return 1;
    }

    unsigned char buffer[512];
    int counter = 0;
    FILE *img = NULL;
    if (argv[1] != NULL)
    {
        while (fread(&buffer, sizeof(buffer), 1, file) == 1)
        {
            char Newfile[8];
            if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
            {

                sprintf(Newfile, "%03i.jpg", counter);
                counter++;
                if (img != NULL)
                {
                    fclose(img);
                }

                img = fopen(Newfile, "w");
                if (img == NULL)
                {
                    printf("Could not create %s.\n", Newfile);
                    return 1;
                }
            }

            if (img != NULL)
            {
                fwrite(buffer, sizeof(buffer), 1, img);
            }
        }
    }

    if (img != NULL)
    {
        fclose(img);
    }
    fclose(file);
}
