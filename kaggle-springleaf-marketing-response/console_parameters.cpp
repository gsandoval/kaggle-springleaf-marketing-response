//
//  console_parameters.cpp
//  kaggle-springleaf-marketing-response
//
//  Created by Guillermo Alberto Sandoval Sanchez on 9/7/15.
//
//

#include "console_parameters.h"
#include <cstring>
#include <sstream>

using namespace std;

ConsoleParameters::ConsoleParameters(int count, const char* args[])
{
    string current_param_name;
    this->executable_name = string(args[0]);
    for (unsigned int i = 1; i < count; i++) {
        if (args[i][0] == '-') {
            int start_index = 1;
            if (args[i][1] == '-') {
                start_index = 2;
            }
            
            if (current_param_name != "") {
                this->params[current_param_name] = vector<string>();
            }
            
            current_param_name = string(args[i] + start_index);
        } else {
            if (this->params.find(current_param_name) == this->params.end()) {
                this->params[current_param_name] = vector<string>();
            }
            this->params[current_param_name].push_back(string(args[i]));
            current_param_name = "";
        }
    }
}

int ConsoleParameters::GetInt(vector<string> names, int default_value)
{
    for (unsigned int n = 0; n < names.size(); n++) {
        string name = names[n];
        
        auto it = this->params.find(name);
        if (it == this->params.end()) {
            continue;
        }
        auto values = it->second;
        if (values.size() == 0) {
            return default_value;
        }
        int val;
        istringstream iss(values[0]);
        iss >> val;
        return val;
    }
    
    return default_value;
}

string ConsoleParameters::GetString(vector<string> names, string default_value)
{
    for (unsigned int n = 0; n < names.size(); n++) {
        string name = names[n];
        
        auto it = this->params.find(name);
        if (it == this->params.end()) {
            continue;
        }
        auto values = it->second;
        if (values.size() == 0) {
            return default_value;
        }
        return values[0];
    }
    return default_value;
}

double ConsoleParameters::GetDouble(vector<string> names, double default_value)
{
    for (unsigned int n = 0; n < names.size(); n++) {
        string name = names[n];
        
        auto it = this->params.find(name);
        if (it == this->params.end()) {
            continue;
        }
        auto values = it->second;
        if (values.size() == 0) {
            return default_value;
        }
        double val;
        istringstream iss(values[0]);
        iss >> val;
        return val;
    }
    
    return default_value;
}

bool ConsoleParameters::GetBool(vector<string> names, bool default_value)
{
    for (unsigned int n = 0; n < names.size(); n++) {
        string name = names[n];
        
        auto it = this->params.find(name);
        if (it == this->params.end()) {
            continue;
        }
        
        auto values = it->second;
        if (values.size() == 0) {
            return default_value;
        }
        bool val;
        istringstream iss(values[0]);
        iss >> val;
        return val;
    }
    
    return default_value;
}

bool ConsoleParameters::Has(vector<string> names)
{
    for (unsigned int n = 0; n < names.size(); n++) {
        string name = names[n];
        
        auto it = this->params.find(name);
        if (it == this->params.end()) {
            continue;
        }
        return true;
    }
    return false;
}

vector<int> ConsoleParameters::GetInts(vector<string> names)
{
    vector<int> casted;
    for (unsigned int n = 0; n < names.size(); n++) {
        string name = names[n];
        
        auto it = this->params.find(name);
        if (it == this->params.end()) {
            continue;
        }
        auto values = it->second;
        int val;
        for (unsigned int i = 0; i < values.size(); i++) {
            istringstream iss(values[0]);
            iss >> val;
            casted.push_back(val);
        }
        return casted;
    }
    
    return casted;
}

vector<string> ConsoleParameters::GetStrings(vector<string> names)
{
    vector<string> casted;
    
    for (unsigned int n = 0; n < names.size(); n++) {
        string name = names[n];
        
        auto it = this->params.find(name);
        if (it == this->params.end()) {
            continue;
        }
        return it->second;
    }
    
    return casted;
}

vector<double> ConsoleParameters::GetDoubles(vector<string> names)
{
    vector<double> casted;
    
    for (unsigned int n = 0; n < names.size(); n++) {
        string name = names[n];
        
        auto it = this->params.find(name);
        if (it == this->params.end()) {
            continue;
        }
        auto values = it->second;
        double val;
        for (unsigned int i = 0; i < values.size(); i++) {
            istringstream iss(values[0]);
            iss >> val;
            casted.push_back(val);
        }
    }
    
    return casted;
}

vector<bool> ConsoleParameters::GetBools(vector<string> names)
{
    vector<bool> casted;
    
    for (unsigned int n = 0; n < names.size(); n++) {
        string name = names[n];
        
        auto it = this->params.find(name);
        if (it == this->params.end()) {
            continue;
        }
        auto values = it->second;
        bool val;
        for (unsigned int i = 0; i < values.size(); i++) {
            istringstream iss(values[0]);
            iss >> val;
            casted.push_back(val);
        }
    }
    
    return casted;
}


