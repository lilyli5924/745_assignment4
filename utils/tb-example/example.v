module example ( clock, G0, G1, G2, G3, G17  );

  input  clock, G0, G1, G2, G3;
  output G17;

  reg G5, G6, G7;
  wire n17, n18, n19, n20, n23, n34, n37, n40;

  assign G17 = ~n37;
  assign n17 = ~G0 & G6;
  assign n18 = n23 | n17;
  assign n19 = G3 | n17;
  assign n20 = ~n19 | ~n18;
  assign n34 = G0 & ~n37;
  assign n37 = ~G5 & ~n20;
  assign n23 = ~G1 & ~G7;
  assign n40 = ~G2 & ~n23;

  always @ (posedge clock) begin
    G5 <= n34;
    G6 <= n37;
    G7 <= n40;
  end

endmodule
