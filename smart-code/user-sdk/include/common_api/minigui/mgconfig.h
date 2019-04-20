/* mgconfig.h.  Generated from mgconfig.h.in by configure.  */
/* mgconfig.h.in.  Generated from configure.in by autoheader.  */

/* Define to one of `_getb67', `GETB67', `getb67' for Cray-2 and Cray-YMP
   systems. This function is required for `alloca.c' support on those systems.
   */
/* #undef CRAY_STACKSEG_END */

/* Define to 1 if using `alloca.c'. */
/* #undef C_ALLOCA */

/* Define to 1 if you have `alloca', as a function or macro. */
#define HAVE_ALLOCA 1

/* Define to 1 if you have <alloca.h> and it should be used (not on Ultrix).
   */
#define HAVE_ALLOCA_H 1

/* Define to 1 if you have the <dirent.h> header file, and it defines `DIR'.
   */
#define HAVE_DIRENT_H 1

/* Define to 1 if you have the <dlfcn.h> header file. */
#define HAVE_DLFCN_H 1

/* Define to 1 if you don't have `vprintf' but do have `_doprnt.' */
/* #undef HAVE_DOPRNT */

/* Define to 1 if you have the `getpagesize' function. */
#define HAVE_GETPAGESIZE 1

/* Define to 1 if you have the `getpt' function. */
#define HAVE_GETPT 1

/* Define to 1 if you have the <inttypes.h> header file. */
#define HAVE_INTTYPES_H 1

/* Define to 1 if you have the <locale.h> header file. */
#define HAVE_LOCALE_H 1

/* Define to 1 if you have the <math.h> header file. */
#define HAVE_MATH_H 1

/* Define to 1 if you have the <memory.h> header file. */
#define HAVE_MEMORY_H 1

/* Define to 1 if you have a working `mmap' system call. */
/* #undef HAVE_MMAP */

/* Define to 1 if you have the <ndir.h> header file, and it defines `DIR'. */
/* #undef HAVE_NDIR_H */

/* Define to 1 if you have the `setenv' function. */
#define HAVE_SETENV 1

/* Define to 1 if you have the `setlocale' function. */
#define HAVE_SETLOCALE 1

/* Define to 1 if you have the <stdint.h> header file. */
#define HAVE_STDINT_H 1

/* Define to 1 if you have the <stdlib.h> header file. */
#define HAVE_STDLIB_H 1

/* Define to 1 if you have the `strcasecmp' function. */
#define HAVE_STRCASECMP 1

/* Define to 1 if you have the `strdup' function. */
#define HAVE_STRDUP 1

/* Define to 1 if you have the `strerror' function. */
#define HAVE_STRERROR 1

/* Define to 1 if you have the <strings.h> header file. */
#define HAVE_STRINGS_H 1

/* Define to 1 if you have the <string.h> header file. */
#define HAVE_STRING_H 1

/* Define to 1 if you have the <sys/dir.h> header file, and it defines `DIR'.
   */
/* #undef HAVE_SYS_DIR_H */

/* Define to 1 if you have the <sys/ndir.h> header file, and it defines `DIR'.
   */
/* #undef HAVE_SYS_NDIR_H */

/* Define to 1 if you have the <sys/param.h> header file. */
#define HAVE_SYS_PARAM_H 1					// change by mjq 20160331 start - end 

/* Define to 1 if you have the <sys/stat.h> header file. */
#define HAVE_SYS_STAT_H 1

/* Define to 1 if you have the <sys/time.h> header file. */
#define HAVE_SYS_TIME_H 1

/* Define to 1 if you have the <sys/types.h> header file. */
#define HAVE_SYS_TYPES_H 1

/* Define to 1 if you have the <termio.h> header file. */
#define HAVE_TERMIO_H 1

/* Define to 1 if you have the `tmpfile' function. */
#define HAVE_TMPFILE 1

