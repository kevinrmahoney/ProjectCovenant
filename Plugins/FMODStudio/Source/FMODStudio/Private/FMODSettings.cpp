// Copyright (c), Firelight Technologies Pty, Ltd. 2012-2022.

#include "FMODSettings.h"
#include "Misc/Paths.h"

#if WITH_EDITOR
#include "Settings/ProjectPackagingSettings.h"
#endif

#ifdef FMOD_PLATFORM_HEADER
#include "FMODPlatform.h"
#endif

//////////////////////////////////////////////////////////////////////////
// UPaperRuntimeSettings

inline EFMODPlatforms::Type CurrentPlatform()
{
    EFMODPlatforms::Type platform;
#if defined(FMOD_PLATFORM_HEADER)
    platform = FMODPlatform_CurrentPlatform();
#elif WITH_EDITOR
    platform = EFMODPlatforms::Editor;
#elif PLATFORM_WINDOWS
    platform = EFMODPlatforms::Windows;
#elif PLATFORM_LINUX
    platform = EFMODPlatforms::Linux;
#elif PLATFORM_MAC
    platform = EFMODPlatforms::Mac;
#elif PLATFORM_ANDROID
    platform = EFMODPlatforms::Android;
#elif PLATFORM_IOS || PLATFORM_TVOS
    platform = EFMODPlatforms::IOS;
#endif
    return platform;
}

UFMODSettings::UFMODSettings(const FObjectInitializer &ObjectInitializer)
    : Super(ObjectInitializer)
{
    MasterBankName = TEXT("Master");
    BankOutputDirectory.Path = TEXT("FMOD");
    OutputFormat = EFMODSpeakerMode::Surround_5_1;
    OutputType = EFMODOutput::TYPE_AUTODETECT;
    ContentBrowserPrefix = TEXT("/Game/FMOD/");
    bLoadAllBanks = true;
    bLoadAllSampleData = false;
    bEnableLiveUpdate = true;
    bVol0Virtual = true;
    Vol0VirtualLevel = 0.0001f;
    RealChannelCount = 64;
    TotalChannelCount = 512;
    DSPBufferLength = 0;
    DSPBufferCount = 0;
    FileBufferSize = 2048;
    StudioUpdatePeriod = 0;
    LiveUpdatePort = 9264;
    EditorLiveUpdatePort = 9265;
    ReloadBanksDelay = 5;
    bMatchHardwareSampleRate = true;
    bLockAllBuses = false;
    bEnableMemoryTracking = false;
}

FString UFMODSettings::GetFullBankPath() const
{
    FString FullPath = BankOutputDirectory.Path;
    if (FPaths::IsRelative(FullPath))
    {
        FullPath = FPaths::ProjectContentDir() / FullPath;
    }

    if (ForcePlatformName == TEXT("."))
    {
        // Leave path without subdirectory
    }
    else if (!ForcePlatformName.IsEmpty())
    {
        FullPath = FullPath / ForcePlatformName;
    }
    else
    {
#ifdef FMOD_PLATFORM_HEADER
        FString PlatformName = FMODPlatform_PlatformName();
#elif PLATFORM_IOS || PLATFORM_TVOS || PLATFORM_ANDROID
        FString PlatformName = "Mobile";
#elif PLATFORM_PS4
        FString PlatformName = "PS4";
#elif PLATFORM_XBOXONE
        FString PlatformName = "XboxOne";
#elif PLATFORM_SWITCH
        FString PlatformName = "Switch";
#else
        FString PlatformName = "Desktop";
#endif
        FullPath = FullPath / PlatformName;
    }
    return FullPath;
}

FString UFMODSettings::GetMasterBankFilename() const
{
    return MasterBankName + TEXT(".bank");
}

FString UFMODSettings::GetMasterAssetsBankFilename() const
{
    return MasterBankName + TEXT(".assets.bank");
}

FString UFMODSettings::GetMasterStringsBankFilename() const
{
    return MasterBankName + TEXT(".strings.bank");
}

FString UFMODSettings::GetFullContentPath() const
{
    return ContentBrowserPrefix;
}

#if WITH_EDITOR
FString UFMODSettings::GetDesktopBankPath() const
{
    FString Path = BankOutputDirectory.Path;

    if (ForcePlatformName.IsEmpty())
    {
        Path = Path / "Desktop";
    }
    else if (ForcePlatformName != TEXT("."))
    {
        Path = Path / ForcePlatformName;
    }

    return Path;
}

