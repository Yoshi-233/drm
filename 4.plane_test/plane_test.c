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

struct buffer_object {
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
	struct drm_mode_create_dumb create = {};
 	struct drm_mode_map_dumb map = {};

	create.width = bo->width;
	create.height = bo->height;
	create.bpp = 32;
	drmIoctl(fd, DRM_IOCTL_MODE_CREATE_DUMB, &create);

	bo->pitch = create.pitch;
	bo->size = create.size;
	bo->handle = create.handle;
	drmModeAddFB(fd, bo->width, bo->height, 24, 32, bo->pitch,
			   bo->handle, &bo->fb_id);

	map.handle = create.handle;
	drmIoctl(fd, DRM_IOCTL_MODE_MAP_DUMB, &map);

	bo->vaddr = mmap(0, create.size, PROT_READ | PROT_WRITE,
			MAP_SHARED, fd, map.offset);

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
	drmModeConnector *conn;
	drmModeRes *res;
	// 结构体位置:./libdrm-2.4.123/xf86drmMode.h
	drmModePlaneRes *plane_res;
	uint32_t conn_id;
	uint32_t crtc_id;
	uint32_t plane_id;

	fd = open("/dev/dri/card0", O_RDWR | O_CLOEXEC);

	res = drmModeGetResources(fd);
	crtc_id = res->crtcs[0];
	conn_id = res->connectors[0];

	// 函数位置：./libdrm-2.4.123/xf86drm.c
	// 这是一个设置客户端能力的函数调用。
	drmSetClientCap(fd, DRM_CLIENT_CAP_UNIVERSAL_PLANES, 1);
	// 函数位置：./libdrm-2.4.123/xf86drmMode.c
	plane_res = drmModeGetPlaneResources(fd);
	plane_id = plane_res->planes[0];
	for(i = 0; i < plane_res->count_planes; i++) {
		printf("idx:%d, count:%d, plane_id:%d.\n", i, plane_res->count_planes, plane_res->planes[i]);
	}

	conn = drmModeGetConnector(fd, conn_id);
	buf.width = conn->modes[0].hdisplay;
	buf.height = conn->modes[0].vdisplay;

	modeset_create_fb(fd, &buf);

	drmModeSetCrtc(fd, crtc_id, buf.fb_id,
			0, 0, &conn_id, 1, &conn->modes[0]);

	getchar();

	/* crop the rect from framebuffer(100, 150) to crtc(50, 50)
	 * 位于./libdrm-2.4.123/xf86drm.c
	 ** /
	/* drm_public int drmModeSetPlane(int fd, uint32_t plane_id, uint32_t crtc_id,
		    uint32_t fb_id, uint32_t flags,
		    int32_t crtc_x, int32_t crtc_y,
		    uint32_t crtc_w, uint32_t crtc_h,
		    uint32_t src_x, uint32_t src_y,
		    uint32_t src_w, uint32_t src_h)
	* crtc_x, crtc_y为从显示器左上角开始显示的起始位置offset
	* crtc_w, crtc_h为显示器显示的大小
	* src_x, src_y为显示buffer的显示有效数据起始位置offset
	* src_w, src_h为显示buffer使用的大小
	* flag:
	* 0：不使用标志，表示平面以默认方式进行渲染。
	* DRM_MODE_PAGE_FLIP：如果设置了此标志，平面将以页面翻转的方式更新，这通常用于提高显示性能，特别是在视频播放时。
	* DRM_MODE_ATOMIC：如果系统支持原子操作（atomic modesetting），可以使用此标志来表示此设置是一个原子操作的一部分。原子操作可以使得多个显示属性的更改能够在一次更新中同时发生，以避免视觉上的干扰。
	* DRM_MODE_REFLECT_X 和 DRM_MODE_REFLECT_Y：这些标志用于翻转图像的方向，DRM_MODE_REFLECT_X 表示水平翻转，DRM_MODE_REFLECT_Y 表示垂直翻转。
	* DRM_MODE_SCALE：这个标志用于指定是否对平面进行缩放。
	* */
	drmModeSetPlane(fd, plane_id, crtc_id, buf.fb_id, 0,
			50, 50, 320, 320,
			100 << 16, 150 << 16, 320 << 16, 320 << 16);

	getchar();

	modeset_destroy_fb(fd, &buf);

	drmModeFreeConnector(conn);
	drmModeFreePlaneResources(plane_res);
	drmModeFreeResources(res);

	close(fd);

	return 0;
}

