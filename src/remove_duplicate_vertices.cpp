#include <common.h>
#include <npe.h>
#include <typedefs.h>






#include <igl/remove_duplicate_vertices.h>

const char* ds_remove_duplicate_vertices = R"igl_Qu8mg5v7(

REMOVE_DUPLICATE_VERTICES Remove duplicate vertices upto a uniqueness
  tolerance (epsilon)

Parameters
----------
V  #V by dim list of vertex positions
epsilon  uniqueness tolerance (significant digit), can probably think of
  this as a tolerance on L1 distance


Returns
-------
SV  #SV by dim new list of vertex positions
SVI #V by 1 list of indices so SV = V(SVI,:) 
SVJ #SV by 1 list of indices so V = SV(SVJ,:)
Wrapper that also remaps given faces (F) --> (SF) so that SF index SV

See also
--------


Notes
-----
None

Examples
--------
% Mesh in (V,F)
[SV,SVI,SVJ] = remove_duplicate_vertices(V,1e-7);
% remap faces
SF = SVJ(F);
  

)igl_Qu8mg5v7";

npe_function(remove_duplicate_vertices)
npe_doc(ds_remove_duplicate_vertices)

npe_arg(v, dense_float, dense_double)
npe_arg(f, dense_int, dense_long, dense_longlong)
npe_arg(epsilon, double)


npe_begin_code()

  // TODO: remove __copy
  // I believe we can prevent this. The libigl function uses "DerivedV rv"
  //    which calls Eigen::Map(Eigen::Matrix<>)::Map() and DNE
  assert_nonzero_rows(v, "v");
  Eigen::MatrixXd v_copy = v.template cast<double>();
  Eigen::MatrixXd sv;
  npe_Matrix_f svi;
  npe_Matrix_f svj;
  npe_Matrix_f sf;
  igl::remove_duplicate_vertices(v_copy, f, epsilon, sv, svi, svj, sf);
  Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor> sv_row_major = sv;
  return std::make_tuple(npe::move(sv_row_major), npe::move(svi), npe::move(svj), npe::move(sf));

npe_end_code()


