// Licensed to the .NET Foundation under one or more agreements.
// The .NET Foundation licenses this file to you under the MIT license.
#include "common.h"
#include "CommonTypes.h"
#include "CommonMacros.h"
#include "rhassert.h"

//
// Floating point and 64-bit integer math helpers.
//

FCIMPL1_D(uint64_t, RhpDbl2ULng, double val)
{
    const double two63  = 2147483648.0 * 4294967296.0;
    uint64_t ret;
    if (val < two63)
    {
        ret = (int64_t)(val);
    }
    else
    {
        // subtract 0x8000000000000000, do the convert then add it back again
        ret = (int64_t)(val - two63) + I64(0x8000000000000000);
    }
    return ret;
}
FCIMPLEND

#undef min
#undef max
#include <cmath>

FCIMPL2_FF(float, RhpFltRem, float dividend, float divisor)
{
    //
    // From the ECMA standard:
    //
    // If [divisor] is zero or [dividend] is infinity
    //   the result is NaN.
    // If [divisor] is infinity,
    //   the result is [dividend] (negated for -infinity***).
    //
    // ***"negated for -infinity" has been removed from the spec
    //

    if (divisor==0 || !std::isfinite(dividend))
    {
        return -nanf("");
    }
    else if (!std::isfinite(divisor) && !std::isnan(divisor))
    {
        return dividend;
    }
    // else...
    return fmodf(dividend,divisor);
}
FCIMPLEND

FCIMPL2_DD(double, RhpDblRem, double dividend, double divisor)
{
    //
    // From the ECMA standard:
    //
    // If [divisor] is zero or [dividend] is infinity
    //   the result is NaN.
    // If [divisor] is infinity,
    //   the result is [dividend] (negated for -infinity***).
    //
    // ***"negated for -infinity" has been removed from the spec
    //
    if (divisor==0 || !std::isfinite(dividend))
    {
        return -nan("");
    }
    else if (!std::isfinite(divisor) && !std::isnan(divisor))
    {
        return dividend;
    }
    // else...
    return(fmod(dividend,divisor));
}
FCIMPLEND

#ifndef HOST_64BIT
EXTERN_C int64_t QCALLTYPE RhpLDiv(int64_t i, int64_t j)
{
    ASSERT(j && "Divide by zero!");
    return i / j;
}

EXTERN_C uint64_t QCALLTYPE RhpULDiv(uint64_t i, uint64_t j)
{
    ASSERT(j && "Divide by zero!");
    return i / j;
}

EXTERN_C int64_t QCALLTYPE RhpLMod(int64_t i, int64_t j)
{
    ASSERT(j && "Divide by zero!");
    return i % j;
}

EXTERN_C uint64_t QCALLTYPE RhpULMod(uint64_t i, uint64_t j)
{
    ASSERT(j && "Divide by zero!");
    return i % j;
}

FCIMPL1_D(int64_t, RhpDbl2Lng, double val)
{
    return (int64_t)val;
}
FCIMPLEND

FCIMPL1_D(int32_t, RhpDbl2Int, double val)
{
    return (int32_t)val;
}
FCIMPLEND

FCIMPL1_D(uint32_t, RhpDbl2UInt, double val)
{
    return (uint32_t)val;
}
FCIMPLEND

FCIMPL1_L(double, RhpLng2Dbl, int64_t val)
{
    return (double)val;
}
FCIMPLEND

FCIMPL1_L(double, RhpULng2Dbl, uint64_t val)
{
    return (double)val;
}
FCIMPLEND

#endif

#ifdef HOST_ARM
EXTERN_C int32_t F_CALL_CONV RhpIDiv(int32_t i, int32_t j)
{
    ASSERT(j && "Divide by zero!");
    return i / j;
}

EXTERN_C uint32_t F_CALL_CONV RhpUDiv(uint32_t i, uint32_t j)
{
    ASSERT(j && "Divide by zero!");
    return i / j;
}

EXTERN_C int32_t F_CALL_CONV RhpIMod(int32_t i, int32_t j)
{
    ASSERT(j && "Divide by zero!");
    return i % j;
}

EXTERN_C uint32_t F_CALL_CONV RhpUMod(uint32_t i, uint32_t j)
{
    ASSERT(j && "Divide by zero!");
    return i % j;
}

EXTERN_C int64_t F_CALL_CONV RhpLMul(int64_t i, int64_t j)
{
    return i * j;
}

EXTERN_C uint64_t F_CALL_CONV RhpLRsz(uint64_t i, int32_t j)
{
    return i >> (j & 0x3f);
}

EXTERN_C int64_t F_CALL_CONV RhpLRsh(int64_t i, int32_t j)
{
    return i >> (j & 0x3f);
}

EXTERN_C int64_t F_CALL_CONV RhpLLsh(int64_t i, int32_t j)
{
    return i << (j & 0x3f);
}

#endif // HOST_ARM

#ifdef HOST_X86

