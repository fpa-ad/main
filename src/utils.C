#include "utils.h"
#include <sstream>

using namespace std;

string current_time()
{
    auto t = std::time(nullptr);
    auto tm = *std::localtime(&t);
    stringstream ss;
    ss << std::put_time(&tm, "%d-%m-%Y %H-%M-%S");
    return ss.str();
}