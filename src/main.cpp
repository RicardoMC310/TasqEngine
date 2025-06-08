#include "../include/Platform/Platform.hpp"

int main(int argc, char **argv)
{

    if (argc < 2)
    {
        std::cerr << "CPP: preciso que passe um arquivo .lua para interpretar.\n";
        return -1;
    }

    Tasq::Platform platform;

    platform.registerAllFuncs();

    if (!platform.openFile(argv[1]))
    {
        std::cerr << "CPP: Erro ao ler arquivo .lua\n";
        std::cerr << platform.getError();
        return -1;
    }

    platform.run();

    return 0;
}