/* Define to 1 if you have the <unistd.h> header file. */
#define HAVE_UNISTD_H 1

/* Define to 1 if you have the `vprintf' function. */
#define HAVE_VPRINTF 1

/* Binary age of MiniGUI */
#define MINIGUI_BINARY_AGE 0

/* Interface age of MiniGUI */
#define MINIGUI_INTERFACE_AGE 0

/* Major version of MiniGUI */
#define MINIGUI_MAJOR_VERSION 1

/* Micro version of MiniGUI */
#define MINIGUI_MICRO_VERSION 8

/* Minor version of MiniGUI */
#define MINIGUI_MINOR_VERSION 6

/* Define to the address where bug reports for this package should be sent. */
#define PACKAGE_BUGREPORT ""

/* Define to the full name of this package. */
#define PACKAGE_NAME ""

/* Define to the full name and version of this package. */
#define PACKAGE_STRING ""

/* Define to the one symbol short name of this package. */
#define PACKAGE_TARNAME ""

/* Define to the home page for this package. */
#define PACKAGE_URL ""									// change by mjq 20160331 start - end

/* Define to the version of this package. */
#define PACKAGE_VERSION ""

/* If using the C implementation of alloca, define if you know the
   direction of stack growth for your system; otherwise it will be
   automatically deduced at runtime.
	STACK_DIRECTION > 0 => grows toward higher addresses
	STACK_DIRECTION < 0 => grows toward lower addresses
	STACK_DIRECTION = 0 => direction of growth unknown */
/* #undef STACK_DIRECTION */

/* Define to 1 if you have the ANSI C header files. */
#define STDC_HEADERS 1

/* Define to 1 if you can safely include both <sys/time.h> and <time.h>. */
#define TIME_WITH_SYS_TIME 1

/* Define to 1 if your <sys/time.h> declares `struct tm'. */
/* #undef TM_IN_SYS_TIME */

/* Define if compile for Win32 platform */
/* #undef WIN32 */

/* Define if include IAL engine for ABSSIG */
/* #undef _ABSSIG_IAL */

/* Define if include IAL engine for Arca Tpanel Ads7846 */
/* #undef _ADS7846_IAL */

/* Define if include IAL engine for ADS */
/* #undef _ADS_IAL */

/* Define if include advanced 2D graphics APIs */
/* #undef _ADV_2DAPI */

/* Define if support Arabic charset */
/* #undef _ARABIC_SUPPORT */

/* Define if include IAL engine for ARM3000 */
/* #undef _ARM3000_IAL */

/* Define if include the automatic IAL engine */
/* #undef _AUTO_IAL */

/* Define if support BIG5 charset */
/* #undef _BIG5_SUPPORT */

/* Define if include clipboard support */
/* #undef _CLIPBOARD_SUPPORT */

/* Define if include the common IAL engine */
/* #undef _COMM_IAL */

/* Define if use coordinate transformation */
/* #undef _COOR_TRANS */

/* Define if include BUTTON control */
#define _CTRL_BUTTON 1

/* Define if include COMBOBOX control */
#define _CTRL_COMBOBOX 1

/* Define if include LISTBOX control */
#define _CTRL_LISTBOX 1

/* Define if include MENUBUTTON control */
/* #undef _CTRL_MENUBUTTON */

/* Define if include NEWTOOLBAR control */
/* #undef _CTRL_NEWTOOLBAR */

/* Define if include old MEDIT control */
/* #undef _CTRL_OLDMEDIT */

/* Define if include PROGRESSBAR control */
#define _CTRL_PROGRESSBAR 1

/* Define if include PROPSHEET control */
#define _CTRL_PROPSHEET 1

/* Define if include SCROLLVIEW control */
#define _CTRL_SCROLLVIEW 1

/* Define if include SIMEDIT control */
#define _CTRL_SIMEDIT 1

/* Define if include SLEDIT control */
#define _CTRL_SLEDIT 1

