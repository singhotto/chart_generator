# Chart Generator

`chart_generator` is a C++ library designed to generate charts from a set of values and their corresponding labels. This project provides functionalities to customize the appearance of the charts, including bar width, spacing, and maximum data values.

## Features

- Create charts with specified values and optional labels.
- Customize bar width and spacing between bars.
- Set the maximum data value for scaling the chart.
- Draw axes for better visualization.
- Save generated charts as BMP files.

## Main Functions

### Constructor

- `Chart(const std::vector<float>& values);`
  - Initializes a chart with the specified values.

- `Chart(const std::vector<float>& values, const std::vector<std::string>& labels);`
  - Initializes a chart with the specified values and labels.

### Destructor

- `~Chart();`
  - Cleans up resources when the chart object is destroyed.

### Setters

- `void setBarWidth(int w);`
  - Sets the width of the bars in the chart.

- `void setSpacing(int s);`
  - Sets the spacing between the bars.

- `void setMaxDataValue(int v);`
  - Sets the maximum data value for the chart, which is used for scaling.

### Drawing Functions

- `void drawAxes();`
  - Draws the axes for the chart.

- `void drawBars(Color color);`
  - Draws the bars in the chart with the specified color.

### File Output

- `void writeBMP(const char *filename);`
  - Saves the generated chart as a BMP file with the given filename.

## Usage Example

```cpp
#include "Chart.h"

int main() {
    std::vector<float> values = {10.0, 20.0, 30.0, 40.0};
    std::vector<std::string> labels = {"A", "B", "C", "D"};

    Chart chart(values, labels);
    chart.setBarWidth(50);
    chart.setSpacing(10);
    chart.setMaxDataValue(50);
    chart.drawAxes();
    chart.drawBars({150, 100, 200});
    chart.drawXLabels({255, 0, 0});
    chart.writeBMP("chart.bmp");

    return 0;
}
