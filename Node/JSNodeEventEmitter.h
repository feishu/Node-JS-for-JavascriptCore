//
//  JSNodeEventEmitter.h
//  Javascripter
//
//  Created by Switt Kongdachalert on 29/12/17.
//  Copyright © 2017 Switt's Software. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <JavaScriptCore/JavaScriptCore.h>

//typedef JSValue JSValue;

@protocol JSNodeEventEmitterProtocol <JSExport>
@property (readonly) NSInteger defaultMaxListeners;
-(id)init;
-(NSInteger)getMaxListeners;
-(id <JSNodeEventEmitterProtocol>)setMaxListeners:(NSInteger)n;

-(NSInteger)listenerCount:(NSString *)eventName;
-(NSArray <JSValue *>*)listeners:(NSString *)eventName;


JSExportAs(on,
-(id <JSNodeEventEmitterProtocol>)on:(NSString *)eventName callback:(JSValue *)listener
);

JSExportAs(once,
-(id <JSNodeEventEmitterProtocol>)once:(NSString *)eventName callback:(JSValue *)listener
);

JSExportAs(addListener,
-(id <JSNodeEventEmitterProtocol>)addListener:(NSString *)eventName callback:(JSValue *)listener
);

JSExportAs(prependListener,
-(id <JSNodeEventEmitterProtocol>)prependListener:(NSString *)eventName callback:(JSValue *)listener
           );

JSExportAs(prependOnceListener,
-(id <JSNodeEventEmitterProtocol>)prependOnceListener:(NSString *)eventName callback:(JSValue *)listener
           );

-(id <JSNodeEventEmitterProtocol>)removeAllListeners:(NSString *)eventName;

JSExportAs(removeListener,
-(id <JSNodeEventEmitterProtocol>)removeListener:(NSString *)eventName callback:(JSValue *)listener
           );

-(NSArray <NSString *>*)eventNames;

-(BOOL)emit:(NSString *)eventName :(id)arguments, ...;
@end

//Event: 'newListener' : The EventEmitter instance will emit its own 'newListener' event before a listener is added to its internal array of listeners
//Listeners registered for the 'newListener' event will be passed the event name and a reference to the listener being added.

//Event: 'removeListener' : The 'removeListener' event is emitted after the listener is removed.
@interface JSNodeEventEmitter : NSObject <JSNodeEventEmitterProtocol>
-(BOOL)emit:(NSString *)eventName argumentsArray:(NSArray *)argumentsArray;
+(id <JSNodeEventEmitterProtocol>)constructor;
@end
