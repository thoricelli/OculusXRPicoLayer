#ifndef OVR_TYPES_H
#define OVR_TYPES_H

#include <stdio.h>
#include <stdbool.h>
#include <inttypes.h>
#include <stdint.h>

typedef struct OculusInitParams_
{
    int sType;
    char* email;
    char* password;
    uint64_t appId;
    char* uriPrefixOverride;
} OculusInitParams;

typedef int32_t KeyValuePairType;

typedef struct ovrKeyValuePair_ {
    char* key_;
    KeyValuePairType valueType_;
    char* stringValue_;
    int intValue_;
    double doubleValue_;
} ovrKeyValuePair;

enum VoipMuteState
{
    Unknown,
    Muted,
    Unmuted
};

typedef void(*FilterCallback)(int16_t pcmData[], size_t pcmDataLength, int frequency, int numChannels);


typedef enum ovrLaunchResult {
    ovrLaunchResult_Unknown,
    ovrLaunchResult_Success,
    ovrLaunchResult_FailedRoomFull,
    ovrLaunchResult_FailedGameAlreadyStarted,
    ovrLaunchResult_FailedRoomNotFound,
    ovrLaunchResult_FailedUserDeclined,
    ovrLaunchResult_FailedOtherReason,
} LaunchResult;

typedef struct ovrNetSyncVec3_ {
    float x;
    float y;
    float z;
} ovrNetSyncVec3;

typedef enum ovrSendPolicy_ {
    ovrSend_Unreliable,
    ovrSend_Reliable,
    ovrSend_Unknown,
} SendPolicy;

typedef enum ovrSystemVoipStatus_ {
    ovrSystemVoipStatus_Unknown,
    ovrSystemVoipStatus_Unavailable,
    ovrSystemVoipStatus_Suppressed,
    ovrSystemVoipStatus_Active,
} SystemVoipStatus;

typedef enum ovrVoipDtxState_ {
    ovrVoipDtxState_Unknown,
    ovrVoipDtxState_Enabled,
    ovrVoipDtxState_Disabled,
} VoipDtxState;

typedef enum ovrVoipBitrate_ {
    ovrVoipBitrate_Unknown,
    ovrVoipBitrate_B16000,
    ovrVoipBitrate_B24000,
    ovrVoipBitrate_B32000,
    ovrVoipBitrate_B64000,
    ovrVoipBitrate_B96000,
    ovrVoipBitrate_B128000,
} VoipBitrate;

typedef enum ovrVoipSampleRate_ {
    ovrVoipSampleRate_Unknown,
    ovrVoipSampleRate_HZ24000,
    ovrVoipSampleRate_HZ44100,
    ovrVoipSampleRate_HZ48000,
} VoipSampleRate;


typedef enum ovrReportRequestResponse_ {
    ovrReportRequestResponse_Unknown,
    ovrReportRequestResponse_Handled,
    ovrReportRequestResponse_Unhandled,
    ovrReportRequestResponse_Unavailable,
} ReportRequestResponse;

typedef enum ovrAchievementType_ {
    ovrAchievement_TypeUnknown,
    ovrAchievement_TypeSimple,
    ovrAchievement_TypeBitfield,
    ovrAchievement_TypeCount,
} AchievementType;

typedef enum ovrLeaderboardFilterType_ {
    ovrLeaderboard_FilterNone,
    ovrLeaderboard_FilterFriends,
    ovrLeaderboard_FilterUnknown,
    ovrLeaderboard_FilterUserIds,
} LeaderboardFilterType;

typedef enum ovrLeaderboardStartAt_ {
    ovrLeaderboard_StartAtTop,
    ovrLeaderboard_StartAtCenteredOnViewer,
    ovrLeaderboard_StartAtCenteredOnViewerOrTop,
    ovrLeaderboard_StartAtUnknown,
} LeaderboardStartAt;

typedef enum ovrLivestreamingAudience_ {
    ovrLivestreamingAudience_Unknown,
    ovrLivestreamingAudience_Public,
    ovrLivestreamingAudience_Friends,
    ovrLivestreamingAudience_OnlyMe,
} LivestreamingAudience;


typedef enum ovrLivestreamingMicrophoneStatus_ {
    ovrLivestreamingMicrophoneStatus_Unknown,
    ovrLivestreamingMicrophoneStatus_MicrophoneOn,
    ovrLivestreamingMicrophoneStatus_MicrophoneOff,
} LivestreamingMicrophoneStatus;

typedef enum ppfMatchmakingStatApproach_ {
    ppfMatchmakingStatApproach_Unknown  = 0,
    ppfMatchmakingStatApproach_Trailing = 1,
    ppfMatchmakingStatApproach_Swingy   = 2,
} MatchmakingStatApproach;

typedef enum ovrMediaContentType_ {
    ovrMediaContentType_Unknown,
    ovrMediaContentType_Photo,
} MediaContentType;


