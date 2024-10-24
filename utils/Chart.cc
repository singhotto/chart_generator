#include "Chart.hh"

float max(const std::vector<float> &values) {
    if (values.empty()) 
        throw std::invalid_argument("The input vector is empty.");

    float maxValue = values[0]; 
    for (const float &value : values) {
        if (value > maxValue) {
            maxValue = value;
        }
    }
    return maxValue; // Return the result
}

Chart::Chart(const std::vector<float> &values)
    : Chart(values, std::vector<std::string>())
{
}

Chart::Chart(const std::vector<float> &values, const std::vector<std::string> &labels)
{
    float maxValue = max(values) * 1.1f;
    // heightFactor = maxValue / maxBarHeight;
    heightFactor = maxBarHeight / maxValue;

    if (!labels.empty() && labels.size() != values.size()) 
        throw std::invalid_argument("The input vector is empty.");


    int size = width * height * 3;
    pixels = new uint8_t[size];
    for (int i = 0; i < size; i++)
        pixels[i] = 255;
        
    if (values.size()>200){
        spacing = 1;
    }else if(values.size() > 100){
        spacing = 2;
    }else{
        spacing = 5;
    }
    
    barWidth = (chartWidth - (values.size()-1) * spacing)/values.size();
    
    data = values;
    this->labels = labels;
}

Chart::~Chart()
{
    delete[] pixels;
}

void Chart::setBarWidth(int w)
{
    barWidth = w;
}

void Chart::setSpacing(int s)
{
    spacing = s;
}

void Chart::setMaxDataValue(int v)
{
    maxDataValue = v;
}

void Chart::drawChar(char c, int x, int y, Color color, int scale)
{
    if (c < 0 || c > 127)
        return; // Ensure character is within bounds

    const uint8_t *bitmap = font[c];

    for (int i = 0; i < 8; ++i)
    {
        for (int j = 0; j < 8; ++j)
        {
            if (bitmap[i] & (1 << (7 - j)))
            { // Check if the pixel is set
                // Draw the character vertically (rotated 90 degrees)
                for (int dy = 0; dy < scale; ++dy)
                {
                    for (int dx = 0; dx < scale; ++dx)
                    {
                        // Adjust the coordinates to flip and rotate the character
                        int pixelX = x + i * scale + dx;              // Moving along x-axis normally
                        int pixelY = y - j * scale - dy;              // Invert y-axis to go up
                        int pixelIndex = (pixelY * width + pixelX);   // Calculate pixel index
                        
                        if (pixelIndex >= 0 && pixelIndex < width * height)
                        {                                         // Ensure within bounds
                            pixels[pixelIndex * 3 + 0] = color.b; // Blue
                            pixels[pixelIndex * 3 + 1] = color.g; // Green
                            pixels[pixelIndex * 3 + 2] = color.r; // Red
                        }
                    }
                }
            }
        }
    }
}


void Chart::setPixel(int x, int y, Color color)
{
    if (x >= 0 && x < width && y >= 0 && y < height)
    {
        int index = (y * width + x) * 3;
        pixels[index] = color.b;
        pixels[index + 1] = color.g;
        pixels[index + 2] = color.r;
    }
}

// Draw a line between two points
void Chart::drawLine(int x1, int y1, int x2, int y2, Color color)
{
    int dx = abs(x2 - x1);
    int dy = abs(y2 - y1);
    int sx = (x1 < x2) ? 1 : -1;
    int sy = (y1 < y2) ? 1 : -1;
    int err = dx - dy;

    while (true)
    {
        setPixel(x1, y1, color); // Set pixel color
        if (x1 == x2 && y1 == y2)
            break;
        int e2 = 2 * err;
        if (e2 > -dy)
        {
            err -= dy;
            x1 += sx;
        }
        if (e2 < dx)
        {
            err += dx;
            y1 += sy;
        }
    }
}

// Draw the X and Y axes
void Chart::drawAxes()
{
    // X-axis
    drawLine(marginX, height - marginBottom, width - marginX, height - marginBottom, {0, 0, 0}); // Black horizontal line
    // Y-axis
    drawLine(marginX, height - marginBottom, marginX, marginTop, {0, 0, 0}); // Black vertical line
}

// Draw labels on the X-axis
void Chart::drawXLabels(Color color)
{
    int xPos = marginX;
    const int axisMargin = 10;
    float barX = 0.0f;
    if (data.size()>200){
        barX = 0;
    }else if(data.size() > 100){
        barX = (barWidth / 8);
    }else if(data.size() > 50){
        barX = (barWidth / 4);
    }else{
        barX = (barWidth / 2);
    }

    for (const auto &label : labels)
    {
        int textX = xPos + barX;

        for(int i = 0;i<label.length(); i++){
            drawChar(label[label.length()-1-i], textX, height - marginBottom + axisMargin + 7 * i, color, 1);
        }
        
        xPos += barWidth + spacing;
    }
}

// Draw a vertical bar
void Chart::drawBar(int x, int barHeight, Color color)
{
    for (int i = 0; i < barWidth; ++i)
    {
        for (int j = 0; j < barHeight; ++j)
        {
            setPixel(x + i, height - marginBottom - j - 1, color); // Start from above the X-axis
        }
    }
}

void Chart::drawBars(Color color)
{
    for (size_t i = 0; i < data.size(); ++i) {
        int scaledHeight = data[i] * heightFactor;  // Scale the bar height

        drawBar(marginX + i * (barWidth + spacing), scaledHeight, color);  // Blue bars
    }
}

void Chart::writeBMP(const char *filename)
{
    BMPHeader bmpHeader;
    DIBHeader dibHeader;

    dibHeader.width = width;
    dibHeader.height = height;
    dibHeader.imageSize = width * height * 3;
    bmpHeader.fileSize = sizeof(BMPHeader) + sizeof(DIBHeader) + dibHeader.imageSize;

    std::ofstream file(filename, std::ios::binary);
    if (!file)
    {
        std::cerr << "Could not open file for writing.\n";
        return;
    }

    file.write(reinterpret_cast<const char *>(&bmpHeader), sizeof(BMPHeader));
    file.write(reinterpret_cast<const char *>(&dibHeader), sizeof(DIBHeader));

    for (int y = height - 1; y >= 0; --y)
    { // BMP format stores pixels bottom-to-top
        file.write(reinterpret_cast<const char *>(pixels + y * width * 3), width * 3);
    }

    file.close();
}