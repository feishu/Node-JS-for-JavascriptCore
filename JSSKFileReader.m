//
//  JSSKFileReader.m
//  Javascripter
//
//  Created by Switt Kongdachalert on 31/12/17.
//  Copyright © 2017 Switt's Software. All rights reserved.
//

#import "JSSKFileReader.h"

@implementation JSSKFileReader {
}
static NSString *documentsDirectoryPath = nil;


+(NSString *)stringFromFileAtPath:(NSString *)filePath {
    NSString *fullPath = [[self documentsDirectoryPath] stringByAppendingPathComponent:filePath];
    return [NSString stringWithContentsOfFile:fullPath usedEncoding:nil error:nil];
}
+(BOOL)saveString:(NSString *)string toFileAtPath:(NSString *)filePath {
    NSString *fullPath = [[self documentsDirectoryPath] stringByAppendingPathComponent:filePath];
    return [string writeToFile:fullPath atomically:YES encoding:NSUTF8StringEncoding error:nil];
}


+(NSString *)base64StringFromFileAtPath:(NSString *)filePath {
    NSString *fullPath = [[self documentsDirectoryPath] stringByAppendingPathComponent:filePath];
    [NSFileManager defaultManager];
    return [[NSData dataWithContentsOfFile:fullPath] base64EncodedStringWithOptions:NSDataBase64EncodingEndLineWithLineFeed];
}
+(BOOL)saveBase64String:(NSString *)string toFileAtPath:(NSString *)filePath {
    NSData *data = [[NSData alloc] initWithBase64EncodedString:string options:NSDataBase64DecodingIgnoreUnknownCharacters];
    if(!data) return NO;
    
    NSString *fullPath = [[self documentsDirectoryPath] stringByAppendingPathComponent:filePath];
    return [data writeToFile:fullPath atomically:YES];
}


+(NSArray <NSString *>*)contentsOfDirectoryAtPath:(NSString *)filePath {
    NSString *fullPath = [[self documentsDirectoryPath] stringByAppendingPathComponent:filePath];
    return [[NSFileManager defaultManager] contentsOfDirectoryAtPath:fullPath error:nil];
}




+(NSString *)documentsDirectoryPath {
    if(!documentsDirectoryPath) {
        NSArray *paths = NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES);
        documentsDirectoryPath = [paths objectAtIndex:0];
    }
    return documentsDirectoryPath;
}

@end