typedef enum ovrNetSyncVoipMicSource_ {
    ovrNetSyncVoipMicSource_Unknown,
    ovrNetSyncVoipMicSource_None,
    ovrNetSyncVoipMicSource_Internal,
} NetSyncVoipMicSource;

typedef enum ovrNetSyncVoipStreamMode_ {
    ovrNetSyncVoipStreamMode_Unknown,
    ovrNetSyncVoipStreamMode_Ambisonic,
    ovrNetSyncVoipStreamMode_Mono,
} NetSyncVoipStreamMode;

typedef enum {
    ovrRoom_JoinPolicyNone,
    ovrRoom_JoinPolicyEveryone,
    ovrRoom_JoinPolicyFriendsOfMembers,
    ovrRoom_JoinPolicyFriendsOfOwner,
    ovrRoom_JoinPolicyInvitedUsers,
} RoomJoinPolicy;

typedef enum ppfRoomMembershipLockStatus_ {
    ppfRoomMembershipLockStatus_Unknown = 0,
    ppfRoomMembershipLockStatus_Lock    = 1,
    ppfRoomMembershipLockStatus_Unlock  = 2,
} RoomMembershipLockStatus;

typedef enum ovrChallengeVisibility_ {
    ovrChallengeVisibility_Unknown,
    ovrChallengeVisibility_InviteOnly,
    ovrChallengeVisibility_Public,
    ovrChallengeVisibility_Private,
} ChallengeVisibility;

typedef enum ovrCloudStorageDataStatus_ {
    ovrCloudStorageDataStatus_Unknown,
    ovrCloudStorageDataStatus_InSync,
    ovrCloudStorageDataStatus_NeedsDownload,
    ovrCloudStorageDataStatus_RemoteDownloading,
    ovrCloudStorageDataStatus_NeedsUpload,
    ovrCloudStorageDataStatus_LocalUploading,
    ovrCloudStorageDataStatus_InConflict,
} CloudStorageDataStatus;

typedef enum ovrCloudStorageUpdateStatus_ {
    ovrCloudStorageUpdateStatus_Unknown,
    ovrCloudStorageUpdateStatus_Ok,
    ovrCloudStorageUpdateStatus_BetterVersionStored,
    ovrCloudStorageUpdateStatus_ManualMergeRequired,
} CloudStorageUpdateStatus;

typedef enum ovrLaunchType_ {
    ovrLaunchType_Unknown,
    ovrLaunchType_Normal,
    ovrLaunchType_Invite,
    ovrLaunchType_Coordinated,
    ovrLaunchType_Deeplink,
} LaunchType;

typedef enum ovrServiceProvider_ {
    ovrServiceProvider_Unknown,
    ovrServiceProvider_Dropbox,
    ovrServiceProvider_Facebook,
    ovrServiceProvider_Google,
    ovrServiceProvider_Instagram,
    ovrServiceProvider_RemoteMedia,
} ServiceProvider;

typedef enum ovrLivestreamingStartStatus_ {
    ovrLivestreamingStartStatus_Success = 1,
    ovrLivestreamingStartStatus_Unknown = 0,
    ovrLivestreamingStartStatus_NoPackageSet = -1,
    ovrLivestreamingStartStatus_NoFbConnect = -2,
    ovrLivestreamingStartStatus_NoSessionId = -3,
    ovrLivestreamingStartStatus_MissingParameters = -4,
} LivestreamingStartStatus;

