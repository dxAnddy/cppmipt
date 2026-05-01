#include <iostream>
#include <filesystem>
#include <stdexcept>
#include <cstdio>
#include <fstream>
#include <cmath>

int main(int argc, char **argv) {
    std::string program  = (argc > 1) ? argv[1] : "../build/matrix";
    std::string test_dir = (argc > 2) ? argv[2] : "./e2e";

    if(!std::filesystem::exists(program)) {
        std::cerr << "Program was now found " << program << std::endl;
        std::cerr << "Usage ./a.out {program} {test_dir}" << std::endl;
        return -1;
    }

    if(!std::filesystem::exists(test_dir)) {
        std::cerr << "Test dir was now found " << program << std::endl;
        std::cerr << "Usage ./a.out {program} {test_dir}" << std::endl;
        return -1;
    }

    int passed = 0, total = 0;

    for(auto && file : std::filesystem::directory_iterator(test_dir)) {
        
        if(file.path().extension() != ".dat") continue;

        std::string test_path = file.path().string();
        

        std::filesystem::path tmp = file.path();
        tmp.replace_extension(".ans");
        std::string ans_path = tmp.string();
        std::string cmd = program + " < '" + test_path +"'"; 

        FILE *pipe = popen(cmd.c_str(), "r");
        char buffer[128];
        std::string output = "";
        while(fgets(buffer, sizeof(buffer), pipe) != nullptr) {
            output += buffer;
        }
        pclose(pipe);

        std::ifstream file_exp(ans_path);
        std::string line = "";
        std::getline(file_exp, line);
        double expected = std::stod(line);
        double actual = std::stod(output);

        if(std::abs(expected - actual) < 1e-5) {
            passed++;
        } else {
            std::cout << "Expected: " << expected << "Actual: " << actual << std::endl;
        }  
        
        total++;
    }

    std::cout << passed << "/" << total << std::endl;
    if(passed == total) return 0;
    return -1;
}