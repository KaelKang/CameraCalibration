/**
@File      GxIAPI.h
@Brief     the interface for the GxIAPI dll module. 
@author    Software Department
@Date      2015-7-23
@Version   1.1.1507.9231
*/

#ifndef GX_GALAXY_H
#define GX_GALAXY_H




#if defined(_WIN32)
	#ifndef _STDINT_H 
		#ifdef _MSC_VER // Microsoft compiler
			#if _MSC_VER < 1600
				typedef __int8            int8_t;
				typedef __int16           int16_t;
				typedef __int32           int32_t;
				typedef __int64           int64_t;
				typedef unsigned __int8   uint8_t;
				typedef unsigned __int16  uint16_t;
				typedef unsigned __int32  uint32_t;
				typedef unsigned __int64  uint64_t;
			#else
				// In Visual Studio 2010 is stdint.h already included
				#include <stdint.h>
			#endif
		#else
			// Not a Microsoft compiler
			#include <stdint.h>
		#endif
	#endif 
#else
	// Linux
	#include <stdint.h>
#endif




#include <stddef.h>

#ifdef WIN32
	#ifndef _WIN32
		#define _WIN32
	#endif
#endif

#ifdef _WIN32
	#include <Windows.h>
	#define GX_DLLIMPORT   __declspec(dllimport)
	#define GX_DLLEXPORT   __declspec(dllexport)

	#define GX_STDC __stdcall
	#define GX_CDEC __cdecl

	#if defined(__cplusplus)
		#define GX_EXTC extern "C"
	#else
		#define GX_EXTC
	#endif
#else
	// remove the None #define conflicting with GenApi
	#undef None
	#if __GNUC__>=4
		#define GX_DLLIMPORT   __attribute__((visibility("default")))
		#define GX_DLLEXPORT   __attribute__((visibility("default")))

		#if defined(__i386__)
			#define GX_STDC __attribute__((stdcall))
			#define GX_CDEC __attribute__((cdecl))
		#else
			#define GX_STDC 
			#define GX_CDEC 
		#endif

		#if defined(__cplusplus)
			#define GX_EXTC extern "C"
		#else
			#define GX_EXTC
		#endif
	#else
		#error Unknown compiler
	#endif
#endif

#ifdef GX_GALAXY_DLL
	#define GX_DLLENTRY GX_EXTC GX_DLLEXPORT
#else
	#define GX_DLLENTRY GX_EXTC GX_DLLIMPORT
#endif



typedef enum GX_STATUS_LIST
{
	GX_STATUS_SUCCESS                =  0,           ///< 
	GX_STATUS_ERROR                  = -1,           ///< 
	GX_STATUS_NOT_FOUND_TL           = -2,           ///< 
	GX_STATUS_NOT_FOUND_DEVICE       = -3,           ///< 
	GX_STATUS_OFFLINE                = -4,           ///< 
	GX_STATUS_INVALID_PARAMETER      = -5,           ///< 
	GX_STATUS_INVALID_HANDLE         = -6,           ///< 
	GX_STATUS_INVALID_CALL           = -7,           ///< 
	GX_STATUS_INVALID_ACCESS         = -8,           ///< 
	GX_STATUS_NEED_MORE_BUFFER       = -9,           ///< 
	GX_STATUS_ERROR_TYPE             = -10,          ///< 
	GX_STATUS_OUT_OF_RANGE           = -11,          ///< 
	GX_STATUS_NOT_IMPLEMENTED        = -12,          ///< 
	GX_STATUS_NOT_INIT_API           = -13,          ///< 
	GX_STATUS_TIMEOUT                = -14,          ///< 
}GX_STATUS_LIST;
typedef int32_t GX_STATUS;


typedef enum GX_FRAME_STATUS_LIST
{
	GX_FRAME_STATUS_SUCCESS          = 0,     ///< 
	GX_FRAME_STATUS_INCOMPLETE       = -1,    ///< 
}GX_FRAME_STATUS_LIST;
typedef  int32_t  GX_FRAME_STATUS;


typedef enum GX_DEVICE_CLASS_LIST
{
	GX_DEVICE_CLASS_UNKNOWN = 0,     ///< 
	GX_DEVICE_CLASS_USB2    = 1,     ///< 
	GX_DEVICE_CLASS_GEV     = 2,     ///< 
	GX_DEVICE_CLASS_U3V     = 3,     ///< 
}GX_DEVICE_CLASS_LIST;
typedef  int32_t GX_DEVICE_CLASS;


typedef enum GX_FEATURE_TYPE
{
	GX_FEATURE_INT				   =0x10000000,  ///< 
	GX_FEATURE_FLOAT               =0X20000000,  ///< 
	GX_FEATURE_ENUM				   =0x30000000,  ///< 
	GX_FEATURE_BOOL				   =0x40000000,  ///< 
	GX_FEATURE_STRING			   =0x50000000,  ///< 
	GX_FEATURE_BUFFER			   =0x60000000,  ///< 
	GX_FEATURE_COMMAND			   =0x70000000,  ///< 
}GX_FEATURE_TYPE;


typedef enum GX_FEATURE_LEVEL
{
	GX_FEATURE_LEVEL_REMOTE_DEV	    =0x00000000,  ///< RemoteDevice Layer
	GX_FEATURE_LEVEL_TL				=0x01000000,  ///< TL Layer
	GX_FEATURE_LEVEL_IF             =0x02000000,  ///< Interface Layer	
	GX_FEATURE_LEVEL_DEV		    =0x03000000,  ///< Device Layer
	GX_FEATURE_LEVEL_DS			    =0x04000000,  ///< DataStream Layer
}GX_FEATURE_LEVEL;


typedef enum GX_ACCESS_MODE
{
	GX_ACCESS_READONLY      =2,        ///< 
	GX_ACCESS_CONTROL       =3,        ///< 
	GX_ACCESS_EXCLUSIVE     =4,        ///< 
}GX_ACCESS_MODE;
typedef int32_t GX_ACCESS_MODE_CMD;


typedef enum GX_ACCESS_STATUS
{
	GX_ACCESS_STATUS_UNKNOWN    = 0,   ///< 
	GX_ACCESS_STATUS_READWRITE  = 1,   ///< 
	GX_ACCESS_STATUS_READONLY   = 2,   ///< 
	GX_ACCESS_STATUS_NOACCESS   = 3,   ///< 
}GX_ACCESS_STATUS;
typedef int32_t GX_ACCESS_STATUS_CMD;


typedef enum GX_OPEN_MODE
{
	GX_OPEN_SN              =0,        ///< 
	GX_OPEN_IP              =1,        ///< 
	GX_OPEN_MAC             =2,        ///< 
	GX_OPEN_INDEX           =3,        ///< 
	GX_OPEN_USERID          =4,        ///< 
}GX_OPEN_MODE;
typedef int32_t GX_OPEN_MODE_CMD;