typedef enum ovrMessageType_ {
    ovrMessage_Unknown,

    ovrMessage_Achievements_AddCount                               = 0x03E76231,
    ovrMessage_Achievements_AddFields                              = 0x14AA2129,
    ovrMessage_Achievements_GetAllDefinitions                      = 0x03D3458D,
    ovrMessage_Achievements_GetAllProgress                         = 0x4F9FDE1D,
    ovrMessage_Achievements_GetDefinitionsByName                   = 0x629101BC,
    ovrMessage_Achievements_GetNextAchievementDefinitionArrayPage  = 0x2A7DD255,
    ovrMessage_Achievements_GetNextAchievementProgressArrayPage    = 0x2F42E727,
    ovrMessage_Achievements_GetProgressByName                      = 0x152663B1,
    ovrMessage_Achievements_Unlock                                 = 0x593CCBDD,
    ovrMessage_ApplicationLifecycle_GetRegisteredPIDs              = 0x04E5CF62,
    ovrMessage_ApplicationLifecycle_GetSessionKey                  = 0x3AAF591D,
    ovrMessage_ApplicationLifecycle_RegisterSessionKey             = 0x4DB6AFF8,
    ovrMessage_Application_GetVersion                              = 0x68670A0E,
    ovrMessage_Application_LaunchOtherApp                          = 0x54E2D1F8,
    ovrMessage_AssetFile_Delete                                    = 0x6D5D7886,
    ovrMessage_AssetFile_DeleteById                                = 0x5AE8CD52,
    ovrMessage_AssetFile_DeleteByName                              = 0x420AC1CF,
    ovrMessage_AssetFile_Download                                  = 0x11449FC5,
    ovrMessage_AssetFile_DownloadById                              = 0x2D008992,
    ovrMessage_AssetFile_DownloadByName                            = 0x6336CEFA,
    ovrMessage_AssetFile_DownloadCancel                            = 0x080AD3C7,
    ovrMessage_AssetFile_DownloadCancelById                        = 0x51659514,
    ovrMessage_AssetFile_DownloadCancelByName                      = 0x446AECFA,
    ovrMessage_AssetFile_GetList                                   = 0x4AFC6F74,
    ovrMessage_AssetFile_Status                                    = 0x02D32F60,
    ovrMessage_AssetFile_StatusById                                = 0x5D955D38,
    ovrMessage_AssetFile_StatusByName                              = 0x41CFDA50,
    ovrMessage_CloudStorage2_GetUserDirectoryPath                  = 0x76A42EEE,
    ovrMessage_CloudStorage_Delete                                 = 0x28DA456D,
    ovrMessage_CloudStorage_GetNextCloudStorageMetadataArrayPage   = 0x5C07A2EF,
    ovrMessage_CloudStorage_Load                                   = 0x40846B41,
    ovrMessage_CloudStorage_LoadBucketMetadata                     = 0x7327A50D,
    ovrMessage_CloudStorage_LoadConflictMetadata                   = 0x445A52F2,
    ovrMessage_CloudStorage_LoadHandle                             = 0x326ADA36,
    ovrMessage_CloudStorage_LoadMetadata                           = 0x03E6A292,
    ovrMessage_CloudStorage_ResolveKeepLocal                       = 0x30588D05,
    ovrMessage_CloudStorage_ResolveKeepRemote                      = 0x7525A306,
    ovrMessage_CloudStorage_Save                                   = 0x4BBB5C2E,
    ovrMessage_Entitlement_GetIsViewerEntitled                     = 0x186B58B1,
    ovrMessage_IAP_ConsumePurchase                                 = 0x1FBB72D9,
    ovrMessage_IAP_GetNextProductArrayPage                         = 0x1BD94AAF,
    ovrMessage_IAP_GetNextPurchaseArrayPage                        = 0x47570A95,
    ovrMessage_IAP_GetProductsBySKU                                = 0x7E9ACAF5,
    ovrMessage_IAP_GetViewerPurchases                              = 0x3A0F8419,
    ovrMessage_IAP_GetViewerPurchasesDurableCache                  = 0x63599E2B,
    ovrMessage_IAP_LaunchCheckoutFlow                              = 0x3F9B0D0D,
    ovrMessage_LanguagePack_GetCurrent                             = 0x1F90F0D5,
    ovrMessage_LanguagePack_SetCurrent                             = 0x5B4FBBE0,
    ovrMessage_Leaderboard_GetEntries                              = 0x5DB3474C,
    ovrMessage_Leaderboard_GetEntriesAfterRank                     = 0x18378BEF,
    ovrMessage_Leaderboard_GetEntriesByIds                         = 0x39607BFC,
    ovrMessage_Leaderboard_GetNextEntries                          = 0x4E207CD9,
    ovrMessage_Leaderboard_GetPreviousEntries                      = 0x4901DAC0,
    ovrMessage_Leaderboard_WriteEntry                              = 0x117FC8FE,
    ovrMessage_Livestreaming_GetStatus                             = 0x489A6995,
    ovrMessage_Livestreaming_PauseStream                           = 0x369C7683,
    ovrMessage_Livestreaming_ResumeStream                          = 0x22526D8F,
    ovrMessage_Matchmaking_Browse                                  = 0x1E6532C8,
    ovrMessage_Matchmaking_Browse2                                 = 0x66429E5B,
    ovrMessage_Matchmaking_Cancel                                  = 0x206849AF,
    ovrMessage_Matchmaking_Cancel2                                 = 0x10FE8DD4,
    ovrMessage_Matchmaking_CreateAndEnqueueRoom                    = 0x604C5DC8,
    ovrMessage_Matchmaking_CreateAndEnqueueRoom2                   = 0x295BEADB,
    ovrMessage_Matchmaking_CreateRoom                              = 0x033B132A,
    ovrMessage_Matchmaking_CreateRoom2                             = 0x496DA384,
    ovrMessage_Matchmaking_Enqueue                                 = 0x40C16C71,
    ovrMessage_Matchmaking_Enqueue2                                = 0x121212B5,
    ovrMessage_Matchmaking_EnqueueRoom                             = 0x708A4064,
    ovrMessage_Matchmaking_EnqueueRoom2                            = 0x5528DBA4,
    ovrMessage_Matchmaking_GetAdminSnapshot                        = 0x3C215F94,
    ovrMessage_Matchmaking_GetStats                                = 0x42FC9438,
    ovrMessage_Matchmaking_JoinRoom                                = 0x4D32D7FD,
    ovrMessage_Matchmaking_ReportResultInsecure                    = 0x1A36D18D,
    ovrMessage_Matchmaking_StartMatch                              = 0x44D40945,
    ovrMessage_Media_ShareToFacebook                               = 0x00E38AEF,
    ovrMessage_Notification_GetNextRoomInviteNotificationArrayPage = 0x0621FB77,
    ovrMessage_Notification_GetRoomInvites                         = 0x6F916B92,
    ovrMessage_Notification_MarkAsRead                             = 0x717259E3,
    ovrMessage_Party_GetCurrent                                    = 0x47933760,
    ovrMessage_RichPresence_Clear                                  = 0x57B752B3,
    ovrMessage_RichPresence_GetDestinations                        = 0x586F2D14,
    ovrMessage_RichPresence_GetNextDestinationArrayPage            = 0x67367F45,
    ovrMessage_RichPresence_Set                                    = 0x3C147509,
    ovrMessage_Room_CreateAndJoinPrivate                           = 0x75D6E377,
    ovrMessage_Room_CreateAndJoinPrivate2                          = 0x5A3A6243,
    ovrMessage_Room_Get                                            = 0x659A8FB8,
    ovrMessage_Room_GetCurrent                                     = 0x09A6A504,
    ovrMessage_Room_GetCurrentForUser                              = 0x0E0017E5,
    ovrMessage_Room_GetInvitableUsers                              = 0x1E325792,
    ovrMessage_Room_GetInvitableUsers2                             = 0x4F53E8B0,
    ovrMessage_Room_GetModeratedRooms                              = 0x0983FD77,
    ovrMessage_Room_GetNextRoomArrayPage                           = 0x4E8379C6,
    ovrMessage_Room_InviteUser                                     = 0x4129EC13,
    ovrMessage_Room_Join                                           = 0x16CA8F09,
    ovrMessage_Room_Join2                                          = 0x4DAB1C42,
    ovrMessage_Room_KickUser                                       = 0x49835736,
    ovrMessage_Room_LaunchInvitableUserFlow                        = 0x323FE273,
    ovrMessage_Room_Leave                                          = 0x72382475,
    ovrMessage_Room_SetDescription                                 = 0x3044852F,
    ovrMessage_Room_UpdateDataStore                                = 0x026E4028,
    ovrMessage_Room_UpdateMembershipLockStatus                     = 0x370BB7AC,
    ovrMessage_Room_UpdateOwner                                    = 0x32B63D1D,
    ovrMessage_Room_UpdatePrivateRoomJoinPolicy                    = 0x1141029B,
    ovrMessage_User_Get                                            = 0x6BCF9E47,
    ovrMessage_User_GetAccessToken                                 = 0x06A85ABE,
    ovrMessage_User_GetLoggedInUser                                = 0x436F345D,
    ovrMessage_User_GetLoggedInUserFriends                         = 0x587C2A8D,
    ovrMessage_User_GetLoggedInUserFriendsAndRooms                 = 0x5E870B87,
    ovrMessage_User_GetLoggedInUserRecentlyMetUsersAndRooms        = 0x295FBA30,
    ovrMessage_User_GetNextUserAndRoomArrayPage                    = 0x7FBDD2DF,
    ovrMessage_User_GetNextUserArrayPage                           = 0x267CF743,
    ovrMessage_User_GetOrgScopedID                                 = 0x18F0B01B,
    ovrMessage_User_GetSdkAccounts                                 = 0x67526A83,
    ovrMessage_User_GetUserProof                                   = 0x22810483,
    ovrMessage_User_LaunchFriendRequestFlow                        = 0x0904B598,
    ovrMessage_User_LaunchProfile                                  = 0x0A397297,
    ovrMessage_Voip_SetSystemVoipSuppressed                        = 0x453FC9AA,
    ovrMessage_Notification_ApplicationLifecycle_LaunchIntentChanged = 0x04B34CA3,
    ovrMessage_Notification_AssetFile_DownloadUpdate = 0x2FDD0CCD,
    ovrMessage_Notification_Cal_FinalizeApplication = 0x750C5099,
    ovrMessage_Notification_Cal_ProposeApplication = 0x2E7451F5,
    ovrMessage_Notification_HTTP_Transfer = 0x7DD46E2F,
    ovrMessage_Notification_Livestreaming_StatusChange = 0x2247596E,
    ovrMessage_Notification_Matchmaking_MatchFound = 0x0BC3FCD7,
    ovrMessage_Notification_NetSync_ConnectionStatusChanged = 0x073484CA,
    ovrMessage_Notification_NetSync_SessionsChanged = 0x387E7F36,
    ovrMessage_Notification_Networking_ConnectionStateChange = 0x5E02D49A,
    ovrMessage_Notification_Networking_PeerConnectRequest = 0x4D31E2CF,
    ovrMessage_Notification_Networking_PingResult = 0x51153012,
    ovrMessage_Notification_Party_PartyUpdate = 0x1D118AB2,
    ovrMessage_Notification_Room_InviteAccepted = 0x6D1071B1,
    ovrMessage_Notification_Room_InviteReceived = 0x6A499D54,
    ovrMessage_Notification_Room_RoomUpdate = 0x60EC3C2F,
    ovrMessage_Notification_Voip_ConnectRequest = 0x36243816,
    ovrMessage_Notification_Voip_StateChange = 0x34EFA660,
    ovrMessage_Notification_Voip_SystemVoipState = 0x58D254A5,
    ovrMessage_PlatformInitializeWithAccessToken = 0x35692F2B,
    ovrMessage_Platform_InitializeStandaloneOculus = 0x51F8CE0C,
    ovrMessage_PlatformInitializeAndroidAsynchronous = 0x1AD307B4,
    ovrMessage_PlatformInitializeWindowsAsynchronous = 0x6DA7BA8F,
} OvrMessageType;

