import subprocess
import time
import csv

unroll_count = 10
indent = " " * 12

instructions = [
    {"description": "NOP", "asm": "NOP"},
    {"description": "ADD Rn, Rm", "asm": "ADD r7, r8"},
    {"description": "ADD Rn, x(Rm)", "asm": "ADD r7, 4(r8)"},
    {"description": "ADD @Rn, Rm", "asm": "ADD @r7, r8"},
    {"description": "ADD @Rn, x(Rm)", "asm": "ADD @r7, 4(r8)"},
    {"description": "ADD @Rn+, Rm", "asm": "ADD @r7+, r8"},
    {"description": "ADD @Rn+, x(Rm)", "asm": "ADD @r7+, 4(r8)"},
    {"description": "ADD #N, Rm", "asm": "ADD #0x1234, r8"},
    {"description": "ADD #N, x(Rm)", "asm": "ADD #0x1234, 4(r8)"},
    {"description": "ADD x(Rn), Rm", "asm": "ADD 4(r7), r8"},
    {"description": "ADD x(Rn), x(Rm)", "asm": "ADD 4(r7), 4(r8)"},
]

with open("results.csv", "w", newline='') as csvfile:
    csvwriter = csv.writer(csvfile)
    csvwriter.writerow(["Instruction", "Cycle count", "Unroll count"])

    for instr in instructions:

        # Generate the main.c file from the template
        with open("template.c", "r") as file:
            template = file.read()
            template = template.replace("UNROLL_COUNT", str(unroll_count))
            benchmark_block = ""
            for i in range(unroll_count):
                benchmark_block += f'{indent}"{instr["asm"]}\\n"\n'
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
