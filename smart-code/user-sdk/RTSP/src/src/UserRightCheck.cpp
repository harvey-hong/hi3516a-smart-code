#include "../inc/template/TSingletons.h"
#include "../inc/GlobalObject.h"
#include "../inc/InternalCommon.h"
#include "../inc/UserRightCheck.h"


namespace ApplicationLayer
{
CUserRightCheck::CUserRightCheck()
{
}

CUserRightCheck::~CUserRightCheck()
{
}

//\\ ͨ���ص���ȡ�ϲ��û������ж�ָ���û��Ƿ���ʵʱ��������ʷ���ķ���Ȩ��
int CUserRightCheck::RightCheck(char *pUserName, eRtspStreamType eStreamType, int nChannel)
{
#if 0

    if (NULL == pUserName || nChannel < 0 || nChannel >= MAX_CHANNEL_NUMBER)
    {
        return RET_FAIL;
    }

    if (eStreamType <= eRtspStreamTypeBegin || eStreamType >= eRtspStreamTypeEnd)
    {
        return RET_FAIL;
    }

    int nRet = RET_SUCCESS;
    HY_DVR_USER_CFG cUser;
    memset(&cUser, 0, sizeof(cUser));
    DWORD dwBufSize = sizeof(cUser);
    DWORD dwUserID = ApplicationLayer::TSingletons<CGlobalObject>::Instance().UserID();
    if (RET_SUCCESS != nRet || dwBufSize != sizeof(cUser))
    {
        return RET_FAIL;
    }

    if (cUser.bValid)
    {
        int nIndex;

        for (nIndex = 0; nIndex < DVR_MAX_USER_NUM; nIndex++)
        {
            if (cUser.struUser[nIndex].bValid && 0 == strcmp(cUser.struUser[nIndex].szUserName, pUserName))
            {
                if (eRtspStreamHistory == eStreamType)
                {
                    if (cUser.struUser[nIndex].struUserRight.nChannelRight[4] & (1 << nChannel))
                    {
                        return RET_SUCCESS;
                    }
                }
                else
                {
                    if (cUser.struUser[nIndex].struUserRight.nChannelRight[5] & (1 << nChannel))
                    {
                        return RET_SUCCESS;
                    }
                }

                break;
            }
        }
    }

    return RET_FAIL;
#endif
    return RET_SUCCESS;
}
}

