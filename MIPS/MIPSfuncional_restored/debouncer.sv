module debouncer (
    input  logic clk, // Recebe o clock de 10Hz do divisor
    input  logic btn_in,
    output logic btn_out
);

    logic btn_sync_1, btn_sync_2;

    // Sincronizador e detector de borda operando no relógio lento
    always_ff @(posedge clk) begin
        btn_sync_1 <= btn_in;
        btn_sync_2 <= btn_sync_1;
    end
    
    // Gera um pulso limpo que dura exatamente 1 ciclo do PC (100ms)
    assign btn_out = btn_sync_1 & ~btn_sync_2;

endmodule