/* Define if include STATIC control */
#define _CTRL_STATIC 1

/* Define if include TEXTEDIT control */
/* #undef _CTRL_TEXTEDIT */

/* Define if include TOOLBAR control */
/* #undef _CTRL_TOOLBAR */

/* Define if include TRACKBAR control */
#define _CTRL_TRACKBAR 1

/* Define if include cursor support */
#define _CURSOR_SUPPORT 1

/* Define if support Cyrillic charset */
/* #undef _CYRILLIC_SUPPORT */

/* Define if build with debugging messages */
/* #undef _DEBUG */

/* Define if include IAL engine for DM270 */
/* #undef _DM270_IAL */

/* Define if include IAL engine for Intel DMG STB Remote Controller */
/* #undef _DMGSTB_IAL */

/* Define if mouse button can do double click */
#define _DOUBLE_CLICK 1

/* Define if include the dummy IAL engine */
/* #undef _DUMMY_IAL */

/* Define if include the em85 IAL engine */
/* #undef _EM85_IAL */

/* Define if include the em86 IAL engine */
/* #undef _EM86_IAL */

/* Define if include IAL engine for EMBEST ARM2410 */
/* #undef _EMBEST2410_IAL */

/* Define if include IAL engine for EMBEST ARM44B0 */
/* #undef _EMBEST44B0_IAL */

/* Define if include IAL engine for EP7211 */
/* #undef _EP7211_IAL */

/* Define if support EUCJP charset */
/* #undef _EUCJP_SUPPORT */

/* Define if support EUCKR charset */
/* #undef _EUCKR_SUPPORT */

/* Define if include IAL engine for xScale EVMV 1.0 */
/* #undef _EVMV10_IAL */

/* Define if include ANIMATION control */
/* #undef _EXT_CTRL_ANIMATION */

/* Define if include COOLBAR control */
/* #undef _EXT_CTRL_COOLBAR */

/* Define if include GRIDVIEW control */
/* #undef _EXT_CTRL_GRIDVIEW */

/* Define if include ICONVIEW control */
/* #undef _EXT_CTRL_ICONVIEW */

/* Define if include LISTVIEW control */
#define _EXT_CTRL_LISTVIEW 1

/* Define if include MONTHCALENDAR control */
#define _EXT_CTRL_MONTHCAL 1

#define _EXT_CTRL_ANIMATION 1 //add by yujun 20160309

/* Define if include SPINBOX control */
/* #undef _EXT_CTRL_SPINBOX */

/* Define if include TREEVIEW control */
/* #undef _EXT_CTRL_TREEVIEW */

/* Define if include skin support */
/* #undef _EXT_SKIN */

/* Define if include 16BPP FB subdriver */
/* #undef _FBLIN16_SUPPORT */

/* Define if include 1BPP FB subdriver (MSB is left) */
/* #undef _FBLIN1L_SUPPORT */

/* Define if include 1BPP FB subdriver (MSB is right) */
/* #undef _FBLIN1R_SUPPORT */

/* Define if include 24BPP FB subdriver */
/* #undef _FBLIN24_SUPPORT */

/* Define if include 2BPP FB subdriver (MSB is left) */
/* #undef _FBLIN2L_SUPPORT */

/* Define if include 2BPP FB subdriver (MSB is right) */
/* #undef _FBLIN2R_SUPPORT */

/* Define if include 32BPP FB subdriver */
/* #undef _FBLIN32_SUPPORT */

/* Define if include 4BPP FB subdriver (MSB is left) */
/* #undef _FBLIN4L_SUPPORT */

/* Define if include 4BPP FB subdriver (MSB is right) */
/* #undef _FBLIN4R_SUPPORT */

/* Define if include 8BPP FB subdriver */
/* #undef _FBLIN8_SUPPORT */

/* Define if include VGA16 FB subdriver */
/* #undef _FBVGA16_SUPPORT */

/* Define if include IAL engine for FFT7202 */
/* #undef _FFT7202_IAL */

