/*
 * Copyright (c) 2007 Dave Airlie <airlied@linux.ie>
 * Copyright (c) 2007 Jakob Bornecrantz <wallbraker@gmail.com>
 * Copyright (c) 2008 Red Hat Inc.
 * Copyright (c) 2007-2008 Tungsten Graphics, Inc., Cedar Park, TX., USA
 * Copyright (c) 2007-2008 Intel Corporation
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 */

#ifndef _DRM_MODE_H
#define _DRM_MODE_H

#include "drm.h"

#if defined(__cplusplus)
extern "C" {
#endif

/**
 * DOC: overview
 *
 * DRM exposes many UAPI and structure definitions to have a consistent
 * and standardized interface with users.
 * Userspace can refer to these structure definitions and UAPI formats
 * to communicate to drivers.
 */

#define DRM_CONNECTOR_NAME_LEN	32
#define DRM_DISPLAY_MODE_LEN	32
#define DRM_PROP_NAME_LEN	32

#define DRM_MODE_TYPE_BUILTIN	(1<<0) /* deprecated */
#define DRM_MODE_TYPE_CLOCK_C	((1<<1) | DRM_MODE_TYPE_BUILTIN) /* deprecated */
#define DRM_MODE_TYPE_CRTC_C	((1<<2) | DRM_MODE_TYPE_BUILTIN) /* deprecated */
#define DRM_MODE_TYPE_PREFERRED	(1<<3)
#define DRM_MODE_TYPE_DEFAULT	(1<<4) /* deprecated */
#define DRM_MODE_TYPE_USERDEF	(1<<5)
#define DRM_MODE_TYPE_DRIVER	(1<<6)

#define DRM_MODE_TYPE_ALL	(DRM_MODE_TYPE_PREFERRED |	\
				 DRM_MODE_TYPE_USERDEF |	\
				 DRM_MODE_TYPE_DRIVER)

/* Video mode flags */
/* bit compatible with the xrandr RR_ definitions (bits 0-13)
 *
 * ABI warning: Existing userspace really expects
 * the mode flags to match the xrandr definitions. Any
 * changes that don't match the xrandr definitions will
 * likely need a new client cap or some other mechanism
 * to avoid breaking existing userspace. This includes
 * allocating new flags in the previously unused bits!
 */
#define DRM_MODE_FLAG_PHSYNC			(1<<0)
#define DRM_MODE_FLAG_NHSYNC			(1<<1)
#define DRM_MODE_FLAG_PVSYNC			(1<<2)
#define DRM_MODE_FLAG_NVSYNC			(1<<3)
#define DRM_MODE_FLAG_INTERLACE			(1<<4)
#define DRM_MODE_FLAG_DBLSCAN			(1<<5)
#define DRM_MODE_FLAG_CSYNC			(1<<6)
#define DRM_MODE_FLAG_PCSYNC			(1<<7)
#define DRM_MODE_FLAG_NCSYNC			(1<<8)
#define DRM_MODE_FLAG_HSKEW			(1<<9) /* hskew provided */
#define DRM_MODE_FLAG_BCAST			(1<<10) /* deprecated */
#define DRM_MODE_FLAG_PIXMUX			(1<<11) /* deprecated */
#define DRM_MODE_FLAG_DBLCLK			(1<<12)
#define DRM_MODE_FLAG_CLKDIV2			(1<<13)
 /*
  * When adding a new stereo mode don't forget to adjust DRM_MODE_FLAGS_3D_MAX
  * (define not exposed to user space).
  */
#define DRM_MODE_FLAG_3D_MASK			(0x1f<<14)
#define  DRM_MODE_FLAG_3D_NONE		(0<<14)
#define  DRM_MODE_FLAG_3D_FRAME_PACKING		(1<<14)
#define  DRM_MODE_FLAG_3D_FIELD_ALTERNATIVE	(2<<14)
#define  DRM_MODE_FLAG_3D_LINE_ALTERNATIVE	(3<<14)
#define  DRM_MODE_FLAG_3D_SIDE_BY_SIDE_FULL	(4<<14)
#define  DRM_MODE_FLAG_3D_L_DEPTH		(5<<14)
#define  DRM_MODE_FLAG_3D_L_DEPTH_GFX_GFX_DEPTH	(6<<14)
#define  DRM_MODE_FLAG_3D_TOP_AND_BOTTOM	(7<<14)
#define  DRM_MODE_FLAG_3D_SIDE_BY_SIDE_HALF	(8<<14)

/* Picture aspect ratio options */
#define DRM_MODE_PICTURE_ASPECT_NONE		0
#define DRM_MODE_PICTURE_ASPECT_4_3		1
#define DRM_MODE_PICTURE_ASPECT_16_9		2
#define DRM_MODE_PICTURE_ASPECT_64_27		3
#define DRM_MODE_PICTURE_ASPECT_256_135		4

/* Content type options */
#define DRM_MODE_CONTENT_TYPE_NO_DATA		0
#define DRM_MODE_CONTENT_TYPE_GRAPHICS		1
#define DRM_MODE_CONTENT_TYPE_PHOTO		2
#define DRM_MODE_CONTENT_TYPE_CINEMA		3
#define DRM_MODE_CONTENT_TYPE_GAME		4

/* Aspect ratio flag bitmask (4 bits 22:19) */
#define DRM_MODE_FLAG_PIC_AR_MASK		(0x0F<<19)
#define  DRM_MODE_FLAG_PIC_AR_NONE \
			(DRM_MODE_PICTURE_ASPECT_NONE<<19)
#define  DRM_MODE_FLAG_PIC_AR_4_3 \
			(DRM_MODE_PICTURE_ASPECT_4_3<<19)
#define  DRM_MODE_FLAG_PIC_AR_16_9 \
			(DRM_MODE_PICTURE_ASPECT_16_9<<19)
#define  DRM_MODE_FLAG_PIC_AR_64_27 \
			(DRM_MODE_PICTURE_ASPECT_64_27<<19)
#define  DRM_MODE_FLAG_PIC_AR_256_135 \
			(DRM_MODE_PICTURE_ASPECT_256_135<<19)

#define  DRM_MODE_FLAG_ALL	(DRM_MODE_FLAG_PHSYNC |		\
				 DRM_MODE_FLAG_NHSYNC |		\
				 DRM_MODE_FLAG_PVSYNC |		\
				 DRM_MODE_FLAG_NVSYNC |		\
				 DRM_MODE_FLAG_INTERLACE |	\
				 DRM_MODE_FLAG_DBLSCAN |	\
				 DRM_MODE_FLAG_CSYNC |		\
				 DRM_MODE_FLAG_PCSYNC |		\
				 DRM_MODE_FLAG_NCSYNC |		\
				 DRM_MODE_FLAG_HSKEW |		\
				 DRM_MODE_FLAG_DBLCLK |		\
				 DRM_MODE_FLAG_CLKDIV2 |	\
				 DRM_MODE_FLAG_3D_MASK)

/* DPMS flags */
/* bit compatible with the xorg definitions. */
#define DRM_MODE_DPMS_ON	0
#define DRM_MODE_DPMS_STANDBY	1
#define DRM_MODE_DPMS_SUSPEND	2
#define DRM_MODE_DPMS_OFF	3

/* Scaling mode options */
#define DRM_MODE_SCALE_NONE		0 /* Unmodified timing (display or
					     software can still scale) */
#define DRM_MODE_SCALE_FULLSCREEN	1 /* Full screen, ignore aspect */
#define DRM_MODE_SCALE_CENTER		2 /* Centered, no scaling */
#define DRM_MODE_SCALE_ASPECT		3 /* Full screen, preserve aspect */

