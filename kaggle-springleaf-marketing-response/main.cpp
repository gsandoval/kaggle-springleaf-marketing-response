//
//  main.cpp
//  kaggle-springleaf-marketing-response
//

#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
#include <cmath>
#include <string>
#include <fstream>
#include <queue>
#include <numeric>
#include <ctime>
#include <sstream>
#include <cstdio>
#include <cstdlib>
#include <limits>

#include "console_parameters.h"
#include "csv_column_reader.h"
#include "springleaf_data_parser.h"

using namespace std;

int main(int argc, const char * argv[]) {
    if (argc <= 1) {
        cerr << "Please specify the path for the file to be processed" << endl;
        return -1;
    }
    
    bool missing_parameters = false;
    ConsoleParameters params(argc, argv);
    if (!params.Has({"f", "file"})) {
        cerr << "You need to specify an input file" << endl;
        missing_parameters = true;
    }
    if (!params.Has({"c", "column"})) {
        cerr << "You need to specify a column to process" << endl;
        missing_parameters = true;
    }
    if (missing_parameters) {
        return -1;
    }
    
    string filename = params.GetString({"f", "file"});
    int column_index = params.GetInt({"c", "column"});
    column_index = 73;
    
    CsvColumnReader column_reader(filename);
    auto data = column_reader.GetColumnData(column_index);
    
    SpringleafDataParser parser;
    auto output = parser.ProcessColumn(data);
    
    return 0;
}
