/* SPDX-License-Identifier: GPL-2.0 */
/*
 * Copyright (C) 2021 Samsung Electronics.
 *
 */

#ifndef __DIT_2_2_0_H__
#define __DIT_2_2_0_H__

#define DIT_REG_CLK_GT_OFF			0x0100 /* 20 bit */
#define DIT_REG_DMA_INIT_DATA			0x0104 /* 28 bit */

/* 0:16beat, 1:8beat, 2:4beat, 3:2beat, 4:1beat */
#define DIT_REG_TX_DESC_CTRL_SRC		0x0108 /* 3 bit */
#define DIT_REG_TX_DESC_CTRL_DST		0x010C /* 3 bit */
#define DIT_REG_TX_HEAD_CTRL			0x0110 /* 3 bit */
#define DIT_REG_TX_MOD_HD_CTRL			0x0114 /* 3 bit */
#define DIT_REG_TX_PKT_CTRL			0x0118 /* 3 bit */
#define DIT_REG_TX_CHKSUM_CTRL			0x011C /* 3 bit */

#define DIT_REG_RX_DESC_CTRL_SRC		0x0120 /* 3 bit */
#define DIT_REG_RX_DESC_CTRL_DST		0x0124 /* 3 bit */
#define DIT_REG_RX_HEAD_CTRL			0x0128 /* 3 bit */
#define DIT_REG_RX_MOD_HD_CTRL			0x012C /* 3 bit */
#define DIT_REG_RX_PKT_CTRL			0x0130 /* 3 bit */
#define DIT_REG_RX_CHKSUM_CTRL			0x0134 /* 3 bit */

#define DIT_REG_DMA_CHKSUM_OFF			0x0138 /* 2 bit */
#define DIT_REG_INT_ENABLE			0x0140
#define DIT_REG_INT_MASK			0x0144
#define DIT_REG_INT_PENDING			0x0148
#define DIT_REG_STATUS				0x014C

/* start address for Tx desc */
#define DIT_REG_TX_RING_START_ADDR_0_SRC	0x0200	/* SRC_A */
#define DIT_REG_TX_RING_START_ADDR_1_SRC	0x0204
#define DIT_REG_TX_RING_START_ADDR_0_DST0	0x0218	/* DST00 */
#define DIT_REG_TX_RING_START_ADDR_1_DST0	0x021C
#define DIT_REG_TX_RING_START_ADDR_0_DST1	0x0220
#define DIT_REG_TX_RING_START_ADDR_1_DST1	0x0224
#define DIT_REG_TX_RING_START_ADDR_0_DST2	0x0228
#define DIT_REG_TX_RING_START_ADDR_1_DST2	0x022C

/* start address for Rx desc */
#define DIT_REG_RX_RING_START_ADDR_0_SRC	0x0248	/* SRC_A */
#define DIT_REG_RX_RING_START_ADDR_1_SRC	0x024C
#define DIT_REG_RX_RING_START_ADDR_0_DST0	0x0260	/* DST00 */
#define DIT_REG_RX_RING_START_ADDR_1_DST0	0x0264
#define DIT_REG_RX_RING_START_ADDR_0_DST1	0x0268
#define DIT_REG_RX_RING_START_ADDR_1_DST1	0x026C
#define DIT_REG_RX_RING_START_ADDR_0_DST2	0x0270
#define DIT_REG_RX_RING_START_ADDR_1_DST2	0x0274

/* address for Tx desc */
#define DIT_REG_NAT_TX_DESC_ADDR_0_SRC		0x4000	/* SRC_A, 32 bit */
#define DIT_REG_NAT_TX_DESC_ADDR_1_SRC		0x4004	/* 4 bit */
#define DIT_REG_NAT_TX_DESC_ADDR_EN_SRC		0x4008	/* 1 bit */
#define DIT_REG_NAT_TX_DESC_ADDR_0_DST0		0x4024	/* DST00 */
#define DIT_REG_NAT_TX_DESC_ADDR_1_DST0		0x4028
#define DIT_REG_NAT_TX_DESC_ADDR_0_DST1		0x402C
#define DIT_REG_NAT_TX_DESC_ADDR_1_DST1		0x4030
#define DIT_REG_NAT_TX_DESC_ADDR_0_DST2		0x4034
#define DIT_REG_NAT_TX_DESC_ADDR_1_DST2		0x4038

/* address for Rx desc */
#define DIT_REG_NAT_RX_DESC_ADDR_0_SRC		0x4054	/* SRC_A, 32 bit */
#define DIT_REG_NAT_RX_DESC_ADDR_1_SRC		0x4058	/* 4 bit */
#define DIT_REG_NAT_RX_DESC_ADDR_EN_SRC		0x405C	/* 1 bit */
#define DIT_REG_NAT_RX_DESC_ADDR_0_DST0		0x4078
#define DIT_REG_NAT_RX_DESC_ADDR_1_DST0		0x407C
#define DIT_REG_NAT_RX_DESC_ADDR_0_DST1		0x4080
#define DIT_REG_NAT_RX_DESC_ADDR_1_DST1		0x4084
#define DIT_REG_NAT_RX_DESC_ADDR_0_DST2		0x4088
#define DIT_REG_NAT_RX_DESC_ADDR_1_DST2		0x408C

#define DIT_REG_NAT_TTLDEC_EN			0x4150

/* total: DIT_REG_NAT_INTERFACE_NUM_MAX, interval: DIT_REG_NAT_INTERFACE_NUM_INTERVAL */
#define DIT_REG_NAT_INTERFACE_NUM		0x4200

#define DIT_REG_VERSION				0x9000

#define DIT_REG_NAT_INTERFACE_NUM_MAX		(8)
#define DIT_REG_NAT_INTERFACE_NUM_INTERVAL	(4)

enum dit_nat_ttldec_en_bits {
	TX_TTLDEC_EN_BIT,
	RX_TTLDEC_EN_BIT,
};

struct dit_src_desc {
	u64	src_addr:36,
		_reserved_0:12,
		/* the below 16 bits are "private info" on the document */
		pre_csum:1,		/* checksum successful from pktproc */
		udp_csum_zero:1,	/* reset udp checksum 0 after NAT */
		_reserved_2:14;
	u64	length:16,
		ch_id:8,		/* "interface" on the document */
		_reserved_1:24,
		control:8,
		status:8;
} __packed;

struct dit_dst_desc {
	u64	dst_addr:36,
		packet_info:12,
		/* the below 16 bits are "private info" on the document */
		pre_csum:1,
		udp_csum_zero:1,
		_reserved_2:14;
	u64	length:16,
		org_port:16,
		trans_port:16;
	union {
		/* meaning changes before/after interrupt */
		u64	control:8,
			ch_id:8;	/* "interface" on the document */
	};
	u64	status:8;
} __packed;

/* DIT_INT_PENDING */
enum dit_int_pending_bits {
	TX_DST0_INT_PENDING_BIT = 3,
	TX_DST1_INT_PENDING_BIT = 7,
	TX_DST2_INT_PENDING_BIT,
	RX_DST00_INT_PENDING_BIT = 19,
	RX_DST0_INT_PENDING_BIT = RX_DST00_INT_PENDING_BIT,
	RX_DST1_INT_PENDING_BIT = 23,
	RX_DST2_INT_PENDING_BIT,
	RSVD0_INT_PENDING_BIT = 30,
	ERR_INT_PENDING_BIT = RSVD0_INT_PENDING_BIT,	/* No ERR interrupt */
};

#endif /* __DIT_2_2_0_H__ */
