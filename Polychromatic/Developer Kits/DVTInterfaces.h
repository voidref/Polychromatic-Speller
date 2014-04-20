//
//  DVTInterfaces.h
//  Polychromatic
//
//  Created by Kolin Krewinkel on 3/30/14.
//  Copyright 2014 Apple Inc. All rights reserved.
//
//  Sourced from class-dump. Some borrowed from CodePilot for quick compilation.
//

#import <Cocoa/Cocoa.h>

@interface IDEDocumentController : NSObject
+ (id)sharedDocumentController;
- (NSArray *)workspaceDocuments;
@end

@class DVTDocumentLocation, DVTFileDataType;
@interface DVTFilePath : NSObject
- (NSURL *)fileURL;
- (NSString *)pathString;
- (NSString *)fileName;
+ (DVTFilePath *)filePathForPathString:(NSString *)path;
- (DVTFilePath *)file;
- (NSImage *)navigableItem_image;

- (DVTDocumentLocation *)navigableItem_contentDocumentLocation;
- (DVTFileDataType *)navigableItem_documentType;
- (DVTFilePath *)parentFilePath;
- (DVTFilePath *)volumeFilePath;
@end

@interface IDEIndex : NSObject
{
}

+ (BOOL)languageSupportsSymbolColoring:(id)arg1;
+ (id)resolutionForName:(id)arg1 kind:(id)arg2 containerName:(id)arg3;
+ (id)pathToClang;
+ (id)_dataSourceExtensionForFile:(id)arg1 withLanguage:(id)arg2;
+ (void)syncPerformBlockOnMainThread:(dispatch_block_t)arg1;
+ (void)initialize;
+ (BOOL)includeAutoImportResults;
+ (BOOL)indexFollowsActiveScheme;
+ (id)schedulingLogAspect;
+ (id)clangInvocationLogAspect;
+ (id)symbolAdditionLogAspect;
+ (id)deferredMetricLogAspect;
+ (id)metricLogAspect;
+ (id)logAspect;
@property(readonly, nonatomic) DVTFilePath *databaseFile; // @synthesize databaseFile=_databaseFile;
//@property(readonly, nonatomic) IDEIndexDatabase *database; // @synthesize database=_workspaceDatabase;
- (id)targetIdentifiersForFile:(id)arg1;
- (id)mainFilesForFile:(id)arg1;
- (id)sdkForFile:(id)arg1;
- (id)timestampForFile:(id)arg1;
- (void)_buildOperationDidStop:(id)arg1;
- (void)_buildSettingsDidChange:(id)arg1;
- (void)_activeRunDestinationDidChange:(id)arg1;
- (void)_activeRunContextDidChange:(id)arg1;
- (void)_clearAllCachedBuildSettings;
- (void)_computePreferredTargets;
- (BOOL)isPreferredTarget:(id)arg1 priority:(char *)arg2;
- (BOOL)isPreferredTarget:(id)arg1;
- (id)databaseQueryProvider;
- (id)queryProviderForLocation:(id)arg1 highPriority:(BOOL)arg2;
- (void)dontDeferJobForFile:(id)arg1 indexable:(id)arg2;
- (void)registerHotFile:(id)arg1;
- (id)queryProviderForFile:(id)arg1 highPriority:(BOOL)arg2;
- (id)resolutionForName:(id)arg1 kind:(id)arg2 containerName:(id)arg3;
- (id)indexableForCopiedHeader:(id)arg1;
- (id)originalPathsForPaths:(id)arg1;
- (id)effectivePathForHeader:(id)arg1;
- (void)_initCopiedHeaders;
- (void)indexModuleIfNeeded:(id)arg1;
- (void)_cleanupOldPCHs;
- (void)didCancelIndexingPCHFile:(id)arg1;
- (BOOL)createPCHFile:(id)arg1 arguments:(id)arg2 hashCriteria:(id)arg3 target:(id)arg4 session:(id)arg5 willIndex:(BOOL)arg6 translationUnit:(id *)arg7;
- (void)database:(id)arg1 reportAutoQueryProgress:(double)arg2;
- (void)clearPCHFailuresForDatabase:(id)arg1;
- (void)databaseDidReportError:(id)arg1;
- (void)databaseDidLoad:(id)arg1;
- (void)databaseDidOpen:(id)arg1;
- (id)databaseProvidersAndVersions:(id)arg1;
- (void)database:(id)arg1 didForgetFiles:(id)arg2;
- (void)database:(id)arg1 didEndImportSession:(id)arg2;
- (void)databaseDidSave:(id)arg1;
- (void)databaseDidIndexHotFile:(id)arg1;
- (void)_respondToFileChangeNotification:(id)arg1;
@property(readonly, nonatomic) DVTFilePath *workspaceFile;
@property(readonly, nonatomic) NSString *workspaceName;
- (id)dataSourceExtensionForFile:(id)arg1 settings:(id)arg2;
- (id)_dataSourceExtensionForFile:(id)arg1 withSettings:(id)arg2;
- (id)settingsForFile:(id)arg1 indexable:(id)arg2;
- (id)_waitForSettingsForFile:(id)arg1 object:(id)arg2;
- (id)_waitForSettingsFromObject:(id)arg1;
- (id)workspaceHeadersForIndexable:(id)arg1;
- (void)gatherProductHeadersForIndexable:(id)arg1;
- (long long)purgeCount;
- (void)purgeFileCaches;
- (void)close;
- (void)editorWillSaveFile:(id)arg1;
- (void)expediteIndexing;
- (void)_stopIndexing;
- (void)setThrottleFactor:(double)arg1;
- (void)resumeIndexing;
- (void)suspendIndexing;
@property(readonly, nonatomic) BOOL shouldAllowRefactoring;
@property(readonly, nonatomic) BOOL isQuiescent;
- (void)doWhenFilesReady:(dispatch_block_t)arg1;
- (void)willRegisterMoreFiles:(BOOL)arg1;
- (void)unregisterFile:(id)arg1;
- (void)registerFile:(id)arg1;
- (id)indexableForIdentifier:(id)arg1;
- (void)unregisterObject:(id)arg1;
- (void)registerObject:(id)arg1;
- (void)postNotificationName:(id)arg1;
- (void)postNotificationName:(id)arg1 userInfo:(id)arg2;
- (id)description;
- (void)setIndexState:(id)arg1;
- (id)indexState;
@property(readonly) DVTFilePath *workspaceBuildProductsDirPath;
@property(readonly) DVTFilePath *headerMapFilePath;
- (void)observeValueForKeyPath:(id)arg1 ofObject:(id)arg2 change:(id)arg3 context:(void *)arg4;
- (BOOL)isCurrentForWorkspace:(id)arg1;
- (void)beginTextIndexing;
- (id)initWithWorkspace:(id)arg1;
- (id)initWithFolder:(id)arg1;
- (id)initWithFolder:(id)arg1 forWorkspace:(id)arg2;
- (void)_cleanupOldIndexFoldersForWorkspace:(id)arg1;
- (double)_atime:(struct stat *)arg1;
- (BOOL)_stat:(struct stat *)arg1 filePath:(id)arg2;
- (id)_databaseFileURLForFolder:(id)arg1;
- (id)_databaseFolderForWorkspace:(id)arg1;
- (BOOL)_reopenDatabaseWithRemoval:(BOOL)arg1;
- (BOOL)_createDatabaseFolder;
- (void)_setupObservers;
- (id)allAutoImportItemsMatchingKind:(id)arg1 symbolLanguage:(id)arg2;
- (id)allAutoImportItemsMatchingKind:(id)arg1;
- (id)filesWithSymbolOccurrencesMatchingName:(id)arg1 kind:(id)arg2;
- (id)classesWithReferencesToSymbols:(id)arg1;
- (id)allClassesWithMembers:(id)arg1;
- (id)classesWithMembers:(id)arg1;
- (id)allMethodsMatchingMethod:(id)arg1 forReceiver:(id)arg2;
- (id)membersMatchingName:(id)arg1 kinds:(id)arg2 forInterfaces:(id)arg3;
- (id)membersMatchingKinds:(id)arg1 forInterfaces:(id)arg2;
- (id)symbolsForResolutions:(id)arg1;
- (id)parsedCodeCommentAtLocation:(id)arg1 withCurrentFileContentDictionary:(id)arg2;
- (id)codeDiagnosticsAtLocation:(id)arg1 withCurrentFileContentDictionary:(id)arg2;
- (id)codeCompletionsAtLocation:(id)arg1 withCurrentFileContentDictionary:(id)arg2 completionContext:(id *)arg3;
- (id)allParentsOfSymbols:(id)arg1 cancelWhen:(dispatch_block_t)arg2;
- (id)topLevelSymbolsInFile:(id)arg1;
- (unsigned long long)countOfSymbolsMatchingKind:(id)arg1 workspaceOnly:(BOOL)arg2;
- (id)allSymbolsMatchingKind:(id)arg1 workspaceOnly:(BOOL)arg2 cancelWhen:(dispatch_block_t)arg3;
- (id)allSymbolsMatchingKind:(id)arg1 workspaceOnly:(BOOL)arg2;
- (id)allSymbolsMatchingKind:(id)arg1;
- (id)testMethodsForClasses:(id)arg1;
- (id)allSubClassesForClasses:(id)arg1;
- (id)allSymbolsMatchingNames:(id)arg1 kind:(id)arg2;
- (id)allSymbolsMatchingName:(id)arg1 kind:(id)arg2;
- (id)allProtocolsMatchingName:(id)arg1;
- (id)allClassesMatchingName:(id)arg1;
- (id)impliedHeadersForModuleImportLocation:(id)arg1 withCurrentFileContentDictionary:(id)arg2;
- (id)importedFileAtDocumentLocation:(id)arg1 withCurrentFileContentDictionary:(id)arg2;
- (id)importedFilesAtDocument:(id)arg1 withCurrentFileContentDictionary:(id)arg2;
- (id)collectionElementTypeSymbolForSymbol:(id)arg1 withCurrentFileContentDictionary:(id)arg2;
- (id)typeSymbolForSymbol:(id)arg1 withCurrentFileContentDictionary:(id)arg2;
- (id)messageReceiverInContext:(id)arg1 withCurrentFileContentDictionary:(id)arg2;
- (id)referencesToSymbolMatchingName:(id)arg1 inContext:(id)arg2 withCurrentFileContentDictionary:(id)arg3;
- (id)referencesToSymbol:(id)arg1 inContext:(id)arg2 withCurrentFileContentDictionary:(id)arg3;
- (id)symbolsUsedInContext:(id)arg1 withCurrentFileContentDictionary:(id)arg2;
- (id)symbolsOccurrencesInContext:(id)arg1 withCurrentFileContentDictionary:(id)arg2;
- (id)symbolsMatchingName:(id)arg1 inContext:(id)arg2 withCurrentFileContentDictionary:(id)arg3;
- (id)symbolsMatchingName:(id)arg1 inContext:(id)arg2;
- (id)symbolsContaining:(id)arg1 anchorStart:(BOOL)arg2 anchorEnd:(BOOL)arg3 subsequence:(BOOL)arg4 ignoreCase:(BOOL)arg5 cancelWhen:(dispatch_block_t)arg6;
- (id)symbolsContaining:(id)arg1 anchorStart:(BOOL)arg2 anchorEnd:(BOOL)arg3 subsequence:(BOOL)arg4 ignoreCase:(BOOL)arg5;
- (id)topLevelProtocolsWorkspaceOnly:(BOOL)arg1 cancelWhen:(dispatch_block_t)arg2;
- (id)topLevelProtocolsWorkspaceOnly:(BOOL)arg1;
- (id)topLevelProtocols;
- (id)topLevelClassesWorkspaceOnly:(BOOL)arg1 cancelWhen:(dispatch_block_t)arg2;
- (id)topLevelClassesWorkspaceOnly:(BOOL)arg1;
- (id)topLevelClasses;
- (id)filesContaining:(id)arg1 anchorStart:(BOOL)arg2 anchorEnd:(BOOL)arg3 subsequence:(BOOL)arg4 ignoreCase:(BOOL)arg5 cancelWhen:(dispatch_block_t)arg6;
- (id)filesIncludedByFile:(id)arg1;
- (id)filesIncludingFile:(id)arg1;
- (id)mainFileForSelectionFilePath:(id)arg1 buildSettings:(id *)arg2;
- (id)objCOrCCompilationUnitIndexablesForMainFile:(id)arg1 indexableObjects:(id)arg2;
- (BOOL)isFileObjCCompilationUnitOrHeader:(id)arg1 error:(id *)arg2;
- (id)_localizedPhraseForDependentObjCCompilationUnit:(id)arg1 errorLanguages:(id)arg2 sharedLanguageIdentifier:(id)arg3 sharedIndexableObject:(id)arg4;
- (id)_localizedDescriptionForObjCCompilationUnit:(id)arg1 errorLanguages:(id)arg2;
- (BOOL)_errorLanguages:(id *)arg1 forFilePath:(id)arg2 indexableObjects:(id)arg3;

