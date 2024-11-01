#include "logic_inst.h"
#include "logic.h"

#include <iostream>

using namespace logic;

static void calc_a(op_in &in3, op_in &in2, op_in &in1, op_in &in0, op_not &not_in3, op_not &not_in2, op_not &not_in1,op_not &not_in0, bool &out_value)
{
    // f(a, b, c, d) = b'd' + c + bd + a

    // calc not in2 and not in0
    op_and<2> not_in2_and_not_in0;
    not_in2_and_not_in0.link<0>(not_in2.get_out());
    not_in2_and_not_in0.link<1>(not_in0.get_out());

    // calc in2 and in0
    op_and<2> in2_and_in0;
    in2_and_in0.link<0>(in2.get_out());
    in2_and_in0.link<1>(in0.get_out());

    op_or<4> out_a_or;
    out_a_or.link<0>(not_in2_and_not_in0.get_out());
    out_a_or.link<1>(in1.get_out());
    out_a_or.link<2>(in2_and_in0.get_out());
    out_a_or.link<3>(in3.get_out());

    op_out out_a;
    out_a.link(out_a_or.get_out());

    out_value = out_a.get_value();
}

static void calc_b(op_in &in3, op_in &in2, op_in &in1, op_in &in0, op_not &not_in3, op_not &not_in2, op_not &not_in1,op_not &not_in0, bool &out_value)
{
    // f(a, b, c, d) = b' + c'd' + cd

    // calc not in1 and not in0
    op_and<2> not_in1_and_not_in0;
    not_in1_and_not_in0.link<0>(not_in1.get_out());
    not_in1_and_not_in0.link<1>(not_in0.get_out());

    // calc in1 and in0
    op_and<2> in1_and_in0;
    in1_and_in0.link<0>(in1.get_out());
    in1_and_in0.link<1>(in0.get_out());

    op_or<3> out_b_or;
    out_b_or.link<0>(not_in2.get_out());
    out_b_or.link<1>(not_in1_and_not_in0.get_out());
    out_b_or.link<2>(in1_and_in0.get_out());

    op_out out_b;
    out_b.link(out_b_or.get_out());

    out_value = out_b.get_value();
}

static void calc_c(op_in &in3, op_in &in2, op_in &in1, op_in &in0, op_not &not_in3, op_not &not_in2, op_not &not_in1,op_not &not_in0, bool &out_value)
{
    // f(a, b, c, d) = c' + d + b

    op_or<3> out_c_or;
    out_c_or.link<0>(not_in1.get_out());
    out_c_or.link<1>(in0.get_out());
    out_c_or.link<2>(in2.get_out());

    op_out out_c;
    out_c.link(out_c_or.get_out());

    out_value = out_c.get_value();
}

static void calc_d(op_in &in3, op_in &in2, op_in &in1, op_in &in0, op_not &not_in3, op_not &not_in2, op_not &not_in1,op_not &not_in0, bool &out_value)
{
    // f(a, b, c, d) = b'd' + b'c + bc'd + cd' + a

    // calc not in2 and not in0
    op_and<2> not_in2_and_not_in0;
    not_in2_and_not_in0.link<0>(not_in2.get_out());
    not_in2_and_not_in0.link<1>(not_in0.get_out());

    // calc not in2 and in1
    op_and<2> not_in2_and_in1;
    not_in2_and_in1.link<0>(not_in2.get_out());
    not_in2_and_in1.link<1>(in1.get_out());

    // calc in2 and not in1 and in0
    op_and<3> in2_and_not_in1_and_in0;
    in2_and_not_in1_and_in0.link<0>(in2.get_out());
    in2_and_not_in1_and_in0.link<1>(not_in1.get_out());
    in2_and_not_in1_and_in0.link<2>(in0.get_out());

    // calc in1 and not in0
    op_and<2> in1_and_not_in0;
    in1_and_not_in0.link<0>(in1.get_out());
    in1_and_not_in0.link<1>(not_in0.get_out());

    op_or<5> out_d_or;
    out_d_or.link<0>(not_in2_and_not_in0.get_out());
    out_d_or.link<1>(not_in2_and_in1.get_out());
    out_d_or.link<2>(in2_and_not_in1_and_in0.get_out());
    out_d_or.link<3>(in1_and_not_in0.get_out());
    out_d_or.link<4>(in3.get_out());

    op_out out_d;
    out_d.link(out_d_or.get_out());

    out_value = out_d.get_value();
}

static void calc_e(op_in &in3, op_in &in2, op_in &in1, op_in &in0, op_not &not_in3, op_not &not_in2, op_not &not_in1,op_not &not_in0, bool &out_value)
{
    // f(a, b, c, d) = b'd' + cd'

    // calc not in2 and not in0
    op_and<2> not_in2_and_not_in0;
    not_in2_and_not_in0.link<0>(not_in2.get_out());
    not_in2_and_not_in0.link<1>(not_in0.get_out());

    // calc in1 and not in0
    op_and<2> in1_and_not_in0;
    in1_and_not_in0.link<0>(in1.get_out());
    in1_and_not_in0.link<1>(not_in0.get_out());

    op_or<2> out_e_or;
    out_e_or.link<0>(not_in2_and_not_in0.get_out());
    out_e_or.link<1>(in1_and_not_in0.get_out());

    op_out out_e;
    out_e.link(out_e_or.get_out());

    out_value = out_e.get_value();
}

