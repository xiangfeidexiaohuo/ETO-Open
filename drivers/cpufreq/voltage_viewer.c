/*
 * Author: 未霜 (Coolapk @SegmentFault) <799620521@qq.com>
 *
 * This program will provide a sysfs interface to read the voltage 
 * value of the register. The path is at "/sys/devices/system/cpu/cpu(*)/
 * cpufreq/UV_mv_table". File format meets two standards, the relevant
 * definitions of the two standards will be explained below.
 *
 */

/*
 * Possible values for "profile" are :
 *
 *   0 - Disable
 *   1 - File format for Kernel Adiutor (Default)
 *   2 - File format for EX Kernel Manager
 *
 */

#include <linux/sysfs.h>
#include <linux/voltage_viewer.h>
#include <linux/string.h>
#include <linux/module.h>
#include <linux/pm_opp.h>

Voltage_Table pwrcl_clk_vdd;
Voltage_Table perfcl_clk_vdd;
Voltage_Table dev_clk_vdd;

unsigned int profile = 1;
module_param(profile, uint, 0644);

ssize_t get_Voltages(char *buf)
{
	ssize_t count = 0;
	unsigned int i;

	switch (profile) {
	case 0:
		count += sprintf(buf + count, "<unsuppoorted>\n");
		break;
	case 1:
		for (i = 0; i < pwrcl_clk_vdd.size; i++)
			count += sprintf(buf + count, "pwrcl:%lumhz: %d mV\n", pwrcl_clk_vdd.rate[i] / 1000000, pwrcl_clk_vdd.uv[i] / 1000);
		for (i = 0; i < perfcl_clk_vdd.size; i++)
			count += sprintf(buf + count, "perfcl:%lumhz: %d mV\n", perfcl_clk_vdd.rate[i] / 1000000, perfcl_clk_vdd.uv[i] / 1000);
		for (i = 0; i < dev_clk_vdd.size; i++) {
			if (strcmp (dev_clk_vdd.dev_name[i], "soc:qcom,l3-cpu0") == 0)
				count += sprintf(buf + count, "l3-pwrcl:%lumhz: %d mV\n", dev_clk_vdd.rate[i] / 1000000, dev_clk_vdd.uv[i] / 1000);
			else if (strcmp (dev_clk_vdd.dev_name[i], "soc:qcom,l3-cpu4") == 0)
				count += sprintf(buf + count, "l3-perfcl:%lumhz: %d mV\n", dev_clk_vdd.rate[i] / 1000000, dev_clk_vdd.uv[i] / 1000);
			else if (strcmp (dev_clk_vdd.dev_name[i], "soc:qcom,l3-cdsp") == 0)
				count += sprintf(buf + count, "l3-cdsp:%lumhz: %d mV\n", dev_clk_vdd.rate[i] / 1000000, dev_clk_vdd.uv[i] / 1000);
			else if (strcmp (dev_clk_vdd.dev_name[i], "5000000.qcom,kgsl-3d0") == 0)
			count += sprintf(buf + count, "kgsl-3d0:%lumhz: %d mV\n", dev_clk_vdd.rate[i] / 1000000, dev_clk_vdd.uv[i] / 1000);
		}
		break;
	case 2:
		for (i = 0; i < pwrcl_clk_vdd.size; i++)
			count += sprintf(buf + count, "%lumhz: %d mV\n", pwrcl_clk_vdd.rate[i] / 1000000, pwrcl_clk_vdd.uv[i] / 1000);
		for (i = 0; i < perfcl_clk_vdd.size; i++)
			count += sprintf(buf + count, "%lumhz: %d mV\n", perfcl_clk_vdd.rate[i] / 1000000, perfcl_clk_vdd.uv[i] / 1000);
		for (i = 0; i < dev_clk_vdd.size; i++) {
			if (strcmp (dev_clk_vdd.dev_name[i], "soc:qcom,l3-cpu0") == 0)
				count += sprintf(buf + count, "%lumhz: %d mV\n", dev_clk_vdd.rate[i] / 1000000, dev_clk_vdd.uv[i] / 1000);
			else if (strcmp (dev_clk_vdd.dev_name[i], "soc:qcom,l3-cpu4") == 0)
				count += sprintf(buf + count, "%lumhz: %d mV\n", dev_clk_vdd.rate[i] / 1000000, dev_clk_vdd.uv[i] / 1000);
			else if (strcmp (dev_clk_vdd.dev_name[i], "soc:qcom,l3-cdsp") == 0)
				count += sprintf(buf + count, "%lumhz: %d mV\n", dev_clk_vdd.rate[i] / 1000000, dev_clk_vdd.uv[i] / 1000);
			else if (strcmp (dev_clk_vdd.dev_name[i], "5000000.qcom,kgsl-3d0") == 0)
			count += sprintf(buf + count, "%lumhz: %d mV\n", dev_clk_vdd.rate[i] / 1000000, dev_clk_vdd.uv[i] / 1000);
		}
		break;
	}
	return count;
}


