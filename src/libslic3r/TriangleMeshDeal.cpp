#include "TriangleMeshDeal.hpp"

#include <igl/loop.h>
#undef NDEBUG
#include <assert.h>
#include <boost/log/trivial.hpp>

namespace Slic3r {
TriangleMesh TriangleMeshDeal::smooth_triangle_mesh(const TriangleMesh& mesh, bool& ok)
{
    {
        using namespace igl;
        typedef Eigen::Matrix<float, Eigen::Dynamic, 3, Eigen::DontAlign | Eigen::RowMajor> RowMatrixX3f;
        typedef Eigen::Matrix<int, Eigen::Dynamic, 3, Eigen::DontAlign | Eigen::RowMajor>   RowMatrixX3i;

        auto vertices_count = mesh.its.vertices.size();
        auto indices_count  = mesh.its.indices.size();
        // Copy the ITS vertices/faces into Eigen matrices. 0632bae8's igl::loop
        // overload (V, F, NV, NF) requires PlainObjectBase inputs (not Map), and
        // the input matrices must match the Row-major layout the subdivision
        // expects. Earlier baselines accepted a Map<const ...>; this one does not.
        RowMatrixX3f OV(vertices_count, 3);
        RowMatrixX3i OF(indices_count, 3);
        for (size_t i = 0; i < vertices_count; ++i) {
            OV(i, 0) = mesh.its.vertices[i].x();
            OV(i, 1) = mesh.its.vertices[i].y();
            OV(i, 2) = mesh.its.vertices[i].z();
        }
        for (size_t i = 0; i < indices_count; ++i) {
            OF(i, 0) = mesh.its.indices[i][0];
            OF(i, 1) = mesh.its.indices[i][1];
            OF(i, 2) = mesh.its.indices[i][2];
        }
        RowMatrixX3f V;
        RowMatrixX3i F;

        ok = true;
        loop(OV, OF, V, F);

        indexed_triangle_set its;
        // Explicit row loops: the vendored Eigen build lacks VectorwiseOp
        // cbegin/cend (only present in newer releases), so range-assigning
        // via rowwise() iterators does not compile everywhere.
        its.vertices.reserve(V.rows());
        for (Eigen::Index r = 0; r < V.rows(); ++r)
            its.vertices.emplace_back(V(r, 0), V(r, 1), V(r, 2));
        its.indices.reserve(F.rows());
        for (Eigen::Index r = 0; r < F.rows(); ++r)
            its.indices.emplace_back(F(r, 0), F(r, 1), F(r, 2));
        TriangleMesh result_mesh(its);
        return result_mesh;
    }
}
} // namespace Slic3r
