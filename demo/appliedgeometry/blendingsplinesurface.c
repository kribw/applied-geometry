namespace kwi
{
    // *************************
    // Public functions
    // *************************
    using namespace GMlib;

    template <typename T>
    BlendingSplineSurface<T>::BlendingSplineSurface(PCurve<T, 3>* mc,
                                                    const int     n)
    {
        _mc = mc;                 // set model curve
        _d  = 1;                  // degree
        _k  = _d + 1;             // order
        _n  = n;                  // no. control curves
        create_knot_vector(n);    // create knot vector
        create_local_curves(n);   // create local curves
    }

    template <typename T>
    BlendingSplineSurface<T>::~BlendingSplineSurface()
    {
    }

    template <typename T>
    inline bool BlendingSplineSurface<T>::isClosed() const
    {
        return true;
    }

    // *************************
    // Protected functions
    // *************************

    template <typename T>
    void BlendingSplineSurface<T>::eval(T t, int d, bool /*l*/) const
    {
        // Set dim (derivatives + 1)
        this->_p.setDim(d + 1);

        const int  i  = get_i(t);
        const T    w1 = get_w(_d, i, t);
        const auto x  = (1 - get_b(w1)) * _lc[i - 1]->evaluateParent(t, d);
        const auto y  = get_b(w1) * _lc[i]->evaluateParent(t, d);
        this->_p      = x + y;
    }

    template <typename T>
    void BlendingSplineSurface<T>::localSimulate(double dt) 
    {
        this->move(Vector<float, 3>(2.0 * std::sin(dt), 0.0, 0.0));
        // rotate, tilt/turn/roll, change shape
    }

    template <typename T>
    inline T BlendingSplineSurface<T>::getStartP() const
    {
        return _mc->getParStart();
    }

    template <typename T>
    inline T BlendingSplineSurface<T>::getEndP() const
    {
        return _mc->getParEnd();
    }

    // *************************
    // ** Private functions   **
    // *************************

    template <typename T>
    inline void BlendingSplineSurface<T>::create_knot_vector(const int n)
    {
        // n = no. control points.

        // Set size of knot vector
        _t.resize(_k + n);

        T start = this->getParStart();
        T delta = this->getParDelta();

        for (int i = 0; i < n + 1; ++i) {
            _t[i + 1] = start + i * (delta / n);
        }
        _t[0] = _t[1] - (_t[n + 1] - _t[n]);
    }

    template <typename T>
    inline void BlendingSplineSurface<T>::create_local_curves(const int n)
    {
        for (int i = 0; i < n; ++i) {
            // start, end, current
            auto curve = new PSubCurve<T>(_mc, _t[i], _t[i + 2], _t[i + 1]);
            curve->toggleDefaultVisualizer();
            curve->sample(4, 0);
            curve->setCollapsed(true);
            curve->setParent(this);
            this->insert(curve);
            _lc.push_back(curve);
        }
        _lc.push_back(_lc[0]);
    }

    template <typename T>
    inline T BlendingSplineSurface<T>::get_w(const int d, const int i,
                                             const T t) const
    {
        return (t - _t[i]) / (_t[i + d] - _t[i]);
    }

    template <typename T>
    inline int BlendingSplineSurface<T>::get_i(const T t) const
    {
        for (int i = _d; i < _n; ++i) {
            if (t <= _t[i + 1]) return i;
        }
        return _n;   // in case of rounding error or similar
    }

    template <typename T>
    inline T BlendingSplineSurface<T>::get_b(const T t) const
    {
        return T(-2 * std::pow(t, 3) + 3 * std::pow(t, 2));
    }

}   // END namespace kwi