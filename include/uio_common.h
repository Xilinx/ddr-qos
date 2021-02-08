/*
 * Copyright 2021 Xilinx Inc.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef UIO_COMMON_H_
#define UIO_COMMON_H_

#include <stdint.h>
/***************** Macros (Inline Functions) Definitions *********************/
#define MAX_UIO_PATH_SIZE       256
#define MAX_UIO_NAME_SIZE       64
#define MAX_UIO_MAPS            5
#define UIO_INVALID_ADDR        0
#define XIL_COMPONENT_IS_READY  1
#define XIL_COMPONENT_NOT_READY 0
#define HW_WRITE(addr, off, val) *((volatile uint32_t *) ( ((uint8_t*)addr)+ off )) = (val)
#define HW_READ(addr,off) *((volatile uint32_t *) ( ((uint8_t*)addr) + off ))
#define Xil_AssertVoid(expr)    assert(expr)
#define Xil_AssertNonvoid(expr) assert(expr)


/**************************** Type Definitions ******************************/
typedef unsigned int u32;
typedef unsigned char u8;
typedef unsigned short int u16;

typedef struct {
	u32 addr;
	u32 size;
} uio_map;

typedef struct {
	int isInitialized;
	int  uio_fd;
	int  uio_num;
	char name[ MAX_UIO_NAME_SIZE ];
	char version[ MAX_UIO_NAME_SIZE ];
	uio_map maps[ MAX_UIO_MAPS ];
} uio_info;

typedef struct {
	void *Control_bus_BaseAddress; /* Base address of VCU APM */
	void *params[MAX_UIO_MAPS];
	u32 IsReady;
} uio_handle;

enum err_code {
	XST_SUCCESS,
	XST_FAILURE,
	XST_DEVICE_NOT_FOUND,
	XST_OPEN_DEVICE_FAILED,
	XST_ERR_TIMEOUT
};

int uio_Initialize(uio_info *InfoPtr, const char* InstanceName);
int uio_get_Handler(uio_info *InfoPtr, uio_handle *handle, int map_count);
int uio_release_handle(uio_info *InfoPtr, uio_handle *handle, int map_count);
int uio_Release(uio_info *InfoPtr);
#endif /* UIO_COMMON_H_ */
