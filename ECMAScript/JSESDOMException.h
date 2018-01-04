//
//  JSESDOMException.h
//  Javascripter
//
//  Created by Switt Kongdachalert on 31/12/17.
//  Copyright © 2017 Switt's Software. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <JavascriptCore/JavascriptCore.h>

#define INCOMPLETE_IMPLEMENTATION 1

@protocol JSESDOMException <JSExport>
@property (readonly) short code;
@property (readonly) NSString *message;
@property (readonly) NSString *name;
@end
@interface JSESDOMException : NSObject
@end
