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

#define WS_ROI_RECT_LENGHT 1000             //ģ�����򳤶�

/** Support language encoding format list! **/
#define _GB2312_  "gb2312"
#define _UTF8_      "utf-8"

#ifdef __cplusplus
namespace ws_utility
{
#endif

//�����������Դ�����ȵ���
WS_ERR utility_init();

//----------------------------------------------- �ȴ�С ---------------------------------
WS_S32 utility_min(WS_S32 para1, WS_S32 para2);
WS_S32 utility_max(WS_S32 para1, WS_S32 para2);
WS_S32 utility_middle(WS_S32 para, WS_S32 min, WS_S32 max);

WS_U32 utility_min(WS_U32 para1, WS_U32 para2);
WS_U32 utility_max(WS_U32 para1, WS_U32 para2);
WS_U32 utility_middle(WS_U32 para, WS_U32 min, WS_U32 max);

//--------------------------------------------����Ŵ�------------------------------------
WS_VOID utility_hor_ver_x1_ex(const WS_CHAR *src, WS_S16 *dst, WS_U32 src_w, WS_U32 src_h, WS_U32 dst_stride, WS_U32 dst_h, WS_U16 valid, WS_U16 invalid);
WS_VOID utility_hor_ver_x3_ex(const WS_CHAR *src, WS_S16 *dst, WS_U32 src_w, WS_U32 src_h, WS_U32 dst_stride, WS_U32 dst_h, WS_U16 valid, WS_U16 invalid);
WS_VOID utility_hor_ver_x2_ex(const WS_CHAR *src, WS_S16 *dst, WS_U32 src_w, WS_U32 src_h, WS_U32 dst_stride, WS_U32 dst_h, WS_U16 valid, WS_U16 invalid);
WS_VOID utility_hor_ver_x4_ex(const WS_CHAR *src, WS_S16 *dst, WS_U32 src_w, WS_U32 src_h, WS_U32 dst_stride, WS_U32 dst_h, WS_U16 valid, WS_U16 invalid);


//---------------------------------------------- ˯�ߺ��� --------------------------------------
WS_ERR  utility_system(const WS_CHAR *cmd);
WS_VOID utility_sleep_ms(WS_U32 ms);    //˯�ߺ���

//�ɻ���˯�ߣ����߳������ʹ����ͨ˯�ߣ�����˯��ʱ��ܳ���Ҫ�����߳�ʱ�޷�Ѹ�ٻ��ѣ�����ʹ��ws_interuptable_sleep����Ѹ�ٻ��Ѻ��˳���purpose���ڳ������ʱ�����
ws_interuptable_sleep *utility_new_interuptable_sleep();

//--------------------------------------------- �̹߳��� --------------------------------------------------
//�̴߳��������̺߳���(ע�⣬���̺߳��������Ǵ����̵߳ĺ���)�ĵ�һ����� utility_save_pid_name(pthread_self(), getpid(), __FUNCTION__); ע���̵߳�PID�ͺ����������ڼ��
WS_ERR utility_creat_thread(ws_thread_work_type work_type, ws_thread_priority priority, ws_thread_func func, void *usr_para, pthread_t *thread_hand);
WS_ERR utility_creat_thread_detach(ws_thread_work_type work_type, ws_thread_priority priority, ws_thread_func func, void *usr_para, pthread_t *thread_hand);
WS_ERR utility_save_pid_name(pthread_t thread_hand, pid_t pid, const WS_CHAR *thr_func_name);
//�̻߳��գ���������֮��ű�ʾ�߳�ȷʵ�Ѿ��˳���
WS_ERR utility_retrieve_thread(pthread_t thread_hand);
WS_ERR utility_cancel_thread(pthread_t thread_hand);//Modified by peishunting 2014.12.18 start  - end
//---------------------------------------------- �ڴ���� --------------------------------------------------
//�ڴ���䡢�ͷţ�ws_memmory_purpose �Լ����������һ�·����Ŀ�ģ����ڵ������
WS_VOID *utility_malloc(const char *funcname,const char *filename,const char *p,ws_module_id caller_id, ws_memmory_purpose purpose, size_t size);
//�ڴ��ͷţ�����Ƿ�double free�����õ�ʱ���__FILE__��__FUNCTION__�������������ʱ��ö�λ
WS_ERR utility_free(const WS_CHAR *file, const WS_CHAR *function, WS_VOID *memory);

//----------------------------------------------- �ļ����� --------------------------------------------------
ws_txt_file_operate *utility_new_txt_file_operate();
ws_binary_file_operate *utility_new_binary_file_operate();
ws_xml_operate *utility_new_xml_operate();
ws_bmp_operate *utility_new_bmp_operate();

//------------------------------------------------ �����㷨 -------------------------------------------------
ws_md5_cnt *utility_new_md5_cnt();

//------------------------------------------------- ͬ���� --------------------------------------------------
//��������������ʱֱ��delete��������ʱ�����������֣�����������Է�����Է���
ws_lock *utility_new_lock(const WS_CHAR *lock_name);
ws_rw_lock *utility_new_rw_lock(const WS_CHAR *lock_name);  //Ĭ��д�߳����ȼ����ڶ��߳�

//------------------------------------------------- ʱ���ʽת�� --------------------------------------------
#if defined(_SUPPORT_TIME_TYPE_AND_STANDARD_)
 WS_ERR utility_get_time_buf_show_for_osd_chinese(char *show_time_buf,ws_soft::ws_gui_show_time_type show_time_type,ws_soft::ws_gui_time_standard time_standard);
 WS_ERR utility_get_time_buf_show_for_osd_english(char *show_time_buf,ws_soft::ws_gui_show_time_type show_time_type,ws_soft::ws_gui_time_standard time_standard);
 WS_ERR utility_get_time_buf_show_for_traditional_chinese(char *show_time_buf,ws_soft::ws_gui_show_time_type show_time_type,ws_soft::ws_gui_time_standard time_standard);
 WS_U32 change_twenty_four_to_twelve_standard(WS_U32 tm_hour);
#endif 

WS_ERR utility_linux_to_ws_time(time_t linux_time, ws_time_struct *ws_time);
WS_ERR utility_ws_to_linux_time(const ws_time_struct *ws_time, time_t *linux_time);
WS_S32 utility_cnt_delta_ms(const struct timeval *time1, const struct timeval *time2);  //����ʱ���ֵ��time1С��time2���ظ�
WS_U32 utility_cnt_interval_ms(const struct timeval *time1, const struct timeval *time2);   //����ʱ���ֵ������ֵ
WS_S32 utility_cmp_time(const struct timeval *time1, const struct timeval *time2);  //�Ƚϴ�С��time1С��time2���ظ�����ȷ���0��time1����time2������

WS_S32 utility_correct_time_same_day(const ws_time_struct *time1, const ws_time_struct *time2, WS_U32 delta);  

WS_ERR utility_get_month_day(const ws_time_struct *ws_time, int *day); //���㵱ǰʱ�������¹��ж�����

//----------------------------------------------- ��ʱ�� ------------------------------------------------------
//ע�ᶨʱ�������ص���caller_id ���øú�����ģ��ID��func_name��ע��Ļص����������ƣ�����������������Ե�ʱ������, interval_ms��ʾ�����������100����Ϊ��λ
//��func�����в��������ע��ͷ�ע�ắ��
WS_ERR utility_c_regist_timer(ws_module_id  caller_id, ws_timer_func func, const char *func_name, WS_U32 interval_ms, WS_BOOL work_once);
WS_ERR utility_c_unregist_timer(ws_timer_func func);

//ע�ᶨʱ�������ص���caller_id ���øú�����ģ��ID��objectΪ�̳�ws_timer_client��ӿں�Ķ���
//�ڴ������в��������ע��ͷ�ע�ắ��
WS_ERR utility_cpp_regist_timer(ws_module_id caller_id, ws_timer_client *client, const char *client_name, WS_U32 interval_ms, WS_BOOL work_once);
WS_ERR utility_cpp_unregist_timer(ws_timer_client *client);

//-------------------------------------------- ������� -----------------------------------------------------------
//����ָ���ָ�ģʽ�ͷֱ��ʸ������ڵ�ʵ����������
WS_ERR utility_cnt_div_real_rect(const ws_display_screen_info *screen_info, ws_real_rect *real_rect, size_t rect_dim);
//���������ת���ɾ�������
WS_ERR utility_cnt_real_rect(WS_U32 resol_w, WS_U32 resol_h, const ws_abstract_rect *abstract_rect, ws_real_rect *real_rect);
WS_BOOL utility_is_valid_rect(const ws_abstract_rect *abstract_rect);   //�жϳ��������Ƿ�Ϸ�

void utility_cnt_accumulate_rect(ws_abstract_rect &old_rect, const ws_abstract_rect *new_rect); //�����ۼ�����

//����ƫ������
WS_ERR utility_cnt_excursion_rect(ws_abstract_rect &old_rect, ws_real_rect &real_rect, const ws_abstract_coordinate *start, const ws_abstract_coordinate *stop);

//����Ŵ���С�ۻ�����
WS_ERR utility_cnt_amplification_rect(ws_abstract_rect &old_rect, ws_real_rect &real_rect, const ws_abstract_coordinate *coor);
WS_ERR utility_cnt_lessen_rect(ws_abstract_rect &old_rect, ws_real_rect &real_rect, const ws_abstract_coordinate *coor);

//�������ڽ������1000*1000��ģ�����ʵ�ߴ�ת���ɰٷֱȳߴ�
void utility_cnt_real_to_abstract(ws_abstract_rect &old_rect, ws_real_rect &real_rect);

//---------------------------------------- ���� ----------------------------------
WS_ERR utility_get_local_mac(char *mac);                    // change by linhh 20160725 

//---------------------------------------------- ������� ---------------------------------------------------------
//ע����϶���purpose�Լ������������ϵ���;������ѡ�������help��������˵������ϸ�ο�utility_sample��ʹ�÷���
WS_ERR utility_regist_diag(ws_diagnose_client *client, const WS_CHAR *purpose, const WS_CHAR *help);
WS_ERR utility_unregist_diag(ws_diagnose_client *client);

//------------------------------------------------���Ź��ӿ�------------------------------------------------------
//����ģ�����utility_registע�ῴ�Ź�������Ĳ���ΪID�ͷ�ֵ(��sΪ��λ)���ú�������һ��ָ�룬fetch_dog���������������
//ι���������������NULL��ʾע��ʧ��
WS_U32 *utility_regist_watch_dog(ws_module_id module_id, WS_U32 threshold);
WS_ERR utility_fetch_dog(WS_U32 *space_pointer);//ι������������utility_regist_watch_dog���صĲ������в���
WS_BOOL utility_check_need_reset(ws_module_id *module_id);//�������WS_TURE��id��ָʾ���ĸ�ģ������

//------------------------------------------------�쳣����ӿ�----------------------------------------------------
//��Ҫ��Ӧģ����Լ���������ݵ�utility�б��棬�������м���߳�����ȡ��Щ�쳣�������Ƿ��쳣���ø��µ�ʱ���Ҫ����

//��������ַ��ĺϷ���,һ��A-Za-z0-9_-
WS_ERR utility_char_legal_manager(const WS_CHAR *name_or_pwd);

/* hzg added check character validation 20150424 start */
//��������ַ��ĺϷ���,[A-Za-z0-9_-]and GB2312 Chinese character.
WS_ERR utility_check_normal_char_and_chinese(const WS_CHAR *name_or_pwd);
/* hzg added check character validation 20150424 end */

//add by liuyu date 2014-10-20 start
/*�������� ���ٶ�һ���������ݽ�������*/
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

