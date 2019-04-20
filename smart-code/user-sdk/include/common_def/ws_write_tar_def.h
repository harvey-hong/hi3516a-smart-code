#ifndef _WS_WRITE_TAR_DEF_H_
#define _WS_WRITE_TAR_DEF_H_
// add by ljx 20151224 start

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/ioctl.h>
#include <mtd/mtd-user.h>

#define ws_path_of_mtdblcok2	"/dev/mtdblock2"
#define ws_path_of_mtd2			"/dev/mtd2"
#define WS_CONF_TAR_PACKET		"/config/ws_conf.tgz"

struct mtd_epage_buf
{
	unsigned long long  start;
	unsigned long       data_len;
	unsigned long       oob_len;
	unsigned char     * data_ptr;
	unsigned char     * oob_ptr; 
};

//add by liuy date 2016-04-05 start
//编译时需要手动修改这里的参数
//3535的内核中此两项发生了变更
//3.4以下版本内核的平台，目前来看，包括21,31采用23和24
#define MEMEWRITEPAGE		_IOWR('M', 23, struct mtd_epage_buf)
#define MEMEREADPAGE		_IOWR('M', 24, struct mtd_epage_buf)// add by ljx 20151224

//3.4以上版本内核的平台，目前来看，包括21A,31A,35,36采用25和26
//#define MEMEWRITEPAGE		_IOWR('M', 25, struct mtd_epage_buf)
//#define MEMEREADPAGE		_IOWR('M', 26, struct mtd_epage_buf)// add by ljx 20151224

//add by liuy date 2016-04-05 end


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
// add by ljx 20151224 end

#endif

