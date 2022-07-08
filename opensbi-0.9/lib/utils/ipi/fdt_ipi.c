/*
 * SPDX-License-Identifier: BSD-2-Clause
 *
 * Copyright (c) 2020 Western Digital Corporation or its affiliates.
 *
 * Authors:
 *   Anup Patel <anup.patel@wdc.com>
 */

#include <sbi/sbi_scratch.h>
#include <sbi_utils/fdt/fdt_helper.h>
#include <sbi_utils/ipi/fdt_ipi.h>

extern struct fdt_ipi fdt_ipi_clint;

static struct fdt_ipi *ipi_drivers[] = {
	&fdt_ipi_clint
};

static void dummy_send(u32 target_hart)
{
}

static void dummy_clear(u32 target_hart)
{
}

static struct fdt_ipi dummy = {
	.match_table = NULL,
	.cold_init = NULL,
	.warm_init = NULL,
	.exit = NULL,
	.send = dummy_send,
	.clear = dummy_clear
};

static struct fdt_ipi *current_driver = &dummy;

void fdt_ipi_send(u32 target_hart)
{
	current_driver->send(target_hart);
}

void fdt_ipi_clear(u32 target_hart)
{
	current_driver->clear(target_hart);
}

void fdt_ipi_exit(void)
{
	if (current_driver->exit)
		current_driver->exit();
}

static int fdt_ipi_warm_init(void)
{
	if (current_driver->warm_init)
		return current_driver->warm_init();
	return 0;
}

static int __init fdt_ipi_cold_init(void)
{
	int pos, noff, rc;
	struct fdt_ipi *drv;
	const struct fdt_match *match;
	void *fdt = sbi_scratch_thishart_arg1_ptr();

	for (pos = 0; pos < array_size(ipi_drivers); pos++) {
		drv = ipi_drivers[pos];

		noff = -1;
		while ((noff = fdt_find_match(fdt, noff,
					drv->match_table, &match)) >= 0) {
			if (drv->cold_init) {
				rc = drv->cold_init(fdt, noff, match);
				if (rc)
					return rc;
			}
			current_driver = drv;
		}

		if (current_driver != &dummy)
			break;
	}

	return 0;
}

int __init fdt_ipi_init(bool cold_boot)
{
	int rc;

	if (cold_boot) {
		rc = fdt_ipi_cold_init();
		if (rc)
			return rc;
	}

	return fdt_ipi_warm_init();
}
