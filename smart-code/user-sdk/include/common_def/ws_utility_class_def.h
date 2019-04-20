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

//可唤醒睡眠
class ws_interuptable_sleep
{
public:
    virtual WS_ERR sleep_ms(WS_U32 ms) = 0;
    virtual WS_ERR wakeup() = 0;

public:
    virtual ~ws_interuptable_sleep() {};
};

//诊断信息
typedef void (*ws_diag_dump)(const char *format, ...);
class ws_diagnose_client
{
public:
    virtual WS_VOID diagnose_dump(WS_U32 para, ws_diag_dump dump_fuc) = 0;

public:
    virtual ~ws_diagnose_client() {};
};

//定时器
class ws_timer_client
{
public:
    virtual WS_VOID process_timer() = 0;

public:
    virtual ~ws_timer_client() {};
};

//封装通用锁的使用，调用的时候用 __FILE__ 和 __FUNCTION__ 把调用点传递进来，便于监控锁的使用状况
class ws_lock
{
public:
    virtual WS_ERR lock(const WS_CHAR *file_name, const WS_CHAR *func_name) = 0;    //加锁
    virtual WS_ERR trylock(const WS_CHAR *file_name, const WS_CHAR *func_name) = 0; //尝试加锁，成功返回WS_SUCCESS
    virtual WS_ERR unlock(const WS_CHAR *file_name, const WS_CHAR *func_name) = 0;  //释放锁

    virtual WS_BOOL if_is_dead_lock() = 0;  //检测是否死锁
    virtual WS_VOID get_state_info(WS_CHAR *info_buf, size_t buf_size) = 0; //获取当前使用锁的状况，是否被锁上，被谁锁上

public:
    virtual ~ws_lock() {};
};

//封装读写锁的使用，调用的时候用 __FILE__ 和 __FUNCTION__ 把调用点传递进来，便于监控锁的使用状况
class ws_rw_lock
{
public:
    virtual WS_ERR rd_lock(const WS_CHAR *file_name, const WS_CHAR *func_name) = 0;     //读加锁
    virtual WS_ERR rd_trylock(const WS_CHAR *file_name, const WS_CHAR *func_name) = 0;  //读尝试加锁

    virtual WS_ERR wr_lock(const WS_CHAR *file_name, const WS_CHAR *func_name) = 0;     //写加锁
    virtual WS_ERR wr_trylock(const WS_CHAR *file_name, const WS_CHAR *func_name) = 0;  //写尝试加锁

    virtual WS_ERR unlock(const WS_CHAR *file_name, const WS_CHAR *func_name) = 0;  //释放锁,调用的时候用 __FUNCTION__ 把函数名带进来，便于监控锁的使用状况

    virtual WS_VOID get_state_info(WS_CHAR *info_buf, size_t buf_size) = 0; //获取当前使用锁的状况，是否被锁上，被谁锁上
public:
    virtual ~ws_rw_lock() {};
};

//文本文件读写访问
class ws_txt_file_operate
{
public:
    virtual WS_ERR  open(const char *fname, ws_file_open_mode mode) = 0;    //op_as_binary标示是否已二进制方式操作，linux下无效，windows下有效
    virtual WS_ERR  close() = 0;

    virtual WS_ERR  read(WS_CHAR *buf, size_t buf_size) = 0;    //一次读取一行
    virtual WS_ERR  write(const WS_CHAR *str) = 0;

    //ofset为负数表示向前偏移，为正数表示向后偏移
    virtual WS_ERR  seek(ws_file_cnt_ofset_mode mode, WS_S32 ofset) = 0;

    virtual WS_ERR  sync() = 0; //同步到磁盘，成功返回WS_SUCCESS，失败返回其他
    virtual WS_S32  get_file_size() = 0;    //获取文件大小，以字节为单位

public:
    virtual ~ws_txt_file_operate() {};
};

class ws_binary_file_operate
{
public:
    virtual WS_ERR  open(const char *fname, ws_file_open_mode mode) = 0;    //op_as_binary标示是否已二进制方式操作，linux下无效，windows下有效
    virtual WS_ERR  close() = 0;

    virtual size_t  read(void *buf, size_t buf_size, size_t need_rd_size) = 0;  //读指定大小数据，返回实际读取的大小
    virtual size_t  write(const void *buf, size_t need_wr_size) = 0;    //写指定大小数据，返回实际写入的大小

    //ofset为负数表示向前偏移，为正数表示向后偏移
    virtual WS_ERR  seek(ws_file_cnt_ofset_mode mode, WS_S32 ofset) = 0;

    virtual WS_ERR  sync() = 0; //同步到磁盘，成功返回WS_SUCCESS，失败返回其他
    virtual WS_S32  get_file_size() = 0;    //获取文件大小，以字节为单位
    virtual WS_S32  get_fd_pos() = 0;   //获取当前文件指针位置

public:
    virtual ~ws_binary_file_operate() {};
};


//xml文件访问
class ws_xml_operate
{
public:
    virtual WS_ERR clear_content() = 0;                 //清除内容
    virtual WS_ERR load_file(const char *fname) = 0;    //从文件导入初始内容
    virtual WS_ERR load_buf(const char *buf) = 0;       //从缓冲区导入初始内容

    virtual WS_ERR save_content(const char *fname) = 0; //将内容保存成文件
    virtual WS_ERR export_content(WS_CHAR *buf, size_t buf_size, WS_U32 *export_size) = 0;  //将内容导出
    virtual size_t get_content_size() = 0;  //获取内容大小

    /***********************************************************************************
       信息在节点中的存储有两种方式，一种是直接存储，一种通过属性
       <Persons>
            <Person>
                <name>yuhj</name>
                <info age="32" wheight="75"></info>
            </Person>
        </Persons>

        Persons.person.name和Persons.person.info都是节点，name节点中的信息通过文本直接存储，而info节点中有两个属性，分别为age和weight
        通常配置文件采用直接存储的方式，便于查阅，而网络中的消息通信采用属性存储方式，便于抓包后分析
        如果把几级节点目录一起传进来，一是调用者需要把几级目录拼接，二是xml对象需要解析，调用者麻烦且实现者容易出错，绝大多数情况下不超过三级，有别的需求的话再加就是了
        如果只有一级，则key1和key2为NULL,
        如果只有两级，则key2为NULL,
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

//bmp文件处理
class ws_bmp_operate
{
public:
    virtual WS_ERR  open(const char *fname, ws_file_open_mode mode) = 0;    //op_as_binary标示是否已二进制方式操作，linux下无效，windows下有效
    virtual WS_ERR  close() = 0;

    virtual WS_ERR  get_w_h(int *width, int *height) = 0;
    virtual size_t  read(char *buf, size_t buf_size) = 0;   //读指定大小数据，返回实际读取的大小
    virtual size_t  write_rgb(void *buf, int width, int height, int stride, ws_rgb_color_mode color_mode) = 0;  //将数据保存为bmp

public:
    virtual ~ws_bmp_operate() {};
};

//Md5计算
class ws_md5_cnt
{
public:
    virtual WS_ERR reset() = 0; //清空计算结果
    virtual WS_ERR add_data(const WS_CHAR *data, WS_U32 data_len) = 0;      //开始累加计算
    virtual WS_ERR get_result(WS_CHAR *result_buf, size_t buf_size) = 0;    //获取最终结果，16个字节

public:
    virtual ~ws_md5_cnt() {};
};


#ifdef __cplusplus
}//namespace ws_utility {//changed by mjq 2014.11.26
}//extern "C" {
#endif

#endif  //_WS_UTILITY_CLASS_DEF_H_

