module small_1 ( clock, 
    G0, G1, G2,
    G117, G132, G66, G118, G133, G67  );
  input  clock, G0, G1, G2;
  output G117, G132, G66, G118, G133, G67;
  reg G10, G11, G12, G13, G14, G15, G16, G17, G18, G19, G20, G21, G22, G23;
  wire n53, n54_1, n55, n56, n58, n59_1, n60, n62, n63, n64_1, n65, n66, n67,
    n69_1, n70, n71, n72, n73, n75, n76, n77, n78, n79_1, n81, n82, n83,
    n85, n86, n87, n88, n89, n90, n92, n93, n95, n96, n97, n98, n99, n100,
    n102, n103, n104, n106, n107, n109, n110, n112, n113, n19, n24, n29,
    n34, n39, n44, n49, n54, n59, n64, n69, n74, n79, n84;
  assign n19 = ~G0 & ~G10;
  assign n24 = ~G0 & ~n53 & ~n54_1;
  assign n53 = ~G10 & ~G11;
  assign n54_1 = G10 & ~n55;
  assign n55 = ~G11 & ~n56;
  assign n56 = ~G12 & G13;
  assign n29 = ~G0 & ~n58 & ~n59_1 & ~n60;
  assign n58 = ~G11 & ~G12;
  assign n59_1 = G11 & G12 & G10;
  assign n60 = ~G10 & ~G12;
  assign n34 = ~n62 & ~G0 & ~n65;
  assign n62 = ~G13 & ~n63;
  assign n63 = G10 & n64_1;
  assign n64_1 = G11 & G12;
  assign n65 = G10 & ~n66;
  assign n66 = ~n58 & ~n67;
  assign n67 = G13 & n64_1;
  assign n39 = ~G0 & ~n69_1;
  assign n69_1 = ~n70 & ~n73;
  assign n70 = ~G14 & ~n71;
  assign n71 = ~G23 & ~n72;
  assign n72 = ~G11 & n56 & G10;
  assign n73 = G14 & n71;
  assign n44 = ~G0 & n75;
  assign n75 = ~n76 & ~n78;
  assign n76 = ~G12 & G11 & n77 & ~G22;
  assign n77 = G13 & ~G14;
  assign n78 = ~G15 & ~n79_1;
  assign n79_1 = n58 & n77 & G22;
  assign n49 = ~n75 & ~n81 & ~n82;
  assign n81 = ~G12 & ~G13;
  assign n82 = ~n77 & ~n83;
  assign n83 = G14 & G16;
  assign n54 = ~n75 & ~n85 & ~n87 & ~n89 & ~n77 & ~n90;
  assign n85 = ~G17 & n86;
  assign n86 = G12 & G14;
  assign n87 = G14 & n88;
  assign n88 = ~G13 & n58;
  assign n89 = ~G14 & n64_1;
  assign n90 = G13 & ~G17;
  assign n59 = ~n92 & ~n75 & ~n77 & ~n87 & ~n93;
  assign n92 = ~G18 & G12 & G14;
  assign n93 = G13 & ~G18;
  assign n64 = n95 | n100;
  assign n95 = ~n75 & ~n96;
  assign n96 = ~n97 & ~n77 & ~n99;
  assign n97 = G19 & ~n98;
  assign n98 = ~G13 & ~n86;
  assign n99 = G14 & n58 & ~G13;
  assign n100 = ~G10 & n75;
  assign n69 = n100 | n102;
  assign n102 = ~n103 & ~n75 & G14;
  assign n103 = ~n88 & ~n104;
  assign n104 = G20 & ~n81;
  assign n74 = ~n106 & ~n75 & ~n81 & ~n77 & ~n107;
  assign n106 = G14 & ~G21;
  assign n107 = ~G11 & ~G14;
  assign n79 = ~G0 & ~n109 & ~n110;
  assign n109 = ~G2 & ~G22;
  assign n110 = G2 & G22;
  assign n84 = ~G0 & ~n112 & ~n113;
  assign n112 = ~G1 & ~G23;
  assign n113 = G1 & G23;
  assign G117 = G18;
  assign G132 = G20;
  assign G66 = G16;
  assign G118 = G19;
  assign G133 = G21;
  assign G67 = G17;
  always @ (posedge clock) begin
    G10 <= n19;
    G11 <= n24;
    G12 <= n29;
    G13 <= n34;
    G14 <= n39;
    G15 <= n44;
    G16 <= n49;
    G17 <= n54;
    G18 <= n59;
    G19 <= n64;
    G20 <= n69;
    G21 <= n74;
    G22 <= n79;
    G23 <= n84;
  end
endmodule


