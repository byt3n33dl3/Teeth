/*******************************************************************************
 * Copyright (c) 2008-2024 The Khronos Group.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * C licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 ******************************************************************************/

#ifndef OPENCL_CL_GL_H_
#define OPENCL_CL_GL_H_

/*
** This header is generated from the Khronos OpenCL XML API Registry.
*/

#include "pro_platform.h"
#pragma message("The extensions in pro_platform.h have been moved into pro_platform.h.  Please include pro_platform.h directly.")

/* CL_NO_PROTOTYPES implies CL_NO_EXTENSION_PROTOTYPES: */
#if defined(CL_NO_PROTOTYPES) && !defined(CL_NO_EXTENSION_PROTOTYPES)
#define CL_NO_EXTENSION_PROTOTYPES
#endif

/* CL_NO_EXTENSION_PROTOTYPES implies
   CL_NO_ICD_DISPATCH_EXTENSION_PROTOTYPES and
   CL_NO_NON_ICD_DISPATCH_EXTENSION_PROTOTYPES: */
#if defined(CL_NO_EXTENSION_PROTOTYPES) && \
    !defined(CL_NO_ICD_DISPATCH_EXTENSION_PROTOTYPES)
#define CL_NO_ICD_DISPATCH_EXTENSION_PROTOTYPES
#endif
#if defined(CL_NO_EXTENSION_PROTOTYPES) && \
    !defined(CL_NO_NON_ICD_DISPATCH_EXTENSION_PROTOTYPES)
#define CL_NO_NON_ICD_DISPATCH_EXTENSION_PROTOTYPES
#endif

