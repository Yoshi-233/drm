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

struct buffer_object
{
	uint32_t width;
	uint32_t height;
	uint32_t pitch;
	uint32_t handle;
	uint32_t size;
	uint8_t *vaddr;
	uint32_t fb_id;
};

struct buffer_object buf;

static int modeset_create_fb(int fd, struct buffer_object *bo)
{
	// ./libdrm-2.4.123/include/drm/drm_mode.h
	struct drm_mode_create_dumb create = {};
	struct drm_mode_map_dumb map = {};

	/* create a dumb-buffer, the pixel format is XRGB888 */
	create.width = bo->width;
	create.height = bo->height;
	create.bpp = 32;
	printf("before drmIoctl, width=%d, height=%d, bpp=%d, handle=%d, pitch=%d, size=0x%llx.\n", 
		create.width, create.height, create.bpp, create.handle, create.pitch, create.size);

	/* DRM_IOCTL_MODE_CREATE_DUMB的定义在./libdrm-2.4.123/include/drm/drm.h
	 * 对应的ioctl函数在 ./linux-6.11.3/drivers/gpu/drm/drm_ioctl.c
	 * DRM_IOCTL_DEF(DRM_IOCTL_MODE_CREATE_DUMB, drm_mode_create_dumb_ioctl, 0),
	 * drm_mode_create_dumb_ioctl函数在 ./linux-6.11.3/drivers/gpu/drm/drm_dumb_buffers.c
	 * */
	// 创建 DUMB 缓冲区： 通过调用 drmIoctl(fd, DRM_IOCTL_MODE_CREATE_DUMB, &create);
	// 程序向内核请求分配一个显存缓冲区。这是显存分配的主要步骤之一。
	drmIoctl(fd, DRM_IOCTL_MODE_CREATE_DUMB, &create);
	// pitch = width * bpp / 8
	printf("after drmIoctl, width=%d, height=%d, bpp=%d, handle=%d, pitch=%d, size=0x%llx.\n",
	       create.width, create.height, create.bpp, create.handle, create.pitch, create.size);

	/* bind the dumb-buffer to an FB object */
	bo->pitch = create.pitch;
	bo->size = create.size;
	bo->handle = create.handle;
	// 调用drmModeAddFB将dumb buffer绑定到一个帧缓冲对象上。此时指定了帧缓冲的宽度、高度及其他参数
	// 位置./libdrm-2.4.123/xf86drmMode.c
	// 绑定到帧缓冲对象： 在创建了 DUMB 缓冲区后，会调用 drmModeAddFB 函数，将该缓冲区绑定到帧缓冲对象（Framebuffer）上。
	// 这是为了将缓冲区与显示设备关联，使得该缓冲区可以被用于显示输出
	drmModeAddFB(fd, bo->width, bo->height, 24, 32, bo->pitch,
		     bo->handle, &bo->fb_id);

	/* map the dumb-buffer to userspace */
	map.handle = create.handle;
	/* DRM_IOCTL_MODE_MAP_DUMB的定义在./libdrm-2.4.123/include/drm/drm.h
	 * 对应的ioctl函数在 ./linux-6.11.3/drivers/gpu/drm/drm_ioctl.c
	 * DRM_IOCTL_DEF(DRM_IOCTL_MODE_MAP_DUMB, drm_mode_mmap_dumb_ioctl, 0),
	 * drm_mode_mmap_dumb_ioctl函数在 ./linux-6.11.3/drivers/gpu/drm/drm_dumb_buffers.c
	 * 映射到用户空间： 然后，通过调用 drmIoctl(fd, DRM_IOCTL_MODE_MAP_DUMB, &map); 
	 * 和 mmap，程序可以将显存缓冲区映射到用户空间，从而使用户程序能够直接访问显存。
	 * */
	printf("map, handle=%d, pad=%d, offset=0x%llx.\n",
	       map.handle, map.pad, map.offset);
	drmIoctl(fd, DRM_IOCTL_MODE_MAP_DUMB, &map);
	printf("map, handle=%d, pad=%d, offset=0x%llx.\n",
	       map.handle, map.pad, map.offset);

	bo->vaddr = mmap(0, create.size, PROT_READ | PROT_WRITE,
			 MAP_SHARED, fd, map.offset);

	/* initialize the dumb-buffer with white-color */
	memset(bo->vaddr, 0xff, bo->size);

	return 0;
}

static void modeset_destroy_fb(int fd, struct buffer_object *bo)
{
	struct drm_mode_destroy_dumb destroy = {};

	drmModeRmFB(fd, bo->fb_id);

	munmap(bo->vaddr, bo->size);

	destroy.handle = bo->handle;
	drmIoctl(fd, DRM_IOCTL_MODE_DESTROY_DUMB, &destroy);
}

