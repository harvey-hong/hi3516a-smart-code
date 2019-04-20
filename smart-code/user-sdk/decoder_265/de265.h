/*
 * H.265 video codec.
 * Copyright (c) 2013-2014 struktur AG, Dirk Farin <farin@struktur.de>
 *
 * This file is part of libde265.
 *
 * libde265 is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as
 * published by the Free Software Foundation, either version 3 of
 * the License, or (at your option) any later version.
 *
 * libde265 is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with libde265.  If not, see <http://www.gnu.org/licenses/>.
*/


#ifndef DE265_H
#define DE265_H

#ifdef __cplusplus
extern "C" {
#endif

#include "de265-version.h"

//#define inline static __inline


#ifndef __STDC_LIMIT_MACROS
#define __STDC_LIMIT_MACROS 1
#endif
#include <stdint.h>

#if defined(_MSC_VER) && !defined(LIBDE265_STATIC_BUILD)
  #ifdef LIBDE265_EXPORTS
  #define LIBDE265_API __declspec(dllexport)
  #else
  #define LIBDE265_API __declspec(dllimport)
  #endif
#elif HAVE_VISIBILITY
  #ifdef LIBDE265_EXPORTS
  #define LIBDE265_API __attribute__((__visibility__("default")))
  #else
  #define LIBDE265_API
  #endif
#else
  #define LIBDE265_API
#endif

#if __GNUC__
#define LIBDE265_DEPRECATED __attribute__((deprecated))
#elif defined(_MSC_VER)
#define LIBDE265_DEPRECATED __declspec(deprecated)
#else
#define LIBDE265_DEPRECATED
#endif

#if defined(_MSC_VER)
#define LIBDE265_INLINE __inline
#else
#define LIBDE265_INLINE inline
#endif

/* === version numbers === */

// version of linked libde265 library
//LIBDE265_API const char *de265_get_version(void);
//LIBDE265_API uint32_t de265_get_version_number(void);

//LIBDE265_API int de265_get_version_number_major(void);
//LIBDE265_API int de265_get_version_number_minor(void);
//LIBDE265_API int de265_get_version_number_maintenance(void);


/* === error codes === */

typedef enum {
  DE265_OK = 0,
  DE265_ERROR_NO_SUCH_FILE=1,
  //DE265_ERROR_NO_STARTCODE=2,  obsolet
  //DE265_ERROR_EOF=3,
  DE265_ERROR_COEFFICIENT_OUT_OF_IMAGE_BOUNDS=4,
  DE265_ERROR_CHECKSUM_MISMATCH=5,
  DE265_ERROR_CTB_OUTSIDE_IMAGE_AREA=6,
  DE265_ERROR_OUT_OF_MEMORY=7,
  DE265_ERROR_CODED_PARAMETER_OUT_OF_RANGE=8,
  DE265_ERROR_IMAGE_BUFFER_FULL=9,
  DE265_ERROR_CANNOT_START_THREADPOOL=10,
  DE265_ERROR_LIBRARY_INITIALIZATION_FAILED=11,
  DE265_ERROR_LIBRARY_NOT_INITIALIZED=12,
  DE265_ERROR_WAITING_FOR_INPUT_DATA=13,
  DE265_ERROR_CANNOT_PROCESS_SEI=14,
  DE265_ERROR_PARAMETER_PARSING=15,
  DE265_ERROR_NO_INITIAL_SLICE_HEADER=16,
  DE265_ERROR_PREMATURE_END_OF_SLICE=17,
  DE265_ERROR_UNSPECIFIED_DECODING_ERROR=18,

  // --- errors that should become obsolete in later libde265 versions ---

  //DE265_ERROR_MAX_THREAD_CONTEXTS_EXCEEDED = 500, obsolet
  //DE265_ERROR_MAX_NUMBER_OF_SLICES_EXCEEDED = 501, obsolet
  DE265_ERROR_NOT_IMPLEMENTED_YET = 502,
  //DE265_ERROR_SCALING_LIST_NOT_IMPLEMENTED = 502, obsolet

  // --- warnings ---

  DE265_WARNING_NO_WPP_CANNOT_USE_MULTITHREADING = 1000,
  DE265_WARNING_WARNING_BUFFER_FULL=1001,
  DE265_WARNING_PREMATURE_END_OF_SLICE_SEGMENT=1002,
  DE265_WARNING_INCORRECT_ENTRY_POINT_OFFSET=1003,
  DE265_WARNING_CTB_OUTSIDE_IMAGE_AREA=1004,
  DE265_WARNING_SPS_HEADER_INVALID=1005,
  DE265_WARNING_PPS_HEADER_INVALID=1006,
  DE265_WARNING_SLICEHEADER_INVALID=1007,
  DE265_WARNING_INCORRECT_MOTION_VECTOR_SCALING=1008,
  DE265_WARNING_NONEXISTING_PPS_REFERENCED=1009,
  DE265_WARNING_NONEXISTING_SPS_REFERENCED=1010,
  DE265_WARNING_BOTH_PREDFLAGS_ZERO=1011,
  DE265_WARNING_NONEXISTING_REFERENCE_PICTURE_ACCESSED=1012,
  DE265_WARNING_NUMMVP_NOT_EQUAL_TO_NUMMVQ=1013,
  DE265_WARNING_NUMBER_OF_SHORT_TERM_REF_PIC_SETS_OUT_OF_RANGE=1014,
  DE265_WARNING_SHORT_TERM_REF_PIC_SET_OUT_OF_RANGE=1015,
  DE265_WARNING_FAULTY_REFERENCE_PICTURE_LIST=1016,
  DE265_WARNING_EOSS_BIT_NOT_SET=1017,
  DE265_WARNING_MAX_NUM_REF_PICS_EXCEEDED=1018,
  DE265_WARNING_INVALID_CHROMA_FORMAT=1019,
  DE265_WARNING_SLICE_SEGMENT_ADDRESS_INVALID=1020,
  DE265_WARNING_DEPENDENT_SLICE_WITH_ADDRESS_ZERO=1021,
  DE265_WARNING_NUMBER_OF_THREADS_LIMITED_TO_MAXIMUM=1022,
  DE265_NON_EXISTING_LT_REFERENCE_CANDIDATE_IN_SLICE_HEADER=1023,
  DE265_WARNING_CANNOT_APPLY_SAO_OUT_OF_MEMORY=1024,
  DE265_WARNING_SPS_MISSING_CANNOT_DECODE_SEI=1025,
  DE265_WARNING_COLLOCATED_MOTION_VECTOR_OUTSIDE_IMAGE_AREA=1026
} de265_error;

//LIBDE265_API const char* de265_get_error_text(de265_error err);

/* Returns true, if 'err' is DE265_OK or a warning.
 */
//LIBDE265_API int  de265_isOK(de265_error err);


#define DE265_MAX_VPS_SETS 16   // this is the maximum as defined in the standard
#define DE265_MAX_SPS_SETS 16   // this is the maximum as defined in the standard
#define DE265_MAX_PPS_SETS 64   // this is the maximum as defined in the standard


#ifdef __cplusplus
}
#endif

#endif