/* Dithering mode options */
#define DRM_MODE_DITHERING_OFF	0
#define DRM_MODE_DITHERING_ON	1
#define DRM_MODE_DITHERING_AUTO 2

/* Dirty info options */
#define DRM_MODE_DIRTY_OFF      0
#define DRM_MODE_DIRTY_ON       1
#define DRM_MODE_DIRTY_ANNOTATE 2

/* Link Status options */
#define DRM_MODE_LINK_STATUS_GOOD	0
#define DRM_MODE_LINK_STATUS_BAD	1

/*
 * DRM_MODE_ROTATE_<degrees>
 *
 * Signals that a drm plane is been rotated <degrees> degrees in counter
 * clockwise direction.
 *
 * This define is provided as a convenience, looking up the property id
 * using the name->prop id lookup is the preferred method.
 */
#define DRM_MODE_ROTATE_0       (1<<0)
#define DRM_MODE_ROTATE_90      (1<<1)
#define DRM_MODE_ROTATE_180     (1<<2)
#define DRM_MODE_ROTATE_270     (1<<3)

/*
 * DRM_MODE_ROTATE_MASK
 *
 * Bitmask used to look for drm plane rotations.
 */
#define DRM_MODE_ROTATE_MASK (\
		DRM_MODE_ROTATE_0  | \
		DRM_MODE_ROTATE_90  | \
		DRM_MODE_ROTATE_180 | \
		DRM_MODE_ROTATE_270)

/*
 * DRM_MODE_REFLECT_<axis>
 *
 * Signals that the contents of a drm plane is reflected along the <axis> axis,
 * in the same way as mirroring.
 * See kerneldoc chapter "Plane Composition Properties" for more details.
 *
 * This define is provided as a convenience, looking up the property id
 * using the name->prop id lookup is the preferred method.
 */
#define DRM_MODE_REFLECT_X      (1<<4)
#define DRM_MODE_REFLECT_Y      (1<<5)

/*
 * DRM_MODE_REFLECT_MASK
 *
 * Bitmask used to look for drm plane reflections.
 */
#define DRM_MODE_REFLECT_MASK (\
		DRM_MODE_REFLECT_X | \
		DRM_MODE_REFLECT_Y)

/* Content Protection Flags */
#define DRM_MODE_CONTENT_PROTECTION_UNDESIRED	0
#define DRM_MODE_CONTENT_PROTECTION_DESIRED     1
#define DRM_MODE_CONTENT_PROTECTION_ENABLED     2

/**
 * struct drm_mode_modeinfo - Display mode information.
 * @clock: pixel clock in kHz
 * @hdisplay: horizontal display size
 * @hsync_start: horizontal sync start
 * @hsync_end: horizontal sync end
 * @htotal: horizontal total size
 * @hskew: horizontal skew
 * @vdisplay: vertical display size
 * @vsync_start: vertical sync start
 * @vsync_end: vertical sync end
 * @vtotal: vertical total size
 * @vscan: vertical scan
 * @vrefresh: approximate vertical refresh rate in Hz
 * @flags: bitmask of misc. flags, see DRM_MODE_FLAG_* defines
 * @type: bitmask of type flags, see DRM_MODE_TYPE_* defines
 * @name: string describing the mode resolution
 *
 * This is the user-space API display mode information structure. For the
 * kernel version see struct drm_display_mode.
 */
struct drm_mode_modeinfo {
	__u32 clock; 	    // 表示像素时钟频率，以千赫（kHz）为单位。该值指定了显示器能够处理的每个像素的刷新速率。
	__u16 hdisplay;	    // 水平显示的像素数，即屏幕在水平方向上可显示的像素数量。
	__u16 hsync_start;  // 水平同步信号的开始位置，定义了何时开始一个新的水平线条的显示
	__u16 hsync_end;    // 水平同步信号的结束位置，指示同步脉冲的结束。
	__u16 htotal;	    // 水平总宽度，包括显示区和控制区域的总数，这个值是 hdisplay 与前后同步信号的和
	__u16 hskew;	    // 水平偏移，表示显示输出的微小调整或校正。
	__u16 vdisplay;	    // 垂直显示的像素数，即屏幕在垂直方向上可显示的像素数量。
	__u16 vsync_start;  // 垂直同步信号的开始位置，指示何时开始新的垂直刷新。
	__u16 vsync_end;    // 垂直同步信号的结束位置，指示同步脉冲的结束。
	__u16 vtotal;	    // 垂直总高度，总像素包含了显示区和控制区域的数量。
	__u16 vscan;	    // 垂直扫描线的数量，通常用于描述单行显示的扫描行（如交错扫描）。

	__u32 vrefresh;     // 近似的垂直刷新率，以赫兹（Hz）表示，指示屏幕每秒刷新多少次。

	__u32 flags;	    // 一个额外的标志位掩码，使用 DRM_MODE_FLAG_* 定义(DRM_MODE_FLAG_PHSYNC)，表示显示模式的特性或属性（如是否支持双扫描等）。
	__u32 type;	    // 个类型标志位掩码，使用 DRM_MODE_TYPE_* 定义(DRM_MODE_TYPE_BUILTIN)，表示模式的种类或来源（如用户定义、驱动程序定义等）。
	char name[DRM_DISPLAY_MODE_LEN];
};

struct drm_mode_card_res {
	/* 这是一个指向 framebuffer（帧缓冲区）对象 ID 的指针。
	 * Framebuffer 是存储图像数据的内存区域，通常用于显示内容。
	 * 这个指针允许用户空间的程序获取与设备相关的 framebuffer 的信息。
	 *  */
	__u64 fb_id_ptr;
	/* 这是一个指向 CRTC（显示控制器）对象 ID 的指针。
	 * CRTC 负责生成输出信号并控制显示设备上的图像显示。
	 * 该指针用于获取系统中当前可用的 CRTC 的信息。 
	 * */
	__u64 crtc_id_ptr;
	/* 这是一个指向连接器对象 ID 的指针。
	 * 连接器（如 HDMI、DP 等）是连接显示设备（如显示器、电视等）和图形硬件之间的接口。
	 * 这个指针帮助用户空间获取可用的连接器信息。
	 * */
	__u64 connector_id_ptr;
	/* 这是一个指向编码器对象 ID 的指针。
	 * 编码器类似于连接器，但是它会将图形信号转换为适合特定连接器格式的信号。
	 * 这意味着它会在 GPU 和显示设备之间充当一个转换器。 
	 * */
	__u64 encoder_id_ptr;
	/* 表示当前系统中的 framebuffer 数量。
	 * 它提供了用户空间程序了解可以使用多少个 framebuffer 的信息。
	 * */
	__u32 count_fbs;
	/* 表示当前系统中的 CRTC 数量。
	 * 它指出有多少个显示控制器可以用来输出图形信息。
	 * */
	__u32 count_crtcs;
	/* 表示当前系统中的连接器数量。
	 * 它反映了可以连接的显示器类型数量。
	 **/
	__u32 count_connectors;
	/* 表示当前系统中的编码器数量。它与连接器相关，但提供了更底层的设备功能信息 */
	__u32 count_encoders;
	/* 表示支持的最小显示宽度。它用于限制所支持的显示分辨率 */
	__u32 min_width;
	/* 表示支持的最大显示宽度。它用于限制所支持的显示分辨率 */
	__u32 max_width;
	/* 表示支持的最小显示高度。用于限制所支持的显示分辨率 */
	__u32 min_height;
	/* 表示支持的最大显示高度。用于限制所支持的显示分辨率 */
	__u32 max_height;
};

struct drm_mode_crtc {
	__u64 set_connectors_ptr;
	__u32 count_connectors;

