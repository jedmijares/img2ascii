#include <Magick++.h>
#include <iostream>


int main(int argc, char** argv)
{
    if(argc < 2)
    {
        std::cout << "Need input file. \n";
        return -1;
    }

    std::string inputFile = argv[1];

    return 0;
}