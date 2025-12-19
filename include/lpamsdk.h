/*
 * lpamsdk.h
 *
 *      Author: Laser Pulse - Guannan Guo
 * 		Data: Jan 4 2024 
 */

#ifndef LPAMSDK_H
#define LPAMSDK_H

#ifndef LPAMSDK_API
	#define LPAMSDK_API
#endif

#ifdef WIN32
	#ifdef COMPILE_LIBRARY_FLAG
		#define LPAMSDK_API __declspec(dllexport)
	#else
		#define LPAMSDK_API __declspec(dllimport)
	#endif
#endif

#ifdef __cplusplus
extern "C"
{
#endif



typedef enum
{
	/** USB interface */
	USB_IFC			= 1 << 0,

	/** Bluetooth interface */
	BLUETOOTH_IFC	= 1 << 1,

	/** Ethernet interface */
	ETHERNET_IFC	= 1 << 2,

	/** Any interface */
	ANY_IFC = USB_IFC | BLUETOOTH_IFC | ETHERNET_IFC

}DaqDeviceInterface;

/** \brief A structure that defines a particular AMS device, usually obtained using lpAMSGetDeviceInventory().
 *
 * The struct contains fields with the product name, ID, and interface.
 */
struct DaqDeviceDescriptor
{
	/** The generic (unqualified) product name of the device referenced by the DaqDeviceDescriptor */
	char productName[64];

	/**The numeric string indicating the product type referenced by the DaqDeviceDescriptor.*/
	unsigned int productId;

	/** The enumeration indicating the type of interface in use by the device referenced by the DaqDeviceDescriptor. */
	DaqDeviceInterface devInterface;

	/** Similar to \p productname, but may contain additional information. */
	char devString[64];

	/** A string that uniquely identifies a specific device, usually with a serial number or MAC address. */
	char uniqueId[64];

	/** Reserved for future use */
	char reserved[512];
};

/** \brief LPAMSDK error codes */
typedef enum
{
	/** No error has occurred */
	ERR_NO_ERROR 					= 0,

	/** Unhandled internal exception */
	ERR_UNHANDLED_EXCEPTION 		= 1,

	/** Invalid device handle */
	ERR_BAD_DEV_HANDLE 				= 2,

	/** This function cannot be used with this device */
	ERR_BAD_DEV_TYPE 				= 3,

	/** Insufficient permission to access this device */
	ERR_USB_DEV_NO_PERMISSION		= 4,

	/** USB interface is already claimed */
	ERR_USB_INTERFACE_CLAIMED 		= 5,

	/** Device not found */
	ERR_DEV_NOT_FOUND 				= 6,

	/** Device not connected or connection lost */
	ERR_DEV_NOT_CONNECTED 			= 7,

	/** Device no longer responding */
	ERR_DEAD_DEV 					= 8,

	/** Buffer too small for operation */
	ERR_BAD_BUFFER_SIZE 			= 9,

	/** Invalid buffer */
	ERR_BAD_BUFFER 					= 10,

	/** Invalid memory type */
	ERR_BAD_MEM_TYPE 				= 11,

	/** Invalid memory region */
	ERR_BAD_MEM_REGION 				= 12,

	/** Invalid range */
	ERR_BAD_RANGE					= 13,

	/** Invalid analog input channel specified */
	ERR_BAD_AI_CHAN					= 14,

	/** Invalid input mode specified */
	ERR_BAD_INPUT_MODE				= 15,

	/** A background process is already in progress */
	ERR_ALREADY_ACTIVE				= 16,

	/** Invalid trigger type specified */
	ERR_BAD_TRIG_TYPE				= 17,

	/** FIFO overrun, data was not transferred from device fast enough */
	ERR_OVERRUN						= 18,

	/** FIFO underrun, data was not transferred to device fast enough */
	ERR_UNDERRUN					= 19,

	/** Operation timed out */
	ERR_TIMEDOUT					= 20,

	/** Invalid option specified */
	ERR_BAD_OPTION					= 21,

	/** Invalid sampling rate specified */
	ERR_BAD_RATE					= 22,

	/** Sample count cannot be greater than FIFO size for BURSTIO scans */
	ERR_BAD_BURSTIO_COUNT			= 23,

	/** Configuration not supported */
	ERR_CONFIG_NOT_SUPPORTED		= 24,

	/** Invalid configuration value */
	ERR_BAD_CONFIG_VAL				= 25,

	/** Invalid analog input channel type specified */
	ERR_BAD_AI_CHAN_TYPE			= 26,

	/** ADC overrun occurred */
	ERR_ADC_OVERRUN					= 27,

	/** Invalid thermocouple type specified */
	ERR_BAD_TC_TYPE					= 28,

	/** Invalid unit specified */
	ERR_BAD_UNIT					= 29,

	/** Invalid queue size */
	ERR_BAD_QUEUE_SIZE				= 30,

	/** Invalid config item specified */
	ERR_BAD_CONFIG_ITEM				= 31,

	/** Invalid info item specified */
	ERR_BAD_INFO_ITEM				= 32,

	/** Invalid flag specified */
	ERR_BAD_FLAG					= 33,

	/** Invalid sample count specified */
	ERR_BAD_SAMPLE_COUNT			= 34,

	/** Internal error */
	ERR_INTERNAL					= 35,

	/** Invalid coupling mode */
	ERR_BAD_COUPLING_MODE			= 36,

	/** Invalid sensor sensitivity */
	ERR_BAD_SENSOR_SENSITIVITY		= 37,

	/** Invalid IEPE mode */
	ERR_BAD_IEPE_MODE				= 38,

	/** Invalid channel queue specified */
	ERR_BAD_AI_CHAN_QUEUE			= 39,

	/** Invalid gain queue specified */
	ERR_BAD_AI_GAIN_QUEUE			= 40,

	/** Invalid mode queue specified */
	ERR_BAD_AI_MODE_QUEUE			= 41,

	/** FPGA file not found */
	ERR_FPGA_FILE_NOT_FOUND			= 42,

	/** Unable to read FPGA file */
	ERR_UNABLE_TO_READ_FPGA_FILE	= 43,

	/** FPGA not loaded */
	ERR_NO_FPGA						= 44,

	/** Invalid argument */
	ERR_BAD_ARG						= 45,

	/** Minimum slope value reached */
	ERR_MIN_SLOPE_VAL_REACHED		= 46,

	/** Maximum slope value reached */
	ERR_MAX_SLOPE_VAL_REACHED		= 47,

	/** Minimum offset value reached */
	ERR_MIN_OFFSET_VAL_REACHED		= 48,

	/** Maximum offset value reached */
	ERR_MAX_OFFSET_VAL_REACHED		= 49,

	/** Invalid port type specified */
	ERR_BAD_PORT_TYPE				= 50,

	/** Digital I/O is configured incorrectly */
	ERR_WRONG_DIG_CONFIG			= 51,

	/** Invalid bit number */
	ERR_BAD_BIT_NUM					= 52,

	/** Invalid port value specified */
	ERR_BAD_PORT_VAL				= 53,

	/** Invalid re-trigger count */
	ERR_BAD_RETRIG_COUNT			= 54,

	/** Invalid analog output channel specified */
	ERR_BAD_AO_CHAN					= 55,

	/** Invalid D/A output value specified */
	ERR_BAD_DA_VAL					= 56,

	/** Invalid timer specified */
	ERR_BAD_TMR						= 57,

	/** Invalid frequency specified */
	ERR_BAD_FREQUENCY				= 58,

	/** Invalid duty cycle specified */
	ERR_BAD_DUTY_CYCLE				= 59,

	/** Invalid initial delay specified */
	ERR_BAD_INITIAL_DELAY			= 60,

	/** Invalid counter specified */
	ERR_BAD_CTR						= 61,

	/** Invalid counter value specified */
	ERR_BAD_CTR_VAL					= 62,

	/** Invalid DAQ input channel type specified */
	ERR_BAD_DAQI_CHAN_TYPE			= 63,

	/** Invalid number of channels specified */
	ERR_BAD_NUM_CHANS				= 64,

	/** Invalid counter register specified */
	ERR_BAD_CTR_REG					= 65,

	/** Invalid counter measurement type specified */
	ERR_BAD_CTR_MEASURE_TYPE		= 66,

	/** Invalid counter measurement mode specified */
	ERR_BAD_CTR_MEASURE_MODE		= 67,

	/** Invalid debounce time specified */
	ERR_BAD_DEBOUNCE_TIME			= 68,

	/** Invalid debounce mode specified */
	ERR_BAD_DEBOUNCE_MODE			= 69,

	/** Invalid edge detection mode specified */
	ERR_BAD_EDGE_DETECTION			= 70,

	/** Invalid tick size specified */
	ERR_BAD_TICK_SIZE				= 71,

	/** Invalid DAQ output channel type specified */
	ERR_BAD_DAQO_CHAN_TYPE			= 72,

	/** No connection established */
	ERR_NO_CONNECTION_ESTABLISHED	= 73,

	/** Invalid event type specified */
	ERR_BAD_EVENT_TYPE				= 74,

	/** An event handler has already been enabled for this event type */
	ERR_EVENT_ALREADY_ENABLED		= 75,

	/** Invalid event parameter specified */
	ERR_BAD_EVENT_PARAMETER			= 76,

	/** Invalid callback function specified */
	ERR_BAD_CALLBACK_FUCNTION		= 77,

	/** Invalid memory address */
	ERR_BAD_MEM_ADDRESS				= 78,

	/** Memory access denied */
	ERR_MEM_ACCESS_DENIED			= 79,

	/** Device is not available at time of request */
	ERR_DEV_UNAVAILABLE				= 80,

	/** Re-trigger option is not supported for the specified trigger type */
	ERR_BAD_RETRIG_TRIG_TYPE		= 81,

	/** This function cannot be used with this version of the device */
	ERR_BAD_DEV_VER 				= 82,

	/** This digital operation is not supported on the specified port */
	ERR_BAD_DIG_OPERATION			= 83,

	/** Invalid digital port index specified */
	ERR_BAD_PORT_INDEX				= 84,

	/** Temperature input has open connection */
	ERR_OPEN_CONNECTION				= 85,

	/** Device is not ready to send data */
	ERR_DEV_NOT_READY				= 86,

	/** Pacer overrun, external clock rate too fast. */
	ERR_PACER_OVERRUN				= 87,

	/** Invalid trigger channel specified */
	ERR_BAD_TRIG_CHANNEL			= 88,

	/** Invalid trigger level specified */
	ERR_BAD_TRIG_LEVEL				= 89,

	/** Invalid channel order */
	ERR_BAD_CHAN_ORDER				= 90,

	/** Temperature input is out of range */
	ERR_TEMP_OUT_OF_RANGE			= 91,

	/** Trigger threshold is out of range */
	ERR_TRIG_THRESHOLD_OUT_OF_RANGE	= 92,

	/** Incompatible firmware version, firmware update required */
	ERR_INCOMPATIBLE_FIRMWARE 		= 93,

	/** Specified network interface is not available or disconnected */
	ERR_BAD_NET_IFC 				= 94,

	/** Invalid host specified */
	ERR_BAD_NET_HOST 				= 95,

	/** Invalid port specified */
	ERR_BAD_NET_PORT 				= 96,

	/** Network interface used to obtain the device descriptor not available or disconnected */
	ERR_NET_IFC_UNAVAILABLE			= 97,

	/** Network connection failed */
	ERR_NET_CONNECTION_FAILED		= 98,

	/** Invalid connection code */
	ERR_BAD_CONNECTION_CODE			= 99,

	/** Connection code ignored */
	ERR_CONNECTION_CODE_IGNORED		= 100,

	/** Network device already in use */
	ERR_NET_DEV_IN_USE				= 101,

	/** Invalid network frame  */
	ERR_BAD_NET_FRAME				= 102,

	/** Network device did not respond within expected time */
	ERR_NET_TIMEOUT					= 103,

	/** Data socket connection failed */
	ERR_DATA_SOCKET_CONNECTION_FAILED = 104,

	/** One or more bits on the specified port are used for alarm */
	ERR_PORT_USED_FOR_ALARM 		= 105,

	/** The specified bit is used for alarm */
	ERR_BIT_USED_FOR_ALARM 			= 106,

	/** Common-mode voltage range exceeded */
	ERR_CMR_EXCEEDED 				= 107,

	/** Network buffer overrun, data was not transferred from buffer fast enough */
	ERR_NET_BUFFER_OVERRUN 			= 108,

	/** Invalid network buffer */
	ERR_BAD_NET_BUFFER 				= 109
} UlError;

/** \brief A structure containing information about the progress of the specified scan operation.
 *
 * The struct contains fields for the current and total scan count and index value.
 */
struct TransferStatus
{
	/** The number of samples per channel transferred since the scan started. This is the same as \p currentTotalCount for single channel scans. */
	unsigned long long currentScanCount;

	/** The total number of samples transferred since the scan started. This is the same as \p currentScanCount
	 * multiplied by the number of channels in the scan. */
	unsigned long long currentTotalCount;

	/** This marks the location in the buffer where the last scan of data values are stored.
	 * For continuous scans, this value increments up to (buffer size - number of channels) and restarts from 0. */
	long long currentIndex;

	/** Reserved for future use */
	char reserved[64];
};

/** \brief Scan status */
typedef enum
{
	/** Scan is idle */
	SS_IDLE = 0,

	/** Scan is running */
	SS_RUNNING = 1
}ScanStatus;

/** \brief A structure containing information about the progress of the specified scan operation. */
typedef struct 	TransferStatus TransferStatus;

/** \brief A structure containing information about AMS device. */
typedef struct 	DaqDeviceDescriptor LPAMSDeviceDescriptor;

/**
 * \brief The AMS device
 */
typedef long long LPAMSDeviceHandle;

typedef UlError LPAMSError;

/**
 * \brief Get the list of LPAMS devices available to the system.
 * @param devDescriptors[] an array of LPAMSDeviceDescriptor structs, each of which contains fields specifying
 * information about the AMS device.
 * @param numDescriptors the size of the array. If the size is not correct, the required size is returned.
 * @return The LPAMSDK error code.
 */
LPAMSDK_API LPAMSError lpAMSGetDeviceInventory(LPAMSDeviceDescriptor devDescriptors[], unsigned int* numDescriptors);

/**
 * Create a device object for the AMS device specified by the descriptor.
 * @param devDescriptor LPAMSDeviceDescriptor struct containing fields that describe the device
 * @return The device handle.
 */
LPAMSDK_API LPAMSDeviceHandle lpAMSCreateDevice(LPAMSDeviceDescriptor devDescriptor);

/**
 * Establish a connection to a physical AMS device.
 * @param devHandle the handle to the AMS device
 * @return The LPAMSDK error code.
 */
LPAMSDK_API LPAMSError lpConnectAMSDevice(LPAMSDeviceHandle devHandle);

/**
 * Get AMS device SN.
 * @param devHandle the handle to the AMS device
 * @param serial the SN to the AMS device
 * @return The LPAMSDK error code.
 */
LPAMSDK_API LPAMSError lpGetAMSDeviceSN(LPAMSDeviceHandle devHandle, int* serial);

/**
 * Set gains for the 3 channels in AMS device.
 * @param devHandle the handle to the AMS device
 * @param ch1Gain Gain Setting for channel 1
 * @param ch2Gain Gain Setting for channel 2
 * @param ch3Gain Gain Setting for channel 3
 * @return The LPAMSDK error code.
 */
LPAMSDK_API LPAMSError lpAMSAInGain(LPAMSDeviceHandle devHandle, int ch1Gain, int ch2Gain, int ch3Gain);

/**
 * Get gains for the 3 channels in AMS device.
 * @param devHandle the handle to the AMS device
 * @param ch1Gain Gain Setting for channel 1
 * @param ch2Gain Gain Setting for channel 2
 * @param ch3Gain Gain Setting for channel 3
 * @return The LPAMSDK error code.
 */
LPAMSDK_API LPAMSError lpAMSAInReadGain(LPAMSDeviceHandle devHandle, int* ch1Gain, int* ch2Gain, int* ch3Gain);

/**
 * Scans 4 A/D channels, and stores the samples in an array.
 * @param devHandle the handle to the AMS device
 * @param data[] pointer to the buffer to receive the data array
 * @return The LPAMSDK error code.
 */
LPAMSDK_API LPAMSError lpAMSAInScan(LPAMSDeviceHandle devHandle, double data[]);

/**
 * Returns the status, count, and index of an A/D scan operation.
 * @param devHandle the handle to the AMS device
 * @param status the status of the background operation (idle or running)
 * @param xferStatus a TransferStatus struct containing fields that return the current sample count, scan count, and buffer index
 * for the specified input scan operation
 * @return The LPAMSDK error code.
 */
LPAMSDK_API LPAMSError lpAMSAInScanStatus(LPAMSDeviceHandle devHandle, ScanStatus* status, TransferStatus* xferStatus);

/**
 * Stops the analog input operation currently running.
 * @param devHandle the handle to the AMS device
 * @return The LPAMSDK error code.
 */
LPAMSDK_API LPAMSError lpAMSAInScanStop(LPAMSDeviceHandle devHandle);

/**
 * Disconnect from a device.
 * @param devHandle the handle to the AMS device
 * @return The LPAMSDK error code.
 */
LPAMSDK_API LPAMSError lpDisconnectAMSDevice(LPAMSDeviceHandle devHandle);

/**
 * Remove a device, and release all resources associated with that device.
 * @param devHandle the handle to the AMS device
 * @return The LPAMSDK error code.
 */
LPAMSDK_API LPAMSError lpReleaseAMSDevice(LPAMSDeviceHandle devHandle);
#ifdef __cplusplus
}
#endif 
#endif /* LPAMSDK_H */