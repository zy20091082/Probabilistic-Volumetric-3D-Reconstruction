// This is brcv/seg/bsta/bsta_gaussian_full.h
#ifndef bsta_gaussian_full_h_
#define bsta_gaussian_full_h_

//:
// \file
// \brief A Gaussian distribution with a full covariance matrix
// \author Matt Leotta (mleotta@lems.brown.edu)
// \date 1/25/06
//
// \verbatim
//  Modifications
// \endverbatim

#include "bsta_gaussian.h"
#include <vnl/vnl_vector_fixed.h>
#include <vnl/vnl_matrix_fixed.h>


//: A Gaussian distribution with a full covariance matrix
template <class T, unsigned n>
class bsta_gaussian_full : public bsta_gaussian<T,n>
{
  public:
    //: Constructor
    bsta_gaussian_full<T,n>():
      bsta_gaussian<T,n>(), covar_(T(0)),
      det_covar_(T(0)), inv_covar_(NULL) {}

    //: Constructor
    bsta_gaussian_full<T,n>(const vnl_vector_fixed<T,n>& mean,
                              const vnl_matrix_fixed<T,n,n>& covar):
      bsta_gaussian<T,n>(mean), covar_(covar),
      det_covar_(T(-1)), inv_covar_(NULL)
    {compute_det();}

    //: Destructor
    ~bsta_gaussian_full<T,n>() { delete inv_covar_; }

    //: The covariance matrix of the distribution
    const vnl_matrix_fixed<T,n,n>& covar() const { return covar_; }

    //: Set the covariance matrix of the distribution
    void set_covar(const vnl_matrix_fixed<T,n,n>& covar);

    //: The probability of this sample given square mahalanobis distance
    T dist_probability(const T& sqr_mahal_dist) const
    {
      if(det_covar_ <= 0)
        return T(0);
      return static_cast<T>(vcl_sqrt(1/(det_covar_*two_pi_power<n>::value()))
           * vcl_exp(-sqr_mahal_dist/2));
    }

    //: The probability of this sample
    T probability(const vnl_vector_fixed<T,n>& pt) const
    {
      return dist_probability(sqr_mahalanobis_dist(pt));
    }

    //: The squared Mahalanobis distance to this point
    T sqr_mahalanobis_dist(const vnl_vector_fixed<T,n>& pt) const;

    //: Compute the determinant of the covariance matrix
    T det_covar() const { return det_covar_; }

    //: The inverse covariance matrix of the distribution
    const vnl_matrix_fixed<T,n,n>& inv_covar() const;

  protected:
    //: The covariance matrix
    vnl_matrix_fixed<T,n,n> covar_;

    //: The cached covariance determinant
    T det_covar_;

  private:
    //: compute the determinant of the covariance
    void compute_det();

    //: cache for inverse of the covariance matrix
    mutable vnl_matrix_fixed<T,n,n>* inv_covar_;
};


#endif // bsta_gaussian_full_h_
