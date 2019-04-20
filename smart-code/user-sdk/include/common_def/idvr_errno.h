
/*!
 *\file		idvr_errno.h
 *\brief	错误码定义
 *\author	林云
 *\date		2009/03/23

说明：
	idvr软件各模块错误码统一规划，按照模块划分，每1000个错误码一个区间。
	比如公共错误码的范围为1-1000，用户管理的错误码范围为
 */

#ifndef _INC_IDVR_ERRNO_H_
#define _INC_IDVR_ERRNO_H_

/*! 模块ID定义 */
#define IDVR_AVL_MODULE_ID	1000	//! 参数管理模块
#define IDVR_AVP_MODULE_ID	2000	//! 参数管理模块
#define IDVR_BAK_MODULE_ID	3000	//! 用户管理模块
#define IDVR_BKD_MODULE_ID	4000	//! 参数管理模块
#define IDVR_DIP_MODULE_ID	5000	//! 参数管理模块
#define IDVR_DOP_MODULE_ID	6000	//! 参数管理模块
#define IDVR_MPU_MODULE_ID	7000	//! 参数管理模块
#define IDVR_OPL_MODULE_ID	8000	//! 参数管理模块
#define IDVR_PAR_MODULE_ID	9000	//! 参数管理模块
#define IDVR_PRW_MODULE_ID	10000	//! 参数管理模块
#define IDVR_PTZ_MODULE_ID	11000	//! 参数管理模块
#define IDVR_PUB_MODULE_ID	12000	//! 参数管理模块
#define IDVR_STR_MODULE_ID	13000	//! 参数管理模块
#define IDVR_SYS_MODULE_ID	14000	//! 参数管理模块
#define IDVR_USR_MODULE_ID	15000	//! 参数管理模块
#define IDVR_CIU_MODULE_ID	16000	//! CIU模块


/*! 公共错误码定义(其范围1-999) */
#define IDVR_OK									0	/*! 没有错误 */
#define IDVR_ERROR_PARAMETER					1	/*! 函数调用，输入参数错误 */
#define IDVR_ERROR_PARAMETER_INVALID_POINTER	2	/*! 函数调用，无效的指针 */
#define IDVR_ERROR_PARAMETER_OVERFLOW			3	/*! 函数调用，参数溢出 */
#define IDVR_ERROR_CHANNELNO					4	/*! 通道号错误 */
#define IDVR_ERROR_WEEKDAY						5	/*! 星期错误 */
#define IDVR_ERROR_DATE							6	/*! 日期错误 */
#define IDVR_ERROR_TIMESLICE					7	/*! 设置的时间段冲突 */
#define IDVR_ERROR_UNSUPPORT					8	/*! 不支持的调用，主要是未实现的接口调用 */
#define IDVR_ERROR_ORDER						9	/*! 函数调用顺序出错 */
#define IDVR_ERROR_CONFIGFILE					10	/*! 读写配置文件出错 */
#define IDVR_ERROR_NEEDMOREBUF					11	/*! 需要更大的缓冲区 */
#define IDVR_ERROR_ALLOC						12	/*! 内存分配失败 */
#define IDVR_ERROR_CREATETHREAD					13	/*! 创建线程失败 */
#define IDVR_ERROR_INITIDVR						14	/*! 初始化系统SDK失败 */
#define IDVR_ERROR_HISDK						15	/*! 系统SDK调用接口返回失败 */
#define IDVR_ERROR_TIME							16	/*! 时间错误 */
#define IDVR_ERROR_FILE_NOT_EXSIT				17	/*! 文件不存在 */
#define IDVR_ERROR_CLOSE_FILE					18	/*! 关闭文件失败 */
#define IDVR_ERROR_INVALID_USB_DEVICE			19	/*! USB设备不存在 */
#define IDVR_ERROR_OPEN_FILE					20	/*! flash打开文件失败 */
#define IDVR_ERROR_READ_FILE					21	/*! flash读文件失败 */
#define IDVR_ERROR_WRITE_FILE					22	/*! flash写文件失败 */
#define IDVR_ERROR_USB_OPEN_FILE                23	/*! USB设备打开文件失败 */
#define IDVR_ERROR_USB_READ_FILE                24	/*! USB设备读文件失败 */
#define IDVR_ERROR_USB_WRITE_FILE               25	/*! USB设备写文件失败 */
#define IDVR_ERROR_INVALID_POINTER			26	/*! 无效的指针 */