@end

@interface DVTModelObject : NSObject
@end

@interface IDEContainerItem : DVTModelObject
@end

@interface IDEGroup : IDEContainerItem
- (NSArray *)subitems;
- (NSImage *)navigableItem_image;
@end

@interface IDEContainer : DVTModelObject
- (DVTFilePath *)filePath;
- (IDEGroup *)rootGroup;
- (void)debugPrintInnerStructure;
- (void)debugPrintStructure;
@end

@interface IDEXMLPackageContainer : IDEContainer
@end

@interface IDEWorkspace : IDEXMLPackageContainer
- (IDEIndex *)index;
- (NSString *)name;
- (NSSet *)referencedContainers;
@end

@interface IDEWorkspaceDocument : NSObject
- (IDEWorkspace *)workspace;
- (NSArray *)recentEditorDocumentURLs;
- (id)sdefSupport_fileReferences;
@end

@interface IDEWorkspaceWindow : NSWindow
- (IDEWorkspaceDocument *)document;
@end

@interface IDEWorkspaceWindow (MissingMethods)
+ (IDEWorkspaceWindow *)mc_lastActiveWorkspaceWindow;
@end

@interface DVTApplication : NSApplication
@end

@interface IDEApplication : DVTApplication
+ (IDEApplication *)sharedApplication;
@end

