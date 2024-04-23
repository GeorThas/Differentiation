#include "DiffPowerFunc.h"
#include <string>

    bool DiffPowerFunc::IsIt(std::string func)
    {
        if (func.length() > 2 && func.substr(0, 2) == "x^")
        {
            try
            {
                stod(func.substr(2));
                return true;
            }
            catch (...) {}
        }

        return false;
    }

    std::string DiffPowerFunc::Diff(std::string func)
    {
        
        //int i = func.find(".");
        if (func.find('.') < 0) {
            double power = stod(func.substr(2));
            return std::to_string(power) + "*x^" + std::to_string(power - 1);
        }
        else {
            int power = stoi(func.substr(2));
            return std::to_string(power) + "*x^" + std::to_string(power - 1);
        }
       
        
    }
