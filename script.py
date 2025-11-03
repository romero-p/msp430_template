import subprocess
import time

# Start the UART script
uart_process = subprocess.Popen(["python3", "-u", "uart.py"], stdout=subprocess.PIPE, stderr=subprocess.STDOUT, text=True)

# Run the make commands to flash MSP430
subprocess.run(["make", "clean"])
subprocess.run(["make"])
subprocess.run(["make", "flash"])

time.sleep(2)

# Read the output from the UART script
for line in uart_process.stdout:
    print(line, end='', flush=True)
    
# Terminate the UART process
uart_process.terminate()