@interface DVTViewController : NSViewController
@end

@class DVTExtension;
@interface IDEViewController : DVTViewController

@property (nonatomic, retain) DVTExtension *representedExtension;

@end

@interface DVTLayoutView_ML : NSView
{
    NSMutableDictionary *invalidationTokens;
    BOOL _layoutNeeded;
    BOOL _implementsLayoutCompletionCallback;
    NSCountedSet *_frameChangeObservations;
    NSCountedSet *_boundsChangeObservations;
    BOOL _implementsDrawRect;
    BOOL _needsSecondLayoutPass;
}

+ (void)_layoutWindow:(id)arg1;
+ (void)_recursivelyLayoutSubviewsOfView:(id)arg1 populatingSetWithLaidOutViews:(id)arg2;
+ (void)_doRecursivelyLayoutSubviewsOfView:(id)arg1 populatingSetWithLaidOutViews:(id)arg2 completionCallBackHandlers:(id)arg3 currentLayoutPass:(long long)arg4 needsSecondPass:(char *)arg5;
+ (void)scheduleWindowForLayout:(id)arg1;
+ (id)alreadyLaidOutViewsForCurrentDisplayPassOfWindow:(id)arg1;
+ (void)clearAlreadyLaidOutViewsForCurrentDisplayPassOfWindow:(id)arg1;
@property BOOL needsSecondLayoutPass; // @synthesize needsSecondLayoutPass=_needsSecondLayoutPass;
@property(getter=isLayoutNeeded) BOOL layoutNeeded; // @synthesize layoutNeeded=_layoutNeeded;
- (BOOL)wantsDefaultClipping;
- (void)stopInvalidatingLayoutWithChangesToKeyPath:(id)arg1 ofObject:(id)arg2;
- (void)invalidateLayoutWithChangesToKeyPath:(id)arg1 ofObject:(id)arg2;
- (void)_autoLayoutViewViewFrameDidChange:(id)arg1;
- (void)_autoLayoutViewViewBoundsDidChange:(id)arg1;
- (void)stopInvalidatingLayoutWithBoundsChangesToView:(id)arg1;
- (void)stopInvalidatingLayoutWithFrameChangesToView:(id)arg1;
- (void)invalidateLayoutWithBoundsChangesToView:(id)arg1;
- (void)invalidateLayoutWithFrameChangesToView:(id)arg1;
- (void)tearDownObservationForObservedObject:(id)arg1 notificationName:(id)arg2 table:(id)arg3;
- (void)setupObservationForObservedObject:(id)arg1 selector:(SEL)arg2 notificationName:(id)arg3 table:(id *)arg4;
- (void)setFrameSize:(struct CGSize)arg1;
- (void)didCompleteLayout;
- (void)layoutBottomUp;
- (void)layoutTopDown;
- (void)layoutIfNeeded;
- (void)didLayoutSubview:(id)arg1;
- (id)subviewsOrderedForLayout;
- (void)viewWillDraw;
- (void)_reallyLayoutIfNeededBottomUp;
- (void)_reallyLayoutIfNeededTopDown;
- (void)invalidateLayout;
- (void)viewDidMoveToWindow;
- (id)initWithCoder:(id)arg1;
- (id)initWithFrame:(struct CGRect)arg1;
- (void)_DVTLayoutView_MLSharedInit;
- (void)dealloc;

@end

@interface DVTSourceNodeTypes : NSObject
{
}

+ (BOOL)nodeType:(short)arg1 conformsToNodeTypeNamed:(id)arg2;
+ (long long)nodeTypesCount;
+ (id)nodeTypeNameForId:(short)arg1;
+ (short)registerNodeTypeNamed:(id)arg1;
+ (void)initialize;

@end

@interface DVTSourceModelItem : NSObject
{
    int _rc;
    struct _NSRange _relativeLocation;
    long long _langId;
    long long _token;
    DVTSourceModelItem *_parent;
    NSMutableArray *_children;
    unsigned int _nodeType:15;
    unsigned int _isOpaque:1;
    unsigned int _dirty:1;
    unsigned int _isBlock:1;
    unsigned int _ignoreToken:1;
    unsigned int _inheritsNodeType:1;
    unsigned int _isIdentifier:1;
    unsigned int _needsAdjustNodeType:1;
    unsigned int _isSimpleToken:1;
    unsigned int _isVolatile:1;
    unsigned int _needToDirtyRightEdges:1;
}

