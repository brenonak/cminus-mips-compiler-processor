# C- MIPS — Compilador & Processador

Projeto completo de compilador e arquitetura de computadores, desenvolvido para as disciplinas de **Laboratório de Sistemas Computacionais: Compiladores** e **Laboratório de Sistemas Computacionais: Arquitetura e Organização de Computadores**.

O repositório reúne dois projetos integrados:

- **`/Compilador`** — Compilador para a linguagem **C−** (Louden, 2004), com pipeline completo: análise léxica, sintática e semântica; geração de código intermediário (quádruplas); geração de código assembly MIPS; e montagem para código binário.

- **`/MIPS`** — Processador **MIPS monociclo** de 32 bits, implementado em **SystemVerilog**, com banco de registradores, ULA, memórias de instrução e dados, e interface de I/O (chaves e displays de 7 segmentos), sintetizado e executado em **FPGA**.

Juntos, os dois módulos formam um toolchain completo: um programa escrito em C− é compilado, montado em binário e executado nativamente no hardware do processador projetado.

```
Código C-  →  Compilador  →  Assembly MIPS  →  Binário (.mif)  →  Processador (FPGA)
```
