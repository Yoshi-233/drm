#define _GNU_SOURCE
#include <errno.h>
#include <fcntl.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <time.h>
#include <unistd.h>
#include <xf86drm.h>
#include <xf86drmMode.h>

struct drm_device
{
	uint32_t width;			    // 显示器的宽的像素点数量
	uint32_t height;		    // 显示器的高的像素点数量
	uint32_t pitch;			    // 每行占据的字节数
	uint32_t handle;		    // drm_mode_create_dumb的返回句柄
	uint32_t size;			    // 显示器占据的总字节数
	uint32_t *vaddr;		    // mmap的首地址
	uint32_t fb_id;			    // 创建的framebuffer的id号
	struct drm_mode_create_dumb create; // 创建的dumb
	struct drm_mode_map_dumb map;	    // 内存映射结构体
};

struct property_crtc
{
	uint32_t blob_id;
	uint32_t property_crtc_id;
	uint32_t property_mode_id;
	uint32_t property_active;
};

drmModeConnector *conn; // connetor相关的结构体
drmModeRes *res;	// 资源
drmModePlaneRes *plane_res;

int fd; // 文件描述符
uint32_t conn_id;
uint32_t crtc_id;
uint32_t plane_id[3];

#define RED 0XFF0000
#define GREEN 0X00FF00
#define BLUE 0X0000FF

uint32_t color_table[6] = {RED, GREEN, BLUE, RED, GREEN, BLUE};

struct drm_device buf;
struct property_crtc pc;

static int drm_create_fb(struct drm_device *bo)
{
	/* create a dumb-buffer, the pixel format is XRGB888 */
	bo->create.width = bo->width;
	bo->create.height = bo->height;
	bo->create.bpp = 32;

	/* handle, pitch, size will be returned */
	drmIoctl(fd, DRM_IOCTL_MODE_CREATE_DUMB, &bo->create);

	/* bind the dumb-buffer to an FB object */
	bo->pitch = bo->create.pitch;
	bo->size = bo->create.size;
	bo->handle = bo->create.handle;
	drmModeAddFB(fd, bo->width, bo->height, 24, 32, bo->pitch,
		     bo->handle, &bo->fb_id);

	// 每行占用字节数，共占用字节数，MAP_DUMB的句柄
	printf("pitch = %d ,size = %d, handle = %d \n", bo->pitch, bo->size, bo->handle);

	/* map the dumb-buffer to userspace */
	bo->map.handle = bo->create.handle;
	drmIoctl(fd, DRM_IOCTL_MODE_MAP_DUMB, &bo->map);

	bo->vaddr = mmap(0, bo->create.size, PROT_READ | PROT_WRITE,
			 MAP_SHARED, fd, bo->map.offset);

	/* initialize the dumb-buffer with white-color */
	memset(bo->vaddr, 0xff, bo->size);

	return 0;
}

static void drm_destroy_fb(struct drm_device *bo)
{
	struct drm_mode_destroy_dumb destroy = {};
	drmModeRmFB(fd, bo->fb_id);
	munmap(bo->vaddr, bo->size);
	destroy.handle = bo->handle;
	drmIoctl(fd, DRM_IOCTL_MODE_DESTROY_DUMB, &destroy);
}

static uint32_t get_property(int fd, drmModeObjectProperties *props)
{
	// 位于./libdrm-2.4.123/xf86drmMode.h
	// drmModeObjectProperties *props是一群属性
	// drmModePropertyPtr property是单个属性，通过drmModeGetProperty获得
	drmModePropertyPtr property;
	uint32_t i, j;

	printf("count_props is %d.\n ", props->count_props);
	for (i = 0; i < props->count_props; i++)
	{
		printf("--------- props:id=%d, value=0x%lx ---------\n", props->props[i], props->prop_values[i]);
		// 位于./libdrm-2.4.123/xf86drmMode.c
		property = drmModeGetProperty(fd, props->props[i]);
		printf("id:%d, flag:0x%x, name:%s\t\n", property->prop_id, property->flags, property->name);
		printf("------ property count_values is %d. ------\n ", property->count_values);
		for (j = 0; j < property->count_values; j++)
		{
			printf("idx[%d] property values:0x%lx.\n ", j, property->values[j]);
		}
		printf("------ property count_enums is %d. ------\n ", property->count_enums);
		for (j = 0; j < property->count_enums; j++)
		{
			printf("idx[%d] property enum name:%s, val:0x%llx.\n ", j,
			       property->enums[j].name, property->enums[j].value);
		}
		printf("------ property count_blobs is %d.\n ------", property->count_blobs);
		for (j = 0; j < property->count_blobs; j++)
		{
			printf("idx[%d] property blob_id:0x%x.\n ", j, property->blob_ids[j]);
		}
		printf("--------- end ---------\n\n");
	}
	return 0;
}

static uint32_t get_property_id(int fd, drmModeObjectProperties *props,
				const char *name)
{
	drmModePropertyPtr property;
	uint32_t i, id = 0;

	/* find property according to the name */
	for (i = 0; i < props->count_props; i++)
	{
		property = drmModeGetProperty(fd, props->props[i]);
		if (!strcmp(property->name, name))
			id = property->prop_id;
		drmModeFreeProperty(property);

		if (id)
			break;
	}

	return id;
}

