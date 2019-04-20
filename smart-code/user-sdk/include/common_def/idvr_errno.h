
/*!
 *\file		idvr_errno.h
 *\brief	�����붨��
 *\author	����
 *\date		2009/03/23

˵����
	idvr�����ģ�������ͳһ�滮������ģ�黮�֣�ÿ1000��������һ�����䡣
	���繫��������ķ�ΧΪ1-1000���û�����Ĵ����뷶ΧΪ
 */

#ifndef _INC_IDVR_ERRNO_H_
#define _INC_IDVR_ERRNO_H_

/*! ģ��ID���� */
#define IDVR_AVL_MODULE_ID	1000	//! ��������ģ��
#define IDVR_AVP_MODULE_ID	2000	//! ��������ģ��
#define IDVR_BAK_MODULE_ID	3000	//! �û�����ģ��
#define IDVR_BKD_MODULE_ID	4000	//! ��������ģ��
#define IDVR_DIP_MODULE_ID	5000	//! ��������ģ��
#define IDVR_DOP_MODULE_ID	6000	//! ��������ģ��
#define IDVR_MPU_MODULE_ID	7000	//! ��������ģ��
#define IDVR_OPL_MODULE_ID	8000	//! ��������ģ��
#define IDVR_PAR_MODULE_ID	9000	//! ��������ģ��
#define IDVR_PRW_MODULE_ID	10000	//! ��������ģ��
#define IDVR_PTZ_MODULE_ID	11000	//! ��������ģ��
#define IDVR_PUB_MODULE_ID	12000	//! ��������ģ��
#define IDVR_STR_MODULE_ID	13000	//! ��������ģ��
#define IDVR_SYS_MODULE_ID	14000	//! ��������ģ��
#define IDVR_USR_MODULE_ID	15000	//! ��������ģ��
#define IDVR_CIU_MODULE_ID	16000	//! CIUģ��


/*! ���������붨��(�䷶Χ1-999) */
#define IDVR_OK									0	/*! û�д��� */
#define IDVR_ERROR_PARAMETER					1	/*! �������ã������������ */
#define IDVR_ERROR_PARAMETER_INVALID_POINTER	2	/*! �������ã���Ч��ָ�� */
#define IDVR_ERROR_PARAMETER_OVERFLOW			3	/*! �������ã�������� */
#define IDVR_ERROR_CHANNELNO					4	/*! ͨ���Ŵ��� */
#define IDVR_ERROR_WEEKDAY						5	/*! ���ڴ��� */
#define IDVR_ERROR_DATE							6	/*! ���ڴ��� */
#define IDVR_ERROR_TIMESLICE					7	/*! ���õ�ʱ��γ�ͻ */
#define IDVR_ERROR_UNSUPPORT					8	/*! ��֧�ֵĵ��ã���Ҫ��δʵ�ֵĽӿڵ��� */
#define IDVR_ERROR_ORDER						9	/*! ��������˳����� */
#define IDVR_ERROR_CONFIGFILE					10	/*! ��д�����ļ����� */
#define IDVR_ERROR_NEEDMOREBUF					11	/*! ��Ҫ����Ļ����� */
#define IDVR_ERROR_ALLOC						12	/*! �ڴ����ʧ�� */
#define IDVR_ERROR_CREATETHREAD					13	/*! �����߳�ʧ�� */
#define IDVR_ERROR_INITIDVR						14	/*! ��ʼ��ϵͳSDKʧ�� */
#define IDVR_ERROR_HISDK						15	/*! ϵͳSDK���ýӿڷ���ʧ�� */
#define IDVR_ERROR_TIME							16	/*! ʱ����� */
#define IDVR_ERROR_FILE_NOT_EXSIT				17	/*! �ļ������� */
#define IDVR_ERROR_CLOSE_FILE					18	/*! �ر��ļ�ʧ�� */
#define IDVR_ERROR_INVALID_USB_DEVICE			19	/*! USB�豸������ */
#define IDVR_ERROR_OPEN_FILE					20	/*! flash���ļ�ʧ�� */
#define IDVR_ERROR_READ_FILE					21	/*! flash���ļ�ʧ�� */
#define IDVR_ERROR_WRITE_FILE					22	/*! flashд�ļ�ʧ�� */
#define IDVR_ERROR_USB_OPEN_FILE                23	/*! USB�豸���ļ�ʧ�� */
#define IDVR_ERROR_USB_READ_FILE                24	/*! USB�豸���ļ�ʧ�� */
#define IDVR_ERROR_USB_WRITE_FILE               25	/*! USB�豸д�ļ�ʧ�� */
#define IDVR_ERROR_INVALID_POINTER			26	/*! ��Ч��ָ�� */


