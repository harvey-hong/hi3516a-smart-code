#ifndef HIE_SERVER_CFG_H
#define HIE_SERVER_CFG_H

/**************************************************************************
 *                           ���Ͷ���                                     *
 **************************************************************************/

//1500ϵ��
#define	DVR_1500_4CIF		1	/*! 4· CIFǶ��ʽ */
#define	DVR_1500_8CIF		2	/*! 8· CIFǶ��ʽ */
#define	DVR_1500_12CIF		3	/*! 12· CIFǶ��ʽ */
#define	DVR_1500_16CIF		4	/*! 16· CIFǶ��ʽ */
#define	DVR_1500_4D1		5	/*! 4· D1Ƕ��ʽ */
#define	DVR_1500_8D1		6	/*! 8· D1Ƕ��ʽ */

//8550ϵ��
#define	DVR_8550_4CIF		7	/*! 4· CIFǶ��ʽ */

//1700ϵ��
#define	DVR_1700_8CIF		8	/*! 8· 1700 CIFǶ��ʽ */
#define	DVR_1700_16CIF		9	/*! 16· 1700 CIFǶ��ʽ */
#define	DVR_1700_4D1		10	/*! 4· 1700 D1Ƕ��ʽ */
#define	DVR_1700_8D1		11	/*! 8· 1700 D1Ƕ��ʽ */
#define	DVR_1700_16D1		12	/*! 16· 1700 D1FǶ��ʽ */


/**************************************************************************
 *                           ��������                                     *
 **************************************************************************/

#define DVR_MAX_VIDEOIN_NUM				(16)
#define DVR_MAX_PTZ_NUM					(DVR_MAX_VIDEOIN_NUM)
#define DVR_MAX_VIDEOENC_NUM			(DVR_MAX_VIDEOIN_NUM)
#define DVR_MAX_ALARMIN_NUM				(16)
#define DVR_MAX_ALARMOUT_NUM			(8)
#define DVR_MAX_EXCEPTION_NUM			(8)
#define DVR_MAX_VIDEOOUT_NUM			(8)

#define DVR_MAX_DAYS					(7)
#define DVR_MAX_TIMESEGMENT				(24 * 60 / 5)	//ÿ5����һ��ʱ���

#define DVR_MAX_IP_STR_LEN				(16)
#define DVR_MAX_MAC_STR_LEN				(18)
#define DVR_MAX_MAC_NUM_LEN				(6)
#define DVR_MAX_DDNSPRO_NUM				(32)
#define DVR_MAX_DDNSPRONAME_LEN			(128)
#define DVR_MAX_DOMAINNAME_LEN 			(256)
#define DVR_MAX_EMAIL_LEN				(256)

#define DVR_MAX_USER_NUM 				(16)
#define DVR_MAX_USERNAME_LEN 			(64)
#define DVR_MAX_PASSWORD_LEN 			(64)
#define DVR_MAX_RIGHT_NUM				(32)

/** @brief ��������û��� */
#define DVR_MAX_ONLINEUSER_NUM			(16)

/** @brief IP�������� */
#define DVR_MAX_WHITEIP_NUM				(10)

#define DVR_MAX_PRESET_NUM				(128)
#define DVR_MAX_MOTIONSCOPE_NUM			(32)
#define DVR_MAX_PICSEC_NUM				(24)
#define DVR_MAX_VIDEOSHELTER_NUM		(8)
#define DVR_MAX_FONTNAME_LEN			(32)	//����������
#define DVR_MAX_CHANNELNAME_LEN			(20 + 1)	//����ͨ������󳤶�,��������
#define DVR_MAX_PTZPRONAME_LEN			(48)	//PTZЭ�����Ƴ���
#define DVR_MAX_PTZPRO_NUM				(512)	//PTZЭ�����(��װ��δ��װ��256)
#define DVR_MAX_LATTICE_WIDTH			(24 * 10)	//������
#define DVR_MAX_LATTICE_HEIGHT			(24)	//����߶�
#define DVR_MAX_LATTICE_BUFSIZE			(24 * 24 * 10 / 8)	//���������С

#define DVR_MAX_PARTITION_DEVNODE_LEN	(16)
#define DVR_MAX_PARTITION_IN_HARDDISK	(15)
#define DVR_MAX_PARTITION_IN_DISKGROUP	(32)
#define DVR_MAX_HARDDISK_NUM 			(8)
#define DVR_MAX_DISKGROUP_NUM 			(8)

#define DVR_MAX_VGARESOLVING_NUM		(16)

#define DVR_MAX_VERSION_LEN				(32)

/** @brief Hxht��ͨ�ַ�������																*/
#define DVR_COMMON_STRING_LEN			(32)


/** @brief ֧�ֵ�Э����������																*/
#define DVR_MAX_SUPPORT_PROTOCOL_NUM	(32)

/** @brief WIFI�ȵ�������󳤶� */
#define DVR_MAX_SSID_LEN				(128)

/** @brief ����ʶ���WIFI�ȵ������� */
#define DVR_MAX_AP_NUM					(10)

/** @brief WIFI��Կ��󳤶� */
#define DVR_MAX_WIFI_KEY_LEN			(128)

/** @brief ���Դ�豸����																			*/
#define MAX_SOURCE_DEVICE_NUMBER		(16)

/** @brief �������豸����																			*/
#define MAX_DEVICE_OUTPUT				(16)

//֧�����VGA����
#define MAX_VGA_NUM						(8)

//TV���
#define MAX_TV_NUM						(8) 

/** @brief ISP ����ģ����� */
#define DVR_MAX_ISP_TEMPLATE		(6)

/** @brief ISP ������AEWindow ���� */
#define DVR_MAX_ISP_AEWINDOW		(6)

/** @brief ISP ������ƽ��ģ����� */
#define DVR_MAX_ISP_WHITEBALANCE	(6)

/* CB 20160223 �����������ӿڷ�װ start */
#define DVR_ALARMSERVER_IP_STR_LEN				(16)
#define DVR_ALARMSERVER_USERNAME_LEN 			(64)
#define DVR_ALARMSERVER_PASSWORD_LEN 			(64)
/* CB 20160223 �����������ӿڷ�װ end */

/**************************************************************************
*								Э�����ƶ���			                  *
**************************************************************************/
//˽��Э��
#define	PROTOCOL_PRIVATE				0

//�ֻ�Э��
#define	PROTOCOL_TIDEMOBILE			1

//���Ż�ͨЭ��
#define	PROTOCOL_HXHT						(1<<1)

//RTSPЭ��
#define	PROTOCOL_RTSP						(1<<2)

//OnvifЭ��
#define	PROTOCOL_ONVIF						(1<<3)

#define	PROTOCOL_HTTP						(1<<4)

#define	PROTOCOL_DISCOVERY					(1<<5)

//RTMPЭ��
#define	PROTOCOL_RTMP						(1<<6)

#define	PROTOCOL_IPDECTETION				(1<<8)

//˽��DDNS ����ͻ���
#define	PROTOCOL_PDNS						(1<<9)

//xxxЭ��
//#define PROTOCOL_XXX						(1<<4)

/**************************************************************************
 *                             ������Ϣ���������Ͷ���                     *
 **************************************************************************/

///////////////////////////////////////////////////////////////////////////////////////////////////////
#define HY_DVR_GET_NETCFG 			101	/*��ȡ�������          */
#define HY_DVR_SET_NETCFG 			102	/*�����������          */

#define NETCFG_ALL			       	0xFFFFFFFF	/*ȫ����������          */
#define NETCFG_DHCP_CONF			1	/*Dhcp������Ϣ          */
#define NETCFG_DHCP_STATE			(1 << 1)	/*Dhcp״̬��Ϣ          */
#define NETCFG_ETH_IF				(1 << 2)	/*Eth������Ϣ           */
#define NETCFG_PPPOE_CONF			(1 << 3)	/*PPPoE����             */
#define NETCFG_PPPOE_IF				(1 << 4)	/*PPPoE������Ϣ         */
#define NETCFG_DNS_CONF				(1 << 5)	/*DNS������Ϣ           */
#define NETCFG_DDNS_CONF			(1 << 6)	/*DDNS������Ϣ          */
#define NETCFG_HTTP_CONF			(1 << 7)	/*http����              */
#define NETCFG_LISTENPORT_CONF		(1 << 8)	/*����˿�������Ϣ      */
#define NETCFG_MOBILE_CONF			(1 << 9)	/*�ֻ��˿�������Ϣ      */
#define NETCFG_AUTODETECT_CONF		(1 << 10)	/*�Զ����ֶ˿�������Ϣ  */
#define NETCFG_WLAN_IF				(1 << 11)	/*WIFI������Ϣ          */
#define NETCFG_WLAN_DHCP_CONF		(1 << 12)	/*WIFI DHCP����         */
#define NETCFG_WLAN_DHCP_STATE		(1 << 13)	/*WIFI Dhcp״̬��Ϣ     */
#define NETCFG_WLAN_DNS_CONF		(1 << 14)	/*WIFI DNS������Ϣ      */
#define NETCFG_WLAN_ACCESSPOINTS	(1 << 15)	/*WIFI �ȵ��б�         */
#define NETCFG_WLAN_CONNECTION		(1 << 16)	/*WIFI ��������         */
#define NETCFG_WLAN_STATE			(1 << 17)	/*WIFI ����״̬         */
#define NETCFG_UPNP_CONF			(1 << 18)	/*UPNP ������Ϣ         */
#define NETCFG_PDNS_CONF			(1 << 19)	/*PDNS ������Ϣ         */

//change lhh start 20140627
#define NETCFG_RESET_IP				(1 << 20) 	/* Reset IP for admin */
#define NETCFG_RESET_PASSWORD		(1 << 21)	/* Reset Password for admin */
//change lhh end 20140627

///////////////////////////////////////////////////////////////////////////////////////////////////////
#define HY_DVR_GET_NETSERVERCFG 	103	/*��ȡ���������ò���            */
#define HY_DVR_SET_NETSERVERCFG 	104	/*���÷��������ò���            */
//������
#define NETSERVERCFG_ALL			0xFFFFFFFF	/*ȫ����������          */
#define NETSERVERCFG_CMS_CONF		1	/*CMS������Ϣ               */
#define NETSERVERCFG_CMS_STATE		2	/*CMS״̬��Ϣ               */
#define NETSERVERCFG_AMS_CONF		4	/*AMS������Ϣ               */
#define NETSERVERCFG_NTP_CONF		8	/*NTP������Ϣ               */
#define NETSERVERCFG_EML_CONF		16	/*EML������Ϣ               */
#define NETSERVERCFG_EML_1_CONF		32	/*EML������Ϣ(1.1�汾) */
#define NETSERVERCFG_CMS_PROTOCOL	64	/*CMSЭ����Ϣ */


///////////////////////////////////////////////////////////////////////////////////////////////////////
#define HY_DVR_GET_PICCFG 					105	/*��ȡ���Ĺ�����������ò���            */
#define HY_DVR_SET_PICCFG 					106	/*�������Ĺ�����������ò���            */
//������
#define PICCFG_ALL							0xFFFFFFFF	/*ȫ����������                                      */
#define PICCFG_WORKMODE_CONF					1	/*����ģʽ                                              */
#define PICCFG_OSD_CONF						2	/*OSD��Ϣ                                       		*/
#define PICCFG_CHNAME_CONF					4	/*ͨ��������Ϣ                                   */
#define PICCFG_TIMESEC_CONF					8	/*ʱ�����Ϣ                                        */
#define PICCFG_VIDEOLOST_CONF					16	/*��Ƶ��ʧ������Ϣ                                      */
#define PICCFG_MOTION_CONF					32	/*�ƶ����������Ϣ                                      */
#define PICCFG_MOSAIC_CONF						64	/*������������Ϣ                                        */
#define PICCFG_CHNAME_UNICODE_CONF			128	/*ͨ��������Ϣ(unicode)                                      */
#define PCICFG_MOTION_AREA					256
#define PICCFG_ALL_1							512		/*ȫ����������                                      */
#define PICCFG_ALL_DEF							0x400		/*����Ĭ��ͼ������                                      */ //add by qqy, at 2017-02-28 10:37:17
#define PCICFG_MOTION_AREA_DEF				0x401   /*Ĭ���ƶ��������                                    */ //add by qqy, at 2017-02-28 10:37:17

///////////////////////////////////////////////////////////////////////////////////////////////////////
#define HY_DVR_GET_COMPRESSCFG 					107	/*��ȡ���Ĺ�����������ò���            */
#define HY_DVR_SET_COMPRESSCFG 					108	/*�������Ĺ�����������ò���            */
//������
#define COMPRESSCFG_ALL							0xFFFFFFFF	/*ȫ����������                                      */
#define COMPRESSCFG_WORKMODE_CONF				1	/*����ģʽ������Ϣ                                  */
#define COMPRESSCFG_COMPRESS_CAP				2	/*����������Ϣ                                      */
#define COMPRESSCFG_COMPRESS_CONF				4	/*����������Ϣ                                      */
// change lhh start 20140627
#define	COMPRESSCFG_COMPRESS_DEFAULT			8
// change lhh end 20140627


///////////////////////////////////////////////////////////////////////////////////////////////////////
#define HY_DVR_GET_RECORDCFG 	    109	/*��ȡ����¼����� */
#define HY_DVR_SET_RECORDCFG 	    110	/*���ñ���¼����� */
//������
#define RECORDCFG_ALL				0xFFFFFFFF	/*ȫ��¼������                                      */
#define RECORD_CTRL_STATE			1	/*¼�����״̬����*/
#define RECORD_STREAM				2	/*¼������ѡ�� */
#define RECORD_STATE				3	/*¼��״̬����ʱ���ƶ���⡢�ֶ� */ //add by qqy, at 2017-03-06 20:14:24


///////////////////////////////////////////////////////////////////////////////////////////////////////
#define HY_DVR_GET_SYSTIME 					111	/*��ȡϵͳʱ�����          */
#define HY_DVR_SET_SYSTIME 					112	/*����ϵͳʱ�����          */
//������
#define SYSTIME_ALL							0xFFFFFFFF	/*ϵͳʱ������          */


///////////////////////////////////////////////////////////////////////////////////////////////////////
#define HY_DVR_GET_PTZCFG 					113	/*��ȡ��̨����                  */
#define HY_DVR_SET_PTZCFG 					114	/*������̨����                  */
//������
#define 	PTZCFG_ALL							0xFFFFFFFF	/*��̨��������                  */
#define	PTZ_USR_CMD						0x01		/* ���û����˴��ڷ�������*/
#define	PTZ_USR_CMD_ENUM				0x02		/* ���û����˴��ڷ�������*/

///////////////////////////////////////////////////////////////////////////////////////////////////////
#define HY_DVR_GET_SERIALCFG 				115	/*��ȡ�������ò���          */
#define HY_DVR_SET_SERIALCFG 				116	/*���ô������ò���          */
//������
#define SERIALCFG_ALL						0xFFFFFFFF	/*ȫ�����ڲ�������          */
#define SERIALCFG_PTZ_ELCTRONIC_CFG			1			/*����PTZ����	          */
#define SERIALCFG_PTZ_REPLENISH_1_CFG		2			/*PTZ��������	          */
#define SERIALCFG_ALL_DEF						3	/*ȫ�����ڲ�������          */


///////////////////////////////////////////////////////////////////////////////////////////////////////
#define HY_DVR_GET_ALARMCFG 					117	/*��ȡ�������ò���          */
#define HY_DVR_SET_ALARMCFG 					118	/*���ñ������ò���          */
//������
#define ALARMCFG_ALL									0xFFFFFFFF	/*ȫ��������������          */
#define ALARMCFG_WORKMODE_CONF				1	/*��������ģʽ                  */
#define ALARMCFG_IMGCAPTURE_CONF				2	/*��������                          */
#define ALARMCFG_ALARMIN_CONF					4	/*������������                  */
#define ALARMCFG_ALARMOUT_CONF				8	/*�����������                  */
#define ALARMCFG_EXCEPTION_CONF				16	/*�쳣��������                  */


///////////////////////////////////////////////////////////////////////////////////////////////////////
#define HY_DVR_GET_VIDEOOUTCFG 					119	/*��ȡ��ʾ������ò���          */
#define HY_DVR_SET_VIDEOOUTCFG 					120	/*������ʾ������ò���          */
//������
#define VIDEOOUTCFG_ALL								0xFFFFFFFF	/*ȫ����ʾ�����������          */


///////////////////////////////////////////////////////////////////////////////////////////////////////
#define HY_DVR_GET_USERCFG 					121	/*��ȡ�û���Ϣ����          */
#define HY_DVR_SET_USERCFG 					122	/*�����û���Ϣ����          */
//������
#define USERCFG_ALL							0xFFFF	/*�û���Ϣ����                  */
#define USERCFG_ALL_1							0xFFFFFFFF	/*�û���Ϣ����                  */
#define USERCFG_ONE							1	/*�����û���Ϣ                  */
#define USERCFG_CREATE						2	/*����û�                  */
#define USERCFG_REMOVE						4	/*ɾ���û�                  */

#define USERCFG_USER_ONLINE					8	/** @brief �����û�	 */

#define USERCFG_USER_ONLINE_ONE				16	/** @brief ���������û�	 */

#define USERCFG_WHITE_IP_ENABLE				32	/** @brief �Ƿ������û�������	 */

#define USERCFG_WHITE_IP					64	/** @brief �û�������			 */


///////////////////////////////////////////////////////////////////////////////////////////////////////
#define HY_DVR_GET_DEVICEINFO 			123	/*��ȡ�豸��Ϣ����                  */
#define HY_DVR_SET_DEVICEINFO			124	/*�����豸��Ϣ������ֻ������ */
//������
#define DEVICEINFO_ALL					0xFFFFFFFF	/*ȫ���豸��Ϣ����                  */


