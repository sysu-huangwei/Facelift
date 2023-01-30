//
//  FileUtilsForIOS.mm
//
//  Created by rayyyhuang on 2021/4/14.
//

#import "FileUtilsForIOS.h"
#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#import "BaseDefine.h"

const char *getResourcePathForIOS() {
    return [NSBundle.mainBundle.bundlePath stringByAppendingPathComponent:@"ImageEffect.bundle"].UTF8String;
}

//Alpha为原始图像的透明度
unsigned char* RGBADataWithAlpha(UIImage* image) {
    CGImageAlphaInfo info = CGImageGetAlphaInfo(image.CGImage);
    BOOL hasAlpha = ((info == kCGImageAlphaPremultipliedLast) ||
                     (info == kCGImageAlphaPremultipliedFirst) ||
                     (info == kCGImageAlphaLast) ||
                     (info == kCGImageAlphaFirst) ? YES : NO);
    
    long width = CGImageGetWidth(image.CGImage);
    long height = CGImageGetHeight(image.CGImage);
    if(width == 0 || height == 0)
        return 0;
    unsigned char* imageData = (unsigned char *) malloc(4 * width * height);
    
    CGColorSpaceRef cref = CGColorSpaceCreateDeviceRGB();
    CGContextRef gc = CGBitmapContextCreate(imageData,
                                            width,height,
                                            8,width*4,
                                            cref,kCGImageAlphaPremultipliedLast);
    CGColorSpaceRelease(cref);
    UIGraphicsPushContext(gc);
    
    if (hasAlpha == YES)
    {
        CGContextSetRGBFillColor(gc, 1.0, 1.0, 1.0, 1.0);
        CGContextFillRect(gc, CGRectMake(0.0, 0.0, (CGFloat)width, (CGFloat)height));
    }
    CGRect rect = {{ 0 , 0 }, {(CGFloat)width, (CGFloat)height }};
    CGContextDrawImage( gc, rect, image.CGImage );
    UIGraphicsPopContext();
    CGContextRelease(gc);
    
    
    
    if (hasAlpha == YES)
    {
        unsigned char array[256][256] = {0};
        for (int j=1; j<256; j++)
        {
            for (int i=0; i<256; i++)
            {
                array[j][i] = fmin(fmax(0.0f,(j+i-255)*255.0/i+0.5),255.0f);
            }
        }
        GLubyte* alphaData = (GLubyte*) calloc(width * height, sizeof(GLubyte));
        CGContextRef alphaContext = CGBitmapContextCreate(alphaData, width, height, 8, width, NULL, kCGImageAlphaOnly);
        CGContextDrawImage(alphaContext, CGRectMake(0.0, 0.0, (CGFloat)width, (CGFloat)height), image.CGImage);
        // Draw the image into the bitmap context
        CGContextRelease(alphaContext);
        GLubyte* pDest = imageData;
        GLubyte* alphaTemp = alphaData;
        for (int j=0; j<height; j++)
        {
            for (int i=0; i<width; i++)
            {
                
                //自己反计算回原来的alpha值
                pDest[0] = array[pDest[0]][alphaTemp[0]];
                pDest[1] = array[pDest[1]][alphaTemp[0]];
                pDest[2] = array[pDest[2]][alphaTemp[0]];
                
                pDest[3] = alphaTemp[0];
                pDest += 4;
                alphaTemp++;
            }
        }
        free(alphaData);
    }
    
    
    return imageData;// CGBitmapContextGetData(gc);
}


unsigned char *loadMemoryToRGBAPixelsForIOS(const char *memoryData, unsigned long dataSize, int &outWidth, int &outHeight) {
    NSData *nsData = [NSData dataWithBytesNoCopy:(char *)memoryData length:dataSize freeWhenDone:NO];
    UIImage *image = [UIImage imageWithData:nsData];
    if (image == nil) {
        outWidth = 0;
        outHeight = 0;
        return NULL;
    }
    outWidth = image.size.width;
    outHeight = image.size.height;
    return RGBADataWithAlpha(image);
}
