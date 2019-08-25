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

#ifndef _LINUX_VOLTAGE_VIEWER_H
#define _LINUX_VOLTAGE_VIEWER_H

typedef struct{
	unsigned int size;
	char dev_name[60][32];
	unsigned long rate[60];
	unsigned int uv[60];
}Voltage_Table;

extern Voltage_Table pwrcl_clk_vdd;
extern Voltage_Table perfcl_clk_vdd;
extern Voltage_Table dev_clk_vdd;

extern ssize_t get_Voltages(char *buf);

#endif