typedef enum ovrNetSyncDisconnectReason_ {
    ovrNetSyncDisconnectReason_Unknown,
    ovrNetSyncDisconnectReason_LocalTerminated,
    ovrNetSyncDisconnectReason_ServerTerminated,
    ovrNetSyncDisconnectReason_Failed,
    ovrNetSyncDisconnectReason_Lost,
} NetSyncDisconnectReason;


typedef enum ovrNetSyncConnectionStatus_ {
    ovrNetSyncConnectionStatus_Unknown,
    ovrNetSyncConnectionStatus_Connecting,
    ovrNetSyncConnectionStatus_Disconnected,
    ovrNetSyncConnectionStatus_Connected,
} NetSyncConnectionStatus;

typedef enum ovrPeerConnectionState_ {
    ovrPeerState_Unknown,
    ovrPeerState_Connected,
    ovrPeerState_Timeout,
    ovrPeerState_Closed,
} PeerConnectionState;

typedef enum ovrPartyUpdateAction_ {
    ovrPartyUpdateAction_Unknown,
    ovrPartyUpdateAction_Join,
    ovrPartyUpdateAction_Leave,
    ovrPartyUpdateAction_Invite,
    ovrPartyUpdateAction_Uninvite,
} PartyUpdateAction;

typedef enum ovrPlatformInitializeResult_ {
    ovrPlatformInitialize_Success = 0,
    ovrPlatformInitialize_Uninitialized = -1,
    ovrPlatformInitialize_PreLoaded = -2,
    ovrPlatformInitialize_FileInvalid = -3,
    ovrPlatformInitialize_SignatureInvalid = -4,
    ovrPlatformInitialize_UnableToVerify = -5,
    ovrPlatformInitialize_VersionMismatch = -6,
    ovrPlatformInitialize_Unknown = -7,
    ovrPlatformInitialize_InvalidCredentials = -8,
    ovrPlatformInitialize_NotEntitled = -9,
} PlatformInitializeResult;

