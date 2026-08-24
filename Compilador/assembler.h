/* assembler.h — Montador Binário MIPS */
#ifndef _ASSEMBLER_H_
#define _ASSEMBLER_H_

/* Lê o arquivo .asm (texto) e gera o arquivo .mif (binário).
 * Deve ser chamado APÓS generate_assembly(). */
void generate_binary(const char *asm_file, const char *mif_file);

#endif