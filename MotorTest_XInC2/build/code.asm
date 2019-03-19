	// .file	"D:/WizChess/MotorTest_XInC2/build/motortest.opt"
//	.section	//.text,"xr"
//align
@ = (@ + 1-1)  & -1
sxc__Z10Initializev:                    // @_Z10Initializev
// BB#0:
	inp	r0, 0x72
	and	r0, r0, 0xfbff
	outp	r0, 0x72
BB0_1:                                  // =>This Inner Loop Header: Depth=1
	inp	r0, 0x72
	//cmp	r0, 0x0
	bc	LT0, BB0_1
// BB#2:
	mov	r0, 0x1
	outp	r0, 0x75
	mov	r0, 0x803
	outp	r0, 0x74
	inp	r0, 0x72
	and	r0, r0, 0xfbff
	outp	r0, 0x72
BB0_3:                                  // =>This Inner Loop Header: Depth=1
	inp	r0, 0x72
	//cmp	r0, 0x0
	bc	LT0, BB0_3
// BB#4:
	inp	r0, 0x72
	ior	r0, r0, 0xc00
	outp	r0, 0x72
BB0_5:                                  // =>This Inner Loop Header: Depth=1
	inp	r0, 0x72
	//cmp	r0, 0x0
	bc	NC, BB0_5
// BB#6:                                // %_Z14sys_clock_init12crystal_freq8sys_freq.exit
	mov	r0, 0x8083
	outp	r0, 0x73
	mov	r0, 0x16
	outp	r0, 0x70
	mov	r0, 0x73
	outp	r0, 0x71
	jsr	r6, r6

//align
@ = (@ + 1-1)  & -1
sxc__Z9long_waitv:                      // @_Z9long_waitv
// BB#0:
	mov	r0, 0x0
	mov	r2, 0xd8f0
BB1_1:                                  // =>This Loop Header: Depth=1
                                        //     Child Loop BB1_2 Depth 2
	inp	r1, 0x3
	sub	r3, r2, r1
BB1_2:                                  //   Parent Loop BB1_1 Depth=1
                                        // =>  This Inner Loop Header: Depth=2
	inp	r1, 0x3
	add	r1, r3, r1
	//cmp	r1, 0x0
	bc	LT0, BB1_2
// BB#3:                                // %_Z14sys_clock_waitj.exit
                                        //   in Loop: Header=BB1_1 Depth=1
	add	r0, r0, 0x1
	sub	r1, r0, 0x1388
	bc	NE, BB1_1
// BB#4:
	jsr	r6, r6

//align
@ = (@ + 1-1)  & -1
sxc__Z21button_reading_threadPv:        // @_Z21button_reading_threadPv
// BB#0:
	mov	r0, 0x0
	mov	r2, 0x1
	bra	BB2_1
BB2_2:                                  //   in Loop: Header=BB2_1 Depth=1
	outp	r2, 0x20
BB2_1:                                  // %.backedge
                                        // =>This Inner Loop Header: Depth=1
	inp	r1, 0x26
	bic	r1, r1, 0x6
	//cmp	r1, 0x0
	bc	VS, BB2_2
// BB#3:                                //   in Loop: Header=BB2_1 Depth=1
	outp	r0, 0x20
	bra	BB2_1

//sxc_main
//align
@ = (@ + 1-1)  & -1
sxc_main:                               // @main
// BB#0:
	add	sp, sp, 0x2
	st	r6, sp, 0xfffe          // 1-byte Folded Spill
	mov	r0, 0x200
	outp	r0, 0x25
	mov	r1, 0x100
	outp	r1, 0x23
	outp	r0, 0x23
	outp	r1, 0x21
	mov	r2, 0x0
	outp	r2, 0x27
	mov	r0, 0x8000
	outp	r0, 0x7
	mov	r1, 0xa
	outp	r1, 0x3
	outp	r2, 0x0
	mov	r1, sxc__Z21button_reading_threadPv
	outp	r1, 0x1
	outp	r0, 0x6
	outp	r0, 0x7
	ld	r1, thrds_vector
	and	r1, r1, 0xfffd
	st	r1, thrds_vector
	outp	r1, 0x4
	outp	r0, 0x6
	outp	r2, 0x22
	mov	r2, 0x1
	bra	BB3_1
BB3_4:                                  //   in Loop: Header=BB3_1 Depth=1
	mov	r0, 0x0
	outp	r0, 0x24
	outp	r0, 0x22
	inp	r1, 0x22
	//APP
		jsr	r6, XPD_EchoUnsignedDec
	//NO_APP
	mov	r1, 0xa
	//APP
		jsr	r6, XPD_WriteByte
	//NO_APP
	add	r2, r2, 0x1
BB3_1:                                  // %.backedge
                                        // =>This Inner Loop Header: Depth=1
	st	r2, sp, 0xffff          // 1-byte Folded Spill
	mov	r1, 0xa
	//APP
		jsr	r6, XPD_WriteByte
	//NO_APP
	mov	r1, sxc_.str
	//APP
		jsr	r6, XPD_EchoString
	//NO_APP
	add	r1, r2, 0xffff
	//APP
		jsr	r6, XPD_EchoUnsignedDec
	//NO_APP
	mov	r1, 0xa
	//APP
		jsr	r6, XPD_WriteByte
	//NO_APP
	jsr	r6, sxc__Z9long_waitv
	jsr	r6, sxc__Z9long_waitv
	ld	r2, sp, 0xffff          // 1-byte Folded Reload
	and	r0, r2, 0x1
	//cmp	r0, 0x0
	bc	ZS, BB3_4