/*! 回放模块错误码定义 */
#define IDVR_AVP_NOT_OPEN						(IDVR_AVP_MODULE_ID + 1)	/*! 没有指定播放源 */
#define IDVR_AVP_ALREADY_OPEN					(IDVR_AVP_MODULE_ID + 2)	/*! 播放源已经打开 */
#define IDVR_AVP_GET_INSTANCE_FAIL				(IDVR_AVP_MODULE_ID + 3)	/*! 获取解码器实例失败 */
#define IDVR_AVP_NO_ENOUGH_DEC					(IDVR_AVP_MODULE_ID + 4)	/*! 解码器数量不足 */
#define IDVR_AVP_NOT_BIND_DEC					(IDVR_AVP_MODULE_ID + 5)	/*! 没有绑定解码器 */
#define IDVR_AVP_UNSUPPORTED_IN_STATE			(IDVR_AVP_MODULE_ID + 6)	/*! 执行当前状态不支持的操作 */
#define IDVR_AVP_STREAM_NO_DPMANAGER			(IDVR_AVP_MODULE_ID + 7)	/*! 流播放器，获取弹出器管理接口失败 */
#define IDVR_AVP_STREAM_DPM_CREATE_FAIL			(IDVR_AVP_MODULE_ID + 8)	/*! 流播放器，创建弹出器失败 */
#define IDVR_AVP_STREAM_DPM_SETATTR_FAIL		(IDVR_AVP_MODULE_ID + 9)	/*! 流播放器，设置弹出器属性失败 */
#define IDVR_AVP_STREAM_DPM_ADDCH_FAIL			(IDVR_AVP_MODULE_ID + 10)	/*! 流播放器，添加弹出器通道失败 */
#define IDVR_AVP_STREAM_DPM_SETDATATYPE_FAIL	(IDVR_AVP_MODULE_ID + 11)	/*! 流播放器，设置数据弹出类型失败 */
#define IDVR_AVP_STREAM_DPM_SETDIRECTION_FAIL	(IDVR_AVP_MODULE_ID + 12)	/*! 流播放器，设置数据弹出方向失败 */
#define IDVR_AVP_STREAM_DPM_SEEK_FAIL			(IDVR_AVP_MODULE_ID + 13)	/*! 流播放器，设置数据弹出点失败 */
#define IDVR_AVP_STREAM_DPM_STARTPOP_FAIL		(IDVR_AVP_MODULE_ID + 14)	/*! 流播放器，启动数据弹出器失败 */
#define IDVR_AVP_STREAM_DPM_STOPPOP_FAIL		(IDVR_AVP_MODULE_ID + 15)	/*! 流播放器，停止数据弹出器失败 */
#define IDVR_AVP_STREAM_DPM_ADD_RECTYPE			(IDVR_AVP_MODULE_ID + 16)	/*! 流播放器，数据弹出器添加录像类型 */
#define IDVR_AVP_STREAM_DPM_DEL_RECTYPE			(IDVR_AVP_MODULE_ID + 17)	/*! 流播放器，数据弹出器删除录像类型 */
#define IDVR_AVP_STREAM_NO_SNAPSHOT_MANAGER		(IDVR_AVP_MODULE_ID + 18)	/*! 流播放器，没有快照管理器句柄 */
#define IDVR_AVP_STREAM_NO_ENCMASK				(IDVR_AVP_MODULE_ID + 19)	/*! 流播放器，没有输入编码通道 */
#define IDVR_AVP_STREAM_BROWSE_NO_DATA			(IDVR_AVP_MODULE_ID + 20)	/*! 流播放器，浏览点没有数据 */
#define IDVR_AVP_STREAM_NOT_IN_DRAG				(IDVR_AVP_MODULE_ID + 21)	/*! 流播放器，不是拖放模式 */
#define IDVR_AVP_STREAM_GETVOSHOWTIME_FAIL		(IDVR_AVP_MODULE_ID + 22)	/*! 流播放器，获取播放时间失败 */


