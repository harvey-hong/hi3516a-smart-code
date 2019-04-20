#ifndef _WS_DISK_MANAGE_DEF_H_
#define _WS_DISK_MANAGE_DEF_H_

#include "ws_common.h"
#include "ws_comm_type.h"
#include "ws_comm_sys.h" //add by lmw 2016 9 22
#define WS_ATA_DEVICE_PORT_INFO_PTAH "/sys/class/ata_port" 
#define WS_DATA_IMPORT_DISK_SERIAL_N0 "/config/date_import_" 

//using namespace ws_soft; //del by qqy, at 2017-01-10 18:57:25 ���IPC���ܱ���ͨ��
using namespace ws_utility;//add by lmw 2016 9 22

#ifdef __cplusplus
extern "C" {
namespace ws_soft
{
#endif

typedef enum
{
    WS_USB_DEV_UNKNOW,
    WS_USB_FLASH_DISK,  //U ��
    WS_USB_CD_WRITER,   //��¼��
    WS_SATA_CD_WRITER,  //sata��¼��
} ws_usb_dev_type;

typedef struct
{
    WS_CHAR dev_name[16];       //�豸��(usb disk ���� DVD/CD)

    WS_CHAR vendor_name[16];    //��������
    WS_CHAR product_name[48];   //��Ʒ��
    WS_CHAR scsi_name[16];
    ws_usb_dev_type type;

    WS_S32  part_num;       //������Ŀ
    WS_CHAR part_mount_dir[ws_utility::WS_NVR_MAX_USB_PART_NUM][16];    //�������ص�
    WS_S32 valid_space_MB[ws_utility::WS_NVR_MAX_USB_PART_NUM]; //ÿ�������Ŀ��ÿռ�
    WS_S32 total_space_MB[ws_utility::WS_NVR_MAX_USB_PART_NUM]; //ÿ���������ܿռ�
} ws_usb_disk_info;

// ��Ӳ�̼��ӿڻ��ʽ���� ��������޸�Ӳ��״̬�ͷ���״̬
typedef enum
{
    WS_HARD_DISK_STATE_UNKNOW,			//
    WS_HARD_DISK_NEED_FORMAT,   		    // Ӳ�̸�ʽ���г������쳣����: ������ʹ�� ȷ��OK
    WS_HARD_DISK_ABNORMAL,      		    // Ӳ�̷�������ʧ��ʱ���߹��صķ�������������: ȷ��OK
    WS_HARD_DISK_NORMAL,        		//����
    WS_HARD_DISK_FORMATING,     		// Ӳ��׼��������ʽ�����߸�ʽ�������ø�״̬
    WS_HARD_DISK_FORMAT_FAILED,     		//��ʽ��ʧ��
    WS_HARD_DISK_VOLUME_ERROR,          //Ӳ����ɸ�ʽ����������Ϣ����
    WS_HARD_DISK_ERROR,                             // ��Ӳ�̷����������Ӳ����С��������Ӳ���з�������Լ����
    WS_HARD_DISK_CHECKING,				//����� Ϊ���ڼ��ʱ������������Ҫ�رռ��
    WS_HARD_DISK_LOST,	         
    WS_HARD_DISK_PART_INFO_LOST,		//Ӳ�̷�����Ϣ��ʧ
    WS_HARD_DISK_NO_SPACE,				// HDD no space
} ws_hard_disk_state;

typedef enum
{
    WS_HARD_DISK_PART_UNKNOW,			//
    WS_HARD_DISK_PART_NORMAL,			 //��������
    WS_HARD_DISK_PART_ERROR,			        // �����豸�ڵ㲻���������ʻ����и�ʽ�����쳣����ʱ����: ȷ��OK 
    WS_HARD_DISK_PART_NEED_REPAIR,		 //��������ʧ�ܻ��߹��صķ�����ʽ����ȷȷ��OK
    WS_HARD_DISK_PART_NEED_CHECK,             // �����޸�ʧ�����������Ϊ����Լ죬ȷ��OK 
    WS_HARD_DISK_PART_READ_ONLY,		       //����ֻ��
    WS_HARD_DISK_PART_SMALL_MEMORY,		// ���̷���ΪС���� ȷ��OK
} ws_hard_disk_part_state;

typedef enum
{
    WS_HARD_DISK_TYPE_UNKNOW,	
    WS_HARD_DISK_TYPE_DISK,		        // Ӳ���ͺ�
    WS_HARD_DISK_TYPE_USB,			 //USB �ͺ�
    WS_HARD_DISK_TYPE_USB_CDROM,		 //USB ��¼��
    WS_HARD_DISK_TYPE_SATA_CDROM,      //SATA ��¼��
    WS_HARD_DISK_TYPE_END,
} ws_hard_disk_type;

typedef struct
{
    WS_CHAR     serial_no[48];
}ws_disk_serial;

typedef struct
{
    WS_CHAR vendor_name[16];
    WS_CHAR product_name[48];   //��Ʒ��
    WS_CHAR serial_no[48];   //��ƷΨһ��� add by liuyu date 2014-12-18
    WS_S32 scsi_bus_num;    //�������ĸ����

    ws_hard_disk_state state;
	ws_time_struct start_time;//��ʼʱ��										//Ҫ��
	ws_time_struct end_time;//����ʱ��										//Ҫ��
    int disk_space_MB; //Ӳ���ܿռ�
    int part_num;   //���÷�����

    WS_CHAR part_mount_dir[ws_utility::WS_NVR_MAX_HDISK_PART_NUM][16];  //�������ص�
    int valid_space_MB[ws_utility::WS_NVR_MAX_HDISK_PART_NUM]; //ÿ�������Ŀ��ÿռ�
    int total_space_MB[ws_utility::WS_NVR_MAX_HDISK_PART_NUM]; //ÿ���������ܿռ�
    int available_node[ws_utility::WS_NVR_MAX_HDISK_PART_NUM];//add by mjq 20151211 
    WS_BOOL 		is_complete;			// add by lmw 2016 10 20
} ws_hard_disk_info;

typedef struct
{
    WS_BOOL auto_rotate;    //�Ƿ��Զ���ת
} ws_hard_disk_work_ctl;


//��ʱֻ�ܻ�ȡ��֮ǰ �ı���ļ��е���Ϣ�������ܻ�ȡ�����̵��κ�������Ϣ
typedef struct fmt_node
{
    WS_CHAR     serial_no[48];
    WS_U32	  part_idx;
    fmt_node    *next;
} ws_fmt_disk;

typedef struct format_info
{
    WS_CHAR serial_no[48];
    WS_U32 part_idx;
}ws_disk_format_info;


typedef struct
{
    WS_CHAR                 mount_dir[64];
    ws_usb_dev_type      dev_type;
    WS_CHAR                 scsi_name[16];
    int                           valid_space_MB;
    int                           total_space_MB;
} ws_dev_part_info;

#ifdef __cplusplus
}//namespace ws_soft {
}//extern "C" {
#endif

#endif  //_WS_DISK_MANAGE_DEF_H_


