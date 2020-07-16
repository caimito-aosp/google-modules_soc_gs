/* SPDX-License-Identifier: GPL-2.0-only
 *
 * Copyright 2020 Google LLC
 *
 */
#ifndef __ACPM_H__
#define __ACPM_H__

struct acpm_info {
	struct device *dev;
	void __iomem *timer_base;
	unsigned int timer_cnt;
	unsigned int enter_wfi;
};

extern void *memcpy_align_4(void *dest, const void *src, unsigned int n);

#define GS_PMU_CORTEX_APM_CONFIGURATION                           (0x0100)
#define GS_PMU_CORTEX_APM_STATUS                                  (0x0104)
#define GS_PMU_CORTEX_APM_OPTION                                  (0x0108)
#define GS_PMU_CORTEX_APM_DURATION0                               (0x0110)
#define GS_PMU_CORTEX_APM_DURATION1                               (0x0114)
#define GS_PMU_CORTEX_APM_DURATION2                               (0x0118)
#define GS_PMU_CORTEX_APM_DURATION3                               (0x011C)

#define GS_TIMER_APM_TCVR					      (0x0008)


#define APM_LOCAL_PWR_CFG_RESET         (~(0x1 << 0))

extern struct acpm_framework *acpm_initdata;
extern void __iomem *acpm_srambase;
extern void *get_fvmap_base(void);

#endif
