//
//  JSNodeHTTPProtocol.h
//  Javascripter
//
//  Created by Switt Kongdachalert on 31/12/17.
//  Copyright © 2017 Switt's Software. All rights reserved.
//

#ifndef JSNodeHTTPProtocol_h
#define JSNodeHTTPProtocol_h

#import "JSNodeEventEmitter.h"

/*
 Events are
 
 Event: 'checkContinue'
 Event: 'checkExpectation'
 Event: 'clientError'
 Event: 'close'
 Event: 'connect'
 Event: 'connection'
 Event: 'request'
 Event: 'upgrade'
 
 Functions are
 server.close([callback])
 server.listen()
 server.listening
 server.maxHeadersCount
 server.setTimeout([msecs][, callback])
 server.timeout
 server.keepAliveTimeout
 */

@protocol JSNodeHTTPProtocol <JSExport, JSNodeEventEmitterProtocol>

///A Boolean indicating whether or not the server is listening for connections
@property (readonly) BOOL listening;

///Limits maximum incoming headers count, equal to 2000 by default. If set to 0 - no limit will be applied
@property (assign) NSInteger maxHeadersCount;

///Timeout in milliseconds. Defaults to 120000
@property (assign) double timeout;

///Timeout in milliseconds. Defaults to 5000
@property (assign) double keepAliveTimeout;

///Stops the server from accepting new connections. See net.Server.close().
-(void)close:(JSValue *)callback;

///Starts the HTTP server listening for connections. This method is identical to server.listen() from net.Server
-(void)listen:(UInt16)port;

///Sets the timeout value for sockets, and emits a 'timeout' event on the Server object, passing the socket as an argument, if a timeout occurs
JSExportAs(setTimeout,
-(void)setTimeout:(double)msecs callback:(JSValue *)callback
);

@end


/**
 Event: 'aborted'
    Emitted when the request has been aborted and the network socket has closed
 Event: 'close'
    Indicates that the underlying connection was closed. Just like 'end', this event occurs only once per response
 
 It implements the Readable Stream interface, as well as the following additional events, methods, and properties.
 */
@protocol JSNodeHTTPIncomingMessageProtocol <JSExport, JSNodeEventEmitterProtocol>
@property (retain) NSDictionary *headers;
@property (retain) NSString *httpVersion;
@property (retain) NSString *httpVersionMajor;
@property (retain) NSString *httpVersionMinor;
@property (retain) NSString *method;

/**
 The raw request/response headers list exactly as they were received.
 Note that the keys and values are in the same list. It is not a list of tuples. So, the even-numbered offsets are key values, and the odd-numbered offsets are the associated values.
 Header names are not lowercased, and duplicates are not merged.
 */
@property (retain) NSArray <NSString *>*rawHeaders;

///The raw request/response trailer keys and values exactly as they were received. Only populated at the 'end' event.
@property (retain) NSArray <NSString *>*rawTrailers;

@property (assign) NSInteger statusCode;
@property (retain) NSString *statusMessage;

///The request/response trailers object. Only populated at the 'end' event.
@property (retain) id trailers;

///Request URL string. This contains only the URL that is present in the actual HTTP request.
///Only valid for request obtained from http.Server
@property (retain) NSString *url;

-(void)destroy:(JSValue *)error;

///Calls message.connection.setTimeout(msecs, callback)
///Returns message
-(id <JSNodeHTTPIncomingMessageProtocol>)setTimeout:(double)msecs callback:(JSValue *)callback;

//-(net.Socket)socket;
@end

@protocol JSNodeHTTPServerResponseProtocol <JSExport, JSNodeEventEmitterProtocol>
//@property (retain) Net.Socket connection;

///Boolean value that indicates whether the response has completed. Starts as false. After response.end() executes, the value will be true.
@property (assign) BOOL finished;

///Boolean (read-only). True if headers were sent, false otherwise.
@property (readonly) BOOL headersSent;

//@property (assign) BOOL sendDate;

//Reference to the underlying socket
//@property (retain) Net.socket socket;

///When using implicit headers (not calling response.writeHead() explicitly), this property controls the status code that will be sent to the client when the headers get flushed.
@property (assign) NSInteger statusCode;

///When using implicit headers (not calling response.writeHead() explicitly), this property controls the status message that will be sent to the client when the headers get flushed. If this is left as undefined then the standard message for the status code will be used.
@property (retain) NSString *statusMessage;

///This method adds HTTP trailing headers (a header but at the end of the message) to the response.
///Trailers will only be emitted if chunked encoding is used for the response; if it is not (e.g. if the request was HTTP/1.0), they will be silently discarded.
-(void)addTrailers:(NSDictionary *)headers;

/**
 Finishes sending the request. If any parts of the body are unsent, it will flush them to the stream. If the request is chunked, this will send the terminating '0\r\n\r\n'.
 
 @param data : if is specified, it is equivalent to calling request.write(data, encoding) followed by request.end(callback).
 
 @param callback : if is specified, it will be called when the request stream is finished.
 */
JSExportAs(end,
-(void)end:(NSString *)data encoding:(NSString *)encoding callback:(JSValue *)function
);

///Reads out a header that's already been queued but not sent to the client. Note that the name is case insensitive.
-(NSString *)getHeader:(NSString *)name;

///Returns an array containing the unique names of the current outgoing headers. All header names are lowercase
-(NSArray <NSString *>*)getHeaderNames;

///Returns a shallow copy of the current outgoing headers. Since a shallow copy is used, array values may be mutated without additional calls to various header-related http module methods. The keys of the returned object are the header names and the values are the respective header values. All header names are lowercase.
-(NSDictionary *)getHeaders;

///Returns true if the header identified by name is currently set in the outgoing headers. Note that the header name matching is case-insensitive.
-(BOOL)hasHeader:(NSString *)name;

///Removes a header that's queued for implicit sending.
-(void)removeHeader:(NSString *)name;

///Sets a single header value for implicit headers. If this header already exists in the to-be-sent headers, its value will be replaced. Use an array of strings here to send multiple headers with the same name.
JSExportAs(setHeader,
-(void)setHeader:(NSString *)name value:(JSValue *)value
);

//-(void)setTimeout

///If this method is called and response.writeHead() has not been called, it will switch to implicit header mode and flush the implicit headers.
JSExportAs(write,
-(BOOL)write:(NSString *)chunk encoding:(NSString *)encoding callback:(JSValue *)callback
);

///Sends a HTTP/1.1 100 Continue message to the client, indicating that the request body should be sent. See the 'checkContinue' event on Server.
-(void)writeContinue;

///Sends a response header to the request. The status code is a 3-digit HTTP status code, like 404. The last argument, headers, are the response headers. Optionally one can give a human-readable statusMessage as the second argument.
///This method must only be called once on a message and it must be called before response.end() is called.
-(void)writeHead:(NSInteger)statusCode
   statusMessage:(NSString *)statusMessage
         headers:(NSDictionary *)headers;

@end


#endif /* JSNodeHTTPProtocol_h */
