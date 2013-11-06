//
//  MMRecordResponseSerializer.h
//  AFNetworking iOS Example
//
//  Created by Conrad Stoll on 10/17/13.
//  Copyright (c) 2013 Gowalla. All rights reserved.
//

#import "AFURLResponseSerialization.h"

#import <CoreData/CoreData.h>

/**
 MMRecordResponseSerializer is a response serializer for AFNetworking that can serialize an HTTP
 response object into a list of MMRecord objects. MMRecord objects are subclasses of Core Data
 NSManagedObjects. The record response serializer uses the MMRecord parsing system to convert from a
 response object into a list of parsed and fully populated managed objects. This allows you to use
 AFNetworking to make a HTTP request and to obtain NSManagedObjects directly in the success block
 for that request.
 
 The responseObject in the AFNetworking success block will contain an array of MMRecord subclasses
 when using the MMRecordResponseSerializer.
 
 You must initialize the record response serializer with both a NSManagedObjectContext and an
 instance of AFHTTPResponseSerializer. The context will be used for creating and updating parsed
 managed objects. The HTTP response serializer will be used for converting the HTTP response into
 a usable form. You are asked to specify the instance of the response serializer so that this class
 can support JSON, XML, or other forms of HTTP responses.
 
 You must also subclass MMRecordResponseSerializer in order to provide your own mapping from
 a response to a type of record. Use the response and response object to decide which form of entity
 you want to populate and return in the AFNetworking success block. Implementation of this mapping
 is required, and is left as an exercise to the reader.
 */
@interface MMRecordResponseSerializer : AFHTTPResponseSerializer <AFURLResponseSerialization>

@property (nonatomic, strong, readonly) NSManagedObjectContext *context;
@property (nonatomic, strong, readonly) AFHTTPResponseSerializer *HTTPResponseSerializer;

/**
 Designated initializer for the MMRecordResponseSerializer.
 
 @param context The managed object context you wish to have records returned associated with.
 @param HTTPResponseSerializer The base HTTP response serializer you want to use to serialize the 
 base response.
 */
+ (instancetype)serializerWithManagedObjectContext:(NSManagedObjectContext *)context
                            HTTPResponseSerializer:(AFHTTPResponseSerializer *)HTTPResponseSerializer;

/**
 Required subclass method for determining which type of entity to create objects of for a given
 response and response object.

 @param response The response from the HTTP request.
 @param responseObject The parsed response object returned from the designated HTTPResponseSerializer.
 @warning You are required to subclass this method.
 */
- (NSEntityDescription *)entityForResponse:(NSURLResponse *)response
                            responseObject:(id)responseObject;

@end