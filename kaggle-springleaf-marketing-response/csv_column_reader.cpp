//
//  csv_column_reader.cpp
//  kaggle-springleaf-marketing-response
//
//  Created by Guillermo Alberto Sandoval Sanchez on 9/7/15.
//
//

#include "csv_column_reader.h"

using namespace std;

CsvColumnReader::CsvColumnReader(string filename)
{
    this->filename = filename;
}

shared_ptr<vector<string>> CsvColumnReader::GetColumnData(unsigned int column_index)
{
    FILE* input_file = fopen(this->filename.c_str(), "r");
    
    shared_ptr<vector<string>> rows(new vector<string>());
    
    const unsigned int BUFFER_SIZE = 500000;
    char buffer[BUFFER_SIZE];
    unsigned int line_num = 0;
    while (fscanf(input_file, "%[^\n]\n", buffer) != EOF) {
        if (line_num == 0) {
            line_num++;
            continue;
        }
        
        size_t len = strlen(buffer);
        unsigned int current_column_index = 0;
        size_t start = 0, end = len;
        
        unsigned int i = 0;
        for (; i < len && current_column_index < column_index; i++) {
            if (buffer[i] == ',') {
                start = i + 1;
                current_column_index++;
            }
        }
        for (; i < len; i++) {
            if (buffer[i] == ',') {
                end = i;
                break;
            }
        }
        if (buffer[start] == '"') {
            start++;
        }
        if (buffer[end - 1] == '"') {
            end--;
        }
        size_t str_len = end - start + 1;
        char* entry = new char[str_len];
        memset(entry, 0, str_len);
        memcpy(entry, buffer + start, end - start);

        rows->push_back(string(entry));
        
        delete[] entry;
        
        line_num++;
    }
    
    fclose(input_file);
    
    return rows;
}