UFMODSettings::EProblem UFMODSettings::Check() const
{
    if (!IsBankPathSet())
    {
        return BankPathNotSet;
    }

    // Check packaging settings to ensure that only the correct bank output directory for desktop (or forced platform) banks is set-up for staging
    FString DesktopBankPath = GetDesktopBankPath();
    UProjectPackagingSettings* PackagingSettings = Cast<UProjectPackagingSettings>(UProjectPackagingSettings::StaticClass()->GetDefaultObject());
    bool bCorrectPathAdded = false;
    bool bOtherPathsAdded = false;
    bool bAssetsToCookAdded = false;

    for (int i = 0; i < PackagingSettings->DirectoriesToAlwaysStageAsNonUFS.Num(); ++i)
    {
        if (PackagingSettings->DirectoriesToAlwaysStageAsNonUFS[i].Path.StartsWith(BankOutputDirectory.Path))
        {
            if (PackagingSettings->DirectoriesToAlwaysStageAsNonUFS[i].Path == DesktopBankPath)
            {
                bCorrectPathAdded = true;
            }
            else
            {
                bOtherPathsAdded = true;
            }
        }
    }

    for (int i = 0; i < PackagingSettings->DirectoriesToAlwaysStageAsUFS.Num(); ++i)
    {
        if (PackagingSettings->DirectoriesToAlwaysStageAsUFS[i].Path.StartsWith(BankOutputDirectory.Path))
        {
            bOtherPathsAdded = true;
            break;
        }
    }

    for (int i = 0; i < PackagingSettings->DirectoriesToAlwaysCook.Num(); ++i)
    {
        if (PackagingSettings->DirectoriesToAlwaysCook[i].Path.StartsWith(GetFullContentPath()))
        {
            bAssetsToCookAdded = true;
            break;
        }
    }

    if (!bCorrectPathAdded || bOtherPathsAdded || !bAssetsToCookAdded)
    {
        return PackagingSettingsBad;
    }

    return Okay;
}
#endif // WITH_EDITOR

EFMODSpeakerMode::Type UFMODSettings::GetSpeakerMode() const
{
    return Platforms.Contains(CurrentPlatform()) ? Platforms.Find(CurrentPlatform())->SpeakerMode : OutputFormat;
}

EFMODOutput::Type UFMODSettings::GetOutputType() const
{
    return Platforms.Contains(CurrentPlatform()) ? Platforms.Find(CurrentPlatform())->OutputType : OutputType;
}

int32 UFMODSettings::GetSampleRate() const
{
    return Platforms.Contains(CurrentPlatform()) ? Platforms.Find(CurrentPlatform())->SampleRate : SampleRate;
}

int32 UFMODSettings::GetMemoryPoolSize() const
{
    return (Platforms.Contains(CurrentPlatform()) ? Platforms.Find(CurrentPlatform())->CustomPoolSize : 0);
}

int32 UFMODSettings::GetRealChannelCount() const
{
    return Platforms.Contains(CurrentPlatform()) ? Platforms.Find(CurrentPlatform())->RealChannelCount : RealChannelCount;
}

bool UFMODSettings::SetCodecs(FMOD_ADVANCEDSETTINGS& advSettings) const
{
    const FFMODPlatformSettings* platform = Platforms.Find(CurrentPlatform());
    if (platform == nullptr)
    {
        return false;
    }
    TMap<TEnumAsByte<EFMODCodec::Type>, int32> codecList = platform->Codecs;

    for (const TPair<TEnumAsByte<EFMODCodec::Type>, int32>& pair : codecList)
    {
        switch (pair.Key)
        {
        case EFMODCodec::XMA:
            advSettings.maxXMACodecs = pair.Value;
            break;
        case EFMODCodec::AT9:
            advSettings.maxAT9Codecs = pair.Value;
            break;
        case EFMODCodec::FADPCM:
            advSettings.maxFADPCMCodecs = pair.Value;
            break;
        case EFMODCodec::OPUS:
            advSettings.maxOpusCodecs = pair.Value;
            break;
        case EFMODCodec::VORBIS:
        default:
            advSettings.maxVorbisCodecs = pair.Value;
            break;
        }
    }
    return true;
}