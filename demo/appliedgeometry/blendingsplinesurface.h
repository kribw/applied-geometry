#ifndef KWI_BLENDING_SPLINE_SURFACE_H
#define KWI_BLENDING_SPLINE_SURFACE_H

#include "../../gmlib/modules/parametrics/gmpcurve.h"
#include "../../gmlib/modules/parametrics/curves/gmpsubcurve.h"

#include "simplesubsurf.h"

// stl
#include <vector>
#include <tuple>

using namespace GMlib;

namespace kwi
{
    template <typename T>
    class BlendingSplineSurface : public PSurf<T, 3> {
        GM_SCENEOBJECT(BlendingSplineSurface)

      public:
        BlendingSplineSurface(PSurf<T, 3>* mc, const int nu, const int nv);
        virtual ~BlendingSplineSurface();

        //****************************************
        //****** Virtual public functions   ******
        //****************************************
      protected:
        // Virtual functions from PSurf, which have to be implemented locally
        void eval(T u, T v, int d1, int d2, bool lu = true,
                  bool lv = true) const override;
        T    getStartPU() const override;
        T    getEndPU() const override;
        T    getStartPV() const override;
        T    getEndPV() const override;
        bool isClosedU() const override;
        bool isClosedV() const override;
        //void localSimulate(double dt) override;

        int                   _d;    // degree
        int                   _k;    // order
        std::vector<T>        _u;    // knot vector in u-direction
        std::vector<T>        _v;    // knot vector in v-direction
        int                   _nu;   // no. control points in u-direction
        int                   _nv;   // no. control points in v-direction
        PSurf<T, 3>*          _ms;   // model surface
        DMatrix<PSurf<T, 3>*> _ls;   // local surfaces

      private:
        void create_knot_vector(std::vector<T>& knot_vector, const int n,
                                const bool is_closed, const T start,
                                const T delta);
        void create_closed_knot_vector(std::vector<T>& knot_vector, const int n,
                                       const T start, const T delta);
        void create_open_knot_vector(std::vector<T>& knot_vector, const int n);
        void create_local_surfaces();
        int  get_index(const std::vector<T>& knot_vector, const int n,
                       const T t) const;
        std::tuple<T, T> get_w(const std::vector<T>& knot_vector, const int d,
                               const int i, const T t) const;
        std::tuple<T, T> get_b(const T t) const;
    };   // END class BlendingSplineSurface

}   // namespace kwi

// Include BlendingSplineSurface class function implementations
#include "blendingsplinesurface.c"

#endif   // KWI_BLENDING_SPLINE_SURFACE_H
