module small_3 ( clock, 
    Rdy1RtHS1, Rdy2RtHS1, Rdy1BmHS1, Rdy2BmHS1, InDoneHS1, RtTSHS1,
    TpArrayHS1, OutputHS1, WantBmHS1, WantRtHS1, OutAvHS1, FullOHS1,
    FullIHS1, Prog_2, Prog_1, Prog_0,
    ReWhBufHS1, TgWhBufHS1, SeOutAvHS1, LdProgHS1, Mode2HS1, ReRtTSHS1,
    ShftIRHS1, NewTrHS1, Mode1HS1, ShftORHS1, ActRtHS1, Mode0HS1, TxHInHS1,
    LxHInHS1, NewLineHS1, ActBmHS1, GoBmHS1, LoadOHHS1, DumpIHS1,
    SeFullOHS1, GoRtHS1, LoadIHHS1, SeFullIHS1  );
  input  clock, Rdy1RtHS1, Rdy2RtHS1, Rdy1BmHS1, Rdy2BmHS1, InDoneHS1, RtTSHS1,
    TpArrayHS1, OutputHS1, WantBmHS1, WantRtHS1, OutAvHS1, FullOHS1,
    FullIHS1, Prog_2, Prog_1, Prog_0;
  output ReWhBufHS1, TgWhBufHS1, SeOutAvHS1, LdProgHS1, Mode2HS1, ReRtTSHS1,
    ShftIRHS1, NewTrHS1, Mode1HS1, ShftORHS1, ActRtHS1, Mode0HS1, TxHInHS1,
    LxHInHS1, NewLineHS1, ActBmHS1, GoBmHS1, LoadOHHS1, DumpIHS1,
    SeFullOHS1, GoRtHS1, LoadIHHS1, SeFullIHS1;
  reg State_5, State_4, State_3, State_2, State_1, State_0, ActRtHS1,
    ActBmHS1, GoRtHS1, GoBmHS1, NewTrHS1, ReRtTSHS1, Mode0HS1, Mode1HS1,
    Mode2HS1, NewLineHS1, ShftORHS1, ShftIRHS1, LxHInHS1, TxHInHS1,
    LoadOHHS1, LoadIHHS1, SeOutAvHS1, SeFullOHS1, SeFullIHS1, TgWhBufHS1,
    ReWhBufHS1, LdProgHS1, DumpIHS1;
  wire n127, n128, n129_1, n130, n131, n132, n134, n135, n136, n138, n139,
    n140, n141_1, n142, n143, n144, n145_1, n146, n147, n148, n149_1, n150,
    n151, n152, n153_1, n154, n155, n156, n157_1, n158, n159, n160, n161_1,
    n162, n163, n165_1, n166, n167, n168, n169_1, n170, n171, n172, n173_1,
    n174, n175, n176, n177_1, n178, n179, n180, n181_1, n182, n183, n185_1,
    n186, n187, n188, n189_1, n190, n191, n192, n193_1, n194, n195, n197_1,
    n198, n199, n200, n201, n202, n203, n204, n205, n206, n208, n209, n210,
    n211, n212, n213, n214, n215, n216, n217, n218, n219, n220, n221, n222,
    n223, n224, n225, n226, n227, n228, n229, n230, n232, n233, n234, n235,
    n236, n237, n238, n239, n240, n242, n243, n244, n246, n247, n248, n249,
    n250, n251, n253, n254, n255, n256, n257, n258, n259, n260, n262, n263,
    n264, n265, n266, n267, n270, n271, n272, n274, n275, n276, n277, n279,
    n280, n281, n282, n283, n287, n288, n289, n290, n291, n292, n293, n294,
    n296, n297, n298, n299, n300, n301, n303, n304, n305, n306, n307, n308,
    n309, n310, n312, n313, n314, n315, n316, n317, n320, n321, n322, n323,
    n324, n326, n327, n332, n79, n84, n89, n94, n99, n104, n109, n113,
    n117, n121, n125, n129, n133, n137, n141, n145, n149, n153, n157, n161,
    n165, n169, n173, n177, n181, n185, n189, n193, n197;
  assign n79 = n127 | n132 | n141 | n135 | n141_1 | n145_1 | n147 | n153_1 | n154 | n161_1 | n163;
  assign n127 = n129_1 & State_0 & ~n128;
  assign n128 = ~FullOHS1 & ~FullIHS1;
  assign n129_1 = ~State_4 & n130;
  assign n130 = ~State_2 & n131;
  assign n131 = State_5 & ~State_3;
  assign n132 = ~Rdy1RtHS1 & ~Rdy1BmHS1 & n129_1;
  assign n141 = ~State_0 & n134 & State_4;
  assign n134 = ~State_1 & n130;
  assign n135 = ~n136 & n129;
  assign n136 = ~Prog_2 & ~Prog_1;
  assign n129 = n139 & n138 & ~State_1;
  assign n138 = RtTSHS1 & ~State_3;
  assign n139 = ~State_0 & n140 & State_2;
  assign n140 = ~State_5 & ~State_4;
  assign n141_1 = ~n142 & ~n143 & n144;
  assign n142 = ~State_1 & ~State_0;
  assign n143 = State_1 & State_0;
  assign n144 = State_2 & n131;
  assign n145_1 = ~State_0 & n146;
  assign n146 = Prog_2 & n134;
  assign n147 = ~n148 & ~n149_1;
  assign n148 = Rdy1BmHS1 & Rdy2BmHS1;
  assign n149_1 = ~n150 & ~n151;
  assign n150 = ~Prog_0 & n134;
  assign n151 = n131 & n152;
  assign n152 = ~State_1 & State_0;
  assign n153_1 = n129_1 & Prog_2 & ~n128;
  assign n154 = ~n155 & ~n156;
  assign n155 = Rdy1RtHS1 & Rdy2RtHS1;
  assign n156 = ~n157_1 & ~n159;
  assign n157_1 = Prog_0 & n158;
  assign n158 = ~State_0 & n130;
  assign n159 = n160 & State_5 & ~State_3;
  assign n160 = State_1 & ~State_0;
  assign n161_1 = n131 & n162 & ~State_4;
  assign n162 = ~Prog_2 & n152;
  assign n163 = State_5 & ~Prog_2 & ~State_4 & ~State_3 & n160;
  assign n84 = n165_1 | n171 | n175 | n176;
  assign n165_1 = State_4 & ~n166;
  assign n166 = ~n141_1 & ~n167;
  assign n167 = n131 & ~n168;
  assign n168 = ~n169_1 & ~n170;
  assign n169_1 = ~Rdy2RtHS1 & n160;
  assign n170 = ~Rdy2BmHS1 & n152;
  assign n171 = n174 & Rdy2RtHS1 & Prog_0 & ~n172;
  assign n172 = WantBmHS1 & ~n173_1;
  assign n173_1 = Rdy1BmHS1 & ~Rdy2BmHS1;
  assign n174 = n128 & ~State_4 & ~State_0 & n146;
  assign n175 = ~InDoneHS1 & n141;
  assign n176 = ~n179 & n174 & ~n177_1;
  assign n177_1 = WantRtHS1 & ~n178;
  assign n178 = Rdy1RtHS1 & ~Rdy2RtHS1;
  assign n179 = n172 & ~n180;
  assign n180 = Rdy2BmHS1 & n181_1;
  assign n181_1 = ~n182 & ~n183;
  assign n182 = ~Prog_1 & ~Prog_0;
  assign n183 = Prog_1 & Prog_0;
  assign n89 = n185_1 | n187 | n190 | n192 | n195;
  assign n185_1 = n152 & n186;
  assign n186 = State_3 & n140;
  assign n187 = ~TpArrayHS1 & n188;
  assign n188 = State_0 & n189_1;
  assign n189_1 = ~State_2 & n186;
  assign n190 = State_3 & n191;
  assign n191 = State_1 & n139;
  assign n192 = n128 & ~State_0 & n148 & n193_1 & ~State_5;
  assign n193_1 = ~State_2 & n194 & ~State_3;
  assign n194 = ~State_4 & ~State_1;
  assign n195 = ~State_1 & n189_1;
  assign n94 = n191 | n197_1 | n202 | n192 | n204 | n205 | n206;
  assign n197_1 = n178 & n198;
  assign n198 = ~n199 & n158 & State_1;
  assign n199 = ~State_4 & ~n200;
  assign n200 = ~FullIHS1 & n201;
  assign n201 = ~FullOHS1 & Prog_2;
  assign n202 = n173_1 & n203;
  assign n203 = ~n199 & n134 & State_0;
  assign n204 = ~n138 & n139;
  assign n205 = State_1 & n188;
  assign n206 = ~InDoneHS1 & n141_1;
  assign n99 = n208 | n210 | n212 | n220 | n188 | n221 | n228 | n229 | n230;
  assign n208 = ~n209 & n174 & Rdy2BmHS1 & WantBmHS1;
  assign n209 = ~Rdy1RtHS1 & ~Rdy2RtHS1;
  assign n210 = n211 & Rdy2BmHS1 & WantBmHS1;
  assign n211 = ~WantRtHS1 & n174;
  assign n212 = n159 & ~n213;
  assign n213 = ~State_2 & ~n214 & ~n218;
  assign n214 = ~State_4 & ~n215;
  assign n215 = ~n216 & ~n217;
  assign n216 = ~InDoneHS1 & ~Prog_2;
  assign n217 = Prog_2 & ~n128;
  assign n218 = ~n155 & ~n219;
  assign n219 = ~Prog_2 & ~State_4;
  assign n220 = Rdy2BmHS1 & n203 & ~Rdy1BmHS1;
  assign n221 = ~n224 & ~n223 & n222 & ~FullIHS1 & n194 & FullOHS1;
  assign n222 = ~Prog_2 & n158;
  assign n223 = ~Rdy1BmHS1 & ~Prog_0;
  assign n224 = ~n225 & ~n226;
  assign n225 = Prog_0 & n178;
  assign n226 = ~Prog_0 & ~n148 & ~n227;
  assign n227 = ~Rdy1BmHS1 & ~Rdy2BmHS1;
  assign n228 = ~InDoneHS1 & n190;
  assign n229 = State_1 & n127;
  assign n230 = n160 & ~State_3 & ~State_4 & ~n155 & State_2;
  assign n104 = n229 | n232 | n192 | n195 | n234 | n237 | n238;
  assign n232 = n174 & Rdy2RtHS1 & ~n233 & WantRtHS1;
  assign n233 = WantBmHS1 & n227;
  assign n234 = ~n223 & ~n224 & n235;
  assign n235 = ~FullOHS1 & n236;
  assign n236 = n194 & n222;
  assign n237 = Rdy2RtHS1 & n198 & ~Rdy1RtHS1;
  assign n238 = n151 & ~n239;
  assign n239 = ~State_2 & ~n214 & ~n240;
  assign n240 = ~n148 & ~n219;
  assign n109 = n141 | n242 | n243 | n244;
  assign n242 = n144 & n160;
  assign n243 = ~State_2 & n161_1 & Prog_0;
  assign n244 = Prog_0 & n163;
  assign n113 = n141 | n246 | n188 | n247 | n250;
  assign n246 = n144 & n152;
  assign n247 = ~Prog_0 & ~n248;
  assign n248 = ~n161_1 & ~n249;
  assign n249 = ~State_2 & n163;
  assign n250 = ~n251 & n186 & ~State_0;
  assign n251 = ~State_2 & State_1;
  assign n117 = n197_1 | n253 | n256 | n258 | n260;
  assign n253 = n254 & WantRtHS1 & ~n172;
  assign n254 = n255 & Rdy1RtHS1 & ~Rdy2RtHS1 & ~State_4 & n128;
  assign n255 = Prog_2 & n158;
  assign n256 = ~n257 & Prog_0 & ~n209 & n236 & ~n155;
  assign n257 = FullOHS1 & FullIHS1;
  assign n258 = n259 & ~Rdy1BmHS1 & ~Rdy1RtHS1 & ~FullOHS1 & n143;
  assign n259 = ~FullIHS1 & n129_1;
  assign n260 = n191 & ~State_3 & n155;
  assign n121 = n258 | n262 | n202 | n192 | n266;
  assign n262 = ~n257 & ~n263;
  assign n263 = ~n264 & ~n265;
  assign n264 = n236 & n173_1 & n150;
  assign n265 = n236 & n150 & ~Rdy1BmHS1 & Rdy2BmHS1;
  assign n266 = WantBmHS1 & n267;
  assign n267 = ~n177_1 & n128 & ~State_4 & n173_1 & n146;
  assign n125 = n188 | n250;
  assign n133 = n270 | n271 | n243 | n272;
  assign n270 = n160 & ~State_3 & ~State_4 & State_5 & State_2;
  assign n271 = Prog_0 & n141;
  assign n272 = ~Prog_0 & n163;
  assign n137 = n274 | n163 | n275;
  assign n274 = Prog_1 & n141;
  assign n275 = ~n276 & ~State_4 & n131;
  assign n276 = ~n162 & ~n277;
  assign n277 = ~n143 & State_2 & ~n142;
  assign n145 = n192 | n279 | n236 | n258 | n280;
  assign n279 = Prog_2 & n129;
  assign n280 = ~n281 & n201 & n259;
  assign n281 = ~n282 & ~n283;
  assign n282 = Rdy1RtHS1 & n169_1;
  assign n283 = Rdy1BmHS1 & n170;
  assign n149 = n190 | n275 | n188 | n141 | n195;
  assign n153 = n141 | n249;
  assign n157 = n287 | n288 | n188 | n291 | n294;
  assign n287 = n193_1 & ~State_0 & Prog_2;
  assign n288 = ~Rdy2BmHS1 & ~n289;
  assign n289 = ~n146 & ~n290;
  assign n290 = n150 & ~n257;
  assign n291 = ~Rdy2RtHS1 & ~n292;
  assign n292 = ~n255 & ~n293;
  assign n293 = n157_1 & ~n257;
  assign n294 = n140 & n142;
  assign n161 = n296 | n297 | n294 | n298 | n188 | n301;
  assign n296 = ~FullOHS1 & Rdy2BmHS1 & ~Prog_0 & n222;
  assign n297 = n129_1 & State_0 & ~Rdy1BmHS1;
  assign n298 = ~n299 & ~FullIHS1 & n222;
  assign n299 = ~n223 & ~n300;
  assign n300 = Rdy2RtHS1 & Prog_0;
  assign n301 = ~FullOHS1 & ~Rdy1RtHS1 & ~Prog_2 & n157_1;
  assign n165 = n303 | n267 | n307 | n258 | n280 | n309 | n310;
  assign n303 = n186 & ~n304;
  assign n304 = ~n305 & ~n306;
  assign n305 = State_2 & n142;
  assign n306 = n143 & TpArrayHS1 & ~State_2;
  assign n307 = ~WantBmHS1 & ~n308;
  assign n308 = ~n211 & ~n254;
  assign n309 = n235 & ~n155 & ~n209 & Prog_0;
  assign n310 = n226 & n235;
  assign n169 = n312 | n316 | n317;
  assign n312 = ~n313 & Rdy2RtHS1 & n142 & n259;
  assign n313 = ~n314 & ~n315;
  assign n314 = FullOHS1 & ~Rdy1RtHS1 & ~Prog_2 & Prog_0;
  assign n315 = ~Prog_0 & ~WantBmHS1 & WantRtHS1 & n201;
  assign n316 = ~n181_1 & n210;
  assign n317 = ~n224 & n222 & ~FullIHS1 & n194 & FullOHS1;
  assign n173 = ~OutAvHS1 & ~n128;
  assign n177 = n320 | n258 | n321 | n303 | n322;
  assign n320 = ~FullOHS1 & n265;
  assign n321 = n235 & Prog_0 & ~Rdy1RtHS1 & Rdy2RtHS1;
  assign n322 = InDoneHS1 & ~n323;
  assign n323 = ~n275 & ~n324;
  assign n324 = OutputHS1 & n141;
  assign n181 = n312 | n326 | n316 | n327;
  assign n326 = InDoneHS1 & n249;
  assign n327 = n265 & n222 & FullOHS1 & ~FullIHS1;
  assign n185 = ~OutAvHS1 & FullIHS1;
  assign n189 = ~OutAvHS1 & ~FullIHS1;
  assign n193 = n189_1 & n250;
  assign n197 = n316 | n332;
  assign n332 = ~Prog_0 & ~WantBmHS1 & n174 & WantRtHS1 & Rdy2RtHS1;
  always @ (posedge clock) begin
    State_5 <= n79;
    State_4 <= n84;
    State_3 <= n89;
    State_2 <= n94;
    State_1 <= n99;
    State_0 <= n104;
    ActRtHS1 <= n109;
    ActBmHS1 <= n113;
    GoRtHS1 <= n117;
    GoBmHS1 <= n121;
    NewTrHS1 <= n125;
    ReRtTSHS1 <= n129;
    Mode0HS1 <= n133;
    Mode1HS1 <= n137;
    Mode2HS1 <= n141;
    NewLineHS1 <= n145;
    ShftORHS1 <= n149;
    ShftIRHS1 <= n153;
    LxHInHS1 <= n157;
    TxHInHS1 <= n161;
    LoadOHHS1 <= n165;
    LoadIHHS1 <= n169;
    SeOutAvHS1 <= n173;
    SeFullOHS1 <= n177;
    SeFullIHS1 <= n181;
    TgWhBufHS1 <= n185;
    ReWhBufHS1 <= n189;
    LdProgHS1 <= n193;
    DumpIHS1 <= n197;
  end
endmodule


