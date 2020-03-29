#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION

#include <stdio.h>
#include "stb_image.h"
#include "stb_image_write.h"

int main(void)
{
    // Hey... ehm...
    // This is ...
    // well...
    // HORRIBLE C CODE

    // But bare with me, I'm only playing around with
    // the language for now. Give me a repo or three
    // and I'll get up to speed. =)

    const int cropX = 423;
    const int cropY = 38;

    const int cropWidth = 524;
    const int cropHeight = 524;

    int width,height,n;
    unsigned char *data = stbi_load("source.jpg", &width, &height, &n, 3);

    printf("%ix%i - %i\n\n", width, height, n);

    int bytesCount = width * height;

    int startByte = (((cropY - 1) * width) + cropX);

    printf("Start byte: %i\n\n", startByte);

    int availableBytes = ((cropWidth * cropHeight) * 3) * sizeof(char);
    printf("We have %i bytes to work with.\n", availableBytes);
    unsigned char *croppedData = (unsigned char *)malloc(availableBytes);

    int targetCropY = (cropY + cropHeight) - 1;
    int copiedByte = 0;
    for(int ny = cropY - 1; ny < targetCropY; ny++)
    {
        int currentY = ny * width;

        for(int nx = cropX; nx < cropX + cropWidth; nx++)
        {
            int currentByte = ((currentY + nx) - 1) * 3;

            croppedData[copiedByte + 0] = data[currentByte + 0];
            croppedData[copiedByte + 1] = data[currentByte + 1];
            croppedData[copiedByte + 2] = data[currentByte + 2];

            copiedByte = copiedByte + 3;
        }
    }

    stbi_write_jpg("result.jpg", cropWidth, cropHeight, 3, croppedData, 100);
    printf("Done");

    free(croppedData);
    stbi_image_free(data);

    return(0);
}
