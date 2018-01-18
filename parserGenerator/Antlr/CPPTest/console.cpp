#include <cstdio>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include <array>

using namespace std;

string exec(const char* cmd) {
    array<char, 128> buffer;
    string result;
    shared_ptr<FILE> pipe(popen(cmd, "r"), pclose);
    if (!pipe) throw std::runtime_error("popen() failed!");
    while (!feof(pipe.get())) {
        if (fgets(buffer.data(), 128, pipe.get()) != nullptr)
            result += buffer.data();
    }
    return result;
}

int main(int argc, char *argv[]) {
	cout << "Console Test" << endl;
	string consoleResult = exec("java -cp .:antlr-4.7-complete.jar ANTLRDemo TestFiles/class.cpp");
	int parseResult = stoi(consoleResult);
    if(parseResult) {
        cout << "Parse Success" << endl;
    } else {
        cout << "Parse Failed" << endl;
    }
}