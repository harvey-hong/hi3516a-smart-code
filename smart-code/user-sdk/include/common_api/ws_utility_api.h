#ifndef _WS_UTILITY_API_H_
#define _WS_UTILITY_API_H_

#include "ws_common.h"
#include "ws_comm_errno.h"
#include "ws_comm_display.h"

#include "ws_utility_def.h"
#include "ws_utility_class_def.h"
#include "ws_exception_proc_def.h"
#include "ws_network_def.h"
#include "ws_trigger_def.h"

#define WS_ROI_RECT_LENGHT 1000             //模板区域长度

/** Support language encoding format list! **/
#define _GB2312_  "gb2312"
#define _UTF8_      "utf-8"

#ifdef __cplusplus
namespace ws_utility
{
#endif

//构造好所有资源，首先调用
WS_ERR utility_init();

//----------------------------------------------- 比大小 ---------------------------------
WS_S32 utility_min(WS_S32 para1, WS_S32 para2);
WS_S32 utility_max(WS_S32 para1, WS_S32 para2);
WS_S32 utility_middle(WS_S32 para, WS_S32 min, WS_S32 max);

WS_U32 utility_min(WS_U32 para1, WS_U32 para2);
WS_U32 utility_max(WS_U32 para1, WS_U32 para2);
WS_U32 utility_middle(WS_U32 para, WS_U32 min, WS_U32 max);

//--------------------------------------------点阵放大------------------------------------
WS_VOID utility_hor_ver_x1_ex(const WS_CHAR *src, WS_S16 *dst, WS_U32 src_w, WS_U32 src_h, WS_U32 dst_stride, WS_U32 dst_h, WS_U16 valid, WS_U16 invalid);
WS_VOID utility_hor_ver_x3_ex(const WS_CHAR *src, WS_S16 *dst, WS_U32 src_w, WS_U32 src_h, WS_U32 dst_stride, WS_U32 dst_h, WS_U16 valid, WS_U16 invalid);
WS_VOID utility_hor_ver_x2_ex(const WS_CHAR *src, WS_S16 *dst, WS_U32 src_w, WS_U32 src_h, WS_U32 dst_stride, WS_U32 dst_h, WS_U16 valid, WS_U16 invalid);
WS_VOID utility_hor_ver_x4_ex(const WS_CHAR *src, WS_S16 *dst, WS_U32 src_w, WS_U32 src_h, WS_U32 dst_stride, WS_U32 dst_h, WS_U16 valid, WS_U16 invalid);


//---------------------------------------------- 睡眠函数 --------------------------------------
WS_ERR  utility_system(const WS_CHAR *cmd);
WS_VOID utility_sleep_ms(WS_U32 ms);    //睡眠函数

//可唤醒睡眠，在线程中如果使用普通睡眠，当需睡眠时间很长，要销毁线程时无法迅速唤醒，可以使用ws_interuptable_sleep对象，迅速唤醒后退出，purpose用于出问题的时候分析
ws_interuptable_sleep *utility_new_interuptable_sleep();

//--------------------------------------------- 线程管理 --------------------------------------------------
//线程创建，在线程函数(注意，是线程函数，不是创建线程的函数)的第一句加上 utility_save_pid_name(pthread_self(), getpid(), __FUNCTION__); 注册线程的PID和函数名，便于监管
WS_ERR utility_creat_thread(ws_thread_work_type work_type, ws_thread_priority priority, ws_thread_func func, void *usr_para, pthread_t *thread_hand);
WS_ERR utility_creat_thread_detach(ws_thread_work_type work_type, ws_thread_priority priority, ws_thread_func func, void *usr_para, pthread_t *thread_hand);
WS_ERR utility_save_pid_name(pthread_t thread_hand, pid_t pid, const WS_CHAR *thr_func_name);
//线程回收，函数返回之后才表示线程确实已经退出了
WS_ERR utility_retrieve_thread(pthread_t thread_hand);
WS_ERR utility_cancel_thread(pthread_t thread_hand);//Modified by peishunting 2014.12.18 start  - end
//---------------------------------------------- 内存操作 --------------------------------------------------
//内存分配、释放，ws_memmory_purpose 言简意赅的描述一下分配的目的，便于调试诊断
WS_VOID *utility_malloc(const char *funcname,const char *filename,const char *p,ws_module_id caller_id, ws_memmory_purpose purpose, size_t size);
//内存释放，监测是否double free，调用的时候把__FILE__和__FUNCTION__传进来，出错的时候好定位
WS_ERR utility_free(const WS_CHAR *file, const WS_CHAR *function, WS_VOID *memory);

//----------------------------------------------- 文件操作 --------------------------------------------------
ws_txt_file_operate *utility_new_txt_file_operate();
ws_binary_file_operate *utility_new_binary_file_operate();
ws_xml_operate *utility_new_xml_operate();
ws_bmp_operate *utility_new_bmp_operate();

//------------------------------------------------ 加密算法 -------------------------------------------------
ws_md5_cnt *utility_new_md5_cnt();

//------------------------------------------------- 同步锁 --------------------------------------------------
//创建锁对象，销毁时直接delete，创建的时候给锁起个名字，出了问题可以方便调试分析
ws_lock *utility_new_lock(const WS_CHAR *lock_name);
ws_rw_lock *utility_new_rw_lock(const WS_CHAR *lock_name);  //默认写线程优先级高于读线程

//------------------------------------------------- 时间格式转换 --------------------------------------------
#if defined(_SUPPORT_TIME_TYPE_AND_STANDARD_)
 WS_ERR utility_get_time_buf_show_for_osd_chinese(char *show_time_buf,ws_soft::ws_gui_show_time_type show_time_type,ws_soft::ws_gui_time_standard time_standard);
 WS_ERR utility_get_time_buf_show_for_osd_english(char *show_time_buf,ws_soft::ws_gui_show_time_type show_time_type,ws_soft::ws_gui_time_standard time_standard);
 WS_ERR utility_get_time_buf_show_for_traditional_chinese(char *show_time_buf,ws_soft::ws_gui_show_time_type show_time_type,ws_soft::ws_gui_time_standard time_standard);
 WS_U32 change_twenty_four_to_twelve_standard(WS_U32 tm_hour);
#endif 

WS_ERR utility_linux_to_ws_time(time_t linux_time, ws_time_struct *ws_time);
WS_ERR utility_ws_to_linux_time(const ws_time_struct *ws_time, time_t *linux_time);
WS_S32 utility_cnt_delta_ms(const struct timeval *time1, const struct timeval *time2);  //计算时间差值，time1小于time2返回负
WS_U32 utility_cnt_interval_ms(const struct timeval *time1, const struct timeval *time2);   //计算时间差值，绝对值
WS_S32 utility_cmp_time(const struct timeval *time1, const struct timeval *time2);  //比较大小，time1小于time2返回负，相等返回0，time1大于time2返回正

WS_S32 utility_correct_time_same_day(const ws_time_struct *time1, const ws_time_struct *time2, WS_U32 delta);  

WS_ERR utility_get_month_day(const ws_time_struct *ws_time, int *day); //计算当前时间所在月共有多少天

//----------------------------------------------- 定时器 ------------------------------------------------------
//注册定时器工作回调，caller_id 调用该函数的模块ID，func_name，注册的回调函数的名称，这两个参数方便调试的时候的诊断, interval_ms表示工作间隔，以100毫秒为单位
//在func函数中不允许调用注册和反注册函数
WS_ERR utility_c_regist_timer(ws_module_id  caller_id, ws_timer_func func, const char *func_name, WS_U32 interval_ms, WS_BOOL work_once);
WS_ERR utility_c_unregist_timer(ws_timer_func func);

//注册定时器工作回调，caller_id 调用该函数的模块ID，object为继承ws_timer_client虚接口后的对象
//在处理函数中不允许调用注册和反注册函数
WS_ERR utility_cpp_regist_timer(ws_module_id caller_id, ws_timer_client *client, const char *client_name, WS_U32 interval_ms, WS_BOOL work_once);
WS_ERR utility_cpp_unregist_timer(ws_timer_client *client);

//-------------------------------------------- 区域计算 -----------------------------------------------------------
//计算指定分割模式和分辨率各个窗口的实际区域坐标
WS_ERR utility_cnt_div_real_rect(const ws_display_screen_info *screen_info, ws_real_rect *real_rect, size_t rect_dim);
//将相对坐标转换成绝对坐标
WS_ERR utility_cnt_real_rect(WS_U32 resol_w, WS_U32 resol_h, const ws_abstract_rect *abstract_rect, ws_real_rect *real_rect);
WS_BOOL utility_is_valid_rect(const ws_abstract_rect *abstract_rect);   //判断抽象坐标是否合法

void utility_cnt_accumulate_rect(ws_abstract_rect &old_rect, const ws_abstract_rect *new_rect); //计算累计区域

//计算偏移区域
WS_ERR utility_cnt_excursion_rect(ws_abstract_rect &old_rect, ws_real_rect &real_rect, const ws_abstract_coordinate *start, const ws_abstract_coordinate *stop);

//计算放大缩小累积区域
WS_ERR utility_cnt_amplification_rect(ws_abstract_rect &old_rect, ws_real_rect &real_rect, const ws_abstract_coordinate *coor);
WS_ERR utility_cnt_lessen_rect(ws_abstract_rect &old_rect, ws_real_rect &real_rect, const ws_abstract_coordinate *coor);

//仅作用于将相对于1000*1000的模板的真实尺寸转换成百分比尺寸
void utility_cnt_real_to_abstract(ws_abstract_rect &old_rect, ws_real_rect &real_rect);

//---------------------------------------- 网络 ----------------------------------
WS_ERR utility_get_local_mac(char *mac);                    // change by linhh 20160725 

//---------------------------------------------- 在线诊断 ---------------------------------------------------------
//注册诊断对象，purpose言简意赅的描述诊断的用途，方便选择操作，help描述参数说明，详细参考utility_sample中使用方法
WS_ERR utility_regist_diag(ws_diagnose_client *client, const WS_CHAR *purpose, const WS_CHAR *help);
WS_ERR utility_unregist_diag(ws_diagnose_client *client);

//------------------------------------------------看门狗接口------------------------------------------------------
//各个模块调用utility_regist注册看门狗，传入的参数为ID和阀值(以s为单位)，该函数返回一个指针，fetch_dog根据这个参数进行
//喂狗操作，如果返回NULL表示注册失败
WS_U32 *utility_regist_watch_dog(ws_module_id module_id, WS_U32 threshold);
WS_ERR utility_fetch_dog(WS_U32 *space_pointer);//喂狗函数，根据utility_regist_watch_dog返回的参数进行操作
WS_BOOL utility_check_need_reset(ws_module_id *module_id);//如果返回WS_TURE，id号指示是哪个模块死掉

//------------------------------------------------异常处理接口----------------------------------------------------
//需要相应模块把自己的情况传递到utility中保存，后续会有检测线程来读取这些异常，不论是否异常，该更新的时候就要更新

//检测输入字符的合法性,一般A-Za-z0-9_-
WS_ERR utility_char_legal_manager(const WS_CHAR *name_or_pwd);

/* hzg added check character validation 20150424 start */
//检测输入字符的合法性,[A-Za-z0-9_-]and GB2312 Chinese character.
WS_ERR utility_check_normal_char_and_chinese(const WS_CHAR *name_or_pwd);
/* hzg added check character validation 20150424 end */

//add by liuyu date 2014-10-20 start
/*快速排序法 快速对一组整型数据进行排序*/
WS_ERR utility_quicksort(ws_quick_sort a[],size_t numsize);
//add by liuyu date 2014-10-20 end

/* hongzg 20150508 added for Chinese character encoding convert start */
/** Use this function to convert Chinese charscter encoding between UTF-8 and GB2312. 
***  from_charset and to_charset MUST be  _GB2312_("gb2312") or _UTF8_("utf-8")
***  src_buf is input string,  dst_buf is output string, all those buffer's memory MUST 
***  be alloced by caller, gb2312 encoding 2 bytes, and utf8 encoding 3 bytes for 1 chinese character.
***  return WS_SUCCESS is OK, othe return value is fail and need check system errno.**/
WS_ERR utility_charset_convert(const WS_CHAR *from_charset,const WS_CHAR *to_charset,WS_CHAR *src_buf, WS_U32 src_len,WS_CHAR *dst_buf, WS_U32 dst_len);
/* hongzg 20150508 added for Chinese character encoding convert end */

WS_ERR utility_get_connect_cfg(ws_soft::ws_local_connect_cfg *cfg,const char *if_name);

//liujl change start-end at 20170828, Synchronous branch SVN998 code
#ifdef  _SUPPORT_SYSLOG_
WS_ERR utility_syslog(const char *LogString);
#endif

class CMutex
{
public:
    CMutex();
    virtual ~CMutex();

public:
    int     create();
    
