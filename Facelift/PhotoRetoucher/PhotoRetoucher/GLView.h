//
//  GLView.h
//  PhotoRetoucher
//
//  Created by rayyyhuang on 2022/11/14.
//

#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN

typedef NS_ENUM(NSUInteger, EffectType) {
    EffectType_Mesh = 7,
};

@interface GLView : UIView

- (void)setInputImage:(UIImage *)image;

- (void)render;

- (void)setEffectAlpha:(EffectType)type alpha:(float)alpha;

@end

NS_ASSUME_NONNULL_END
