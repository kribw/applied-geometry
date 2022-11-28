namespace kwi
{
    // *************************
    // Public functions
    // *************************
    //using namespace GMlib;

    template <typename T>
    PAstroidCurve<T>::PAstroidCurve(T a = T(1))
    {
        _a = a;
    }

    template <typename T>
    PAstroidCurve<T>::~PAstroidCurve()
    {
    }

    template <typename T>
    inline bool PAstroidCurve<T>::isClosed() const
    {
        return true;
    }

    // *************************
    // Protected functions
    // *************************

    template <typename T>
    void PAstroidCurve<T>::eval(T t, int d, bool /*l*/) const
    {
        this->_p.setDim(d + 1);
        this->_p[0][0] = _a * pow(std::cos(t), 3);
        this->_p[0][1] = _a * pow(std::sin(t), 3);
        this->_p[0][2] = T(0);
    }

    template <typename T>
    inline T PAstroidCurve<T>::getStartP() const
    {
        return 0;
    }

    template <typename T>
    inline T PAstroidCurve<T>::getEndP() const
    {
        return M_2PI;
    }

    // *************************
    // ** Private functions   **
    // *************************

}   // END namespace kwi
