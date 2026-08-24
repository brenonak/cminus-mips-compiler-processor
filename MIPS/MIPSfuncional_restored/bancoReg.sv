module bancoReg (
    input logic clock,                  // Clock
    input logic reset,                  // Reset síncrono
    input logic regWrite,               // Sinal 1 - habilita escrita
    input logic [4:0] leReg1,           // Endereco do registrador 1
    input logic [4:0] leReg2,           // Endereco do registrador 2
    input logic [4:0] escreveReg,       // Endereco do registrador para escrita
    input logic [31:0] escreveDado,     // Dado para ser escrito no registrador

    output logic [31:0] leDado1,        // Saida da leitura 1
    output logic [31:0] leDado2         // Saida da leitura 2
);

    logic [31:0] registradores [31:0];  // Memoria de 32 bits dos 32 registradores

    // Escrita e reset dos registradores
    always_ff @(posedge clock) begin
        if (reset) begin
            for (int i=0; i<32; i++) begin
                registradores[i] <= 32'b0;
            end
        end
        else if (regWrite) begin
            if (escreveReg != 5'd0) begin  // Manter registrador [0] com valor ZERO
                registradores[escreveReg] <= escreveDado;
            end
        end
    end

    // Escrita dos dados nas saidas
    assign leDado1 = registradores[leReg1];
    assign leDado2 = registradores[leReg2];

endmodule