typedef enum ovrRoomJoinability_ {
    ovrRoom_JoinabilityUnknown,
    ovrRoom_JoinabilityAreIn,
    ovrRoom_JoinabilityAreKicked,
    ovrRoom_JoinabilityCanJoin,
    ovrRoom_JoinabilityIsFull,
    ovrRoom_JoinabilityNoViewer,
    ovrRoom_JoinabilityPolicyPrevents,
} RoomJoinability;


typedef enum ovrRoomType_ {
    ovrRoom_TypeUnknown,
    ovrRoom_TypeMatchmaking,
    ovrRoom_TypeModerated,
    ovrRoom_TypePrivate,
    ovrRoom_TypeSolo,
} RoomType;

typedef enum ovrSdkAccountType_ {
    ovrSdkAccountType_Unknown,
    ovrSdkAccountType_Oculus,
    ovrSdkAccountType_FacebookGameroom,
} SdkAccountType;

typedef enum ovrShareMediaStatus_ {
    ovrShareMediaStatus_Unknown,
    ovrShareMediaStatus_Shared,
    ovrShareMediaStatus_Canceled,
} ShareMediaStatus;

typedef enum ovrUserPresenceStatus_ {
    ovrUserPresenceStatus_Unknown,
    ovrUserPresenceStatus_Online,
    ovrUserPresenceStatus_Offline,
} UserPresenceStatus;

typedef enum ovrAbuseReportType_ {
    ovrAbuseReportType_Unknown,
    ovrAbuseReportType_Object,
    ovrAbuseReportType_User,
} AbuseReportType;

typedef enum AbuseReportVideoMode_
{
    AbuseReportVideoMode_Unknown,
    Collect,
    Optional,
    Skip,
} AbuseReportVideoMode;

