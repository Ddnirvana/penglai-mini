/* SPDX-License-Identifier: GPL-2.0 WITH Linux-syscall-note */
/*
 * Copyright (C) 2012 ARM Ltd.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#ifndef __ASM_BITSPERLONG_H
#define __ASM_BITSPERLONG_H

#if defined(__LP64__)
/* Assuming __LP64__ will be defined for native ELF64's and not for ILP32. */
#  define __BITS_PER_LONG 64
#elif defined(__ILP32__)
#  define __BITS_PER_LONG 32
#else
#  error "Neither LP64 nor ILP32: unsupported ABI in asm/bitsperlong.h"
#endif

#include <asm-generic/bitsperlong.h>

#endif	/* __ASM_BITSPERLONG_H */
