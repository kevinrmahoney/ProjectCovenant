// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
struct FFMODEventInstance;
class UFMODVCA;
class UFMODBus;
class UObject;
class UFMODEvent;
class UFMODBank;
class UFMODAsset;
class USceneComponent;
class UFMODAudioComponent;
#ifdef FMODSTUDIO_FMODBlueprintStatics_generated_h
#error "FMODBlueprintStatics.generated.h already included, missing '#pragma once' in FMODBlueprintStatics.h"
#endif
#define FMODSTUDIO_FMODBlueprintStatics_generated_h

#define FID_ProjectCovenant_Plugins_FMODStudio_Source_FMODStudio_Classes_FMODBlueprintStatics_h_29_GENERATED_BODY \
	friend struct Z_Construct_UScriptStruct_FFMODEventInstance_Statics; \
	FMODSTUDIO_API static class UScriptStruct* StaticStruct();


template<> FMODSTUDIO_API UScriptStruct* StaticStruct<struct FFMODEventInstance>();

#define FID_ProjectCovenant_Plugins_FMODStudio_Source_FMODStudio_Classes_FMODBlueprintStatics_h_44_SPARSE_DATA
#define FID_ProjectCovenant_Plugins_FMODStudio_Source_FMODStudio_Classes_FMODBlueprintStatics_h_44_RPC_WRAPPERS \
 \
	DECLARE_FUNCTION(execSetLocale); \
	DECLARE_FUNCTION(execMixerResume); \
	DECLARE_FUNCTION(execMixerSuspend); \
	DECLARE_FUNCTION(execSetOutputDriverByIndex); \
	DECLARE_FUNCTION(execSetOutputDriverByName); \
	DECLARE_FUNCTION(execGetOutputDrivers); \
	DECLARE_FUNCTION(execEventInstanceSetTransform); \
	DECLARE_FUNCTION(execEventInstanceKeyOff); \
	DECLARE_FUNCTION(execEventInstanceRelease); \
	DECLARE_FUNCTION(execEventInstanceStop); \
	DECLARE_FUNCTION(execEventInstancePlay); \
	DECLARE_FUNCTION(execEventInstanceSetProperty); \
	DECLARE_FUNCTION(execEventInstanceGetParameterValue); \
	DECLARE_FUNCTION(execEventInstanceGetParameter); \
	DECLARE_FUNCTION(execEventInstanceSetParameter); \
	DECLARE_FUNCTION(execEventInstanceSetPaused); \
	DECLARE_FUNCTION(execEventInstanceSetPitch); \
	DECLARE_FUNCTION(execEventInstanceSetVolume); \
	DECLARE_FUNCTION(execEventInstanceIsValid); \
	DECLARE_FUNCTION(execGetGlobalParameterValueByName); \
	DECLARE_FUNCTION(execGetGlobalParameterByName); \
	DECLARE_FUNCTION(execSetGlobalParameterByName); \
	DECLARE_FUNCTION(execVCASetVolume); \
	DECLARE_FUNCTION(execBusStopAllEvents); \
	DECLARE_FUNCTION(execBusSetMute); \
	DECLARE_FUNCTION(execBusSetPaused); \
	DECLARE_FUNCTION(execBusSetVolume); \
	DECLARE_FUNCTION(execFindEventInstances); \
	DECLARE_FUNCTION(execUnloadEventSampleData); \
	DECLARE_FUNCTION(execLoadEventSampleData); \
	DECLARE_FUNCTION(execUnloadBankSampleData); \
	DECLARE_FUNCTION(execLoadBankSampleData); \
	DECLARE_FUNCTION(execIsBankLoaded); \
	DECLARE_FUNCTION(execUnloadBank); \
	DECLARE_FUNCTION(execLoadBank); \
	DECLARE_FUNCTION(execFindEventByName); \
	DECLARE_FUNCTION(execFindAssetByName); \
	DECLARE_FUNCTION(execPlayEventAttached); \
	DECLARE_FUNCTION(execPlayEventAtLocation); \
	DECLARE_FUNCTION(execPlayEvent2D);


#define FID_ProjectCovenant_Plugins_FMODStudio_Source_FMODStudio_Classes_FMODBlueprintStatics_h_44_RPC_WRAPPERS_NO_PURE_DECLS \
 \
	DECLARE_FUNCTION(execSetLocale); \
	DECLARE_FUNCTION(execMixerResume); \
	DECLARE_FUNCTION(execMixerSuspend); \
	DECLARE_FUNCTION(execSetOutputDriverByIndex); \
	DECLARE_FUNCTION(execSetOutputDriverByName); \
	DECLARE_FUNCTION(execGetOutputDrivers); \
	DECLARE_FUNCTION(execEventInstanceSetTransform); \
	DECLARE_FUNCTION(execEventInstanceKeyOff); \
	DECLARE_FUNCTION(execEventInstanceRelease); \
	DECLARE_FUNCTION(execEventInstanceStop); \
	DECLARE_FUNCTION(execEventInstancePlay); \
	DECLARE_FUNCTION(execEventInstanceSetProperty); \
	DECLARE_FUNCTION(execEventInstanceGetParameterValue); \
	DECLARE_FUNCTION(execEventInstanceGetParameter); \
	DECLARE_FUNCTION(execEventInstanceSetParameter); \
	DECLARE_FUNCTION(execEventInstanceSetPaused); \
	DECLARE_FUNCTION(execEventInstanceSetPitch); \
	DECLARE_FUNCTION(execEventInstanceSetVolume); \
	DECLARE_FUNCTION(execEventInstanceIsValid); \
	DECLARE_FUNCTION(execGetGlobalParameterValueByName); \
	DECLARE_FUNCTION(execGetGlobalParameterByName); \
	DECLARE_FUNCTION(execSetGlobalParameterByName); \
	DECLARE_FUNCTION(execVCASetVolume); \
	DECLARE_FUNCTION(execBusStopAllEvents); \
	DECLARE_FUNCTION(execBusSetMute); \
	DECLARE_FUNCTION(execBusSetPaused); \
	DECLARE_FUNCTION(execBusSetVolume); \
	DECLARE_FUNCTION(execFindEventInstances); \
	DECLARE_FUNCTION(execUnloadEventSampleData); \
	DECLARE_FUNCTION(execLoadEventSampleData); \
	DECLARE_FUNCTION(execUnloadBankSampleData); \
	DECLARE_FUNCTION(execLoadBankSampleData); \
	DECLARE_FUNCTION(execIsBankLoaded); \
	DECLARE_FUNCTION(execUnloadBank); \
	DECLARE_FUNCTION(execLoadBank); \
	DECLARE_FUNCTION(execFindEventByName); \
	DECLARE_FUNCTION(execFindAssetByName); \
	DECLARE_FUNCTION(execPlayEventAttached); \
	DECLARE_FUNCTION(execPlayEventAtLocation); \
	DECLARE_FUNCTION(execPlayEvent2D);