/*! �ط�ģ������붨�� */
#define IDVR_AVP_NOT_OPEN						(IDVR_AVP_MODULE_ID + 1)	/*! û��ָ������Դ */
#define IDVR_AVP_ALREADY_OPEN					(IDVR_AVP_MODULE_ID + 2)	/*! ����Դ�Ѿ��� */
#define IDVR_AVP_GET_INSTANCE_FAIL				(IDVR_AVP_MODULE_ID + 3)	/*! ��ȡ������ʵ��ʧ�� */
#define IDVR_AVP_NO_ENOUGH_DEC					(IDVR_AVP_MODULE_ID + 4)	/*! �������������� */
#define IDVR_AVP_NOT_BIND_DEC					(IDVR_AVP_MODULE_ID + 5)	/*! û�а󶨽����� */
#define IDVR_AVP_UNSUPPORTED_IN_STATE			(IDVR_AVP_MODULE_ID + 6)	/*! ִ�е�ǰ״̬��֧�ֵĲ��� */
#define IDVR_AVP_STREAM_NO_DPMANAGER			(IDVR_AVP_MODULE_ID + 7)	/*! ������������ȡ����������ӿ�ʧ�� */
#define IDVR_AVP_STREAM_DPM_CREATE_FAIL			(IDVR_AVP_MODULE_ID + 8)	/*! ��������������������ʧ�� */
#define IDVR_AVP_STREAM_DPM_SETATTR_FAIL		(IDVR_AVP_MODULE_ID + 9)	/*! �������������õ���������ʧ�� */
#define IDVR_AVP_STREAM_DPM_ADDCH_FAIL			(IDVR_AVP_MODULE_ID + 10)	/*! ������������ӵ�����ͨ��ʧ�� */
#define IDVR_AVP_STREAM_DPM_SETDATATYPE_FAIL	(IDVR_AVP_MODULE_ID + 11)	/*! �����������������ݵ�������ʧ�� */
#define IDVR_AVP_STREAM_DPM_SETDIRECTION_FAIL	(IDVR_AVP_MODULE_ID + 12)	/*! �����������������ݵ�������ʧ�� */
#define IDVR_AVP_STREAM_DPM_SEEK_FAIL			(IDVR_AVP_MODULE_ID + 13)	/*! �����������������ݵ�����ʧ�� */
#define IDVR_AVP_STREAM_DPM_STARTPOP_FAIL		(IDVR_AVP_MODULE_ID + 14)	/*! �����������������ݵ�����ʧ�� */
#define IDVR_AVP_STREAM_DPM_STOPPOP_FAIL		(IDVR_AVP_MODULE_ID + 15)	/*! ����������ֹͣ���ݵ�����ʧ�� */
#define IDVR_AVP_STREAM_DPM_ADD_RECTYPE			(IDVR_AVP_MODULE_ID + 16)	/*! �������������ݵ��������¼������ */
#define IDVR_AVP_STREAM_DPM_DEL_RECTYPE			(IDVR_AVP_MODULE_ID + 17)	/*! �������������ݵ�����ɾ��¼������ */
#define IDVR_AVP_STREAM_NO_SNAPSHOT_MANAGER		(IDVR_AVP_MODULE_ID + 18)	/*! ����������û�п��չ�������� */
#define IDVR_AVP_STREAM_NO_ENCMASK				(IDVR_AVP_MODULE_ID + 19)	/*! ����������û���������ͨ�� */
#define IDVR_AVP_STREAM_BROWSE_NO_DATA			(IDVR_AVP_MODULE_ID + 20)	/*! ���������������û������ */
#define IDVR_AVP_STREAM_NOT_IN_DRAG				(IDVR_AVP_MODULE_ID + 21)	/*! ���������������Ϸ�ģʽ */
#define IDVR_AVP_STREAM_GETVOSHOWTIME_FAIL		(IDVR_AVP_MODULE_ID + 22)	/*! ������������ȡ����ʱ��ʧ�� */


