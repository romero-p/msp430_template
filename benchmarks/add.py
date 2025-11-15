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