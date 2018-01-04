//
//  JSNodeHTTPIncomingMessage.h
//  Javascripter
//
//  Created by Switt Kongdachalert on 1/1/18.
//  Copyright © 2018 Switt's Software. All rights reserved.
//

#import "JSNodeEventEmitter.h"
#import "JSNodeHTTPProtocol.h"

@interface JSNodeHTTPIncomingMessage : JSNodeEventEmitter <JSNodeHTTPIncomingMessageProtocol>

@end


@interface JSNodeHTTPServerResponse : JSNodeEventEmitter <JSNodeHTTPServerResponseProtocol>
@property (readonly) NSString *body;
@end
