#!/usr/bin/python

import sys
from ctypes import *
import pcan

class QEIData(Structure):
  _fields_ = [
    ('sec', c_uint32),
    ('nsec', c_uint32),
  ]

filter_id = 123

can = pcan.CANIX()

errno = can.init()

if errno != 0:
	print "CAN bus error 0x%04x" % code

cnt = 0;

while (True):
	m = pcan.Msg(0, 0, 0, (0,)*8)
	dword = can.read(pointer(m))
	if dword != pcan.ERR_QRCVEMPTY:
		if (filter_id > 0) and (filter_id != (m.ID >> 15) & 0xFF):
			continue

		msg = cast(pointer(m.DATA), POINTER(QEIData)).contents

		print "%d - %d.%d: %d %d" % (cnt, int(m.ID >> 15) & 0xFF, int(m.ID >> 7) & 0xFF, msg.sec, msg.nsec / 1000)
		print ""
		
		cnt = cnt + 1
