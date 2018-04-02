/*************************************************************************
 ** ��Ȩ����(C), 2001-2013, �㽭�󻪼����ɷ����޹�˾.
 ** ��Ȩ����.
 **
 ** $Id$
 **
 ** ��������   : Proxy Client C�����
 **
 ** �޸���ʷ     : 2013��12��23�� zhu_long Modification
*************************************************************************/

#ifndef _DAHUA_P2P_PROXY_CLIENT_CWRAP_H_
#define _DAHUA_P2P_PROXY_CLIENT_CWRAP_H_

#include "Defs.h"

#ifdef WIN32
	typedef unsigned __int64 UINT64;
#else
	typedef unsigned long long UINT64;
#endif

#ifdef  __cplusplus
extern "C" {
#endif

///\brief ����״̬
typedef enum
{
    DHProxyStateUnauthorized,           ///< ������֤ʧ�ܣ����кŷǷ�����Կ����
    DHProxyStateForbidden,              ///< �����ֹ��½���豸ID�ظ����������ܾ���
    DHProxyStateOffline,                ///< ��������
    DHProxyStateOnline,                 ///< ��������
} DHProxyClientProxyState;

///\brief P2Pͨ��״̬
typedef enum
{
    DHP2PChannelStateInit,              ///< P2Pͨ����ʼ����
    DHP2PChannelStateActive,            ///< P2Pͨ������ͨ
    DHP2PChannelStateNonExist,          ///< P2Pͨ��������
	DHP2PChannelStateUnauthorized,      ///< P2Pͨ����Ȩʧ��
} DHProxyClientP2PChannelState;

///\brief ӳ��˿�����ͳ��
typedef struct
{
    UINT64               recvBytes;     ///< �ܽ����ֽ�KB
    UINT64               sendBytes;     ///< �ܷ����ֽ�KB

    double               curRecvRate;   ///< ��ǰ��������Kb/s
    double               curSendRate;   ///< ��ǰ��������Kb/s

    double               lostRate;      ///< ������
    double               liveTime;      ///< ͨ���ʱ��(��S)
} DHProxyClientMapPortRate;

///\brief Զ�̴�����Ϣ
typedef struct
{
    char                remoteId[64];      ///< ������ID
    char                remoteIp[64];      ///< Զ�̴���IP
    int                 remotePort;        ///< Զ�̴���˿�
} DHProxyClientRemotePortInfo;

typedef enum
{
    DHP2POptionPortGuess,                 ///< �˿ڲ²�ѡ�� ����ֵ: 0 �ر� 1 ����
    DHP2POptionSetMTU,                    ///< MTUѡ��	  ����ֵ: ����ֵ
    DHP2POptionUPNP,                      ///< UPNPѡ��	  ����ֵ: 0 �ر� 1 ����
    DHP2POptionRelay,                     ///< Relayѡ��  ����ֵ: 0 ��֧����ת 1 ֧����ת
    DHP2POptionPTCPThreadNum,             ///< PTCP�߳���Ŀѡ��  ����ֵ: ����ֵ    
    DHP2POptionRecvBufSize,               ///< P2P���ջ�������С����λ:�ֽ�
    DHP2POptionPTCPSendBuffer,            ///< PTCP���ͻ�������С����λ:�ֽ�
    DHP2POptionPTCPRecvBuffer,            ///< PTCP���ջ�������С����λ:�ֽ�
    DHP2POptionSendBufSize,               ///< TCP���ͻ�������С����λ:�ֽ�
    DHP2POptionLocal,                     ///< Localѡ��     ����ֵ��0 ��֧�־��������� 1 ֧�־���������
    DHP2POptionLinkSwitch,                ///< ��·�л�ѡ��  ����ֵ: 0 �ر���·�л�  1 ֧����·�л�,��ѡ��ֻ�Դ���ͻ�����Ч
    DHP2POptionRemoteCommand,             ///< Զ������ѡ��  ����ֵ��0 �ر� 1 ����
    DHP2POptionMultiHolePunch,            ///< ���ش�ѡ��  ����ֵ: 0 �ر� 1 ����, Ĭ�Ͽ���
    DHP2POptionIceDefaultRange,           ///< ICEĬ�ϳ����µĲ²ⷶΧ
    DHP2POptionIceConeVsSymmRange,        ///< ICEԲ׶����Գ��ͳ����µĲ²ⷶΧ
    DHP2POptionIceSymmVsSymmRange,        ///< ICE�Գ�����Գ��ͳ����µĲ²ⷶΧ
    DHP2POptionLinkSwitchSpace,           ///< ��·�л����
}DHProxyOption;


///\brief ��־����
typedef enum
{
    DHProxyLogLevelSilent,                /// < �ü��𲻴�ӡ��Ϣ
    DHProxyLogLevelErr,                   /// < ��������
    DHProxyLogLevelWarning,               /// < ���ܵ��³���
    DHProxyLogLevelInfo,                  /// < ��֪�û�����ǰ����״̬
    DHProxyLogLevelTrace,                 /// < ������Ϣ
    DHProxyLogLevelDebug                  /// < ��ϸ������Ϣ
}DHProxyLogLevel;

///\brief ���
typedef void*	ProxyClientHandler;

///\bried �ͻ����ϱ���͸��Ϣ�ص�
///\param deviceId    �豸���к�
///\param deviceIp    �豸��NAT���IP
///\param devicePort  �豸��NAT��Ķ˿�
///\param clientIp    �ͻ���NAT���IP
///\param clientPort  �ͻ���NAT��Ķ˿�
///\param linkType    ��������(0:������; 1:P2P; 2:ת��)
typedef void (* DHP2PTraversalInfoHandler)(const char *deviceId, const char *deviceIp, const int devicePort, const char *clientIp, const int clientPort, const int linkType);

///\brief ��ʼ��
///\param[in]       svraddr  ������IP(�ݲ�֧������)
///\param[in]       svrport  �������˿�
///\param[in]       passwd   ��Կ
///\return 0ʧ��/������client���
///\note ���ʹ��UDP���أ��������ð�����󳤶ȣ�����ѡ��ΪDHP2POptionSetMTU��
///\     �������ֵ������1400�ֽ�
TOU_API ProxyClientHandler DHProxyClientInit(const char* svrip, int svrport, const char* passwd);

///\brief �ͷ���Դ
///\param[in]       handler  ʵ��client���
TOU_API void DHProxyClientRelease(ProxyClientHandler handler);

///\brief ͨ��Զ�̴����ӳ��(�첽ģʽ)
///\param[in]       handler  ʵ��client���
///\param[in]       deviceId    Զ�̴���ID
///\param[in]       targetPort  Ŀ��˿�
///\param[in,out]   localPort   ����ӳ��˿�,Ϊ0���ڲ��������һ���˿�
///\return 0��Ӷ˿�ӳ��ɹ�/-1��Ӷ˿�ӳ��ʧ��
///\note ͨ�������Ƿ�ɹ������DHProxyClientChannelstate�ӿڲ�ѯ
TOU_API int DHProxyClientAddPort(ProxyClientHandler handler,
		const char* deviceId, int targetPort, int *localPort);

///\brief ͨ��Զ�̴����ӳ��(ͬ��ģʽ)
///\param[in]       handler  ʵ��client���
///\param[in]       deviceId    Զ�̴���ID
///\param[in]       targetPort  Ŀ��˿�
///\param[in,out]   localPort   ����ӳ��˿�,Ϊ0���ڲ��������һ���˿�
///\param[in]       timeOut     ��ʱʱ��(��λ:����)
///\note timeOutΪ0�� �����ó�ʱʱ��, ֱ���н������
///\return 0ͨ�������ɹ�/-1ͨ������ʧ��
TOU_API int DHProxyClientAddPortSync(ProxyClientHandler handler, 
        const char *deviceId, int targetPort, int *localPort, unsigned int timeOut);

///\brief ɾ��һ��ӳ��
///\param[in]   handler  ʵ��client���
///\param[in]   port ����ӳ��˿�
///\return 0�ɹ�/-1ʧ��
TOU_API int DHProxyClientDelPort(ProxyClientHandler handler, int port);

///\brief ��ѯӳ��˿�����
///\param[in]   handler  ʵ��client���
///\param[in]   port ����ӳ��˿�
///\param[out]  rate ��ǰӳ������
///\return 0�ɹ�/-1ʧ��
TOU_API int DHProxyClientQueryRate(ProxyClientHandler handler,
		int port, DHProxyClientMapPortRate *rate);

///\brief ��ѯӳ��˿ڵ�P2Pͨ��״̬
///\param[in]   handler  ʵ��client���
///\param[in]   port ����ӳ��˿�
///\param[out]  state ��ǰӳ��˿�״̬�� @see DHProxyClientP2PChannelState
///\return 0�ɹ�/-1ʧ��
TOU_API int DHProxyClientChannelstate(ProxyClientHandler handler, int port, int *state);

///\brief ��ȡ��ǰ����ͻ���״̬
///\param[in]   handler  ʵ��client���
///\param[out] 	state  ��ǰ����ͻ���״̬, @see DHProxyClientProxyState
///\return 0�ɹ�/-1ʧ��
TOU_API int DHProxyClientState(ProxyClientHandler handler, int *state);

///\brief ��ѯԶ�̴����������״̬
///\param[in]   handler  ʵ��client���
///\param[in]   deviceId Զ�̴���ID
///\param[out] 	state ��ǰ���������״̬, @see DHProxyClientProxyState
///\return 0�ɹ�/-1ʧ��
TOU_API int DHProxyClientServerState(ProxyClientHandler handler, const char* deviceId, int *state);

///\brief ��ѯԶ�̴������������Ϣ
///\param[in]   handler  ʵ��client���
///\param[in]   port  ��������˿�
///\param[out]  info  Զ�̴����������Ϣ, @see DHProxyClientRemotePortInfo
///\return 0�ɹ�/-1ʧ��
TOU_API int DHProxyClientQueryRemoetInfo(ProxyClientHandler handler, int port, DHProxyClientRemotePortInfo *info);

///\breif ��ʼ��
///\param[in]       svraddr  ������IP(�ݲ�֧������)
///\param[in]       svrport  �������˿�
///\param[in]       passwd   ��Կ
///\param[in]       username   �û���
///\return 0ʧ��/������client���
TOU_API ProxyClientHandler DHProxyClientInitWtihName(const char* svrip, int svrport, const char* passwd, const char* username);

///\brief ����Proxyѡ��
///\param[in]   handler  ʵ��client���
///\param[in] option ProxyOptionö��
///\param[in] value ���ò���ֵ
///\return 0 �ɹ�; -1 ʧ��
///\note value���� @see ProxyOption
TOU_API	int DHProxySetOption(ProxyClientHandler handler, DHProxyOption option, int value);

///\brief ��ȡ��Ӧoption��ֵ
///\param[in] handler  ʵ��client���
///\param[in] option ProxyOptionö��
///\return �������õĲ���ֵ: -1 ʧ��; >=0 option��ֵ 
TOU_API int DHProxyGetOption(ProxyClientHandler handler, DHProxyOption option);

///\brief ������־����,���ڸü������־�������
///\param[in] handler   ʵ��client���
///\param[in] level     DHProxyLogLevelö��
///\note level���� @see DHProxyLogLevel
///\note Ĭ����־����Ϊ DHProxyLogLevelDebug
TOU_API void DHProxySetLogLevel(ProxyClientHandler handler, DHProxyLogLevel level);

///\brief ��ȡ�豸��Ϣ
///\param[in]      handler    ʵ��client���
///\param[in]      deviceId   �豸���к�
///\param[in]      bufferLen  �洢�豸��Ϣ�Ļ���������
///\param[out]     deviceInfo �豸��Ϣ
///\return true�ɹ�/falseʧ��
TOU_API bool DHProxyGetDeviceInfo(ProxyClientHandler handler, const char *deviceId, int bufferLen, char *deviceInfo);

///\brief ע���ϱ���͸��Ϣ�Ļص�
///\param[in]      handler         ʵ��client���
///\param[in]      reportHandler   ��͸��Ϣ�ϱ��Ļص����� @see DHP2PTraversalInfoHandler
///\note �ûص�������P2P���ϲ��ϱ���͸��Ϣ
///\note �����ڸûص��д����ϲ�ҵ�񣬷�ֹ����P2P�ڲ��߳�
TOU_API void DHProxyRegP2PTraversalInfoHandler(ProxyClientHandler handler, const DHP2PTraversalInfoHandler reportHandler);

#ifdef  __cplusplus
}
#endif

#endif /* _DAHUA_P2P_PROXY_CLIENT_CWRAP_H_ */
