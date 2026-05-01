#include <iostream>
#include <filesystem>
#include <stdexcept>
#include <cstdio>

int main(int argc, char **argv) {
    std::string program  = (argc > 1) ? argv[1] : "../build/matrix";
    std::string test_dir = (argc > 2) ? argv[2] : "./e2e";

    if(!std::filesystem::exists(program)) {
        std::cerr << "Program was now found " << program << std::endl;
        std::cerr << "Usage ./a.out {program} {test_dir}" << std::endl;
        return -1;
    }

    if(!std::filesystem::exists(program)) {
        std::cerr << "Test dir was now found " << program << std::endl;
        std::cerr << "Usage ./a.out {program} {test_dir}" << std::endl;
        return -1;
    }

    int passed = 0, total = 0;

    for(auto && file : std::filesystem::directory_iterator(test_dir)) {
        
        if(file.path().extension() != ".dat") continue;

        std::string test_path = file.path().string();
        std::string cmd = program + " < '" + test_path +"'"; 

        FILE *pipe = popen(cmd.c_str(), "r");
        char buffer[128];
    }

    std::cout << passed << " // " << total << std::endl;
    if(passed == total) return 0;
    return -1;
}