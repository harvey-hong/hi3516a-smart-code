/**
 * \file mgext.h
 * \author Wei Yongming <ymwei@minigui.org>
 * \date 2002/01/06
 * 
 * The header file of MiniGUI extension library.
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
 * $Id: mgext.h,v 1.119 2005/09/04 06:03:54 weiym Exp $
 *
 *             MiniGUI for Linux/uClinux, eCos, uC/OS-II, VxWorks, 
 *                     and ThreadX version 1.6.x
 *             Copyright (C) 2002-2005 Feynman Software.
 *             Copyright (C) 1998-2002 Wei Yongming.
 */

#ifndef MGEXT_H
#define MGEXT_H

#ifdef  __cplusplus
extern "C" {
#endif

    /**
     * \addtogroup mgext_fns Interfaces of the MiniGUI extension 
     *             library (libmgext)
     * @{
     */

/**
 * \fn BOOL InitMiniGUIExt (void)
 * \brief Initializes MiniGUI extension library.
 *
 * This function initializes MiniGUI extension library. You should call
 * this function before using any API provided by MiniGUIExt library.
 *
 * \return This function returns TRUE when success, otherwise FALSE.
 *
 * \sa MiniGUIExtCleanUp
 */
MGEXT_EXPORT BOOL InitMiniGUIExt (void);

/**
 * \fn MiniGUIExtCleanUp (void)
 * \brief Cleans up the MiniGUI extension library.
 *
 * This function cleans up the MiniGUI extension library. You should call
 * this function when you no longer use APIs provided by MiniGUIExt library.
 *
 * \sa InitMiniGUIExt
 */
MGEXT_EXPORT void MiniGUIExtCleanUp (void);

    /**
     * \addtogroup mgext_controls Controls defined in libmgext
     * @{
     */

    /** @} end of mgext_controls */

    /** @} end of mgext_fns */

#ifdef _EXT_CTRL_SPINBOX
#include "ext/spinbox.h"
#endif /* _EXT_CTRL_SPINBOX */

#ifdef _EXT_CTRL_MONTHCAL
#include "ext/monthcal.h"
#endif /* _EXT_CTRL_MONTHCAL */

#ifdef _EXT_CTRL_COOLBAR
#include "ext/coolbar.h"
#endif /* _CTRL_COOLBAR */

#ifdef _EXT_CTRL_LISTVIEW
#include "ext/listview.h"
#include "ext/listview_ex.h"
#endif  /* _EXT_CTRL_LISTVIEW */

#ifdef _EXT_CTRL_TREEVIEW
#include "ext/treeview.h"
#endif /* _EXT_CTRL_TREEVIEW */

#ifdef _EXT_CTRL_GRIDVIEW
#include "ext/gridview.h"
#endif /* _EXT_CTRL_GRIDVIEW */

#ifdef _EXT_CTRL_ICONVIEW
#include "ext/iconview.h"
#endif  /* _EXT_CTRL_ICONVIEW */

#ifdef _EXT_CTRL_ANIMATION
#include "ext/animation.h"
#endif  /* _EXT_CTRL_ANIMATION */

#ifdef  __cplusplus
}
#endif

#endif /* MGEXT_H */