///////////////////////////////////////////////////////////////////////////////////////////////////////
#define HY_DVR_GET_DEVICECFG 		125	/*��ȡ�豸���ò���                  */
#define HY_DVR_SET_DEVICECFG		126	/*�����豸���ò���                  */
//������
#define DEVICECFG_ALL						0xFFFFFFFF	/*ȫ���豸���ò���                  */
#define DEVICECFG_LOCKSCREENTIME_CONF		1	/*����ʱ�����                          */
#define DEVICECFG_LANGUAGE_CONF			2	/*����                                          */
#define DEVICECFG_DATETIME_CONF				4	/*����ʱ���ʽ                          */
#define DEVICECFG_DST_CONF					8	/*��ʱ��                                        */
#define DEVICECFG_REMOTECONTROL_ID			16	/*�豸ID������ң����                */
#define DEVICECFG_TIMEZONE_CONF			32	/*ʱ��                */
#define DEVICECFG_VIDEOSTANDARD_CONF		64	/*��Ƶ��ʽ������Ϣ                                      */

///////////////////////////////////////////////////////////////////////////////////////////////////////
#define HY_DVR_GET_STORAGEINFO			127	/*��ȡ�洢ϵͳ��Ϣ                  */
#define HY_DVR_SET_STORAGEINFO			128	/*���ô洢ϵͳ��Ϣ��ֻ������ */
//������
#define STORAGEINFO_ALL					0xFFFFFFFF	/*ȫ���豸��Ϣ����                  */
#define STORAGEINFO_WORKMODE_CONF	1	/*�洢ϵͳ����ģʽ����          */
#define STORAGEINFO_DISK_INFO			2	/*Ӳ����Ϣ����                      */
#define STORAGEINFO_DISKGROUP_INFO	4	/*��������Ϣ����                        */
#define STORAGEINFO_DISK_MARK			8	/*����Ч����                        */


///////////////////////////////////////////////////////////////////////////////////////////////////////
#define HY_DVR_GET_DEVICESTATE		129	/*��ȡ�豸״̬��Ϣ                  */
#define HY_DVR_SET_DEVICESTATE		130	/*�����豸״̬��Ϣ���ճ����� */
//������
#define DEVICESTATE_ALL				0xFFFFFFFF	/*ȫ���豸״̬��Ϣ                      */


///////////////////////////////////////////////////////////////////////////////////////////////////////
#define HY_DVR_GET_DEVICEMAINTENANCE	131	/*��ȡ�豸�Զ�ά������                  */
#define HY_DVR_SET_DEVICEMAINTENANCE	132	/*�����豸�Զ�ά������                  */
//������
#define DEVICEMAINTENANCE_ALL			0xFFFFFFFF	/*ȫ���豸�Զ�ά������                  */


///////////////////////////////////////////////////////////////////////////////////////////////////////
#define HY_DVR_GET_DEVICECUSTOM	133	/*��ȡ�豸���ܶ������� */
#define HY_DVR_SET_DEVICECUSTOM	134	/*�����豸���ܶ������� */
//������
#define DEVICECUSTOM_ALL		0xFFFFFFFF	/*ȫ���豸���ܶ������� */
#define DEVICECUSTOM_HCRESMODE_CONF				8	/*HC���ͱ������Դ����ģʽ��Ϣ */

///////////////////////////////////////////////////////////////////////////////////////////////////////
//������
#define HY_DVR_GET_HXHT			135	/*��ȡHXHT���� */
#define HY_DVR_SET_HXHT			136	/*����HXHT���� */
//������
#define HXHT_ALL				0xFFFFFFFF	/* ȫ��HXHT���� */
#define	HXHT_NATSTATUS			1	/* NAT״̬����    */
#define	HXHT_VOICEPARAM			2	/* ������������ */
#define HXHT_CMS_STORAGE		4	/*CMS�洢ע��������Ϣ       */
#define HXHT_DEVICE_ID			8	/*ǰ���豸ID               */

///////////////////////////////////////////////////////////////////////////////////////////////////////
#define	HY_DVR_GET_PROTOCOL		137	/* ��ȡҪ���ص�Э�����ƣ�˽��Э���Ǳ�����صģ��������У� */
#define	HY_DVR_SET_PROTOCOL		138	/* ����Ҫ���ص�Э������ */
//������
#define PROTOCOL_ALL			0xFFFFFFFF	/* ȫ��Ҫ���ص�Э������ */


#define	HY_DVR_GET_SOURCE_DEVICE	139	/* ��ȡԴ�豸���� */
#define	HY_DVR_SET_SOURCE_DEVICE	140	/* ����Դ�豸���� */
//������
#define SOURCE_DEVICE_ALL			0xFFFFFFFF	/* ȫ��Դ�豸���� */

///////////////////////////////////////////////////////////////////////////////////////////////////////
//������
/** @brief ��ȡ��������ʾ�豸��Ϣ												*/
#define	HY_DVR_GET_DISP_DEV					143

/** @brief ���ý�������ʾ�豸��Ϣ												*/
#define	HY_DVR_SET_DISP_DEV					144

//������
/** @brief ���н�������ʾ�豸��Ϣ(HY_DVR_DISPDEV_CFG)						 */
#define DISP_DEV_ALL						0xFFFFFFFF

/** @brief VGA��Ϣ(HY_DVR_VGAPARA_CFG)										 */
#define DISP_DEV_VGA						1

/** @brief TV ��Ϣ(HY_DVR_VOOUT_CFG)										 */
#define DISP_DEV_TV							2

///////////////////////////////////////////////////////////////////////////////////////////////////////
#define	HY_DVR_GET_NXP8850ISP		145	/* ��ȡNXP8850 ISP���� */
#define	HY_DVR_SET_NXP8850ISP		146	/* ����NXP8850 ISP���� */
//������
#define NXP8850ISP_ALL				0xFFFFFFFF	/* ȫ��ISP���� */

///////////////////////////////////////////////////////////////////////////////////////////////////////
#define	HY_DVR_GET_IMAGEISP					147	
 //add by qqy,start at 2016-08-23 17:06:20
//������
#define CUR_IMAGE_ISP_CFG						0	/*get current all isp cfg */
#define DEF_IMAGE_ISP_CFG						1	/*get default all isp cfg */
 //add by qqy,end at 2016-08-23 17:06:22

#define	HY_DVR_SET_IMAGEISP					152	

#define	HY_DVR_SET_REBOOT					148	

#define	HY_DVR_SET_RESET					        149	

#define	HY_DVR_SET_UPDATE					150

#define	HY_DVR_SET_UPDATE_CONFIG			151

// add by lhh 20150708 start - end : for NVR reset IPC param of ISP and enc and motion etc.
#define     HY_DVR_SET_RESET_PARAM                      155  

// add by liuyu sync by linhh 20160104 start - end 
#define HY_DVR_GET_PTZ_SPEED				156

#define HY_DVR_GET_COMPRESSCFG_EX			157	//add by liuy date 2016-02-17 start-end

#define HY_DVR_SET_COMPRESSCFG_EX			158	//add by liuy date 2016-02-17 start-end

/** @brief ��ȡӦ�ò����Բ���													*/
#define	HY_DVR_GET_APP_FEATURE				200
/** @brief ����Ӧ�ò����Բ���													*/
#define	HY_DVR_SET_APP_FEATURE				201
//������
/** @brief ��Чֵ																*/
#define APP_FEATURE_ALL						0xFFFFFFFF

#define	HY_DVR_CAPTURE_CLIENT				211
#define	CAPTURE_CLIENT_START				0x01
#define	CAPTURE_CLIENT_STATUS				0x02
#define	CAPTURE_CLIENT_GET_BUFF				0x04
#define	CAPTURE_CLIENT_RELEASE_BUFF			0x08

#define	HY_DVR_UPNP_CLIENT					212
#define	DVR_UPNP_CLIENT_SET					0x01
#define	DVR_UPNP_CLIENT_CLR					0x02
#define	DVR_UPNP_CLIENT_GET					0x04

/* CB 20160223 �����������ӿڷ�װ start */
#define HY_DVR_GET_ALARMSERVER 			213	/*��ȡ������������Ϣ    */
#define HY_DVR_SET_ALARMSERVER 			214	/*���ñ�����������Ϣ    */
/* CB 20160223 �����������ӿڷ�װ end */
///////////////////////////////////////////////////////////////////////////////////////////////////////

/**************************************************************************
*                         ̽��������Ϣ���������Ͷ���                      *
************************************************************************* */

///////////////////////////////////////////////////////////////////////////////////////////////////////
//������
/** @brief ��ȡ�������												          	 */
#define HY_DVR_PROBE_GET_NETCFG 			17

/** @brief �����������												          	 */
#define HY_DVR_PROBE_SET_NETCFG 			18

//������
/** @brief ������������(HY_DVR_PROBE_NET_CFG)						          	 */
#define PROBE_NETCFG_BASE					1

/** @brief ���������ȵ�����(HY_DVR_PROBE_WLAN_CONNECTION)						 */
#define PROBE_NETCFG_WLAN_CONNECTION		2

/** @brief �ȵ��б�����(HY_DVR_PROBE_WLAN_ACCESSPOINT_CFG)						 */
#define PROBE_NETCFG_WLAN_AP_LIST			3

///////////////////////////////////////////////////////////////////////////////////////////////////////

/**************************************************************************
 *                        ������Ϣ�ṹ�嶨��                              *
 **************************************************************************/

////////////////////////////////////////////////////////////////////////////

typedef struct
{
    //! ״̬,0Ϊ����,1Ϊ����,2Ϊ��֧��
    unsigned char   bytState;
    int     start_sec;
    int     end_sec;
} HY_DVR_SCHEDTIME_SUB, *LPHY_DVR_SCHEDTIME_SUB;

typedef struct
{
        HY_DVR_SCHEDTIME_SUB    sSubSchedule[4];
} HY_DVR_SCHEDTIME_PRE_DAY, *LPHY_DVR_SCHEDTIME_PRE_DAY;

typedef struct
{
    int bValid;				

    HY_DVR_SCHEDTIME_PRE_DAY sDaySchedule[DVR_MAX_DAYS];

    unsigned char byReserve[3];

} HY_DVR_SCHEDTIME_EX, *LPHY_DVR_SCHEDTIME_EX;

 
//ʱ��ƻ�, 24Сʱ�ȷֳ�48��ʱ���
typedef struct
{
	int bValid;					//! ���ṹ���Ƿ���Ч��=0��ʾ��Ч

	//! һ�������0Ϊ��������1Ϊ����
	unsigned char bySetType[DVR_MAX_DAYS][DVR_MAX_TIMESEGMENT];

	//! ״̬,0Ϊ����(ȫ�첼��),1Ϊ����,2Ϊ��֧��
	unsigned char byState;

	//! ����λ
	unsigned char byReserve[3];

} HY_DVR_SCHEDTIME, *LPHY_DVR_SCHEDTIME;

//����ģʽ
typedef struct
{
	int bValid;					//! ���ṹ���Ƿ���Ч��=0��ʾ��Ч

	int nWorkMode;				//�߼�ģʽ��0Ϊ��ͨģʽ��1Ϊ�߼�ģʽ

} HY_DVR_WORKMODE, *LPHY_DVR_WORKMODE;

/*������Ϣ*/
typedef struct
{
	int bValid;					//! ���ṹ���Ƿ���Ч��=0��ʾ��Ч

	char szFontName[DVR_MAX_FONTNAME_LEN];	//������
	int nFontStyle;				//������
	int nFontSize;				//�����С

} HY_DVR_FONT_INFO, *LPHY_DVR_FONT_INFO;

/*��������*/
typedef struct
{
	int bValid;					//! ���ṹ���Ƿ���Ч��=0��ʾ��Ч

	char strName[DVR_MAX_CHANNELNAME_LEN];	//ͨ������(�ַ���)
	int nCharSet;				//ͨ�����ַ��� 0 GB, 1 unicode

	//����� DVR_MAX_LATTICE_WIDTH
	//���߶� DVR_MAX_LATTICE_HEIGHT
	int nWidth;					//ͨ�����������ַ������(������Ϊ��λ)
	int nHeight;				//ͨ�����������ַ����߶�(������Ϊ��λ)

	//���󣬰���ɨ��
	//��Ϊ (nWidth + 7)/8
	//��ΪnHeight
	//Ŀǰ���֧��10��24*24�ĵ���
	unsigned char byLattice[DVR_MAX_LATTICE_BUFSIZE];

	HY_DVR_FONT_INFO struFontInfo;	//ͨ����������Ϣ

} HY_DVR_ALIAS_CFG, *LPHY_DVR_ALIAS_CFG;

/*��������,unicode�汾*/
typedef struct
{
	int bValid;					//! ���ṹ���Ƿ���Ч��=0��ʾ��Ч

	//Ϊunicode��
	unsigned short strName[DVR_MAX_CHANNELNAME_LEN];	//ͨ������(�ַ���)
	int nCharSet;

	//����� DVR_MAX_LATTICE_WIDTH
	//���߶� DVR_MAX_LATTICE_HEIGHT
	int nWidth;					//ͨ�����������ַ������(������Ϊ��λ)
	int nHeight;				//ͨ�����������ַ����߶�(������Ϊ��λ)

	//���󣬰���ɨ��
	//��Ϊ (nWidth + 7)/8
	//��ΪnHeight
	//Ŀǰ���֧��10��24*24�ĵ���
	unsigned char byLattice[DVR_MAX_LATTICE_BUFSIZE];

	HY_DVR_FONT_INFO struFontInfo;	//ͨ����������Ϣ

} HY_DVR_ALIAS_CFG_1, *LPHY_DVR_ALIAS_CFG_1;

////////////////////////////////////////////////////////////////////////////

//DDNSЭ����Ϣ�ṹ
typedef struct
{
	int bValid;					//! ���ṹ���Ƿ���Ч��=0��ʾ��Ч

	int bDdnsEnable;			/* 0-�������Զ�ע��, 1-�����Զ�ע�� */

	/* ��ǰDDNS��״̬ (ֻ��) */
	//0��ʾ�Ѿ�ֹͣ��1��ʾ����������2��ʾ�Ѿ�������3��ʾ����ֹͣ
	int nDdnsState;

	char szProtocolName[DVR_MAX_DDNSPRONAME_LEN];	/*Э������  (ֻ��) */
	char szUserName[DVR_MAX_USERNAME_LEN];	/*ע���û��� */
	char szUserPassword[DVR_MAX_PASSWORD_LEN];	/*ע���û����� */
	char szDomainName[DVR_MAX_DOMAINNAME_LEN];	/*ע���û����� */

	unsigned short wRegisterPort;	/*����˿� */

	int nAutoRegIntervals;		/*�Զ�ע����ʱ�䣬��λΪ�� */

} HY_DVR_DDNS, *LPHY_DVR_DDNS;

//DDNS�������ýṹ
typedef struct
{
	int bValid;					//! ���ṹ���Ƿ���Ч��=0��ʾ��Ч

	int nDdnsProtocolCount;		//֧�ֵ�DDNSЭ������(ֻ��)

	HY_DVR_DDNS struDdnsProtocol[DVR_MAX_DDNSPRO_NUM];

} HY_DVR_DDNS_CONF, *LPHY_DVR_DDNS_CONF;

typedef struct
{
	int bValid;
	int bOnLine;
	int nPdnsState;
       char szServerDomainName[DVR_MAX_DOMAINNAME_LEN];
       char szUserDomainName[DVR_MAX_DOMAINNAME_LEN];
       int szServerPort;
       int nAutoUpdateInterval;
}   HY_DVR_PDNS, *LPHY_DVR_PDNS;

typedef struct
{
	int bValid;
	int nPdnsServerCount;
	HY_DVR_PDNS struPdns[2];
} HY_DVR_PDNS_CONF, *LPHY_DVR_PDNS_CONF;

//PPPoE����������Ϣ
typedef struct
{
	int bValid;					//! ���ṹ���Ƿ���Ч��=0��ʾ��Ч

	int bPPPoEEnable;			/* 0-������PPPoE,1-���� PPPoE */

	//PPPoE�����Ϣ
	char szPPPoEUser[DVR_MAX_USERNAME_LEN];	/* PPPoE�û��� */
	char szPPPoEPassword[DVR_MAX_PASSWORD_LEN];	/* PPPoE���� */

} HY_DVR_PPPOE_CONF, *LPHY_DVR_PPPOE_CONF;

//PPPoE������Ϣ
typedef struct
{
	int bValid;					//! ���ṹ���Ƿ���Ч��=0��ʾ��Ч

	/*PPPoE ����״̬(ֻ��) */
	//0��ʾû�����ӣ�1��ʾ�������ӣ�2��ʾ���ӳɹ���3��ʾ���ڹҶ�
	int nPPPoEState;

	char szPPPoEIP[DVR_MAX_IP_STR_LEN];	/*PPPoE IP��ַ(ֻ��) */

	char szPPPoESubnetMask[DVR_MAX_IP_STR_LEN];	/*PPPoE ��������(ֻ��) */

	char szPPPoEGateway[DVR_MAX_IP_STR_LEN];	/*PPPoE ����(ֻ��) */

} HY_DVR_PPPOE_IF, *LPHY_DVR_PPPOE_IF;

//DHCP������Ϣ
typedef struct
{
	int bValid;					//! ���ṹ���Ƿ���Ч��=0��ʾ��Ч

	int bDhcpEnable;			/* 0-������Dhcp,1-����Dhcp */

} HY_DVR_DHCP_CONF, *LPHY_DVR_DHCP_CONF;

//DHCP״̬��Ϣ
typedef struct
{
	int bValid;					//! ���ṹ���Ƿ���Ч��=0��ʾ��Ч

	int nDhcpState;				/*0-δ����,1-��ȡ�ɹ�,2-���ڻ�ȡ,3-��ȡʧ��,������ȡ*/

} HY_DVR_DHCP_STATE, *LPHY_DVR_DHCP_STATE;

//DNS������Ϣ
typedef struct
{
	int bValid;					//! ���ṹ���Ƿ���Ч��=0��ʾ��Ч

	char szPrimaryDNS[DVR_MAX_IP_STR_LEN];	/*��DNS������ */
	char szSecondaryDNS[DVR_MAX_IP_STR_LEN];	/*����DNS */

} HY_DVR_DNS_CONF, *LPHY_DVR_DNS_CONF;

//http������Ϣ
typedef struct
{
	int bValid;					//! ���ṹ���Ƿ���Ч��=0��ʾ��Ч

	int bEnable;				//���û����http����

	unsigned short wHttpPort;	/* Http�˿� */

} HY_DVR_HTTP_CONF, *LPHY_DVR_HTTP_CONF;