/*! MPU模块错误码定义 */
#define IDVR_MPU_AVP_FILEPLAYER_NOT_CREATED				(IDVR_MPU_MODULE_ID + 1)	/*! 文件播放器没有创建 */
#define IDVR_MPU_AVP_STREAMPLAYER_NOT_CREATED			(IDVR_MPU_MODULE_ID + 2)	/*! 流播放器没有创建 */
#define IDVR_MPU_AVP_INVALID_PLAYER_HANDLE				(IDVR_MPU_MODULE_ID + 3)	/*! 无效的播放器句柄 */
#define IDVR_MPU_NO_CCONFIG_INSTANCE					(IDVR_MPU_MODULE_ID + 4)	/*! 获取配置文件管理器实例失败 */
#define IDVR_MPU_STR_NO_SNAPSHOT_MANAGER_INSTANCE		(IDVR_MPU_MODULE_ID + 5)	/*! 获取快照管理器实例失败 */
#define IDVR_MPU_STR_NO_DISKGROUP_MANAGER_INSTANCE		(IDVR_MPU_MODULE_ID + 6)	/*! 获取盘组管理器实例失败 */
#define IDVR_MPU_STR_NO_DISK_MANAGER_INSTANCE			(IDVR_MPU_MODULE_ID + 7)	/*! 获取磁盘管理器实例失败 */
#define IDVR_MPU_STR_NO_RECORD_MANAGER_INSTANCE			(IDVR_MPU_MODULE_ID + 8)	/*! 获取录像管理器实例失败 */
#define IDVR_MPU_AVL_NO_CHANNEL_MANAGER_INSTANCE		(IDVR_MPU_MODULE_ID + 9)	/*! 获取通道管理器实例失败 */
#define IDVR_MPU_PRW_NO_PREVIEW_MANAGER_INSTANCE		(IDVR_MPU_MODULE_ID + 10)	/*! 获取预览管理器实例失败 */
#define IDVR_MPU_SYS_NO_SYS_MANAGER_INSTANCE			(IDVR_MPU_MODULE_ID + 11)	/*! 获取系统管理器实例失败 */
#define IDVR_MPU_SYS_NO_MAINTENANCE_MANAGER_INSTANCE	(IDVR_MPU_MODULE_ID + 12)	/*! 获取自动维护管理器实例失败 */
#define IDVR_MPU_SYS_NO_UPDATE_MANAGER_INSTANCE			(IDVR_MPU_MODULE_ID + 13)	/*! 获取升级管理器实例失败 */
#define IDVR_MPU_PTZ_NO_MANAGER_INSTANCE				(IDVR_MPU_MODULE_ID + 14)	/*! 获取云台管理器实例失败 */
#define IDVR_MPU_OPL_NO_MANAGER_INSTANCE				(IDVR_MPU_MODULE_ID + 15)	/*! 获取日志管理器实例失败 */
#define IDVR_MPU_USR_NO_MANAGER_INSTANCE				(IDVR_MPU_MODULE_ID + 16)	/*! 获取用户管理器实例失败 */
#define IDVR_MPU_USR_NO_CUSER_INSTANCE					(IDVR_MPU_MODULE_ID + 17)	/*! 获取用户实例失败 */
#define IDVR_MPU_BAK_NO_MANAGER_INSTANCE				(IDVR_MPU_MODULE_ID + 18)	/*! 获取备份管理器实例失败 */
#define IDVR_MPU_NET_NO_MANAGER_INSTANCE				(IDVR_MPU_MODULE_ID + 19)	/*! 获取本地网络管理器实例失败 */
#define IDVR_MPU_DDNS_NO_MANAGER_INSTANCE				(IDVR_MPU_MODULE_ID + 20)	/*! 获取DDNS管理器实例失败 */
#define IDVR_MPU_PPPOE_NO_MANAGER_INSTANCE				(IDVR_MPU_MODULE_ID + 21)	/*! 获取PPPoE管理器实例失败 */
#define IDVR_MPU_AMS_NO_MANAGER_INSTANCE				(IDVR_MPU_MODULE_ID + 22)	/*! 获取报警服务器管理器实例失败 */
#define IDVR_MPU_EML_NO_MANAGER_INSTANCE				(IDVR_MPU_MODULE_ID + 23)	/*! 获取Email管理器实例失败 */
#define IDVR_MPU_NMS_NO_MANAGER_INSTANCE				(IDVR_MPU_MODULE_ID + 24)	/*! 获取管理服务器实例失败 */
#define IDVR_MPU_NTP_NO_MANAGER_INSTANCE				(IDVR_MPU_MODULE_ID + 25)	/*! 获取NTP服务器管理实例失败 */
#define IDVR_MPU_DIP_NO_MANAGER_INSTANCE				(IDVR_MPU_MODULE_ID + 26)	/*! 获取报警输入管理器实例失败 */
#define IDVR_MPU_DOP_NO_MANAGER_INSTANCE				(IDVR_MPU_MODULE_ID + 27)	/*! 获取报警输出管理器实例失败 */
#define IDVR_MPU_TPC_NO_MANAGER_INSTANCE				(IDVR_MPU_MODULE_ID + 28)
#define IDVR_MPU_IN_SHUTDOWN_PROCESS					(IDVR_MPU_MODULE_ID + 29)	/*!已进入关机过程 */
#define IDVR_MPU_EML_NOT_READY							(IDVR_MPU_MODULE_ID + 30)	/*!Email功能没有配置好 */
#define IDVR_MPU_EML_NO_ADDRESSEE						(IDVR_MPU_MODULE_ID + 31)	/*!没有Email收件人 */
#define IDVR_MPU_UPNP_NO_MANAGER_INSTANCE				(IDVR_MPU_MODULE_ID + 32)	/*!获取upnp 管理器示例失败 */
//!! 2012 caoy提供

