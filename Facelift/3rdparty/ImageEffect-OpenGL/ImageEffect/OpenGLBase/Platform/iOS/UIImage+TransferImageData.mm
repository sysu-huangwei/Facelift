//
//  UIImage+TransferImageData.mm
//
//  Created by rayyyhuang on 2022/11/26.
//

#import "UIImage+TransferImageData.h"

//图像格式
typedef NS_ENUM(NSUInteger , TransferImageDataFromat) {
    TransferImageDataFromat_ARGB = 0, //ARGB格式图像
    TransferImageDataFromat_RGBA = 1, //RGBA格式图像
    TransferImageDataFromat_GRAY = 2, //Gray格式图像
};

@implementation UIImage (TransferImageData)

#pragma mark UIImage图像和byte数据转换

- (unsigned char *)transferToARGBData {
    return [self transferToDataWithFormat:TransferImageDataFromat_ARGB isNeedAlpha:YES];
}

- (unsigned char *)transferToRGBAData {
    return [self transferToDataWithFormat:TransferImageDataFromat_RGBA isNeedAlpha:YES];
}

- (unsigned char *)transferToGrayData {
    return [self transferToDataWithFormat:TransferImageDataFromat_GRAY isNeedAlpha:YES];
}

/// 获取图像的 byte数据
/// @param format 图像像素格式
/// @param isNeedAlpha 是否需要保留透明度通道，如果不保留，透明通道会全部置为255（完全不透明）
- (unsigned char *)transferToDataWithFormat:(TransferImageDataFromat)format isNeedAlpha:(BOOL)isNeedAlpha {
    size_t width = CGImageGetWidth(self.CGImage);
    size_t height = CGImageGetHeight(self.CGImage);
    if(width == 0 || height == 0)
        return nullptr;
    
    unsigned char* imageData = nullptr;
    int bytesPerRow;
    CGImageAlphaInfo alphaInfo;
    CGColorSpaceRef colorSpace = CGColorSpaceCreateDeviceGray();
    switch (format) {
        case TransferImageDataFromat_ARGB:
            imageData = new unsigned char[width * height * 4];
            bytesPerRow = (int)width * 4;
            alphaInfo = kCGImageAlphaPremultipliedFirst;
            colorSpace = CGColorSpaceCreateDeviceRGB();
            break;
        case TransferImageDataFromat_RGBA:
            imageData = new unsigned char[width * height * 4];
            bytesPerRow = (int)width * 4;
            alphaInfo = kCGImageAlphaPremultipliedLast;
            colorSpace = CGColorSpaceCreateDeviceRGB();
            break;
        case TransferImageDataFromat_GRAY:
            imageData = new unsigned char[width * height];
            bytesPerRow = (int)width;
            alphaInfo = kCGImageAlphaNone;
            colorSpace = CGColorSpaceCreateDeviceGray();
            break;
        default:
            break;
    }
    
    CGContextRef gc = CGBitmapContextCreate(imageData, width, height, 8, bytesPerRow, colorSpace, alphaInfo);
    CGColorSpaceRelease(colorSpace);
    UIGraphicsPushContext(gc);
    
    if (!isNeedAlpha && format != TransferImageDataFromat_GRAY) {
        CGContextSetRGBFillColor(gc, 1.0, 1.0, 1.0, 1.0);
        CGContextFillRect(gc, CGRectMake(0.0, 0.0, (CGFloat)width, (CGFloat)height));
    }
    
    CGRect rect = {{0, 0}, {(CGFloat)width, (CGFloat)height}};
    CGContextDrawImage(gc, rect, self.CGImage);
    UIGraphicsPopContext();
    CGContextRelease(gc);
    
    return imageData;
}

+ (UIImage *)transferToImageWithARGBData:(unsigned char *)data withSize:(CGSize)size {
    return [self transferToImageWithARGBData:data withWidth:size.width withHeight:size.height];
}

+ (UIImage *)transferToImageWithARGBData:(unsigned char *)data withWidth:(int)width withHeight:(int)height {
    return [self transferToImageWithData:data withWidth:width withHeight:height withFormat:TransferImageDataFromat_ARGB];
}

+ (UIImage *)transferToImageWithRGBAData:(unsigned char *)data withSize:(CGSize) size {
    return [self transferToImageWithRGBAData:data withWidth:size.width withHeight:size.height];
}

+ (UIImage *)transferToImageWithRGBAData:(unsigned char *)data withWidth:(int)width withHeight:(int)height {
    return [self transferToImageWithData:data withWidth:width withHeight:height withFormat:TransferImageDataFromat_RGBA];
}

+ (UIImage *)transferToImageWithGrayData:(unsigned char *)data withSize:(CGSize)size {
    return [self transferToImageWithGrayData:data withWidth:size.width withHeight:size.height];
}

+ (UIImage *)transferToImageWithGrayData:(unsigned char *)data withWidth:(int)width withHeight:(int)height {
    return [self transferToImageWithData:data withWidth:width withHeight:height withFormat:TransferImageDataFromat_GRAY];
}

+ (UIImage *)transferToImageWithData:(unsigned char *)data withWidth:(int)width withHeight:(int)height withFormat:(TransferImageDataFromat)format {
    int bytesPerRow;
    CGImageAlphaInfo alphaInfo;
    CGColorSpaceRef colorSpace;
    switch (format) {
        case TransferImageDataFromat_ARGB:
            bytesPerRow = (int)width * 4;
            alphaInfo = kCGImageAlphaPremultipliedFirst;
            colorSpace = CGColorSpaceCreateDeviceRGB();
            break;
        case TransferImageDataFromat_RGBA:
            bytesPerRow = (int)width * 4;
            alphaInfo = kCGImageAlphaPremultipliedLast;
            colorSpace = CGColorSpaceCreateDeviceRGB();
            break;
        case TransferImageDataFromat_GRAY:
            bytesPerRow = (int)width;
            alphaInfo = kCGImageAlphaNone;
            colorSpace = CGColorSpaceCreateDeviceGray();
            break;
        default:
            break;
    }
    
    CGContextRef context = CGBitmapContextCreate(data, width, height, 8, bytesPerRow, colorSpace, alphaInfo);
    CGColorSpaceRelease(colorSpace);
    if (context == NULL) {
        return nil;
    }
    
    CGImageRef cgImageRef = CGBitmapContextCreateImage(context);
    CGContextRelease(context);
    UIImage *grayImage = [[UIImage alloc] initWithCGImage:cgImageRef];
    CGImageRelease(cgImageRef);
    return grayImage;
}

@end