static void calc_f(op_in &in3, op_in &in2, op_in &in1, op_in &in0, op_not &not_in3, op_not &not_in2, op_not &not_in1,op_not &not_in0, bool &out_value)
{
    // f(a, b, c, d) = c'd' + bc' + bd' + a

    // calc not in1 and not in0
    op_and<2> not_in1_and_not_in0;
    not_in1_and_not_in0.link<0>(not_in1.get_out());
    not_in1_and_not_in0.link<1>(not_in0.get_out());

    // calc in2 and not in1
    op_and<2> in2_and_not_in1;
    in2_and_not_in1.link<0>(in2.get_out());
    in2_and_not_in1.link<1>(not_in1.get_out());

    // calc in2 and not in0
    op_and<2> in2_and_not_in0;
    in2_and_not_in0.link<0>(in2.get_out());
    in2_and_not_in0.link<1>(not_in0.get_out());

    op_or<4> out_f_or;
    out_f_or.link<0>(not_in1_and_not_in0.get_out());
    out_f_or.link<1>(in2_and_not_in1.get_out());
    out_f_or.link<2>(in2_and_not_in0.get_out());
    out_f_or.link<3>(in3.get_out());

    op_out out_f;
    out_f.link(out_f_or.get_out());

    out_value = out_f.get_value();
}

static void calc_g(op_in &in3, op_in &in2, op_in &in1, op_in &in0, op_not &not_in3, op_not &not_in2, op_not &not_in1,op_not &not_in0, bool &out_value)
{
    // f(a, b, c, d) = b'c + bc' + a + cd'

    // calc not in2 and in1
    op_and<2> not_in2_and_in1;
    not_in2_and_in1.link<0>(not_in2.get_out());
    not_in2_and_in1.link<1>(in1.get_out());

    // calc in2 and not in1
    op_and<2> in2_and_not_in1;
    in2_and_not_in1.link<0>(in2.get_out());
    in2_and_not_in1.link<1>(not_in1.get_out());

    // calc in1 and not in0
    op_and<2> in1_and_not_in0;
    in1_and_not_in0.link<0>(in1.get_out());
    in1_and_not_in0.link<1>(not_in0.get_out());

    op_or<4> out_g_or;
    out_g_or.link<0>(not_in2_and_in1.get_out());
    out_g_or.link<1>(in2_and_not_in1.get_out());
    out_g_or.link<2>(in1_and_not_in0.get_out());
    out_g_or.link<3>(in3.get_out());

    op_out out_g;
    out_g.link(out_g_or.get_out());

    out_value = out_g.get_value();
}

void logic_inst::run(int digit, bool v[7])
{
    op_in in0;
    op_in in1;
    op_in in2;
    op_in in3;

    int a = digit >> 3 & 1;
    int b = digit >> 2 & 1;
    int c = digit >> 1 & 1;
    int d = digit & 1;

    in0.set_value(d);
    in1.set_value(c);
    in2.set_value(b);
    in3.set_value(a);

    op_not not_in3;
    op_not not_in2;
    op_not not_in1;
    op_not not_in0;

    not_in3.link(in3.get_out());
    not_in2.link(in2.get_out());
    not_in1.link(in1.get_out());
    not_in0.link(in0.get_out());

    bool out_a = false;
    bool out_b = false;
    bool out_c = false;
    bool out_d = false;
    bool out_e = false;
    bool out_f = false;
    bool out_g = false;

    std::cout << "digit=" << digit;
    std::cout << " in3=" << a << " in2=" << b << " in1=" << c << " in0=" << d;
    calc_a(in3, in2, in1, in0, not_in3, not_in2, not_in1, not_in0, out_a);
    calc_b(in3, in2, in1, in0, not_in3, not_in2, not_in1, not_in0, out_b);
    calc_c(in3, in2, in1, in0, not_in3, not_in2, not_in1, not_in0, out_c);
    calc_d(in3, in2, in1, in0, not_in3, not_in2, not_in1, not_in0, out_d);
    calc_e(in3, in2, in1, in0, not_in3, not_in2, not_in1, not_in0, out_e);
    calc_f(in3, in2, in1, in0, not_in3, not_in2, not_in1, not_in0, out_f);
    calc_g(in3, in2, in1, in0, not_in3, not_in2, not_in1, not_in0, out_g);
    std::cout << " A=" << out_a << " B=" << out_b << " C=" << out_c << " D=" << out_d
        << " E=" << out_e << " F=" << out_f << " G=" << out_g << std::endl;

    v[0] = out_a;
    v[1] = out_b;
    v[2] = out_c;
    v[3] = out_d;
    v[4] = out_e;
    v[5] = out_f;
    v[6] = out_g;
}