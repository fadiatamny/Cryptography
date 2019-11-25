#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cmath>

using namespace std;

static unsigned seed = 0;

static unsigned GetNextRandom(void)
{
	if (seed == 0)
	{
		cerr << "Seed must be initialized before a random number can be generated.\n";
		exit(3);
	}
	unsigned next = (seed * 134775813 + 1) & 0xffffffff;
	seed = next;
	return next;	
}

static unsigned EncryptOrDecrypt(unsigned m)
{
	return m ^ GetNextRandom();
}

int main(int argc, const char* argv[])
{
	if (argc != 4)
	{
		cerr << "Usage: "<<argv[0] << " seed input output\n";
		return 1;
	}
	seed = (unsigned)strtoul(argv[1], NULL, 10);
	std::ifstream ifs(argv[2]);
	std::ofstream ofs(argv[3]);
	ifs.seekg(0, std::ios::end);
	if (ifs.tellg() %4)
	{
		cerr << "Input file size needs to be a multiple of 4.\n";
		return 2;
	}
	ifs.seekg(0, std::ios::beg);
	unsigned m;
	for (;;)
	{
		unsigned m;
		ifs.read((char*)&m, sizeof(m));
		if (ifs.gcount() == 0)
			break;
		unsigned c = EncryptOrDecrypt(m);
		ofs.write((char*)&c, sizeof(m));
	}
	return 0;
}
