#ifndef KWI_P_CLOSED_SUB_DIV_CURVE_H
#define KWI_P_CLOSED_SUB_DIV_CURVE_H

#include "../../gmlib/modules/parametrics/gmpcurve.h"

// stl
#include <vector>
#include <cmath>

using namespace GMlib;

namespace kwi
{
    template <typename T>
    class PClosedSubDivCurve : public PCurve<T, 3> {
        GM_SCENEOBJECT(PClosedSubDivCurve)

      public:
        PClosedSubDivCurve();
        PClosedSubDivCurve(const DVector<Vector<T, 3>>& p, int d);
        virtual ~PClosedSubDivCurve();

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
        void laneRiesenfeldClosed(std::vector<DVector<Vector<T, 3>>>& p, int k,
                                  int d) const;
        int  doublePart(std::vector<DVector<Vector<T, 3>>>& p, int n) const;
        void smoothPartClosed(std::vector<DVector<Vector<T, 3>>>& p, int n,
                              int d) const;
    };   // END class PClosedSubDivCurve

}   // namespace kwi

// Include PClosedSubDivCurve class function implementations
#include "pclosedsubdivcurve.c"

#endif   // KWI_P_CLOSED_SUB_DIV_CURVE_H
