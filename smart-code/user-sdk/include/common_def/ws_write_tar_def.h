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
//����ʱ��Ҫ�ֶ��޸�����Ĳ���
//3535���ں��д�������˱��
//3.4���°汾�ں˵�ƽ̨��Ŀǰ����������21,31����23��24
#define MEMEWRITEPAGE		_IOWR('M', 23, struct mtd_epage_buf)
#define MEMEREADPAGE		_IOWR('M', 24, struct mtd_epage_buf)// add by ljx 20151224

//3.4���ϰ汾�ں˵�ƽ̨��Ŀǰ����������21A,31A,35,36����25��26
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
// add by ljx 20151224 end

#endif

