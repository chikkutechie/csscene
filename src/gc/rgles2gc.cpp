
#include "rcommon.h"
#include "rmeshshape.h"
#include "rgles2gc.h"
#include "rlog.h"

#include <stdexcept>

namespace chikkooos
{

#if defined(R_ES) || defined(R_ES2)
#define PRECISION "precision mediump float; \n"
#else
#define PRECISION "\n"
#endif

#if defined(R_ES2)
#define RClearDepth(x) glClearDepthf(x)
#define RDepthRange(x, y) glDepthRangef(x, y);
#else
#define RClearDepth(x) glClearDepth(x)
#define RDepthRange(x, y) glDepthRange(x, y);
#endif

#if defined(R_ES2)
#define GLSL_VERSION  "\n"
#else
#define GLSL_VERSION  "#version 120 \n"
#endif

RGles2Gc::RGles2Gc()
{}

RGles2Gc::~RGles2Gc()
{
    mProgramMap.clear();
}

bool RGles2Gc::doInitialize()
{
    rLogI() << "RGles2Gc::doInitialize" << std::endl;

    glViewport(data_p().mViewX, data_p().mViewY,
               data_p().mViewWidth, data_p().mViewHeight);

    glClearColor(backgroundColor().r(), backgroundColor().g(),
                 backgroundColor().b(), backgroundColor().a());

    RCheckGLError();

#if !defined(R_ES2)
    //enable(GL_TEXTURE_2D);
#endif

    glCullFace(GL_BACK);
    glFrontFace(GL_CCW);

    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

#if !defined(R_ES2)
    //enable(GL_VERTEX_PROGRAM_POINT_SIZE);
    //enable(GL_PROGRAM_POINT_SIZE);
#endif

    data_p().mInitialized = true;

    RCheckGLError();

    return true;
}

std::string RGles2Gc::createVertexShader(ProgramKey const &  k) const
{
    std::stringstream shader;

    // declarations
    shader << GLSL_VERSION
              "\n"
              "uniform mat4 u_mvp_matrix;\n"
              "\n"
              "attribute vec3 a_position;\n"
              "\n";

    if (k.mHasTexture) {
        if (k.mIsPointSprite) {
            shader << "uniform float u_pointsize;\n";
            if (k.mHasPointSpriteAlpha) {
                shader << "attribute float a_alpha;\n"
                       << "varying float v_alpha;\n";
            }
        } else {
            shader << "attribute vec2 a_texCoord;\n"
                      "varying vec2 v_texCoord;\n"
                      "\n";
        }
    }

    if (k.mLightCount) {
        shader << "attribute vec3 a_normal;\n"
                  "varying vec3 v_normal;\n"
                  "varying vec3 v_position;\n"
                  "\n";
    }

    // main function
    shader << "void main()\n"
           << "{\n";

    if (k.mHasTexture) {
        if (k.mIsPointSprite) {
            if (k.mHasPointSpriteAlpha) {
                shader << "  v_alpha = a_alpha;\n";
            }
            shader << "  gl_PointSize = u_pointsize;\n";

        } else {
            shader << "  v_texCoord = a_texCoord;\n";
        }
        shader << "\n";
    }

    if (k.mLightCount) {
        shader << "  v_position = a_position;\n"
                  "  v_normal = a_normal;\n"
                  "\n";
    }

    shader << "  gl_Position = u_mvp_matrix * vec4(a_position, 1.0);\n"
              "}\n"
              "\n";

    return shader.str();
}

std::string RGles2Gc::createFragmentShader(ProgramKey const & k) const
{
    std::stringstream shader;

    // precision and version
    shader << GLSL_VERSION
           << "\n"
           << PRECISION
           <<   "\n";


    // declarations
    if (!k.mHasTexture && !k.mLightCount) {
        shader << "uniform vec4 u_color;\n"
                  "\n";
    }
    if (k.mHasTexture) {
        if (k.mHasTextureTransform) {
            shader << "uniform mat3 u_texMatrix;\n";
        }

        if (k.mIsPointSprite) {
            if (k.mHasPointSpriteAlpha) {
                shader << "varying float v_alpha;\n";
            }
        } else {
            shader << "varying vec2 v_texCoord;\n";
        }
        shader << "uniform sampler2D s_texture;\n"
                  "\n";
    }

    if (k.mLightCount) {
        shader << "uniform mat4 u_mv_matrix;\n"
                  "uniform mat4 u_normalmatrix;\n"
                  "\n"
                  "uniform vec3 u_viewer;\n"
                  "\n"
                  "varying vec3 v_normal;\n"
                  "varying vec3 v_position;\n"
                  "\n"
                  "uniform vec3 u_globalambient;\n"
                  "\n"
                  "const float c_0 = 0.0;\n"
                  "const float c_1 = 1.0;\n"
                  "\n";

        shader << "struct Material\n"
                  "{\n"
                  "  vec3 ambient;\n"
                  "  vec3 diffuse;\n"
                  "  vec3 specular;\n"
                  "  float specexp;\n"
                  "  vec3 emissive;\n"
                  "};\n"
                  "uniform Material u_material;\n"
                  "\n";

        if (k.mHasDirLight) {
            shader << "struct DirLight\n"
                      "{\n"
                      "  vec3 ambient;\n"
                      "  vec3 diffuse;\n"
                      "  vec3 specular;\n"
                      "  vec3 lightpos;\n"
                      "};\n";
        }

        if (k.mHasSpotLight) {
            shader << "struct SpotLight\n"
                      "{\n"
                      "  vec3 ambient;\n"
                      "  vec3 diffuse;\n"
                      "  vec3 specular;\n"
                      "  vec3 lightpos;\n"
                      "  vec3 spotdir;\n"
                      "  float spotexponent;\n"
                      "  float spotcutoff;\n"
                      "  float constatten;\n"
                      "  float linearatten;\n"
                      "  float quadatten;\n"
                      "};\n";
        }

        if (k.mHasPointLight) {
            shader << "struct PointLight\n"
                      "{\n"
                      "  vec3 ambient;\n"
                      "  vec3 diffuse;\n"
                      "  vec3 specular;\n"
                      "  vec3 lightpos;\n"
                      "  float constatten;\n"
                      "  float linearatten;\n"
                      "  float quadatten;\n"
                      "};\n";
        }
        int i=1;
        for (LightsConstIter iter = data_p().mLights.begin(); iter != data_p().mLights.end(); ++iter, ++i) {
            if ((*iter)->isDirectionLight()) {
                shader << "uniform DirLight u_light_" << i << ";\n";
            } else if ((*iter)->isSpotLight()) {
                shader << "uniform SpotLight u_light_" << i << ";\n";
            } else if ((*iter)->isPointLight()) {
                shader << "uniform PointLight u_light_" << i << ";\n";
            }
        }

    }

    // light related functions
    if (k.mHasDirLight) {
        shader <<   "void CalculateDirLight(in DirLight light, float shininess, in vec3 halfV,\n"
                    "                       in vec3 normal, inout vec3 ambient, inout vec3 diffuse,\n"
                    "                       inout vec3 specular) {\n"
                    "  float nDotVP;\n"
                    "  float nDotHV;\n"
                    "  float pf;\n"
                    "  nDotVP = max(c_0, dot(normal, normalize(light.lightpos)));\n"
                    "  nDotHV = max(c_0, dot(normal, halfV));\n"
                    "  if (nDotVP == c_0) {\n"
                    "    pf = c_0;\n"
                    "  } else {\n"
                    "    pf = pow(nDotHV, shininess);\n"
                    "  }\n"
                    "  ambient  = ambient;\n"
                    "  diffuse  = diffuse * nDotVP;\n"
                    "  specular = specular * pf;\n"
                    "}\n"
                    "\n";

    }

    if (k.mHasPointLight) {
        shader <<   "void CalculatePointLight(in PointLight light, float shininess, \n"
                    "                         in vec3 eye, in vec3 position, \n"
                    "                         in vec3 normal, inout vec3 ambient,\n"
                    "                         inout vec3 diffuse, inout vec3 specular) {\n"
                    "  float nDotVP;\n"
                    "  float nDotHV;\n"
                    "  float pf;\n"
                    "  float attenuation;\n"
                    "  float d;\n"
                    "  vec3  VP;\n"
                    "  vec3  halfVector;\n"
                    "  VP = light.lightpos - position;\n"
                    "  d = sqrt(dot(VP, VP));\n"
                    "  VP = normalize(VP);\n"
                    "  attenuation = c_1 / (light.constatten + light.linearatten * d + light.quadatten * d * d);\n"
                    "  halfVector = normalize(VP + eye);\n"
                    "  nDotVP = max(c_0, dot(normal, VP));\n"
                    "  nDotHV = max(c_0, dot(normal, halfVector));\n"
                    "  if (nDotVP == c_0) {\n"
                    "    pf = c_0;\n"
                    "  } else {\n"
                    "    pf = pow(nDotHV, shininess);\n"
                    "  }\n"
                    " ambient = ambient * attenuation;\n"
                    " diffuse = diffuse * nDotVP * attenuation;\n"
                    " specular = specular * pf * attenuation;\n"
                    "}\n"
                    "\n";
    }

    if (k.mHasSpotLight) {
        shader <<   "void CalculateSpotLight(SpotLight light, float shininess,\n"
                    "                        in vec3 eye, in vec3 position, \n"
                    "                        in vec3 normal, inout vec3 ambient,\n"
                    "                        inout vec3 diffuse, inout vec3 specular) {\n"
                    "  float nDotVP;\n"
                    "  float nDotHV;\n"
                    "  float pf;\n"
                    "  float spotDot;\n"
                    "  float spotAttenuation;\n"
                    "  float attenuation;\n"
                    "  float d;\n"
                    "  vec3 VP;\n"
                    "  vec3 halfVector;\n"
                    "  VP = light.lightpos - position;\n"
                    "  d = length(dot(VP, VP));\n"
                    "  VP = normalize(VP);\n"
                    "  attenuation = c_1 / (light.constatten + light.linearatten * d + light.quadatten * d * d);\n"
                    "  spotDot = dot(-VP, normalize(light.spotdir));\n"
                    "  if (spotDot < light.spotcutoff) {\n"
                    "    spotAttenuation = c_0;\n"
                    "  } else {\n"
                    "     spotAttenuation = pow(spotDot, light.spotexponent);\n"
                    "  }\n"
                    "  attenuation *= spotAttenuation;\n"
                    "  halfVector = normalize(VP + eye);\n"
                    "  nDotVP = max(c_0, dot(normal, VP));\n"
                    "  nDotHV = max(c_0, dot(normal, halfVector));\n"
                    "  if (nDotVP == c_0) {\n"
                    "    pf = c_0;\n"
                    "  } else {\n"
                    "    pf = pow(nDotHV, shininess);\n"
                    "  }\n"
                    " ambient = ambient * attenuation;\n"
                    " diffuse = diffuse * nDotVP * attenuation;\n"
                    " specular = specular * pf * attenuation;\n"
                    "}\n"
                    "\n";
    }

    // definitions
    shader << "void main()\n"
              "{\n";

    if (k.mLightCount) {
        shader << "  vec3 lighting = vec3(c_0, c_0, c_0);\n"
                  "  vec4 tNormal = u_normalmatrix * vec4(v_normal.x, v_normal.y, v_normal.z, c_1);\n"
                  "  vec3 tNordNormal = normalize(tNormal.xyz);\n"
                  "  vec3 tempAmbient;\n"
                  "  vec3 tempDiffuse;\n"
                  "  vec3 halfWidth;\n"
                  "  vec3 tempSpecular;\n"
                  "  vec4 position = u_mv_matrix * vec4(v_position.x, v_position.y, v_position.z, c_1);\n";

        int i=1;
        for (LightsConstIter iter = data_p().mLights.begin(); iter != data_p().mLights.end(); ++iter, ++i) {
            shader << "  tempAmbient = u_light_" << i << ".ambient;\n"
                      "  tempDiffuse = u_light_" << i << ".diffuse;\n"
                      "  tempSpecular = u_light_" << i << ".specular;\n";
            // direction light
            if ((*iter)->isDirectionLight()) {
                shader << "  vec3 ldir = u_light_" << i << ".lightpos.xyz - position.xyz;\n"
                          "  halfWidth = normalize(normalize(ldir) + u_viewer);\n"
                          "  CalculateDirLight(u_light_" << i << ", u_material.specexp, halfWidth,\n"
                          "                   tNordNormal, tempAmbient, tempDiffuse, tempSpecular);\n";
            // spot light
            } else if ((*iter)->isSpotLight()) {
               shader << "  CalculateSpotLight(u_light_" << i << ",  u_material.specexp, u_viewer, position.xyz, \n"
                         "            tNordNormal, tempAmbient, tempDiffuse, tempSpecular);\n";
            // point light
            } else if ((*iter)->isPointLight()) {
                shader << "  CalculatePointLight(u_light_" << i << ", u_material.specexp , u_viewer, position.xyz, \n"
                          "             tNordNormal, tempAmbient, tempDiffuse, tempSpecular);\n";
            }

            shader << "  lighting += tempAmbient * u_material.ambient;\n"
                      "  lighting += tempDiffuse * u_material.diffuse;\n"
                      "  lighting += tempSpecular * u_material.specular;\n";
        }
        shader << "  lighting += u_material.emissive;\n";
        shader << "  lighting += u_globalambient;\n";
    }

    shader << "  vec4 finalColor = vec4(1.0, 1.0, 1.0, 1.0);\n";

    if (k.mHasTexture) {
        if (k.mIsPointSprite) {
            if (k.mHasTextureTransform) {
                shader << "  vec3 transformedTexCoord = u_texMatrix * vec3(gl_PointCoord.x, gl_PointCoord.y, 1.0f);\n";
                shader << "  finalColor = finalColor * texture2D(s_texture, transformedTexCoord.xy);\n";
            } else {
                shader << "  finalColor = finalColor * texture2D(s_texture, gl_PointCoord);\n";
            }


            if (k.mHasPointSpriteAlpha) {
                shader << "  finalColor.a *= v_alpha;\n";
            }
        } else {
            if (k.mHasTextureTransform) {
                shader << "  vec3 transformedTexCoord = u_texMatrix * vec3(v_texCoord.x, v_texCoord.y, 1.0f);\n";
                shader << "  finalColor = finalColor * texture2D(s_texture, transformedTexCoord.xy);\n";
            } else {
                shader << "  finalColor = finalColor * texture2D(s_texture, v_texCoord);\n";
            }
        }
    }

    if (k.mLightCount) {
        shader << "  finalColor = vec4(finalColor.rgb * lighting, finalColor.a);\n";
    }
    if (!k.mHasTexture && !k.mLightCount) {
        shader << "  finalColor = u_color;\n";
    }

    shader << "  gl_FragColor = finalColor;\n";

    shader << "}\n"
              "\n";

    return shader.str();
}

RGles2Gc::ShaderData RGles2Gc::getProgramUsingKey(ProgramKey const & k)
{
    ProgramMapIter iter = mProgramMap.find(k.toString());
    if (iter != mProgramMap.end()) {
        return iter->second;
    }

    RShaderObject shader;

    std::string vShader = createVertexShader(k);
    RCheckGLError();
    std::string fShader = createFragmentShader(k);
    RCheckGLError();

    ShaderData data;
    if (!shader.create(vShader.c_str(), fShader.c_str())) {
        return data;
    }

    data.mShader = shader;
    data.mVariables = shader.getVariables();

    mProgramMap.insert(std::pair<std::string, ShaderData>(k.toString(), data));

    return data;
}

RGles2Gc::ShaderData RGles2Gc::getProgram(ProgramKey * key)
{
    ProgramKey k;

    k.mHasTexture = !data_p().mTexture.isNull();

    if (k.mHasTexture) {
        k.mHasTextureTransform = (data_p().mTextureTransform != 0);
    }

    k.mLightCount = data_p().mLights.size();

    for (LightsIter iter = data_p().mLights.begin(); iter != data_p().mLights.end(); ++iter) {
        if ((*iter)->isDirectionLight()) {
            k.mHasDirLight = true;
        } else if ((*iter)->isSpotLight()) {
            k.mHasSpotLight = true;
        } else if ((*iter)->isPointLight()) {
            k.mHasPointLight = true;
        }
    }

    if (key != 0) {
        *key = k;
    }

    return getProgramUsingKey(k);
}

void RGles2Gc::draw(RParticles const & ps)
{
    RCheckGLError();

    enable(GL_TEXTURE_2D);

    if (ps.count() == 0) {
        return;
    }

#if !defined(R_ES2)
    enable(GL_POINT_SPRITE);
    glTexEnvi(GL_POINT_SPRITE, GL_COORD_REPLACE, GL_TRUE);
#endif

    glBlendFunc(GL_SRC_ALPHA, GL_ONE);

    ProgramKey key;

    key.mHasTexture = !data_p().mTexture.isNull();
    if (!key.mHasTexture) {
        return;
    }

    key.mIsPointSprite = true;

    key.mHasPointSpriteAlpha = (ps.alphas() != 0);

    ShaderData d = getProgramUsingKey(key);

    d.mShader.unuse();
    d.mShader.use();
    chikkooos::RTransformation t = frustum().matrix().multiply(camera().transformation().matrix());
    t = t.multiply(transformation());

    glActiveTexture(GL_TEXTURE0);
    bindTexture(data_p().mTexture);
    glUniform1i(d.mVariables["s_texture"], 0);

    glUniformMatrix4fv(d.mVariables["u_mvp_matrix"], 1, false, t.matrix().data());

    glUniform1f(d.mVariables["u_pointsize"], ps.size());

    if (key.mHasPointSpriteAlpha) {
        glVertexAttribPointer(d.mVariables["a_alpha"], 1, GL_FLOAT, GL_FALSE, 0, ps.alphas());
        glEnableVertexAttribArray(d.mVariables["a_alpha"]);
    }

    glVertexAttribPointer(d.mVariables["a_position"], 3, GL_FLOAT, GL_FALSE, 0, ps.vertices());
    glEnableVertexAttribArray(d.mVariables["a_position"]);

    glDrawArrays(GL_POINTS, 0, ps.count());
    d.mShader.unuse();

    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

#if !defined(R_ES2)
    disable(GL_POINT_SPRITE);
#endif

    disable(GL_TEXTURE_2D);
}

void RGles2Gc::draw(RShape const & s)
{
    ProgramKey key;

    ShaderData d = getProgram(&key);

    draw(s, d, key);
}

void RGles2Gc::draw(RShape const & s, ShaderData & d, ProgramKey const & key)
{
    d.mShader.use();
    RCheckGLError();

    if (key.mHasTexture) {
        drawTexture(s, d);
    } else {
        unbindTexture();
    }

    if (key.mLightCount > 0) {
#if !defined(R_ES2)
        enable(GL_LIGHTING);
#endif
        RCheckGLError();
        drawLight(s, d);
#if !defined(R_ES2)
        disable(GL_LIGHTING);
#endif
    }

    if (!key.mHasTexture && !key.mLightCount) {
        drawSimple(s, d);
    }

    chikkooos::RTransformation t = frustum().matrix().multiply(camera().transformation().matrix());
	t = t.multiply(transformation());

    glUniformMatrix4fv(d.mVariables["u_mvp_matrix"], 1, false, t.matrix().data());
    RCheckGLError();

    glEnableVertexAttribArray(d.mVariables["a_position"]);
    RCheckGLError();

    bool buffer = false;

    if (s.hasBuffer()) {
        const RShapeBuffer & sb = s.getBuffer();
        if (sb.hasVertices()) {
            sb.bindVertices();
            RCheckGLError();
            glVertexAttribPointer(d.mVariables["a_position"], 3, GL_FLOAT, GL_FALSE, 0, 0);
            RCheckGLError();
            sb.unbind();
            buffer = true;
        }
    }

    if (!buffer) {
        glVertexAttribPointer(d.mVariables["a_position"], 3, GL_FLOAT, GL_FALSE, 0, s.vertices());
        RCheckGLError();
    }

    if (s.indicesCount() > 0) {
        bool indices = false;
        if (buffer) {
            const RShapeBuffer & sb = s.getBuffer();
            if (sb.hasIndices()) {
                sb.bindIndices();
                glDrawElements(s.primitive(), s.indicesCount(), GL_UNSIGNED_SHORT, 0);
                sb.unbind();
                indices = true;
            }
        }
        if (!indices) {
            glDrawElements(s.primitive(), s.indicesCount(), GL_UNSIGNED_SHORT, s.indices());
            RCheckGLError();
        }
    } else {
        glDrawArrays(s.primitive(), 0, s.verticesCount());
        RCheckGLError();
    }

    glDisableVertexAttribArray(d.mVariables["a_position"]);

    if (key.mHasTexture) {
        unbindTexture();
        glDisableVertexAttribArray(d.mVariables["a_texCoord"]);
    }

    if (key.mLightCount > 0) {
        glDisableVertexAttribArray(d.mVariables["a_normal"]);
    }

    d.mShader.unuse();
    RCheckGLError();
}

void RGles2Gc::drawSimple(RShape const & s, ShaderData const & d)
{
    glUniform4f(d.mVariables["u_color"], foregroundColor().r(), foregroundColor().g(),
                foregroundColor().b(), foregroundColor().a());
}

void RGles2Gc::drawTexture(RShape const & s, ShaderData const & d)
{
    glEnableVertexAttribArray(d.mVariables["a_texCoord"]);

    glActiveTexture(GL_TEXTURE0);
    bindTexture(data_p().mTexture);
    RCheckGLError();

    if (data_p().mTextureTransform) {
        glUniformMatrix3fv(d.mVariables["u_texMatrix"], 1, false, data_p().mTextureTransform->matrix3x3());
    }

    glUniform1i(d.mVariables["s_texture"], 0);

    bool buffer = false;
    if (s.hasBuffer()) {
        const RShapeBuffer & sb = s.getBuffer();
        if (sb.hasTexCoords()) {
            sb.bindTexCoords();
            RCheckGLError();
            glVertexAttribPointer(d.mVariables["a_texCoord"], 2, GL_FLOAT, GL_FALSE, 0, 0);
            RCheckGLError();
            sb.unbind();
            buffer = true;
        }
    }

    if (!buffer) {
        glVertexAttribPointer(d.mVariables["a_texCoord"], 2, GL_FLOAT, GL_FALSE, 0, s.texcoords());
    }
}

void RGles2Gc::drawLight(RShape const & s, ShaderData const & d)
{
    // normal matrix
	RTransformation mvMatrix = camera().transformation().multiply(transformation());
	RTransformation mat = mvMatrix.invertTranspose();

    glUniformMatrix4fv(d.mVariables["u_normalmatrix"], 1, false, mat.matrix().data());
    glUniformMatrix4fv(d.mVariables["u_mv_matrix"], 1, false, mvMatrix.matrix().data());

    glUniform3f(d.mVariables["u_viewer"], camera().eye().x(), camera().eye().y(), camera().eye().z());

    glUniform3f(d.mVariables["u_globalambient"], globalAmbientColor().r(), globalAmbientColor().g(), globalAmbientColor().b());

    // material properties
    glUniform3f(d.mVariables["u_material.ambient"], material().ambient().r(), material().ambient().g(), material().ambient().b());
    glUniform3f(d.mVariables["u_material.diffuse"], material().diffuse().r(), material().diffuse().g(), material().diffuse().b());
    glUniform3f(d.mVariables["u_material.specular"], material().specular().r(), material().specular().g(), material().specular().b());
    glUniform3f(d.mVariables["u_material.emissive"], material().emissive().r(), material().emissive().g(), material().emissive().b());
    glUniform1f(d.mVariables["u_material.specexp"], material().shininess());
    RCheckGLError();

    // lights properties
    int i = 1;
    for (LightsIter iter = data_p().mLights.begin(); iter != data_p().mLights.end(); ++iter, ++i) {
        const RLight &l = **iter;
        do {
            std::stringstream var;
            var << "u_light_" << i << ".ambient";
            glUniform3f(d.mVariables[var.str()], l.ambient().r(), l.ambient().g(), l.ambient().b());
        } while (0);

        do {
            std::stringstream var;
            var << "u_light_" << i << ".diffuse";
            glUniform3f(d.mVariables[var.str()], l.diffuse().r(), l.diffuse().g(), l.diffuse().b());
        } while (0);

        do {
            std::stringstream var;
            var << "u_light_" << i << ".specular";
           glUniform3f(d.mVariables[var.str()], l.specular().r(), l.specular().g(), l.specular().b());
        } while (0);

        do {
            std::stringstream var;
            var << "u_light_" << i << ".lightpos";
            glUniform3f(d.mVariables[var.str()], l.position().x(), l.position().y(), l.position().z());
        } while (0);

        if (!(*iter)->isDirectionLight()) {
            if ((*iter)->isSpotLight()) {
                std::stringstream spotdir;
                spotdir << "u_light_" << i << ".spotdir";
                glUniform3f(d.mVariables[spotdir.str()], l.direction().x(), l.direction().y(), l.direction().z());
                std::stringstream spotexp;
                spotexp << "u_light_" << i << ".spotexponent";
                glUniform1f(d.mVariables[spotexp.str()], l.spotExponent());
                std::stringstream spotcut;
                spotcut << "u_light_" << i << ".spotcutoff";
                glUniform1f(d.mVariables[spotcut.str()], l.spotCutoff());
            }
            // spot light and point light
            std::stringstream att1;
            att1 << "u_light_" << i << ".constatten";
            std::stringstream att2;
            att2 << "u_light_" << i << ".linearatten";
            std::stringstream att3;
            att3 << "u_light_" << i << ".quadatten";
            glUniform1f(d.mVariables[att1.str()], l.constAttenuation());
            glUniform1f(d.mVariables[att2.str()], l.linearAttenuation());
            glUniform1f(d.mVariables[att3.str()], l.quadAttenuation());
        }

    }

    // load normals
    glEnableVertexAttribArray(d.mVariables["a_normal"]);
    RCheckGLError();

    bool buffer = false;

    if (s.hasBuffer()) {
        const RShapeBuffer & sb = s.getBuffer();
        if (sb.hasNormals()) {
            sb.bindNormals();
            RCheckGLError();
            glVertexAttribPointer(d.mVariables["a_normal"], 3, GL_FLOAT, GL_FALSE, 0, 0);
            RCheckGLError();
            sb.unbind();
            buffer = true;
        }
    }

    if (!buffer) {
        glVertexAttribPointer(d.mVariables["a_normal"], 3, GL_FLOAT, GL_FALSE, 0, s.normals());
    }
}

void RGles2Gc::drawShadow(RShape const & s)
{
    if (s.hasPlane()) {
        const RShapePlane & sp = s.getPlane();
        if (!sp.isNull()) {
            for (LightsIter iter = data_p().mLights.begin();
                iter != data_p().mLights.end(); ++iter) {
                drawShadow(sp, (*iter)->position());
            }
        }
    }
}

void RGles2Gc::drawShadow(const RShapePlane & s, RVector const & lp)
{
    unsigned int    i, j, k, jj;
    unsigned int    p1, p2;
    RVector         v1, v2;
    float           side;

    enable(GL_POLYGON_OFFSET_FACTOR);
    enable(GL_POLYGON_OFFSET_UNITS);
    enable(GL_POLYGON_OFFSET_FILL);

    glPolygonOffset(-1.0f, -1.0f);

    //set visual parameter
    for (i=0; i<s.planes().size(); i++) {
        const RShapePlane::Plane & plane = s.at(i);
        side =  plane.mCoeffA*lp.x()+
                plane.mCoeffB*lp.y()+
                plane.mCoeffC*lp.z()+
                plane.mCoeffD*lp.w();
        if (side >0) {
            plane.mVisible = true;
        } else {
            plane.mVisible = false;
        }
    }

    glDepthMask(GL_FALSE);
    glDepthFunc(GL_LEQUAL);

    enable(GL_STENCIL_TEST);
    glColorMask(0, 0, 0, 0);
    glStencilFunc(GL_ALWAYS, 1, 0xffffffff);

    // first pass, stencil operation decreases stencil value
    glFrontFace(GL_CCW);
    glStencilOp(GL_KEEP, GL_KEEP, GL_INCR);

    for (i=0; i<s.planes().size();i++) {
        const RShapePlane::Plane & plane = s.at(i);
        if (plane.mVisible) {
            for (j=0;j<3;j++) {
                k = plane.mNeighIndex[j];
                if ((!k) || (!s.at(k-1).mVisible)) {
                    p1 = plane.mPointIndex[j];
                    jj = (j+1)%3;
                    p2 = plane.mPointIndex[jj];

                    v1.setX((s.point(p1).x() - lp.x())*100.0f);
                    v1.setY((s.point(p1).y() - lp.y())*100.0f);
                    v1.setZ((s.point(p1).z() - lp.z())*100.0f);

                    v2.setX((s.point(p2).x() - lp.x())*100.0f);
                    v2.setY((s.point(p2).y() - lp.y())*100.0f);
                    v2.setZ((s.point(p2).z() - lp.z())*100.0f);

                    float vertices[] = {
                        s.point(p1).x(), s.point(p1).y(), s.point(p1).z(),
                        s.point(p1).x() + v1.x(), s.point(p1).y() + v1.y(), s.point(p1).z() + v1.z(),
                        s.point(p2).x(), s.point(p2).y(), s.point(p2).z(),
                        s.point(p2).x() + v2.x(), s.point(p2).y() + v2.y(), s.point(p2).z() + v2.z()
                    };

                    ProgramKey key;
                    ShaderData d = getProgramUsingKey(key);
                    RSmartPointer<RMeshShape> shape = new RMeshShape();
                    shape->addVertices(vertices, (sizeof(vertices)/sizeof(vertices[0]))/3);
                    shape->setPrimitive(GL_TRIANGLE_STRIP);
                    draw(*(shape.data()), d, key);
                }
            }
        }
    }

    glFrontFace(GL_CW);
    glStencilOp(GL_KEEP, GL_KEEP, GL_DECR);

    for (i=0; i<s.planes().size();i++){
        const RShapePlane::Plane & plane = s.at(i);
        if (plane.mVisible) {
            for (j=0;j<3;j++){
                k = plane.mNeighIndex[j];
                if ((!k) || (!s.at(k-1).mVisible)){
                    p1 = plane.mPointIndex[j];
                    jj = (j+1)%3;
                    p2 = plane.mPointIndex[jj];

                    v1.setX((s.point(p1).x() - lp.x())*100.0f);
                    v1.setY((s.point(p1).y() - lp.y())*100.0f);
                    v1.setZ((s.point(p1).z() - lp.z())*100.0f);

                    v2.setX((s.point(p2).x() - lp.x())*100.0f);
                    v2.setY((s.point(p2).y() - lp.y())*100.0f);
                    v2.setZ((s.point(p2).z() - lp.z())*100.0f);

                    float vertices[] = {
                        s.point(p1).x(),
                        s.point(p1).y(),
                        s.point(p1).z(),
                        s.point(p1).x() + v1.x(),
                        s.point(p1).y() + v1.y(),
                        s.point(p1).z() + v1.z(),
                        s.point(p2).x(),
                        s.point(p2).y(),
                        s.point(p2).z(),
                        s.point(p2).x() + v2.x(),
                        s.point(p2).y() + v2.y(),
                        s.point(p2).z() + v2.z()
                    };

                    ProgramKey key;
                    ShaderData d = getProgramUsingKey(key);
                    RSmartPointer<RMeshShape> shape = new RMeshShape();
                    shape->addVertices(vertices, (sizeof(vertices)/sizeof(vertices[0]))/3);
                    shape->setPrimitive(GL_TRIANGLE_STRIP);
                    draw(*(shape.data()), d, key);
                }
            }
        }
    }

    glFrontFace(GL_CCW);
    glColorMask(1, 1, 1, 1);

    RColor oldFG = foregroundColor();

    setForegroundColor(RColor(0.0f, 0.0f, 0.0f, 0.4f));

    enable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glStencilFunc(GL_NOTEQUAL, 0, 0xffffffff);
    glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);

    float vertices[] = {
        -0.1f, 0.1f,-0.10f,
        -0.1f,-0.1f,-0.10f,
         0.1f, 0.1f,-0.10f,
         0.1f,-0.1f,-0.10f
    };

    ProgramKey key;
    ShaderData d = getProgramUsingKey(key);
    RSmartPointer<RMeshShape> shape = new RMeshShape();
    shape->addVertices(vertices, (sizeof(vertices)/sizeof(vertices[0]))/3);
    shape->setPrimitive(GL_TRIANGLE_STRIP);
    draw(*(shape.data()), d, key);

    setForegroundColor(oldFG);

    enable(GL_BLEND);
    glBlendEquation(GL_FUNC_ADD);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glDepthFunc(GL_LEQUAL);
    glDepthMask(GL_TRUE);
    disable(GL_STENCIL_TEST);

    disable(GL_POLYGON_OFFSET_FACTOR);
    disable(GL_POLYGON_OFFSET_UNITS);
    disable(GL_POLYGON_OFFSET_FILL);
}

}

