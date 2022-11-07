#ifndef KWI_B_SPLINE_H
#define KWI_B_SPLINE_H

#include "../../gmlib/modules/parametrics/gmpcurve.h"

//#include "../../gmlib/modules/core/types/gmangle.h"

// stl
#include <vector>

namespace kwi
{
    template <typename T>
    class BSpline : public PCurve<T, 3> {
        GM_SCENEOBJECT(BSpline)

      public:
        BSpline();
        BSpline(const GMlib::DVector<GMlib::Vector<T, 3>>& c);
        BSpline(const GMlib::DVector<GMlib::Vector<T, 3>>& p, int n);
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

        // Protected data for the curve
        T _rx;
        T _ry;

        int                                     _d;   // dimension
        int                                     _k;   // order
        GMlib::DVector<GMlib::Vector<float, 3>> _c;   // control points
        std::vector<T>                          _t;   // knot vector

      private:
        T    getDeltaP() const;
        void create_knot_vector(int n);
        T    get_w(int d, int i, T t) const;
        int  get_i(T t) const;
        int  get_basis(T t, T& p1, T& p2, T& p3) const;

    };   // END class PCircle

}   // namespace kwi

// Include PCircle class function implementations
//#include "../../gmlib/modules/parametrics/curves/gmpcircle.c"
#include "bspline.c"

#endif   // KWI_B_SPLINE_H
