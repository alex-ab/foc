/*
 * Copyright (C) 2000-2006 Erik Andersen <andersen@uclibc.org>
 *
 * Licensed under the LGPL v2.1, see the file COPYING.LIB in this tarball.
 */
#include <setjmp.h>
#include <jmpbuf-offsets.h>

/* Test if longjmp to JMPBUF would unwind the frame
   containing a local variable at ADDRESS.  */
#define _JMPBUF_UNWINDS(jmpbuf, address) \
  ((void *) (address) < (void *) _jmpbuf_sp(jmpbuf))

#ifdef __UCLIBC_HAS_THREADS_NATIVE__
#include <stdint.h>
#include <unwind.h>

/* Test if longjmp to JMPBUF would unwind the frame
   containing a local variable at ADDRESS.  */
#undef _JMPBUF_UNWINDS
#define _JMPBUF_UNWINDS(jmpbuf, address, demangle) \
  ((void *) (address) < (void *) demangle (jmpbuf[JB_SP]))

#define _JMPBUF_CFA_UNWINDS_ADJ(_jmpbuf, _context, _adj) \
  _JMPBUF_UNWINDS_ADJ (_jmpbuf, (void *) _Unwind_GetCFA (_context), _adj)

#define _JMPBUF_UNWINDS_ADJ(_jmpbuf, _address, _adj) \
  ((uintptr_t) (_address) - (_adj) < (uintptr_t) _jmpbuf_sp(_jmpbuf) - (_adj))
#endif