// BB#2:                                //   in Loop: Header=BB3_1 Depth=1
	mov	r0, 0x2
	outp	r0, 0x24
	mov	r0, 0x1
	outp	r0, 0x22
	inp	r1, 0x22
	//APP
		jsr	r6, XPD_EchoUnsignedDec
	//NO_APP
	mov	r1, 0xa
	//APP
		jsr	r6, XPD_WriteByte
	//NO_APP
	add	r2, r2, 0x1
	bra	BB3_1

//align
@ = (@ + 1-1)  & -1
sxc___xinc_udiv:                        // @__xinc_udiv
// BB#0:
	add	sp, sp, 0x1
	st	r6, sp, 0xffff          // 1-byte Folded Spill
	add	r1, r2, 0x0
	add	r2, r3, 0x0
	//APP
	jsr	r6, UnsignedDivide
	//NO_APP
	add	r0, r1, 0x0
	ld	r6, sp, 0xffff          // 1-byte Folded Reload
	sub	sp, sp, 0x1
	jsr	r6, r6

//align
@ = (@ + 1-1)  & -1
sxc___xinc_umod:                        // @__xinc_umod
// BB#0:
	add	sp, sp, 0x1
	st	r6, sp, 0xffff          // 1-byte Folded Spill
	add	r1, r2, 0x0
	add	r2, r3, 0x0
	//APP
	jsr	r6, UnsignedDivide
	//NO_APP
	add	r0, r2, 0x0
	ld	r6, sp, 0xffff          // 1-byte Folded Reload
	sub	sp, sp, 0x1
	jsr	r6, r6

//align
@ = (@ + 1-1)  & -1
sxc_memset:                             // @memset
// BB#0:
	sub	r1, r4, 0x0
	bc	EQ, BB6_3
// BB#1:
	add	r0, r2, 0x0
BB6_2:                                  // %.lr.ph
                                        // =>This Inner Loop Header: Depth=1
	st	r3, r0, 0x0
	add	r0, r0, 0x1
	add	r4, r4, 0xffff
	//cmp	r4, 0x0
	bc	ZC, BB6_2
BB6_3:                                  // %._crit_edge
	add	r0, r2, 0x0
	jsr	r6, r6

//align
@ = (@ + 1-1)  & -1
sxc_memcpy:                             // @memcpy
// BB#0:
	sub	r1, r2, r3
	bc	EQ, BB7_4
// BB#1:
	sub	r1, r4, 0x0
	bc	EQ, BB7_4
// BB#2:
	add	r0, r2, 0x0
BB7_3:                                  // %.lr.ph.i
                                        // =>This Inner Loop Header: Depth=1
	ld	r1, r3, 0x0
	st	r1, r0, 0x0
	add	r3, r3, 0x1
	add	r0, r0, 0x1
	add	r4, r4, 0xffff
	//cmp	r4, 0x0
	bc	ZC, BB7_3
BB7_4:                                  // %memcpy_base.exit
	add	r0, r2, 0x0
	jsr	r6, r6

//align
@ = (@ + 1-1)  & -1
sxc_memmove:                            // @memmove
// BB#0:
	mov	r0, 0x1
	mov	r5, 0x1
	sub	r1, r4, 0x0
	bc	EQ, @ + 1 + 0x1
	mov	r5, 0x0 //Select--False
	sub	r1, r2, r3
	bc	EQ, @ + 1 + 0x1
	mov	r0, 0x0 //Select--False
	ior	r0, r0, r5
	sub	r1, r3, r2
	bc	UGE, BB8_1
// BB#4:
	and	r0, r0, 0x1
	//cmp	r0, 0x0
	bc	ZC, BB8_7
// BB#5:                                // %.lr.ph23.i.preheader
	mov	r0, 0x1
	sub	r0, r0, r4
BB8_6:                                  // %.lr.ph23.i
                                        // =>This Inner Loop Header: Depth=1
	sub	r1, r2, r0
	sub	r4, r3, r0
	ld	r4, r4, 0x0
	st	r4, r1, 0x0
	add	r0, r0, 0x1
	sub	r1, r0, 0x1
	bc	NE, BB8_6
	bra	BB8_7
BB8_1:
	and	r0, r0, 0x1
	//cmp	r0, 0x0
	bc	ZC, BB8_7
// BB#2:
	add	r0, r2, 0x0
BB8_3:                                  // %.lr.ph.i
                                        // =>This Inner Loop Header: Depth=1
	ld	r1, r3, 0x0
	st	r1, r0, 0x0
	add	r3, r3, 0x1
	add	r0, r0, 0x1
	add	r4, r4, 0xffff
	//cmp	r4, 0x0
	bc	ZC, BB8_3
BB8_7:                                  // %memcpy_base.exit
	add	r0, r2, 0x0
	jsr	r6, r6

