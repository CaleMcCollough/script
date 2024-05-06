/* Script2™
@link    https://github.com/KabukiStarship/Script2.git
@file    /_ConfigHeader.inl
@author  Cale McCollough <https://cookingwithcale.org>
@license Copyright Kabuki Starship™ <kabukistarship.com>; This Source Code 
Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of
the MPL was not distributed with this file, You can obtain one at 
<https://mozilla.org/MPL/2.0/>. */

#include <_Seams.inl>

#define SCRIPT2 0

#define YES_0 0
#define NO_0 1

#define STRING_TYPE_A 1  //< UTF-8.
#define STRING_TYPE_B 2  //< UTF-16.
#define STRING_TYPE_C 3  //< UTF-32.
#define STRING_TYPE_D 4  //< MSB-variant encoding.

#define PLATFORM_BARE_METAL 1
#define PLATFORM_MBED_BARE_METAL 2
#define PLATFORM_MBED_OS 3
#define PLATFORM_ARDUINO 4
#define PLATFORM_WIN32 5
#define PLATFORM_WINDOWS 6
#define PLATFORM_ANDROID 7
#define PLATFORM_LINUX 8
#define PLATFORM_OSX 9
#define PLATFORM_IOS 10

#define CPU_X86 1
#define CPU_X64 2
#define CPU_ARM8 3
#define CPU_ARM16 4
#define CPU_ARM32 5
#define CPU_ARM64 6

#include <cstdint>
#if defined(_MSC_VER) && defined(_M_AMD64)
#define USING_VISUAL_CPP_X64 1
#include <intrin.h>
#include <intrin0.h>
#pragma intrinsic(_umul128)
#elif (__GNUC__ > 4 || (__GNUC__ == 4 && __GNUC_MINOR__ >= 6))
#define USING_GCC 1
#if defined(__x86_64__)
#define COMPILER_SUPPORTS_16_BYTE_INTEGERS 1
#endif
#endif

#define ASSEMBLE_EXE 0
#define ASSEMBLE_LIB_STATIC 1
#define ASSEMBLE_LIB_DYNAMIC 1

#define CPU_8_BYTE 0
#define CPU_4_BYTE 1
#define CPU_2_BYTE 2
#define CPU_1_BYTE 2

#define CPU_ENDIAN_LITTLE 0

/* OpenGL POD types.

typedef unsigned int GLenum;
typedef unsigned char GLboolean;
typedef unsigned int GLbitfield;
typedef signed char GLbyte;
typedef short GLshort;
typedef int GLint;
typedef int GLsizei;
typedef unsigned char GLubyte;
typedef unsigned short GLushort;
typedef unsigned int GLuint;
typedef float GLfloat;
typedef float GLclampf;
typedef double GLdouble;
typedef double GLclampd;
typedef void GLvoid;
*/

typedef char CHA;
typedef char16_t CHB;
typedef char32_t CHC;
typedef wchar_t CHN;

typedef int8_t ISA;
typedef uint8_t IUA;
typedef int16_t ISB;
typedef uint16_t IUB;
typedef bool BOL;
typedef int32_t ISC;
typedef uint32_t IUC;
typedef int32_t TMC;
typedef int64_t TMD;
typedef int64_t ISD;
typedef uint64_t IUD;
typedef uint64_t IUE;
typedef int64_t ISE;

typedef IUB FPB;
typedef float FPC;
typedef double FPD;
typedef double FPE;

typedef uintptr_t IUW;
typedef intptr_t ISW;
typedef IUW Type;

typedef int ISN;
typedef unsigned int IUN;

typedef short ISM;
typedef unsigned short IUM;

typedef ISC TMC;  //< A 32-bit seconds since epoch timestamp.
typedef ISD TMD;  //< A 64-bit seconds since epoch timestamp.

typedef void* PTR;
typedef const void* PTC;