	__u32 crtc_id; /**< Id */
	__u32 fb_id; /**< Id of framebuffer */

	__u32 x; /**< x Position on the framebuffer */
	__u32 y; /**< y Position on the framebuffer */

	__u32 gamma_size; // 表示 gamma LUT（查找表）的大小。使用 gamma 效应可以调整图像的亮度和对比度，通常在显示设备中应用
	__u32 mode_valid; // 一个标志，表明当前的显示模式是否有效。它通常用于指示设置的模式是否可被 CRTC 接受
	struct drm_mode_modeinfo mode; // 是一个结构体，包含了关于当前显示模式详细信息的字段，例如像素时钟、显示分辨率、刷新率等。这个字段为 CRTC 提供了所需的模式信息。
};

#define DRM_MODE_PRESENT_TOP_FIELD	(1<<0)
#define DRM_MODE_PRESENT_BOTTOM_FIELD	(1<<1)

/* Planes blend with or override other bits on the CRTC */
struct drm_mode_set_plane {
	__u32 plane_id;
	__u32 crtc_id;
	__u32 fb_id; /* fb object contains surface format type */
	__u32 flags; /* see above flags */

	/* Signed dest location allows it to be partially off screen */
	__s32 crtc_x;
	__s32 crtc_y;
	__u32 crtc_w;
	__u32 crtc_h;

	/* Source values are 16.16 fixed point */
	__u32 src_x;
	__u32 src_y;
	__u32 src_h;
	__u32 src_w;
};

/**
 * struct drm_mode_get_plane - Get plane metadata.
 *
 * Userspace can perform a GETPLANE ioctl to retrieve information about a
 * plane.
 *
 * To retrieve the number of formats supported, set @count_format_types to zero
 * and call the ioctl. @count_format_types will be updated with the value.
 *
 * To retrieve these formats, allocate an array with the memory needed to store
 * @count_format_types formats. Point @format_type_ptr to this array and call
 * the ioctl again (with @count_format_types still set to the value returned in
 * the first ioctl call).
 */
struct drm_mode_get_plane {
	/**
	 * @plane_id: Object ID of the plane whose information should be
	 * retrieved. Set by caller.
	 */
	__u32 plane_id;

	/** @crtc_id: Object ID of the current CRTC. */
	__u32 crtc_id;
	/** @fb_id: Object ID of the current fb. */
	__u32 fb_id;

	/**
	 * @possible_crtcs: Bitmask of CRTC's compatible with the plane. CRTC's
	 * are created and they receive an index, which corresponds to their
	 * position in the bitmask. Bit N corresponds to
	 * :ref:`CRTC index<crtc_index>` N.
	 */
	__u32 possible_crtcs;
	/** @gamma_size: Never used. */
	__u32 gamma_size;

	/** @count_format_types: Number of formats. */
	__u32 count_format_types;
	/**
	 * @format_type_ptr: Pointer to ``__u32`` array of formats that are
	 * supported by the plane. These formats do not require modifiers.
	 */
	__u64 format_type_ptr;
};

struct drm_mode_get_plane_res {
	__u64 plane_id_ptr;
	__u32 count_planes;
};

#define DRM_MODE_ENCODER_NONE	0
#define DRM_MODE_ENCODER_DAC	1
#define DRM_MODE_ENCODER_TMDS	2
#define DRM_MODE_ENCODER_LVDS	3
#define DRM_MODE_ENCODER_TVDAC	4
#define DRM_MODE_ENCODER_VIRTUAL 5
#define DRM_MODE_ENCODER_DSI	6
#define DRM_MODE_ENCODER_DPMST	7
#define DRM_MODE_ENCODER_DPI	8

struct drm_mode_get_encoder {
	__u32 encoder_id;
	__u32 encoder_type;

	__u32 crtc_id; /**< Id of crtc */

	__u32 possible_crtcs;
	__u32 possible_clones;
};

/* This is for connectors with multiple signal types. */
/* Try to match DRM_MODE_CONNECTOR_X as closely as possible. */
enum drm_mode_subconnector {
	DRM_MODE_SUBCONNECTOR_Automatic   = 0,  /* DVI-I, TV     */
	DRM_MODE_SUBCONNECTOR_Unknown     = 0,  /* DVI-I, TV, DP */
	DRM_MODE_SUBCONNECTOR_VGA	  = 1,  /*            DP */
	DRM_MODE_SUBCONNECTOR_DVID	  = 3,  /* DVI-I      DP */
	DRM_MODE_SUBCONNECTOR_DVIA	  = 4,  /* DVI-I         */
	DRM_MODE_SUBCONNECTOR_Composite   = 5,  /*        TV     */
	DRM_MODE_SUBCONNECTOR_SVIDEO	  = 6,  /*        TV     */
	DRM_MODE_SUBCONNECTOR_Component   = 8,  /*        TV     */
	DRM_MODE_SUBCONNECTOR_SCART	  = 9,  /*        TV     */
	DRM_MODE_SUBCONNECTOR_DisplayPort = 10, /*            DP */
	DRM_MODE_SUBCONNECTOR_HDMIA       = 11, /*            DP */
	DRM_MODE_SUBCONNECTOR_Native      = 15, /*            DP */
	DRM_MODE_SUBCONNECTOR_Wireless    = 18, /*            DP */
};

#define DRM_MODE_CONNECTOR_Unknown	0
#define DRM_MODE_CONNECTOR_VGA		1
#define DRM_MODE_CONNECTOR_DVII		2
#define DRM_MODE_CONNECTOR_DVID		3
#define DRM_MODE_CONNECTOR_DVIA		4
#define DRM_MODE_CONNECTOR_Composite	5
#define DRM_MODE_CONNECTOR_SVIDEO	6
#define DRM_MODE_CONNECTOR_LVDS		7
#define DRM_MODE_CONNECTOR_Component	8
#define DRM_MODE_CONNECTOR_9PinDIN	9
#define DRM_MODE_CONNECTOR_DisplayPort	10
#define DRM_MODE_CONNECTOR_HDMIA	11
#define DRM_MODE_CONNECTOR_HDMIB	12
#define DRM_MODE_CONNECTOR_TV		13
#define DRM_MODE_CONNECTOR_eDP		14
#define DRM_MODE_CONNECTOR_VIRTUAL      15
#define DRM_MODE_CONNECTOR_DSI		16
#define DRM_MODE_CONNECTOR_DPI		17
#define DRM_MODE_CONNECTOR_WRITEBACK	18
#define DRM_MODE_CONNECTOR_SPI		19
#define DRM_MODE_CONNECTOR_USB		20

/**
 * struct drm_mode_get_connector - Get connector metadata.
 *
 * User-space can perform a GETCONNECTOR ioctl to retrieve information about a
 * connector. User-space is expected to retrieve encoders, modes and properties
 * by performing this ioctl at least twice: the first time to retrieve the
 * number of elements, the second time to retrieve the elements themselves.
 *
 * To retrieve the number of elements, set @count_props and @count_encoders to
 * zero, set @count_modes to 1, and set @modes_ptr to a temporary struct
 * drm_mode_modeinfo element.
 *
 * To retrieve the elements, allocate arrays for @encoders_ptr, @modes_ptr,
 * @props_ptr and @prop_values_ptr, then set @count_modes, @count_props and
 * @count_encoders to their capacity.
 *
 * Performing the ioctl only twice may be racy: the number of elements may have
 * changed with a hotplug event in-between the two ioctls. User-space is
 * expected to retry the last ioctl until the number of elements stabilizes.
 * The kernel won't fill any array which doesn't have the expected length.
 *
 * **Force-probing a connector**
 *
 * If the @count_modes field is set to zero and the DRM client is the current
 * DRM master, the kernel will perform a forced probe on the connector to
 * refresh the connector status, modes and EDID. A forced-probe can be slow,
 * might cause flickering and the ioctl will block.
 *
 * User-space needs to force-probe connectors to ensure their metadata is
 * up-to-date at startup and after receiving a hot-plug event. User-space
 * may perform a forced-probe when the user explicitly requests it. User-space
 * shouldn't perform a forced-probe in other situations.
 * 这段代码定义了一个名为 struct drm_mode_get_connector 的数据结构，它主要用于在用户空间中通过
 * GETCONNECTOR ioctl 操作获取显示连接器的元数据。
 * struct drm_mode_get_connector 是一个包含多种信息的结构体，用于描述显示连接器的状态和特性
 */
