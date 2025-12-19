import os
import sys

# Function to check if a DLL is 32-bit or 64-bit
def check_dll_architecture(dll_path):
    if not os.path.exists(dll_path):
        return "File not found"
    
    try:
        with open(dll_path, 'rb') as f:
            # Read the DOS header
            dos_header = f.read(64)
            if dos_header[0:2] != b'MZ':
                return "Not a valid PE file"
            
            # Get the offset to the PE header
            pe_offset = int.from_bytes(dos_header[60:64], byteorder='little')
            
            # Read the PE header
            f.seek(pe_offset)
            pe_header = f.read(24)
            if pe_header[0:4] != b'PE\x00\x00':
                return "Not a valid PE file"
            
            # Get the machine type
            machine_type = int.from_bytes(pe_header[4:6], byteorder='little')
            
            # Map machine type to architecture
            if machine_type == 0x014c:
                return "32-bit (x86)"
            elif machine_type == 0x8664:
                return "64-bit (x64)"
            elif machine_type == 0x0200:
                return "Itanium (IA-64)"
            else:
                return f"Unknown architecture (machine type: 0x{machine_type:X})"
    except Exception as e:
        return f"Error checking architecture: {e}"

# Check Python architecture
print(f"Python architecture: {sys.maxsize > 2**32 and '64-bit (x64)' or '32-bit (x86)'}")

# Check DLLs
dll_dir = os.path.join(os.path.dirname(__file__), "dll")
dlls_to_check = ["lpamsdk.dll", "lpamsdk_d.dll", "libusb-1.0.dll", "pthreadVC2.dll"]

for dll_name in dlls_to_check:
    dll_path = os.path.join(dll_dir, dll_name)
    arch = check_dll_architecture(dll_path)
    print(f"{dll_name:20} -> {arch}")

# Also check if there are any other DLLs in the directory
print("\nOther files in DLL directory:")
for file in os.listdir(dll_dir):
    if file not in dlls_to_check:
        print(f"  {file}")