/* Define if include IAL engine for EM85xx Front Panel and Remote Controller
   */
/* #undef _FIP_IAL */

/* Define if include fixed math routines */
#define _FIXED_MATH 1

/* Define if window style is flat */
/* #undef _FLAT_WINDOW_STYLE */

/* Define if include IAL engine for FXRM9200 */
/* #undef _FXRM9200_IAL */

/* Define if support GB18030 charset */
/* #undef _GB18030_SUPPORT */

/* Define if support GBK charset */
/* #undef _GBK_SUPPORT */

/* Define if support GB2312 charset */
/* #undef _GB_SUPPORT */

/* Define if support GIF bmp file format */
/* #undef _GIF_FILE_SUPPORT */

/* Define if include GPM mouse subdriver */
#define _GPM_SUPPORT 1

/* Define if is gray screen */
/* #undef _GRAY_SCREEN */

/* Define if support Greek charset */
/* #undef _GREEK_SUPPORT */

/* Define if has FreeType 2 */
/* #undef _HAS_FREETYPE2 */

/* Define if have math library */
#define _HAVE_MATH_LIB 1

/* Define if your Linux have text mode */
#define _HAVE_TEXT_MODE 1

/* Define if support Hebrew charset */
/* #undef _HEBREW_SUPPORT */

/* Define if include IAL engine for Helio Touch Panel */
/* #undef _HELIO_IAL */

/* Define if include IAL engine for HHARM2410R3 touch screen */
/* #undef _HH2410R3_IAL */

/* Define if include IAL engine for HHARM2440 touch screen */
/* #undef _HH2440_IAL */

/* Define if include IAL engine for HHARM44B0 touch screen */
/* #undef _HH44B0_IAL */

/* Define if include the IAL engine for HHCF5249 PS/2 keyboard and IrDA */
/* #undef _HH5249KBDIR_IAL */

/* Define if include GB2312 IME */
#define _IME_GB2312 1

/* Define if include GB2312 Intelligent Pinyin IME module */
#define _IME_GB2312_PINYIN 1

/* Define if include IMPS2 mouse subdriver */
#define _IMPS2_SUPPORT 1

/* Define if include in-core font: Courier */
/* #undef _INCOREFONT_COURIER */

/* Define if include in-core font: Helvetica */
/* #undef _INCOREFONT_HELV */

/* Define if include in-core font: SansSerif */
/* #undef _INCOREFONT_SANSSERIF */

/* Define if include in-core font: Symbol */
/* #undef _INCOREFONT_SYMBOL */

/* Define if include in-core font: VGAS */
/* #undef _INCOREFONT_VGAS */

/* Define if include in-core font: 12x12 fixed/ming RBF for BIG5 */
/* #undef _INCORERBF_BIG5_12 */

/* Define if include in-core font: 16x16 fixed/ming RBF for BIG5 */
/* #undef _INCORERBF_BIG5_16 */

/* Define if include in-core font: 24x24 fixed/ming RBF for BIG5 */
/* #undef _INCORERBF_BIG5_24 */

/* Define if include in-core font: 12x12 fixed/song RBF for GB2312 */
/* #undef _INCORERBF_GB12 */

/* Define if include in-core font: 16x16 fixed/song RBF for GB2312 */
/* #undef _INCORERBF_GB16 */

/* Define if include in-core font: 16x16 fixed/hei RBF for GB2312 */
/* #undef _INCORERBF_GB16_HEI */

/* Define if include in-core font: 24x24 fixed/song RBF for GB2312 */
/* #undef _INCORERBF_GB24 */

/* Define if include in-core font: 12-Pixel Kanji RBFs for SHIFT-JIS */
/* #undef _INCORERBF_KJ12 */

/* Define if include in-core font: 14-Pixel Kanji RBFs for SHIFT-JIS */
/* #undef _INCORERBF_KJ14 */