typedef enum ChallengeViewerFilter_
{
    ChallengeViewerFilter_Unknown,
    AllVisible,
    Participating,
    Invited,
    ParticipatingOrInvited,
} ChallengeViewerFilter;

typedef enum MultiplayerErrorErrorKey_
{
    MultiplayerErrorErrorKey_Unknown,
    DestinationUnavailable,
    DlcRequired,
    General,
    GroupFull,
    InviterNotJoinable,
    LevelNotHighEnough,
    LevelNotUnlocked,
    NetworkTimeout,
    NoLongerAvailable,
    UpdateRequired,
    TutorialRequired,

} MultiplayerErrorErrorKey;


typedef enum RichPresenceExtraContext_
{
    RichPresenceExtraContext_Unknown,
    None,
    CurrentCapacity,
    StartedAgo,
    EndingIn,
    LookingForAMatch,
} RichPresenceExtraContext;

typedef enum UserOrdering_
{
    UserOrdering_Unknown,
    UserOrdering_none,
    PresenceAlphabetical,

} UserOrdering;

typedef enum TimeWindow
{
    TimeWindow_Unknown,
    OneHour,
    OneDay,
    OneWeek,
    ThirtyDays,
    NinetyDays,

} TimeWindow;

typedef enum MessageType_
{ //TODO - rename this to type; it's already in Message class
    MessageType_Unknown,

    AbuseReport_ReportRequestHandled                   = 0x4B8EFC86,
    Achievements_AddCount                              = 0x03E76231,
    Achievements_AddFields                             = 0x14AA2129,
    Achievements_GetAllDefinitions                     = 0x03D3458D,
    Achievements_GetAllProgress                        = 0x4F9FDE1D,
    Achievements_GetDefinitionsByName                  = 0x629101BC,
    Achievements_GetNextAchievementDefinitionArrayPage = 0x2A7DD255,
    Achievements_GetNextAchievementProgressArrayPage   = 0x2F42E727,
    Achievements_GetProgressByName                     = 0x152663B1,
    Achievements_Unlock                                = 0x593CCBDD,
    ApplicationLifecycle_GetRegisteredPIDs             = 0x04E5CF62,
    ApplicationLifecycle_GetSessionKey                 = 0x3AAF591D,
    ApplicationLifecycle_RegisterSessionKey            = 0x4DB6AFF8,
    Application_CancelAppDownload                      = 0x7C2060DE,
    Application_CheckAppDownloadProgress               = 0x5534A924,
    Application_GetVersion                             = 0x68670A0E,
    Application_InstallAppUpdateAndRelaunch            = 0x14806B85,
    Application_LaunchOtherApp                         = 0x54E2D1F8,
    Application_StartAppDownload                       = 0x44FC006E,
    AssetFile_Delete                                   = 0x6D5D7886,
    AssetFile_DeleteById                               = 0x5AE8CD52,
    AssetFile_DeleteByName                             = 0x420AC1CF,
    AssetFile_Download                                 = 0x11449FC5,
    AssetFile_DownloadById                             = 0x2D008992,
    AssetFile_DownloadByName                           = 0x6336CEFA,
    AssetFile_DownloadCancel                           = 0x080AD3C7,
    AssetFile_DownloadCancelById                       = 0x51659514,
    AssetFile_DownloadCancelByName                     = 0x446AECFA,
    AssetFile_GetList                                  = 0x4AFC6F74,
    AssetFile_Status                                   = 0x02D32F60,
    AssetFile_StatusById                               = 0x5D955D38,
    AssetFile_StatusByName                             = 0x41CFDA50,
    Avatar_LaunchAvatarEditor                          = 0x05F1E153,
    Challenges_Create                                  = 0x6859D641,
    Challenges_DeclineInvite                           = 0x568E76C0,
    Challenges_Delete                                  = 0x264885CA,
    Challenges_Get                                     = 0x77584EF3,
    Challenges_GetEntries                              = 0x121AB45F,
    Challenges_GetEntriesAfterRank                     = 0x08891A7F,
    Challenges_GetEntriesByIds                         = 0x316509DC,
    Challenges_GetList                                 = 0x43264356,
    Challenges_GetNextChallenges                       = 0x5B7CA1B6,
    Challenges_GetNextEntries                          = 0x7F4CA0C6,
    Challenges_GetPreviousChallenges                   = 0x0EB4040D,
    Challenges_GetPreviousEntries                      = 0x78C90470,
    Challenges_Join                                    = 0x21248069,
    Challenges_Leave                                   = 0x296116E5,
    Challenges_UpdateInfo                              = 0x1175BE60,
    DeviceApplicationIntegrity_GetIntegrityToken       = 0x3271ABDA,
    Entitlement_GetIsViewerEntitled                    = 0x186B58B1,
    GroupPresence_Clear                                = 0x6DAA9CC3,
    GroupPresence_GetInvitableUsers                    = 0x234BC3F1,
    GroupPresence_GetNextApplicationInviteArrayPage    = 0x04F8C0F2,
    GroupPresence_GetSentInvites                       = 0x08260AB1,
    GroupPresence_LaunchInvitePanel                    = 0x0F9ECF9F,
    GroupPresence_LaunchMultiplayerErrorDialog         = 0x2955AF24,
    GroupPresence_LaunchRejoinDialog                   = 0x1577036F,
    GroupPresence_LaunchRosterPanel                    = 0x35728882,
    GroupPresence_SendInvites                          = 0x0DCBD364,
    GroupPresence_Set                                  = 0x675F5C24,
    GroupPresence_SetDeeplinkMessageOverride           = 0x521ADF0D,
    GroupPresence_SetDestination                       = 0x4C5B268A,
    GroupPresence_SetIsJoinable                        = 0x2A8F1055,
    GroupPresence_SetLobbySession                      = 0x48FF55BE,
    GroupPresence_SetMatchSession                      = 0x314C84B8,
    IAP_ConsumePurchase                                = 0x1FBB72D9,
    IAP_GetNextProductArrayPage                        = 0x1BD94AAF,
    IAP_GetNextPurchaseArrayPage                       = 0x47570A95,
    IAP_GetProductsBySKU                               = 0x7E9ACAF5,
    IAP_GetViewerPurchases                             = 0x3A0F8419,
    IAP_GetViewerPurchasesDurableCache                 = 0x63599E2B,
    IAP_LaunchCheckoutFlow                             = 0x3F9B0D0D,
    LanguagePack_GetCurrent                            = 0x1F90F0D5,
    LanguagePack_SetCurrent                            = 0x5B4FBBE0,
    Leaderboard_Get                                    = 0x6AD44EF8,
    Leaderboard_GetEntries                             = 0x5DB3474C,
    Leaderboard_GetEntriesAfterRank                    = 0x18378BEF,
    Leaderboard_GetEntriesByIds                        = 0x39607BFC,
    Leaderboard_GetNextEntries                         = 0x4E207CD9,
    Leaderboard_GetNextLeaderboardArrayPage            = 0x35F6769B,
    Leaderboard_GetPreviousEntries                     = 0x4901DAC0,
    Leaderboard_WriteEntry                             = 0x117FC8FE,
    Leaderboard_WriteEntryWithSupplementaryMetric      = 0x72C692FA,
    Media_ShareToFacebook                              = 0x00E38AEF,
    Notification_MarkAsRead                            = 0x717259E3,
    Party_GetCurrent                                   = 0x47933760,
    RichPresence_Clear                                 = 0x57B752B3,
    RichPresence_GetDestinations                       = 0x586F2D14,
    RichPresence_GetNextDestinationArrayPage           = 0x67367F45,
    RichPresence_Set                                   = 0x3C147509,
    UserAgeCategory_Get                                = 0x21CBE0C0,
    UserAgeCategory_Report                             = 0x2E4DD8D6,
    UserDataStore_PrivateDeleteEntryByKey              = 0x5C896F3E,
    UserDataStore_PrivateGetEntries                    = 0x6C8A8228,
    UserDataStore_PrivateGetEntryByKey                 = 0x1C068319,
    UserDataStore_PrivateWriteEntry                    = 0x41D2828B,
    UserDataStore_PublicDeleteEntryByKey               = 0x1DD5E5FB,
    UserDataStore_PublicGetEntries                     = 0x167D4BC2,
    UserDataStore_PublicGetEntryByKey                  = 0x195C66C6,
    UserDataStore_PublicWriteEntry                     = 0x34364A0A,
    User_Get                                           = 0x6BCF9E47,
    User_GetAccessToken                                = 0x06A85ABE,
    User_GetBlockedUsers                               = 0x7D201556,
    User_GetLoggedInUser                               = 0x436F345D,
    User_GetLoggedInUserFriends                        = 0x587C2A8D,
    User_GetNextBlockedUserArrayPage                   = 0x7C2AFDCB,
    User_GetNextUserArrayPage                          = 0x267CF743,
    User_GetNextUserCapabilityArrayPage                = 0x2309F399,
    User_GetOrgScopedID                                = 0x18F0B01B,
    User_GetSdkAccounts                                = 0x67526A83,
    User_GetUserProof                                  = 0x22810483,
    User_LaunchBlockFlow                               = 0x6FD62528,
    User_LaunchFriendRequestFlow                       = 0x0904B598,
    User_LaunchUnblockFlow                             = 0x14A22A97,
    Voip_GetMicrophoneAvailability                     = 0x744CE345,
    Voip_SetSystemVoipSuppressed                       = 0x453FC9AA,

    /// The user has tapped the report button in the panel that appears after
    /// pressing the Oculus button.
    Notification_AbuseReport_ReportButtonPressed = 0x24472F6C,

    /// Sent when a launch intent is received (for both cold and warm starts). The
    /// payload is the type of the intent. ApplicationLifecycle.GetLaunchDetails()
    /// should be called to get the other details.
    Notification_ApplicationLifecycle_LaunchIntentChanged = 0x04B34CA3,

    /// Sent to indicate download progress for asset files.
    Notification_AssetFile_DownloadUpdate = 0x2FDD0CCD,

    /// Sent when the user is finished using the invite panel to send out
    /// invitations. Contains a list of invitees.
    Notification_GroupPresence_InvitationsSent = 0x679A84B6,

    /// Sent when a user has chosen to join the destination/lobby/match. Read all
    /// the fields to figure out where the user wants to go and take the
    /// appropriate actions to bring them there. If the user is unable to go there,
    /// provide adequate messaging to the user on why they cannot go there. These
    /// notifications should be responded to immediately.
    Notification_GroupPresence_JoinIntentReceived = 0x773889F6,

    /// Sent when the user has chosen to leave the destination/lobby/match from the
    /// Oculus menu. Read the specific fields to check the user is currently from
    /// the destination/lobby/match and take the appropriate actions to remove
    /// them. Update the user's presence clearing the appropriate fields to
    /// indicate the user has left.
    Notification_GroupPresence_LeaveIntentReceived = 0x4737EA1D,

    /// Sent to indicate that more data has been read or an error occured.
    Notification_HTTP_Transfer = 0x7DD46E2F,

    /// Indicates that the livestreaming session has been updated. You can use this
    /// information to throttle your game performance or increase CPU/GPU
    /// performance. Use Message.GetLivestreamingStatus() to extract the updated
    /// livestreaming status.
    Notification_Livestreaming_StatusChange = 0x2247596E,

    /// Sent when the status of a connection has changed.
    Notification_NetSync_ConnectionStatusChanged = 0x073484CA,

    /// Sent when the list of known connected sessions has changed. Contains the
    /// new list of sessions.
    Notification_NetSync_SessionsChanged = 0x387E7F36,

    /// Indicates that party has been updated
    Notification_Party_PartyUpdate = 0x1D118AB2,

    /// Indicates that the current microphone availability state has been updated.
    /// Use Voip.GetMicrophoneAvailability() to extract the microphone availability
    /// state.
    Notification_Voip_MicrophoneAvailabilityStateUpdate = 0x3E20CB57,

    /// Sent to indicate that some part of the overall state of SystemVoip has
    /// changed. Use Message.GetSystemVoipState() and the properties of
    /// SystemVoipState to extract the state that triggered the notification.
    ///
    /// Note that the state may have changed further since the notification was
    /// generated, and that you may call the `GetSystemVoip...()` family of
    /// functions at any time to get the current state directly.
    Notification_Voip_SystemVoipState = 0x58D254A5,

    /// Get vr camera related webrtc data channel messages for update.
    Notification_Vrcamera_GetDataChannelMessageUpdate = 0x6EE4F33C,

    /// Get surface and update action from platform webrtc for update.
    Notification_Vrcamera_GetSurfaceUpdate = 0x37F21084,


    Platform_InitializeWithAccessToken = 0x35692F2B,
    Platform_InitializeStandaloneOculus = 0x51F8CE0C,
    Platform_InitializeAndroidAsynchronous = 0x1AD307B4,
    Platform_InitializeWindowsAsynchronous = 0x6DA7BA8F,
} MessageType;