int main(int argc, char **argv)
{
	int fd, i;
	// 结构体定义位置libdrm-2.4.123/xf86drmMode.h
	drmModeConnector *conn;
	// 结构体定义位置libdrm-2.4.123/xf86drmMode.h
	drmModeRes *res;
	uint32_t conn_id;
	uint32_t crtc_id;

	fd = open("/dev/dri/card0", O_RDWR | O_CLOEXEC);

	/* 打开设备文件，并获取连接器和资源信息,
	 * CRTCS是连接器的ID，connectors是连接器的属性，res是资源信息
	 * 详细注释见libdrm-2.4.123/xf86drmMode.c
	 * */
	res = drmModeGetResources(fd);
	if (res == NULL) {
		fprintf(stderr, "drmModeGetResources failed\n");
		return -1;
	}

	// 打印
	printf("------- some info in drmModeRes, use res = drmModeGetResources(fd); -------\n");
	for (i = 0; i < res->count_fbs; i++) {
		printf("count_fbs_idx:%d, count_fbs:%d, fb:%d.\n", i, res->count_fbs, res->fbs[i]);
	}
	for (i = 0; i < res->count_crtcs; i++) {
		printf("count_crtcs_idx:%d, count_crtcs:%d, crtc:%d.\n", i, res->count_crtcs, res->crtcs[i]);
	}
	for (i = 0; i < res->count_connectors; i++) {
		printf("count_connectors_idx:%d, count_connectors:%d, connector:%d.\n", i, res->count_connectors, res->connectors[i]);
	}
	for (i = 0; i < res->count_encoders; i++) {
		printf("count_encoders_idx:%d, count_encoders:%d, encoder:%d.\n", i, res->count_encoders, res->encoders[i]);
	}
	printf("min_width:%d, max_width:%d.\n", res->min_width, res->max_width);
	printf("min_height:%d, max_height:%d.\n\n", res->min_height, res->max_height);

	// 一般就一个显示器和连接器
	crtc_id = res->crtcs[0];
	conn_id = res->connectors[0];

	/* 详细注释见libdrm-2.4.123/xf86drmMode.c */
	conn = drmModeGetConnector(fd, conn_id);
	if (conn->connection == DRM_MODE_CONNECTED) {
		printf("connect_id %d connect success.\n", conn->connector_id);
	} else {
		fprintf(stderr, "connect_id %d connect fail!\n", conn->connector_id);
		return -1;
	}
	buf.width = conn->modes[0].hdisplay;
	buf.height = conn->modes[0].vdisplay;
	printf("------- some info in drmModeConnector, use conn = drmModeGetConnector(fd, conn_id); -------\n");
	printf("connector_id:%d, encoder_id:%d.\n", conn->connector_id, conn->encoder_id);
	printf("connector_type:%d, connector_type_id:%d.\n", conn->connector_type, conn->connector_type_id);
	printf("enum connection:%d.\n", conn->connection);
	printf("mmWidth:%d, mmHeight:%d.\n", conn->mmWidth, conn->mmHeight);
	printf("enum subpixel:%d.\n", conn->subpixel);
	for(i = 0; i < conn->count_modes; i++) {
		printf("idx:%d, count_modes:%d, name:%s.\n", i, conn->count_modes, conn->modes[i].name);
		printf("clock:%d, vrefresh:%d, flags:%d, type:%d.\n", 
			conn->modes[i].clock, conn->modes[i].vrefresh, conn->modes[i].flags, conn->modes[i].type);
		printf("hdisplay:%d, hsync_start:%d, hsync_end:%d, htotal:%d, hskew:%d.\n",
		       conn->modes[i].hdisplay, conn->modes[i].hsync_start, conn->modes[i].hsync_end, conn->modes[i].htotal, conn->modes[i].hskew);
		printf("vdisplay:%d, vsync_start:%d, vsync_end:%d, vtotal:%d, vscan:%d.\n",
		       conn->modes[i].vdisplay, conn->modes[i].vsync_start, conn->modes[i].vsync_end, conn->modes[i].vtotal, conn->modes[i].vscan);
	}
	for (i = 0; i < conn->count_props; i++) {
		printf("count_props_idx:%d, count_props:%d, prop:%d, value:0x%lx.\n", i, conn->count_props, conn->props[i], conn->prop_values[i]);
	}
	for (i = 0; i < conn->count_encoders; i++) {
		printf("count_encoders_idx:%d, count_encoders:%d, encoder:%d.\n", i, conn->count_encoders, conn->encoders[i]);
	}

	modeset_create_fb(fd, &buf);

	/* 详细注释见libdrm-2.4.123/xf86drmMode.c */
	if(drmModeSetCrtc(fd, crtc_id, buf.fb_id,
		       0, 0, &conn_id, 1, &conn->modes[0]) < 0 ) {
		perror("drmModeSetCrtc failed");
	}

	getchar();

	modeset_destroy_fb(fd, &buf);

	drmModeFreeConnector(conn);
	drmModeFreeResources(res);

	close(fd);

	return 0;
}
