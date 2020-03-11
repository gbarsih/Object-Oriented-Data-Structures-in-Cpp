#pragma once

#include "uiuc/PNG.h"
using namespace uiuc;

PNG grayscale(PNG image);  
PNG createSpotlight(PNG image, int centerX, int centerY);
PNG illinify(PNG image);
PNG watermark(PNG firstImage, PNG secondImage);
unsigned int hueDistance(int c1, int c2);
int mod(int a, int b);
float eDistance(unsigned int x1, unsigned int x2, unsigned int y1, unsigned int y2);
