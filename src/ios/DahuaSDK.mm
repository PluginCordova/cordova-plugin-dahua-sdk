/* DahuaSDK.m */

#import "DahuaSDK.h"
#import <Cordova/CDV.h>

#import "global_macro_define.h"
#import "Global.h"

static BOOL bStart = YES;
static LLONG lTalkHandle = 0;
static int m_nPort = 99;

@implementation DahuaSDK

- (void)login:(CDVInvokedUrlCommand*)command
{
    CDVPluginResult* pluginResult = nil;
    NSString* ip = [command.arguments objectAtIndex:0];
    NSString* port = [command.arguments objectAtIndex:1];
    NSString* user = [command.arguments objectAtIndex:2];
    NSString* passwd = [command.arguments objectAtIndex:3];

    if (ip == nil || [ip length] == 0) {
        pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_ERROR];
    } else {
        int nSpecCap = 0;
        int nError = 0;
        NET_DEVICEINFO devInfo = {};
        
        LLONG lLoginID = CLIENT_LoginEx((char*)[ip UTF8String], [port intValue], (char*)[user UTF8String], (char*)[passwd UTF8String], nSpecCap, NULL, &devInfo, &nError);
        
        g_loginID = lLoginID;
        
        if (lLoginID)
        {
            pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK messageAsString:@"success"];
        }else {
            NSString* error;
            switch (nError)
            {
                case 1:
                    error = @"login_error_pwd";
                    break;
                    
                case 2:
                    error = @"login_error_account";
                    break;
                    
                case 3:
                    error = @"login_error_overtime";
                    break;
                    
                case 4:
                    error = @"login_error_registered";
                    break;
                    
                case 5:
                    error = @"login_error_locked";
                    break;
                    
                case 6:
                    error = @"login_error_inblacklist";
                    break;
                    
                case 7:
                    error = @"login_error_busy";
                    break;
                    
                case 10:
                    error = @"login_error_maxaccount";
                    break;
                    
                default:
                    error = @"login_error_connect";
                    break;
            }
            
            pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_ERROR messageAsString:error];
        }
    }

    [self.commandDelegate sendPluginResult:pluginResult callbackId:command.callbackId];
}


- (void)talk:(CDVInvokedUrlCommand*)command
{
    CDVPluginResult* pluginResult = nil;
    
    if (bStart) {
        DHDEV_TALKDECODE_INFO stuTalkMode;
        stuTalkMode.encodeType = DH_TALK_PCM;
        stuTalkMode.dwSampleRate = 8000;
        stuTalkMode.nAudioBit = 16;
        stuTalkMode.nPacketPeriod = 0;
        BOOL bSul = CLIENT_SetDeviceMode(g_loginID, DH_TALK_ENCODE_TYPE, &stuTalkMode);
        
        NET_SPEAK_PARAM stuParam = {0};
        stuParam.dwSize = sizeof(NET_SPEAK_PARAM);
        stuParam.nMode = (int)0;
        stuParam.bEnableWait = NO;
        bSul = CLIENT_SetDeviceMode(g_loginID, DH_TALK_SPEAK_PARAM, &stuParam);
        
        bSul = CLIENT_SetDeviceMode(g_loginID, DH_TALK_CLIENT_MODE, NULL);
        BOOL bRet = [self StartAudioRecord];
        if (bRet) {
            lTalkHandle = CLIENT_StartTalkEx(g_loginID, AudioDataCallBack,NULL);
            if(lTalkHandle == 0){
                CLIENT_StopTalk(lTalkHandle);
            }
            bStart = NO;
        }
    }
    else{
        [self stopAudioRecord];
        CLIENT_StopTalkEx(lTalkHandle);
        lTalkHandle = 0;
        bStart = YES;
        
    }
        
    pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK messageAsString:@"ok"];
    

    [self.commandDelegate sendPluginResult:pluginResult callbackId:command.callbackId];
}


void CALLBACK AudioDataCallBack(LLONG lTalkHandle, char *pDataBuf, DWORD dwBufSize, BYTE byAudioFlag, LDWORD dwUser){
    if (1 == byAudioFlag) {
        PLAY_InputData(m_nPort, (BYTE*)pDataBuf, dwBufSize);
    }
}
void CALLBACK AudioCallFunction(LPBYTE pDataBuffer, DWORD DataLength, void* pUserData){
    char* pCbData = NULL;
    pCbData = new char[102400];
    if (NULL == pCbData)
    {
        return;
    }
    int  iCbLen = 0;
    
    pCbData[0]=0x00;
    pCbData[1]=0x00;
    pCbData[2]=0x01;
    pCbData[3]=0xF0;
    
    pCbData[4]=0x0C;
    pCbData[5]=0x02;
    
    *(DWORD*)(pCbData+6)=DataLength;
    memcpy(pCbData+8, pDataBuffer, DataLength);
    
    iCbLen = 8+DataLength;
    CLIENT_TalkSendData(*(LLONG*)pUserData, (char*)pCbData, DataLength);
    delete pCbData;
    pCbData = NULL;
}

-(BOOL) StartAudioRecord
{
    //定义帧长
    int nFrameLength = 1024;
    
    
    BOOL bRet = FALSE;
    
    //    Then call PLAYSDK library to begin recording audio
    bool bOpenRet = PLAY_OpenStream(m_nPort,0,0,1024*100);
    if(bOpenRet)
    {
        BOOL bPlayRet = PLAY_Play(m_nPort,0);
        if(bPlayRet)
        {
            PLAY_PlaySoundShare(m_nPort);
            BOOL bSuccess = PLAY_OpenAudioRecord(AudioCallFunction,16,8000,nFrameLength,0,&lTalkHandle);
            if(bSuccess)
            {
                bRet = TRUE;
            }
            else
            {
                PLAY_StopSoundShare(m_nPort);
                PLAY_Stop(m_nPort);
                PLAY_CloseStream(m_nPort);
            }
        }
        else
        {
            PLAY_CloseStream(m_nPort);
        }
    }
    
    return bRet;
}

-(void)stopAudioRecord {
    PLAY_CloseAudioRecord();
    PLAY_Stop(m_nPort);
    PLAY_StopSoundShare(m_nPort);
    PLAY_CloseStream(m_nPort);
}

@end
