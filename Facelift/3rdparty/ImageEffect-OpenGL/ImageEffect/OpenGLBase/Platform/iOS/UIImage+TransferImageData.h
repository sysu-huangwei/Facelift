//
//  UIImage+TransferImageData.h
//
//  Created by rayyyhuang on 2022/11/26.
//

#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN

@interface UIImage (TransferImageData)

/// 获取ARGB的数据，内存由外部管理，需要delete
/// @return 图像ARGB格式的 byte数据
- (unsigned char *)transferToARGBData;

/// 获取RGBA的数据，内存由外部管理，需要delete
/// @return 图像RGBA格式的 byte数据
- (unsigned char *)transferToRGBAData;

/// 获取Gray的数据，内存由外部管理，需要delete
/// @return 图像Gray格式的 byte数据
- (unsigned char *)transferToGrayData;

/// 将ARGB byte数据转化为UIImage
/// @param data 图像ARGB格式的 byte数据
/// @param size 图像尺寸
/// @return 生成的UIImage
+ (UIImage *)transferToImageWithARGBData:(unsigned char *)data withSize:(CGSize)size;

/// 将ARGB byte数据转化为UIImage
/// @param data 图像ARGB格式的 byte数据
/// @param width 图像宽
/// @param height 图像高
/// @return 生成的UIImage
+ (UIImage *)transferToImageWithARGBData:(unsigned char *)data withWidth:(int)width withHeight:(int)height;

/// 将RGBA byte数据转化为UIImage
/// @param data 图像RGBA格式的 byte数据
/// @param size 图像尺寸
/// @return 生成的UIImage
+ (UIImage *)transferToImageWithRGBAData:(unsigned char *) data withSize:(CGSize) size;

/// 将RGBA byte数据转化为UIImage
/// @param data 图像RGBA格式的 byte数据
/// @param width 图像宽
/// @param height 图像高
/// @return 生成的UIImage
+ (UIImage *)transferToImageWithRGBAData:(unsigned char *)data withWidth:(int)width withHeight:(int)height;

/// 将Gray byte数据转化为UIImage
/// @param data 图像Gray格式的 byte数据
/// @param size 图像尺寸
/// @return 生成的UIImage
+ (UIImage *)transferToImageWithGrayData:(unsigned char *)data withSize:(CGSize)size;

/// 将Gray byte数据转化为UIImage
/// @param data 图像Gray格式的 byte数据
/// @param width 图像宽
/// @param height 图像高
/// @return 生成的UIImage
+ (UIImage *)transferToImageWithGrayData:(unsigned char *)data withWidth:(int)width withHeight:(int)height;

@end

NS_ASSUME_NONNULL_END
