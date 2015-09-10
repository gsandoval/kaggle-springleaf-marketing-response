//
//  springleaf_data_parser.h
//  kaggle-springleaf-marketing-response
//
//  Created by Guillermo Alberto Sandoval Sanchez on 9/7/15.
//
//

#ifndef __kaggle_springleaf_marketing_response__springleaf_data_parser__
#define __kaggle_springleaf_marketing_response__springleaf_data_parser__

#include <cstdio>
#include <memory>
#include <vector>
#include <string>

class SpringleafDataParser
{
private:
    bool IsNumber(const std::string *str);
public:
    
    std::shared_ptr<std::vector<double>> ProcessColumn(std::shared_ptr<std::vector<std::string>> data);
};

#endif /* defined(__kaggle_springleaf_marketing_response__springleaf_data_parser__) */
