//
//  JSSKFileReader.h
//  Javascripter
//
//  Created by Switt Kongdachalert on 31/12/17.
//  Copyright © 2017 Switt's Software. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <JavascriptCore/JavascriptCore.h>

@protocol JSSKFileReaderProtocol <JSExport>
+(NSString *)stringFromFileAtPath:(NSString *)filePath;
+(BOOL)saveString:(NSString *)string toFileAtPath:(NSString *)filePath;

+(NSString *)base64StringFromFileAtPath:(NSString *)filePath;
+(BOOL)saveBase64String:(NSString *)string toFileAtPath:(NSString *)filePath;

+(NSArray <NSString *>*)contentsOfDirectoryAtPath:(NSString *)filePath;
@end

@interface JSSKFileReader : NSObject <JSSKFileReaderProtocol>
@end