//��������˿���Ϣ
typedef struct
{
	int bValid;					//! ���ṹ���Ƿ���Ч��=0��ʾ��Ч

	unsigned short wLocalCmdPort;	/*��������˿� */
	unsigned short wLocalMediaPort;	/*����ý��˿� */

	unsigned short wRtpPort;	/*����rtp�˿� */
    unsigned short wOnvifPort;  /* ONVIF protocol listen port */

} HY_DVR_LISTENPORT_CONF, *LPHY_DVR_LISTENPORT_CONF;

#define LISTENPORT_CONF_LEN		sizeof(HY_DVR_LISTENPORT_CONF)

//�˳��ֻ��ͻ�������
typedef struct
{
	int bValid;					//! ���ṹ���Ƿ���Ч��=0��ʾ��Ч

	unsigned short wMobilePort;	/*�ֻ��˿� */

} HY_DVR_TIDE_MOBILE, *LPHY_DVR_TIDE_MOBILE;

//�ֻ������˿���Ϣ
typedef struct
{
	int bValid;					//! ���ṹ���Ƿ���Ч��=0��ʾ��Ч

	HY_DVR_TIDE_MOBILE struTide;	/*�˳��ֻ����� */

} HY_DVR_MOBILE_CONF, *LPHY_DVR_MOBILE_CONF;

#define MOBILE_CONF_LEN		sizeof(HY_DVR_MOBILE_CONF)


//ETH0���ýṹ
typedef struct
{
	int bValid;					//! ���ṹ���Ƿ���Ч��=0��ʾ��Ч

	//����������������Ϣ
	char szIPAddress[DVR_MAX_IP_STR_LEN];	/* DVR IP��ַ */
	char szSubnetMask[DVR_MAX_IP_STR_LEN];	/* DVR �������� */
	char szGateway[DVR_MAX_IP_STR_LEN];	/* ���ص�ַ */
	char szMacAddress[DVR_MAX_MAC_STR_LEN];	/* ֻ�����������������ַ */

} HY_DVR_ETH_IF, *LPHY_DVR_ETH_IF;

//�Զ����ֶ˿���Ϣ
typedef struct
{
	int bValid;					//! ���ṹ���Ƿ���Ч��=0��ʾ��Ч

	unsigned short wAutoDetectPort;	/*�Զ����ֶ˿� */

} HY_DVR_AUTODETECT_CONF, *LPHY_DVR_AUTODETECT_CONF;

#define AUTODETECT_CONF_LEN		sizeof(HY_DVR_AUTODETECT_CONF)

typedef struct
{
	int bValid;					//���ṹ���Ƿ���Ч��=0��ʾ��Ч

	//!\brief WIFI״̬ 0 ������ 1 ����, 2 ����δ�ҵ�
	int bEnable; 

} HY_DVR_WLAN_STATE, *LPHY_DVR_WLAN_STATE;

typedef struct
{
	int bValid;					//���ṹ���Ƿ���Ч��=0��ʾ��Ч

	// !\brief �ȵ�����
	char szSSID[DVR_MAX_SSID_LEN];

	//!\brief �ȵ�MAC��ַ
	char szMacAddress[DVR_MAX_MAC_STR_LEN];

	//!�ȵ��ź�ǿ��
	int nSignal;

	//!0-Open,1-Shared,2-WPAPSK, 3-WPA2PSK, 4-WPANONE(ad-hocģʽ),5-WPA,6-WPA2
	int nAuthentication;

	//! 0��ʾNONE 1��ʾWEP 2��ʾTKIP 3��ʾAES
	int nEncrypType;

	//!\brief �ȵ�֧�ֵĹ淶0��ʾ802.11b,1��ʾ802.11b/g,2��ʾ802.11b/g/n
	// 1: legacy 11B only
	// 2: legacy 11A only
	// 3: legacy 11a/b/g mixed
	// 4: legacy 11G only
	// 5: 11ABGN mixed
	// 6: 11N only
	// 7: 11GN mixed
	// 8: 11AN mixed
	// 9: 11BGN mixed
	int nWirelessMode;
} HY_DVR_WLAN_ACCESSPOINT, *LPHY_DVR_WLAN_ACCESSPOINT;

typedef struct
{
	int bValid;					//���ṹ���Ƿ���Ч��=0��ʾ��Ч

	HY_DVR_WLAN_ACCESSPOINT struAccessPoints[DVR_MAX_AP_NUM];
} HY_DVR_WLAN_ACCESSPOINT_CFG, *LPHY_DVR_WLAN_ACCESSPOINT_CFG;

typedef struct 
{
	//���ṹ���Ƿ���Ч��=0��ʾ��Ч
	int bValid;

	// ����
	char szKey[DVR_MAX_WIFI_KEY_LEN];

	// ��Կ���� 0-��ʾ16���� 1��ʾ�ַ�������
	int nKeyType;
} HY_DVR_WLAN_KEY, *LPHY_DVR_WLAN_KEY;

typedef struct 
{
	//���ṹ���Ƿ���Ч��=0��ʾ��Ч
	int bValid;

	// WEP��֤��ǰ�õ�KEY������,1~4
	int nDefKeyID;

	// WEP KEY1
	HY_DVR_WLAN_KEY Key1;

	// WEP KEY2
	HY_DVR_WLAN_KEY Key2;

	// WEP KEY3
	HY_DVR_WLAN_KEY Key3;

	// WEP KEY4
	HY_DVR_WLAN_KEY Key4;

	// WPA KEY
	HY_DVR_WLAN_KEY WPAKey;
} HY_DVR_WLAN_KEY_CFG, *LPHY_DVR_WLAN_KEY_CFG;

typedef struct
{
	int bValid;					//���ṹ���Ƿ���Ч��=0��ʾ��Ч

	//!\brief �Ƿ������� 0��ʾδ������ 1��ʾ������(ֻ��) 2��ʾ��������
	int bConnect;

	// !\brief �ȵ�����
	char szSSID[DVR_MAX_SSID_LEN];

	//!\brief �ȵ�MAC��ַ
	char szMacAddress[DVR_MAX_MAC_STR_LEN];

	// ��������
	// 0��ʾManaged, 1��ʾAd-hoc
	int nNetworkType;
	
	// ��֤ģʽ
	// 0-Open,1-Shared,2-WPAPSK, 3-WPA2PSK, 4-WPANONE(ad-hocģʽ),5-WPA,6-WPA2
	int nAuthMode;

	// �����㷨 0-NONE,1-WEP,2-TKIP,3-AES
	int nEncrypType;

	// ��������
	HY_DVR_WLAN_KEY_CFG struKeyCfg;
} HY_DVR_WLAN_CONNECTION, *LPHY_DVR_WLAN_CONNECTION;

/*!
*  @struct	tagHY_DVR_UPNP_CONF
*  @brief	UPNP����
*/
typedef struct
{
	int bValid;														/*!< ���ṹ���Ƿ���Ч��0��ʾ��Ч	*/

	int bEnable;													/*!< UPNP���� 0 ������ 1 ����		*/
	char szWanAddress[DVR_MAX_IP_STR_LEN];							/*!< ���ڵ�ַ(ֻ��)					*/
	int nLocalHttpPort;												/*!< ����HTTP�˿�					*/
	int nExportHttpPort;											/*!< ����HTTP�˿�					*/
	int nHttpPortState;												/*!< HTTP״̬ 0 �ɹ� 1 ʧ�� 2 ӳ����*/
	int nLocalMobilePort;											/*!< �����ֻ��˿�					*/
	int nExportMobilePort;											/*!< �����ֻ��˿�					*/
	int nMobilePortState;											/*!< �ֻ�״̬ 0 �ɹ� 1 ʧ�� 2 ӳ����*/
	int nLocalCommandPort;											/*!< ��������˿�					*/
	int nExportCommandPort;											/*!< ��������˿�					*/
	int nCommandPortState;											/*!< ����״̬ 0 �ɹ� 1 ʧ�� 2 ӳ����*/
	int nLocalMediaPort;											/*!< ����ý��˿�					*/
	int nExportMediaPort;											/*!< ����ý��˿�					*/
	int nMediaPortState;											/*!< ý��״̬ 0 �ɹ� 1 ʧ�� 2 ӳ����*/
	int nReserve[8];												/*!< ����							*/
} HY_DVR_UPNP_CONF, *LPHY_DVR_UPNP_CONF;

////////////////////////////////////////////////////////////////////////////
//�����������������ýṹ
typedef struct
{
	int bValid;					//! ���ṹ���Ƿ���Ч��=0��ʾ��Ч

	HY_DVR_DHCP_CONF struDhcp_Conf;	//Dhcp������Ϣ
	HY_DVR_DHCP_STATE struDhcp_State;	//Dhcp״̬��Ϣ

	HY_DVR_ETH_IF struEth;		//Eth������Ϣ

	HY_DVR_PPPOE_CONF struPPPoE_Conf;	//PPPoE����
	HY_DVR_PPPOE_IF struPPPoE_IF;	//PPPoE������Ϣ

	HY_DVR_DNS_CONF struDNS;	//DNS������Ϣ

	HY_DVR_DDNS_CONF struDDNS;	//DDNS������Ϣ

	HY_DVR_HTTP_CONF struHttp;	//http����

	HY_DVR_LISTENPORT_CONF struListenPort;	//����˿�������Ϣ

	HY_DVR_MOBILE_CONF struMobilePort;	//�ֻ��˿�������Ϣ

	HY_DVR_AUTODETECT_CONF struAutoDetectPort;	//�Զ����ֶ˿�����

	HY_DVR_DHCP_CONF struWIFIDhcp_Conf; //WLAN DHCP

	HY_DVR_ETH_IF struWIFICommon; //WIFI ������Ϣ
	
	HY_DVR_WLAN_ACCESSPOINT_CFG struWIFIAccessPoint;/*!< WIFI�ȵ����� */

	HY_DVR_WLAN_CONNECTION struWIFIConnectCfg;	/*!< WIFI�������� */

	HY_DVR_WLAN_STATE struWIFIState;	/*!< WIFI ״̬ */

	HY_DVR_DHCP_STATE struWIFIDhcp_State;	//Dhcp״̬��Ϣ

	HY_DVR_DNS_CONF struWIFIDNS;	//DNS������Ϣ

	HY_DVR_UPNP_CONF	struUPNPConf;			/*!< UPNP������Ϣ				*/
} HY_DVR_NET_CFG, *LPHY_DVR_NET_CFG;

#define NET_CFG_LEN   sizeof (HY_DVR_NET_CFG)
////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////

//���Ĺ��������������Ϣ 
typedef struct
{
	int bValid;					//! ���ṹ���Ƿ���Ч��=0��ʾ��Ч

	int bCmsEnable;				/*0-�����ù��������, 1-���� */

	char szManageHostAddress[DVR_MAX_DOMAINNAME_LEN];	/*Զ�̹���������ַ�����ȿ������� */

	unsigned short wManageHostPort;	/*Զ�̹��������˿� */

	int nAutoRegIntervals;		/*ע����ʱ�䣬��λΪ�� */

} HY_DVR_NET_CMS, *LPHY_DVR_NET_CMS;

//���Ĺ������������״̬
typedef struct
{
	int bValid;					//! ���ṹ���Ƿ���Ч��=0��ʾ��Ч

	int nCmsState;				/*CMSע��״̬,Ŀǰϵͳ��֧�� */

} HY_DVR_CMS_STATE, *LPHY_DVR_CMS_STATE;

//�������������������Ϣ
typedef struct
{
	int bValid;					//! ���ṹ���Ƿ���Ч��=0��ʾ��Ч

	int bAmsEnable;				/*0-�����ñ���������, 1-���� */

	char szAlarmHostAddress[DVR_MAX_DOMAINNAME_LEN];	/*���������������ȿ������� */

	unsigned short wAlarmHostPort;	/*�����������˿� */

} HY_DVR_NET_AMS, *LPHY_DVR_NET_AMS;

//Ntp������������Ϣ
typedef struct
{
	int bValid;					//! ���ṹ���Ƿ���Ч��=0��ʾ��Ч

	int bNtpEnable;				/*0-������, 1-���� */

	char szNtpHostAddress[DVR_MAX_DOMAINNAME_LEN];	/*Ntp�����������ȿ������� */
	unsigned short wNtpHostPort;	/*Ntp���������˿� */

	int nAutoRegIntervals;		/*Ntp������ͬ�����ʱ�䣬��λΪ�� */

} HY_DVR_NET_NTP, *LPHY_DVR_NET_NTP;

//Email������������Ϣ
typedef struct
{
	int bValid;					//! ���ṹ���Ƿ���Ч��=0��ʾ��Ч

	int bEmlEnable;				/*0-������, 1-���� */

	char szSmtpServer[DVR_MAX_DOMAINNAME_LEN];	/*smtp��������ַ */
	unsigned short wSmtpPort;	/*�˿� */

	char szSenderAddress[DVR_MAX_EMAIL_LEN];	/*�����������ַ */

	char szSmtpUserName[DVR_MAX_USERNAME_LEN];	/*smtp�������ʺ�(��Ч����) */
	char szSmtpPassword[DVR_MAX_PASSWORD_LEN];	/*smtp���������� (��������������) */

} HY_DVR_NET_EML, *LPHY_DVR_NET_EML;

//Email������������Ϣ(1.1.0�汾ʹ��)
typedef struct
{
	int bValid;					//! ���ṹ���Ƿ���Ч��=0��ʾ��Ч

	int bEmlEnable;				/*0-������, 1-���� */

	char szSmtpServer[DVR_MAX_DOMAINNAME_LEN];	/*smtp��������ַ(����Ϊ������IP��ַ) */
	unsigned short wSmtpPort;	/*�˿� */
	int nSmtpAuth;				/*��֤��ʽ(0ΪNONE, 1ΪLOGIN, 2ΪPLAIN) */
	int nSmtpTLS;				/*�Ƿ�ʹ�ð�ȫ��½(0Ϊoff, 1Ϊon) */

	char szSenderEmail[DVR_MAX_EMAIL_LEN];	/*�����������ַ */
	char szSenderPassword[DVR_MAX_PASSWORD_LEN];	/*�������������� */

	//���²����ݲ�ʹ��
	int nProtocol;				//(ĿǰΪsmtp)
	int nTimeout;				//��ʱ����
	int nAuto_from;

	//����ΪTLS��ظ߼��������ݲ�ʹ��
	int nTls_starttls;
	int nTls_certcheck;
	int nTls_force_sslv3;
	int nTls_min_dh_prime_bits;
	int nTls_priorities;

} HY_DVR_NET_EML_1, *LPHY_DVR_NET_EML_1;

//////////////////////////////////////////////////////////////////////////////
//Э������
typedef struct
{
	int bValid;					//���ṹ���Ƿ���Ч��=0��ʾ��Ч

	unsigned long dwProtocolName;	/*!< Э�����ƣ�Э���ǰ�λ���úͶ�ȡ�ģ�����ֻ���ֻ�Э��ʱ����ֵΪ1��
									   ֻ�л��Ż�ͨЭ��ʱ����ֵΪ2������Э�鶼��ʱ����ֵΪ3��
									   ��˽��Э���Ǳ�����صģ��������У� */
} HY_DVR_PROTOCOL_NAME, *LPHY_DVR_PROTOCOL_NAME;

typedef struct
{
	int 	bValid;

	int	    BRIGHT;
	int     CONTRAST;
	int     SATURATION;
	int     HUE;
	int	    SHARP;

	int	    HREV;                   /* ���ַ�ת */
	int	    XDR;                    /*  ���ֿ�̬ */
	int	    DNIGHT;                 /* ��ҹ�л� */
	int	    DNR;                    /* ���ֽ���	 */
	int	    SENSUP;                 /* ֡�ۻ� */
	int	    GAMMA;                  /* GAMMA���� */
	int	    SHADING;                /* ��Ӱ���� */
	int	    BADDOT;                 /* ������� */    
	int	    DIS ;                   /* ����ȥ���� */
	int	    FOG;                    /* ����ȥ�� */

	// ���ӷŴ�
	int	DOOM;
	
	int	CROSS;

	// ��ƽ��ģʽ
	int	WBALANCE;
	// �ֶ���ƽ���к����
	int	REDEN;
	// �ֶ���ƽ����������
	int	BLUEEN;
	
	int	BPE;
	int	BLCEN;
	int	BLCAREA;
	int	PEAK;
	int	ECLIPSE;

	// �ع�ģʽ
	int	EXPORT;

	// �ֶ��ع����ʱ��
	int	SHUTTER;
	
	int	AGC;

	// 20130813 ����µ�ISP ����
	int	LDC;
	int 	IRIS;
	int	EXPPRI;
	int	AGCLevel;
	int	SensUpLevel;
	
} HY_DVR_ISP_PARAM, *LPHY_DVR_ISP_PARAM;

typedef struct
{
	int 	bValid;

	// ���õ�ISP�������������ӦVALUE
	int   iIndex ;
	int   iValue ;
}HY_DVR_ISP_SET_PARAM, *LPHY_DVR_ISP_SET_PARAM;


//CMS��Ӧ��Э������
typedef struct
{
	int bValid;					//���ṹ���Ƿ���Ч��=0��ʾ��Ч

	unsigned long dwCMSProtocol;	/*!< Э�����ƣ���CMS����Ҫ��дIP��ַ����Ҫ�����豸�ˣ����
									   CMS�е�IP��ַ��Ϊ��һ��Э��׼���ģ������˽��Э�飬��ô�豸
									   ��ע�ᵽNVMS�У������HxhtЭ�飬���豸ע�ᵽHxht�Ľ���������С�
									   �ò���ֻ�ܱ�ʾһ��Э�顣 */
} HY_DVR_CMS_FOR_PROTOCOL, *LPHY_DVR_CMS_FOR_PROTOCOL;

