#ifndef _WS_BW_CONTROL_DEF_H_
#define _WS_BW_CONTROL_DEF_H_

#include "HieServer_Common.h"
#include "ws_comm_debug.h"
#include "ws_comm_av.h"
#include "ws_comm_data.h"

using namespace ws_soft;

enum eBWControlType
{
    eBWControlTypeBegin        = 0,
    eBWControlRoute,    //��·��Ϊ��λ���е���
    eBWControlTerminal,//���ն�Ϊ��λ���е���
    eBWControlClient,//�Կͻ���Ϊ��λ���е���
    eBWControlTypeEnd,
};

typedef enum _eBWStreamSpeed
{
	eHistSpeedBegin,								/* ��ʼֵ			*/
	eHistSpeedQuarter,								/* 1/4���ٶȲ���	*/
	eHistSpeedHalf, 								/* 1/2���ٶȲ���	*/
	eHistSpeedNormal,								/* �����ٶȲ���		*/
	eHistSpeedTwo,									/* 2���ٶȲ���		*/
	eHistSpeedFour,									/* 4���ٶȲ���		*/
	eHistSpeedEight,								/* 8���ٶȲ���		*/
	eHistSpeedSixteen,								/* 16���ٶȲ���		*/
	eHistSpeedSingle,								/* ��֡���ٶȲ��� 	*/
	eHistSpeedEnd,									/* ����ֵ	9    	*/
	
	eDynamicAdjustSpeedBegin,	
	eDynamicAdjustSpeedOne,							/* ��λ1 */	
	eDynamicAdjustSpeedTwo,							/* ��λ2 */
	eDynamicAdjustSpeedThree,						/* ��λ3 */		
	eDynamicAdjustSpeedFour,						/* ��λ4 */
	eDynamicAdjustSpeedFive,						/* ��λ5 */
	eDynamicAdjustSpeedSix,							/* ��λ6 */
	eDynamicAdjustSpeedEnd,							/* 17 */


	eRealStreamSpeedBegin,	
	eRealStreamSpeedOneThirdIFrame,					/* ������I֡��һ��I֡	*/
	eRealStreamSpeedHalfIFrame,						/* ��һ��I֡��һ��I֡	*/
	eRealStreamSpeedIFrame,							/* ֻ��I֡ 		21		*/
	eRealStreamSpeedIPFrame,						/* I֡P֡����			*/
	eRealStreamSpeedEnd,
}eBWStreamSpeed;
enum eBWTaskType
{
    eBWTaskTypeBegin        = 0,
    eBWTaskSpeedAuto,
    eBWTaskSpeedManual,
    eBWTaskTypeEnd,
};

typedef struct _stream_info
{
    eProtocolID		protocol;
    DWORD           dwMediaSessionID;//!<ý��ỰID
    char            cRouteIP[IP_ADDRESS_LEN];            //·��WAN��IP��ַ��    // ������Ϊ0
    char            cRouteMAC[MAC_ADDRESS_LEN];      //·��WAN��MAC��ַ��   // ������Ϊ0
    char            cTeminalIP[IP_ADDRESS_LEN];             //�ն�IP��ַ��// һ���ն��Ͽ����ж���ͻ���
    char            cTeminalMAC[MAC_ADDRESS_LEN];       //�ն�MAC��ַ
    int                     iClientID;                      //�ͻ���ID��    // ��¼�û�ID���豸������ID
    eBWTaskType         BWTaskType;     //�������ͣ�// �ʹ���Э���Զ����������û��ֹ�����
    int                     iVideoChannel;              //��������ͨ���ţ�              // ��Ƶͨ����
    bool                bSameRoute;           //Ϊ�������ͬһ��·��
    eMediaStreamType streamType;        //ʵʱ������ʷ����������
    ws_venc_str_type    streamVencType;//����������������
} StreamInfo;

typedef struct _BWLostInfo   //�ͻ�����������Ϣ
{
    char                cDeviceID[48];//�豸UID
    DWORD              dwMediaSessionID;             //�����������ĻỰID��
    int                     iRcvPacket;            //��ǰͳ�ƽ����ܰ�����
    int                     iLostPacket;            //��ǰͳ�ƶ�ʧ�ܰ�����
} BWLostInfo;

#define MAX_BW_LOST_LOG_COUNT (10)
#define MAX_MEDIA_SESSION (128 + 128 + 1)
#endif  /*#ifndef _WS_BW_CONTROL_DEF_H_*/
