//
//  csv_column_reader.h
//  kaggle-springleaf-marketing-response
//
//  Created by Guillermo Alberto Sandoval Sanchez on 9/7/15.
//
//

#ifndef __kaggle_springleaf_marketing_response__csv_column_reader__
#define __kaggle_springleaf_marketing_response__csv_column_reader__

#include <cstdio>
#include <string>
#include <vector>
#include <memory>

class CsvColumnReader
{
private:
    std::string filename;
public:
    CsvColumnReader(std::string filename);
    
    std::shared_ptr<std::vector<std::string>> GetColumnData(unsigned int column_index);
};

#endif /* defined(__kaggle_springleaf_marketing_response__csv_column_reader__) */
