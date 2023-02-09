// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "FMODStudio/Classes/FMODAudioComponent.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeFMODAudioComponent() {}
// Cross Module References
	FMODSTUDIO_API UEnum* Z_Construct_UEnum_FMODStudio_EFMODEventProperty();
	UPackage* Z_Construct_UPackage__Script_FMODStudio();
	FMODSTUDIO_API UScriptStruct* Z_Construct_UScriptStruct_FFMODAttenuationDetails();
	FMODSTUDIO_API UScriptStruct* Z_Construct_UScriptStruct_FFMODOcclusionDetails();
	ENGINE_API UEnum* Z_Construct_UEnum_Engine_ECollisionChannel();
	FMODSTUDIO_API UFunction* Z_Construct_UDelegateFunction_FMODStudio_OnEventStopped__DelegateSignature();
	FMODSTUDIO_API UFunction* Z_Construct_UDelegateFunction_FMODStudio_OnTimelineMarker__DelegateSignature();
	FMODSTUDIO_API UFunction* Z_Construct_UDelegateFunction_FMODStudio_OnTimelineBeat__DelegateSignature();
	FMODSTUDIO_API UClass* Z_Construct_UClass_UFMODAudioComponent_NoRegister();
	FMODSTUDIO_API UClass* Z_Construct_UClass_UFMODAudioComponent();
	ENGINE_API UClass* Z_Construct_UClass_USceneComponent();
	FMODSTUDIO_API UClass* Z_Construct_UClass_UFMODEvent_NoRegister();
// End Cross Module References
	static FEnumRegistrationInfo Z_Registration_Info_UEnum_EFMODEventProperty;
	static UEnum* EFMODEventProperty_StaticEnum()
	{
		if (!Z_Registration_Info_UEnum_EFMODEventProperty.OuterSingleton)
		{
			Z_Registration_Info_UEnum_EFMODEventProperty.OuterSingleton = GetStaticEnum(Z_Construct_UEnum_FMODStudio_EFMODEventProperty, Z_Construct_UPackage__Script_FMODStudio(), TEXT("EFMODEventProperty"));
		}
		return Z_Registration_Info_UEnum_EFMODEventProperty.OuterSingleton;
	}
	template<> FMODSTUDIO_API UEnum* StaticEnum<EFMODEventProperty::Type>()
	{
		return EFMODEventProperty_StaticEnum();
	}
	struct Z_Construct_UEnum_FMODStudio_EFMODEventProperty_Statics
	{
		static const UECodeGen_Private::FEnumeratorParam Enumerators[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Enum_MetaDataParams[];
#endif
		static const UECodeGen_Private::FEnumParams EnumParams;
	};
	const UECodeGen_Private::FEnumeratorParam Z_Construct_UEnum_FMODStudio_EFMODEventProperty_Statics::Enumerators[] = {
		{ "EFMODEventProperty::ChannelPriority", (int64)EFMODEventProperty::ChannelPriority },
		{ "EFMODEventProperty::ScheduleDelay", (int64)EFMODEventProperty::ScheduleDelay },
		{ "EFMODEventProperty::ScheduleLookahead", (int64)EFMODEventProperty::ScheduleLookahead },
		{ "EFMODEventProperty::MinimumDistance", (int64)EFMODEventProperty::MinimumDistance },
		{ "EFMODEventProperty::MaximumDistance", (int64)EFMODEventProperty::MaximumDistance },
		{ "EFMODEventProperty::Count", (int64)EFMODEventProperty::Count },
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UEnum_FMODStudio_EFMODEventProperty_Statics::Enum_MetaDataParams[] = {
		{ "ChannelPriority.Comment", "/* Priority to set on low-level channels created by this event instance (-1 to 256). */" },
		{ "ChannelPriority.Name", "EFMODEventProperty::ChannelPriority" },
		{ "ChannelPriority.ToolTip", "Priority to set on low-level channels created by this event instance (-1 to 256)." },
		{ "Comment", "// Event property\n" },
		{ "Count.Comment", "/** Number of options */" },
		{ "Count.Name", "EFMODEventProperty::Count" },
		{ "Count.ToolTip", "Number of options" },
		{ "MaximumDistance.Comment", "/** Override the event's 3D maximum distance, or -1 for default. */" },
		{ "MaximumDistance.Name", "EFMODEventProperty::MaximumDistance" },
		{ "MaximumDistance.ToolTip", "Override the event's 3D maximum distance, or -1 for default." },
		{ "MinimumDistance.Comment", "/** Override the event's 3D minimum distance, or -1 for default. */" },
		{ "MinimumDistance.Name", "EFMODEventProperty::MinimumDistance" },
		{ "MinimumDistance.ToolTip", "Override the event's 3D minimum distance, or -1 for default." },
		{ "ModuleRelativePath", "Classes/FMODAudioComponent.h" },
		{ "ScheduleDelay.Comment", "/** Schedule delay to synchronized playback for multiple tracks in DSP clocks, or -1 for default. */" },
		{ "ScheduleDelay.Name", "EFMODEventProperty::ScheduleDelay" },
		{ "ScheduleDelay.ToolTip", "Schedule delay to synchronized playback for multiple tracks in DSP clocks, or -1 for default." },
		{ "ScheduleLookahead.Comment", "/** Schedule look-ahead on the timeline in DSP clocks, or -1 for default. */" },
		{ "ScheduleLookahead.Name", "EFMODEventProperty::ScheduleLookahead" },
		{ "ScheduleLookahead.ToolTip", "Schedule look-ahead on the timeline in DSP clocks, or -1 for default." },
		{ "ToolTip", "Event property" },
	};
#endif
	const UECodeGen_Private::FEnumParams Z_Construct_UEnum_FMODStudio_EFMODEventProperty_Statics::EnumParams = {
		(UObject*(*)())Z_Construct_UPackage__Script_FMODStudio,
		nullptr,
		"EFMODEventProperty",
		"EFMODEventProperty::Type",
		Z_Construct_UEnum_FMODStudio_EFMODEventProperty_Statics::Enumerators,
		UE_ARRAY_COUNT(Z_Construct_UEnum_FMODStudio_EFMODEventProperty_Statics::Enumerators),
		RF_Public|RF_Transient|RF_MarkAsNative,
		EEnumFlags::None,
		(uint8)UEnum::ECppForm::Namespaced,
		METADATA_PARAMS(Z_Construct_UEnum_FMODStudio_EFMODEventProperty_Statics::Enum_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UEnum_FMODStudio_EFMODEventProperty_Statics::Enum_MetaDataParams))
	};
	UEnum* Z_Construct_UEnum_FMODStudio_EFMODEventProperty()
	{
		if (!Z_Registration_Info_UEnum_EFMODEventProperty.InnerSingleton)
		{
			UECodeGen_Private::ConstructUEnum(Z_Registration_Info_UEnum_EFMODEventProperty.InnerSingleton, Z_Construct_UEnum_FMODStudio_EFMODEventProperty_Statics::EnumParams);
		}
		return Z_Registration_Info_UEnum_EFMODEventProperty.InnerSingleton;
	}
	static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_FMODAttenuationDetails;
class UScriptStruct* FFMODAttenuationDetails::StaticStruct()
{
	if (!Z_Registration_Info_UScriptStruct_FMODAttenuationDetails.OuterSingleton)
	{
		Z_Registration_Info_UScriptStruct_FMODAttenuationDetails.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FFMODAttenuationDetails, Z_Construct_UPackage__Script_FMODStudio(), TEXT("FMODAttenuationDetails"));
	}
	return Z_Registration_Info_UScriptStruct_FMODAttenuationDetails.OuterSingleton;
}
template<> FMODSTUDIO_API UScriptStruct* StaticStruct<FFMODAttenuationDetails>()
{
	return FFMODAttenuationDetails::StaticStruct();
}
	struct Z_Construct_UScriptStruct_FFMODAttenuationDetails_Statics
	{
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[];
#endif
		static void* NewStructOps();
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_bOverrideAttenuation_MetaData[];
#endif
		static void NewProp_bOverrideAttenuation_SetBit(void* Obj);
		static const UECodeGen_Private::FBoolPropertyParams NewProp_bOverrideAttenuation;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_MinimumDistance_MetaData[];
#endif
		static const UECodeGen_Private::FFloatPropertyParams NewProp_MinimumDistance;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_MaximumDistance_MetaData[];
#endif
		static const UECodeGen_Private::FFloatPropertyParams NewProp_MaximumDistance;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const UECodeGen_Private::FStructParams ReturnStructParams;
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FFMODAttenuationDetails_Statics::Struct_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "ModuleRelativePath", "Classes/FMODAudioComponent.h" },
	};
#endif
	void* Z_Construct_UScriptStruct_FFMODAttenuationDetails_Statics::NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FFMODAttenuationDetails>();
	}
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FFMODAttenuationDetails_Statics::NewProp_bOverrideAttenuation_MetaData[] = {
		{ "Category", "FMOD|Attenuation" },
		{ "Comment", "/** Should we use Attenuation set in Studio or be able to modify in Editor. */" },
		{ "ModuleRelativePath", "Classes/FMODAudioComponent.h" },
		{ "ToolTip", "Should we use Attenuation set in Studio or be able to modify in Editor." },
	};
