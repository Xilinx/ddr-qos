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

#include <getopt.h>
#include <stdio.h>
#include <unistd.h>
#include <devmem_ddrqos.h>

int set_qos = -1;
int qos_type = -1;
int port_num = -1;
u32 qos_val = 0xf;

static u32 getopt_integer(char *optarg)
{
  int rc;
  u32 value;
  rc = sscanf(optarg, "0x%x", &value);
  if (rc <= 0)
    rc = sscanf(optarg, "%ul", &value);
  return value;
}

static struct option const long_opts[] = {
	{"set qos value :range[0-0x2] \n",
		required_argument, NULL, 's'},
	{"get qos value for the given port \n",
		required_argument, NULL, 'g'},
	{"port no[0-6]\n 0-port0\n 1-port1r\n"
			" 2-port2r\n 3-port3\n 4-port4\n 5-port5\n"
			" 6-all ports\n", required_argument, NULL, 'p'},
	{"version\n", required_argument, NULL, 'v'},
	{"help\n", no_argument, NULL, 'h'},
	{0, 0, 0, 0}
};

static int XDDRQos_rd_wr_qos(u32 metric, u32 port_num, u32 qos_val);

static void usage(const char *name)
{
	int i = 0;

	fprintf(stdout, "Xilinx copyright 2021\n\n");
	fprintf(stdout, "This application is to set QOS value for"
					"DDR slots\n on zynqmp platform\n\n");
	fprintf(stdout, "usage: %s [OPTIONS]\n\n", name);
	fprintf(stdout, "%s -s <val> -p <port num> \n\n", name);
	fprintf(stdout, "%s -g -p <port num> \n\n", name);

	for (i=0 ; i<(sizeof(long_opts)/sizeof(long_opts[0])) - 2; i++)
		fprintf(stdout, "-%c represents %s\n",
			long_opts[i].val, long_opts[i].name);
	i++;
}

int main(int argc, char *argv[])
{
	int cmd_opt;

	if (argc == 1) {
		usage(argv[0]);
		return 0;
	}

	while ((cmd_opt =
		getopt_long(argc, argv, "hgvc:s:p:", long_opts,
			    NULL)) != -1) {
		switch (cmd_opt) {
		case 0:
			/* long option */
			break;

		case 's':
			set_qos = 1;
			qos_val	= getopt_integer(optarg);
			if (qos_val < 0 || qos_val > 0x2) {
				printf("-s is to set qos value for the DDR ports\n"
						"select in the range of [0-0x2] \n");
				return 0;
			}
			break;

		case 'g':
			set_qos = 0;
			break;

		case 'p':
			port_num = getopt_integer(optarg);
			if (port_num < 0 || port_num > 0x6) {
				printf("-p: Invalid port number: select below option:\n 0-PORT0 \n 1-PORT1R \n"
					" 2-PORT2R \n 3-PORT3 \n 4-PORT4 \n 5-PORT5 \n 6-All ports\n"
					" setting to default value %x\n\n", port_num);
				return 0;
			}
			break;

		case 'v':
			printf("Xilinx zynqmp ddr qos app version 0.1 \n");
			return 0;
			break;

		case 'h':
			usage(argv[0]);
			return 0;
			break;
		default:
			printf("Invalid option. type -h for help \n");
			return 0;
		}
	}
	if (set_qos < 0 || port_num < 0) {
		printf("Invalid input, type -h for help\n");
		printf("Usage: \n");
		printf("%s -s <val> -p <port num> \n\n", argv[0]);
		printf("%s -g -p <port num> \n\n", argv[0]);
		return 0;
	}

	return XDDRQos_rd_wr_qos(set_qos, port_num, qos_val);
}


static int XDDRQos_rd_wr_qos(u32 metric, u32 port_num, u32 qos_val) {
	mem_info mem_handle;
	int ret;

	ret = uDDRQos_Init(&mem_handle);
	if (ret > 0)
		return ret;

	if (metric)
		XDDRQos_SetQos(&mem_handle, port_num, qos_val);
	else
		XDDRQos_GetQos(&mem_handle, port_num);

	return uDDRQos_DeInit(&mem_handle);
}

