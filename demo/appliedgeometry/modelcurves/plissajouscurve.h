#ifndef KWI_P_LISSAJOUS_CURVE_H
#define KWI_P_LISSAJOUS_CURVE_H

//#include "../../gmlib/modules/parametrics/gmpcurve.h"

// stl
#include <vector>
#include <cmath>

#include <parametrics/gmpcurve.h>

using namespace GMlib;

namespace kwi
{
    template <typename T>
    class PLissajousCurve : public PCurve<T, 3> {
        GM_SCENEOBJECT(PLissajousCurve)

      public:
        PLissajousCurve(T a, T b, T c, T n);
        virtual ~PLissajousCurve();

        //****************************************
        //****** Virtual public functions   ******
        //****************************************
        // from PCurve
        bool isClosed() const override;

      protected:
        // Virtual functions from PCurve, which have to be implemented locally
        void eval(T t, int d, bool l) const override;
        T    getStartP() const override;
        T    getEndP() const override;

      private:
        T _a;
        T _b;
        T _c;
        T _n;
    };   // END class PLissajousCurve

}   // namespace kwi

// Include PLissajousCurve class function implementations
#include "plissajouscurve.c"

#endif   // KWI_P_LISSAJOUS_CURVE_H