+ (id)sourceModelItemWithRange:(struct _NSRange)arg1 language:(long long)arg2 token:(long long)arg3 nodeType:(short)arg4;
@property struct _NSRange relativeLocation; // @synthesize relativeLocation=_relativeLocation;
@property(retain, nonatomic) NSMutableArray *children; // @synthesize children=_children;
@property(nonatomic) DVTSourceModelItem *parent; // @synthesize parent=_parent;
@property long long token; // @synthesize token=_token;
@property long long langId; // @synthesize langId=_langId;
- (void)enumerateIdentifierItemsInRelativeRange:(struct _NSRange)arg1 usingBlock:(id)arg2;
- (void)clearAdjustedNodeTypes;
- (long long)compare:(id)arg1;
- (id)followingItem;
- (id)precedingItem;
- (id)_lastLeafItem;
- (id)_firstLeafItem;
- (id)nextItem;
- (id)previousItem;
- (BOOL)isAncestorOf:(id)arg1;
- (id)childAdjoiningLocation:(unsigned long long)arg1;
- (id)childEnclosingLocation:(unsigned long long)arg1;
- (id)_childEnclosingLocation:(unsigned long long)arg1;
- (unsigned long long)indexOfChildAtLocation:(unsigned long long)arg1;
- (unsigned long long)indexOfChildAfterLocation:(unsigned long long)arg1;
- (unsigned long long)indexOfChildBeforeLocation:(unsigned long long)arg1;
- (unsigned long long)numberOfChildren;
- (void)addChildrenFromArray:(id)arg1 inRange:(struct _NSRange)arg2;
- (void)addChildren:(id)arg1;
- (void)addChild:(id)arg1;
- (void)assignAllParents:(id)arg1;
- (void)assignParents:(id)arg1;
- (BOOL)isVolatile;
- (void)setVolatile:(BOOL)arg1;
@property BOOL needsAdjustNodeType;
- (BOOL)needToDirtyRightEdges;
- (void)setNeedToDirtyRightEdges:(BOOL)arg1;
- (BOOL)isSimpleToken;
- (void)setIsSimpleToken:(BOOL)arg1;
- (BOOL)inheritsNodeType;
- (void)setInheritsNodeType:(BOOL)arg1;
- (BOOL)ignoreToken;
- (void)setIgnoreToken:(BOOL)arg1;
- (BOOL)dirty;
- (void)setDirty:(BOOL)arg1;
- (BOOL)isIdentifier;
- (short)rawNodeType;
- (BOOL)isOpaque;
- (void)setIsOpaque:(BOOL)arg1;
- (short)nodeType;
- (void)setNodeType:(short)arg1;
- (struct _NSRange)innerRange;
- (void)offsetBy:(long long)arg1;
- (void)setRange:(struct _NSRange)arg1;
- (struct _NSRange)range;
- (id)enclosingBlock;
- (long long)blockDepth;
- (void)setIsBlock:(BOOL)arg1;
- (BOOL)isBlock;
- (void)dirtyRange:(struct _NSRange)arg1 changeInLength:(long long)arg2;
- (void)dirtyRelativeRange:(struct _NSRange)arg1 changeInLength:(long long)arg2;
- (void)validate;
- (id)dumpContext;
- (id)contextArray;
- (id)simpleDescription;
- (id)diffableDescription;
- (id)description;
- (id)innerDescription:(id)arg1 showSelf:(BOOL)arg2;
- (id)initWithRange:(struct _NSRange)arg1 language:(long long)arg2 token:(long long)arg3 nodeType:(short)arg4;
- (BOOL)_isDeallocating;
- (BOOL)_tryRetain;
- (unsigned long long)retainCount;
- (oneway void)release;
- (id)retain;

@end

#pragma mark -

@interface DVTSourceModel : NSObject
{
    struct _NSRange _dirtyRange;
    long long _batchDelta;
    DVTSourceModelItem *_sourceItems;
    BOOL _isDoingBatchEdit;
}

+ (id)editorResponsivenessPerformanceLogAspect;
+ (void)initialize;
@property BOOL isDoingBatchEdit; // @synthesize isDoingBatchEdit=_isDoingBatchEdit;
@property long long batchDelta; // @synthesize batchDelta=_batchDelta;
@property struct _NSRange dirtyRange; // @synthesize dirtyRange=_dirtyRange;
@property(retain) DVTSourceModelItem *sourceItems; // @synthesize sourceItems=_sourceItems;
- (id)objCMethodNameForItem:(id)arg1 nameRanges:(id *)arg2;
- (BOOL)isItemDictionaryLiteral:(id)arg1;
- (BOOL)isItemObjectLiteral:(id)arg1;
- (BOOL)isItemForStatement:(id)arg1;
- (BOOL)isItemSemanticBlock:(id)arg1;
- (BOOL)isItemBracketExpression:(id)arg1;
- (BOOL)isItemAngleExpression:(id)arg1;
- (BOOL)isItemParenExpression:(id)arg1;
- (BOOL)isPostfixExpressionAtLocation:(unsigned long long)arg1;
- (BOOL)isInTokenizableCodeAtLocation:(unsigned long long)arg1;
- (BOOL)isInPlainCodeAtLocation:(unsigned long long)arg1;
- (BOOL)isInKeywordAtLocation:(unsigned long long)arg1;
- (BOOL)isIncompletionPlaceholderAtLocation:(unsigned long long)arg1;
- (BOOL)isInNumberConstantAtLocation:(unsigned long long)arg1;
- (BOOL)isInCharacterConstantAtLocation:(unsigned long long)arg1;
- (BOOL)isInIdentifierAtLocation:(unsigned long long)arg1;
- (BOOL)isInStringConstantAtLocation:(unsigned long long)arg1;
- (BOOL)isInIncludeStatementAtLocation:(unsigned long long)arg1;
- (BOOL)isInPreprocessorStatementAtLocation:(unsigned long long)arg1;
- (BOOL)isInDocCommentAtLocation:(unsigned long long)arg1;
- (BOOL)isInCommentAtLocation:(unsigned long long)arg1;
- (id)completionPlaceholderItemAtLocation:(unsigned long long)arg1;
- (id)identOrKeywordItemAtLocation:(unsigned long long)arg1;
- (id)objCDeclaratorItemAtLocation:(unsigned long long)arg1;
- (id)numberConstantAtLocation:(unsigned long long)arg1;
- (id)characterConstantAtLocation:(unsigned long long)arg1;
- (id)stringConstantAtLocation:(unsigned long long)arg1;
- (id)moduleImportStatementAtLocation:(unsigned long long)arg1;
- (id)includeStatementAtLocation:(unsigned long long)arg1;
- (id)preprocessorStatementAtLocation:(unsigned long long)arg1;
- (id)docCommentAtLocation:(unsigned long long)arg1;
- (id)commentAtLocation:(unsigned long long)arg1;
- (id)placeholderItemsFromItem:(id)arg1;
- (id)identifierItemsFromItem:(id)arg1;
- (id)commentBlockItems;
- (id)functionsAndMethodItems;
- (id)classItems;
- (void)addBlockItemsInTypeList:(long long *)arg1 fromItem:(id)arg2 toArray:(id)arg3;
- (void)addIdentifierItemsFromItem:(id)arg1 toArray:(id)arg2;
- (void)addItemsInTypeList:(long long *)arg1 fromItem:(id)arg2 toArray:(id)arg3;
- (id)functionOrMethodDefinitionAtLocation:(unsigned long long)arg1;
- (id)functionOrMethodAtLocation:(unsigned long long)arg1;
- (id)interfaceDeclarationAtLocation:(unsigned long long)arg1;
- (id)typeDeclarationAtLocation:(unsigned long long)arg1;
- (id)classAtLocation:(unsigned long long)arg1;
- (id)itemNameAtLocation:(unsigned long long)arg1 inTypeList:(long long *)arg2 nameRanges:(id *)arg3 scopeRange:(struct _NSRange *)arg4;
- (id)nameOfItem:(id)arg1 nameRanges:(id *)arg2 scopeRange:(struct _NSRange *)arg3;
- (void)enumerateIdentifierItemsInRange:(struct _NSRange)arg1 usingBlock:(id)arg2;
- (id)itemAtLocation:(unsigned long long)arg1 ofType:(id)arg2;
- (id)itemAtLocation:(unsigned long long)arg1 inTypeList:(long long *)arg2;
- (long long *)typeListForSpecNames:(id)arg1;
- (id)builtUpNameForItem:(id)arg1 nameRanges:(id *)arg2;
- (id)_builtUpNameForItem:(id)arg1 mutableNameRanges:(id)arg2;
- (id)_builtUpNameForSubTree:(id)arg1 mutableNameRanges:(id)arg2;
- (id)objectLiteralItemAtLocation:(unsigned long long)arg1;
- (id)parenItemAtLocation:(unsigned long long)arg1;
- (id)parenLikeItemAtLocation:(unsigned long long)arg1;
- (id)foldableBlockItemForLocation:(unsigned long long)arg1;
- (id)foldableBlockItemForLineAtLocation:(unsigned long long)arg1;
- (id)blockItemAtLocation:(unsigned long long)arg1;
- (long long)indentForItem:(id)arg1;
- (id)adjoiningItemAtLocation:(unsigned long long)arg1;
- (id)enclosingItemAtLocation:(unsigned long long)arg1;
- (id)_topLevelSourceItem;
- (void)parse;
- (void)doingBatchEdit:(BOOL)arg1;
- (void)dirtyRange:(struct _NSRange)arg1 changeInLength:(long long)arg2;
- (id)initWithSourceBufferProvider:(id)arg1;

