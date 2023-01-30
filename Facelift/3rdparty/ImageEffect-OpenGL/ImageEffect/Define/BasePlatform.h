//
//  BasePlatform.h
//
//  Created by rayyy on 2021/8/25.
//

#ifndef BASEPLATFORM_H
#define BASEPLATFORM_H

#if defined(WIN32) || defined(_WIN32) || defined(_WIN32_) || defined(WIN64) || defined(_WIN64) || defined(_WIN64_)
#define PLATFORM_WINDOWS 1 //Windows平台
#elif defined(ANDROID) || defined(_ANDROID_)
#define PLATFORM_ANDROID 1 //Android平台
#elif defined(__linux__)
#define PLATFORM_LINUX     1 //Linux平台
#elif defined(__APPLE__) || defined(TARGET_OS_IPHONE) || defined(TARGET_IPHONE_SIMULATOR) || defined(TARGET_OS_MAC)
#define PLATFORM_IOS     1 //iOS、Mac平台
#else
#define PLATFORM_UNKNOWN 1
#endif

#endif /* BASEPLATFORM_H */
