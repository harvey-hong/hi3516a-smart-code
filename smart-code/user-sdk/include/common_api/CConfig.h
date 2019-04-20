#ifndef _INC_CCONFIG_499BC98601C8_INCLUDED
#define _INC_CCONFIG_499BC98601C8_INCLUDED

#include <stdio.h>
#include <pthread.h>
#include "idvr_errno.h"

//!\brief   参数管理模块    配置文件读写类
class CConfig
{
public:
    //!\brief   获取dvr配置实例
    //!\return  dvr配置的实例指针
    static CConfig *GetInstance();

    // linhaihong change start
    /*
     Modified by lhh, at 2014-07-25 13:28:30
     reason: get config file for default configure
    */
    static CConfig *GetDefaultInstance(const char *pszFileName);

    /*
     Modified by lhh, at 2014-07-25 13:30:02
     reason: get version file for configure
    */
    static CConfig *GetVerInstance(const char *pszFileName);

    /*
     Modified by lhh, at 2014-07-25 13:30:44
     reason: get ISP Param file for configure
    */
    static CConfig *GetISPInstance(const char *pszFileName);
    // linhaihong change end

    /*
     Modified by liuy, at 2016-01-12
     reason: get USR Param file for configure
    */
    static CConfig *GetUSERInstance(const char *pszFileName);
    // liuy change end

    //!\brief   获取配置参数
    //!\param   pszSection      区段名
    //!\param   pszKey          关键字名
    //!\param   nDefault        缺省值
    //!\return  返回整形参数值
    int GetValue(const char *pszSection, const char *pszKey, int nDefault);

    //!\brief   设置配置参数
    //!\param   pszSection      区段名
    //!\param   pszKey          关键字名
    //!\param   nValue          整形参数值
    //!\return  0表示成功，其它为错误码
    int SetValue(const char *pszSection, const char *pszKey, int nValue);

    //add by liuy date 2016-01-12 start
    //!\brief   删除配置，只支持整区段删除
    //!\param   pszSection      区段名
    //!\return  0表示成功，其它为错误码
    int DelValue(const char *pszSection);

    //!\brief   根据编号获取区段名
    //!\param   pszSection      区段名存储地址
    //!\param   pszSection_size      区段名存储地址可用长度
    //!\param   idx      想要获取的区段编号
    //!\return  0表示成功，其它为错误码
    int GetSectionByIdx(char *pszSection, size_t pszSection_size, int idx);

    //!\brief   获取区段名是否存在
    //!\param   pszSection      区段名
    //!\return  1表示存在，0表示不存在
    int GetSectionExist(const char *pszSection);
    //add by liuy date 2016-01-12 end

    //!\brief   释放配置信息内存空间
    //!\return  0表示成功，其它为错误码
    int UnloadFile();

    //!\brief   恢复默认配置,本函数只用于配置文件已正常加载情况下的恢复参数
    //!恢复默认前会备份先前加载的配置文件,备份文件名为文件名+-bak
    //!\param   pszDefFileName      默认配置文件名称（含路径）
    //!\param   pszFlagFile 标记不恢复的项的文件
    //!\return  0表示成功，其它为错误码
    int ResumeDefCfg(const char *pszDefFileName, const char *pszFlagFile = NULL);

    //!\brief 升级配置文件
    //! 升级配置文件前会备份先前加载的配置文件，备份文件名为文件名+-bak
    //!\param pszNewCfgFileName 升级的配置文件名称
    //!\param pszFlagFile 标记更新的项的文件,为NULL则将新配置文件中的值添加到原配置文件中
    //!\return 0表示成功,其他为错误码
    int UpdateCfg(const char *pszNewCfgFileName, const char *pszFlagFile = NULL);

    //!\brief   获取新实例
    //!\return  新的实例指针
    static CConfig *NewInstance();

    //!\brief   释放实例
    static void ReleaseInstance(CConfig *pInstance);

    //!\brief   读取配置文件
    //!         自动识别文件类型
    //!\param   pszFileName     配置文件名称（含路径）
    //!\return  0表示成功，其它为错误码
    int LoadFile(const char *pszFileName);

    //!\brief   保存配置信息到原文件
    //!\return  0表示成功，其它为错误码
    int SaveFile();

    //!\brief   获取配置参数
    //!\param   pszSection      区段名
    //!\param   pszKey          关键字名
    //!\param   pszDefault      缺省值
    //!\param   pValue          返回字符串型参数值
    //!\param   nSize           buf空间大小
    //!\return
    //本接口字符串型参数值到pValue指向的buf，并返回pValue
    char *GetValue(const char *pszSection, const char *pszKey, const char *pszDefault, char *pValue, int nSize);