typedef enum GX_FEATURE_ID
{
	//////////////////////////////////////////////////////////////////////////
	/// Remote Device Feature
	//////////////////////////////////////////////////////////////////////////

	//---------------DeviceInfomation Section--------------------------
	GX_STRING_DEVICE_VENDOR_NAME               = 0   | GX_FEATURE_STRING | GX_FEATURE_LEVEL_REMOTE_DEV,     ///< 
	GX_STRING_DEVICE_MODEL_NAME                = 1   | GX_FEATURE_STRING | GX_FEATURE_LEVEL_REMOTE_DEV,     ///< 
	GX_STRING_DEVICE_FIRMWARE_VERSION          = 2   | GX_FEATURE_STRING | GX_FEATURE_LEVEL_REMOTE_DEV,     ///< 
	GX_STRING_DEVICE_VERSION                   = 3   | GX_FEATURE_STRING | GX_FEATURE_LEVEL_REMOTE_DEV,     ///< 
	GX_STRING_DEVICE_SERIAL_NUMBER             = 4   | GX_FEATURE_STRING | GX_FEATURE_LEVEL_REMOTE_DEV,     ///< 
	GX_STRING_FACTORY_SETTING_VERSION          = 6   | GX_FEATURE_STRING | GX_FEATURE_LEVEL_REMOTE_DEV,     ///< 
	GX_STRING_DEVICE_USERID                    = 7   | GX_FEATURE_STRING | GX_FEATURE_LEVEL_REMOTE_DEV,     ///< 
	GX_INT_DEVICE_LINK_SELECTOR                = 8   | GX_FEATURE_INT    | GX_FEATURE_LEVEL_REMOTE_DEV,     ///< 
	GX_ENUM_DEVICE_LINK_THROUGHPUT_LIMIT_MODE  = 9   | GX_FEATURE_ENUM   | GX_FEATURE_LEVEL_REMOTE_DEV,     ///< Refer to GX_DEVICE_LINK_THROUGHPUT_LIMIT_MODE_ENTRY
	GX_INT_DEVICE_LINK_THROUGHPUT_LIMIT        = 10  | GX_FEATURE_INT    | GX_FEATURE_LEVEL_REMOTE_DEV,     ///< 
	GX_INT_DEVICE_LINK_CURRENT_THROUGHPUT      = 11  | GX_FEATURE_INT    | GX_FEATURE_LEVEL_REMOTE_DEV,     ///< 


	//---------------ImageFormat Section--------------------------------
	GX_INT_SENSOR_WIDTH               = 1000 | GX_FEATURE_INT | GX_FEATURE_LEVEL_REMOTE_DEV,     ///< 
	GX_INT_SENSOR_HEIGHT              = 1001 | GX_FEATURE_INT | GX_FEATURE_LEVEL_REMOTE_DEV,     ///< 
	GX_INT_WIDTH_MAX                  = 1002 | GX_FEATURE_INT | GX_FEATURE_LEVEL_REMOTE_DEV,     ///< 
	GX_INT_HEIGHT_MAX                 = 1003 | GX_FEATURE_INT | GX_FEATURE_LEVEL_REMOTE_DEV,     ///< 
	GX_INT_OFFSET_X                   = 1004 | GX_FEATURE_INT | GX_FEATURE_LEVEL_REMOTE_DEV,     ///< 
	GX_INT_OFFSET_Y                   = 1005 | GX_FEATURE_INT | GX_FEATURE_LEVEL_REMOTE_DEV,     ///< 
	GX_INT_WIDTH                      = 1006 | GX_FEATURE_INT | GX_FEATURE_LEVEL_REMOTE_DEV,     ///< 
	GX_INT_HEIGHT                     = 1007 | GX_FEATURE_INT | GX_FEATURE_LEVEL_REMOTE_DEV,     ///< 
	GX_INT_BINNING_HORIZONTAL         = 1008 | GX_FEATURE_INT | GX_FEATURE_LEVEL_REMOTE_DEV,     ///< 
	GX_INT_BINNING_VERTICAL           = 1009 | GX_FEATURE_INT | GX_FEATURE_LEVEL_REMOTE_DEV,     ///< 
	GX_INT_DECIMATION_HORIZONTAL      = 1010 | GX_FEATURE_INT | GX_FEATURE_LEVEL_REMOTE_DEV,     ///< 
	GX_INT_DECIMATION_VERTICAL        = 1011 | GX_FEATURE_INT | GX_FEATURE_LEVEL_REMOTE_DEV,     ///< 
	GX_ENUM_PIXEL_SIZE                = 1012 | GX_FEATURE_ENUM | GX_FEATURE_LEVEL_REMOTE_DEV,    ///< Refer to GX_PIXEL_SIZE_ENTRY
	GX_ENUM_PIXEL_COLOR_FILTER        = 1013 | GX_FEATURE_ENUM | GX_FEATURE_LEVEL_REMOTE_DEV,    ///< Refer to GX_PIXEL_COLOR_FILTER_ENTRY
	GX_ENUM_PIXEL_FORMAT              = 1014 | GX_FEATURE_ENUM | GX_FEATURE_LEVEL_REMOTE_DEV,    ///< Refer to GX_PIXEL_FORMAT_ENTRY
	GX_BOOL_REVERSE_X                 = 1015 | GX_FEATURE_BOOL | GX_FEATURE_LEVEL_REMOTE_DEV,    ///< 
	GX_BOOL_REVERSE_Y                 = 1016 | GX_FEATURE_BOOL | GX_FEATURE_LEVEL_REMOTE_DEV,    ///< 
	GX_ENUM_TEST_PATTERN              = 1017 | GX_FEATURE_ENUM | GX_FEATURE_LEVEL_REMOTE_DEV,    ///< Refer to GX_TEST_PATTERN_ENTRY
	GX_ENUM_TEST_PATTERN_GENERATOR_SELECTOR = 1018 | GX_FEATURE_ENUM | GX_FEATURE_LEVEL_REMOTE_DEV,   ///< Refer to GX_TEST_PATTERN_GENERATOR_SELECTOR_ENTRY


	//---------------TransportLayer Section-------------------------------
	GX_INT_PAYLOAD_SIZE                              = 2000 | GX_FEATURE_INT | GX_FEATURE_LEVEL_REMOTE_DEV,  ///< 
	GX_BOOL_GEV_CURRENT_IPCONFIGURATION_LLA          = 2001 | GX_FEATURE_BOOL | GX_FEATURE_LEVEL_REMOTE_DEV, ///< 
	GX_BOOL_GEV_CURRENT_IPCONFIGURATION_DHCP         = 2002 | GX_FEATURE_BOOL | GX_FEATURE_LEVEL_REMOTE_DEV, ///< 
	GX_BOOL_GEV_CURRENT_IPCONFIGURATION_PERSISTENTIP = 2003 | GX_FEATURE_BOOL | GX_FEATURE_LEVEL_REMOTE_DEV, ///< 
	GX_INT_ESTIMATED_BANDWIDTH                       = 2004 | GX_FEATURE_INT | GX_FEATURE_LEVEL_REMOTE_DEV,  ///< Unit Bps(Bytes per second)
	GX_INT_GEV_HEARTBEAT_TIMEOUT                     = 2005 | GX_FEATURE_INT | GX_FEATURE_LEVEL_REMOTE_DEV,  ///< Unit ms
	GX_INT_GEV_PACKETSIZE                            = 2006 | GX_FEATURE_INT | GX_FEATURE_LEVEL_REMOTE_DEV,  ///< 
	GX_INT_GEV_PACKETDELAY                           = 2007 | GX_FEATURE_INT | GX_FEATURE_LEVEL_REMOTE_DEV,  ///< 
	GX_INT_GEV_LINK_SPEED                            = 2008 | GX_FEATURE_INT | GX_FEATURE_LEVEL_REMOTE_DEV,  ///< 

	//---------------AcquisitionTrigger Section---------------------------
	GX_ENUM_ACQUISITION_MODE          = 3000 | GX_FEATURE_ENUM | GX_FEATURE_LEVEL_REMOTE_DEV,    ///< Refer to GX_ACQUISITION_MODE_ENTRY
	GX_COMMAND_ACQUISITION_START      = 3001 | GX_FEATURE_COMMAND | GX_FEATURE_LEVEL_REMOTE_DEV, ///< 
	GX_COMMAND_ACQUISITION_STOP       = 3002 | GX_FEATURE_COMMAND | GX_FEATURE_LEVEL_REMOTE_DEV, ///< 
	GX_INT_ACQUISITION_SPEED_LEVEL    = 3003 | GX_FEATURE_INT | GX_FEATURE_LEVEL_REMOTE_DEV,     ///< 
	GX_INT_ACQUISITION_FRAME_COUNT    = 3004 | GX_FEATURE_INT | GX_FEATURE_LEVEL_REMOTE_DEV,     ///< 
	GX_ENUM_TRIGGER_MODE              = 3005 | GX_FEATURE_ENUM | GX_FEATURE_LEVEL_REMOTE_DEV,    ///< Refer to GX_TRIGGER_MODE_ENTRY
	GX_COMMAND_TRIGGER_SOFTWARE       = 3006 | GX_FEATURE_COMMAND | GX_FEATURE_LEVEL_REMOTE_DEV, ///< 
	GX_ENUM_TRIGGER_ACTIVATION        = 3007 | GX_FEATURE_ENUM | GX_FEATURE_LEVEL_REMOTE_DEV,    ///< Refer to GX_TRIGGER_ACTIVATION_ENTRY
	GX_ENUM_TRIGGER_SWITCH            = 3008 | GX_FEATURE_ENUM | GX_FEATURE_LEVEL_REMOTE_DEV,    ///< Refer to GX_TRIGGER_SWITCH_ENTRY
	GX_FLOAT_EXPOSURE_TIME            = 3009 | GX_FEATURE_FLOAT | GX_FEATURE_LEVEL_REMOTE_DEV,   ///< 
	GX_ENUM_EXPOSURE_AUTO             = 3010 | GX_FEATURE_ENUM | GX_FEATURE_LEVEL_REMOTE_DEV,    ///< Refer to GX_EXPOSURE_AUTO_ENTRY
	GX_FLOAT_TRIGGER_FILTER_RAISING   = 3011 | GX_FEATURE_FLOAT | GX_FEATURE_LEVEL_REMOTE_DEV,   ///< 
	GX_FLOAT_TRIGGER_FILTER_FALLING   = 3012 | GX_FEATURE_FLOAT | GX_FEATURE_LEVEL_REMOTE_DEV,   ///< 
	GX_ENUM_TRIGGER_SOURCE            = 3013 | GX_FEATURE_ENUM | GX_FEATURE_LEVEL_REMOTE_DEV,    ///< Refer to GX_TRIGGER_SOURCE_ENTRY
	GX_ENUM_EXPOSURE_MODE             = 3014 | GX_FEATURE_ENUM | GX_FEATURE_LEVEL_REMOTE_DEV,    ///< Refer to GX_EXPOSURE_MODE_ENTRY
	GX_ENUM_TRIGGER_SELECTOR          = 3015 | GX_FEATURE_ENUM | GX_FEATURE_LEVEL_REMOTE_DEV,    ///< Refer to GX_TRIGGER_SELECTOR_ENTRY
	GX_FLOAT_TRIGGER_DELAY            = 3016 | GX_FEATURE_FLOAT | GX_FEATURE_LEVEL_REMOTE_DEV,   ///< 
	GX_ENUM_TRANSFER_CONTROL_MODE     = 3017 | GX_FEATURE_ENUM | GX_FEATURE_LEVEL_REMOTE_DEV,    ///< Refer to GX_TRANSFER_CONTROL_MODE_ENTRY
	GX_ENUM_TRANSFER_OPERATION_MODE   = 3018 | GX_FEATURE_ENUM | GX_FEATURE_LEVEL_REMOTE_DEV,    ///< Refer to GX_TRANSFER_OPERATION_MODE_ENTRY
	GX_COMMAND_TRANSFER_START         = 3019 | GX_FEATURE_COMMAND | GX_FEATURE_LEVEL_REMOTE_DEV, ///< 
	GX_INT_TRANSFER_BLOCK_COUNT       = 3020 | GX_FEATURE_INT | GX_FEATURE_LEVEL_REMOTE_DEV,     ///< GX_ENUM_TRANSFER_OPERATION_MODE must set to be GX_ENUM_TRANSFER_OPERATION_MODE_MULTIBLOCK
	GX_BOOL_FRAMESTORE_COVER_ACTIVE   = 3021 | GX_FEATURE_BOOL | GX_FEATURE_LEVEL_REMOTE_DEV,    ///< 


	//----------------DigitalIO Section----------------------------------
	GX_ENUM_USER_OUTPUT_SELECTOR      = 4000 | GX_FEATURE_ENUM | GX_FEATURE_LEVEL_REMOTE_DEV,   ///< Refer to GX_USER_OUTPUT_SELECTOR_ENTRY
	GX_BOOL_USER_OUTPUT_VALUE         = 4001 | GX_FEATURE_BOOL | GX_FEATURE_LEVEL_REMOTE_DEV,   ///< 
	GX_ENUM_USER_OUTPUT_MODE          = 4002 | GX_FEATURE_ENUM | GX_FEATURE_LEVEL_REMOTE_DEV,   ///< Refer to GX_USER_OUTPUT_MODE_ENTRY
	GX_ENUM_STROBE_SWITCH             = 4003 | GX_FEATURE_ENUM | GX_FEATURE_LEVEL_REMOTE_DEV,   ///< Refer to GX_STROBE_SWITCH_ENTRY
	GX_ENUM_LINE_SELECTOR             = 4004 | GX_FEATURE_ENUM | GX_FEATURE_LEVEL_REMOTE_DEV,   ///< Refer to GX_LINE_SELECTOR_ENTRY
	GX_ENUM_LINE_MODE                 = 4005 | GX_FEATURE_ENUM | GX_FEATURE_LEVEL_REMOTE_DEV,   ///< Refer to GX_LINE_MODE_ENTRY
	GX_BOOL_LINE_INVERTER             = 4006 | GX_FEATURE_BOOL | GX_FEATURE_LEVEL_REMOTE_DEV,   ///< 
	GX_ENUM_LINE_SOURCE               = 4007 | GX_FEATURE_ENUM | GX_FEATURE_LEVEL_REMOTE_DEV,   ///< Refer to GX_LINE_SOURCE_ENTRY
	GX_BOOL_LINE_STATUS               = 4008 | GX_FEATURE_BOOL | GX_FEATURE_LEVEL_REMOTE_DEV,   ///< 
	GX_INT_LINE_STATUS_ALL            = 4009 | GX_FEATURE_INT  | GX_FEATURE_LEVEL_REMOTE_DEV,   ///< 

	//----------------AnalogControls Section----------------------------
	GX_ENUM_GAIN_AUTO                 = 5000 | GX_FEATURE_ENUM | GX_FEATURE_LEVEL_REMOTE_DEV,   ///< Refer to GX_GAIN_AUTO_ENTRY
	GX_ENUM_GAIN_SELECTOR             = 5001 | GX_FEATURE_ENUM | GX_FEATURE_LEVEL_REMOTE_DEV,   ///< Refer to GX_GAIN_SELECTOR_ENTRY	
	GX_ENUM_BLACKLEVEL_AUTO           = 5003 | GX_FEATURE_ENUM | GX_FEATURE_LEVEL_REMOTE_DEV,   ///< Refer to GX_BLACKLEVEL_AUTO_ENTRY
	GX_ENUM_BLACKLEVEL_SELECTOR       = 5004 | GX_FEATURE_ENUM | GX_FEATURE_LEVEL_REMOTE_DEV,   ///< Refer to GX_BLACKLEVEL_SELECTOR_ENTRY	
	GX_ENUM_BALANCE_WHITE_AUTO        = 5006 | GX_FEATURE_ENUM | GX_FEATURE_LEVEL_REMOTE_DEV,   ///< Refer to GX_BALANCE_WHITE_AUTO_ENTRY
	GX_ENUM_BALANCE_RATIO_SELECTOR    = 5007 | GX_FEATURE_ENUM | GX_FEATURE_LEVEL_REMOTE_DEV,   ///< Refer to GX_BALANCE_RATIO_SELECTOR_ENTRY
	GX_FLOAT_BALANCE_RATIO            = 5008 | GX_FEATURE_FLOAT | GX_FEATURE_LEVEL_REMOTE_DEV,  ///< 
	GX_ENUM_COLOR_CORRECT             = 5009 | GX_FEATURE_ENUM | GX_FEATURE_LEVEL_REMOTE_DEV,   ///< Refer to GX_COLOR_CORRECT_ENTRY
	GX_ENUM_DEAD_PIXEL_CORRECT        = 5010 | GX_FEATURE_ENUM | GX_FEATURE_LEVEL_REMOTE_DEV,   ///< Refer to GX_DEAD_PIXEL_CORRECT_ENTRY
	GX_FLOAT_GAIN                     = 5011 | GX_FEATURE_FLOAT | GX_FEATURE_LEVEL_REMOTE_DEV,  ///< 
	GX_FLOAT_BLACKLEVEL               = 5012 | GX_FEATURE_FLOAT | GX_FEATURE_LEVEL_REMOTE_DEV,  ///< 

	//---------------CustomFeature Section-------------------------
	GX_INT_ADC_LEVEL                  = 6000 | GX_FEATURE_INT | GX_FEATURE_LEVEL_REMOTE_DEV,    ///< 
	GX_INT_H_BLANKING                 = 6001 | GX_FEATURE_INT | GX_FEATURE_LEVEL_REMOTE_DEV,    ///< 
	GX_INT_V_BLANKING                 = 6002 | GX_FEATURE_INT | GX_FEATURE_LEVEL_REMOTE_DEV,    ///< 
	GX_STRING_USER_PASSWORD           = 6003 | GX_FEATURE_STRING | GX_FEATURE_LEVEL_REMOTE_DEV, ///< 
	GX_STRING_VERIFY_PASSWORD         = 6004 | GX_FEATURE_STRING | GX_FEATURE_LEVEL_REMOTE_DEV, ///< 
	GX_BUFFER_USER_DATA               = 6005 | GX_FEATURE_BUFFER | GX_FEATURE_LEVEL_REMOTE_DEV, ///< 
	GX_INT_GRAY_VALUE                 = 6006 | GX_FEATURE_INT | GX_FEATURE_LEVEL_REMOTE_DEV,    ///< 
	GX_ENUM_AA_LIGHT_ENVIRONMENT      = 6007 | GX_FEATURE_ENUM | GX_FEATURE_LEVEL_REMOTE_DEV,   ///< Refer to GX_AA_LIGHT_ENVIRMENT_ENTRY
	GX_INT_AAROI_OFFSETX              = 6008 | GX_FEATURE_INT | GX_FEATURE_LEVEL_REMOTE_DEV,    ///< 
	GX_INT_AAROI_OFFSETY              = 6009 | GX_FEATURE_INT | GX_FEATURE_LEVEL_REMOTE_DEV,    ///< 
	GX_INT_AAROI_WIDTH                = 6010 | GX_FEATURE_INT | GX_FEATURE_LEVEL_REMOTE_DEV,    ///< 
	GX_INT_AAROI_HEIGHT               = 6011 | GX_FEATURE_INT | GX_FEATURE_LEVEL_REMOTE_DEV,    ///< 
	GX_FLOAT_AUTO_GAIN_MIN            = 6012 | GX_FEATURE_FLOAT | GX_FEATURE_LEVEL_REMOTE_DEV,  ///< 
	GX_FLOAT_AUTO_GAIN_MAX            = 6013 | GX_FEATURE_FLOAT | GX_FEATURE_LEVEL_REMOTE_DEV,  ///< 
	GX_FLOAT_AUTO_EXPOSURE_TIME_MIN   = 6014 | GX_FEATURE_FLOAT | GX_FEATURE_LEVEL_REMOTE_DEV,  ///< 
	GX_FLOAT_AUTO_EXPOSURE_TIME_MAX   = 6015 | GX_FEATURE_FLOAT | GX_FEATURE_LEVEL_REMOTE_DEV,  ///< 
	GX_BUFFER_FRAME_INFORMATION       = 6016 | GX_FEATURE_BUFFER | GX_FEATURE_LEVEL_REMOTE_DEV, ///< 
	GX_INT_CONTRAST_PARAM             = 6017 | GX_FEATURE_INT | GX_FEATURE_LEVEL_REMOTE_DEV,    ///< 
	GX_FLOAT_GAMMA_PARAM              = 6018 | GX_FEATURE_FLOAT | GX_FEATURE_LEVEL_REMOTE_DEV,  ///< 
	GX_INT_COLOR_CORRECTION_PARAM     = 6019 | GX_FEATURE_INT | GX_FEATURE_LEVEL_REMOTE_DEV,    ///< 
	GX_ENUM_IMAGE_GRAY_RAISE_SWITCH   = 6020 | GX_FEATURE_ENUM | GX_FEATURE_LEVEL_REMOTE_DEV,   ///< Refer to GX_IMAGE_GRAY_RAISE_SWITCH_ENTRY
	GX_ENUM_AWB_LAMP_HOUSE            = 6021 | GX_FEATURE_ENUM | GX_FEATURE_LEVEL_REMOTE_DEV,   ///< Refer to GX_AWB_LAMP_HOUSE_ENTRY
	GX_INT_AWBROI_OFFSETX             = 6022 | GX_FEATURE_INT | GX_FEATURE_LEVEL_REMOTE_DEV,    ///< 
	GX_INT_AWBROI_OFFSETY             = 6023 | GX_FEATURE_INT | GX_FEATURE_LEVEL_REMOTE_DEV,    ///< 
	GX_INT_AWBROI_WIDTH               = 6024 | GX_FEATURE_INT | GX_FEATURE_LEVEL_REMOTE_DEV,    ///< 
	GX_INT_AWBROI_HEIGHT              = 6025 | GX_FEATURE_INT | GX_FEATURE_LEVEL_REMOTE_DEV,    ///< 

	//---------------UserSetControl Section-------------------------
	GX_ENUM_USER_SET_SELECTOR         = 7000 | GX_FEATURE_ENUM | GX_FEATURE_LEVEL_REMOTE_DEV,    ///< Refer to GX_USER_SET_SELECTOR_ENTRY
	GX_COMMAND_USER_SET_LOAD          = 7001 | GX_FEATURE_COMMAND | GX_FEATURE_LEVEL_REMOTE_DEV, ///< 
	GX_COMMAND_USER_SET_SAVE          = 7002 | GX_FEATURE_COMMAND | GX_FEATURE_LEVEL_REMOTE_DEV, ///< 
	GX_ENUM_USER_SET_DEFAULT          = 7003 | GX_FEATURE_ENUM | GX_FEATURE_LEVEL_REMOTE_DEV,    ///< Refer to GX_USER_SET_DEFAULT_ENTRY

	//---------------Event Section-------------------------
	GX_ENUM_EVENT_SELECTOR             = 8000 | GX_FEATURE_ENUM | GX_FEATURE_LEVEL_REMOTE_DEV, ///< Refer to GX_EVENT_SELECTOR_ENTRY
	GX_ENUM_EVENT_NOTIFICATION         = 8001 | GX_FEATURE_ENUM | GX_FEATURE_LEVEL_REMOTE_DEV, ///< Refer to GX_EVENT_NOTIFICATION_ENTRY
	GX_INT_EVENT_EXPOSUREEND           = 8002 | GX_FEATURE_INT | GX_FEATURE_LEVEL_REMOTE_DEV,    ///< 
	GX_INT_EVENT_EXPOSUREEND_TIMESTAMP = 8003 | GX_FEATURE_INT | GX_FEATURE_LEVEL_REMOTE_DEV,    ///< 
	GX_INT_EVENT_EXPOSUREEND_FRAMEID   = 8004 | GX_FEATURE_INT | GX_FEATURE_LEVEL_REMOTE_DEV,    ///< 
	GX_INT_EVENT_BLOCK_DISCARD         = 8005 | GX_FEATURE_INT | GX_FEATURE_LEVEL_REMOTE_DEV,    ///< 
	GX_INT_EVENT_BLOCK_DISCARD_TIMESTAMP = 8006 | GX_FEATURE_INT | GX_FEATURE_LEVEL_REMOTE_DEV,    ///< 
	GX_INT_EVENT_OVERRUN                 = 8007 | GX_FEATURE_INT | GX_FEATURE_LEVEL_REMOTE_DEV,    ///< 
	GX_INT_EVENT_OVERRUN_TIMESTAMP       = 8008 | GX_FEATURE_INT | GX_FEATURE_LEVEL_REMOTE_DEV,    ///< 
	GX_INT_EVENT_FRAMESTART_OVERTRIGGER  = 8009 | GX_FEATURE_INT | GX_FEATURE_LEVEL_REMOTE_DEV,    ///< 
	GX_INT_EVENT_FRAMESTART_OVERTRIGGER_TIMESTAMP = 8010 | GX_FEATURE_INT | GX_FEATURE_LEVEL_REMOTE_DEV,    ///< 
	GX_INT_EVENT_BLOCK_NOT_EMPTY                  = 8011 | GX_FEATURE_INT | GX_FEATURE_LEVEL_REMOTE_DEV,    ///< 
	GX_INT_EVENT_BLOCK_NOT_EMPTY_TIMESTAMP        = 8012 | GX_FEATURE_INT | GX_FEATURE_LEVEL_REMOTE_DEV,    ///< 

	//---------------LUT Section-------------------------
	GX_ENUM_LUT_SELECTOR             = 9000 | GX_FEATURE_ENUM | GX_FEATURE_LEVEL_REMOTE_DEV, ///< Refer to GX_LUT_SELECTOR_ENTRY
	GX_BUFFER_LUT_VALUEALL           = 9001 | GX_FEATURE_BUFFER | GX_FEATURE_LEVEL_REMOTE_DEV, ///< 

	//---------------ChunkData Section-------------------------
	GX_BOOL_CHUNKMODE_ACTIVE         = 10001 | GX_FEATURE_BOOL | GX_FEATURE_LEVEL_REMOTE_DEV, ///< 
	GX_ENUM_CHUNK_SELECTOR           = 10002 | GX_FEATURE_ENUM | GX_FEATURE_LEVEL_REMOTE_DEV, ///< Refer to GX_CHUNK_SELECTOR_ENTRY
	GX_BOOL_CHUNK_ENABLE             = 10003 | GX_FEATURE_BOOL | GX_FEATURE_LEVEL_REMOTE_DEV, ///< 
	

	//////////////////////////////////////////////////////////////////////////
	/// Device Feature
	//////////////////////////////////////////////////////////////////////////
	GX_DEV_INT_COMMAND_TIMEOUT     = 0 | GX_FEATURE_INT | GX_FEATURE_LEVEL_DEV, ///< Unit ms
	GX_DEV_INT_COMMAND_RETRY_COUNT = 1 | GX_FEATURE_INT | GX_FEATURE_LEVEL_DEV, ///< 

	//////////////////////////////////////////////////////////////////////////
	/// DataStream Feature
	//////////////////////////////////////////////////////////////////////////
	GX_DS_INT_ANNOUNCED_BUFFER_COUNT          = 0 | GX_FEATURE_INT | GX_FEATURE_LEVEL_DS, ///< The announced buffer count
	GX_DS_INT_DELIVERED_FRAME_COUNT           = 1 | GX_FEATURE_INT | GX_FEATURE_LEVEL_DS, ///< The delivered frame count,Incomplete frame included
	GX_DS_INT_LOST_FRAME_COUNT                = 2 | GX_FEATURE_INT | GX_FEATURE_LEVEL_DS, ///< The lost frame count, Because of Lack of resources
	GX_DS_INT_INCOMPLETE_FRAME_COUNT          = 3 | GX_FEATURE_INT | GX_FEATURE_LEVEL_DS, ///< The incomplete frame count
	GX_DS_INT_DELIVERED_PACKET_COUNT          = 4 | GX_FEATURE_INT | GX_FEATURE_LEVEL_DS, ///< The delivered packet count
	GX_DS_INT_RESEND_PACKET_COUNT             = 5 | GX_FEATURE_INT | GX_FEATURE_LEVEL_DS, ///< The resend packet count
	GX_DS_INT_RESCUED_PACKED_COUNT            = 6 | GX_FEATURE_INT | GX_FEATURE_LEVEL_DS, ///< The rescued packet count
	GX_DS_INT_RESEND_COMMAND_COUNT            = 7 | GX_FEATURE_INT | GX_FEATURE_LEVEL_DS, ///< The resend command count
	GX_DS_INT_UNEXPECTED_PACKED_COUNT         = 8 | GX_FEATURE_INT | GX_FEATURE_LEVEL_DS, ///< The unexpected packet count
	GX_DS_INT_MAX_PACKET_COUNT_IN_ONE_BLOCK   = 9 | GX_FEATURE_INT | GX_FEATURE_LEVEL_DS, ///< The maximum allowable number of resend packets in one block
	GX_DS_INT_MAX_PACKET_COUNT_IN_ONE_COMMAND = 10 | GX_FEATURE_INT | GX_FEATURE_LEVEL_DS, ///< The maximum allowable number of resend packets in one command
	GX_DS_INT_RESEND_TIMEOUT                  = 11 | GX_FEATURE_INT | GX_FEATURE_LEVEL_DS, ///< The resend timeout
	GX_DS_INT_MAX_WAIT_PACKET_COUNT           = 12 | GX_FEATURE_INT | GX_FEATURE_LEVEL_DS, ///< The maximum wait packet count
	GX_DS_ENUM_RESEND_MODE                    = 13 | GX_FEATURE_ENUM | GX_FEATURE_LEVEL_DS, ///< Refer to GX_DS_RESEND_MODE_ENTRY
	GX_DS_INT_MISSING_BLOCKID_COUNT           = 14 | GX_FEATURE_INT | GX_FEATURE_LEVEL_DS,  ///< The missing block ID count
	GX_DS_INT_BLOCK_TIMEOUT                   = 15 | GX_FEATURE_INT | GX_FEATURE_LEVEL_DS,  ///< The block timeout
	GX_DS_INT_STREAM_TRANSFER_SIZE            = 16 | GX_FEATURE_INT | GX_FEATURE_LEVEL_DS,  ///< the transfer size
	GX_DS_INT_STREAM_TRANSFER_NUMBER_URB      = 17 | GX_FEATURE_INT | GX_FEATURE_LEVEL_DS,  ///< the transfer URB number

	//////////////////////////////////////////////////////////////////////////
	/// Deprecated Section
	//////////////////////////////////////////////////////////////////////////
	GX_STRING_DEVICE_ID               = 4    | GX_FEATURE_STRING | GX_FEATURE_LEVEL_REMOTE_DEV, ///< switch to GX_STRING_DEVICE_SERIAL_NUMBER	
	GX_STRING_DEVICE_HARDWARE_VERSION = 5    | GX_FEATURE_STRING | GX_FEATURE_LEVEL_REMOTE_DEV, ///< 
	GX_INT_GAIN                       = 5002 | GX_FEATURE_INT | GX_FEATURE_LEVEL_REMOTE_DEV,    ///< switch to GX_FLOAT_GAIN
	GX_INT_BLACKLEVEL                 = 5005 | GX_FEATURE_INT | GX_FEATURE_LEVEL_REMOTE_DEV,    ///< switch to GX_FLOAT_BLACKLEVEL
	GX_FLOAT_BALANCE_RATIO_SELECTOR   = 5007 | GX_FEATURE_ENUM | GX_FEATURE_LEVEL_REMOTE_DEV,   ///< switch to GX_ENUM_BALANCE_RATIO_SELECTOR
	GX_ENUM_AA_LIGHT_ENVIRMENT        = 6007 | GX_FEATURE_ENUM | GX_FEATURE_LEVEL_REMOTE_DEV,   ///< switch to GX_ENUM_AA_LIGHT_ENVIRONMENT
	GX_INT_ROI_X                      = 6008 | GX_FEATURE_INT | GX_FEATURE_LEVEL_REMOTE_DEV,    ///< switch to GX_INT_AAROI_OFFSETX
	GX_INT_ROI_Y                      = 6009 | GX_FEATURE_INT | GX_FEATURE_LEVEL_REMOTE_DEV,    ///< switch to GX_INT_AAROI_OFFSETY
	GX_INT_ROI_WIDTH                  = 6010 | GX_FEATURE_INT | GX_FEATURE_LEVEL_REMOTE_DEV,    ///< switch to GX_INT_AAROI_WIDTH
	GX_INT_ROI_HEIGHT                 = 6011 | GX_FEATURE_INT | GX_FEATURE_LEVEL_REMOTE_DEV,    ///< switch to GX_INT_AAROI_HEIGHT
	GX_INT_AUTO_GAIN_VALUEMIN         = 6012 | GX_FEATURE_INT | GX_FEATURE_LEVEL_REMOTE_DEV,    ///< switch to GX_FLOAT_AUTO_GAIN_MIN
	GX_INT_AUTO_GAIN_VALUEMAX         = 6013 | GX_FEATURE_INT | GX_FEATURE_LEVEL_REMOTE_DEV,    ///< switch to GX_FLOAT_AUTO_GAIN_MAX
	GX_INT_AUTO_SHUTTER_VALUEMIN      = 6014 | GX_FEATURE_INT | GX_FEATURE_LEVEL_REMOTE_DEV,    ///< switch to GX_FLOAT_AUTO_EXPOSURE_TIME_MIN
	GX_INT_AUTO_SHUTTER_VALUEMAX      = 6015 | GX_FEATURE_INT | GX_FEATURE_LEVEL_REMOTE_DEV,    ///< switch to GX_FLOAT_AUTO_EXPOSURE_TIME_MAX
	GX_INT_CONTRASTPARAM              = 6017 | GX_FEATURE_INT | GX_FEATURE_LEVEL_REMOTE_DEV,    ///< switch to GX_INT_CONTRAST_PARAM
	GX_FLOAT_GAMMAPARAM               = 6018 | GX_FEATURE_FLOAT | GX_FEATURE_LEVEL_REMOTE_DEV,  ///< switch to GX_FLOAT_GAMMA_PARAM
	GX_INT_COLORCORRECTIONPARAM       = 6019 | GX_FEATURE_INT | GX_FEATURE_LEVEL_REMOTE_DEV,    ///< switch to GX_INT_COLOR_CORRECTION_PARAM


}GX_FEATURE_ID;
typedef int32_t GX_FEATURE_ID_CMD;


