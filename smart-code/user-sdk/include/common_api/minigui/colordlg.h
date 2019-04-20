/**
 * \file colordlg.h
 * \author Linxs <Linxs@minigui.net>
 * \date 2004/6/16
 * 
 *  This file includes interfaces of Color Selection Dialog Box.
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
 * $Id: colordlg.h,v 1.11 2005/09/04 06:03:54 weiym Exp $
 *
 *             MiniGUI for Linux/uClinux, eCos, uC/OS-II, VxWorks, 
 *                     and ThreadX version 1.6.x
 *             Copyright (C) 2002-2005 Feynman Software.
 *             Copyright (C) 1998-2002 Wei Yongming.
 */

#ifndef _MGUI_COLORDLG_H
#define _MGUI_COLORDLG_H

#ifdef __cplusplus
extern "C" {
#endif  /* __cplusplus */

#ifdef _USE_NEWGAL

    /**
     * \addtogroup mywins_fns Interfaces of MyWins module of MiniGUIExt library
     * @{
     */

    /**
     * \defgroup mywins_colorseldlg Color Selection Dialog Box
     * @{
     */

/**
 * The color data structure used by \a ColorSelDialog.
 * \sa ColorSelDialog.
 */
typedef struct _COLORDATA {
    /** reserves, not used now. */
    DWORD           style;
    /** the value of the color  returned. */
    gal_pixel       pixel;
    /** the R, G, B value of the color returned. */
    Uint8           r, g, b;
    /** the H, S, V value of the color returned. */
    Uint16          h;
    Uint8           s, v;
} COLORDATA, *PCOLORDATA;

#define SELCOLOR_OK     IDOK
#define SELCOLOR_CANCEL IDCANCEL

#include "colorspace.h"

/**
 * \fn int ColorSelDialog (HWND hWnd, int x, int y, 
                int w, int h, PCOLORDATA pClrData)
 * \brief Creates a Color Selection Dialog Box.
 *
 * This function creates a Color Selection Dialog Box, and returns 
 * the values of the color selected by the user.
 *
 * \param hWnd The hosting main window.
 * \param x  x,y,w,h: The default position and size of the dialog box.
 * \param y  x,y,w,h: The default position and size of the dialog box.
 * \param w  x,y,w,h: The default position and size of the dialog box.
 * \param h  x,y,w,h: The default position and size of the dialog box.
 * \param pClrData The pointer to the COLORDATA structure.
 *
 * \retval IDOK     The user choosed a color and OK button clicked.
 * \retval IDCANCEL The user clicked the Cancel button.
 * 
 * \sa COLORDATA, ColorSelDialog
 */
MGEXT_EXPORT int ColorSelDialog (HWND hWnd, int x, int y, 
                int w, int h, PCOLORDATA pClrData);

    /** @} end of mywins_colorseldlg*/

    /** @} end of mywins_fns */

#endif /* _USE_NEWGAL */

#ifdef __cplusplus
}
#endif  /* __cplusplus */

#endif /* _MGUI_COLORDLG_H */


