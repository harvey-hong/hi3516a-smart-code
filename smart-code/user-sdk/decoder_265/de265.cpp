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

#define DEBUG_INSERT_STREAM_ERRORS 0


#include "de265.h"
#include "util.h"



#include <assert.h>
#include <string.h>
#include <stdlib.h>


// TODO: should be in some vps.c related header
extern "C" {
// LIBDE265_API const char *de265_get_version(void)
// {
    // return (LIBDE265_VERSION);
// }

// LIBDE265_API uint32_t de265_get_version_number(void)
// {
    // return (LIBDE265_NUMERIC_VERSION);
// }

// LIBDE265_API int de265_get_version_number_major(void)
// {
  // return ((LIBDE265_NUMERIC_VERSION)>>24) & 0xFF;
// }

// LIBDE265_API int de265_get_version_number_minor(void)
// {
  // return ((LIBDE265_NUMERIC_VERSION)>>16) & 0xFF;
// }

// LIBDE265_API int de265_get_version_number_maintenance(void)
// {
  // return ((LIBDE265_NUMERIC_VERSION)>>8) & 0xFF;
// }


// LIBDE265_API const char* de265_get_error_text(de265_error err)
// {
  // switch (err) {
  // case DE265_OK: return "no error";
  // case DE265_ERROR_NO_SUCH_FILE: return "no such file";
    // //case DE265_ERROR_NO_STARTCODE: return "no startcode found";
    // //case DE265_ERROR_EOF: return "end of file";
  // case DE265_ERROR_COEFFICIENT_OUT_OF_IMAGE_BOUNDS: return "coefficient out of image bounds";
  // case DE265_ERROR_CHECKSUM_MISMATCH: return "image checksum mismatch";
  // case DE265_ERROR_CTB_OUTSIDE_IMAGE_AREA: return "CTB outside of image area";
  // case DE265_ERROR_OUT_OF_MEMORY: return "out of memory";
  // case DE265_ERROR_CODED_PARAMETER_OUT_OF_RANGE: return "coded parameter out of range";
  // case DE265_ERROR_IMAGE_BUFFER_FULL: return "DPB/output queue full";
  // case DE265_ERROR_CANNOT_START_THREADPOOL: return "cannot start decoding threads";
  // case DE265_ERROR_LIBRARY_INITIALIZATION_FAILED: return "global library initialization failed";
  // case DE265_ERROR_LIBRARY_NOT_INITIALIZED: return "cannot free library data (not initialized";

  // //case DE265_ERROR_MAX_THREAD_CONTEXTS_EXCEEDED:
  // //  return "internal error: maximum number of thread contexts exceeded";
  // //case DE265_ERROR_MAX_NUMBER_OF_SLICES_EXCEEDED:
  // //  return "internal error: maximum number of slices exceeded";
  // case DE265_ERROR_NOT_IMPLEMENTED_YET:
    // return "unimplemented decoder feature";
    // //case DE265_ERROR_SCALING_LIST_NOT_IMPLEMENTED:
    // //return "scaling list not implemented";

  // case DE265_ERROR_WAITING_FOR_INPUT_DATA:
    // return "no more input data, decoder stalled";
  // case DE265_ERROR_CANNOT_PROCESS_SEI:
    // return "SEI data cannot be processed";
  // case DE265_ERROR_PARAMETER_PARSING:
    // return "command-line parameter error";
  // case DE265_ERROR_NO_INITIAL_SLICE_HEADER:
    // return "first slice missing, cannot decode dependent slice";
  // case DE265_ERROR_PREMATURE_END_OF_SLICE:
    // return "premature end of slice data";
  // case DE265_ERROR_UNSPECIFIED_DECODING_ERROR:
    // return "unspecified decoding error";

  // case DE265_WARNING_NO_WPP_CANNOT_USE_MULTITHREADING:
    // return "Cannot run decoder multi-threaded because stream does not support WPP";
  // case DE265_WARNING_WARNING_BUFFER_FULL:
    // return "Too many warnings queued";
  // case DE265_WARNING_PREMATURE_END_OF_SLICE_SEGMENT:
    // return "Premature end of slice segment";
  // case DE265_WARNING_INCORRECT_ENTRY_POINT_OFFSET:
    // return "Incorrect entry-point offsets";
  // case DE265_WARNING_CTB_OUTSIDE_IMAGE_AREA:
    // return "CTB outside of image area (concealing stream error...)";
  // case DE265_WARNING_SPS_HEADER_INVALID:
    // return "sps header invalid";
  // case DE265_WARNING_PPS_HEADER_INVALID:
    // return "pps header invalid";
  // case DE265_WARNING_SLICEHEADER_INVALID:
    // return "slice header invalid";
  // case DE265_WARNING_INCORRECT_MOTION_VECTOR_SCALING:
    // return "impossible motion vector scaling";
  // case DE265_WARNING_NONEXISTING_PPS_REFERENCED:
    // return "non-existing PPS referenced";
  // case DE265_WARNING_NONEXISTING_SPS_REFERENCED:
    // return "non-existing SPS referenced";
  // case DE265_WARNING_BOTH_PREDFLAGS_ZERO:
    // return "both predFlags[] are zero in MC";
  // case DE265_WARNING_NONEXISTING_REFERENCE_PICTURE_ACCESSED:
    // return "non-existing reference picture accessed";
  // case DE265_WARNING_NUMMVP_NOT_EQUAL_TO_NUMMVQ:
    // return "numMV_P != numMV_Q in deblocking";
  // case DE265_WARNING_NUMBER_OF_SHORT_TERM_REF_PIC_SETS_OUT_OF_RANGE:
    // return "number of short-term ref-pic-sets out of range";
  // case DE265_WARNING_SHORT_TERM_REF_PIC_SET_OUT_OF_RANGE:
    // return "short-term ref-pic-set index out of range";
  // case DE265_WARNING_FAULTY_REFERENCE_PICTURE_LIST:
    // return "faulty reference picture list";
  // case DE265_WARNING_EOSS_BIT_NOT_SET:
    // return "end_of_sub_stream_one_bit not set to 1 when it should be";
  // case DE265_WARNING_MAX_NUM_REF_PICS_EXCEEDED:
    // return "maximum number of reference pictures exceeded";
  // case DE265_WARNING_INVALID_CHROMA_FORMAT:
    // return "invalid chroma format in SPS header";
  // case DE265_WARNING_SLICE_SEGMENT_ADDRESS_INVALID:
    // return "slice segment address invalid";
  // case DE265_WARNING_DEPENDENT_SLICE_WITH_ADDRESS_ZERO:
    // return "dependent slice with address 0";
  // case DE265_WARNING_NUMBER_OF_THREADS_LIMITED_TO_MAXIMUM:
    // return "number of threads limited to maximum amount";
  // case DE265_NON_EXISTING_LT_REFERENCE_CANDIDATE_IN_SLICE_HEADER:
    // return "non-existing long-term reference candidate specified in slice header";
  // case DE265_WARNING_CANNOT_APPLY_SAO_OUT_OF_MEMORY:
    // return "cannot apply SAO because we ran out of memory";
  // case DE265_WARNING_SPS_MISSING_CANNOT_DECODE_SEI:
    // return "SPS header missing, cannot decode SEI";
  // case DE265_WARNING_COLLOCATED_MOTION_VECTOR_OUTSIDE_IMAGE_AREA:
    // return "collocated motion-vector is outside image area";

  // default: return "unknown error";
  // }
// }

// LIBDE265_API int de265_isOK(de265_error err)
// {
  // return err == DE265_OK || err >= 1000;
// }


}
