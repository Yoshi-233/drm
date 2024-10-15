/*
 * Copyright (c) 2016 Intel Corporation
 *
 * Permission to use, copy, modify, distribute, and sell this software and its
 * documentation for any purpose is hereby granted without fee, provided that
 * the above copyright notice appear in all copies and that both that copyright
 * notice and this permission notice appear in supporting documentation, and
 * that the name of the copyright holders not be used in advertising or
 * publicity pertaining to distribution of the software without specific,
 * written prior permission.  The copyright holders make no representations
 * about the suitability of this software for any purpose.  It is provided "as
 * is" without express or implied warranty.
 *
 * THE COPYRIGHT HOLDERS DISCLAIM ALL WARRANTIES WITH REGARD TO THIS SOFTWARE,
 * INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS, IN NO
 * EVENT SHALL THE COPYRIGHT HOLDERS BE LIABLE FOR ANY SPECIAL, INDIRECT OR
 * CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE,
 * DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER
 * TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE
 * OF THIS SOFTWARE.
 */

#ifndef __DRM_MODESET_H__
#define __DRM_MODESET_H__

#include <linux/kref.h>
#include <drm/drm_lease.h>
struct drm_object_properties;
struct drm_property;
struct drm_device;
struct drm_file;

/**
 * struct drm_mode_object - base structure for modeset objects
 * @id: userspace visible identifier
 * @type: type of the object, one of DRM_MODE_OBJECT\_\*
 * @properties: properties attached to this object, including values
 * @refcount: reference count for objects which with dynamic lifetime
 * @free_cb: free function callback, only set for objects with dynamic lifetime
 *
 * Base structure for modeset objects visible to userspace. Objects can be
 * looked up using drm_mode_object_find(). Besides basic uapi interface
 * properties like @id and @type it provides two services:
 *
 * - It tracks attached properties and their values. This is used by &drm_crtc,
 *   &drm_plane and &drm_connector. Properties are attached by calling
 *   drm_object_attach_property() before the object is visible to userspace.
 *
 * - For objects with dynamic lifetimes (as indicated by a non-NULL @free_cb) it
 *   provides reference counting through drm_mode_object_get() and
 *   drm_mode_object_put(). This is used by &drm_framebuffer, &drm_connector
 *   and &drm_property_blob. These objects provide specialized reference
 *   counting wrappers.
 */
struct drm_mode_object {
	/* 表示对象的唯一标识符，id 是一个 32 位的无符号整数。这个标识符通常用来在用户空间中引用这个对象。 */
	uint32_t id;
	/* 这个成员变量表示对象的类型，同样是一个 32 位的无符号整数。
	 * type 的值是从预定义的类型中选择的，通常会与 DRM（Direct Rendering Manager）对象的类型常量相对应，
	 *用来区分这个对象属于哪一种类别，比如是显示控制器（CRTC）、图层（plane）还是连接器（connector）。*/
	uint32_t type;
	/* 这是一个指向 drm_object_properties 结构体的指针，用来跟踪附加到该对象的属性。
	 * 属性保存了与对象相关的数据，例如分辨率、颜色深度等，方便用于在图形渲染时进行设置和管理。
	 * 这个成员变量的位置在./linux-6.11.3/include/drm/drm_property.h */
	struct drm_object_properties *properties;
	/* 这是一个引用计数结构体，用于管理对象的生命周期。当对象被引用时，引用计数增加，当引用不再使用时，计数减少。
	 * 这样可以避免内存泄漏，确保当没有任何引用时可以安全地释放对象。 */
	struct kref refcount;
	/* 这是一个指向函数的指针，函数的参数是一个指向 kref 的指针。
	 * 这个回调函数用于释放对象的资源，仅在对象具有动态生命周期时设定。
	 * 如果对象不再被使用且引用计数降为零，这个回调就会被调用以进行清理。 */
	void (*free_cb)(struct kref *kref);
};

#define DRM_OBJECT_MAX_PROPERTY 64
/**
 * struct drm_object_properties - property tracking for &drm_mode_object
 */
struct drm_object_properties {
	/**
	 * @count: number of valid properties, must be less than or equal to
	 * DRM_OBJECT_MAX_PROPERTY.
	 * 该成员用于保存有效属性的数量。这个数量必须小于或等于 DRM_OBJECT_MAX_PROPERTY（最多支持的属性数）
	 */

	int count;
	/**
	 * @properties: Array of pointers to &drm_property.
	 *
	 * NOTE: if we ever start dynamically destroying properties (ie.
	 * not at drm_mode_config_cleanup() time), then we'd have to do
	 * a better job of detaching property from mode objects to avoid
	 * dangling property pointers:
	 * 这是一个指针数组，每个指针指向一个 drm_property 结构体，表示附加到 DRM 对象的属性列表。
	 * 注释中提到，如果未来我们开始动态销毁属性，则需要更小心地处理，以避免悬空指针的问题。
	 */
	struct drm_property *properties[DRM_OBJECT_MAX_PROPERTY];

	/**
	 * @values: Array to store the property values, matching @properties. Do
	 * not read/write values directly, but use
	 * drm_object_property_get_value() and drm_object_property_set_value().
	 *
	 * Note that atomic drivers do not store mutable properties in this
	 * array, but only the decoded values in the corresponding state
	 * structure. The decoding is done using the &drm_crtc.atomic_get_property and
	 * &drm_crtc.atomic_set_property hooks for &struct drm_crtc. For
	 * &struct drm_plane the hooks are &drm_plane_funcs.atomic_get_property and
	 * &drm_plane_funcs.atomic_set_property. And for &struct drm_connector
	 * the hooks are &drm_connector_funcs.atomic_get_property and
	 * &drm_connector_funcs.atomic_set_property .
	 *
	 * Hence atomic drivers should not use drm_object_property_set_value()
	 * and drm_object_property_get_value() on mutable objects, i.e. those
	 * without the DRM_MODE_PROP_IMMUTABLE flag set.
	 *
	 * For atomic drivers the default value of properties is stored in this
	 * array, so drm_object_property_get_default_value can be used to
	 * retrieve it.
	 * 个数组存储与 properties 数组中属性相对应的值。
	 **  用户不应直接读取或写入该数组中的值，而应使用 drm_object_property_get_value() 
	 和 drm_object_property_set_value() 函数进行操作。这确保了操作的正确性和有效性。
	 */
	uint64_t values[DRM_OBJECT_MAX_PROPERTY];
};

/* Avoid boilerplate.  I'm tired of typing. */
#define DRM_ENUM_NAME_FN(fnname, list)				\
	const char *fnname(int val)				\
	{							\
		int i;						\
		for (i = 0; i < ARRAY_SIZE(list); i++) {	\
			if (list[i].type == val)		\
				return list[i].name;		\
		}						\
		return "(unknown)";				\
	}

struct drm_mode_object *drm_mode_object_find(struct drm_device *dev,
					     struct drm_file *file_priv,
					     uint32_t id, uint32_t type);
void drm_mode_object_get(struct drm_mode_object *obj);
void drm_mode_object_put(struct drm_mode_object *obj);

int drm_object_property_set_value(struct drm_mode_object *obj,
				  struct drm_property *property,
				  uint64_t val);
int drm_object_property_get_value(struct drm_mode_object *obj,
				  struct drm_property *property,
				  uint64_t *value);
int drm_object_property_get_default_value(struct drm_mode_object *obj,
					  struct drm_property *property,
					  uint64_t *val);

void drm_object_attach_property(struct drm_mode_object *obj,
				struct drm_property *property,
				uint64_t init_val);

bool drm_mode_object_lease_required(uint32_t type);
#endif
