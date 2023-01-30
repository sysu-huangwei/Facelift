//
//  EditViewController.h
//  PhotoRetoucher
//
//  Created by Ray on 2021/11/9.
//

#import "ViewController.h"
#import "GLView.h"

NS_ASSUME_NONNULL_BEGIN

@interface EditViewController : ViewController

@property (strong, nonatomic) IBOutlet GLView *showView;
@property (strong, nonatomic) IBOutlet UISlider *effectSlider;
@property (strong, nonatomic) IBOutlet UILabel *effectSliderLabel;
@property (strong, nonatomic) UIButton *currentSelectedButton;

- (instancetype)initWithOriginImage:(UIImage *)originImage;

@end

NS_ASSUME_NONNULL_END
