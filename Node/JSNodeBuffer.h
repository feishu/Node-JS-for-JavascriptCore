//
//  JSNodeBuffer.h
//  Javascripter
//
//  Created by Switt Kongdachalert on 31/12/17.
//  Copyright © 2017 Switt's Software. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <JavaScriptCore/JavaScriptCore.h>

@protocol JSNodeBufferProtocol <JSExport>
+(instancetype)alloc:(NSInteger)size :(id)fill :(NSString *)encoding;
+(instancetype)allocUnsafe:(NSInteger)size;
+(instancetype)allocUnsafeSlow:(NSInteger)size;
+(instancetype)byteLength:(NSString *)string :(NSString *)encoding;
+(instancetype)compare:(id <JSNodeBufferProtocol>)buf1 :(id <JSNodeBufferProtocol>)buf2;
+(instancetype)concat:(NSArray <id <JSNodeBufferProtocol>> *)list :(NSInteger)totalLength;

+(instancetype)from:(id)argument;
///Allocates a new Buffer using an array of octets
//+(instancetype)from:(NSArray *)array;
///Copies the passed buffer data onto a new Buffer instance
//+(instancetype)from:(id <JSNodeBufferProtocol>)buffer;
//+(instancetype)from:(ArrayBuffer)list :(NSInteger)byteOffset :(NSInteger)length;

+(BOOL)isBuffer:(id)argument;

///Returns true if encoding contains a supported character encoding, or false otherwise
+(BOOL)isEncoding:(NSString *)encoding;

///Default: 8192
///This is the number of bytes used to determine the size of pre-allocated, internal Buffer instances used for pooling. This value may be modified
+(NSInteger)poolSize;


@end
