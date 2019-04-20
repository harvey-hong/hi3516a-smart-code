#ifndef HIE_SERVER_CFG_H
#define HIE_SERVER_CFG_H

/**************************************************************************
 *                           板型定义                                     *
 **************************************************************************/

//1500系列
#define	DVR_1500_4CIF		1	/*! 4路 CIF嵌入式 */
#define	DVR_1500_8CIF		2	/*! 8路 CIF嵌入式 */
#define	DVR_1500_12CIF		3	/*! 12路 CIF嵌入式 */
#define	DVR_1500_16CIF		4	/*! 16路 CIF嵌入式 */
#define	DVR_1500_4D1		5	/*! 4路 D1嵌入式 */
#define	DVR_1500_8D1		6	/*! 8路 D1嵌入式 */

//8550系列
#define	DVR_8550_4CIF		7	/*! 4路 CIF嵌入式 */

//1700系列
#define	DVR_1700_8CIF		8	/*! 8路 1700 CIF嵌入式 */
#define	DVR_1700_16CIF		9	/*! 16路 1700 CIF嵌入式 */
#define	DVR_1700_4D1		10	/*! 4路 1700 D1嵌入式 */
#define	DVR_1700_8D1		11	/*! 8路 1700 D1嵌入式 */
#define	DVR_1700_16D1		12	/*! 16路 1700 D1F嵌入式 */


/**************************************************************************
 *                           常量定义                                     *
 **************************************************************************/

#define DVR_MAX_VIDEOIN_NUM				(16)
#define DVR_MAX_PTZ_NUM					(DVR_MAX_VIDEOIN_NUM)
#define DVR_MAX_VIDEOENC_NUM			(DVR_MAX_VIDEOIN_NUM)
#define DVR_MAX_ALARMIN_NUM				(16)
#define DVR_MAX_ALARMOUT_NUM			(8)
#define DVR_MAX_EXCEPTION_NUM			(8)
#define DVR_MAX_VIDEOOUT_NUM			(8)

#define DVR_MAX_DAYS					(7)
#define DVR_MAX_TIMESEGMENT				(24 * 60 / 5)	//每5分钟一个时间段

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

/** @brief 最大在线用户数 */
#define DVR_MAX_ONLINEUSER_NUM			(16)

/** @brief IP白名单数 */
#define DVR_MAX_WHITEIP_NUM				(10)

#define DVR_MAX_PRESET_NUM				(128)
#define DVR_MAX_MOTIONSCOPE_NUM			(32)
#define DVR_MAX_PICSEC_NUM				(24)
#define DVR_MAX_VIDEOSHELTER_NUM		(8)
#define DVR_MAX_FONTNAME_LEN			(32)	//字体名长度
#define DVR_MAX_CHANNELNAME_LEN			(20 + 1)	//点阵通道名最大长度,含结束符
#define DVR_MAX_PTZPRONAME_LEN			(48)	//PTZ协议名称长度
#define DVR_MAX_PTZPRO_NUM				(512)	//PTZ协议个数(安装和未安装各256)
#define DVR_MAX_LATTICE_WIDTH			(24 * 10)	//点阵宽度
#define DVR_MAX_LATTICE_HEIGHT			(24)	//点阵高度
#define DVR_MAX_LATTICE_BUFSIZE			(24 * 24 * 10 / 8)	//点阵总体大小

#define DVR_MAX_PARTITION_DEVNODE_LEN	(16)
#define DVR_MAX_PARTITION_IN_HARDDISK	(15)
#define DVR_MAX_PARTITION_IN_DISKGROUP	(32)
#define DVR_MAX_HARDDISK_NUM 			(8)
#define DVR_MAX_DISKGROUP_NUM 			(8)

#define DVR_MAX_VGARESOLVING_NUM		(16)

#define DVR_MAX_VERSION_LEN				(32)

/** @brief Hxht普通字符串长度																*/
#define DVR_COMMON_STRING_LEN			(32)


/** @brief 支持的协议库的最大个数																*/
#define DVR_MAX_SUPPORT_PROTOCOL_NUM	(32)

/** @brief WIFI热点名称最大长度 */
#define DVR_MAX_SSID_LEN				(128)

/** @brief 可以识别的WIFI热点最大个数 */
#define DVR_MAX_AP_NUM					(10)

/** @brief WIFI密钥最大长度 */
#define DVR_MAX_WIFI_KEY_LEN			(128)

/** @brief 最大源设备个数																			*/
#define MAX_SOURCE_DEVICE_NUMBER		(16)

/** @brief 最大输出设备个数																			*/
#define MAX_DEVICE_OUTPUT				(16)

//支持最大VGA个数
#define MAX_VGA_NUM						(8)

//TV输出
#define MAX_TV_NUM						(8) 

/** @brief ISP 参数模版个数 */
#define DVR_MAX_ISP_TEMPLATE		(6)

/** @brief ISP 参数邋AEWindow 个数 */
#define DVR_MAX_ISP_AEWINDOW		(6)

/** @brief ISP 参数白平衡模版个数 */
#define DVR_MAX_ISP_WHITEBALANCE	(6)

/* CB 20160223 报警服务器接口封装 start */
#define DVR_ALARMSERVER_IP_STR_LEN				(16)
#define DVR_ALARMSERVER_USERNAME_LEN 			(64)
#define DVR_ALARMSERVER_PASSWORD_LEN 			(64)
/* CB 20160223 报警服务器接口封装 end */

/**************************************************************************
*								协议名称定义			                  *
**************************************************************************/
//私有协议
#define	PROTOCOL_PRIVATE				0

//手机协议
#define	PROTOCOL_TIDEMOBILE			1

//互信互通协议
#define	PROTOCOL_HXHT						(1<<1)

//RTSP协议
#define	PROTOCOL_RTSP						(1<<2)

//Onvif协议
#define	PROTOCOL_ONVIF						(1<<3)

#define	PROTOCOL_HTTP						(1<<4)

#define	PROTOCOL_DISCOVERY					(1<<5)

//RTMP协议
#define	PROTOCOL_RTMP						(1<<6)

#define	PROTOCOL_IPDECTETION				(1<<8)

//私有DDNS 服务客户端
#define	PROTOCOL_PDNS						(1<<9)

//xxx协议
//#define PROTOCOL_XXX						(1<<4)

/**************************************************************************
 *                             配置信息主、次类型定义                     *
 **************************************************************************/

///////////////////////////////////////////////////////////////////////////////////////////////////////
#define HY_DVR_GET_NETCFG 			101	/*获取网络参数          */
#define HY_DVR_SET_NETCFG 			102	/*设置网络参数          */

#define NETCFG_ALL			       	0xFFFFFFFF	/*全部网络配置          */
#define NETCFG_DHCP_CONF			1	/*Dhcp配置信息          */
#define NETCFG_DHCP_STATE			(1 << 1)	/*Dhcp状态信息          */
#define NETCFG_ETH_IF				(1 << 2)	/*Eth网络信息           */
#define NETCFG_PPPOE_CONF			(1 << 3)	/*PPPoE配置             */
#define NETCFG_PPPOE_IF				(1 << 4)	/*PPPoE网络信息         */
#define NETCFG_DNS_CONF				(1 << 5)	/*DNS配置信息           */
#define NETCFG_DDNS_CONF			(1 << 6)	/*DDNS配置信息          */
#define NETCFG_HTTP_CONF			(1 << 7)	/*http配置              */
#define NETCFG_LISTENPORT_CONF		(1 << 8)	/*服务端口配置信息      */
#define NETCFG_MOBILE_CONF			(1 << 9)	/*手机端口配置信息      */
#define NETCFG_AUTODETECT_CONF		(1 << 10)	/*自动发现端口配置信息  */
#define NETCFG_WLAN_IF				(1 << 11)	/*WIFI网络信息          */
#define NETCFG_WLAN_DHCP_CONF		(1 << 12)	/*WIFI DHCP配置         */
#define NETCFG_WLAN_DHCP_STATE		(1 << 13)	/*WIFI Dhcp状态信息     */
#define NETCFG_WLAN_DNS_CONF		(1 << 14)	/*WIFI DNS配置信息      */
#define NETCFG_WLAN_ACCESSPOINTS	(1 << 15)	/*WIFI 热点列表         */
#define NETCFG_WLAN_CONNECTION		(1 << 16)	/*WIFI 连接配置         */
#define NETCFG_WLAN_STATE			(1 << 17)	/*WIFI 连接状态         */
#define NETCFG_UPNP_CONF			(1 << 18)	/*UPNP 配置信息         */
#define NETCFG_PDNS_CONF			(1 << 19)	/*PDNS 配置信息         */

//change lhh start 20140627
#define NETCFG_RESET_IP				(1 << 20) 	/* Reset IP for admin */
#define NETCFG_RESET_PASSWORD		(1 << 21)	/* Reset Password for admin */
//change lhh end 20140627

///////////////////////////////////////////////////////////////////////////////////////////////////////
#define HY_DVR_GET_NETSERVERCFG 	103	/*获取服务器配置参数            */
#define HY_DVR_SET_NETSERVERCFG 	104	/*设置服务器配置参数            */
//次类型
#define NETSERVERCFG_ALL			0xFFFFFFFF	/*全部网络配置          */
#define NETSERVERCFG_CMS_CONF		1	/*CMS配置信息               */
#define NETSERVERCFG_CMS_STATE		2	/*CMS状态信息               */
#define NETSERVERCFG_AMS_CONF		4	/*AMS配置信息               */
#define NETSERVERCFG_NTP_CONF		8	/*NTP配置信息               */
#define NETSERVERCFG_EML_CONF		16	/*EML配置信息               */
#define NETSERVERCFG_EML_1_CONF		32	/*EML配置信息(1.1版本) */
#define NETSERVERCFG_CMS_PROTOCOL	64	/*CMS协议信息 */


///////////////////////////////////////////////////////////////////////////////////////////////////////
#define HY_DVR_GET_PICCFG 					105	/*获取中心管理服务器配置参数            */
#define HY_DVR_SET_PICCFG 					106	/*设置中心管理服务器配置参数            */
//次类型
#define PICCFG_ALL							0xFFFFFFFF	/*全部网络配置                                      */
#define PICCFG_WORKMODE_CONF					1	/*工作模式                                              */
#define PICCFG_OSD_CONF						2	/*OSD信息                                       		*/
#define PICCFG_CHNAME_CONF					4	/*通道别名信息                                   */
#define PICCFG_TIMESEC_CONF					8	/*时间段信息                                        */
#define PICCFG_VIDEOLOST_CONF					16	/*视频丢失配置信息                                      */
#define PICCFG_MOTION_CONF					32	/*移动侦测配置信息                                      */
#define PICCFG_MOSAIC_CONF						64	/*马赛克配置信息                                        */
#define PICCFG_CHNAME_UNICODE_CONF			128	/*通道别名信息(unicode)                                      */
#define PCICFG_MOTION_AREA					256
#define PICCFG_ALL_1							512		/*全部网络配置                                      */
#define PICCFG_ALL_DEF							0x400		/*所有默认图像配置                                      */ //add by qqy, at 2017-02-28 10:37:17
#define PCICFG_MOTION_AREA_DEF				0x401   /*默认移动侦测区域                                    */ //add by qqy, at 2017-02-28 10:37:17

///////////////////////////////////////////////////////////////////////////////////////////////////////
#define HY_DVR_GET_COMPRESSCFG 					107	/*获取中心管理服务器配置参数            */
#define HY_DVR_SET_COMPRESSCFG 					108	/*设置中心管理服务器配置参数            */
//次类型
#define COMPRESSCFG_ALL							0xFFFFFFFF	/*全部网络配置                                      */
#define COMPRESSCFG_WORKMODE_CONF				1	/*工作模式配置信息                                  */
#define COMPRESSCFG_COMPRESS_CAP				2	/*编码能力信息                                      */
#define COMPRESSCFG_COMPRESS_CONF				4	/*编码配置信息                                      */
// change lhh start 20140627
#define	COMPRESSCFG_COMPRESS_DEFAULT			8
// change lhh end 20140627


///////////////////////////////////////////////////////////////////////////////////////////////////////
#define HY_DVR_GET_RECORDCFG 	    109	/*获取本地录像参数 */
#define HY_DVR_SET_RECORDCFG 	    110	/*设置本地录像参数 */
//次类型
#define RECORDCFG_ALL				0xFFFFFFFF	/*全部录像配置                                      */
#define RECORD_CTRL_STATE			1	/*录像控制状态配置*/
#define RECORD_STREAM				2	/*录像码流选择 */
#define RECORD_STATE				3	/*录像状态，定时、移动侦测、手动 */ //add by qqy, at 2017-03-06 20:14:24


///////////////////////////////////////////////////////////////////////////////////////////////////////
#define HY_DVR_GET_SYSTIME 					111	/*获取系统时间参数          */
#define HY_DVR_SET_SYSTIME 					112	/*设置系统时间参数          */
//次类型
#define SYSTIME_ALL							0xFFFFFFFF	/*系统时间配置          */


///////////////////////////////////////////////////////////////////////////////////////////////////////
#define HY_DVR_GET_PTZCFG 					113	/*获取云台参数                  */
#define HY_DVR_SET_PTZCFG 					114	/*设置云台参数                  */
//次类型
#define 	PTZCFG_ALL							0xFFFFFFFF	/*云台参数配置                  */
#define	PTZ_USR_CMD						0x01		/* 配置机器人串口发送命令*/
#define	PTZ_USR_CMD_ENUM				0x02		/* 配置机器人串口发送命令*/

///////////////////////////////////////////////////////////////////////////////////////////////////////
#define HY_DVR_GET_SERIALCFG 				115	/*获取串口配置参数          */
#define HY_DVR_SET_SERIALCFG 				116	/*设置串口配置参数          */
//次类型
#define SERIALCFG_ALL						0xFFFFFFFF	/*全部串口参数配置          */
#define SERIALCFG_PTZ_ELCTRONIC_CFG			1			/*电子PTZ配置	          */
#define SERIALCFG_PTZ_REPLENISH_1_CFG		2			/*PTZ补充配置	          */
#define SERIALCFG_ALL_DEF						3	/*全部串口参数配置          */


///////////////////////////////////////////////////////////////////////////////////////////////////////
#define HY_DVR_GET_ALARMCFG 					117	/*获取报警配置参数          */
#define HY_DVR_SET_ALARMCFG 					118	/*设置报警配置参数          */
//次类型
#define ALARMCFG_ALL									0xFFFFFFFF	/*全部报警参数配置          */
#define ALARMCFG_WORKMODE_CONF				1	/*报警工作模式                  */
#define ALARMCFG_IMGCAPTURE_CONF				2	/*快照配置                          */
#define ALARMCFG_ALARMIN_CONF					4	/*报警输入配置                  */
#define ALARMCFG_ALARMOUT_CONF				8	/*报警输出配置                  */
#define ALARMCFG_EXCEPTION_CONF				16	/*异常处理配置                  */


///////////////////////////////////////////////////////////////////////////////////////////////////////
#define HY_DVR_GET_VIDEOOUTCFG 					119	/*获取显示输出配置参数          */
#define HY_DVR_SET_VIDEOOUTCFG 					120	/*设置显示输出配置参数          */
//次类型
#define VIDEOOUTCFG_ALL								0xFFFFFFFF	/*全部显示输出参数配置          */


///////////////////////////////////////////////////////////////////////////////////////////////////////
#define HY_DVR_GET_USERCFG 					121	/*获取用户信息参数          */
#define HY_DVR_SET_USERCFG 					122	/*设置用户信息参数          */
//次类型
#define USERCFG_ALL							0xFFFF	/*用户信息参数                  */
#define USERCFG_ALL_1							0xFFFFFFFF	/*用户信息参数                  */
#define USERCFG_ONE							1	/*单个用户信息                  */
#define USERCFG_CREATE						2	/*添加用户                  */
#define USERCFG_REMOVE						4	/*删除用户                  */