    int     destroy();

    int     lock();

    int     trylock();

    int     unlock();
    
protected:
    CMutex(const CMutex &rObj);
    CMutex &operator=(const CMutex &rObj);
private:
    pthread_mutex_t          m_hMutex;
    pthread_mutexattr_t     m_hAttribute;
    bool                             m_bState;
};

class CMutexSingle
{
public:
    CMutexSingle();
    virtual ~CMutexSingle();
public:
    int     create();
    
    int     destroy();

    int     lock();

    int     trylock();

    int     unlock();
    
protected:
    CMutexSingle(const CMutexSingle &rObj);
    CMutexSingle &operator=(const CMutexSingle &rObj);
private:
    pthread_mutex_t       m_hMutex;
    pthread_mutexattr_t  m_hAttribute;
    bool                          m_bState;
};

class CGuard
{
public:
    CGuard(CMutex *pMutex);
    virtual ~CGuard();
    
protected:
    CGuard(const CGuard &rObj);
    CGuard &operator=(const CGuard &rObj);
private:
    CMutex  *m_pMutex;
};

class CGuardSingle
{
public:
    CGuardSingle(CMutexSingle *pMutex);
    virtual ~CGuardSingle();
    
protected:
    CGuardSingle(const CGuardSingle &rObj);
    CGuardSingle &operator=(const CGuardSingle &rObj);
    
private:
    CMutexSingle  *m_pMutex;
};

class CSignal
{
public:
    CSignal();
    virtual ~CSignal();
    
public:
    int     create();
    int     destroy();
    int     signal();
    int     wait(unsigned long timeout = 0xFFFFFFFF);
protected:
    CSignal(const CSignal &rObj);
    CSignal &operator=(const CSignal &rObj);
private:
    pthread_mutex_t m_hMutex;
    pthread_cond_t   m_hCond;
    int                      m_dwSemCount;
    bool                    m_bState;
};

#ifdef __cplusplus
}
#endif

#endif  //#ifndef _UTILITY_API_H_

