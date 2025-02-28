/*
-----------------------------------------------------------------------------
This source file is part of OGRE
(Object-oriented Graphics Rendering Engine)
For the latest info, see http://www.ogre3d.org

Copyright (c) 2000-2014 Torus Knot Software Ltd
Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
-----------------------------------------------------------------------------
*/
#ifndef _ShaderExDualQuaternionSkinning_
#define _ShaderExDualQuaternionSkinning_

#include "OgreShaderPrerequisites.h"

#ifdef RTSHADER_SYSTEM_BUILD_EXT_SHADERS
#include "OgreShaderExHardwareSkinningTechnique.h"

namespace Ogre {
namespace RTShader {

/** \addtogroup Optional
*  @{
*/
/** \addtogroup RTShader
*  @{
*/

/** Implement a sub render state which performs dual quaternion hardware skinning.
    This sub render state uses bone matrices converted to dual quaternions and adds calculations
    to transform the points and normals using their associated dual quaternions.
*/
class DualQuaternionSkinning : public HardwareSkinningTechnique
{
// Interface.
public:
    /** Class default constructor */
    DualQuaternionSkinning();

    /**
    @see SubRenderState::resolveParameters.
    */
    bool resolveParameters(ProgramSet* programSet) override;

    /**
    @see SubRenderState::resolveDependencies.
    */
    bool resolveDependencies(ProgramSet* programSet) override;

    /**
    @see SubRenderState::addFunctionInvocations.
    */
    bool addFunctionInvocations(ProgramSet* programSet) override;

// Protected methods
protected:
    /** Adds functions to calculate position data in world, object and projective space */
    void addPositionCalculations(Function* vsMain);

    /** Adjusts the sign of a dual quaternion depending on its orientation to the root dual quaternion */
    void adjustForCorrectAntipodality(Function* vsMain, int index, const ParameterPtr& pTempWorldMatrix);

    /** Adds the weight of a given position for a given index
    @param pPositionTempParameter
        Requires a temp parameter with a matrix the same size of pPositionRelatedParam
    */
    void addIndexedPositionWeight(Function* vsMain, int index, ParameterPtr& pWorldMatrix,
                                  ParameterPtr& pPositionTempParameter, ParameterPtr& pPositionRelatedOutputParam);
    
    /** Adds the calculations for calculating a normal related element */
    void addNormalRelatedCalculations(Function* vsMain,
                                      ParameterPtr& pNormalRelatedParam,
                                      ParameterPtr& pNormalWorldRelatedParam);

protected:
    UniformParameterPtr mParamInScaleShearMatrices;
    ParameterPtr mParamLocalBlendPosition;
    ParameterPtr mParamBlendS;
    ParameterPtr mParamBlendDQ;
    ParameterPtr mParamInitialDQ;
    ParameterPtr mParamTempWorldMatrix;

    ParameterPtr mParamTempFloat2x4;
    ParameterPtr mParamTempFloat3x3;
    ParameterPtr mParamTempFloat3x4;
    
    ParameterPtr mParamIndex1;
    ParameterPtr mParamIndex2;

};

} // namespace RTShader
} // namespace Ogre

#endif // RTSHADER_SYSTEM_BUILD_EXT_SHADERS
#endif // _ShaderExDualQuaternionSkinning_

