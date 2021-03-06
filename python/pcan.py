# WARNING: this file was autogenerated from pcan.h and libpcan.h
from ctypes import *

HW_ISA = 1
HW_DONGLE_SJA = 5
HW_DONGLE_SJA_EPP = 6
HW_DONGLE_PRO = 7
HW_DONGLE_PRO_EPP = 8
HW_ISA_SJA = 9
HW_PCI = 10
HW_USB = 11
HW_PCCARD = 12
HW_USB_PRO = 13
MAX_STANDARD_ID = 0x7ff
MAX_EXTENDED_ID = 0x1fffffff
ERR_OK = 0x0000
ERR_XMTFULL = 0x0001
ERR_OVERRUN = 0x0002
ERR_BUSLIGHT = 0x0004
ERR_BUSHEAVY = 0x0008
ERR_BUSOFF = 0x0010
ERR_QRCVEMPTY = 0x0020
ERR_QOVERRUN = 0x0040
ERR_QXMTFULL = 0x0080
ERR_REGTEST = 0x0100
ERR_NOVXD = 0x0200
ERR_RESOURCE = 0x2000
ERR_ILLPARAMTYPE = 0x4000
ERR_ILLPARAMVAL = 0x8000
ERRMASK_ILLHANDLE = 0x1C00
MSGTYPE_STATUS = 0x80
MSGTYPE_EXTENDED = 0x02
MSGTYPE_RTR = 0x01
MSGTYPE_STANDARD = 0x00
VERSIONSTRING_LEN = 64
SF_GET_SERIALNUMBER = 1
SF_SET_SERIALNUMBER = 2
SF_GET_HCDEVICENO = 3
SF_SET_HCDEVICENO = 4
MYSEQ_START = 0x80
BAUD_1M = 0x0014
BAUD_500K = 0x001C
BAUD_250K = 0x011C
BAUD_125K = 0x031C
BAUD_100K = 0x432F
BAUD_50K = 0x472F
BAUD_20K = 0x532F
BAUD_10K = 0x672F
BAUD_5K = 0x7F7F
INIT_TYPE_EX = 0x01
INIT_TYPE_ST = 0x00

class STATUS( Structure ):
  """for PCAN_GET_STATUS"""
  _fields_ = [
    ('wErrorFlag',c_ushort), # same as in TPDIAG, is cleared in driver after access
    ('nLastError',c_int), # is cleared in driver after access
  ]

class EXTRAPARAMS( Structure ):
  """None"""
  _fields_ = [
    ('nSubFunction',c_int), # a sub-function number SF_... to determine the union element used
    ('dwSerialNumber',c_uint), # to get and set the pcan-usb serial number
    ('ucHCDeviceNo',c_ubyte), # only for USB-devices to get or set a hard assigned number
  ]

class BTR0BTR1( Structure ):
  """None"""
  _fields_ = [
    ('dwBitRate',c_uint), # in + out, bitrate in bits per second
    ('wBTR0BTR1',c_ushort), # out only: the result
  ]

class Msg( Structure ):
  """for PCAN_WRITE_MSG"""
  _fields_ = [
    ('ID',c_uint), # 11/29 bit code
    ('MSGTYPE',c_ubyte), # bits of MSGTYPE_*
    ('LEN',c_ubyte), # count of data bytes (0..8)
    ('DATA',c_ubyte * 8), # data bytes, up to 8
  ]

class Init( Structure ):
  """for PCAN_INIT"""
  _fields_ = [
    ('wBTR0BTR1',c_ushort), # merged BTR0 and BTR1 register of the SJA1000
    ('ucCANMsgType',c_ubyte), # 11 or 29 bits - put MSGTYPE_... in here
    ('ucListenOnly',c_ubyte), # listen only mode when != 0
  ]

class DIAG( Structure ):
  """for PCAN_DIAG, in opposition to PCAN_GET_STATUS nothing is cleared"""
  _fields_ = [
    ('wType',c_ushort), # the type of interface hardware - see HW_....
    ('dwBase',c_uint), # the base address or port of this device
    ('wIrqLevel',c_ushort), # the irq level of this device
    ('dwReadCounter',c_uint), # counts all reads to this device from start
    ('dwWriteCounter',c_uint), # counts all writes
    ('dwIRQcounter',c_uint), # counts all interrupts
    ('dwErrorCounter',c_uint), # counts all errors
    ('wErrorFlag',c_ushort), # gathers all errors
    ('nLastError',c_int), # the last local error for this device
    ('nOpenPaths',c_int), # number of open paths for this device
    ('szVersionString',c_char * VERSIONSTRING_LEN), # driver version string
  ]

class RdMsg( Structure ):
  """for PCAN_READ_MSG"""
  _fields_ = [
    ('Msg',Msg), # the above message
    ('dwTime',c_uint), # a timestamp in msec, read only
    ('wUsec',c_ushort), # remainder in micro-seconds
  ]

class EXTENDEDSTATUS( Structure ):
  """for PCAN_GET_ESTATUS"""
  _fields_ = [
    ('wErrorFlag',c_ushort), # same as in TPDIAG, is cleared in driver after access
    ('nLastError',c_int), # is cleared in driver after access
    ('nPendingReads',c_int), # count of unread telegrams
    ('nPendingWrites',c_int), # count of unsent telegrams
  ]

class MSGFILTER( Structure ):
  """None"""
  _fields_ = [
    ('FromID',c_uint), # First CAN ID to accept
    ('ToID',c_uint), # Last CAN ID to accept
    ('MSGTYPE',c_ubyte), # bits of MSGTYPE_*
  ]
class PCAN( Union ):
  """Union of all PCAN structures from pcan.h"""
  _fields_ = [
    ('asSTATUS',STATUS),
    ('asEXTRAPARAMS',EXTRAPARAMS),
    ('asBTR0BTR1',BTR0BTR1),
    ('asMsg',Msg),
    ('asInit',Init),
    ('asDIAG',DIAG),
    ('asRdMsg',RdMsg),
    ('asEXTENDEDSTATUS',EXTENDEDSTATUS),
    ('asMSGFILTER',MSGFILTER),
    ('raw',c_char * 128)
  ]

lib = cdll.LoadLibrary('libpcan.so')

class CAN(object):
  """Namespace for CAN functions of libpcan.h"""
  open = lib.CAN_Open
  init = lib.CAN_Init
  close = lib.CAN_Close
  status = lib.CAN_Status
  write = lib.CAN_Write
  read = lib.CAN_Read
  resetfilter = lib.CAN_ResetFilter
  msgfilter = lib.CAN_MsgFilter
  versioninfo = lib.CAN_VersionInfo

class LICAN(object):
  """Namespace for LINUX_CAN functions of libpcan.h"""
  write_timeout = lib.LINUX_CAN_Write_Timeout
  read = lib.LINUX_CAN_Read
  read_timeout = lib.LINUX_CAN_Read_Timeout
  filehandle = lib.LINUX_CAN_FileHandle
  extended_status = lib.LINUX_CAN_Extended_Status
  open = lib.LINUX_CAN_Open
  statistics = lib.LINUX_CAN_Statistics
  btr0btr1 = lib.LINUX_CAN_BTR0BTR1

from pcan_linux import *
