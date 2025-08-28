import subprocess

# Start the UART script
uart_process = subprocess.Popen(["python3", "-u", "uart.py"], stdout=subprocess.PIPE, stderr=subprocess.STDOUT, text=True)

# Run the make commands to flash MSP430
subprocess.run(["make", "clean"])
subprocess.run(["make"])
subprocess.run(["make", "flash"])


# Read the output from the UART script
output = uart_process.stdout.readline()
print(output, flush=True)

# Terminate the UART process
uart_process.terminate()