/*! MPUģ������붨�� */
#define IDVR_MPU_AVP_FILEPLAYER_NOT_CREATED				(IDVR_MPU_MODULE_ID + 1)	/*! �ļ�������û�д��� */
#define IDVR_MPU_AVP_STREAMPLAYER_NOT_CREATED			(IDVR_MPU_MODULE_ID + 2)	/*! ��������û�д��� */
#define IDVR_MPU_AVP_INVALID_PLAYER_HANDLE				(IDVR_MPU_MODULE_ID + 3)	/*! ��Ч�Ĳ�������� */
#define IDVR_MPU_NO_CCONFIG_INSTANCE					(IDVR_MPU_MODULE_ID + 4)	/*! ��ȡ�����ļ�������ʵ��ʧ�� */
#define IDVR_MPU_STR_NO_SNAPSHOT_MANAGER_INSTANCE		(IDVR_MPU_MODULE_ID + 5)	/*! ��ȡ���չ�����ʵ��ʧ�� */
#define IDVR_MPU_STR_NO_DISKGROUP_MANAGER_INSTANCE		(IDVR_MPU_MODULE_ID + 6)	/*! ��ȡ���������ʵ��ʧ�� */
#define IDVR_MPU_STR_NO_DISK_MANAGER_INSTANCE			(IDVR_MPU_MODULE_ID + 7)	/*! ��ȡ���̹�����ʵ��ʧ�� */
#define IDVR_MPU_STR_NO_RECORD_MANAGER_INSTANCE			(IDVR_MPU_MODULE_ID + 8)	/*! ��ȡ¼�������ʵ��ʧ�� */
#define IDVR_MPU_AVL_NO_CHANNEL_MANAGER_INSTANCE		(IDVR_MPU_MODULE_ID + 9)	/*! ��ȡͨ��������ʵ��ʧ�� */
#define IDVR_MPU_PRW_NO_PREVIEW_MANAGER_INSTANCE		(IDVR_MPU_MODULE_ID + 10)	/*! ��ȡԤ��������ʵ��ʧ�� */
#define IDVR_MPU_SYS_NO_SYS_MANAGER_INSTANCE			(IDVR_MPU_MODULE_ID + 11)	/*! ��ȡϵͳ������ʵ��ʧ�� */
#define IDVR_MPU_SYS_NO_MAINTENANCE_MANAGER_INSTANCE	(IDVR_MPU_MODULE_ID + 12)	/*! ��ȡ�Զ�ά��������ʵ��ʧ�� */
#define IDVR_MPU_SYS_NO_UPDATE_MANAGER_INSTANCE			(IDVR_MPU_MODULE_ID + 13)	/*! ��ȡ����������ʵ��ʧ�� */
#define IDVR_MPU_PTZ_NO_MANAGER_INSTANCE				(IDVR_MPU_MODULE_ID + 14)	/*! ��ȡ��̨������ʵ��ʧ�� */
#define IDVR_MPU_OPL_NO_MANAGER_INSTANCE				(IDVR_MPU_MODULE_ID + 15)	/*! ��ȡ��־������ʵ��ʧ�� */
#define IDVR_MPU_USR_NO_MANAGER_INSTANCE				(IDVR_MPU_MODULE_ID + 16)	/*! ��ȡ�û�������ʵ��ʧ�� */
#define IDVR_MPU_USR_NO_CUSER_INSTANCE					(IDVR_MPU_MODULE_ID + 17)	/*! ��ȡ�û�ʵ��ʧ�� */
#define IDVR_MPU_BAK_NO_MANAGER_INSTANCE				(IDVR_MPU_MODULE_ID + 18)	/*! ��ȡ���ݹ�����ʵ��ʧ�� */
#define IDVR_MPU_NET_NO_MANAGER_INSTANCE				(IDVR_MPU_MODULE_ID + 19)	/*! ��ȡ�������������ʵ��ʧ�� */
#define IDVR_MPU_DDNS_NO_MANAGER_INSTANCE				(IDVR_MPU_MODULE_ID + 20)	/*! ��ȡDDNS������ʵ��ʧ�� */
#define IDVR_MPU_PPPOE_NO_MANAGER_INSTANCE				(IDVR_MPU_MODULE_ID + 21)	/*! ��ȡPPPoE������ʵ��ʧ�� */
#define IDVR_MPU_AMS_NO_MANAGER_INSTANCE				(IDVR_MPU_MODULE_ID + 22)	/*! ��ȡ����������������ʵ��ʧ�� */
#define IDVR_MPU_EML_NO_MANAGER_INSTANCE				(IDVR_MPU_MODULE_ID + 23)	/*! ��ȡEmail������ʵ��ʧ�� */
#define IDVR_MPU_NMS_NO_MANAGER_INSTANCE				(IDVR_MPU_MODULE_ID + 24)	/*! ��ȡ���������ʵ��ʧ�� */
#define IDVR_MPU_NTP_NO_MANAGER_INSTANCE				(IDVR_MPU_MODULE_ID + 25)	/*! ��ȡNTP����������ʵ��ʧ�� */
#define IDVR_MPU_DIP_NO_MANAGER_INSTANCE				(IDVR_MPU_MODULE_ID + 26)	/*! ��ȡ�������������ʵ��ʧ�� */
#define IDVR_MPU_DOP_NO_MANAGER_INSTANCE				(IDVR_MPU_MODULE_ID + 27)	/*! ��ȡ�������������ʵ��ʧ�� */
#define IDVR_MPU_TPC_NO_MANAGER_INSTANCE				(IDVR_MPU_MODULE_ID + 28)
#define IDVR_MPU_IN_SHUTDOWN_PROCESS					(IDVR_MPU_MODULE_ID + 29)	/*!�ѽ���ػ����� */
#define IDVR_MPU_EML_NOT_READY							(IDVR_MPU_MODULE_ID + 30)	/*!Email����û�����ú� */
#define IDVR_MPU_EML_NO_ADDRESSEE						(IDVR_MPU_MODULE_ID + 31)	/*!û��Email�ռ��� */
#define IDVR_MPU_UPNP_NO_MANAGER_INSTANCE				(IDVR_MPU_MODULE_ID + 32)	/*!��ȡupnp ������ʾ��ʧ�� */
//!! 2012 caoy�ṩ