@end

#pragma mark -

@interface DVTSourceTextView : NSTextView

-(void)_commonInitDVTSourceTextView;

@end

#pragma mark -

@protocol DVTSourceLanguageSourceModelService <NSObject>
- (struct _NSRange)rangeForBlockContainingRange:(struct _NSRange)arg1;
- (NSString *)stringForItem:(DVTSourceModelItem *)arg1;
- (DVTSourceModelItem *)commonSourceModelItemAtRange:(struct _NSRange)arg1;
- (DVTSourceModelItem *)sourceModelItemAtCharacterIndex:(unsigned long long)arg1;
- (DVTSourceModelItem *)sourceModelItemAtCharacterIndex:(unsigned long long)arg1 affinity:(unsigned long long)arg2;
- (DVTSourceModel *)sourceModelWithoutParsing;
- (DVTSourceModel *)sourceModel;
@end

@interface DVTTextStorage : NSTextStorage

@property DVTSourceModel* sourceModel;
@property(readonly) id sourceModelService; // DVTSourceTextStorage

@property(readonly) unsigned long long currentChangeIndex;

-(NSColor*)colorAtCharacterIndex:(unsigned long long)charIndex effectiveRange:(NSRangePointer)range context:(id)context;
-(void)fixSyntaxColoringInRange:(NSRange)range;
-(short)nodeTypeAtCharacterIndex:(unsigned long long)charIndex effectiveRange:(NSRangePointer)range context:(id)context;
// FIXME: Workaround for NSObject+YOLO buggyness
-(NSColor*)yl_colorAtCharacterIndex:(unsigned long long)charIndex effectiveRange:(NSRangePointer)range context:(id)context;
- (id<DVTSourceLanguageSourceModelService>)sourceModelItemAtCharacterIndex:(unsigned long long)arg1; //DVTSourceTextStorage in Xcode 5, DVTSourceLanguageSourceModelService protocol in Xcode 5.1

@end

@class DVTCustomDataSpecifier, DVTPointerArray, DVTStackBacktrace, NSColor, NSFont, NSImage, NSString, NSURL;

@interface DVTFontAndColorTheme : NSObject
{
    NSString *_name;
    NSImage *_image;
    NSURL *_dataURL;
    DVTCustomDataSpecifier *_customDataSpecifier;
    NSColor *_sourceTextBackgroundColor;
    NSColor *_sourceTextSidebarBackgroundColor;
    NSColor *_sourceTextSidebarEdgeColor;
    NSColor *_sourceTextSidebarNumbersColor;
    NSColor *_sourceTextFoldbarBackgroundColor;
    NSColor *_sourceTextSelectionColor;
    NSColor *_sourceTextSecondarySelectionColor;
    NSColor *_sourceTextInsertionPointColor;
    NSColor *_sourceTextInvisiblesColor;
    NSColor *_sourceTextBlockDimBackgroundColor;
    NSColor *_sourceTextTokenizedBorderColor;
    NSColor *_sourceTextTokenizedBackgroundColor;
    NSColor *_sourceTextTokenizedBorderSelectedColor;
    NSColor *_sourceTextTokenizedBackgroundSelectedColor;
    NSColor *_consoleTextBackgroundColor;
    NSColor *_consoleTextSelectionColor;
    NSColor *_consoleTextSecondarySelectionColor;
    NSColor *_consoleTextInsertionPointColor;
    NSColor *_consoleDebuggerPromptTextColor;
    NSColor *_consoleDebuggerInputTextColor;
    NSColor *_consoleDebuggerOutputTextColor;
    NSColor *_consoleExecutableInputTextColor;
    NSColor *_consoleExecutableOutputTextColor;
    NSFont *_consoleDebuggerPromptTextFont;
    NSFont *_consoleDebuggerInputTextFont;
    NSFont *_consoleDebuggerOutputTextFont;
    NSFont *_consoleExecutableInputTextFont;
    NSFont *_consoleExecutableOutputTextFont;
    NSColor *_debuggerInstructionPointerColor;
    NSColor *_sourcePlainTextColor;
    NSFont *_sourcePlainTextFont;
    DVTPointerArray *_syntaxColorsByNodeType;
    DVTPointerArray *_syntaxFontsByNodeType;
    NSColor *_sourceTextCompletionPreviewColor;
    BOOL _builtIn;
    BOOL _loadedData;
    BOOL _contentNeedsSaving;
    BOOL _hasMultipleSourceTextFonts;
}