//////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////
//�������ṹ
typedef struct
{
	int bValid;					//! ���ṹ���Ƿ���Ч��=0��ʾ��Ч

	HY_DVR_NET_CMS struCMS;		//���Ĺ����������Ϣ    
	HY_DVR_NET_AMS struAMS;		//������������Ϣ    
	HY_DVR_NET_NTP struNTP;		//NTP��������Ϣ 
	HY_DVR_NET_EML struEML;		//Email��������Ϣ  

	HY_DVR_CMS_FOR_PROTOCOL struCMSForProtocol;	//���Ĺ����������Ϣ��Ӧ��Э�飨��CMS�ǰ󶨵ģ�

	HY_DVR_CMS_STATE struCmsState;	//���Ĺ������������״̬

	HY_DVR_NET_EML_1 struEML_1;	//Email��������Ϣ  1.1��

} HY_DVR_NET_MANAGER, *LPHY_DVR_NET_MANAGER;

#define NET_MANAGER_LEN   sizeof (HY_DVR_NET_MANAGER)
////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////

//ͼ��������ýṹ(ÿͨ��֧��24��ʱ���)
typedef struct
{
	int bValid;					//! ���ṹ���Ƿ���Ч��=0��ʾ��Ч

	int bTimeSegEnable;			/*����ʱ��Ƭ */

	int nStartTime;				/*��ʼʱ�� ���00:00ʱ������  */
	int nStopTime;				/*����ʱ�� ���00:00ʱ������  */

	int nBrightness;			/*����,0-255 */
	int nContrast;				/*�Աȶ�,0-255 */
	int nSaturation;			/*���Ͷ�,0-255 */
	int nHue;					/*ɫ��,0-255 */

} HY_DVR_CHROMA_SEC, *LPHY_DVR_CHROMA_SEC;

//ͼ��������ýṹ(ÿͨ��֧��24��ʱ���)
typedef struct
{
	int bValid;					//! ���ṹ���Ƿ���Ч��=0��ʾ��Ч

	//ɫ�Ȳ���
	HY_DVR_CHROMA_SEC struChromaSec[DVR_MAX_PICSEC_NUM];

} HY_DVR_CHROMA, *LPHY_DVR_CHROMA;


/*�쳣����ʽ*/
#define DVR_ALARM_TRIGGER_NONE			0	/*����Ӧ */
#define DVR_ALARM_TRIGGER_PREVIEW		(0x1)	/*������Ļ��ʾ��ͨ��������¼��������� */
#define DVR_ALARM_TRIGGER_AUDIOOUT	(0x1 << 1)	/*�������� */
#define DVR_ALARM_TRIGGER_RECORD		(0x1 << 2)	/*����¼�� */
#define DVR_ALARM_TRIGGER_SNAPSHOT	(0x1 << 3)	/*�������� */
#define DVR_ALARM_TRIGGER_ALARMOUT	(0x1 << 4)	/*����������� */
#define DVR_ALARM_TRIGGER_NOTIFYAMS	(0x1 << 5)	/*�ϴ��������� */
#define DVR_ALARM_TRIGGER_PTZ			(0x1 << 6)	/*����PTZ */
#define DVR_ALARM_TRIGGER_EMAIL		(0x1 << 7)	/*����EMail֪ͨ */
#define DVR_ALARM_TRIGGER_NOTIFYGUI	(0x1 << 8)	/*��Ļ��ʾ */

/*��������ṹ��*/
typedef struct
{
	int bValid;					//! ���ṹ���Ƿ���Ч��=0��ʾ��Ч

	unsigned long dwHandleType;	/*����ʽ,����ʽ��"��"��� */

	int nRecordChannelMask;		//����¼��ͨ����ʶ����λ��ʾ
	int nSnapshotChannelMask;	//��������ͨ����ʶ����λ��ʾ
	int nAlarmOutChannelMask;	//�����������ͨ����ʶ����λ��ʾ

	//�����������ͨ��
	int nPtzAction[DVR_MAX_PTZ_NUM];	//nPtzAction �����Ķ���,  0��ʾ�޶��� , 1����Ԥ�õ�, 2����Ѳ�� 3�����켣
	int nPtzIndex[DVR_MAX_PTZ_NUM];	//nPtzIndex  ������Ԥ�õ�/Ѳ��/�켣�ı��

	int nMonitorMask;			//���ԡ����ԡ�����+����,spot

} HY_DVR_HANDLEEXCEPTION, *LPHY_DVR_HANDLEEXCEPTION;


//�ƶ����
typedef struct
{
    int bValid;					//! ���ṹ���Ƿ���Ч��=0��ʾ��Ч

    int bEnable;				/* �Ƿ����ƶ���� */

    int nSenstive;				/*�ƶ����������, 0 - 5,Խ��Խ����,0xff�ر� */

    int nXScope;
    int nYScope;				/*X,Y�����鷶Χ */

    /*�������,����32*32��С���,Ϊ1��ʾ�ĺ�����ƶ��������,0-��ʾ���� */
    unsigned char byMotionScope[DVR_MAX_MOTIONSCOPE_NUM][DVR_MAX_MOTIONSCOPE_NUM];

    HY_DVR_HANDLEEXCEPTION struHandleType;	/* ����ʽ */

    HY_DVR_SCHEDTIME struSchedTime;	/* 0��ʾ��������1��ʾ���� */
    HY_DVR_SCHEDTIME_EX struSchedTimeEx;	 
} HY_DVR_MOTION, *LPHY_DVR_MOTION;


//�źŶ�ʧ���� 
typedef struct
{
	int bValid;					//! ���ṹ���Ƿ���Ч��=0��ʾ��Ч

	int bEnable;				/* �Ƿ����źŶ�ʧ���� */

	HY_DVR_HANDLEEXCEPTION struHandleType;	/* ����ʽ */

	HY_DVR_SCHEDTIME struSchedTime;	/* 0��ʾ��������1��ʾ���� */

} HY_DVR_VILOST, *LPHY_DVR_VILOST;


//�ڵ����� �����С704*576 
typedef struct
{
	int bValid;					//! ���ṹ���Ƿ���Ч��=0��ʾ��Ч

	int bEnable;				/* �Ƿ����� */

	//����������������ʵ����������
	int nHideAreaTopLeftX;		/* �����������x������� */
	int nHideAreaTopLeftY;		/* �����������y������� */
	int nHideAreaBottomRightX;	/* �����������x������� */
	int nHideAreaBottomRightY;	/* �����������y������� */

} HY_DVR_MOSAIC_INFO, *LPHY_DVR_MOSAIC_INFO;

//�ڵ����� �����С704*576 
typedef struct
{
	int bValid;					//! ���ṹ���Ƿ���Ч��=0��ʾ��Ч

	//������
	int bEnableMosaic;			/* �Ƿ������ڵ� ,0-��,1-�� ����Ϊ704*576 */

	HY_DVR_MOSAIC_INFO struMosaicInfo[DVR_MAX_VIDEOSHELTER_NUM];

} HY_DVR_MOSAIC, *LPHY_DVR_MOSAIC;

//OSD������Ϣ
typedef struct
{
	int bValid;					//! ���ṹ���Ƿ���Ч��=0��ʾ��Ч

	int nShowOsd;				/* 0Ϊͨ��ʱ�������ʾ��1Ϊ��ʾͨ����2��Ϊ��ʾʱ�䡢3Ϊ���߾���ʾ */

	int nTimeTopLeftX;			/* ʱ���x���� */
	int nTimeTopLeftY;			/* ʱ���y���� */

	int nNameTopLeftX;			/* ���Ƶ�x���� */
	int nNameTopLeftY;			/* ���Ƶ�y���� */

	int	nTimePos ;
	int 	nTextPos ;

} HY_DVR_OSD_CFG, *LPHY_DVR_OSD_CFG;

typedef struct
{
	int bValid;					//! ���ṹ���Ƿ���Ч��=0��ʾ��Ч

	int nShowOsd;				/* 0Ϊͨ��ʱ�������ʾ��1Ϊ��ʾͨ����2��Ϊ��ʾʱ�䡢3Ϊ���߾���ʾ */

	int nTimeTopLeftX;			/* ʱ���x���� */
	int nTimeTopLeftY;			/* ʱ���y���� */

	int nNameTopLeftX;			/* ���Ƶ�x���� */
	int nNameTopLeftY;			/* ���Ƶ�y���� */
} HY_DVR_OSD_CFG_1, *LPHY_DVR_OSD_CFG_1;


/////////////////////////////////////////////////////////////////////////////////////////////////
//ͼ������ṹ
typedef struct
{
    int bValid;                 //! ���ṹ���Ƿ���Ч��=0��ʾ��Ч

    HY_DVR_WORKMODE     struWorkMode;   //����ģʽ(ֻ��)

    //��ʾOSD
    HY_DVR_OSD_CFG  struOsd[DVR_MAX_VIDEOIN_NUM];

    //ͨ����
    HY_DVR_ALIAS_CFG struChName[DVR_MAX_VIDEOIN_NUM];

    //ͼ���������24��ʱ���
    HY_DVR_CHROMA struChroma[DVR_MAX_VIDEOIN_NUM];

    //�źŶ�ʧ����
    HY_DVR_VILOST struViLost[DVR_MAX_VIDEOIN_NUM];

    //�ƶ����
    HY_DVR_MOTION struMotion[DVR_MAX_VIDEOIN_NUM];

    //������
    HY_DVR_MOSAIC struMosaic[DVR_MAX_VIDEOIN_NUM];

    //ͨ������unicode��
    HY_DVR_ALIAS_CFG_1 struChName_1[DVR_MAX_VIDEOIN_NUM];
} HY_DVR_PIC_CFG, *LPHY_DVR_PIC_CFG;

#define PIC_CFG_LEN				sizeof (HY_DVR_PIC_CFG)

/////////////////////////////////////////////////////////////////////////////////////////////////
typedef struct
{
	int bValid;					//! ���ṹ���Ƿ���Ч��=0��ʾ��Ч

	HY_DVR_WORKMODE 		struWorkMode;	//����ģʽ(ֻ��)

	//��ʾOSD
	HY_DVR_OSD_CFG_1 		struOsd[DVR_MAX_VIDEOIN_NUM];

	//ͨ����
	HY_DVR_ALIAS_CFG 		struChName[DVR_MAX_VIDEOIN_NUM];

	//ͼ���������24��ʱ���
	HY_DVR_CHROMA 			struChroma[DVR_MAX_VIDEOIN_NUM];

	//�źŶ�ʧ���� 
	HY_DVR_VILOST 			struViLost[DVR_MAX_VIDEOIN_NUM];

	//�ƶ���� 
	HY_DVR_MOTION 			struMotion[DVR_MAX_VIDEOIN_NUM];

	//������
	HY_DVR_MOSAIC 			struMosaic[DVR_MAX_VIDEOIN_NUM];

	//ͨ������unicode��
	HY_DVR_ALIAS_CFG_1 		struChName_1[DVR_MAX_VIDEOIN_NUM];
} HY_DVR_PIC_CFG_1, *LPHY_DVR_PIC_CFG_1;



typedef struct
{
	int 	bValid;			
	// �ƶ�����������
	int	m_AreaCnt ;				
	// �ƶ�����������
	int	m_StartX[16];
	int	m_StartY[16];
	int	m_Width[16];
	int	m_Height[16];
} HY_DVR_PIC_MOTION, *LPHY_DVR_PIC_MOTION;

typedef struct
{
	int 	bValid;			

	HY_DVR_PIC_MOTION	struMotion[DVR_MAX_VIDEOIN_NUM];
} HY_DVR_PIC_CFG_MOTION, *LPHY_DVR_PIC_CFG_MOTION;


/////////////////////////////////////////////////////////////////////////////////////////////////

/* NXP8850 Image Sensor Processing������Ϣ: ���ֽ��� ��De-Noise��*/
typedef struct
{
	int bValid;					//! ���ṹ���Ƿ���Ч��=0��ʾ��Ч

	/*
	   ����ģ������ :
	   ���壺 ͨ�����������Ĳ�ͬ���в�ͬ�����ű��ĵ���
	   0    ��ͨ 
	   1    ���� 
	   2 ���ڵ����� 
	   3 ����
	   4 �����
	   5 �Զ���
	   6��7 ����
	 */
	int nWorkMode;

	/*
	   ͼ����ɫ ��Video Color��
	   0    �ڰ�
	   1    ��ɫ  
	 */
	int nVideoColor;

	/*
	   ͼ���� (Video orientation)
	   0    ����
	   1    ��ת      
	   2    ����
	   3    ��ת+ ����
	 */
	int nVideoOrientation;

	/*
	   ǰ������Ƶ��
	   0    60Hz
	   1    50Hz
	 */
	int nInputFrequency;

} HY_DVR_ISP_COMMON, *LPHY_DVR_ISP_COMMON;

/* NXP8850 Image Sensor Processing������Ϣ: AE Mode ����*/
typedef struct
{
	int bValid;					//! ���ṹ���Ƿ���Ч��=0��ʾ��Ч

	int nMode;					//AEģʽ��0-�Զ� 1-���� 2-�ֶ�

}HY_DVR_AE_MODE, *LPHY_DVR_AE_MODE;

/* NXP8850 Image Sensor Processing������Ϣ: AE Window ����*/
typedef struct
{
	int bValid;					//! ���ṹ���Ƿ���Ч��=0��ʾ��Ч

	//����(on /off)
	int bOpen;

	//X (0-4095) ��Ҫʶ�����Ŀ�ȣ���������720p,����1280
	int nX;

	//Y (0-4095) ��Ҫʶ�������Ч���ظ߶�
	int nY;

	//width (1-4095) ��Ҫʶ�����Ŀ��
	int nWidth;

	//height(1-4095) ��Ҫʶ�������Ч���ظ߶�
	int nHeight;

	//Weighting (1X �� 8X��ѡ) ����0-7
	int nWeighting;
	
} HY_DVR_AEWINDOW_CFG, *LPHY_DVR_AEWINDOW_CFG;

/* NXP8850 Image Sensor Processing������Ϣ: �ع����*/
typedef struct
{
	int bValid;					//! ���ṹ���Ƿ���Ч��=0��ʾ��Ч

	//��ͷ��Ȧ��(Lens Type)     0Ϊ �����Զ���Ȧ  1-256Ϊ �ֶ���Ȧ��Ӧ(0-255)
	int bLensType;

	/*
		Ŀ������  (Target Lumiance)	0-255
	*/
	int nTargetLumiance;

	/*
		ƫ�� (Offset)	0-255
	*/
	int nOffset;

	/*
		�����ٶ�  (Shutter Speed)
		��С�ٶȣ�0��1/2
		����ٶȣ�1/120��1
		�ٶȿ�ѡ
		0,1/120,1/60,1/30,1/15,1/8,1/4,1/2,1 
	*/
	int nMinShutterSpeed;
	int nMaxShutterSpeed;

	/*
		����ϵ�� (Gain)
		��С���� 1x ~ 16x 
		������� 2x ~ 32x
	*/
	int nMinAutoGain;
	int nMaxAutoGain;
	
} HY_DVR_EXPOSAL_CFG, *LPHY_DVR_EXPOSAL_CFG;

/* NXP8850 Image Sensor Processing������Ϣ: ��ƽ�� (White Balance)*/
typedef struct
{
	int bValid;					//! ���ṹ���Ƿ���Ч��=0��ʾ��Ч

	/*
		1 �Զ�
		2 �ֶ��� �ֶ� ��Ҫ�޸� RED Gain (0-255),Blue Gain(0-255)
		3 ����
		4 ̫��
		5 ����
		6 ���ӫ���
	*/
	int bWorkMode;

	int nRedGain[DVR_MAX_ISP_WHITEBALANCE];

	int nBlueGain[DVR_MAX_ISP_WHITEBALANCE];

} HY_DVR_WHITEBALANCE_CFG, *LPHY_DVR_WHITEBALANCE_CFG;

/* NXP8850 Image Sensor Processing������Ϣ: ���ֽ��� ��De-Noise��*/
typedef struct
{
	int bValid;					//! ���ṹ���Ƿ���Ч��=0��ʾ��Ч

	/*
	   0    �ر�
	   1    ����
	   Y  Strength ��0-255��
	   Cb strength (0-255)
	   Cr strength (0-255)
	 */
	int bWorkMode;

	int nYStrength;

	int nCbStrength;

	int nCrStrength;

} HY_DVR_DENOISE_CFG, *LPHY_DVR_DENOISE_CFG;

/* NXP8850 Image Sensor Processing������Ϣ*/
typedef struct
{
	int bValid;					//! ���ṹ���Ƿ���Ч��=0��ʾ��Ч

	/*
	AE ģʽ��Ϊ�ֶ�ģʽʱ��AE Window�������ò�����Ч��
	*/
	HY_DVR_AE_MODE struAEMode;

	/*
		AE Window ����,�ֳ�6��Window,�ֱ��� 1 -6 
	*/
	HY_DVR_AEWINDOW_CFG struAEWindow[DVR_MAX_ISP_AEWINDOW];

	/*
		�ع����
	*/
	HY_DVR_EXPOSAL_CFG struExposal;
		
	/*
		��ƽ�� (White Balance)
	*/
	HY_DVR_WHITEBALANCE_CFG struWhiteBalance;

	/*
		���ֽ��� ��De-Noise��
	*/
	HY_DVR_DENOISE_CFG struDeNoise;

} HY_DVR_ISP_TEMPLATE, *LPHY_DVR_ISP_TEMPLATE;

/* NXP8850 Image Sensor Processing������Ϣ*/
typedef struct
{
	int bValid;					//! ���ṹ���Ƿ���Ч��=0��ʾ��Ч

	//ISP�������ò���
	HY_DVR_ISP_COMMON struCommon;

	//ISP����ģ��
	HY_DVR_ISP_TEMPLATE struTemplate[DVR_MAX_ISP_TEMPLATE];

} HY_DVR_NXP8850ISP_CFG, *LPHY_DVR_NXP8850ISP_CFG;

#define NXP8850ISP_CFG_LEN		(sizeof (HY_DVR_NXP8850ISP_CFG))
/////////////////////////////////////////////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////////////////////////////////////
//��������
#define   DVR_MAX_STREAM_TYPE		2
#define   DVR_CAP_NORMAL_H264    	0x01
#define   DVR_CAP_ADVANCED_H264		0x02

#define   DVR_CAP_RESOLUTION_QCIF   0x01
#define   DVR_CAP_RESOLUTION_CIF    0x02
#define   DVR_CAP_RESOLUTION_D1   	0x04			//ʵʱ2CIF
#define   DVR_CAP_RESOLUTION_SD    	0x08			//ʵʱD1

