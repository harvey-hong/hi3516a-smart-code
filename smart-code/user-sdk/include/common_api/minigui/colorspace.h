/**
 * \file colorspace.h
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
 * $Id: colorspace.h,v 1.8 2005/09/04 06:03:54 weiym Exp $
 *
 *             MiniGUI for Linux/uClinux, eCos, uC/OS-II, VxWorks, 
 *                     and ThreadX version 1.6.x
 *             Copyright (C) 2002-2005 Feynman Software.
 *             Copyright (C) 1998-2002 Wei Yongming.
 */

#ifndef _MGUI_COLORSPACE_H
#define _MGUI_COLORSPACE_H


#ifdef __cplusplus
extern "C" {
#endif  /* __cplusplus */

#ifdef _USE_NEWGAL

    /**
     * \addtogroup mywins_fns Interfaces of MyWins module of MiniGUIExt library
     * @{
     */

    /**
     * \defgroup mywins_colorspace Color Space Conversion Functions
     *
     * This module defines some color space conversion functions.
     *
     * @{
     */

/**
 * \fn void RGB2HSV (Uint8 r, Uint8 g, Uint8 b, 
                Uint16 *hout, Uint8 *sout, Uint8 *vout)
 * \brief Converts r/g/b values of a color in RGB color space to h/s/v of 
 *        the color in HSV color space.
 *
 * This function converts r/g/b values of a color in RGB color space to 
 * h/s/v values of the color in HSV color space. 
 *
 * \param r     The the red value of the color in RGB space to be converted.
 * \param g     The the green value of the color in RGB space to be converted.
 * \param b     The the blue value of the color in RGB space to be converted.
 * \param hout  The pointer to Uint16, returns the h value of the color
 *              in HSV color space.
 * \param sout  The pointer to Uint8, returns the s value of the color 
 *              in HSV color space returned.
 * \param vout  The pointer to Uint8, returns the v value of the color
 *              in HSV color space returned.
 *
 * \sa HSV2RGB, YUV2RGB, RGB2YUV 
 */

void RGB2HSV (Uint8 r, Uint8 g, Uint8 b, 
                Uint16 *hout, Uint8 *sout, Uint8 *vout);

/**
 * \fn void HSV2RGB (Uint16 hin, Uint8 sin, Uint8 vin, 
                Uint8 *rout, Uint8 *gout, Uint8 *bout)
 * \brief Converts h/s/v values of a color to r/g/b values of the color.
 *
 * This function converts h/s/v values of a color in HSV color space 
 * to r/g/b values of the color in RGB space. 
 *
 * \param hin   The the h value of the HSV color space to be converted, 
 *              the range is between 0 to 359.
 * \param sin   The the s value of the HSV color space to be converted, 
 *              the range is between 0 to 255.
 * \param vin   The the v value of the HSV color space to be converted, 
 *              the range is between 0 to 255.
 * \param rout  The pointer to Uint8, returns the red value of the RGB 
 *              color space.
 * \param gout  The pointer to Uint8, returns the green value of the RGB 
 *              color space.
 * \param bout  The pointer to Uint8, returns the bout value of the RGB 
 *              color space.
 * 
 * \sa RGB2HSV, YUV2RGB, RGB2YUV 
 */

void HSV2RGB (Uint16 hin, Uint8 sin, Uint8 vin, 
                Uint8 *rout, Uint8 *gout, Uint8 *bout);

/**
 * \fn void YUV2RGB (int y, int u, int v, Uint8 *r, Uint8 *g, Uint8 *b)
 * \brief Converts y/u/v values of a color in YUV color space to 
 *        to r/g/b values of the color in RGB color space.
 *
 * This function converts y/u/v values of YUV color space to r/g/b values 
 * of RGB color space. 
 *
 * \param y     The the y value of the YUV color space to be converted.
 * \param u     The the u value of the YUV color space to be converted.
 * \param v     The the v value of the YUV color space to be converted.
 * \param r     The pointer to Uint8, returns the red value of the 
 *              RGB color space.
 * \param g     The pointer to Uint8, returns the green value of the 
 *              RGB color space.
 * \param b     The pointer to Uint8, returns the bout value of the 
 *              RGB color space.
 * 
 * \sa RGB2HSV, HSV2RGB, RGB2YUV 
 */

void YUV2RGB (int y, int u, int v, Uint8 *r, Uint8 *g, Uint8 *b);

/**
 * \fn void RGB2YUV (Uint8 r, Uint8 g, Uint8 b, int *y, int *u, int *v)
 * \brief Converts r/g/b values of a color in RGB color space 
 *        to y/u/v values of the color in YUV color space.
 *
 * The function converts r/g/b values of a color in RGB color space 
 *        to y/u/v values of the color in YUV color space.
 *
 * \param r  The the red value of the RGB color space to be converted.
 * \param g  The the green value of the RGB color space to be converted.
 * \param b  The the blue value of the RGB color space to be converted.
 * \param y  The pointer to int, returns the y value of the YUV color space.
 * \param u  The pointer to int, returns the u value of the YUV color space.
 * \param v  The pointer to int, returns the v value of the YUV color space.
 * 
 * \sa RGB2HSV, HSV2RGB, YUV2RGB 
 */
MG_EXPORT void RGB2YUV (Uint8 r, Uint8 g, Uint8 b, int *y, int *u, int *v);

    /** @} end of mywins_colorspace*/

    /** @} end of mywins_fns */

#endif /* _USE_NEWGAL */

#ifdef __cplusplus
}
#endif  /* __cplusplus */

#endif /* _MGUI_COLORSPACE_H */


