/*
 * sun50i H616 LPDDR4-1200 timings, as programmed by Allwinner's boot0
 *
 * The chips are probably able to be driven by a faster clock, but boot0
 * uses a more conservative timing (as usual).
 *
 * (C) Copyright 2020 Jernej Skrabec <jernej.skrabec@siol.net>
 * Based on H6 DDR3 timings:
 * (C) Copyright 2018,2019 Arm Ltd.
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */

#include <common.h>
#include <asm/arch/dram.h>
#include <asm/arch/cpu.h>

void mctl_set_timing_params(const struct dram_para *para)
{
	struct sunxi_mctl_ctl_reg * const mctl_ctl =
			(struct sunxi_mctl_ctl_reg *)SUNXI_DRAM_CTL0_BASE;

	u8 tccd		= 4;			/* JEDEC: 4nCK */
	u8 tfaw		= ns_to_t(36);		/* JEDEC: 30 ns w/ 1K pages */
	u8 trrd		= max(ns_to_t(6), 4);	/* JEDEC: max(6 ns, 4nCK) */
	u8 trcd		= ns_to_t(17);		/* JEDEC: 13.5 ns */
	u8 trc		= ns_to_t(60);		/* JEDEC: 49.5 ns */
	u8 txp		= max(ns_to_t(6), 3);	/* JEDEC: max(6 ns, 3nCK) */
	u8 trtp		= max(ns_to_t(8), 4);	/* JEDEC: max(7.5 ns, 4nCK) */
	u8 trp		= ns_to_t(20);		/* JEDEC: >= 13.75 ns */
	u8 tras		= ns_to_t(40);		/* JEDEC >= 36 ns, <= 9*trefi */
	u16 trefi	= ns_to_t(7800) / 32;	/* JEDEC: 7.8us@Tcase <= 85C */
	u16 trfc	= ns_to_t(350);		/* JEDEC: 160 ns for 2Gb */
	u16 txsr	= 69;			/* ? */

	u8 tmrw		= 6;			/* ? */
	u8 tmrd		= 6;			/* JEDEC: 4nCK */
	u8 tmod		= max(ns_to_t(15), 12);	/* JEDEC: max(15 ns, 12nCK) */
	u8 tcke		= max(ns_to_t(6), 6);	/* JEDEC: max(5.625 ns, 3nCK) */
	u8 tcksrx	= max(ns_to_t(5), 2);	/* JEDEC: max(10 ns, 5nCK) */
	u8 tcksre	= max(ns_to_t(5), 2);	/* JEDEC: max(10 ns, 5nCK) */
	u8 tckesr	= tcke;		/* JEDEC: tCKE(min) + 1nCK */
	u8 trasmax	= (para->clk / 2) / 32;	/* JEDEC: tREFI * 9 */
	u8 txs		= ns_to_t(380) / 32;	/* JEDEC: max(5nCK,tRFC+10ns) */
	u8 txsdll	= 16;			/* JEDEC: 512 nCK */
	u8 txsabort	= 4;			/* ? */
	u8 txsfast	= 4;			/* ? */
	u8 tcl		= 10;			/* JEDEC: CL / 2 => 6 */
	u8 tcwl		= 5;			/* JEDEC: 8 */
	u8 t_rdata_en	= 9;			/* ? */

	u8 twtp		= 24;			/* (WL + BL / 2 + tWR) / 2 */
	u8 twr2rd	= trtp + 14;		/* (WL + BL / 2 + tWTR) / 2 */
	u8 trd2wr	= 18;			/* (RL + BL / 2 + 2 - WL) / 2 */

	/* set DRAM timing */
	writel((twtp << 24) | (tfaw << 16) | (trasmax << 8) | tras,
	       &mctl_ctl->dramtmg[0]);
	writel((txp << 16) | (trtp << 8) | trc, &mctl_ctl->dramtmg[1]);
	writel((tcwl << 24) | (tcl << 16) | (trd2wr << 8) | twr2rd,
	       &mctl_ctl->dramtmg[2]);
	writel((tmrw << 20) | (tmrd << 12) | tmod, &mctl_ctl->dramtmg[3]);
	writel((trcd << 24) | (tccd << 16) | (trrd << 8) | trp,
	       &mctl_ctl->dramtmg[4]);
	writel((tcksrx << 24) | (tcksre << 16) | (tckesr << 8) | tcke,
	       &mctl_ctl->dramtmg[5]);
	/* Value suggested by ZynqMP manual and used by libdram */
	writel((txp + 2) | 0x02020000, &mctl_ctl->dramtmg[6]);
	writel((txsfast << 24) | (txsabort << 16) | (txsdll << 8) | txs,
	       &mctl_ctl->dramtmg[8]);
	writel(0x00020208, &mctl_ctl->dramtmg[9]);
	writel(0xE0C05, &mctl_ctl->dramtmg[10]);
	writel(0x440C021C, &mctl_ctl->dramtmg[11]);
	writel(8, &mctl_ctl->dramtmg[12]);
	writel(0xA100002, &mctl_ctl->dramtmg[13]);
	writel(txsr, &mctl_ctl->dramtmg[14]);

	writel(0x203f0, &mctl_ctl->init[0]);
	writel(0x1f20000, &mctl_ctl->init[1]);
	writel(0xd05, &mctl_ctl->init[2]);
	writel(0x0034001b, &mctl_ctl->init[3]);
	writel(0x00330000, &mctl_ctl->init[4]);
	writel(0x00100004, &mctl_ctl->init[5]);
	writel(0x00040072, &mctl_ctl->init[6]);
	writel(0x00240009, &mctl_ctl->init[7]);

	writel(0, &mctl_ctl->dfimisc);
	clrsetbits_le32(&mctl_ctl->rankctl, 0xff0, 0x660);

	/* Configure DFI timing */
	writel(0x02918005, &mctl_ctl->dfitmg0);
	writel(0x100202, &mctl_ctl->dfitmg1);

	/* set refresh timing */
	writel(0x002b0041, &mctl_ctl->rfshtmg);
}