typedef void* GX_DEV_HANDLE;               ///< 
typedef void* GX_EVENT_CALLBACK_HANDLE;    ///< 
typedef void* GX_FEATURE_CALLBACK_HANDLE;  ///< 

//------------------------------------------------------------------------------------
typedef enum GX_PIXEL_SIZE_ENTRY
{
	GX_PIXEL_SIZE_BPP8  = 8,
	GX_PIXEL_SIZE_BPP10 = 10,
	GX_PIXEL_SIZE_BPP12 = 12,
	GX_PIXEL_SIZE_BPP16 = 16,
	GX_PIXEL_SIZE_BPP24 = 24,
	GX_PIXEL_SIZE_BPP30 = 30,
	GX_PIXEL_SIZE_BPP32 = 32,
	GX_PIXEL_SIZE_BPP36 = 36,
	GX_PIXEL_SIZE_BPP48 = 48,
	GX_PIXEL_SIZE_BPP64 = 64,
}GX_PIXEL_SIZE_ENTRY;

typedef enum GX_PIXEL_COLOR_FILTER_ENTRY
{
	GX_COLOR_FILTER_NONE     = 0,                        ///<
	GX_COLOR_FILTER_BAYER_RG = 1,                        ///<
	GX_COLOR_FILTER_BAYER_GB = 2,                        ///<
	GX_COLOR_FILTER_BAYER_GR = 3,                        ///<
	GX_COLOR_FILTER_BAYER_BG = 4,                        ///<
}GX_PIXEL_COLOR_FILTER_ENTRY;

