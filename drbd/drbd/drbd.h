/*
  drbd.h
  Kernel module for 2.2.x Kernels
  
  This file is part of drbd by Philipp Reisner.

  drbd is free software; you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation; either version 2, or (at your option)
  any later version.
  
  drbd is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with drbd; see the file COPYING.  If not, write to
  the Free Software Foundation, 675 Mass Ave, Cambridge, MA 02139, USA.

*/
#ifndef DRBD_H
#define DRBD_H

#include <asm/types.h>

#ifdef __KERNEL__
#include <linux/types.h>
#include <linux/ioctl.h>
#else
#include <sys/types.h>
#include <sys/ioctl.h>
#include <sys/wait.h>
#include <limits.h>
#endif

#ifdef __KERNEL__
#define IN const
#define OUT
#define INOUT
#else
#define IN
#define OUT const
#define INOUT
#endif                                 


#define MAX_SOCK_ADDR	128		/* 108 for Unix domain - 
					   16 for IP, 16 for IPX,
					   24 for IPv6,
					   about 80 for AX.25 
					   must be at least one bigger than
					   the AF_UNIX size (see net/unix/af_unix.c
					   :unix_mkname()).  
					 */


struct ioctl_drbd_config
{
  IN int      lower_device;
  IN char     other_addr[MAX_SOCK_ADDR];
  IN int      other_addr_len;
  IN char     my_addr[MAX_SOCK_ADDR];
  IN int      my_addr_len;
  IN int      timeout;
  IN int      sync_rate; /* KB/sec */
  IN int      skip_sync; 
  IN int      tl_size; /* size of the transfer log */
};

/* This is the layout for a Packet on the wire! 
 * The byteorder is the network byte order!
 */
typedef struct
{
  __u32 magic;
  __u16 command;
  __u16 length;    /* obsolete ?? hmmm, maybe ... */
  __u64 block_nr;  /* 64 Bits Block number */
} Drbd_Packet;

typedef struct
{
  __u64 my_size;
  __u32 my_state;
  __u32 my_blksize;
} Drbd_ParameterBlock;

typedef enum { Data,Ack,SyncNow,ReportParams,BlkSizeChanged } Drbd_Packet_Cmd;
typedef enum { Primary, Secondary } Drbd_State;
typedef enum { 
  Unconfigured, 
  Unconnected, 
  WFConnection,
  WFReportParams,
  Syncing, 
  Connected 
} Drbd_CState; 

#define DRBD_MAGIC 0x83740267

#define DRBD_IOCTL_GET_VERSION   _IOR( 'D', 0x00, int )
#define DRBD_IOCTL_SET_CONFIG    _IOW( 'D', 0x01, struct ioctl_drbd_config )
#define DRBD_IOCTL_SET_STATE     _IOW( 'D', 0x02, Drbd_State )

#endif