#ifdef __cplusplus
extern "C" {
#endif

/***************************************************************
* cl_khr_gl_sharing
***************************************************************/
#define cl_khr_gl_sharing 1
#define CL_KHR_GL_SHARING_EXTENSION_NAME \
    "cl_khr_gl_sharing"

typedef cl_uint             cl_gl_context_info;

/* Error codes */
#define CL_INVALID_GL_SHAREGROUP_REFERENCE_KHR              -1000

/* cl_gl_context_info */
#define CL_CURRENT_DEVICE_FOR_GL_CONTEXT_KHR                0x2006
#define CL_DEVICES_FOR_GL_CONTEXT_KHR                       0x2007

/* Additional cl_context_properties */
#define CL_GL_CONTEXT_KHR                                   0x2008
#define CL_EGL_DISPLAY_KHR                                  0x2009
#define CL_GLX_DISPLAY_KHR                                  0x200A
#define CL_WGL_HDC_KHR                                      0x200B
#define CL_CGL_SHAREGROUP_KHR                               0x200C

typedef cl_uint             cl_gl_object_type;
typedef cl_uint             cl_gl_texture_info;
typedef cl_uint             cl_gl_platform_info;

/* cl_gl_object_type */
#define CL_GL_OBJECT_BUFFER                                 0x2000
#define CL_GL_OBJECT_TEXTURE2D                              0x2001
#define CL_GL_OBJECT_TEXTURE3D                              0x2002
#define CL_GL_OBJECT_RENDERBUFFER                           0x2003

#if defined(CL_VERSION_1_2)
/* cl_gl_object_type */
#define CL_GL_OBJECT_TEXTURE2D_ARRAY                        0x200E
#define CL_GL_OBJECT_TEXTURE1D                              0x200F
#define CL_GL_OBJECT_TEXTURE1D_ARRAY                        0x2010
#define CL_GL_OBJECT_TEXTURE_BUFFER                         0x2011

#endif /* defined(CL_VERSION_1_2) */

/* cl_gl_texture_info */
#define CL_GL_TEXTURE_TARGET                                0x2004
#define CL_GL_MIPMAP_LEVEL                                  0x2005


typedef cl_int CL_API_CALL
clGetGLContextInfoKHR_t(
    const cl_context_properties* properties,
    cl_gl_context_info param_name,
    size_t param_value_size,
    void* param_value,
    size_t* param_value_size_ret);

typedef clGetGLContextInfoKHR_t *
clGetGLContextInfoKHR_fn CL_API_SUFFIX__VERSION_1_0;

typedef cl_mem CL_API_CALL
clCreateFromGLBuffer_t(
    cl_context context,
    cl_mem_flags flags,
    cl_GLuint bufobj,
    cl_int* errcode_ret);

typedef clCreateFromGLBuffer_t *
clCreateFromGLBuffer_fn CL_API_SUFFIX__VERSION_1_0;

#if !defined(CL_NO_ICD_DISPATCH_EXTENSION_PROTOTYPES)

extern CL_API_ENTRY cl_int CL_API_CALL
clGetGLContextInfoKHR(
    const cl_context_properties* properties,
    cl_gl_context_info param_name,
    size_t param_value_size,
    void* param_value,
    size_t* param_value_size_ret) CL_API_SUFFIX__VERSION_1_0;

extern CL_API_ENTRY cl_mem CL_API_CALL
clCreateFromGLBuffer(
    cl_context context,
    cl_mem_flags flags,
    cl_GLuint bufobj,
    cl_int* errcode_ret) CL_API_SUFFIX__VERSION_1_0;

#endif /* !defined(CL_NO_ICD_DISPATCH_EXTENSION_PROTOTYPES) */

#if defined(CL_VERSION_1_2)

typedef cl_mem CL_API_CALL
clCreateFromGLTexture_t(
    cl_context context,
    cl_mem_flags flags,
    cl_GLenum target,
    cl_GLint miplevel,
    cl_GLuint texture,
    cl_int* errcode_ret);

typedef clCreateFromGLTexture_t *
clCreateFromGLTexture_fn CL_API_SUFFIX__VERSION_1_2;

#if !defined(CL_NO_ICD_DISPATCH_EXTENSION_PROTOTYPES)

extern CL_API_ENTRY cl_mem CL_API_CALL
clCreateFromGLTexture(
    cl_context context,
    cl_mem_flags flags,
    cl_GLenum target,
    cl_GLint miplevel,
    cl_GLuint texture,
    cl_int* errcode_ret) CL_API_SUFFIX__VERSION_1_2;

#endif /* !defined(CL_NO_ICD_DISPATCH_EXTENSION_PROTOTYPES) */

#endif /* defined(CL_VERSION_1_2) */


typedef cl_mem CL_API_CALL
clCreateFromGLRenderbuffer_t(
    cl_context context,
    cl_mem_flags flags,
    cl_GLuint renderbuffer,
    cl_int* errcode_ret);

typedef clCreateFromGLRenderbuffer_t *
clCreateFromGLRenderbuffer_fn CL_API_SUFFIX__VERSION_1_0;

typedef cl_int CL_API_CALL
clGetGLObjectInfo_t(
    cl_mem memobj,
    cl_gl_object_type* gl_object_type,
    cl_GLuint* gl_object_name);

typedef clGetGLObjectInfo_t *
clGetGLObjectInfo_fn CL_API_SUFFIX__VERSION_1_0;

typedef cl_int CL_API_CALL
clGetGLTextureInfo_t(
    cl_mem memobj,
    cl_gl_texture_info param_name,
    size_t param_value_size,
    void* param_value,
    size_t* param_value_size_ret);

typedef clGetGLTextureInfo_t *
clGetGLTextureInfo_fn CL_API_SUFFIX__VERSION_1_0;

typedef cl_int CL_API_CALL
clEnqueueAcquireGLObjects_t(
    cl_command_queue command_queue,
    cl_uint num_objects,
    const cl_mem* mem_objects,
    cl_uint num_events_in_wait_list,
    const cl_event* event_wait_list,
    cl_event* event);

typedef clEnqueueAcquireGLObjects_t *
clEnqueueAcquireGLObjects_fn CL_API_SUFFIX__VERSION_1_0;

typedef cl_int CL_API_CALL
clEnqueueReleaseGLObjects_t(
    cl_command_queue command_queue,
    cl_uint num_objects,
    const cl_mem* mem_objects,
    cl_uint num_events_in_wait_list,
    const cl_event* event_wait_list,
    cl_event* event);

typedef clEnqueueReleaseGLObjects_t *
clEnqueueReleaseGLObjects_fn CL_API_SUFFIX__VERSION_1_0;

#if !defined(CL_NO_ICD_DISPATCH_EXTENSION_PROTOTYPES)

extern CL_API_ENTRY cl_mem CL_API_CALL
clCreateFromGLRenderbuffer(
    cl_context context,
    cl_mem_flags flags,
    cl_GLuint renderbuffer,
    cl_int* errcode_ret) CL_API_SUFFIX__VERSION_1_0;

extern CL_API_ENTRY cl_int CL_API_CALL
clGetGLObjectInfo(
    cl_mem memobj,
    cl_gl_object_type* gl_object_type,
    cl_GLuint* gl_object_name) CL_API_SUFFIX__VERSION_1_0;

extern CL_API_ENTRY cl_int CL_API_CALL
clGetGLTextureInfo(
    cl_mem memobj,
    cl_gl_texture_info param_name,
    size_t param_value_size,
    void* param_value,
    size_t* param_value_size_ret) CL_API_SUFFIX__VERSION_1_0;

extern CL_API_ENTRY cl_int CL_API_CALL
clEnqueueAcquireGLObjects(
    cl_command_queue command_queue,
    cl_uint num_objects,
    const cl_mem* mem_objects,
    cl_uint num_events_in_wait_list,
    const cl_event* event_wait_list,
    cl_event* event) CL_API_SUFFIX__VERSION_1_0;

extern CL_API_ENTRY cl_int CL_API_CALL
clEnqueueReleaseGLObjects(
    cl_command_queue command_queue,
    cl_uint num_objects,
    const cl_mem* mem_objects,
    cl_uint num_events_in_wait_list,
    const cl_event* event_wait_list,
    cl_event* event) CL_API_SUFFIX__VERSION_1_0;

#endif /* !defined(CL_NO_ICD_DISPATCH_EXTENSION_PROTOTYPES) */

/* OpenCL 1.0 APIs that were deprecated in OpenCL 1.2 */

typedef cl_mem CL_API_CALL
clCreateFromGLTexture2D_t(
    cl_context context,
    cl_mem_flags flags,
    cl_GLenum target,
    cl_GLint miplevel,
    cl_GLuint texture,
    cl_int* errcode_ret);

typedef clCreateFromGLTexture2D_t *
clCreateFromGLTexture2D_fn CL_API_SUFFIX__VERSION_1_1_DEPRECATED;

typedef cl_mem CL_API_CALL
clCreateFromGLTexture3D_t(
    cl_context context,
    cl_mem_flags flags,
    cl_GLenum target,
    cl_GLint miplevel,
    cl_GLuint texture,
    cl_int* errcode_ret);

typedef clCreateFromGLTexture3D_t *
clCreateFromGLTexture3D_fn CL_API_SUFFIX__VERSION_1_1_DEPRECATED;

#if !defined(CL_NO_ICD_DISPATCH_EXTENSION_PROTOTYPES)

extern CL_API_ENTRY cl_mem CL_API_CALL
clCreateFromGLTexture2D(
    cl_context context,
    cl_mem_flags flags,
    cl_GLenum target,
    cl_GLint miplevel,
    cl_GLuint texture,
    cl_int* errcode_ret) CL_API_SUFFIX__VERSION_1_1_DEPRECATED;

extern CL_API_ENTRY cl_mem CL_API_CALL
clCreateFromGLTexture3D(
    cl_context context,
    cl_mem_flags flags,
    cl_GLenum target,
    cl_GLint miplevel,
    cl_GLuint texture,
    cl_int* errcode_ret) CL_API_SUFFIX__VERSION_1_1_DEPRECATED;

#endif /* !defined(CL_NO_ICD_DISPATCH_EXTENSION_PROTOTYPES) */

/***************************************************************
* cl_khr_gl_event
***************************************************************/
#define cl_khr_gl_event 1
#define CL_KHR_GL_EVENT_EXTENSION_NAME \
    "cl_khr_gl_event"

typedef struct __GLsync *   cl_GLsync;

/* cl_command_type */
#define CL_COMMAND_GL_FENCE_SYNC_OBJECT_KHR                 0x200D


typedef cl_event CL_API_CALL
clCreateEventFromGLsyncKHR_t(
    cl_context context,
    cl_GLsync sync,
    cl_int* errcode_ret);

typedef clCreateEventFromGLsyncKHR_t *
clCreateEventFromGLsyncKHR_fn CL_API_SUFFIX__VERSION_1_1;

#if !defined(CL_NO_ICD_DISPATCH_EXTENSION_PROTOTYPES)

extern CL_API_ENTRY cl_event CL_API_CALL
clCreateEventFromGLsyncKHR(
    cl_context context,
    cl_GLsync sync,
    cl_int* errcode_ret) CL_API_SUFFIX__VERSION_1_1;

#endif /* !defined(CL_NO_ICD_DISPATCH_EXTENSION_PROTOTYPES) */

/***************************************************************
* cl_khr_gl_depth_images
***************************************************************/
#define cl_khr_gl_depth_images 1
#define CL_KHR_GL_DEPTH_IMAGES_EXTENSION_NAME \
    "cl_khr_gl_depth_images"

/* cl_channel_order */
#define CL_DEPTH_STENCIL                                    0x10BE

/* cl_channel_type */
#define CL_UNORM_INT24                                      0x10DF

/***************************************************************
* cl_khr_gl_msaa_sharing
***************************************************************/
#define cl_khr_gl_msaa_sharing 1
#define CL_KHR_GL_MSAA_SHARING_EXTENSION_NAME \
    "cl_khr_gl_msaa_sharing"

/* cl_gl_texture_info */
#define CL_GL_NUM_SAMPLES                                   0x2012

/***************************************************************
* cl_intel_sharing_format_query_gl
***************************************************************/
#define cl_intel_sharing_format_query_gl 1
#define CL_INTEL_SHARING_FORMAT_QUERY_GL_EXTENSION_NAME \
    "cl_intel_sharing_format_query_gl"

/* when cl_khr_gl_sharing is supported */

typedef cl_int CL_API_CALL
clGetSupportedGLTextureFormatsINTEL_t(
    cl_context context,
    cl_mem_flags flags,
    cl_mem_object_type image_type,
    cl_uint num_entries,
    cl_GLenum* gl_formats,
    cl_uint* num_texture_formats);

typedef clGetSupportedGLTextureFormatsINTEL_t *
clGetSupportedGLTextureFormatsINTEL_fn ;

#if !defined(CL_NO_NON_ICD_DISPATCH_EXTENSION_PROTOTYPES)

extern CL_API_ENTRY cl_int CL_API_CALL
clGetSupportedGLTextureFormatsINTEL(
    cl_context context,
    cl_mem_flags flags,
    cl_mem_object_type image_type,
    cl_uint num_entries,
    cl_GLenum* gl_formats,
    cl_uint* num_texture_formats) ;

#endif

#ifdef __cplusplus
}
#endif
}