#define GX_PIXEL_MONO                  ( 0x01000000 )
#define GX_PIXEL_COLOR                 ( 0x02000000 )

#define GX_PIXEL_8BIT                  ( 0x00080000 )
#define GX_PIXEL_10BIT                 ( 0x000A0000 )
#define GX_PIXEL_12BIT                 ( 0x000C0000 )
#define GX_PIXEL_16BIT                 ( 0x00100000 )
#define GX_PIXEL_24BIT                 ( 0x00180000 )
#define GX_PIXEL_30BIT                 ( 0x001E0000 )
#define GX_PIXEL_32BIT                 ( 0x00200000 )
#define GX_PIXEL_36BIT                 ( 0x00240000 )
#define GX_PIXEL_48BIT                 ( 0x00300000 )
#define GX_PIXEL_64BIT                 ( 0x00400000 )

typedef enum GX_PIXEL_FORMAT_ENTRY
{
	GX_PIXEL_FORMAT_UNDEFINED          = (0),
	GX_PIXEL_FORMAT_MONO8              = (GX_PIXEL_MONO  | GX_PIXEL_8BIT  | 0x0001),//0x1080001,
	GX_PIXEL_FORMAT_MONO8_SIGNED       = (GX_PIXEL_MONO  | GX_PIXEL_8BIT  | 0x0002),//0x1080002,
	GX_PIXEL_FORMAT_MONO10             = (GX_PIXEL_MONO  | GX_PIXEL_16BIT | 0x0003),//0x1100003,	
	GX_PIXEL_FORMAT_MONO12             = (GX_PIXEL_MONO  | GX_PIXEL_16BIT | 0x0005),//0x1100005,	
	GX_PIXEL_FORMAT_MONO14             = (GX_PIXEL_MONO  | GX_PIXEL_16BIT | 0x0025),//0x1100025,
	GX_PIXEL_FORMAT_MONO16             = (GX_PIXEL_MONO  | GX_PIXEL_16BIT | 0x0007),//0x1100007,
	GX_PIXEL_FORMAT_BAYER_GR8          = (GX_PIXEL_MONO  | GX_PIXEL_8BIT  | 0x0008),//0x1080008,               
	GX_PIXEL_FORMAT_BAYER_RG8          = (GX_PIXEL_MONO  | GX_PIXEL_8BIT  | 0x0009),//0x1080009,                
	GX_PIXEL_FORMAT_BAYER_GB8          = (GX_PIXEL_MONO  | GX_PIXEL_8BIT  | 0x000A),//0x108000A,
	GX_PIXEL_FORMAT_BAYER_BG8          = (GX_PIXEL_MONO  | GX_PIXEL_8BIT  | 0x000B),//0x108000B,
	GX_PIXEL_FORMAT_BAYER_GR10         = (GX_PIXEL_MONO  | GX_PIXEL_16BIT | 0x000C),//0x110000C,                
	GX_PIXEL_FORMAT_BAYER_RG10         = (GX_PIXEL_MONO  | GX_PIXEL_16BIT | 0x000D),//0x110000D,
	GX_PIXEL_FORMAT_BAYER_GB10         = (GX_PIXEL_MONO  | GX_PIXEL_16BIT | 0x000E),//0x110000E,
	GX_PIXEL_FORMAT_BAYER_BG10         = (GX_PIXEL_MONO  | GX_PIXEL_16BIT | 0x000F),//0x110000F,
	GX_PIXEL_FORMAT_BAYER_GR12         = (GX_PIXEL_MONO  | GX_PIXEL_16BIT | 0x0010),//0x1100010,              
	GX_PIXEL_FORMAT_BAYER_RG12         = (GX_PIXEL_MONO  | GX_PIXEL_16BIT | 0x0011),//0x1100011,
	GX_PIXEL_FORMAT_BAYER_GB12         = (GX_PIXEL_MONO  | GX_PIXEL_16BIT | 0x0012),//0x1100012,
	GX_PIXEL_FORMAT_BAYER_BG12         = (GX_PIXEL_MONO  | GX_PIXEL_16BIT | 0x0013),//0x1100013,	
	GX_PIXEL_FORMAT_BAYER_GR16         = (GX_PIXEL_MONO  | GX_PIXEL_16BIT | 0x002E),//0x110002E,                
	GX_PIXEL_FORMAT_BAYER_RG16         = (GX_PIXEL_MONO  | GX_PIXEL_16BIT | 0x002F),//0x110002F,
	GX_PIXEL_FORMAT_BAYER_GB16         = (GX_PIXEL_MONO  | GX_PIXEL_16BIT | 0x0030),//0x1100030,
	GX_PIXEL_FORMAT_BAYER_BG16         = (GX_PIXEL_MONO  | GX_PIXEL_16BIT | 0x0031),//0x1100031,	
	GX_PIXEL_FORMAT_RGB8_PLANAR        = (GX_PIXEL_COLOR | GX_PIXEL_24BIT | 0x0021),//0x2180021,
	GX_PIXEL_FORMAT_RGB10_PLANAR       = (GX_PIXEL_COLOR | GX_PIXEL_48BIT | 0x0022),//0x2300022,
	GX_PIXEL_FORMAT_RGB12_PLANAR       = (GX_PIXEL_COLOR | GX_PIXEL_48BIT | 0x0023),//0x2300023,
	GX_PIXEL_FORMAT_RGB16_PLANAR       = (GX_PIXEL_COLOR | GX_PIXEL_48BIT | 0x0024),//0x2300024,
}GX_PIXEL_FORMAT_ENTRY;

typedef enum GX_ACQUISITION_MODE_ENTRY
{
	GX_ACQ_MODE_SINGLE_FRAME = 0,                          ///<
	GX_ACQ_MODE_MULITI_FRAME = 1,                          ///<
	GX_ACQ_MODE_CONTINUOUS   = 2,                          ///<
}GX_ACQUISITION_MODE_ENTRY;

typedef enum GX_TRIGGER_MODE_ENTRY
{
	GX_TRIGGER_MODE_OFF = 0,                             ///< 
	GX_TRIGGER_MODE_ON  = 1,                             ///< 
}GX_TRIGGER_MODE_ENTRY;

typedef enum GX_TRIGGER_SOURCE_ENTRY
{
	GX_TRIGGER_SOURCE_SOFTWARE = 0,                      ///< 
	GX_TRIGGER_SOURCE_LINE0    = 1,                      ///< 
	GX_TRIGGER_SOURCE_LINE1    = 2,                      ///< 
	GX_TRIGGER_SOURCE_LINE2    = 3,                      ///< 
	GX_TRIGGER_SOURCE_LINE3    = 4,                      ///< 
}GX_TRIGGER_SOURCE_ENTRY;

typedef enum GX_TRIGGER_ACTIVATION_ENTRY
{
	GX_TRIGGER_ACTIVATION_FALLINGEDGE = 0,               ///< 
	GX_TRIGGER_ACTIVATION_RISINGEDGE  = 1,               ///< 
}GX_TRIGGER_ACTIVATION_ENTRY;

