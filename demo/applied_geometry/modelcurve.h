#ifndef KWI_MODEL_CURVE_H
#define KWI_MODEL_CURVE_H

//#include "../../gmlib/modules/parametrics/gmpcurve.h"

// stl
#include <vector>
#include <cmath>

#include <parametrics/gmpcurve.h>

using namespace GMlib;

namespace kwi
{
    template <typename T>
    class ModelCurve : public PCurve<T, 3> {
        GM_SCENEOBJECT(ModelCurve)

      public:
        ModelCurve(T a);
        virtual ~ModelCurve();

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
    };   // END class ModelCurve

}   // namespace kwi

// Include ModelCurve class function implementations
#include "modelcurve.c"

#endif   // KWI_MODEL_CURVE_H