#define DVR_CAP_RESOLUTION_4CIF_SIM   0x10		//��ʵʱD1
#define DVR_CAP_RESOLUTION_2CIF_SIM   0x20		//��ʵʱ2CIF

#define DVR_CAP_RESOLUTION_QVGA		0x40		//320*240
#define DVR_CAP_RESOLUTION_VGA			0x80		//640*480
#define DVR_CAP_RESOLUTION_SVGA		0x100		//800*600
#define DVR_CAP_RESOLUTION_XVGA		0x200		//1024*768
#define DVR_CAP_RESOLUTION_HD720		0x400	//1280*720
#define DVR_CAP_RESOLUTION_QuadVGA	0x800		//1280*960
#define DVR_CAP_RESOLUTION_SXGA		0x1000		//1280*1024
#define DVR_CAP_RESOLUTION_UXGA		0x2000		//1600*1200
#define DVR_CAP_RESOLUTION_HD1080		0x4000		//1920*1080
#define DVR_CAP_RESOLUTION_SD1		0x8000		//960*576


//���������ṹ
typedef struct
{
	int bValid;					//! ���ṹ���Ƿ���Ч��=0��ʾ��Ч

	int nStreamFormatCap;		/*֧�ֵ�������ʽ�� ����֧�ֵĸ�ʽ���Ľ�� */

	unsigned long dwResolutionCap[DVR_MAX_STREAM_TYPE];	/*ÿ�ֱ����ʽ��֧�ֵķֱ��ʸ�ʽ,֧�����еĸ�ʽ���Ľ�� */

} HY_DVR_COMPRESS_CAP, *LPHY_DVR_COMPRESS_CAP;

//�������ýṹ
typedef struct
{
	int bValid;					//! ���ṹ���Ƿ���Ч��=0��ʾ��Ч

	//֡�� 1-20��ffΪȫ֡��
	int nVideoFrameRate;

	//�������ޡ���λK��
	int nVideoBitrateH;

	//��������
	int nVideoBitrateL;

	//����ϵ��:0-6
	int nQuotiety;

	//�ֱ���0-CIF, 1-D1
	int nResolution;

	//��������0-��Ƶ��,1-������
	int nStreamType;

	//¼������ 0-������ 1-��׼ 2-�� 3-�Զ���
	int nPicQuality;

	//��������0: �������ʣ�1: ���룬2���޶�����
	int nBitrateType;
//add by liuy date 2016-01-25 start
	//ͼ���
	int nwidth;

	//ͼ���
	int nheight;

	//���֡��
	int nMaxFps;

//add by liuy date 2016-01-25 end

} HY_DVR_COMPRESSION_INFO, *LPHY_DVR_COMPRESSION_INFO;

//�������ýṹ
typedef struct
{
	int bValid;					//! ���ṹ���Ƿ���Ч��=0��ʾ��Ч

	//֡�� 1-20��ffΪȫ֡��
	int nVideoFrameRate;

	//�������ޡ���λK��
	int nVideoBitrateH;

	//��������
	int nVideoBitrateL;

	//����ϵ��:0-6
	int nQuotiety;

	//�ֱ���0-CIF, 1-D1
	int nResolution;

	//��������0-��Ƶ��,1-������
	int nStreamType;

	//¼������ 0-������ 1-��׼ 2-�� 3-�Զ���
	int nPicQuality;

	//��������0: �������ʣ�1: ���룬2���޶�����
	int nBitrateType;
//add by liuy date 2016-01-25 start
	//ͼ���
	int nwidth;

	//ͼ���
	int nheight;

	//���֡��
	int nMaxFps;

//add by liuy date 2016-01-25 end

//add by liuy date 2016-02-03 start
	//�������� 0-h264,1-H265
	int nEncFormat;
//add by liuy date 2016-02-03 end

} HY_DVR_COMPRESSION_INFO_EX, *LPHY_DVR_COMPRESSION_INFO_EX;


//��������������ṹ
typedef struct
{
	int 		bValid;	

	int 		bEnalbe;		

	int 		nVideoFrameRate;

	int 		nVideoBitrate;

	// �������ֱ���
	int	nResolution ;

} HY_DVR_AUX_COMPRESSION_INFO, *LPHY_DVR_AUX_COMPRESSION_INFO;


//ͨ����������ṹ
typedef struct
{
	int 		bValid;					//! ���ṹ���Ƿ���Ч��=0��ʾ��Ч

	int 		nDelayRecordTime;		/* ¼���ӳ�ʱ�䳤�� */
	int 		nPreRecordTime;			/* Ԥ¼ʱ�� 0-��Ԥ¼ 1-5�� 2-10�� 3-15�� 4-20�� 5-25�� */

	HY_DVR_COMPRESS_CAP 			struCompressCap;	/*ѹ�������� ���ڻ�ȡ����ʱ��Ч��ֻ���� */

	HY_DVR_AUX_COMPRESSION_INFO 	struNetPara;	/* ������ */

	HY_DVR_COMPRESSION_INFO 		struRecordPara[3];	/*0��������,1�¼�¼��,2�ֶ�¼�� */

} HY_DVR_COMPRESSION_CHANNEL, *LPHY_DVR_COMPRESSION_CHANNEL;

//ͨ����������ṹ
typedef struct
{
	int 		bValid;					//! ���ṹ���Ƿ���Ч��=0��ʾ��Ч

	int 		nDelayRecordTime;		/* ¼���ӳ�ʱ�䳤�� */
	int 		nPreRecordTime;			/* Ԥ¼ʱ�� 0-��Ԥ¼ 1-5�� 2-10�� 3-15�� 4-20�� 5-25�� */

	HY_DVR_COMPRESS_CAP 			struCompressCap;	/*ѹ�������� ���ڻ�ȡ����ʱ��Ч��ֻ���� */

	HY_DVR_AUX_COMPRESSION_INFO 	struNetPara;	/* ������ */

	HY_DVR_COMPRESSION_INFO_EX 		struRecordPara[3];	/*0��������,1�¼�¼��,2�ֶ�¼�� */

} HY_DVR_COMPRESSION_CHANNEL_EX, *LPHY_DVR_COMPRESSION_CHANNEL_EX;


typedef struct
{
	int bValid;					//! ���ṹ���Ƿ���Ч��=0��ʾ��Ч

	HY_DVR_WORKMODE struWorkMode;	//����ģʽ(ֻ��)

	HY_DVR_COMPRESSION_CHANNEL 	struCompressChannel[DVR_MAX_VIDEOIN_NUM];

} HY_DVR_COMPRESSION_CFG, *LPHY_DVR_COMPRESSION_CFG;

typedef struct
{
	int bValid;					//! ���ṹ���Ƿ���Ч��=0��ʾ��Ч

	HY_DVR_WORKMODE struWorkMode;	//����ģʽ(ֻ��)

	HY_DVR_COMPRESSION_CHANNEL_EX 	struCompressChannel[DVR_MAX_VIDEOIN_NUM];

} HY_DVR_COMPRESSION_CFG_EX, *LPHY_DVR_COMPRESSION_CFG_EX;

#define COMPRESS_CFG_LEN   sizeof (HY_DVR_COMPRESSION_CFG)
/////////////////////////////////////////////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////////////////////////////////////
//¼�����״̬
typedef struct
{
	int bValid;					//! ���ṹ���Ƿ���Ч��=0��ʾ��Ч

	//0��ʾ�ֶ�¼��,1��ʾ�Զ�¼��,2��ʾ�ر�¼��
	unsigned int uRecordMode[DVR_MAX_VIDEOIN_NUM];
} HY_DVR_RECORD_CTRLSTATE, *LPHY_DVR_RECORD_CTRLSTATE;

//¼������ѡ��
typedef struct
{
	int bValid;					//! ���ṹ���Ƿ���Ч��=0��ʾ��Ч

	//0��ʾ������,1��ʾ������(CIF),2��ʾ����������(VGA)
	unsigned int uStreamIndex[DVR_MAX_VIDEOIN_NUM];
} HY_DVR_RECORD_STREAM, *LPHY_DVR_RECORD_STREAM;


//¼������ѡ��
typedef struct
{
	int bValid;					//! ���ṹ���Ƿ���Ч��=0��ʾ��Ч

	int 	week[4] ;
	int	start[4];
	int	end[4];
	int	enable[4];
} HY_DVR_RECORD_PLAN, *LPHY_DVR_RECORD_PLAN;


//¼��ƻ��ṹ
typedef struct
{
    int bValid;					//! ���ṹ���Ƿ���Ч��=0��ʾ��Ч

    //0��ʾ��¼��1��ʾ��ʱ¼��2��ʾ�ƶ�¼��
    HY_DVR_SCHEDTIME 		struRecordTime[DVR_MAX_VIDEOIN_NUM];

    HY_DVR_SCHEDTIME_EX 		sRecordSchedule[DVR_MAX_VIDEOIN_NUM]; 

    //\\ ��ȡ������ʽ��¼��ƻ�
    HY_DVR_RECORD_PLAN	strRecordPlan[DVR_MAX_VIDEOIN_NUM];

    //¼�����״̬
    HY_DVR_RECORD_CTRLSTATE struRecordCtlState;

    //¼������ѡ��
    HY_DVR_RECORD_STREAM struRecordStream;

} HY_DVR_RECORD_SCHED, *LPHY_DVR_RECORD_SCHED;

#define RECORD_SCHED_LEN sizeof(HY_DVR_RECORD_SCHED)
/////////////////////////////////////////////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////////////////////////////////////
//����ϵͳʱ�����
typedef struct
{
	int nYear;					//��
	int nMonth;					//��
	int nDay;					//��
	int nHour;					//ʱ
	int nMinute;				//��
	int nSecond;				//��

} HY_DVR_TIME, *LPHY_DVR_TIME;

#define TIME_CFG_LEN sizeof(HY_DVR_TIME)
/////////////////////////////////////////////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////////////////////////////////////
 //add by qqy,start at 2017-03-15 10:24:20
 typedef struct
{
        int   nChannnel;
	unsigned long   nCmd ;
	unsigned long   nPara ;
}HY_DVR_PTZPRO_CMD, *LPHY_DVR_PTZPRO_CMD;
 //add by qqy,end at 2017-03-15 10:24:23

//��̨Э����Ϣ
typedef struct
{
	int bValid;					//! ���ṹ���Ƿ���Ч��=0��ʾ��Ч

	int nUseable;				/*PTZЭ���״̬��0��δ��װ��1���Ѱ�װ�� */
	int bSystem;				/*PTZЭ���״̬��0����ϵͳ���еģ���ɾ����1��ϵͳ���еģ�����ɾ���� */

	char szPTZName[DVR_MAX_PTZPRONAME_LEN];	/*PTZЭ������ */

} HY_DVR_PTZPRO, *LPHY_DVR_PTZPRO;

//��̨Э�������Ϣ
typedef struct
{
	int bValid;					//! ���ṹ���Ƿ���Ч��=0��ʾ��Ч

	int nPtzCount;				/* ϵͳ֧��PTZЭ��ĸ��� */

	HY_DVR_PTZPRO struPTZProtocol[DVR_MAX_PTZPRO_NUM];	/*ϵͳPTZ���� */

} HY_DVR_PTZPRO_CFG, *LPHY_DVR_PTZPRO_CFG;

#define PTZPRO_CFG_LEN sizeof(HY_DVR_PTZPRO_CFG)
/////////////////////////////////////////////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////////////////////////////////////
//��̨��Ϣ
typedef struct
{
	int bValid;					//! ���ṹ���Ƿ���Ч��=0��ʾ��Ч

	unsigned char bySetPreset[DVR_MAX_PRESET_NUM];	/* Ԥ�õ��Ƿ�����,0-û������,1-���� */
	unsigned char bySetCruise[DVR_MAX_PRESET_NUM];	/* Ѳ���Ƿ�����: 0-û������,1-���� */
	unsigned char bySetTrack[DVR_MAX_PRESET_NUM];	/* �켣�Ƿ�����,0-û������,1-���� */

} HY_DVR_PTZ, *LPHY_DVR_PTZ;

//��������
typedef struct
{
	int bValid;					//! ���ṹ���Ƿ���Ч��=0��ʾ��Ч

	int nBaudRate;				/* ������(bps)��0��50��1��75��2��110��3��150��4��300��5��600��6��1200��7��2400��8��4800��9��9600��10��19200�� 11��38400��12��57600��13��76800��14��115.2k; */
	int nDataBit;				/* �����м�λ 0��5λ��1��6λ��2��7λ��3��8λ; */
	int nStopBit;				/* ֹͣλ 0��1λ��1��2λ; */
	int nParity;				/* У�� 0����У�飬1����У�飬2��żУ��; */
	int nFlowcontrol;			/* 0���ޣ�1��������,2-Ӳ���� */
	int nDecoderAddress;		/*��������ַ:0 - 255 */
	int nComType;				/*0��COM1 RS232��1��COM2 RS485 */

} HY_DVR_SERIAL, *LPHY_DVR_SERIAL;

/////////////////////////////////////////////////////////////////////////////////////////////////
//��̨��������
typedef struct
{
	int bValid;					//! ���ṹ���Ƿ���Ч��=0��ʾ��Ч

	int nUseable;				//! �Ƿ�������������
	int nCycle;					//! ��������������, 0��ʾ����
	int nAction;				//! �������� 0��ʾԤ�õ� 1��ʾѲ�� 2��ʾ�켣 3��ʾ�Զ�ɨ��
	int nIndex;					//! ������(Ԥ�õ��,Ѳ����,�켣��,�Զ�ɨ����·��)
} HY_DVR_PTZACTION, *LPHY_DVR_PTZACTION;

typedef struct
{
	int bValid;					//! ���ṹ���Ƿ���Ч��=0��ʾ��Ч

	char szPTZName[DVR_MAX_PTZPRONAME_LEN];	/*PTZЭ������ */

	int speed;						/* ��PTZ�ٶȴ��������ļ�Edvr.cfg�� */
	HY_DVR_SERIAL struSerial;	//��������

	HY_DVR_PTZACTION struPTZAction;

} HY_DVR_DECODER_CHANNEL, *LPHY_DVR_DECODER_CHANNEL;

//sony�ĵ���ptz��о����
typedef struct  
{
	int bValid;					//! ���ṹ���Ƿ���Ч��=0��ʾ��Ч

	int nDigitZoom;				/*!< ���ֱ䱶 (0-�� 1-��)			                        */
	int nLowLum;				/*!< ���ն� (0-�� 1-��)										*/
	int nBackLight;				/*!< ���ⲹ�� (0-�� 1-��)									*/
	int nAutoShutter;			/*!< �Զ����� (0-�ֶ� 1-�Զ�)			                    */
	int nWhiteBalance;			/*!< ��ƽ�� (0-�ֶ� 1-�Զ� 2-���� 3-���� 4-ATW 5-ONE PUSH)	*/
	int nRedGain;				/*!< ������ (0~255)											*/
	int nBlueGain;				/*!< ������ (0~255)											*/
	int nAcutance;				/*!< ��� (0~15)											*/
	int nExpMode;				/*!< �ع�ģʽ (0-�Զ� 1-�ֶ� 2-�������� 3-��Ȧ����)			*/
	int nShutterSpeed;			/*!< �����ٶ� (0~15)				                        */
	int nIrisSpeed;				/*!< ��Ȧ (0-�ֶ� 1-�Զ���									*/
	int nWideDyn;				/*!< ��̬ (0-�� 1-��)										*/
	int n3DFilter;				/*!< 3D����	(0-�� 1-��)										*/
	int nMirror;				/*!< ����  (0-�� 1-��)										*/
	int nReverse;				/*!< ��ת  (0-�� 1-��)										*/
	int nInputFrequency;		/*!< ����Ƶ��  (0-60Hz 1-50Hz)                              */
	int nLongRestrict;			/*!< �������٣�1-����0-�أ�									*/
	int nNorthSet;				/*!< ��λ�趨��1-�趨��										*/

} HY_DVR_PTZ_ELCTRONIC_SONY, *LPHY_DVR_PTZ_ELCTRONIC_SONY;

//����ͨ���ĵ���ptz����
typedef struct  
{
	int bValid;					//! ���ṹ���Ƿ���Ч��=0��ʾ��Ч

	HY_DVR_PTZ_ELCTRONIC_SONY struPtzElcSony;

} HY_DVR_PTZ_ELCTRONIC_CHANNEL, *LPHY_DVR_PTZ_ELCTRONIC_CHANNEL;


typedef struct 
{
	int bValid;																/*!< ���ṹ���Ƿ���Ч��0��ʾ��Ч */

	int	iWorkMode;															/*!< ����ģʽ: 0�Զ���1�ֶ�									*/
	int	iManualSwitch;														/*!< �ֶ�����: 0�ֶ��أ�1�ֶ���								*/
	int	iOpenThreshold;														/*!< �����¶ȣ����ڴ��¶�ʱ����								*/
	int	iCloseThreshold;													/*!< �ر��¶ȣ����ڴ��¶�ʱ����								*/
} HY_DVR_PTZ_TEMPERATURE_DEVICE, *LPHY_DVR_PTZ_TEMPERATURE_DEVICE;

/*!
*  @struct	HY_DVR_PTZ_ELCTRONIC_CH_TEMPERATURE
*  @brief	����ͨ���ĵ���ptz�¶��豸����
*/
typedef struct  
{
	int bValid;																/*!< ���ṹ���Ƿ���Ч��0��ʾ��Ч */

	HY_DVR_PTZ_TEMPERATURE_DEVICE struPtzFanDevice;							/*!< �����豸���� */
	HY_DVR_PTZ_TEMPERATURE_DEVICE struPtzHeaterDevice;						/*!< �����豸���� */
	HY_DVR_PTZ_TEMPERATURE_DEVICE struPtzReserveDevice[14];					/*!< �¶��豸����(�����豸ʱ��һ) */

} HY_DVR_PTZ_ELCTRONIC_CH_TEMPERATURE, *LPHY_DVR_PTZ_ELCTRONIC_CH_TEMPERATURE;

