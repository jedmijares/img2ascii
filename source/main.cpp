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

    std::cout << filename << " is an " << inputImg.columns() << " by " << inputImg.rows() << " image.\n";

    return 0;
}