/*! �û���������붨�� */
#define IDVR_USR_ERROR_USER_NOEXSIT				(IDVR_USR_MODULE_ID + 1)	/*! �û������� */
#define IDVR_USR_ERROR_USER_EXSIT_ALREADY		(IDVR_USR_MODULE_ID + 2)	/*! �û��Ѵ��� */
#define IDVR_USR_ERROR_INVALID_HANDLE			(IDVR_USR_MODULE_ID + 3)	/*! �û�����Ƿ� */
#define IDVR_USR_ERROR_USER_MAX_COUNT			(IDVR_USR_MODULE_ID + 4)	/*! �û����Ѵﵽ���ֵ */
#define IDVR_USR_ERROR_DB_OPEN_FAILED			(IDVR_USR_MODULE_ID + 5)	/*! �û����ݿ��ʧ�� */
#define IDVR_USR_ERROR_INVALID_USERNAME		(IDVR_USR_MODULE_ID + 6)	/*! ��Ч���û��� */

/*! �洢��������붨�� */
#define IDVR_STR_ERROR_DISK_INIT_FAILED             (IDVR_STR_MODULE_ID + 1)	/*! ��ʼ��Ӳ�̶���ʧ�� */
#define IDVR_STR_ERROR_DISK_INFO_FAILED             (IDVR_STR_MODULE_ID + 2)	/*! ��ȡ������Ϣʧ�� */
#define IDVR_STR_ERROR_DISK_THREAD_FAILED           (IDVR_STR_MODULE_ID + 3)	/*! �����߳�ʧ�� */
#define IDVR_STR_ERROR_PARTITION_NOFIND             (IDVR_STR_MODULE_ID + 4)	/*! û���ҵ��÷��� */
#define IDVR_STR_ERROR_PARTITION_NOUNMOUNT          (IDVR_STR_MODULE_ID + 5)	/*! ����δ��ж�أ��޷���ʽ�� */
#define IDVR_STR_ERROR_DISK_NOFIND                  (IDVR_STR_MODULE_ID + 6)	/*! û���ҵ���Ӳ�� */
#define IDVR_STR_ERROR_PARTITION_NUMERROR           (IDVR_STR_MODULE_ID + 7)	/*! �����������ķ������� */
#define IDVR_STR_ERROR_SYS_PARTITION                (IDVR_STR_MODULE_ID + 8)	/*! ϵͳ���������޷�ɾ�� */
#define IDVR_STR_ERROR_DISK_UMOUNT_BUSY             (IDVR_STR_MODULE_ID + 9)	/*!  �з�������ʹ�ã��޷�ж�� */
#define IDVR_STR_ERROR_GROUP_EXIT                   (IDVR_STR_MODULE_ID + 10)	/*!  �Ѿ����ڵķ��� */
#define IDVR_STR_ERROR_SYS_PARTITION_ADD            (IDVR_STR_MODULE_ID + 11)	/*!  ϵͳ���������޷���ӵ����� */
#define IDVR_STR_ERROR_NOTSUPPORT					(IDVR_STR_MODULE_ID + 12)	/*!  ϵͳ��֧�ָ����� */
#define IDVR_STR_ERROR_ALLFULL						(IDVR_STR_MODULE_ID + 13)	/*!  ���з��������޷�ץͼ */
#define IDVR_STR_ERROR_NOTPARTITION					(IDVR_STR_MODULE_ID + 14)	/*!  û�з��������û�й��أ��޷�ץͼ */

