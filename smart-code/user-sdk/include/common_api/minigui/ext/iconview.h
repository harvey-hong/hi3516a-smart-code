/**
 * \file iconview.h
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
 * $Id: iconview.h,v 1.4 2005/02/16 02:59:57 snig Exp $
 *
 *             MiniGUI for Linux/uClinux, eCos, uC/OS-II, VxWorks, 
 *                     and ThreadX version 1.6.x
 *             Copyright (C) 2002-2005 Feynman Software.
 *             Copyright (C) 1998-2002 Wei Yongming.
 */

#ifndef EXT_ICONVIEW_H
#define EXT_ICONVIEW_H

#ifdef  __cplusplus
extern "C" {
#endif

    /**
     * \addtogroup mgext_fns
     * @{
     */

    /**
     * \addtogroup mgext_controls
     * @{
     */

    /**
     * \defgroup mgext_ctrl_iconview IconView control
     * @{
     */

#define CTRL_ICONVIEW       ("IconView")

/** Iconview return value */
#define IV_OKAY                 0
#define IV_ERR                  (-1)
#define IV_ERRSPACE             (-2)

typedef GHANDLE HIVITEM;

/** 
 * Structure of the iconview item info, contains information about an item.
 * This structure is used for creating or retrieving an item. 
 */
typedef struct _IVITEMINFO
{
    /**
     * the Index of the item
     */
    int nItem;

    /**
     * the bitmap icon of the item
     */
    PBITMAP bmp;

    /**
     * the text label of the item
     */
    const char *label;

    /** attached additional data of this item */
    DWORD addData;

    /**
     * reserved
     */
    DWORD dwFlags;

} IVITEMINFO;
typedef IVITEMINFO* PIVITEMINFO;

/** iconview icon flags, reserved */
#define IVFLAG_BITMAP	0x0001
#define IVFLAG_ICON	0x0002


/**
 * \fn int iconview_is_item_hilight (HWND hWnd, GHANDLE hivi)
 * \brief use this to whether an iconview item is hilighted.
 */
MGEXT_EXPORT int iconview_is_item_hilight (HWND hWnd, GHANDLE hivi);

/**
 * \fn DWORD iconview_get_item_bitmap (GHANDLE hivi)
 * \brief use this to get bitmap handle from an iconview item 
 */
MGEXT_EXPORT PBITMAP iconview_get_item_bitmap (GHANDLE hivi);

/**
 * \fn DWORD iconview_get_item_label (GHANDLE hivi)
 * \brief use this to get text label from an iconview item 
 */
MGEXT_EXPORT const char* iconview_get_item_label (GHANDLE hivi);

/** 
 * \fn DWORD iconview_get_item_adddata (GHANDLE hivi)
 * \brief use this to get additional data from an iconview item 
 */
MGEXT_EXPORT DWORD iconview_get_item_adddata (GHANDLE hivi);


    /**
     * \defgroup mgext_ctrl_iconview_styles Styles of iconview control
     * @{
     */

/* reserved */
#define IVS_NOTIFY              SVS_NOTIFY
#define IVS_UPNOTIFY            SVS_UPNOTIFY
#define IVS_AUTOSORT            SVS_AUTOSORT
#define IVS_LOOP                SVS_LOOP


    /** @} end of mgext_ctrl_iconview_styles */

    /**
     * \defgroup mgext_ctrl_iconview_msgs Messages of ListView control
     * @{
     */

/**
 *  \def IVM_ADDITEM
 *  \brief Adds a item to iconview. 
 *  
 *  \code 
 *  IVM_ADDITEM
 *  PIVITEMINFO p
 *
 *  p =(LPARAM)lParam;
 *  \endcode
 *
 *  \param p Pointes to a IVITEMINFO structure that contains the information of 
 *           the new item to be added. nItem member of the IVITEMINFO struct speficied 
 *           the item position in its parent item, beginning with zero.
 *
 *  \return Returns the handle of the new item if successful, or 0 otherwise.
 */
#define IVM_ADDITEM            0xF300

/**
 * \def IVM_SETITEMSIZE
 * \brief Sets the item width and height of an iconview control
 *
 * All the items have the same item size. This message should be sent
 * before you add items to iconview control.
 *
 * \code
 * IVM_SETITEMSIZE
 * int width;
 * int height;
 *
 * wParam = width;
 * lParam = height;
 * \endcode
 *
 * \param width  Width of an item.
 * \param height Height of an item.
 *
 * \return 0.
 */

#define IVM_SETITEMSIZE           0xF436


/**
 * the same common control messages as scrollview control
 */
#define IVM_RESETCONTENT        SVM_RESETCONTENT
#define IVM_DELITEM             SVM_DELITEM
#define IVM_SETITEMDRAW         SVM_SETITEMDRAW
#define IVM_SETCONTWIDTH        SVM_SETCONTWIDTH
#define IVM_SETCONTHEIGHT       SVM_SETCONTHEIGHT
#define IVM_SETITEMOPS          SVM_SETITEMOPS
#define IVM_GETMARGINS          SVM_GETMARGINS
#define IVM_SETMARGINS          SVM_SETMARGINS
#define IVM_GETLEFTMARGIN       SVM_GETLEFTMARGIN
#define IVM_GETTOPMARGIN        SVM_GETTOPMARGIN
#define IVM_GETRIGHTMARGIN      SVM_GETRIGHTMARGIN
#define IVM_GETBOTTOMMARGIN     SVM_GETBOTTOMMARGIN
#define IVM_GETVISIBLEWIDTH     SVM_GETVISIBLEWIDTH
#define IVM_GETVISIBLEHEIGHT    SVM_GETVISIBLEHEIGHT
#define IVM_GETCONTWIDTH        SVM_GETCONTWIDTH
#define IVM_GETCONTHEIGHT       SVM_GETCONTHEIGHT
#define IVM_SETCONTRANGE        SVM_SETCONTRANGE
#define IVM_GETCONTENTX         SVM_GETCONTENTX
#define IVM_GETCONTENTY         SVM_GETCONTENTY
#define IVM_SETCONTPOS          SVM_SETCONTPOS
#define IVM_GETCURSEL           SVM_GETCURSEL
#define IVM_SELECTITEM          SVM_SELECTITEM
#define IVM_SHOWITEM            SVM_SHOWITEM
#define IVM_CHOOSEITEM          SVM_CHOOSEITEM
#define IVM_SETCURSEL           SVM_SETCURSEL
#define IVM_SETITEMINIT         SVM_SETITEMINIT
#define IVM_SETITEMDESTROY      SVM_SETITEMDESTROY
#define IVM_SETITEMCMP          SVM_SETITEMCMP
#define IVM_MAKEPOSVISIBLE      SVM_MAKEPOSVISIBLE
#define IVM_GETHSCROLLVAL       SVM_GETHSCROLLVAL
#define IVM_GETVSCROLLVAL       SVM_GETVSCROLLVAL
#define IVM_GETHSCROLLPAGEVAL   SVM_GETHSCROLLPAGEVAL
#define IVM_GETVSCROLLPAGEVAL   SVM_GETVSCROLLPAGEVAL
#define IVM_SETSCROLLVAL        SVM_SETSCROLLVAL
#define IVM_SETSCROLLPAGEVAL    SVM_SETSCROLLPAGEVAL
#define IVM_SORTITEMS           SVM_SORTITEMS
#define IVM_GETITEMCOUNT        SVM_GETITEMCOUNT
#define IVM_GETITEMADDDATA      SVM_GETITEMADDDATA
#define IVM_SETITEMADDDATA      SVM_SETITEMADDDATA
#define IVM_REFRESHITEM         SVM_REFRESHITEM
#define IVM_GETFIRSTVISIBLEITEM SVM_GETFIRSTVISIBLEITEM

    /** @} end of mgext_ctrl_iconview_msgs */


    /**
     * \defgroup mgext_ctrl_iconview_ncs Notification code of IconView control
     * @{
     */

#define IVN_CLICKED            SVN_CLICKED
#define IVN_SELCHANGED         SVN_SELCHANGED


    /** @} end of mgext_ctrl_iconview_ncs */

    /** @} end of mgext_ctrl_iconview */

    /** @} end of mgext_controls */

    /** @} end of mgext_fns */

#ifdef  __cplusplus
}
#endif

#endif /* EXT_ICONVIEW_H */