//����ͨ���ĵ���ptz����
typedef struct  
{
	int bValid;					//! ���ṹ���Ƿ���Ч��=0��ʾ��Ч

	HY_DVR_PTZ_ELCTRONIC_CHANNEL   struPtzElcChannel[DVR_MAX_PTZ_NUM];
	HY_DVR_PTZ_ELCTRONIC_CH_TEMPERATURE   struPtzElcChTemperature[DVR_MAX_PTZ_NUM];

} HY_DVR_PTZ_ELCTRONIC, *LPHY_DVR_PTZ_ELCTRONIC;

/*!
*  @struct	tagHY_DVR_PTZACTION
*  @brief	��̨��������
*/
typedef struct
{
	int bValid;																/*!< ���ṹ���Ƿ���Ч��0��ʾ��Ч */
	HY_DVR_PTZACTION struPTZAction[DVR_MAX_PTZ_NUM];						/*!< ��̨���� */

} HY_DVR_PTZACTION_CFG, *LPHY_DVR_PTZACTION_CFG;

/*!
*  @struct	HY_DVR_PTZ_REPLENISH_CONTENT_1
*  @brief	ptz�豸������������
*/
typedef struct 
{
	int bValid;																/*!< ���ṹ���Ƿ���Ч��0��ʾ��Ч */

	int	iLowPowerConsumption;												/*!< �͹���: 0�أ�1��										*/
	int	iScreenWiper;														/*!< ��ˢ��: 0�أ�1���Σ�2����								*/
	int	iNightVision;														/*!< ҹ�ӣ�0�أ�1����2�Զ�									*/
	int	iDemist;															/*!< ����0�أ�1��											*/
} HY_DVR_PTZ_REPLENISH_CONTENT_1, *LPHY_DVR_PTZ_REPLENISH_CONTENT_1;

/*!
*  @struct	HY_DVR_PTZ_REPLENISH_1
*  @brief	ptz�豸��������
*/
typedef struct
{
	int bValid;																/*!< ���ṹ���Ƿ���Ч��0��ʾ��Ч */
	HY_DVR_PTZ_REPLENISH_CONTENT_1 struContent[DVR_MAX_PTZ_NUM];			/*!< �������� */

} HY_DVR_PTZ_REPLENISH_1, *LPHY_DVR_PTZ_REPLENISH_1;

/*!
*  @struct	tagHY_DVR_DECODER_CFG
*  @brief	�豸��������
 */
typedef struct
{
	int bValid;																/*!< ���ṹ���Ƿ���Ч��0��ʾ��Ч */
	HY_DVR_DECODER_CHANNEL struDecoder[DVR_MAX_PTZ_NUM];					/*!< ������ͨ������ */
	HY_DVR_PTZACTION_CFG	struPtzAction;									/*!< ��ͨ����̨�������� */
	HY_DVR_PTZ_ELCTRONIC	struPtzElc;										/*!< ����ptz���� */
	HY_DVR_PTZ_REPLENISH_1	struReplenish1;									/*!< ��������1		*/

} HY_DVR_DECODER_CFG, *LPHY_DVR_DECODER_CFG;

#define  DECODER_CFG_LEN  sizeof(HY_DVR_DECODER_CFG)
///////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////
//��������������
typedef struct
{
	int bValid;					//! ���ṹ���Ƿ���Ч��=0��ʾ��Ч

	int nAlarmInType;			/*����������,0������,1������ */

	HY_DVR_HANDLEEXCEPTION struHandleType;	/* ����ʽ */

	HY_DVR_SCHEDTIME struSchedTime;	//ʱ��ƻ�

} HY_DVR_ALARMIN_CHANNEL, *LPHY_DVR_ALARMIN_CHANNEL;

//���������ͨ������
typedef struct
{
	int bValid;					//! ���ṹ���Ƿ���Ч��=0��ʾ��Ч

	int nAlarmOutDelay;			/* �������ʱ��(-1Ϊ���ޣ��ֶ��ر�) */

	HY_DVR_SCHEDTIME struSchedTime;	//�����������ʱ��

} HY_DVR_ALARMOUT_CHANNEL, *LPHY_DVR_ALARMOUT_CHANNEL;

//��������ץͼ����
typedef struct
{
	int bValid;					//! ���ṹ���Ƿ���Ч��=0��ʾ��Ч

	int nCapPicCount;			//������������
	int nCapPicIntervalTime;	//�������ռ��ʱ��

} HY_DVR_ALARM_CAPTURE_PIC, *LPHY_DVR_ALARM_CAPTURE_PIC;

//ϵͳ�쳣���
typedef struct
{
	int bValid;					//! ���ṹ���Ƿ���Ч��=0��ʾ��Ч

	int bEnable;				//�Ƿ��������

	int nCheckTime;				//���ʱ��������λΪ��

	HY_DVR_HANDLEEXCEPTION struHandleType;	/* ��������ʽ */

} HY_DVR_SYSTEM_EXCEPTION, *LPHY_DVR_SYSTEM_EXCEPTION;

//��������
typedef struct
{
	int bValid;					//! ���ṹ���Ƿ���Ч��=0��ʾ��Ч

	HY_DVR_WORKMODE struWorkMode;	//����ģʽ(ֻ��)

	HY_DVR_ALARM_CAPTURE_PIC struCapPic;	//��������

	HY_DVR_ALARMIN_CHANNEL struAlarmIn[DVR_MAX_ALARMIN_NUM];	//������������

	HY_DVR_ALARMOUT_CHANNEL struAlarmOut[DVR_MAX_ALARMOUT_NUM];	//������������

	/*
	   0    Ӳ�̹���
	   1    IP��ͻ
	   2    �Ƿ�����
	   3    ���߶�
	   4    ������
	   5    �����쳣
	 */
	HY_DVR_SYSTEM_EXCEPTION struSystemException[DVR_MAX_EXCEPTION_NUM];

	//��������ͨ������
	HY_DVR_ALIAS_CFG struAlarmInAlias[DVR_MAX_ALARMIN_NUM];

	//�������ͨ������
	HY_DVR_ALIAS_CFG struAlarmOutAlias[DVR_MAX_ALARMOUT_NUM];

	//��������ͨ������(unicode)
	HY_DVR_ALIAS_CFG_1 struAlarmInAlias_1[DVR_MAX_ALARMIN_NUM];

	//�������ͨ������(unicode)
	HY_DVR_ALIAS_CFG_1 struAlarmOutAlias_1[DVR_MAX_ALARMOUT_NUM];
    
        HY_DVR_SCHEDTIME_EX struAlarmInSchedule[DVR_MAX_ALARMIN_NUM]; //add by qqy, at 2017-03-13 16:03:48
} HY_DVR_ALARM_CFG, *LPHY_DVR_ALARM_CFG;

#define ALARM_CFG_LEN   sizeof (HY_DVR_ALARM_CFG)
//////////////////////////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////
//��ʾ����
typedef struct
{
	int bValid;					//! ���ṹ���Ƿ���Ч��=0��ʾ��Ч

	int nScreenSaveTime;		/* ��Ļ����ʱ�� */

	int nMenuAlphaValue;		/* �˵��뱳��ͼ��Աȶ� */

	//int nResolvingPowerCount; //֧�ֵ����Էֱ�����

	//int nCurrentResolvingPower[3];    //��ǰ���Էֱ���

	//int nResolvingPowerList[3][DVR_MAX_VGARESOLVING_NUM]; //֧�ֵ����Էֱ����б�

} HY_DVR_VO_CFG, *LPHY_DVR_VO_CFG;

#define VO_CFG_LEN   sizeof (HY_DVR_VO_CFG)
/////////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////

//�û�ʹ����Ϣ
typedef struct
{
	int bValid;					//! ���ṹ���Ƿ���Ч��=0��ʾ��Ч

	int bEnable;				//�Ƿ�����

} HY_DVR_USER_ENABLE, *LPHY_DVR_USER_ENABLE;


//�û�������Ϣ
typedef struct
{
	int bValid;					//! ���ṹ���Ƿ���Ч��=0��ʾ��Ч

	char szPassword[DVR_MAX_PASSWORD_LEN];	/* ���� */

	unsigned char byLimitMac[DVR_MAX_MAC_NUM_LEN];	/* ���Ʒ��������ַ */

	char szLimitIP[DVR_MAX_IP_STR_LEN];	/* ���Ʒ���IP��ַ */

	char szEmail[DVR_MAX_EMAIL_LEN];

} HY_DVR_USER_INFO, *LPHY_DVR_USER_INFO;

//�û�Ȩ����Ϣ
typedef struct
{
	int bValid;					//! ���ṹ���Ƿ���Ч��=0��ʾ��Ч

	int nLocalRight[DVR_MAX_RIGHT_NUM];	/* Ȩ�� */
	/*����0: ����ϵͳ���� */
	/*����1: �ļ����� */
	/*����2: ¼�񱸷� */
	/*����3: ϵͳ�ر� */
	/*����4: �ʼ�֪ͨ */

	int nRemoteRight[DVR_MAX_RIGHT_NUM];	/* Ȩ�� */
	/*����0: ϵͳ���� */
	/*����1: �����Խ� */
	/*����2: ������� */
	/*����3: ������� */
	/*����4: Զ������ */
	/*����5: �ر�ϵͳ */

	int nChannelRight[DVR_MAX_RIGHT_NUM];	/* Ȩ�� */
	/*����0: ���ػط� */
	/*����1: ����Ԥ�� */
	/*����2: ������̨���� */
	/*����3: �����ֶ�¼�� */
	/*����4: Զ�̻ط� */
	/*����5: Զ��Ԥ�� */
	/*����6: Զ����̨���� */
	/*����7: Զ���ֶ�¼�� */

} HY_DVR_USER_RIGHT, *LPHY_DVR_USER_RIGHT;


//�û���ϢȨ����Ϣ
typedef struct
{
	int bValid;					//! ���ṹ���Ƿ���Ч��=0��ʾ��Ч

	char szUserName[DVR_MAX_USERNAME_LEN];	/* �û��� ���16λ */

	//�û�ʹ����Ϣ
	HY_DVR_USER_ENABLE struUserEnable;

	//�û�������Ϣ
	HY_DVR_USER_INFO struUserInfo;

	//�û�Ȩ����Ϣ
	HY_DVR_USER_RIGHT struUserRight;

} HY_DVR_USER, *LPHY_DVR_USER;

typedef struct
{
	int bValid;					//! ���ṹ���Ƿ���Ч��=0��ʾ��Ч

	// �Ƿ�ΪԶ���û�
	int bRemote;

	// �Ƿ�������״̬
	int bConnect;

	// �û����
	unsigned long dwUserID;

	// ��½Э��
	unsigned long dwProtocolID;

	// �û���
	char szUserName[DVR_MAX_USERNAME_LEN];

	// ��½IP
	unsigned long dwIPAddress;

	// ��½ʱ��
	HY_DVR_TIME struLoginTime;

	// �������� b/s
	unsigned long dwBitrate;
}HY_DVR_ONLINEUSER, *LPHY_DVR_ONLINEUSER; 

typedef struct
{
	int bValid;					//! ���ṹ���Ƿ���Ч��=0��ʾ��Ч

	// �����û��б�
	HY_DVR_ONLINEUSER struOnlineUser[DVR_MAX_ONLINEUSER_NUM];
} HY_DVR_ONLINEUSER_CFG, *LPHY_DVR_ONLINEUSER_CFG;

typedef struct
{
	int bValid;					//! ���ṹ���Ƿ���Ч��=0��ʾ��Ч

	unsigned long dwWhiteIP;
} HY_DVR_WHITEIP, *LPHY_DVR_WHITEIP;

typedef struct
{
	int bValid;					//! ���ṹ���Ƿ���Ч��=0��ʾ��Ч

	int bEnable;				// �Ƿ�����IP������
} HY_DVR_WHITEIP_ENABLE, *LPHY_DVR_WHITEIP_ENABLE;

typedef struct
{
	int bValid;					//! ���ṹ���Ƿ���Ч��=0��ʾ��Ч

	HY_DVR_WORKMODE struWorkMode;	//����ģʽ(ֻ��)

	HY_DVR_USER struUser[DVR_MAX_USER_NUM];

	HY_DVR_ONLINEUSER_CFG struUserOnline;

	HY_DVR_WHITEIP struWhiteIP[DVR_MAX_WHITEIP_NUM];

	HY_DVR_WHITEIP_ENABLE struWhiteIPEnable;

} HY_DVR_USER_CFG, *LPHY_DVR_USER_CFG;

#define USER_CFG_LEN	sizeof(HY_DVR_USER_CFG)
/////////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////
//�豸��Ϣ�ṹ(ֻ��)
typedef struct
{
	int bValid;					//! ���ṹ���Ƿ���Ч��=0��ʾ��Ч

	//���ͱ��
	unsigned long dwBoardType;

	//�豸�������ƣ���HY-2016HC
	char szTypeName[DVR_MAX_VERSION_LEN];

    unsigned long dwSerialNum;  /* ���к� */

    //!\brief   Ӳ���汾
    char szHardwareVersion[DVR_MAX_VERSION_LEN];

    //!\brief   ����汾
    char szSoftwareVersion[DVR_MAX_VERSION_LEN];

    //!\brief   ����汾
    char szDspVersion[DVR_MAX_VERSION_LEN];

	unsigned char 	byVideoInChannels;	/*��Ƶ����·�� */
	unsigned char 	byAudioInChannels;	/*��Ƶ����·�� */
	unsigned char 	byAlarmInChannels;	/*��������·�� */
	unsigned char 	byAlarmOutChannels;	/*�������·�� */

	unsigned char 	byVGAChannels;	/*VGA�ӿڸ��� */

	unsigned char 	bySpotOutChannles;	/*SPOT���·�� */
	unsigned char 	byVoiceInChannels;	/*�����Խ�����·�� */

} HY_DVR_DEVICE_INFO, *LPHY_DVR_DEVICE_INFO;

#define	DEVICE_INFO_LEN	sizeof(HY_DVR_DEVICE_INFO)
//////////////////////////////////////////////////////////////////////////////



//////////////////////////////////////////////////////////////////////////////
///*!
//*  @struct	tagHY_DVR_DEVICE_OUTPUT_INDEX
//*  @brief	����豸���(ֻ��)
//*/
//typedef struct tagHY_DVR_DEVICE_OUTPUT_INDEX
//{
//	int bValid;															/*!< ���ṹ���Ƿ���Ч��0��ʾ��Ч */
//
//	unsigned long	dwDeviceType;										/*!< �豸����(0: ��Ч, 1: VGA, 2 :TV) */
//	unsigned long	dwDeviceIndex;										/*!< �豸��� */
//
//} HY_DVR_DEVICE_OUTPUT_INDEX, *LPHY_DVR_DEVICE_OUTPUT_INDEX;
//
///*!
//*  @struct	tagHY_DVR_DEVICE_OUTPUT
//*  @brief	����豸��Ϣ(ֻ��)
//*/
//typedef struct tagHY_DVR_DEVICE_OUTPUT
//{
//	int bValid;															/*!< ���ṹ���Ƿ���Ч��0��ʾ��Ч */
//
//	HY_DVR_DEVICE_OUTPUT_INDEX cOutputDevice[MAX_DEVICE_OUTPUT];
//
//} HY_DVR_DEVICE_OUTPUT, *LPHY_DVR_DEVICE_OUTPUT;

//////////////////////////////////////////////////////////////////////////////
//��ʱ����Ϣ�ṹ
typedef struct
{
	int bValid;					//! ���ṹ���Ƿ���Ч��=0��ʾ��Ч

	//!\brief   �Ƿ�������ʱ��
	int bEnableDST;

	HY_DVR_TIME struStart;		//��ʼʱ�䣬����Ч

	HY_DVR_TIME struEnd;		//����ʱ�䣬����Ч

	int nDSTBias;				//��������ʱ�䣬����Ϊ��λ

} HY_DVR_DST, *LPHY_DVR_DST;

//�豸�������ã�����ʱ���ʽ
typedef struct
{
	int bValid;					//! ���ṹ���Ƿ���Ч��=0��ʾ��Ч

	//!\brief   �Զ�����ʱ�䣨��λΪ�룩
	int nAutoLockScreenTime;

	//!\brief   ����
	// 0(Default) - �������� 1 - �������� 2 - Ӣ��
	int nMenuLanguage;

	//!\brief   ���ڸ�ʽ
	// 0(Default) - YYYY-MM-DD W hh:mm:ss, 1 - YYYY-MM-DD hh:mm:ss, 2 - MM-DD-YYYY W hh:mm:ss, 3 - MM-DD-YYYY hh:mm:ss
	int nDateFormat;

	//!\brief   ʱ���ʽ��12Сʱ�ƣ�24Сʱ�ƣ�
	int nTimeFormat;

} HY_DVR_GUI, *LPHY_DVR_GUI;

//�豸�������ã�ʱ��
typedef struct
{
	int bValid;					//! ���ṹ���Ƿ���Ч��=0��ʾ��Ч

	//!\brief   ʱ��ʱ��
	int nTimeZone;

} HY_DVR_TIMEZONE, *LPHY_DVR_TIMEZONE;

//�豸�������ã�ʱ��
typedef struct
{
	int bValid;					//! ���ṹ���Ƿ���Ч��=0��ʾ��Ч

	int nDvrID;					/* DVR ID,����ң���� */

} HY_DVR_DVRID, *LPHY_DVR_DVRID;

typedef struct
{
	int bValid;					//! ���ṹ���Ƿ���Ч��=0��ʾ��Ч

	int nVideoInStandard;		//��Ƶ������ʽ

	int nVideoOutStandard;		//��Ƶ�����ʽ��ͨ����������ʽһ����

} HY_DVR_STANDARD, *LPHY_DVR_STANDARD;


//�豸�������ýṹ
typedef struct
{
	int bValid;					//! ���ṹ���Ƿ���Ч��=0��ʾ��Ч

	HY_DVR_DVRID 		struDvrID;

	//!\brief   �Զ�����ʱ�䣨��λΪ�룩
	HY_DVR_GUI 			struGUI;

	HY_DVR_TIMEZONE 	struTimeZone;

	//��ʱ����Ϣ
	HY_DVR_DST 			struDST;

	//�豸����
	HY_DVR_ALIAS_CFG 	struDvrAlias;

	//�豸��ʽ
	HY_DVR_STANDARD 	struStandard;

	//�豸����(unicode)
	HY_DVR_ALIAS_CFG_1 	struDvrAlias_1;

} HY_DVR_DEVICE_CFG, *LPHY_DVR_DEVICE_CFG;

