namespace kwi
{
    // *************************
    // Public functions
    // *************************
    using namespace GMlib;

    template <typename T>
    BlendingSpline<T>::BlendingSpline(PCurve<T, 3>& mc, const int n)
    {
        _mc = mc;                 // set model curve
        _d  = 1;                  // degree ?
        _k  = _d + 1;             // order
        create_knot_vector(n);    // create knot vector
        create_local_curves(n);   // create local curves
    }

    template <typename T>
    BlendingSpline<T>::~BlendingSpline()
    {
    }

    template <typename T>
    inline bool BlendingSpline<T>::isClosed() const
    {
        return true;
    }

    // *************************
    // Protected functions
    // *************************

    template <typename T>
    void BlendingSpline<T>::eval(T t, int d, bool /*l*/) const
    {
        // Set dim (derivatives + 1)
        this->_p.setDim(d + 1);

        // do something
    }

    template <typename T>
    inline T BlendingSpline<T>::getStartP() const
    {
        return _mc->getParStart();
    }

    template <typename T>
    inline T BlendingSpline<T>::getEndP() const
    {
        return _mc->getParEnd();
    }

    // *************************
    // ** Private functions   **
    // *************************

    template <typename T>
    inline void BlendingSpline<T>::create_knot_vector(const int n)
    {
        // n = no. control points.

        // Set size of knot vector
        _t.resize(_k + n);

        T start = this->getParStart();
        T delta = this->getParDelta();

        for (int i = 0; i < n + 1) {
            _t[i + 1] = start + i * (delta / n + 1);
        }
        _t[0] = _t[1] - (_t[n + 1] - _t[n]);
    }

    template <typename T>
    inline void BlendingSpline<T>::create_local_curves(const int n)
    {
        for (int i = 0; i < n; ++i) {
            // start, end, current
            _lc.push_back(new PSubCurve<T>(_mc, _t[i], _t[i + 2], _t[i + 1]));
        }
        _lc.push_back(_lc[0]);
    }

    template <typename T>
    inline T BlendingSpline<T>::get_w(const int d, const int i, const T t) const
    {
        return (t - _t[i]) / (_t[i + d] - _t[i]);
    }
    
    template <typename T>
    inline int BlendingSpline<T>::get_i(const T t) const
    {
        for (int i = 0; i < _t.size()) {
            if (t <= _t[i]) return i;
        }

        return _t.size() - 1; // in case of rounding error or similar
    }

    template <typename T>
    inline float BlendingSpline<T>::get_b(const T t) const
    {
        return 0;
    }

}   // END namespace kwi