/* Define if include in-core font: 16-Pixel Kanji RBFs for SHIFT-JIS */
/* #undef _INCORERBF_KJ16 */

/* Define if include in-core font: 8x16 fixed RBF for ISO8859-1 */
/* #undef _INCORERBF_LATIN1_16 */

/* Define if include in-core font: 12x24 fixed RBF for ISO8859-1 */
/* #undef _INCORERBF_LATIN1_24 */

/* Define if build MiniGUI for no file I/O system */
/* #undef _INCORE_RES */

/* Define if include IAL engine for iPAQ */
/* #undef _IPAQ_IAL */

/* Define if support JPEG bmp file format */
/* #undef _JPG_FILE_SUPPORT */

/* Define if use the German keyboard layout */
/* #undef _KBD_LAYOUT_DE */

/* Define if use the German-Latin1 keyboard layout */
/* #undef _KBD_LAYOUT_DELATIN1 */

/* Define if use the Spanish keyboard layout */
/* #undef _KBD_LAYOUT_ES */

/* Define if use the Spanish CP850 keyboard layout */
/* #undef _KBD_LAYOUT_ESCP850 */

/* Define if use the French keyboard layout */
/* #undef _KBD_LAYOUT_FR */

/* Define if use the French PC keyboard layout */
/* #undef _KBD_LAYOUT_FRPC */

/* Define if use the Italian keyboard layout */
/* #undef _KBD_LAYOUT_IT */

/* Define if include IAL engine for L7200 */
/* #undef _L7200_IAL */

/* Define if support Latin 10 charset */
/* #undef _LATIN10_SUPPORT */

/* Define if support Latin 2 charset */
/* #undef _LATIN2_SUPPORT */

/* Define if support Latin 3 charset */
/* #undef _LATIN3_SUPPORT */

/* Define if support Latin 4 charset */
/* #undef _LATIN4_SUPPORT */

/* Define if support Latin 5 charset */
/* #undef _LATIN5_SUPPORT */

/* Define if support Latin 6 charset */
/* #undef _LATIN6_SUPPORT */

/* Define if support Latin 7 charset */
/* #undef _LATIN7_SUPPORT */

/* Define if support Latin 8 charset */
/* #undef _LATIN8_SUPPORT */

/* Define if support Latin 9 charset */
#define _LATIN9_SUPPORT 1

/* Define if support LBM bmp file format */
/* #undef _LBM_FILE_SUPPORT */

/* Define if include vcongui support */
/* #undef _LIB_VCONGUI */

/* Define if build lite version of MiniGUI */
/* #undef _LITE_VERSION */

/* Define if include IAL engine for uClinux touch screen palm/mc68ez328 */
/* #undef _MC68X328_IAL */

/* Define if include About MiniGUI Dialog Box */
/* #undef _MISC_ABOUTDLG */

/* Define if include code for mouse calibration */
/* #undef _MISC_MOUSECALIBRATE */

/* Define if include code for screenshots */
/* #undef _MISC_SAVESCREEN */

/* Define if we can move window by mouse */
#define _MOVE_WINDOW_BY_MOUSE 1

/* Define if include IAL engine for MPC823 */
/* #undef _MPC823_IAL */

/* Define if include MS3 mouse subdriver */
#define _MS3_SUPPORT 1

/* Define if include messages' string names */
/* #undef _MSG_STRING */

/* Define if include MS mouse subdriver */
#define _MS_SUPPORT 1

/* Define if support native graphics engine on Common LCD */
/* #undef _NATIVE_GAL_COMMLCD */

/* Define if include native graphics engine */
/* #undef _NATIVE_GAL_ENGINE */

/* Define if support native graphics engine on FBCON */
/* #undef _NATIVE_GAL_FBCON */

/* Define if support native graphics engine on QVFB */
/* #undef _NATIVE_GAL_QVFB */

/* Define if include native (Linux console) IAL engine */
#define _NATIVE_IAL_ENGINE 1

