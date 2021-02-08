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

#ifndef UAXI_QOS_H_
#define UAXI_QOS_H_

#include "uio_common.h"

#define DDRQOS_INSTANCE_NAME	"ddr_qos"
#define MAP_CNT             0x1

#define DDR_QOS_PORT_TYPE_OFFSET	0x00

#define EXIT_SUCCESS	0
#define EXIT_FAIL		1

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


#define XDDRQos_ReadReg 	HW_READ
#define XDDRQos_WriteReg 	HW_WRITE


enum DDRQos_PORT {
	PORT0,
	PORT1R,
	PORT2R,
	PORT3,
	PORT4,
	PORT5,
	PORT_MAX,
};

int uDDRQos_Init(uio_handle *qos_handle);
int uDDRQos_DeInit(uio_handle *qos_handle);
int XDDRQos_SetQos(const uio_handle *InstancePtr, u32 Port, u32 Val);
int XDDRQos_GetQos(const uio_handle *InstancePtr, u32 Port);
#endif /* UAFIFM_QOS_H_ */
