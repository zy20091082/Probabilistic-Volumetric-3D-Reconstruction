#include <iostream>
#include <vector>
#include <vcl_compiler.h>
#include <vsol/vsol_point_3d_sptr.h>
#include <vbl/vbl_array_2d.hxx>
typedef std::vector<std::vector<vsol_point_3d_sptr> >* vptr;
VBL_ARRAY_2D_INSTANTIATE(vptr);