typedef enum GX_TRIGGER_SWITCH_ENTRY
{
	GX_TRIGGER_SWITCH_OFF = 0,                           ///< 
	GX_TRIGGER_SWITCH_ON  = 1,                           ///< 
}GX_TRIGGER_SWITCH_ENTRY;

typedef enum GX_EXPOSURE_MODE_ENTRY
{
	GX_EXPOSURE_MODE_TIMED          = 1,                 ///< 
	GX_EXPOSURE_MODE_TRIGGERWIDTH   = 2,                 ///< 
}GX_EXPOSURE_MODE_ENTRY;

typedef enum GX_EXPOSURE_AUTO_ENTRY
{
	GX_EXPOSURE_AUTO_OFF        = 0,                     ///< 
	GX_EXPOSURE_AUTO_CONTINUOUS = 1,                     ///< 
	GX_EXPOSURE_AUTO_ONCE       = 2,                     ///< 
}GX_EXPOSURE_AUTO_ENTRY;

typedef enum GX_USER_OUTPUT_SELECTOR_ENTRY
{
	GX_USER_OUTPUT_SELECTOR_OUTPUT0 = 1,                   ///<
	GX_USER_OUTPUT_SELECTOR_OUTPUT1 = 2,                   ///<
	GX_USER_OUTPUT_SELECTOR_OUTPUT2 = 4,                   ///<
}GX_USER_OUTPUT_SELECTOR_ENTRY;

typedef enum GX_USER_OUTPUT_MODE_ENTRY
{
	GX_USER_OUTPUT_MODE_STROBE      = 0,                   ///<
	GX_USER_OUTPUT_MODE_USERDEFINED = 1,                   ///<
}GX_USER_OUTPUT_MODE_ENTRY;

typedef enum GX_STROBE_SWITCH_ENTRY
{
	GX_STROBE_SWITCH_OFF = 0,                            ///< 
	GX_STROBE_SWITCH_ON  = 1,                            ///< 
}GX_STROBE_SWITCH_ENTRY;

typedef enum GX_GAIN_AUTO_ENTRY
{
	GX_GAIN_AUTO_OFF        = 0,                         ///< 
	GX_GAIN_AUTO_CONTINUOUS = 1,                         ///< 
	GX_GAIN_AUTO_ONCE       = 2,                         ///< 
}GX_GAIN_AUTO_ENTRY;

typedef enum GX_GAIN_SELECTOR_ENTRY
{
	GX_GAIN_SELECTOR_ALL   = 0,                          ///< 
	GX_GAIN_SELECTOR_RED   = 1,                          ///< 
	GX_GAIN_SELECTOR_GREEN = 2,                          ///< 
	GX_GAIN_SELECTOR_BLUE  = 3,                          ///< 
}GX_GAIN_SELECTOR_ENTRY;

typedef enum GX_BLACKLEVEL_AUTO_ENTRY
{
	GX_BLACKLEVEL_AUTO_OFF        = 0,                   ///< 
	GX_BLACKLEVEL_AUTO_CONTINUOUS = 1,                   ///< 
	GX_BLACKLEVEL_AUTO_ONCE       = 2,                   ///< 
}GX_BLACKLEVEL_AUTO_ENTRY;

typedef enum GX_BLACKLEVEL_SELECTOR_ENTRY
{
	GX_BLACKLEVEL_SELECTOR_ALL   = 0,                    ///< 
	GX_BLACKLEVEL_SELECTOR_RED   = 1,                    ///< 
	GX_BLACKLEVEL_SELECTOR_GREEN = 2,                    ///< 
	GX_BLACKLEVEL_SELECTOR_BLUE  = 3,                    ///< 
}GX_BLACKLEVEL_SELECTOR_ENTRY;

typedef enum GX_BALANCE_WHITE_AUTO_ENTRY
{
	GX_BALANCE_WHITE_AUTO_OFF        = 0,                ///< 
	GX_BALANCE_WHITE_AUTO_CONTINUOUS = 1,                ///< 
	GX_BALANCE_WHITE_AUTO_ONCE       = 2,                ///< 
}GX_BALANCE_WHITE_AUTO_ENTRY;

typedef enum GX_BALANCE_RATIO_SELECTOR_ENTRY
{
	GX_BALANCE_RATIO_SELECTOR_RED   = 0,                   ///<
	GX_BALANCE_RATIO_SELECTOR_GREEN = 1,                   ///<
	GX_BALANCE_RATIO_SELECTOR_BLUE  = 2,                   ///<
}GX_BALANCE_RATIO_SELECTOR_ENTRY;

typedef enum GX_COLOR_CORRECT_ENTRY
{
	GX_COLOR_CORRECT_OFF = 0,                            ///< 
	GX_COLOR_CORRECT_ON  = 1,                            ///< 
}GX_COLOR_CORRECT_ENTRY;

typedef enum GX_DEAD_PIXEL_CORRECT_ENTRY
{
	GX_DEAD_PIXEL_CORRECT_OFF = 0,                       ///< 
	GX_DEAD_PIXEL_CORRECT_ON  = 1,                       ///< 
}GX_DEAD_PIXEL_CORRECT_ENTRY;

typedef enum GX_AA_LIGHT_ENVIRMENT_ENTRY
{
	GX_AA_LIGHT_ENVIRMENT_NATURELIGHT = 0,                 ///<
	GX_AA_LIGHT_ENVIRMENT_AC50HZ      = 1,                 ///<
	GX_AA_LIGHT_ENVIRMENT_AC60HZ      = 2,                 ///<
}GX_AA_LIGHT_ENVIRMENT_ENTRY;

typedef enum GX_USER_SET_SELECTOR_ENTRY
{
	GX_ENUM_USER_SET_SELECTOR_DEFAULT  = 0,                 ///<
	GX_ENUM_USER_SET_SELECTOR_USERSET0 = 1,                 ///<
}GX_USER_SET_SELECTOR_ENTRY;

typedef enum GX_IMAGE_GRAY_RAISE_SWITCH_ENTRY
{
	GX_IMAGE_GRAY_RAISE_SWITCH_OFF = 0,                     ///< 
	GX_IMAGE_GRAY_RAISE_SWITCH_ON  = 1,                     ///< 
}GX_IMAGE_GRAY_RAISE_SWITCH_ENTRY;

typedef enum GX_AWB_LAMP_HOUSE_ENTRY
{
	GX_AWB_LAMP_HOUSE_ADAPTIVE      = 0,                      ///< 
	GX_AWB_LAMP_HOUSE_D65           = 1,                      ///< 6500k
	GX_AWB_LAMP_HOUSE_FLUORESCENCE  = 2,                      ///< 
	GX_AWB_LAMP_HOUSE_INCANDESCENT  = 3,                      ///< 
	GX_AWB_LAMP_HOUSE_D75           = 4,                      ///< 7500k
	GX_AWB_LAMP_HOUSE_D50           = 5,                      ///< 5000k
	GX_AWB_LAMP_HOUSE_D30           = 6,                      ///< 3000k
}GX_AWB_LAMP_HOUSE_ENTRY;

typedef enum GX_TEST_PATTERN_ENTRY
{
	GX_ENUM_TEST_PATTERN_OFF                    = 0,            ///<
	GX_ENUM_TEST_PATTERN_GRAY_FRAME_RAMP_MOVING = 1,            ///<
	GX_ENUM_TEST_PATTERN_SLANT_LINE_MOVING      = 2,            ///<
	GX_ENUM_TEST_PATTERN_VERTICAL_LINE_MOVING   = 3,            ///<
}GX_TEST_PATTERN_ENTRY;

typedef enum GX_TRIGGER_SELECTOR_ENTRY
{
	GX_ENUM_TRIGGER_SELECTOR_FRAME_START        = 1,               ///<
} GX_TRIGGER_SELECTOR_ENTRY;

typedef enum GX_LINE_SELECTOR_ENTRY
{
	GX_ENUM_LINE_SELECTOR_LINE0           = 0,               ///<
	GX_ENUM_LINE_SELECTOR_LINE1           = 1,               ///<
	GX_ENUM_LINE_SELECTOR_LINE2           = 2,               ///<
	GX_ENUM_LINE_SELECTOR_LINE3           = 3,               ///<
} GX_LINE_SELECTOR_ENTRY;

typedef enum GX_LINE_MODE_ENTRY
{
	GX_ENUM_LINE_MODE_INPUT            = 0,               ///<
	GX_ENUM_LINE_MODE_OUTPUT           = 1,               ///<
} GX_LINE_MODE_ENTRY;

typedef enum GX_LINE_SOURCE_ENTRY
{
	GX_ENUM_LINE_SOURCE_OFF               = 0,       ///<
	GX_ENUM_LINE_SOURCE_STROBE            = 1,       ///<
	GX_ENUM_LINE_SOURCE_USEROUTPUT0       = 2,       ///<
	GX_ENUM_LINE_SOURCE_USEROUTPUT1       = 3,       ///<
	GX_ENUM_LINE_SOURCE_USEROUTPUT2       = 4,       ///<
} GX_LINE_SOURCE_ENTRY;

typedef enum GX_EVENT_SELECTOR_ENTRY
{
	GX_ENUM_EVENT_SELECTOR_EXPOSUREEND              = 0x0004,       ///<
	GX_ENUM_EVENT_SELECTOR_BLOCK_DISCARD            = 0x9000,       ///<
	GX_ENUM_EVENT_SELECTOR_EVENT_OVERRUN            = 0x9001,       ///<
	GX_ENUM_EVENT_SELECTOR_FRAMESTART_OVERTRIGGER   = 0x9002,       ///<
	GX_ENUM_EVENT_SELECTOR_BLOCK_NOT_EMPTY          = 0x9003,       ///<
} GX_EVENT_SELECTOR_ENTRY;

typedef enum GX_EVENT_NOTIFICATION_ENTRY
{
	GX_ENUM_EVENT_NOTIFICATION_OFF             = 0,       ///<
	GX_ENUM_EVENT_NOTIFICATION_ON              = 1,       ///<
} GX_EVENT_NOTIFICATION_ENTRY;

typedef enum GX_LUT_SELECTOR_ENTRY
{
	GX_ENUM_LUT_SELECTOR_LUMINANCE             = 0,       ///<
} GX_LUT_SELECTOR_ENTRY;

typedef enum GX_TRANSFERDELAY_MODE_ENTRY
{
	GX_ENUM_TRANSFERDELAY_MODE_OFF     = 0,       ///<
	GX_ENUM_TRANSFERDELAY_MODE_ON      = 1,       ///<
} GX_TRANSFERDELAY_MODE_ENTRY;

typedef enum GX_COVER_FRAMESTORE_MODE_ENTRY
{
	GX_ENUM_COVER_FRAMESTORE_MODE_OFF     = 0,       ///<
	GX_ENUM_COVER_FRAMESTORE_MODE_ON      = 1,       ///<
} GX_COVER_FRAMESTORE_MODE_ENTRY;

typedef enum GX_USER_SET_DEFAULT_ENTRY
{
	GX_ENUM_USER_SET_DEFAULT_DEFAULT      = 0,       ///<
	GX_ENUM_USER_SET_DEFAULT_USERSET0     = 1,       ///<
} GX_USER_SET_DEFAULT_ENTRY;

typedef enum GX_TRANSFER_CONTROL_MODE_ENTRY
{
	GX_ENUM_TRANSFER_CONTROL_MODE_BASIC             = 0,   ///< 
	GX_ENUM_TRANSFER_CONTROL_MODE_USERCONTROLED     = 1,   ///< 
} GX_TRANSFER_CONTROL_MODE_ENTRY;

typedef enum GX_TRANSFER_OPERATION_MODE_ENTRY
{
	GX_ENUM_TRANSFER_OPERATION_MODE_MULTIBLOCK  = 0,  ///< 
} GX_TRANSFER_OPERATION_MODE_ENTRY;

typedef enum GX_DS_RESEND_MODE_ENTRY
{
	GX_DS_RESEND_MODE_OFF     = 0,  ///< 
	GX_DS_RESEND_MODE_ON      = 1,  ///< 
} GX_DS_RESEND_MODE_ENTRY;

typedef enum GX_DEVICE_LINK_THROUGHPUT_LIMIT_MODE_ENTRY
{
	GX_DEVICE_LINK_THROUGHPUT_LIMIT_MODE_OFF   = 0,   ///< 
	GX_DEVICE_LINK_THROUGHPUT_LIMIT_MODE_ON    = 1    ///< 
}GX_DEVICE_LINK_THROUGHPUT_LIMIT_MODE_ENTRY;

