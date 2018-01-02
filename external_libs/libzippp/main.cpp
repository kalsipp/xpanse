#include <iostream>
#include <string>
#include <vector>
#include "libzippp.h"

using namespace libzippp;

int main(int argc, char **argv)
{
    std::cout << "hello" << std::endl;
    ZipArchive zf("archive.zip");
    zf.open(ZipArchive::READ_ONLY);

    std::vector<ZipEntry> entries = zf.getEntries();
    std::vector<ZipEntry>::iterator it;
    for (it = entries.begin() ; it != entries.end(); ++it) {
        ZipEntry entry = *it;
        std::string name = entry.getName();
        int size = entry.getSize();

        //the length of binaryData will be size
        void* binaryData = entry.readAsBinary();

        //the length of textData will be size
        std::string textData = entry.readAsText();

        //...
    }

    zf.close();
}