/*! ������������붨�� */
#define IDVR_PAR_ERROR_NOSECTION 					(IDVR_PAR_MODULE_ID + 1)	//! δ�ҵ�section
#define IDVR_PAR_ERROR_NOKEY 						(IDVR_PAR_MODULE_ID + 2)	//! δ�ҵ�key
#define IDVR_PAR_ERROR_ERANGE						(IDVR_PAR_MODULE_ID + 3)	//! ���Ϸ�����ת��
#define IDVR_PAR_ERROR_GETINSTANCE					(IDVR_PAR_MODULE_ID + 4)	//! ��ȡ��������ʵ��ʧ��
#define IDVR_PAR_ERROR_INVALID_FORMAT				(IDVR_PAR_MODULE_ID + 5)	//! �Ƿ������ļ���ʽ
#define IDVR_PAR_ERROR_EMPTY_FILE                   (IDVR_PAR_MODULE_ID + 6)	//! �����ļ�Ϊ�ջ���ֻ�����հ��ַ�

/*! ������־�����붨��*/
#define IDVR_OPL_ERROR_DB_OPEN_FAILED				(IDVR_OPL_MODULE_ID + 1)	/* ��־���ݿ��ʧ�� */

/*! ���ݴ����붨�� */
#define IDVR_BAK_ERROR_BACKUP_RUNNING				(IDVR_BAK_MODULE_ID + 1)	/* �����Ѿ����� */