typedef enum GX_TEST_PATTERN_GENERATOR_SELECTOR_ENTRY
{
	GX_TEST_PATTERN_GENERATOR_SELECTOR_SENSOR  = 0,  ///< 
	GX_TEST_PATTERN_GENERATOR_SELECTOR_REGION0 = 1   ///< 
}GX_TEST_PATTERN_GENERATOR_SELECTOR_ENTRY;


typedef enum GX_CHUNK_SELECTOR_ENTRY
{
	GX_CHUNK_SELECTOR_CHUNK_FRAME_ID     = 1,    ///< 
	GX_CHUNK_SELECTOR_CHUNK_TIME_STAMP   = 2     ///< 
}GX_CHUNK_SELECTOR_ENTRY;



#define GX_INFO_LENGTH_8_BYTE   (8)  ///< 
#define GX_INFO_LENGTH_32_BYTE  (32) ///< 
#define GX_INFO_LENGTH_64_BYTE  (64) ///< 
#define GX_INFO_LENGTH_128_BYTE (128)///< 


typedef struct GX_DEVICE_IP_INFO 
{
	char szDeviceID[GX_INFO_LENGTH_64_BYTE + 4];         ///< 
	char szMAC[GX_INFO_LENGTH_32_BYTE];                  ///< 
	char szIP[GX_INFO_LENGTH_32_BYTE];                   ///< 
	char szSubNetMask[GX_INFO_LENGTH_32_BYTE];           ///< 
	char szGateWay[GX_INFO_LENGTH_32_BYTE];              ///< 
	char szNICMAC[GX_INFO_LENGTH_32_BYTE];               ///< 
	char szNICIP[GX_INFO_LENGTH_32_BYTE];                ///< 
	char szNICSubNetMask[GX_INFO_LENGTH_32_BYTE];        ///< 
	char szNICGateWay[GX_INFO_LENGTH_32_BYTE];           ///< 
	char szNICDescription[GX_INFO_LENGTH_128_BYTE + 4];  ///< 
	char reserved[512];                                  ///< 
}GX_DEVICE_IP_INFO;

typedef struct GX_DEVICE_BASE_INFO 
{
	char szVendorName[GX_INFO_LENGTH_32_BYTE];              ///< 
	char szModelName[GX_INFO_LENGTH_32_BYTE];               ///< 
	char szSN[GX_INFO_LENGTH_32_BYTE];                      ///< 
	char szDisplayName[GX_INFO_LENGTH_128_BYTE + 4];        ///< 
	char szDeviceID[GX_INFO_LENGTH_64_BYTE + 4];            ///< 
	char szUserID[GX_INFO_LENGTH_64_BYTE + 4];              ///< 
	GX_ACCESS_STATUS_CMD  accessStatus;                     ///< 
	GX_DEVICE_CLASS   deviceClass;                          ///< 
	char reserved[300];                                     ///< 
}GX_DEVICE_BASE_INFO;

typedef struct GX_OPEN_PARAM 
{
	char               *pszContent;        ///< 
	GX_OPEN_MODE_CMD   openMode;           ///< 
	GX_ACCESS_MODE_CMD accessMode;         ///< 
}GX_OPEN_PARAM;

typedef struct GX_FRAME_CALLBACK_PARAM
{
	void*               pUserParam;         ///< 
	GX_FRAME_STATUS     status;             ///< 
	const  void*        pImgBuf;            ///< 
	int32_t             nImgSize;           ///< 
	int32_t             nWidth;             ///< 
	int32_t             nHeight;            ///< 
	int32_t             nPixelFormat;       ///< 
	uint64_t            nFrameID;           ///< 
	uint64_t            nTimestamp;         ///< 
	int32_t             reserved[1];        ///< 
}GX_FRAME_CALLBACK_PARAM;

typedef struct GX_FRAME_DATA
{
	GX_FRAME_STATUS		nStatus;             ///< 
	void*				pImgBuf;             ///< 
	int32_t				nWidth;              ///< 
	int32_t				nHeight;             ///< 
	int32_t				nPixelFormat;        ///< 
	int32_t				nImgSize;            ///< 
	uint64_t			nFrameID;            ///< 
	uint64_t			nTimestamp;          ///< 
	int32_t				reserved[3];         ///< 
}GX_FRAME_DATA;


typedef struct GX_INT_RANGE
{
	int64_t nMin;                      ///< 
	int64_t nMax;                      ///< 
	int64_t nInc;                      ///< 
	int32_t reserved[8];               ///< 
}GX_INT_RANGE;

typedef struct GX_FLOAT_RANGE
{
	double  dMin;                           ///< 
	double  dMax;                           ///< 
	double  dInc;                           ///< 
	char    szUnit[GX_INFO_LENGTH_8_BYTE];  ///< 
	bool    bIncIsValid;                    ///< 
	int8_t  reserved[31];                   ///< 
}GX_FLOAT_RANGE;

typedef struct GX_ENUM_DESCRIPTION
{
	int64_t nValue;                               ///< 
	char    szSymbolic[GX_INFO_LENGTH_64_BYTE];   ///< 
	int32_t reserved[8];                          ///< 
}GX_ENUM_DESCRIPTION;


//----------------------------------------------------------------------------------
/**
\brief     
\param     pFrameData    
\return    void
*/
//----------------------------------------------------------------------------------
typedef void (GX_STDC* GXCaptureCallBack) (GX_FRAME_CALLBACK_PARAM *pFrameData);
//----------------------------------------------------------------------------------
/**
\brief     
\param     pUserParam    
\return    void
*/
//----------------------------------------------------------------------------------
typedef void (GX_STDC *GXDeviceOfflineCallBack) (void *pUserParam);
//----------------------------------------------------------------------------------
/**
\brief     
\param     nFeatureID    
\param     pUserParam    
\return    void
*/
//----------------------------------------------------------------------------------
typedef void (GX_STDC *GXFeatureCallBack) (GX_FEATURE_ID_CMD  nFeatureID , void *pUserParam);



#define GX_API GX_EXTC GX_STATUS GX_STDC

//------------------------------------------------------------------------
/**
\brief     
\attention 
\return    GX_STATUS_SUCCESS             
           GX_STATUS_NOT_FOUND_TL
		   Other status refer to GX_STATUS_LIST
		           
*/
//------------------------------------------------------------------------
GX_API GXInitLib();

//----------------------------------------------------------------------------------
/**
\brief     
\attention 
\return    GX_STATUS_SUCCESS            
           Other status refer to GX_STATUS_LIST   
*/
//----------------------------------------------------------------------------------
GX_API GXCloseLib();

//------------------------------------------------------------------------
/**
\brief       
\attention   
\param [out] pErrorCode    
\param [out] pszErrText    
\param [in,out] pSize      
\return GX_STATUS_SUCCESS                
        GX_STATUS_INVALID_PARAMETER      
	    GX_STATUS_NEED_MORE_BUFFER       
	    Other status refer to GX_STATUS_LIST
*/
//------------------------------------------------------------------------
GX_API GXGetLastError             (GX_STATUS *pErrorCode, char *pszErrText, size_t *pSize);

//----------------------------------------------------------------------------------
/**
\brief     
\attention 
\param     [out]punNumDevices 
\param     [in]unTimeOut      
\return    GX_STATUS_SUCCESS             
           GX_STATUS_NOT_INIT_API        
           GX_STATUS_INVALID_PARAMETER  
           Other status refer to GX_STATUS_LIST
*/
//----------------------------------------------------------------------------------
GX_API GXUpdateDeviceList         (uint32_t* punNumDevices, uint32_t nTimeOut);

//----------------------------------------------------------------------------------
/**
\brief    
\attention 
\param     [out]punNumDevices 
\param     [in]unTimeOut     
\return    GX_STATUS_SUCCESS             
           GX_STATUS_NOT_INIT_API       
           GX_STATUS_INVALID_PARAMETER  
           Other status refer to GX_STATUS_LIST
*/
//----------------------------------------------------------------------------------
GX_API GXUpdateAllDeviceList         (uint32_t* punNumDevices, uint32_t nTimeOut);

//----------------------------------------------------------------------------------
/**
\brief        
\attention    
\param [out] pDeviceInfo   
\param [in,out]pBufferSize 
\return    GX_STATUS_SUCCESS             
           GX_STATUS_NOT_INIT_API        
           GX_STATUS_INVALID_PARAMETER   
           Other status refer to GX_STATUS_LIST
*/
//----------------------------------------------------------------------------------
GX_API GXGetAllDeviceBaseInfo     (GX_DEVICE_BASE_INFO* pDeviceInfo, size_t* pBufferSize);

//----------------------------------------------------------------------------------
/**
\brief        
\attention    
\param [in]  nIndex  started from 1
\param [out] pstDeviceIPInfo   
\return    GX_STATUS_SUCCESS    
		   GX_STATUS_NOT_INIT_API        
           GX_STATUS_INVALID_PARAMETER   
           Other status refer to GX_STATUS_LIST
*/
//----------------------------------------------------------------------------------
GX_API GXGetDeviceIPInfo(uint32_t nIndex, GX_DEVICE_IP_INFO* pstDeviceIPInfo);

//----------------------------------------------------------------------------------
/**
\brief 
\param nDeviceIndex started from 1
\param phDevice 
\return Refer to GX_STATUS_LIST
*/
//----------------------------------------------------------------------------------
GX_API GXOpenDeviceByIndex        (uint32_t nDeviceIndex, GX_DEV_HANDLE* phDevice);   // Deprecated

//----------------------------------------------------------------------------------
/**
\brief     
\attention 
\param     [in]pOpenParam    
\param     [out]phDevice     
\return    GX_STATUS_SUCCESS             
           GX_STATUS_NOT_INIT_API        
           GX_STATUS_INVALID_PARAMETER  
		   GX_STATUS_NOT_FOUND_DEVICE    
		   GX_STATUS_INVALID_ACCESS      
           Other status refer to GX_STATUS_LIST
*/
//----------------------------------------------------------------------------------
GX_API GXOpenDevice               (GX_OPEN_PARAM* pOpenParam, GX_DEV_HANDLE* phDevice);

//----------------------------------------------------------------------------------
/**
\brief     
\attention 
\param     [in]hDevice 
\return    GX_STATUS_SUCCESS             
           GX_STATUS_NOT_INIT_API        
		   GX_STATUS_INVALID_HANDLE      
		   Other status refer to GX_STATUS_LIST
*/
//----------------------------------------------------------------------------------
GX_API GXCloseDevice              (GX_DEV_HANDLE hDevice);

//----------------------------------------------------------------------------------
/**
\brief     
\attention 
\param     [in]       hDevice                  
\param     [in]       pszIP                    
\param     [in, out]  pnIPLength               
\param     [in]       pnIPLength              
\param     [out]      pnIPLength              
\param     [in]       pszSubNetMask            
\param     [in, out]  pnSubNetMaskLength       
\param     [in]       pnSubNetMaskLength     
\param     [out]      pnSubNetMaskLength      
\param     [in]       pszDefaultGateWay        
\param     [in, out]  pnDefaultGateWayLength   
\param     [in]       pnDefaultGateWayLength 
\param     [out]      pnDefaultGateWayLength 
\return    GX_STATUS_SUCCESS             
		   GX_STATUS_NOT_INIT_API        
		   GX_STATUS_INVALID_PARAMETER  
		   Other status refer to GX_STATUS_LIST
*/
//----------------------------------------------------------------------------------
GX_API GXGetDevicePersistentIpAddress (GX_DEV_HANDLE  hDevice, 
									   char* pszIP, 
									   size_t *pnIPLength, 
									   char* pszSubNetMask, 
									   size_t *pnSubNetMaskLength, 
									   char* pszDefaultGateWay, 
									   size_t *pnDefaultGateWayLength);

//----------------------------------------------------------------------------------
/**
\brief     
\attention 
\param     [in]     hDevice              
\param     [in]     pszIP                
\param     [in]     pszSubNetMask        
\param     [in]     pszDefaultGateWay    
\return    GX_STATUS_SUCCESS            
           GX_STATUS_NOT_INIT_API        
		   GX_STATUS_INVALID_HANDLE      
		   Other status refer to GX_STATUS_LIST
*/
//----------------------------------------------------------------------------------
GX_API GXSetDevicePersistentIpAddress (GX_DEV_HANDLE  hDevice, 
									   const char* pszIP, 
									   const char* pszSubNetMask, 
									   const char* pszDefaultGateWay);

