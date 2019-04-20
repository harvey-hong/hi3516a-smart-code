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
    NEW_OLD_OFF = 0,//不比较

    NEW_EE_OLD, //new==old
    NEW_BE_OLD, //new>=old
    NEW_SE_OLD, //new<=old
    NEW_B_OLD,  //new>old
    NEW_S_OLD,  //new<old
} ws_version_ops_e;

typedef enum
{
    LIST_OFF = 0,   //不比较

    LIST_ONLY,      //仅允许列表指定的项
    LIST_FORBID,    //不允许列表指定的项
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
    char fname[128];                // 文件名称
} update_file_attr_t;

typedef struct
{
    char fname[128];                // 文件名称
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

    int valid_ofset;    //实际升级包的偏移

    int valid_size;     //实际升级包的大小


    int support_bd_ofset;   //支持的板型的存放位置  (以hsx_update_bdname_len为单位存放)

    int support_bd_num;     //支持的板型的数目


    ws_utility::ws_soft_version base_version;       //依赖的基础版本

    ws_utility::ws_soft_version packet_version; //当前升级包的版本


    ws_version_ops_e check_base_version;    //对基础版本的检查

    ws_version_ops_e check_packet_version;  //对packet版本的检查

    ws_list_ops_e check_board_type;     //对板型list的检查


    int reserved[96];

    unsigned char md5[16];  //原始升级包的md5值

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
	int magic_num;	//magic标识
	int md5;			//文件MD5码
	update_file_type file_type;	//文件类型
	update_file_system_type file_system_type;	//文件系统类型
	int need_update;		//标志是否在下次启动时进行更新（为1表示需要）
	int last_start_success;		//上一次启动是否成功，每次系统成功启动后由文件系统置位，uboot检测该标志位如果为1表明上次启动成功，重新复位，一旦检测到该位为0，重新利用前期文件系统进行恢复。
	int file_length;				//文件长度
	int start_block;				//起始块
	int total_block;				//总块数
	int start_page;				//起始页
	int total_page;				//总页数
	int update_failed_count;		//更新失败次数
	int update_cnt;				//需要升级的文件数，也是属性表个数
	int update_uboot_reboot;		//标记升级完uboot之后重启，继续其他的升级
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

//3535的内核中此两项发生了变更
//3.4以下版本内核的平台，目前来看，包括21,31采用23和24
//#define MEMEWRITEPAGE		_IOWR('M', 23, struct mtd_epage_buf)
//#define MEMEREADPAGE		_IOWR('M', 24, struct mtd_epage_buf)// add by ljx 20151224

//3.4以上版本内核的平台，目前来看，包括21A,31A,35,36采用25和26
//#define MEMEWRITEPAGE		_IOWR('M', 25, struct mtd_epage_buf)
//#define MEMEREADPAGE		_IOWR('M', 26, struct mtd_epage_buf)// add by ljx 20151224

//使用时,具体的ID自己写入填写,需根据版型来判断
#define WSMEMEWRITEPAGE(x)	_IOWR('M', x, struct mtd_epage_buf)
#define WSMEMEREADPAGE(x)	       _IOWR('M', x, struct mtd_epage_buf)

#endif

#define YAFFS2_SIGN_MAGIC    "YFSS!V10"

#ifdef __cplusplus
}//namespace ws_soft {
}//extern "C" {
#endif

#endif //#ifndef _WS_COMM_TRIGGER_H_

