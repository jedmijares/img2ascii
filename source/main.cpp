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

    bool invertFlag = false;
    int argvIndex = 1;
    while ((argvIndex < argc - 1) && (*argv[argvIndex] == '-'))
    {
        std::string argument(argv[argvIndex]);
        if (argument.compare("-i") == 0)
        {
            invertFlag = true;
            argvIndex++;
        }
        
    }

    try
    {
        std::string filename = argv[argc - 1];
        Magick::Image inputImg(filename);
        // inputImg.zoom(Magick::Geometry(inputImg.columns()/7,inputImg.rows()/7));
    
        for(int y = 0; y < inputImg.rows(); y++)
        {
            for(int x = 0; x < inputImg.columns(); x++)
            {
                // https://en.wikipedia.org/wiki/Relative_luminance
                float pixelBrightness = 0.2126*(inputImg.pixelColor(x,y)).quantumRed() + 0.7152*(inputImg.pixelColor(x,y)).quantumGreen() + 0.0722*(inputImg.pixelColor(x,y)).quantumBlue();
                const char* asciiChart = " `^\",:;Il!i~+_-?][}{1)(|\\/tfjrxnuvczXYUJCLQ0OZmwqpdbkhao*#MW&8%B@$"; // ASCII from dimmest to brightest
                int charIndex = (pixelBrightness)/QuantumRange * sizeof(asciiChart); // map brightness value to a printable character in array
                for(int i = 0; i < 2; i++) // print each character multiple times to account for difference in length to width
                {
                    if(!invertFlag) std::cout << asciiChart[charIndex];
                    else std::cout << asciiChart[sizeof(asciiChart) - charIndex];
                }
            }
            std::cout << "\n";
        }
    }
    catch( std::exception& error_ )
    {
      std::cout << "Caught exception: " << error_.what() << "\n";
      return 1;
    }

    return 0;
}