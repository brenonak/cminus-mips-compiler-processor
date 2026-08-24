# Compilador C− (Projeto Final – Laboratório de Sistemas Computacionais: Compiladores)

### Aluno: Breno Cerqueira Reis Nakamura (RA: 168765)

Este projeto implementa um compilador completo para a linguagem **C−**, cobrindo todas as fases de análise e síntese, desde o código-fonte até o binário executável no processador MIPS monociclo implementado em FPGA.

### Pipeline completo:

```
Código C-  →  Análise  →  AST  →  Código Intermediário  →  Assembly MIPS  →  Binário (.mif)  →  FPGA
```

### Módulos implementados:

- **Análise léxica** (Flex) — reconhecimento de tokens
- **Análise sintática** (Bison) — construção da Árvore Sintática Abstrata (AST)
- **Análise semântica** — tabela de símbolos, gerenciamento de escopos, verificação de tipos
- **Geração de Código Intermediário** — quádruplas de três endereços (Three-Address Code)
- **Geração de Código Assembly** — tradução das quádruplas para assembly MIPS textual
- **Geração de Código Binário** — montagem do assembly em instruções de 32 bits para o processador
- **Visualização da AST** via Graphviz

---

## Estrutura do Projeto em /Compilador

```
.
├── scanner.l        # Analisador léxico (Flex)
├── parser.y         # Analisador sintático e semântico (Bison)
├── globals.h        # Definições globais: structs da AST, tabela de símbolos e quádruplas
├── util.c           # Funções auxiliares: AST, tabela de símbolos e gerador de CI
├── cgen.h           # Header do gerador de código assembly
├── cgen.c           # Gerador de código assembly MIPS
├── assembler.h      # Header do montador binário
├── assembler.c      # Montador de código binário (.mif)
└── README.md
```

---

## Requisitos de Software

- **Flex**
- **Bison**
- **GCC**
- **Graphviz** (opcional, para visualização da AST)

---

## Compilação do Projeto

No diretório do projeto, execute os comandos abaixo **em ordem**:

```bash
flex scanner.l
bison -d parser.y
gcc -o compilador parser.tab.c lex.yy.c util.c cgen.c assembler.c
```

Isso irá gerar o executável `compilador` (ou `compilador.exe` no Windows).

---

## Execução

Para compilar um programa escrito em C−:

```bash
./compilador programa.txt
```

O compilador irá:

1. Exibir a **tabela de símbolos** com todas as variáveis e funções declaradas
2. Gerar o arquivo `arvore.dot` com a **Árvore Sintática Abstrata (AST)**
3. Exibir o **Código Intermediário** em quádruplas no formato `(op, arg1, arg2, resultado)`
4. Gerar o arquivo `codigo.asm` com o **código assembly MIPS** textual
5. Gerar o arquivo `codigo.mif` com o **código binário de 32 bits** para o processador

Em caso de erros léxicos, sintáticos ou semânticos, o compilador exibe mensagens de erro com a linha correspondente e **não gera** código intermediário, assembly ou binário.

---

## Carregamento na FPGA

O arquivo `codigo.mif` gerado contém uma instrução de 32 bits por linha, em formato binário, compatível com a diretiva `$readmemb` do SystemVerilog.

Para executar o programa compilado no processador MIPS monociclo implementado em FPGA:

1. Copie o arquivo `codigo.mif` para o diretório do projeto do processador
2. O módulo `memoriaROM` carrega automaticamente o arquivo na memória de instruções:
   ```systemverilog
   $readmemb("codigo.mif", rom);
   ```
3. Sintetize o projeto no Quartus e grave na placa FPGA
4. Use as **chaves (switches)** da placa para fornecer valores de entrada (`input()`)
5. Pressione o **botão Enter** para confirmar cada entrada
6. O resultado de `output()` é exibido nos **displays de 7 segmentos**

---

## Visualização da AST (Graphviz)

Se o Graphviz estiver instalado, gere a imagem da AST com:

```bash
dot -Tpng arvore.dot -o arvore.png
```

---

## Formato do Código Intermediário

As quádruplas seguem o formato `(op, arg1, arg2, resultado)`:

| Operação             | Exemplo                         |
|----------------------|---------------------------------|
| Carga de constante   | `(LDI, 10, -, $t0)`            |
| Atribuição           | `(:=, $t0, -, x)`              |
| Operação aritmética  | `(+, a, b, $t1)`               |
| Desvio condicional   | `(JZ, $t1, -, L0)`             |
| Desvio incondicional | `(JMP, -, -, L1)`              |
| Chamada de função    | `(CALL, soma, -, $t2)`         |
| Passagem de argumento| `(PARAM, $t0, -, -)`           |
| Retorno              | `(RET, $t1, -, -)`             |
| Leitura de vetor     | `(LDV, v[$t0], -, $t1)`        |

Temporários são nomeados `$t0`, `$t1`, ... e labels são nomeados `L0`, `L1`, ...

---

## Arquitetura do Processador Alvo

O código é gerado para um processador MIPS monociclo de 32 bits, implementado em SystemVerilog e sintetizado em FPGA, com as seguintes características:

- **32 registradores** de 32 bits (r0 fixo em zero)
- **Memória word-addressable** (incrementos de ±1, não ±4)
- **Memória de dados**: 256 posições de 32 bits (RAM)
- **Memória de instruções**: 256 posições de 32 bits (ROM, carregada via `codigo.mif`)
- **Instruções de branch compostas**: BEQ, BNE, BLT, BGT, BLE, BGE
- **Instruções de I/O nativas**: IN (chaves) e OUT (display)

### Convenção de registradores adotada:

| Nome     | Físico | Uso                              |
|----------|--------|----------------------------------|
| `$zero`  | r0     | Constante zero (fixo, hardware)  |
| `$v0`    | r2     | Valor de retorno de função       |
| `$t0`    | r8     | Scratch — operando 1             |
| `$t1`    | r9     | Scratch — operando 2             |
| `$t2`    | r10    | Scratch — resultado              |
| `$s0`    | r16    | Scratch — cálculo de endereço    |
| `$sp`    | r29    | Stack pointer                    |
| `$ra`    | r31    | Return address (JAL)             |

---

## Programas de Teste Validados

| Programa     | Funcionalidade testada                                     |
|--------------|------------------------------------------------------------|
| `gcd.txt`    | Recursão, algoritmo de Euclides, if/else                   |
| `sort.txt`   | Vetor global, passagem por referência, múltiplas funções   |
| `fatorial.txt` | Recursão simples, multiplicação encadeada                |

---

## Observações

- A linguagem C− é um subconjunto simplificado de C, conforme definida em Louden (2004, p. 494)
- A análise semântica verifica: declaração de variáveis, escopo, tipos, uso de vetores, número e tipos de parâmetros em chamadas de função, e presença obrigatória da função `main`
- O gerenciamento de escopos usa uma pilha: global, função e bloco
- A geração de código intermediário é feita por travessia recursiva da AST na função `generate_quads` (implementada em `util.c`)
- O gerador de assembly (`cgen.c`) utiliza estratégia de memory spilling generalizado: todos os temporários residem na memória, usando apenas 3 registradores scratch para operações load-compute-store
- O montador binário (`assembler.c`) opera em duas passagens: coleta de labels na primeira, codificação na segunda
- O arquivo `.mif` gerado inclui comentários com a instrução original para facilitar depuração