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

#include <devmem_ddrqos.h>

u32 port_info[] = { DDR_QOS_PORT_TYPE_PORT0_TYPE_SHIFT,
					DDR_QOS_PORT_TYPE_PORT1R_TYPE_SHIFT,
					DDR_QOS_PORT_TYPE_PORT2R_TYPE_SHIFT,
					DDR_QOS_PORT_TYPE_PORT3_TYPE_SHIFT,
					DDR_QOS_PORT_TYPE_PORT4_TYPE_SHIFT,
					DDR_QOS_PORT_TYPE_PORT5_TYPE_SHIFT
					};

int XDDRQos_SetQos(const mem_info *InstancePtr, u32 Port, u32 Val) {
	u32 Reg_Value;
	u32 New_Val;

	if (InstancePtr == NULL) {
        printf("%s Null instance pointer passed\n", __func__);
        return FAIL;
    }

    if (InstancePtr->IsReady != XIL_COMPONENT_IS_READY) {
        printf("Instance mapping not ready");
        return FAIL;
    }

	/*
	 * Assert the arguments.
	 */
	if ((Val <  DDR_QOS_TYPE_BEST_EFFORT || Val > DDR_QOS_TYPE_VIDEO_CLASS) ||
					(Port < PORT0 || Port > PORT_MAX)) {
		return -FAIL;
	}

	Reg_Value = XDDRQos_ReadReg(InstancePtr->Control_bus_BaseAddress,
											DDR_QOS_PORT_TYPE_OFFSET);
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
		case PORT0:
			New_Val = ((Reg_Value  & ~DDR_QOS_PORT_TYPE_PORT0_TYPE_MASK) |
					(Val << DDR_QOS_PORT_TYPE_PORT0_TYPE_SHIFT));
			break;

		case PORT1R:
			New_Val = ((Reg_Value  & ~DDR_QOS_PORT_TYPE_PORT1R_TYPE_MASK) |
                    (Val << DDR_QOS_PORT_TYPE_PORT1R_TYPE_SHIFT));
			break;
		case PORT2R:
			New_Val = ((Reg_Value  & ~DDR_QOS_PORT_TYPE_PORT2R_TYPE_MASK) |
                    (Val << DDR_QOS_PORT_TYPE_PORT2R_TYPE_SHIFT));
			break;
		case PORT3:
			New_Val = ((Reg_Value  & ~DDR_QOS_PORT_TYPE_PORT3_TYPE_MASK) |
                    (Val << DDR_QOS_PORT_TYPE_PORT3_TYPE_SHIFT));
			break;
		case PORT4:
			New_Val = ((Reg_Value  & ~DDR_QOS_PORT_TYPE_PORT4_TYPE_MASK) |
                    (Val << DDR_QOS_PORT_TYPE_PORT4_TYPE_SHIFT));
			break;
		case PORT5:
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
	return SUCCESS;
}

int XDDRQos_GetQos(const mem_info *InstancePtr, u32 Port) {
	u32 Reg_Value;
	u32 Val;
	int i;

	if (InstancePtr == NULL) {
        printf("%s Null instance pointer passed\n", __func__);
        return FAIL;
    }

    if (InstancePtr->IsReady != XIL_COMPONENT_IS_READY) {
        printf("Instance mapping not ready");
        return FAIL;
    }

	/*
	 * Assert the arguments.
	 */
	if (Port < PORT0 || Port > PORT_MAX) {
		return FAIL;
	}

	Reg_Value = XDDRQos_ReadReg(InstancePtr->Control_bus_BaseAddress,
            DDR_QOS_PORT_TYPE_OFFSET);
	/*
	 * Set Qos Value
	 */
	if (Port == PORT_MAX) {
		for (i = 0; i < PORT_MAX; i++) {
			Val = ( Reg_Value >> port_info[i]) & DDR_QOS_MASK;
			printf("DDR QoS for Port number %x is %x\n", i, Val);
		}
	} else {
		switch (Port) {
		case PORT0:
			Val = (Reg_Value >> DDR_QOS_PORT_TYPE_PORT0_TYPE_SHIFT) &
																DDR_QOS_MASK;
			break;
		case PORT1R:
			Val = (Reg_Value >> DDR_QOS_PORT_TYPE_PORT1R_TYPE_SHIFT) &
																DDR_QOS_MASK;
			break;
		case PORT2R:
			Val = (Reg_Value >> DDR_QOS_PORT_TYPE_PORT2R_TYPE_SHIFT) &
																DDR_QOS_MASK;
			break;
		case PORT3:
			Val = (Reg_Value >> DDR_QOS_PORT_TYPE_PORT3_TYPE_SHIFT) &
																DDR_QOS_MASK;
			break;
		case PORT4:
			Val = (Reg_Value >> DDR_QOS_PORT_TYPE_PORT4_TYPE_SHIFT) &
																DDR_QOS_MASK;
			break;
		case PORT5:
			Val = (Reg_Value >> DDR_QOS_PORT_TYPE_PORT5_TYPE_SHIFT) &
																DDR_QOS_MASK;
			break;
		default:
			printf("Invalid port no selection %x\n", Port);

		}
		printf("DDR QoS for Port number %x is %x\n", Port, Val);
	}
	return SUCCESS;
}

int uDDRQos_Init(mem_info *mem_handle) {

	mem_handle->memfd = open("/dev/mem", O_RDWR | O_SYNC);
	if (mem_handle->memfd == -1) {
		printf("Can't open /dev/mem.\n");
		return FAIL;
	}

	mem_handle->Control_bus_BaseAddress = mmap(0, MAP_SIZE, PROT_READ | PROT_WRITE,
							MAP_SHARED, mem_handle->memfd, DDR_QOS_CTRL_BASE & ~MAP_MASK);
	if (mem_handle->Control_bus_BaseAddress == (void *) -1) {
		close(mem_handle->memfd);
		printf("Can't map the memory to user space.\n");
		return FAIL;
	}
	mem_handle->IsReady = XIL_COMPONENT_IS_READY;
	return SUCCESS;
}

int uDDRQos_DeInit(mem_info *mem_handle) {

	if (mem_handle->IsReady)
	{
		if (munmap(mem_handle->Control_bus_BaseAddress, MAP_SIZE) == -1) {
			 printf("Can't unmap memory from user space.\n");
			 return FAIL;
		}

		close(mem_handle->memfd);
		mem_handle->Control_bus_BaseAddress = NULL;
		mem_handle->IsReady = XIL_COMPONENT_NOT_READY;
	}

	return SUCCESS;
}