/*! 用户管理错误码定义 */
#define IDVR_USR_ERROR_USER_NOEXSIT				(IDVR_USR_MODULE_ID + 1)	/*! 用户不存在 */
#define IDVR_USR_ERROR_USER_EXSIT_ALREADY		(IDVR_USR_MODULE_ID + 2)	/*! 用户已存在 */
#define IDVR_USR_ERROR_INVALID_HANDLE			(IDVR_USR_MODULE_ID + 3)	/*! 用户句柄非法 */
#define IDVR_USR_ERROR_USER_MAX_COUNT			(IDVR_USR_MODULE_ID + 4)	/*! 用户数已达到最大值 */
#define IDVR_USR_ERROR_DB_OPEN_FAILED			(IDVR_USR_MODULE_ID + 5)	/*! 用户数据库打开失败 */
#define IDVR_USR_ERROR_INVALID_USERNAME		(IDVR_USR_MODULE_ID + 6)	/*! 无效的用户名 */

/*! 存储管理错误码定义 */
#define IDVR_STR_ERROR_DISK_INIT_FAILED             (IDVR_STR_MODULE_ID + 1)	/*! 初始化硬盘对象失败 */
#define IDVR_STR_ERROR_DISK_INFO_FAILED             (IDVR_STR_MODULE_ID + 2)	/*! 获取磁盘信息失败 */
#define IDVR_STR_ERROR_DISK_THREAD_FAILED           (IDVR_STR_MODULE_ID + 3)	/*! 创建线程失败 */
#define IDVR_STR_ERROR_PARTITION_NOFIND             (IDVR_STR_MODULE_ID + 4)	/*! 没有找到该分区 */
#define IDVR_STR_ERROR_PARTITION_NOUNMOUNT          (IDVR_STR_MODULE_ID + 5)	/*! 分区未被卸载，无法格式化 */
#define IDVR_STR_ERROR_DISK_NOFIND                  (IDVR_STR_MODULE_ID + 6)	/*! 没有找到该硬盘 */
#define IDVR_STR_ERROR_PARTITION_NUMERROR           (IDVR_STR_MODULE_ID + 7)	/*! 超过最大允许的分区数量 */
#define IDVR_STR_ERROR_SYS_PARTITION                (IDVR_STR_MODULE_ID + 8)	/*! 系统保留分区无法删除 */
#define IDVR_STR_ERROR_DISK_UMOUNT_BUSY             (IDVR_STR_MODULE_ID + 9)	/*!  有分区正在使用，无法卸载 */
#define IDVR_STR_ERROR_GROUP_EXIT                   (IDVR_STR_MODULE_ID + 10)	/*!  已经存在的分组 */
#define IDVR_STR_ERROR_SYS_PARTITION_ADD            (IDVR_STR_MODULE_ID + 11)	/*!  系统保留分区无法添加到盘组 */
#define IDVR_STR_ERROR_NOTSUPPORT					(IDVR_STR_MODULE_ID + 12)	/*!  系统不支持该盘组 */
#define IDVR_STR_ERROR_ALLFULL						(IDVR_STR_MODULE_ID + 13)	/*!  所有分区满，无法抓图 */
#define IDVR_STR_ERROR_NOTPARTITION					(IDVR_STR_MODULE_ID + 14)	/*!  没有分区或分区没有挂载，无法抓图 */

/*! 参数管理错误码定义 */
#define IDVR_PAR_ERROR_NOSECTION 					(IDVR_PAR_MODULE_ID + 1)	//! 未找到section
#define IDVR_PAR_ERROR_NOKEY 						(IDVR_PAR_MODULE_ID + 2)	//! 未找到key
#define IDVR_PAR_ERROR_ERANGE						(IDVR_PAR_MODULE_ID + 3)	//! 不合法数字转换
#define IDVR_PAR_ERROR_GETINSTANCE					(IDVR_PAR_MODULE_ID + 4)	//! 获取参数管理实例失败
#define IDVR_PAR_ERROR_INVALID_FORMAT				(IDVR_PAR_MODULE_ID + 5)	//! 非法配置文件格式
#define IDVR_PAR_ERROR_EMPTY_FILE                   (IDVR_PAR_MODULE_ID + 6)	//! 配置文件为空或者只包含空白字符

