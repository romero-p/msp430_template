instructions = [
    {"description": "NOP", "asm": "NOP"},
    {"description": "MOV Rn, Rm", "asm": "MOV r7, r8"},
    {"description": "MOV Rn, x(Rm)", "asm": "MOV r7, 4(r8)"},
    {"description": "MOV @Rn, Rm", "asm": "MOV @r7, r8"},
    {"description": "MOV @Rn, x(Rm)", "asm": "MOV @r7, 4(r8)"},
    {"description": "MOV @Rn+, Rm", "asm": "MOV @r7+, r8"},
    {"description": "MOV @Rn+, x(Rm)", "asm": "MOV @r7+, 4(r8)"},
    {"description": "MOV #N, Rm", "asm": "MOV #0x1234, r8"},
    {"description": "MOV #N, x(Rm)", "asm": "MOV #0x1234, 4(r8)"},
    {"description": "MOV x(Rn), Rm", "asm": "MOV 4(r7), r8"},
    {"description": "MOV x(Rn), x(Rm)", "asm": "MOV 4(r7), 4(r8)"},
]