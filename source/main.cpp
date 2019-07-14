// Jed Mijares
// main file for img2ascii

#include <Magick++.h>
#include <iostream>

int main(int argc, char** argv)
{
    if(argc < 2)
    {
        std::cout << "Need input file. \n";
        return -1;
    }

    std::string filename = argv[1];
    Magick::Image inputImg(filename);

    for(int y = 0; y < inputImg.rows(); y++)
    {
        for(int x = 0; x < inputImg.columns(); x++)
        {
            for(int i = 0; i < 3; i++) // print each character 3 times to account for difference in length to width
            {
                // https://en.wikipedia.org/wiki/Relative_luminance
                float pixelBrightness = 0.2126*(inputImg.pixelColor(x,y)).quantumRed() + 0.7152*(inputImg.pixelColor(x,y)).quantumGreen() + 0.0722*(inputImg.pixelColor(x,y)).quantumBlue();
                const std::string asciiChart = " `^\",:;Il!i~+_-?][}{1)(|\\/tfjrxnuvczXYUJCLQ0OZmwqpdbkhao*#MW&8%B@$";
                int charIndex = (pixelBrightness)/QuantumRange * sizeof(asciiChart); // map brightness value to a printable character in array
                std::cout << asciiChart[charIndex];
            }
        }
        std::cout << "\n";
    }

    return 0;
}