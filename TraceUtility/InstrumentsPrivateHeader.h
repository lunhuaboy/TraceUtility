//
//  InstrumentsPrivateHeader.h
//  TraceUtility
//
//  Created by Qusic on 8/9/15.
//  Copyright (c) 2015 Qusic. All rights reserved.
//

#import <Foundation/Foundation.h>

#ifdef __cplusplus
extern "C" {
#endif
    NSString *PFTDeveloperDirectory(void);
    void PFTLoadPlugins(void);
#ifdef __cplusplus
}
#endif

@interface PFTCallTreeNode : NSObject
- (NSString *)libraryName;
- (NSString *)symbolName;
- (NSUInteger)address;
- (NSArray *)symbolNamePath; // Call stack
- (PFTCallTreeNode *)root;
- (PFTCallTreeNode *)parent;
- (NSArray *)children;
- (int)numberChildren;
- (int)terminals; // An integer value of this node, such as self running time in millisecond.
- (int)count; // Total value of all nodes of the subtree whose root node is this node. It means that if you increase terminals by a value, count will also be increased by the same value, and that the value of count is calculated automatically and you connot modify it.
- (NSUInteger)weightCount; // Count of different kinds of double values;
- (double)selfWeight:(NSUInteger)index; // A double value similar to terminal at the specific index.
- (double)weight:(NSUInteger)index; // A double value similar to count at the specific index. The difference is that you decide how weigh should be calculated.
- (double)selfCountPercent; // self.terminal / root.count
- (double)totalCountPercent; // self.count / root.count
- (double)parentCountPercent; // parent.count / root.count
- (double)selfWeightPercent:(NSUInteger)index; // self.selfWeight / root.weight
- (double)totalWeightPercent:(NSUInteger)index; // self.weight / root.weight
- (double)parentWeightPercent:(NSUInteger)index; // parent.weight / root.weight
@end

@interface XRBacktraceRepository : NSObject
- (PFTCallTreeNode *)rootNode;
- (void)refreshTreeRoot;
@end

@interface XRRun : NSObject
- (NSInteger)runNumber;
- (NSString *)displayName;
- (NSTimeInterval)startTime;
- (NSTimeInterval)endTime;
@end

@interface XRSamplerRun : XRRun
- (XRBacktraceRepository *)backtraceRepository;
@end

@interface XRRunListData : NSObject
- (NSDictionary *)runData;
- (NSArray *)runNumbers;
- (NSDictionary *)dataForAllRuns;
@end

@interface PFTInstrumentType : NSObject
- (NSString *)uuid;
- (NSString *)name;
- (NSString *)category;
@end

@interface XRDevice : NSObject
- (NSString *)deviceIdentifier;
- (NSString *)deviceDisplayName;
- (NSString *)deviceDescription;
- (NSString *)productType;
- (NSString *)productVersion;
- (NSString *)buildVersion;
@end

@interface PFTProcess : NSObject
- (NSString *)bundleIdentifier;
- (NSString *)displayName;
- (NSString *)executablePath;
- (NSArray *)arguments;
- (NSDictionary *)environment;
- (XRDevice *)device;
@end

@interface XRInstrument : NSObject
- (PFTInstrumentType *)type;
- (PFTProcess *)target;
- (NSArray *)allRuns;
@end

@interface PFTInstrumentList : NSObject
- (NSArray *)allInstruments;
@end

@interface XRTrace : NSObject
- (instancetype)initForCommandLine:(BOOL)commandLine;
- (PFTInstrumentList *)basicInstruments;
- (PFTInstrumentList *)recordingInstruments;
- (XRRunListData *)runData;
- (BOOL)saveDocument:(NSURL *)documentURL saveAllRuns:(BOOL)saveAllRuns error:(NSError **)errpt;
- (BOOL)loadDocument:(NSURL *)documentURL error:(NSError **)errpt;
- (void)close;
@end

@interface DVTDeveloperPaths : NSObject
+ (void)initializeApplicationDirectoryName:(id)arg1;
@end
