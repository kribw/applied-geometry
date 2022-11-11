#ifndef KWI_CLOSED_SUB_DIV_CURVE_H
#define KWI_CLOSED_SUB_DIV_CURVE_H

#include "../../gmlib/modules/parametrics/gmpcurve.h"

// stl
#include <vector>
#include <cmath>

using namespace GMlib;

namespace kwi
{
    template <typename T>
    class ClosedSubDivCurve : public PCurve<T, 3> {
        GM_SCENEOBJECT(ClosedSubDivCurve)

      public:
        ClosedSubDivCurve();
        ClosedSubDivCurve(const DVector<Vector<T, 3>>& p, int d);
        virtual ~ClosedSubDivCurve();

        //****************************************
        //****** Virtual public functions   ******
        //****************************************
        // from PCurve
        bool isClosed() const override;
        void sample(int m, int d) override;

      protected:
        // Virtual functions from PCurve, which have to be implemented locally
        void eval(T t, int d, bool l) const override;
        T    getStartP() const override;
        T    getEndP() const override;

        int                       _d;        // degree
        DVector<Vector<float, 3>> _points;   // points

      private:
        DVector<Vector<float, 3>>
             laneRiesenfeldClosed(DVector<Vector<float, 3>> p, int k, int d);
        int  doublePart(DVector<Vector<float, 3>> p, int n);
        void smoothPartClosed(DVector<Vector<float, 3>> p, int n, int d);
    };   // END class PCircle

}   // namespace kwi

// Include PCircle class function implementations
#include "closedsubdivcurve.c"

#endif   // KWI_CLOSED_SUB_DIV_CURVE_H