//----------------------------------------------------------------------------------
/**
\brief      
\attention  
\param [in]hDevice     
\param [in]featureID   
\param [out]pszName    
\param [in,out]pnSize  
\return    GX_STATUS_SUCCESS             
           GX_STATUS_NOT_INIT_API        
		   GX_STATUS_INVALID_HANDLE      
           GX_STATUS_INVALID_PARAMETER   
		   GX_STATUS_NEED_MORE_BUFFER    
           Other status refer to GX_STATUS_LIST
*/
//----------------------------------------------------------------------------------
GX_API GXGetFeatureName           (GX_DEV_HANDLE hDevice, GX_FEATURE_ID_CMD featureID, char* pszName, size_t* pnSize); 

//----------------------------------------------------------------------------------
/**
\brief      
\attention  
\param [in]hDevice   
\param [in]featureID 
\param [out]pbIsImplemented 
\return    GX_STATUS_SUCCESS            
           GX_STATUS_NOT_INIT_API       
		   GX_STATUS_INVALID_HANDLE      
		   GX_STATUS_INVALID_PARAMETER   
		   Other status refer to GX_STATUS_LIST
*/
//----------------------------------------------------------------------------------
GX_API GXIsImplemented		      (GX_DEV_HANDLE hDevice, GX_FEATURE_ID_CMD featureID, bool* pbIsImplemented);

//----------------------------------------------------------------------------------
/**
\brief      
\attention  
\param [in]hDevice 
\param [in]featureID 
\param [out]pbIsReadable 
\return    GX_STATUS_SUCCESS            
           GX_STATUS_NOT_INIT_API        
		   GX_STATUS_INVALID_HANDLE      
		   GX_STATUS_NOT_IMPLEMENTED     
		   GX_STATUS_INVALID_PARAMETER   
		   Other status refer to GX_STATUS_LIST
*/
//----------------------------------------------------------------------------------
GX_API GXIsReadable               (GX_DEV_HANDLE hDevice, GX_FEATURE_ID_CMD featureID, bool* pbIsReadable);

//----------------------------------------------------------------------------------
/**
\brief     
\attention  
\param [in]hDevice 
\param [in]featureID 
\param [out]pbIsWritable 
\return    GX_STATUS_SUCCESS            
           GX_STATUS_NOT_INIT_API        
		   GX_STATUS_INVALID_HANDLE      
		   GX_STATUS_NOT_IMPLEMENTED     
		   GX_STATUS_INVALID_PARAMETER   
		   Other status refer to GX_STATUS_LIST
*/
//----------------------------------------------------------------------------------
GX_API GXIsWritable               (GX_DEV_HANDLE hDevice, GX_FEATURE_ID_CMD featureID, bool* pbIsWritable);

//----------------------------------------------------------------------------------
/**
\brief      
\attention  
\param [in]hDevice    
\param [in]featureID  
\param [out]pIntRange
\return    GX_STATUS_SUCCESS             
           GX_STATUS_NOT_INIT_API        
		   GX_STATUS_INVALID_HANDLE      
		   GX_STATUS_NOT_IMPLEMENTED     
		   GX_STATUS_ERROR_TYPE          
		   GX_STATUS_INVALID_PARAMETER   
		   Other status refer to GX_STATUS_LIST
*/
//----------------------------------------------------------------------------------
GX_API GXGetIntRange		      (GX_DEV_HANDLE hDevice, GX_FEATURE_ID_CMD featureID, GX_INT_RANGE* pIntRange);

//----------------------------------------------------------------------------------
/**
\brief      
\attention 
\param [in]hDevice 
\param [in]featureID 
\param [out]pnValue 
\return    GX_STATUS_SUCCESS             
           GX_STATUS_NOT_INIT_API        
		   GX_STATUS_INVALID_HANDLE      
		   GX_STATUS_NOT_IMPLEMENTED     
		   GX_STATUS_ERROR_TYPE          
		   GX_STATUS_INVALID_PARAMETER   
		   GX_STATUS_INVALID_ACCESS      
		   Other status refer to GX_STATUS_LIST
*/
//----------------------------------------------------------------------------------
GX_API GXGetInt				      (GX_DEV_HANDLE hDevice, GX_FEATURE_ID_CMD featureID, int64_t* pnValue);

//----------------------------------------------------------------------------------
/**
\brief      
\attention  
\param [in]hDevice   
\param [in]featureID 
\param [in]pnValue  
\return    GX_STATUS_SUCCESS             
           GX_STATUS_NOT_INIT_API        
		   GX_STATUS_INVALID_HANDLE      
		   GX_STATUS_NOT_IMPLEMENTED    
		   GX_STATUS_ERROR_TYPE          
		   GX_STATUS_OUT_OF_RANGE        
		   GX_STATUS_INVALID_ACCESS     
           Other status refer to GX_STATUS_LIST
*/
//----------------------------------------------------------------------------------
GX_API GXSetInt				      (GX_DEV_HANDLE hDevice, GX_FEATURE_ID_CMD featureID, int64_t nValue);

//----------------------------------------------------------------------------------
/**
\brief      
\attention  
\param [in]hDevice 
\param [in]featureID
\param [out]pFloatRange
\return    GX_STATUS_SUCCESS             
           GX_STATUS_NOT_INIT_API        
		   GX_STATUS_INVALID_HANDLE      
		   GX_STATUS_NOT_IMPLEMENTED     
		   GX_STATUS_ERROR_TYPE          
		   GX_STATUS_INVALID_PARAMETER   
		   Other status refer to GX_STATUS_LIST
*/
//----------------------------------------------------------------------------------
GX_API GXGetFloatRange		      (GX_DEV_HANDLE hDevice, GX_FEATURE_ID_CMD featureID, GX_FLOAT_RANGE* pFloatRange);

//----------------------------------------------------------------------------------
/**
\brief      
\attention  
\param [in]hDevice   
\param [in]featureID 
\param [in]dValue    
\return    GX_STATUS_SUCCESS             
           GX_STATUS_NOT_INIT_API        
		   GX_STATUS_INVALID_HANDLE      
		   GX_STATUS_NOT_IMPLEMENTED     
		   GX_STATUS_ERROR_TYPE          
		   GX_STATUS_OUT_OF_RANGE        
		   GX_STATUS_INVALID_ACCESS      
		   Other status refer to GX_STATUS_LIST
*/
//----------------------------------------------------------------------------------
GX_API GXSetFloat                 (GX_DEV_HANDLE hDevice, GX_FEATURE_ID_CMD featureID, double dValue);

//----------------------------------------------------------------------------------
/**
\brief      
\attention  
\param [in]hDevice   
\param [in]featureID 
\param [out]pdValue  
\return    GX_STATUS_SUCCESS             
           GX_STATUS_NOT_INIT_API        
		   GX_STATUS_INVALID_HANDLE      
		   GX_STATUS_NOT_IMPLEMENTED     
		   GX_STATUS_ERROR_TYPE          
		   GX_STATUS_INVALID_PARAMETER   
		   GX_STATUS_INVALID_ACCESS      
		   Other status refer to GX_STATUS_LIST
*/
//----------------------------------------------------------------------------------
GX_API GXGetFloat                 (GX_DEV_HANDLE hDevice, GX_FEATURE_ID_CMD featureID, double* pdValue);

//----------------------------------------------------------------------------------
/**
\brief      
\attention  
\param [in]hDevice 
\param [in]featureID 
\param [out]pnEntryNums 
\return    GX_STATUS_SUCCESS             
           GX_STATUS_NOT_INIT_API        
		   GX_STATUS_INVALID_HANDLE     
		   GX_STATUS_NOT_IMPLEMENTED     
		   GX_STATUS_ERROR_TYPE          
		   GX_STATUS_INVALID_PARAMETER   
           Other status refer to GX_STATUS_LIST
*/
//----------------------------------------------------------------------------------
GX_API GXGetEnumEntryNums         (GX_DEV_HANDLE hDevice, GX_FEATURE_ID_CMD featureID, uint32_t* pnEntryNums);

//----------------------------------------------------------------------------------
/**
\brief      
\attention  
\param [in]hDevice   
\param [in]featureID 
\param [out]pEnumDescription 
\param [in,out]pBufferSize    
\return    GX_STATUS_SUCCESS            
           GX_STATUS_NOT_INIT_API       
		   GX_STATUS_INVALID_HANDLE     
		   GX_STATUS_NOT_IMPLEMENTED    
		   GX_STATUS_ERROR_TYPE         
		   GX_STATUS_INVALID_PARAMETER  
		   GX_STATUS_NEED_MORE_BUFFER    
           Other status refer to GX_STATUS_LIST
*/
//----------------------------------------------------------------------------------
GX_API GXGetEnumDescription       (GX_DEV_HANDLE hDevice, 
								   GX_FEATURE_ID_CMD featureID, 
								   GX_ENUM_DESCRIPTION* pEnumDescription,
								   size_t* pBufferSize);

//----------------------------------------------------------------------------------
/**
\brief      
\attention  
\param [in]hDevice 
\param [in]featureID 
\param [out]pnValue 
\return    GX_STATUS_SUCCESS             
           GX_STATUS_NOT_INIT_API        
		   GX_STATUS_INVALID_HANDLE      
		   GX_STATUS_NOT_IMPLEMENTED    
		   GX_STATUS_ERROR_TYPE          
		   GX_STATUS_INVALID_PARAMETER   
		   GX_STATUS_INVALID_ACCESS      
		   Other status refer to GX_STATUS_LIST
*/
//----------------------------------------------------------------------------------
GX_API GXGetEnum			      (GX_DEV_HANDLE hDevice, GX_FEATURE_ID_CMD featureID, int64_t* pnValue);

//----------------------------------------------------------------------------------
/**
\brief      
\attention  
\param [in]hDevice   
\param [in]featureID 
\param [in]pnValue   
\return    GX_STATUS_SUCCESS             
           GX_STATUS_NOT_INIT_API        
		   GX_STATUS_INVALID_HANDLE     
		   GX_STATUS_NOT_IMPLEMENTED    
		   GX_STATUS_ERROR_TYPE         
		   GX_STATUS_INVALID_PARAMETER   
		   GX_STATUS_INVALID_ACCESS     
		   Other status refer to GX_STATUS_LIST
*/
//----------------------------------------------------------------------------------
GX_API GXSetEnum			      (GX_DEV_HANDLE hDevice, GX_FEATURE_ID_CMD featureID, int64_t nValue);

//----------------------------------------------------------------------------------
/**
\brief      
\attention  
\param [in]hDevice 
\param [in]featureID 
\param [out]pbValue 
\return    GX_STATUS_SUCCESS             
           GX_STATUS_NOT_INIT_API        
		   GX_STATUS_INVALID_HANDLE      
		   GX_STATUS_NOT_IMPLEMENTED     
		   GX_STATUS_ERROR_TYPE          
		   GX_STATUS_INVALID_PARAMETER   
		   GX_STATUS_INVALID_ACCESS     
		   Other status refer to GX_STATUS_LIST
*/
//----------------------------------------------------------------------------------
GX_API GXGetBool			      (GX_DEV_HANDLE hDevice, GX_FEATURE_ID_CMD featureID, bool* pbValue);

//----------------------------------------------------------------------------------
/**
\brief      
\attention  
\param [in]hDevice   
\param [in]featureID 
\param [in]pbValue  
\return    GX_STATUS_SUCCESS             
           GX_STATUS_NOT_INIT_API       
		   GX_STATUS_INVALID_HANDLE      
		   GX_STATUS_NOT_IMPLEMENTED    
		   GX_STATUS_ERROR_TYPE          
		   GX_STATUS_INVALID_ACCESS      
		   Other status refer to GX_STATUS_LIST
*/
//----------------------------------------------------------------------------------
GX_API GXSetBool			      (GX_DEV_HANDLE hDevice, GX_FEATURE_ID_CMD featureID, bool bValue);

//----------------------------------------------------------------------------------
/**
\brief      
\attention  
\param [in]hDevice   
\param [in]featureID 
\param [out]pnSize   
\return    GX_STATUS_SUCCESS             
           GX_STATUS_NOT_INIT_API        
		   GX_STATUS_INVALID_HANDLE      
		   GX_STATUS_NOT_IMPLEMENTED     
		   GX_STATUS_ERROR_TYPE          
		   GX_STATUS_INVALID_PARAMETER   
		   Other status refer to GX_STATUS_LIST
*/
//----------------------------------------------------------------------------------
GX_API GXGetStringLength	      (GX_DEV_HANDLE hDevice, GX_FEATURE_ID_CMD featureID, size_t* pnSize);