typedef enum AccountAgeCategory_
{
    AccountAgeCategory_Unknown,
    Ch,
    Tn,
    Ad,
} AccountAgeCategory;


typedef struct ovrUserAndRoomArrayHandle_
{} ovrUserAndRoomArrayHandle;

typedef struct ovrUserArrayHandle_
{} ovrUserArrayHandle;

typedef struct ovrCloudStorageMetadataArrayHandle_
{} ovrCloudStorageMetadataArrayHandle;

/// A unique identifier for some entity in the system (user, room, etc).
///
typedef uint64_t ovrID;
typedef uint64_t ovrRequest;

typedef enum ovrPlatformInitializeResult2_ {
    ovrPlatformInitializeResult__Success = 0,
    ovrPlatformInitializeResult__Uninitialized = -1,
    ovrPlatformInitializeResult__PreLoaded = -2,
    ovrPlatformInitializeResult__FileInvalid = -3,
    ovrPlatformInitializeResult__SignatureInvalid = -4,
    ovrPlatformInitializeResult__UnableToVerify = -5,
    ovrPlatformInitializeResult__VersionMismatch = -6,
    ovrPlatformInitializeResult__Unknown = -7,
    ovrPlatformInitializeResult__InvalidCredentials = -8,
    ovrPlatformInitializeResult_ovrPlatformInitialize_NotEntitled = -9,
} ovrPlatformInitializeResult;


#endif