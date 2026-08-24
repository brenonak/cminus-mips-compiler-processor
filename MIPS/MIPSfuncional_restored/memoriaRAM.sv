module memoriaRAM #(
    parameter DATA_WIDTH = 32,
    parameter ADDR_WIDTH = 8
) (
    input  logic                      read_clock,
    input  logic                      write_clock,
    input  logic                      we,          
    input  logic                      memread,     
    input  logic [ADDR_WIDTH-1:0]     read_addr,
    input  logic [ADDR_WIDTH-1:0]     write_addr,
    input  logic [DATA_WIDTH-1:0]     data,
    output logic [DATA_WIDTH-1:0]     q            
);

    logic [DATA_WIDTH-1:0] ram [0:(2**ADDR_WIDTH)-1];

    // Processo de escrita (síncrono com o clock do processador)
    always_ff @(posedge write_clock) begin
        if (we)
            ram[write_addr] <= data;
    end

    // Processo de leitura (síncrono com o clock rápido)
    always_ff @(posedge read_clock) begin
        if (memread)
            q <= ram[read_addr];
    end

endmodule