/*! 操作日志错误码定义*/
#define IDVR_OPL_ERROR_DB_OPEN_FAILED				(IDVR_OPL_MODULE_ID + 1)	/* 日志数据库打开失败 */

/*! 备份错误码定义 */
#define IDVR_BAK_ERROR_BACKUP_RUNNING				(IDVR_BAK_MODULE_ID + 1)	/* 备份已经启动 */

/*! 云台控制错误码定义 */
#define IDVR_PTZ_ERROR_LOAD_INTERNAL_PROTOCOL		(IDVR_PTZ_MODULE_ID + 1)	/*加载内部协议失败 */
#define IDVR_PTZ_ERROR_LOAD_EXTERNAL_PROTOCOL		(IDVR_PTZ_MODULE_ID + 2)	/*加载外部协议失败 */
#define IDVR_PTZ_ERROR_PROTOCOL_NO_EXIST			(IDVR_PTZ_MODULE_ID + 3)	/*协议不存在 */
#define IDVR_PTZ_ERROR_PROTOCOL_ALREADY_EXIST		(IDVR_PTZ_MODULE_ID + 4)	/*协议已存在 */
#define IDVR_PTZ_ERROR_PROTOCOL_INVALID_FORMAT		(IDVR_PTZ_MODULE_ID + 5)	/*非法的格式 */
#define IDVR_PTZ_ERROR_PROTOCOL_IS_USED				(IDVR_PTZ_MODULE_ID + 6)	/*协议正在被使用 */
#define IDVR_PTZ_ERROR_PROTOCOL_TOOMUCH				(IDVR_PTZ_MODULE_ID + 7)	/*协议个数超过限制数 */

/*!系统管理模块错误码定义*/
#define IDVR_SYS_UPDATE_ERROR_SIZE                   IDVR_SYS_MODULE_ID + 1	/*!<升级包过大 */
#define IDVR_SYS_UPDATE_ERROR_VERSION                IDVR_SYS_MODULE_ID + 2	/*!<版本信息不对 */
#define IDVR_SYS_UPDATE_NO_FILE		                 IDVR_SYS_MODULE_ID + 3	/*!<没有这个文件 */
#define IDVR_SYS_UPDATE_ERR_FILE		                 IDVR_SYS_MODULE_ID + 4	/*!<升级包错误 */


/*!PRW模块错误码定义*/
#define IDVR_PRW_ERROR_POLLLIST_NULL					IDVR_PRW_MODULE_ID + 1	/*!<轮巡序列为空 */
#define IDVR_PRW_ERROR_IS_ALERTING						IDVR_PRW_MODULE_ID + 2	/*!<正在联动屏幕提示,不能轮巡 */
#define IDVR_PRW_ERROR_IS_POLLING						IDVR_PRW_MODULE_ID +3	/*!<正在轮巡中 */


/*!CIU模块错误码定义*/
#define IDVR_CIU_UNSUPPORTED_MAJORTYPE			(IDVR_CIU_MODULE_ID + 1)	/*!<不支持的主命令字 */
#define IDVR_CIU_UNSUPPORTED_MINORTYPE			(IDVR_CIU_MODULE_ID + 2)	/*!<不支持的次命令字 */
#define IDVR_CIU_STRUCT_UNVALID						(IDVR_CIU_MODULE_ID + 3)	/*!<结构体无效 */
#define IDVR_CIU_STRUCT_READONLY					(IDVR_CIU_MODULE_ID + 4)	/*!<结构体是只读的 */
#define IDVR_CIU_BUF_SMALL							(IDVR_CIU_MODULE_ID + 5)	/*!<缓冲区太小 */
#define IDVR_CIU_STRUCT_UNSUPPORTED				(IDVR_CIU_MODULE_ID + 6)	/*!<系统不支持该结构体的设置或读取 */
#define IDVR_CIU_NO_RIGHT							(IDVR_CIU_MODULE_ID + 7)	/*!<没有权限 */
#define IDVR_CIU_PARAM_OVERFLOW					(IDVR_CIU_MODULE_ID + 8)	/*!<参数溢出 */
#define IDVR_CIU_CALLSDK_FAIL						(IDVR_CIU_MODULE_ID + 9)	/*!<调用SDK失败 */


#endif							/* _INC_IDVR_ERRNO_H_ */
