/**
 * \file newfiledlg.h
 * \author Wei Yongming <ymwei@minigui.org>
 * \date 2004/05/09
 * 
 *  This file includes interfaces of new Open File Dialog Box.
 *
 \verbatim
    Copyright (C) 2002-2005 Feynman Software
    Copyright (C) 1998-2002 Wei Yongming

    This file is part of MiniGUI, a compact cross-platform Graphics 
    User Interface (GUI) support system for real-time embedded systems.

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

    If you are using MiniGUI for developing commercial, proprietary, or other
    software not covered by the GPL terms, you must have a commercial license
    for MiniGUI. Please see http://www.minigui.com/product/index.html for 
    how to obtain this. If you are interested in the commercial MiniGUI 
    licensing, please write to sales@minigui.com. 

 \endverbatim
 */

/*
 * $Id: newfiledlg.h,v 1.11 2005/09/04 06:03:54 weiym Exp $
 *
 *             MiniGUI for Linux/uClinux, eCos, uC/OS-II, VxWorks, 
 *                     and ThreadX version 1.6.x
 *             Copyright (C) 2002-2005 Feynman Software.
 *             Copyright (C) 1998-2002 Wei Yongming.
 */

#ifndef _MGUI_NEWFILEDLG_H
#define _MGUI_NEWFILEDLG_H
#ifndef WIN32
#include <sys/types.h>
#include <dirent.h>
#endif
#ifdef __cplusplus
extern "C" {
#endif  /* __cplusplus */

    /**
     * \addtogroup mywins_fns Interfaces of MyWins module of MiniGUIExt library
     * @{
     */

    /**
     * \defgroup mywins_newfiledlg Open File Dialog Box
     * @{
     */

#define FILE_ERROR_OK           0
#define FILE_ERROR_PARAMERR     -1
#define FILE_ERROR_PATHNOTEXIST -2
#define MAX_FILTER_LEN          255

#define MY_NAMEMAX      127
#define MY_PATHMAX      255
/**
 * The file dialog box structure used by \a ShowOpenDialog.
 * \sa ShowOpenDialog.
 */
typedef struct _NEWFILEDLGDATA
{
    /** indicates to create a Save File or an Open File dialog box. */
    BOOL    IsSave;
    /** the full path name of the file returned. */
    char    filefullname[MY_NAMEMAX + MY_PATHMAX + 1];
    /** the name of the file to be opened. */
    char    filename[MY_NAMEMAX + 1];
    /** the initial path of the dialog box. */
    char    filepath[MY_PATHMAX + 1];
    /**
     * the filter string, for example: 
     * All file (*.*)|Text file (*.txt;*.TXT)
     */
    char    filter[MAX_FILTER_LEN + 1];
    /** the initial index of the filter*/
    int     filterindex;
} NEWFILEDLGDATA;

typedef NEWFILEDLGDATA* PNEWFILEDLGDATA;

/**
 * \fn int ShowOpenDialog (HWND hWnd, int lx, int ty, 
                int w, int h, PNEWFILEDLGDATA pnfdd)
 * \brief Creates an Open File Dialog Box.
 *
 * This function creates an Open File Dialog Box, and returns 
 * the full path name of the file selected by user.
 *
 * \param hWnd The hosting main window.
 * \param lx lx,ty,w,h: The default position and size of the dialog box.
 * \param ty lx,ty,w,h: The default position and size of the dialog box.
 * \param w  lx,ty,w,h: The default position and size of the dialog box.
 * \param h  lx,ty,w,h: The default position and size of the dialog box.
 * \param pnfdd The pointer to the NEWFILEDLGDATA structure.
 *
 * \retval IDOK The user choosed a file and OK button clicked.
 * \retval IDCANCLE CANCEL button clicked.
 * 
 * \sa NEWFILEDLGDATA, ShowOpenDialog
 */
MGEXT_EXPORT int ShowOpenDialog (HWND hWnd, int lx, int ty, 
                int w, int h, PNEWFILEDLGDATA pnfdd);

    /** @} end of mywins_newfiledlg */

    /** @} end of mywins_fns */

#ifdef __cplusplus
}
#endif  /* __cplusplus */

#endif /* _MGUI_NEWFILEDLG_H */


