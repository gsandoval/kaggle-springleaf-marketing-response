//
//  springleaf_data_parser.cpp
//  kaggle-springleaf-marketing-response
//
//  Created by Guillermo Alberto Sandoval Sanchez on 9/7/15.
//
//

#include "springleaf_data_parser.h"

#include <map>
#include <set>
#include <cstdlib>
#include <iomanip>
#include <sstream>
#include <ctime>
#include <cmath>

using namespace std;

shared_ptr<vector<double>> SpringleafDataParser::ProcessColumn(shared_ptr<vector<string>> data)
{
    shared_ptr<vector<double>> output(new vector<double>());
    size_t ELEM_COUNT = data->size();
    string date_pattern_template = "08NOV11:00:00:00";
    size_t date_str_len = date_pattern_template.length();
    char months[100];
    strcpy(months, "JANFEBMARAPRMAYJUNJULAUGSEPOCTNOVDEC");
    
    bool all_numbers = true;
    map<string, long> non_numeric;
    map<string, long> all_mapped_values;
    double min_value;
    double max_value;
    bool is_category = false;
    bool is_date = false;
    bool impossible_date = false;
    long max_date_milis = numeric_limits<long>::min();
    long min_date_milis = numeric_limits<long>::max();
    vector<long> date_milis;
    
    char month_str[4];
    memset(month_str, 0, 4);
    char date_str[3];
    char year_str[3];
    for (unsigned int i = 0; i < data->size(); i++) {
        string *entry = &data->at(i);
        bool is_number = this->IsNumber(entry);
        
        if (!is_number && non_numeric.size() < 2) {
            all_numbers = is_number;
            if (non_numeric.find(*entry) == non_numeric.end()) {
                non_numeric[*entry] = non_numeric.size();
            }
        }
        
        if (!is_number && date_str_len == entry->length() && !impossible_date) {
            strncpy(month_str, entry->c_str() + 2, 3);
            char *pos = strstr(months, month_str);
            if (pos != NULL) {
                is_date = true;
                
                int position = (int)(pos - months);
                int month = position / 3;
                
                memset(date_str, 0, 3);
                strncpy(date_str, entry->c_str(), 2);
                memset(year_str, 0, 3);
                strncpy(year_str, entry->c_str() + 5, 2);
                
                int date = atoi(date_str);
                int year = atoi(year_str);
                year += (year < 16 ? 100 : 0);
                
                tm tm_val;
                time_t rawtime;
                time(&rawtime);
                tm_val = *localtime(&rawtime);
                
                tm_val.tm_mon = month;
                tm_val.tm_year = year;
                tm_val.tm_mday = date;
                
                time_t date_time = mktime(&tm_val);
                
                long milis = static_cast<long>(date_time);
                if (min_date_milis > milis) {
                    min_date_milis = milis;
                }
                if (max_date_milis < milis) {
                    max_date_milis = milis;
                }
                date_milis.push_back(milis);
                
                /*
                char buff[200];
                tm_val = *localtime (&date_time);
                strftime(buff, sizeof(buff), "%Y %m %d", &tm_val);
                 */
            } else {
                is_date = false;
                impossible_date = true;
            }
        } else {
            date_milis.push_back(0);
        }
        
        if (all_mapped_values.find(*entry) == all_mapped_values.end()) {
            all_mapped_values[*entry] = all_mapped_values.size();
        }
    }
    
    if (is_date) {
        max_value = max_date_milis;
        min_value = min_date_milis;
        double empty_value = min_date_milis - 24 * 60 * 60 * 1000;
        for (int i = 0; i < date_milis.size(); i++) {
            if (date_milis[i] == 0) {
                output->push_back(empty_value);
            } else {
                output->push_back(date_milis[i]);
            }
        }
    } else if (all_numbers || (!all_numbers && non_numeric.size() == 1)) {
        string placeholder = "";
        if (non_numeric.size() == 1) {
            placeholder = non_numeric.begin()->first;
        }

        min_value = numeric_limits<double>::max();
        max_value = numeric_limits<double>::min();
        double* converted_nums = new double[ELEM_COUNT];
        for (unsigned int i = 0; i < ELEM_COUNT; i++) {
            string *val = &data->at(i);
            if (*val != placeholder) {
                converted_nums[i] = stod(val->c_str());
                if (min_value > converted_nums[i]) {
                    min_value = converted_nums[i];
                }
                if (max_value < converted_nums[i]) {
                    max_value = converted_nums[i];
                }
            }
        }
        
        int near_to_min = 0;
        int near_to_max = 0;
        set<double> diff_nums_near_to_min;
        set<double> diff_nums_near_to_max;
        double second_smallest = numeric_limits<double>::max();
        double second_largest = numeric_limits<double>::min();
        double min_group[2] = {numeric_limits<double>::max(), numeric_limits<double>::min()};
        double max_group[2] = {numeric_limits<double>::max(), numeric_limits<double>::min()};
        double *group;
        for (unsigned int i = 0; i < ELEM_COUNT; i++) {
            if (data->at(i) == placeholder) {
                continue;
            }
            if (converted_nums[i] != min_value && second_smallest > converted_nums[i]) {
                second_smallest = converted_nums[i];
            }
            if (converted_nums[i] != max_value && second_largest < converted_nums[i]) {
                second_largest = converted_nums[i];
            }
            double d1 = converted_nums[i] - min_value;
            double d2 = max_value - converted_nums[i];
            d1 = d1 < 0 ? -d1 : d1;
            d2 = d2 < 0 ? -d2 : d2;
            if (d1 < d2) {
                near_to_min++;
                diff_nums_near_to_min.insert(converted_nums[i]);
                group = min_group;
            } else {
                near_to_max++;
                diff_nums_near_to_max.insert(converted_nums[i]);
                group = max_group;
            }
            
            if (group[0] > converted_nums[i]) {
                group[0] = converted_nums[i];
            }
            if (group[1] < converted_nums[i]) {
                group[1] = converted_nums[i];
            }
        }
        
        double category_marker;
        if (diff_nums_near_to_min.size() == 1) {
            category_marker = min_value;
            min_value = second_smallest;
        } else if (diff_nums_near_to_max.size() == 1) {
            category_marker = max_value;
            max_value = second_largest;
        } else {
            category_marker = max_value + 1;
        }
        
        double range = max_value - min_value;
        
        double mid_min_group = std::abs(min_group[0] - min_group[1]) / 2.0;
        double mid_max_group = std::abs(max_group[0] - max_group[1]) / 2.0;
        bool abort_its_category = false;
        if ((mid_min_group + min_group[1] > range / 2) || (mid_max_group - max_group[0] < range / 2)) {
            
        } else {
            abort_its_category = true;
        }
        
        if (abort_its_category) {
            is_category = true;
            min_value = 0;
            max_value = all_mapped_values.size() - 1;
            for (unsigned int i = 0; i < ELEM_COUNT; i++) {
                output->push_back(all_mapped_values[data->at(i)]);
            }
        } else {
            double scale_reduction;
            if (range > 1 || range < -1) {
                scale_reduction = 1;
            } else {
                scale_reduction = .1;
            }
            min_value -= scale_reduction;
            double category_marker_value = min_value - scale_reduction;
            for (unsigned int i = 0; i < ELEM_COUNT; i++) {
                if (data->at(i) == placeholder) {
                    converted_nums[i] = min_value;
                } else if (converted_nums[i] == category_marker) {
                    converted_nums[i] = category_marker_value;
                }
            }
            
            
            for (unsigned int i = 0; i < ELEM_COUNT; i++) {
                output->push_back(converted_nums[i]);
            }
        }
        
        delete[] converted_nums;
    } else {
        is_category = true;
        min_value = 0;
        max_value = all_mapped_values.size() - 1;
        for (unsigned int i = 0; i < ELEM_COUNT; i++) {
            output->push_back(all_mapped_values[data->at(i)]);
        }
    }
    
    double range = max_value - min_value;
    for (unsigned int i = 0; i < ELEM_COUNT; i++) {
        (*output)[i] = (output->at(i) - min_value) / range;
    }
    
    if (!is_category) {
        
    }
    
    return output;
}

bool SpringleafDataParser::IsNumber(const string *str)
{
    for (unsigned int i = 0; i < str->length(); i++) {
        if ((*str)[i] < '0' || (*str)[i] > '9') {
            return false;
        }
    }
    return true;
}
