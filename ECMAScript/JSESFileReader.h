//
//  JSESFileReader.h
//  Javascripter
//
//  Created by Switt Kongdachalert on 31/12/17.
//  Copyright © 2017 Switt's Software. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "JSESDOMException.h"

@protocol JSESFileReaderProtocol <JSExport>
@property (readonly) JSESDOMException *exception;
@property (readonly) NSInteger *readyState;

///The file's contents. This property is only valid after the read operation is complete, and the format of the data depends on which of the methods was used to initiate the read operation
@property (readonly) id result;

///Event handlers
//@property (retain) JSValue *onabort;
//@property (retain) JSValue *onerror;

///A handler for the load event. This event is triggered each time the reading operation is successfully completed.
@property (retain) JSValue *onload;
//@property (retain) JSValue *onloadstart;
//@property (retain) JSValue *onloadend;
//@property (retain) JSValue *onprogress;
-(void)abort;

///Starts reading the contents of the specified Blob, once finished, the result attribute contains an ArrayBuffer representing the file's data.
-(void)readAsArrayBuffer;

///Starts reading the contents of the specified Blob, once finished, the result attribute contains the raw binary data from the file as a string.
-(void)readAsBinaryString;

///Starts reading the contents of the specified Blob, once finished, the result attribute contains a data: URL representing the file's data.
-(void)readAsDataURL;

///Starts reading the contents of the specified Blob, once finished, the result attribute contains the contents of the file as a text string.
-(void)readAsText;
@end

@interface JSESFileReader : NSObject <JSESFileReaderProtocol>

@end
