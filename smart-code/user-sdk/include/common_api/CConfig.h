#ifndef _INC_CCONFIG_499BC98601C8_INCLUDED
#define _INC_CCONFIG_499BC98601C8_INCLUDED

#include <stdio.h>
#include <pthread.h>
#include "idvr_errno.h"

//!\brief   ��������ģ��    �����ļ���д��
class CConfig
{
public:
    //!\brief   ��ȡdvr����ʵ��
    //!\return  dvr���õ�ʵ��ָ��
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

    //!\brief   ��ȡ���ò���
    //!\param   pszSection      ������
    //!\param   pszKey          �ؼ�����
    //!\param   nDefault        ȱʡֵ
    //!\return  �������β���ֵ
    int GetValue(const char *pszSection, const char *pszKey, int nDefault);

    //!\brief   �������ò���
    //!\param   pszSection      ������
    //!\param   pszKey          �ؼ�����
    //!\param   nValue          ���β���ֵ
    //!\return  0��ʾ�ɹ�������Ϊ������
    int SetValue(const char *pszSection, const char *pszKey, int nValue);

    //add by liuy date 2016-01-12 start
    //!\brief   ɾ�����ã�ֻ֧��������ɾ��
    //!\param   pszSection      ������
    //!\return  0��ʾ�ɹ�������Ϊ������
    int DelValue(const char *pszSection);

    //!\brief   ���ݱ�Ż�ȡ������
    //!\param   pszSection      �������洢��ַ
    //!\param   pszSection_size      �������洢��ַ���ó���
    //!\param   idx      ��Ҫ��ȡ�����α��
    //!\return  0��ʾ�ɹ�������Ϊ������
    int GetSectionByIdx(char *pszSection, size_t pszSection_size, int idx);

    //!\brief   ��ȡ�������Ƿ����
    //!\param   pszSection      ������
    //!\return  1��ʾ���ڣ�0��ʾ������
    int GetSectionExist(const char *pszSection);
    //add by liuy date 2016-01-12 end

    //!\brief   �ͷ�������Ϣ�ڴ�ռ�
    //!\return  0��ʾ�ɹ�������Ϊ������
    int UnloadFile();

    //!\brief   �ָ�Ĭ������,������ֻ���������ļ���������������µĻָ�����
    //!�ָ�Ĭ��ǰ�ᱸ����ǰ���ص������ļ�,�����ļ���Ϊ�ļ���+-bak
    //!\param   pszDefFileName      Ĭ�������ļ����ƣ���·����
    //!\param   pszFlagFile ��ǲ��ָ�������ļ�
    //!\return  0��ʾ�ɹ�������Ϊ������
    int ResumeDefCfg(const char *pszDefFileName, const char *pszFlagFile = NULL);

    //!\brief ���������ļ�
    //! ���������ļ�ǰ�ᱸ����ǰ���ص������ļ��������ļ���Ϊ�ļ���+-bak
    //!\param pszNewCfgFileName �����������ļ�����
    //!\param pszFlagFile ��Ǹ��µ�����ļ�,ΪNULL���������ļ��е�ֵ��ӵ�ԭ�����ļ���
    //!\return 0��ʾ�ɹ�,����Ϊ������
    int UpdateCfg(const char *pszNewCfgFileName, const char *pszFlagFile = NULL);

    //!\brief   ��ȡ��ʵ��
    //!\return  �µ�ʵ��ָ��
    static CConfig *NewInstance();

    //!\brief   �ͷ�ʵ��
    static void ReleaseInstance(CConfig *pInstance);

    //!\brief   ��ȡ�����ļ�
    //!         �Զ�ʶ���ļ�����
    //!\param   pszFileName     �����ļ����ƣ���·����
    //!\return  0��ʾ�ɹ�������Ϊ������
    int LoadFile(const char *pszFileName);

    //!\brief   ����������Ϣ��ԭ�ļ�
    //!\return  0��ʾ�ɹ�������Ϊ������
    int SaveFile();

    //!\brief   ��ȡ���ò���
    //!\param   pszSection      ������
    //!\param   pszKey          �ؼ�����
    //!\param   pszDefault      ȱʡֵ
    //!\param   pValue          �����ַ����Ͳ���ֵ
    //!\param   nSize           buf�ռ��С
    //!\return
    //���ӿ��ַ����Ͳ���ֵ��pValueָ���buf��������pValue
    char *GetValue(const char *pszSection, const char *pszKey, const char *pszDefault, char *pValue, int nSize);

