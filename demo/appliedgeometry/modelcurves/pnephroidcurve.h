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
    class PNephroidCurve : public PCurve<T, 3> {
        GM_SCENEOBJECT(PNephroidCurve)

      public:
        PNephroidCurve(T a);
        virtual ~PNephroidCurve();

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
    };   // END class PNephroidCurve

}   // namespace kwi

// Include PNephroidCurve class function implementations
#include "pnephroidcurve.c"

#endif   // KWI_P_LISSAJOUS_CURVE_H
