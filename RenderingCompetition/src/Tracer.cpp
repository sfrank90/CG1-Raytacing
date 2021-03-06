/*
* *********************************************
*
* Rendering Competition - CG1
*
* (c) 2014 by Alexander Knueppel & Sven Frank        
*
* *********************************************
*
*/

#include "../include/Random.h"
#include "../include/Tracer.h"
#include "../include/Ray.h"
#include "../include/cie.h"
#include "../include/Light.h"
#include "../include/Material.h"

void MySimpleTracer::computeJitters() {
	RandomFloat rnd;

	float aspect = static_cast<float>(mWidth)/static_cast<float>(mHeight);
	win_to_vp[0] = aspect/static_cast<float>(mWidth);
	win_to_vp[1] = 1.0f/static_cast<float>(mHeight);
	lower_left = glm::vec2(aspect*(-0.5f), -0.5f);
	step = win_to_vp/static_cast<float>(subdivs);

	jitter.resize(subdivs*subdivs, glm::vec2(0.5f)*win_to_vp);

	for(unsigned int i = 0; i < subdivs; ++i)
		for(unsigned int j = 1; j < subdivs; ++j) 
			jitter[i*subdivs + j] = glm::vec2(rnd() + j, rnd() + i)*step; 
}

void MySimpleTracer::incrementPixelSubdivs() {
	++subdivs;
	computeJitters();
}

void MySimpleTracer::decrementPixelSubdivs() {
	if(subdivs > 1) {
		--subdivs;
		computeJitters();
	}
}

glm::vec3 MySimpleTracer::calculatePixel(int x, int y) const {
  //glm::vec3 result(0.0);
  glm::vec2 vp_pos = glm::vec2(x, y)*win_to_vp + lower_left;

  float radiance[WAVELENGTHS] = {0.0f};
  glm::vec3 result(0.f);
  for(unsigned int i = 0; i < jitter.size(); ++i) {
	  Ray ray;
	  if(mScene->dof()) {
		  float angle = (jitter[i].x/win_to_vp.x) * constants::two_pi; 
          float radius = 0.5*jitter[i].y; 
          glm::vec2 offset(std::cos(angle) * radius, std::sin(angle) * radius);
		  mScene->getCamera()->initRay(vp_pos.x + 0.5f*win_to_vp.x,  vp_pos.y + 0.5f*win_to_vp.y, offset.x, offset.y, ray);
	  }
	  else {
		  mScene->getCamera()->initRay(vp_pos.x + jitter[i].x, vp_pos.y + jitter[i].y, ray);
	  }

	  // ====> logic goes here
	  result += traceRay(ray, glm::vec3(1.f));// + (globalIradiance(ray,3.f, 350)+causticIradiance(ray,2.f, 350));
  }

  return result / (float)jitter.size();
}

//glm::vec3 MySpectralTracer::calculatePixel(int x, int y) const {
//  //glm::vec3 result(0.0);
//  glm::vec2 vp_pos = glm::vec2(x, y)*win_to_vp + lower_left;
//
//  float radiance[WAVELENGTHS] = {0.0f};
//  glm::vec3 result(0.f);
//  for(unsigned int i = 0; i < jitter.size(); ++i) {
//	  Ray ray;
//	  if(mScene->dof()) {
//		  float angle = (jitter[i].x/win_to_vp.x) * constants::two_pi; 
//          float radius = 0.5*jitter[i].y; 
//          glm::vec2 offset(std::cos(angle) * radius, std::sin(angle) * radius);
//		  mScene->getCamera()->initRay(vp_pos.x + 0.5f*win_to_vp.x,  vp_pos.y + 0.5f*win_to_vp.y, offset.x, offset.y, ray);
//	  }
//	  else {
//		  mScene->getCamera()->initRay(vp_pos.x + jitter[i].x, vp_pos.y + jitter[i].y, ray);
//	  }
//	  //if nothing is hit just go to the next sample
//	  if (!mScene->intersect(ray)) 
//		  result += glm::vec3(0.f);//continue;
//	  else result += glm::vec3(1.f);
//	  //for (int w = 0; w < WAVELENGTHS; ++w) {
//			///* Get a radiance sample for this wavelength. */
//			//float wavelength = 380.0f + RESOLUTION * w;
//			//radiance[w] += estimateRadiance(ray, wavelength);
//	  //}
//  }
//  //using CIESystem
//  //glm::vec3 result = SpectrumToRGB(radiance, CIESystem) / (static_cast<float>(jitter.size()) * WAVELENGTHS);
//  //no radiance here...
//  //if(result == glm::vec3(0.f))
//	 // return mBackground;
//
//  return result / (float)jitter.size();
//}
//
//float MySpectralTracer::estimateRadiance(const Ray &ray, float wavelength) const {
//    /* Light path loop. */
//	RandomFloat rnd;
//	Ray newRay(ray);
//    while (true) {
//		if (!newRay.hasHit && !mScene->intersect(newRay)) 
//			 return 0.f;
//        /* Get the surface normal at the intersection point. */
//		glm::vec3 normal = newRay.hitNormal;
//
//        /* If the geometry intersected is a light source, return the emitted light. */
//		if (newRay.hitObject->isLight()) {
//            /* Note we assume light sources do not reflect light, this is usually correct. */
//			return newRay.hitObject->getLight()->emit(newRay, wavelength);
//        }
//
//		glm::vec3 exitant = newRay.getHitMaterial()->sample(newRay, wavelength);
//		float radiance = newRay.getHitMaterial()->brdf(newRay, exitant, wavelength, true);
//
//		if (glm::dot(newRay.dir,normal) > 0.0f) 
//			radiance *= exp(-newRay.t * newRay.getHitMaterial()->mExtinctionInside);
//		else 
//			radiance *= exp(-newRay.t * newRay.getHitMaterial()->mExtinctionOutside);
//
//        /* Russian roulette for unbiased depth. Note this means the loop is guaranteed to terminate, since the
//         * reflectance is defined as being strictly less than 1. */
//        if (rnd() > radiance) 
//			return 0.0f;
//
//        /* Go to the next ray bounce. */
//		newRay = Ray(newRay.getHitPoint() + newRay.hitNormal*(float)constants::epsilon, glm::normalize(exitant));
//    }
//
//    /* No light path formed. */
//    return 0.0f;
//}

//const Shader *RayCaster::getShader(const geometry::Ray &ray) const {
//	return mScene->getShader(ray);
//}
