//
//  console_parameters.h
//  kaggle-springleaf-marketing-response
//
//  Created by Guillermo Alberto Sandoval Sanchez on 9/7/15.
//
//

#ifndef __kaggle_springleaf_marketing_response__console_parameters__
#define __kaggle_springleaf_marketing_response__console_parameters__

#include <cstdio>
#include <map>
#include <string>
#include <vector>

class ConsoleParameters
{
private:
    std::map<std::string, std::vector<std::string>> params;
    std::string executable_name;
public:
    ConsoleParameters(int count, const char* args[]);
    
    int GetInt(std::vector<std::string> names, int default_value = 0);
    std::string GetString(std::vector<std::string> names, std::string default_value = "");
    double GetDouble(std::vector<std::string> names, double default_value = 0.0);
    bool GetBool(std::vector<std::string> names, bool default_value = false);
    std::vector<int> GetInts(std::vector<std::string> names);
    std::vector<std::string> GetStrings(std::vector<std::string> names);
    std::vector<double> GetDoubles(std::vector<std::string> names);
    std::vector<bool> GetBools(std::vector<std::string> names);
    bool Has(std::vector<std::string> names);
};

#endif /* defined(__kaggle_springleaf_marketing_response__console_parameters__) */
