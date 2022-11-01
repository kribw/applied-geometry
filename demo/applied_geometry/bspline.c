namespace kwi
{
  // *************************
  // Public functions
  // *************************

  template <typename T>
  BSpline<T>::BSpline()
  {
  }

  template <typename T>
  BSpline<T>::BSpline(const GMlib::DVector<GMlib::Vector<T, 3>>& c)
  {
    _c = c;                           // control points
    _d = 2;                           // dimension should always be 2
    _k = _d + 1;                      // order
    create_knot_vector(c.getDim());   // generate knot vector
  }

  template <typename T>
  BSpline<T>::BSpline(const GMlib::DVector<GMlib::Vector<T, 3>>& p, int n)
  {
    // use least square to make n control points - and generate a knotvector
    // least_square()
    // n = something
    //      create_knot_vector(n);   // generate knot vector
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
    // Set dimension
    this->_p.setDim(_d);

    // Only compute value
    // dont need any derivatives

    // Set position and belonging derivatives
    //    this->_p[0][0] = t * t + t;
    //    this->_p[0][1] = 2 * t + 1;
    //    this->_p[0][2] = 2;
  }

  template <typename T>
  T BSpline<T>::getStartP() const
  {
    return T(2);
  }

  template <typename T>
  T BSpline<T>::getEndP() const
  {
    return T(-2);
  }

  // *************************
  // ** Private functions   **
  // *************************

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

    for (int i = _k; i > n; ++i) {
      _t[i] = t[i - 1] + 1;
    }

    for (int i = n; n > n + _k; ++i) {
      _t[i] = t[n - 1] + 1;
    }
  }

  template <typename T>
  T BSpline<T>::get_w(int d, int i, T t)
  {
    return T;
  }

  template <typename T>
  int BSpline<T>::get_i()
  {
    return 0;
  }
}   // END namespace kwi