    //!\brief   设置配置参数
    //!\param   pszSection      区段名
    //!\param   pszKey          关键字名
    //!\param   pValue          字符串型参数值
    //!\return  0表示成功，其它为错误码
    int SetValue(const char *pszSection, const char *pszKey, const char *pValue);

    //!\brief   另存配置信息到其它文件
    //!\param   pszFileName     配置文件名称（含路径）
    //!\return  0表示成功，其它为错误码
    int SaveAsFile(const char *pszFileName);

protected:
    CConfig();

    CConfig(CConfig &cfg);

    ~CConfig();

    //!\brief   读取ini文件
    //!         自动识别文件完整性
    //!\param   pszFileName     配置文件名称（含路径）
    //!\return  0表示成功，其它为错误码
    int LoadIniFile(const char *pszFileName);

    //!\brief   保存配置信息到Ini文件
    //!\param   pszFileName     配置文件名称（含路径）
    //!\return  0表示成功，其它为错误码
    int SaveIniFile(const char *pszFileName);

public:
    struct tagSection;
private:
    //!\brief 读取一个section
    //!\param fp 文件指针
    //!\param pSect section指针
    //!\return 0表示读取正确，其他表示错误码
    //!\sa ENCONFIG 错误码
    int ReadIniSection(FILE *fp, tagSection *pSect);

    //!\brief 从配置文件的一行中获取section名称
    //!\param pszSectionName section名称缓冲区指针
    //!\param szBuf 一行字符串
    //!\return 0表示获取成功,其他表示获取失败
    int GetIniSectionName(char **pszSectionName, char *szBuf);

    //!\brief 从配置文件的一行获取key名称和值
    //!\param szBuf 一行字符串
    //!\param pszKey key名字符串缓冲区指针
    //!\param pszValue key值字符串缓冲区指针
    //!\return 0表示获取成功 其他表示获取失败
    int GetIniKey(char *szBuf, char **pszKey, char **pszValue);

    //!\brief 释放加载过程中占用的内存空间
    int FreeMemory();

    //!\brief 查找一个section
    //!\param pszSection section名
    //!\return NULL表示查找失败 其他表示section指针
    tagSection *SearchSection(const char *pszSection);

    //!\brief   获取配置参数
    //!\param   pszSection      区段名
    //!\param   pszKey          关键字名
    //!\param   pszDefault      缺省值
    //!\param   pValue          返回字符串型参数值
    //!\param   nSize           buf空间大小
    //!\return
    //本接口字符串型参数值到pValue指向的buf，并返回pValue
    char *InternalGetValue(const char *pszSection, const char *pszKey, const char *pszDefault, char *pValue, int nSize);

    //!\brief   设置配置参数
    //!\param   pszSection      区段名
    //!\param   pszKey          关键字名
    //!\param   pValue          字符串型参数值
    //!\return  0表示成功，其它为错误码
    int InternalSetValue(const char *pszSection, const char *pszKey, const char *pValue);

    //!\brief 备份文件
    static int BackupFile(const char *pszFileName);

    //!\brief 添加新的section,内容为空
    tagSection *AddSection();
    //add by liuy date 2016-01-12 start
    //!\brief   删除配置，只支持整区段删除
    int DelSection(const char *pszSection);

    //!\param   pszSection      区段名存储地址
    //!\param   pszSection_size      区段名存储地址可用长度
    //!\param   idx      想要获取的区段编号
    int GetSection(char *pszSection, size_t pszSection_size, int idx);
    //add by liuy date 2016-01-12 end
    tagSection *InsertSection();

    static int Lock();

    static int Unlock();

private:
    static CConfig  *m_pEdvrCfg;                    // 正常缺省文件

    // linhaihong change start
    static CConfig  *m_pDefaultCfg;                 // 缺省配置文件
    static CConfig  *m_pVerCfg;                     // 版本配置文件
    static CConfig  *m_pISPCfg;                     // ISP配置文件
    // linhaihong change end
    // liuy change start
    static CConfig  *m_pUSRCfg;                     // USR配置文件
    // liuy change end

    static char *m_strCfgFile;
    char *m_strFile;
    tagSection *m_pSection;
    int m_nSectionCount;
    int m_nType;
    int m_nCurrentLine;
    static pthread_mutex_t m_mtxConfig;
};

#endif                          /* __CONFIG_H_ */
