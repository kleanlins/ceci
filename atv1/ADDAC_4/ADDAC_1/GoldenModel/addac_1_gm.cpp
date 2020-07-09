#include "addac_1_gm.hpp"

ADDAC::ADDAC(int order) : S(0), cout(0), acc(0), cinLocal(0), order(order), flop(){};

int ADDAC::getOrdem()
{
    return order;
}

std::tuple<int, int> ADDAC::solve(int a, int sel0, int sel1, int clk, int reset, int cin)
{
    int inv = inversor(a);
    int mux1 = mux(a, inv, sel0);

    if (order == 0)
    {
        cin = sel0;
        cinLocal = cin;
    }
    cinLocal = cin;

    int soma1 = soma(mux1, acc, cin);
    cout = carry(mux1, acc, cin);
    int mux2 = mux(mux1, soma1, sel1);

    acc = flop.solve(mux2, reset, clk);
    soma1 = soma(mux1, acc, cin);
    cout = carry(mux1, acc, cin);
    mux2 = mux(mux1, soma1, sel1);

    S = mux2;

    return {S, cout};
}

int ADDAC::getCin()
{
    return cinLocal;
}

int ADDAC::getAcc()
{
    return acc;
}