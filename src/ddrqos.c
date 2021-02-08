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
#include <uio_ddrqos.h>
#include "uio_common.h"
#include <unistd.h>


#define DEFAULT_METRIC			(0x0)
#define DEFAULT_QOSVAL			(0x0)
#define DEFAULT_PORTNUM			(0x0)

u32 metric = DEFAULT_METRIC;
u32 qos_val = DEFAULT_QOSVAL;
u32 port_num = DEFAULT_PORTNUM;

static uint32_t getopt_integer(char *optarg)
{
  int rc;
  uint32_t value;
  rc = sscanf(optarg, "0x%x", &value);
  if (rc <= 0)
    rc = sscanf(optarg, "%ul", &value);
  return value;
}

static struct option const long_opts[] = {
	{"metric [0-1]\n 0: set_qos \n 1: get_qos\n", required_argument, NULL, 'm'},
	{"port no[0-6]\n 0-PORT0\n 1-PORT1R\n"
			" 2-PORT2R\n 3-PORT3\n 4-PORT4\n 5-PORT5\n"
			" 6-All ports\n", required_argument, NULL, 'p'},
	{"QoS value range[0x0-0x2]\n 0: BEST EFFORT\n"
			" 1: VIDEO CLASS\n 2: LOW LATENCY\n",
							 required_argument, NULL, 'v'},
	{"help\n", no_argument, NULL, 'h'},
	{0, 0, 0, 0}
};
static int XDDRQos_rd_wr_qos(u32 metric, u32 port_num, u32 qos_val);

static void usage(const char *name)
{
	int i = 0;

	fprintf(stdout, "%s\n\n", name);
	fprintf(stdout, "usage: %s [OPTIONS]\n\n", name);

	for (i=0 ; i<(sizeof(long_opts)/sizeof(long_opts[0])) - 2; i++)
		fprintf(stdout, "-%c represents %s\n",
			long_opts[i].val, long_opts[i].name);
	fprintf(stdout, "-%c (%s) print usage help and exit\n",
		long_opts[i].val, long_opts[i].name);
	i++;
}

int main(int argc, char *argv[])
{
	int cmd_opt;

	while ((cmd_opt =
		getopt_long(argc, argv, "hc:m:p:v:", long_opts,
			    NULL)) != -1) {
		switch (cmd_opt) {
		case 0:
			/* long option */
			break;
		case 'm':
			metric = getopt_integer(optarg);
			if (metric < 0 || metric > 0x1) {
				metric = DEFAULT_METRIC;
				printf("-m: Invalid selection: select\n 0: get_qos\n 1: set_qos\n"
					 "setting to default value %d\n\n", metric);
			}
			break;

		case 'p':
			port_num = getopt_integer(optarg);
			if (port_num < 0 || port_num > 0x6) {
				port_num = DEFAULT_PORTNUM;
				printf("-p: Invalid port number: select below option:\n 0-PORT0 \n 1-PORT1R \n"
					" 2-PORT2R \n 3-PORT3 \n 4-PORT4 \n 5-PORT5 \n 6-All ports\n"
					" setting to default value %x\n\n", port_num);
			}
			break;

		case 'v':
			qos_val	= getopt_integer(optarg);
			if (qos_val < 0 || qos_val > 0x2) {
				qos_val = DEFAULT_QOSVAL;
				printf("-v Invalid QOS value: range [0-0x2]\n"
					" 0-BEST_EFFORT\n 1-VIDEO_CLASS\n 2-LOW_LATENCY\n "
					"setting to default value %d\n\n", qos_val);
			}
			break;

		case 'h':
		default:
			usage(argv[0]);
			return 0;
			break;
		}
	}
	if (cmd_opt == 0) {
		usage(argv[0]);
		return 0;
	}
	return XDDRQos_rd_wr_qos(metric, port_num, qos_val);
}

static int XDDRQos_rd_wr_qos(u32 metric, u32 port_num, u32 qos_val) {
	uio_handle qos_handle;
	int ret;

	ret = uDDRQos_Init(&qos_handle);
	if (ret > 0)
		return ret;

	if (metric)
		XDDRQos_SetQos(&qos_handle, port_num, qos_val);
	else
		XDDRQos_GetQos(&qos_handle, port_num);

	return uDDRQos_DeInit(&qos_handle);
}

