/*!
* @file
*  UserRightCheck.h
* @brief
*  �û�Ȩ�޼��
* @author
*  Cheng Yanfang
* @date
*  2010��11��3��
* @version
*  1.0.0
*/

#ifndef RTSP_USER_RINGHT_CHECK_H

#define RTSP_USER_RINGHT_CHECK_H

#include "./HYRtspCommon.h"

namespace ApplicationLayer
{
/*!
* \class CUserRightCheck
* \brief �û�Ȩ�޼��
*/
class CUserRightCheck
{
public:
    CUserRightCheck();
    ~CUserRightCheck();

    int RightCheck(char *pUserName, eRtspStreamType eStreamType, int nChannel);

private:

};

}

#endif
