/******************************************************************************
*                 SOFA, Simulation Open-Framework Architecture                *
*                    (c) 2006 INRIA, USTL, UJF, CNRS, MGH                     *
*                                                                             *
* This program is free software; you can redistribute it and/or modify it     *
* under the terms of the GNU Lesser General Public License as published by    *
* the Free Software Foundation; either version 2.1 of the License, or (at     *
* your option) any later version.                                             *
*                                                                             *
* This program is distributed in the hope that it will be useful, but WITHOUT *
* ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or       *
* FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License *
* for more details.                                                           *
*                                                                             *
* You should have received a copy of the GNU Lesser General Public License    *
* along with this program. If not, see <http://www.gnu.org/licenses/>.        *
*******************************************************************************
* Authors: The SOFA Team and external contributors (see Authors.txt)          *
*                                                                             *
* Contact information: contact@sofa-framework.org                             *
******************************************************************************/
#include <SofaMeshCollision/RayTriangleIntersection.h>

#include <SofaMeshCollision/TriangleModel.h>
#include <sofa/core/VecId.h>

namespace sofa::component::collision
{

RayTriangleIntersection::RayTriangleIntersection()
{
}

RayTriangleIntersection::~RayTriangleIntersection()
{
}

bool RayTriangleIntersection::NewComputation(const sofa::type::Vector3 &p1, const sofa::type::Vector3 &p2, const sofa::type::Vector3 &p3, const sofa::type::Vector3 &origin, const sofa::type::Vector3 &direction,   SReal &t,  SReal &u, SReal &v)
{
    t = 0; u = 0; v = 0;

    sofa::type::Vector3 edge1 = p2 - p1;
    sofa::type::Vector3 edge2 = p3 - p1;

    sofa::type::Vector3 tvec, pvec, qvec;
    SReal det, inv_det;

    pvec = direction.cross(edge2);

    det = dot(edge1, pvec);
    if(det<=1.0e-20 && det >=-1.0e-20)
    {
        return false;
    }

    inv_det = 1.0 / det;

    tvec = origin - p1;

    u = dot(tvec, pvec) * inv_det;
    if (u < -0.0000001 || u > 1.0000001)
        return false;

    qvec = tvec.cross(edge1);

    v = dot(direction, qvec) * inv_det;
    if (v < -0.0000001 || (u + v) > 1.0000001)
        return false;

    t = dot(edge2, qvec) * inv_det;

    if (t < 0.0000001 || t!=t || v!=v || u!=u)
        return false;

    return true;
}

bool RayTriangleIntersection::NewComputation(TTriangle<sofa::defaulttype::Vec3Types>* triP, const sofa::type::Vector3& origin, const sofa::type::Vector3& direction, SReal& t, SReal& u, SReal& v)
{
    return NewComputation(triP->p1(), triP->p2(), triP->p3(), origin, direction, t, u, v);
}

} //namespace sofa::component::collision