+ (id)_defaultSourceCodeFont;
+ (id)keyPathsForValuesAffectingConsoleTextSecondarySelectionColor;
+ (id)keyPathsForValuesAffectingSourceTextSecondarySelectionColor;
+ (id)titleForNewPreferenceSetFromTemplate;
+ (id)preferenceSetsListHeader;
+ (id)preferenceSetsFileExtension;
+ (id)defaultKeyForExcludedBuiltInPreferenceSets;
+ (id)defaultKeyForCurrentPreferenceSet;
+ (id)builtInPreferenceSetsDirectoryURL;
+ (id)systemPreferenceSet;
+ (id)preferenceSetGroupingName;
+ (id)_nodeTypesIncludedInPreferences;
+ (id)_stringRepresentationOfFont:(id)arg1;
+ (id)_fontWithName:(id)arg1 size:(double)arg2;
+ (id)currentTheme;
+ (id)preferenceSetsManager;
+ (void)initialize;
@property(readonly) BOOL loadedData; // @synthesize loadedData=_loadedData;
@property(readonly) DVTPointerArray *syntaxFontsByNodeType; // @synthesize syntaxFontsByNodeType=_syntaxFontsByNodeType;
@property(readonly) DVTPointerArray *syntaxColorsByNodeType; // @synthesize syntaxColorsByNodeType=_syntaxColorsByNodeType;
@property(nonatomic) BOOL hasMultipleSourceTextFonts; // @synthesize hasMultipleSourceTextFonts=_hasMultipleSourceTextFonts;
@property BOOL contentNeedsSaving; // @synthesize contentNeedsSaving=_contentNeedsSaving;
@property(retain) DVTCustomDataSpecifier *customDataSpecifier; // @synthesize customDataSpecifier=_customDataSpecifier;
@property(readonly, getter=isBuiltIn) BOOL builtIn; // @synthesize builtIn=_builtIn;
@property(retain) NSImage *image; // @synthesize image=_image;
@property(copy) NSString *name; // @synthesize name=_name;
- (void)setFont:(id)arg1 forNodeTypes:(id)arg2;
- (void)setColor:(NSColor *)arg1 forNodeTypes:(id)arg2;
- (void)_setColorOrFont:(id)arg1 forNodeTypes:(id)arg2;
- (id)fontForNodeType:(short)arg1;
- (NSColor *)colorForNodeType:(short)arg1;
@property(readonly) NSFont *sourcePlainTextFont;
@property(readonly) NSColor *sourcePlainTextColor;
- (void)setDebuggerInstructionPointerColor:(NSColor *)arg1;
- (void)setConsoleExecutableOutputTextFont:(NSFont *)arg1;
- (void)setConsoleExecutableInputTextFont:(NSFont *)arg1;
- (void)setConsoleDebuggerOutputTextFont:(NSFont *)arg1;
- (void)setConsoleDebuggerInputTextFont:(NSFont *)arg1;
- (void)setConsoleDebuggerPromptTextFont:(NSFont *)arg1;
- (void)setConsoleExecutableOutputTextColor:(NSColor *)arg1;
- (void)setConsoleExecutableInputTextColor:(NSColor *)arg1;
- (void)setConsoleDebuggerOutputTextColor:(NSColor *)arg1;
- (void)setConsoleDebuggerInputTextColor:(NSColor *)arg1;
- (void)setConsoleDebuggerPromptTextColor:(NSColor *)arg1;
- (void)primitiveSetConsoleDebuggerPromptTextColor:(NSColor *)arg1;
- (void)setConsoleTextInsertionPointColor:(NSColor *)arg1;
- (void)setConsoleTextSelectionColor:(NSColor *)arg1;
- (void)setConsoleTextBackgroundColor:(NSColor *)arg1;
- (void)setSourceTextInvisiblesColor:(NSColor *)arg1;
- (void)setSourceTextInsertionPointColor:(NSColor *)arg1;
- (void)setSourceTextSelectionColor:(NSColor *)arg1;
- (void)setSourceTextBackgroundColor:(NSColor *)arg1;
- (void)_setColorOrFont:(id)arg1 forKey:(id)arg2 colorOrFontivar:(id *)arg3;
@property(readonly) NSColor *debuggerInstructionPointerColor;
@property(readonly) NSFont *consoleExecutableOutputTextFont;
@property(readonly) NSFont *consoleExecutableInputTextFont;
@property(readonly) NSFont *consoleDebuggerOutputTextFont;
@property(readonly) NSFont *consoleDebuggerInputTextFont;
@property(readonly) NSFont *consoleDebuggerPromptTextFont;
@property(readonly) NSColor *consoleExecutableOutputTextColor;
@property(readonly) NSColor *consoleExecutableInputTextColor;
@property(readonly) NSColor *consoleDebuggerOutputTextColor;
@property(readonly) NSColor *consoleDebuggerInputTextColor;
@property(readonly) NSColor *consoleDebuggerPromptTextColor;
@property(readonly) NSColor *consoleTextInsertionPointColor;
@property(readonly) NSColor *consoleTextSecondarySelectionColor;
@property(readonly) NSColor *consoleTextSelectionColor;
@property(readonly) NSColor *consoleTextBackgroundColor;
@property(readonly) NSColor *sourceTextTokenizedBackgroundSelectedColor;
@property(readonly) NSColor *sourceTextTokenizedBorderSelectedColor;
@property(readonly) NSColor *sourceTextTokenizedBackgroundColor;
@property(readonly) NSColor *sourceTextTokenizedBorderColor;
@property(readonly) NSColor *sourceTextLinkColor;
@property(readonly) NSColor *sourceTextCompletionPreviewColor;
@property(readonly) NSColor *sourceTextBlockDimBackgroundColor;
@property(readonly) NSColor *sourceTextInvisiblesColor;
@property(readonly) NSColor *sourceTextInsertionPointColor;
@property(readonly) NSColor *sourceTextSecondarySelectionColor;
@property(readonly) NSColor *sourceTextSelectionColor;
@property(readonly) NSColor *sourceTextFoldbarBackgroundColor;
@property(readonly) NSColor *sourceTextSidebarNumbersColor;
@property(readonly) NSColor *sourceTextSidebarEdgeColor;
@property(readonly) NSColor *sourceTextSidebarBackgroundColor;
@property(readonly) NSColor *sourceTextBackgroundColor;
- (id)description;
@property(readonly) NSString *localizedName;
- (void)_updateHasMultipleSourceTextFonts;
- (void)_updateDerivedColors;
- (BOOL)_loadFontsAndColors;
- (id)dataRepresentationWithError:(id *)arg1;
- (void)primitiveInvalidate;
- (id)initWithCustomDataSpecifier:(id)arg1 basePreferenceSet:(id)arg2;
- (id)initWithName:(id)arg1 dataURL:(id)arg2;
- (id)_initWithName:(id)arg1 syntaxColorsByNodeType:(id)arg2 syntaxFontsByNodeType:(id)arg3;
- (void)_themeCommonInit;
- (id)init;

// Remaining properties
@property(retain) DVTStackBacktrace *creationBacktrace;
@property(readonly) DVTStackBacktrace *invalidationBacktrace;
@property(readonly, nonatomic, getter=isValid) BOOL valid;

@end

@interface DVTControllerContentView : DVTLayoutView_ML
{
    struct CGSize _minContentFrameSize;
    struct CGSize _maxContentFrameSize;
    DVTViewController *_viewController;
    NSWindow *_kvoWindow;
    int _horizontalAlignmentWhenClipping;
    int _horizontalAlignmentWhenPadding;
    int _verticalAlignmentWhenClipping;
    int _verticalAlignmentWhenPadding;
    int _verticalContentViewResizingMode;
    int _horizontalContentViewResizingMode;
    BOOL _isInstalled;
    BOOL _isPadding;
    BOOL _isReplacingSubview;
    BOOL _disablePaddingWarning;
    BOOL _isGrouped;
    NSMutableArray *_frameChangeTokens;
    NSArray *_currentContentViewConstraints;
    BOOL _constraintsCameFromNib;
}

