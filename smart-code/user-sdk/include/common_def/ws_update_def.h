#ifndef _WS_UPDATE_DEF_H_
#define _WS_UPDATE_DEF_H_

#include "ws_comm_type.h"

#ifdef __cplusplus
extern "C" {
namespace ws_soft
{
#endif

typedef struct
{
    ws_utility::ws_soft_version packet_version;
    WS_CHAR packet_fname[ws_utility::WS_MAX_FILE_NAME_LEN + 1];
} ws_upgrade_packet;

typedef struct
{
    WS_CHAR file_name[ws_utility::WS_MAX_FILE_NAME_LEN + 1];
} ws_config_file;


typedef enum
{
    NEW_OLD_OFF = 0,//���Ƚ�

    NEW_EE_OLD, //new==old
    NEW_BE_OLD, //new>=old
    NEW_SE_OLD, //new<=old
    NEW_B_OLD,  //new>old
    NEW_S_OLD,  //new<old
} ws_version_ops_e;

typedef enum
{
    LIST_OFF = 0,   //���Ƚ�

    LIST_ONLY,      //�������б�ָ������
    LIST_FORBID,    //�������б�ָ������
} ws_list_ops_e;

typedef int (*version_check_permit)(const ws_utility::ws_soft_version *ver_0, const ws_utility::ws_soft_version *ver_1);

#define ws_update_bdname_len 	(32)
#define MAX_FILE_NUM 			(16)
#define MAX_FILE_NAME_LENGTH 	(64)
#define DATA_PIECE_VALID_LENGTH		(2048)
#define DATA_PIECE_INVALID_LENGTH 	(64)

typedef struct
{
	char	name[ws_update_bdname_len];
}ws_board_name_t;

typedef enum
{
	TYPE_UNKNOW = 0x0,
	TYPE_UBOOT,
	TYPE_KERNEL,
	TYPE_LOGO,
	TYPE_FS,
	TYPE_SLAVE_UBOOT_KERNEL,
	TYPE_SLAVE_FS,
	TYPE_TOOL,

	TYPE_CONF = 0x100,
}update_file_type;


typedef struct
{
	char file_name[MAX_FILE_NAME_LENGTH];
	int is_yaffs;
	update_file_type file_type;
	unsigned int file_length;
	unsigned int real_length;
}file_list_info;

typedef struct
{
	file_list_info file_info_p[MAX_FILE_NUM];
	int file_num;
}file_list_t;

typedef struct
{
    char fname[128];                // �ļ�����
} update_file_attr_t;

typedef struct
{
    char fname[128];                // �ļ�����
} xml_file_attr_t;

typedef struct
{
    const char *ops_name;
    ws_version_ops_e    ops;
    version_check_permit    permit;
} version_ops_info;

typedef struct
{

    int magic;

    int valid_ofset;    //ʵ����������ƫ��

    int valid_size;     //ʵ���������Ĵ�С


    int support_bd_ofset;   //֧�ֵİ��͵Ĵ��λ��  (��hsx_update_bdname_lenΪ��λ���)

    int support_bd_num;     //֧�ֵİ��͵���Ŀ


    ws_utility::ws_soft_version base_version;       //�����Ļ����汾

    ws_utility::ws_soft_version packet_version; //��ǰ�������İ汾


    ws_version_ops_e check_base_version;    //�Ի����汾�ļ��

    ws_version_ops_e check_packet_version;  //��packet�汾�ļ��

    ws_list_ops_e check_board_type;     //�԰���list�ļ��


    int reserved[96];

    unsigned char md5[16];  //ԭʼ��������md5ֵ

} ws_update_fhead_t;


typedef int (*list_check_permit)(const ws_update_fhead_t *fhead, const ws_board_name_t *board_name);


typedef struct
{
    const char *ops_name;
    ws_list_ops_e   ops;
    list_check_permit   permit;
} list_ops_info;


typedef enum
{
	TYPE_NONE = 0x0,
	TYPE_YAFFS2,
	TYPE_JFFS2,
}update_file_system_type;

typedef struct
{
	int magic_num;	//magic��ʶ
	int md5;			//�ļ�MD5��
	update_file_type file_type;	//�ļ�����
	update_file_system_type file_system_type;	//�ļ�ϵͳ����
	int need_update;		//��־�Ƿ����´�����ʱ���и��£�Ϊ1��ʾ��Ҫ��
	int last_start_success;		//��һ�������Ƿ�ɹ���ÿ��ϵͳ�ɹ����������ļ�ϵͳ��λ��uboot���ñ�־λ���Ϊ1�����ϴ������ɹ������¸�λ��һ����⵽��λΪ0����������ǰ���ļ�ϵͳ���лָ���
	int file_length;				//�ļ�����
	int start_block;				//��ʼ��
	int total_block;				//�ܿ���
	int start_page;				//��ʼҳ
	int total_page;				//��ҳ��
	int update_failed_count;		//����ʧ�ܴ���
	int update_cnt;				//��Ҫ�������ļ�����Ҳ�����Ա����
	int update_uboot_reboot;		//���������uboot֮����������������������
}update_file_attr_table;

struct mtd_epage_buf 
{
	unsigned long long  start;
	unsigned long       data_len;
	unsigned long       oob_len;
	unsigned char     * data_ptr;
	unsigned char     * oob_ptr; 
};


#if defined (_KERNEL_VER_3_10_)
#if 0
struct mtd_write_req {
	unsigned long long start;
	unsigned long long len;
	unsigned long long ooblen;
	unsigned long long usr_data;
	unsigned long long usr_oob;
	unsigned char mode;
	unsigned char padding[7];
};
#endif
#define WSMEMEWRITEPAGE(x)		_IOWR('M', 24, struct mtd_write_req)
#else

//3535���ں��д�������˱��
//3.4���°汾�ں˵�ƽ̨��Ŀǰ����������21,31����23��24
//#define MEMEWRITEPAGE		_IOWR('M', 23, struct mtd_epage_buf)
//#define MEMEREADPAGE		_IOWR('M', 24, struct mtd_epage_buf)// add by ljx 20151224

//3.4���ϰ汾�ں˵�ƽ̨��Ŀǰ����������21A,31A,35,36����25��26
//#define MEMEWRITEPAGE		_IOWR('M', 25, struct mtd_epage_buf)
//#define MEMEREADPAGE		_IOWR('M', 26, struct mtd_epage_buf)// add by ljx 20151224

//ʹ��ʱ,�����ID�Լ�д����д,����ݰ������ж�
#define WSMEMEWRITEPAGE(x)	_IOWR('M', x, struct mtd_epage_buf)
#define WSMEMEREADPAGE(x)	       _IOWR('M', x, struct mtd_epage_buf)

#endif

#define YAFFS2_SIGN_MAGIC    "YFSS!V10"

#ifdef __cplusplus
}//namespace ws_soft {
}//extern "C" {
#endif

#endif //#ifndef _WS_COMM_TRIGGER_H_

