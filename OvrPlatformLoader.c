#include <stdio.h>
#include <stdbool.h>
#include <inttypes.h>
#include <time.h>
#include <math.h>
#include <android/log.h>

#include "OvrPlatformLoader.h"
#include "/include/PxrPlugin.h"
#include "/include/PxrPlatformLoader.h"
#include "/include/Globals.h"

//My soul...

// Initialization

bool ovr_UnityInitWrapper(char *appId) {
    __android_log_print(ANDROID_LOG_INFO, PLUGIN_NAME, "%s was called!", __func__);
    return ppf_UnityInitWrapper(appId) == ppfPlatformInitializeResult_Success;
}

// Initializes just the global variables to use the Unity api without calling the init logic

void ovr_UnityInitGlobals(intptr_t loggingCB) {
    __android_log_print(ANDROID_LOG_INFO, PLUGIN_NAME, "%s called!", __func__ );
    return;
}
unsigned long ovr_UnityInitWrapperAsynchronous(char *appId) {
    __android_log_print(ANDROID_LOG_INFO, PLUGIN_NAME, "%s was called!", __func__);
    ppf_UnityInitAsynchronousWrapper(appId);
    return 0x1AD307B4; //Platform_InitializeAndroidAsynchronous, not sure if I can just return what ppf_UnityInitAsynchronousWrapper outputs.
}
bool ovr_UnityInitWrapperStandalone(char *accessToken, intptr_t loggingCB) {
    __android_log_print(ANDROID_LOG_INFO, PLUGIN_NAME, "%s called! But not implemented!", __func__);
    return ppf_UnityInitWrapper("0") == ppfPlatformInitializeResult_Success;
}
unsigned long ovr_Platform_InitializeStandaloneOculus(OculusInitParams* init) {
    __android_log_print(ANDROID_LOG_INFO, PLUGIN_NAME, "%s called! But not implemented!", __func__);
    ppf_UnityInitWrapper("0");
    return 0x1AD307B4;
}
unsigned long ovr_PlatformInitializeWithAccessToken(uint64_t appId, char *accessToken) {
    __android_log_print(ANDROID_LOG_INFO, PLUGIN_NAME, "%s called! But not implemented!", __func__);
    ppf_UnityInitWrapper("0");
    return 0x1AD307B4;
}
unsigned long ovr_PlatformInitializeWithAccessTokenAndOptions(uint64_t appId, char *accessToken, ovrKeyValuePair configOptions[], uintptr_t numOptions) {
    __android_log_print(ANDROID_LOG_INFO, PLUGIN_NAME, "%s called! But not implemented!", __func__);
    ppf_UnityInitWrapper((char *)&appId);
    return 0x1AD307B4;
}

//We are NOT on Windows!
bool ovr_UnityInitWrapperWindows(char *appId, intptr_t loggingCB) {
    return 0;
}
unsigned long ovr_UnityInitWrapperWindowsAsynchronous(char *appId, intptr_t loggingCB) {
    return 0x1AD307B4;
}

bool ovr_SetDeveloperAccessToken(char *accessToken) {
    return true;
}
intptr_t ovr_GetLoggedInUserLocale() {
    return 0;
}


// Message queue access

intptr_t ovr_PopMessage() {
    return 0;
}
void ovr_FreeMessage(intptr_t message) {
    return;
}

// VOIP

intptr_t ovr_Voip_CreateEncoder() {
    return 0;
}
void ovr_Voip_DestroyEncoder(intptr_t encoder) {
    return;
}
intptr_t ovr_Voip_CreateDecoder() {
    return 0;
}
void ovr_Voip_DestroyDecoder(intptr_t decoder) {
    return;
}
intptr_t ovr_Microphone_Create() {
    return 0;
}
void ovr_Microphone_Destroy(intptr_t obj) {
    return;
}
void ovr_Voip_SetSystemVoipPassthrough(bool passthrough) {
    return;
}
void ovr_Voip_SetSystemVoipMicrophoneMuted(enum VoipMuteState muted) {
    return;
}

// Misc

void ovr_UnityResetTestPlatform() {
    return;
}
unsigned long ovr_HTTP_GetWithMessageType(char *url, int messageType) {
    return 0;
}
void ovr_CrashApplication() {
    Pxr_Shutdown();
}
void ovr_Voip_SetMicrophoneFilterCallback(FilterCallback cb) {
    return;
}
void ovr_Voip_SetMicrophoneFilterCallbackWithFixedSizeBuffer(FilterCallback cb, uintptr_t bufferSizeElements) {
    return;
}

// Logging

void ovr_Log_NewEvent(intptr_t eventName, intptr_t *values, uintptr_t length) {
    __android_log_print(ANDROID_LOG_INFO, PLUGIN_NAME, "OVR Log: event: %ld, ", eventName);
    return;
}
intptr_t ovr_ApplicationLifecycle_GetLaunchDetails() {
    return 0;
}
void ovr_ApplicationLifecycle_LogDeeplinkResult(intptr_t trackingID, LaunchResult result) {
    return;
}

// Other?

