#include "Bitmap.h"
#include <windows.h>
#include <fstream>
#include <cassert>

#pragma pack(push, 2)
struct BMPFileHeader {
	unsigned short signature;
	unsigned int fileSize;
	unsigned int reserved;
	unsigned int offset;
};

struct BMPInfoHeader {
	unsigned int bitmapInfoHeaderSize;
	int width;
	int height;
	unsigned short numPlanes;
	unsigned short numBitsPerPixel;
	unsigned int compressionType;
	unsigned int imageDataSize;
	unsigned int horizontalResolution;
	unsigned int verticalResolution;
	unsigned int numColors;
	unsigned int numImportantColors;
};
#pragma pack(pop)

Bitmap::Bitmap(const std::string& filePath) {
	std::ifstream file(filePath, std::ios_base::binary);

	if (file.fail()) {
		throw std::runtime_error("shit's fucked up");
	}

	BMPFileHeader fileHeader;
	BMPInfoHeader infoHeader;

	file.read((char*)&fileHeader, sizeof(fileHeader));
	assert(fileHeader.signature == 0x4D42);
	assert(fileHeader.offset == 54);

	file.read((char*)&infoHeader, sizeof(infoHeader));
	assert(infoHeader.bitmapInfoHeaderSize == 40);
	assert(infoHeader.numPlanes == 1);
	assert(infoHeader.compressionType == 0);
	assert(infoHeader.numBitsPerPixel == 24);

	unsigned int numPixels = std::abs(infoHeader.width) * std::abs(infoHeader.height);
	mPixels.resize(numPixels);

	std::vector<PixelData> pixelData;
	pixelData.resize(numPixels);

	file.read((char*)&pixelData[0], numPixels * sizeof(PixelData));

	for (int pixelIndex = 0; pixelIndex < numPixels; ++pixelIndex) {
		std::memcpy(&mPixels[pixelIndex], &pixelData[pixelIndex], sizeof(PixelData));
	}
}