#define FID_ProjectCovenant_Plugins_FMODStudio_Source_FMODStudio_Classes_FMODBlueprintStatics_h_44_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesUFMODBlueprintStatics(); \
	friend struct Z_Construct_UClass_UFMODBlueprintStatics_Statics; \
public: \
	DECLARE_CLASS(UFMODBlueprintStatics, UBlueprintFunctionLibrary, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/FMODStudio"), NO_API) \
	DECLARE_SERIALIZER(UFMODBlueprintStatics)


#define FID_ProjectCovenant_Plugins_FMODStudio_Source_FMODStudio_Classes_FMODBlueprintStatics_h_44_INCLASS \
private: \
	static void StaticRegisterNativesUFMODBlueprintStatics(); \
	friend struct Z_Construct_UClass_UFMODBlueprintStatics_Statics; \
public: \
	DECLARE_CLASS(UFMODBlueprintStatics, UBlueprintFunctionLibrary, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/FMODStudio"), NO_API) \
	DECLARE_SERIALIZER(UFMODBlueprintStatics)


#define FID_ProjectCovenant_Plugins_FMODStudio_Source_FMODStudio_Classes_FMODBlueprintStatics_h_44_STANDARD_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API UFMODBlueprintStatics(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(UFMODBlueprintStatics) \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UFMODBlueprintStatics); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UFMODBlueprintStatics); \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API UFMODBlueprintStatics(UFMODBlueprintStatics&&); \
	NO_API UFMODBlueprintStatics(const UFMODBlueprintStatics&); \
public:


#define FID_ProjectCovenant_Plugins_FMODStudio_Source_FMODStudio_Classes_FMODBlueprintStatics_h_44_ENHANCED_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API UFMODBlueprintStatics(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()) : Super(ObjectInitializer) { }; \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API UFMODBlueprintStatics(UFMODBlueprintStatics&&); \
	NO_API UFMODBlueprintStatics(const UFMODBlueprintStatics&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UFMODBlueprintStatics); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UFMODBlueprintStatics); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(UFMODBlueprintStatics)


#define FID_ProjectCovenant_Plugins_FMODStudio_Source_FMODStudio_Classes_FMODBlueprintStatics_h_41_PROLOG
#define FID_ProjectCovenant_Plugins_FMODStudio_Source_FMODStudio_Classes_FMODBlueprintStatics_h_44_GENERATED_BODY_LEGACY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_ProjectCovenant_Plugins_FMODStudio_Source_FMODStudio_Classes_FMODBlueprintStatics_h_44_SPARSE_DATA \
	FID_ProjectCovenant_Plugins_FMODStudio_Source_FMODStudio_Classes_FMODBlueprintStatics_h_44_RPC_WRAPPERS \
	FID_ProjectCovenant_Plugins_FMODStudio_Source_FMODStudio_Classes_FMODBlueprintStatics_h_44_INCLASS \
	FID_ProjectCovenant_Plugins_FMODStudio_Source_FMODStudio_Classes_FMODBlueprintStatics_h_44_STANDARD_CONSTRUCTORS \
public: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#define FID_ProjectCovenant_Plugins_FMODStudio_Source_FMODStudio_Classes_FMODBlueprintStatics_h_44_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_ProjectCovenant_Plugins_FMODStudio_Source_FMODStudio_Classes_FMODBlueprintStatics_h_44_SPARSE_DATA \
	FID_ProjectCovenant_Plugins_FMODStudio_Source_FMODStudio_Classes_FMODBlueprintStatics_h_44_RPC_WRAPPERS_NO_PURE_DECLS \
	FID_ProjectCovenant_Plugins_FMODStudio_Source_FMODStudio_Classes_FMODBlueprintStatics_h_44_INCLASS_NO_PURE_DECLS \
	FID_ProjectCovenant_Plugins_FMODStudio_Source_FMODStudio_Classes_FMODBlueprintStatics_h_44_ENHANCED_CONSTRUCTORS \
static_assert(false, "Unknown access specifier for GENERATED_BODY() macro in class FMODBlueprintStatics."); \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> FMODSTUDIO_API UClass* StaticClass<class UFMODBlueprintStatics>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_ProjectCovenant_Plugins_FMODStudio_Source_FMODStudio_Classes_FMODBlueprintStatics_h


#define FOREACH_ENUM_EFMOD_STUDIO_STOP_MODE(op) \
	op(ALLOWFADEOUT) \
	op(IMMEDIATE) 
PRAGMA_ENABLE_DEPRECATION_WARNINGS
