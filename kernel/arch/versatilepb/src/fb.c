#include "mm/mmu.h"
#include "dev/fb.h"
#include "hardware.h"

int32_t videoInit(fb_info_t *fbInfo) {
	/*640x480*/
	*((uint32_t*)(MMIO_BASE | 0x1c)) = 0x2c77; //640x480
	*((uint32_t*)(MMIO_BASE | 0x00120000)) = 0x3f1f3f9c; 
	*((uint32_t*)(MMIO_BASE | 0x00120004)) = 0x090b61df; 
	*((uint32_t*)(MMIO_BASE | 0x00120008)) = 0x067f1800; 
	/*
	*((uint32_t*)(MMIO_BASE | 0x1c)) = 0x2cac; //800x600
	*((uint32_t*)(MMIO_BASE | 0x00120000)) = 0x1313a4c4;
	*((uint32_t*)(MMIO_BASE | 0x00120004)) = 0x0505f6f7; 
	*((uint32_t*)(MMIO_BASE | 0x00120008)) = 0x071f1800; 
	*/

	*((uint32_t*)(MMIO_BASE | 0x00120010)) = fbInfo->pointer; 
	*((uint32_t*)(MMIO_BASE | 0x00120018)) = 0x082b;
	return 0;
}

static fb_info_t _fbInfo __attribute__((aligned(16)));

inline fb_info_t* fb_get_info() {
	return &_fbInfo;
}

bool fb_init() {
	// initialize fbinfo 640x480
	_fbInfo.height = 480;
	_fbInfo.width = 640;
	_fbInfo.vheight = 480;
	_fbInfo.vwidth = 640;

	// initialize fbinfo 800x600
	/*
	_fbInfo.height = 600;
	_fbInfo.width = 800;
	_fbInfo.vheight = 600;
	_fbInfo.vwidth = 800;
	*/
	_fbInfo.pitch = 0;
	_fbInfo.depth = 32;
	_fbInfo.xoffset = 0;
	_fbInfo.yoffset = 0;
	_fbInfo.pointer = V2P(_fb_start);
	_fbInfo.size = 0;

	if(videoInit(&_fbInfo) == 0)
		return true;
	return false;
}