/*! ��̨���ƴ����붨�� */
#define IDVR_PTZ_ERROR_LOAD_INTERNAL_PROTOCOL		(IDVR_PTZ_MODULE_ID + 1)	/*�����ڲ�Э��ʧ�� */
#define IDVR_PTZ_ERROR_LOAD_EXTERNAL_PROTOCOL		(IDVR_PTZ_MODULE_ID + 2)	/*�����ⲿЭ��ʧ�� */
#define IDVR_PTZ_ERROR_PROTOCOL_NO_EXIST			(IDVR_PTZ_MODULE_ID + 3)	/*Э�鲻���� */
#define IDVR_PTZ_ERROR_PROTOCOL_ALREADY_EXIST		(IDVR_PTZ_MODULE_ID + 4)	/*Э���Ѵ��� */
#define IDVR_PTZ_ERROR_PROTOCOL_INVALID_FORMAT		(IDVR_PTZ_MODULE_ID + 5)	/*�Ƿ��ĸ�ʽ */
#define IDVR_PTZ_ERROR_PROTOCOL_IS_USED				(IDVR_PTZ_MODULE_ID + 6)	/*Э�����ڱ�ʹ�� */
#define IDVR_PTZ_ERROR_PROTOCOL_TOOMUCH				(IDVR_PTZ_MODULE_ID + 7)	/*Э��������������� */

/*!ϵͳ����ģ������붨��*/
#define IDVR_SYS_UPDATE_ERROR_SIZE                   IDVR_SYS_MODULE_ID + 1	/*!<���������� */
#define IDVR_SYS_UPDATE_ERROR_VERSION                IDVR_SYS_MODULE_ID + 2	/*!<�汾��Ϣ���� */
#define IDVR_SYS_UPDATE_NO_FILE		                 IDVR_SYS_MODULE_ID + 3	/*!<û������ļ� */
#define IDVR_SYS_UPDATE_ERR_FILE		                 IDVR_SYS_MODULE_ID + 4	/*!<���������� */


/*!PRWģ������붨��*/
#define IDVR_PRW_ERROR_POLLLIST_NULL					IDVR_PRW_MODULE_ID + 1	/*!<��Ѳ����Ϊ�� */
#define IDVR_PRW_ERROR_IS_ALERTING						IDVR_PRW_MODULE_ID + 2	/*!<����������Ļ��ʾ,������Ѳ */
#define IDVR_PRW_ERROR_IS_POLLING						IDVR_PRW_MODULE_ID +3	/*!<������Ѳ�� */


/*!CIUģ������붨��*/
#define IDVR_CIU_UNSUPPORTED_MAJORTYPE			(IDVR_CIU_MODULE_ID + 1)	/*!<��֧�ֵ��������� */
#define IDVR_CIU_UNSUPPORTED_MINORTYPE			(IDVR_CIU_MODULE_ID + 2)	/*!<��֧�ֵĴ������� */
#define IDVR_CIU_STRUCT_UNVALID						(IDVR_CIU_MODULE_ID + 3)	/*!<�ṹ����Ч */
#define IDVR_CIU_STRUCT_READONLY					(IDVR_CIU_MODULE_ID + 4)	/*!<�ṹ����ֻ���� */
#define IDVR_CIU_BUF_SMALL							(IDVR_CIU_MODULE_ID + 5)	/*!<������̫С */
#define IDVR_CIU_STRUCT_UNSUPPORTED				(IDVR_CIU_MODULE_ID + 6)	/*!<ϵͳ��֧�ָýṹ������û��ȡ */
#define IDVR_CIU_NO_RIGHT							(IDVR_CIU_MODULE_ID + 7)	/*!<û��Ȩ�� */
#define IDVR_CIU_PARAM_OVERFLOW					(IDVR_CIU_MODULE_ID + 8)	/*!<������� */
#define IDVR_CIU_CALLSDK_FAIL						(IDVR_CIU_MODULE_ID + 9)	/*!<����SDKʧ�� */


#endif							/* _INC_IDVR_ERRNO_H_ */
