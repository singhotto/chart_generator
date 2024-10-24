// main.cpp
#include <iostream>
#include <fstream>
#include <cstdint>
#include <string>
#include "utils/Chart.hh"

int main() {

    // Sample data for bar chart
    int size = 50;
    std::vector<float> values;
    std::vector<std::string> labels;
    values.reserve(size); 
    labels.reserve(size);

    for(int i = 1; i<size+1; i++){
        std::string s = std::to_string(i);
        values.push_back(i*10);
        labels.push_back(s);
    } 

    Chart chart(values, labels);
    
    // Draw bars with scaled heights
    chart.drawBars({150, 100, 200});

    // Draw axes and labels
    chart.drawAxes();
    chart.drawXLabels(labels);

    chart.writeBMP("output.bmp");

    return 0;
}