//----------------------------------------------------------------------------------
/**
\brief     
\attention  
\param [in]hDevice   
\param [in]featureID 
\param [out]pnSize   
\return    GX_STATUS_SUCCESS             
           GX_STATUS_NOT_INIT_API        
		   GX_STATUS_INVALID_HANDLE     
		   GX_STATUS_NOT_IMPLEMENTED     
		   GX_STATUS_ERROR_TYPE         
		   GX_STATUS_INVALID_PARAMETER  
		   Other status refer to GX_STATUS_LIST
*/
//----------------------------------------------------------------------------------
GX_API GXGetStringMaxLength	      (GX_DEV_HANDLE hDevice, GX_FEATURE_ID_CMD featureID, size_t* pnSize);

//----------------------------------------------------------------------------------
/**
\brief      
\attention  
\param [in]hDevice 
\param [in]featureID 
\param [out]pszContent 
\param [in,out]pnSize 
\return    GX_STATUS_SUCCESS             
           GX_STATUS_NOT_INIT_API        
		   GX_STATUS_INVALID_HANDLE      
		   GX_STATUS_NOT_IMPLEMENTED     
		   GX_STATUS_ERROR_TYPE          
		   GX_STATUS_INVALID_PARAMETER   
		   GX_STATUS_INVALID_ACCESS      
		   GX_STATUS_NEED_MORE_BUFFER    
		   Other status refer to GX_STATUS_LIST
*/
//----------------------------------------------------------------------------------
GX_API GXGetString			      (GX_DEV_HANDLE hDevice, 
								   GX_FEATURE_ID_CMD featureID, 
								   char* pszContent, 
								   size_t* pnSize);

//----------------------------------------------------------------------------------
/**
\brief      
\attention  
\param [in]hDevice 
\param [in]featureID 
\param [in]pszContent 
\return    GX_STATUS_SUCCESS             
           GX_STATUS_NOT_INIT_API        
		   GX_STATUS_INVALID_HANDLE      
		   GX_STATUS_NOT_IMPLEMENTED     
		   GX_STATUS_ERROR_TYPE          
		   GX_STATUS_INVALID_PARAMETER   
		   GX_STATUS_OUT_OF_RANGE        
		   GX_STATUS_INVALID_ACCESS      
		   Other status refer to GX_STATUS_LIST
*/
//----------------------------------------------------------------------------------
GX_API GXSetString			      (GX_DEV_HANDLE hDevice, GX_FEATURE_ID_CMD featureID, char* pszContent);

//----------------------------------------------------------------------------------
/**
\brief      
\attention  
\param [in]hDevice   
\param [in]featureID 
\param [out]pnSize  
\return    GX_STATUS_SUCCESS            
           GX_STATUS_NOT_INIT_API        
		   GX_STATUS_INVALID_HANDLE      
		   GX_STATUS_NOT_IMPLEMENTED     
		   GX_STATUS_ERROR_TYPE         
		   GX_STATUS_INVALID_PARAMETER  
		   Other status refer to GX_STATUS_LIST
*/
//----------------------------------------------------------------------------------
GX_API GXGetBufferLength	      (GX_DEV_HANDLE hDevice, GX_FEATURE_ID_CMD featureID, size_t* pnSize);

//----------------------------------------------------------------------------------
/**
\brief      
\attention  
\param [in]hDevice 
\param [in]featureID 
\param [out]pBuffer 
\param [in,out]pnSize 
\return    GX_STATUS_SUCCESS             
           GX_STATUS_NOT_INIT_API        
		   GX_STATUS_INVALID_HANDLE      
		   GX_STATUS_NOT_IMPLEMENTED     
		   GX_STATUS_ERROR_TYPE          
		   GX_STATUS_INVALID_PARAMETER   
		   GX_STATUS_INVALID_ACCESS      
		   GX_STATUS_NEED_MORE_BUFFER    
		   Other status refer to GX_STATUS_LIST
*/
//----------------------------------------------------------------------------------
GX_API GXGetBuffer			      (GX_DEV_HANDLE hDevice, 
								   GX_FEATURE_ID_CMD featureID, 
								   uint8_t* pBuffer, 
								   size_t* pnSize);

//----------------------------------------------------------------------------------
/**
\brief      
\attention  
\param [in]hDevice   
\param [in]featureID
\param [in]pBuffer   
\param [in]nSize     
\return    GX_STATUS_SUCCESS             
           GX_STATUS_NOT_INIT_API        
		   GX_STATUS_INVALID_HANDLE      
		   GX_STATUS_NOT_IMPLEMENTED     
		   GX_STATUS_ERROR_TYPE          
		   GX_STATUS_INVALID_PARAMETER   
		   GX_STATUS_OUT_OF_RANGE        
		   GX_STATUS_INVALID_ACCESS      
		   Other status refer to GX_STATUS_LIST
*/
//----------------------------------------------------------------------------------
GX_API GXSetBuffer			      (GX_DEV_HANDLE hDevice, 
								   GX_FEATURE_ID_CMD featureID, 
								   uint8_t* pBuffer, 
								   size_t nSize);

//----------------------------------------------------------------------------------
/**
\brief      
\attention 
\param [in]hDevice    
\param [in]featureID  
\return    GX_STATUS_SUCCESS             
           GX_STATUS_NOT_INIT_API        
		   GX_STATUS_INVALID_HANDLE     
		   GX_STATUS_NOT_IMPLEMENTED    
		   GX_STATUS_ERROR_TYPE          
		   GX_STATUS_INVALID_ACCESS     
		   Other status refer to GX_STATUS_LIST
*/
//----------------------------------------------------------------------------------
GX_API GXSendCommand		      (GX_DEV_HANDLE hDevice, GX_FEATURE_ID_CMD featureID);

//----------------------------------------------------------------------------------
/**
\brief      
\attention  
\param [in]hDevice     
\param [in]pUserParam  
\param [in]callBackFun 
\return    GX_STATUS_SUCCESS             
           GX_STATUS_NOT_INIT_API        
		   GX_STATUS_INVALID_HANDLE      
		   GX_STATUS_INVALID_PARAMETER  
		   GX_STATUS_INVALID_CALL        
		   Other status refer to GX_STATUS_LIST
*/
//----------------------------------------------------------------------------------
GX_API GXRegisterCaptureCallback  (GX_DEV_HANDLE hDevice, void *pUserParam, GXCaptureCallBack callBackFun);

//----------------------------------------------------------------------------------
/**
\brief      
\attention  
\param [in]hDevice
\return    GX_STATUS_SUCCESS             
           GX_STATUS_NOT_INIT_API       
		   GX_STATUS_INVALID_HANDLE     
		   GX_STATUS_INVALID_CALL        
		   Other status refer to GX_STATUS_LIST
*/
//----------------------------------------------------------------------------------
GX_API GXUnregisterCaptureCallback(GX_DEV_HANDLE hDevice);

//----------------------------------------------------------------------------------
/**
\brief      
\attention  
\param [in]hDevice        
\param [in,out]pFrameData 
\param [in]nTimeout       
\return    GX_STATUS_SUCCESS             
           GX_STATUS_NOT_INIT_API        
		   GX_STATUS_INVALID_HANDLE      
		   GX_STATUS_INVALID_CALL       
		   GX_STATUS_INVALID_PARAMETER   
		   GX_STATUS_NEED_MORE_BUFFER   
		   Other status refer to GX_STATUS_LIST
*/
//----------------------------------------------------------------------------------
GX_API GXGetImage(GX_DEV_HANDLE hDevice, GX_FRAME_DATA *pFrameData, uint32_t nTimeout);

//----------------------------------------------------------------------------------
/**
\brief      
\attention  
\param     [in]hDevice        
\return    GX_STATUS_SUCCESS             
           GX_STATUS_NOT_INIT_API       
		   GX_STATUS_INVALID_HANDLE      
		   Other status refer to GX_STATUS_LIST
*/
//----------------------------------------------------------------------------------
GX_API GXFlushQueue(GX_DEV_HANDLE hDevice);

//----------------------------------------------------------------------------------
/**
\brief      
\attention  
\param [in]hDevice     
\param [in]pUserParam  
\param [in]callBackFun 
\param [in]eventID     
\return    GX_STATUS_SUCCESS             
           GX_STATUS_NOT_INIT_API        
		   GX_STATUS_INVALID_HANDLE      
		   GX_STATUS_INVALID_PARAMETER   
		   Other status refer to GX_STATUS_LIST
*/
//----------------------------------------------------------------------------------
GX_API GXRegisterDeviceOfflineCallback    (GX_DEV_HANDLE hDevice, 
										   void* pUserParam, 
										   GXDeviceOfflineCallBack callBackFun, 
										   GX_EVENT_CALLBACK_HANDLE *pHCallBack);

//----------------------------------------------------------------------------------
/**
\brief      
\attention  
\param [in]hDevice    
\param [in]eventID    
\return    GX_STATUS_SUCCESS             
           GX_STATUS_NOT_INIT_API        
		   GX_STATUS_INVALID_HANDLE      
		   GX_STATUS_INVALID_CALL        
		   GX_STATUS_INVALID_PARAMETER   
		   Other status refer to GX_STATUS_LIST
*/
//----------------------------------------------------------------------------------
GX_API GXUnregisterDeviceOfflineCallback  (GX_DEV_HANDLE hDevice, GX_EVENT_CALLBACK_HANDLE  hCallBack);

//----------------------------------------------------------------------------------
/**
\brief      
\attention  
\param     [in]hDevice       
\return    GX_STATUS_SUCCESS             
           GX_STATUS_NOT_INIT_API       
		   GX_STATUS_INVALID_HANDLE      
		   Other status refer to GX_STATUS_LIST
*/
//----------------------------------------------------------------------------------
GX_API GXFlushEvent               (GX_DEV_HANDLE hDevice);

//----------------------------------------------------------------------------------
/**
\brief      
\param     [in]hDevice        
\param     [in]pnEventNum     
\return    GX_STATUS_SUCCESS             
		   GX_STATUS_NOT_INIT_API       
           GX_STATUS_INVALID_HANDLE      
           GX_STATUS_INVALID_PARAMETER   
           Other status refer to GX_STATUS_LIST
*/
//----------------------------------------------------------------------------------
GX_API GXGetEventNumInQueue       (GX_DEV_HANDLE hDevice, uint32_t *pnEventNum);

//----------------------------------------------------------------------------------
/**
\brief     
\attention  
\param [in]hDevice    
\param [in]pUserParam  
\param [in]callBackFun 
\param [in]featureID  
\param [out]pHCallBack  
\return    GX_STATUS_SUCCESS             
           GX_STATUS_NOT_INIT_API        
		   GX_STATUS_INVALID_HANDLE      
		   GX_STATUS_INVALID_PARAMETER   
		   Other status refer to GX_STATUS_LIST
*/
//----------------------------------------------------------------------------------
GX_API GXRegisterFeatureCallback  (GX_DEV_HANDLE hDevice, 
								   void* pUserParam, 
								   GXFeatureCallBack  callBackFun, 
								   GX_FEATURE_ID_CMD  featureID,
								   GX_FEATURE_CALLBACK_HANDLE *pHCallBack);

//----------------------------------------------------------------------------------
/**
\brief      
\attention  
\param [in]hDevice     
\param [in]featureID   
\param [out]pHCallBack  
\return    GX_STATUS_SUCCESS            
           GX_STATUS_NOT_INIT_API       
		   GX_STATUS_INVALID_HANDLE     
		   Other status refer to GX_STATUS_LIST
*/
//----------------------------------------------------------------------------------
GX_API GXUnregisterFeatureCallback(GX_DEV_HANDLE  hDevice, GX_FEATURE_ID_CMD featureID, GX_FEATURE_CALLBACK_HANDLE  hCallBack);

//----------------------------------------------------------------------------------
/**
\brief      
\param [in]hDevice        
\param [in]pszFilePath    
\return     GX_STATUS_SUCCESS             
			GX_STATUS_NOT_INIT_API        
			GX_STATUS_INVALID_HANDLE      
			Other status refer to GX_STATUS_LIST

*/
//----------------------------------------------------------------------------------
GX_API GXExportConfigFile (GX_DEV_HANDLE hDevice, const char * pszFilePath);

//----------------------------------------------------------------------------------
/**
\brief      
\param [in]hDevice         
\param [in]pszFilePath    
\param [in]bVerify         
\return     GX_STATUS_SUCCESS             
			GX_STATUS_NOT_INIT_API       
			GX_STATUS_INVALID_HANDLE      
			Other status refer to GX_STATUS_LIST

*/
//----------------------------------------------------------------------------------
GX_API GXImportConfigFile(GX_DEV_HANDLE hDevice, const char * pszFilePath, bool bVerify = false);

#endif  //GX_GALAXY_H
