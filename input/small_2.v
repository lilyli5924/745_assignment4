module small_2 ( clock, 
    FM, TEST, CLR,
    GRN2, YLW2, RED2, GRN1, YLW1, RED1  );
  input  clock, FM, TEST, CLR;
  output GRN2, YLW2, RED2, GRN1, YLW1, RED1;
  reg TESTL, FML, OLATCH_Y2L, OLATCHVUC_6, OLATCHVUC_5, OLATCH_R1L,
    OLATCH_G2L, OLATCH_G1L, OLATCH_FEL, C3_Q3, C3_Q2, C3_Q1, C3_Q0, UC_16,
    UC_17, UC_18, UC_19, UC_8, UC_9, UC_10, UC_11;
  wire n73, n74_1, n76, n77, n80, n81, n82, n83, n84_1, n85, n86, n87, n88,
    n89_1, n90, n91, n92, n93, n95, n96, n97, n99_1, n100, n102, n104_1,
    n105, n107, n108, n109_1, n110, n111, n112, n113, n114_1, n115, n116,
    n117, n118, n119_1, n121, n123, n125, n127, n128, n129, n130, n131,
    n133, n135, n137, n139, n140, n141, n143, n144, n145, n19, n24, n29,
    n34, n39, n44, n49, n54, n59, n64, n69, n74, n79, n84, n89, n94, n99,
    n104, n109, n114, n119;
  assign n19 = ~CLR & ~n73 & ~n74_1;
  assign n73 = TEST & TESTL;
  assign n74_1 = ~TEST & ~TESTL;
  assign n24 = ~CLR & ~n76 & ~n77;
  assign n76 = FM & FML;
  assign n77 = ~FM & ~FML;
  assign n29 = ~C3_Q2 & ~CLR & ~OLATCH_FEL & C3_Q1 & C3_Q0;
  assign n34 = n80 | n89_1;
  assign n80 = ~n81 & ~n85;
  assign n81 = n82 & ~n83;
  assign n82 = ~CLR & OLATCH_FEL;
  assign n83 = C3_Q2 & n84_1;
  assign n84_1 = ~C3_Q3 & ~FML & C3_Q0 & ~C3_Q1;
  assign n85 = ~n87 & ~C3_Q1 & ~C3_Q0 & ~CLR & ~n86;
  assign n86 = ~C3_Q3 & ~C3_Q2;
  assign n87 = C3_Q2 & ~n88;
  assign n88 = FML & ~C3_Q3;
  assign n89_1 = UC_17 & ~n90;
  assign n90 = ~n81 & ~n91;
  assign n91 = n92 & n93;
  assign n92 = ~CLR & C3_Q2;
  assign n93 = ~C3_Q0 & FML & ~C3_Q1;
  assign n39 = n89_1 | n95;
  assign n95 = ~n82 & ~n92 & ~n96;
  assign n96 = ~C3_Q1 & n97;
  assign n97 = ~C3_Q0 & ~CLR & C3_Q3;
  assign n44 = CLR | n99_1 | n100;
  assign n99_1 = ~OLATCH_FEL & n86;
  assign n100 = ~C3_Q2 & ~C3_Q1 & ~OLATCH_FEL & C3_Q0;
  assign n49 = ~n97 & ~n82 & ~n92 & ~n102;
  assign n102 = C3_Q0 & ~CLR & C3_Q1;
  assign n54 = ~n105 & ~n104_1 & ~n93 & n92;
  assign n104_1 = FML & C3_Q3;
  assign n105 = OLATCH_FEL & ~n84_1;
  assign n64 = ~n107 & ~CLR & ~n115 & ~n119_1;
  assign n107 = ~n114_1 & C3_Q3 & n108;
  assign n108 = ~n110 & UC_16 & ~n109_1;
  assign n109_1 = ~UC_19 & ~UC_17 & ~UC_18;
  assign n110 = ~TESTL & ~n111;
  assign n111 = UC_8 & ~n112;
  assign n112 = ~UC_9 & n113;
  assign n113 = ~UC_10 & ~UC_11;
  assign n114_1 = ~C3_Q0 & ~C3_Q2 & ~C3_Q1;
  assign n115 = ~C3_Q3 & ~n116;
  assign n116 = C3_Q2 & n117;
  assign n117 = C3_Q1 & n118;
  assign n118 = C3_Q0 & n108;
  assign n119_1 = C3_Q3 & n116;
  assign n69 = ~n107 & ~CLR & ~n116 & ~n121;
  assign n121 = ~C3_Q2 & ~n117;
  assign n74 = ~n107 & ~CLR & ~n117 & ~n123;
  assign n123 = ~C3_Q1 & ~n118;
  assign n79 = ~n107 & ~CLR & ~n118 & ~n125;
  assign n125 = ~C3_Q0 & ~n108;
  assign n84 = ~n108 & ~CLR & ~n127 & ~n131;
  assign n127 = ~UC_16 & ~n128;
  assign n128 = UC_17 & n129;
  assign n129 = UC_18 & n130;
  assign n130 = UC_19 & ~n110;
  assign n131 = UC_16 & n128;
  assign n89 = ~n108 & ~CLR & ~n128 & ~n133;
  assign n133 = ~UC_17 & ~n129;
  assign n94 = ~n108 & ~CLR & ~n129 & ~n135;
  assign n135 = ~UC_18 & ~n130;
  assign n99 = ~n108 & ~CLR & ~n130 & ~n137;
  assign n137 = ~UC_19 & n110;
  assign n104 = ~n111 & ~CLR & ~n139 & ~n141;
  assign n139 = ~UC_8 & ~n140;
  assign n140 = UC_10 & UC_11 & UC_9;
  assign n141 = UC_8 & n140;
  assign n109 = ~n111 & ~CLR & ~n143 & ~n145;
  assign n143 = ~UC_9 & ~n144;
  assign n144 = UC_10 & UC_11;
  assign n145 = UC_9 & n144;
  assign n114 = ~n111 & ~CLR & ~n113 & ~n144;
  assign n119 = ~n111 & ~CLR & ~UC_11;
  assign GRN2 = OLATCH_G2L;
  assign YLW2 = OLATCH_Y2L;
  assign RED2 = ~OLATCHVUC_5;
  assign GRN1 = OLATCH_G1L;
  assign YLW1 = ~OLATCHVUC_6;
  assign RED1 = OLATCH_R1L;
  assign n59 = ~n90;
  always @ (posedge clock) begin
    TESTL <= n19;
    FML <= n24;
    OLATCH_Y2L <= n29;
    OLATCHVUC_6 <= n34;
    OLATCHVUC_5 <= n39;
    OLATCH_R1L <= n44;
    OLATCH_G2L <= n49;
    OLATCH_G1L <= n54;
    OLATCH_FEL <= n59;
    C3_Q3 <= n64;
    C3_Q2 <= n69;
    C3_Q1 <= n74;
    C3_Q0 <= n79;
    UC_16 <= n84;
    UC_17 <= n89;
    UC_18 <= n94;
    UC_19 <= n99;
    UC_8 <= n104;
    UC_9 <= n109;
    UC_10 <= n114;
    UC_11 <= n119;
  end
endmodule