#define	DEVICE_CFG_LEN	sizeof(HY_DVR_DEVICE_CFG)
//////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////
//������Ϣ�ṹ
typedef struct
{
	int bValid;					//! ���ṹ���Ƿ���Ч��=0��ʾ��Ч

	char szDevNode[DVR_MAX_PARTITION_DEVNODE_LEN];	//�豸�ڵ���, �� /dev/sda1

	unsigned long dwCapacity;	//������, MΪ��λ
	unsigned long dwSpare;		//ʣ������

	unsigned long dwStartCHS;	// ������ʼ����

	unsigned long dwEndtCHS;	// ������������

} HY_DVR_DISK_PARTITION, *LPHY_DVR_DISK_PARTITION;

//Ӳ�̱��
typedef struct
{
	int bValid;					//! ���ṹ���Ƿ���Ч��=0��ʾ��Ч

	int nVerifyMark;			//��֤��(���øı�ʱ����֤���ͬ���ı�)

} HY_DVR_DISK_MARK, *LPHY_DVR_DISK_MARK;

#define	DISK_MARK_LEN	sizeof(HY_DVR_DISK_MARK)

//�洢�豸���ͣ�HD��SD��USB��IPSAN��NAS��
typedef struct
{
	int bValid;					//! ���ṹ���Ƿ���Ч��=0��ʾ��Ч

	int nDiskType;				//! 0- unkonown��1-HDD��2-USB��4-CDROM��8-SD��16-IPSAN��32-NAS
}HY_DVR_DISK_TYPE, *LPHY_DVR_DISK_TYPE;

//Ӳ����Ϣ�ṹ
typedef struct
{
	int bValid;					//! ���ṹ���Ƿ���Ч��=0��ʾ��Ч

	int bEnable;				//�Ƿ�װ�д�Ӳ��

	HY_DVR_DISK_MARK struVerifyMark;	//��֤��(���øı�ʱ����֤���ͬ���ı�)

	int nRestState;				//Ӳ��״̬���Ƿ����ߣ�
	int nWriteState;			//Ӳ��״̬���Ƿ��д��

	char szSerialNum[DVR_MAX_VERSION_LEN];	//���к�
	char szTypeName[DVR_MAX_VERSION_LEN];	//Ӳ������
	int nBusNum;				//����λ��,SATA1

	unsigned long dwCapacity;	//����,MΪ��λ
	//unsigned long dwSpare;        //��ʣ������

	int nPartitionCount;		//��������

	HY_DVR_DISK_PARTITION struPartitionInfo[DVR_MAX_PARTITION_IN_HARDDISK];	//������Ϣ

	HY_DVR_DISK_TYPE struDiskType;

} HY_DVR_DISK, *LPHY_DVR_DISK;

//������Ϣ�ṹ
typedef struct
{
	int bValid;					//���ṹ���Ƿ���Ч��=0��ʾ��Ч

	int bEnable;					//�Ƿ����ñ�����

	int nGroupType;				//��������

	int nBindChannelMask;		//�󶨵�ͨ��

	int nDataKeepTime;			//���ݱ���ʱ��

	int nPartitionCount;			//����ӵķ�������

	char szPartitionList[DVR_MAX_PARTITION_IN_DISKGROUP][DVR_MAX_PARTITION_DEVNODE_LEN];	//�豸�ڵ��б�,֧��32������

} HY_DVR_DISK_GROUP, *LPHY_DVR_DISK_GROUP;

/*!
*  @struct	tagHY_DVR_DISK_TYPE_CFG
*  @brief	�洢�豸��������
*/
typedef struct tagHY_DVR_DISK_TYPE_CFG
{
	int bValid;																/*!< ���ṹ���Ƿ���Ч��0��ʾ��Ч */
	HY_DVR_DISK_TYPE struDiskType[DVR_MAX_HARDDISK_NUM];					/*!< �洢�豸���� */

}HY_DVR_DISK_TYPE_CFG, *LPHY_DVR_DISK_TYPE_CFG;
//�洢���� ��Ϣ

typedef struct
{
	int 		bValid;									//���ṹ���Ƿ���Ч��=0��ʾ��Ч

	HY_DVR_WORKMODE 		struWorkMode;				//����ģʽ(ֻ��)

	HY_DVR_DISK 			struDisk[DVR_MAX_HARDDISK_NUM];	//8��Ӳ�̣�ֻ����

	HY_DVR_DISK_GROUP 		struDiskGroup[DVR_MAX_DISKGROUP_NUM];	//8�����飨ֻ����

	HY_DVR_DISK_TYPE_CFG 	struDiskType;										/*!< �洢�豸�������ã�ֻ���� */

	int		struRecordTime;								//\\ �����ļ����ʱ��
} HY_DVR_STORAGE_CFG, *LPHY_DVR_STORAGE_CFG;

#define	STORAGE_CFG_LEN	sizeof(HY_DVR_STORAGE_CFG)
//////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////
/*!
*	@struct tagHY_DVR_VGA_VIDEO_BITRATE
*	@brief	VGA����������
*/
typedef struct tagHY_DVR_VGA_VIDEO_BITRATE
{
	int bValid;																/*!< ���ṹ���Ƿ���Ч��0��ʾ��Ч */

	int nVGAVideoBitrate;													/*!< ���������ʣ���λkbit/s�� */

}HY_DVR_VGA_VIDEO_BITRATE, *LPHY_DVR_VGA_VIDEO_BITRATE;

//�豸ͨ��״̬
typedef struct
{
	int bValid;					//���ṹ���Ƿ���Ч��=0��ʾ��Ч(��ϵͳû�и�ͨ��)

	int nVideoBitrate;			//����������
	int nChildVideoBitrate;		//����������

	int bUseAuxVideoStream;		//�Ƿ�����������

	//��¼��0
	//����¼������1
	//��ͨ����2
	//�ֶ�¼������3
	//�ƶ�¼��4
	int nRecordType;			//¼��״̬(������)
	int bViLost;				//�Ƿ�������Ƶ�źű���(0��ʾ���źţ�1��ʾ���ź�)
	int bMotion;				//�Ƿ����ƶ�����(�в�֧��)

	HY_DVR_VGA_VIDEO_BITRATE struVGABitrate;								/*!< VGA���������� */

} HY_DVR_CHANNEL_STATE, *LPHY_DVR_CHANNEL_STATE;

/*!
*  @struct	tagHY_DVR_VGA_VIDEO_BITRATE_CFG
*  @brief	VGA��������������
*/
typedef struct tagHY_DVR_VGA_VIDEO_BITRATE_CFG
{
	int bValid;																/*!< ���ṹ���Ƿ���Ч��0��ʾ��Ч */
	HY_DVR_VGA_VIDEO_BITRATE struVGABitrate[DVR_MAX_VIDEOIN_NUM];			/*!< VGA���������� */

}HY_DVR_VGA_VIDEO_BITRATE_CFG, *LPHY_DVR_VGA_VIDEO_BITRATE_CFG;

//�豸״̬��Ϣ(ֻ��)
typedef struct
{
	int bValid;					//���ṹ���Ƿ���Ч��=0��ʾ��Ч

	HY_DVR_CHANNEL_STATE struChannelState[DVR_MAX_VIDEOIN_NUM];	//ͨ��״̬

	HY_DVR_VGA_VIDEO_BITRATE_CFG struVGABitrate;							/*!< VGA�������������� */

} HY_DVR_DEVICE_STATE, *LPHY_DVR_DEVICE_STATE;

#define	DEVICE_STATE_LEN	sizeof(HY_DVR_DEVICE_STATE)
//////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////
//�豸�Զ�ά����������
typedef struct
{
	int bValid;					//���ṹ���Ƿ���Ч��=0��ʾ��Ч(��ϵͳû�и�ͨ��)

	int bEnable;				//���ã����ǽ���

	int nMode;					//ά��ģʽ 0Ϊÿ�졢1Ϊÿ�ܡ�2Ϊ����

	//����ģʽʱ����0λ��ʾ������,��1λ��ʾ����1,��ӦλΪ1��ʾ������Ч
	int nWeekDayMask;

	//��Ϊ����ģʽ����������ʱ����Ч
	//����ģʽ��ʱ����Ч
	HY_DVR_TIME struTime;

} HY_DVR_MAINTENANCE_COMMON, *LPHY_DVR_MAINTENANCE_COMMON;

//�豸�Զ�ά��
typedef struct
{
	int bValid;					//���ṹ���Ƿ���Ч��=0��ʾ��Ч

	HY_DVR_MAINTENANCE_COMMON struCommon;	//��������

} HY_DVR_DEVICE_MAINTENANCE, *LPHY_DVR_DEVICE_MAINTENANCE;

#define	DEVICE_MAINTENANCE_LEN	sizeof(HY_DVR_DEVICE_MAINTENANCE)
//////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////

/*!
*  @struct	tagHY_DVR_HC_RESMODE
*  @brief	HC���ͱ������Դ����ģʽ
*/
typedef struct tagHY_DVR_HC_RESMODE
{
	int bValid;					/*!< ���ṹ���Ƿ���Ч��0��ʾ��Ч */

	//�ýṹ��ֻ��HC��HS��������Ч

	/*  ����ģʽȡֵ��ΧΪ(0 - 2)
	   16·����: 
	   ģʽ0ʱ��ϵͳ֧��16·ʵʱCIF���ʵʱ2CIF��D1��ʽ�����
	   ģʽ1ʱ��ϵͳ֧��8·ʵʱ2CIF ��8·ʵʱCIF ��⣬4·2CIFʵʱ����
	   ģʽ2ʱ��ϵͳ֧��4·ʵʱD1 ��12·ʵʱCIF���룬1·D1ʵʱ����
	   8·����: 
	   ģʽ0ʱ��ϵͳ֧��8·ʵʱCIF���ʵʱ2CIF��D1��ʽ�����
	   ģʽ1ʱ��ϵͳ֧��2·ʵʱD1 ��6·ʵʱCIF ��⣬4·D1ʵʱ����
	   ģʽ2ʱ��ϵͳ֧��6·ʵʱD1 ��2·ʵʱCIF���룬1·D1ʵʱ����
	 */
	int nMode;

	unsigned long dwChMask;		/*!< ͨ�����룬��0λΪ1��ʾͨ��1֧��2CIF��D1��ʽ���룬�������� */

} HY_DVR_HC_RESMODE, *LPHY_DVR_HC_RESMODE;

//�豸���ܶ���
typedef struct
{
	int bValid;					//���ṹ���Ƿ���Ч��=0��ʾ��Ч

	HY_DVR_WORKMODE struUser;	//�߼��û�����ģʽ

	HY_DVR_WORKMODE struAlarm;	//�߼���������ģʽ

	HY_DVR_WORKMODE struPic;	//�߼�ͼ���������

	HY_DVR_WORKMODE struEmail;	//Email��������

	HY_DVR_WORKMODE struRecord;	//�߼�¼���������

	HY_DVR_WORKMODE struCMS;	//���Ĺ������������

	HY_DVR_WORKMODE struAMS;	//��������������

	HY_DVR_WORKMODE struNTP;	//NTP����������

	HY_DVR_WORKMODE struStorage;	//�߼��洢����

	HY_DVR_WORKMODE struMaintenance;	//�Զ�ά������

	HY_DVR_HC_RESMODE struHCResMode;	/*!< HC���ͱ������Դ����ģʽ */

	//HY_DVR_WORKMODE struBeep; //�����澯�Զ����(Ŀǰ��δ֧��)

} HY_DVR_DEVICE_CUSTOM, *LPHY_DVR_DEVICE_CUSTOM;

#define	DEVICE_CUSTOM_LEN	sizeof(HY_DVR_DEVICE_CUSTOM)
//////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////
//�澯��ֵ���ݲ�ʵ�֣�
typedef struct
{
	int bValid;					//���ṹ���Ƿ���Ч��=0��ʾ��Ч

	float fCPUUseRatio;			/*!< CPU������ */
	float fMemoryUseRatio;		/*!< �ڴ������� */
	float fDiskSpaceRatio;		/*!< Ӳ�������� */
	unsigned long dwDiskSpaceBalance;	/*!< Ӳ��ʣ��ռ� */

} HY_DVR_THRESHOLD, *LPHY_DVR_THRESHOLD;

//���ط�ʽ����������NAT�����������֣��ݲ�ʵ�֣�
typedef struct
{
	int bValid;					//���ṹ���Ƿ���Ч��=0��ʾ��Ч
	unsigned long dwDownloadMode;	/*!< ���ط�ʽ�� 0-hxht, 1-STREAM_TCP */

} HY_DVR_DOWNLOAD_MODE, *LPHY_DVR_DOWNLOADMODE;

//////////////////////////////////////////////////////////////////////////////

//���Ĺ���������洢ע��������Ϣ
typedef struct
{
	int bValid;					//! ���ṹ���Ƿ���Ч��=0��ʾ��Ч

	char szManageHostAddress[DVR_MAX_DOMAINNAME_LEN];	/*Զ�̹���������ַ�����ȿ������� */

	unsigned short wManageHostPort;	/*Զ�̹��������˿� */

} HY_DVR_NET_CMS_STOREAGE, *LPHY_DVR_NET_CMS_STOREAGE;

//ǰ���豸ID
typedef struct
{
	int bValid;					//! ���ṹ���Ƿ���Ч��=0��ʾ��Ч

	char szDeviceID[DVR_COMMON_STRING_LEN];	/* ǰ���豸ID */

} HY_DVR_DEVICE_ID, *LPHY_DVR_DEVICE_ID;

//NAT����
typedef struct
{
	int bValid;					//���ṹ���Ƿ���Ч��=0��ʾ��Ч

	unsigned long dwIsNAT;		/*!< �Ƿ���NAT���棬0��ʾ���ں��棬1��ʾ��NAT���� */

} HY_DVR_NATSTATUS, *LPHY_DVR_NATSTATUS;

/*
ѹ����ʽ ����ͨ���� �������   ��������    
G711U.HX      1        16        8000  
G711A.HX      1        16        8000  
G722.HX       1        16    8000��16000
*/
//������������
typedef struct
{
	int bValid;					//���ṹ���Ƿ���Ч��=0��ʾ��Ч

	char szAudioEncoder[DVR_COMMON_STRING_LEN];	/*!< ֧�ֵ����������ʽ�������ж�����Զ��Ÿ�����G711U.HX G711A.HX G722.HX */
	unsigned long dwChannel;	/*!< ͨ���� */
	unsigned long dwBitsPerSample;	/*!< ������� */
	unsigned long dwSamplesPerSec;	/*!< ������ */

} HY_DVR_VOICEPARAM, *LPHY_DVR_VOICEPARAM;

typedef struct
{
	int bValid;					//���ṹ���Ƿ���Ч��=0��ʾ��Ч

	HY_DVR_NET_CMS_STOREAGE struCmsStorage;	//���Ĺ���������洢ע����Ϣ
	HY_DVR_DEVICE_ID struDeviceID;	//ǰ���豸ID
	HY_DVR_NATSTATUS struNATStatus;	//NAT״̬
	HY_DVR_VOICEPARAM struVoiceParam;	//�������в���

} HY_DVR_HXHT_CFG, *LPHY_DVR_HXHT_CFG;

typedef struct
{
	int bValid;					//���ṹ���Ƿ���Ч��=0��ʾ��Ч

	unsigned int dwFileMap; //0~30λ��ʾ1��~31�ŵ��ļ��ֲ����,0��ʾ���ļ�,1��ʾ���ļ�
} HY_DVR_FILEMAP_CFG, * LPHY_DVR_FILEMAP_CFG;


//////////////////////////////////////////////////////////////////////////////

/** @brief ��ַ����(��������)																		*/
#define HY_DVR_ADDRESS_LEN				(256)

/** @brief �û�������																	*/
#define HY_DVR_USERNAME_LEN				(32)

/** @brief �û����볤��																	*/
#define HY_DVR_USERPASS_LEN				(32)

/** @brief Ĭ�ϱ����ֶθ���																*/
#define HY_DVR_DEF_RESERVE_NUM			(3)

/*!
*  @struct	tagHY_DVR_USERLOGIN_INFO
*  @brief	�û���¼����
*/
typedef struct tagHY_DVR_USERLOGIN
{
	int bValid;													//���ṹ���Ƿ���Ч��=0��ʾ��Ч
	char	sServerIP[HY_DVR_ADDRESS_LEN];						/*!< ��������IP��ַ							*/
	unsigned long	dwCommandPort;								/*!< ��¼���ӵ�����˿�						*/
	char	sUName[HY_DVR_USERNAME_LEN];						/*!< ��¼�û����û�����						*/
	char	sUPass[HY_DVR_USERPASS_LEN];						/*!< ��¼�û����û�����						*/
	unsigned long	dwReserve[HY_DVR_DEF_RESERVE_NUM];			/*!< ����									*/
}HY_DVR_USERLOGIN_INFO, *LPHY_DVR_USERLOGIN_INFO;

/*!
*  @struct	tagHY_DVR_SOURCE_DEVICE_INFO
*  @brief	Դ�豸��Ϣ
*/
typedef struct tagHY_DVR_SOURCE_DEVICE_INFO
{
	int bValid;													//���ṹ���Ƿ���Ч��=0��ʾ��Ч

	int						nEnable;							/*!< 0��ʾ�����ã�1��ʾ����			*/
	HY_DVR_USERLOGIN_INFO	cUserPara;							/*!< �û�����						*/
	unsigned long			dwVideoInNumber;					/*!< ��Ƶ������						*/
	unsigned long			dwReserve[HY_DVR_DEF_RESERVE_NUM];	/*!< ����							*/
}HY_DVR_SOURCE_DEVICE_INFO, *LPHY_DVR_SOURCE_DEVICE_INFO;