#endif
	void Z_Construct_UScriptStruct_FFMODAttenuationDetails_Statics::NewProp_bOverrideAttenuation_SetBit(void* Obj)
	{
		((FFMODAttenuationDetails*)Obj)->bOverrideAttenuation = 1;
	}
	const UECodeGen_Private::FBoolPropertyParams Z_Construct_UScriptStruct_FFMODAttenuationDetails_Statics::NewProp_bOverrideAttenuation = { "bOverrideAttenuation", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Bool , RF_Public|RF_Transient|RF_MarkAsNative, 1, sizeof(uint8), sizeof(FFMODAttenuationDetails), &Z_Construct_UScriptStruct_FFMODAttenuationDetails_Statics::NewProp_bOverrideAttenuation_SetBit, METADATA_PARAMS(Z_Construct_UScriptStruct_FFMODAttenuationDetails_Statics::NewProp_bOverrideAttenuation_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FFMODAttenuationDetails_Statics::NewProp_bOverrideAttenuation_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FFMODAttenuationDetails_Statics::NewProp_MinimumDistance_MetaData[] = {
		{ "Category", "FMOD|Attenuation" },
		{ "ClampMin", "0.0" },
		{ "Comment", "/** Override the event's 3D minimum distance. */" },
		{ "EditCondition", "bOverrideAttenuation" },
		{ "ModuleRelativePath", "Classes/FMODAudioComponent.h" },
		{ "ToolTip", "Override the event's 3D minimum distance." },
		{ "UIMin", "0.0" },
	};
#endif
	const UECodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FFMODAttenuationDetails_Statics::NewProp_MinimumDistance = { "MinimumDistance", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FFMODAttenuationDetails, MinimumDistance), METADATA_PARAMS(Z_Construct_UScriptStruct_FFMODAttenuationDetails_Statics::NewProp_MinimumDistance_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FFMODAttenuationDetails_Statics::NewProp_MinimumDistance_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FFMODAttenuationDetails_Statics::NewProp_MaximumDistance_MetaData[] = {
		{ "Category", "FMOD|Attenuation" },
		{ "ClampMin", "0.0" },
		{ "Comment", "/** Override the event's 3D maximum distance. */" },
		{ "EditCondition", "bOverrideAttenuation" },
		{ "ModuleRelativePath", "Classes/FMODAudioComponent.h" },
		{ "ToolTip", "Override the event's 3D maximum distance." },
		{ "UIMin", "0.0" },
	};
#endif
	const UECodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FFMODAttenuationDetails_Statics::NewProp_MaximumDistance = { "MaximumDistance", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FFMODAttenuationDetails, MaximumDistance), METADATA_PARAMS(Z_Construct_UScriptStruct_FFMODAttenuationDetails_Statics::NewProp_MaximumDistance_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FFMODAttenuationDetails_Statics::NewProp_MaximumDistance_MetaData)) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FFMODAttenuationDetails_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FFMODAttenuationDetails_Statics::NewProp_bOverrideAttenuation,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FFMODAttenuationDetails_Statics::NewProp_MinimumDistance,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FFMODAttenuationDetails_Statics::NewProp_MaximumDistance,
	};
	const UECodeGen_Private::FStructParams Z_Construct_UScriptStruct_FFMODAttenuationDetails_Statics::ReturnStructParams = {
		(UObject* (*)())Z_Construct_UPackage__Script_FMODStudio,
		nullptr,
		&NewStructOps,
		"FMODAttenuationDetails",
		sizeof(FFMODAttenuationDetails),
		alignof(FFMODAttenuationDetails),
		Z_Construct_UScriptStruct_FFMODAttenuationDetails_Statics::PropPointers,
		UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FFMODAttenuationDetails_Statics::PropPointers),
		RF_Public|RF_Transient|RF_MarkAsNative,
		EStructFlags(0x00000001),
		METADATA_PARAMS(Z_Construct_UScriptStruct_FFMODAttenuationDetails_Statics::Struct_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FFMODAttenuationDetails_Statics::Struct_MetaDataParams))
	};
	UScriptStruct* Z_Construct_UScriptStruct_FFMODAttenuationDetails()
	{
		if (!Z_Registration_Info_UScriptStruct_FMODAttenuationDetails.InnerSingleton)
		{
			UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_FMODAttenuationDetails.InnerSingleton, Z_Construct_UScriptStruct_FFMODAttenuationDetails_Statics::ReturnStructParams);
		}
		return Z_Registration_Info_UScriptStruct_FMODAttenuationDetails.InnerSingleton;
	}
	static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_FMODOcclusionDetails;
class UScriptStruct* FFMODOcclusionDetails::StaticStruct()
{
	if (!Z_Registration_Info_UScriptStruct_FMODOcclusionDetails.OuterSingleton)
	{
		Z_Registration_Info_UScriptStruct_FMODOcclusionDetails.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FFMODOcclusionDetails, Z_Construct_UPackage__Script_FMODStudio(), TEXT("FMODOcclusionDetails"));
	}
	return Z_Registration_Info_UScriptStruct_FMODOcclusionDetails.OuterSingleton;
}
template<> FMODSTUDIO_API UScriptStruct* StaticStruct<FFMODOcclusionDetails>()
{
	return FFMODOcclusionDetails::StaticStruct();
}
	struct Z_Construct_UScriptStruct_FFMODOcclusionDetails_Statics
	{
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[];
#endif
		static void* NewStructOps();
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_bEnableOcclusion_MetaData[];
#endif
		static void NewProp_bEnableOcclusion_SetBit(void* Obj);
		static const UECodeGen_Private::FBoolPropertyParams NewProp_bEnableOcclusion;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_OcclusionTraceChannel_MetaData[];
#endif
		static const UECodeGen_Private::FBytePropertyParams NewProp_OcclusionTraceChannel;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_bUseComplexCollisionForOcclusion_MetaData[];
#endif
		static void NewProp_bUseComplexCollisionForOcclusion_SetBit(void* Obj);
		static const UECodeGen_Private::FBoolPropertyParams NewProp_bUseComplexCollisionForOcclusion;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const UECodeGen_Private::FStructParams ReturnStructParams;
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FFMODOcclusionDetails_Statics::Struct_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "ModuleRelativePath", "Classes/FMODAudioComponent.h" },
	};
#endif
	void* Z_Construct_UScriptStruct_FFMODOcclusionDetails_Statics::NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FFMODOcclusionDetails>();
	}
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FFMODOcclusionDetails_Statics::NewProp_bEnableOcclusion_MetaData[] = {
		{ "Category", "FMOD|Occlusion" },
		{ "Comment", "/** Enable Occlusion Settings. */" },
		{ "ModuleRelativePath", "Classes/FMODAudioComponent.h" },
		{ "ToolTip", "Enable Occlusion Settings." },
	};
#endif
	void Z_Construct_UScriptStruct_FFMODOcclusionDetails_Statics::NewProp_bEnableOcclusion_SetBit(void* Obj)
	{
		((FFMODOcclusionDetails*)Obj)->bEnableOcclusion = 1;
	}
	const UECodeGen_Private::FBoolPropertyParams Z_Construct_UScriptStruct_FFMODOcclusionDetails_Statics::NewProp_bEnableOcclusion = { "bEnableOcclusion", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, sizeof(bool), sizeof(FFMODOcclusionDetails), &Z_Construct_UScriptStruct_FFMODOcclusionDetails_Statics::NewProp_bEnableOcclusion_SetBit, METADATA_PARAMS(Z_Construct_UScriptStruct_FFMODOcclusionDetails_Statics::NewProp_bEnableOcclusion_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FFMODOcclusionDetails_Statics::NewProp_bEnableOcclusion_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FFMODOcclusionDetails_Statics::NewProp_OcclusionTraceChannel_MetaData[] = {
		{ "Category", "FMOD|Occlusion" },
		{ "Comment", "/* Which trace channel to use for audio occlusion checks. */" },
		{ "EditCondition", "bEnableOcclusion" },
		{ "ModuleRelativePath", "Classes/FMODAudioComponent.h" },
		{ "ToolTip", "Which trace channel to use for audio occlusion checks." },
	};
#endif
	const UECodeGen_Private::FBytePropertyParams Z_Construct_UScriptStruct_FFMODOcclusionDetails_Statics::NewProp_OcclusionTraceChannel = { "OcclusionTraceChannel", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FFMODOcclusionDetails, OcclusionTraceChannel), Z_Construct_UEnum_Engine_ECollisionChannel, METADATA_PARAMS(Z_Construct_UScriptStruct_FFMODOcclusionDetails_Statics::NewProp_OcclusionTraceChannel_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FFMODOcclusionDetails_Statics::NewProp_OcclusionTraceChannel_MetaData)) }; // 727872708
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FFMODOcclusionDetails_Statics::NewProp_bUseComplexCollisionForOcclusion_MetaData[] = {
		{ "Category", "FMOD|Occlusion" },
		{ "Comment", "/** Whether or not to enable complex geometry occlusion checks. */" },
		{ "EditCondition", "bEnableOcclusion" },
		{ "ModuleRelativePath", "Classes/FMODAudioComponent.h" },
		{ "ToolTip", "Whether or not to enable complex geometry occlusion checks." },
	};
