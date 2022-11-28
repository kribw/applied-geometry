#ifndef KWI_P_EPITROCHOID_CURVE_H
#define KWI_P_EPITROCHOID_CURVE_H

//#include "../../gmlib/modules/parametrics/gmpcurve.h"

// stl
#include <vector>
#include <cmath>

#include <parametrics/gmpcurve.h>

using namespace GMlib;

namespace kwi
{
    template <typename T>
    class PEpitrochoidCurve : public PCurve<T, 3> {
        GM_SCENEOBJECT(PEpitrochoidCurve)

      public:
        PEpitrochoidCurve(T a, T b, T c);
        virtual ~PEpitrochoidCurve();

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
    };   // END class PEpitrochoidCurve

}   // namespace kwi

// Include PEpitrochoidCurve class function implementations
#include "pepitrochoidcurve.c"

#endif   // KWI_P_EPITROCHOID_CURVE_H
