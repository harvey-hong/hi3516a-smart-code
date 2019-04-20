/**
 * \file listview.h
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
 * $Id: listview.h,v 1.6 2005/09/04 06:58:21 jpzhang Exp $
 *
 *             MiniGUI for Linux/uClinux, eCos, uC/OS-II, VxWorks, 
 *                     and ThreadX version 1.6.x
 *             Copyright (C) 2002-2005 Feynman Software.
 *             Copyright (C) 1998-2002 Wei Yongming.
 */

#ifndef EXT_LISTVIEW_H
#define EXT_LISTVIEW_H

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
     * \defgroup mgext_ctrl_listview ListView control
     * @{
     */

#define CTRL_LISTVIEW       ("ListView")

/** Listview return value */
#define LV_OKAY                 0
#define LV_ERR                  (-1)
#define LV_ERRSPACE             (-2)


typedef GHANDLE HLVITEM;

/** list view item flags */
#define LVIF_FOLD               0x0001L

/** 
 * Structure of the listview item info, contains information about an item.
 * This structure is used for creating or retrieving an item. 
 */
typedef struct _LVITEM
{
    /**
     * the rows of the item
     */
    int nItem;
    /** height of the item */
    int nItemHeight;
    /** attached additional data of this item */
    DWORD itemData;

    /**
     * State flags of the item, can be OR'ed by the following values:
     *
     * - LVIF_FOLD\n
     *   The item is folded.
     *
     * When adding an item to the listview control, only LVIF_FOLD
     * flag is valid.
     */
    DWORD dwFlags;

} LVITEM;
typedef LVITEM *PLVITEM;

/** listview icon flags */
#define LVFLAG_BITMAP	0x0001
#define LVFLAG_ICON	    0x0002

/** 
 * Struct of the listview subitem info, contains information about a subitem.
 * This structure is used for creating or retrieving a subitem.
 */ 
typedef struct _LVSUBITEM
{
    /** flags of the subitem, can be OR'ed by the following values:
     *
     * - LVFLAG_BITMAP
     *   The sub item has a bitmap icon.
     * - LVFLAG_ICON
     *   The sub item has an icon.
     */
    DWORD flags;
    /** the Subitem vertical position(rows) */
    int nItem;
    /** the Subitem horizontal position(columns) */
    int subItem;
    /** text content of this subitem */
    char *pszText;
    /** max text len */
    int nTextMax;
    /** text color of the subitem */
    int nTextColor;
    /** image of the subitem, can be bitmap or icon, determined by flags */
    DWORD image; 
} LVSUBITEM;
typedef LVSUBITEM *PLVSUBITEM;

/** Contains information for sorting listview */
typedef struct _LVSORTDATA
{
    /** Sorting column index */
    int ncol;
    /** low sorted or high sorted */
    int losorted;
    /** listview handle */
    HWND hLV;
} LVSORTDATA;
typedef LVSORTDATA *PLVSORTDATA;

/** type of listview comparision fuction */
typedef int (*PFNLVCOMPARE) (HLVITEM nItem1, HLVITEM nItem2, PLVSORTDATA sortData);


/** Column flags */
/** column text left align, default */
#define LVCF_LEFTALIGN	        0x0000
/** column text right align */
#define LVCF_RIGHTALIGN	        0x0001
/** column text center align */
#define LVCF_CENTERALIGN        0x0002
/** column treeview style */
#define LVCF_TREEVIEW           0x0004

/** header flags */
/** header text left align, default */
#define LVHF_LEFTALIGN		0x0000
/** header text right align */
#define LVHF_RIGHTALIGN		0x0004
/** header text center align */
#define LVHF_CENTERALIGN	0x0008

/** 
 * Struct of the listview column info, contains information about a column.
 * This structure is used for creating or retrieving a column.
 */
typedef struct _LVCOLUMN
{
    /** the horizontal position */
    int nCols;
    /** column's width */
    int width;
    /** the title of this column */
    char *pszHeadText;
    /** max text len */
    int nTextMax;
    /** image of the column header, can be bitmap or icon */
    DWORD image; 
    /** Comparision function associated with the column */
    PFNLVCOMPARE pfnCompare;
    /** Column and header flags */
    DWORD colFlags;
} LVCOLUMN;
typedef LVCOLUMN *PLVCOLUMN;

/** listview search flags */
/** search by text */
#define LVFF_TEXT	    0x0001
/** search by addtional data */
#define LVFF_ADDDATA	0x0002

/** Contains information for finding a certain item info */
typedef struct _LVFINDINFO
{
    /** 
     * Type of search to perform. 
     * This member can be set to one or more of the following values:
     * - LVFF_TEXT
     *   Searches based on the item(subitems) text.
     * - LVFF_ADDDATA
     *   Searches based on the attached additional item data.
     */
    DWORD flags;
    /** Search index to begin with, 0 from the beginning */
    int iStart;
    /** pszInfo containing nCols columns' text */
    int nCols;
    /** all the subitem's content of this item */
    char **pszInfo;
    /** the additional item data */
    DWORD addData;

    /** The found item's row, reserved */
    int nItem;
    /** The found subitem's column, reserved */
    int nSubitem;

} LVFINDINFO;
typedef LVFINDINFO *PLVFINDINFO;

/** Contains listview general notification information */
typedef struct _LVNM_NORMAL
{
    /** wParam parameter of the message */
    WPARAM wParam;
    /** lParam parameter of the message */
    LPARAM lParam;
} LVNM_NORMAL;
typedef LVNM_NORMAL *PLVNM_NORMAL;

/** keydown notification information */
typedef LVNM_NORMAL LVNM_KEYDOWN;
typedef LVNM_KEYDOWN *PLVNM_KEYDOWN;

/** Contains listview notification information when mouse down on the header  */
typedef LVNM_NORMAL LVNM_HEADRDOWN;
typedef LVNM_HEADRDOWN *PLVNM_HEADRDOWN;

/** Contains listview notification information when mouse up on the header  */
typedef LVNM_NORMAL LVNM_HEADRUP;
typedef LVNM_HEADRUP *PLVNM_HEADUP;

/** Contains listview notification information when mouse down on the item area */
typedef LVNM_NORMAL LVNM_ITEMRDOWN;
typedef LVNM_ITEMRDOWN *PLVNM_ITEMRDOWN;

/** Contains listview notification information when mouse up on the item area */
typedef LVNM_NORMAL LVNM_ITEMRUP;
typedef LVNM_ITEMRUP *PLVNM_ITEMRUP;

    /**
     * \defgroup mgext_ctrl_listview_styles Styles of listview control
     * @{
     */

/**
 * \def LVS_UPNOTIFY
 * \brief Notifies the parent window when mouse is up (default is down).
 *
 * Causes the listview to notify the listview parent window 
 * with a notification message when the user make actions, such as clicks, doubleclicks, ...,etc.
 */
#define LVS_UPNOTIFY            0x0001L             /* must be the same with SVS_UPNOTIFY */
#define LVS_NOTIFY              LVS_UPNOTIFY

/**
 * \def LVS_SORT
 * \brief Sorts strings automatically.
 *
 * Causes the listview to sort strings automatically. 
 */
#define LVS_SORT                0x0002L

/**
 * \def LVS_MULTIPLESEL
 * \brief Causes the listview to allow the user to select multiple items.
 */
#define LVS_MULTIPLESEL         0x0008L              /* reserved */

/**
 * \def LVS_CHECKBOX
 * \brief Displays a check box in an item.
 */
#define LVS_CHECKBOX            0x1000L              /* reserved */

/**
 * \def LVS_AUTOCHECK
 * \brief If the list box has LVS_CHECKBOX style, this
 *        style tell the box to auto-switch the check box between 
 *        checked or un-checked when the user click the check mark box of an item.
 */
#define LVS_AUTOCHECK           0x2000L              /* reserved */

#define LVS_AUTOCHECKBOX        (LVS_CHECKBOX | LVS_AUTOCHECK)    /* reserved */

/**
 * \def LVS_TREEVIEW
 * \brief Uses listview in a treeview style.
 */
#define LVS_TREEVIEW            0x4000L

    /** @} end of mgext_ctrl_listview_styles */

    /**
     * \defgroup mgext_ctrl_listview_msgs Messages of ListView control
     * @{
     */

/**
 *  \def LVM_ADDITEM
 *  \brief Adds a item to listview, this item is also called a row. 
 *  
 *  \code 
 *  LVM_ADDITEM
 *  PLVITEM p
 *  HLVITEM parent;
 *
 *  wParam = (WPARAM)parent;
 *  p =(LPARAM)lParam;
 *  \endcode
 *
 *  \param p Pointes to a LVITEM structure that contains the information of 
 *           the new item to be added. nItem member of the LVITEM struct speficied 
 *           the item position in its parent item, beginning with zero.
 *  \param parent handle of the parent item into which the new item is about to insert.
 *           If parent equals zero, the parent item will be the root of listview.
 *
 *  \return Returns the handle of the new item if successful, or 0 otherwise.
 */
#define LVM_ADDITEM            0xF110

/**
 * \def LVM_FILLSUBITEM
 * \brief Sets the content of a subitem, indentified by rows and columns.
 * 
 * \code
 * LVM_FILLSUBITEM
 * PLVSUBITEM p;
 * HLVITEM pi;
 *
 * lParam = (LPARAM)p;
 * wParam = (WPARAM)pi;
 * \endcode
 *
 * \param p  Pointes to a PLVSUBITEM structure that contains the information of 
 *           the subitem to set. If pi is not zero, nItem member of this struct
 *           has no meaning.
 * \param pi handle of the target item.
 *           If pi equals zero, the row position of the target item is 
 *           specified by nItem member of p structure.
 *
 * \return Returns LV_OKAY if successful, or LV_ERR otherwise.
 */
#define LVM_FILLSUBITEM        0xF111

/**
 * \def LVM_ADDCOLUMN
 * \brief Adds a new column to listview, indentified by column.
 * 
 * \code
 *  LVM_ADDCOLUMN
 *  PLVCOLUMN p;
 *
 *  wParam = 0;
 *  lParam =(LPARAM)p;
 * \endcode
 *
 * \param p Pointes to a LVCOLUMN structure that contains the information about the new 
 *          column to be added.
 */
#define LVM_ADDCOLUMN          0xF112

/**
 * \def LVM_DELITEM
 * \brief Deletes an item form listview.
 *
 * \code
 * LVM_DELITEM
 * int nRow;
 * HLVITEM pi;
 *
 * wParam = (WPARAM)nRow;
 * lParam = (LPARAM)pi;
 * \endcode
 *
 * \param nRow If pi is zero, nRow specified the row index of the target item to delete.
 * \param pi handle of the target item.
 *
 * \return Returns LV_OKAY if successful, or LV_ERR otherwise.
 */
#define LVM_DELITEM            0xF113

/**
 * \def LVM_CLEARSUBITEM
 * \brief Clears the content of a subitem.
 * 
 * \code
 * LVM_CLEARSUBITEM
 * PLVSUBITEM p;
 * HLVITEM pi;
 *
 * lParam = (LPARAM)p;
 * wParam = (WPARAM)pi;
 * \endcode
 *
 * \param p  Pointes to a PLVSUBITEM structure that contains the information of 
 *           the subitem to clear. If pi is not zero, nItem member of this struct
 *           has no meaning.
 * \param pi handle of the target item.
 *           If pi equals zero, the row position of the target item is 
 *           specified by nItem member of p structure.
 *
 * \return Returns LV_OKAY if successful, or LV_ERR otherwise.
 */
#define LVM_CLEARSUBITEM       0xF114

/**
 * \def LVM_DELCOLUMN
 * \brief Deletes a column from listview, all subitem in this column will be removed.  
 *
 * \code
 * LVM_DELCOLUMN
 * int nCols;
 *
 * wParam = (WPARAM)nCol;
 * lParam = 0;
 * \endcode
 *
 * \param nCol the index of the column to be removed.
 * \return Returns LV_OKAY if successful, or LV_ERR otherwise.
 */
#define LVM_DELCOLUMN          0xF115

/**
 * \def LVM_COLSORT
 * \brief Sorts all subitems according to a certain column. 
 *
 * \code
 * LVM_COLSORT
 * int ncol;
 *
 * wParam = (WPARAM)ncol;
 * lParam = 0;
 * \endcode
 *
 * \param ncol Index of the column.
 * \return Returns LV_OKAY if successful, or LV_ERR otherwise.
 */
#define LVM_COLSORT            0xF116

/**
 * \def LVM_SETSUBITEMCOLOR
 * \brief Sets the text color of a subitem.
 *
 * \code
 * LVM_SETSUBITEMCOLOR
 * PLVSUBITEM p;
 * HLVITEM pi;
 *
 * lParam = (LPARAM)p;
 * wParam = (WPARAM)pi;
 * \endcode
 *
 * \param p  Pointes to a PLVSUBITEM structure that contains the information of 
 *           the subitem to set. If pi is not zero, nItem member of this struct
 *           has no meaning.
 * \param pi handle of the target item.
 *           If pi equals zero, the row position of the target item is 
 *           specified by nItem member of p structure.
 *
 * \return Always returns 0;
 */
#define LVM_SETSUBITEMCOLOR       0xF117


/**
 * \def LVM_GETSUBITEMCOLOR
 * \brief Gets the text color of a subitem.
 *
 * \code
 * LVM_SETSUBITEMCOLOR
 * PLVSUBITEM p;
 * HLVITEM pi;
 *
 * add by liuyu date 2014-08-04
 *
 * lParam = (LPARAM)p;
 * wParam = (WPARAM)pi;
 * \endcode
 *
 * \param p  Pointes to a PLVSUBITEM structure that contains the information of 
 *           the subitem to get. If pi is not zero, nItem member of this struct
 *           has no meaning.
 * \param pi handle of the target item.
 *           If pi equals zero, the row position of the target item is 
 *           specified by nItem member of p structure.
 *
 * \return Always returns 0;
 */
#define LVM_GETSUBITEMCOLOR       0xF150


/**
 * \def LVM_FINDITEM
 *
 * \code
 * LVM_FINDITEM
 * PLVFINDINFO plvfi;
 * HLVITEM parent;
 *
 * wParam = (WPARAM)parent;
 * lParam = (LPARAM)plvfi;
 * \endcode
 *
 * \param parent Handle of the item to search in.
 * \param plvfi Points to a LVFINDINFO structure containing information for searching.
 *              If parent is zero, iStart member of plvfi specifieds the start position
 *              on search.
 *
 * \return Returns the handle of the found item if successful, or 0 otherwise.
 */
#define LVM_FINDITEM           0xF118

/**
 *
 * \def LVM_GETSUBITEMTEXT
 * \brief Retrieves the text of a listview subitem.
 *
 * \code 
 * LVM_GETSUBITEMTEXT
 * PLVSUBITEM p;
 * HLVITEM pi;
 *
 * lParam = (LPARAM)p;
 * wParam = (WPARAM)pi;
 * \endcode
 *
 * \param p  Pointes to a PLVSUBITEM structure that contains the information of 
 *           the subitem to set. If pi is not zero, nItem member of this struct
 *           has no meaning.
 * \param pi handle of the target item.
 *           If pi equals zero, the row position of the target item is 
 *           specified by nItem member of p structure.
 *
 * \return Returns len of the text if successful, -1 otherwise.
 */

#define LVM_GETSUBITEMTEXT         0xF119

/**
 * \def LVM_GETITEMCOUNT
 * \brief Gets the number of all the items(rows) in a listview.
 *
 * \code
 * LVM_GETITEMCOUNT
 *
 * wParam = 0;
 * lParam = 0;
 * \endcode
 *
 * \return The number of the items.
 */
#define LVM_GETITEMCOUNT       0xF11A

/**
 * \def LVM_GETCOLUMNCOUNT
 * \brief Gets the number of all the columns in listview.
 *
 * \code
 * LVM_GETCOLUMNCOUNT
 *
 * wParam = 0;
 * lParam = 0;
 * \endcode
 *
 * \return the number of all the columns in listview.
 */
#define LVM_GETCOLUMNCOUNT     0xF11B

/**
 * \def LVM_GETSELECTEDITEM
 * \brief Gets the current selected item.
 *
 * \code
 * LVM_GETSELECTEDITEM
 *
 * wParam = 0;
 * lParam = 0;
 * \endcode
 *
 * \return handle of the current selected item.
 */
#define LVM_GETSELECTEDITEM    0xF11C

/**
 * \def LVM_DELALLITEM
 * \brief Removes all the items in listview.
 *
 * \code
 * LVM_DEALLITEM
 *
 * wParam = 0;
 * lParam = 0;
 * \endcode
 *
 * \return Returns TRUE if successful, or FALSE otherwise.
 */
#define LVM_DELALLITEM           0xF11D

/**
 * \def LVM_MODIFYHEAD
 * \brief Changes the title of a column.
 *
 * \code
 * LVM_MODIFYHEAD
 * PLVCOLUMN pcol;
 *
 * wParam = 0;
 * lParam = (LPARAM)pcol;
 * \endcode
 *
 * \param pcol Pointer to a LVCOLUMN struct.
 * \return Returns LV_OKAY if successfull, or LV_ERR otherwise.
 */
#define LVM_MODIFYHEAD           0xF11E

/**
 * \def LVM_SELECTITEM
 * \brief Selects an item.
 *
 * \code
 * LVM_SELECTITEM
 * int nRow;
 * HLVITEM pi;
 *
 * wParam = (WPARAM)nRow;
 * lParam = (LPARAM)pi;
 * \endcode
 *
 * \param nRow If pi is zero, nRow specified the row index of the target item to select.
 * \param pi handle of the target item.
 *
 * \return Always returns 0.
 */
#define LVM_SELECTITEM		0xF11F 


/**
 * \def LVM_SHOWITEM
 * \brief Makes the item is entirely visible in the list view.
 *
 * \code
 * LVM_SHOWITEM
 * int nRow;
 * HLVITEM pi;
 *
 * wParam = (WPARAM)nRow;
 * lParam = (LPARAM)pi;
 * \endcode
 *
 * \param nRow If pi is zero, nRow specified the row index of the target item to show.
 * \param pi handle of the target item.
 *
 * \return Always returns 0.
 */
#define LVM_SHOWITEM		0xF120 

/**
 * \def LVM_GETSUBITEMLEN
 * \brief Gets the text len of the subitem.
 *
 * \code
 * LVM_GETSUBITEMLEN
 * PLVSUBITEM p;
 * HLVITEM pi;
 *
 * lParam = (LPARAM)p;
 * wParam = (WPARAM)pi;
 * \endcode
 *
 * \param p  Pointes to a PLVSUBITEM structure that contains the information of 
 *           the subitem to set. If pi is not zero, nItem member of this struct
 *           has no meaning.
 * \param pi handle of the target item.
 *           If pi equals zero, the row position of the target item is 
 *           specified by nItem member of p structure.
 *
 * \return Returns the text len if successful, or LV_ERR otherwise.
 */
#define LVM_GETSUBITEMLEN   	0xF121

/**
 * \def LVM_SETCOLUMN
 * \brief Sets the attributes of a listview column.
 *
 * \code
 * LVM_SETCOLUMN
 * PLVCOLUMN pcol;
 *
 * wParam = 0;
 * lParam = (LPARAM)pcol;
 * \endcode
 *
 * \param pcol Points to a LVCOLUMN structure containing the new column information.
 *
 * \return Returns LV_OKAY if successful, or LV_ERR otherwise.
 */
#define LVM_SETCOLUMN		0xF122

/**
 * \def LVM_SETSUBITEMTEXT
 * \brief Sets the text of a subitem.
 *
 * \code
 * LVM_SETSUBITEMTEXT
 * PLVSUBITEM p;
 * HLVITEM pi;
 *
 * wParam = (WPARAM)pi;
 * lParam = (LPARAM)p;
 * \endcode
 *
 * \param p  Pointes to a PLVSUBITEM structure that contains the information of 
 *           the subitem to set. If pi is not zero, nItem member of this struct
 *           has no meaning.
 * \param pi handle of the target item.
 *           If pi equals zero, the row position of the target item is 
 *           specified by nItem member of p structure.
 *
 * \return Returns LV_OKAY if successful, or LV_ERR otherwise.
 */
#define LVM_SETSUBITEMTEXT	0xF123

/**
 * \def LVM_SETSUBITEM
 * \brief Sets the attributes of a subitem.
 *
 * \code
 * LVM_SETSUBITEM
 * PLVSUBITEM p;
 * HLVITEM pi;
 *
 * lParam = (LPARAM)p;
 * wParam = (WPARAM)pi;
 * \endcode
 *
 * \param p  Pointes to a PLVSUBITEM structure that contains the information of 
 *           the subitem to set. If pi is not zero, nItem member of this struct
 *           has no meaning.
 * \param pi handle of the target item.
 *           If pi equals zero, the row position of the target item is 
 *           specified by nItem member of p structure.
 *
 * \return Returns LV_OKAY if successful, or LV_ERR otherwise.
 */
#define LVM_SETSUBITEM		0xF124

/**
 * \def LVM_GETCOLUMN
 * \brief Retrieves the information about a listview column.
 *
 * \code
 * LVM_GETCOLUMN
 * int nCol;
 * PLVCOLUMN pcol;
 *
 * wParam = (WPARAM)nCol;
 * lParam = (LPARAM)pcol;
 * \endcode
 *
 * \param nCol Index of the column.
 * \param pcol Points to a LVCOLUMN structure for retrieving the information 
 *             about the column.
 *
 * \return Returns TRUE if successful, or FALSE otherwise.
 */
#define LVM_GETCOLUMN		0xF125 

/**
 * \def LVM_GETCOLUMNWIDTH
 * \brief Retrieves the width of a listview column.
 *
 * \code
 * LVM_GETCOLUMNWIDTH
 * int nCol;
 *
 * wParam = (WPARAM)nCol;
 * lParam = (LPARAM)0;
 * \endcode
 *
 * \param nCol Index of the column.
 *
 * \return Returns the column width if successful, or -1 otherwise.
 */
#define LVM_GETCOLUMNWIDTH	0xF126 

/**
 * \def LVM_GETITEM
 * \brief Retrieves the item's attributes.
 *
 * \code
 * LVM_GETITEM
 * HLVITEM pi;
 * LVITEM item_info;
 *
 * wParam = (WPARAM)pi;
 * lParam = (LPARAM)&item_info;
 * \endcode
 *
 * \param pi handle of the target item.
 * \param item_info Used for storing the target item's attributes. 
                    If pi is zero, nItem field of item_info specified the row index 
                    of the target item to get.
 *
 * \return Returns LV_OKAY if successful, or LV_ERR otherwise.
 */
#define LVM_GETITEM		0xF127 

/**
 * \def LVM_GETITEMSTATE
 * \brief Retrieves the state of a listview item.
 *
 * \code
 * LVM_GETITEMSTATE
 * UINT mask;
 * HLVITEM pi;
 *
 * wParam = (WPARAM)pi;
 * lParam = (LPARAM)mask;
 * \endcode
 *
 * \param pi handle of the target item.
 * \param mask Contains state information to retrieve, can be the combination
 *             of the following values.
 *
 * \return Returns the current state of the specified item.
 */
#define LVM_GETITEMSTATE	0xF128 

/**
 * \def LVM_GETSELECTEDCOLUMN
 * \brief Retrieves the index of the currently selected column of a listview.
 *
 * \code
 * LVM_GETSELECTEDCOLUMN
 *
 * wParam = 0;
 * lParam = 0;
 * \endcode
 *
 * \return Returns the index of the selected column.
 */
#define LVM_GETSELECTEDCOLUMN	0xF129 

/**
 * \def LVM_GETSELECTEDCOUNT
 * \brief Retrieves the number of the selected items in a listview.
 *
 * \code
 * LVM_GETSELECTEDCOUNT
 *
 * wParam = 0;
 * lParam = 0;
 * \endcode
 *
 * \return Returns the number of the selected items.
 */
#define LVM_GETSELECTEDCOUNT	0xF130 

/**
 * \def LVM_GETTOPVISIBLE
 * \brief Retrieves the index of the topmost visible item in a listview.
 *
 * \code
 * LVM_GETTOPVISIBLE
 *
 * wParam = 0;
 * lParam = 0;
 * \endcode
 *
 * \return Returns the index of the topmost visible item if successful, or zero.
 */
#define LVM_GETTOPVISIBLE	0xF131 

#define LVM_NULL		0xF132 

#define LVM_SETITEMSTATE	0xF133 

/**
 * \def LVM_SORTITEMS
 * \brief Uses an application-defined comparision function to sort the items.
 *
 * \code
 * LVM_SORTITEMS
 * PLVSORTDATA sortData;
 * PFNLVCOMPARE pfnCompare;
 *
 * wParam = (WPARAM)sortData;
 * lParam = (LPARAM)pfnCompare;
 * \endcode
 *
 * \param sortData Sorting datas passed to the comparision function.
 * \param pfnCompare Pointer to the application-defined comparision function. The
 *                   comparision function is called during the sort operation
 *                   each time the relative order of the two items needs to be 
 *                   compared.
 *
 *                   The comparison function must return a negative value if the 
 *                   first item precedes the second, a positive value if 
 *                   the first item follows the second, or zero if the two 
 *                   items are equivalent.
 *
 *                   The comparision function has the following form:
 *
 *                   int CompareFunction(int nItem1, int nItem2, PLVSORTDATA sortData);
 *
 *                   nItem1 is the handle of the first item, nItem2 is the handle
 *                   of the second item, and sortData is passed to CompareFunction
 *                   as the third parameter.
 *
 * \return Returns TRUE if successful, or FALSE otherwise.
 */
#define LVM_SORTITEMS		0xF134 

/**
 * \def LVM_SETITEMHEIGHT
 * \brief Changes the height of a item.
 *
 * \code
 * LVM_SETITEMHEIGHT
 * int height;
 * HLVITEM pi;
 *
 * wParam = (WPARAM)pi;
 * lParam = (LPARAM)height;
 * \endcode
 *
 * \param height The new height of the item.
 * \param pi handle of the target item.
 *
 * \return Returns TRUE if successful, or FALSE otherwise.
 */
#define LVM_SETITEMHEIGHT	0xF135 

/**
 * \def LVM_SETHEADHEIGHT
 * \brief Changes the height of the header.
 *
 * \code
 * LVM_SETHEADHEIGHT
 * int height;
 *
 * wParam = (WPARAM)height;
 * lParam = 0;
 * \endcode
 *
 * \param height The new height of the header.
 * \return Returns TRUE if successful, or FALSE otherwise.
 */
#define LVM_SETHEADHEIGHT	0xF136 

/**
 * \def LVM_GETITEMADDDATA
 * \brief Gets the 32-bit data value associated with an item.
 * 
 * An application sends an LVM_GETITEMADDDATA message to a listview to get the 
 * 32-bit data value stored for the item with index of \a wParam; 
 * By default this is zero. An application must set the 
 * item data value by sending an LVM_SETITEMADDDATA message to the listview for 
 * this value to have meaning.
 *
 * \code
 * LVM_GETITEMADDDATA
 * int index;
 * HLVITEM pi;
 *
 * wParam = (WPARAM)index;
 * lParam = (LPARAM)pi;
 * \endcode
 *
 * \param pi handle of the target item.
 * \param index The index of the specified item. If pi is not zero, use pi instead.
 *
 * \return The 32-bit data value associated with an item on success, otherwise
 *         -1 to indicate an error.
 */
#define LVM_GETITEMADDDATA       0xF137

/**
 * \def LVM_SETITEMADDDATA
 * \brief Associates a 32-bit data value with an item.
 * 
 * An application sends an LVM_SETITEMADDDATA message to associate a 32-bit data 
 * value specified in the \a lParam parameter with an item in the listview.
 *
 * \code
 * LVM_SETITEMADDDATA
 * HLVITEM pi;
 * DWORD addData;
 *
 * wParam = (WPARAM)pi;
 * lParam = (LPARAM)addData;
 * \endcode
 *
 * \param pi handle of the target item.
 * \param addData the 32-bit data value which will associated with the item.
 *
 * \return One of the following values:
 *          - LV_OKAY\n         Success
 *          - LV_ERR\n          Invalid item index
 *
 */
#define LVM_SETITEMADDDATA       0xF138

/**
 * \def LVM_CHOOSEITEM
 * \brief Selects and shows an item.
 *
 * \code
 * LVM_CHOOSEITEM
 * int nRow;
 * HLVITEM pi;
 *
 * wParam = (WPARAM)nRow;
 * lParam = (LPARAM)pi;
 * \endcode
 *
 * \param nRow If pi is zero, nRow specified the row index of the target item to choose.
 * \param pi handle of the target item.
 *
 * \return Always returns 0.
 */
#define LVM_CHOOSEITEM		0xF139

/**
 * \def LVM_SETSTRCMPFUNC
 * \brief Sets the STRCMP function used to sort items.
 *
 * An application sends a LVM_SETSTRCMPFUNC message to set a 
 * new STRCMP function to sort items in the Listview control.
 *
 * Note that you should send this message before adding 
 * any item to the Listview control.
 *
 * \code
 * static int my_strcmp (const char* s1, const char* s2, size_t n)
 * {
 *      ...
 *      return 0;
 * }
 *
 * LVM_SETSTRCMPFUNC
 *
 * wParam = 0;
 * lParam = (LPARAM) my_strcmp;
 * \endcode
 *
 * \param my_strcmp Your own function to compare two strings.
 *
 * \return One of the following values:
 *          - 0\n     Success
 *          - -1\n    Not an empty TreeView control
 */
#define LVM_SETSTRCMPFUNC       0xF140

#define LVIR_PARENT             1
#define LVIR_FIRSTCHILD         2
#define LVIR_NEXTSIBLING        3
#define LVIR_PREVSIBLING        4

/**
 * \def LVM_GETRELATEDITEM
 * \brief Retrives related item of specific item.
 *
 * \code
 * LVM_GETRELATEDITEM
 * int related;
 * GHANDLE item;
 *
 * wParam = (WPARAM)related;
 * lParam = (LPARAM)item;
 * \endcode
 *
 * \param related A integer which indicates the relationship between 
 *        the item to retrive and the specified item, can be one of the following values:
 *          - TVIR_PARENT\n
 *              To retrive the parent item of the specified item.
 *          - TVIR_FIRSTCHILD\n
 *              To retrive the first child item of the specified item.
 *          - TVIR_NEXTSIBLING\n
 *              To retrive the next sibling item of the specified item.
 *          - TVIR_PREVSIBLING\n
 *              To retrive the previous sibling item of the specified item.
 *
 * \param item The handle to the known item.
 *
 * \return The handle of the related item on success, otherwise 0.
 */
#define LVM_GETRELATEDITEM      0xF141

/**
 * \def LVM_FOLDITEM
 * \brief Folds or unfolds an item.
 *
 * \code
 * LVM_FOLDITEM
 * int bFold;
 * HLVITEM pi;
 *
 * wParam = (WPARAM)bFold;
 * lParam = (LPARAM)pi;
 * \endcode
 *
 * \param bFold to fold or to unfold, TRUE is to fold.
 * \param pi handle of the target item.
 *
 * \return Always returns 0.
 */
#define LVM_FOLDITEM            0xF142

/**
 * \def LVM_SETSUBITEM_ALL
 * \brief Sets information of all subitems.
 *
 * \code
 * LVM_SETSUBITEM_ALL
 * PLVSUBITEM p1;
 * int count;
 *
 * add by pst date 2014-08-12
 *
 * lParam = (LPARAM)p1;
 * wParam = (WPARAM)count;
 * \endcode
 *
 * \param p1  Pointes to a PLVSUBITEM structure that contains the information of 
 *           the subitem to get. 
 * \param count The total number of subitems want to set.
 * \return returns LV_OKAY for success, LV_ERR for fail;
 */
#define LVM_SETSUBITEM_ALL		0xF144
/**
 * \def LVM_ADDITEM_ALL
 * \brief Sets information of all subitems.
 *
 * \code
 * LVM_ADDITEM_ALL
 * PLVITEM p1;
 * int nRow;
 *
 * add by pst date 2014-08-12
 *
 * lParam = (LPARAM)p1;
 * wParam = (WPARAM)nRow;
 * \endcode
 *
 * \param nRow  The line number you want to add
 * \param p1  Pointes to a PLVSUBITEM structure that contains the information of 
 *           the subitem to get.
 *
 * \return returns 0 for success, -1 for fail;
 */
#define LVM_ADDITEM_ALL         0xF145


    /** @} end of mgext_ctrl_listview_msgs */

    /**
     * \defgroup mgext_ctrl_listview_ncs Notification code of ListView control
     * @{
     */

#define LVN_CLICKED            1    /* must be the same as SVN_CLICKED */
/**
 * \def LVN_SELCHANGE
 * \brief This notification code informs parent window the current selected item 
 *        has changed.
 */
#define LVN_SELCHANGE          2    /* must be the same as SVN_SELCHANGED */

/**
 * \def LVN_ITEMRDOWN
 * \brief This notification code informs parent window the right mouse button down
 *        on a listview item.
 */
#define LVN_ITEMRDOWN          4

/**
 * \def LVN_ITEMRUP
 * \brief This notification code informs parent window the right mouse button up
 *        on a listview item.
 */
#define LVN_ITEMRUP            5

/**
 * \def LVN_HEADRDOWN
 * \brief This notification code informs parent window the right mouse button down
 *        on the listview header.
 */
#define LVN_HEADRDOWN          6

/**
 * \def LVN_HEADRUP
 * \brief This notification code informs parent window the right mouse button up
 *        on the listview header.
 */
#define LVN_HEADRUP            7

/**
 * \def LVN_KEYDOWN
 * \brief This notification code informs parent window that a key has been pressed.
 */
#define LVN_KEYDOWN            8

/**
 *
 * \def LVN_ITEMDBCLK
 * \brief This notification code informs parent window the current selected item 
 *        has be double clicked.
 */
#define LVN_ITEMDBCLK          9

/**
 * \def LVN_ITEMCLK
 * \brief This notification code informs parent window the current selected item 
 *        has been clicked.
 */
#define LVN_ITEMCLK            10

/**
 * \def LVN_COLCHANGE
 * \brief This notification code informs parent window the current selected column 
 *        has changed.
 */
#define LVN_COLCHANGE          11

/**
 * \def LVN_FOLDED
 * \brief This notification code informs that user folds an item by mouse
 *        clicking.
 */
#define LVN_FOLDED             12

/**
 * \def LVN_UNFOLDED
 * \brief This notification code informs that user unfolds an item by mouse
 *        clicking.
 */
#define LVN_UNFOLDED           13

    /** @} end of mgext_ctrl_listview_ncs */

    /** @} end of mgext_ctrl_listview */

    /** @} end of mgext_controls */

    /** @} end of mgext_fns */

#ifdef  __cplusplus
}
#endif

#endif /* EXT_LISTVIEW_H */

