/*!
* @file
*  UserRightCheck.h
* @brief
*  用户权限检查
* @author
*  Cheng Yanfang
* @date
*  2010年11月3日
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
* \brief 用户权限检查
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