typedef IUW DTW;  //< Word-sized Ascii Data Type.
typedef IUA DTA;  //< 8-bit Ascii Data Type.
typedef IUB DTB;  //< 16-bit Ascii Data Type.
typedef IUC DTC;  //< 32-bit Ascii Data Type.
typedef IUD DTD;  //< 64-bit Ascii Data Type.
//struct IUE { 
//   IUD a,
//       b
//};

typedef ISN Error; //< An error code.

/* 2-byte Type Bit Pattern.
| b15:b14 |  b13:b9 | b8:b7 | b6:b5 | b4:b0 |
|:-------:|:-------:|:-----:|:-----:|:-----:|
|   MB    |    MT   |  SW   |  VT   |  POD  | */

namespace _ {
// ASCII C0 Control codes.
enum {
  _NUL = 0,    //< ASCII C0 NUL 0
  _SOH,        //< ASCII C0 NUL 1
  _STX,        //< ASCII C0 STX 2
  _ETX,        //< ASCII C0 ETX 3
  _EOT,        //< ASCII C0 EOT 4
  _ENQ,        //< ASCII C0 ENQ 5
  _ACK,        //< ASCII C0 ACK 6
  _BEL,        //< ASCII C0 BEL 7
  _BS,         //< ASCII C0 BS 8
  _TAB,        //< ASCII C0 TAB 9
  _LF,         //< ASCII C0 LF 10
  _VT,         //< ASCII C0 VT 11
  _FF,         //< ASCII C0 FF 12
  _CR,         //< ASCII C0 CR 13
  _SO,         //< ASCII C0 SO 14
  _SI,         //< ASCII C0 IS 15
  _DLE,        //< ASCII C0 DLE 16
  _DC1,        //< ASCII C0 DC1 17
  _DC2,        //< ASCII C0 DC2 18
  _DC3,        //< ASCII C0 DC3 19
  _DC4,        //< ASCII C0 DC4 20
  _NAK,        //< ASCII C0 NAK 21
  _SYN,        //< ASCII C0 SYN 22
  _ETB,        //< ASCII C0 ETB 23
  _CAN,        //< ASCII C0 CAN 24
  _EM,         //< ASCII C0 EM 25
  _SUB,        //< ASCII C0 SUB 26
  _ESC,        //< ASCII C0 ESC 27
  _FS,         //< ASCII C0 FS 28
  _GS,         //< ASCII C0 GS 29
  _RS,         //< ASCII C0 RS 30
  _US,         //< ASCII C0 US 31
  _DEL = 127,  //< ASCII C0 DEL 127
};

/* A list of the bit masks for the ASCII data types bit pattern.
| b15:b14 |  b13:b9  | b8:b7 | b6:b5 | b4:b0 |
|:-------:|:--------:|:-----:|:-----:|:-----:|
|   MB    | Map type |  SW   |  VHT  |  POD  | */
enum {
  DTVHT      = 0x0060, //< Mask for b6:b5.
  DTASW      = 0x0080, //< Mask for b7.
  DTBSW      = 0x0180, //< Mask for b8:b7.
  DTBMT      = 0x3E00, //< Mask for b13:b9.
  DTBMB      = 0xC000, //< Mask for b15:b14.
  DTASWShift = 7,      //< Bits to shift to .
  DTBSWShift = 7,      //< Bits to shift b8:b7 into LSb.
  DTBMTShift = 13,     //< Bits to shift b8:b7 into b13:b9 into LSb.
  DTBMBShift = 14,     //< Bits to shift b8:b7 into b15:b14 into LSb.
};

/* List of the 32 ASCII POD Data Types.
@link ./Spec/Data/ReadMe.md */
enum {
  NIL = 0,   //< 00. Nil/void.
  _NIL = 0,  //< 00. Nil/void.
  _IUA,      //< 01. 1-byte unsigned integer.
  _ISA,      //< 02. 1-byte signed integer.
  _CHA,      //< 03. 1-byte character.
  _FPB,      //< 04. 2-byte floating-point number.
  _IUB,      //< 05. 2-byte unsigned integer.
  _ISB,      //< 06. 2-byte signed integer.
  _CHB,      //< 07. 2-byte character.
  _FPC,      //< 08. 4-byte floating-point number.
  _IUC,      //< 09. 4-byte unsigned integer.
  _ISC,      //< 10. 4-byte signed integer.
  _CHC,      //< 11. 4-byte character.
  _TME,      //< 12. 8-byte sub-second timestamp with TMC and an IUC tick.
  _IUD,      //< 13. 8-byte unsigned integer.
  _ISD,      //< 14. 8-byte signed integer.
  _FPD,      //< 15. 8-byte floating-point number.
  _IUE,      //< 16. 16-byte unsigned integer.
  _ISE,      //< 17. 16-byte signed integer.
  _FPE,      //< 18. 16-byte floating-point number.
  _BOL,      //< 19. Impl-defined 1-bit or 1, 2 or 4-byte boolean value.
  _DTA,      //< 20. Impl-defined word-aligned Data Type A.
  _DTB,      //< 21. Impl-defined word-aligned Data Type B.
  _DTC,      //< 22. Impl-defined word-aligned Data Type C.
  _DTD,      //< 23. Impl-defined word-aligned Data Type D.
  _DTE,      //< 24. Impl-defined word-aligned Data Type E.
  _DTF,      //< 25. Impl-defined word-aligned Data Type F.
  _DTG,      //< 26. Impl-defined word-aligned Data Type G.
  _DTH,      //< 27. Impl-defined word-aligned Data Type H.
  _DTI,      //< 28. Impl-defined word-aligned Data Type I.
  _DTJ,      //< 29. Impl-defined word-aligned Data Type J.
  _DTK,      //< 30. Impl-defined word-aligned Data Type K.
  _DTL,      //< 31. Impl-defined word-aligned Data Type L.
};

enum {
  _ISN = sizeof(ISN) == 1 ? _ISA
  : sizeof(ISN) == 2 ? _ISB
  : sizeof(ISN) == 4 ? _ISC
  : _ISD,
};

enum {
  _STA = 1,  //< 01. Nil-terminated string Type 1 (UTF-8).
  _STB,      //< 02. Nil-terminated string Type 2 (UTF-16).
  _STC,      //< 03. Nil-terminated string Type 3 (UTF-32).
  _WLD = 26, //< 26. A pointer.
  _VAL,      //< 27. A 2-word value.
  _TVT,      //< 28. A Type-Value tuple.
  _BGV,      //< 29. A 2-word value.
  _TBT,      //< 30. A Type-BigVal tuple.
  _TST,      //< 31. A Type-String tuple.
  _CH = 0,   //< Base type for CHA, CHB, and CHC.
  _FP = 0,   //< Base type for FPB, FPC, FPD, and FPE.
  _IU = 0,   //< Base type for IUA, IUB, IUC, IUD, and IUE.
  _IS = 0,   //< Base type for ISA, ISB, ISD, ISD, and ISE.
};

enum {
  _PTR = 1 << 14,          //< 64.  Pointer modifier.
  _CNS = 1 << 15,          //< 128. Constant.
  _CNS_PTR = _CNS | _PTR,  //< 128. Constant Pointer.
  _CNS_STA = _CNS | _CHA,  //< 133. Constant CHA*.
  _CNS_STB = _CNS | _CHB,  //< 134. Constant CHB*.
  _CNS_STC = _CNS | _CHC,  //< 135. Constant CHC*.
};

/*| b15:b14 | b13:b9 | b8:b7 | b6:b5 | b4:b0 |
  |:-------:|:------:|:-----:|:-----:|:-----:|
  |   MOD   |   MT   |  SW   |  VT   |  POD  | */
enum {
  _RSB = 97,  //< 97. A type-value tuple list with 2-byte signed size_bytes.
  _RSC = 98,  //< 98. A type-value tuple list with 4-byte signed size_bytes.
  _RSD = 99,  //< 99. A type-value tuple list with 8-byte signed size_bytes.
  Invalid = 32,         //< Number of Ascii Data Type base types.
  ATypePODBitCount = 5,  //< Bit count for POD types 0-31.
  ATypeVTBit0      = 5,  //< Start bit of the MOD Bits for 16-bit ASCII Types.
  ATypeSWBit0      = 7,  //< Start bit of the MOD Bits for 16-bit ASCII Types.
  ATypeMTBit0      = 9,  //< Start bit of the MOD Bits for 16-bit ASCII Types.
  ATypeMODBit0     = 14, //< Start bit of the MOD Bits for 16-bit ASCII Types.
  ATypePODCount    = 32, //< Starting index of invalid types.
  ATypePODMask     = ATypePODCount - 1, //< Starting index of invalid types.
};

enum {
  _SWA = 0,   //< 0. Class or POD type.
  _SWB = 1,   //< 1. size_width of size_bytes is 16-bits wide.
  _SWC = 2,   //< 2. size_width of size_bytes is 32-bits wide.
  _SWD = 3,   //< 3. size_width of size_bytes is 64-bits wide.
  _SWE = 4,   //< 4. Psudo size_width of size_bytes is 128-bits wide.
};

enum {
  _POD = 0,                       //< A POD type.
  _ARY = 1,                       //< Array of POD types.
  _SCK = 2,                       //< Vector of POD types.
  _MAT = 3,                       //< Matrix of POD types.
  _STR = 1,                       //< ASCII, UTF-8, UTF-16, or UTF-32 string.
  VTPODMask = 0  << ATypeVTBit0,  //< Mask for the Vector Type POD bits. #Junk
  VTARYMask = 1  << ATypeVTBit0,  //< Mask for the Vector Type ARY bits.
  VTVECMask = 2  << ATypeVTBit0,  //< Mask for the Vector Type VEC bits.
  VTMATMask = 3  << ATypeVTBit0,  //< Mask for the Vector Type MAT bits.
  SWAMask   = 0,                  //< Mask for the SWA bits. #Junk
  SWBMask   = 1  << ATypeSWBit0,  //< Mask for the SWB bits.
  SWCMask   = 2  << ATypeSWBit0,  //< Mask for the SWC bits.
  SWDMask   = 3  << ATypeSWBit0,  //< Mask for the SWD bits.
  PODMask   = 31,                 //< Mask for the POD bits.
  VTMask    = 3  << ATypeVTBit0,  //< Mask for the VT bits.
  SWMask    = SWDMask,            //< Mask for the SW bits.
  MTMask    = 31 << ATypeMTBit0,  //< Mask for the MT bits.
  MODMask   = 15 << ATypeMODBit0, //< Mask for the MB bits.
  ARAMask   = 0  << ATypeMODBit0 | VTARYMask,  //<  8-bit Array types. #Junk
  ARBMask   = 1  << ATypeMODBit0 | VTARYMask,  //< 16-bit Array types.
  ARCMask   = 2  << ATypeMODBit0 | VTARYMask,  //< 32-bit Array types.
  ARDMask   = 3  << ATypeMODBit0 | VTARYMask,  //< 64-bit Array types.
  _LST = 48,                      //< ASCII List type.
  _ARA_CHA  = ARAMask | _CHA,     //< 8-bit Loom of UTF-8 strings.
  _ARA_CHB  = ARAMask | _CHB,     //< 8-bit Loom of UTF-16 strings.
  _ARA_CHC  = ARAMask | _CHC,     //< 8-bit Loom of UTF-32 strings.
  _ARB_CHA  = ARBMask | _CHA,     //< 16-bit Loom of UTF-8 strings.
  _ARB_CHB  = ARBMask | _CHB,     //< 16-bit Loom of UTF-16 strings.
  _ARB_CHC  = ARBMask | _CHC,     //< 16-bit Loom of UTF-32 strings.
  _ARC_CHA  = ARCMask | _CHA,     //< 32-bit Loom of UTF-8 strings.
  _ARC_CHB  = ARCMask | _CHB,     //< 32-bit Loom of UTF-16 strings.
  _ARC_CHC  = ARCMask | _CHC,     //< 32-bit Loom of UTF-32 strings.
  _ARD_CHA  = ARDMask | _CHA,     //< 64-bit Loom of UTF-8 strings.
  _ARD_CHB  = ARDMask | _CHB,     //< 64-bit Loom of UTF-16 strings.
  _ARD_CHC  = ARDMask | _CHC,     //< 64-bit Loom of UTF-32 strings.
};
// Default Loom type.
#if USING_LOM
enum {
  _LOM = USING_LOM,
};
#else
enum {
  _LOM = _ARC_CHA,
};
#endif

enum {
  WordByteCount = sizeof(void*),
  ACPUBitCount  = (WordByteCount == 2) ? 1
                : (WordByteCount == 4) ? 2 : (WordByteCount == 8) ? 3 
                : 0,