    //!\brief   �������ò���
    //!\param   pszSection      ������
    //!\param   pszKey          �ؼ�����
    //!\param   pValue          �ַ����Ͳ���ֵ
    //!\return  0��ʾ�ɹ�������Ϊ������
    int SetValue(const char *pszSection, const char *pszKey, const char *pValue);

    //!\brief   ���������Ϣ�������ļ�
    //!\param   pszFileName     �����ļ����ƣ���·����
    //!\return  0��ʾ�ɹ�������Ϊ������
    int SaveAsFile(const char *pszFileName);

protected:
    CConfig();

    CConfig(CConfig &cfg);

    ~CConfig();

    //!\brief   ��ȡini�ļ�
    //!         �Զ�ʶ���ļ�������
    //!\param   pszFileName     �����ļ����ƣ���·����
    //!\return  0��ʾ�ɹ�������Ϊ������
    int LoadIniFile(const char *pszFileName);

    //!\brief   ����������Ϣ��Ini�ļ�
    //!\param   pszFileName     �����ļ����ƣ���·����
    //!\return  0��ʾ�ɹ�������Ϊ������
    int SaveIniFile(const char *pszFileName);

public:
    struct tagSection;
private:
    //!\brief ��ȡһ��section
    //!\param fp �ļ�ָ��
    //!\param pSect sectionָ��
    //!\return 0��ʾ��ȡ��ȷ��������ʾ������
    //!\sa ENCONFIG ������
    int ReadIniSection(FILE *fp, tagSection *pSect);

    //!\brief �������ļ���һ���л�ȡsection����
    //!\param pszSectionName section���ƻ�����ָ��
    //!\param szBuf һ���ַ���
    //!\return 0��ʾ��ȡ�ɹ�,������ʾ��ȡʧ��
    int GetIniSectionName(char **pszSectionName, char *szBuf);

    //!\brief �������ļ���һ�л�ȡkey���ƺ�ֵ
    //!\param szBuf һ���ַ���
    //!\param pszKey key���ַ���������ָ��
    //!\param pszValue keyֵ�ַ���������ָ��
    //!\return 0��ʾ��ȡ�ɹ� ������ʾ��ȡʧ��
    int GetIniKey(char *szBuf, char **pszKey, char **pszValue);

    //!\brief �ͷż��ع�����ռ�õ��ڴ�ռ�
    int FreeMemory();

    //!\brief ����һ��section
    //!\param pszSection section��
    //!\return NULL��ʾ����ʧ�� ������ʾsectionָ��
    tagSection *SearchSection(const char *pszSection);

    //!\brief   ��ȡ���ò���
    //!\param   pszSection      ������
    //!\param   pszKey          �ؼ�����
    //!\param   pszDefault      ȱʡֵ
    //!\param   pValue          �����ַ����Ͳ���ֵ
    //!\param   nSize           buf�ռ��С
    //!\return
    //���ӿ��ַ����Ͳ���ֵ��pValueָ���buf��������pValue
    char *InternalGetValue(const char *pszSection, const char *pszKey, const char *pszDefault, char *pValue, int nSize);

    //!\brief   �������ò���
    //!\param   pszSection      ������
    //!\param   pszKey          �ؼ�����
    //!\param   pValue          �ַ����Ͳ���ֵ
    //!\return  0��ʾ�ɹ�������Ϊ������
    int InternalSetValue(const char *pszSection, const char *pszKey, const char *pValue);

    //!\brief �����ļ�
    static int BackupFile(const char *pszFileName);

    //!\brief ����µ�section,����Ϊ��
    tagSection *AddSection();
    //add by liuy date 2016-01-12 start
    //!\brief   ɾ�����ã�ֻ֧��������ɾ��
    int DelSection(const char *pszSection);

    //!\param   pszSection      �������洢��ַ
    //!\param   pszSection_size      �������洢��ַ���ó���
    //!\param   idx      ��Ҫ��ȡ�����α��
    int GetSection(char *pszSection, size_t pszSection_size, int idx);
    //add by liuy date 2016-01-12 end
    tagSection *InsertSection();

    static int Lock();

    static int Unlock();

private:
    static CConfig  *m_pEdvrCfg;                    // ����ȱʡ�ļ�

    // linhaihong change start
    static CConfig  *m_pDefaultCfg;                 // ȱʡ�����ļ�
    static CConfig  *m_pVerCfg;                     // �汾�����ļ�
    static CConfig  *m_pISPCfg;                     // ISP�����ļ�
    // linhaihong change end
    // liuy change start
    static CConfig  *m_pUSRCfg;                     // USR�����ļ�
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