struct drm_mode_get_connector {
	/** @encoders_ptr: Pointer to ``__u32`` array of object IDs.
	 * 指向一个 __u32 数组，表示与连接器相关的编码器的对象 ID。编码器负责将图形信号转换为特定连接器格式的信号。
	 */
	__u64 encoders_ptr;
	/** @modes_ptr: Pointer to struct drm_mode_modeinfo array.
	 * 指向一个 struct drm_mode_modeinfo 数组，存储与连接器兼容的显示模式的信息。
	 */
	__u64 modes_ptr;
	/** @props_ptr: Pointer to ``__u32`` array of property IDs.
	 * 指向一个 __u32 数组，包含连接器的属性 IDs。
	 */
	__u64 props_ptr;
	/** @prop_values_ptr: Pointer to ``__u64`` array of property values.
	 * 指向一个 __u64 数组，存储连接器属性的值。
	 */
	__u64 prop_values_ptr;

	/** @count_modes: Number of modes.
	 * 表示连接器支持的显示模式的数量
	 */
	__u32 count_modes;
	/** @count_props: Number of properties.
	 * 表示连接器的属性数量
	 */
	__u32 count_props;
	/** @count_encoders: Number of encoders.
	 * 表示与连接器对应的编码器数量。
	 */
	__u32 count_encoders;

	/** @encoder_id: Object ID of the current encoder. */
	__u32 encoder_id;
	/** @connector_id: Object ID of the connector. */
	__u32 connector_id;
	/**
	 * @connector_type: Type of the connector.
	 *
	 * See DRM_MODE_CONNECTOR_* defines.
	 * 连接器类型的标识符，使用 DRM_MODE_CONNECTOR_* 定义
	 * 例如DRM_MODE_CONNECTOR_VGA, DRM_MODE_CONNECTOR_DSI等，在本文件中定义
	 */
	__u32 connector_type;
	/**
	 * @connector_type_id: Type-specific connector number.
	 *
	 * This is not an object ID. This is a per-type connector number. Each
	 * (type, type_id) combination is unique across all connectors of a DRM
	 * device.
	 *
	 * The (type, type_id) combination is not a stable identifier: the
	 * type_id can change depending on the driver probe order.
	 * 接器的类型特定编号，每种连接器类型下该编号是唯一的，不同的探测顺序可能影响其稳定性
	 */
	__u32 connector_type_id;

	/**
	 * @connection: Status of the connector.
	 *
	 * See enum drm_connector_status.
	 * 接器的状态，可能的值由 enum drm_connector_status 定义,
	 * 位置./linux-6.11.3/include/drm/drm_connector.h
	 */
	__u32 connection;
	/** @mm_width: Width of the connected sink in millimeters.
	 * 连接的显示器的宽度，以毫米为单位。
	*/
	__u32 mm_width;
	/** @mm_height: Height of the connected sink in millimeters.
	 * 连接的显示器的高度，以毫米为单位。
	*/
	__u32 mm_height;
	/**
	 * @subpixel: Subpixel order of the connected sink.
	 *
	 * See enum subpixel_order.
	 * 显示器的子像素顺序，可能的值由 enum subpixel_order 定义, 例如SubPixelHorizontalRGB
	 * 位置./linux-6.11.3/include/drm/drm_connector.h
	 */
	__u32 subpixel;

	/** @pad: Padding, must be zero.
	 * 为保持结构对齐而设置的填充字段，必须为零。
	*/
	__u32 pad;
};

#define DRM_MODE_PROP_PENDING	(1<<0) /* deprecated, do not use */
#define DRM_MODE_PROP_RANGE	(1<<1)
#define DRM_MODE_PROP_IMMUTABLE	(1<<2)
#define DRM_MODE_PROP_ENUM	(1<<3) /* enumerated type with text strings */
#define DRM_MODE_PROP_BLOB	(1<<4)
#define DRM_MODE_PROP_BITMASK	(1<<5) /* bitmask of enumerated types */

/* non-extended types: legacy bitmask, one bit per type: */
#define DRM_MODE_PROP_LEGACY_TYPE  ( \
		DRM_MODE_PROP_RANGE | \
		DRM_MODE_PROP_ENUM | \
		DRM_MODE_PROP_BLOB | \
		DRM_MODE_PROP_BITMASK)

/* extended-types: rather than continue to consume a bit per type,
 * grab a chunk of the bits to use as integer type id.
 */
#define DRM_MODE_PROP_EXTENDED_TYPE	0x0000ffc0
#define DRM_MODE_PROP_TYPE(n)		((n) << 6)
#define DRM_MODE_PROP_OBJECT		DRM_MODE_PROP_TYPE(1)
#define DRM_MODE_PROP_SIGNED_RANGE	DRM_MODE_PROP_TYPE(2)

/* the PROP_ATOMIC flag is used to hide properties from userspace that
 * is not aware of atomic properties.  This is mostly to work around
 * older userspace (DDX drivers) that read/write each prop they find,
 * without being aware that this could be triggering a lengthy modeset.
 */
#define DRM_MODE_PROP_ATOMIC        0x80000000

/**
 * struct drm_mode_property_enum - Description for an enum/bitfield entry.
 * @value: numeric value for this enum entry.
 * @name: symbolic name for this enum entry.
 *
 * See struct drm_property_enum for details.
 */
struct drm_mode_property_enum {
	__u64 value;
	char name[DRM_PROP_NAME_LEN];
};

/**
 * struct drm_mode_get_property - Get property metadata.
 *
 * User-space can perform a GETPROPERTY ioctl to retrieve information about a
 * property. The same property may be attached to multiple objects, see
 * "Modeset Base Object Abstraction".
 *
 * The meaning of the @values_ptr field changes depending on the property type.
 * See &drm_property.flags for more details.
 *
 * The @enum_blob_ptr and @count_enum_blobs fields are only meaningful when the
 * property has the type &DRM_MODE_PROP_ENUM or &DRM_MODE_PROP_BITMASK. For
 * backwards compatibility, the kernel will always set @count_enum_blobs to
 * zero when the property has the type &DRM_MODE_PROP_BLOB. User-space must
 * ignore these two fields if the property has a different type.
 *
 * User-space is expected to retrieve values and enums by performing this ioctl
 * at least twice: the first time to retrieve the number of elements, the
 * second time to retrieve the elements themselves.
 *
 * To retrieve the number of elements, set @count_values and @count_enum_blobs
 * to zero, then call the ioctl. @count_values will be updated with the number
 * of elements. If the property has the type &DRM_MODE_PROP_ENUM or
 * &DRM_MODE_PROP_BITMASK, @count_enum_blobs will be updated as well.
 *
 * To retrieve the elements themselves, allocate an array for @values_ptr and
 * set @count_values to its capacity. If the property has the type
 * &DRM_MODE_PROP_ENUM or &DRM_MODE_PROP_BITMASK, allocate an array for
 * @enum_blob_ptr and set @count_enum_blobs to its capacity. Calling the ioctl
 * again will fill the arrays.
 * struct drm_mode_get_property 主要用于用户空间与内核之间的交互，帮助用户获取与设备相关属性的信息。
 */
