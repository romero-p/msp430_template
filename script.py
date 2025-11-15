import subprocess
import time
import csv

# User-configurable parameters
unroll_count = 10 # Number of times to unroll each instruction
benchmark_file = "exp1.py" # Benchmark file to use

# Constants
indent = " " * 12
benchmark_path = f"benchmarks/{benchmark_file}"
benchmark_description = benchmark_file.replace(".py", "")
csv_path = f"results/{benchmark_description}.csv"
# Import the instructions from the benchmark file
benchmark_module = __import__(f"benchmarks.{benchmark_description}", fromlist=['instructions'])
instructions = benchmark_module.instructions

with open(csv_path, "w", newline='') as csvfile:
    csvwriter = csv.writer(csvfile)
    csvwriter.writerow(["Instruction", "Cycle count", "Unroll count"])

    for instr in instructions:
        asm_list = instr["asm"] if isinstance(instr["asm"], list) else [instr["asm"]]
        # Generate the main.c file from the template
        with open("template.c", "r") as file:
            template = file.read()
            template = template.replace("UNROLL_COUNT", str(unroll_count))
            benchmark_block = ""
            for i in range(unroll_count):
                for line in asm_list:
                    benchmark_block += f'{indent}"{line}\\n"\n'
            template = template.replace("BENCHMARK", benchmark_block.strip())
        with open("src/main.c", "w") as file:
            file.write(template)

        # Start the UART script
        uart_process = subprocess.Popen(["python3", "-u", "uart.py"], stdout=subprocess.PIPE, stderr=subprocess.STDOUT, text=True)

        # Run the make commands to flash MSP430
        subprocess.run(["make", "clean"])
        subprocess.run(["make"])
        subprocess.run(["make", "flash"])

        time.sleep(2)

        # Read the output from the UART script
        cycle_count = uart_process.stdout.readline()
        print(cycle_count, end='', flush=True)
        cycle_count = cycle_count.strip()

        # Terminate the UART process
        uart_process.terminate()

        csvwriter.writerow([instr["description"], cycle_count, unroll_count])
