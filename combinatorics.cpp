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
    if (m > n)
        return 0;

    UI result = 1;
    for (UI i = 1; i <= m; ++i)
    {
        if (double(UINT_MAX - result) / double(result) < double(n))
            throw runtime_error("number is very big, sorry");
        else
            result *= n;
    }

    return result;
}

UI P(UI n)
{
    UI result = 1;
    for (UI i = 1; i <= n; ++i)
    {
        if (double(UINT_MAX - result) / double(result) < double(i))
            throw runtime_error("number is very big, sorry");
        else
            result *= i;
    }
    return result;
}

UI A(UI m, UI n)
{
    if (m > n)
        return 0;

    UI result = 1;
    for (UI i = n - m + 1; i <= n; ++i)
    {
        if (double(UINT_MAX - result) / double(result) < double(i))
            throw runtime_error("number is very big, sorry");
        else
            result *= i;
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

    UI result = 1;
    for (auto& i : numerator)
    {
        if (double(UINT_MAX - result) / double(result) < double(i))
            throw runtime_error("number is very big, sorry");
        else
            result *= i;
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

    vector<UI> D(d);
    for (UI i = 0; i != d; D[i++] = 1);

    if (d == m)
    {
        for (UI i = 1; i != s; ++i)
        {
            for (UI j = 1; j != d; ++j)
            {
                if (UINT_MAX - (j + 1) * D[j] < D[j-1])
                    throw runtime_error("number is very big, sorry");
                D[j] = D[j-1] + (j + 1) * D[j];
            }
        }
    }
    else
    {
        for (UI i = 1; i != s; ++i)
        {
            for (UI j = 1; j != d; ++j)
            {
                if (UINT_MAX - (i + 1) * D[j-1] < D[j])
                    throw runtime_error("number is very big, sorry");
                D[j] = D[j] + (i + 1) * D[j-1];
            }
        }
    }
    return D[d-1];
}

UI B(UI n)
{
    UI res = 0;
    for (UI m = 1; m <= n; ++m)
    {
        try {
            UI temp = S(m, n);
            res += temp;
        } catch (runtime_error& error) {
            throw;
        }
    }
    return res;
}

//combinatorics::combinatorics()
//{

//}
