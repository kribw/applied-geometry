#ifndef KWI_BLENDING_SPLINE_H
#define KWI_BLENDING_SPLINE_H

#include "../../gmlib/modules/parametrics/gmpcurve.h"
#include "../../gmlib/modules/parametrics/curves/gmpsubcurve.h"

// stl
#include <vector>

using namespace GMlib;

namespace kwi
{
    template <typename T>
    class BlendingSpline : public PCurve<T, 3> {
        GM_SCENEOBJECT(BlendingSpline)

      public:
        BlendingSpline(PCurve<T, 3>* mc, const int n);
        virtual ~BlendingSpline();

        //****************************************
        //****** Virtual public functions   ******
        //****************************************
        // from PCurve
        bool isClosed() const override;

      protected:
        // Virtual functions from PCurve, which have to be implemented locally
        void eval(T t, int d, bool l) const override;
        void localSimulate(double dt) override;
        T    getStartP() const override;
        T    getEndP() const override;

        int                        _d;    // degree
        int                        _k;    // order
        std::vector<T>             _t;    // knot vector
        int                        _n;    // no. control curves
        PCurve<T, 3>*              _mc;   // model curve
        std::vector<PCurve<T, 3>*> _lc;   // local curves

      private:
        void create_knot_vector(const int n);
        void create_local_curves(const int n);
        T    get_w(const int d, const int i, const T t) const;
        int  get_i(const T t) const;
        T    get_b(const T t) const;
    };   // END class BlendingSpline

}   // namespace kwi

// Include BlendingSpline class function implementations
#include "blendingspline.c"

#endif   // KWI_BLENDING_SPLINE_H
