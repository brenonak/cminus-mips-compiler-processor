module PC (
    input logic clockPC,
    input logic reset,
    input logic enable,
    input logic halt,               // Sinal de parada
    input logic [31:0] prox_end,
    
    output logic [31:0] atualPC
);

    // O reset agora é assíncrono e o resto é síncrono
    always_ff @(posedge clockPC or posedge reset) begin
        if (reset) begin
            atualPC <= 32'b0;
        end
        else if (enable && !halt) begin
            atualPC <= prox_end;
        end
    end

endmodule