+ (void)initialize;
@property BOOL isGrouped; // @synthesize isGrouped=_isGrouped;
@property BOOL disablePaddingWarning; // @synthesize disablePaddingWarning=_disablePaddingWarning;
@property(nonatomic) int verticalContentViewResizingMode; // @synthesize verticalContentViewResizingMode=_verticalContentViewResizingMode;
@property(nonatomic) int horizontalContentViewResizingMode; // @synthesize horizontalContentViewResizingMode=_horizontalContentViewResizingMode;
@property(nonatomic) int verticalAlignmentWhenClipping; // @synthesize verticalAlignmentWhenClipping=_verticalAlignmentWhenClipping;
@property(nonatomic) int horizontalAlignmentWhenClipping; // @synthesize horizontalAlignmentWhenClipping=_horizontalAlignmentWhenClipping;
@property(nonatomic) struct CGSize minimumContentViewFrameSize; // @synthesize minimumContentViewFrameSize=_minContentFrameSize;
@property(nonatomic) int verticalAlignmentWhenPadding; // @synthesize verticalAlignmentWhenPadding=_verticalAlignmentWhenPadding;
@property(nonatomic) int horizontalAlignmentWhenPadding; // @synthesize horizontalAlignmentWhenPadding=_horizontalAlignmentWhenPadding;
@property(nonatomic) struct CGSize maximumContentViewFrameSize; // @synthesize maximumContentViewFrameSize=_maxContentFrameSize;
- (BOOL)performKeyEquivalent:(id)arg1;
- (void)_invalidateLayoutBecauseOfSubviewFrameChange:(id)arg1;
- (void)willRemoveSubview:(id)arg1;
- (void)didAddSubview:(id)arg1;
- (void)windowWillClose:(id)arg1;
- (void)viewDidMoveToSuperview;
- (void)viewDidMoveToWindow;
- (void)viewWillMoveToSuperview:(id)arg1;
- (void)viewWillMoveToWindow:(id)arg1;
@property(readonly) BOOL isInstalled;
- (void)_viewDidInstall;
- (void)_viewWillUninstall;
@property(retain) IBOutlet NSView *contentView;
- (void)replaceSubview:(id)arg1 with:(id)arg2;
- (void)setSubviews:(id)arg1;
- (void)addSubview:(id)arg1;
- (void)layoutBottomUp;
- (void)layoutTopDown;
- (void)setTranslatesAutoresizingMaskIntoConstraints:(BOOL)arg1;
- (void)_syncContentViewTranslatesAutoresizingMaskIntoConstraintsValue;
- (void)updateConstraints;
- (void)setNextResponder:(id)arg1;
@property(retain, nonatomic) DVTViewController *viewController;
- (void)_checkKvoWindow;
@property(readonly) NSWindow *kvoWindow;
- (void)primitiveInvalidate;
- (id)initWithFrame:(struct CGRect)arg1;
- (void)awakeFromNib;
- (id)accessibilityAttributeValue:(id)arg1;
- (BOOL)accessibilityIsIgnored;

// Remaining properties
@property(retain) DVTStackBacktrace *creationBacktrace;
@property(readonly) DVTStackBacktrace *invalidationBacktrace;
@property(readonly, nonatomic, getter=isValid) BOOL valid;

@end

@interface DVTBorderedView : DVTLayoutView_ML
{
    NSColor *_topBorderColor;
    NSColor *_bottomBorderColor;
    NSColor *_leftBorderColor;
    NSColor *_rightBorderColor;
    NSColor *_topInactiveBorderColor;
    NSColor *_bottomInactiveBorderColor;
    NSColor *_leftInactiveBorderColor;
    NSColor *_rightInactiveBorderColor;
    NSColor *_shadowColor;
    NSColor *_backgroundColor;
    NSColor *_inactiveBackgroundColor;
    NSGradient *_backgroundGradient;
    NSGradient *_inactiveBackgroundGradient;
    NSView *_contentView;
    int _verticalContentViewResizingMode;
    int _horizontalContentViewResizingMode;
    int _borderSides;
    int _shadowSides;
//    id <DVTCancellable> _windowActivationObservation;
//    int _highlightSides;
//    id <DVTPainter> _backgroundPainter;
}

//@property(retain) id <DVTPainter> backgroundPainter; // @synthesize backgroundPainter=_backgroundPainter;
@property(nonatomic) int highlightSides; // @synthesize highlightSides=_highlightSides;
@property(nonatomic) int verticalContentViewResizingMode; // @synthesize verticalContentViewResizingMode=_verticalContentViewResizingMode;
@property(copy, nonatomic) NSColor *topInactiveBorderColor; // @synthesize topInactiveBorderColor=_topInactiveBorderColor;
@property(copy, nonatomic) NSColor *topBorderColor; // @synthesize topBorderColor=_topBorderColor;
@property int shadowSides; // @synthesize shadowSides=_shadowSides;
@property(copy) NSColor *shadowColor; // @synthesize shadowColor=_shadowColor;
@property(copy, nonatomic) NSColor *rightInactiveBorderColor; // @synthesize rightInactiveBorderColor=_rightInactiveBorderColor;
@property(copy, nonatomic) NSColor *rightBorderColor; // @synthesize rightBorderColor=_rightBorderColor;
@property(copy, nonatomic) NSColor *leftInactiveBorderColor; // @synthesize leftInactiveBorderColor=_leftInactiveBorderColor;
@property(copy, nonatomic) NSColor *leftBorderColor; // @synthesize leftBorderColor=_leftBorderColor;
@property(copy, nonatomic) NSGradient *inactiveBackgroundGradient; // @synthesize inactiveBackgroundGradient=_inactiveBackgroundGradient;
@property(copy, nonatomic) NSColor *inactiveBackgroundColor; // @synthesize inactiveBackgroundColor=_inactiveBackgroundColor;
@property(nonatomic) int horizontalContentViewResizingMode; // @synthesize horizontalContentViewResizingMode=_horizontalContentViewResizingMode;
@property(nonatomic) NSView *contentView; // @synthesize contentView=_contentView;
@property(copy, nonatomic) NSColor *bottomInactiveBorderColor; // @synthesize bottomInactiveBorderColor=_bottomInactiveBorderColor;
@property(copy, nonatomic) NSColor *bottomBorderColor; // @synthesize bottomBorderColor=_bottomBorderColor;
@property(nonatomic) int borderSides; // @synthesize borderSides=_borderSides;
@property(copy, nonatomic) NSGradient *backgroundGradient; // @synthesize backgroundGradient=_backgroundGradient;
@property(copy, nonatomic) NSColor *backgroundColor; // @synthesize backgroundColor=_backgroundColor;
- (void)window:(id)arg1 didChangeActivationState:(long long)arg2;
- (void)viewWillMoveToWindow:(id)arg1;
- (void)drawRect:(struct CGRect)arg1;
- (void)drawBorderInRect:(struct CGRect)arg1;
- (void)drawHighlightInRect:(struct CGRect)arg1;
- (void)drawBackgroundInRect:(struct CGRect)arg1;
- (BOOL)_isInactive;
- (void)layoutBottomUp;
- (void)layoutTopDown;
- (void)_contentViewFrameDidChange:(id)arg1;
- (struct CGSize)frameSizeForContentSize:(struct CGSize)arg1;
- (struct CGSize)boundSizeForContentSize:(struct CGSize)arg1;
@property(readonly) struct CGRect contentRect;
- (struct CGRect)_contentRectExcludingShadow;
//- (CDStruct_bf6d4a14)_contentInset;
//- (CDStruct_bf6d4a14)_borderInset;
//- (CDStruct_bf6d4a14)_shadowInset;
- (BOOL)isShowingShadow;
- (void)setAllInactiveBordersToColor:(id)arg1;
- (void)setAllBordersToColor:(id)arg1;
- (void)setShadowSide:(int)arg1;
- (void)_setBorderSides:(int)arg1;
- (void)dealloc;
- (void)encodeWithCoder:(id)arg1;
- (id)initWithCoder:(id)arg1;
- (id)initWithFrame:(struct CGRect)arg1;

