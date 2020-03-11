#include <iostream>
#include <cmath>
#include <cstdlib>

#include "uiuc/PNG.h"
#include "uiuc/HSLAPixel.h"
#include "ImageTransform.h"

/* ******************
(Begin multi-line comment...)

Write your name and email address in the comment space here:

Name:
Email:

(...end multi-line comment.)
******************** */

using uiuc::PNG;
using uiuc::HSLAPixel;

/**
 * Returns an image that has been transformed to grayscale.
 *
 * The saturation of every pixel is set to 0, removing any color.
 *
 * @return The grayscale image.
 */
PNG grayscale(PNG image) {
  /// This function is already written for you so you can see how to
  /// interact with our PNG class.
  for (unsigned x = 0; x < image.width(); x++) {
    for (unsigned y = 0; y < image.height(); y++) {
      HSLAPixel & pixel = image.getPixel(x, y);

      // `pixel` is a reference to the memory stored inside of the PNG `image`,
      // which means you're changing the image directly. No need to `set`
      // the pixel since you're directly changing the memory of the image.
      pixel.s = 0;
    }
  }

  return image;
}



/**
 * Returns an image with a spotlight centered at (`centerX`, `centerY`).
 *
 * A spotlight adjusts the luminance of a pixel based on the distance the pixel
 * is away from the center by decreasing the luminance by 0.5% per 1 pixel euclidean
 * distance away from the center.
 *
 * For example, a pixel 3 pixels above and 4 pixels to the right of the center
 * is a total of `sqrt((3 * 3) + (4 * 4)) = sqrt(25) = 5` pixels away and
 * its luminance is decreased by 2.5% (0.975x its original value).  At a
 * distance over 160 pixels away, the luminance will always decreased by 80%.
 * 
 * The modified PNG is then returned.
 *
 * @param image A PNG object which holds the image data to be modified.
 * @param centerX The center x coordinate of the crosshair which is to be drawn.
 * @param centerY The center y coordinate of the crosshair which is to be drawn.
 *
 * @return The image with a spotlight.
 */
PNG createSpotlight(PNG image, int centerX, int centerY) {
    for (unsigned x = 0; x < image.width(); x++) {
      for (unsigned y = 0; y < image.height(); y++) {
          HSLAPixel & pixel = image.getPixel(x, y);
          int distance = eDistance(x, centerX, y, centerY);
          if (distance < 160.0){
              pixel.l = pixel.l*(1.0 - 0.005*floor(distance));
          }
          else {
              pixel.l = pixel.l*0.2;
          }
      }
    }
  return image;
  
}

float eDistance(unsigned int x1, unsigned int x2, unsigned int y1, unsigned int y2) {
    int dx = (x1 - x2)*(x1 - x2);
    int dy = (y1 - y2)*(y1 - y2);
    return (float) sqrt(dx + dy);
}
 

/**
 * Returns a image transformed to Illini colors.
 *
 * The hue of every pixel is set to the a hue value of either orange or
 * blue, based on if the pixel's hue value is closer to orange than blue.
 *
 * @param image A PNG object which holds the image data to be modified.
 *
 * @return The illinify'd image.
**/
PNG illinify(PNG image) {
    unsigned int w = image.width();
    unsigned int h = image.height();
    unsigned int iorange = 11;
    unsigned int iblue = 216;
    for (unsigned x = 0; x < w; x++) {
      for (unsigned y = 0; y < h; y++) {
          HSLAPixel & pixel = image.getPixel(x, y);
          if (hueDistance(pixel.h, iorange) < hueDistance(pixel.h, iblue)) {
              pixel.h = iorange;
          }
          else {
              pixel.h = iblue;
          }
        }
    }
  return image;
}
 

/**
* Returns an immge that has been watermarked by another image.
*
* The luminance of every pixel of the second image is checked, if that
* pixel's luminance is 1 (100%), then the pixel at the same location on
* the first image has its luminance increased by 0.2.
*
* @param firstImage  The first of the two PNGs, which is the base image.
* @param secondImage The second of the two PNGs, which acts as the stencil.
*
* @return The watermarked image.
*/
PNG watermark(PNG firstImage, PNG secondImage) {
    unsigned int w1 = firstImage.width();
    unsigned int w2 = secondImage.width();
    unsigned int h1 = firstImage.height();
    unsigned int h2 = secondImage.height();
    float xprog = 0.0; //tracks progress in x axis
    float yprog = 0.0; //tracks progress in y axis
    unsigned int x2 = 0;
    unsigned int y2 = 0;
    for (unsigned x = 0; x < w1; x++) {
      for (unsigned y = 0; y < h1; y++) {
          xprog = (float) x / (float) w1;
          yprog = (float) y / (float) h1;
          x2 = floor(xprog * w2);
          y2 = floor(yprog * h2);
          HSLAPixel & pixel = firstImage.getPixel(x, y);
          HSLAPixel & mask = secondImage.getPixel(x2, y2);
          if (mask.l == 1.0) {
              pixel.l = (pixel.l + 0.2) > 1.0 ? 1.0 : (pixel.l + 0.2);
          }
        }
    }
    return firstImage;
}

unsigned int hueDistance(int c1, int c2) {
    int d = mod(abs(c1 - c2), 360);
    d = d > 180 ? 360 - d : d;
    return (unsigned int) d;
}

int mod(int a, int b) {
    return a - floor(a/b)*b;
}
