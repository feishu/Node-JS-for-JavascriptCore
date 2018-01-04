//
//  JSNodeHTTPIncomingMessage.m
//  Javascripter
//
//  Created by Switt Kongdachalert on 1/1/18.
//  Copyright © 2018 Switt's Software. All rights reserved.
//

#import "JSNodeHTTPIncomingMessage.h"

@implementation JSNodeHTTPIncomingMessage
@synthesize url;
@synthesize headers;
@synthesize method;
@synthesize rawHeaders;
@synthesize httpVersion;
@synthesize httpVersionMajor;
@synthesize httpVersionMinor;
@synthesize statusCode;
@synthesize statusMessage;
@synthesize trailers;
@synthesize rawTrailers;


-(void)destroy:(JSValue *)error {
    
}

///Calls message.connection.setTimeout(msecs, callback)
///Returns message
-(id <JSNodeHTTPIncomingMessageProtocol>)setTimeout:(double)msecs callback:(JSValue *)callback {
    return self;
}

@end


@implementation JSNodeHTTPServerResponse {
    NSMutableString *_body;
    
    NSMutableDictionary *_headers;
}
@synthesize headersSent;
@synthesize statusMessage;
@synthesize finished;
@synthesize statusCode;
@synthesize body = _body;

-(id)init {
    if(self = [super init]) {
        statusCode = 200;
        statusMessage = @"";
        _body = [NSMutableString new];
        _headers = [NSMutableDictionary new];
    }
    return self;
}

- (void)addTrailers:(NSDictionary *)headers {
    
}

- (void)end:(NSString *)data encoding:(NSString *)encoding callback:(JSValue *)function {
    [_body appendString:data];
}

- (NSString *)getHeader:(NSString *)name {
    return nil;
}

- (NSArray<NSString *> *)getHeaderNames {
    return nil;
}

- (NSDictionary *)getHeaders {
    return nil;
}

- (BOOL)hasHeader:(NSString *)name {
    return NO;
}

- (void)removeHeader:(NSString *)name {
    
}

- (void)setHeader:(NSString *)name value:(JSValue *)value {
    
}

- (BOOL)write:(NSString *)chunk encoding:(NSString *)encoding callback:(JSValue *)callback {
    [_body appendString:chunk];
    return YES;
}

- (void)writeContinue {
    
}

- (void)writeHead:(NSInteger)statusCode statusMessage:(NSString *)statusMessage headers:(NSDictionary *)headers {
    self.statusCode = statusCode;
    self.statusMessage = statusMessage;
    [_headers addEntriesFromDictionary:headers];
}

@end

