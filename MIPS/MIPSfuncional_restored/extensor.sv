module extensor (
    input  logic [15:0] entrada,
    output logic [31:0] saida
);

    always_comb begin
        if (entrada[15] == 1) begin
            saida[31:16] = 16'b1111111111111111;   // Valor negativo em complemento de 2, replica 1 nos bits mais altos
        end else begin
            // Sinal 0 → replica 16 '0's
            saida[31:16] = 16'b0000000000000000;    // Valor positivo, replica 0 nos bits mais altos
        end

        saida[15:0] = entrada;                      // Copia a entrada nos bits menos significativos
    end

endmodule