#define USERCFG_USER_ONLINE					8	/** @brief 在线用户	 */

#define USERCFG_USER_ONLINE_ONE				16	/** @brief 单个在线用户	 */

#define USERCFG_WHITE_IP_ENABLE				32	/** @brief 是否启用用户白名单	 */

#define USERCFG_WHITE_IP					64	/** @brief 用户白名单			 */


///////////////////////////////////////////////////////////////////////////////////////////////////////
#define HY_DVR_GET_DEVICEINFO 			123	/*获取设备信息参数                  */
#define HY_DVR_SET_DEVICEINFO			124	/*设置设备信息参数，只读不用 */
//次类型
#define DEVICEINFO_ALL					0xFFFFFFFF	/*全部设备信息参数                  */


///////////////////////////////////////////////////////////////////////////////////////////////////////
#define HY_DVR_GET_DEVICECFG 		125	/*获取设备配置参数                  */
#define HY_DVR_SET_DEVICECFG		126	/*设置设备配置参数                  */
//次类型
#define DEVICECFG_ALL						0xFFFFFFFF	/*全部设备配置参数                  */
#define DEVICECFG_LOCKSCREENTIME_CONF		1	/*锁屏时间参数                          */
#define DEVICECFG_LANGUAGE_CONF			2	/*语言                                          */
#define DEVICECFG_DATETIME_CONF				4	/*日期时间格式                          */
#define DEVICECFG_DST_CONF					8	/*夏时制                                        */
#define DEVICECFG_REMOTECONTROL_ID			16	/*设备ID，用于遥控器                */
#define DEVICECFG_TIMEZONE_CONF			32	/*时区                */
#define DEVICECFG_VIDEOSTANDARD_CONF		64	/*视频制式配置信息                                      */

///////////////////////////////////////////////////////////////////////////////////////////////////////
#define HY_DVR_GET_STORAGEINFO			127	/*获取存储系统信息                  */
#define HY_DVR_SET_STORAGEINFO			128	/*设置存储系统信息，只读不用 */
//次类型
#define STORAGEINFO_ALL					0xFFFFFFFF	/*全部设备信息参数                  */
#define STORAGEINFO_WORKMODE_CONF	1	/*存储系统工作模式参数          */
#define STORAGEINFO_DISK_INFO			2	/*硬盘信息参数                      */
#define STORAGEINFO_DISKGROUP_INFO	4	/*磁盘组信息参数                        */
#define STORAGEINFO_DISK_MARK			8	/*磁盘效验码                        */


///////////////////////////////////////////////////////////////////////////////////////////////////////
#define HY_DVR_GET_DEVICESTATE		129	/*获取设备状态信息                  */
#define HY_DVR_SET_DEVICESTATE		130	/*设置设备状态信息，空出不用 */
//次类型
#define DEVICESTATE_ALL				0xFFFFFFFF	/*全部设备状态信息                      */


///////////////////////////////////////////////////////////////////////////////////////////////////////
#define HY_DVR_GET_DEVICEMAINTENANCE	131	/*获取设备自动维护配置                  */
#define HY_DVR_SET_DEVICEMAINTENANCE	132	/*设置设备自动维护配置                  */
//次类型
#define DEVICEMAINTENANCE_ALL			0xFFFFFFFF	/*全部设备自动维护配置                  */


///////////////////////////////////////////////////////////////////////////////////////////////////////
#define HY_DVR_GET_DEVICECUSTOM	133	/*获取设备功能定制配置 */
#define HY_DVR_SET_DEVICECUSTOM	134	/*设置设备功能定制配置 */
//次类型
#define DEVICECUSTOM_ALL		0xFFFFFFFF	/*全部设备功能定制配置 */
#define DEVICECUSTOM_HCRESMODE_CONF				8	/*HC板型编解码资源分配模式信息 */

///////////////////////////////////////////////////////////////////////////////////////////////////////
//主类型
#define HY_DVR_GET_HXHT			135	/*获取HXHT配置 */
#define HY_DVR_SET_HXHT			136	/*设置HXHT配置 */
//次类型
#define HXHT_ALL				0xFFFFFFFF	/* 全部HXHT配置 */
#define	HXHT_NATSTATUS			1	/* NAT状态配置    */
#define	HXHT_VOICEPARAM			2	/* 语音呼叫配置 */
#define HXHT_CMS_STORAGE		4	/*CMS存储注册配置信息       */
#define HXHT_DEVICE_ID			8	/*前端设备ID               */

///////////////////////////////////////////////////////////////////////////////////////////////////////
#define	HY_DVR_GET_PROTOCOL		137	/* 获取要加载的协议名称（私有协议是必须加载的，不在其中） */
#define	HY_DVR_SET_PROTOCOL		138	/* 设置要加载的协议名称 */
//次类型
#define PROTOCOL_ALL			0xFFFFFFFF	/* 全部要加载的协议名称 */


#define	HY_DVR_GET_SOURCE_DEVICE	139	/* 获取源设备配置 */
#define	HY_DVR_SET_SOURCE_DEVICE	140	/* 设置源设备配置 */
//次类型
#define SOURCE_DEVICE_ALL			0xFFFFFFFF	/* 全部源设备配置 */

///////////////////////////////////////////////////////////////////////////////////////////////////////
//主类型
/** @brief 获取解码器显示设备信息												*/
#define	HY_DVR_GET_DISP_DEV					143

/** @brief 设置解码器显示设备信息												*/
#define	HY_DVR_SET_DISP_DEV					144

//次类型
/** @brief 所有解码器显示设备信息(HY_DVR_DISPDEV_CFG)						 */
#define DISP_DEV_ALL						0xFFFFFFFF

/** @brief VGA信息(HY_DVR_VGAPARA_CFG)										 */
#define DISP_DEV_VGA						1

/** @brief TV 信息(HY_DVR_VOOUT_CFG)										 */
#define DISP_DEV_TV							2

///////////////////////////////////////////////////////////////////////////////////////////////////////
#define	HY_DVR_GET_NXP8850ISP		145	/* 获取NXP8850 ISP参数 */
#define	HY_DVR_SET_NXP8850ISP		146	/* 设置NXP8850 ISP参数 */
//次类型
#define NXP8850ISP_ALL				0xFFFFFFFF	/* 全部ISP参数 */

///////////////////////////////////////////////////////////////////////////////////////////////////////
#define	HY_DVR_GET_IMAGEISP					147	
 //add by qqy,start at 2016-08-23 17:06:20
//次类型
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

/** @brief 获取应用层特性参数													*/
#define	HY_DVR_GET_APP_FEATURE				200
/** @brief 设置应用层特性参数													*/
#define	HY_DVR_SET_APP_FEATURE				201
//次类型
/** @brief 无效值																*/
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

/* CB 20160223 报警服务器接口封装 start */
#define HY_DVR_GET_ALARMSERVER 			213	/*获取报警服务器信息    */
#define HY_DVR_SET_ALARMSERVER 			214	/*设置报警服务器信息    */
/* CB 20160223 报警服务器接口封装 end */
///////////////////////////////////////////////////////////////////////////////////////////////////////

/**************************************************************************
*                         探测配置信息主、次类型定义                      *
************************************************************************* */

///////////////////////////////////////////////////////////////////////////////////////////////////////
//主类型
/** @brief 获取网络参数												          	 */
#define HY_DVR_PROBE_GET_NETCFG 			17

/** @brief 设置网络参数												          	 */
#define HY_DVR_PROBE_SET_NETCFG 			18

//次类型
/** @brief 基本网络配置(HY_DVR_PROBE_NET_CFG)						          	 */
#define PROBE_NETCFG_BASE					1

/** @brief 无线连接热点配置(HY_DVR_PROBE_WLAN_CONNECTION)						 */
#define PROBE_NETCFG_WLAN_CONNECTION		2

/** @brief 热点列表配置(HY_DVR_PROBE_WLAN_ACCESSPOINT_CFG)						 */
#define PROBE_NETCFG_WLAN_AP_LIST			3

///////////////////////////////////////////////////////////////////////////////////////////////////////

/**************************************************************************
 *                        配置信息结构体定义                              *
 **************************************************************************/

////////////////////////////////////////////////////////////////////////////