FCIMPL1_D(double, acos, double x)
    return std::acos(x);
FCIMPLEND

FCIMPL1_F(float, acosf, float x)
    return std::acosf(x);
FCIMPLEND

FCIMPL1_D(double, acosh, double x)
    return std::acosh(x);
FCIMPLEND

FCIMPL1_F(float, acoshf, float x)
    return std::acoshf(x);
FCIMPLEND

FCIMPL1_D(double, asin, double x)
    return std::asin(x);
FCIMPLEND

FCIMPL1_F(float, asinf, float x)
    return std::asinf(x);
FCIMPLEND

FCIMPL1_D(double, asinh, double x)
    return std::asinh(x);
FCIMPLEND

FCIMPL1_F(float, asinhf, float x)
    return std::asinhf(x);
FCIMPLEND

FCIMPL1_D(double, atan, double x)
    return std::atan(x);
FCIMPLEND

FCIMPL1_F(float, atanf, float x)
    return std::atanf(x);
FCIMPLEND

FCIMPL2_DD(double, atan2, double x, double y)
    return std::atan2(x, y);
FCIMPLEND

FCIMPL2_FF(float, atan2f, float x, float y)
    return std::atan2f(x, y);
FCIMPLEND

FCIMPL1_D(double, atanh, double x)
    return std::atanh(x);
FCIMPLEND

FCIMPL1_F(float, atanhf, float x)
    return std::atanhf(x);
FCIMPLEND

FCIMPL1_D(double, cbrt, double x)
    return std::cbrt(x);
FCIMPLEND

FCIMPL1_F(float, cbrtf, float x)
    return std::cbrtf(x);
FCIMPLEND

FCIMPL1_D(double, ceil, double x)
    return std::ceil(x);
FCIMPLEND

FCIMPL1_F(float, ceilf, float x)
    return std::ceilf(x);
FCIMPLEND

FCIMPL1_D(double, cos, double x)
    return std::cos(x);
FCIMPLEND

FCIMPL1_F(float, cosf, float x)
    return std::cosf(x);
FCIMPLEND

FCIMPL1_D(double, cosh, double x)
    return std::cosh(x);
FCIMPLEND

FCIMPL1_F(float, coshf, float x)
    return std::coshf(x);
FCIMPLEND

FCIMPL1_D(double, exp, double x)
    return std::exp(x);
FCIMPLEND

FCIMPL1_F(float, expf, float x)
    return std::expf(x);
FCIMPLEND

FCIMPL1_D(double, floor, double x)
    return std::floor(x);
FCIMPLEND

FCIMPL1_F(float, floorf, float x)
    return std::floorf(x);
FCIMPLEND

FCIMPL1_D(double, log, double x)
    return std::log(x);
FCIMPLEND

FCIMPL1_F(float, logf, float x)
    return std::logf(x);
FCIMPLEND

FCIMPL1_D(double, log2, double x)
    return std::log2(x);
FCIMPLEND

FCIMPL1_F(float, log2f, float x)
    return std::log2f(x);
FCIMPLEND

FCIMPL1_D(double, log10, double x)
    return std::log10(x);
FCIMPLEND

FCIMPL1_F(float, log10f, float x)
    return std::log10f(x);
FCIMPLEND

FCIMPL2_DD(double, pow, double x, double y)
    return std::pow(x, y);
FCIMPLEND

FCIMPL2_FF(float, powf, float x, float y)
    return std::powf(x, y);
FCIMPLEND

FCIMPL1_D(double, sin, double x)
    return std::sin(x);
FCIMPLEND

FCIMPL1_F(float, sinf, float x)
    return std::sinf(x);
FCIMPLEND

FCIMPL1_D(double, sinh, double x)
    return std::sinh(x);
FCIMPLEND

FCIMPL1_F(float, sinhf, float x)
    return std::sinhf(x);
FCIMPLEND

FCIMPL1_D(double, sqrt, double x)
    return std::sqrt(x);
FCIMPLEND

FCIMPL1_F(float, sqrtf, float x)
    return std::sqrtf(x);
FCIMPLEND

FCIMPL1_D(double, tan, double x)
    return std::tan(x);
FCIMPLEND

FCIMPL1_F(float, tanf, float x)
    return std::tanf(x);
FCIMPLEND

FCIMPL1_D(double, tanh, double x)
    return std::tanh(x);
FCIMPLEND

FCIMPL1_F(float, tanhf, float x)
    return std::tanhf(x);
FCIMPLEND

FCIMPL3_DDD(double, fma, double x, double y, double z)
    return std::fma(x, y, z);
FCIMPLEND

FCIMPL3_FFF(float, fmaf, float x, float y, float z)
    return std::fmaf(x, y, z);
FCIMPLEND

FCIMPL2_DI(double, modf, double x, double* intptr)
    return std::modf(x, intptr);
FCIMPLEND

FCIMPL2_FI(float, modff, float x, float* intptr)
    return std::modff(x, intptr);
FCIMPLEND

#endif
