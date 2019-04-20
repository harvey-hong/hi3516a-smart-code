#ifndef _WS_UTILITY_CLASS_DEF_H_
#define _WS_UTILITY_CLASS_DEF_H_

#include "ws_comm_sys.h"
#include "ws_comm_type.h"
#include "ws_comm_errno.h"
#include "ws_utility_def.h"
#include "ws_utility_class_def.h"




#ifdef __cplusplus
extern "C" {
namespace ws_utility //changed by mjq 2014.11.26

{
#endif

//�ɻ���˯��
class ws_interuptable_sleep
{
public:
    virtual WS_ERR sleep_ms(WS_U32 ms) = 0;
    virtual WS_ERR wakeup() = 0;

public:
    virtual ~ws_interuptable_sleep() {};
};

//�����Ϣ
typedef void (*ws_diag_dump)(const char *format, ...);
class ws_diagnose_client
{
public:
    virtual WS_VOID diagnose_dump(WS_U32 para, ws_diag_dump dump_fuc) = 0;

public:
    virtual ~ws_diagnose_client() {};
};

//��ʱ��
class ws_timer_client
{
public:
    virtual WS_VOID process_timer() = 0;

public:
    virtual ~ws_timer_client() {};
};

//��װͨ������ʹ�ã����õ�ʱ���� __FILE__ �� __FUNCTION__ �ѵ��õ㴫�ݽ��������ڼ������ʹ��״��
class ws_lock
{
public:
    virtual WS_ERR lock(const WS_CHAR *file_name, const WS_CHAR *func_name) = 0;    //����
    virtual WS_ERR trylock(const WS_CHAR *file_name, const WS_CHAR *func_name) = 0; //���Լ������ɹ�����WS_SUCCESS
    virtual WS_ERR unlock(const WS_CHAR *file_name, const WS_CHAR *func_name) = 0;  //�ͷ���

    virtual WS_BOOL if_is_dead_lock() = 0;  //����Ƿ�����
    virtual WS_VOID get_state_info(WS_CHAR *info_buf, size_t buf_size) = 0; //��ȡ��ǰʹ������״�����Ƿ����ϣ���˭����

public:
    virtual ~ws_lock() {};
};

//��װ��д����ʹ�ã����õ�ʱ���� __FILE__ �� __FUNCTION__ �ѵ��õ㴫�ݽ��������ڼ������ʹ��״��
class ws_rw_lock
{
public:
    virtual WS_ERR rd_lock(const WS_CHAR *file_name, const WS_CHAR *func_name) = 0;     //������
    virtual WS_ERR rd_trylock(const WS_CHAR *file_name, const WS_CHAR *func_name) = 0;  //�����Լ���

    virtual WS_ERR wr_lock(const WS_CHAR *file_name, const WS_CHAR *func_name) = 0;     //д����
    virtual WS_ERR wr_trylock(const WS_CHAR *file_name, const WS_CHAR *func_name) = 0;  //д���Լ���

    virtual WS_ERR unlock(const WS_CHAR *file_name, const WS_CHAR *func_name) = 0;  //�ͷ���,���õ�ʱ���� __FUNCTION__ �Ѻ����������������ڼ������ʹ��״��

    virtual WS_VOID get_state_info(WS_CHAR *info_buf, size_t buf_size) = 0; //��ȡ��ǰʹ������״�����Ƿ����ϣ���˭����
public:
    virtual ~ws_rw_lock() {};
};

//�ı��ļ���д����
class ws_txt_file_operate
{
public:
    virtual WS_ERR  open(const char *fname, ws_file_open_mode mode) = 0;    //op_as_binary��ʾ�Ƿ��Ѷ����Ʒ�ʽ������linux����Ч��windows����Ч
    virtual WS_ERR  close() = 0;

    virtual WS_ERR  read(WS_CHAR *buf, size_t buf_size) = 0;    //һ�ζ�ȡһ��
    virtual WS_ERR  write(const WS_CHAR *str) = 0;

    //ofsetΪ������ʾ��ǰƫ�ƣ�Ϊ������ʾ���ƫ��
    virtual WS_ERR  seek(ws_file_cnt_ofset_mode mode, WS_S32 ofset) = 0;

    virtual WS_ERR  sync() = 0; //ͬ�������̣��ɹ�����WS_SUCCESS��ʧ�ܷ�������
    virtual WS_S32  get_file_size() = 0;    //��ȡ�ļ���С�����ֽ�Ϊ��λ

public:
    virtual ~ws_txt_file_operate() {};
};

class ws_binary_file_operate
{
public:
    virtual WS_ERR  open(const char *fname, ws_file_open_mode mode) = 0;    //op_as_binary��ʾ�Ƿ��Ѷ����Ʒ�ʽ������linux����Ч��windows����Ч
    virtual WS_ERR  close() = 0;

    virtual size_t  read(void *buf, size_t buf_size, size_t need_rd_size) = 0;  //��ָ����С���ݣ�����ʵ�ʶ�ȡ�Ĵ�С
    virtual size_t  write(const void *buf, size_t need_wr_size) = 0;    //дָ����С���ݣ�����ʵ��д��Ĵ�С

    //ofsetΪ������ʾ��ǰƫ�ƣ�Ϊ������ʾ���ƫ��
    virtual WS_ERR  seek(ws_file_cnt_ofset_mode mode, WS_S32 ofset) = 0;

    virtual WS_ERR  sync() = 0; //ͬ�������̣��ɹ�����WS_SUCCESS��ʧ�ܷ�������
    virtual WS_S32  get_file_size() = 0;    //��ȡ�ļ���С�����ֽ�Ϊ��λ
    virtual WS_S32  get_fd_pos() = 0;   //��ȡ��ǰ�ļ�ָ��λ��

public:
    virtual ~ws_binary_file_operate() {};
};


//xml�ļ�����
class ws_xml_operate
{
public:
    virtual WS_ERR clear_content() = 0;                 //�������
    virtual WS_ERR load_file(const char *fname) = 0;    //���ļ������ʼ����
    virtual WS_ERR load_buf(const char *buf) = 0;       //�ӻ����������ʼ����

    virtual WS_ERR save_content(const char *fname) = 0; //�����ݱ�����ļ�
    virtual WS_ERR export_content(WS_CHAR *buf, size_t buf_size, WS_U32 *export_size) = 0;  //�����ݵ���
    virtual size_t get_content_size() = 0;  //��ȡ���ݴ�С

    /***********************************************************************************
       ��Ϣ�ڽڵ��еĴ洢�����ַ�ʽ��һ����ֱ�Ӵ洢��һ��ͨ������
       <Persons>
            <Person>
                <name>yuhj</name>
                <info age="32" wheight="75"></info>
            </Person>
        </Persons>

        Persons.person.name��Persons.person.info���ǽڵ㣬name�ڵ��е���Ϣͨ���ı�ֱ�Ӵ洢����info�ڵ������������ԣ��ֱ�Ϊage��weight
        ͨ�������ļ�����ֱ�Ӵ洢�ķ�ʽ�����ڲ��ģ��������е���Ϣͨ�Ų������Դ洢��ʽ������ץ�������
        ����Ѽ����ڵ�Ŀ¼һ�𴫽�����һ�ǵ�������Ҫ�Ѽ���Ŀ¼ƴ�ӣ�����xml������Ҫ�������������鷳��ʵ�������׳��������������²������������б������Ļ��ټӾ�����
        ���ֻ��һ������key1��key2ΪNULL,
        ���ֻ����������key2ΪNULL,
    *************************************************************************************/
    virtual WS_ERR read_str(const char *key0, const char *key1, const char *key2, const char *key3, char *buf, size_t buf_size) = 0;
    virtual WS_ERR read_str_ex(const char *key0, const char *key1, const char *key2, const char *key3, char *buf, size_t buf_size) = 0;
    virtual WS_ERR read_str_ex2(const char *key0, const char *key1, const char *key2, const char *key3, char *buf, size_t buf_size) = 0; //add by qqy, at 2017-04-27 20:29:17
    virtual WS_ERR write_str(const char *key0, const char *key1, const char *key2, const char *key3, const char *str) = 0;
    virtual WS_Xml_Node *write_str_ex(const char *key0, const char *key1, const char *key2, const char *key3, const char *str) = 0;
    virtual WS_ERR write_str_ex2(const char *key0, const char *key1, const char *key2, const char *key3, const char *str) = 0;
    virtual WS_ERR read_int(const char *key0, const char *key1, const char *key2, const char *key3, WS_S32 *para) = 0;
    virtual WS_ERR read_int_ex(const char *key0, const char *key1, const char *key2, const char *key3, WS_S32 *para) = 0;
    virtual WS_ERR read_int_ex2(const char *key0, const char *key1, const char *key2, const char *key3, WS_S32 *para) = 0;	 //add by qqy, at 2017-04-27 20:28:50
    virtual WS_ERR write_int(const char *key0, const char *key1, const char *key2, const char *key3, WS_S32 para) = 0;
    virtual WS_Xml_Node *write_int_ex(const char *key0, const char *key1, const char *key2, const char *key3, WS_S32 para) = 0;
    virtual WS_Xml_Node *get_parent(TiXmlElement *cur_node) = 0;
    virtual WS_Xml_Node *add_child_node(TiXmlElement *cur_node, const char *NameStr, const char *ValueStr) = 0;
    virtual WS_ERR write_int_ex2(const char *key0, const char *key1, const char *key2, const char *key3, WS_S32 para) = 0;
    virtual WS_ERR read_attr_str(const char *key0, const char *key1, const char *key2, const char *attr, char *buf, size_t buf_size) = 0;
    virtual WS_ERR write_attr_str(const char *key0, const char *key1, const char *key2, const char *attr, const char *str) = 0;

    virtual WS_ERR read_attr_int(const char *key0, const char *key1, const char *key2, const char *attr, WS_S32 *para) = 0;
    virtual WS_ERR write_attr_int(const char *key0, const char *key1, const char *key2, const char *attr, WS_S32 para) = 0;

	virtual WS_ERR get_first_child_key_name(const char *key0, const char *key1, const char *key2, char *buf, size_t buf_size) = 0;
	virtual WS_ERR get_next_sibling_key_name(const char *key0, const char *key1, const char *key2, const char *key3, char *buf, size_t buf_size) = 0;
	virtual WS_ERR add_key1(const char *key0,const char *key1, const char *AfterKeyName ) = 0;
	virtual WS_ERR delet_key1(const char *key0,char *key1) = 0;
	virtual WS_ERR change_key1_name(const char *key0,char *old_key1,char *new_key1) = 0;
	virtual WS_ERR add_key2(const char *key0,const char *key1,const char *key2, const char *AfterKeyName ) = 0;
	virtual WS_ERR delet_key2(const char *key0,char *key1,char *key2) = 0;
	virtual WS_ERR change_key2_name(const char *key0,char *key1,char *old_key2,char *new_key2) = 0;
	virtual WS_ERR add_key3_of_int(const char *key0,char *key1,char *key2,char *key3,WS_S32 value, const char *AfterKeyName ) = 0;
	virtual WS_ERR add_key3_of_str(const char *key0,const char *key1,const char *key2,const char *key3,const char *key3_value, const char *AfterKeyName ) = 0;
	virtual WS_ERR delet_key3(const char *key0,char *key1,char *key2,char *key3) = 0;
	virtual WS_ERR change_key3_of_int(const char *key0,char *key1,char *key2,char *old_key3,char *new_key3,WS_S32 new_value) = 0;
	virtual WS_ERR change_key3_of_str(const char *key0,char *key1,char *key2,char *old_key3,char *new_key3,char *new_value)=0;
	virtual WS_ERR find_element_ex(const char *key0, const char *key1, const char *key2, const char *key3)= 0;
	virtual WS_ERR write_attr_str_of_xml_tool(const char *key0, const char *key1, const char *key2, const char *key3,const char *attr, const char *str)=0;
	virtual WS_ERR read_attr_str_of_xml_tool(const char *key0, const char *key1, const char *key2,const char *key3 ,const char *attr, char *buf, size_t buf_size)=0;

 //add by qqy,start at 2017-05-02 17:54:46
    virtual int GetFirstElement(int handle, const char *key) = 0;
    virtual int GetSiblingElement(int handle, const char *key) = 0;
    virtual WS_ERR read_str(int handle, const char *key,char *buf, size_t buf_size) = 0;
    virtual WS_ERR read_int(int handle, const char *key,WS_S32 *para) = 0;
 //add by qqy,end at 2017-05-02 17:54:48

public:
    virtual ~ws_xml_operate() {};
};

//bmp�ļ�����
class ws_bmp_operate
{
public:
    virtual WS_ERR  open(const char *fname, ws_file_open_mode mode) = 0;    //op_as_binary��ʾ�Ƿ��Ѷ����Ʒ�ʽ������linux����Ч��windows����Ч
    virtual WS_ERR  close() = 0;

    virtual WS_ERR  get_w_h(int *width, int *height) = 0;
    virtual size_t  read(char *buf, size_t buf_size) = 0;   //��ָ����С���ݣ�����ʵ�ʶ�ȡ�Ĵ�С
    virtual size_t  write_rgb(void *buf, int width, int height, int stride, ws_rgb_color_mode color_mode) = 0;  //�����ݱ���Ϊbmp

public:
    virtual ~ws_bmp_operate() {};
};

//Md5����
class ws_md5_cnt
{
public:
    virtual WS_ERR reset() = 0; //��ռ�����
    virtual WS_ERR add_data(const WS_CHAR *data, WS_U32 data_len) = 0;      //��ʼ�ۼӼ���
    virtual WS_ERR get_result(WS_CHAR *result_buf, size_t buf_size) = 0;    //��ȡ���ս����16���ֽ�

public:
    virtual ~ws_md5_cnt() {};
};


#ifdef __cplusplus
}//namespace ws_utility {//changed by mjq 2014.11.26
}//extern "C" {
#endif

#endif  //_WS_UTILITY_CLASS_DEF_H_

