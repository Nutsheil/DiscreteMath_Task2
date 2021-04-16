#include "combinatorics.h"

#include <iostream>
#include <vector>

using namespace std;

UI GCD(UI a, UI b)
{
    return b ? GCD(b, a % b) : a;
}

void Reduction(vector<UI> &numerator, vector<UI> &denominator)
{
    for (auto &j : denominator)
    {
        auto i = numerator.begin();
        while (j != 1)
        {
            UI gcd = GCD(*i, j);
            *i /= gcd;
            j /= gcd;

            if (*i == 1)
                numerator.erase(i);
            i++;
        }
    }
}

UI U(UI m, UI n)
{
    if (n == 1)
        return 1;

    double result = 1;
    for (UI i = 1; i <= m; ++i)
    {
        result *= n;
        if (result > UINT_MAX)
            throw runtime_error("number is very big, sorry");
    }
    return result;
}

UI P(UI n)
{
    double result = 1;
    for (UI i = 1; i <= n; ++i)
    {
        result *= i;
        if (result > UINT_MAX)
            throw runtime_error("number is very big, sorry");
    }
    return result;
}

UI A(UI m, UI n)
{
    if (m > n)
        return 0;

    double result = 1;
    for (UI i = n - m + 1; i <= n; ++i)
    {
        result *= i;
        if (result > UINT_MAX)
            throw runtime_error("number is very big, sorry");
    }
    return result;
}

UI C(UI m, UI n)
{
    if (m > n)
        return 0;
    if (m == n)
        return 1;
    if (m == 0)
        return 1;
    if (m == 1)
        return n;

    // tipa 4to-bi srazu otseyatb big number
    if (n > 100 && (m > 10 && m < n - 10))
        throw runtime_error("number is very big, sorry");
    // kak-to tak


    vector<UI> numerator;
    vector<UI> denominator;

    if (m < n - m)
    {
        for (UI i = 1; i <= m; ++i)
        {
            numerator.push_back(n - m + i);
            denominator.push_back(i);
        }
    }
    else
    {
        for (UI i = 1; i <= n - m; ++i)
        {
            numerator.push_back(m + i);
            denominator.push_back(i);
        }
    }

    Reduction(numerator, denominator);

    double result = 1;
    for (auto& i : numerator)
    {
        result *= i;
        if (result > UINT_MAX)
            throw runtime_error("number is very big, sorry");
    }
    return result;
}

UI S(UI m, UI n)
{
    if (m == 0)
        return 0;
    if (m > n)
        return 0;
    if (m == n)
        return 1;
    if (n == 1)
        return 1;

    UI d = m < n-m+1 ? m : n-m+1;
    UI s = m < n-m+1 ? n-m+1 : m;

    vector<double> D(d);
    for (UI i = 0; i != d; D[i++] = 1);

    if (d == m)
    {
        for (UI i = 1; i != s; ++i)
        {
            for (UI j = 1; j != d; ++j)
            {
                D[j] = D[j-1] + (j + 1) * D[j];
                if (D[j] > UINT_MAX)
                    throw runtime_error("number is very big, sorry");
            }
        }
    }
    else
    {
        for (UI i = 1; i != s; ++i)
        {
            for (UI j = 1; j != d; ++j)
            {
                D[j] = D[j] + (i + 1) * D[j-1];
                if (D[j] > UINT_MAX)
                    throw runtime_error("number is very big, sorry");
            }
        }
    }
    return D[d-1];
}

UI B(UI n)
{
    if (n == 0)
        return 1;

    double res = 0;
    for (UI m = 1; m <= n; ++m)
    {
        try {
            UI temp = S(m, n);
            res += temp;
            if (res > UINT_MAX)
                throw runtime_error("number is very big, sorry");
        } catch (runtime_error& error) {
            throw;
        }
    }
    return res;
}
