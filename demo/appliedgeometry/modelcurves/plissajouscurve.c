namespace kwi
{
    // *************************
    // Public functions
    // *************************
    // using namespace GMlib;

    template <typename T>
    PLissajousCurve<T>::PLissajousCurve(T a = T(1), T b = T(1), T c = T(M_2PI), T n = T(1))
    {
        _a = a;
        _b = b;
        _c = c;
        _n = n;
    }

    template <typename T>
    PLissajousCurve<T>::~PLissajousCurve()
    {
    }

    template <typename T>
    inline bool PLissajousCurve<T>::isClosed() const
    {
        return true;
    }

    // *************************
    // Protected functions
    // *************************

    template <typename T>
    void PLissajousCurve<T>::eval(T t, int d, bool /*l*/) const
    {
        this->_p.setDim(d + 1);
        this->_p[0][0] = _a * std::sin(_n * t + _c);
        this->_p[0][1] = _b * std::sin(t);
        this->_p[0][2] = T(0);
    }

    template <typename T>
    inline T PLissajousCurve<T>::getStartP() const
    {
        return 0;
    }

    template <typename T>
    inline T PLissajousCurve<T>::getEndP() const
    {
        return M_2PI;
    }

    // *************************
    // ** Private functions   **
    // *************************

}   // END namespace kwi
