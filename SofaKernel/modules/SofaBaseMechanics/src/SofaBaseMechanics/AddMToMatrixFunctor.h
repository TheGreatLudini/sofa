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
#pragma once
#include <SofaBaseMechanics/config.h>
#include <sofa/linearalgebra/BaseMatrix.h>
#include <sofa/defaulttype/RigidTypes.h>

namespace sofa::component::mass
{

template<class Deriv, class MassType>
class AddMToMatrixFunctor
{
public:
    void operator()(linearalgebra::BaseMatrix * mat, const MassType& mass, int pos, double fact)
    {
        const double m = mass*fact;
        for (unsigned int i=0; i<Deriv::size(); ++i)
            mat->add(pos+i, pos+i, m);
    }

    ///Method to add non-diagonal terms
    void operator()(linearalgebra::BaseMatrix * mat, const MassType& mass, int posRow, int posColumn, double fact)
    {
        const double m = mass*fact;
        for (unsigned int i=0; i<Deriv::size(); ++i)
            mat->add(posRow+i, posColumn+i, m);
    }
};

template<int N, typename Real>
class AddMToMatrixFunctor< type::Vec<N,Real>, type::Mat<N,N,Real> >
{
public:
    void operator()(linearalgebra::BaseMatrix * mat, const type::Mat<N,N,Real>& mass, int pos, double fact)
    {
        for (int i=0; i<N; ++i)
            for (int j=0; j<N; ++j)
            {
                mat->add(pos+i, pos+j, mass[i][j]*fact);
            }
    }
};

template<typename Real>
class AddMToMatrixFunctor< defaulttype::RigidDeriv<3,Real>, defaulttype::RigidMass<3,Real> >
{
public:
    enum { N=3 };
    void operator()(linearalgebra::BaseMatrix * mat, const defaulttype::RigidMass<N,Real>& mass, int pos, double fact)
    {
        const double m = mass.mass*fact;
        for (int i=0; i<N; ++i)
            mat->add(pos+i, pos+i, m);
        for (int i=0; i<N; ++i)
            for (int j=0; j<N; ++j)
            {
                mat->add(pos+N+i, pos+N+j, mass.inertiaMassMatrix[i][j]*fact);
            }
    }
};

template<typename Real>
class AddMToMatrixFunctor< defaulttype::RigidDeriv<2,Real>, defaulttype::RigidMass<2,Real> >
{
public:
    enum { N=2 };
    void operator()(linearalgebra::BaseMatrix * mat, const defaulttype::RigidMass<N,Real>& mass, int pos, double fact)
    {
        const double m = mass.mass*fact;
        for (int i=0; i<N; ++i)
            mat->add(pos+i, pos+i, m);
        mat->add(pos+N, pos+N, mass.inertiaMassMatrix*fact);
    }
};

} // namespace sofa::component::mass