#ifndef OPENCL_CL_HALF_H
#define OPENCL_CL_HALF_H

#include "pro_platform.h"

#include <pro.h>

#ifdef __cplusplus
extern "C" {
#endif


/**
 * Rounding mode used when converting to cl_half.
 */
typedef enum
{
  CL_HALF_RTE, // round to nearest even
  CL_HALF_RTZ, // round towards zero
  CL_HALF_RTP, // round towards positive infinity
  CL_HALF_RTN, // round towards negative infinity
} cl_half_rounding_mode;


/* Private utility macros. */
#define CL_HALF_EXP_MASK 0x7C00
#define CL_HALF_MAX_FINITE_MAG 0x7BFF


/*
 * Utility to deal with values that overflow when converting to half precision.
 */
static inline cl_half cl_half_handle_overflow(cl_half_rounding_mode rounding_mode,
                                              uint16_t sign)
{
  if (rounding_mode == CL_HALF_RTZ)
  {
    // Round overflow towards zero -> largest finite number (preserving sign)
    return (sign << 15) | CL_HALF_MAX_FINITE_MAG;
  }
  else if (rounding_mode == CL_HALF_RTP && sign)
  {
    // Round negative overflow towards positive infinity -> most negative finite number
    return (1 << 15) | CL_HALF_MAX_FINITE_MAG;
  }
  else if (rounding_mode == CL_HALF_RTN && !sign)
  {
    // Round positive overflow towards negative infinity -> largest finite number
    return CL_HALF_MAX_FINITE_MAG;
  }

  // Overflow to infinity
  return (sign << 15) | CL_HALF_EXP_MASK;
}

/*
 * Utility to deal with values that underflow when converting to half precision.
 */
static inline cl_half cl_half_handle_underflow(cl_half_rounding_mode rounding_mode,
                                               uint16_t sign)
{
  if (rounding_mode == CL_HALF_RTP && !sign)
  {
    // Round underflow towards positive infinity -> smallest positive value
    return (sign << 15) | 1;
  }
  else if (rounding_mode == CL_HALF_RTN && sign)
  {
    // Round underflow towards negative infinity -> largest negative value
    return (sign << 15) | 1;
  }

  // Flush to zero
  return (sign << 15);
}


/**
 * Convert a cl_float to a cl_half.
 */
static inline cl_half cl_half_from_float(cl_float f, cl_half_rounding_mode rounding_mode)
{
  // Type-punning to get direct access to underlying bits
  union
  {
    cl_float f;
    uint32_t i;
  } f32;
  f32.f = f;

  // Extract sign bit
  uint16_t sign = f32.i >> 31;

  // Extract FP32 exponent and mantissa
  uint32_t f_exp = (f32.i >> (CL_FLT_MANT_DIG - 1)) & 0xFF;
  uint32_t f_mant = f32.i & ((1 << (CL_FLT_MANT_DIG - 1)) - 1);

  // Remove FP32 exponent bias
  int32_t exp = f_exp - CL_FLT_MAX_EXP + 1;

  // Add FP16 exponent bias
  uint16_t h_exp = (uint16_t)(exp + CL_HALF_MAX_EXP - 1);

  // Position of the bit that will become the FP16 mantissa LSB
  uint32_t lsb_pos = CL_FLT_MANT_DIG - CL_HALF_MANT_DIG;

  // Check for NaN / infinity
  if (f_exp == 0xFF)
  {
    if (f_mant)
    {
      // NaN -> propagate mantissa and silence it
      uint16_t h_mant = (uint16_t)(f_mant >> lsb_pos);
      h_mant |= 0x200;
      return (sign << 15) | CL_HALF_EXP_MASK | h_mant;
    }
    else
    {
      // Infinity -> zero mantissa
      return (sign << 15) | CL_HALF_EXP_MASK;
    }
  }

  // Check for zero
  if (!f_exp && !f_mant)
  {
    return (sign << 15);
  }

  // Check for overflow
  if (exp >= CL_HALF_MAX_EXP)
  {
    return cl_half_handle_overflow(rounding_mode, sign);
  }

  // Check for underflow
  if (exp < (CL_HALF_MIN_EXP - CL_HALF_MANT_DIG - 1))
  {
    return cl_half_handle_underflow(rounding_mode, sign);
  }

  // Check for value that will become denormal
  if (exp < -14)
  {
    // Denormal -> include the implicit 1 from the FP32 mantissa
    h_exp = 0;
    f_mant |= 1 << (CL_FLT_MANT_DIG - 1);

    // Mantissa shift amount depends on exponent
    lsb_pos = -exp + (CL_FLT_MANT_DIG - 25);
  }

  // Generate FP16 mantissa by shifting FP32 mantissa
  uint16_t h_mant = (uint16_t)(f_mant >> lsb_pos);

  // Check whether we need to round
  uint32_t halfway = 1 << (lsb_pos - 1);
  uint32_t mask = (halfway << 1) - 1;
  switch (rounding_mode)
  {
    case CL_HALF_RTE:
      if ((f_mant & mask) > halfway)
      {
        // More than halfway -> round up
        h_mant += 1;
      }
      else if ((f_mant & mask) == halfway)
      {
        // Exactly halfway -> round to nearest even
        if (h_mant & 0x1)
          h_mant += 1;
      }
      break;
    case CL_HALF_RTZ:
      // Mantissa has already been truncated -> do nothing
      break;
    case CL_HALF_RTP:
      if ((f_mant & mask) && !sign)
      {
        // Round positive numbers up
        h_mant += 1;
      }
      break;
    case CL_HALF_RTN:
      if ((f_mant & mask) && sign)
      {
        // Round negative numbers down
        h_mant += 1;
      }
      break;
  }

  // Check for mantissa overflow
  if (h_mant & 0x400)
  {
    h_exp += 1;
    h_mant = 0;
  }

  return (sign << 15) | (h_exp << 10) | h_mant;
}


/**
 * Convert a cl_double to a cl_half.
 */
static inline cl_half cl_half_from_double(cl_double d, cl_half_rounding_mode rounding_mode)
{
  // Type-punning to get direct access to underlying bits
  union
  {
    cl_double d;
    uint64_t i;
  } f64;
  f64.d = d;

  // Extract sign bit
  uint16_t sign = f64.i >> 63;

  // Extract FP64 exponent and mantissa
  uint64_t d_exp = (f64.i >> (CL_DBL_MANT_DIG - 1)) & 0x7FF;
  uint64_t d_mant = f64.i & (((uint64_t)1 << (CL_DBL_MANT_DIG - 1)) - 1);

  // Remove FP64 exponent bias
  int64_t exp = d_exp - CL_DBL_MAX_EXP + 1;

  // Add FP16 exponent bias
  uint16_t h_exp = (uint16_t)(exp + CL_HALF_MAX_EXP - 1);

  // Position of the bit that will become the FP16 mantissa LSB
  uint32_t lsb_pos = CL_DBL_MANT_DIG - CL_HALF_MANT_DIG;

  // Check for NaN / infinity
  if (d_exp == 0x7FF)
  {
    if (d_mant)
    {
      // NaN -> propagate mantissa and silence it
      uint16_t h_mant = (uint16_t)(d_mant >> lsb_pos);
      h_mant |= 0x200;
      return (sign << 15) | CL_HALF_EXP_MASK | h_mant;
    }
    else
    {
      // Infinity -> zero mantissa
      return (sign << 15) | CL_HALF_EXP_MASK;
    }
  }

  // Check for zero
  if (!d_exp && !d_mant)
  {
    return (sign << 15);
  }

  // Check for overflow
  if (exp >= CL_HALF_MAX_EXP)
  {
    return cl_half_handle_overflow(rounding_mode, sign);
  }

  // Check for underflow
  if (exp < (CL_HALF_MIN_EXP - CL_HALF_MANT_DIG - 1))
  {
    return cl_half_handle_underflow(rounding_mode, sign);
  }

  // Check for value that will become denormal
  if (exp < -14)
  {
    // Include the implicit 1 from the FP64 mantissa
    h_exp = 0;
    d_mant |= (uint64_t)1 << (CL_DBL_MANT_DIG - 1);

    // Mantissa shift amount depends on exponent
    lsb_pos = (uint32_t)(-exp + (CL_DBL_MANT_DIG - 25));
  }

  // Generate FP16 mantissa by shifting FP64 mantissa
  uint16_t h_mant = (uint16_t)(d_mant >> lsb_pos);

  // Check whether we need to round
  uint64_t halfway = (uint64_t)1 << (lsb_pos - 1);
  uint64_t mask = (halfway << 1) - 1;
  switch (rounding_mode)
  {
    case CL_HALF_RTE:
      if ((d_mant & mask) > halfway)
      {
        // More than halfway -> round up
        h_mant += 1;
      }
      else if ((d_mant & mask) == halfway)
      {
        // Exactly halfway -> round to nearest even
        if (h_mant & 0x1)
          h_mant += 1;
      }
      break;
    case CL_HALF_RTZ:
      // Mantissa has already been truncated -> do nothing
      break;
    case CL_HALF_RTP:
      if ((d_mant & mask) && !sign)
      {
        // Round positive numbers up
        h_mant += 1;
      }
      break;
    case CL_HALF_RTN:
      if ((d_mant & mask) && sign)
      {
        // Round negative numbers down
        h_mant += 1;
      }
      break;
  }

  // Check for mantissa overflow
  if (h_mant & 0x400)
  {
    h_exp += 1;
    h_mant = 0;
  }

  return (sign << 15) | (h_exp << 10) | h_mant;
}


/**
 * Convert a cl_half to a cl_float.
 */
static inline cl_float cl_half_to_float(cl_half h)
{
  // Type-punning to get direct access to underlying bits
  union
  {
    cl_float f;
    uint32_t i;
  } f32;

  // Extract sign bit
  uint16_t sign = h >> 15;

  // Extract FP16 exponent and mantissa
  uint16_t h_exp = (h >> (CL_HALF_MANT_DIG - 1)) & 0x1F;
  uint16_t h_mant = h & 0x3FF;

  // Remove FP16 exponent bias
  int32_t exp = h_exp - CL_HALF_MAX_EXP + 1;

  // Add FP32 exponent bias
  uint32_t f_exp = exp + CL_FLT_MAX_EXP - 1;

  // Check for NaN / infinity
  if (h_exp == 0x1F)
  {
    if (h_mant)
    {
      // NaN -> propagate mantissa and silence it
      uint32_t f_mant = h_mant << (CL_FLT_MANT_DIG - CL_HALF_MANT_DIG);
      f_mant |= 0x400000;
      f32.i = (sign << 31) | 0x7F800000 | f_mant;
      return f32.f;
    }
    else
    {
      // Infinity -> zero mantissa
      f32.i = (sign << 31) | 0x7F800000;
      return f32.f;
    }
  }

  // Check for zero / denormal
  if (h_exp == 0)
  {
    if (h_mant == 0)
    {
      // Zero -> zero exponent
      f_exp = 0;
    }
    else
    {
      // Denormal -> normalize it
      // - Shift mantissa to make most-significant 1 implicit
      // - Adjust exponent accordingly
      uint32_t shift = 0;
      while ((h_mant & 0x400) == 0)
      {
        h_mant <<= 1;
        shift++;
      }
      h_mant &= 0x3FF;
      f_exp -= shift - 1;
    }
  }

  f32.i = (sign << 31) | (f_exp << 23) | (h_mant << 13);
  return f32.f;
}


#undef CL_HALF_EXP_MASK
#undef CL_HALF_MAX_FINITE_MAG


#ifdef __cplusplus
}
#endif

#endif