/*!
*  @struct	tagHY_DVR_SOURCE_DEVICE_INFO_CONFIG
*  @brief	Դ�豸����
*/
typedef struct tagHY_DVR_SOURCE_DEVICE_INFO_CONFIG
{
	int bValid;														//���ṹ���Ƿ���Ч��=0��ʾ��Ч

	HY_DVR_SOURCE_DEVICE_INFO	cSourceDevice[MAX_SOURCE_DEVICE_NUMBER];	/*!< Դ�豸��Ϣ					*/
	unsigned long				dwReserve[HY_DVR_DEF_RESERVE_NUM];			/*!< ����				*/
}HY_DVR_SOURCE_DEVICE_INFO_CONFIG, *LPHY_DVR_SOURCE_DEVICE_INFO_CONFIG;

//////////////////////////////////////////////////////////////////////////////
//��ʾ�豸����
//��ȡ��ʾ�豸��Ϣ

/*!
*  @struct	tagHY_DVR_VGAPARA
*  @brief	VGA����
*/
typedef struct tagHY_DVR_VGAPARA
{
	int bValid;									/*!< ���ṹ���Ƿ���Ч��0��ʾ��Ч */

	int nResolution;							/*!< �ֱ��� ,����λ��ʾ */
	int nResolutionCap;							/*!< ����������ֻ������ֱ����й�,��λ��ʾ�������ھ�λΪ1��ʾ
												֧��9���� */
	unsigned long	dwDeviceIndex;				/*!< �豸��� */

}HY_DVR_VGAPARA, *LPHY_DVR_VGAPARA;

/*!
*  @struct	tagHY_DVR_VGAPARA_CFG
*  @brief	VGA��������
*/
typedef struct tagHY_DVR_VGAPARA_CFG
{
	int bValid;									/*!< 0��ʾ��Ч 1��ʾ��Ч */

	int nVGACount;								/*!< VGA Outʵ�ʸ��� */
	HY_DVR_VGAPARA struVga[MAX_VGA_NUM];

}HY_DVR_VGAPARA_CFG, *LPHY_DVR_VGAPARA_CFG;

/*!
*  @struct	tagHY_DVR_VOOUT
*  @brief	��Ƶ���
*/
typedef struct tagHY_DVR_VOOUT
{
	int bValid; 								/*!< 0��ʾ��Ч 1��ʾ��Ч */

	int byVideoFormat;							/*!< �����ʽ,0-PAL,1-NTSC */
	int wLeftffset;								/*!< ��Ƶ�����ƫ�� */
	int wRightffset;							/*!< ��Ƶ�����ƫ�� */
	int wTopffset;								/*!< ��Ƶ�����ƫ�� */
	int wBottomffset;							/*!< ��Ƶ�����ƫ�� */
	int dwResolutionCap;						/*!< ����������ֻ����*/
	unsigned long	dwDeviceIndex;				/*!< �豸��� */

}HY_DVR_VOOUT, *LPHY_DVR_VOOUT;

/*!
*  @struct	tagHY_DVR_VOOUT_CFG
*  @brief	��Ƶ�������
*/
typedef struct tagHY_DVR_VOOUT_CFG
{
	int bValid;									/*!< 0��ʾ��Ч 1��ʾ��Ч */
	int nTVCount;								/*!< TV Out ����*/
	HY_DVR_VOOUT struTv[MAX_TV_NUM];

}HY_DVR_VOOUT_CFG, *LPHY_DVR_VOOUT_CFG;

/*!
*  @struct	tagHY_DVR_DISPDEV_CFG
*  @brief	��������ʾ�豸��Ϣ
*/
typedef struct tagHY_DVR_DISPDEV_CFG
{
	int bValid; 								/*!< 0��ʾ��Ч 1��ʾ��Ч */

	HY_DVR_VGAPARA_CFG struVGA;					/*!< VGA���� */
	HY_DVR_VOOUT_CFG struTV;					/*!< TV���� */

} HY_DVR_DISPDEV_CFG,  * LPHY_DVR_DISPDEV_CFG;

//////////////////////////////////////////////////////////////////////////////
/*!
*  @enum	eDeviceCapability
*  @brief	�豸��������
*/
typedef enum eDeviceCapability
{
	//�����ֶ�0
	eCapabilityLocalNetwork			= 0x00,							/*!< ��������								*/
	eCapabilityWirelessNetwork		= 0x01,							/*!< ��������								*/
	eCapabilityDHCP					= 0x02,							/*!< DHCP									*/
}eDeviceCapability;
//////////////////////////////////////////////////////////////////////////////
/*!
*  @struct	tagHY_DVR_PROBE_NET_INTERFACE
*  @brief	����ӿ�����
*/
typedef struct tagHY_DVR_PROBE_NET_INTERFACE
{ 
	unsigned char	m_bytEnable;									/*!< �Ƿ����ã�0-�����ã�1-���ã�2-δ�ҵ�	*/
	unsigned char	m_bytGetIPMode;									/*!< ��ȡ��ַ��0-�ֶ��趨��1-DHCP��ȡ		*/
	unsigned char	m_bytDevMac[DVR_MAX_MAC_NUM_LEN];				/*!< �豸MAC��ַ(Read)						*/
	unsigned char	m_bytDevIP[DVR_MAX_IP_STR_LEN];					/*!< �豸��ǰIP��ַ							*/
	unsigned char	m_bytDevMask[DVR_MAX_IP_STR_LEN];				/*!< �豸IP��ַ����							*/
	unsigned char	m_bytDevGateway[DVR_MAX_IP_STR_LEN];			/*!< �豸���ص�ַ							*/
	unsigned long	m_dwNetworkState;								/*!< ����״̬:
																			0-���ӳɹ�,
																			1-δ����,
																			2-������������,
																			3-��������ʧ��,��������,
																			4-���ڻ�ȡIP,
																			5-��ȡIPʧ��,������ȡ				*/
	unsigned long	m_dwReserve;									/*!< ��������								*/
}HY_DVR_PROBE_NET_INTERFACE, *LPHY_DVR_PROBE_NET_INTERFACE;
/*!
*  @struct	tagHY_DVR_PROBE_NET_CFG
*  @brief	̽����������
*/
typedef struct tagHY_DVR_PROBE_NET_CFG
{ 
	unsigned char	m_bytDevType;									/*!< ����������(Read)						*/
	unsigned char	m_bytDevChan;									/*!< �豸ͨ������(Read)						*/
	unsigned char	m_bytDevAutoReg;								/*!< �Ƿ������Զ�ע��						*/
	unsigned char	m_bytDevRegInterval;							/*!< �豸ע����ʱ��						*/
	HY_DVR_PROBE_NET_INTERFACE	m_cInterface[3];					/*!< ����ӿ�����							*/
	unsigned char	m_bytDevManHost[DVR_MAX_IP_STR_LEN];			/*!< �豸����������ַ						*/
	unsigned short	m_bytDevDetectPort;								/*!< �豸�Զ����ּ����˿�					*/
	unsigned short	m_wManHostPort;									/*!< �豸���������˿�						*/
	unsigned short	m_wCmdPort;										/*!< �豸����˿�							*/
	unsigned short	m_wMediaPort;									/*!< �豸ý��˿�							*/
	unsigned long	m_dwDeviceCapability[4];						/*!< �豸������λ�����eDeviceCapability����*/
	unsigned long	m_dwReserve[3];									/*!< ��������								*/
}HY_DVR_PROBE_NET_CFG, *LPHY_DVR_PROBE_NET_CFG;
//////////////////////////////////////////////////////////////////////////////
/*!
*  @struct	tagHY_DVR_WLAN_CONNECTION
*  @brief	WIFI��������
*/
typedef struct tagHY_DVR_PROBE_WLAN_CONNECTION
{
	int		m_bEnable;												/*!< WIFI״̬ 0 ������ 1 ����, 2 ����δ�ҵ�*/
	int		m_bConnect;												/*!< �Ƿ������ϣ�0��ʾδ������ 1��ʾ������(ֻ��) */
	char	m_szSSID[DVR_MAX_SSID_LEN];								/*!< �ȵ�����								*/
	char	m_szKey[DVR_MAX_WIFI_KEY_LEN];							/*!< ����									*/
	char	m_szMacAddress[DVR_MAX_MAC_STR_LEN];					/*!< �ȵ�MAC��ַ							*/
	int		m_nNetworkType;											/*!< ��������: 0��ʾManaged, 1��ʾAd-hoc	*/
	int		m_nAuthMode;											/*!< ��֤ģʽ: 0-OPEN,1-SHARED,2-WEPAUTO,3-WPAPSK,4-WPA2PSK,5-WPANONE,6-WPA,7-WPA2*/
	int		m_nEncrypType;											/*!< �����㷨 0-NONE,1-WEP,2-TKIP,3-AES		*/
	unsigned long	m_dwReserve[3];									/*!< ��������								*/
} HY_DVR_PROBE_WLAN_CONNECTION, *LPHY_DVR_PROBE_WLAN_CONNECTION;
//////////////////////////////////////////////////////////////////////////////
/*!
*  @struct	tagHY_DVR_PROBE_WLAN_ACCESSPOINT
*  @brief	WIFI�ȵ�
*/
typedef struct tagHY_DVR_PROBE_WLAN_ACCESSPOINT
{
	char szSSID[DVR_MAX_SSID_LEN];									/*!< �ȵ����� */
	char szMacAddress[DVR_MAX_MAC_STR_LEN];							/*!< �ȵ�MAC��ַ */
	int nSignal;													/*!< �ȵ��ź�ǿ�� */
	int nAuthentication;											/*!< ��֤ģʽ 0-Open,1-Shared,2-WPAPSK, 3-WPA2PSK, 4-WPANONE(ad-hocģʽ),5-WPA,6-WPA2 */
	int nEncrypType;												/*!< ����ģʽ  0��ʾNONE 1��ʾWEP 2��ʾTKIP 3��ʾAES */
	int nWirelessMode;												/*!< 1: legacy 11B only 2: legacy 11A only 3: legacy 11a/b/g mixed
																		 4: legacy 11G only 5: 11ABGN mixed    6: 11N only
																		 7: 11GN mixed      8: 11AN mixed      9: 11BGN mixed */
	unsigned long	m_dwReserve[3];									/*!< ��������								*/
} HY_DVR_PROBE_WLAN_ACCESSPOINT, *LPHY_DVR_PROBE_WLAN_ACCESSPOINT;

/*!
*  @struct	tagHY_DVR_PROBE_WLAN_ACCESSPOINT_CFG
*  @brief	WIFI�ȵ�����
*/
typedef struct tagHY_DVR_PROBE_WLAN_ACCESSPOINT_CFG
{
	int		m_nNumber;												/*!< ��Ч�ȵ����							*/
	HY_DVR_PROBE_WLAN_ACCESSPOINT m_struAccessPoints[DVR_MAX_AP_NUM];/*!< WIFI�ȵ�								*/
	unsigned long	m_dwReserve[3];									/*!< ��������								*/
} HY_DVR_PROBE_WLAN_ACCESSPOINT_CFG, *LPHY_DVR_PROBE_WLAN_ACCESSPOINT_CFG;
//////////////////////////////////////////////////////////////////////////////

typedef struct
{
    int                    bValid;					    /* ���ṹ���Ƿ���Ч��=0��ʾ��Ч */
    int                    m_usercount;               /* ���ü��������ܴ��ڶ��IE��Ӧһ��������������*/			
    int                    m_bEnable;
    char                  asAddress[DVR_ALARMSERVER_IP_STR_LEN];	
    unsigned short        asPort;	
    char                  asUsername[DVR_ALARMSERVER_USERNAME_LEN];	
    char                  asPassword[DVR_ALARMSERVER_PASSWORD_LEN];	
    int			          OffLine;
    unsigned int	      OffLineTime;

    char                  UserUID[48];
    char                  P2PUID[48];
    int                   PushAlarmArray[_MAX_CHANNEL_NUM_];
    unsigned long	      m_alarmType;
    unsigned long	      m_AlarmTime;
    unsigned long	      m_AlarmCnt;
    unsigned long	      m_AlarmCh;
} HY_DVR_ALARMSERVER_IF, *LPHY_DVR_ALARMSERVER_IF;

#define ALARM_SERVER_MAXNUM	4
typedef struct
{
	HY_DVR_ALARMSERVER_IF alarmserverinfo[ALARM_SERVER_MAXNUM];
} HY_DVR_ALARMSERVERINFO_IF, *LPHY_DVR_ALARMSERVERINFO_IF;
#define ALARMSERVER_CFG_LEN   sizeof (HY_DVR_ALARMSERVERINFO_IF)

/*      ����ID......            */
typedef enum
{
    eCmdTypeBegin = 0,
    eCmdTypeConnect,		//�����豸����
    eCmdTypeDisconnect,	//�Ͽ��豸����
    eCmdTypeAlarmSubscibe,	//�ͻ��˶��ı�����Ϣ
    eCmdTypeAlarmUnSubscribe,//�ͻ���ȡ�����ı�����Ϣ
    eCmdTypeAlarm,//������Ϣ
    eCmdTypeClientHeart,//�ͻ����򱨾����������͵�������
    eCmdTypeDeviceHeart,//�豸�򱨾����������͵�������
    eCmdTypeDeviceHeartReply,//�������������豸������Ӧ��
    eCmdTypeSubscribeServerInfo,	//subscribe alarmserver info to IPC
    eCmdTypeUnsubscribeServerInfo,	//unsubscribe alarmserver info to IPC
    eCmdTypeToAlarmServer = 0x040c, //���͸����������������İ�  
    eCmdTypeEnd,
}CmdType;

/* change by linhh 20170526 start : ͳһ����ģ�����Ͷ��� ��HieServer_Cfg.h �� ws_status_def.h ��*/
/*  �豸������Ϣ......      */
typedef enum
{
    edevicetypeBegin               = 0,
    edevicetypeIPC,			/* IPC  */
    edevicetypeNVR,			/* NVR */
    edevicetypeDVR,			/* DVR */
    edevicetypeEnd,
}edevicetype;

/* ��������*/
typedef enum   
{
    ealarmtypeBegin = 0,
    ealarmtypeMD,   //�ƶ���ⱨ��
    ealarmtypeGPIO, //GPIO����
    ealarmtypeVLOST,//��Ƶ��ʧ
    ealarmtypeRLOF,
    ealarmtypeCOVER,
    ealarmtypeNEEDRECORD,
    ealarmtypeLOGOUT,
    ealarmtypeALL = 1000,
    ealarmtypeEnd,
} AlarmType;

struct UnsubscribeAlarmInfo
{
    CmdType	CommandID;//ID = 10
    int	AlarmPort;//alarmport�˿�
};

struct SubscribeAlarmInfo
{
    CmdType	CommandID;//ID = 9
    int	AlarmPort;//alarmport�˿�
};

//�豸���͹����ı�����Ϣ�ṹ��
struct DeviceAlarmMessage
{
    CmdType CommandID;//����ID=5
    AlarmType alarmtype;
    int AlarmIndex;
    int channel;
    int IsOn;//����״̬
    int time;
    char DeviceUID[48];//�����豸��UID
};

//!<����������Ϣ.......
struct SendAlarmMessage
{
    AlarmType alarmtype;
    int AlarmIndex;
    int channel;
    int IsOn;//����״̬
    int time; //�豸��������ʱ���豸ʱ��
    int user;//�ͻ����
    int CmdPort;//����˿�
    char LocalIP[20];//�����豸��IP
    char DeviceUID[48];//�����豸��UID
};

//!<�����������......
struct Connect_info
{
    CmdType CommandID;	//����ID=1
    char DeviceUID[48];//�豸��UID
};

//!<�Ͽ��������......
struct Disconnect_info
{
    CmdType CommandID;	//����ID=2
    char DeviceUID[48];//�豸��UID
};

struct AlarmRequest
{
    CmdType CommandID;		//����ID=3
    char dev_publicIP[16];			//�豸�Ĺ���IP��ַ
    edevicetype devicetype;		//�豸������
    AlarmType alarmtype;		//������Ϣ������
    int         channel;					//ͨ����
    int         user;		//�ͻ����
    int	    UserID;//�ͻ����û���¼��������豸����
    char    DeviceUID[48];//�����豸��UID
    int	HttpPort;//�豸��HttpPort
}; 

struct AlarmReject
{
    CmdType CommandID;		//����ID=4
    char dev_publicIP[16];			//�豸�Ĺ���IP��ַ
    edevicetype devicetype;		//�豸������
    AlarmType alarmtype;		//������Ϣ������
    int channel;					//ͨ����
    int user;		//�ͻ����
    int	UserID;//�ͻ����û���¼��������豸����
    char DeviceUID[48];//�����豸��UID
    int	HttpPort;//�豸��HttpPort
}; 

//!<�ͻ��˷��͵�������......
struct ClientHeartBeat
{
    CmdType CommandID;//����ID=6
    int HeartBeatNum;
    int user;		//�ͻ����
};

//!<�����豸���͵�������......
struct HeartBeatPacket
{
    CmdType CommandID;//����ID=7
    int HeartBeatNum;
    int	NetAbNormal;//֪ͨ�����������������쳣
    int	CmdPort;//�����豸����˿�
    int	HttpPort;//device Http Port
    char LocalIP[20];//�����豸IP
    char DeviceUID[48];//�豸UID��Ϣ
};

struct HeartBeatPacketReply
{
    CmdType CommandID;//����ID=8
    int		NetNormal;//����ָ���־�����Ϊ1��ʾ����ָ�
    int		DisableServer;//ֹͣ���������־,���Ϊ1��ʾ�������������ٹ�������豸�ı�����Ϣ
    char 	LocalIP[16];//Alarmserver IP
    int		AlarmPort;//AlarmServer AlarmPort
};

typedef struct AlarmMessage
{
    unsigned long   m_alarmType;
    unsigned long   m_AlarmTime;
    unsigned long   m_AlarmCnt;
    unsigned long   m_AlarmCh;
    unsigned long   m_Status;
} AlarmMessage;

struct HeartBeat
{
    int NetAbNormal;
    int dwUserLoginHander;
};

struct HeartBeatReply
{
    char DeviceUID[48];//�����豸��UID
    int NetNormal;
    int dwUserLoginHander;
};
/* change by linhh 20170526 end: ͳһ����ģ�����Ͷ��� ��HieServer_Cfg.h �� ws_status_def.h ��*/

#endif