struct drm_mode_get_property {
	/** @values_ptr: Pointer to a ``__u64`` array. */
	__u64 values_ptr;
	/** @enum_blob_ptr: Pointer to a struct drm_mode_property_enum array.
	 * 这些字段在属性类型为 DRM_MODE_PROP_ENUM 或 DRM_MODE_PROP_BITMASK 时才有意义。
	 */
	__u64 enum_blob_ptr;

	/**
	 * @prop_id: Object ID of the property which should be retrieved. Set
	 * by the caller.
	 */
	__u32 prop_id;
	/**
	 * @flags: ``DRM_MODE_PROP_*`` bitfield. See &drm_property.flags for
	 * a definition of the flags.
	 */
	__u32 flags;
	/**
	 * @name: Symbolic property name. User-space should use this field to
	 * recognize properties.
	 */
	char name[DRM_PROP_NAME_LEN];

	/** @count_values: Number of elements in @values_ptr. */
	__u32 count_values;
	/** @count_enum_blobs: Number of elements in @enum_blob_ptr. */
	__u32 count_enum_blobs;
};

struct drm_mode_connector_set_property {
	__u64 value;
	__u32 prop_id;
	__u32 connector_id;
};

#define DRM_MODE_OBJECT_CRTC 0xcccccccc
#define DRM_MODE_OBJECT_CONNECTOR 0xc0c0c0c0
#define DRM_MODE_OBJECT_ENCODER 0xe0e0e0e0
#define DRM_MODE_OBJECT_MODE 0xdededede
#define DRM_MODE_OBJECT_PROPERTY 0xb0b0b0b0
#define DRM_MODE_OBJECT_FB 0xfbfbfbfb
#define DRM_MODE_OBJECT_BLOB 0xbbbbbbbb
#define DRM_MODE_OBJECT_PLANE 0xeeeeeeee
#define DRM_MODE_OBJECT_ANY 0

struct drm_mode_obj_get_properties {
	__u64 props_ptr;
	__u64 prop_values_ptr;
	__u32 count_props;
	__u32 obj_id;
	__u32 obj_type;
};

struct drm_mode_obj_set_property {
	__u64 value;
	__u32 prop_id;
	__u32 obj_id;
	__u32 obj_type;
};

struct drm_mode_get_blob {
	__u32 blob_id;
	__u32 length;
	__u64 data;
};

// 用途：这是原始的帧缓冲区添加请求结构，主要用于旧版的ioctl接口。它仅支持RGB格式的帧缓冲。
// 字段：包括基础的信息，如帧缓冲的宽度、高度、每个像素的字节数（bpp）、深度、图像数据的处理等，但它的功能相对较为简单。
struct drm_mode_fb_cmd
{
	__u32 fb_id;
	__u32 width;
	__u32 height;
	__u32 pitch;
	__u32 bpp;
	__u32 depth;
	/* driver specific handle */
	__u32 handle;
};

#define DRM_MODE_FB_INTERLACED	(1<<0) /* for interlaced framebuffers */
#define DRM_MODE_FB_MODIFIERS	(1<<1) /* enables ->modifier[] */

/**
 * struct drm_mode_fb_cmd2 - Frame-buffer metadata.
 *
 * This struct holds frame-buffer metadata. There are two ways to use it:
 *
 * - User-space can fill this struct and perform a &DRM_IOCTL_MODE_ADDFB2
 *   ioctl to register a new frame-buffer. The new frame-buffer object ID will
 *   be set by the kernel in @fb_id.
 * - User-space can set @fb_id and perform a &DRM_IOCTL_MODE_GETFB2 ioctl to
 *   fetch metadata about an existing frame-buffer.
 *
 * In case of planar formats, this struct allows up to 4 buffer objects with
 * offsets and pitches per plane. The pitch and offset order are dictated by
 * the format FourCC as defined by ``drm_fourcc.h``, e.g. NV12 is described as:
 *
 *     YUV 4:2:0 image with a plane of 8-bit Y samples followed by an
 *     interleaved U/V plane containing 8-bit 2x2 subsampled colour difference
 *     samples.
 *
 * So it would consist of a Y plane at ``offsets[0]`` and a UV plane at
 * ``offsets[1]``.
 *
 * To accommodate tiled, compressed, etc formats, a modifier can be specified.
 * For more information see the "Format Modifiers" section. Note that even
 * though it looks like we have a modifier per-plane, we in fact do not. The
 * modifier for each plane must be identical. Thus all combinations of
 * different data layouts for multi-plane formats must be enumerated as
 * separate modifiers.
 *
 * All of the entries in @handles, @pitches, @offsets and @modifier must be
 * zero when unused. Warning, for @offsets and @modifier zero can't be used to
 * figure out whether the entry is used or not since it's a valid value (a zero
 * offset is common, and a zero modifier is &DRM_FORMAT_MOD_LINEAR).
 * 用途：这个结构体是在struct drm_mode_fb_cmd的基础上扩展的，旨在支持更多的功能，包括多平面帧缓冲和四字符代码作为像素格式的指定。
字段：比drm_mode_fb_cmd有更多的字段和更复杂的结构，能够支持多种格式和不同的内存布局。它提供的信息更加详细，适应现代图形驱动的需求。
 */
struct drm_mode_fb_cmd2 {
	/** @fb_id: Object ID of the frame-buffer. */
	__u32 fb_id;
	/** @width: Width of the frame-buffer. */
	__u32 width;
	/** @height: Height of the frame-buffer. */
	__u32 height;
	/**
	 * @pixel_format: FourCC format code, see ``DRM_FORMAT_*`` constants in
	 * ``drm_fourcc.h``.
	 */
	__u32 pixel_format;
	/**
	 * @flags: Frame-buffer flags (see &DRM_MODE_FB_INTERLACED and
	 * &DRM_MODE_FB_MODIFIERS).
	 */
	__u32 flags;

	/**
	 * @handles: GEM buffer handle, one per plane. Set to 0 if the plane is
	 * unused. The same handle can be used for multiple planes.
	 */
	__u32 handles[4];
	/** @pitches: Pitch (aka. stride) in bytes, one per plane. */
	__u32 pitches[4];
	/** @offsets: Offset into the buffer in bytes, one per plane. */
	__u32 offsets[4];
	/**
	 * @modifier: Format modifier, one per plane. See ``DRM_FORMAT_MOD_*``
	 * constants in ``drm_fourcc.h``. All planes must use the same
	 * modifier. Ignored unless &DRM_MODE_FB_MODIFIERS is set in @flags.
	 */
	__u64 modifier[4];
};

#define DRM_MODE_FB_DIRTY_ANNOTATE_COPY 0x01
#define DRM_MODE_FB_DIRTY_ANNOTATE_FILL 0x02
#define DRM_MODE_FB_DIRTY_FLAGS         0x03

#define DRM_MODE_FB_DIRTY_MAX_CLIPS     256

/*
 * Mark a region of a framebuffer as dirty.
 *
 * Some hardware does not automatically update display contents
 * as a hardware or software draw to a framebuffer. This ioctl
 * allows userspace to tell the kernel and the hardware what
 * regions of the framebuffer have changed.
 *
 * The kernel or hardware is free to update more then just the
 * region specified by the clip rects. The kernel or hardware
 * may also delay and/or coalesce several calls to dirty into a
 * single update.
 *
 * Userspace may annotate the updates, the annotates are a
 * promise made by the caller that the change is either a copy
 * of pixels or a fill of a single color in the region specified.
 *
 * If the DRM_MODE_FB_DIRTY_ANNOTATE_COPY flag is given then
 * the number of updated regions are half of num_clips given,
 * where the clip rects are paired in src and dst. The width and
 * height of each one of the pairs must match.
 *
 * If the DRM_MODE_FB_DIRTY_ANNOTATE_FILL flag is given the caller
 * promises that the region specified of the clip rects is filled
 * completely with a single color as given in the color argument.
 */

