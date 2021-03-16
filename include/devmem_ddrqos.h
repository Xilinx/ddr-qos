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

#ifndef DDR_QOS_H_
#define DDR_QOS_H_

#include <assert.h>
#include <unistd.h>
#include <stdio.h>
#include <stddef.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <stdlib.h>
#include <stdint.h>

#define DDRQOS_INSTANCE_NAME	"ddr_qos"
#define MAP_CNT             0x1

#define DDR_QOS_PORT_TYPE_OFFSET	0x00

#define SUCCESS		0
#define FAIL		-1

#define DDR_QOS_TYPE_BEST_EFFORT  0x0
#define DDR_QOS_TYPE_LOW_LATENCY  0x1
#define DDR_QOS_TYPE_VIDEO_CLASS  0x2

#define DDR_QOS_PORT_TYPE_PORT0_TYPE_SHIFT	0
#define DDR_QOS_PORT_TYPE_PORT1R_TYPE_SHIFT	2
#define DDR_QOS_PORT_TYPE_PORT2R_TYPE_SHIFT	6
#define DDR_QOS_PORT_TYPE_PORT3_TYPE_SHIFT	10
#define DDR_QOS_PORT_TYPE_PORT4_TYPE_SHIFT	12
#define DDR_QOS_PORT_TYPE_PORT5_TYPE_SHIFT	14


#define DDR_QOS_PORT_TYPE_PORT0_TYPE_MASK	0x3
#define DDR_QOS_PORT_TYPE_PORT1R_TYPE_MASK	0xC
#define DDR_QOS_PORT_TYPE_PORT2R_TYPE_MASK	0xC0
#define DDR_QOS_PORT_TYPE_PORT3_TYPE_MASK	0xC00
#define DDR_QOS_PORT_TYPE_PORT4_TYPE_MASK	0x3000
#define DDR_QOS_PORT_TYPE_PORT5_TYPE_MASK	0xC000
#define DDR_QOS_PORT_TYPE_PORT_FULL_MASK	0xFFFF

#define DDR_QOS_MASK		0x3

#define SUCCESS     0
#define FAIL        -1

#define XIL_COMPONENT_IS_READY  1
#define XIL_COMPONENT_NOT_READY 0

#define DDR_QOS_CTRL_BASE		0xFD090000
#define MAP_SIZE 4096UL
#define MAP_MASK (MAP_SIZE - 1)

#define XDDRQos_ReadReg(addr,off)   *((volatile uint32_t *) ( ((uint8_t*)addr) + off ))
#define XDDRQos_WriteReg(addr, off, val)    *((volatile uint32_t *) ( ((uint8_t*)addr)+ off )) = (val)

/**************************** Type Definitions ******************************/
typedef unsigned int u32;
typedef unsigned char u8;
typedef unsigned short int u16;

typedef struct {
    int IsReady;
    int memfd;
    void *Control_bus_BaseAddress;
} mem_info;

enum Qos_Type {
    RD_QOS = 1,
    WR_QOS,
    RD_ISSUE,
    WR_ISSUE,
};


enum DDRQos_PORT {
	PORT0,
	PORT1R,
	PORT2R,
	PORT3,
	PORT4,
	PORT5,
	PORT_MAX,
};

int uDDRQos_Init(mem_info *qos_handle);
int uDDRQos_DeInit(mem_info *qos_handle);
int XDDRQos_SetQos(const mem_info *InstancePtr, u32 Port, u32 Val);
int XDDRQos_GetQos(const mem_info *InstancePtr, u32 Port);
#endif /* DDR_QOS_H_ */
