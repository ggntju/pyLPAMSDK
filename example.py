#!/usr/bin/env python3
"""
Example script for using the LPAMSDK Python wrapper.
"""

import sys
import os
import ctypes
import time

# Add the current directory to the path so we can import lpamsdk
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))

import lpamsdk as lp

def main():
    """Main function to demonstrate LPAMSDK usage."""
    print("LPAMSDK Python Wrapper Example")
    print("=" * 40)

    # Step 1: Get device inventory
    print("\n1. Getting device inventory...")

    DeviceArray = lp.LPAMSDeviceDescriptor * 1
    dev_descriptors = DeviceArray()
    
    # First get the number of devices
    num_devices = ctypes.c_uint(1)
    err = lp.lpAMSGetDeviceInventory(dev_descriptors, ctypes.byref(num_devices))
    
    if err != lp.LPAMSError.ERR_NO_ERROR:
        print(f"Error getting device count: {err}")
        return 1
    
    if num_devices.value == 0:
        print("No devices found. Make sure your device is connected.")
        return 1
    
    print(f"Found {num_devices.value} device(s)")
    
    # Now get the actual device information
    DeviceArray = lp.LPAMSDeviceDescriptor * num_devices.value
    dev_descriptors = DeviceArray()
    
    err = lp.lpAMSGetDeviceInventory(dev_descriptors, ctypes.byref(num_devices))
    
    if err != lp.LPAMSError.ERR_NO_ERROR:
        print(f"Error getting device inventory: {err}")
        return 1
    
    print("Device details:")
    for i in range(num_devices.value):
        dev = dev_descriptors[i]
        print(f"\nDevice {i+1}:")
        print(f"  Product Name: {dev.productName.decode('utf-8')}")
        print(f"  Product ID: {dev.productId}")
        print(f"  Interface: {dev.devInterface}")
        print(f"  Device String: {dev.devString.decode('utf-8')}")

    # Step 2: Create device object
    print("\n2. Creating device object...")
    dev_handle = lp.lpAMSCreateDevice(dev_descriptors[0])
    if not dev_handle:
        print("Error creating device object")
        return 1
    print(f"Device handle created: {dev_handle}")

    # Step 3: Connect to device
    print("\n3. Connecting to device...")
    err = lp.lpConnectAMSDevice(dev_handle)
    if err != lp.LPAMSError.ERR_NO_ERROR:
        print(f"Error connecting to device: {err}")
        return 1
    print("Connected to device successfully!")

    # Step 4: Read current gains
    print("\n4. Reading current gains...")
    ch1_gain = ctypes.c_int()
    ch2_gain = ctypes.c_int()
    ch3_gain = ctypes.c_int()
    err = lp.lpAMSAInReadGain(dev_handle, ctypes.byref(ch1_gain), ctypes.byref(ch2_gain), ctypes.byref(ch3_gain))
    if err != lp.LPAMSError.ERR_NO_ERROR:
        print(f"Error reading gains: {err}")
        return 1
    print(f"Current gains - Ch1: {ch1_gain.value}, Ch2: {ch2_gain.value}, Ch3: {ch3_gain.value}")

    # Step 5: Set new gains (example values)
    print("\n5. Setting new gains...")
    new_gains = (2, 3, 4)
    err = lp.lpAMSAInGain(dev_handle, *new_gains)
    if err != lp.LPAMSError.ERR_NO_ERROR:
        print(f"Error setting gains: {err}")
        return 1
    print(f"Set gains to - Ch1: {new_gains[0]}, Ch2: {new_gains[1]}, Ch3: {new_gains[2]}")

    # Step 6: Verify new gains
    print("\n6. Verifying new gains...")
    gains = (ctypes.c_int(), ctypes.c_int(), ctypes.c_int())
    err = lp.lpAMSAInReadGain(dev_handle, (gains[0]), (gains[1]), (gains[2]))
    if err != lp.LPAMSError.ERR_NO_ERROR:
        print(f"Error reading gains: {err}")
        return 1
    print(f"New gains - Ch1: {gains[0]}, Ch2: {gains[1]}, Ch3: {gains[2]}")

    # Step 7: Perform a scan
    print("\n7. Performing a scan...")
    # bufferSize must be fixed as this value, DO NOT CHANGE IT
    bufferSize = 5000000
    # Create a buffer to store 4 channels of scan data
    scan_data = (ctypes.c_double * bufferSize)()
    err = lp.lpAMSAInScan(dev_handle, scan_data)
    if err != lp.LPAMSError.ERR_NO_ERROR:
        print(f"Error performing scan: {err}")
        return 1
    # print(f"Scan data (4 channels): {list(scan_data)}")

    # Step 8: Get scan status
    print("\n8. Getting scan status...")
    status = ctypes.c_int()  # ScanStatus enum
    xfer_status = lp.TransferStatus()
    err = lp.lpAMSAInScanStatus(dev_handle, ctypes.byref(status), ctypes.byref(xfer_status))
    if err != lp.LPAMSError.ERR_NO_ERROR:
        print(f"Error getting scan status: {err}")
        return 1
    
    status_str = "Running" if status.value == lp.ScanStatus.SS_RUNNING else "Idle"
    print(f"Scan status: {status_str}")
    # print(f"Current scan count: {xfer_status.currentScanCount}")
    # print(f"Current total count: {xfer_status.currentTotalCount}")
    # print(f"Current index: {xfer_status.currentIndex}")

    count = 0
    limit = 100000 * 10
    pIndex = 0
    cIndex = 0
    cycleCount = 0

    data_container_0 = []
    data_container_1 = []
    data_container_2 = []
    data_container_3 = []

    start = time.time()
    print("Start running")

    while(status.value == lp.ScanStatus.SS_RUNNING and err == lp.LPAMSError.ERR_NO_ERROR and count < limit):
        if(cycleCount == 400):
            cycleCount = 0
        
        err = lp.lpAMSAInScanStatus(dev_handle, ctypes.byref(status), ctypes.byref(xfer_status))
        index = xfer_status.currentIndex
        if(index >= 0):
            cIndex = index
            if(cIndex == pIndex):
                continue
            if(cIndex > pIndex):
                for c in range(0, cIndex - pIndex + 1):
                    for i in range(0, 4):
                        if  ((i == 0) and ((c + pIndex) % 4 == i)):
                            # print(f"Ch0: {scan_data[c + pIndex]}", end="\t")
                            data_container_0.append(scan_data[c + pIndex])
                        elif((i == 1) and ((c + pIndex) % 4 == i)):
                            # print(f"Ch1: {scan_data[c + pIndex]}", end="\t")
                            data_container_1.append(scan_data[c + pIndex])
                        elif((i == 2) and ((c + pIndex) % 4 == i)):
                            # print(f"Ch2: {scan_data[c + pIndex]}", end="\t")
                            data_container_2.append(scan_data[c + pIndex])
                        elif((i == 3) and ((c + pIndex) % 4 == i)):
                            # print(f"Ch3: {scan_data[c + pIndex]}", end="\n")
                            data_container_3.append(scan_data[c + pIndex])
            if(cIndex < pIndex):
                for c in range(0, bufferSize - pIndex + 1):
                    for i in range(0, 4):
                        if  ((i == 0) and ((c + pIndex) % 4 == i)):
                            # print(f"Ch0: {scan_data[c + pIndex]}", end="\t")
                            data_container_0.append(scan_data[c + pIndex])
                        elif((i == 1) and ((c + pIndex) % 4 == i)):
                            # print(f"Ch1: {scan_data[c + pIndex]}", end="\t")
                            data_container_1.append(scan_data[c + pIndex])
                        elif((i == 2) and ((c + pIndex) % 4 == i)):
                            # print(f"Ch2: {scan_data[c + pIndex]}", end="\t")
                            data_container_2.append(scan_data[c + pIndex])
                        elif((i == 3) and ((c + pIndex) % 4 == i)):
                            # print(f"Ch3: {scan_data[c + pIndex]}", end="\n")
                            data_container_3.append(scan_data[c + pIndex])

                cycleCount = cycleCount + 1
                for c in range(0, cIndex):
                    for i in range(0, 4):
                        if  ((i == 0) and ((c) % 4 == i)):
                            # print(f"Ch0: {scan_data[c]}", end="\t")
                            data_container_0.append(scan_data[c])
                        elif((i == 1) and ((c) % 4 == i)):
                            # print(f"Ch1: {scan_data[c]}", end="\t")
                            data_container_1.append(scan_data[c])
                        elif((i == 2) and ((c) % 4 == i)):
                            # print(f"Ch2: {scan_data[c]}", end="\t")
                            data_container_2.append(scan_data[c])
                        elif((i == 3) and ((c) % 4 == i)):
                            # print(f"Ch3: {scan_data[c]}", end="\n")
                            data_container_3.append(scan_data[c])
            
            pIndex = cIndex
            count = xfer_status.currentScanCount
    
    end = time.time()
    print(f"Running time: {end - start}")

    # Step 9: Disconnect and release device
    print("\n9. Disconnecting and releasing device...")
    err = lp.lpDisconnectAMSDevice(dev_handle)
    if err != lp.LPAMSError.ERR_NO_ERROR:
        print(f"Error disconnecting from device: {err}")
        return 1
    
    err = lp.lpReleaseAMSDevice(dev_handle)
    if err != lp.LPAMSError.ERR_NO_ERROR:
        print(f"Error releasing device: {err}")
        return 1
    
    print("Disconnected and released device resources successfully!")
    print("\nExample completed successfully!")
    return 0

if __name__ == "__main__":
    sys.exit(main())