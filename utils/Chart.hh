#ifndef CHART_GENERATOR_HH
#define CHART_GENERATOR_HH

#include <iostream>
#include <fstream>
#include <cstdint>
#include <vector>
#include "BMPHeader.hh"
#include "Font.hh"

struct Color {
    uint8_t r, g, b; // RGB values
};

class Chart
{
private:
    const int width = 1920;
    const int height = 1080;
    const int marginX = 50;
    const int marginTop = 30;
    const int marginBottom = 50;
    const int maxBarHeight = height - marginTop - marginBottom;
    const int chartWidth = width - marginX * 2;
    float heightFactor;
    int barWidth;
    int spacing;
    int maxDataValue;
    uint8_t* pixels;

    std::vector<float> data;

    void drawChar(char c, int x, int y, Color color, int scale);
    void setPixel(int x, int y, Color color);
    void drawLine(int x1, int y1, int x2, int y2, Color color);
public:
    Chart(const std::vector<float>& values);
    Chart(const std::vector<float>& values, const std::vector<std::string>& labels);
    ~Chart();

    void setBarWidth(int w);
    void setSpacing(int s);
    void setMaxDataValue(int v);

    void drawAxes();
    void drawXLabels(const std::vector<std::string> &labels);
    void drawBar(int x, int barHeight, Color color);
    void drawBars(Color color);
    void writeBMP(const char *filename);
};

#endif