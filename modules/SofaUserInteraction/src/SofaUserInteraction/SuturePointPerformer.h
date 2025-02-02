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
#include <SofaUserInteraction/config.h>

#include <SofaUserInteraction/InteractionPerformer.h>
#include <SofaDeformable/StiffSpringForceField.h>
#include <SofaDeformable/SpringForceField.h>
#include <SofaBoundaryCondition/FixedConstraint.h>

#include <SofaUserInteraction/MouseInteractor.h>

namespace sofa::component::collision
{

class SuturePointPerformerConfiguration
{
public:
    void setStiffness (double f) {stiffness=f;}
    void setDamping (double f) {damping=f;}

protected:
    double stiffness;
    double damping;
};


template <class DataTypes>
class SOFA_SOFAUSERINTERACTION_API SuturePointPerformer: public TInteractionPerformer<DataTypes>, public SuturePointPerformerConfiguration
{
public:
    typedef typename DataTypes::Real Real;
    typedef sofa::component::interactionforcefield::LinearSpring<Real> Spring;
    typedef sofa::component::interactionforcefield::StiffSpringForceField<DataTypes> SpringObjectType;
    typedef sofa::component::projectiveconstraintset::FixedConstraint<DataTypes> FixObjectType;

    SuturePointPerformer(BaseMouseInteractor *i);
    ~SuturePointPerformer();

    void start();
    void execute() {}

protected:
    bool first;
    unsigned int fixedIndex;

    sofa::type::vector<Spring> addedSprings;

    BodyPicked firstPicked;
    SpringObjectType *SpringObject;
    FixObjectType *FixObject;
};

#if  !defined(SOFA_COMPONENT_COLLISION_SUTUREPOINTPERFORMER_CPP)
extern template class SOFA_SOFAUSERINTERACTION_API  SuturePointPerformer<defaulttype::Vec3Types>;

#endif

} // namespace sofa::component::collision
