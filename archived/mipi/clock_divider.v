//in_clk is assumed as 50MHz, the reset is active high 
module clock_divider(   input in_clk, reset,
                        output outclk);
    parameter divider_count = 2;//outclk is 25MHz by default

    reg [9:0] counter;

    always @(posedge in_clk) begin
        if (reset) begin
            outclk <= 1'b0;
            counter <= 10'b0;
        end else begin
            if (counter == divider_count) begin
                outclk <= ~outclk;
                counter <= 10'b0;
            end else
                counter <= counter + 1;  
        end
    end
endmodule