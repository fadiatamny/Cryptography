#include "includes.hpp"
#include "des.hpp"

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        std::cout << "Please insert the results" << std::endl;
        exit(-1);
    }

    std::string str = "1010101010111011000010010001100000100111001101101100110011011101";
    std::vector<unsigned char> key(str.begin(), str.end());
    str = argv[1];
    std::vector<unsigned char> message(str.begin(), str.end());

    for (auto i = message.begin(); i != message.end(); ++i)
        std::cout << *i << ' ';
    std::cout << std::endl;

    std::vector<unsigned char> enc = encryptBlock(message, key);
    
    for (auto i = enc.begin(); i != enc.end(); ++i)
        std::cout << *i << ' ';
    std::cout << std::endl;
    
    std::vector<unsigned char> dec = decryptBlock(enc, key);
    
    for (auto i = dec.begin(); i != dec.end(); ++i)
        std::cout << *i << ' ';
    std::cout << std::endl;
    
    return 0;
}