struct drm_mode_fb_dirty_cmd {
	__u32 fb_id;
	__u32 flags;
	__u32 color;
	__u32 num_clips;
	__u64 clips_ptr;
};

struct drm_mode_mode_cmd {
	__u32 connector_id;
	struct drm_mode_modeinfo mode;
};

#define DRM_MODE_CURSOR_BO	0x01
#define DRM_MODE_CURSOR_MOVE	0x02
#define DRM_MODE_CURSOR_FLAGS	0x03

/*
 * depending on the value in flags different members are used.
 *
 * CURSOR_BO uses
 *    crtc_id
 *    width
 *    height
 *    handle - if 0 turns the cursor off
 *
 * CURSOR_MOVE uses
 *    crtc_id
 *    x
 *    y
 */
struct drm_mode_cursor {
	__u32 flags;
	__u32 crtc_id;
	__s32 x;
	__s32 y;
	__u32 width;
	__u32 height;
	/* driver specific handle */
	__u32 handle;
};

struct drm_mode_cursor2 {
	__u32 flags;
	__u32 crtc_id;
	__s32 x;
	__s32 y;
	__u32 width;
	__u32 height;
	/* driver specific handle */
	__u32 handle;
	__s32 hot_x;
	__s32 hot_y;
};

struct drm_mode_crtc_lut {
	__u32 crtc_id;
	__u32 gamma_size;

	/* pointers to arrays */
	__u64 red;
	__u64 green;
	__u64 blue;
};

struct drm_color_ctm {
	/*
	 * Conversion matrix in S31.32 sign-magnitude
	 * (not two's complement!) format.
	 *
	 * out   matrix    in
	 * |R|   |0 1 2|   |R|
	 * |G| = |3 4 5| x |G|
	 * |B|   |6 7 8|   |B|
	 */
	__u64 matrix[9];
};

struct drm_color_lut {
	/*
	 * Values are mapped linearly to 0.0 - 1.0 range, with 0x0 == 0.0 and
	 * 0xffff == 1.0.
	 */
	__u16 red;
	__u16 green;
	__u16 blue;
	__u16 reserved;
};

/**
 * struct drm_plane_size_hint - Plane size hints
 *
 * The plane SIZE_HINTS property blob contains an
 * array of struct drm_plane_size_hint.
 */
struct drm_plane_size_hint {
	__u16 width;
	__u16 height;
};

/**
 * struct hdr_metadata_infoframe - HDR Metadata Infoframe Data.
 *
 * HDR Metadata Infoframe as per CTA 861.G spec. This is expected
 * to match exactly with the spec.
 *
 * Userspace is expected to pass the metadata information as per
 * the format described in this structure.
 */
struct hdr_metadata_infoframe {
	/**
	 * @eotf: Electro-Optical Transfer Function (EOTF)
	 * used in the stream.
	 */
	__u8 eotf;
	/**
	 * @metadata_type: Static_Metadata_Descriptor_ID.
	 */
	__u8 metadata_type;
	/**
	 * @display_primaries: Color Primaries of the Data.
	 * These are coded as unsigned 16-bit values in units of
	 * 0.00002, where 0x0000 represents zero and 0xC350
	 * represents 1.0000.
	 * @display_primaries.x: X coordinate of color primary.
	 * @display_primaries.y: Y coordinate of color primary.
	 */
	struct {
		__u16 x, y;
	} display_primaries[3];
	/**
	 * @white_point: White Point of Colorspace Data.
	 * These are coded as unsigned 16-bit values in units of
	 * 0.00002, where 0x0000 represents zero and 0xC350
	 * represents 1.0000.
	 * @white_point.x: X coordinate of whitepoint of color primary.
	 * @white_point.y: Y coordinate of whitepoint of color primary.
	 */
	struct {
		__u16 x, y;
	} white_point;
	/**
	 * @max_display_mastering_luminance: Max Mastering Display Luminance.
	 * This value is coded as an unsigned 16-bit value in units of 1 cd/m2,
	 * where 0x0001 represents 1 cd/m2 and 0xFFFF represents 65535 cd/m2.
	 */
	__u16 max_display_mastering_luminance;
	/**
	 * @min_display_mastering_luminance: Min Mastering Display Luminance.
	 * This value is coded as an unsigned 16-bit value in units of
	 * 0.0001 cd/m2, where 0x0001 represents 0.0001 cd/m2 and 0xFFFF
	 * represents 6.5535 cd/m2.
	 */
	__u16 min_display_mastering_luminance;
	/**
	 * @max_cll: Max Content Light Level.
	 * This value is coded as an unsigned 16-bit value in units of 1 cd/m2,
	 * where 0x0001 represents 1 cd/m2 and 0xFFFF represents 65535 cd/m2.
	 */
	__u16 max_cll;
	/**
	 * @max_fall: Max Frame Average Light Level.
	 * This value is coded as an unsigned 16-bit value in units of 1 cd/m2,
	 * where 0x0001 represents 1 cd/m2 and 0xFFFF represents 65535 cd/m2.
	 */
	__u16 max_fall;
};

/**
 * struct hdr_output_metadata - HDR output metadata
 *
 * Metadata Information to be passed from userspace
 */
struct hdr_output_metadata {
	/**
	 * @metadata_type: Static_Metadata_Descriptor_ID.
	 */
	__u32 metadata_type;
	/**
	 * @hdmi_metadata_type1: HDR Metadata Infoframe.
	 */
	union {
		struct hdr_metadata_infoframe hdmi_metadata_type1;
	};
};

/**
 * DRM_MODE_PAGE_FLIP_EVENT
 *
 * Request that the kernel sends back a vblank event (see
 * struct drm_event_vblank) with the &DRM_EVENT_FLIP_COMPLETE type when the
 * page-flip is done.
 */
#define DRM_MODE_PAGE_FLIP_EVENT 0x01
/**
 * DRM_MODE_PAGE_FLIP_ASYNC
 *
 * Request that the page-flip is performed as soon as possible, ie. with no
 * delay due to waiting for vblank. This may cause tearing to be visible on
 * the screen.
 *
 * When used with atomic uAPI, the driver will return an error if the hardware
 * doesn't support performing an asynchronous page-flip for this update.
 * User-space should handle this, e.g. by falling back to a regular page-flip.
 *
 * Note, some hardware might need to perform one last synchronous page-flip
 * before being able to switch to asynchronous page-flips. As an exception,
 * the driver will return success even though that first page-flip is not
 * asynchronous.
 */
#define DRM_MODE_PAGE_FLIP_ASYNC 0x02
#define DRM_MODE_PAGE_FLIP_TARGET_ABSOLUTE 0x4
#define DRM_MODE_PAGE_FLIP_TARGET_RELATIVE 0x8
#define DRM_MODE_PAGE_FLIP_TARGET (DRM_MODE_PAGE_FLIP_TARGET_ABSOLUTE | \
				   DRM_MODE_PAGE_FLIP_TARGET_RELATIVE)
/**
 * DRM_MODE_PAGE_FLIP_FLAGS
 *
 * Bitmask of flags suitable for &drm_mode_crtc_page_flip_target.flags.
 */