/* Define if include NEWGAL engine for BF533 OSD via SPI */
/* #undef _NEWGAL_ENGINE_BF533 */

/* Define if include NEWGAL engine for Common LCD */
/* #undef _NEWGAL_ENGINE_COMMLCD */

/* Define if include dummy NEWGAL engine */
/* #undef _NEWGAL_ENGINE_DUMMY */

/* Define if include NEWGAL engine for EM85xx OSD */
/* #undef _NEWGAL_ENGINE_EM85XXOSD */

/* Define if include FrameBuffer console NEWGAL engine */
/* #undef _NEWGAL_ENGINE_FBCON */

/* Define if include gm8126 NEWGAL engine */
/* #undef _NEWGAL_ENGINE_GM8126 */

/* Define if include gm8181 NEWGAL engine */
/* #undef _NEWGAL_ENGINE_GM8181 */

/* Define if include his3520 NEWGAL engine */
/* #undef _NEWGAL_ENGINE_HIS3520 */

/* Define if include his3531 NEWGAL engine */
#define _NEWGAL_ENGINE_HIS3531 1

/* Define if include NEWGAL engine for mb93493 YUV FrameBuffer driver */
/* #undef _NEWGAL_ENGINE_MB93493 */

/* Define if include Qt Virtual FrameBuffer NEWGAL engine */
/* #undef _NEWGAL_ENGINE_QVFB */

/* Define if include Shadow NEWGAL engine */
/* #undef _NEWGAL_ENGINE_SHADOW */

/* Define if include NEWGAL engine for SVPXX OSD */
/* #undef _NEWGAL_ENGINE_SVPXXOSD */

/* Define if include NEWGAL engine for UTPMC */
/* #undef _NEWGAL_ENGINE_UTPMC */

/* Define if include windows Virtual FrameBuffer NEWGAL engine */
/* #undef _NEWGAL_ENGINE_WVFB */

/* Define if include IAL engine for OKWAP Palm2 */
/* #undef _PALMII_IAL */

/* Define if window style is PC 3D */
#define _PC3D_WINDOW_STYLE 1

/* Define if support PCX bmp file format */
/* #undef _PCX_FILE_SUPPORT */

/* Define if window style is phone */
/* #undef _PHONE_WINDOW_STYLE */

/* Define if support PNG bmp file format */
#define _PNG_FILE_SUPPORT 1

/* Define if include PS2 mouse subdriver */
#define _PS2_SUPPORT 1

/* Define if include IAL engine for PX255B */
/* #undef _PX255B_IAL */

/* Define if support QPF font */
#define _QPF_SUPPORT 1

/* Define if include the QVFB IAL engine */
/* #undef _QVFB_IAL */

/* Define if include the random IAL engine */
/* #undef _RANDOM_IAL */

/* Define if support raw bitmap fonts */
#define _RBF_SUPPORT 1

/* Define to 0 if use clockwise rotation of screen, otherwise to 1 */
/* #undef _ROT_DIR_CW */

/* Define if include SaveBitmap function */
/* #undef _SAVE_BITMAP */

/* Define if support SHIFTJIS charset */
/* #undef _SHIFTJIS_SUPPORT */

/* Define if include IAL engine for touch screen of SkyEye EP7312 simulation
   */
/* #undef _SKYEYE_EP7312_IAL */

/* Define if include IAL engine for SMDK2410 touch screen */
/* #undef _SMDK2410_IAL */

/* Define if build Standalone version of MiniGUI-Lite */
/* #undef _STAND_ALONE */

/* Define if include SVGALib engine */
/* #undef _SVGALIB */

/* Define if include IAL engine for WinBond SPVXX */
/* #undef _SVPXX_IAL */

/* Define if include IAL engine for MT T800 */
/* #undef _T800_IAL */

/* Define if include IAL engine for Tongfang STB */
/* #undef _TFSTB_IAL */