  //< Mask to align to CPU word boundry.
  ACPUAlignMask   = WordByteCount - 1,
  NaNInt = sizeof(ISC) == 4 ? static_cast<ISC>(0xFFFFFFFF)
         : sizeof(ISC) == 2 ? static_cast<ISC>(0xFFFF)
         : 0,
  Exit    = -1, //< Flag to exit the Room.
  Success =  0, //< Universal successful return value.
  PSH     = -1, //< Flag to push an item on the top of a stack.
  PCK     = -2, //< Flag to insert an item on the top of a stack.
  ERR     = PSH - 1, //< Flag for unspecified error and the SCK op count.
  ANY     = -2, //< Flag to add an item anywhere in a collection.
};

// Enum list of Script2 errors stored in negative form.
enum {
  ErrorA = 0,                   //< Error 00: A error.
  ErrorAuthenticationError = 1, //< Error 01: Authentication error.
  ErrorArrayOverflow,           //< Error 02: Array overflow.
  ErrorBufferOverflow,          //< Error 03: Buffer overflow.
  ErrorBufferUnderflow,         //< Error 04: Buffer underflow.
  ErrorInputInvalid,            //< Error 05: Input invalid.
  ErrorInputNil,                //< Error 06: Input nil.
  ErrorInvalidArgs,             //< Error 07: Invalid args.
  ErrorInvalidArgument,         //< Error 08: Invalid argument.
  ErrorInvalidBuffer,           //< Error 09: Invalid buffer.
  ErrorInvalidDoor,             //< Error 10: Invalid door.
  ErrorInvalidErrorHandler,     //< Error 11: Invalid error handler.
  ErrorInvalidHeader,           //< Error 12: Invalid header.
  ErrorInvalidHash,             //< Error 13: Invalid hash.
  ErrorInvalidIndex,            //< Error 14: Invalid index.
  ErrorInvalidEnquery,          //< Error 15: Invalid inquiry.
  ErrorInvalidOp,               //< Error 16: Invalid op.
  ErrorInvalidOperand,          //< Error 17: Invalid operand.
  ErrorInvalidRoom,             //< Error 18: Invalid Room number.
  ErrorInvalidType,             //< Error 19: Invalid type.
  ErrorInvalidUTF8,             //< Error 20: Invalid UTF-8.
  ErrorInvalidUTF16,            //< Error 21: Invalid UTF-16.
  ErrorInvalidUTF32,            //< Error 22: Invalid UTF-32.
  ErrorObjLocked,               //< Error 23: OBJ locked.
  ErrorTooManyParameters,       //< Error 24: Parameter overflow.
  ErrorTooManyPops,             //< Error 25: Pop overflow
  ErrorStackOverflow,           //< Error 26: Stack overflow.
  ErrorTextOverflow,            //< Error 27: Text overflow.
  ErrorVarintOverflow,          //< Error 28: Varint overflow.
  ErrorImplementation = ErrorVarintOverflow, //< Error 29: Implementation error.
  ErrorCountMax       = ErrorImplementation, //< Total count of Script errors.
};
}  //< namespace _

typedef IUB DTB;