#define DRM_MODE_PAGE_FLIP_FLAGS (DRM_MODE_PAGE_FLIP_EVENT | \
				  DRM_MODE_PAGE_FLIP_ASYNC | \
				  DRM_MODE_PAGE_FLIP_TARGET)

/*
 * Request a page flip on the specified crtc.
 *
 * This ioctl will ask KMS to schedule a page flip for the specified
 * crtc.  Once any pending rendering targeting the specified fb (as of
 * ioctl time) has completed, the crtc will be reprogrammed to display
 * that fb after the next vertical refresh.  The ioctl returns
 * immediately, but subsequent rendering to the current fb will block
 * in the execbuffer ioctl until the page flip happens.  If a page
 * flip is already pending as the ioctl is called, EBUSY will be
 * returned.
 *
 * Flag DRM_MODE_PAGE_FLIP_EVENT requests that drm sends back a vblank
 * event (see drm.h: struct drm_event_vblank) when the page flip is
 * done.  The user_data field passed in with this ioctl will be
 * returned as the user_data field in the vblank event struct.
 *
 * Flag DRM_MODE_PAGE_FLIP_ASYNC requests that the flip happen
 * 'as soon as possible', meaning that it not delay waiting for vblank.
 * This may cause tearing on the screen.
 *
 * The reserved field must be zero.
 */

struct drm_mode_crtc_page_flip {
	__u32 crtc_id;
	__u32 fb_id;
	__u32 flags;
	__u32 reserved;
	__u64 user_data;
};

/*
 * Request a page flip on the specified crtc.
 *
 * Same as struct drm_mode_crtc_page_flip, but supports new flags and
 * re-purposes the reserved field:
 *
 * The sequence field must be zero unless either of the
 * DRM_MODE_PAGE_FLIP_TARGET_ABSOLUTE/RELATIVE flags is specified. When
 * the ABSOLUTE flag is specified, the sequence field denotes the absolute
 * vblank sequence when the flip should take effect. When the RELATIVE
 * flag is specified, the sequence field denotes the relative (to the
 * current one when the ioctl is called) vblank sequence when the flip
 * should take effect. NOTE: DRM_IOCTL_WAIT_VBLANK must still be used to
 * make sure the vblank sequence before the target one has passed before
 * calling this ioctl. The purpose of the
 * DRM_MODE_PAGE_FLIP_TARGET_ABSOLUTE/RELATIVE flags is merely to clarify
 * the target for when code dealing with a page flip runs during a
 * vertical blank period.
 */

struct drm_mode_crtc_page_flip_target {
	__u32 crtc_id;
	__u32 fb_id;
	__u32 flags;
	__u32 sequence;
	__u64 user_data;
};

/**
 * struct drm_mode_create_dumb - Create a KMS dumb buffer for scanout.
 * @height: buffer height in pixels
 * @width: buffer width in pixels
 * @bpp: bits per pixel
 * @flags: must be zero
 * @handle: buffer object handle
 * @pitch: number of bytes between two consecutive lines
 * @size: size of the whole buffer in bytes
 *
 * User-space fills @height, @width, @bpp and @flags. If the IOCTL succeeds,
 * the kernel fills @handle, @pitch and @size.
 * 这段代码定义了一个名为 drm_mode_create_dumb 的结构体，
 * 该结构体用于创建一个 KMS（Kernel Mode Setting）"dumb buffer"，
 * 该缓冲区主要用于扫描输出（scanout）。
 */
struct drm_mode_create_dumb {
	__u32 height;
	__u32 width;
	// 表示每个像素的位数（bits per pixel），即像素所需的比特数。
	// 例如，32bpp 表示每个像素使用 32 位来表示，在大多数情况下，这包含了红色、绿色、蓝色和透明度（Alpha）通道。
	__u32 bpp;
	// 这个字段通常被设置为零。在创建缓冲区时，这个字段的意义比较小，但在一些场合可以扩展，以便在未来添加更多标志。
	__u32 flags;

	// 这是缓冲区对象的句柄，当缓冲区成功创建时，内核会填充这个字段。用户可以通过这个句柄引用创建的缓冲区.
	__u32 handle;
	// 表示连续两行之间的字节数（即每行的跨度），这个字段在缓冲区创建成功后由内核填充，可以用于获取每行数据的存储大小。
	__u32 pitch;
	// 这个字段表示整个缓冲区的大小（以字节为单位）。与 pitch 一样，在缓冲区创建成功后由内核填充。
	__u64 size;
};

/* set up for mmap of a dumb scanout buffer
 * drm_mode_map_dumb 结构体的主要功能是为内核中的用户空间应用程序提供一个机制，
 通过这个机制，用户空间可以请求将一个简单的扫描输出缓冲区（
 通常是一个“愚蠢”缓冲区，意味着它没有特定的硬件加速支持）映射到其地址空间。
 这通常用于显示图形，例如，通过 mmap 系统调用，使得程序可以直接访问帧缓冲区的内容。*/
struct drm_mode_map_dumb {
	/** Handle for the object being mapped.
	 * 这个字段是一个无符号32位整数，表示要映射的对象的句柄。
	 * 句柄通常是一个唯一标识符，用于引用在图形内存中的特定对象，例如帧缓冲区
	*/
	__u32 handle;
	/* 这个字段用于填充，确保数据结构的对齐。
	* 在某些体系结构中，数据结构的字段可能需要对齐到特定的字节边界，这个字段通常用来满足这种对齐要求。
	*/
	__u32 pad;
	/**
	 * Fake offset to use for subsequent mmap call
	 *
	 * This is a fixed-size type for 32/64 compatibility.
	 * 这是一个无符号64位整数，表示一个“伪偏移”，用于后续的内存映射调用（mmap）。
	 * 此偏移量是指示内存中实际映射地址的偏移，适用于32位和64位的兼容性。
	 * 在众多平台上，mmap 系统调用用于将文件或设备的内容映射到进程的地址空间中，进而允许进程直接读写内存。
	 */
	__u64 offset;
};

struct drm_mode_destroy_dumb {
	__u32 handle;
};

/**
 * DRM_MODE_ATOMIC_TEST_ONLY
 *
 * Do not apply the atomic commit, instead check whether the hardware supports
 * this configuration.
 *
 * See &drm_mode_config_funcs.atomic_check for more details on test-only
 * commits.
 * 功能：当此标志被设置时，不会真正应用原子提交，而是检查硬件是否支持当前的配置。
 *      这个测试可以确保在尝试改变硬件状态之前，不会实际影响输出。
 * 用途：在用户空间进行更新之前，先验证硬件是否能正确执行该更新，以避免因不兼容而导致的错误
 */
#define DRM_MODE_ATOMIC_TEST_ONLY 0x0100
/**
 * DRM_MODE_ATOMIC_NONBLOCK
 *
 * Do not block while applying the atomic commit. The &DRM_IOCTL_MODE_ATOMIC
 * IOCTL returns immediately instead of waiting for the changes to be applied
 * in hardware. Note, the driver will still check that the update can be
 * applied before retuning.
 * 功能：此标志指示在应用原子提交时不应阻塞。调用该IOCTL后，函数会立即返回，而不需等待硬件应用更改。
 *      尽管这样，不同驱动仍会检查更新是否可以成功应用。
 * 用途：适用于需要快速响应而不想等待硬件完成任务的场景，帮助减少延迟。
 */