typedef struct
{
    //! 状态,0为禁用,1为启用,2为不支持
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

 
//时间计划, 24小时等分成48个时间段
typedef struct
{
	int bValid;					//! 本结构体是否有效，=0表示无效

	//! 一般情况，0为不布防，1为布防
	unsigned char bySetType[DVR_MAX_DAYS][DVR_MAX_TIMESEGMENT];

	//! 状态,0为禁用(全天布防),1为启用,2为不支持
	unsigned char byState;

	//! 保留位
	unsigned char byReserve[3];

} HY_DVR_SCHEDTIME, *LPHY_DVR_SCHEDTIME;

//工作模式
typedef struct
{
	int bValid;					//! 本结构体是否有效，=0表示无效

	int nWorkMode;				//高级模式，0为普通模式，1为高级模式

} HY_DVR_WORKMODE, *LPHY_DVR_WORKMODE;

/*字体信息*/
typedef struct
{
	int bValid;					//! 本结构体是否有效，=0表示无效

	char szFontName[DVR_MAX_FONTNAME_LEN];	//字体名
	int nFontStyle;				//字体风格
	int nFontSize;				//字体大小

} HY_DVR_FONT_INFO, *LPHY_DVR_FONT_INFO;

/*别名配置*/
typedef struct
{
	int bValid;					//! 本结构体是否有效，=0表示无效

	char strName[DVR_MAX_CHANNELNAME_LEN];	//通道名称(字符串)
	int nCharSet;				//通道名字符集 0 GB, 1 unicode

	//最大宽度 DVR_MAX_LATTICE_WIDTH
	//最大高度 DVR_MAX_LATTICE_HEIGHT
	int nWidth;					//通道名称完整字符串宽度(以像素为单位)
	int nHeight;				//通道名称完整字符串高度(以像素为单位)

	//点阵，按行扫描
	//宽为 (nWidth + 7)/8
	//高为nHeight
	//目前最大支持10个24*24的点阵
	unsigned char byLattice[DVR_MAX_LATTICE_BUFSIZE];

	HY_DVR_FONT_INFO struFontInfo;	//通道名字体信息

} HY_DVR_ALIAS_CFG, *LPHY_DVR_ALIAS_CFG;

/*别名配置,unicode版本*/
typedef struct
{
	int bValid;					//! 本结构体是否有效，=0表示无效

	//为unicode码
	unsigned short strName[DVR_MAX_CHANNELNAME_LEN];	//通道名称(字符串)
	int nCharSet;

	//最大宽度 DVR_MAX_LATTICE_WIDTH
	//最大高度 DVR_MAX_LATTICE_HEIGHT
	int nWidth;					//通道名称完整字符串宽度(以像素为单位)
	int nHeight;				//通道名称完整字符串高度(以像素为单位)

	//点阵，按行扫描
	//宽为 (nWidth + 7)/8
	//高为nHeight
	//目前最大支持10个24*24的点阵
	unsigned char byLattice[DVR_MAX_LATTICE_BUFSIZE];

	HY_DVR_FONT_INFO struFontInfo;	//通道名字体信息

} HY_DVR_ALIAS_CFG_1, *LPHY_DVR_ALIAS_CFG_1;

////////////////////////////////////////////////////////////////////////////

//DDNS协议信息结构
typedef struct
{
	int bValid;					//! 本结构体是否有效，=0表示无效

	int bDdnsEnable;			/* 0-不启用自动注册, 1-启用自动注册 */

	/* 当前DDNS，状态 (只读) */
	//0表示已经停止，1表示正在启动，2表示已经启动，3表示正在停止
	int nDdnsState;

	char szProtocolName[DVR_MAX_DDNSPRONAME_LEN];	/*协议名称  (只读) */
	char szUserName[DVR_MAX_USERNAME_LEN];	/*注册用户名 */
	char szUserPassword[DVR_MAX_PASSWORD_LEN];	/*注册用户密码 */
	char szDomainName[DVR_MAX_DOMAINNAME_LEN];	/*注册用户域名 */

	unsigned short wRegisterPort;	/*服务端口 */

	int nAutoRegIntervals;		/*自动注册间隔时间，单位为秒 */

} HY_DVR_DDNS, *LPHY_DVR_DDNS;

//DDNS功能配置结构
typedef struct
{
	int bValid;					//! 本结构体是否有效，=0表示无效

	int nDdnsProtocolCount;		//支持的DDNS协议总数(只读)

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

//PPPoE功能配置信息
typedef struct
{
	int bValid;					//! 本结构体是否有效，=0表示无效

	int bPPPoEEnable;			/* 0-不启用PPPoE,1-启用 PPPoE */

	//PPPoE相关信息
	char szPPPoEUser[DVR_MAX_USERNAME_LEN];	/* PPPoE用户名 */
	char szPPPoEPassword[DVR_MAX_PASSWORD_LEN];	/* PPPoE密码 */

} HY_DVR_PPPOE_CONF, *LPHY_DVR_PPPOE_CONF;

//PPPoE网络信息
typedef struct
{
	int bValid;					//! 本结构体是否有效，=0表示无效

	/*PPPoE 连接状态(只读) */
	//0表示没有连接，1表示正在连接，2表示连接成功，3表示正在挂断
	int nPPPoEState;

	char szPPPoEIP[DVR_MAX_IP_STR_LEN];	/*PPPoE IP地址(只读) */

	char szPPPoESubnetMask[DVR_MAX_IP_STR_LEN];	/*PPPoE 子网掩码(只读) */

	char szPPPoEGateway[DVR_MAX_IP_STR_LEN];	/*PPPoE 网关(只读) */

} HY_DVR_PPPOE_IF, *LPHY_DVR_PPPOE_IF;

//DHCP配置信息
typedef struct
{
	int bValid;					//! 本结构体是否有效，=0表示无效

	int bDhcpEnable;			/* 0-不启用Dhcp,1-启用Dhcp */

} HY_DVR_DHCP_CONF, *LPHY_DVR_DHCP_CONF;

//DHCP状态信息
typedef struct
{
	int bValid;					//! 本结构体是否有效，=0表示无效

	int nDhcpState;				/*0-未连接,1-获取成功,2-正在获取,3-获取失败,继续获取*/

} HY_DVR_DHCP_STATE, *LPHY_DVR_DHCP_STATE;

//DNS配置信息
typedef struct
{
	int bValid;					//! 本结构体是否有效，=0表示无效

	char szPrimaryDNS[DVR_MAX_IP_STR_LEN];	/*主DNS服务器 */
	char szSecondaryDNS[DVR_MAX_IP_STR_LEN];	/*备用DNS */

} HY_DVR_DNS_CONF, *LPHY_DVR_DNS_CONF;

//http配置信息
typedef struct
{
	int bValid;					//! 本结构体是否有效，=0表示无效

	int bEnable;				//启用或禁用http服务

	unsigned short wHttpPort;	/* Http端口 */

} HY_DVR_HTTP_CONF, *LPHY_DVR_HTTP_CONF;

//网络监听端口信息
typedef struct
{
	int bValid;					//! 本结构体是否有效，=0表示无效

	unsigned short wLocalCmdPort;	/*本地命令端口 */
	unsigned short wLocalMediaPort;	/*本地媒体端口 */

	unsigned short wRtpPort;	/*本地rtp端口 */
    unsigned short wOnvifPort;  /* ONVIF protocol listen port */

} HY_DVR_LISTENPORT_CONF, *LPHY_DVR_LISTENPORT_CONF;

#define LISTENPORT_CONF_LEN		sizeof(HY_DVR_LISTENPORT_CONF)

//浪潮手机客户端配置
typedef struct
{
	int bValid;					//! 本结构体是否有效，=0表示无效

	unsigned short wMobilePort;	/*手机端口 */

} HY_DVR_TIDE_MOBILE, *LPHY_DVR_TIDE_MOBILE;

//手机监听端口信息
typedef struct
{
	int bValid;					//! 本结构体是否有效，=0表示无效

	HY_DVR_TIDE_MOBILE struTide;	/*浪潮手机配置 */

} HY_DVR_MOBILE_CONF, *LPHY_DVR_MOBILE_CONF;

#define MOBILE_CONF_LEN		sizeof(HY_DVR_MOBILE_CONF)


//ETH0配置结构
typedef struct
{
	int bValid;					//! 本结构体是否有效，=0表示无效

	//本地网络适配器信息
	char szIPAddress[DVR_MAX_IP_STR_LEN];	/* DVR IP地址 */
	char szSubnetMask[DVR_MAX_IP_STR_LEN];	/* DVR 子网掩码 */
	char szGateway[DVR_MAX_IP_STR_LEN];	/* 网关地址 */
	char szMacAddress[DVR_MAX_MAC_STR_LEN];	/* 只读：服务器的物理地址 */

} HY_DVR_ETH_IF, *LPHY_DVR_ETH_IF;

//自动发现端口信息
typedef struct
{
	int bValid;					//! 本结构体是否有效，=0表示无效

	unsigned short wAutoDetectPort;	/*自动发现端口 */

} HY_DVR_AUTODETECT_CONF, *LPHY_DVR_AUTODETECT_CONF;

#define AUTODETECT_CONF_LEN		sizeof(HY_DVR_AUTODETECT_CONF)

typedef struct
{
	int bValid;					//本结构体是否有效，=0表示无效

	//!\brief WIFI状态 0 不启用 1 启用, 2 网卡未找到
	int bEnable; 

} HY_DVR_WLAN_STATE, *LPHY_DVR_WLAN_STATE;

typedef struct
{
	int bValid;					//本结构体是否有效，=0表示无效

	// !\brief 热点名称
	char szSSID[DVR_MAX_SSID_LEN];

	//!\brief 热点MAC地址
	char szMacAddress[DVR_MAX_MAC_STR_LEN];

	//!热点信号强度
	int nSignal;

	//!0-Open,1-Shared,2-WPAPSK, 3-WPA2PSK, 4-WPANONE(ad-hoc模式),5-WPA,6-WPA2
	int nAuthentication;

	//! 0表示NONE 1表示WEP 2表示TKIP 3表示AES
	int nEncrypType;

	//!\brief 热点支持的规范0表示802.11b,1表示802.11b/g,2表示802.11b/g/n
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
	int bValid;					//本结构体是否有效，=0表示无效

	HY_DVR_WLAN_ACCESSPOINT struAccessPoints[DVR_MAX_AP_NUM];
} HY_DVR_WLAN_ACCESSPOINT_CFG, *LPHY_DVR_WLAN_ACCESSPOINT_CFG;

typedef struct 
{
	//本结构体是否有效，=0表示无效
	int bValid;

	// 密码
	char szKey[DVR_MAX_WIFI_KEY_LEN];

	// 密钥类型 0-表示16进制 1表示字符串类型
	int nKeyType;
} HY_DVR_WLAN_KEY, *LPHY_DVR_WLAN_KEY;

typedef struct 
{
	//本结构体是否有效，=0表示无效
	int bValid;

	// WEP认证当前用的KEY的索引,1~4
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
	int bValid;					//本结构体是否有效，=0表示无效

	//!\brief 是否连接上 0表示未连接上 1表示连接上(只读) 2表示正在连接
	int bConnect;

	// !\brief 热点名称
	char szSSID[DVR_MAX_SSID_LEN];

	//!\brief 热点MAC地址
	char szMacAddress[DVR_MAX_MAC_STR_LEN];

	// 网络类型
	// 0表示Managed, 1表示Ad-hoc
	int nNetworkType;
	
	// 认证模式
	// 0-Open,1-Shared,2-WPAPSK, 3-WPA2PSK, 4-WPANONE(ad-hoc模式),5-WPA,6-WPA2
	int nAuthMode;

	// 加密算法 0-NONE,1-WEP,2-TKIP,3-AES
	int nEncrypType;

	// 密码配置
	HY_DVR_WLAN_KEY_CFG struKeyCfg;
} HY_DVR_WLAN_CONNECTION, *LPHY_DVR_WLAN_CONNECTION;

/*!
*  @struct	tagHY_DVR_UPNP_CONF
*  @brief	UPNP配置
*/
typedef struct
{
	int bValid;														/*!< 本结构体是否有效，0表示无效	*/

	int bEnable;													/*!< UPNP控制 0 不启用 1 启用		*/
	char szWanAddress[DVR_MAX_IP_STR_LEN];							/*!< 出口地址(只读)					*/
	int nLocalHttpPort;												/*!< 本地HTTP端口					*/
	int nExportHttpPort;											/*!< 出口HTTP端口					*/
	int nHttpPortState;												/*!< HTTP状态 0 成功 1 失败 2 映射中*/
	int nLocalMobilePort;											/*!< 本地手机端口					*/
	int nExportMobilePort;											/*!< 出口手机端口					*/
	int nMobilePortState;											/*!< 手机状态 0 成功 1 失败 2 映射中*/
	int nLocalCommandPort;											/*!< 本地信令端口					*/
	int nExportCommandPort;											/*!< 出口信令端口					*/
	int nCommandPortState;											/*!< 信令状态 0 成功 1 失败 2 映射中*/
	int nLocalMediaPort;											/*!< 本地媒体端口					*/
	int nExportMediaPort;											/*!< 出口媒体端口					*/
	int nMediaPortState;											/*!< 媒体状态 0 成功 1 失败 2 映射中*/
	int nReserve[8];												/*!< 保留							*/
} HY_DVR_UPNP_CONF, *LPHY_DVR_UPNP_CONF;

////////////////////////////////////////////////////////////////////////////
//本地网络适配器配置结构
typedef struct
{
	int bValid;					//! 本结构体是否有效，=0表示无效

	HY_DVR_DHCP_CONF struDhcp_Conf;	//Dhcp配置信息
	HY_DVR_DHCP_STATE struDhcp_State;	//Dhcp状态信息

	HY_DVR_ETH_IF struEth;		//Eth网络信息

	HY_DVR_PPPOE_CONF struPPPoE_Conf;	//PPPoE配置
	HY_DVR_PPPOE_IF struPPPoE_IF;	//PPPoE网络信息

	HY_DVR_DNS_CONF struDNS;	//DNS配置信息

	HY_DVR_DDNS_CONF struDDNS;	//DDNS配置信息

	HY_DVR_HTTP_CONF struHttp;	//http配置

	HY_DVR_LISTENPORT_CONF struListenPort;	//服务端口配置信息

	HY_DVR_MOBILE_CONF struMobilePort;	//手机端口配置信息

	HY_DVR_AUTODETECT_CONF struAutoDetectPort;	//自动发现端口配置

	HY_DVR_DHCP_CONF struWIFIDhcp_Conf; //WLAN DHCP

	HY_DVR_ETH_IF struWIFICommon; //WIFI 网络信息
	
	HY_DVR_WLAN_ACCESSPOINT_CFG struWIFIAccessPoint;/*!< WIFI热点配置 */

	HY_DVR_WLAN_CONNECTION struWIFIConnectCfg;	/*!< WIFI连接配置 */

	HY_DVR_WLAN_STATE struWIFIState;	/*!< WIFI 状态 */

	HY_DVR_DHCP_STATE struWIFIDhcp_State;	//Dhcp状态信息

	HY_DVR_DNS_CONF struWIFIDNS;	//DNS配置信息

	HY_DVR_UPNP_CONF	struUPNPConf;			/*!< UPNP配置信息				*/
} HY_DVR_NET_CFG, *LPHY_DVR_NET_CFG;

#define NET_CFG_LEN   sizeof (HY_DVR_NET_CFG)
////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////

//中心管理服务器配置信息 
typedef struct
{
	int bValid;					//! 本结构体是否有效，=0表示无效

	int bCmsEnable;				/*0-不启用管理服务器, 1-启用 */

	char szManageHostAddress[DVR_MAX_DOMAINNAME_LEN];	/*远程管理主机地址，长度考虑域名 */

	unsigned short wManageHostPort;	/*远程管理主机端口 */

	int nAutoRegIntervals;		/*注册间隔时间，单位为秒 */

} HY_DVR_NET_CMS, *LPHY_DVR_NET_CMS;

//中心管理服务器连接状态
typedef struct
{
	int bValid;					//! 本结构体是否有效，=0表示无效

	int nCmsState;				/*CMS注册状态,目前系统不支持 */

} HY_DVR_CMS_STATE, *LPHY_DVR_CMS_STATE;

//报警管理服务器配置信息
typedef struct
{
	int bValid;					//! 本结构体是否有效，=0表示无效

	int bAmsEnable;				/*0-不启用报警服务器, 1-启用 */

	char szAlarmHostAddress[DVR_MAX_DOMAINNAME_LEN];	/*报警服务器，长度考虑域名 */

	unsigned short wAlarmHostPort;	/*报警服务器端口 */

} HY_DVR_NET_AMS, *LPHY_DVR_NET_AMS;

//Ntp服务器配置信息
typedef struct
{
	int bValid;					//! 本结构体是否有效，=0表示无效

	int bNtpEnable;				/*0-不启用, 1-启用 */

	char szNtpHostAddress[DVR_MAX_DOMAINNAME_LEN];	/*Ntp服务器，长度考虑域名 */
	unsigned short wNtpHostPort;	/*Ntp服务器，端口 */

	int nAutoRegIntervals;		/*Ntp服务器同步间隔时间，单位为秒 */

} HY_DVR_NET_NTP, *LPHY_DVR_NET_NTP;

//Email服务器配置信息
typedef struct
{
	int bValid;					//! 本结构体是否有效，=0表示无效

	int bEmlEnable;				/*0-不启用, 1-启用 */

	char szSmtpServer[DVR_MAX_DOMAINNAME_LEN];	/*smtp服务器地址 */
	unsigned short wSmtpPort;	/*端口 */

	char szSenderAddress[DVR_MAX_EMAIL_LEN];	/*发件人邮箱地址 */

	char szSmtpUserName[DVR_MAX_USERNAME_LEN];	/*smtp服务器帐号(无效参数) */
	char szSmtpPassword[DVR_MAX_PASSWORD_LEN];	/*smtp服务器密码 (发件人邮箱密码) */

} HY_DVR_NET_EML, *LPHY_DVR_NET_EML;

//Email服务器配置信息(1.1.0版本使用)
typedef struct
{
	int bValid;					//! 本结构体是否有效，=0表示无效

	int bEmlEnable;				/*0-不启用, 1-启用 */

	char szSmtpServer[DVR_MAX_DOMAINNAME_LEN];	/*smtp服务器地址(可以为域名或IP地址) */
	unsigned short wSmtpPort;	/*端口 */
	int nSmtpAuth;				/*验证方式(0为NONE, 1为LOGIN, 2为PLAIN) */
	int nSmtpTLS;				/*是否使用安全登陆(0为off, 1为on) */

	char szSenderEmail[DVR_MAX_EMAIL_LEN];	/*发件人邮箱地址 */
	char szSenderPassword[DVR_MAX_PASSWORD_LEN];	/*发件人邮箱密码 */

	//以下参数暂不使用
	int nProtocol;				//(目前为smtp)
	int nTimeout;				//超时配置
	int nAuto_from;

	//以下为TLS相关高级参数，暂不使用
	int nTls_starttls;
	int nTls_certcheck;
	int nTls_force_sslv3;
	int nTls_min_dh_prime_bits;
	int nTls_priorities;

} HY_DVR_NET_EML_1, *LPHY_DVR_NET_EML_1;

//////////////////////////////////////////////////////////////////////////////
//协议名称
typedef struct
{
	int bValid;					//本结构体是否有效，=0表示无效

	unsigned long dwProtocolName;	/*!< 协议名称：协议是按位设置和读取的，例如只有手机协议时，该值为1；
									   只有互信互通协议时，该值为2；两个协议都有时，该值为3。
									   （私有协议是必须加载的，不在其中） */
} HY_DVR_PROTOCOL_NAME, *LPHY_DVR_PROTOCOL_NAME;

typedef struct
{
	int 	bValid;

	int	    BRIGHT;
	int     CONTRAST;
	int     SATURATION;
	int     HUE;
	int	    SHARP;

	int	    HREV;                   /* 数字翻转 */
	int	    XDR;                    /*  数字宽动态 */
	int	    DNIGHT;                 /* 日夜切换 */
	int	    DNR;                    /* 数字降噪	 */
	int	    SENSUP;                 /* 帧累积 */
	int	    GAMMA;                  /* GAMMA调整 */
	int	    SHADING;                /* 阴影调整 */
	int	    BADDOT;                 /* 坏点矫正 */    
	int	    DIS ;                   /* 数字去抖动 */
	int	    FOG;                    /* 数字去雾 */

	// 电子放大
	int	DOOM;
	
	int	CROSS;

	// 白平衡模式
	int	WBALANCE;
	// 手动白平衡中红分量
	int	REDEN;
	// 手动白平衡中蓝分量
	int	BLUEEN;
	
	int	BPE;
	int	BLCEN;
	int	BLCAREA;
	int	PEAK;
	int	ECLIPSE;

	// 曝光模式
	int	EXPORT;

	// 手动曝光快门时间
	int	SHUTTER;
	
	int	AGC;

	// 20130813 添加新的ISP 功能
	int	LDC;
	int 	IRIS;
	int	EXPPRI;
	int	AGCLevel;
	int	SensUpLevel;
	
} HY_DVR_ISP_PARAM, *LPHY_DVR_ISP_PARAM;

typedef struct
{
	int 	bValid;

	// 设置的ISP参数的索引与对应VALUE
	int   iIndex ;
	int   iValue ;
}HY_DVR_ISP_SET_PARAM, *LPHY_DVR_ISP_SET_PARAM;


//CMS对应的协议名称
typedef struct
{
	int bValid;					//本结构体是否有效，=0表示无效

	unsigned long dwCMSProtocol;	/*!< 协议名称：在CMS中需要填写IP地址，需要告诉设备端，这个
									   CMS中的IP地址是为哪一个协议准备的，如果是私有协议，那么设备
									   将注册到NVMS中；如果是Hxht协议，则设备注册到Hxht的接入服务器中。
									   该参数只能表示一种协议。 */
} HY_DVR_CMS_FOR_PROTOCOL, *LPHY_DVR_CMS_FOR_PROTOCOL;

//////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////
//网络管理结构
typedef struct
{
	int bValid;					//! 本结构体是否有效，=0表示无效

	HY_DVR_NET_CMS struCMS;		//中心管理服务器信息    
	HY_DVR_NET_AMS struAMS;		//报警服务器信息    
	HY_DVR_NET_NTP struNTP;		//NTP服务器信息 
	HY_DVR_NET_EML struEML;		//Email服务器信息  

	HY_DVR_CMS_FOR_PROTOCOL struCMSForProtocol;	//中心管理服务器信息对应的协议（和CMS是绑定的）

	HY_DVR_CMS_STATE struCmsState;	//中心管理服务器连接状态

	HY_DVR_NET_EML_1 struEML_1;	//Email服务器信息  1.1版

} HY_DVR_NET_MANAGER, *LPHY_DVR_NET_MANAGER;

#define NET_MANAGER_LEN   sizeof (HY_DVR_NET_MANAGER)
////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////

//图像参数配置结构(每通道支持24个时间段)
typedef struct
{
	int bValid;					//! 本结构体是否有效，=0表示无效

	int bTimeSegEnable;			/*启用时间片 */

	int nStartTime;				/*开始时间 相对00:00时的秒数  */
	int nStopTime;				/*结束时间 相对00:00时的秒数  */

	int nBrightness;			/*亮度,0-255 */
	int nContrast;				/*对比度,0-255 */
	int nSaturation;			/*饱和度,0-255 */
	int nHue;					/*色调,0-255 */

} HY_DVR_CHROMA_SEC, *LPHY_DVR_CHROMA_SEC;

//图像参数配置结构(每通道支持24个时间段)
typedef struct
{
	int bValid;					//! 本结构体是否有效，=0表示无效

	//色度参数
	HY_DVR_CHROMA_SEC struChromaSec[DVR_MAX_PICSEC_NUM];

} HY_DVR_CHROMA, *LPHY_DVR_CHROMA;


/*异常处理方式*/
#define DVR_ALARM_TRIGGER_NONE			0	/*无响应 */
#define DVR_ALARM_TRIGGER_PREVIEW		(0x1)	/*触发屏幕显示，通道参数由录像参数决定 */
#define DVR_ALARM_TRIGGER_AUDIOOUT	(0x1 << 1)	/*声音警告 */
#define DVR_ALARM_TRIGGER_RECORD		(0x1 << 2)	/*触发录像 */
#define DVR_ALARM_TRIGGER_SNAPSHOT	(0x1 << 3)	/*触发拍照 */
#define DVR_ALARM_TRIGGER_ALARMOUT	(0x1 << 4)	/*触发报警输出 */
#define DVR_ALARM_TRIGGER_NOTIFYAMS	(0x1 << 5)	/*上传报警中心 */
#define DVR_ALARM_TRIGGER_PTZ			(0x1 << 6)	/*触发PTZ */
#define DVR_ALARM_TRIGGER_EMAIL		(0x1 << 7)	/*发生EMail通知 */
#define DVR_ALARM_TRIGGER_NOTIFYGUI	(0x1 << 8)	/*屏幕提示 */

/*联动处理结构体*/
typedef struct
{
	int bValid;					//! 本结构体是否有效，=0表示无效

	unsigned long dwHandleType;	/*处理方式,处理方式的"或"结果 */

	int nRecordChannelMask;		//联动录像通道标识，按位表示
	int nSnapshotChannelMask;	//联动快照通道标识，按位表示
	int nAlarmOutChannelMask;	//联动报警输出通道标识，按位表示

	//可以联动多个通道
	int nPtzAction[DVR_MAX_PTZ_NUM];	//nPtzAction 联动的动作,  0表示无动作 , 1联动预置点, 2联动巡航 3联动轨迹
	int nPtzIndex[DVR_MAX_PTZ_NUM];	//nPtzIndex  联动的预置点/巡航/轨迹的编号

	int nMonitorMask;			//主显、辅显、主显+辅显,spot

} HY_DVR_HANDLEEXCEPTION, *LPHY_DVR_HANDLEEXCEPTION;


//移动侦测
typedef struct
{
    int bValid;					//! 本结构体是否有效，=0表示无效

    int bEnable;				/* 是否处理移动侦测 */

    int nSenstive;				/*移动侦测灵敏度, 0 - 5,越低越灵敏,0xff关闭 */

    int nXScope;
    int nYScope;				/*X,Y方向宏块范围 */

    /*侦测区域,共有32*32个小宏块,为1表示改宏块是移动侦测区域,0-表示不是 */
    unsigned char byMotionScope[DVR_MAX_MOTIONSCOPE_NUM][DVR_MAX_MOTIONSCOPE_NUM];

    HY_DVR_HANDLEEXCEPTION struHandleType;	/* 处理方式 */

    HY_DVR_SCHEDTIME struSchedTime;	/* 0表示不布防，1表示布防 */
    HY_DVR_SCHEDTIME_EX struSchedTimeEx;	 
} HY_DVR_MOTION, *LPHY_DVR_MOTION;


//信号丢失报警 
typedef struct
{
	int bValid;					//! 本结构体是否有效，=0表示无效

	int bEnable;				/* 是否处理信号丢失报警 */

	HY_DVR_HANDLEEXCEPTION struHandleType;	/* 处理方式 */

	HY_DVR_SCHEDTIME struSchedTime;	/* 0表示不布防，1表示布防 */

} HY_DVR_VILOST, *LPHY_DVR_VILOST;


//遮挡报警 区域大小704*576 
typedef struct
{
	int bValid;					//! 本结构体是否有效，=0表示无效

	int bEnable;				/* 是否启用 */

	//这里用整数，代表实际像素坐标
	int nHideAreaTopLeftX;		/* 马赛克区域的x相对坐标 */
	int nHideAreaTopLeftY;		/* 马赛克区域的y相对坐标 */
	int nHideAreaBottomRightX;	/* 马赛克区域的x相对坐标 */
	int nHideAreaBottomRightY;	/* 马赛克区域的y相对坐标 */

} HY_DVR_MOSAIC_INFO, *LPHY_DVR_MOSAIC_INFO;

//遮挡报警 区域大小704*576 
typedef struct
{
	int bValid;					//! 本结构体是否有效，=0表示无效

	//马赛克
	int bEnableMosaic;			/* 是否启动遮挡 ,0-否,1-是 区域为704*576 */

	HY_DVR_MOSAIC_INFO struMosaicInfo[DVR_MAX_VIDEOSHELTER_NUM];

} HY_DVR_MOSAIC, *LPHY_DVR_MOSAIC;

//OSD配置信息
typedef struct
{
	int bValid;					//! 本结构体是否有效，=0表示无效

	int nShowOsd;				/* 0为通道时间均不显示、1为显示通道，2、为显示时间、3为两者均显示 */

	int nTimeTopLeftX;			/* 时间的x坐标 */
	int nTimeTopLeftY;			/* 时间的y坐标 */

	int nNameTopLeftX;			/* 名称的x坐标 */
	int nNameTopLeftY;			/* 名称的y坐标 */

	int	nTimePos ;
	int 	nTextPos ;

} HY_DVR_OSD_CFG, *LPHY_DVR_OSD_CFG;

typedef struct
{
	int bValid;					//! 本结构体是否有效，=0表示无效

	int nShowOsd;				/* 0为通道时间均不显示、1为显示通道，2、为显示时间、3为两者均显示 */

	int nTimeTopLeftX;			/* 时间的x坐标 */
	int nTimeTopLeftY;			/* 时间的y坐标 */

	int nNameTopLeftX;			/* 名称的x坐标 */
	int nNameTopLeftY;			/* 名称的y坐标 */
} HY_DVR_OSD_CFG_1, *LPHY_DVR_OSD_CFG_1;


/////////////////////////////////////////////////////////////////////////////////////////////////
//图像参数结构
typedef struct
{
    int bValid;                 //! 本结构体是否有效，=0表示无效

    HY_DVR_WORKMODE     struWorkMode;   //工作模式(只读)

    //显示OSD
    HY_DVR_OSD_CFG  struOsd[DVR_MAX_VIDEOIN_NUM];

    //通道名
    HY_DVR_ALIAS_CFG struChName[DVR_MAX_VIDEOIN_NUM];

    //图像参数，分24个时间段
    HY_DVR_CHROMA struChroma[DVR_MAX_VIDEOIN_NUM];

    //信号丢失报警
    HY_DVR_VILOST struViLost[DVR_MAX_VIDEOIN_NUM];

    //移动侦测
    HY_DVR_MOTION struMotion[DVR_MAX_VIDEOIN_NUM];

    //马赛克
    HY_DVR_MOSAIC struMosaic[DVR_MAX_VIDEOIN_NUM];

    //通道名（unicode）
    HY_DVR_ALIAS_CFG_1 struChName_1[DVR_MAX_VIDEOIN_NUM];
} HY_DVR_PIC_CFG, *LPHY_DVR_PIC_CFG;

#define PIC_CFG_LEN				sizeof (HY_DVR_PIC_CFG)

/////////////////////////////////////////////////////////////////////////////////////////////////
typedef struct
{
	int bValid;					//! 本结构体是否有效，=0表示无效

	HY_DVR_WORKMODE 		struWorkMode;	//工作模式(只读)

	//显示OSD
	HY_DVR_OSD_CFG_1 		struOsd[DVR_MAX_VIDEOIN_NUM];

	//通道名
	HY_DVR_ALIAS_CFG 		struChName[DVR_MAX_VIDEOIN_NUM];

	//图像参数，分24个时间段
	HY_DVR_CHROMA 			struChroma[DVR_MAX_VIDEOIN_NUM];

	//信号丢失报警 
	HY_DVR_VILOST 			struViLost[DVR_MAX_VIDEOIN_NUM];

	//移动侦测 
	HY_DVR_MOTION 			struMotion[DVR_MAX_VIDEOIN_NUM];

	//马赛克
	HY_DVR_MOSAIC 			struMosaic[DVR_MAX_VIDEOIN_NUM];

	//通道名（unicode）
	HY_DVR_ALIAS_CFG_1 		struChName_1[DVR_MAX_VIDEOIN_NUM];
} HY_DVR_PIC_CFG_1, *LPHY_DVR_PIC_CFG_1;



typedef struct
{
	int 	bValid;			
	// 移动侦测区域个数
	int	m_AreaCnt ;				
	// 移动侦测区域个数
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

/* NXP8850 Image Sensor Processing配置信息: 数字降噪 （De-Noise）*/
typedef struct
{
	int bValid;					//! 本结构体是否有效，=0表示无效

	/*
	   参数模板配置 :
	   意义： 通过环境条件的不同进行不同参数脚本的调节
	   0    普通 
	   1    室内 
	   2 室内低亮度 
	   3 室外
	   4 出入口
	   5 自定义
	   6，7 待定
	 */
	int nWorkMode;

	/*
	   图像颜色 （Video Color）
	   0    黑白
	   1    彩色  
	 */
	int nVideoColor;

	/*
	   图像方向 (Video orientation)
	   0    正常
	   1    翻转      
	   2    镜像
	   3    翻转+ 镜像
	 */
	int nVideoOrientation;

	/*
	   前端输入频率
	   0    60Hz
	   1    50Hz
	 */
	int nInputFrequency;

} HY_DVR_ISP_COMMON, *LPHY_DVR_ISP_COMMON;

/* NXP8850 Image Sensor Processing配置信息: AE Mode 设置*/
typedef struct
{
	int bValid;					//! 本结构体是否有效，=0表示无效

	int nMode;					//AE模式，0-自动 1-背光 2-手动

}HY_DVR_AE_MODE, *LPHY_DVR_AE_MODE;

/* NXP8850 Image Sensor Processing配置信息: AE Window 设置*/
typedef struct
{
	int bValid;					//! 本结构体是否有效，=0表示无效

	//开关(on /off)
	int bOpen;

	//X (0-4095) 需要识别到最大的宽度，如果是最大720p,就是1280
	int nX;

	//Y (0-4095) 需要识别最大有效像素高度
	int nY;

	//width (1-4095) 需要识别到最大的宽度
	int nWidth;

	//height(1-4095) 需要识别最大有效像素高度
	int nHeight;

	//Weighting (1X 到 8X可选) 参数0-7
	int nWeighting;
	
} HY_DVR_AEWINDOW_CFG, *LPHY_DVR_AEWINDOW_CFG;

/* NXP8850 Image Sensor Processing配置信息: 曝光参数*/
typedef struct
{
	int bValid;					//! 本结构体是否有效，=0表示无效

	//镜头光圈：(Lens Type)     0为 开启自动光圈  1-256为 手动光圈对应(0-255)
	int bLensType;

	/*
		目标亮度  (Target Lumiance)	0-255
	*/
	int nTargetLumiance;

	/*
		偏移 (Offset)	0-255
	*/
	int nOffset;

	/*
		快门速度  (Shutter Speed)
		最小速度，0～1/2
		最大速度，1/120～1
		速度可选
		0,1/120,1/60,1/30,1/15,1/8,1/4,1/2,1 
	*/
	int nMinShutterSpeed;
	int nMaxShutterSpeed;

	/*
		增益系数 (Gain)
		最小增益 1x ~ 16x 
		最大增益 2x ~ 32x
	*/
	int nMinAutoGain;
	int nMaxAutoGain;
	
} HY_DVR_EXPOSAL_CFG, *LPHY_DVR_EXPOSAL_CFG;

/* NXP8850 Image Sensor Processing配置信息: 白平衡 (White Balance)*/
typedef struct
{
	int bValid;					//! 本结构体是否有效，=0表示无效

	/*
		1 自动
		2 手动： 手动 需要修改 RED Gain (0-255),Blue Gain(0-255)
		3 多云
		4 太阳
		5 阴天
		6 冷白荧光灯
	*/
	int bWorkMode;

	int nRedGain[DVR_MAX_ISP_WHITEBALANCE];

	int nBlueGain[DVR_MAX_ISP_WHITEBALANCE];

} HY_DVR_WHITEBALANCE_CFG, *LPHY_DVR_WHITEBALANCE_CFG;

/* NXP8850 Image Sensor Processing配置信息: 数字降噪 （De-Noise）*/
typedef struct
{
	int bValid;					//! 本结构体是否有效，=0表示无效

	/*
	   0    关闭
	   1    开启
	   Y  Strength （0-255）
	   Cb strength (0-255)
	   Cr strength (0-255)
	 */
	int bWorkMode;

	int nYStrength;

	int nCbStrength;

	int nCrStrength;

} HY_DVR_DENOISE_CFG, *LPHY_DVR_DENOISE_CFG;

/* NXP8850 Image Sensor Processing配置信息*/
typedef struct
{
	int bValid;					//! 本结构体是否有效，=0表示无效

	/*
	AE 模式，为手动模式时，AE Window设置配置才是有效的
	*/
	HY_DVR_AE_MODE struAEMode;

	/*
		AE Window 设置,分成6个Window,分别是 1 -6 
	*/
	HY_DVR_AEWINDOW_CFG struAEWindow[DVR_MAX_ISP_AEWINDOW];

	/*
		曝光参数
	*/
	HY_DVR_EXPOSAL_CFG struExposal;
		
	/*
		白平衡 (White Balance)
	*/
	HY_DVR_WHITEBALANCE_CFG struWhiteBalance;

	/*
		数字降噪 （De-Noise）
	*/
	HY_DVR_DENOISE_CFG struDeNoise;

} HY_DVR_ISP_TEMPLATE, *LPHY_DVR_ISP_TEMPLATE;

/* NXP8850 Image Sensor Processing配置信息*/
typedef struct
{
	int bValid;					//! 本结构体是否有效，=0表示无效

	//ISP基本配置参数
	HY_DVR_ISP_COMMON struCommon;

	//ISP参数模版
	HY_DVR_ISP_TEMPLATE struTemplate[DVR_MAX_ISP_TEMPLATE];

} HY_DVR_NXP8850ISP_CFG, *LPHY_DVR_NXP8850ISP_CFG;

#define NXP8850ISP_CFG_LEN		(sizeof (HY_DVR_NXP8850ISP_CFG))
/////////////////////////////////////////////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////////////////////////////////////
//编码类型
#define   DVR_MAX_STREAM_TYPE		2
#define   DVR_CAP_NORMAL_H264    	0x01
#define   DVR_CAP_ADVANCED_H264		0x02

#define   DVR_CAP_RESOLUTION_QCIF   0x01
#define   DVR_CAP_RESOLUTION_CIF    0x02
#define   DVR_CAP_RESOLUTION_D1   	0x04			//实时2CIF
#define   DVR_CAP_RESOLUTION_SD    	0x08			//实时D1

#define DVR_CAP_RESOLUTION_4CIF_SIM   0x10		//非实时D1
#define DVR_CAP_RESOLUTION_2CIF_SIM   0x20		//非实时2CIF

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


//编码能力结构
typedef struct
{
	int bValid;					//! 本结构体是否有效，=0表示无效

	int nStreamFormatCap;		/*支持的码流格式， 所有支持的格式相或的结果 */

	unsigned long dwResolutionCap[DVR_MAX_STREAM_TYPE];	/*每种编码格式下支持的分辨率格式,支持所有的格式相或的结果 */

} HY_DVR_COMPRESS_CAP, *LPHY_DVR_COMPRESS_CAP;

//编码配置结构
typedef struct
{
	int bValid;					//! 本结构体是否有效，=0表示无效

	//帧率 1-20，ff为全帧率
	int nVideoFrameRate;

	//码率上限。单位K，
	int nVideoBitrateH;

	//码率下限
	int nVideoBitrateL;

	//量化系数:0-6
	int nQuotiety;

	//分辨率0-CIF, 1-D1
	int nResolution;

	//码流类型0-视频流,1-复合流
	int nStreamType;

	//录像质量 0-高质量 1-标准 2-低 3-自定义
	int nPicQuality;

	//码率类型0: 变码率率，1: 定码，2：限定码率
	int nBitrateType;
//add by liuy date 2016-01-25 start
	//图像宽
	int nwidth;

	//图像高
	int nheight;

	//最大帧率
	int nMaxFps;

//add by liuy date 2016-01-25 end

} HY_DVR_COMPRESSION_INFO, *LPHY_DVR_COMPRESSION_INFO;

//编码配置结构
typedef struct
{
	int bValid;					//! 本结构体是否有效，=0表示无效

	//帧率 1-20，ff为全帧率
	int nVideoFrameRate;

	//码率上限。单位K，
	int nVideoBitrateH;

	//码率下限
	int nVideoBitrateL;

	//量化系数:0-6
	int nQuotiety;

	//分辨率0-CIF, 1-D1
	int nResolution;

	//码流类型0-视频流,1-复合流
	int nStreamType;

	//录像质量 0-高质量 1-标准 2-低 3-自定义
	int nPicQuality;

	//码率类型0: 变码率率，1: 定码，2：限定码率
	int nBitrateType;
//add by liuy date 2016-01-25 start
	//图像宽
	int nwidth;

	//图像高
	int nheight;

	//最大帧率
	int nMaxFps;

//add by liuy date 2016-01-25 end

//add by liuy date 2016-02-03 start
	//编码类型 0-h264,1-H265
	int nEncFormat;
//add by liuy date 2016-02-03 end

} HY_DVR_COMPRESSION_INFO_EX, *LPHY_DVR_COMPRESSION_INFO_EX;


//子码流编码参数结构
typedef struct
{
	int 		bValid;	

	int 		bEnalbe;		

	int 		nVideoFrameRate;

	int 		nVideoBitrate;

	// 子码流分辨率
	int	nResolution ;

} HY_DVR_AUX_COMPRESSION_INFO, *LPHY_DVR_AUX_COMPRESSION_INFO;


//通道编码参数结构
typedef struct
{
	int 		bValid;					//! 本结构体是否有效，=0表示无效

	int 		nDelayRecordTime;		/* 录象延迟时间长度 */
	int 		nPreRecordTime;			/* 预录时间 0-不预录 1-5秒 2-10秒 3-15秒 4-20秒 5-25秒 */

	HY_DVR_COMPRESS_CAP 			struCompressCap;	/*压缩能力， 仅在获取参数时有效（只读） */

	HY_DVR_AUX_COMPRESSION_INFO 	struNetPara;	/* 子码流 */

	HY_DVR_COMPRESSION_INFO 		struRecordPara[3];	/*0基本配置,1事件录像,2手动录像 */

} HY_DVR_COMPRESSION_CHANNEL, *LPHY_DVR_COMPRESSION_CHANNEL;

//通道编码参数结构
typedef struct
{
	int 		bValid;					//! 本结构体是否有效，=0表示无效

	int 		nDelayRecordTime;		/* 录象延迟时间长度 */
	int 		nPreRecordTime;			/* 预录时间 0-不预录 1-5秒 2-10秒 3-15秒 4-20秒 5-25秒 */

	HY_DVR_COMPRESS_CAP 			struCompressCap;	/*压缩能力， 仅在获取参数时有效（只读） */

	HY_DVR_AUX_COMPRESSION_INFO 	struNetPara;	/* 子码流 */

	HY_DVR_COMPRESSION_INFO_EX 		struRecordPara[3];	/*0基本配置,1事件录像,2手动录像 */

} HY_DVR_COMPRESSION_CHANNEL_EX, *LPHY_DVR_COMPRESSION_CHANNEL_EX;


typedef struct
{
	int bValid;					//! 本结构体是否有效，=0表示无效

	HY_DVR_WORKMODE struWorkMode;	//工作模式(只读)

	HY_DVR_COMPRESSION_CHANNEL 	struCompressChannel[DVR_MAX_VIDEOIN_NUM];

} HY_DVR_COMPRESSION_CFG, *LPHY_DVR_COMPRESSION_CFG;

typedef struct
{
	int bValid;					//! 本结构体是否有效，=0表示无效

	HY_DVR_WORKMODE struWorkMode;	//工作模式(只读)

	HY_DVR_COMPRESSION_CHANNEL_EX 	struCompressChannel[DVR_MAX_VIDEOIN_NUM];

} HY_DVR_COMPRESSION_CFG_EX, *LPHY_DVR_COMPRESSION_CFG_EX;

#define COMPRESS_CFG_LEN   sizeof (HY_DVR_COMPRESSION_CFG)
/////////////////////////////////////////////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////////////////////////////////////
//录像控制状态
typedef struct
{
	int bValid;					//! 本结构体是否有效，=0表示无效

	//0表示手动录像,1表示自动录像,2表示关闭录像
	unsigned int uRecordMode[DVR_MAX_VIDEOIN_NUM];
} HY_DVR_RECORD_CTRLSTATE, *LPHY_DVR_RECORD_CTRLSTATE;

//录像码流选择
typedef struct
{
	int bValid;					//! 本结构体是否有效，=0表示无效

	//0表示主码流,1表示子码流(CIF),2表示高清子码流(VGA)
	unsigned int uStreamIndex[DVR_MAX_VIDEOIN_NUM];
} HY_DVR_RECORD_STREAM, *LPHY_DVR_RECORD_STREAM;


//录像码流选择
typedef struct
{
	int bValid;					//! 本结构体是否有效，=0表示无效

	int 	week[4] ;
	int	start[4];
	int	end[4];
	int	enable[4];
} HY_DVR_RECORD_PLAN, *LPHY_DVR_RECORD_PLAN;


//录像计划结构
typedef struct
{
    int bValid;					//! 本结构体是否有效，=0表示无效

    //0表示无录像，1表示定时录像，2表示移动录像
    HY_DVR_SCHEDTIME 		struRecordTime[DVR_MAX_VIDEOIN_NUM];

    HY_DVR_SCHEDTIME_EX 		sRecordSchedule[DVR_MAX_VIDEOIN_NUM]; 

    //\\ 获取华宇形式的录像计划
    HY_DVR_RECORD_PLAN	strRecordPlan[DVR_MAX_VIDEOIN_NUM];

    //录像控制状态
    HY_DVR_RECORD_CTRLSTATE struRecordCtlState;

    //录像码流选择
    HY_DVR_RECORD_STREAM struRecordStream;

} HY_DVR_RECORD_SCHED, *LPHY_DVR_RECORD_SCHED;

#define RECORD_SCHED_LEN sizeof(HY_DVR_RECORD_SCHED)
/////////////////////////////////////////////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////////////////////////////////////
//配置系统时间参数
typedef struct
{
	int nYear;					//年
	int nMonth;					//月
	int nDay;					//日
	int nHour;					//时
	int nMinute;				//分
	int nSecond;				//秒

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

//云台协议信息
typedef struct
{
	int bValid;					//! 本结构体是否有效，=0表示无效

	int nUseable;				/*PTZ协议的状态（0：未安装，1：已安装） */
	int bSystem;				/*PTZ协议的状态（0：非系统固有的，可删除，1：系统固有的，不能删除） */

	char szPTZName[DVR_MAX_PTZPRONAME_LEN];	/*PTZ协议名称 */

} HY_DVR_PTZPRO, *LPHY_DVR_PTZPRO;

//云台协议管理信息
typedef struct
{
	int bValid;					//! 本结构体是否有效，=0表示无效

	int nPtzCount;				/* 系统支持PTZ协议的个数 */

	HY_DVR_PTZPRO struPTZProtocol[DVR_MAX_PTZPRO_NUM];	/*系统PTZ名称 */

} HY_DVR_PTZPRO_CFG, *LPHY_DVR_PTZPRO_CFG;

#define PTZPRO_CFG_LEN sizeof(HY_DVR_PTZPRO_CFG)
/////////////////////////////////////////////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////////////////////////////////////
//云台信息
typedef struct
{
	int bValid;					//! 本结构体是否有效，=0表示无效

	unsigned char bySetPreset[DVR_MAX_PRESET_NUM];	/* 预置点是否设置,0-没有设置,1-设置 */
	unsigned char bySetCruise[DVR_MAX_PRESET_NUM];	/* 巡航是否设置: 0-没有设置,1-设置 */
	unsigned char bySetTrack[DVR_MAX_PRESET_NUM];	/* 轨迹是否设置,0-没有设置,1-设置 */

} HY_DVR_PTZ, *LPHY_DVR_PTZ;

//串口配置
typedef struct
{
	int bValid;					//! 本结构体是否有效，=0表示无效

	int nBaudRate;				/* 波特率(bps)，0－50，1－75，2－110，3－150，4－300，5－600，6－1200，7－2400，8－4800，9－9600，10－19200， 11－38400，12－57600，13－76800，14－115.2k; */
	int nDataBit;				/* 数据有几位 0－5位，1－6位，2－7位，3－8位; */
	int nStopBit;				/* 停止位 0－1位，1－2位; */
	int nParity;				/* 校验 0－无校验，1－奇校验，2－偶校验; */
	int nFlowcontrol;			/* 0－无，1－软流控,2-硬流控 */
	int nDecoderAddress;		/*解码器地址:0 - 255 */
	int nComType;				/*0－COM1 RS232，1－COM2 RS485 */

} HY_DVR_SERIAL, *LPHY_DVR_SERIAL;

/////////////////////////////////////////////////////////////////////////////////////////////////
//云台守望动作
typedef struct
{
	int bValid;					//! 本结构体是否有效，=0表示无效

	int nUseable;				//! 是否启用守望动作
	int nCycle;					//! 守望动作的周期, 0表示开机
	int nAction;				//! 动作类型 0表示预置点 1表示巡航 2表示轨迹 3表示自动扫描
	int nIndex;					//! 索引号(预置点号,巡航号,轨迹号,自动扫描线路号)
} HY_DVR_PTZACTION, *LPHY_DVR_PTZACTION;

typedef struct
{
	int bValid;					//! 本结构体是否有效，=0表示无效

	char szPTZName[DVR_MAX_PTZPRONAME_LEN];	/*PTZ协议名称 */

	int speed;						/* 将PTZ速度存入配置文件Edvr.cfg中 */
	HY_DVR_SERIAL struSerial;	//串口配置

	HY_DVR_PTZACTION struPTZAction;

} HY_DVR_DECODER_CHANNEL, *LPHY_DVR_DECODER_CHANNEL;

//sony的电子ptz机芯配置
typedef struct  
{
	int bValid;					//! 本结构体是否有效，=0表示无效

	int nDigitZoom;				/*!< 数字变倍 (0-关 1-开)			                        */
	int nLowLum;				/*!< 低照度 (0-关 1-开)										*/
	int nBackLight;				/*!< 背光补偿 (0-关 1-开)									*/
	int nAutoShutter;			/*!< 自动快门 (0-手动 1-自动)			                    */
	int nWhiteBalance;			/*!< 白平衡 (0-手动 1-自动 2-室内 3-室外 4-ATW 5-ONE PUSH)	*/
	int nRedGain;				/*!< 红增益 (0~255)											*/
	int nBlueGain;				/*!< 蓝增益 (0~255)											*/
	int nAcutance;				/*!< 锐度 (0~15)											*/
	int nExpMode;				/*!< 曝光模式 (0-自动 1-手动 2-快门优先 3-光圈优先)			*/
	int nShutterSpeed;			/*!< 快门速度 (0~15)				                        */
	int nIrisSpeed;				/*!< 光圈 (0-手动 1-自动）									*/
	int nWideDyn;				/*!< 宽动态 (0-关 1-开)										*/
	int n3DFilter;				/*!< 3D降噪	(0-关 1-开)										*/
	int nMirror;				/*!< 镜像  (0-关 1-开)										*/
	int nReverse;				/*!< 翻转  (0-关 1-开)										*/
	int nInputFrequency;		/*!< 输入频率  (0-60Hz 1-50Hz)                              */
	int nLongRestrict;			/*!< 长焦限速（1-开，0-关）									*/
	int nNorthSet;				/*!< 北位设定（1-设定）										*/

} HY_DVR_PTZ_ELCTRONIC_SONY, *LPHY_DVR_PTZ_ELCTRONIC_SONY;

//单个通道的电子ptz配置
typedef struct  
{
	int bValid;					//! 本结构体是否有效，=0表示无效

	HY_DVR_PTZ_ELCTRONIC_SONY struPtzElcSony;

} HY_DVR_PTZ_ELCTRONIC_CHANNEL, *LPHY_DVR_PTZ_ELCTRONIC_CHANNEL;


typedef struct 
{
	int bValid;																/*!< 本结构体是否有效，0表示无效 */

	int	iWorkMode;															/*!< 操作模式: 0自动，1手动									*/
	int	iManualSwitch;														/*!< 手动开关: 0手动关，1手动开								*/
	int	iOpenThreshold;														/*!< 开启温度，高于此温度时开启								*/
	int	iCloseThreshold;													/*!< 关闭温度，低于此温度时开启								*/
} HY_DVR_PTZ_TEMPERATURE_DEVICE, *LPHY_DVR_PTZ_TEMPERATURE_DEVICE;

/*!
*  @struct	HY_DVR_PTZ_ELCTRONIC_CH_TEMPERATURE
*  @brief	单个通道的电子ptz温度设备配置
*/
typedef struct  
{
	int bValid;																/*!< 本结构体是否有效，0表示无效 */

	HY_DVR_PTZ_TEMPERATURE_DEVICE struPtzFanDevice;							/*!< 风扇设备配置 */
	HY_DVR_PTZ_TEMPERATURE_DEVICE struPtzHeaterDevice;						/*!< 加热设备配置 */
	HY_DVR_PTZ_TEMPERATURE_DEVICE struPtzReserveDevice[14];					/*!< 温度设备配置(增加设备时减一) */

} HY_DVR_PTZ_ELCTRONIC_CH_TEMPERATURE, *LPHY_DVR_PTZ_ELCTRONIC_CH_TEMPERATURE;

//所有通道的电子ptz配置
typedef struct  
{
	int bValid;					//! 本结构体是否有效，=0表示无效

	HY_DVR_PTZ_ELCTRONIC_CHANNEL   struPtzElcChannel[DVR_MAX_PTZ_NUM];
	HY_DVR_PTZ_ELCTRONIC_CH_TEMPERATURE   struPtzElcChTemperature[DVR_MAX_PTZ_NUM];

} HY_DVR_PTZ_ELCTRONIC, *LPHY_DVR_PTZ_ELCTRONIC;

/*!
*  @struct	tagHY_DVR_PTZACTION
*  @brief	云台守望动作
*/
typedef struct
{
	int bValid;																/*!< 本结构体是否有效，0表示无效 */
	HY_DVR_PTZACTION struPTZAction[DVR_MAX_PTZ_NUM];						/*!< 云台守望 */

} HY_DVR_PTZACTION_CFG, *LPHY_DVR_PTZACTION_CFG;

/*!
*  @struct	HY_DVR_PTZ_REPLENISH_CONTENT_1
*  @brief	ptz设备补充配置内容
*/
typedef struct 
{
	int bValid;																/*!< 本结构体是否有效，0表示无效 */

	int	iLowPowerConsumption;												/*!< 低功耗: 0关，1开										*/
	int	iScreenWiper;														/*!< 雨刷器: 0关，1单刮，2连刮								*/
	int	iNightVision;														/*!< 夜视：0关，1开，2自动									*/
	int	iDemist;															/*!< 除雾：0关，1开											*/
} HY_DVR_PTZ_REPLENISH_CONTENT_1, *LPHY_DVR_PTZ_REPLENISH_CONTENT_1;

/*!
*  @struct	HY_DVR_PTZ_REPLENISH_1
*  @brief	ptz设备补充配置
*/
typedef struct
{
	int bValid;																/*!< 本结构体是否有效，0表示无效 */
	HY_DVR_PTZ_REPLENISH_CONTENT_1 struContent[DVR_MAX_PTZ_NUM];			/*!< 配置内容 */

} HY_DVR_PTZ_REPLENISH_1, *LPHY_DVR_PTZ_REPLENISH_1;

/*!
*  @struct	tagHY_DVR_DECODER_CFG
*  @brief	设备解码配置
 */
typedef struct
{
	int bValid;																/*!< 本结构体是否有效，0表示无效 */
	HY_DVR_DECODER_CHANNEL struDecoder[DVR_MAX_PTZ_NUM];					/*!< 各解码通道配置 */
	HY_DVR_PTZACTION_CFG	struPtzAction;									/*!< 各通道云台守望配置 */
	HY_DVR_PTZ_ELCTRONIC	struPtzElc;										/*!< 电子ptz配置 */
	HY_DVR_PTZ_REPLENISH_1	struReplenish1;									/*!< 补充配置1		*/

} HY_DVR_DECODER_CFG, *LPHY_DVR_DECODER_CFG;

#define  DECODER_CFG_LEN  sizeof(HY_DVR_DECODER_CFG)
///////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////
//各报警输入配置
typedef struct
{
	int bValid;					//! 本结构体是否有效，=0表示无效

	int nAlarmInType;			/*报警器类型,0：常开,1：常闭 */

	HY_DVR_HANDLEEXCEPTION struHandleType;	/* 处理方式 */

	HY_DVR_SCHEDTIME struSchedTime;	//时间计划

} HY_DVR_ALARMIN_CHANNEL, *LPHY_DVR_ALARMIN_CHANNEL;

//各报警输出通道配置
typedef struct
{
	int bValid;					//! 本结构体是否有效，=0表示无效

	int nAlarmOutDelay;			/* 输出保持时间(-1为无限，手动关闭) */

	HY_DVR_SCHEDTIME struSchedTime;	//报警输出布防时间

} HY_DVR_ALARMOUT_CHANNEL, *LPHY_DVR_ALARMOUT_CHANNEL;

//报警联动抓图配置
typedef struct
{
	int bValid;					//! 本结构体是否有效，=0表示无效

	int nCapPicCount;			//联动快照张数
	int nCapPicIntervalTime;	//联动快照间隔时间

} HY_DVR_ALARM_CAPTURE_PIC, *LPHY_DVR_ALARM_CAPTURE_PIC;

//系统异常检测
typedef struct
{
	int bValid;					//! 本结构体是否有效，=0表示无效

	int bEnable;				//是否启动检测

	int nCheckTime;				//检测时间间隔，单位为秒

	HY_DVR_HANDLEEXCEPTION struHandleType;	/* 联动处理方式 */

} HY_DVR_SYSTEM_EXCEPTION, *LPHY_DVR_SYSTEM_EXCEPTION;

//报警设置
typedef struct
{
	int bValid;					//! 本结构体是否有效，=0表示无效

	HY_DVR_WORKMODE struWorkMode;	//工作模式(只读)

	HY_DVR_ALARM_CAPTURE_PIC struCapPic;	//联动快照

	HY_DVR_ALARMIN_CHANNEL struAlarmIn[DVR_MAX_ALARMIN_NUM];	//报警输入配置

	HY_DVR_ALARMOUT_CHANNEL struAlarmOut[DVR_MAX_ALARMOUT_NUM];	//报警输入配置

	/*
	   0    硬盘故障
	   1    IP冲突
	   2    非法访问
	   3    网线断
	   4    盘组满
	   5    盘组异常
	 */
	HY_DVR_SYSTEM_EXCEPTION struSystemException[DVR_MAX_EXCEPTION_NUM];

	//报警输入通道别名
	HY_DVR_ALIAS_CFG struAlarmInAlias[DVR_MAX_ALARMIN_NUM];

	//报警输出通道别名
	HY_DVR_ALIAS_CFG struAlarmOutAlias[DVR_MAX_ALARMOUT_NUM];

	//报警输入通道别名(unicode)
	HY_DVR_ALIAS_CFG_1 struAlarmInAlias_1[DVR_MAX_ALARMIN_NUM];

	//报警输出通道别名(unicode)
	HY_DVR_ALIAS_CFG_1 struAlarmOutAlias_1[DVR_MAX_ALARMOUT_NUM];
    
        HY_DVR_SCHEDTIME_EX struAlarmInSchedule[DVR_MAX_ALARMIN_NUM]; //add by qqy, at 2017-03-13 16:03:48
} HY_DVR_ALARM_CFG, *LPHY_DVR_ALARM_CFG;

#define ALARM_CFG_LEN   sizeof (HY_DVR_ALARM_CFG)
//////////////////////////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////
//显示参数
typedef struct
{
	int bValid;					//! 本结构体是否有效，=0表示无效

	int nScreenSaveTime;		/* 屏幕保护时间 */

	int nMenuAlphaValue;		/* 菜单与背景图象对比度 */

	//int nResolvingPowerCount; //支持的主显分辨率数

	//int nCurrentResolvingPower[3];    //当前主显分变率

	//int nResolvingPowerList[3][DVR_MAX_VGARESOLVING_NUM]; //支持的主显分变率列表

} HY_DVR_VO_CFG, *LPHY_DVR_VO_CFG;

#define VO_CFG_LEN   sizeof (HY_DVR_VO_CFG)
/////////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////

//用户使能信息
typedef struct
{
	int bValid;					//! 本结构体是否有效，=0表示无效

	int bEnable;				//是否启用

} HY_DVR_USER_ENABLE, *LPHY_DVR_USER_ENABLE;


//用户基本信息
typedef struct
{
	int bValid;					//! 本结构体是否有效，=0表示无效

	char szPassword[DVR_MAX_PASSWORD_LEN];	/* 密码 */

	unsigned char byLimitMac[DVR_MAX_MAC_NUM_LEN];	/* 限制访问物理地址 */

	char szLimitIP[DVR_MAX_IP_STR_LEN];	/* 限制访问IP地址 */

	char szEmail[DVR_MAX_EMAIL_LEN];

} HY_DVR_USER_INFO, *LPHY_DVR_USER_INFO;

//用户权限信息
typedef struct
{
	int bValid;					//! 本结构体是否有效，=0表示无效

	int nLocalRight[DVR_MAX_RIGHT_NUM];	/* 权限 */
	/*数组0: 本地系统设置 */
	/*数组1: 文件管理 */
	/*数组2: 录像备份 */
	/*数组3: 系统关闭 */
	/*数组4: 邮件通知 */

	int nRemoteRight[DVR_MAX_RIGHT_NUM];	/* 权限 */
	/*数组0: 系统设置 */
	/*数组1: 语音对讲 */
	/*数组2: 串口输出 */
	/*数组3: 报警输出 */
	/*数组4: 远程升级 */
	/*数组5: 关闭系统 */

	int nChannelRight[DVR_MAX_RIGHT_NUM];	/* 权限 */
	/*数组0: 本地回放 */
	/*数组1: 本地预览 */
	/*数组2: 本地云台控制 */
	/*数组3: 本地手动录像 */
	/*数组4: 远程回放 */
	/*数组5: 远程预览 */
	/*数组6: 远程云台控制 */
	/*数组7: 远程手动录像 */

} HY_DVR_USER_RIGHT, *LPHY_DVR_USER_RIGHT;


//用户信息权限信息
typedef struct
{
	int bValid;					//! 本结构体是否有效，=0表示无效

	char szUserName[DVR_MAX_USERNAME_LEN];	/* 用户名 最大16位 */

	//用户使能信息
	HY_DVR_USER_ENABLE struUserEnable;

	//用户基本信息
	HY_DVR_USER_INFO struUserInfo;

	//用户权限信息
	HY_DVR_USER_RIGHT struUserRight;

} HY_DVR_USER, *LPHY_DVR_USER;

typedef struct
{
	int bValid;					//! 本结构体是否有效，=0表示无效

	// 是否为远程用户
	int bRemote;

	// 是否处于连接状态
	int bConnect;

	// 用户句柄
	unsigned long dwUserID;

	// 登陆协议
	unsigned long dwProtocolID;

	// 用户名
	char szUserName[DVR_MAX_USERNAME_LEN];

	// 登陆IP
	unsigned long dwIPAddress;

	// 登陆时间
	HY_DVR_TIME struLoginTime;

	// 网络流量 b/s
	unsigned long dwBitrate;
}HY_DVR_ONLINEUSER, *LPHY_DVR_ONLINEUSER; 

typedef struct
{
	int bValid;					//! 本结构体是否有效，=0表示无效

	// 在线用户列表
	HY_DVR_ONLINEUSER struOnlineUser[DVR_MAX_ONLINEUSER_NUM];
} HY_DVR_ONLINEUSER_CFG, *LPHY_DVR_ONLINEUSER_CFG;

typedef struct
{
	int bValid;					//! 本结构体是否有效，=0表示无效

	unsigned long dwWhiteIP;
} HY_DVR_WHITEIP, *LPHY_DVR_WHITEIP;

typedef struct
{
	int bValid;					//! 本结构体是否有效，=0表示无效

	int bEnable;				// 是否启用IP白名单
} HY_DVR_WHITEIP_ENABLE, *LPHY_DVR_WHITEIP_ENABLE;

typedef struct
{
	int bValid;					//! 本结构体是否有效，=0表示无效

	HY_DVR_WORKMODE struWorkMode;	//工作模式(只读)

	HY_DVR_USER struUser[DVR_MAX_USER_NUM];

	HY_DVR_ONLINEUSER_CFG struUserOnline;

	HY_DVR_WHITEIP struWhiteIP[DVR_MAX_WHITEIP_NUM];

	HY_DVR_WHITEIP_ENABLE struWhiteIPEnable;

} HY_DVR_USER_CFG, *LPHY_DVR_USER_CFG;

#define USER_CFG_LEN	sizeof(HY_DVR_USER_CFG)
/////////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////
//设备信息结构(只读)
typedef struct
{
	int bValid;					//! 本结构体是否有效，=0表示无效

	//板型编号
	unsigned long dwBoardType;

	//设备型谱名称，如HY-2016HC
	char szTypeName[DVR_MAX_VERSION_LEN];

    unsigned long dwSerialNum;  /* 序列号 */

    //!\brief   硬件版本
    char szHardwareVersion[DVR_MAX_VERSION_LEN];

    //!\brief   软件版本
    char szSoftwareVersion[DVR_MAX_VERSION_LEN];

    //!\brief   编码版本
    char szDspVersion[DVR_MAX_VERSION_LEN];

	unsigned char 	byVideoInChannels;	/*视频输入路数 */
	unsigned char 	byAudioInChannels;	/*音频输入路数 */
	unsigned char 	byAlarmInChannels;	/*报警输入路数 */
	unsigned char 	byAlarmOutChannels;	/*报警输出路数 */

	unsigned char 	byVGAChannels;	/*VGA接口个数 */

	unsigned char 	bySpotOutChannles;	/*SPOT输出路数 */
	unsigned char 	byVoiceInChannels;	/*语音对讲输入路数 */

} HY_DVR_DEVICE_INFO, *LPHY_DVR_DEVICE_INFO;

#define	DEVICE_INFO_LEN	sizeof(HY_DVR_DEVICE_INFO)
//////////////////////////////////////////////////////////////////////////////



//////////////////////////////////////////////////////////////////////////////
///*!
//*  @struct	tagHY_DVR_DEVICE_OUTPUT_INDEX
//*  @brief	输出设备编号(只读)
//*/
//typedef struct tagHY_DVR_DEVICE_OUTPUT_INDEX
//{
//	int bValid;															/*!< 本结构体是否有效，0表示无效 */
//
//	unsigned long	dwDeviceType;										/*!< 设备类型(0: 无效, 1: VGA, 2 :TV) */
//	unsigned long	dwDeviceIndex;										/*!< 设备编号 */
//
//} HY_DVR_DEVICE_OUTPUT_INDEX, *LPHY_DVR_DEVICE_OUTPUT_INDEX;
//
///*!
//*  @struct	tagHY_DVR_DEVICE_OUTPUT
//*  @brief	输出设备信息(只读)
//*/
//typedef struct tagHY_DVR_DEVICE_OUTPUT
//{
//	int bValid;															/*!< 本结构体是否有效，0表示无效 */
//
//	HY_DVR_DEVICE_OUTPUT_INDEX cOutputDevice[MAX_DEVICE_OUTPUT];
//
//} HY_DVR_DEVICE_OUTPUT, *LPHY_DVR_DEVICE_OUTPUT;

//////////////////////////////////////////////////////////////////////////////
//夏时制信息结构
typedef struct
{
	int bValid;					//! 本结构体是否有效，=0表示无效

	//!\brief   是否启用夏时制
	int bEnableDST;

	HY_DVR_TIME struStart;		//开始时间，年无效

	HY_DVR_TIME struEnd;		//结束时间，年无效

	int nDSTBias;				//调整多少时间，以秒为单位

} HY_DVR_DST, *LPHY_DVR_DST;

//设备基本配置，日期时间格式
typedef struct
{
	int bValid;					//! 本结构体是否有效，=0表示无效

	//!\brief   自动锁屏时间（单位为秒）
	int nAutoLockScreenTime;

	//!\brief   语言
	// 0(Default) - 简体中文 1 - 繁体中文 2 - 英文
	int nMenuLanguage;

	//!\brief   日期格式
	// 0(Default) - YYYY-MM-DD W hh:mm:ss, 1 - YYYY-MM-DD hh:mm:ss, 2 - MM-DD-YYYY W hh:mm:ss, 3 - MM-DD-YYYY hh:mm:ss
	int nDateFormat;

	//!\brief   时间格式（12小时制，24小时制）
	int nTimeFormat;

} HY_DVR_GUI, *LPHY_DVR_GUI;

//设备基本配置，时区
typedef struct
{
	int bValid;					//! 本结构体是否有效，=0表示无效

	//!\brief   时区时差
	int nTimeZone;

} HY_DVR_TIMEZONE, *LPHY_DVR_TIMEZONE;

//设备基本配置，时区
typedef struct
{
	int bValid;					//! 本结构体是否有效，=0表示无效

	int nDvrID;					/* DVR ID,用于遥控器 */

} HY_DVR_DVRID, *LPHY_DVR_DVRID;

typedef struct
{
	int bValid;					//! 本结构体是否有效，=0表示无效

	int nVideoInStandard;		//视频输入制式

	int nVideoOutStandard;		//视频输出制式（通常和输入制式一样）

} HY_DVR_STANDARD, *LPHY_DVR_STANDARD;


//设备基本配置结构
typedef struct
{
	int bValid;					//! 本结构体是否有效，=0表示无效

	HY_DVR_DVRID 		struDvrID;

	//!\brief   自动锁屏时间（单位为秒）
	HY_DVR_GUI 			struGUI;

	HY_DVR_TIMEZONE 	struTimeZone;

	//夏时制信息
	HY_DVR_DST 			struDST;

	//设备别名
	HY_DVR_ALIAS_CFG 	struDvrAlias;

	//设备制式
	HY_DVR_STANDARD 	struStandard;

	//设备别名(unicode)
	HY_DVR_ALIAS_CFG_1 	struDvrAlias_1;

} HY_DVR_DEVICE_CFG, *LPHY_DVR_DEVICE_CFG;

#define	DEVICE_CFG_LEN	sizeof(HY_DVR_DEVICE_CFG)
//////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////
//分区信息结构
typedef struct
{
	int bValid;					//! 本结构体是否有效，=0表示无效

	char szDevNode[DVR_MAX_PARTITION_DEVNODE_LEN];	//设备节点名, 如 /dev/sda1

	unsigned long dwCapacity;	//总容量, M为单位
	unsigned long dwSpare;		//剩余容量

	unsigned long dwStartCHS;	// 分区起始扇区

	unsigned long dwEndtCHS;	// 分区结束扇区

} HY_DVR_DISK_PARTITION, *LPHY_DVR_DISK_PARTITION;

//硬盘标记
typedef struct
{
	int bValid;					//! 本结构体是否有效，=0表示无效

	int nVerifyMark;			//验证码(配置改变时，验证码会同步改变)

} HY_DVR_DISK_MARK, *LPHY_DVR_DISK_MARK;

#define	DISK_MARK_LEN	sizeof(HY_DVR_DISK_MARK)

//存储设备类型（HD、SD、USB、IPSAN、NAS）
typedef struct
{
	int bValid;					//! 本结构体是否有效，=0表示无效

	int nDiskType;				//! 0- unkonown、1-HDD、2-USB、4-CDROM、8-SD、16-IPSAN、32-NAS
}HY_DVR_DISK_TYPE, *LPHY_DVR_DISK_TYPE;

//硬盘信息结构
typedef struct
{
	int bValid;					//! 本结构体是否有效，=0表示无效

	int bEnable;				//是否安装有此硬盘

	HY_DVR_DISK_MARK struVerifyMark;	//验证码(配置改变时，验证码会同步改变)

	int nRestState;				//硬盘状态（是否休眠）
	int nWriteState;			//硬盘状态（是否读写）

	char szSerialNum[DVR_MAX_VERSION_LEN];	//序列号
	char szTypeName[DVR_MAX_VERSION_LEN];	//硬盘类型
	int nBusNum;				//物理位置,SATA1

	unsigned long dwCapacity;	//容量,M为单位
	//unsigned long dwSpare;        //总剩余容量

	int nPartitionCount;		//分区数量

	HY_DVR_DISK_PARTITION struPartitionInfo[DVR_MAX_PARTITION_IN_HARDDISK];	//分区信息

	HY_DVR_DISK_TYPE struDiskType;

} HY_DVR_DISK, *LPHY_DVR_DISK;

//盘组信息结构
typedef struct
{
	int bValid;					//本结构体是否有效，=0表示无效

	int bEnable;					//是否启用本盘组

	int nGroupType;				//盘组类型

	int nBindChannelMask;		//绑定的通道

	int nDataKeepTime;			//数据保持时间

	int nPartitionCount;			//已添加的分区数量

	char szPartitionList[DVR_MAX_PARTITION_IN_DISKGROUP][DVR_MAX_PARTITION_DEVNODE_LEN];	//设备节点列表,支持32个分区

} HY_DVR_DISK_GROUP, *LPHY_DVR_DISK_GROUP;

/*!
*  @struct	tagHY_DVR_DISK_TYPE_CFG
*  @brief	存储设备类型配置
*/
typedef struct tagHY_DVR_DISK_TYPE_CFG
{
	int bValid;																/*!< 本结构体是否有效，0表示无效 */
	HY_DVR_DISK_TYPE struDiskType[DVR_MAX_HARDDISK_NUM];					/*!< 存储设备类型 */

}HY_DVR_DISK_TYPE_CFG, *LPHY_DVR_DISK_TYPE_CFG;
//存储管理 信息

typedef struct
{
	int 		bValid;									//本结构体是否有效，=0表示无效

	HY_DVR_WORKMODE 		struWorkMode;				//工作模式(只读)

	HY_DVR_DISK 			struDisk[DVR_MAX_HARDDISK_NUM];	//8个硬盘（只读）

	HY_DVR_DISK_GROUP 		struDiskGroup[DVR_MAX_DISKGROUP_NUM];	//8个盘组（只读）

	HY_DVR_DISK_TYPE_CFG 	struDiskType;										/*!< 存储设备类型配置（只读） */

	int		struRecordTime;								//\\ 设置文件打包时间
} HY_DVR_STORAGE_CFG, *LPHY_DVR_STORAGE_CFG;

#define	STORAGE_CFG_LEN	sizeof(HY_DVR_STORAGE_CFG)
//////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////
/*!
*	@struct tagHY_DVR_VGA_VIDEO_BITRATE
*	@brief	VGA子码流码率
*/
typedef struct tagHY_DVR_VGA_VIDEO_BITRATE
{
	int bValid;																/*!< 本结构体是否有效，0表示无效 */

	int nVGAVideoBitrate;													/*!< 子码流码率（单位kbit/s） */

}HY_DVR_VGA_VIDEO_BITRATE, *LPHY_DVR_VGA_VIDEO_BITRATE;

//设备通道状态
typedef struct
{
	int bValid;					//本结构体是否有效，=0表示无效(即系统没有该通道)

	int nVideoBitrate;			//主码流码率
	int nChildVideoBitrate;		//子码流码率

	int bUseAuxVideoStream;		//是否启动子码流

	//无录像0
	//报警录像类型1
	//普通类型2
	//手动录像类型3
	//移动录像4
	int nRecordType;			//录像状态(分类型)
	int bViLost;				//是否有无视频信号报警(0表示无信号，1表示有信号)
	int bMotion;				//是否有移动报警(尚不支持)

	HY_DVR_VGA_VIDEO_BITRATE struVGABitrate;								/*!< VGA子码流码率 */

} HY_DVR_CHANNEL_STATE, *LPHY_DVR_CHANNEL_STATE;

/*!
*  @struct	tagHY_DVR_VGA_VIDEO_BITRATE_CFG
*  @brief	VGA子码流码率配置
*/
typedef struct tagHY_DVR_VGA_VIDEO_BITRATE_CFG
{
	int bValid;																/*!< 本结构体是否有效，0表示无效 */
	HY_DVR_VGA_VIDEO_BITRATE struVGABitrate[DVR_MAX_VIDEOIN_NUM];			/*!< VGA子码流码率 */

}HY_DVR_VGA_VIDEO_BITRATE_CFG, *LPHY_DVR_VGA_VIDEO_BITRATE_CFG;

//设备状态信息(只读)
typedef struct
{
	int bValid;					//本结构体是否有效，=0表示无效

	HY_DVR_CHANNEL_STATE struChannelState[DVR_MAX_VIDEOIN_NUM];	//通道状态

	HY_DVR_VGA_VIDEO_BITRATE_CFG struVGABitrate;							/*!< VGA子码流码率配置 */

} HY_DVR_DEVICE_STATE, *LPHY_DVR_DEVICE_STATE;

#define	DEVICE_STATE_LEN	sizeof(HY_DVR_DEVICE_STATE)
//////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////
//设备自动维护基本配置
typedef struct
{
	int bValid;					//本结构体是否有效，=0表示无效(即系统没有该通道)

	int bEnable;				//启用，还是禁用

	int nMode;					//维护模式 0为每天、1为每周、2为单次

	//星期模式时，第0位表示星期天,第1位表示星期1,对应位为1表示当天有效
	int nWeekDayMask;

	//如为单次模式，则年月日时分有效
	//其它模式，时分有效
	HY_DVR_TIME struTime;

} HY_DVR_MAINTENANCE_COMMON, *LPHY_DVR_MAINTENANCE_COMMON;

//设备自动维护
typedef struct
{
	int bValid;					//本结构体是否有效，=0表示无效

	HY_DVR_MAINTENANCE_COMMON struCommon;	//基本参数

} HY_DVR_DEVICE_MAINTENANCE, *LPHY_DVR_DEVICE_MAINTENANCE;

#define	DEVICE_MAINTENANCE_LEN	sizeof(HY_DVR_DEVICE_MAINTENANCE)
//////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////

/*!
*  @struct	tagHY_DVR_HC_RESMODE
*  @brief	HC板型编解码资源分配模式
*/
typedef struct tagHY_DVR_HC_RESMODE
{
	int bValid;					/*!< 本结构体是否有效，0表示无效 */

	//该结构体只在HC或HS板型中有效

	/*  工作模式取值范围为(0 - 2)
	   16路板型: 
	   模式0时，系统支持16路实时CIF或非实时2CIF、D1格式编解码
	   模式1时，系统支持8路实时2CIF 加8路实时CIF 编解，4路2CIF实时解码
	   模式2时，系统支持4路实时D1 加12路实时CIF编码，1路D1实时解码
	   8路板型: 
	   模式0时，系统支持8路实时CIF或非实时2CIF、D1格式编解码
	   模式1时，系统支持2路实时D1 加6路实时CIF 编解，4路D1实时解码
	   模式2时，系统支持6路实时D1 加2路实时CIF编码，1路D1实时解码
	 */
	int nMode;

	unsigned long dwChMask;		/*!< 通道掩码，第0位为1表示通道1支持2CIF或D1格式编码，依次类推 */

} HY_DVR_HC_RESMODE, *LPHY_DVR_HC_RESMODE;

//设备功能定制
typedef struct
{
	int bValid;					//本结构体是否有效，=0表示无效

	HY_DVR_WORKMODE struUser;	//高级用户管理模式

	HY_DVR_WORKMODE struAlarm;	//高级报警管理模式

	HY_DVR_WORKMODE struPic;	//高级图像参数配置

	HY_DVR_WORKMODE struEmail;	//Email报警联动

	HY_DVR_WORKMODE struRecord;	//高级录像参数配置

	HY_DVR_WORKMODE struCMS;	//中心管理服务器配置

	HY_DVR_WORKMODE struAMS;	//报警服务器配置

	HY_DVR_WORKMODE struNTP;	//NTP服务器配置

	HY_DVR_WORKMODE struStorage;	//高级存储管理

	HY_DVR_WORKMODE struMaintenance;	//自动维护配置

	HY_DVR_HC_RESMODE struHCResMode;	/*!< HC板型编解码资源分配模式 */

	//HY_DVR_WORKMODE struBeep; //声音告警自动清除(目前尚未支持)

} HY_DVR_DEVICE_CUSTOM, *LPHY_DVR_DEVICE_CUSTOM;

#define	DEVICE_CUSTOM_LEN	sizeof(HY_DVR_DEVICE_CUSTOM)
//////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////
//告警阀值（暂不实现）
typedef struct
{
	int bValid;					//本结构体是否有效，=0表示无效

	float fCPUUseRatio;			/*!< CPU利用率 */
	float fMemoryUseRatio;		/*!< 内存利用率 */
	float fDiskSpaceRatio;		/*!< 硬盘利用率 */
	unsigned long dwDiskSpaceBalance;	/*!< 硬盘剩余空间 */

} HY_DVR_THRESHOLD, *LPHY_DVR_THRESHOLD;

//下载方式（可以依据NAT的配置来区分，暂不实现）
typedef struct
{
	int bValid;					//本结构体是否有效，=0表示无效
	unsigned long dwDownloadMode;	/*!< 下载方式， 0-hxht, 1-STREAM_TCP */

} HY_DVR_DOWNLOAD_MODE, *LPHY_DVR_DOWNLOADMODE;

//////////////////////////////////////////////////////////////////////////////

//中心管理服务器存储注册配置信息
typedef struct
{
	int bValid;					//! 本结构体是否有效，=0表示无效

	char szManageHostAddress[DVR_MAX_DOMAINNAME_LEN];	/*远程管理主机地址，长度考虑域名 */

	unsigned short wManageHostPort;	/*远程管理主机端口 */

} HY_DVR_NET_CMS_STOREAGE, *LPHY_DVR_NET_CMS_STOREAGE;

//前端设备ID
typedef struct
{
	int bValid;					//! 本结构体是否有效，=0表示无效

	char szDeviceID[DVR_COMMON_STRING_LEN];	/* 前端设备ID */

} HY_DVR_DEVICE_ID, *LPHY_DVR_DEVICE_ID;

//NAT配置
typedef struct
{
	int bValid;					//本结构体是否有效，=0表示无效

	unsigned long dwIsNAT;		/*!< 是否在NAT后面，0表示不在后面，1表示在NAT后面 */

} HY_DVR_NATSTATUS, *LPHY_DVR_NATSTATUS;

/*
压缩格式 语音通道数 采样深度   采样速率    
G711U.HX      1        16        8000  
G711A.HX      1        16        8000  
G722.HX       1        16    8000或16000
*/
//语音参数配置
typedef struct
{
	int bValid;					//本结构体是否有效，=0表示无效

	char szAudioEncoder[DVR_COMMON_STRING_LEN];	/*!< 支持的语音编码格式，可以有多个，以逗号隔开；G711U.HX G711A.HX G722.HX */
	unsigned long dwChannel;	/*!< 通道数 */
	unsigned long dwBitsPerSample;	/*!< 采样深度 */
	unsigned long dwSamplesPerSec;	/*!< 采样率 */

} HY_DVR_VOICEPARAM, *LPHY_DVR_VOICEPARAM;

typedef struct
{
	int bValid;					//本结构体是否有效，=0表示无效

	HY_DVR_NET_CMS_STOREAGE struCmsStorage;	//中心管理服务器存储注册信息
	HY_DVR_DEVICE_ID struDeviceID;	//前端设备ID
	HY_DVR_NATSTATUS struNATStatus;	//NAT状态
	HY_DVR_VOICEPARAM struVoiceParam;	//语音呼叫参数

} HY_DVR_HXHT_CFG, *LPHY_DVR_HXHT_CFG;

typedef struct
{
	int bValid;					//本结构体是否有效，=0表示无效

	unsigned int dwFileMap; //0~30位表示1号~31号的文件分布情况,0表示无文件,1表示有文件
} HY_DVR_FILEMAP_CFG, * LPHY_DVR_FILEMAP_CFG;


//////////////////////////////////////////////////////////////////////////////

/** @brief 地址长度(含结束符)																		*/
#define HY_DVR_ADDRESS_LEN				(256)

/** @brief 用户名长度																	*/
#define HY_DVR_USERNAME_LEN				(32)

/** @brief 用户密码长度																	*/
#define HY_DVR_USERPASS_LEN				(32)

/** @brief 默认保留字段个数																*/
#define HY_DVR_DEF_RESERVE_NUM			(3)

/*!
*  @struct	tagHY_DVR_USERLOGIN_INFO
*  @brief	用户登录参数
*/
typedef struct tagHY_DVR_USERLOGIN
{
	int bValid;													//本结构体是否有效，=0表示无效
	char	sServerIP[HY_DVR_ADDRESS_LEN];						/*!< 服务器端IP地址							*/
	unsigned long	dwCommandPort;								/*!< 登录连接的信令端口						*/
	char	sUName[HY_DVR_USERNAME_LEN];						/*!< 登录用户的用户名称						*/
	char	sUPass[HY_DVR_USERPASS_LEN];						/*!< 登录用户的用户密码						*/
	unsigned long	dwReserve[HY_DVR_DEF_RESERVE_NUM];			/*!< 保留									*/
}HY_DVR_USERLOGIN_INFO, *LPHY_DVR_USERLOGIN_INFO;

/*!
*  @struct	tagHY_DVR_SOURCE_DEVICE_INFO
*  @brief	源设备信息
*/
typedef struct tagHY_DVR_SOURCE_DEVICE_INFO
{
	int bValid;													//本结构体是否有效，=0表示无效

	int						nEnable;							/*!< 0表示不启用，1表示启用			*/
	HY_DVR_USERLOGIN_INFO	cUserPara;							/*!< 用户参数						*/
	unsigned long			dwVideoInNumber;					/*!< 视频输入数						*/
	unsigned long			dwReserve[HY_DVR_DEF_RESERVE_NUM];	/*!< 保留							*/
}HY_DVR_SOURCE_DEVICE_INFO, *LPHY_DVR_SOURCE_DEVICE_INFO;

/*!
*  @struct	tagHY_DVR_SOURCE_DEVICE_INFO_CONFIG
*  @brief	源设备配置
*/
typedef struct tagHY_DVR_SOURCE_DEVICE_INFO_CONFIG
{
	int bValid;														//本结构体是否有效，=0表示无效

	HY_DVR_SOURCE_DEVICE_INFO	cSourceDevice[MAX_SOURCE_DEVICE_NUMBER];	/*!< 源设备信息					*/
	unsigned long				dwReserve[HY_DVR_DEF_RESERVE_NUM];			/*!< 保留				*/
}HY_DVR_SOURCE_DEVICE_INFO_CONFIG, *LPHY_DVR_SOURCE_DEVICE_INFO_CONFIG;

//////////////////////////////////////////////////////////////////////////////
//显示设备属性
//获取显示设备信息

/*!
*  @struct	tagHY_DVR_VGAPARA
*  @brief	VGA参数
*/
typedef struct tagHY_DVR_VGAPARA
{
	int bValid;									/*!< 本结构体是否有效，0表示无效 */

	int nResolution;							/*!< 分辨率 ,比特位表示 */
	int nResolutionCap;							/*!< 分屏能力，只读。与分辨率有关,按位表示，例：第九位为1表示
												支持9分屏 */
	unsigned long	dwDeviceIndex;				/*!< 设备编号 */

}HY_DVR_VGAPARA, *LPHY_DVR_VGAPARA;

/*!
*  @struct	tagHY_DVR_VGAPARA_CFG
*  @brief	VGA参数配置
*/
typedef struct tagHY_DVR_VGAPARA_CFG
{
	int bValid;									/*!< 0表示无效 1表示有效 */

	int nVGACount;								/*!< VGA Out实际个数 */
	HY_DVR_VGAPARA struVga[MAX_VGA_NUM];

}HY_DVR_VGAPARA_CFG, *LPHY_DVR_VGAPARA_CFG;

/*!
*  @struct	tagHY_DVR_VOOUT
*  @brief	视频输出
*/
typedef struct tagHY_DVR_VOOUT
{
	int bValid; 								/*!< 0表示无效 1表示有效 */

	int byVideoFormat;							/*!< 输出制式,0-PAL,1-NTSC */
	int wLeftffset;								/*!< 视频输出左偏移 */
	int wRightffset;							/*!< 视频输出右偏移 */
	int wTopffset;								/*!< 视频输出上偏移 */
	int wBottomffset;							/*!< 视频输出下偏移 */
	int dwResolutionCap;						/*!< 分屏能力，只读。*/
	unsigned long	dwDeviceIndex;				/*!< 设备编号 */

}HY_DVR_VOOUT, *LPHY_DVR_VOOUT;

/*!
*  @struct	tagHY_DVR_VOOUT_CFG
*  @brief	视频输出配置
*/
typedef struct tagHY_DVR_VOOUT_CFG
{
	int bValid;									/*!< 0表示无效 1表示有效 */
	int nTVCount;								/*!< TV Out 个数*/
	HY_DVR_VOOUT struTv[MAX_TV_NUM];

}HY_DVR_VOOUT_CFG, *LPHY_DVR_VOOUT_CFG;

/*!
*  @struct	tagHY_DVR_DISPDEV_CFG
*  @brief	解码器显示设备信息
*/
typedef struct tagHY_DVR_DISPDEV_CFG
{
	int bValid; 								/*!< 0表示无效 1表示有效 */

	HY_DVR_VGAPARA_CFG struVGA;					/*!< VGA参数 */
	HY_DVR_VOOUT_CFG struTV;					/*!< TV参数 */

} HY_DVR_DISPDEV_CFG,  * LPHY_DVR_DISPDEV_CFG;

//////////////////////////////////////////////////////////////////////////////
/*!
*  @enum	eDeviceCapability
*  @brief	设备能力定义
*/
typedef enum eDeviceCapability
{
	//能力字段0
	eCapabilityLocalNetwork			= 0x00,							/*!< 本地网络								*/
	eCapabilityWirelessNetwork		= 0x01,							/*!< 无线网络								*/
	eCapabilityDHCP					= 0x02,							/*!< DHCP									*/
}eDeviceCapability;
//////////////////////////////////////////////////////////////////////////////
/*!
*  @struct	tagHY_DVR_PROBE_NET_INTERFACE
*  @brief	网络接口配置
*/
typedef struct tagHY_DVR_PROBE_NET_INTERFACE
{ 
	unsigned char	m_bytEnable;									/*!< 是否启用：0-不启用，1-启用，2-未找到	*/
	unsigned char	m_bytGetIPMode;									/*!< 获取地址：0-手动设定，1-DHCP获取		*/
	unsigned char	m_bytDevMac[DVR_MAX_MAC_NUM_LEN];				/*!< 设备MAC地址(Read)						*/
	unsigned char	m_bytDevIP[DVR_MAX_IP_STR_LEN];					/*!< 设备当前IP地址							*/
	unsigned char	m_bytDevMask[DVR_MAX_IP_STR_LEN];				/*!< 设备IP地址掩码							*/
	unsigned char	m_bytDevGateway[DVR_MAX_IP_STR_LEN];			/*!< 设备网关地址							*/
	unsigned long	m_dwNetworkState;								/*!< 网络状态:
																			0-连接成功,
																			1-未启用,
																			2-正在连接网络,
																			3-连接网络失败,继续连接,
																			4-正在获取IP,
																			5-获取IP失败,继续获取				*/
	unsigned long	m_dwReserve;									/*!< 保留数据								*/
}HY_DVR_PROBE_NET_INTERFACE, *LPHY_DVR_PROBE_NET_INTERFACE;
/*!
*  @struct	tagHY_DVR_PROBE_NET_CFG
*  @brief	探测网络配置
*/
typedef struct tagHY_DVR_PROBE_NET_CFG
{ 
	unsigned char	m_bytDevType;									/*!< 服务器类型(Read)						*/
	unsigned char	m_bytDevChan;									/*!< 设备通道个数(Read)						*/
	unsigned char	m_bytDevAutoReg;								/*!< 是否启用自动注册						*/
	unsigned char	m_bytDevRegInterval;							/*!< 设备注册间隔时间						*/
	HY_DVR_PROBE_NET_INTERFACE	m_cInterface[3];					/*!< 网络接口配置							*/
	unsigned char	m_bytDevManHost[DVR_MAX_IP_STR_LEN];			/*!< 设备管理主机地址						*/
	unsigned short	m_bytDevDetectPort;								/*!< 设备自动发现监听端口					*/
	unsigned short	m_wManHostPort;									/*!< 设备管理主机端口						*/
	unsigned short	m_wCmdPort;										/*!< 设备命令端口							*/
	unsigned short	m_wMediaPort;									/*!< 设备媒体端口							*/
	unsigned long	m_dwDeviceCapability[4];						/*!< 设备能力，位域详见eDeviceCapability定义*/
	unsigned long	m_dwReserve[3];									/*!< 保留数据								*/
}HY_DVR_PROBE_NET_CFG, *LPHY_DVR_PROBE_NET_CFG;
//////////////////////////////////////////////////////////////////////////////
/*!
*  @struct	tagHY_DVR_WLAN_CONNECTION
*  @brief	WIFI连接配置
*/
typedef struct tagHY_DVR_PROBE_WLAN_CONNECTION
{
	int		m_bEnable;												/*!< WIFI状态 0 不启用 1 启用, 2 网卡未找到*/
	int		m_bConnect;												/*!< 是否连接上：0表示未连接上 1表示连接上(只读) */
	char	m_szSSID[DVR_MAX_SSID_LEN];								/*!< 热点名称								*/
	char	m_szKey[DVR_MAX_WIFI_KEY_LEN];							/*!< 密码									*/
	char	m_szMacAddress[DVR_MAX_MAC_STR_LEN];					/*!< 热点MAC地址							*/
	int		m_nNetworkType;											/*!< 网络类型: 0表示Managed, 1表示Ad-hoc	*/
	int		m_nAuthMode;											/*!< 认证模式: 0-OPEN,1-SHARED,2-WEPAUTO,3-WPAPSK,4-WPA2PSK,5-WPANONE,6-WPA,7-WPA2*/
	int		m_nEncrypType;											/*!< 加密算法 0-NONE,1-WEP,2-TKIP,3-AES		*/
	unsigned long	m_dwReserve[3];									/*!< 保留数据								*/
} HY_DVR_PROBE_WLAN_CONNECTION, *LPHY_DVR_PROBE_WLAN_CONNECTION;
//////////////////////////////////////////////////////////////////////////////
/*!
*  @struct	tagHY_DVR_PROBE_WLAN_ACCESSPOINT
*  @brief	WIFI热点
*/
typedef struct tagHY_DVR_PROBE_WLAN_ACCESSPOINT
{
	char szSSID[DVR_MAX_SSID_LEN];									/*!< 热点名称 */
	char szMacAddress[DVR_MAX_MAC_STR_LEN];							/*!< 热点MAC地址 */
	int nSignal;													/*!< 热点信号强度 */
	int nAuthentication;											/*!< 认证模式 0-Open,1-Shared,2-WPAPSK, 3-WPA2PSK, 4-WPANONE(ad-hoc模式),5-WPA,6-WPA2 */
	int nEncrypType;												/*!< 加密模式  0表示NONE 1表示WEP 2表示TKIP 3表示AES */
	int nWirelessMode;												/*!< 1: legacy 11B only 2: legacy 11A only 3: legacy 11a/b/g mixed
																		 4: legacy 11G only 5: 11ABGN mixed    6: 11N only
																		 7: 11GN mixed      8: 11AN mixed      9: 11BGN mixed */
	unsigned long	m_dwReserve[3];									/*!< 保留数据								*/
} HY_DVR_PROBE_WLAN_ACCESSPOINT, *LPHY_DVR_PROBE_WLAN_ACCESSPOINT;

/*!
*  @struct	tagHY_DVR_PROBE_WLAN_ACCESSPOINT_CFG
*  @brief	WIFI热点配置
*/
typedef struct tagHY_DVR_PROBE_WLAN_ACCESSPOINT_CFG
{
	int		m_nNumber;												/*!< 有效热点个数							*/
	HY_DVR_PROBE_WLAN_ACCESSPOINT m_struAccessPoints[DVR_MAX_AP_NUM];/*!< WIFI热点								*/
	unsigned long	m_dwReserve[3];									/*!< 保留数据								*/
} HY_DVR_PROBE_WLAN_ACCESSPOINT_CFG, *LPHY_DVR_PROBE_WLAN_ACCESSPOINT_CFG;
//////////////////////////////////////////////////////////////////////////////

typedef struct
{
    int                    bValid;					    /* 本结构体是否有效，=0表示无效 */
    int                    m_usercount;               /* 引用计数，可能存在多个IE对应一个报警服务器。*/			
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

/*      命令ID......            */
typedef enum
{
    eCmdTypeBegin = 0,
    eCmdTypeConnect,		//连接设备命令
    eCmdTypeDisconnect,	//断开设备命令
    eCmdTypeAlarmSubscibe,	//客户端订阅报警消息
    eCmdTypeAlarmUnSubscribe,//客户端取消订阅报警消息
    eCmdTypeAlarm,//报警消息
    eCmdTypeClientHeart,//客户端向报警服务器发送的心跳包
    eCmdTypeDeviceHeart,//设备向报警服务器发送的心跳包
    eCmdTypeDeviceHeartReply,//报警服务器给设备的心跳应答
    eCmdTypeSubscribeServerInfo,	//subscribe alarmserver info to IPC
    eCmdTypeUnsubscribeServerInfo,	//unsubscribe alarmserver info to IPC
    eCmdTypeToAlarmServer = 0x040c, //发送给公网报警服务器的包  
    eCmdTypeEnd,
}CmdType;

/* change by linhh 20170526 start : 统一报警模块类型定义 到HieServer_Cfg.h 与 ws_status_def.h 中*/
/*  设备类型信息......      */
typedef enum
{
    edevicetypeBegin               = 0,
    edevicetypeIPC,			/* IPC  */
    edevicetypeNVR,			/* NVR */
    edevicetypeDVR,			/* DVR */
    edevicetypeEnd,
}edevicetype;

/* 报警类型*/
typedef enum   
{
    ealarmtypeBegin = 0,
    ealarmtypeMD,   //移动侦测报警
    ealarmtypeGPIO, //GPIO报警
    ealarmtypeVLOST,//视频丢失
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
    int	AlarmPort;//alarmport端口
};

struct SubscribeAlarmInfo
{
    CmdType	CommandID;//ID = 9
    int	AlarmPort;//alarmport端口
};

//设备发送过来的报警消息结构体
struct DeviceAlarmMessage
{
    CmdType CommandID;//命令ID=5
    AlarmType alarmtype;
    int AlarmIndex;
    int channel;
    int IsOn;//报警状态
    int time;
    char DeviceUID[48];//网络设备的UID
};

//!<报警发送信息.......
struct SendAlarmMessage
{
    AlarmType alarmtype;
    int AlarmIndex;
    int channel;
    int IsOn;//报警状态
    int time; //设备产生报警时的设备时间
    int user;//客户编号
    int CmdPort;//信令端口
    char LocalIP[20];//网络设备的IP
    char DeviceUID[48];//网络设备的UID
};

//!<连接命令参数......
struct Connect_info
{
    CmdType CommandID;	//命令ID=1
    char DeviceUID[48];//设备的UID
};

//!<断开命令参数......
struct Disconnect_info
{
    CmdType CommandID;	//命令ID=2
    char DeviceUID[48];//设备的UID
};

struct AlarmRequest
{
    CmdType CommandID;		//命令ID=3
    char dev_publicIP[16];			//设备的公网IP地址
    edevicetype devicetype;		//设备的类型
    AlarmType alarmtype;		//报警信息的类型
    int         channel;					//通道号
    int         user;		//客户编号
    int	    UserID;//客户端用户登录句柄，由设备分配
    char    DeviceUID[48];//网络设备的UID
    int	HttpPort;//设备的HttpPort
}; 

struct AlarmReject
{
    CmdType CommandID;		//命令ID=4
    char dev_publicIP[16];			//设备的公网IP地址
    edevicetype devicetype;		//设备的类型
    AlarmType alarmtype;		//报警信息的类型
    int channel;					//通道号
    int user;		//客户编号
    int	UserID;//客户端用户登录句柄，由设备分配
    char DeviceUID[48];//网络设备的UID
    int	HttpPort;//设备的HttpPort
}; 

//!<客户端发送的心跳包......
struct ClientHeartBeat
{
    CmdType CommandID;//命令ID=6
    int HeartBeatNum;
    int user;		//客户编号
};

//!<网络设备发送的心跳包......
struct HeartBeatPacket
{
    CmdType CommandID;//命令ID=7
    int HeartBeatNum;
    int	NetAbNormal;//通知报警服务器网络曾异常
    int	CmdPort;//网络设备信令端口
    int	HttpPort;//device Http Port
    char LocalIP[20];//网络设备IP
    char DeviceUID[48];//设备UID信息
};

struct HeartBeatPacketReply
{
    CmdType CommandID;//命令ID=8
    int		NetNormal;//网络恢复标志，如果为1表示网络恢复
    int		DisableServer;//停止报警请求标志,如果为1表示报警服务器不再关心这个设备的报警消息
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
    char DeviceUID[48];//网络设备的UID
    int NetNormal;
    int dwUserLoginHander;
};
/* change by linhh 20170526 end: 统一报警模块类型定义 到HieServer_Cfg.h 与 ws_status_def.h 中*/

#endif