#endif
	void Z_Construct_UScriptStruct_FFMODOcclusionDetails_Statics::NewProp_bUseComplexCollisionForOcclusion_SetBit(void* Obj)
	{
		((FFMODOcclusionDetails*)Obj)->bUseComplexCollisionForOcclusion = 1;
	}
	const UECodeGen_Private::FBoolPropertyParams Z_Construct_UScriptStruct_FFMODOcclusionDetails_Statics::NewProp_bUseComplexCollisionForOcclusion = { "bUseComplexCollisionForOcclusion", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, sizeof(bool), sizeof(FFMODOcclusionDetails), &Z_Construct_UScriptStruct_FFMODOcclusionDetails_Statics::NewProp_bUseComplexCollisionForOcclusion_SetBit, METADATA_PARAMS(Z_Construct_UScriptStruct_FFMODOcclusionDetails_Statics::NewProp_bUseComplexCollisionForOcclusion_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FFMODOcclusionDetails_Statics::NewProp_bUseComplexCollisionForOcclusion_MetaData)) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FFMODOcclusionDetails_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FFMODOcclusionDetails_Statics::NewProp_bEnableOcclusion,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FFMODOcclusionDetails_Statics::NewProp_OcclusionTraceChannel,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FFMODOcclusionDetails_Statics::NewProp_bUseComplexCollisionForOcclusion,
	};
	const UECodeGen_Private::FStructParams Z_Construct_UScriptStruct_FFMODOcclusionDetails_Statics::ReturnStructParams = {
		(UObject* (*)())Z_Construct_UPackage__Script_FMODStudio,
		nullptr,
		&NewStructOps,
		"FMODOcclusionDetails",
		sizeof(FFMODOcclusionDetails),
		alignof(FFMODOcclusionDetails),
		Z_Construct_UScriptStruct_FFMODOcclusionDetails_Statics::PropPointers,
		UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FFMODOcclusionDetails_Statics::PropPointers),
		RF_Public|RF_Transient|RF_MarkAsNative,
		EStructFlags(0x00000001),
		METADATA_PARAMS(Z_Construct_UScriptStruct_FFMODOcclusionDetails_Statics::Struct_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FFMODOcclusionDetails_Statics::Struct_MetaDataParams))
	};
	UScriptStruct* Z_Construct_UScriptStruct_FFMODOcclusionDetails()
	{
		if (!Z_Registration_Info_UScriptStruct_FMODOcclusionDetails.InnerSingleton)
		{
			UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_FMODOcclusionDetails.InnerSingleton, Z_Construct_UScriptStruct_FFMODOcclusionDetails_Statics::ReturnStructParams);
		}
		return Z_Registration_Info_UScriptStruct_FMODOcclusionDetails.InnerSingleton;
	}
	struct Z_Construct_UDelegateFunction_FMODStudio_OnEventStopped__DelegateSignature_Statics
	{
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UECodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UDelegateFunction_FMODStudio_OnEventStopped__DelegateSignature_Statics::Function_MetaDataParams[] = {
		{ "Comment", "/** called when an event stops, either because it played to completion or because a Stop() call turned it off early */" },
		{ "ModuleRelativePath", "Classes/FMODAudioComponent.h" },
		{ "ToolTip", "called when an event stops, either because it played to completion or because a Stop() call turned it off early" },
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UDelegateFunction_FMODStudio_OnEventStopped__DelegateSignature_Statics::FuncParams = { (UObject*(*)())Z_Construct_UPackage__Script_FMODStudio, nullptr, "OnEventStopped__DelegateSignature", nullptr, nullptr, 0, nullptr, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00130000, 0, 0, METADATA_PARAMS(Z_Construct_UDelegateFunction_FMODStudio_OnEventStopped__DelegateSignature_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UDelegateFunction_FMODStudio_OnEventStopped__DelegateSignature_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UDelegateFunction_FMODStudio_OnEventStopped__DelegateSignature()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UDelegateFunction_FMODStudio_OnEventStopped__DelegateSignature_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UDelegateFunction_FMODStudio_OnTimelineMarker__DelegateSignature_Statics
	{
		struct _Script_FMODStudio_eventOnTimelineMarker_Parms
		{
			FString Name;
			int32 Position;
		};
		static const UECodeGen_Private::FStrPropertyParams NewProp_Name;
		static const UECodeGen_Private::FIntPropertyParams NewProp_Position;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UECodeGen_Private::FFunctionParams FuncParams;
	};
	const UECodeGen_Private::FStrPropertyParams Z_Construct_UDelegateFunction_FMODStudio_OnTimelineMarker__DelegateSignature_Statics::NewProp_Name = { "Name", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(_Script_FMODStudio_eventOnTimelineMarker_Parms, Name), METADATA_PARAMS(nullptr, 0) };
	const UECodeGen_Private::FIntPropertyParams Z_Construct_UDelegateFunction_FMODStudio_OnTimelineMarker__DelegateSignature_Statics::NewProp_Position = { "Position", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(_Script_FMODStudio_eventOnTimelineMarker_Parms, Position), METADATA_PARAMS(nullptr, 0) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UDelegateFunction_FMODStudio_OnTimelineMarker__DelegateSignature_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UDelegateFunction_FMODStudio_OnTimelineMarker__DelegateSignature_Statics::NewProp_Name,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UDelegateFunction_FMODStudio_OnTimelineMarker__DelegateSignature_Statics::NewProp_Position,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UDelegateFunction_FMODStudio_OnTimelineMarker__DelegateSignature_Statics::Function_MetaDataParams[] = {
		{ "Comment", "/** called when we reach a named marker on the timeline */" },
		{ "ModuleRelativePath", "Classes/FMODAudioComponent.h" },
		{ "ToolTip", "called when we reach a named marker on the timeline" },
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UDelegateFunction_FMODStudio_OnTimelineMarker__DelegateSignature_Statics::FuncParams = { (UObject*(*)())Z_Construct_UPackage__Script_FMODStudio, nullptr, "OnTimelineMarker__DelegateSignature", nullptr, nullptr, sizeof(Z_Construct_UDelegateFunction_FMODStudio_OnTimelineMarker__DelegateSignature_Statics::_Script_FMODStudio_eventOnTimelineMarker_Parms), Z_Construct_UDelegateFunction_FMODStudio_OnTimelineMarker__DelegateSignature_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UDelegateFunction_FMODStudio_OnTimelineMarker__DelegateSignature_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00130000, 0, 0, METADATA_PARAMS(Z_Construct_UDelegateFunction_FMODStudio_OnTimelineMarker__DelegateSignature_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UDelegateFunction_FMODStudio_OnTimelineMarker__DelegateSignature_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UDelegateFunction_FMODStudio_OnTimelineMarker__DelegateSignature()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UDelegateFunction_FMODStudio_OnTimelineMarker__DelegateSignature_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UDelegateFunction_FMODStudio_OnTimelineBeat__DelegateSignature_Statics
	{
		struct _Script_FMODStudio_eventOnTimelineBeat_Parms
		{
			int32 Bar;
			int32 Beat;
			int32 Position;
			float Tempo;
			int32 TimeSignatureUpper;
			int32 TimeSignatureLower;
		};
		static const UECodeGen_Private::FIntPropertyParams NewProp_Bar;
		static const UECodeGen_Private::FIntPropertyParams NewProp_Beat;
		static const UECodeGen_Private::FIntPropertyParams NewProp_Position;
		static const UECodeGen_Private::FFloatPropertyParams NewProp_Tempo;
		static const UECodeGen_Private::FIntPropertyParams NewProp_TimeSignatureUpper;
		static const UECodeGen_Private::FIntPropertyParams NewProp_TimeSignatureLower;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UECodeGen_Private::FFunctionParams FuncParams;
	};
	const UECodeGen_Private::FIntPropertyParams Z_Construct_UDelegateFunction_FMODStudio_OnTimelineBeat__DelegateSignature_Statics::NewProp_Bar = { "Bar", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(_Script_FMODStudio_eventOnTimelineBeat_Parms, Bar), METADATA_PARAMS(nullptr, 0) };
	const UECodeGen_Private::FIntPropertyParams Z_Construct_UDelegateFunction_FMODStudio_OnTimelineBeat__DelegateSignature_Statics::NewProp_Beat = { "Beat", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(_Script_FMODStudio_eventOnTimelineBeat_Parms, Beat), METADATA_PARAMS(nullptr, 0) };
	const UECodeGen_Private::FIntPropertyParams Z_Construct_UDelegateFunction_FMODStudio_OnTimelineBeat__DelegateSignature_Statics::NewProp_Position = { "Position", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(_Script_FMODStudio_eventOnTimelineBeat_Parms, Position), METADATA_PARAMS(nullptr, 0) };
	const UECodeGen_Private::FFloatPropertyParams Z_Construct_UDelegateFunction_FMODStudio_OnTimelineBeat__DelegateSignature_Statics::NewProp_Tempo = { "Tempo", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(_Script_FMODStudio_eventOnTimelineBeat_Parms, Tempo), METADATA_PARAMS(nullptr, 0) };
	const UECodeGen_Private::FIntPropertyParams Z_Construct_UDelegateFunction_FMODStudio_OnTimelineBeat__DelegateSignature_Statics::NewProp_TimeSignatureUpper = { "TimeSignatureUpper", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(_Script_FMODStudio_eventOnTimelineBeat_Parms, TimeSignatureUpper), METADATA_PARAMS(nullptr, 0) };
	const UECodeGen_Private::FIntPropertyParams Z_Construct_UDelegateFunction_FMODStudio_OnTimelineBeat__DelegateSignature_Statics::NewProp_TimeSignatureLower = { "TimeSignatureLower", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(_Script_FMODStudio_eventOnTimelineBeat_Parms, TimeSignatureLower), METADATA_PARAMS(nullptr, 0) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UDelegateFunction_FMODStudio_OnTimelineBeat__DelegateSignature_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UDelegateFunction_FMODStudio_OnTimelineBeat__DelegateSignature_Statics::NewProp_Bar,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UDelegateFunction_FMODStudio_OnTimelineBeat__DelegateSignature_Statics::NewProp_Beat,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UDelegateFunction_FMODStudio_OnTimelineBeat__DelegateSignature_Statics::NewProp_Position,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UDelegateFunction_FMODStudio_OnTimelineBeat__DelegateSignature_Statics::NewProp_Tempo,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UDelegateFunction_FMODStudio_OnTimelineBeat__DelegateSignature_Statics::NewProp_TimeSignatureUpper,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UDelegateFunction_FMODStudio_OnTimelineBeat__DelegateSignature_Statics::NewProp_TimeSignatureLower,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UDelegateFunction_FMODStudio_OnTimelineBeat__DelegateSignature_Statics::Function_MetaDataParams[] = {
		{ "Comment", "/** called when we reach a beat on the timeline */" },
		{ "ModuleRelativePath", "Classes/FMODAudioComponent.h" },
		{ "ToolTip", "called when we reach a beat on the timeline" },
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UDelegateFunction_FMODStudio_OnTimelineBeat__DelegateSignature_Statics::FuncParams = { (UObject*(*)())Z_Construct_UPackage__Script_FMODStudio, nullptr, "OnTimelineBeat__DelegateSignature", nullptr, nullptr, sizeof(Z_Construct_UDelegateFunction_FMODStudio_OnTimelineBeat__DelegateSignature_Statics::_Script_FMODStudio_eventOnTimelineBeat_Parms), Z_Construct_UDelegateFunction_FMODStudio_OnTimelineBeat__DelegateSignature_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UDelegateFunction_FMODStudio_OnTimelineBeat__DelegateSignature_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00130000, 0, 0, METADATA_PARAMS(Z_Construct_UDelegateFunction_FMODStudio_OnTimelineBeat__DelegateSignature_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UDelegateFunction_FMODStudio_OnTimelineBeat__DelegateSignature_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UDelegateFunction_FMODStudio_OnTimelineBeat__DelegateSignature()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UDelegateFunction_FMODStudio_OnTimelineBeat__DelegateSignature_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	DEFINE_FUNCTION(UFMODAudioComponent::execSetProgrammerSoundName)
	{
		P_GET_PROPERTY(FStrProperty,Z_Param_Value);
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->SetProgrammerSoundName(Z_Param_Value);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UFMODAudioComponent::execGetTimelinePosition)
	{
		P_FINISH;
		P_NATIVE_BEGIN;
		*(int32*)Z_Param__Result=P_THIS->GetTimelinePosition();
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UFMODAudioComponent::execSetTimelinePosition)
	{
		P_GET_PROPERTY(FIntProperty,Z_Param_Time);
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->SetTimelinePosition(Z_Param_Time);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UFMODAudioComponent::execGetLength)
	{
		P_FINISH;
		P_NATIVE_BEGIN;
		*(int32*)Z_Param__Result=P_THIS->GetLength();
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UFMODAudioComponent::execGetProperty)
	{
		P_GET_PROPERTY(FByteProperty,Z_Param_Property);
		P_FINISH;
		P_NATIVE_BEGIN;
		*(float*)Z_Param__Result=P_THIS->GetProperty(EFMODEventProperty::Type(Z_Param_Property));
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UFMODAudioComponent::execSetProperty)
	{
		P_GET_PROPERTY(FByteProperty,Z_Param_Property);
		P_GET_PROPERTY(FFloatProperty,Z_Param_Value);
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->SetProperty(EFMODEventProperty::Type(Z_Param_Property),Z_Param_Value);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UFMODAudioComponent::execGetParameterValue)
	{
		P_GET_PROPERTY(FNameProperty,Z_Param_Name);
		P_GET_PROPERTY_REF(FFloatProperty,Z_Param_Out_UserValue);
		P_GET_PROPERTY_REF(FFloatProperty,Z_Param_Out_FinalValue);
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->GetParameterValue(Z_Param_Name,Z_Param_Out_UserValue,Z_Param_Out_FinalValue);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UFMODAudioComponent::execGetParameter)
	{
		P_GET_PROPERTY(FNameProperty,Z_Param_Name);
		P_FINISH;
		P_NATIVE_BEGIN;
		*(float*)Z_Param__Result=P_THIS->GetParameter(Z_Param_Name);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UFMODAudioComponent::execSetParameter)
	{
		P_GET_PROPERTY(FNameProperty,Z_Param_Name);
		P_GET_PROPERTY(FFloatProperty,Z_Param_Value);
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->SetParameter(Z_Param_Name,Z_Param_Value);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UFMODAudioComponent::execSetPaused)
	{
		P_GET_UBOOL(Z_Param_paused);
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->SetPaused(Z_Param_paused);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UFMODAudioComponent::execSetPitch)
	{
		P_GET_PROPERTY(FFloatProperty,Z_Param_pitch);
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->SetPitch(Z_Param_pitch);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UFMODAudioComponent::execSetVolume)
	{
		P_GET_PROPERTY(FFloatProperty,Z_Param_volume);
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->SetVolume(Z_Param_volume);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UFMODAudioComponent::execIsPlaying)
	{
		P_FINISH;
		P_NATIVE_BEGIN;
		*(bool*)Z_Param__Result=P_THIS->IsPlaying();
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UFMODAudioComponent::execKeyOff)
	{
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->KeyOff();
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UFMODAudioComponent::execRelease)
	{
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->Release();
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UFMODAudioComponent::execStop)
	{
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->Stop();
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UFMODAudioComponent::execPlay)
	{
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->Play();
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UFMODAudioComponent::execSetEvent)
	{
		P_GET_OBJECT(UFMODEvent,Z_Param_NewEvent);
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->SetEvent(Z_Param_NewEvent);
		P_NATIVE_END;
	}
	void UFMODAudioComponent::StaticRegisterNativesUFMODAudioComponent()
	{
		UClass* Class = UFMODAudioComponent::StaticClass();
		static const FNameNativePtrPair Funcs[] = {
			{ "GetLength", &UFMODAudioComponent::execGetLength },
			{ "GetParameter", &UFMODAudioComponent::execGetParameter },
			{ "GetParameterValue", &UFMODAudioComponent::execGetParameterValue },
			{ "GetProperty", &UFMODAudioComponent::execGetProperty },
			{ "GetTimelinePosition", &UFMODAudioComponent::execGetTimelinePosition },
			{ "IsPlaying", &UFMODAudioComponent::execIsPlaying },
			{ "KeyOff", &UFMODAudioComponent::execKeyOff },
			{ "Play", &UFMODAudioComponent::execPlay },
			{ "Release", &UFMODAudioComponent::execRelease },
			{ "SetEvent", &UFMODAudioComponent::execSetEvent },
			{ "SetParameter", &UFMODAudioComponent::execSetParameter },
			{ "SetPaused", &UFMODAudioComponent::execSetPaused },
			{ "SetPitch", &UFMODAudioComponent::execSetPitch },
			{ "SetProgrammerSoundName", &UFMODAudioComponent::execSetProgrammerSoundName },
			{ "SetProperty", &UFMODAudioComponent::execSetProperty },
			{ "SetTimelinePosition", &UFMODAudioComponent::execSetTimelinePosition },
			{ "SetVolume", &UFMODAudioComponent::execSetVolume },
			{ "Stop", &UFMODAudioComponent::execStop },
		};
		FNativeFunctionRegistrar::RegisterFunctions(Class, Funcs, UE_ARRAY_COUNT(Funcs));
	}
	struct Z_Construct_UFunction_UFMODAudioComponent_GetLength_Statics
	{
		struct FMODAudioComponent_eventGetLength_Parms
		{
			int32 ReturnValue;
		};
		static const UECodeGen_Private::FIntPropertyParams NewProp_ReturnValue;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UECodeGen_Private::FFunctionParams FuncParams;
	};
	const UECodeGen_Private::FIntPropertyParams Z_Construct_UFunction_UFMODAudioComponent_GetLength_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FMODAudioComponent_eventGetLength_Parms, ReturnValue), METADATA_PARAMS(nullptr, 0) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UFMODAudioComponent_GetLength_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UFMODAudioComponent_GetLength_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UFMODAudioComponent_GetLength_Statics::Function_MetaDataParams[] = {
		{ "Category", "Audio|FMOD|Components" },
		{ "Comment", "/** Get the event length in milliseconds. */" },
		{ "ModuleRelativePath", "Classes/FMODAudioComponent.h" },
		{ "ToolTip", "Get the event length in milliseconds." },
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UFMODAudioComponent_GetLength_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UFMODAudioComponent, nullptr, "GetLength", nullptr, nullptr, sizeof(Z_Construct_UFunction_UFMODAudioComponent_GetLength_Statics::FMODAudioComponent_eventGetLength_Parms), Z_Construct_UFunction_UFMODAudioComponent_GetLength_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UFMODAudioComponent_GetLength_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UFMODAudioComponent_GetLength_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UFMODAudioComponent_GetLength_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UFMODAudioComponent_GetLength()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UFMODAudioComponent_GetLength_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UFMODAudioComponent_GetParameter_Statics
	{
		struct FMODAudioComponent_eventGetParameter_Parms
		{
			FName Name;
			float ReturnValue;
		};
		static const UECodeGen_Private::FNamePropertyParams NewProp_Name;
		static const UECodeGen_Private::FFloatPropertyParams NewProp_ReturnValue;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UECodeGen_Private::FFunctionParams FuncParams;
	};
	const UECodeGen_Private::FNamePropertyParams Z_Construct_UFunction_UFMODAudioComponent_GetParameter_Statics::NewProp_Name = { "Name", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Name, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FMODAudioComponent_eventGetParameter_Parms, Name), METADATA_PARAMS(nullptr, 0) };
	const UECodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_UFMODAudioComponent_GetParameter_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FMODAudioComponent_eventGetParameter_Parms, ReturnValue), METADATA_PARAMS(nullptr, 0) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UFMODAudioComponent_GetParameter_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UFMODAudioComponent_GetParameter_Statics::NewProp_Name,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UFMODAudioComponent_GetParameter_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UFMODAudioComponent_GetParameter_Statics::Function_MetaDataParams[] = {
		{ "Category", "Audio|FMOD|Components" },
		{ "Comment", "/** Will be deprecated in FMOD 2.01, use `GetParameterValue(FName, float, float)` instead.\n     * Get parameter value from the Event.\n    */" },
		{ "ModuleRelativePath", "Classes/FMODAudioComponent.h" },
		{ "ToolTip", "Will be deprecated in FMOD 2.01, use `GetParameterValue(FName, float, float)` instead.\nGet parameter value from the Event." },
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UFMODAudioComponent_GetParameter_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UFMODAudioComponent, nullptr, "GetParameter", nullptr, nullptr, sizeof(Z_Construct_UFunction_UFMODAudioComponent_GetParameter_Statics::FMODAudioComponent_eventGetParameter_Parms), Z_Construct_UFunction_UFMODAudioComponent_GetParameter_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UFMODAudioComponent_GetParameter_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UFMODAudioComponent_GetParameter_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UFMODAudioComponent_GetParameter_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UFMODAudioComponent_GetParameter()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UFMODAudioComponent_GetParameter_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UFMODAudioComponent_GetParameterValue_Statics
	{
		struct FMODAudioComponent_eventGetParameterValue_Parms
		{
			FName Name;
			float UserValue;
			float FinalValue;
		};
		static const UECodeGen_Private::FNamePropertyParams NewProp_Name;
		static const UECodeGen_Private::FFloatPropertyParams NewProp_UserValue;
		static const UECodeGen_Private::FFloatPropertyParams NewProp_FinalValue;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UECodeGen_Private::FFunctionParams FuncParams;
	};
	const UECodeGen_Private::FNamePropertyParams Z_Construct_UFunction_UFMODAudioComponent_GetParameterValue_Statics::NewProp_Name = { "Name", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Name, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FMODAudioComponent_eventGetParameterValue_Parms, Name), METADATA_PARAMS(nullptr, 0) };
	const UECodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_UFMODAudioComponent_GetParameterValue_Statics::NewProp_UserValue = { "UserValue", nullptr, (EPropertyFlags)0x0010000000000180, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FMODAudioComponent_eventGetParameterValue_Parms, UserValue), METADATA_PARAMS(nullptr, 0) };
	const UECodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_UFMODAudioComponent_GetParameterValue_Statics::NewProp_FinalValue = { "FinalValue", nullptr, (EPropertyFlags)0x0010000000000180, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FMODAudioComponent_eventGetParameterValue_Parms, FinalValue), METADATA_PARAMS(nullptr, 0) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UFMODAudioComponent_GetParameterValue_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UFMODAudioComponent_GetParameterValue_Statics::NewProp_Name,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UFMODAudioComponent_GetParameterValue_Statics::NewProp_UserValue,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UFMODAudioComponent_GetParameterValue_Statics::NewProp_FinalValue,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UFMODAudioComponent_GetParameterValue_Statics::Function_MetaDataParams[] = {
		{ "Category", "Audio|FMOD|Components" },
		{ "Comment", "/** Get parameter value from the Event.\n     * @param Name - Name of parameter\n     * @param UserValue - Parameter value as set from the public API.\n     * @param FinalValue - Final combined parameter value.\n    */" },
		{ "ModuleRelativePath", "Classes/FMODAudioComponent.h" },
		{ "ToolTip", "Get parameter value from the Event.\n@param Name - Name of parameter\n@param UserValue - Parameter value as set from the public API.\n@param FinalValue - Final combined parameter value." },
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UFMODAudioComponent_GetParameterValue_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UFMODAudioComponent, nullptr, "GetParameterValue", nullptr, nullptr, sizeof(Z_Construct_UFunction_UFMODAudioComponent_GetParameterValue_Statics::FMODAudioComponent_eventGetParameterValue_Parms), Z_Construct_UFunction_UFMODAudioComponent_GetParameterValue_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UFMODAudioComponent_GetParameterValue_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04420401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UFMODAudioComponent_GetParameterValue_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UFMODAudioComponent_GetParameterValue_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UFMODAudioComponent_GetParameterValue()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UFMODAudioComponent_GetParameterValue_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UFMODAudioComponent_GetProperty_Statics
	{
		struct FMODAudioComponent_eventGetProperty_Parms
		{
			TEnumAsByte<EFMODEventProperty::Type> Property;
			float ReturnValue;
		};
		static const UECodeGen_Private::FBytePropertyParams NewProp_Property;
		static const UECodeGen_Private::FFloatPropertyParams NewProp_ReturnValue;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UECodeGen_Private::FFunctionParams FuncParams;
	};
	const UECodeGen_Private::FBytePropertyParams Z_Construct_UFunction_UFMODAudioComponent_GetProperty_Statics::NewProp_Property = { "Property", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FMODAudioComponent_eventGetProperty_Parms, Property), Z_Construct_UEnum_FMODStudio_EFMODEventProperty, METADATA_PARAMS(nullptr, 0) }; // 2209603180
	const UECodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_UFMODAudioComponent_GetProperty_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FMODAudioComponent_eventGetProperty_Parms, ReturnValue), METADATA_PARAMS(nullptr, 0) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UFMODAudioComponent_GetProperty_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UFMODAudioComponent_GetProperty_Statics::NewProp_Property,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UFMODAudioComponent_GetProperty_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UFMODAudioComponent_GetProperty_Statics::Function_MetaDataParams[] = {
		{ "Category", "Audio|FMOD|Components" },
		{ "Comment", "/** Get a property of the Event. */" },
		{ "ModuleRelativePath", "Classes/FMODAudioComponent.h" },
		{ "ToolTip", "Get a property of the Event." },
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UFMODAudioComponent_GetProperty_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UFMODAudioComponent, nullptr, "GetProperty", nullptr, nullptr, sizeof(Z_Construct_UFunction_UFMODAudioComponent_GetProperty_Statics::FMODAudioComponent_eventGetProperty_Parms), Z_Construct_UFunction_UFMODAudioComponent_GetProperty_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UFMODAudioComponent_GetProperty_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UFMODAudioComponent_GetProperty_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UFMODAudioComponent_GetProperty_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UFMODAudioComponent_GetProperty()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UFMODAudioComponent_GetProperty_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UFMODAudioComponent_GetTimelinePosition_Statics
	{
		struct FMODAudioComponent_eventGetTimelinePosition_Parms
		{
			int32 ReturnValue;
		};
		static const UECodeGen_Private::FIntPropertyParams NewProp_ReturnValue;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UECodeGen_Private::FFunctionParams FuncParams;
	};
	const UECodeGen_Private::FIntPropertyParams Z_Construct_UFunction_UFMODAudioComponent_GetTimelinePosition_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FMODAudioComponent_eventGetTimelinePosition_Parms, ReturnValue), METADATA_PARAMS(nullptr, 0) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UFMODAudioComponent_GetTimelinePosition_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UFMODAudioComponent_GetTimelinePosition_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UFMODAudioComponent_GetTimelinePosition_Statics::Function_MetaDataParams[] = {
		{ "Category", "Audio|FMOD|Components" },
		{ "Comment", "/** Get the timeline position in milliseconds. */" },
		{ "ModuleRelativePath", "Classes/FMODAudioComponent.h" },
		{ "ToolTip", "Get the timeline position in milliseconds." },
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UFMODAudioComponent_GetTimelinePosition_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UFMODAudioComponent, nullptr, "GetTimelinePosition", nullptr, nullptr, sizeof(Z_Construct_UFunction_UFMODAudioComponent_GetTimelinePosition_Statics::FMODAudioComponent_eventGetTimelinePosition_Parms), Z_Construct_UFunction_UFMODAudioComponent_GetTimelinePosition_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UFMODAudioComponent_GetTimelinePosition_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UFMODAudioComponent_GetTimelinePosition_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UFMODAudioComponent_GetTimelinePosition_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UFMODAudioComponent_GetTimelinePosition()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UFMODAudioComponent_GetTimelinePosition_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UFMODAudioComponent_IsPlaying_Statics
	{
		struct FMODAudioComponent_eventIsPlaying_Parms
		{
			bool ReturnValue;
		};
		static void NewProp_ReturnValue_SetBit(void* Obj);
		static const UECodeGen_Private::FBoolPropertyParams NewProp_ReturnValue;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UECodeGen_Private::FFunctionParams FuncParams;
	};
	void Z_Construct_UFunction_UFMODAudioComponent_IsPlaying_Statics::NewProp_ReturnValue_SetBit(void* Obj)
	{
		((FMODAudioComponent_eventIsPlaying_Parms*)Obj)->ReturnValue = 1;
	}
	const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UFMODAudioComponent_IsPlaying_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, sizeof(bool), sizeof(FMODAudioComponent_eventIsPlaying_Parms), &Z_Construct_UFunction_UFMODAudioComponent_IsPlaying_Statics::NewProp_ReturnValue_SetBit, METADATA_PARAMS(nullptr, 0) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UFMODAudioComponent_IsPlaying_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UFMODAudioComponent_IsPlaying_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UFMODAudioComponent_IsPlaying_Statics::Function_MetaDataParams[] = {
		{ "Category", "Audio|FMOD|Components" },
		{ "Comment", "/** Return true if this component is currently playing an event. */" },
		{ "ModuleRelativePath", "Classes/FMODAudioComponent.h" },
		{ "ToolTip", "Return true if this component is currently playing an event." },
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UFMODAudioComponent_IsPlaying_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UFMODAudioComponent, nullptr, "IsPlaying", nullptr, nullptr, sizeof(Z_Construct_UFunction_UFMODAudioComponent_IsPlaying_Statics::FMODAudioComponent_eventIsPlaying_Parms), Z_Construct_UFunction_UFMODAudioComponent_IsPlaying_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UFMODAudioComponent_IsPlaying_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UFMODAudioComponent_IsPlaying_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UFMODAudioComponent_IsPlaying_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UFMODAudioComponent_IsPlaying()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UFMODAudioComponent_IsPlaying_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UFMODAudioComponent_KeyOff_Statics
	{
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UECodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UFMODAudioComponent_KeyOff_Statics::Function_MetaDataParams[] = {
		{ "Category", "Audio|FMOD|Components" },
		{ "Comment", "/**  Allow an event to continue past a sustain point. */" },
		{ "ModuleRelativePath", "Classes/FMODAudioComponent.h" },
		{ "ToolTip", "Allow an event to continue past a sustain point." },
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UFMODAudioComponent_KeyOff_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UFMODAudioComponent, nullptr, "KeyOff", nullptr, nullptr, 0, nullptr, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UFMODAudioComponent_KeyOff_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UFMODAudioComponent_KeyOff_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UFMODAudioComponent_KeyOff()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UFMODAudioComponent_KeyOff_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UFMODAudioComponent_Play_Statics
	{
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UECodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UFMODAudioComponent_Play_Statics::Function_MetaDataParams[] = {
		{ "Category", "Audio|FMOD|Components" },
		{ "Comment", "/** Start a sound playing on an audio component. */" },
		{ "ModuleRelativePath", "Classes/FMODAudioComponent.h" },
		{ "ToolTip", "Start a sound playing on an audio component." },
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UFMODAudioComponent_Play_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UFMODAudioComponent, nullptr, "Play", nullptr, nullptr, 0, nullptr, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UFMODAudioComponent_Play_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UFMODAudioComponent_Play_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UFMODAudioComponent_Play()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UFMODAudioComponent_Play_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UFMODAudioComponent_Release_Statics
	{
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UECodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UFMODAudioComponent_Release_Statics::Function_MetaDataParams[] = {
		{ "Category", "Audio|FMOD|Components" },
		{ "ModuleRelativePath", "Classes/FMODAudioComponent.h" },
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UFMODAudioComponent_Release_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UFMODAudioComponent, nullptr, "Release", nullptr, nullptr, 0, nullptr, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UFMODAudioComponent_Release_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UFMODAudioComponent_Release_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UFMODAudioComponent_Release()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UFMODAudioComponent_Release_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UFMODAudioComponent_SetEvent_Statics
	{
		struct FMODAudioComponent_eventSetEvent_Parms
		{
			UFMODEvent* NewEvent;
		};
		static const UECodeGen_Private::FObjectPropertyParams NewProp_NewEvent;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UECodeGen_Private::FFunctionParams FuncParams;
	};
	const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UFMODAudioComponent_SetEvent_Statics::NewProp_NewEvent = { "NewEvent", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FMODAudioComponent_eventSetEvent_Parms, NewEvent), Z_Construct_UClass_UFMODEvent_NoRegister, METADATA_PARAMS(nullptr, 0) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UFMODAudioComponent_SetEvent_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UFMODAudioComponent_SetEvent_Statics::NewProp_NewEvent,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UFMODAudioComponent_SetEvent_Statics::Function_MetaDataParams[] = {
		{ "Category", "Audio|FMOD|Components" },
		{ "Comment", "/** New Event to be used by the FMODAudioComponent. */" },
		{ "ModuleRelativePath", "Classes/FMODAudioComponent.h" },
		{ "ToolTip", "New Event to be used by the FMODAudioComponent." },
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UFMODAudioComponent_SetEvent_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UFMODAudioComponent, nullptr, "SetEvent", nullptr, nullptr, sizeof(Z_Construct_UFunction_UFMODAudioComponent_SetEvent_Statics::FMODAudioComponent_eventSetEvent_Parms), Z_Construct_UFunction_UFMODAudioComponent_SetEvent_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UFMODAudioComponent_SetEvent_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UFMODAudioComponent_SetEvent_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UFMODAudioComponent_SetEvent_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UFMODAudioComponent_SetEvent()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UFMODAudioComponent_SetEvent_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UFMODAudioComponent_SetParameter_Statics
	{
		struct FMODAudioComponent_eventSetParameter_Parms
		{
			FName Name;
			float Value;
		};
		static const UECodeGen_Private::FNamePropertyParams NewProp_Name;
		static const UECodeGen_Private::FFloatPropertyParams NewProp_Value;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UECodeGen_Private::FFunctionParams FuncParams;
	};
	const UECodeGen_Private::FNamePropertyParams Z_Construct_UFunction_UFMODAudioComponent_SetParameter_Statics::NewProp_Name = { "Name", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Name, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FMODAudioComponent_eventSetParameter_Parms, Name), METADATA_PARAMS(nullptr, 0) };
	const UECodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_UFMODAudioComponent_SetParameter_Statics::NewProp_Value = { "Value", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FMODAudioComponent_eventSetParameter_Parms, Value), METADATA_PARAMS(nullptr, 0) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UFMODAudioComponent_SetParameter_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UFMODAudioComponent_SetParameter_Statics::NewProp_Name,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UFMODAudioComponent_SetParameter_Statics::NewProp_Value,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UFMODAudioComponent_SetParameter_Statics::Function_MetaDataParams[] = {
		{ "Category", "Audio|FMOD|Components" },
		{ "Comment", "/** Set a parameter of the Event. */" },
		{ "ModuleRelativePath", "Classes/FMODAudioComponent.h" },
		{ "ToolTip", "Set a parameter of the Event." },
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UFMODAudioComponent_SetParameter_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UFMODAudioComponent, nullptr, "SetParameter", nullptr, nullptr, sizeof(Z_Construct_UFunction_UFMODAudioComponent_SetParameter_Statics::FMODAudioComponent_eventSetParameter_Parms), Z_Construct_UFunction_UFMODAudioComponent_SetParameter_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UFMODAudioComponent_SetParameter_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UFMODAudioComponent_SetParameter_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UFMODAudioComponent_SetParameter_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UFMODAudioComponent_SetParameter()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UFMODAudioComponent_SetParameter_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UFMODAudioComponent_SetPaused_Statics
	{
		struct FMODAudioComponent_eventSetPaused_Parms
		{
			bool paused;
		};
		static void NewProp_paused_SetBit(void* Obj);
		static const UECodeGen_Private::FBoolPropertyParams NewProp_paused;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UECodeGen_Private::FFunctionParams FuncParams;
	};
	void Z_Construct_UFunction_UFMODAudioComponent_SetPaused_Statics::NewProp_paused_SetBit(void* Obj)
	{
		((FMODAudioComponent_eventSetPaused_Parms*)Obj)->paused = 1;
	}
	const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UFMODAudioComponent_SetPaused_Statics::NewProp_paused = { "paused", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, sizeof(bool), sizeof(FMODAudioComponent_eventSetPaused_Parms), &Z_Construct_UFunction_UFMODAudioComponent_SetPaused_Statics::NewProp_paused_SetBit, METADATA_PARAMS(nullptr, 0) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UFMODAudioComponent_SetPaused_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UFMODAudioComponent_SetPaused_Statics::NewProp_paused,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UFMODAudioComponent_SetPaused_Statics::Function_MetaDataParams[] = {
		{ "Category", "Audio|FMOD|Components" },
		{ "Comment", "/** Pause/Unpause an audio component. */" },
		{ "ModuleRelativePath", "Classes/FMODAudioComponent.h" },
		{ "ToolTip", "Pause/Unpause an audio component." },
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UFMODAudioComponent_SetPaused_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UFMODAudioComponent, nullptr, "SetPaused", nullptr, nullptr, sizeof(Z_Construct_UFunction_UFMODAudioComponent_SetPaused_Statics::FMODAudioComponent_eventSetPaused_Parms), Z_Construct_UFunction_UFMODAudioComponent_SetPaused_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UFMODAudioComponent_SetPaused_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UFMODAudioComponent_SetPaused_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UFMODAudioComponent_SetPaused_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UFMODAudioComponent_SetPaused()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UFMODAudioComponent_SetPaused_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UFMODAudioComponent_SetPitch_Statics
	{
		struct FMODAudioComponent_eventSetPitch_Parms
		{
			float pitch;
		};
		static const UECodeGen_Private::FFloatPropertyParams NewProp_pitch;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UECodeGen_Private::FFunctionParams FuncParams;
	};
	const UECodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_UFMODAudioComponent_SetPitch_Statics::NewProp_pitch = { "pitch", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FMODAudioComponent_eventSetPitch_Parms, pitch), METADATA_PARAMS(nullptr, 0) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UFMODAudioComponent_SetPitch_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UFMODAudioComponent_SetPitch_Statics::NewProp_pitch,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UFMODAudioComponent_SetPitch_Statics::Function_MetaDataParams[] = {
		{ "Category", "Audio|FMOD|Components" },
		{ "Comment", "/** Sets the pitch multiplier. */" },
		{ "ModuleRelativePath", "Classes/FMODAudioComponent.h" },
		{ "ToolTip", "Sets the pitch multiplier." },
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UFMODAudioComponent_SetPitch_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UFMODAudioComponent, nullptr, "SetPitch", nullptr, nullptr, sizeof(Z_Construct_UFunction_UFMODAudioComponent_SetPitch_Statics::FMODAudioComponent_eventSetPitch_Parms), Z_Construct_UFunction_UFMODAudioComponent_SetPitch_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UFMODAudioComponent_SetPitch_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UFMODAudioComponent_SetPitch_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UFMODAudioComponent_SetPitch_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UFMODAudioComponent_SetPitch()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UFMODAudioComponent_SetPitch_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UFMODAudioComponent_SetProgrammerSoundName_Statics
	{
		struct FMODAudioComponent_eventSetProgrammerSoundName_Parms
		{
			FString Value;
		};
		static const UECodeGen_Private::FStrPropertyParams NewProp_Value;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UECodeGen_Private::FFunctionParams FuncParams;
	};
	const UECodeGen_Private::FStrPropertyParams Z_Construct_UFunction_UFMODAudioComponent_SetProgrammerSoundName_Statics::NewProp_Value = { "Value", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FMODAudioComponent_eventSetProgrammerSoundName_Parms, Value), METADATA_PARAMS(nullptr, 0) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UFMODAudioComponent_SetProgrammerSoundName_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UFMODAudioComponent_SetProgrammerSoundName_Statics::NewProp_Value,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UFMODAudioComponent_SetProgrammerSoundName_Statics::Function_MetaDataParams[] = {
		{ "Category", "Audio|FMOD|Components" },
		{ "Comment", "/** Set the sound name to use for programmer sound.  Will look up the name in any loaded audio table. */" },
		{ "ModuleRelativePath", "Classes/FMODAudioComponent.h" },
		{ "ToolTip", "Set the sound name to use for programmer sound.  Will look up the name in any loaded audio table." },
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UFMODAudioComponent_SetProgrammerSoundName_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UFMODAudioComponent, nullptr, "SetProgrammerSoundName", nullptr, nullptr, sizeof(Z_Construct_UFunction_UFMODAudioComponent_SetProgrammerSoundName_Statics::FMODAudioComponent_eventSetProgrammerSoundName_Parms), Z_Construct_UFunction_UFMODAudioComponent_SetProgrammerSoundName_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UFMODAudioComponent_SetProgrammerSoundName_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UFMODAudioComponent_SetProgrammerSoundName_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UFMODAudioComponent_SetProgrammerSoundName_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UFMODAudioComponent_SetProgrammerSoundName()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UFMODAudioComponent_SetProgrammerSoundName_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UFMODAudioComponent_SetProperty_Statics
	{
		struct FMODAudioComponent_eventSetProperty_Parms
		{
			TEnumAsByte<EFMODEventProperty::Type> Property;
			float Value;
		};
		static const UECodeGen_Private::FBytePropertyParams NewProp_Property;
		static const UECodeGen_Private::FFloatPropertyParams NewProp_Value;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UECodeGen_Private::FFunctionParams FuncParams;
	};
	const UECodeGen_Private::FBytePropertyParams Z_Construct_UFunction_UFMODAudioComponent_SetProperty_Statics::NewProp_Property = { "Property", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FMODAudioComponent_eventSetProperty_Parms, Property), Z_Construct_UEnum_FMODStudio_EFMODEventProperty, METADATA_PARAMS(nullptr, 0) }; // 2209603180
	const UECodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_UFMODAudioComponent_SetProperty_Statics::NewProp_Value = { "Value", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FMODAudioComponent_eventSetProperty_Parms, Value), METADATA_PARAMS(nullptr, 0) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UFMODAudioComponent_SetProperty_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UFMODAudioComponent_SetProperty_Statics::NewProp_Property,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UFMODAudioComponent_SetProperty_Statics::NewProp_Value,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UFMODAudioComponent_SetProperty_Statics::Function_MetaDataParams[] = {
		{ "Category", "Audio|FMOD|Components" },
		{ "Comment", "/** Set a property of the Event. */" },
		{ "ModuleRelativePath", "Classes/FMODAudioComponent.h" },
		{ "ToolTip", "Set a property of the Event." },
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UFMODAudioComponent_SetProperty_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UFMODAudioComponent, nullptr, "SetProperty", nullptr, nullptr, sizeof(Z_Construct_UFunction_UFMODAudioComponent_SetProperty_Statics::FMODAudioComponent_eventSetProperty_Parms), Z_Construct_UFunction_UFMODAudioComponent_SetProperty_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UFMODAudioComponent_SetProperty_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UFMODAudioComponent_SetProperty_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UFMODAudioComponent_SetProperty_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UFMODAudioComponent_SetProperty()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UFMODAudioComponent_SetProperty_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UFMODAudioComponent_SetTimelinePosition_Statics
	{
		struct FMODAudioComponent_eventSetTimelinePosition_Parms
		{
			int32 Time;
		};
		static const UECodeGen_Private::FIntPropertyParams NewProp_Time;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UECodeGen_Private::FFunctionParams FuncParams;
	};
	const UECodeGen_Private::FIntPropertyParams Z_Construct_UFunction_UFMODAudioComponent_SetTimelinePosition_Statics::NewProp_Time = { "Time", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FMODAudioComponent_eventSetTimelinePosition_Parms, Time), METADATA_PARAMS(nullptr, 0) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UFMODAudioComponent_SetTimelinePosition_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UFMODAudioComponent_SetTimelinePosition_Statics::NewProp_Time,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UFMODAudioComponent_SetTimelinePosition_Statics::Function_MetaDataParams[] = {
		{ "Category", "Audio|FMOD|Components" },
		{ "Comment", "/** Set the timeline position in milliseconds. */" },
		{ "ModuleRelativePath", "Classes/FMODAudioComponent.h" },
		{ "ToolTip", "Set the timeline position in milliseconds." },
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UFMODAudioComponent_SetTimelinePosition_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UFMODAudioComponent, nullptr, "SetTimelinePosition", nullptr, nullptr, sizeof(Z_Construct_UFunction_UFMODAudioComponent_SetTimelinePosition_Statics::FMODAudioComponent_eventSetTimelinePosition_Parms), Z_Construct_UFunction_UFMODAudioComponent_SetTimelinePosition_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UFMODAudioComponent_SetTimelinePosition_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UFMODAudioComponent_SetTimelinePosition_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UFMODAudioComponent_SetTimelinePosition_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UFMODAudioComponent_SetTimelinePosition()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UFMODAudioComponent_SetTimelinePosition_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UFMODAudioComponent_SetVolume_Statics
	{
		struct FMODAudioComponent_eventSetVolume_Parms
		{
			float volume;
		};
		static const UECodeGen_Private::FFloatPropertyParams NewProp_volume;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UECodeGen_Private::FFunctionParams FuncParams;
	};
	const UECodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_UFMODAudioComponent_SetVolume_Statics::NewProp_volume = { "volume", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FMODAudioComponent_eventSetVolume_Parms, volume), METADATA_PARAMS(nullptr, 0) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UFMODAudioComponent_SetVolume_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UFMODAudioComponent_SetVolume_Statics::NewProp_volume,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UFMODAudioComponent_SetVolume_Statics::Function_MetaDataParams[] = {
		{ "Category", "Audio|FMOD|Components" },
		{ "Comment", "/** Sets the volume level. */" },
		{ "ModuleRelativePath", "Classes/FMODAudioComponent.h" },
		{ "ToolTip", "Sets the volume level." },
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UFMODAudioComponent_SetVolume_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UFMODAudioComponent, nullptr, "SetVolume", nullptr, nullptr, sizeof(Z_Construct_UFunction_UFMODAudioComponent_SetVolume_Statics::FMODAudioComponent_eventSetVolume_Parms), Z_Construct_UFunction_UFMODAudioComponent_SetVolume_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UFMODAudioComponent_SetVolume_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UFMODAudioComponent_SetVolume_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UFMODAudioComponent_SetVolume_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UFMODAudioComponent_SetVolume()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UFMODAudioComponent_SetVolume_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UFMODAudioComponent_Stop_Statics
	{
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UECodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UFMODAudioComponent_Stop_Statics::Function_MetaDataParams[] = {
		{ "Category", "Audio|FMOD|Components" },
		{ "Comment", "/** Stop an audio component playing its sound cue, issue any delegates if needed. */" },
		{ "ModuleRelativePath", "Classes/FMODAudioComponent.h" },
		{ "ToolTip", "Stop an audio component playing its sound cue, issue any delegates if needed." },
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UFMODAudioComponent_Stop_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UFMODAudioComponent, nullptr, "Stop", nullptr, nullptr, 0, nullptr, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UFMODAudioComponent_Stop_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UFMODAudioComponent_Stop_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UFMODAudioComponent_Stop()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UFMODAudioComponent_Stop_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(UFMODAudioComponent);
	UClass* Z_Construct_UClass_UFMODAudioComponent_NoRegister()
	{
		return UFMODAudioComponent::StaticClass();
	}
	struct Z_Construct_UClass_UFMODAudioComponent_Statics
	{
		static UObject* (*const DependentSingletons[])();
		static const FClassFunctionLinkInfo FuncInfo[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_Event_MetaData[];
#endif
		static const UECodeGen_Private::FObjectPropertyParams NewProp_Event;
		static const UECodeGen_Private::FFloatPropertyParams NewProp_ParameterCache_ValueProp;
		static const UECodeGen_Private::FNamePropertyParams NewProp_ParameterCache_Key_KeyProp;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_ParameterCache_MetaData[];
#endif
		static const UECodeGen_Private::FMapPropertyParams NewProp_ParameterCache;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_ProgrammerSoundName_MetaData[];
#endif
		static const UECodeGen_Private::FStrPropertyParams NewProp_ProgrammerSoundName;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_bEnableTimelineCallbacks_MetaData[];
#endif
		static void NewProp_bEnableTimelineCallbacks_SetBit(void* Obj);
		static const UECodeGen_Private::FBoolPropertyParams NewProp_bEnableTimelineCallbacks;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_bAutoDestroy_MetaData[];
#endif
		static void NewProp_bAutoDestroy_SetBit(void* Obj);
		static const UECodeGen_Private::FBoolPropertyParams NewProp_bAutoDestroy;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_bStopWhenOwnerDestroyed_MetaData[];
#endif
		static void NewProp_bStopWhenOwnerDestroyed_SetBit(void* Obj);
		static const UECodeGen_Private::FBoolPropertyParams NewProp_bStopWhenOwnerDestroyed;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_OnEventStopped_MetaData[];
#endif
		static const UECodeGen_Private::FMulticastDelegatePropertyParams NewProp_OnEventStopped;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_OnTimelineMarker_MetaData[];
#endif
		static const UECodeGen_Private::FMulticastDelegatePropertyParams NewProp_OnTimelineMarker;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_OnTimelineBeat_MetaData[];
#endif
		static const UECodeGen_Private::FMulticastDelegatePropertyParams NewProp_OnTimelineBeat;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_AttenuationDetails_MetaData[];
#endif
		static const UECodeGen_Private::FStructPropertyParams NewProp_AttenuationDetails;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_OcclusionDetails_MetaData[];
#endif
		static const UECodeGen_Private::FStructPropertyParams NewProp_OcclusionDetails;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UECodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_UFMODAudioComponent_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_USceneComponent,
		(UObject* (*)())Z_Construct_UPackage__Script_FMODStudio,
	};
	const FClassFunctionLinkInfo Z_Construct_UClass_UFMODAudioComponent_Statics::FuncInfo[] = {
		{ &Z_Construct_UFunction_UFMODAudioComponent_GetLength, "GetLength" }, // 1804089463
		{ &Z_Construct_UFunction_UFMODAudioComponent_GetParameter, "GetParameter" }, // 964970158
		{ &Z_Construct_UFunction_UFMODAudioComponent_GetParameterValue, "GetParameterValue" }, // 1429540071
		{ &Z_Construct_UFunction_UFMODAudioComponent_GetProperty, "GetProperty" }, // 2056088844
		{ &Z_Construct_UFunction_UFMODAudioComponent_GetTimelinePosition, "GetTimelinePosition" }, // 1819822577
		{ &Z_Construct_UFunction_UFMODAudioComponent_IsPlaying, "IsPlaying" }, // 2368425669
		{ &Z_Construct_UFunction_UFMODAudioComponent_KeyOff, "KeyOff" }, // 255935687
		{ &Z_Construct_UFunction_UFMODAudioComponent_Play, "Play" }, // 4282901360
		{ &Z_Construct_UFunction_UFMODAudioComponent_Release, "Release" }, // 561731244
		{ &Z_Construct_UFunction_UFMODAudioComponent_SetEvent, "SetEvent" }, // 151810274
		{ &Z_Construct_UFunction_UFMODAudioComponent_SetParameter, "SetParameter" }, // 1709821444
		{ &Z_Construct_UFunction_UFMODAudioComponent_SetPaused, "SetPaused" }, // 3369576300
		{ &Z_Construct_UFunction_UFMODAudioComponent_SetPitch, "SetPitch" }, // 219326881
		{ &Z_Construct_UFunction_UFMODAudioComponent_SetProgrammerSoundName, "SetProgrammerSoundName" }, // 4281737680
		{ &Z_Construct_UFunction_UFMODAudioComponent_SetProperty, "SetProperty" }, // 957624049
		{ &Z_Construct_UFunction_UFMODAudioComponent_SetTimelinePosition, "SetTimelinePosition" }, // 452273885
		{ &Z_Construct_UFunction_UFMODAudioComponent_SetVolume, "SetVolume" }, // 813559745
		{ &Z_Construct_UFunction_UFMODAudioComponent_Stop, "Stop" }, // 828724521
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UFMODAudioComponent_Statics::Class_MetaDataParams[] = {
		{ "BlueprintSpawnableComponent", "" },
		{ "BlueprintType", "true" },
		{ "ClassGroupNames", "Audio Common" },
		{ "Comment", "/**\n * Plays FMOD Studio events.\n */" },
		{ "HideCategories", "Object ActorComponent Physics Rendering Mobility LOD PhysicsVolume" },
		{ "IncludePath", "FMODAudioComponent.h" },
		{ "IsBlueprintBase", "true" },
		{ "ModuleRelativePath", "Classes/FMODAudioComponent.h" },
		{ "ToolTip", "Plays FMOD Studio events." },
	};
#endif
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UFMODAudioComponent_Statics::NewProp_Event_MetaData[] = {
		{ "Category", "FMODAudio" },
		{ "Comment", "/** The event asset to use for this sound. */" },
		{ "ModuleRelativePath", "Classes/FMODAudioComponent.h" },
		{ "ToolTip", "The event asset to use for this sound." },
	};
#endif
	const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_UFMODAudioComponent_Statics::NewProp_Event = { "Event", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UFMODAudioComponent, Event), Z_Construct_UClass_UFMODEvent_NoRegister, METADATA_PARAMS(Z_Construct_UClass_UFMODAudioComponent_Statics::NewProp_Event_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UFMODAudioComponent_Statics::NewProp_Event_MetaData)) };
	const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_UFMODAudioComponent_Statics::NewProp_ParameterCache_ValueProp = { "ParameterCache", nullptr, (EPropertyFlags)0x0000000000000001, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, 1, METADATA_PARAMS(nullptr, 0) };
	const UECodeGen_Private::FNamePropertyParams Z_Construct_UClass_UFMODAudioComponent_Statics::NewProp_ParameterCache_Key_KeyProp = { "ParameterCache_Key", nullptr, (EPropertyFlags)0x0000000000000001, UECodeGen_Private::EPropertyGenFlags::Name, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UFMODAudioComponent_Statics::NewProp_ParameterCache_MetaData[] = {
		{ "Category", "FMODAudio" },
		{ "Comment", "/** Event parameter cache. */" },
		{ "ModuleRelativePath", "Classes/FMODAudioComponent.h" },
		{ "ToolTip", "Event parameter cache." },
	};
#endif
	const UECodeGen_Private::FMapPropertyParams Z_Construct_UClass_UFMODAudioComponent_Statics::NewProp_ParameterCache = { "ParameterCache", nullptr, (EPropertyFlags)0x0010020000000005, UECodeGen_Private::EPropertyGenFlags::Map, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UFMODAudioComponent, ParameterCache), EMapPropertyFlags::None, METADATA_PARAMS(Z_Construct_UClass_UFMODAudioComponent_Statics::NewProp_ParameterCache_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UFMODAudioComponent_Statics::NewProp_ParameterCache_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UFMODAudioComponent_Statics::NewProp_ProgrammerSoundName_MetaData[] = {
		{ "Category", "FMODAudio" },
		{ "Comment", "/** Sound name used for programmer sound.  Will look up the name in any loaded audio table. */" },
		{ "ModuleRelativePath", "Classes/FMODAudioComponent.h" },
		{ "ToolTip", "Sound name used for programmer sound.  Will look up the name in any loaded audio table." },
	};
#endif
	const UECodeGen_Private::FStrPropertyParams Z_Construct_UClass_UFMODAudioComponent_Statics::NewProp_ProgrammerSoundName = { "ProgrammerSoundName", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UFMODAudioComponent, ProgrammerSoundName), METADATA_PARAMS(Z_Construct_UClass_UFMODAudioComponent_Statics::NewProp_ProgrammerSoundName_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UFMODAudioComponent_Statics::NewProp_ProgrammerSoundName_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UFMODAudioComponent_Statics::NewProp_bEnableTimelineCallbacks_MetaData[] = {
		{ "Category", "FMODAudio" },
		{ "Comment", "/** Enable timeline callbacks for this sound, so that OnTimelineMarker and OnTimelineBeat can be used. */" },
		{ "ModuleRelativePath", "Classes/FMODAudioComponent.h" },
		{ "ToolTip", "Enable timeline callbacks for this sound, so that OnTimelineMarker and OnTimelineBeat can be used." },
	};
#endif
	void Z_Construct_UClass_UFMODAudioComponent_Statics::NewProp_bEnableTimelineCallbacks_SetBit(void* Obj)
	{
		((UFMODAudioComponent*)Obj)->bEnableTimelineCallbacks = 1;
	}
	const UECodeGen_Private::FBoolPropertyParams Z_Construct_UClass_UFMODAudioComponent_Statics::NewProp_bEnableTimelineCallbacks = { "bEnableTimelineCallbacks", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Bool , RF_Public|RF_Transient|RF_MarkAsNative, 1, sizeof(uint8), sizeof(UFMODAudioComponent), &Z_Construct_UClass_UFMODAudioComponent_Statics::NewProp_bEnableTimelineCallbacks_SetBit, METADATA_PARAMS(Z_Construct_UClass_UFMODAudioComponent_Statics::NewProp_bEnableTimelineCallbacks_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UFMODAudioComponent_Statics::NewProp_bEnableTimelineCallbacks_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UFMODAudioComponent_Statics::NewProp_bAutoDestroy_MetaData[] = {
		{ "Comment", "/** Auto destroy this component on completion. */" },
		{ "ModuleRelativePath", "Classes/FMODAudioComponent.h" },
		{ "ToolTip", "Auto destroy this component on completion." },
	};
#endif
	void Z_Construct_UClass_UFMODAudioComponent_Statics::NewProp_bAutoDestroy_SetBit(void* Obj)
	{
		((UFMODAudioComponent*)Obj)->bAutoDestroy = 1;
	}
	const UECodeGen_Private::FBoolPropertyParams Z_Construct_UClass_UFMODAudioComponent_Statics::NewProp_bAutoDestroy = { "bAutoDestroy", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Bool , RF_Public|RF_Transient|RF_MarkAsNative, 1, sizeof(uint8), sizeof(UFMODAudioComponent), &Z_Construct_UClass_UFMODAudioComponent_Statics::NewProp_bAutoDestroy_SetBit, METADATA_PARAMS(Z_Construct_UClass_UFMODAudioComponent_Statics::NewProp_bAutoDestroy_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UFMODAudioComponent_Statics::NewProp_bAutoDestroy_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UFMODAudioComponent_Statics::NewProp_bStopWhenOwnerDestroyed_MetaData[] = {
		{ "Comment", "/** Stop sound when owner is destroyed. */" },
		{ "ModuleRelativePath", "Classes/FMODAudioComponent.h" },
		{ "ToolTip", "Stop sound when owner is destroyed." },
	};
#endif
	void Z_Construct_UClass_UFMODAudioComponent_Statics::NewProp_bStopWhenOwnerDestroyed_SetBit(void* Obj)
	{
		((UFMODAudioComponent*)Obj)->bStopWhenOwnerDestroyed = 1;
	}
	const UECodeGen_Private::FBoolPropertyParams Z_Construct_UClass_UFMODAudioComponent_Statics::NewProp_bStopWhenOwnerDestroyed = { "bStopWhenOwnerDestroyed", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Bool , RF_Public|RF_Transient|RF_MarkAsNative, 1, sizeof(uint8), sizeof(UFMODAudioComponent), &Z_Construct_UClass_UFMODAudioComponent_Statics::NewProp_bStopWhenOwnerDestroyed_SetBit, METADATA_PARAMS(Z_Construct_UClass_UFMODAudioComponent_Statics::NewProp_bStopWhenOwnerDestroyed_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UFMODAudioComponent_Statics::NewProp_bStopWhenOwnerDestroyed_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UFMODAudioComponent_Statics::NewProp_OnEventStopped_MetaData[] = {
		{ "Comment", "/** Called when an event stops, either because it played to completion or because a Stop() call turned it off early. */" },
		{ "ModuleRelativePath", "Classes/FMODAudioComponent.h" },
		{ "ToolTip", "Called when an event stops, either because it played to completion or because a Stop() call turned it off early." },
	};
#endif
	const UECodeGen_Private::FMulticastDelegatePropertyParams Z_Construct_UClass_UFMODAudioComponent_Statics::NewProp_OnEventStopped = { "OnEventStopped", nullptr, (EPropertyFlags)0x0010000010080000, UECodeGen_Private::EPropertyGenFlags::InlineMulticastDelegate, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UFMODAudioComponent, OnEventStopped), Z_Construct_UDelegateFunction_FMODStudio_OnEventStopped__DelegateSignature, METADATA_PARAMS(Z_Construct_UClass_UFMODAudioComponent_Statics::NewProp_OnEventStopped_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UFMODAudioComponent_Statics::NewProp_OnEventStopped_MetaData)) }; // 2563848394
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UFMODAudioComponent_Statics::NewProp_OnTimelineMarker_MetaData[] = {
		{ "Comment", "/** Called when we reach a named marker (if bEnableTimelineCallbacks is true). */" },
		{ "ModuleRelativePath", "Classes/FMODAudioComponent.h" },
		{ "ToolTip", "Called when we reach a named marker (if bEnableTimelineCallbacks is true)." },
	};
#endif
	const UECodeGen_Private::FMulticastDelegatePropertyParams Z_Construct_UClass_UFMODAudioComponent_Statics::NewProp_OnTimelineMarker = { "OnTimelineMarker", nullptr, (EPropertyFlags)0x0010000010080000, UECodeGen_Private::EPropertyGenFlags::InlineMulticastDelegate, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UFMODAudioComponent, OnTimelineMarker), Z_Construct_UDelegateFunction_FMODStudio_OnTimelineMarker__DelegateSignature, METADATA_PARAMS(Z_Construct_UClass_UFMODAudioComponent_Statics::NewProp_OnTimelineMarker_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UFMODAudioComponent_Statics::NewProp_OnTimelineMarker_MetaData)) }; // 1866420010
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UFMODAudioComponent_Statics::NewProp_OnTimelineBeat_MetaData[] = {
		{ "Comment", "/** Called when we reach a beat of a tempo (if bEnableTimelineCallbacks is true). */" },
		{ "ModuleRelativePath", "Classes/FMODAudioComponent.h" },
		{ "ToolTip", "Called when we reach a beat of a tempo (if bEnableTimelineCallbacks is true)." },
	};
#endif
	const UECodeGen_Private::FMulticastDelegatePropertyParams Z_Construct_UClass_UFMODAudioComponent_Statics::NewProp_OnTimelineBeat = { "OnTimelineBeat", nullptr, (EPropertyFlags)0x0010000010080000, UECodeGen_Private::EPropertyGenFlags::InlineMulticastDelegate, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UFMODAudioComponent, OnTimelineBeat), Z_Construct_UDelegateFunction_FMODStudio_OnTimelineBeat__DelegateSignature, METADATA_PARAMS(Z_Construct_UClass_UFMODAudioComponent_Statics::NewProp_OnTimelineBeat_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UFMODAudioComponent_Statics::NewProp_OnTimelineBeat_MetaData)) }; // 3675615853
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UFMODAudioComponent_Statics::NewProp_AttenuationDetails_MetaData[] = {
		{ "Category", "FMODAudio" },
		{ "Comment", "/** FMOD Custom Attenuation Details. */" },
		{ "ModuleRelativePath", "Classes/FMODAudioComponent.h" },
		{ "ToolTip", "FMOD Custom Attenuation Details." },
	};
#endif
	const UECodeGen_Private::FStructPropertyParams Z_Construct_UClass_UFMODAudioComponent_Statics::NewProp_AttenuationDetails = { "AttenuationDetails", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UFMODAudioComponent, AttenuationDetails), Z_Construct_UScriptStruct_FFMODAttenuationDetails, METADATA_PARAMS(Z_Construct_UClass_UFMODAudioComponent_Statics::NewProp_AttenuationDetails_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UFMODAudioComponent_Statics::NewProp_AttenuationDetails_MetaData)) }; // 175372084
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UFMODAudioComponent_Statics::NewProp_OcclusionDetails_MetaData[] = {
		{ "Category", "FMODAudio" },
		{ "Comment", "/** FMOD Custom Occlusion Details. */" },
		{ "ModuleRelativePath", "Classes/FMODAudioComponent.h" },
		{ "ToolTip", "FMOD Custom Occlusion Details." },
	};
#endif
	const UECodeGen_Private::FStructPropertyParams Z_Construct_UClass_UFMODAudioComponent_Statics::NewProp_OcclusionDetails = { "OcclusionDetails", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UFMODAudioComponent, OcclusionDetails), Z_Construct_UScriptStruct_FFMODOcclusionDetails, METADATA_PARAMS(Z_Construct_UClass_UFMODAudioComponent_Statics::NewProp_OcclusionDetails_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UFMODAudioComponent_Statics::NewProp_OcclusionDetails_MetaData)) }; // 4159284475
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_UFMODAudioComponent_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UFMODAudioComponent_Statics::NewProp_Event,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UFMODAudioComponent_Statics::NewProp_ParameterCache_ValueProp,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UFMODAudioComponent_Statics::NewProp_ParameterCache_Key_KeyProp,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UFMODAudioComponent_Statics::NewProp_ParameterCache,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UFMODAudioComponent_Statics::NewProp_ProgrammerSoundName,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UFMODAudioComponent_Statics::NewProp_bEnableTimelineCallbacks,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UFMODAudioComponent_Statics::NewProp_bAutoDestroy,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UFMODAudioComponent_Statics::NewProp_bStopWhenOwnerDestroyed,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UFMODAudioComponent_Statics::NewProp_OnEventStopped,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UFMODAudioComponent_Statics::NewProp_OnTimelineMarker,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UFMODAudioComponent_Statics::NewProp_OnTimelineBeat,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UFMODAudioComponent_Statics::NewProp_AttenuationDetails,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UFMODAudioComponent_Statics::NewProp_OcclusionDetails,
	};
	const FCppClassTypeInfoStatic Z_Construct_UClass_UFMODAudioComponent_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UFMODAudioComponent>::IsAbstract,
	};
	const UECodeGen_Private::FClassParams Z_Construct_UClass_UFMODAudioComponent_Statics::ClassParams = {
		&UFMODAudioComponent::StaticClass,
		"Engine",
		&StaticCppClassTypeInfo,
		DependentSingletons,
		FuncInfo,
		Z_Construct_UClass_UFMODAudioComponent_Statics::PropPointers,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		UE_ARRAY_COUNT(FuncInfo),
		UE_ARRAY_COUNT(Z_Construct_UClass_UFMODAudioComponent_Statics::PropPointers),
		0,
		0x00B000A4u,
		METADATA_PARAMS(Z_Construct_UClass_UFMODAudioComponent_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_UFMODAudioComponent_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_UFMODAudioComponent()
	{
		if (!Z_Registration_Info_UClass_UFMODAudioComponent.OuterSingleton)
		{
			UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UFMODAudioComponent.OuterSingleton, Z_Construct_UClass_UFMODAudioComponent_Statics::ClassParams);
		}
		return Z_Registration_Info_UClass_UFMODAudioComponent.OuterSingleton;
	}
	template<> FMODSTUDIO_API UClass* StaticClass<UFMODAudioComponent>()
	{
		return UFMODAudioComponent::StaticClass();
	}
	DEFINE_VTABLE_PTR_HELPER_CTOR(UFMODAudioComponent);
	struct Z_CompiledInDeferFile_FID_ProjectCovenant_Plugins_FMODStudio_Source_FMODStudio_Classes_FMODAudioComponent_h_Statics
	{
		static const FEnumRegisterCompiledInInfo EnumInfo[];
		static const FStructRegisterCompiledInInfo ScriptStructInfo[];
		static const FClassRegisterCompiledInInfo ClassInfo[];
	};
	const FEnumRegisterCompiledInInfo Z_CompiledInDeferFile_FID_ProjectCovenant_Plugins_FMODStudio_Source_FMODStudio_Classes_FMODAudioComponent_h_Statics::EnumInfo[] = {
		{ EFMODEventProperty_StaticEnum, TEXT("EFMODEventProperty"), &Z_Registration_Info_UEnum_EFMODEventProperty, CONSTRUCT_RELOAD_VERSION_INFO(FEnumReloadVersionInfo, 2209603180U) },
	};
	const FStructRegisterCompiledInInfo Z_CompiledInDeferFile_FID_ProjectCovenant_Plugins_FMODStudio_Source_FMODStudio_Classes_FMODAudioComponent_h_Statics::ScriptStructInfo[] = {
		{ FFMODAttenuationDetails::StaticStruct, Z_Construct_UScriptStruct_FFMODAttenuationDetails_Statics::NewStructOps, TEXT("FMODAttenuationDetails"), &Z_Registration_Info_UScriptStruct_FMODAttenuationDetails, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FFMODAttenuationDetails), 175372084U) },
		{ FFMODOcclusionDetails::StaticStruct, Z_Construct_UScriptStruct_FFMODOcclusionDetails_Statics::NewStructOps, TEXT("FMODOcclusionDetails"), &Z_Registration_Info_UScriptStruct_FMODOcclusionDetails, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FFMODOcclusionDetails), 4159284475U) },
	};
	const FClassRegisterCompiledInInfo Z_CompiledInDeferFile_FID_ProjectCovenant_Plugins_FMODStudio_Source_FMODStudio_Classes_FMODAudioComponent_h_Statics::ClassInfo[] = {
		{ Z_Construct_UClass_UFMODAudioComponent, UFMODAudioComponent::StaticClass, TEXT("UFMODAudioComponent"), &Z_Registration_Info_UClass_UFMODAudioComponent, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UFMODAudioComponent), 875671077U) },
	};
	static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_ProjectCovenant_Plugins_FMODStudio_Source_FMODStudio_Classes_FMODAudioComponent_h_4145651611(TEXT("/Script/FMODStudio"),
		Z_CompiledInDeferFile_FID_ProjectCovenant_Plugins_FMODStudio_Source_FMODStudio_Classes_FMODAudioComponent_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_ProjectCovenant_Plugins_FMODStudio_Source_FMODStudio_Classes_FMODAudioComponent_h_Statics::ClassInfo),
		Z_CompiledInDeferFile_FID_ProjectCovenant_Plugins_FMODStudio_Source_FMODStudio_Classes_FMODAudioComponent_h_Statics::ScriptStructInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_ProjectCovenant_Plugins_FMODStudio_Source_FMODStudio_Classes_FMODAudioComponent_h_Statics::ScriptStructInfo),
		Z_CompiledInDeferFile_FID_ProjectCovenant_Plugins_FMODStudio_Source_FMODStudio_Classes_FMODAudioComponent_h_Statics::EnumInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_ProjectCovenant_Plugins_FMODStudio_Source_FMODStudio_Classes_FMODAudioComponent_h_Statics::EnumInfo));
PRAGMA_ENABLE_DEPRECATION_WARNINGS
