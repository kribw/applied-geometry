#ifndef KWI_P_ASTROID_CURVE_H
#define KWI_P_ASTROID_CURVE_H

//#include "../../gmlib/modules/parametrics/gmpcurve.h"

// stl
#include <vector>
#include <cmath>

#include <parametrics/gmpcurve.h>

using namespace GMlib;

namespace kwi
{
    template <typename T>
    class PAstroidCurve : public PCurve<T, 3> {
        GM_SCENEOBJECT(PAstroidCurve)

      public:
        PAstroidCurve(T a);
        virtual ~PAstroidCurve();

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
    };   // END class PAstroidCurve

}   // namespace kwi

// Include PAstroidCurve class function implementations
#include "pastroidcurve.c"

#endif   // KWI_P_ASTROID_CURVE_H
