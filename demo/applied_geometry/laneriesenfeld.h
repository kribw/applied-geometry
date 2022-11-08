#ifndef KWI_B_SPLINE_H
#define KWI_B_SPLINE_H

#include "../../gmlib/modules/parametrics/gmpcurve.h"

// stl
#include <vector>

using namespace GMlib;

namespace kwi
{
    template <typename T>
    class LaneRiesenfeld : public PCurve<T, 3> {
        GM_SCENEOBJECT(LaneRiesenfeld)

      public:
        LaneRiesenfeld();
        LaneRiesenfeld(const DVector<Vector<T, 3>>& c);
        LaneRiesenfeld(const DVector<Vector<T, 3>>& p, int n);
        virtual ~LaneRiesenfeld();

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

        // Protected data for the curve
        T _rx;
        T _ry;

        int                       _d;   // dimension
        int                       _k;   // order
        DVector<Vector<float, 3>> _c;   // control points
        std::vector<T>            _t;   // knot vector

      private:
        T    getDeltaP() const;
        DVector<Vector<float, 3>> lane_riesenfeld_closed(DVector<Vector<float, 3>> p, int k, int d);
        int double_part(DVector<Vector<float, 3>> p, int n);
        void smooth_part_closed(DVector<Vector<float, 3>> p, int n, int d);
    };   // END class PCircle

}   // namespace kwi

// Include PCircle class function implementations
//#include "../../gmlib/modules/parametrics/curves/gmpcircle.c"
#include "bspline.c"

#endif   // KWI_B_SPLINE_H