@end

@class DVTBorderedView, DVTObservingToken, DVTReplacementView, DVTTabChooserView, NSArray, NSArrayController, NSColor, NSFont, NSObjectController, NSTableView, NSView;

@interface IDEFontAndColorPrefsPaneController : IDEViewController <NSTableViewDelegate>
{
    DVTReplacementView *preferenceSetReplacementView;
    DVTBorderedView *_fontAndColorBorderView;
    DVTTabChooserView *_tabChooserView;
    NSTableView *_fontAndColorItemTable;
    NSArrayController *_categoriesArrayController;
    NSObjectController *_currentThemeObjectController;
    DVTBorderedView *_generalColorView;
    NSView *_sourceEditorGeneralView;
    NSView *_consoleGeneralView;
    NSArray *_fontAndColorItems;
    DVTObservingToken *_selectedTabObserver;
    DVTObservingToken *_backgroundColorObserver;
    DVTObservingToken *_selectionIndexesObserver;
}

+ (void)initialize;
@property(readonly) NSArrayController *categoriesArrayController; // @synthesize categoriesArrayController=_categoriesArrayController;
@property(retain) NSArray *fontAndColorItems; // @synthesize fontAndColorItems=_fontAndColorItems;
- (void)changeFont:(id)arg1;
- (void)chooseFont:(id)arg1;
- (double)tableView:(id)arg1 heightOfRow:(long long)arg2;
- (void)tableView:(id)arg1 willDisplayCell:(id)arg2 forTableColumn:(id)arg3 row:(long long)arg4;
- (id)_theme;
- (void)_sourceTextColorsChanged:(id)arg1;
- (void)_updateBindingsBasedOnSelectedTab;
- (void)_handleTabChanged;
- (void)_initTabChooserView;
- (void)viewWillUninstall;
- (void)viewDidInstall;
- (void)loadView;
- (void)_updateFontPickerAndColorWell;
@property(copy) NSFont *combinedSyntaxFont;
@property(copy) NSColor *combinedSyntaxColor;
- (void)primitiveInvalidate;

@end

@class DVTChoice, NSArray, NSMapTable, NSMutableArray, NSSearchField;

@interface DVTTabChooserView : DVTBorderedView
{
    double *_currentChoiceXCoordinates;
    NSSearchField *_searchField;
    DVTChoice *_selectedChoice;
    long long _pressedIndex;
    long long _mouseDownIndex;
    NSMutableArray *_choices;
    NSMapTable *_accessibilityProxiesByChoice;
    struct {
        unsigned int hasSearchField:1;
        unsigned int _reserved:7;
    } _flags;
//    id <DVTTabChooserViewDelegate> _delegate;
    double _choicesOffset;
}

+ (id)keyPathsForValuesAffectingSelectedChoice;
+ (void)initialize;
@property double choicesOffset; // @synthesize choicesOffset=_choicesOffset;
//@property __weak id <DVTTabChooserViewDelegate> delegate; // @synthesize delegate=_delegate;
@property(retain, nonatomic) NSSearchField *searchField; // @synthesize searchField=_searchField;
- (id)accessibilityHitTest:(struct CGPoint)arg1;
- (BOOL)accessibilityIsAttributeSettable:(id)arg1;
- (id)accessibilityAttributeValue:(id)arg1;
- (id)accessibilityAttributeNames;
- (BOOL)accessibilityIsIgnored;
- (id)accessibilityProxyForChoice:(id)arg1;
@property BOOL hasSearchField;
- (void)installSearchField;
- (struct CGRect)searchFieldFrame;
- (void)mouseUp:(id)arg1;
- (void)mouseDragged:(id)arg1;
- (void)mouseDown:(id)arg1;
- (BOOL)acceptsFirstMouse:(id)arg1;
- (id)choiceForEvent:(id)arg1 index:(long long *)arg2;
- (id)choiceForPoint:(struct CGPoint)arg1 index:(long long *)arg2;
- (void)drawRect:(struct CGRect)arg1;
- (void)drawChoiceAtIndex:(long long)arg1;
- (void)drawOneChoice;
- (id)attributedTitleForChoice:(id)arg1 forceActive:(BOOL)arg2;
- (void)updateGeometryForDrawing;
- (struct CGRect)rectForChoice:(id)arg1;
- (struct CGRect)rectForChoiceAtIndex:(long long)arg1;
@property(readonly) double minimumWidth;
- (struct CGRect)totalChoicesRect;
- (double)totalWidth;
- (double)widthForChoiceAtIndex:(long long)arg1;
- (double)widthForChoice:(id)arg1;
- (void)updateBoundSelectedObjects;
@property(retain) DVTChoice *selectedChoice; // @synthesize selectedChoice=_selectedChoice;
@property(readonly) NSMutableArray *mutableChoices;
- (void)updateBoundContent;
@property(copy) NSArray *choices;
- (id)choiceWithIdentifier:(id)arg1;
- (id)choiceAtIndex:(long long)arg1;
- (void)viewWillMoveToWindow:(id)arg1;
- (void)dealloc;
- (id)initWithCoder:(id)arg1;
- (id)initWithFrame:(struct CGRect)arg1;
- (void)commonInit;
- (id)dvtExtraBindings;

@end


@interface DVTChoice : NSObject
{
    NSString *_title;
    NSString *_toolTip;
    NSImage *_image;
    NSString *_identifier;
    id _representedObject;
    BOOL _enabled;
}

@property(getter=isEnabled) BOOL enabled; // @synthesize enabled=_enabled;
@property(readonly) id representedObject; // @synthesize representedObject=_representedObject;
@property(copy) NSString *identifier; // @synthesize identifier=_identifier;
@property(readonly) NSImage *image; // @synthesize image=_image;
@property(readonly) NSString *toolTip; // @synthesize toolTip=_toolTip;
@property(readonly) NSString *title; // @synthesize title=_title;
- (id)description;
- (id)initWithTitle:(id)arg1 toolTip:(id)arg2 image:(id)arg3 representedObject:(id)arg4;

@end
