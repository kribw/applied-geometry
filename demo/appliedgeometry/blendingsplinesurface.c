namespace kwi
{
    // *************************
    // Public functions
    // *************************
    using namespace GMlib;

    template <typename T>
    BlendingSplineSurface<T>::BlendingSplineSurface(PSurf<T, 3>* ms,
                                                    const int nu, const int nv)
    {
        _d  = 1;        // degree
        _k  = _d + 1;   // order
        _nu = nu;       // no. control curves
        _nv = nv;       // no. control curves
        _ms = ms;       // set model surface

        // Create knot vectors and local surfaces
        create_knot_vector(_u, _nu, isClosedU(), getStartPU(), getEndPU());
        create_knot_vector(_v, _nv, isClosedV(), getStartPV(), getEndPV());
        create_local_surfaces();
    }

    template <typename T>
    BlendingSplineSurface<T>::~BlendingSplineSurface()
    {
    }

    // *************************
    // Protected functions
    // *************************

    template <typename T>
    void BlendingSplineSurface<T>::eval(T u, T v, int d1, int d2, bool /*lu*/,
                                        bool /*lv*/) const
    {
        // Thanks to Jan for helping me out  with the
        // calculations in the eval function!

        // Set dim (derivatives + 1)
        this->_p.setDim(d1 + 1, d2 + 1);   // (2, 2)

        int              i_u = get_index(_u, _nu, u);
        int              i_v = get_index(_v, _nv, v);
        std::tuple<T, T> w_u = get_w(_u, _d, i_u, u);
        std::tuple<T, T> w_v = get_w(_v, _d, i_v, v);
        std::tuple<T, T> b_u = get_b(std::get<1>(w_u));
        std::tuple<T, T> b_v = get_b(std::get<1>(w_v));

        DMatrix<Vector<T, 3>> s00
          = _ls(i_u - 1)(i_v - 1)->evaluateParent(u, v, d1, d2);
        DMatrix<Vector<T, 3>> s01
          = _ls(i_u - 1)(i_v)->evaluateParent(u, v, d1, d2);
        DMatrix<Vector<T, 3>> s10
          = _ls(i_u)(i_v - 1)->evaluateParent(u, v, d1, d2);
        DMatrix<Vector<T, 3>> s11 = _ls(i_u)(i_v)->evaluateParent(u, v, d1, d2);

        const T u1  = 1 - std::get<0>(b_u);
        const T u2  = std::get<0>(b_u);
        const T v1  = 1 - std::get<0>(b_v);
        const T v2  = std::get<0>(b_v);
        const T du1 = -std::get<1>(b_u) * std::get<1>(w_u);
        const T du2 = std::get<1>(b_u) * std::get<1>(w_u);
        const T dv1 = -std::get<1>(b_v) * std::get<1>(w_v);
        const T dv2 = std::get<1>(b_v) * std::get<1>(w_v);

        // position
        _p[0][0] = u1 * v1 * s00(0)(0) + u2 * v1 * s10(0)(0)
                   + u1 * v2 * s01(0)(0) + u2 * v2 * s11(0)(0);

        // partial derivative u-direction
        _p[0][1] = du1 * v1 * s00(0)(0) + du2 * v1 * s10(0)(0)
                   + du1 * v2 * s01(0)(0) + du2 * v2 * s11(0)(0)
                   + u1 * v1 * s00(0)(1) + u2 * v1 * s10(0)(1)
                   + u1 * v2 * s01(0)(1) + u2 * v2 * s11(0)(1);

        // partial derivative v-direction
        _p[1][0] = u1 * dv1 * s00(0)(0) + u2 * dv1 * s10(0)(0)
                   + +u1 * dv2 * s01(0)(0) + u2 * dv2 * s11(0)(0)
                   + u1 * v1 * s00(1)(0) + u2 * v1 * s10(1)(0)
                   + u1 * v2 * s01(1)(0) + u2 * v2 * s11(1)(0);

        // dont need _p[1][1]
    }

    template <typename T>
    void BlendingSplineSurface<T>::localSimulate(double dt)
    {
        this->sample(_visu[0][0][0], _visu[0][0][1], 1, 1);
    }

    template <typename T>
    inline T BlendingSplineSurface<T>::getStartPU() const
    {
        return _ms->getParStartU();
    }

    template <typename T>
    inline T BlendingSplineSurface<T>::getEndPU() const
    {
        return _ms->getParEndU();
    }

    template <typename T>
    inline T BlendingSplineSurface<T>::getStartPV() const
    {
        return _ms->getParStartV();
    }

    template <typename T>
    inline T BlendingSplineSurface<T>::getEndPV() const
    {
        return _ms->getParEndV();
    }

    template <typename T>
    inline bool BlendingSplineSurface<T>::isClosedU() const
    {
        return _ms->isClosedU();
    }

    template <typename T>
    inline bool BlendingSplineSurface<T>::isClosedV() const
    {
        return _ms->isClosedV();
    }

    // *************************
    // ** Private functions   **
    // *************************

    template <typename T>
    inline void BlendingSplineSurface<T>::create_knot_vector(
      std::vector<T>& knot_vector, const int n, const bool is_closed,
      const T start = T(0), const T delta = T(0))
    {
        if (is_closed)
            create_closed_knot_vector(knot_vector, n, start, delta);
        else
            create_open_knot_vector(knot_vector, n);
    }

    template <typename T>
    inline void BlendingSplineSurface<T>::create_closed_knot_vector(
      std::vector<T>& knot_vector, const int n, const T start, const T delta)
    {
        knot_vector.resize(_k + n);

        for (int i = 0; i < n + 1; ++i) {
            knot_vector[i + 1] = start + i * (delta / n);
        }
        knot_vector[0] = knot_vector[1] - (knot_vector[n + 1] - knot_vector[n]);
    }

    template <typename T>
    inline void BlendingSplineSurface<T>::create_open_knot_vector(
      std::vector<T>& knot_vector, const int n)
    {
        knot_vector.resize(_k + n);

        for (int i = 0; i < _k; ++i) {
            knot_vector[i] = 0;
        }

        for (int i = _k; i < n; ++i) {
            knot_vector[i] = knot_vector[i - 1] + 1;
        }

        for (int i = n; i < n + _k; ++i) {
            knot_vector[i] = knot_vector[n - 1] + 1;
        }
    }

    template <typename T>
    inline void BlendingSplineSurface<T>::create_local_surfaces()
    {
        _ls.setDim((isClosedU() ? _nu + 1 : _nu),
                   (isClosedV() ? _nv + 1 : _nv));

        for (int i = 0; i < _nu; ++i) {
            for (int j = 0; j < _nv; ++j) {
                // (_ms, _u i, _u i+2, u i+1, _v j, _v j+2, _v j+1)
                _ls[i][j]
                  = new PSimpleSubSurf<T>(_ms, _u[i], _u[i + 2], _u[i + 1],
                                          _v[j], _v[j + 2], _v[j + 1]);
                _ls[i][j]->toggleDefaultVisualizer();
                _ls[i][j]->sample(5, 5, 1, 1);
                _ls[i][j]->setCollapsed(true);
                _ls[i][j]->setParent(this);
                this->insert(_ls[i][j]);
            }
        }

        if (isClosedU())
            for (int i = 0; i < _nv; ++i) _ls[_nu][i] = _ls[0][i];

        if (isClosedV())
            for (int j = 0; j < _nu; ++j) _ls[j][_nv] = _ls[j][0];

        if (isClosedU() && isClosedV()) _ls[_nu][_nv] = _ls[0][0];
    }

    template <typename T>
    inline int
    BlendingSplineSurface<T>::get_index(const std::vector<T>& knot_vector,
                                        const int n, const T t) const
    {
        for (int i = _d; i < n; ++i) {
            if (t <= knot_vector[i + 1]) return i;
        }
        return n;   // in case of rounding error or similar
    }

    template <typename T>
    inline std::tuple<T, T>
    BlendingSplineSurface<T>::get_w(const std::vector<T>& knot_vector,
                                    const int d, const int i, const T t) const
    {
        T w   = T((t - knot_vector[i]) / (knot_vector[i + d] - knot_vector[i]));
        T w_d = T((1) / (knot_vector[i + d] - knot_vector[i]));
        return std::make_tuple(w, w_d);
    }

    template <typename T>
    inline std::tuple<T, T> BlendingSplineSurface<T>::get_b(const T t) const
    {
        T b   = T(-2 * std::pow(t, 3) + 3 * std::pow(t, 2));
        T b_d = T(-6 * std::pow(t, 2) + 6 * t);
        return std::make_tuple(b, b_d);
    }

}   // END namespace kwi