/* Define if support TGA bmp file format */
/* #undef _TGA_FILE_SUPPORT */

/* Define if support Thai charset */
/* #undef _THAI_SUPPORT */

/* Define if include IAL engine for THOR */
/* #undef _THOR_IAL */

/* Define if the unit of timer is 10ms */
#define _TIMER_UNIT_10MS 1

/* Define if it is tiny screen */
/* #undef _TINY_SCREEN */

/* Define if trace message dispatching of MiniGUI */
/* #undef _TRACE_MSG */

/* Define if support TrueType font based on FreeType 1.3 or FreeType 2 */
/* #undef _TTF_SUPPORT */

/* Define if support Adobe Type1 fonts */
/* #undef _TYPE1_SUPPORT */

/* Define if include IAL engine for UCB1X00 */
/* #undef _UCB1X00_IAL */

/* Define if support UNICODE */
#define _UNICODE_SUPPORT 1
#define _GB_SUPPORT 1    //zhangxinda added for Chinese Language


/* Define if use fixed scrollbar bar length */
/* #undef _USE_FIXED_SB_BARLEN */

/* Define if use minigui_entry function in MiniGUI */
/* #undef _USE_MINIGUIENTRY */

/* Define if use new GAL interfaces */
#define _USE_NEWGAL 1

/* Define if use own implementation of malloc functions */
/* #undef _USE_OWN_MALLOC */

/* Define if use own implementation of pthread functions */
/* #undef _USE_OWN_PTHREAD */

/* Define if use own implementation of stdio functions */
/* #undef _USE_OWN_STDIO */

/* Define if include the UTPMC IAL engine */
/* #undef _UTPMC_IAL */

/* Define if support var bitmap fonts */
/* #undef _VBF_SUPPORT */

/* Define if include VGA 16-color graphics engine */
/* #undef _VGA16_GAL */

/* Define if include IAL engine for NEC VR4181 */
/* #undef _VR4181_IAL */

/* Define if include the WVFB IAL engine */
/* #undef _WVFB_IAL */

/* Define if compile for Cygwin platform */
/* #undef __CYGWIN__ */

/* Define if compile for OpenDarwin */
/* #undef __DARWIN__ */

/* Define if compile for eCos */
/* #undef __ECOS__ */

/* Define if compile for Linux */
#define __LINUX__ 1

/* Define if compile for non-UNIX like OS */
/* #undef __NOUNIX__ */

/* Define if compile for Nucleus */
/* #undef __NUCLEUS__ */

/* Define for Linux FrameBuffer console (used by Shadow NEGAL engine) */
/* #undef __TARGET_FBCON__ */

/* Define for Linux QVFB (used by Shadow NEGAL engine) */
/* #undef __TARGET_QVFB__ */

/* Define for unknown target */
#define __TARGET_UNKNOWN__ 1

/* Define for VirualFone ANVIL target */
/* #undef __TARGET_VFANVIL__ */

/* Define for VxWorks on i386 */
/* #undef __TARGET_VXI386__ */

/* Define for the Windows QVFB (used by Shadow NEGAL engine) */
/* #undef __TARGET_WVFB__ */

/* Define if compile for ThreadX */
/* #undef __THREADX__ */

/* Define if compile for uC/OS-II */
/* #undef __UCOSII__ */

/* Define if compile for VxWorks */
/* #undef __VXWORKS__ */

/* Define if compile for Winbond SWLinux */
/* #undef __WINBOND_SWLINUX__ */

/* Define if compile for uClinux */
/* #undef __uClinux__ */

/* Define to empty if `const' does not conform to ANSI C. */
/* #undef const */

/* Define to `__inline__' or `__inline' if that's what the C compiler
   calls it, or to nothing if 'inline' is not supported under any name.  */
#ifndef __cplusplus
/* #undef inline */
#endif

/* Define to `unsigned int' if <sys/types.h> does not define. */
/* #undef size_t */
