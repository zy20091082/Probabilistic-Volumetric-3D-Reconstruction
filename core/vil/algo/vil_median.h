#ifndef vil2_median_h_
#define vil2_median_h_
//: \file
//  \brief Perform median filtering on images
//  \author Tim Cootes

#include <vil2/algo/vil2_structuring_element.h>
#include <vil2/vil2_image_view.h>
#include <vcl_algorithm.h>

//: Return r-th sorted value of im[offset[k]]
//  Values im[offset[k]] placed into values[k] then sorted
template <class T>
inline T vil2_sorted_value(const T* im, const int* offset, T* values, unsigned n, unsigned r)
{
  for (unsigned i=0;i<n;++i) values[i]=im[offset[i]];
	vcl_sort(values,values+n);
  return values[r];
}

//: Return (n*r)-th sorted value of pixels under element centred at (i0,j0)
//  \param r in [0,1].
//  \param values used to store values sampled from image before sorting
//  Checks boundary overlap
template <class T>
inline T vil2_sorted_value(const vil2_image_view<T>& image, unsigned plane,
                        const vil2_structuring_element& element, int i0, int j0,
												vcl_vector<T>& values, double r)
{
  values.resize(0);
  unsigned n = element.p_i().size();
  for (int k=0;k<n;++k)
  {
    int i = i0+element.p_i()[k];
    int j = j0+element.p_j()[k];
    if (i>=0 && i<image.ni() && j>=0 && j<image.nj())
		  values.push_back(image(i,j,plane));
  }
	vcl_sort(values.begin(),values.end());
  return values[unsigned(r*(values.size()-1))];
}

//: Computes median value of pixels under structuring element
// dest_image(i0,j0) is the median value of the pixels under the
// structuring element when it is centred on src_image(i0,j0)
// \relates vil2_image_view
// \relates vil2_structuring_element
template <class T>
void vil2_median(const vil2_image_view<T>& src_image,
                        vil2_image_view<T>& dest_image,
                        const vil2_structuring_element& element);


#endif
