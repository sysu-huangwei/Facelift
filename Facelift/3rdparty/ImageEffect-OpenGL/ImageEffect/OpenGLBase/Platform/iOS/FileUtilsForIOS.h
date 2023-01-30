//
//  FileUtilsForIOS.h
//
//  Created by rayyyhuang on 2021/4/14.
//

const char *getResourcePathForIOS();

unsigned char *loadMemoryToRGBAPixelsForIOS(const char *memoryData, unsigned long dataSize, int &outWidth, int &outHeight);