void drm_init()
{
	int i;

	// 位于./libdrm-2.4.123/xf86drmMode.h
	drmModeObjectProperties *props;
	// 位于./libdrm-2.4.123/xf86drmMode.h, 结构体实现在./libdrm-2.4.123/xf86drmMode.c
	drmModeAtomicReq *req;

	fd = open("/dev/dri/card0", O_RDWR | O_CLOEXEC);

	res = drmModeGetResources(fd);
	crtc_id = res->crtcs[0];
	conn_id = res->connectors[0];

	drmSetClientCap(fd, DRM_CLIENT_CAP_UNIVERSAL_PLANES, 1);
	plane_res = drmModeGetPlaneResources(fd);
	for (i = 0; i < 3; i++)
	{
		plane_id[i] = plane_res->planes[i];
		printf("planes[%d]= %d\n", i, plane_id[i]);
	}

	conn = drmModeGetConnector(fd, conn_id);
	buf.width = conn->modes[0].hdisplay;
	buf.height = conn->modes[0].vdisplay;
	drm_create_fb(&buf);

	drmSetClientCap(fd, DRM_CLIENT_CAP_ATOMIC, 1);

	/* get connector properties */
	// ./libdrm-2.4.123/xf86drmMode.c
	props = drmModeObjectGetProperties(fd, conn_id, DRM_MODE_OBJECT_CONNECTOR);
	printf("/-----conn_Property-----/\n");
	get_property(fd, props);
	printf("\n");
	pc.property_crtc_id = get_property_id(fd, props, "CRTC_ID");
	drmModeFreeObjectProperties(props);

	/* get crtc properties */
	props = drmModeObjectGetProperties(fd, crtc_id, DRM_MODE_OBJECT_CRTC);
	printf("\n/-----CRTC_Property-----/\n");
	get_property(fd, props);
	printf("\n");
	pc.property_active = get_property_id(fd, props, "ACTIVE");
	pc.property_mode_id = get_property_id(fd, props, "MODE_ID");
	drmModeFreeObjectProperties(props);

	/* create blob to store current mode, and retun the blob id */
	// 使用drmModeCreatePropertyBlob创建一个blob来存储当前的显示模式，blob的ID存储在pc.blob_id中。
	// 这是为了在设置显示模式时能够引用当前的模式。
	// blob是自定义数据结构，可以用来存储任意数据，在这里用来存储当前的显示模式。
	// 给属性赋值时必须保证属性的flag支持BLOB类型，否则会导致属性设置失败。
	drmModeCreatePropertyBlob(fd, &conn->modes[0],
				  sizeof(conn->modes[0]), &pc.blob_id);

	/* start modeseting */
	req = drmModeAtomicAlloc();
	// ./libdrm-2.4.123/xf86drmMode.c
	drmModeAtomicAddProperty(req, crtc_id, pc.property_active, 1);
	drmModeAtomicAddProperty(req, crtc_id, pc.property_mode_id, pc.blob_id);
	drmModeAtomicAddProperty(req, conn_id, pc.property_crtc_id, crtc_id);
	// ./libdrm-2.4.123/xf86drmMode.c
	drmModeAtomicCommit(fd, req, DRM_MODE_ATOMIC_ALLOW_MODESET, NULL);
	drmModeAtomicFree(req);
}

void drm_exit()
{
	drm_destroy_fb(&buf);
	drmModeFreeConnector(conn);
	drmModeFreePlaneResources(plane_res);
	drmModeFreeResources(res);
	close(fd);
}

int main(int argc, char **argv)
{
	int i, j;
	drm_init();
	// 显示三色
	for (j = 0; j < 3; j++)
	{
		for (i = j * buf.width * buf.height / 3; i < (j + 1) * buf.width * buf.height / 3; i++)
			buf.vaddr[i] = color_table[j];
	}
	// 1：1设置屏幕，没有该函数不会显示画面
	drmModeSetPlane(fd, plane_id[0], crtc_id, buf.fb_id, 0,
			0, 0, buf.width, buf.height,
			0 << 16, 0 << 16, buf.width << 16, buf.height << 16);

	getchar();
	// 将framebuffer上2/3的区域放到图层一上，
	// 此时屏幕改变，将的framebuffer区域拉伸到整个屏幕中
	drmModeSetPlane(fd, plane_id[0], crtc_id, buf.fb_id, 0,
			0, 0, buf.width, buf.height,
			0 << 16, 0 << 16, buf.width << 16, buf.height / 3 * 2 << 16);

	getchar();
	// 将framebuffer区域缩放一倍放到图层二上，把图层二的位置放到屏幕的下方
	// 叠加在图层一上，可以看到图层二覆盖了图层一的部分区域
	drmModeSetPlane(fd, plane_id[1], crtc_id, buf.fb_id, 0,
			buf.width / 4, buf.height / 2, buf.width / 2, buf.height / 2,
			0 << 16, 0 << 16, buf.width << 16, buf.height << 16);

	getchar();

	drm_exit();

	return 0;
}