#define DRM_MODE_ATOMIC_NONBLOCK  0x0200
/**
 * DRM_MODE_ATOMIC_ALLOW_MODESET
 *
 * Allow the update to result in temporary or transient visible artifacts while
 * the update is being applied. Applying the update may also take significantly
 * more time than a page flip. All visual artifacts will disappear by the time
 * the update is completed, as signalled through the vblank event's timestamp
 * (see struct drm_event_vblank).
 *
 * This flag must be set when the KMS update might cause visible artifacts.
 * Without this flag such KMS update will return a EINVAL error. What kind of
 * update may cause visible artifacts depends on the driver and the hardware.
 * User-space that needs to know beforehand if an update might cause visible
 * artifacts can use &DRM_MODE_ATOMIC_TEST_ONLY without
 * &DRM_MODE_ATOMIC_ALLOW_MODESET to see if it fails.
 *
 * To the best of the driver's knowledge, visual artifacts are guaranteed to
 * not appear when this flag is not set. Some sinks might display visual
 * artifacts outside of the driver's control.
 * 功能：允许更新在应用过程中产生临时或暂时的可见伪影（visual artifacts）。
 *      更新可能比单纯的页面翻转需要更多时间，同时在更新完成之前可能会出现视觉伪影。
 * 用途：必须设置此标志当KMS更新可能造成视觉伪影时。如果没有设置且更新可能导致伪影，
 *      则KMS更新将会返回错误（EINVAL）。这个标志确保在发生潜在视觉伪影的情况下，
 *      用户空间可以做出必要的调整以处理这些伪影。
 */
#define DRM_MODE_ATOMIC_ALLOW_MODESET 0x0400

/**
 * DRM_MODE_ATOMIC_FLAGS
 *
 * Bitfield of flags accepted by the &DRM_IOCTL_MODE_ATOMIC IOCTL in
 * &drm_mode_atomic.flags.
 */
#define DRM_MODE_ATOMIC_FLAGS (\
		DRM_MODE_PAGE_FLIP_EVENT |\
		DRM_MODE_PAGE_FLIP_ASYNC |\
		DRM_MODE_ATOMIC_TEST_ONLY |\
		DRM_MODE_ATOMIC_NONBLOCK |\
		DRM_MODE_ATOMIC_ALLOW_MODESET)

struct drm_mode_atomic {
	__u32 flags;
	__u32 count_objs;
	__u64 objs_ptr;
	__u64 count_props_ptr;
	__u64 props_ptr;
	__u64 prop_values_ptr;
	__u64 reserved;
	__u64 user_data;
};

struct drm_format_modifier_blob {
#define FORMAT_BLOB_CURRENT 1
	/* Version of this blob format */
	__u32 version;

	/* Flags */
	__u32 flags;

	/* Number of fourcc formats supported */
	__u32 count_formats;

	/* Where in this blob the formats exist (in bytes) */
	__u32 formats_offset;

	/* Number of drm_format_modifiers */
	__u32 count_modifiers;

	/* Where in this blob the modifiers exist (in bytes) */
	__u32 modifiers_offset;

	/* __u32 formats[] */
	/* struct drm_format_modifier modifiers[] */
};

struct drm_format_modifier {
	/* Bitmask of formats in get_plane format list this info applies to. The
	 * offset allows a sliding window of which 64 formats (bits).
	 *
	 * Some examples:
	 * In today's world with < 65 formats, and formats 0, and 2 are
	 * supported
	 * 0x0000000000000005
	 *		  ^-offset = 0, formats = 5
	 *
	 * If the number formats grew to 128, and formats 98-102 are
	 * supported with the modifier:
	 *
	 * 0x0000007c00000000 0000000000000000
	 *		  ^
	 *		  |__offset = 64, formats = 0x7c00000000
	 *
	 */
	__u64 formats;
	__u32 offset;
	__u32 pad;

	/* The modifier that applies to the >get_plane format list bitmask. */
	__u64 modifier;
};

/**
 * struct drm_mode_create_blob - Create New blob property
 *
 * Create a new 'blob' data property, copying length bytes from data pointer,
 * and returning new blob ID.
 */
struct drm_mode_create_blob {
	/** @data: Pointer to data to copy. */
	__u64 data;
	/** @length: Length of data to copy. */
	__u32 length;
	/** @blob_id: Return: new property ID. */
	__u32 blob_id;
};

/**
 * struct drm_mode_destroy_blob - Destroy user blob
 * @blob_id: blob_id to destroy
 *
 * Destroy a user-created blob property.
 *
 * User-space can release blobs as soon as they do not need to refer to them by
 * their blob object ID.  For instance, if you are using a MODE_ID blob in an
 * atomic commit and you will not make another commit re-using the same ID, you
 * can destroy the blob as soon as the commit has been issued, without waiting
 * for it to complete.
 */
struct drm_mode_destroy_blob {
	__u32 blob_id;
};

/**
 * struct drm_mode_create_lease - Create lease
 *
 * Lease mode resources, creating another drm_master.
 *
 * The @object_ids array must reference at least one CRTC, one connector and
 * one plane if &DRM_CLIENT_CAP_UNIVERSAL_PLANES is enabled. Alternatively,
 * the lease can be completely empty.
 */
struct drm_mode_create_lease {
	/** @object_ids: Pointer to array of object ids (__u32) */
	__u64 object_ids;
	/** @object_count: Number of object ids */
	__u32 object_count;
	/** @flags: flags for new FD (O_CLOEXEC, etc) */
	__u32 flags;

	/** @lessee_id: Return: unique identifier for lessee. */
	__u32 lessee_id;
	/** @fd: Return: file descriptor to new drm_master file */
	__u32 fd;
};

/**
 * struct drm_mode_list_lessees - List lessees
 *
 * List lesses from a drm_master.
 */
struct drm_mode_list_lessees {
	/**
	 * @count_lessees: Number of lessees.
	 *
	 * On input, provides length of the array.
	 * On output, provides total number. No
	 * more than the input number will be written
	 * back, so two calls can be used to get
	 * the size and then the data.
	 */
	__u32 count_lessees;
	/** @pad: Padding. */
	__u32 pad;

	/**
	 * @lessees_ptr: Pointer to lessees.
	 *
	 * Pointer to __u64 array of lessee ids
	 */
	__u64 lessees_ptr;
};

/**
 * struct drm_mode_get_lease - Get Lease
 *
 * Get leased objects.
 */
struct drm_mode_get_lease {
	/**
	 * @count_objects: Number of leased objects.
	 *
	 * On input, provides length of the array.
	 * On output, provides total number. No
	 * more than the input number will be written
	 * back, so two calls can be used to get
	 * the size and then the data.
	 */
	__u32 count_objects;
	/** @pad: Padding. */
	__u32 pad;

	/**
	 * @objects_ptr: Pointer to objects.
	 *
	 * Pointer to __u32 array of object ids.
	 */
	__u64 objects_ptr;
};

/**
 * struct drm_mode_revoke_lease - Revoke lease
 */
struct drm_mode_revoke_lease {
	/** @lessee_id: Unique ID of lessee */
	__u32 lessee_id;
};

/**
 * struct drm_mode_rect - Two dimensional rectangle.
 * @x1: Horizontal starting coordinate (inclusive).
 * @y1: Vertical starting coordinate (inclusive).
 * @x2: Horizontal ending coordinate (exclusive).
 * @y2: Vertical ending coordinate (exclusive).
 *
 * With drm subsystem using struct drm_rect to manage rectangular area this
 * export it to user-space.
 *
 * Currently used by drm_mode_atomic blob property FB_DAMAGE_CLIPS.
 */
struct drm_mode_rect {
	__s32 x1;
	__s32 y1;
	__s32 x2;
	__s32 y2;
};

/**
 * struct drm_mode_closefb
 * @fb_id: Framebuffer ID.
 * @pad: Must be zero.
 */
struct drm_mode_closefb {
	__u32 fb_id;
	__u32 pad;
};

#if defined(__cplusplus)
}
#endif

#endif
