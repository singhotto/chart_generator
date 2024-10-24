// BMPHeader.h
#ifndef BMPHEADER_H
#define BMPHEADER_H

#include <cstdint>

// BMP file header
#pragma pack(push, 1)
struct BMPHeader {
    uint16_t fileType = 0x4D42; // 'BM'
    uint32_t fileSize;
    uint16_t reserved1 = 0;
    uint16_t reserved2 = 0;
    uint32_t offsetData = 54; // Offset to pixel data
};

struct DIBHeader {
    uint32_t size = 40; // DIB header size
    int32_t width;
    int32_t height;
    uint16_t planes = 1;
    uint16_t bitCount = 24; // 24 bits per pixel
    uint32_t compression = 0;
    uint32_t imageSize;
    int32_t xPixelsPerMeter = 2835; // 72 DPI
    int32_t yPixelsPerMeter = 2835; // 72 DPI
    uint32_t colorsUsed = 0;
    uint32_t importantColors = 0;
};
#pragma pack(pop)

#endif // BMPHEADER_H