unsigned long ovr_HTTP_StartTransfer(intptr_t url, ovrKeyValuePair headers[], uintptr_t numItems) {
    return 0;
}
bool ovr_HTTP_Write(unsigned long transferId, uint8_t *bytes, uintptr_t length) {
    return 0;
}
void ovr_HTTP_WriteEOM(unsigned long transferId) {
    return;
}
intptr_t ovr_Message_GetStringForJavascript(intptr_t message) {
    return 0;
}
uintptr_t ovr_NetSync_GetAmbisonicFloatPCM(long connection_id, float *outputBuffer, uintptr_t outputBufferNumElements) {
    return 0;
}
uintptr_t ovr_NetSync_GetAmbisonicInt16PCM(long connection_id, uint16_t *outputBuffer, uintptr_t outputBufferNumElements) {
    return 0;
}
uintptr_t ovr_NetSync_GetAmbisonicInterleavedFloatPCM(long connection_id, float *outputBuffer, uintptr_t outputBufferNumElements) {
    return 0;
}
uintptr_t ovr_NetSync_GetAmbisonicInterleavedInt16PCM(long connection_id, uint16_t *outputBuffer, uintptr_t outputBufferNumElements) {
    return 0;
}
bool ovr_NetSync_GetListenerPosition(long connection_id, uint64_t sessionId, ovrNetSyncVec3 *position) {
    return 0;
}
uintptr_t ovr_NetSync_GetMonostreamFloatPCM(long connection_id, uint64_t sessionId, float *outputBuffer, uintptr_t outputBufferNumElements) {
    return 0;
}
uintptr_t ovr_NetSync_GetMonostreamInt16PCM(long connection_id, uint64_t session_id, uint16_t *outputBuffer, uintptr_t outputBufferNumElements) {
    return 0;
}
uintptr_t ovr_NetSync_GetPcmBufferMaxSamples() {
    return 0;
}
bool ovr_NetSync_GetVoipAmplitude(long connection_id, uint64_t sessionId, float *amplitude) {
    return 0;
}
void ovr_NetSync_SetListenerPosition(long connection_id, ovrNetSyncVec3 *position) {
    return;
}
void ovr_Net_Accept(uint64_t peerID) {
    return;
}
bool ovr_Net_AcceptForCurrentRoom() {
    return 0;
}
void ovr_Net_Close(uint64_t peerID) {
    return;
}
void ovr_Net_CloseForCurrentRoom() {
    return;
}
void ovr_Net_Connect(uint64_t peerID) {
    return;
}
bool ovr_Net_IsConnected(uint64_t peerID) {
    return 0;
}
unsigned long ovr_Net_Ping(uint64_t peerID) {
    return 0;
}
intptr_t ovr_Net_ReadPacket() {
    return 0;
}
bool ovr_Net_SendPacket(uint64_t userID, uintptr_t length, uint8_t *bytes, SendPolicy policy) {
    return 0;
}
bool ovr_Net_SendPacketToCurrentRoom(uintptr_t length, uint8_t *bytes, SendPolicy policy) {
    return 0;
}
int ovr_Party_PluginGetSharedMemHandle() {
    return 0;
}
enum VoipMuteState ovr_Party_PluginGetVoipMicrophoneMuted() {
    return 0;
}
bool ovr_Party_PluginGetVoipPassthrough() {
    return 0;
}
SystemVoipStatus ovr_Party_PluginGetVoipStatus() {
    return 0;
}
void ovr_Voip_Accept(uint64_t userID) {
    return;
}
VoipDtxState ovr_Voip_GetIsConnectionUsingDtx(uint64_t peerID) {
    return 0;
}
VoipBitrate ovr_Voip_GetLocalBitrate(uint64_t peerID) {
    return 0;
}
uintptr_t ovr_Voip_GetOutputBufferMaxSize() {
    return 0;
}
uintptr_t ovr_Voip_GetPCM(uint64_t senderID, uint16_t *outputBuffer, uintptr_t outputBufferNumElements) {
    return 0;
}
uintptr_t ovr_Voip_GetPCMFloat(uint64_t senderID, float *outputBuffer, uintptr_t outputBufferNumElements) {
    return 0;
}
uintptr_t ovr_Voip_GetPCMSize(uint64_t senderID) {
    return 0;
}
uintptr_t ovr_Voip_GetPCMWithTimestamp(uint64_t senderID, uint16_t *outputBuffer, uintptr_t outputBufferNumElements, uint32_t *timestamp) {
    return 0;
}
uintptr_t ovr_Voip_GetPCMWithTimestampFloat(uint64_t senderID, float *outputBuffer, uintptr_t outputBufferNumElements, uint32_t *timestamp) {
    return 0;
}
VoipBitrate ovr_Voip_GetRemoteBitrate(uint64_t peerID) {
    return 0;
}
uint32_t ovr_Voip_GetSyncTimestamp(uint64_t userID) {
    return 0;
}
long ovr_Voip_GetSyncTimestampDifference(uint32_t lhs, uint32_t rhs) {
    return 0;
}
enum VoipMuteState ovr_Voip_GetSystemVoipMicrophoneMuted() {
    return 0;
}
SystemVoipStatus ovr_Voip_GetSystemVoipStatus() {
    return 0;
}
void ovr_Voip_SetMicrophoneMuted(enum VoipMuteState state) {
    return;
}
void ovr_Voip_SetNewConnectionOptions(intptr_t voipOptions) {
    return;
}
void ovr_Voip_SetOutputSampleRate(VoipSampleRate rate) {
    return;
}
void ovr_Voip_Start(uint64_t userID) {
    return;
}
void ovr_Voip_Stop(uint64_t userID) {
    return;
}
unsigned long ovr_AbuseReport_LaunchAdvancedReportFlow(uint64_t content_id, intptr_t abuse_report_options) {
    return 0;
}
unsigned long ovr_AbuseReport_ReportRequestHandled(ReportRequestResponse response) {
    return 0;
}
unsigned long ovr_Achievements_AddCount(intptr_t name, unsigned long count) {
    return 0;
}
unsigned long ovr_Achievements_AddFields(intptr_t name, intptr_t fields) {
    return 0;
}
unsigned long ovr_Achievements_GetAllDefinitions() {
    return 0;
}
unsigned long ovr_Achievements_GetAllProgress() {
    return 0;
}
unsigned long ovr_Achievements_GetDefinitionsByName(char *names, int count) {
    return 0;
}
unsigned long ovr_Achievements_GetProgressByName(char *names, int count) {
    return 0;
}
unsigned long ovr_Achievements_Unlock(intptr_t name) {
    return 0;
}
unsigned long ovr_Application_ExecuteCoordinatedLaunch(unsigned long appID, unsigned long roomID) {
    return 0;
}
unsigned long ovr_Application_GetInstalledApplications() {
    return 0;
}
unsigned long ovr_Application_GetVersion() {
    return 0;
}
unsigned long ovr_Application_LaunchOtherApp(uint64_t appID, intptr_t deeplink_options) {
    return 0;
}
unsigned long ovr_ApplicationLifecycle_GetRegisteredPIDs() {
    return 0;
}
unsigned long ovr_ApplicationLifecycle_GetSessionKey() {
    return 0;
}
unsigned long ovr_ApplicationLifecycle_RegisterSessionKey(intptr_t sessionKey) {
    return 0;
}
unsigned long ovr_AssetFile_Delete(uint64_t assetFileID) {
    return 0;
}
unsigned long ovr_AssetFile_DeleteById(uint64_t assetFileID) {
    return 0;
}
unsigned long ovr_AssetFile_DeleteByName(intptr_t assetFileName) {
    return 0;
}
unsigned long ovr_AssetFile_Download(uint64_t assetFileID) {
    return 0;
}
unsigned long ovr_AssetFile_DownloadById(uint64_t assetFileID) {
    return 0;
}
unsigned long ovr_AssetFile_DownloadByName(intptr_t assetFileName) {
    return 0;
}
unsigned long ovr_AssetFile_DownloadCancel(uint64_t assetFileID) {
    return 0;
}
unsigned long ovr_AssetFile_DownloadCancelById(uint64_t assetFileID) {
    return 0;
}
unsigned long ovr_AssetFile_DownloadCancelByName(intptr_t assetFileName) {
    return 0;
}
unsigned long ovr_AssetFile_GetList() {
    return 0;
}
unsigned long ovr_AssetFile_Status(uint64_t assetFileID) {
    return 0;
}
unsigned long ovr_AssetFile_StatusById(uint64_t assetFileID) {
    return 0;
}
unsigned long ovr_AssetFile_StatusByName(intptr_t assetFileName) {
    return 0;
}
unsigned long ovr_Avatar_LaunchAvatarEditor(intptr_t options) {
    return 0;
}
unsigned long ovr_Avatar_UpdateMetaData(intptr_t avatarMetaData, intptr_t imageFilePath) {
    return 0;
}
unsigned long ovr_Cal_FinalizeApplication(uint64_t groupingObject, uint64_t *userIDs, int numUserIDs, uint64_t finalized_application_ID) {
    return 0;
}
unsigned long ovr_Cal_GetSuggestedApplications(uint64_t groupingObject, uint64_t *userIDs, int numUserIDs) {
    return 0;
}
unsigned long ovr_Cal_ProposeApplication(uint64_t groupingObject, uint64_t *userIDs, int numUserIDs, uint64_t proposed_application_ID) {
    return 0;
}
unsigned long ovr_Challenges_Create(intptr_t leaderboardName, intptr_t challengeOptions) {
    return 0;
}
unsigned long ovr_Challenges_DeclineInvite(uint64_t challengeID) {
    return 0;
}
unsigned long ovr_Challenges_Delete(uint64_t challengeID) {
    return 0;
}
unsigned long ovr_Challenges_Get(uint64_t challengeID) {
    return 0;
}
unsigned long ovr_Challenges_GetEntries(uint64_t challengeID, int limit, LeaderboardFilterType filter, LeaderboardStartAt startAt) {
    return 0;
}
unsigned long ovr_Challenges_GetEntriesAfterRank(uint64_t challengeID, int limit, unsigned long afterRank) {
    return 0;
}
unsigned long ovr_Challenges_GetEntriesByIds(uint64_t challengeID, int limit, LeaderboardStartAt startAt, uint64_t *userIDs, uint userIDLength) {
    return 0;
}
unsigned long ovr_Challenges_GetList(intptr_t challengeOptions, int limit) {
    return 0;
}
unsigned long ovr_Challenges_GetNextChallenges(intptr_t handle) {
    return 0;
}
unsigned long ovr_Challenges_GetNextEntries(intptr_t handle) {
    return 0;
}
unsigned long ovr_Challenges_GetPreviousChallenges(intptr_t handle) {
    return 0;
}
unsigned long ovr_Challenges_GetPreviousEntries(intptr_t handle) {
    return 0;
}
unsigned long ovr_Challenges_Join(uint64_t challengeID) {
    return 0;
}
unsigned long ovr_Challenges_Leave(uint64_t challengeID) {
    return 0;
}
unsigned long ovr_Challenges_UpdateInfo(uint64_t challengeID, intptr_t challengeOptions) {
    return 0;
}
unsigned long ovr_CloudStorage_Delete(intptr_t bucket, intptr_t key) {
    return 0;
}
unsigned long ovr_CloudStorage_Load(intptr_t bucket, intptr_t key) {
    return 0;
}
unsigned long ovr_CloudStorage_LoadBucketMetadata(intptr_t bucket) {
    return 0;
}
unsigned long ovr_CloudStorage_LoadConflictMetadata(intptr_t bucket, intptr_t key) {
    return 0;
}
unsigned long ovr_CloudStorage_LoadHandle(intptr_t handle) {
    return 0;
}
unsigned long ovr_CloudStorage_LoadMetadata(intptr_t bucket, intptr_t key) {
    return 0;
}
unsigned long ovr_CloudStorage_ResolveKeepLocal(intptr_t bucket, intptr_t key, intptr_t remoteHandle) {
    return 0;
}
unsigned long ovr_CloudStorage_ResolveKeepRemote(intptr_t bucket, intptr_t key, intptr_t remoteHandle) {
    return 0;
}
unsigned long ovr_CloudStorage_Save(intptr_t bucket, intptr_t key, uint8_t *data, uint dataSize, long counter, intptr_t extraData) {
    return 0;
}
unsigned long ovr_CloudStorage2_GetUserDirectoryPath() {
    return 0;
}
unsigned long ovr_Colocation_GetCurrentMapUuid() {
    return 0;
}
unsigned long ovr_Colocation_RequestMap(intptr_t uuid) {
    return 0;
}
unsigned long ovr_Colocation_ShareMap(intptr_t uuid) {
    return 0;
}
unsigned long ovr_Entitlement_GetIsViewerEntitled() {
    return 0;
}
unsigned long ovr_GraphAPI_Get(intptr_t url) {
    return 0;
}
unsigned long ovr_GraphAPI_Post(intptr_t url) {
    return 0;
}
unsigned long ovr_GroupPresence_Clear() {
    return 0;
}
unsigned long ovr_GroupPresence_GetInvitableUsers(intptr_t options) {
    return 0;
}
unsigned long ovr_GroupPresence_GetSentInvites() {
    return 0;
}
unsigned long ovr_GroupPresence_LaunchInvitePanel(intptr_t options) {
    return 0;
}
unsigned long ovr_GroupPresence_LaunchMultiplayerErrorDialog(intptr_t options) {
    return 0;
}
unsigned long ovr_GroupPresence_LaunchRejoinDialog(intptr_t lobby_session_id, intptr_t match_session_id, intptr_t destination_api_name) {
    return 0;
}
unsigned long ovr_GroupPresence_LaunchRosterPanel(intptr_t options) {
    return 0;
}
unsigned long ovr_GroupPresence_SendInvites(uint64_t *userIDs, uint userIDLength) {
    return 0;
}
unsigned long ovr_GroupPresence_Set(intptr_t groupPresenceOptions) {
    return 0;
}
unsigned long ovr_GroupPresence_SetDeeplinkMessageOverride(intptr_t deeplink_message) {
    return 0;
}
unsigned long ovr_GroupPresence_SetDestination(intptr_t api_name) {
    return 0;
}
unsigned long ovr_GroupPresence_SetIsJoinable(bool is_joinable) {
    return 0;
}
unsigned long ovr_GroupPresence_SetLobbySession(intptr_t id) {
    return 0;
}
unsigned long ovr_GroupPresence_SetMatchSession(intptr_t id) {
    return 0;
}
unsigned long ovr_HTTP_Get(intptr_t url) {
    return 0;
}
unsigned long ovr_HTTP_GetToFile(intptr_t url, intptr_t diskFile) {
    return 0;
}
unsigned long ovr_HTTP_MultiPartPost(intptr_t url, intptr_t filepath_param_name, intptr_t filepath, intptr_t access_token, ovrKeyValuePair post_params[], uintptr_t numItems) {
    return 0;
}
unsigned long ovr_HTTP_Post(intptr_t url) {
    return 0;
}
unsigned long ovr_IAP_ConsumePurchase(intptr_t sku) {
    return 0;
}
unsigned long ovr_IAP_GetProductsBySKU(char *skus, int count) {
    return 0;
}
unsigned long ovr_IAP_GetViewerPurchases(bool fetchDeveloperPayload) {
    return 0;
}
unsigned long ovr_IAP_GetViewerPurchasesDurableCache() {
    return 0;
}
unsigned long ovr_IAP_LaunchCheckoutFlow(intptr_t sku) {
    return 0;
}
unsigned long ovr_LanguagePack_GetCurrent() {
    return 0;
}
unsigned long ovr_LanguagePack_SetCurrent(intptr_t tag) {
    return 0;
}
unsigned long ovr_Leaderboard_Get(intptr_t leaderboardName) {
    return 0;
}
unsigned long ovr_Leaderboard_GetEntries(intptr_t leaderboardName, int limit, LeaderboardFilterType filter, LeaderboardStartAt startAt) {
    return 0;
}
unsigned long ovr_Leaderboard_GetEntriesAfterRank(intptr_t leaderboardName, int limit, unsigned long afterRank) {
    return 0;
}
unsigned long ovr_Leaderboard_GetEntriesByIds(intptr_t leaderboardName, int limit, LeaderboardStartAt startAt, uint64_t *userIDs, uint userIDLength) {
    return 0;
}
unsigned long ovr_Leaderboard_GetNextEntries(intptr_t handle) {
    return 0;
}
unsigned long ovr_Leaderboard_GetPreviousEntries(intptr_t handle) {
    return 0;
}
unsigned long ovr_Leaderboard_WriteEntry(intptr_t leaderboardName, long score, uint8_t *extraData, uint extraDataLength, bool forceUpdate) {
    return 0;
}
unsigned long ovr_Leaderboard_WriteEntryWithSupplementaryMetric(intptr_t leaderboardName, long score, long supplementaryMetric, uint8_t *extraData, uint extraDataLength, bool forceUpdate) {
    return 0;
}
unsigned long ovr_Livestreaming_IsAllowedForApplication(intptr_t packageName) {
    return 0;
}
unsigned long ovr_Livestreaming_StartPartyStream() {
    return 0;
}
unsigned long ovr_Livestreaming_StartStream(LivestreamingAudience audience, LivestreamingMicrophoneStatus micStatus) {
    return 0;
}
unsigned long ovr_Livestreaming_StopPartyStream() {
    return 0;
}
unsigned long ovr_Livestreaming_StopStream() {
    return 0;
}
unsigned long ovr_Livestreaming_UpdateMicStatus(LivestreamingMicrophoneStatus micStatus) {
    return 0;
}
unsigned long ovr_Matchmaking_Browse(intptr_t pool, intptr_t customQueryData) {
    return 0;
}
unsigned long ovr_Matchmaking_Browse2(intptr_t pool, intptr_t matchmakingOptions) {
    return 0;
}
unsigned long ovr_Matchmaking_Cancel(intptr_t pool, intptr_t requestHash) {
    return 0;
}
unsigned long ovr_Matchmaking_Cancel2() {
    return 0;
}
unsigned long ovr_Matchmaking_CreateAndEnqueueRoom(intptr_t pool, uint maxUsers, bool subscribeToUpdates, intptr_t customQueryData) {
    return 0;
}
unsigned long ovr_Matchmaking_CreateAndEnqueueRoom2(intptr_t pool, intptr_t matchmakingOptions) {
    return 0;
}
unsigned long ovr_Matchmaking_CreateRoom(intptr_t pool, uint maxUsers, bool subscribeToUpdates) {
    return 0;
}
unsigned long ovr_Matchmaking_CreateRoom2(intptr_t pool, intptr_t matchmakingOptions) {
    return 0;
}
unsigned long ovr_Matchmaking_Enqueue(intptr_t pool, intptr_t customQueryData) {
    return 0;
}
unsigned long ovr_Matchmaking_Enqueue2(intptr_t pool, intptr_t matchmakingOptions) {
    return 0;
}
unsigned long ovr_Matchmaking_EnqueueRoom(uint64_t roomID, intptr_t customQueryData) {
    return 0;
}
unsigned long ovr_Matchmaking_EnqueueRoom2(uint64_t roomID, intptr_t matchmakingOptions) {
    return 0;
}
unsigned long ovr_Matchmaking_GetAdminSnapshot() {
    return 0;
}
unsigned long ovr_Matchmaking_GetStats(intptr_t pool, uint maxLevel, MatchmakingStatApproach approach) {
    return 0;
}
unsigned long ovr_Matchmaking_JoinRoom(uint64_t roomID, bool subscribeToUpdates) {
    return 0;
}
unsigned long ovr_Matchmaking_ReportResultInsecure(uint64_t roomID, ovrKeyValuePair data[], uintptr_t numItems) {
    return 0;
}
unsigned long ovr_Matchmaking_StartMatch(uint64_t roomID) {
    return 0;
}
unsigned long ovr_Media_ShareToFacebook(intptr_t postTextSuggestion, intptr_t filePath, MediaContentType contentType) {
    return 0;
}
unsigned long ovr_NetSync_Connect(intptr_t connect_options) {
    return 0;
}
unsigned long ovr_NetSync_Disconnect(long connection_id) {
    return 0;
}
unsigned long ovr_NetSync_GetSessions(long connection_id) {
    return 0;
}
unsigned long ovr_NetSync_GetVoipAttenuation(long connection_id) {
    return 0;
}
unsigned long ovr_NetSync_GetVoipAttenuationDefault() {
    return 0;
}
unsigned long ovr_NetSync_SetVoipAttenuation(long connection_id, float *distances, float *decibels, uintptr_t count) {
    return 0;
}
unsigned long ovr_NetSync_SetVoipAttenuationModel(long connection_id, intptr_t name, float *distances, float *decibels, uintptr_t count) {
    return 0;
}
unsigned long ovr_NetSync_SetVoipChannelCfg(long connection_id, intptr_t channel_name, intptr_t attnmodel, bool disable_spatialization) {
    return 0;
}
unsigned long ovr_NetSync_SetVoipGroup(long connection_id, intptr_t group_id) {
    return 0;
}
unsigned long ovr_NetSync_SetVoipListentoChannels(long connection_id, char *listento_channels, uintptr_t count) {
    return 0;
}
unsigned long ovr_NetSync_SetVoipMicSource(long connection_id, NetSyncVoipMicSource mic_source) {
    return 0;
}
unsigned long ovr_NetSync_SetVoipSessionMuted(long connection_id, uint64_t session_id, bool muted) {
    return 0;
}
unsigned long ovr_NetSync_SetVoipSpeaktoChannels(long connection_id, char *speakto_channels, uintptr_t count) {
    return 0;
}
unsigned long ovr_NetSync_SetVoipStreamMode(long connection_id, uint64_t sessionId, NetSyncVoipStreamMode streamMode) {
    return 0;
}
unsigned long ovr_Notification_GetRoomInvites() {
    return 0;
}
unsigned long ovr_Notification_MarkAsRead(uint64_t notificationID) {
    return 0;
}
unsigned long ovr_Party_Create() {
    return 0;
}
unsigned long ovr_Party_GatherInApplication(uint64_t partyID, uint64_t appID) {
    return 0;
}
unsigned long ovr_Party_Get(uint64_t partyID) {
    return 0;
}
unsigned long ovr_Party_GetCurrent() {
    return 0;
}
unsigned long ovr_Party_GetCurrentForUser(uint64_t userID) {
    return 0;
}
unsigned long ovr_Party_Invite(uint64_t partyID, uint64_t userID) {
    return 0;
}
unsigned long ovr_Party_Join(uint64_t partyID) {
    return 0;
}
unsigned long ovr_Party_Leave(uint64_t partyID) {
    return 0;
}
unsigned long ovr_RichPresence_Clear() {
    return 0;
}
unsigned long ovr_RichPresence_GetDestinations() {
    return 0;
}
unsigned long ovr_RichPresence_Set(intptr_t richPresenceOptions) {
    return 0;
}
unsigned long ovr_RichPresence_SetDestination(intptr_t api_name) {
    return 0;
}
unsigned long ovr_RichPresence_SetIsJoinable(bool is_joinable) {
    return 0;
}
unsigned long ovr_RichPresence_SetLobbySession(intptr_t id) {
    return 0;
}
unsigned long ovr_RichPresence_SetMatchSession(intptr_t id) {
    return 0;
}
unsigned long ovr_Room_CreateAndJoinPrivate(RoomJoinPolicy joinPolicy, uint maxUsers, bool subscribeToUpdates) {
    return 0;
}
unsigned long ovr_Room_CreateAndJoinPrivate2(RoomJoinPolicy joinPolicy, uint maxUsers, intptr_t roomOptions) {
    return 0;
}
unsigned long ovr_Room_Get(uint64_t roomID) {
    return 0;
}
unsigned long ovr_Room_GetCurrent() {
    return 0;
}
unsigned long ovr_Room_GetCurrentForUser(uint64_t userID) {
    return 0;
}
unsigned long ovr_Room_GetInvitableUsers() {
    return 0;
}
unsigned long ovr_Room_GetInvitableUsers2(intptr_t roomOptions) {
    return 0;
}
unsigned long ovr_Room_GetModeratedRooms() {
    return 0;
}
unsigned long ovr_Room_GetSocialRooms(uint64_t appID) {
    return 0;
}
unsigned long ovr_Room_InviteUser(uint64_t roomID, intptr_t inviteToken) {
    return 0;
}
unsigned long ovr_Room_Join(uint64_t roomID, bool subscribeToUpdates) {
    return 0;
}
unsigned long ovr_Room_Join2(uint64_t roomID, intptr_t roomOptions) {
    return 0;
}
unsigned long ovr_Room_KickUser(uint64_t roomID, uint64_t userID, int kickDurationSeconds) {
    return 0;
}
unsigned long ovr_Room_LaunchInvitableUserFlow(uint64_t roomID) {
    return 0;
}
unsigned long ovr_Room_Leave(uint64_t roomID) {
    return 0;
}
unsigned long ovr_Room_SetDescription(uint64_t roomID, intptr_t description) {
    return 0;
}
unsigned long ovr_Room_UpdateDataStore(uint64_t roomID, ovrKeyValuePair data[], uintptr_t numItems) {
    return 0;
}
unsigned long ovr_Room_UpdateMembershipLockStatus(uint64_t roomID, RoomMembershipLockStatus membershipLockStatus) {
    return 0;
}
unsigned long ovr_Room_UpdateOwner(uint64_t roomID, uint64_t userID) {
    return 0;
}
unsigned long ovr_Room_UpdatePrivateRoomJoinPolicy(uint64_t roomID, RoomJoinPolicy newJoinPolicy) {
    return 0;
}
unsigned long ovr_User_CancelRecordingForReportFlow(intptr_t recordingUUID) {
    return 0;
}
unsigned long ovr_User_Get(uint64_t userID) {
    return 0;
}
unsigned long ovr_User_GetAccessToken() {
    return 0;
}
unsigned long ovr_User_GetBlockedUsers() {
    return 0;
}
unsigned long ovr_User_GetLinkedAccounts(intptr_t userOptions) {
    return 0;
}
unsigned long ovr_User_GetLoggedInUser() {
    return 0;
}
unsigned long ovr_User_GetLoggedInUserFriends() {
    return 0;
}
unsigned long ovr_User_GetLoggedInUserFriendsAndRooms() {
    return 0;
}
unsigned long ovr_User_GetLoggedInUserRecentlyMetUsersAndRooms(intptr_t userOptions) {
    return 0;
}
unsigned long ovr_User_GetOrgScopedID(uint64_t userID) {
    return 0;
}
unsigned long ovr_User_GetSdkAccounts() {
    return 0;
}
unsigned long ovr_User_GetUserCapabilities() {
    return 0;
}
unsigned long ovr_User_GetUserProof() {
    return 0;
}
unsigned long ovr_User_LaunchBlockFlow(uint64_t userID) {
    return 0;
}
unsigned long ovr_User_LaunchFriendRequestFlow(uint64_t userID) {
    return 0;
}
unsigned long ovr_User_LaunchProfile(uint64_t userID) {
    return 0;
}
unsigned long ovr_User_LaunchReportFlow(uint64_t userID) {
    return 0;
}
unsigned long ovr_User_LaunchReportFlow2(uint64_t optionalUserID, intptr_t abuseReportOptions) {
    return 0;
}
unsigned long ovr_User_LaunchUnblockFlow(uint64_t userID) {
    return 0;
}
unsigned long ovr_User_NewEntitledTestUser() {
    return 0;
}
unsigned long ovr_User_NewTestUser() {
    return 0;
}
unsigned long ovr_User_NewTestUserFriends() {
    return 0;
}
unsigned long ovr_User_StartRecordingForReportFlow() {
    return 0;
}
unsigned long ovr_User_StopRecordingAndLaunchReportFlow(uint64_t optionalUserID, intptr_t optionalRecordingUUID) {
    return 0;
}
unsigned long ovr_User_StopRecordingAndLaunchReportFlow2(uint64_t optionalUserID, intptr_t optionalRecordingUUID, intptr_t abuseReportOptions) {
    return 0;
}
unsigned long ovr_User_TestUserCreateDeviceManifest(intptr_t deviceID, uint64_t *appIDs, int numAppIDs) {
    return 0;
}
unsigned long ovr_UserDataStore_PrivateDeleteEntryByKey(uint64_t userID, intptr_t key) {
    return 0;
}
unsigned long ovr_UserDataStore_PrivateGetEntries(uint64_t userID) {
    return 0;
}
unsigned long ovr_UserDataStore_PrivateGetEntryByKey(uint64_t userID, intptr_t key) {
    return 0;
}
unsigned long ovr_UserDataStore_PrivateWriteEntry(uint64_t userID, intptr_t key, intptr_t value) {
    return 0;
}
unsigned long ovr_UserDataStore_PublicDeleteEntryByKey(uint64_t userID, intptr_t key) {
    return 0;
}
unsigned long ovr_UserDataStore_PublicGetEntries(uint64_t userID) {
    return 0;
}
unsigned long ovr_UserDataStore_PublicGetEntryByKey(uint64_t userID, intptr_t key) {
    return 0;
}
unsigned long ovr_UserDataStore_PublicWriteEntry(uint64_t userID, intptr_t key, intptr_t value) {
    return 0;
}
unsigned long ovr_Voip_GetMicrophoneAvailability() {
    return 0;
}
unsigned long ovr_Voip_ReportAppVoipSessions(uint64_t *sessionIDs) {
    return 0;
}
unsigned long ovr_Voip_SetSystemVoipSuppressed(bool suppressed) {
    return 0;
}
intptr_t ovr_AbuseReportRecording_GetRecordingUuid(intptr_t obj) {
    return 0;
}
uint ovr_AchievementDefinition_GetBitfieldLength(intptr_t obj) {
    return 0;
}
intptr_t ovr_AchievementDefinition_GetName(intptr_t obj) {
    return 0;
}
unsigned long ovr_AchievementDefinition_GetTarget(intptr_t obj) {
    return 0;
}
AchievementType ovr_AchievementDefinition_GetType(intptr_t obj) {
    return 0;
}
intptr_t ovr_AchievementDefinitionArray_GetElement(intptr_t obj, uintptr_t index) {
    return 0;
}
intptr_t ovr_AchievementDefinitionArray_GetNextUrl(intptr_t obj) {
    return 0;
}
uintptr_t ovr_AchievementDefinitionArray_GetSize(intptr_t obj) {
    return 0;
}
bool ovr_AchievementDefinitionArray_HasNextPage(intptr_t obj) {
    return 0;
}
intptr_t ovr_AchievementProgress_GetBitfield(intptr_t obj) {
    return 0;
}
unsigned long ovr_AchievementProgress_GetCount(intptr_t obj) {
    return 0;
}
bool ovr_AchievementProgress_GetIsUnlocked(intptr_t obj) {
    return 0;
}
intptr_t ovr_AchievementProgress_GetName(intptr_t obj) {
    return 0;
}
unsigned long ovr_AchievementProgress_GetUnlockTime(intptr_t obj) {
    return 0;
}
intptr_t ovr_AchievementProgressArray_GetElement(intptr_t obj, uintptr_t index) {
    return 0;
}
intptr_t ovr_AchievementProgressArray_GetNextUrl(intptr_t obj) {
    return 0;
}
uintptr_t ovr_AchievementProgressArray_GetSize(intptr_t obj) {
    return 0;
}
bool ovr_AchievementProgressArray_HasNextPage(intptr_t obj) {
    return 0;
}
bool ovr_AchievementUpdate_GetJustUnlocked(intptr_t obj) {
    return 0;
}
intptr_t ovr_AchievementUpdate_GetName(intptr_t obj) {
    return 0;
}
uint64_t ovr_Application_GetID(intptr_t obj) {
    return 0;
}
intptr_t ovr_ApplicationInvite_GetDestination(intptr_t obj) {
    return 0;
}
uint64_t ovr_ApplicationInvite_GetID(intptr_t obj) {
    return 0;
}
bool ovr_ApplicationInvite_GetIsActive(intptr_t obj) {
    return 0;
}
intptr_t ovr_ApplicationInvite_GetLobbySessionId(intptr_t obj) {
    return 0;
}
intptr_t ovr_ApplicationInvite_GetMatchSessionId(intptr_t obj) {
    return 0;
}
intptr_t ovr_ApplicationInvite_GetRecipient(intptr_t obj) {
    return 0;
}
intptr_t ovr_ApplicationInviteArray_GetElement(intptr_t obj, uintptr_t index) {
    return 0;
}
intptr_t ovr_ApplicationInviteArray_GetNextUrl(intptr_t obj) {
    return 0;
}
uintptr_t ovr_ApplicationInviteArray_GetSize(intptr_t obj) {
    return 0;
}
bool ovr_ApplicationInviteArray_HasNextPage(intptr_t obj) {
    return 0;
}
intptr_t ovr_ApplicationVersion_GetCurrentName(intptr_t obj) {
    return 0;
}
int ovr_ApplicationVersion_GetLatestCode(intptr_t obj) {
    return 0;
}
intptr_t ovr_ApplicationVersion_GetLatestName(intptr_t obj) {
    return 0;
}
uint64_t ovr_AssetDetails_GetAssetId(intptr_t obj) {
    return 0;
}
intptr_t ovr_AssetDetails_GetAssetType(intptr_t obj) {
    return 0;
}
intptr_t ovr_AssetDetails_GetDownloadStatus(intptr_t obj) {
    return 0;
}
intptr_t ovr_AssetDetails_GetFilepath(intptr_t obj) {
    return 0;
}
intptr_t ovr_AssetDetails_GetIapStatus(intptr_t obj) {
    return 0;
}
intptr_t ovr_AssetDetails_GetLanguage(intptr_t obj) {
    return 0;
}
intptr_t ovr_AssetDetails_GetMetadata(intptr_t obj) {
    return 0;
}
intptr_t ovr_AssetDetailsArray_GetElement(intptr_t obj, uintptr_t index) {
    return 0;
}
uintptr_t ovr_AssetDetailsArray_GetSize(intptr_t obj) {
    return 0;
}
uint64_t ovr_AssetFileDeleteResult_GetAssetFileId(intptr_t obj) {
    return 0;
}
uint64_t ovr_AssetFileDeleteResult_GetAssetId(intptr_t obj) {
    return 0;
}
intptr_t ovr_AssetFileDeleteResult_GetFilepath(intptr_t obj) {
    return 0;
}
bool ovr_AssetFileDeleteResult_GetSuccess(intptr_t obj) {
    return 0;
}
uint64_t ovr_AssetFileDownloadCancelResult_GetAssetFileId(intptr_t obj) {
    return 0;
}
uint64_t ovr_AssetFileDownloadCancelResult_GetAssetId(intptr_t obj) {
    return 0;
}
intptr_t ovr_AssetFileDownloadCancelResult_GetFilepath(intptr_t obj) {
    return 0;
}
bool ovr_AssetFileDownloadCancelResult_GetSuccess(intptr_t obj) {
    return 0;
}
uint64_t ovr_AssetFileDownloadResult_GetAssetId(intptr_t obj) {
    return 0;
}
intptr_t ovr_AssetFileDownloadResult_GetFilepath(intptr_t obj) {
    return 0;
}
uint64_t ovr_AssetFileDownloadUpdate_GetAssetFileId(intptr_t obj) {
    return 0;
}
uint64_t ovr_AssetFileDownloadUpdate_GetAssetId(intptr_t obj) {
    return 0;
}
uint ovr_AssetFileDownloadUpdate_GetBytesTotal(intptr_t obj) {
    return 0;
}
unsigned long ovr_AssetFileDownloadUpdate_GetBytesTotalLong(intptr_t obj) {
    return 0;
}
int ovr_AssetFileDownloadUpdate_GetBytesTransferred(intptr_t obj) {
    return 0;
}
long ovr_AssetFileDownloadUpdate_GetBytesTransferredLong(intptr_t obj) {
    return 0;
}
bool ovr_AssetFileDownloadUpdate_GetCompleted(intptr_t obj) {
    return 0;
}
bool ovr_AvatarEditorResult_GetRequestSent(intptr_t obj) {
    return 0;
}
uint64_t ovr_BlockedUser_GetId(intptr_t obj) {
    return 0;
}
intptr_t ovr_BlockedUserArray_GetElement(intptr_t obj, uintptr_t index) {
    return 0;
}
intptr_t ovr_BlockedUserArray_GetNextUrl(intptr_t obj) {
    return 0;
}
uintptr_t ovr_BlockedUserArray_GetSize(intptr_t obj) {
    return 0;
}
bool ovr_BlockedUserArray_HasNextPage(intptr_t obj) {
    return 0;
}
int ovr_CalApplicationFinalized_GetCountdownMS(intptr_t obj) {
    return 0;
}
uint64_t ovr_CalApplicationFinalized_GetID(intptr_t obj) {
    return 0;
}
intptr_t ovr_CalApplicationFinalized_GetLaunchDetails(intptr_t obj) {
    return 0;
}
uint64_t ovr_CalApplicationProposed_GetID(intptr_t obj) {
    return 0;
}
uint64_t ovr_CalApplicationSuggestion_GetID(intptr_t obj) {
    return 0;
}
intptr_t ovr_CalApplicationSuggestion_GetSocialContext(intptr_t obj) {
    return 0;
}
intptr_t ovr_CalApplicationSuggestionArray_GetElement(intptr_t obj, uintptr_t index) {
    return 0;
}
uintptr_t ovr_CalApplicationSuggestionArray_GetSize(intptr_t obj) {
    return 0;
}
intptr_t ovr_Challenge_GetDescription(intptr_t obj) {
    return 0;
}
unsigned long ovr_Challenge_GetEndDate(intptr_t obj) {
    return 0;
}
uint64_t ovr_Challenge_GetID(intptr_t obj) {
    return 0;
}
intptr_t ovr_Challenge_GetInvitedUsers(intptr_t obj) {
    return 0;
}
intptr_t ovr_Challenge_GetLeaderboard(intptr_t obj) {
    return 0;
}
intptr_t ovr_Challenge_GetParticipants(intptr_t obj) {
    return 0;
}
unsigned long ovr_Challenge_GetStartDate(intptr_t obj) {
    return 0;
}
intptr_t ovr_Challenge_GetTitle(intptr_t obj) {
    return 0;
}
ChallengeVisibility ovr_Challenge_GetVisibility(intptr_t obj) {
    return 0;
}
intptr_t ovr_ChallengeArray_GetElement(intptr_t obj, uintptr_t index) {
    return 0;
}
intptr_t ovr_ChallengeArray_GetNextUrl(intptr_t obj) {
    return 0;
}
intptr_t ovr_ChallengeArray_GetPreviousUrl(intptr_t obj) {
    return 0;
}
uintptr_t ovr_ChallengeArray_GetSize(intptr_t obj) {
    return 0;
}
unsigned long ovr_ChallengeArray_GetTotalCount(intptr_t obj) {
    return 0;
}
bool ovr_ChallengeArray_HasNextPage(intptr_t obj) {
    return 0;
}
bool ovr_ChallengeArray_HasPreviousPage(intptr_t obj) {
    return 0;
}
intptr_t ovr_ChallengeEntry_GetDisplayScore(intptr_t obj) {
    return 0;
}
intptr_t ovr_ChallengeEntry_GetExtraData(intptr_t obj) {
    return 0;
}
uint ovr_ChallengeEntry_GetExtraDataLength(intptr_t obj) {
    return 0;
}
uint64_t ovr_ChallengeEntry_GetID(intptr_t obj) {
    return 0;
}
int ovr_ChallengeEntry_GetRank(intptr_t obj) {
    return 0;
}
long ovr_ChallengeEntry_GetScore(intptr_t obj) {
    return 0;
}
unsigned long ovr_ChallengeEntry_GetTimestamp(intptr_t obj) {
    return 0;
}
intptr_t ovr_ChallengeEntry_GetUser(intptr_t obj) {
    return 0;
}
intptr_t ovr_ChallengeEntryArray_GetElement(intptr_t obj, uintptr_t index) {
    return 0;
}
intptr_t ovr_ChallengeEntryArray_GetNextUrl(intptr_t obj) {
    return 0;
}
intptr_t ovr_ChallengeEntryArray_GetPreviousUrl(intptr_t obj) {
    return 0;
}
uintptr_t ovr_ChallengeEntryArray_GetSize(intptr_t obj) {
    return 0;
}
unsigned long ovr_ChallengeEntryArray_GetTotalCount(intptr_t obj) {
    return 0;
}
bool ovr_ChallengeEntryArray_HasNextPage(intptr_t obj) {
    return 0;
}
bool ovr_ChallengeEntryArray_HasPreviousPage(intptr_t obj) {
    return 0;
}
intptr_t ovr_CloudStorage2UserDirectoryPathResponse_GetPath(intptr_t obj) {
    return 0;
}
intptr_t ovr_CloudStorageConflictMetadata_GetLocal(intptr_t obj) {
    return 0;
}
intptr_t ovr_CloudStorageConflictMetadata_GetRemote(intptr_t obj) {
    return 0;
}
intptr_t ovr_CloudStorageData_GetBucket(intptr_t obj) {
    return 0;
}
intptr_t ovr_CloudStorageData_GetData(intptr_t obj) {
    return 0;
}
uint ovr_CloudStorageData_GetDataSize(intptr_t obj) {
    return 0;
}
intptr_t ovr_CloudStorageData_GetKey(intptr_t obj) {
    return 0;
}
intptr_t ovr_CloudStorageMetadata_GetBucket(intptr_t obj) {
    return 0;
}
long ovr_CloudStorageMetadata_GetCounter(intptr_t obj) {
    return 0;
}
uint ovr_CloudStorageMetadata_GetDataSize(intptr_t obj) {
    return 0;
}
intptr_t ovr_CloudStorageMetadata_GetExtraData(intptr_t obj) {
    return 0;
}
intptr_t ovr_CloudStorageMetadata_GetKey(intptr_t obj) {
    return 0;
}
unsigned long ovr_CloudStorageMetadata_GetSaveTime(intptr_t obj) {
    return 0;
}
CloudStorageDataStatus ovr_CloudStorageMetadata_GetStatus(intptr_t obj) {
    return 0;
}
intptr_t ovr_CloudStorageMetadata_GetVersionHandle(intptr_t obj) {
    return 0;
}
intptr_t ovr_CloudStorageMetadataArray_GetElement(intptr_t obj, uintptr_t index) {
    return 0;
}
intptr_t ovr_CloudStorageMetadataArray_GetNextUrl(intptr_t obj) {
    return 0;
}
uintptr_t ovr_CloudStorageMetadataArray_GetSize(intptr_t obj) {
    return 0;
}
bool ovr_CloudStorageMetadataArray_HasNextPage(intptr_t obj) {
    return 0;
}
intptr_t ovr_CloudStorageUpdateResponse_GetBucket(intptr_t obj) {
    return 0;
}
intptr_t ovr_CloudStorageUpdateResponse_GetKey(intptr_t obj) {
    return 0;
}
CloudStorageUpdateStatus ovr_CloudStorageUpdateResponse_GetStatus(intptr_t obj) {
    return 0;
}
intptr_t ovr_CloudStorageUpdateResponse_GetVersionHandle(intptr_t obj) {
    return 0;
}
uint ovr_DataStore_Contains(intptr_t obj, intptr_t key) {
    return 0;
}
intptr_t ovr_DataStore_GetKey(intptr_t obj, int index) {
    return 0;
}
uintptr_t ovr_DataStore_GetNumKeys(intptr_t obj) {
    return 0;
}
intptr_t ovr_DataStore_GetValue(intptr_t obj, intptr_t key) {
    return 0;
}
intptr_t ovr_Destination_GetApiName(intptr_t obj) {
    return 0;
}
intptr_t ovr_Destination_GetDeeplinkMessage(intptr_t obj) {
    return 0;
}
intptr_t ovr_Destination_GetDisplayName(intptr_t obj) {
    return 0;
}
intptr_t ovr_DestinationArray_GetElement(intptr_t obj, uintptr_t index) {
    return 0;
}
intptr_t ovr_DestinationArray_GetNextUrl(intptr_t obj) {
    return 0;
}
uintptr_t ovr_DestinationArray_GetSize(intptr_t obj) {
    return 0;
}
bool ovr_DestinationArray_HasNextPage(intptr_t obj) {
    return 0;
}
int ovr_Error_GetCode(intptr_t obj) {
    return 0;
}
intptr_t ovr_Error_GetDisplayableMessage(intptr_t obj) {
    return 0;
}
int ovr_Error_GetHttpCode(intptr_t obj) {
    return 0;
}
intptr_t ovr_Error_GetMessage(intptr_t obj) {
    return 0;
}
intptr_t ovr_GroupPresenceJoinIntent_GetDeeplinkMessage(intptr_t obj) {
    return 0;
}
intptr_t ovr_GroupPresenceJoinIntent_GetDestinationApiName(intptr_t obj) {
    return 0;
}
intptr_t ovr_GroupPresenceJoinIntent_GetLobbySessionId(intptr_t obj) {
    return 0;
}
intptr_t ovr_GroupPresenceJoinIntent_GetMatchSessionId(intptr_t obj) {
    return 0;
}
intptr_t ovr_GroupPresenceLeaveIntent_GetDestinationApiName(intptr_t obj) {
    return 0;
}
intptr_t ovr_GroupPresenceLeaveIntent_GetLobbySessionId(intptr_t obj) {
    return 0;
}
intptr_t ovr_GroupPresenceLeaveIntent_GetMatchSessionId(intptr_t obj) {
    return 0;
}
intptr_t ovr_HttpTransferUpdate_GetBytes(intptr_t obj) {
    return 0;
}
unsigned long ovr_HttpTransferUpdate_GetID(intptr_t obj) {
    return 0;
}
uintptr_t ovr_HttpTransferUpdate_GetSize(intptr_t obj) {
    return 0;
}
bool ovr_HttpTransferUpdate_IsCompleted(intptr_t obj) {
    return 0;
}
intptr_t ovr_InstalledApplication_GetApplicationId(intptr_t obj) {
    return 0;
}
intptr_t ovr_InstalledApplication_GetPackageName(intptr_t obj) {
    return 0;
}
intptr_t ovr_InstalledApplication_GetStatus(intptr_t obj) {
    return 0;
}
intptr_t ovr_InstalledApplication_GetVersionName(intptr_t obj) {
    return 0;
}
intptr_t ovr_InstalledApplicationArray_GetElement(intptr_t obj, uintptr_t index) {
    return 0;
}
uintptr_t ovr_InstalledApplicationArray_GetSize(intptr_t obj) {
    return 0;
}
bool ovr_InvitePanelResultInfo_GetInvitesSent(intptr_t obj) {
    return 0;
}
intptr_t ovr_LanguagePackInfo_GetEnglishName(intptr_t obj) {
    return 0;
}
intptr_t ovr_LanguagePackInfo_GetNativeName(intptr_t obj) {
    return 0;
}
intptr_t ovr_LanguagePackInfo_GetTag(intptr_t obj) {
    return 0;
}
bool ovr_LaunchBlockFlowResult_GetDidBlock(intptr_t obj) {
    return 0;
}
bool ovr_LaunchBlockFlowResult_GetDidCancel(intptr_t obj) {
    return 0;
}
intptr_t ovr_LaunchDetails_GetDeeplinkMessage(intptr_t obj) {
    return 0;
}
intptr_t ovr_LaunchDetails_GetDestinationApiName(intptr_t obj) {
    return 0;
}
intptr_t ovr_LaunchDetails_GetLaunchSource(intptr_t obj) {
    return 0;
}
LaunchType ovr_LaunchDetails_GetLaunchType(intptr_t obj) {
    return 0;
}
uint64_t ovr_LaunchDetails_GetRoomID(intptr_t obj) {
    return 0;
}
intptr_t ovr_LaunchDetails_GetTrackingID(intptr_t obj) {
    return 0;
}
intptr_t ovr_LaunchDetails_GetUsers(intptr_t obj) {
    return 0;
}
bool ovr_LaunchFriendRequestFlowResult_GetDidCancel(intptr_t obj) {
    return 0;
}
bool ovr_LaunchFriendRequestFlowResult_GetDidSendRequest(intptr_t obj) {
    return 0;
}
intptr_t ovr_LaunchInvitePanelFlowResult_GetInvitedUsers(intptr_t obj) {
    return 0;
}
bool ovr_LaunchReportFlowResult_GetDidCancel(intptr_t obj) {
    return 0;
}
uint64_t ovr_LaunchReportFlowResult_GetUserReportId(intptr_t obj) {
    return 0;
}
bool ovr_LaunchUnblockFlowResult_GetDidCancel(intptr_t obj) {
    return 0;
}
bool ovr_LaunchUnblockFlowResult_GetDidUnblock(intptr_t obj) {
    return 0;
}
intptr_t ovr_Leaderboard_GetApiName(intptr_t obj) {
    return 0;
}
intptr_t ovr_Leaderboard_GetDestination(intptr_t obj) {
    return 0;
}
uint64_t ovr_Leaderboard_GetID(intptr_t obj) {
    return 0;
}
intptr_t ovr_LeaderboardArray_GetElement(intptr_t obj, uintptr_t index) {
    return 0;
}
intptr_t ovr_LeaderboardArray_GetNextUrl(intptr_t obj) {
    return 0;
}
uintptr_t ovr_LeaderboardArray_GetSize(intptr_t obj) {
    return 0;
}
bool ovr_LeaderboardArray_HasNextPage(intptr_t obj) {
    return 0;
}
intptr_t ovr_LeaderboardEntry_GetDisplayScore(intptr_t obj) {
    return 0;
}
intptr_t ovr_LeaderboardEntry_GetExtraData(intptr_t obj) {
    return 0;
}
uint ovr_LeaderboardEntry_GetExtraDataLength(intptr_t obj) {
    return 0;
}
uint64_t ovr_LeaderboardEntry_GetID(intptr_t obj) {
    return 0;
}
int ovr_LeaderboardEntry_GetRank(intptr_t obj) {
    return 0;
}
long ovr_LeaderboardEntry_GetScore(intptr_t obj) {
    return 0;
}
intptr_t ovr_LeaderboardEntry_GetSupplementaryMetric(intptr_t obj) {
    return 0;
}
unsigned long ovr_LeaderboardEntry_GetTimestamp(intptr_t obj) {
    return 0;
}
intptr_t ovr_LeaderboardEntry_GetUser(intptr_t obj) {
    return 0;
}
intptr_t ovr_LeaderboardEntryArray_GetElement(intptr_t obj, uintptr_t index) {
    return 0;
}
intptr_t ovr_LeaderboardEntryArray_GetNextUrl(intptr_t obj) {
    return 0;
}
intptr_t ovr_LeaderboardEntryArray_GetPreviousUrl(intptr_t obj) {
    return 0;
}
uintptr_t ovr_LeaderboardEntryArray_GetSize(intptr_t obj) {
    return 0;
}
unsigned long ovr_LeaderboardEntryArray_GetTotalCount(intptr_t obj) {
    return 0;
}
bool ovr_LeaderboardEntryArray_HasNextPage(intptr_t obj) {
    return 0;
}
bool ovr_LeaderboardEntryArray_HasPreviousPage(intptr_t obj) {
    return 0;
}
bool ovr_LeaderboardUpdateStatus_GetDidUpdate(intptr_t obj) {
    return 0;
}
uint64_t ovr_LeaderboardUpdateStatus_GetUpdatedChallengeId(intptr_t obj, uint index) {
    return 0;
}
uint ovr_LeaderboardUpdateStatus_GetUpdatedChallengeIdsSize(intptr_t obj) {
    return 0;
}
intptr_t ovr_LinkedAccount_GetAccessToken(intptr_t obj) {
    return 0;
}
ServiceProvider ovr_LinkedAccount_GetServiceProvider(intptr_t obj) {
    return 0;
}
intptr_t ovr_LinkedAccount_GetUserId(intptr_t obj) {
    return 0;
}
intptr_t ovr_LinkedAccountArray_GetElement(intptr_t obj, uintptr_t index) {
    return 0;
}
uintptr_t ovr_LinkedAccountArray_GetSize(intptr_t obj) {
    return 0;
}
bool ovr_LivestreamingApplicationStatus_GetStreamingEnabled(intptr_t obj) {
    return 0;
}
LivestreamingStartStatus ovr_LivestreamingStartResult_GetStreamingResult(intptr_t obj) {
    return 0;
}
bool ovr_LivestreamingStatus_GetCommentsVisible(intptr_t obj) {
    return 0;
}
bool ovr_LivestreamingStatus_GetIsPaused(intptr_t obj) {
    return 0;
}
bool ovr_LivestreamingStatus_GetLivestreamingEnabled(intptr_t obj) {
    return 0;
}
int ovr_LivestreamingStatus_GetLivestreamingType(intptr_t obj) {
    return 0;
}
bool ovr_LivestreamingStatus_GetMicEnabled(intptr_t obj) {
    return 0;
}
int ovr_LivestreamingVideoStats_GetCommentCount(intptr_t obj) {
    return 0;
}
int ovr_LivestreamingVideoStats_GetReactionCount(intptr_t obj) {
    return 0;
}
intptr_t ovr_LivestreamingVideoStats_GetTotalViews(intptr_t obj) {
    return 0;
}
intptr_t ovr_MatchmakingAdminSnapshot_GetCandidates(intptr_t obj) {
    return 0;
}
double ovr_MatchmakingAdminSnapshot_GetMyCurrentThreshold(intptr_t obj) {
    return 0;
}
bool ovr_MatchmakingAdminSnapshotCandidate_GetCanMatch(intptr_t obj) {
    return 0;
}
double ovr_MatchmakingAdminSnapshotCandidate_GetMyTotalScore(intptr_t obj) {
    return 0;
}
double ovr_MatchmakingAdminSnapshotCandidate_GetTheirCurrentThreshold(intptr_t obj) {
    return 0;
}
double ovr_MatchmakingAdminSnapshotCandidate_GetTheirTotalScore(intptr_t obj) {
    return 0;
}
intptr_t ovr_MatchmakingAdminSnapshotCandidate_GetTraceId(intptr_t obj) {
    return 0;
}
intptr_t ovr_MatchmakingAdminSnapshotCandidateArray_GetElement(intptr_t obj, uintptr_t index) {
    return 0;
}
uintptr_t ovr_MatchmakingAdminSnapshotCandidateArray_GetSize(intptr_t obj) {
    return 0;
}
intptr_t ovr_MatchmakingBrowseResult_GetEnqueueResult(intptr_t obj) {
    return 0;
}
intptr_t ovr_MatchmakingBrowseResult_GetRooms(intptr_t obj) {
    return 0;
}
intptr_t ovr_MatchmakingCandidate_GetEntryHash(intptr_t obj) {
    return 0;
}
unsigned long ovr_MatchmakingCandidate_GetUserId(intptr_t obj) {
    return 0;
}
intptr_t ovr_MatchmakingCandidateArray_GetElement(intptr_t obj, uintptr_t index) {
    return 0;
}
intptr_t ovr_MatchmakingCandidateArray_GetNextUrl(intptr_t obj) {
    return 0;
}
uintptr_t ovr_MatchmakingCandidateArray_GetSize(intptr_t obj) {
    return 0;
}
bool ovr_MatchmakingCandidateArray_HasNextPage(intptr_t obj) {
    return 0;
}
intptr_t ovr_MatchmakingEnqueueResult_GetAdminSnapshot(intptr_t obj) {
    return 0;
}
uint ovr_MatchmakingEnqueueResult_GetAverageWait(intptr_t obj) {
    return 0;
}
uint ovr_MatchmakingEnqueueResult_GetMatchesInLastHourCount(intptr_t obj) {
    return 0;
}
uint ovr_MatchmakingEnqueueResult_GetMaxExpectedWait(intptr_t obj) {
    return 0;
}
intptr_t ovr_MatchmakingEnqueueResult_GetPool(intptr_t obj) {
    return 0;
}
uint ovr_MatchmakingEnqueueResult_GetRecentMatchPercentage(intptr_t obj) {
    return 0;
}
intptr_t ovr_MatchmakingEnqueueResult_GetRequestHash(intptr_t obj) {
    return 0;
}
intptr_t ovr_MatchmakingEnqueueResultAndRoom_GetMatchmakingEnqueueResult(intptr_t obj) {
    return 0;
}
intptr_t ovr_MatchmakingEnqueueResultAndRoom_GetRoom(intptr_t obj) {
    return 0;
}
uint64_t ovr_MatchmakingEnqueuedUser_GetAdditionalUserID(intptr_t obj, uint index) {
    return 0;
}
uint ovr_MatchmakingEnqueuedUser_GetAdditionalUserIDsSize(intptr_t obj) {
    return 0;
}
intptr_t ovr_MatchmakingEnqueuedUser_GetCustomData(intptr_t obj) {
    return 0;
}
intptr_t ovr_MatchmakingEnqueuedUser_GetUser(intptr_t obj) {
    return 0;
}
intptr_t ovr_MatchmakingEnqueuedUserArray_GetElement(intptr_t obj, uintptr_t index) {
    return 0;
}
uintptr_t ovr_MatchmakingEnqueuedUserArray_GetSize(intptr_t obj) {
    return 0;
}
unsigned long ovr_MatchmakingNotification_GetAddedByUserId(intptr_t obj) {
    return 0;
}
intptr_t ovr_MatchmakingNotification_GetRoom(intptr_t obj) {
    return 0;
}
intptr_t ovr_MatchmakingNotification_GetTraceId(intptr_t obj) {
    return 0;
}
uint ovr_MatchmakingRoom_GetPingTime(intptr_t obj) {
    return 0;
}
intptr_t ovr_MatchmakingRoom_GetRoom(intptr_t obj) {
    return 0;
}
bool ovr_MatchmakingRoom_HasPingTime(intptr_t obj) {
    return 0;
}
intptr_t ovr_MatchmakingRoomArray_GetElement(intptr_t obj, uintptr_t index) {
    return 0;
}
uintptr_t ovr_MatchmakingRoomArray_GetSize(intptr_t obj) {
    return 0;
}
uint ovr_MatchmakingStats_GetDrawCount(intptr_t obj) {
    return 0;
}
uint ovr_MatchmakingStats_GetLossCount(intptr_t obj) {
    return 0;
}
uint ovr_MatchmakingStats_GetSkillLevel(intptr_t obj) {
    return 0;
}
double ovr_MatchmakingStats_GetSkillMean(intptr_t obj) {
    return 0;
}
double ovr_MatchmakingStats_GetSkillStandardDeviation(intptr_t obj) {
    return 0;
}
uint ovr_MatchmakingStats_GetWinCount(intptr_t obj) {
    return 0;
}
intptr_t ovr_Message_GetAbuseReportRecording(intptr_t obj) {
    return 0;
}
intptr_t ovr_Message_GetAchievementDefinitionArray(intptr_t obj) {
    return 0;
}
intptr_t ovr_Message_GetAchievementProgressArray(intptr_t obj) {
    return 0;
}
intptr_t ovr_Message_GetAchievementUpdate(intptr_t obj) {
    return 0;
}
intptr_t ovr_Message_GetApplicationInviteArray(intptr_t obj) {
    return 0;
}
intptr_t ovr_Message_GetApplicationVersion(intptr_t obj) {
    return 0;
}
intptr_t ovr_Message_GetAssetDetails(intptr_t obj) {
    return 0;
}
intptr_t ovr_Message_GetAssetDetailsArray(intptr_t obj) {
    return 0;
}
intptr_t ovr_Message_GetAssetFileDeleteResult(intptr_t obj) {
    return 0;
}
intptr_t ovr_Message_GetAssetFileDownloadCancelResult(intptr_t obj) {
    return 0;
}
intptr_t ovr_Message_GetAssetFileDownloadResult(intptr_t obj) {
    return 0;
}
intptr_t ovr_Message_GetAssetFileDownloadUpdate(intptr_t obj) {
    return 0;
}
intptr_t ovr_Message_GetAvatarEditorResult(intptr_t obj) {
    return 0;
}
intptr_t ovr_Message_GetBlockedUserArray(intptr_t obj) {
    return 0;
}
intptr_t ovr_Message_GetCalApplicationFinalized(intptr_t obj) {
    return 0;
}
intptr_t ovr_Message_GetCalApplicationProposed(intptr_t obj) {
    return 0;
}
intptr_t ovr_Message_GetCalApplicationSuggestionArray(intptr_t obj) {
    return 0;
}
intptr_t ovr_Message_GetChallenge(intptr_t obj) {
    return 0;
}
intptr_t ovr_Message_GetChallengeArray(intptr_t obj) {
    return 0;
}
intptr_t ovr_Message_GetChallengeEntryArray(intptr_t obj) {
    return 0;
}
intptr_t ovr_Message_GetCloudStorageConflictMetadata(intptr_t obj) {
    return 0;
}
intptr_t ovr_Message_GetCloudStorageData(intptr_t obj) {
    return 0;
}
intptr_t ovr_Message_GetCloudStorageMetadata(intptr_t obj) {
    return 0;
}
intptr_t ovr_Message_GetCloudStorageMetadataArray(intptr_t obj) {
    return 0;
}
intptr_t ovr_Message_GetCloudStorageUpdateResponse(intptr_t obj) {
    return 0;
}
intptr_t ovr_Message_GetDataStore(intptr_t obj) {
    return 0;
}
intptr_t ovr_Message_GetDestinationArray(intptr_t obj) {
    return 0;
}
intptr_t ovr_Message_GetError(intptr_t obj) {
    return 0;
}
intptr_t ovr_Message_GetGroupPresenceJoinIntent(intptr_t obj) {
    return 0;
}
intptr_t ovr_Message_GetGroupPresenceLeaveIntent(intptr_t obj) {
    return 0;
}
intptr_t ovr_Message_GetHttpTransferUpdate(intptr_t obj) {
    return 0;
}
intptr_t ovr_Message_GetInstalledApplicationArray(intptr_t obj) {
    return 0;
}
intptr_t ovr_Message_GetInvitePanelResultInfo(intptr_t obj) {
    return 0;
}
intptr_t ovr_Message_GetLaunchBlockFlowResult(intptr_t obj) {
    return 0;
}
intptr_t ovr_Message_GetLaunchFriendRequestFlowResult(intptr_t obj) {
    return 0;
}
intptr_t ovr_Message_GetLaunchInvitePanelFlowResult(intptr_t obj) {
    return 0;
}
intptr_t ovr_Message_GetLaunchReportFlowResult(intptr_t obj) {
    return 0;
}
intptr_t ovr_Message_GetLaunchUnblockFlowResult(intptr_t obj) {
    return 0;
}
intptr_t ovr_Message_GetLeaderboardArray(intptr_t obj) {
    return 0;
}
intptr_t ovr_Message_GetLeaderboardEntryArray(intptr_t obj) {
    return 0;
}
intptr_t ovr_Message_GetLeaderboardUpdateStatus(intptr_t obj) {
    return 0;
}
intptr_t ovr_Message_GetLinkedAccountArray(intptr_t obj) {
    return 0;
}
intptr_t ovr_Message_GetLivestreamingApplicationStatus(intptr_t obj) {
    return 0;
}
intptr_t ovr_Message_GetLivestreamingStartResult(intptr_t obj) {
    return 0;
}
intptr_t ovr_Message_GetLivestreamingStatus(intptr_t obj) {
    return 0;
}
intptr_t ovr_Message_GetLivestreamingVideoStats(intptr_t obj) {
    return 0;
}
intptr_t ovr_Message_GetMatchmakingAdminSnapshot(intptr_t obj) {
    return 0;
}
intptr_t ovr_Message_GetMatchmakingBrowseResult(intptr_t obj) {
    return 0;
}
intptr_t ovr_Message_GetMatchmakingEnqueueResult(intptr_t obj) {
    return 0;
}
intptr_t ovr_Message_GetMatchmakingEnqueueResultAndRoom(intptr_t obj) {
    return 0;
}
intptr_t ovr_Message_GetMatchmakingRoomArray(intptr_t obj) {
    return 0;
}
intptr_t ovr_Message_GetMatchmakingStats(intptr_t obj) {
    return 0;
}
intptr_t ovr_Message_GetMicrophoneAvailabilityState(intptr_t obj) {
    return 0;
}
intptr_t ovr_Message_GetNativeMessage(intptr_t obj) {
    return 0;
}
intptr_t ovr_Message_GetNetSyncConnection(intptr_t obj) {
    return 0;
}
intptr_t ovr_Message_GetNetSyncSessionArray(intptr_t obj) {
    return 0;
}
intptr_t ovr_Message_GetNetSyncSessionsChangedNotification(intptr_t obj) {
    return 0;
}
intptr_t ovr_Message_GetNetSyncSetSessionPropertyResult(intptr_t obj) {
    return 0;
}
intptr_t ovr_Message_GetNetSyncVoipAttenuationValueArray(intptr_t obj) {
    return 0;
}
intptr_t ovr_Message_GetNetworkingPeer(intptr_t obj) {
    return 0;
}
intptr_t ovr_Message_GetOrgScopedID(intptr_t obj) {
    return 0;
}
intptr_t ovr_Message_GetParty(intptr_t obj) {
    return 0;
}
intptr_t ovr_Message_GetPartyID(intptr_t obj) {
    return 0;
}
intptr_t ovr_Message_GetPartyUpdateNotification(intptr_t obj) {
    return 0;
}
intptr_t ovr_Message_GetPidArray(intptr_t obj) {
    return 0;
}
intptr_t ovr_Message_GetPingResult(intptr_t obj) {
    return 0;
}
intptr_t ovr_Message_GetPlatformInitialize(intptr_t obj) {
    return 0;
}
intptr_t ovr_Message_GetProductArray(intptr_t obj) {
    return 0;
}
intptr_t ovr_Message_GetPurchase(intptr_t obj) {
    return 0;
}
intptr_t ovr_Message_GetPurchaseArray(intptr_t obj) {
    return 0;
}
intptr_t ovr_Message_GetRejoinDialogResult(intptr_t obj) {
    return 0;
}
unsigned long ovr_Message_GetRequestID(intptr_t obj) {
    return 0;
}
intptr_t ovr_Message_GetRoom(intptr_t obj) {
    return 0;
}
intptr_t ovr_Message_GetRoomArray(intptr_t obj) {
    return 0;
}
intptr_t ovr_Message_GetRoomInviteNotification(intptr_t obj) {
    return 0;
}
intptr_t ovr_Message_GetRoomInviteNotificationArray(intptr_t obj) {
    return 0;
}
intptr_t ovr_Message_GetSdkAccountArray(intptr_t obj) {
    return 0;
}
intptr_t ovr_Message_GetSendInvitesResult(intptr_t obj) {
    return 0;
}
intptr_t ovr_Message_GetShareMediaResult(intptr_t obj) {
    return 0;
}
intptr_t ovr_Message_GetString(intptr_t obj) {
    return 0;
}
intptr_t ovr_Message_GetSystemVoipState(intptr_t obj) {
    return 0;
}
MessageType ovr_Message_GetType(intptr_t obj) {
    return 0;
}
intptr_t ovr_Message_GetUser(intptr_t obj) {
    return 0;
}
intptr_t ovr_Message_GetUserAndRoomArray(intptr_t obj) {
    return 0;
}
intptr_t ovr_Message_GetUserArray(intptr_t obj) {
    return 0;
}
intptr_t ovr_Message_GetUserCapabilityArray(intptr_t obj) {
    return 0;
}
intptr_t ovr_Message_GetUserDataStoreUpdateResponse(intptr_t obj) {
    return 0;
}
intptr_t ovr_Message_GetUserProof(intptr_t obj) {
    return 0;
}
intptr_t ovr_Message_GetUserReportID(intptr_t obj) {
    return 0;
}
bool ovr_Message_IsError(intptr_t obj) {
    return 0;
}
uintptr_t ovr_Microphone_GetNumSamplesAvailable(intptr_t obj) {
    return 0;
}
uintptr_t ovr_Microphone_GetOutputBufferMaxSize(intptr_t obj) {
    return 0;
}
uintptr_t ovr_Microphone_GetPCM(intptr_t obj, uint16_t *outputBuffer, uintptr_t outputBufferNumElements) {
    return 0;
}
uintptr_t ovr_Microphone_GetPCMFloat(intptr_t obj, float *outputBuffer, uintptr_t outputBufferNumElements) {
    return 0;
}
uintptr_t ovr_Microphone_ReadData(intptr_t obj, float *outputBuffer, uintptr_t outputBufferSize) {
    return 0;
}
void ovr_Microphone_SetAcceptableRecordingDelayHint(intptr_t obj, uintptr_t delayMs) {
    return;
}
void ovr_Microphone_Start(intptr_t obj) {
    return;
}
void ovr_Microphone_Stop(intptr_t obj) {
    return;
}
bool ovr_MicrophoneAvailabilityState_GetMicrophoneAvailable(intptr_t obj) {
    return 0;
}
long ovr_NetSyncConnection_GetConnectionId(intptr_t obj) {
    return 0;
}
NetSyncDisconnectReason ovr_NetSyncConnection_GetDisconnectReason(intptr_t obj) {
    return 0;
}
uint64_t ovr_NetSyncConnection_GetSessionId(intptr_t obj) {
    return 0;
}
NetSyncConnectionStatus ovr_NetSyncConnection_GetStatus(intptr_t obj) {
    return 0;
}
intptr_t ovr_NetSyncConnection_GetZoneId(intptr_t obj) {
    return 0;
}
long ovr_NetSyncSession_GetConnectionId(intptr_t obj) {
    return 0;
}
bool ovr_NetSyncSession_GetMuted(intptr_t obj) {
    return 0;
}
uint64_t ovr_NetSyncSession_GetSessionId(intptr_t obj) {
    return 0;
}
uint64_t ovr_NetSyncSession_GetUserId(intptr_t obj) {
    return 0;
}
intptr_t ovr_NetSyncSession_GetVoipGroup(intptr_t obj) {
    return 0;
}
intptr_t ovr_NetSyncSessionArray_GetElement(intptr_t obj, uintptr_t index) {
    return 0;
}
uintptr_t ovr_NetSyncSessionArray_GetSize(intptr_t obj) {
    return 0;
}
long ovr_NetSyncSessionsChangedNotification_GetConnectionId(intptr_t obj) {
    return 0;
}
intptr_t ovr_NetSyncSessionsChangedNotification_GetSessions(intptr_t obj) {
    return 0;
}
intptr_t ovr_NetSyncSetSessionPropertyResult_GetSession(intptr_t obj) {
    return 0;
}
float ovr_NetSyncVoipAttenuationValue_GetDecibels(intptr_t obj) {
    return 0;
}
float ovr_NetSyncVoipAttenuationValue_GetDistance(intptr_t obj) {
    return 0;
}
intptr_t ovr_NetSyncVoipAttenuationValueArray_GetElement(intptr_t obj, uintptr_t index) {
    return 0;
}
uintptr_t ovr_NetSyncVoipAttenuationValueArray_GetSize(intptr_t obj) {
    return 0;
}
uint64_t ovr_NetworkingPeer_GetID(intptr_t obj) {
    return 0;
}
PeerConnectionState ovr_NetworkingPeer_GetState(intptr_t obj) {
    return 0;
}
uint64_t ovr_OrgScopedID_GetID(intptr_t obj) {
    return 0;
}
void ovr_Packet_Free(intptr_t obj) {
    return;
}
intptr_t ovr_Packet_GetBytes(intptr_t obj) {
    return 0;
}
SendPolicy ovr_Packet_GetSendPolicy(intptr_t obj) {
    return 0;
}
uint64_t ovr_Packet_GetSenderID(intptr_t obj) {
    return 0;
}
uintptr_t ovr_Packet_GetSize(intptr_t obj) {
    return 0;
}
uint64_t ovr_Party_GetID(intptr_t obj) {
    return 0;
}
intptr_t ovr_Party_GetInvitedUsers(intptr_t obj) {
    return 0;
}
intptr_t ovr_Party_GetLeader(intptr_t obj) {
    return 0;
}
intptr_t ovr_Party_GetRoom(intptr_t obj) {
    return 0;
}
intptr_t ovr_Party_GetUsers(intptr_t obj) {
    return 0;
}
uint64_t ovr_PartyID_GetID(intptr_t obj) {
    return 0;
}
PartyUpdateAction ovr_PartyUpdateNotification_GetAction(intptr_t obj) {
    return 0;
}
uint64_t ovr_PartyUpdateNotification_GetPartyId(intptr_t obj) {
    return 0;
}
uint64_t ovr_PartyUpdateNotification_GetSenderId(intptr_t obj) {
    return 0;
}
intptr_t ovr_PartyUpdateNotification_GetUpdateTimestamp(intptr_t obj) {
    return 0;
}
intptr_t ovr_PartyUpdateNotification_GetUserAlias(intptr_t obj) {
    return 0;
}
uint64_t ovr_PartyUpdateNotification_GetUserId(intptr_t obj) {
    return 0;
}
intptr_t ovr_PartyUpdateNotification_GetUserName(intptr_t obj) {
    return 0;
}
intptr_t ovr_Pid_GetId(intptr_t obj) {
    return 0;
}
intptr_t ovr_PidArray_GetElement(intptr_t obj, uintptr_t index) {
    return 0;
}
uintptr_t ovr_PidArray_GetSize(intptr_t obj) {
    return 0;
}
uint64_t ovr_PingResult_GetID(intptr_t obj) {
    return 0;
}
unsigned long ovr_PingResult_GetPingTimeUsec(intptr_t obj) {
    return 0;
}
bool ovr_PingResult_IsTimeout(intptr_t obj) {
    return 0;
}
PlatformInitializeResult ovr_PlatformInitialize_GetResult(intptr_t obj) {
    return 0;
}
uint ovr_Price_GetAmountInHundredths(intptr_t obj) {
    return 0;
}
intptr_t ovr_Price_GetCurrency(intptr_t obj) {
    return 0;
}
intptr_t ovr_Price_GetFormatted(intptr_t obj) {
    return 0;
}
intptr_t ovr_Product_GetDescription(intptr_t obj) {
    return 0;
}
intptr_t ovr_Product_GetFormattedPrice(intptr_t obj) {
    return 0;
}
intptr_t ovr_Product_GetName(intptr_t obj) {
    return 0;
}
intptr_t ovr_Product_GetSKU(intptr_t obj) {
    return 0;
}
intptr_t ovr_ProductArray_GetElement(intptr_t obj, uintptr_t index) {
    return 0;
}
intptr_t ovr_ProductArray_GetNextUrl(intptr_t obj) {
    return 0;
}
uintptr_t ovr_ProductArray_GetSize(intptr_t obj) {
    return 0;
}
bool ovr_ProductArray_HasNextPage(intptr_t obj) {
    return 0;
}
intptr_t ovr_Purchase_GetDeveloperPayload(intptr_t obj) {
    return 0;
}
unsigned long ovr_Purchase_GetExpirationTime(intptr_t obj) {
    return 0;
}
unsigned long ovr_Purchase_GetGrantTime(intptr_t obj) {
    return 0;
}
uint64_t ovr_Purchase_GetPurchaseID(intptr_t obj) {
    return 0;
}
intptr_t ovr_Purchase_GetPurchaseStrID(intptr_t obj) {
    return 0;
}
intptr_t ovr_Purchase_GetReportingId(intptr_t obj) {
    return 0;
}
intptr_t ovr_Purchase_GetSKU(intptr_t obj) {
    return 0;
}
intptr_t ovr_PurchaseArray_GetElement(intptr_t obj, uintptr_t index) {
    return 0;
}
intptr_t ovr_PurchaseArray_GetNextUrl(intptr_t obj) {
    return 0;
}
uintptr_t ovr_PurchaseArray_GetSize(intptr_t obj) {
    return 0;
}
bool ovr_PurchaseArray_HasNextPage(intptr_t obj) {
    return 0;
}
bool ovr_RejoinDialogResult_GetRejoinSelected(intptr_t obj) {
    return 0;
}
uint64_t ovr_Room_GetApplicationID(intptr_t obj) {
    return 0;
}
intptr_t ovr_Room_GetDataStore(intptr_t obj) {
    return 0;
}
intptr_t ovr_Room_GetDescription(intptr_t obj) {
    return 0;
}
uint64_t ovr_Room_GetID(intptr_t obj) {
    return 0;
}
intptr_t ovr_Room_GetInvitedUsers(intptr_t obj) {
    return 0;
}
bool ovr_Room_GetIsMembershipLocked(intptr_t obj) {
    return 0;
}
RoomJoinPolicy ovr_Room_GetJoinPolicy(intptr_t obj) {
    return 0;
}
RoomJoinability ovr_Room_GetJoinability(intptr_t obj) {
    return 0;
}
intptr_t ovr_Room_GetMatchedUsers(intptr_t obj) {
    return 0;
}
uint ovr_Room_GetMaxUsers(intptr_t obj) {
    return 0;
}
intptr_t ovr_Room_GetName(intptr_t obj) {
    return 0;
}
intptr_t ovr_Room_GetOwner(intptr_t obj) {
    return 0;
}
intptr_t ovr_Room_GetTeams(intptr_t obj) {
    return 0;
}
RoomType ovr_Room_GetType(intptr_t obj) {
    return 0;
}
intptr_t ovr_Room_GetUsers(intptr_t obj) {
    return 0;
}
uint ovr_Room_GetVersion(intptr_t obj) {
    return 0;
}
intptr_t ovr_RoomArray_GetElement(intptr_t obj, uintptr_t index) {
    return 0;
}
intptr_t ovr_RoomArray_GetNextUrl(intptr_t obj) {
    return 0;
}
uintptr_t ovr_RoomArray_GetSize(intptr_t obj) {
    return 0;
}
bool ovr_RoomArray_HasNextPage(intptr_t obj) {
    return 0;
}
uint64_t ovr_RoomInviteNotification_GetID(intptr_t obj) {
    return 0;
}
uint64_t ovr_RoomInviteNotification_GetRoomID(intptr_t obj) {
    return 0;
}
uint64_t ovr_RoomInviteNotification_GetSenderID(intptr_t obj) {
    return 0;
}
unsigned long ovr_RoomInviteNotification_GetSentTime(intptr_t obj) {
    return 0;
}
intptr_t ovr_RoomInviteNotificationArray_GetElement(intptr_t obj, uintptr_t index) {
    return 0;
}
intptr_t ovr_RoomInviteNotificationArray_GetNextUrl(intptr_t obj) {
    return 0;
}
uintptr_t ovr_RoomInviteNotificationArray_GetSize(intptr_t obj) {
    return 0;
}
bool ovr_RoomInviteNotificationArray_HasNextPage(intptr_t obj) {
    return 0;
}
SdkAccountType ovr_SdkAccount_GetAccountType(intptr_t obj) {
    return 0;
}
uint64_t ovr_SdkAccount_GetUserId(intptr_t obj) {
    return 0;
}
intptr_t ovr_SdkAccountArray_GetElement(intptr_t obj, uintptr_t index) {
    return 0;
}
uintptr_t ovr_SdkAccountArray_GetSize(intptr_t obj) {
    return 0;
}
intptr_t ovr_SendInvitesResult_GetInvites(intptr_t obj) {
    return 0;
}
ShareMediaStatus ovr_ShareMediaResult_GetStatus(intptr_t obj) {
    return 0;
}
uint64_t ovr_SupplementaryMetric_GetID(intptr_t obj) {
    return 0;
}
long ovr_SupplementaryMetric_GetMetric(intptr_t obj) {
    return 0;
}
enum VoipMuteState ovr_SystemVoipState_GetMicrophoneMuted(intptr_t obj) {
    return 0;
}
SystemVoipStatus ovr_SystemVoipState_GetStatus(intptr_t obj) {
    return 0;
}
intptr_t ovr_Team_GetAssignedUsers(intptr_t obj) {
    return 0;
}
int ovr_Team_GetMaxUsers(intptr_t obj) {
    return 0;
}
int ovr_Team_GetMinUsers(intptr_t obj) {
    return 0;
}
intptr_t ovr_Team_GetName(intptr_t obj) {
    return 0;
}
intptr_t ovr_TeamArray_GetElement(intptr_t obj, uintptr_t index) {
    return 0;
}
uintptr_t ovr_TeamArray_GetSize(intptr_t obj) {
    return 0;
}
intptr_t ovr_TestUser_GetAccessToken(intptr_t obj) {
    return 0;
}
intptr_t ovr_TestUser_GetAppAccessArray(intptr_t obj) {
    return 0;
}
intptr_t ovr_TestUser_GetFbAppAccessArray(intptr_t obj) {
    return 0;
}
intptr_t ovr_TestUser_GetFriendAccessToken(intptr_t obj) {
    return 0;
}
intptr_t ovr_TestUser_GetFriendAppAccessArray(intptr_t obj) {
    return 0;
}
intptr_t ovr_TestUser_GetUserAlias(intptr_t obj) {
    return 0;
}
uint64_t ovr_TestUser_GetUserFbid(intptr_t obj) {
    return 0;
}
uint64_t ovr_TestUser_GetUserId(intptr_t obj) {
    return 0;
}
intptr_t ovr_TestUserAppAccess_GetAccessToken(intptr_t obj) {
    return 0;
}
uint64_t ovr_TestUserAppAccess_GetAppId(intptr_t obj) {
    return 0;
}
uint64_t ovr_TestUserAppAccess_GetUserId(intptr_t obj) {
    return 0;
}
intptr_t ovr_TestUserAppAccessArray_GetElement(intptr_t obj, uintptr_t index) {
    return 0;
}
uintptr_t ovr_TestUserAppAccessArray_GetSize(intptr_t obj) {
    return 0;
}
intptr_t ovr_User_GetDisplayName(intptr_t obj) {
    return 0;
}
uint64_t ovr_User_GetID(intptr_t obj) {
    return 0;
}
intptr_t ovr_User_GetImageUrl(intptr_t obj) {
    return 0;
}
intptr_t ovr_User_GetInviteToken(intptr_t obj) {
    return 0;
}
intptr_t ovr_User_GetOculusID(intptr_t obj) {
    return 0;
}
intptr_t ovr_User_GetPresence(intptr_t obj) {
    return 0;
}
intptr_t ovr_User_GetPresenceDeeplinkMessage(intptr_t obj) {
    return 0;
}
intptr_t ovr_User_GetPresenceDestinationApiName(intptr_t obj) {
    return 0;
}
intptr_t ovr_User_GetPresenceLobbySessionId(intptr_t obj) {
    return 0;
}
intptr_t ovr_User_GetPresenceMatchSessionId(intptr_t obj) {
    return 0;
}
UserPresenceStatus ovr_User_GetPresenceStatus(intptr_t obj) {
    return 0;
}
intptr_t ovr_User_GetSmallImageUrl(intptr_t obj) {
    return 0;
}
intptr_t ovr_UserAndRoom_GetRoom(intptr_t obj) {
    return 0;
}
intptr_t ovr_UserAndRoom_GetUser(intptr_t obj) {
    return 0;
}
intptr_t ovr_UserAndRoomArray_GetElement(intptr_t obj, uintptr_t index) {
    return 0;
}
intptr_t ovr_UserAndRoomArray_GetNextUrl(intptr_t obj) {
    return 0;
}
uintptr_t ovr_UserAndRoomArray_GetSize(intptr_t obj) {
    return 0;
}
bool ovr_UserAndRoomArray_HasNextPage(intptr_t obj) {
    return 0;
}
intptr_t ovr_UserArray_GetElement(intptr_t obj, uintptr_t index) {
    return 0;
}
intptr_t ovr_UserArray_GetNextUrl(intptr_t obj) {
    return 0;
}
uintptr_t ovr_UserArray_GetSize(intptr_t obj) {
    return 0;
}
bool ovr_UserArray_HasNextPage(intptr_t obj) {
    return 0;
}
intptr_t ovr_UserCapability_GetDescription(intptr_t obj) {
    return 0;
}
bool ovr_UserCapability_GetIsEnabled(intptr_t obj) {
    return 0;
}
intptr_t ovr_UserCapability_GetName(intptr_t obj) {
    return 0;
}
intptr_t ovr_UserCapability_GetReasonCode(intptr_t obj) {
    return 0;
}
intptr_t ovr_UserCapabilityArray_GetElement(intptr_t obj, uintptr_t index) {
    return 0;
}
intptr_t ovr_UserCapabilityArray_GetNextUrl(intptr_t obj) {
    return 0;
}
uintptr_t ovr_UserCapabilityArray_GetSize(intptr_t obj) {
    return 0;
}
bool ovr_UserCapabilityArray_HasNextPage(intptr_t obj) {
    return 0;
}
bool ovr_UserDataStoreUpdateResponse_GetSuccess(intptr_t obj) {
    return 0;
}
intptr_t ovr_UserProof_GetNonce(intptr_t obj) {
    return 0;
}
bool ovr_UserReportID_GetDidCancel(intptr_t obj) {
    return 0;
}
uint64_t ovr_UserReportID_GetID(intptr_t obj) {
    return 0;
}
void ovr_VoipDecoder_Decode(intptr_t obj, uint8_t *compressedData, uintptr_t compressedSize) {
    return;
}
uintptr_t ovr_VoipDecoder_GetDecodedPCM(intptr_t obj, float *outputBuffer, uintptr_t outputBufferSize) {
    return 0;
}
void ovr_VoipEncoder_AddPCM(intptr_t obj, float *inputData, uint inputSize) {
    return;
}
uintptr_t ovr_VoipEncoder_GetCompressedData(intptr_t obj, uint8_t *outputBuffer, uintptr_t intputSize) {
    return 0;
}
uintptr_t ovr_VoipEncoder_GetCompressedDataSize(intptr_t obj) {
    return 0;
}
intptr_t ovr_AbuseReportOptions_Create() {
    return 0;
}
void ovr_AbuseReportOptions_Destroy(intptr_t handle) {
    return;
}
void ovr_AbuseReportOptions_SetPreventPeopleChooser(intptr_t handle, bool value) {
    return;
}
void ovr_AbuseReportOptions_SetReportType(intptr_t handle, AbuseReportType value) {
    return;
}
intptr_t ovr_AdvancedAbuseReportOptions_Create() {
    return 0;
}
void ovr_AdvancedAbuseReportOptions_Destroy(intptr_t handle) {
    return;
}
void ovr_AdvancedAbuseReportOptions_SetDeveloperDefinedContextString(intptr_t handle, intptr_t key, intptr_t value) {
    return;
}
void ovr_AdvancedAbuseReportOptions_ClearDeveloperDefinedContext(intptr_t handle) {
    return;
}
void ovr_AdvancedAbuseReportOptions_SetObjectType(intptr_t handle, intptr_t value) {
    return;
}
void ovr_AdvancedAbuseReportOptions_SetReportType(intptr_t handle, AbuseReportType value) {
    return;
}
void ovr_AdvancedAbuseReportOptions_AddSuggestedUser(intptr_t handle, uint64_t value) {
    return;
}
void ovr_AdvancedAbuseReportOptions_ClearSuggestedUsers(intptr_t handle) {
    return;
}
void ovr_AdvancedAbuseReportOptions_SetVideoMode(intptr_t handle, AbuseReportVideoMode value) {
    return;
}
intptr_t ovr_ApplicationOptions_Create() {
    return 0;
}
void ovr_ApplicationOptions_Destroy(intptr_t handle) {
    return;
}
void ovr_ApplicationOptions_SetDeeplinkMessage(intptr_t handle, intptr_t value) {
    return;
}
void ovr_ApplicationOptions_SetDestinationApiName(intptr_t handle, intptr_t value) {
    return;
}
void ovr_ApplicationOptions_SetLobbySessionId(intptr_t handle, intptr_t value) {
    return;
}
void ovr_ApplicationOptions_SetMatchSessionId(intptr_t handle, intptr_t value) {
    return;
}
void ovr_ApplicationOptions_SetRoomId(intptr_t handle, uint64_t value) {
    return;
}
intptr_t ovr_AvatarEditorOptions_Create() {
    return 0;
}
void ovr_AvatarEditorOptions_Destroy(intptr_t handle) {
    return;
}
void ovr_AvatarEditorOptions_SetSourceOverride(intptr_t handle, intptr_t value) {
    return;
}
intptr_t ovr_ChallengeOptions_Create() {
    return 0;
}
void ovr_ChallengeOptions_Destroy(intptr_t handle) {
    return;
}
void ovr_ChallengeOptions_SetDescription(intptr_t handle, intptr_t value) {
    return;
}
void ovr_ChallengeOptions_SetEndDate(intptr_t handle, unsigned long value) {
    return;
}
void ovr_ChallengeOptions_SetIncludeActiveChallenges(intptr_t handle, bool value) {
    return;
}
void ovr_ChallengeOptions_SetIncludeFutureChallenges(intptr_t handle, bool value) {
    return;
}
void ovr_ChallengeOptions_SetIncludePastChallenges(intptr_t handle, bool value) {
    return;
}
void ovr_ChallengeOptions_SetLeaderboardName(intptr_t handle, intptr_t value) {
    return;
}
void ovr_ChallengeOptions_SetStartDate(intptr_t handle, unsigned long value) {
    return;
}
void ovr_ChallengeOptions_SetTitle(intptr_t handle, intptr_t value) {
    return;
}
void ovr_ChallengeOptions_SetViewerFilter(intptr_t handle, ChallengeViewerFilter value) {
    return;
}
void ovr_ChallengeOptions_SetVisibility(intptr_t handle, ChallengeVisibility value) {
    return;
}
intptr_t ovr_GroupPresenceOptions_Create() {
    return 0;
}
void ovr_GroupPresenceOptions_Destroy(intptr_t handle) {
    return;
}
void ovr_GroupPresenceOptions_SetDeeplinkMessageOverride(intptr_t handle, intptr_t value) {
    return;
}
void ovr_GroupPresenceOptions_SetDestinationApiName(intptr_t handle, intptr_t value) {
    return;
}
void ovr_GroupPresenceOptions_SetIsJoinable(intptr_t handle, bool value) {
    return;
}
void ovr_GroupPresenceOptions_SetLobbySessionId(intptr_t handle, intptr_t value) {
    return;
}
void ovr_GroupPresenceOptions_SetMatchSessionId(intptr_t handle, intptr_t value) {
    return;
}
intptr_t ovr_InviteOptions_Create() {
    return 0;
}
void ovr_InviteOptions_Destroy(intptr_t handle) {
    return;
}
void ovr_InviteOptions_AddSuggestedUser(intptr_t handle, uint64_t value) {
    return;
}
void ovr_InviteOptions_ClearSuggestedUsers(intptr_t handle) {
    return;
}
intptr_t ovr_MatchmakingOptions_Create() {
    return 0;
}
void ovr_MatchmakingOptions_Destroy(intptr_t handle) {
    return;
}
void ovr_MatchmakingOptions_SetCreateRoomDataStoreString(intptr_t handle, intptr_t key, intptr_t value) {
    return;
}
void ovr_MatchmakingOptions_ClearCreateRoomDataStore(intptr_t handle) {
    return;
}
void ovr_MatchmakingOptions_SetCreateRoomJoinPolicy(intptr_t handle, RoomJoinPolicy value) {
    return;
}
void ovr_MatchmakingOptions_SetCreateRoomMaxUsers(intptr_t handle, uint value) {
    return;
}
void ovr_MatchmakingOptions_AddEnqueueAdditionalUser(intptr_t handle, uint64_t value) {
    return;
}
void ovr_MatchmakingOptions_ClearEnqueueAdditionalUsers(intptr_t handle) {
    return;
}
void ovr_MatchmakingOptions_SetEnqueueDataSettingsInt(intptr_t handle, intptr_t key, int value) {
    return;
}
void ovr_MatchmakingOptions_SetEnqueueDataSettingsDouble(intptr_t handle, intptr_t key, double value) {
    return;
}
void ovr_MatchmakingOptions_SetEnqueueDataSettingsString(intptr_t handle, intptr_t key, intptr_t value) {
    return;
}
void ovr_MatchmakingOptions_ClearEnqueueDataSettings(intptr_t handle) {
    return;
}
void ovr_MatchmakingOptions_SetEnqueueIsDebug(intptr_t handle, bool value) {
    return;
}
void ovr_MatchmakingOptions_SetEnqueueQueryKey(intptr_t handle, intptr_t value) {
    return;
}
intptr_t ovr_MultiplayerErrorOptions_Create() {
    return 0;
}
void ovr_MultiplayerErrorOptions_Destroy(intptr_t handle) {
    return;
}
void ovr_MultiplayerErrorOptions_SetErrorKey(intptr_t handle, MultiplayerErrorErrorKey value) {
    return;
}
intptr_t ovr_NetSyncOptions_Create() {
    return 0;
}
void ovr_NetSyncOptions_Destroy(intptr_t handle) {
    return;
}
void ovr_NetSyncOptions_SetVoipGroup(intptr_t handle, intptr_t value) {
    return;
}
void ovr_NetSyncOptions_SetVoipStreamDefault(intptr_t handle, NetSyncVoipStreamMode value) {
    return;
}
void ovr_NetSyncOptions_SetZoneId(intptr_t handle, intptr_t value) {
    return;
}
intptr_t ovr_RichPresenceOptions_Create() {
    return 0;
}
void ovr_RichPresenceOptions_Destroy(intptr_t handle) {
    return;
}
void ovr_RichPresenceOptions_SetApiName(intptr_t handle, intptr_t value) {
    return;
}
void ovr_RichPresenceOptions_SetArgsString(intptr_t handle, intptr_t key, intptr_t value) {
    return;
}
void ovr_RichPresenceOptions_ClearArgs(intptr_t handle) {
    return;
}
void ovr_RichPresenceOptions_SetCurrentCapacity(intptr_t handle, uint value) {
    return;
}
void ovr_RichPresenceOptions_SetDeeplinkMessageOverride(intptr_t handle, intptr_t value) {
    return;
}
void ovr_RichPresenceOptions_SetEndTime(intptr_t handle, unsigned long value) {
    return;
}
void ovr_RichPresenceOptions_SetExtraContext(intptr_t handle, RichPresenceExtraContext value) {
    return;
}
void ovr_RichPresenceOptions_SetInstanceId(intptr_t handle, intptr_t value) {
    return;
}
void ovr_RichPresenceOptions_SetIsIdle(intptr_t handle, bool value) {
    return;
}
void ovr_RichPresenceOptions_SetIsJoinable(intptr_t handle, bool value) {
    return;
}
void ovr_RichPresenceOptions_SetJoinableId(intptr_t handle, intptr_t value) {
    return;
}
void ovr_RichPresenceOptions_SetLobbySessionId(intptr_t handle, intptr_t value) {
    return;
}
void ovr_RichPresenceOptions_SetMatchSessionId(intptr_t handle, intptr_t value) {
    return;
}
void ovr_RichPresenceOptions_SetMaxCapacity(intptr_t handle, uint value) {
    return;
}
void ovr_RichPresenceOptions_SetStartTime(intptr_t handle, unsigned long value) {
    return;
}
intptr_t ovr_RoomOptions_Create() {
    return 0;
}
void ovr_RoomOptions_Destroy(intptr_t handle) {
    return;
}
void ovr_RoomOptions_SetDataStoreString(intptr_t handle, intptr_t key, intptr_t value) {
    return;
}
void ovr_RoomOptions_ClearDataStore(intptr_t handle) {
    return;
}
void ovr_RoomOptions_SetExcludeRecentlyMet(intptr_t handle, bool value) {
    return;
}
void ovr_RoomOptions_SetMaxUserResults(intptr_t handle, uint value) {
    return;
}
void ovr_RoomOptions_SetOrdering(intptr_t handle, UserOrdering value) {
    return;
}
void ovr_RoomOptions_SetRecentlyMetTimeWindow(intptr_t handle, TimeWindow value) {
    return;
}
void ovr_RoomOptions_SetRoomId(intptr_t handle, uint64_t value) {
    return;
}
void ovr_RoomOptions_SetTurnOffUpdates(intptr_t handle, bool value) {
    return;
}
intptr_t ovr_RosterOptions_Create() {
    return 0;
}
void ovr_RosterOptions_Destroy(intptr_t handle) {
    return;
}
void ovr_RosterOptions_AddSuggestedUser(intptr_t handle, uint64_t value) {
    return;
}
void ovr_RosterOptions_ClearSuggestedUsers(intptr_t handle) {
    return;
}
intptr_t ovr_UserOptions_Create() {
    return 0;
}
void ovr_UserOptions_Destroy(intptr_t handle) {
    return;
}
void ovr_UserOptions_SetMaxUsers(intptr_t handle, uint value) {
    return;
}
void ovr_UserOptions_AddServiceProvider(intptr_t handle, ServiceProvider value) {
    return;
}
void ovr_UserOptions_ClearServiceProviders(intptr_t handle) {
    return;
}
void ovr_UserOptions_SetTimeWindow(intptr_t handle, TimeWindow value) {
    return;
}
intptr_t ovr_VoipOptions_Create() {
    return 0;
}
void ovr_VoipOptions_Destroy(intptr_t handle) {
    return;
}
void ovr_VoipOptions_SetBitrateForNewConnections(intptr_t handle, VoipBitrate value) {
    return;
}
void ovr_VoipOptions_SetCreateNewConnectionUseDtx(intptr_t handle, VoipDtxState value);