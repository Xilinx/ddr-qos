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

#include <assert.h>
#include <unistd.h>
#include <stdio.h>
#include <uio_common.h>
#include <uio_ddrqos.h>

static uio_info uQosInfo;

u32 port_info[] = { DDR_QOS_PORT_TYPE_PORT0_TYPE_SHIFT,
					DDR_QOS_PORT_TYPE_PORT1R_TYPE_SHIFT,
					DDR_QOS_PORT_TYPE_PORT2R_TYPE_SHIFT,
					DDR_QOS_PORT_TYPE_PORT3_TYPE_SHIFT,
					DDR_QOS_PORT_TYPE_PORT4_TYPE_SHIFT,
					DDR_QOS_PORT_TYPE_PORT5_TYPE_SHIFT
					};

int XDDRQos_SetQos(const uio_handle *InstancePtr, u32 Port, u32 Val) {
	u32 Reg_Value;
	u32 New_Val;

	/*
	 * Assert the arguments.
	 */
	if ((Val <  DDR_QOS_TYPE_BEST_EFFORT || Val > DDR_QOS_TYPE_VIDEO_CLASS) ||
					(Port < PORT0 || Port > PORT_MAX)) {
		return -XST_FAILURE;
	}

	Xil_AssertVoid(InstancePtr != NULL);
	Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

	Reg_Value = XDDRQos_ReadReg(InstancePtr->Control_bus_BaseAddress, DDR_QOS_PORT_TYPE_OFFSET);
	/*
	 * Set Qos Value
	 */
	if (Port == PORT_MAX) {
			New_Val = (Reg_Value & ~DDR_QOS_PORT_TYPE_PORT_FULL_MASK) |
				  (Val << DDR_QOS_PORT_TYPE_PORT5_TYPE_SHIFT |
				  Val << DDR_QOS_PORT_TYPE_PORT4_TYPE_SHIFT |
				  Val << DDR_QOS_PORT_TYPE_PORT3_TYPE_SHIFT |
				  Val << DDR_QOS_PORT_TYPE_PORT2R_TYPE_SHIFT |
				  Val << DDR_QOS_PORT_TYPE_PORT1R_TYPE_SHIFT |
				  Val << DDR_QOS_PORT_TYPE_PORT0_TYPE_SHIFT) ;
	} else {
		switch (Port) {
		case 0:
			New_Val = ((Reg_Value  & ~DDR_QOS_PORT_TYPE_PORT0_TYPE_MASK) |
					(Val << DDR_QOS_PORT_TYPE_PORT0_TYPE_SHIFT));
			break;

		case 1:
			New_Val = ((Reg_Value  & ~DDR_QOS_PORT_TYPE_PORT1R_TYPE_MASK) |
                    (Val << DDR_QOS_PORT_TYPE_PORT1R_TYPE_SHIFT));
			break;
		case 2:
			New_Val = ((Reg_Value  & ~DDR_QOS_PORT_TYPE_PORT2R_TYPE_MASK) |
                    (Val << DDR_QOS_PORT_TYPE_PORT2R_TYPE_SHIFT));
			break;
		case 3:
			New_Val = ((Reg_Value  & ~DDR_QOS_PORT_TYPE_PORT3_TYPE_MASK) |
                    (Val << DDR_QOS_PORT_TYPE_PORT3_TYPE_SHIFT));
			break;
		case 4:
			New_Val = ((Reg_Value  & ~DDR_QOS_PORT_TYPE_PORT4_TYPE_MASK) |
                    (Val << DDR_QOS_PORT_TYPE_PORT4_TYPE_SHIFT));
			break;
		case 5:
			New_Val = ((Reg_Value  & ~DDR_QOS_PORT_TYPE_PORT5_TYPE_MASK) |
                    (Val << DDR_QOS_PORT_TYPE_PORT5_TYPE_SHIFT));
			break;
		default:
			printf("Invalid port selection\n");
			break;
		}
	}
	XDDRQos_WriteReg(InstancePtr->Control_bus_BaseAddress, DDR_QOS_PORT_TYPE_OFFSET, New_Val);
	printf("DDR QoS is successfully  set for port %x\n", Port);
	return XST_SUCCESS;
}

int XDDRQos_GetQos(const uio_handle *InstancePtr, u32 Port) {
	u32 Reg_Value;
	u32 Val;
	int i;

	/*
	 * Assert the arguments.
	 */
	if (Port < PORT0 || Port > PORT_MAX) {
		return -XST_FAILURE;
	}

	Xil_AssertVoid(InstancePtr != NULL);
	Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

	Reg_Value = XDDRQos_ReadReg(InstancePtr->Control_bus_BaseAddress,
            DDR_QOS_PORT_TYPE_OFFSET);
	/*
	 * Set Qos Value
	 */
	if (Port == PORT_MAX) {
		for (i = 0; i < PORT_MAX; i++) {
			Val = ( Reg_Value >> port_info[i]) & 0x3;
			printf("DDR QoS for Port number %x is %x\n", i, Val);
		}
	} else {
		switch (Port) {
		case 0:
			Val = (Reg_Value >> DDR_QOS_PORT_TYPE_PORT0_TYPE_SHIFT) & 0x3;
			printf("DDR QoS for Port number %x is %x\n", Port, Val);
			break;
		case 1:
			Val = (Reg_Value >> DDR_QOS_PORT_TYPE_PORT1R_TYPE_SHIFT) & 0x3;
			printf("DDR QoS for Port number %x is %x\n", Port, Val);
			break;
		case 2:
			Val = (Reg_Value >> DDR_QOS_PORT_TYPE_PORT2R_TYPE_SHIFT) & 0x3;
			printf("DDR QoS for Port number %x is %x\n", Port, Val);
			break;
		case 3:
			Val = (Reg_Value >> DDR_QOS_PORT_TYPE_PORT3_TYPE_SHIFT) & 0x3;
			printf("DDR QoS for Port number %x is %x\n", Port, Val);
			break;
		case 4:
			Val = (Reg_Value >> DDR_QOS_PORT_TYPE_PORT4_TYPE_SHIFT) & 0x3;
			printf("DDR QoS for Port number %x is %x\n", Port, Val);
			break;
		case 5:
			Val = (Reg_Value >> DDR_QOS_PORT_TYPE_PORT5_TYPE_SHIFT) & 0x3;
			printf("DDR QoS for Port number %x is %x\n", Port, Val);
			break;
		default:
			printf("Invalid port no selection %x\n", Port);

		}
	}
	return XST_SUCCESS;
}

int uDDRQos_Init(uio_handle *qos_handle) {

	int ret = uio_Initialize(&uQosInfo, DDRQOS_INSTANCE_NAME);
	if (ret == XST_DEVICE_NOT_FOUND)
		return ret;

	assert(uQosInfo.isInitialized == XIL_COMPONENT_IS_READY);
	ret = uio_get_Handler(&uQosInfo, qos_handle, MAP_CNT);
	if (ret != XST_SUCCESS)
		return ret;
	assert(qos_handle->IsReady == XIL_COMPONENT_IS_READY);
	return ret;
}

int uDDRQos_DeInit(uio_handle *qos_handle) {

	int ret;

	assert(qos_handle->IsReady == XIL_COMPONENT_IS_READY);
	ret = uio_release_handle(&uQosInfo, qos_handle, MAP_CNT);
	if (ret != XST_SUCCESS)
		return ret;
	ret = uio_Release(&uQosInfo);
	if (ret != XST_SUCCESS)
			return ret;

	return ret;
}
