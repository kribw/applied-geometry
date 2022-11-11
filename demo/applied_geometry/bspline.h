#ifndef KWI_B_SPLINE_H
#define KWI_B_SPLINE_H

#include "../../gmlib/modules/parametrics/gmpcurve.h"

// stl
#include <vector>

using namespace GMlib;

namespace kwi
{
    template <typename T>
    class BSpline : public PCurve<T, 3> {
        GM_SCENEOBJECT(BSpline)

      public:
        BSpline();
        BSpline(const DVector<Vector<T, 3>>& c);
        BSpline(const DVector<Vector<T, 3>>& p, int n);
        virtual ~BSpline();

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

        int                       _d;   // dimension
        int                       _k;   // order
        DVector<Vector<float, 3>> _c;   // control points
        std::vector<T>            _t;   // knot vector

      private:
        void create_knot_vector(const int n);
        T    get_w(const int d, const int i, const T t) const;
        int  get_i(const T t) const;
        int  get_basis(const T t, T& x, T& y, T& z) const;
        DVector<Vector<T, 3>>
        create_control_points(const DVector<Vector<T, 3>>& p, int n) const;
    };   // END class PCircle

}   // namespace kwi

// Include PCircle class function implementations
//#include "../../gmlib/modules/parametrics/curves/gmpcircle.c"
#include "bspline.c"

#endif   // KWI_B_SPLINE_H
