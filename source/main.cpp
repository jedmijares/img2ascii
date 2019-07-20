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

    // values set by command line options
    bool invertFlag = false;
    int pixelCount = 3;
    unsigned int scaleFactor = 0;

    int argvIndex = 1;
    while ((argvIndex < argc - 1) && (*argv[argvIndex] == '-'))
    {
        std::string argument(argv[argvIndex]);
        if (argument.compare("-i") == 0)
        {
            invertFlag = true;
        }
        else if (argument.compare("-p") == 0)
        {
            argvIndex++;
            std::string countString(argv[argvIndex]);
            pixelCount = std::stoi(countString);
        }
        else if (argument.compare("-s") == 0)
        {
            argvIndex++;
            std::string scaleString(argv[argvIndex]);
            scaleFactor = std::stoi(scaleString);
        }
        else
        {
            std::cout << "Error in command line arguments. Exiting program.\n";
            exit(1);
        }
        argvIndex++;
    }

    try
    {
        std::string filename = argv[argc - 1];
        Magick::Image inputImg(filename);
        // inputImg.zoom(Magick::Geometry(inputImg.columns()/7,inputImg.rows()/7));
        if(scaleFactor) // if resize option was set
            inputImg.zoom(Magick::Geometry(inputImg.columns()/scaleFactor,inputImg.rows()/scaleFactor));

        for(int y = 0; y < inputImg.rows(); y++)
        {
            for(int x = 0; x < inputImg.columns(); x++)
            {
                // https://en.wikipedia.org/wiki/Relative_luminance
                float pixelBrightness = 0.2126*(inputImg.pixelColor(x,y)).quantumRed() + 0.7152*(inputImg.pixelColor(x,y)).quantumGreen() + 0.0722*(inputImg.pixelColor(x,y)).quantumBlue();
                const char asciiChart[] = " `^\",:;Il!i~+?][}{1)(|\\/tfjrxnuvczXYUJCLQ0OZmwqpdbkhao#MW&8%B@$"; // ASCII from dimmest to brightest
                const int numChars = (sizeof(asciiChart)-1-2); // -1 for starting at 0, -2 for escape slashes
                int charIndex = ((pixelBrightness)/QuantumRange * numChars); // map brightness value to a printable character in array
                if(charIndex < 0) charIndex = 0;
                if(charIndex > numChars) charIndex = numChars;
                for(int i = 0; i < pixelCount; i++) // print each character multiple times to account for difference in height to width of characters
                {
                    if(!invertFlag) std::cout << asciiChart[charIndex];
                    else std::cout << asciiChart[sizeof(asciiChart) - 1 - charIndex];
                }
            }
            std::cout << "\n";
        }
    }
    catch( std::exception& error ) // catch error thrown by Magick objects
    {
      std::cout << error.what() << "\n";
      return 1;
    }
    return 0;
}