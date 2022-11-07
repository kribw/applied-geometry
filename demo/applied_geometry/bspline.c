namespace kwi
{
    // *************************
    // Public functions
    // *************************
    using namespace GMlib;

    template <typename T>
    BSpline<T>::BSpline()
    {
    }

    template <typename T>
    BSpline<T>::BSpline(const DVector<Vector<T, 3>>& c)
    {
        _c = c;                           // control points
        _d = 2;                           // dimension should always be 2
        _k = _d + 1;                      // order
        create_knot_vector(c.getDim());   // generate knot vector
    }

    template <typename T>
    BSpline<T>::BSpline(const DVector<Vector<T, 3>>& p, int n)
    {
        //        std::cout << "p: " << p << std::endl;
        // use least square to make n control points - and generate a knotvector
        // least_square()
        // n = control points
        _c.setDim(n);
        _d = 2;                  // dimension should always be 2
        _k = _d + 1;                      // order
        create_knot_vector(n);   // generate knot vector


        // A = n * m
        // m = p.getdim
        // n = no. of splines
        DMatrix<T> A(p.getDim(), n, T(0));
        T          dt = getDeltaP() / (p.getDim() - 1);

        for (int j = 0; j < p.getDim(); ++j) {
            T   x, y, z;
            T   t = getStartP() + j * dt;
            int i = get_basis(t, x, y, z);

            A[j][i - 2] = x;
            A[j][i - 1] = y;
            A[j][i]     = z;
        }
        std::cout << "A: " << std::endl;

        qDebug() << A;


        DMatrix<T> A_T = A;
        A_T.transpose();
        const DMatrix<T>            B     = A_T * A;
        const DVector<Vector<T, 3>> b     = A_T * p;
        auto                        B_inv = B;
        B_inv.invert();


        // A_transposed * A * _c = A_transposed * p
        // B c = b
        _c = B_inv * b;
    }

    template <typename T>
    BSpline<T>::~BSpline()
    {
    }

    template <typename T>
    bool BSpline<T>::isClosed() const
    {
        return false;
    }

    // *************************
    // Protected functions
    // *************************

    template <typename T>
    void BSpline<T>::eval(T t, int d, bool /*l*/) const
    {
        // Set dim (derivatives + 1)
        this->_p.setDim(d + 1);

        // Only compute position
        // dont need any derivatives
        T   x, y, z;
        int i       = get_basis(t, x, y, z);
        this->_p[0] = x * _c[i - 2] + y * _c[i - 1] + z * _c[i];
    }

    template <typename T>
    inline T BSpline<T>::getStartP() const
    {
        return _t[_d];
    }

    template <typename T>
    inline T BSpline<T>::getEndP() const
    {
        return _t[_c.getDim()];
    }

    // *************************
    // ** Private functions   **
    // *************************

    template <typename T>
    inline T BSpline<T>::getDeltaP() const
    {
        return getEndP() - getStartP();
    }

    template <typename T>
    void BSpline<T>::create_knot_vector(int n)
    {
        // n = no. control points.
        // n values in knot vector should
        // e.g. 0 0 0 1 2 3 4 4 4

        // Set size of knot vector
        _t.resize(_k + n);

        for (int i = 0; i < _k; ++i) {
            _t[i] = 0;
        }

        for (int i = _k; i < n; ++i) {
            _t[i] = _t[i - 1] + 1;
        }

        for (int i = n; i < n + _k; ++i) {
            _t[i] = _t[n - 1] + 1;
        }
    }

    template <typename T>
    inline T BSpline<T>::get_w(int d, int i, T t) const
    {
        return (t - _t[i]) / (_t[i + d] - _t[i]);
    }

    template <typename T>
    inline int BSpline<T>::get_i(T t) const
    {
        int n = _c.getDim();
        for (int i = _d; i < n; ++i) {
            if (t <= _t[i + 1]) return i;
        }
        return n;   // in case of rounding error or similar
    }


    template <typename T>
    inline int BSpline<T>::get_basis(T t, T& x, T& y, T& z) const
    {
        const int i = get_i(t);

        GMlib::Vector<T, 2> a;
        a[0] = 1 - get_w(1, i, t);
        a[1] = get_w(1, i, t);

        GMlib::Matrix<T, 2, 3> b;
        b[0][0] = 1 - get_w(2, i - 1, t);
        b[0][1] = get_w(2, i - 1, t);
        b[1][1] = 1 - get_w(2, i, t);
        b[1][2] = get_w(2, i, t);

        x = a[0] * b[0][0];
        y = (a[0] * b[0][1] + a[1] * b[1][1]);
        z = a[1] * b[1][2];
        return i;
    }

}   // END namespace kwi
