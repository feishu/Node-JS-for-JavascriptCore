//
//  JSNodeEventEmitter.m
//  Javascripter
//
//  Created by Switt Kongdachalert on 29/12/17.
//  Copyright © 2017 Switt's Software. All rights reserved.
//

#import "JSNodeEventEmitter.h"

@implementation JSNodeEventEmitter {
    NSInteger _maxListeners;
    
    NSMutableDictionary <NSString *, NSMutableArray <JSValue *>*>*onceListeners;
    NSMutableDictionary <NSString *, NSMutableArray <JSValue *>*>*normalListeners;
    
    NSMutableArray <NSArray *> *toAddNormal, *toPrependNormal, *toRemoveOnce, *toRemoveNormal;
    
    BOOL _enumeratingNormal;
}
@synthesize defaultMaxListeners = _defaultMaxListeners;

-(id)init {
    _defaultMaxListeners = 10;
    onceListeners = [NSMutableDictionary new];
    normalListeners = [NSMutableDictionary new];
    
    return self;
}

-(NSInteger)defaultMaxListeners {
    return _defaultMaxListeners;
}

-(NSInteger)getMaxListeners {
    return _maxListeners;
}
-(id <JSNodeEventEmitterProtocol>)setMaxListeners:(NSInteger)n {
    _maxListeners = n;
    return self;
}

-(NSInteger)listenerCount:(NSString *)eventName {
    return _maxListeners ? _maxListeners : _defaultMaxListeners;
}

-(NSArray <JSValue *>*)listeners:(NSString *)eventName {
    NSArray <JSValue *>*onces = onceListeners[eventName];
    NSArray <JSValue *>*multiples = normalListeners[eventName];
    if(!onces) onces = @[]; if(!multiples) multiples = @[];
    
    return [onces arrayByAddingObjectsFromArray:multiples];
}


-(id<JSNodeEventEmitterProtocol>)on:(NSString *)eventName callback:(JSValue *)listener {
    if(_enumeratingNormal) {
        if(!toAddNormal) toAddNormal = [NSMutableArray new];
        [toAddNormal addObject:@[eventName, listener]];
    }
    
    NSMutableArray <JSValue *>*listeners = normalListeners[eventName];
    if(!listeners) {
        listeners = [NSMutableArray new];
        [normalListeners setObject:listeners forKey:eventName];
    }
    [self emit:@"newListener" :listener];
    [listeners addObject:listener];
    return self;
}

-(id<JSNodeEventEmitterProtocol>)once:(NSString *)eventName callback:(JSValue *)listener {
    NSMutableArray <JSValue *>*listeners = onceListeners[eventName];
    if(!listeners) {
        listeners = [NSMutableArray new];
        [onceListeners setObject:listeners forKey:eventName];
    }
    [self emit:@"newListener" :listener];
    [listeners addObject:listener];
    return self;
}

- (id<JSNodeEventEmitterProtocol>)addListener:(NSString *)eventName callback:(JSValue *)listener
{
    return [self on:eventName callback:listener];
}

- (id<JSNodeEventEmitterProtocol>)prependListener:(NSString *)eventName callback:(JSValue *)listener {
    if(_enumeratingNormal) {
        if(!toPrependNormal) toPrependNormal = [NSMutableArray new];
        [toPrependNormal addObject:@[eventName, listener]];
    }
    
    NSMutableArray <JSValue *>*listeners = normalListeners[eventName];
    if(!listeners) {
        listeners = [NSMutableArray new];
        [normalListeners setObject:listeners forKey:eventName];
    }
    [listeners insertObject:listener atIndex:0];
    return self;
}

-(id<JSNodeEventEmitterProtocol>)prependOnceListener:(NSString *)eventName
                                                callback:(JSValue *)listener {
    NSMutableArray <JSValue *>*listeners = onceListeners[eventName];
    if(!listeners) {
        listeners = [NSMutableArray new];
        [onceListeners setObject:listeners
                          forKey:eventName];
    }
    [listeners insertObject:listener atIndex:0];
    return self;
}

- (id<JSNodeEventEmitterProtocol>)removeAllListeners:(NSString *)eventName {
    onceListeners[eventName] = nil;
    normalListeners[eventName] = nil;
    return self;
}


- (id<JSNodeEventEmitterProtocol>)removeListener:(NSString *)eventName
                                            callback:(JSValue *)listener {
    NSMutableArray *ns = normalListeners[eventName];
    NSMutableArray *os = onceListeners[eventName];
    
    if(_enumeratingNormal)
        [toRemoveNormal addObject:@[eventName, listener]];
    else [ns removeObject:listener];
    
    [os removeObject:listener];
    [self emit:@"removeListener" :listener];
    
    return self;
}

-(NSArray<NSString *> *)eventNames {
    NSArray <NSString *> *ok = [onceListeners allKeys];
    NSArray <NSString *> *nk = [normalListeners allKeys];
    
    NSArray <NSString *>*allWithDuplicates = [ok arrayByAddingObjectsFromArray:nk];
    
    //removes the duplication
    return [[NSOrderedSet orderedSetWithArray:allWithDuplicates] array];
}


- (BOOL)emit:(NSString *)eventName :(id)arguments, ... {
    NSLog(@"emitted %@", eventName);
    NSArray *ns = normalListeners[eventName];
    NSArray *os = onceListeners[eventName];
    if(!ns && !os) return NO;
//
//    va_list args;
//    va_start(args, arguments);
//
//    NSMutableArray *argumentsArray = [JSContext currentArguments];
//
//    id arg = nil;
//    while ((arg = va_arg(args,id))) {
//        /// Do your thing with arg here
//        [argumentsArray addObject:arg];
//    }
//    va_end(args);
    
    NSArray *argumentsArray = [JSContext currentArguments];
    if([argumentsArray count] > 1) {
        argumentsArray = [argumentsArray subarrayWithRange:NSMakeRange(1, [argumentsArray count] - 1)];
    }
    return [self emit:eventName argumentsArray:argumentsArray];
}

-(void)addNormalToAdds {
    NSArray *toEnum = toAddNormal;
    toAddNormal = nil;
    for(NSArray *array in toEnum) {
        NSString *eventName = array[0];
        JSValue *listener = array[1];
        
        [self on:eventName callback:listener];
    }
    
    toEnum = toPrependNormal;
    toPrependNormal = nil;
    for(NSArray *array in toEnum) {
        NSString *eventName = array[0];
        JSValue *listener = array[1];
        [self prependListener:eventName callback:listener];
    }
}
-(void)removeNormalToRemoves {
    NSArray *toEnum = toRemoveNormal;
    toRemoveNormal = nil;
    for(NSArray *array in toEnum) {
        NSString *eventName = array[0];
        JSValue *listener = array[1];
        
        [normalListeners[eventName] removeObject:listener];
        [self emit:@"removeListener" :listener];
    }
}

-(BOOL)emit:(NSString *)eventName argumentsArray:(NSArray *)argumentsArray {
    NSArray *ns = normalListeners[eventName];
    NSArray *os = onceListeners[eventName];
    if(!ns && !os) return NO;
    
    _enumeratingNormal = YES;
    for(JSValue *listener in ns) {
        [listener callWithArguments:argumentsArray];
    }
    _enumeratingNormal = NO;
    [self removeNormalToRemoves];
    [self addNormalToAdds];
    
    onceListeners[eventName] = nil;
    
    for(JSValue *listener in os) {
        [listener callWithArguments:argumentsArray];
    }
    
    return YES;
}

@end
